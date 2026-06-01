#include <stdio.h>
#include <stdlib.h>

// A matriz guarda suas dimensoes e um ponteiro duplo "dados".
// O ponteiro duplo aponta para um vetor de ponteiros — cada
// posicao desse vetor aponta para uma linha (vetor de inteiros).
typedef struct Matriz {
    int linhas;
    int colunas;
    int** dados;
} Matriz;

// Cria uma matriz com "linhas" x "colunas" inteiros, todos zerados.
// A alocacao acontece em duas camadas:
//   1) o vetor externo, com um ponteiro por linha;
//   2) cada linha, com um vetor de inteiros.
Matriz* matriz_criar(int linhas, int colunas) {
    Matriz* m = malloc(sizeof(Matriz));
    if (m == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    m->linhas = linhas;
    m->colunas = colunas;

    // Camada 1: vetor externo com "linhas" ponteiros para int.
    // Cada ponteiro desse vetor vai apontar para uma linha
    // alocada na camada 2.
    m->dados = malloc(linhas * sizeof(int*));
    if (m->dados == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }

    // Camada 2: para cada linha, alocamos um vetor de "colunas"
    // inteiros e zeramos as celulas. Sao "linhas" mallocs aqui,
    // mais o malloc do vetor externo, totalizando linhas + 1.
    for (int i = 0; i < linhas; i++) {
        m->dados[i] = malloc(colunas * sizeof(int));
        if (m->dados[i] == NULL) {
            printf("erro: memoria insuficiente\n");
            exit(1);
        }
        for (int j = 0; j < colunas; j++) {
            m->dados[i][j] = 0;
        }
    }
    return m;
}

// Devolve o numero de linhas da matriz.
int matriz_linhas(Matriz* m) {
    return m->linhas;
}

// Devolve o numero de colunas da matriz.
int matriz_colunas(Matriz* m) {
    return m->colunas;
}

// Atribui "valor" a celula (i, j) da matriz.
// Pre-condicao: 0 <= i < linhas e 0 <= j < colunas.
// A expressao m->dados[i][j] e' equivalente a *(*(m->dados + i) + j):
// duas indirecoes — primeiro pegamos a linha i, depois a coluna j.
void matriz_definir(Matriz* m, int i, int j, int valor) {
    m->dados[i][j] = valor;
}

// Devolve o inteiro armazenado em (i, j).
// Pre-condicao: 0 <= i < linhas e 0 <= j < colunas.
int matriz_obter(Matriz* m, int i, int j) {
    return m->dados[i][j];
}

// Imprime a matriz no formato "[ v00 v01 ... ]" linha por linha,
// alinhando cada celula em 3 colunas de largura.
void matriz_imprimir(Matriz* m) {
    for (int i = 0; i < m->linhas; i++) {
        printf("[ ");
        for (int j = 0; j < m->colunas; j++) {
            printf("%3d ", m->dados[i][j]);
        }
        printf("]\n");
    }
}

// Libera TODA a memoria da matriz, na ordem inversa da alocacao:
//   1) cada linha (free de cada vetor de inteiros);
//   2) o vetor externo de ponteiros;
//   3) a propria struct Matriz.
// Inverter essa ordem — liberar o vetor externo antes das linhas —
// causaria vazamento de memoria, porque perderiamos os enderecos
// das linhas antes de libera-las.
void matriz_destruir(Matriz* m) {
    for (int i = 0; i < m->linhas; i++) {
        free(m->dados[i]);
    }
    free(m->dados);
    free(m);
}

// Programa demonstrativo: cria uma matriz 3x4, define algumas
// celulas, le uma celula sem alterar, imprime estados intermediarios
// e libera tudo no final.
int main(void) {
    Matriz* m = matriz_criar(3, 4);

    printf("Matriz recem criada (3x4, zerada):\n");
    matriz_imprimir(m);

    matriz_definir(m, 0, 1, 7);
    matriz_definir(m, 2, 3, 5);
    matriz_definir(m, 1, 0, 9);

    printf("\nApos definir (0,1)=7, (2,3)=5 e (1,0)=9:\n");
    matriz_imprimir(m);

    printf("\nObter (2,3) = %d (a matriz nao muda)\n",
           matriz_obter(m, 2, 3));

    printf("\nDimensoes: %d linhas x %d colunas\n",
           matriz_linhas(m), matriz_colunas(m));

    matriz_destruir(m);
    return 0;
}
