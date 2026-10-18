/*
 * Lógica do jogo, compilada para WebAssembly sem biblioteca padrão.
 * O JavaScript informa teclas, obstáculos e pontos de interação; este arquivo move o personagem,
 * resolve colisões e calcula as matrizes 4x4 (em ordem de coluna, como o WebGPU espera) que a GPU desenha.
 */

#define EXPORTAR(nome) __attribute__((export_name(nome)))
#define VEM_DO_JAVASCRIPT(nome) __attribute__((import_module("matematica"), import_name(nome)))

VEM_DO_JAVASCRIPT("sin") float seno(float angulo);
VEM_DO_JAVASCRIPT("cos") float cosseno(float angulo);
VEM_DO_JAVASCRIPT("atan2") float arco_tangente(float y, float x);

#define PI 3.14159265f
#define MAX_OBSTACULOS 64
#define MAX_PONTOS_DE_INTERACAO 16
#define RAIO_DO_PERSONAGEM 0.3f
#define METROS_POR_SEGUNDO 3.5f
#define MAIOR_INTERVALO_DE_TEMPO 0.05f /* um passo maior, após uma pausa longa, poderia atravessar uma parede fina */
#define ALTURA_DO_ASSENTO 0.5f
#define INCLINACAO_DA_CAMERA (58.0f * PI / 180.0f)
#define DISTANCIA_DA_CAMERA 16.0f
#define ABERTURA_DA_CAMERA (40.0f * PI / 180.0f)

enum Parte { TRONCO, CABECA, BRACO_ESQUERDO, BRACO_DIREITO, PERNA_ESQUERDA, PERNA_DIREITA, TOTAL_DE_PARTES };

typedef struct {
    float x_min, z_min, x_max, z_max;
} Retangulo;

typedef struct {
    float x, z, raio;
} PontoDeInteracao;

static Retangulo obstaculos[MAX_OBSTACULOS];
static int total_de_obstaculos;
static PontoDeInteracao pontos_de_interacao[MAX_PONTOS_DE_INTERACAO];
static int total_de_pontos_de_interacao;

static float posicao_x, posicao_z, direcao;
static float posicao_antes_de_sentar_x, posicao_antes_de_sentar_z;
static int sentado;
static float fase_do_passo, forca_do_passo;
static float camera_x, camera_z;

static float matriz_da_camera_atual[16];
static float repouso_das_partes[TOTAL_DE_PARTES][16];
static float matrizes_das_partes[TOTAL_DE_PARTES][16];

static float raiz_quadrada(float valor)
{
    return __builtin_sqrtf(valor);
}

static float aproximar(float atual, float alvo, float passo_maximo)
{
    if (atual < alvo) return atual + passo_maximo < alvo ? atual + passo_maximo : alvo;
    return atual - passo_maximo > alvo ? atual - passo_maximo : alvo;
}

static void identidade(float *m)
{
    for (int i = 0; i < 16; i++) m[i] = (i % 5 == 0) ? 1.0f : 0.0f;
}

/* resultado = a * b; resultado precisa ser um vetor diferente de a e de b. */
static void multiplicar(float *resultado, float *a, float *b)
{
    for (int coluna = 0; coluna < 4; coluna++) {
        for (int linha = 0; linha < 4; linha++) {
            float soma = 0.0f;
            for (int k = 0; k < 4; k++) soma += a[k * 4 + linha] * b[coluna * 4 + k];
            resultado[coluna * 4 + linha] = soma;
        }
    }
}

static void translacao(float *m, float x, float y, float z)
{
    identidade(m);
    m[12] = x;
    m[13] = y;
    m[14] = z;
}

static void rotacao_x(float *m, float angulo)
{
    identidade(m);
    m[5] = cosseno(angulo);
    m[6] = seno(angulo);
    m[9] = -seno(angulo);
    m[10] = cosseno(angulo);
}

static void rotacao_y(float *m, float angulo)
{
    identidade(m);
    m[0] = cosseno(angulo);
    m[2] = -seno(angulo);
    m[8] = seno(angulo);
    m[10] = cosseno(angulo);
}

/* Projeção em perspectiva com profundidade de 0 a 1, o intervalo do WebGPU. */
static void perspectiva(float *m, float abertura, float proporcao, float perto, float longe)
{
    float foco = cosseno(abertura / 2) / seno(abertura / 2);
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[0] = foco / proporcao;
    m[5] = foco;
    m[10] = longe / (perto - longe);
    m[11] = -1.0f;
    m[14] = perto * longe / (perto - longe);
}

static int colide(float x, float z)
{
    for (int i = 0; i < total_de_obstaculos; i++) {
        Retangulo *o = &obstaculos[i];
        if (x + RAIO_DO_PERSONAGEM > o->x_min && x - RAIO_DO_PERSONAGEM < o->x_max &&
            z + RAIO_DO_PERSONAGEM > o->z_min && z - RAIO_DO_PERSONAGEM < o->z_max) {
            return 1;
        }
    }
    return 0;
}

/* Testa cada eixo separado: ao bater numa parede andando na diagonal, o personagem desliza rente a ela. */
static void mover_sem_atravessar(float passo_x, float passo_z)
{
    if (!colide(posicao_x + passo_x, posicao_z)) posicao_x += passo_x;
    if (!colide(posicao_x, posicao_z + passo_z)) posicao_z += passo_z;
}

/* Move na direção das teclas, com a mesma velocidade também na diagonal, e avança o balanço dos passos. */
static void andar(float segundos, float entrada_x, float entrada_z)
{
    float comprimento = raiz_quadrada(entrada_x * entrada_x + entrada_z * entrada_z);
    if (comprimento < 0.01f) {
        forca_do_passo = aproximar(forca_do_passo, 0.0f, segundos * 6.0f);
        return;
    }

    float distancia = METROS_POR_SEGUNDO * segundos / comprimento;
    mover_sem_atravessar(entrada_x * distancia, entrada_z * distancia);

    direcao = arco_tangente(entrada_x, entrada_z);
    fase_do_passo += segundos * 10.0f;
    if (fase_do_passo > 2 * PI) fase_do_passo -= 2 * PI;
    forca_do_passo = aproximar(forca_do_passo, 1.0f, segundos * 6.0f);
}

static void seguir_personagem(float segundos)
{
    float suavidade = segundos * 5.0f;
    if (suavidade > 1.0f) suavidade = 1.0f;
    camera_x += (posicao_x - camera_x) * suavidade;
    camera_z += (posicao_z - camera_z) * suavidade;
}

/* A câmera fica atrás e acima do personagem; girar o mundo pela inclinação faz a câmera olhar para baixo. */
static void montar_camera(float proporcao_da_tela)
{
    float projecao[16], inclinacao[16], recuo[16], vista[16];
    float olho_y = DISTANCIA_DA_CAMERA * seno(INCLINACAO_DA_CAMERA);
    float olho_z = camera_z + DISTANCIA_DA_CAMERA * cosseno(INCLINACAO_DA_CAMERA);

    perspectiva(projecao, ABERTURA_DA_CAMERA, proporcao_da_tela, 0.1f, 100.0f);
    rotacao_x(inclinacao, INCLINACAO_DA_CAMERA);
    translacao(recuo, -camera_x, -olho_y, -olho_z);
    multiplicar(vista, inclinacao, recuo);
    multiplicar(matriz_da_camera_atual, projecao, vista);
}

/* Ângulo em torno do eixo X da articulação; negativo leva o membro para a frente do personagem. */
static float angulo_da_parte(int parte, float balanco)
{
    if (sentado) {
        if (parte == PERNA_ESQUERDA || parte == PERNA_DIREITA) return -PI / 2;
        if (parte == BRACO_ESQUERDO || parte == BRACO_DIREITO) return -PI / 3;
        return 0.0f;
    }
    if (parte == PERNA_ESQUERDA || parte == BRACO_DIREITO) return balanco;
    if (parte == PERNA_DIREITA || parte == BRACO_ESQUERDO) return -balanco;
    return 0.0f;
}

/* Matriz de cada parte = raiz (posição e direção) x repouso x giro da articulação; sentado, o quadril desce até o assento. */
static void montar_pose(void)
{
    float deslocamento[16], giro[16], raiz[16], parcial[16], articulacao[16];
    float balanco = seno(fase_do_passo) * 0.7f * forca_do_passo;
    float altura = 0.0f;

    if (sentado) altura = ALTURA_DO_ASSENTO - repouso_das_partes[PERNA_ESQUERDA][13];

    translacao(deslocamento, posicao_x, altura, posicao_z);
    rotacao_y(giro, direcao);
    multiplicar(raiz, deslocamento, giro);

    for (int parte = 0; parte < TOTAL_DE_PARTES; parte++) {
        rotacao_x(articulacao, angulo_da_parte(parte, balanco));
        multiplicar(parcial, raiz, repouso_das_partes[parte]);
        multiplicar(matrizes_das_partes[parte], parcial, articulacao);
    }
}

/* Devolve 0 quando não cabe mais nenhum obstáculo, para o JavaScript avisar em vez de ignorar em silêncio. */
EXPORTAR("adicionar_obstaculo")
int adicionar_obstaculo(float x_min, float z_min, float x_max, float z_max)
{
    if (total_de_obstaculos == MAX_OBSTACULOS) return 0;
    obstaculos[total_de_obstaculos] = (Retangulo){x_min, z_min, x_max, z_max};
    total_de_obstaculos++;
    return 1;
}

/* Devolve o número do ponto, usado depois por ponto_de_interacao_proximo, ou -1 se não houver espaço. */
EXPORTAR("adicionar_ponto_de_interacao")
int adicionar_ponto_de_interacao(float x, float z, float raio)
{
    if (total_de_pontos_de_interacao == MAX_PONTOS_DE_INTERACAO) return -1;
    pontos_de_interacao[total_de_pontos_de_interacao] = (PontoDeInteracao){x, z, raio};
    total_de_pontos_de_interacao++;
    return total_de_pontos_de_interacao - 1;
}

EXPORTAR("ponto_de_interacao_proximo")
int ponto_de_interacao_proximo(void)
{
    int mais_proximo = -1;
    float menor_distancia = 0.0f;
    for (int i = 0; i < total_de_pontos_de_interacao; i++) {
        float dx = pontos_de_interacao[i].x - posicao_x;
        float dz = pontos_de_interacao[i].z - posicao_z;
        float distancia = raiz_quadrada(dx * dx + dz * dz);
        if (distancia > pontos_de_interacao[i].raio) continue;
        if (mais_proximo == -1 || distancia < menor_distancia) {
            mais_proximo = i;
            menor_distancia = distancia;
        }
    }
    return mais_proximo;
}

/* Coloca o personagem sobre o assento, virado para o alvo, e guarda onde ele estava para levantar depois. */
EXPORTAR("sentar")
void sentar(float assento_x, float assento_z, float alvo_x, float alvo_z)
{
    if (!sentado) {
        posicao_antes_de_sentar_x = posicao_x;
        posicao_antes_de_sentar_z = posicao_z;
    }
    sentado = 1;
    forca_do_passo = 0.0f;
    posicao_x = assento_x;
    posicao_z = assento_z;
    direcao = arco_tangente(alvo_x - assento_x, alvo_z - assento_z);
}

EXPORTAR("levantar")
void levantar(void)
{
    if (!sentado) return;
    sentado = 0;
    posicao_x = posicao_antes_de_sentar_x;
    posicao_z = posicao_antes_de_sentar_z;
}

/* Avança o jogo; entrada_x e entrada_z vão de -1 a 1 (direita e sul positivos). */
EXPORTAR("atualizar")
void atualizar(float segundos, float entrada_x, float entrada_z, float proporcao_da_tela)
{
    if (segundos > MAIOR_INTERVALO_DE_TEMPO) segundos = MAIOR_INTERVALO_DE_TEMPO;
    if (!sentado) andar(segundos, entrada_x, entrada_z);
    seguir_personagem(segundos);
    montar_camera(proporcao_da_tela);
    montar_pose();
}

EXPORTAR("matriz_da_camera")
float *matriz_da_camera(void)
{
    return matriz_da_camera_atual;
}

/* O JavaScript escreve aqui a matriz de repouso de cada parte, lida do personagem exportado pelo Blender. */
EXPORTAR("repouso_da_parte")
float *repouso_da_parte(int parte)
{
    return repouso_das_partes[parte];
}

EXPORTAR("matriz_da_parte")
float *matriz_da_parte(int parte)
{
    return matrizes_das_partes[parte];
}
