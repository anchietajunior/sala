#include <stdio.h>
#include <stdlib.h>

// Cada no da arvore tem um valor e dois ponteiros para os filhos.
// Quando um filho nao existe, o ponteiro correspondente e' NULL.
typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
} No;

// A arvore guarda apenas o ponteiro para a raiz. Toda a estrutura
// e' alcancada descendo pelos campos esq e dir a partir dela.
typedef struct Arvore {
    No* raiz;
} Arvore;

// Cria uma arvore vazia.
Arvore* arvore_criar(void) {
    Arvore* a = malloc(sizeof(Arvore));
    if (a == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    a->raiz = NULL;
    return a;
}

// Verdadeiro (1) se a arvore nao tem nenhum no.
int arvore_vazia(Arvore* a) {
    return a->raiz == NULL;
}

// Funcao auxiliar recursiva da insercao. Recebe a raiz de uma
// subarvore (que pode ser NULL) e o valor a inserir. Devolve a
// raiz da subarvore — possivelmente um no recem-criado.
static No* inserir_no(No* raiz, int valor) {
    // Caso base: subarvore vazia. Aloca o no novo aqui.
    if (raiz == NULL) {
        No* novo = malloc(sizeof(No));
        if (novo == NULL) {
            printf("erro: memoria insuficiente\n");
            exit(1);
        }
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    // Chave ja existe — ignoramos duplicatas nesta versao.
    if (valor == raiz->valor) {
        return raiz;
    }
    // Decide o lado da descida segundo a propriedade da BST:
    // menor vai para a esquerda, maior vai para a direita.
    if (valor < raiz->valor) {
        raiz->esq = inserir_no(raiz->esq, valor);
    } else {
        raiz->dir = inserir_no(raiz->dir, valor);
    }
    return raiz;
}

// Insere um valor na arvore mantendo a propriedade da BST.
// Duplicatas sao ignoradas silenciosamente.
void arvore_inserir(Arvore* a, int valor) {
    a->raiz = inserir_no(a->raiz, valor);
}

// Funcao auxiliar recursiva da busca.
static int buscar_no(No* raiz, int valor) {
    // Caso base: chegamos a um ponteiro NULL sem encontrar.
    if (raiz == NULL) {
        return 0;
    }
    if (valor == raiz->valor) {
        return 1;
    }
    // Cada comparacao descarta metade da arvore.
    if (valor < raiz->valor) {
        return buscar_no(raiz->esq, valor);
    } else {
        return buscar_no(raiz->dir, valor);
    }
}

// Verdadeiro (1) se o valor esta na arvore.
int arvore_buscar(Arvore* a, int valor) {
    return buscar_no(a->raiz, valor);
}

// As tres travessias seguem o mesmo esqueleto recursivo
// e diferem apenas na ordem das tres linhas internas.

// Pre-ordem: no, esquerda, direita.
static void pre_ordem_no(No* raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->valor);
    pre_ordem_no(raiz->esq);
    pre_ordem_no(raiz->dir);
}

// In-ordem: esquerda, no, direita.
// Em uma BST, esta travessia imprime os valores em ordem crescente.
static void in_ordem_no(No* raiz) {
    if (raiz == NULL) return;
    in_ordem_no(raiz->esq);
    printf("%d ", raiz->valor);
    in_ordem_no(raiz->dir);
}

// Pos-ordem: esquerda, direita, no.
// E' a ordem natural para liberar memoria — quando o no e' visitado,
// seus dois filhos ja foram visitados.
static void pos_ordem_no(No* raiz) {
    if (raiz == NULL) return;
    pos_ordem_no(raiz->esq);
    pos_ordem_no(raiz->dir);
    printf("%d ", raiz->valor);
}

void arvore_pre_ordem(Arvore* a) {
    pre_ordem_no(a->raiz);
    printf("\n");
}

void arvore_in_ordem(Arvore* a) {
    in_ordem_no(a->raiz);
    printf("\n");
}

void arvore_pos_ordem(Arvore* a) {
    pos_ordem_no(a->raiz);
    printf("\n");
}

// Funcao auxiliar recursiva que libera todos os nos da subarvore.
// Usa pos-ordem porque os filhos precisam ser liberados ANTES do pai —
// se libertarmos o pai primeiro, perdemos o caminho para os filhos.
static void destruir_no(No* raiz) {
    if (raiz == NULL) return;
    destruir_no(raiz->esq);
    destruir_no(raiz->dir);
    free(raiz);
}

// Libera toda a memoria usada pela arvore.
void arvore_destruir(Arvore* a) {
    destruir_no(a->raiz);
    free(a);
}

// Programa demonstrativo.
int main(void) {
    Arvore* a = arvore_criar();

    // Insercoes: a raiz vira 50; 30 e 70 viram filhos; 20 e 40
    // viram netos pela esquerda. A arvore final tem altura 2.
    arvore_inserir(a, 50);
    arvore_inserir(a, 30);
    arvore_inserir(a, 70);
    arvore_inserir(a, 20);
    arvore_inserir(a, 40);

    printf("Buscar 40: %s\n", arvore_buscar(a, 40) ? "encontrado" : "nao encontrado");
    printf("Buscar 99: %s\n", arvore_buscar(a, 99) ? "encontrado" : "nao encontrado");

    printf("Pre-ordem: ");
    arvore_pre_ordem(a);

    printf("In-ordem:  ");
    arvore_in_ordem(a);

    printf("Pos-ordem: ");
    arvore_pos_ordem(a);

    arvore_destruir(a);
    return 0;
}
