#include <stdio.h>
#include <stdlib.h>

// Cada no guarda uma chave e dois ponteiros: um para o filho da
// esquerda e outro para o filho da direita. Filho ausente vale NULL.
typedef struct No {
    int chave;
    struct No* esq;
    struct No* dir;
} No;

// Aloca um no sem filhos. Quem chama decide onde ligar o no.
No* criar_no(int chave) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Imprime a arvore como um sumario: cada nivel recua 4 espacos e o
// rotulo diz se o no e' filho da esquerda (E) ou da direita (D).
void imprimir_arvore(No* no, int nivel, char* rotulo) {
    if (no == NULL) return;
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("%s%d\n", rotulo, no->chave);
    imprimir_arvore(no->esq, nivel + 1, "E: ");
    imprimir_arvore(no->dir, nivel + 1, "D: ");
}

// Pre-ordem: o no e' visitado antes dos seus filhos.
void pre_ordem(No* no) {
    if (no == NULL) return;
    printf("%d ", no->chave);
    pre_ordem(no->esq);
    pre_ordem(no->dir);
}

// Em ordem: a esquerda inteira, depois o no, depois a direita.
// Numa arvore binaria de busca, as chaves saem em ordem crescente.
void em_ordem(No* no) {
    if (no == NULL) return;
    em_ordem(no->esq);
    printf("%d ", no->chave);
    em_ordem(no->dir);
}

// Pos-ordem: o no e' visitado depois dos seus filhos.
void pos_ordem(No* no) {
    if (no == NULL) return;
    pos_ordem(no->esq);
    pos_ordem(no->dir);
    printf("%d ", no->chave);
}

// Libera os filhos antes do pai: depois do free do pai, os campos
// esq e dir nao podem mais ser lidos.
void destruir_arvore(No* no) {
    if (no == NULL) return;
    destruir_arvore(no->esq);
    destruir_arvore(no->dir);
    free(no);
}

// Desce comparando: cada comparacao descarta um dos lados inteiro.
No* abb_buscar(No* raiz, int chave) {
    if (raiz == NULL) return NULL;
    if (chave == raiz->chave) {
        return raiz;
    }
    if (chave < raiz->chave) {
        return abb_buscar(raiz->esq, chave);
    }
    return abb_buscar(raiz->dir, chave);
}

// Desce como na busca ate um lugar vazio (NULL) e liga ali o no
// novo. Devolve a raiz da subarvore, que so muda se ela estava vazia.
No* abb_inserir(No* raiz, int chave) {
    if (raiz == NULL) return criar_no(chave);
    if (chave < raiz->chave) {
        raiz->esq = abb_inserir(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = abb_inserir(raiz->dir, chave);
    }
    return raiz;
}

// Pre-condicao: raiz diferente de NULL. A menor chave esta no fim do
// caminho que sempre segue para a esquerda.
No* abb_minimo(No* raiz) {
    No* atual = raiz;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

// Remove a chave e devolve a nova raiz da subarvore.
No* abb_remover(No* raiz, int chave) {
    if (raiz == NULL) return NULL;
    if (chave < raiz->chave) {
        raiz->esq = abb_remover(raiz->esq, chave);
        return raiz;
    }
    if (chave > raiz->chave) {
        raiz->dir = abb_remover(raiz->dir, chave);
        return raiz;
    }
    // Zero ou um filho: o filho que existe (ou NULL) ocupa o lugar do no.
    if (raiz->esq == NULL) {
        No* filho = raiz->dir;
        free(raiz);
        return filho;
    }
    if (raiz->dir == NULL) {
        No* filho = raiz->esq;
        free(raiz);
        return filho;
    }
    // Dois filhos: o sucessor, menor chave da direita, copia a chave para
    // ca e sai da subarvore direita, onde tem no maximo um filho.
    No* sucessor = abb_minimo(raiz->dir);
    raiz->chave = sucessor->chave;
    raiz->dir = abb_remover(raiz->dir, sucessor->chave);
    return raiz;
}

#define PRETO 0
#define VERMELHO 1

// O no da arvore rubro-negra e' o no da arvore binaria com uma cor.
typedef struct NoRB {
    int chave;
    int cor;
    struct NoRB* esq;
    struct NoRB* dir;
} NoRB;

// Todo no novo nasce vermelho: assim ele nao altera a quantidade
// de nos pretos de nenhum caminho da arvore.
NoRB* rb_criar_no(int chave) {
    NoRB* novo = malloc(sizeof(NoRB));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->chave = chave;
    novo->cor = VERMELHO;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// NULL conta como preto: e' o NIL da definicao.
int eh_vermelho(NoRB* no) {
    if (no == NULL) return 0;
    return no->cor == VERMELHO;
}

// O filho da direita sobe e o no desce para a esquerda dele.
// A ordem das chaves (esquerda < no < direita) continua valendo.
NoRB* rotacionar_esquerda(NoRB* no) {
    NoRB* filho = no->dir;
    no->dir = filho->esq;
    filho->esq = no;
    filho->cor = no->cor;
    no->cor = VERMELHO;
    return filho;
}

// Espelho da rotacao anterior: o filho da esquerda sobe.
NoRB* rotacionar_direita(NoRB* no) {
    NoRB* filho = no->esq;
    no->esq = filho->dir;
    filho->dir = no;
    filho->cor = no->cor;
    no->cor = VERMELHO;
    return filho;
}

// Dois filhos vermelhos: o vermelho sobe para o pai.
void inverter_cores(NoRB* no) {
    no->cor = VERMELHO;
    no->esq->cor = PRETO;
    no->dir->cor = PRETO;
}

// Insere como na arvore de busca e, na volta da recursao, corrige as
// cores de baixo para cima, sempre nesta ordem.
NoRB* rb_inserir_no(NoRB* no, int chave) {
    if (no == NULL) return rb_criar_no(chave);
    if (chave < no->chave) {
        no->esq = rb_inserir_no(no->esq, chave);
    } else if (chave > no->chave) {
        no->dir = rb_inserir_no(no->dir, chave);
    }
    if (eh_vermelho(no->dir) && !eh_vermelho(no->esq)) {
        no = rotacionar_esquerda(no);
    }
    if (eh_vermelho(no->esq) && eh_vermelho(no->esq->esq)) {
        no = rotacionar_direita(no);
    }
    if (eh_vermelho(no->esq) && eh_vermelho(no->dir)) {
        inverter_cores(no);
    }
    return no;
}

// A raiz e' sempre preta.
NoRB* rb_inserir(NoRB* raiz, int chave) {
    raiz = rb_inserir_no(raiz, chave);
    raiz->cor = PRETO;
    return raiz;
}

// Mesmo sumario de imprimir_arvore, com a cor de cada no.
void imprimir_rubro_negra(NoRB* no, int nivel, char* rotulo) {
    if (no == NULL) return;
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    if (no->cor == VERMELHO) {
        printf("%s%d (vermelho)\n", rotulo, no->chave);
    } else {
        printf("%s%d (preto)\n", rotulo, no->chave);
    }
    imprimir_rubro_negra(no->esq, nivel + 1, "E: ");
    imprimir_rubro_negra(no->dir, nivel + 1, "D: ");
}

void destruir_rubro_negra(NoRB* no) {
    if (no == NULL) return;
    destruir_rubro_negra(no->esq);
    destruir_rubro_negra(no->dir);
    free(no);
}

// Sete nos criados um a um e ligados pelos ponteiros esq e dir.
void demonstrar_arvore_montada_a_mao(void) {
    No* n50 = criar_no(50);
    No* n30 = criar_no(30);
    No* n70 = criar_no(70);
    No* n20 = criar_no(20);
    No* n40 = criar_no(40);
    No* n60 = criar_no(60);
    No* n80 = criar_no(80);

    n50->esq = n30;
    n50->dir = n70;
    n30->esq = n20;
    n30->dir = n40;
    n70->esq = n60;
    n70->dir = n80;

    printf("== Arvore montada a mao ==\n");
    imprimir_arvore(n50, 0, "raiz: ");
    printf("Pre-ordem: ");
    pre_ordem(n50);
    printf("\nEm ordem:  ");
    em_ordem(n50);
    printf("\nPos-ordem: ");
    pos_ordem(n50);
    printf("\n");
    destruir_arvore(n50);
}

void mostrar_busca(No* raiz, int chave) {
    if (abb_buscar(raiz, chave) != NULL) {
        printf("Buscar %d: encontrado\n", chave);
    } else {
        printf("Buscar %d: nao encontrado\n", chave);
    }
}

// As mesmas chaves, agora posicionadas pela regra da arvore de busca.
void demonstrar_arvore_de_busca(void) {
    int chaves[] = {50, 30, 70, 20, 40, 60, 80};
    No* raiz = NULL;
    for (int i = 0; i < 7; i++) {
        raiz = abb_inserir(raiz, chaves[i]);
    }
    printf("\n== Arvore binaria de busca ==\n");
    mostrar_busca(raiz, 60);
    mostrar_busca(raiz, 65);

    raiz = abb_inserir(raiz, 65);
    raiz = abb_remover(raiz, 20);
    raiz = abb_remover(raiz, 30);
    raiz = abb_remover(raiz, 50);
    printf("Depois de inserir 65 e remover 20, 30 e 50:\n");
    imprimir_arvore(raiz, 0, "raiz: ");
    destruir_arvore(raiz);
}

// Chaves em ordem crescente: o pior caso da arvore de busca comum.
void demonstrar_rubro_negra(void) {
    No* abb = NULL;
    NoRB* rubro_negra = NULL;
    for (int chave = 10; chave <= 50; chave = chave + 10) {
        abb = abb_inserir(abb, chave);
        rubro_negra = rb_inserir(rubro_negra, chave);
    }
    printf("\n== Inserindo 10, 20, 30, 40, 50 ==\n");
    printf("Arvore de busca comum:\n");
    imprimir_arvore(abb, 0, "raiz: ");
    printf("Arvore rubro-negra:\n");
    imprimir_rubro_negra(rubro_negra, 0, "raiz: ");
    destruir_arvore(abb);
    destruir_rubro_negra(rubro_negra);
}

int main(void) {
    demonstrar_arvore_montada_a_mao();
    demonstrar_arvore_de_busca();
    demonstrar_rubro_negra();
    return 0;
}
