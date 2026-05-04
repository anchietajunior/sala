#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Otimizacao de Tenenbaum (cap. 5): a fila mantem
// APENAS o ponteiro para o fim. O inicio e' alcancado em
// O(1) via fim->proximo, porque a lista e' circular —
// o ultimo no aponta de volta para o primeiro.
typedef struct Fila {
    No* fim;
} Fila;

Fila* fila_criar(void) {
    Fila* f = malloc(sizeof(Fila));
    if (f == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    f->fim = NULL;
    return f;
}

int fila_vazia(Fila* f) {
    return f->fim == NULL;
}

void fila_enfileirar(Fila* f, int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->valor = valor;

    if (fila_vazia(f)) {
        // Unico elemento: o no aponta para si mesmo, fechando o anel.
        novo->proximo = novo;
    } else {
        // O novo entra entre o fim atual e o inicio (fim->proximo).
        // 1) novo aponta para quem era o inicio
        // 2) o antigo fim aponta para o novo
        novo->proximo = f->fim->proximo;
        f->fim->proximo = novo;
    }
    f->fim = novo;   // o novo passa a ser o fim
}

int fila_desenfileirar(Fila* f) {
    if (fila_vazia(f)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    No* frente = f->fim->proximo;   // o inicio e' o proximo do fim
    int valor = frente->valor;

    if (frente == f->fim) {
        // So havia um elemento (frente == fim): a fila fica vazia.
        f->fim = NULL;
    } else {
        // Religa: o fim agora aponta diretamente para quem
        // vinha depois da frente, pulando o no removido.
        f->fim->proximo = frente->proximo;
    }
    free(frente);
    return valor;
}

int fila_frente(Fila* f) {
    if (fila_vazia(f)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    return f->fim->proximo->valor;
}

void fila_destruir(Fila* f) {
    if (!fila_vazia(f)) {
        // Quebra o anel para conseguir percorrer linearmente
        // sem cair em loop infinito.
        No* atual = f->fim->proximo;
        f->fim->proximo = NULL;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(f);
}

// A main e' literalmente identica as outras duas versoes —
// mesmo cliente, outra representacao interna.
int main(void) {
    Fila* f = fila_criar();

    fila_enfileirar(f, 10);
    fila_enfileirar(f, 20);
    fila_enfileirar(f, 30);
    printf("Frente da fila: %d\n", fila_frente(f));

    printf("Desenfileirando: ");
    while (!fila_vazia(f)) {
        printf("%d ", fila_desenfileirar(f));
    }
    printf("\n");

    fila_destruir(f);
    return 0;
}
