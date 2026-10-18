#include <stdio.h>
#include <stdlib.h>

// No com dois ponteiros: anterior e proximo.
// O ponteiro anterior nao e' usado pela Fila pura, mas deixa
// a estrutura preparada para extensoes (Deque, remocao no meio).
typedef struct No {
    int valor;
    struct No* anterior;
    struct No* proximo;
} No;

// A fila ainda mantem inicio e fim, como na versao simples.
typedef struct Fila {
    No* inicio;
    No* fim;
} Fila;

Fila* criar(void) {
    Fila* f = malloc(sizeof(Fila));
    if (f == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int vazia(Fila* f) {
    return f->inicio == NULL;
}

void enfileirar(Fila* f, int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = f->fim;   // o anterior do novo e' o antigo fim

    if (vazia(f)) {
        // Fila estava vazia: o novo no tambem e' a frente.
        f->inicio = novo;
    } else {
        // Liga o no que era o fim ao novo no (sentido proximo).
        f->fim->proximo = novo;
    }
    f->fim = novo;
}

int desenfileirar(Fila* f) {
    if (vazia(f)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    No* removido = f->inicio;
    int valor = removido->valor;

    f->inicio = removido->proximo;
    if (f->inicio == NULL) {
        // Removemos o ultimo: zera o fim tambem.
        // Mesmo cuidado da versao simples: nao deixar fim apontando
        // para memoria que vai ser liberada com free() abaixo.
        f->fim = NULL;
    } else {
        // O novo inicio nao tem mais ninguem antes dele.
        f->inicio->anterior = NULL;
    }
    free(removido);
    return valor;
}

int frente(Fila* f) {
    if (vazia(f)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    return f->inicio->valor;
}

void destruir(Fila* f) {
    No* atual = f->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(f);
}

// A main e' literalmente identica a do fila.c — mesmo cliente,
// outra representacao interna.
int main(void) {
    Fila* f = criar();

    enfileirar(f, 10);
    enfileirar(f, 20);
    enfileirar(f, 30);
    printf("Frente da fila: %d\n", frente(f));

    printf("Desenfileirando: ");
    while (!vazia(f)) {
        printf("%d ", desenfileirar(f));
    }
    printf("\n");

    destruir(f);
    return 0;
}
