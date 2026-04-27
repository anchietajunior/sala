/*
 * Fila (FIFO) — implementacao em C
 *
 * Aula 03 — Algoritmos e Estruturas de Dados (UniRios).
 * Representacao: lista encadeada com ponteiros inicio e fim.
 *
 * Compilar e rodar:
 *   gcc -Wall -Wextra -o fila_demo fila.c && ./fila_demo
 */

#include <stdio.h>
#include <stdlib.h>

// Cada elemento da fila vira um No com o valor e um
// ponteiro para o proximo No.
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// A fila guarda dois ponteiros: a frente (proximo a sair)
// e o fim (ultimo que entrou).
typedef struct Fila {
    No* inicio;
    No* fim;
} Fila;

// Cria uma fila vazia.
Fila* fila_criar(void) {
    Fila* f = malloc(sizeof(Fila));
    if (f == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// Verdadeiro (1) se a fila nao tem nenhum elemento.
int fila_vazia(Fila* f) {
    return f->inicio == NULL;
}

// Coloca um valor no fim da fila.
void fila_enfileirar(Fila* f, int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;

    if (fila_vazia(f)) {
        // Fila estava vazia: o novo no e' tambem a frente.
        f->inicio = novo;
    } else {
        // Liga o no que era o fim ao novo no.
        f->fim->proximo = novo;
    }
    f->fim = novo;
}

// Remove e devolve o valor da frente da fila.
// Pre-requisito: a fila nao pode estar vazia.
int fila_desenfileirar(Fila* f) {
    if (fila_vazia(f)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    No* removido = f->inicio;
    int valor = removido->valor;

    f->inicio = removido->proximo;  // a frente avanca para o proximo no
    if (f->inicio == NULL) {
        // Tiramos o ultimo elemento: a fila ficou vazia.
        // O fim tambem precisa virar NULL. Se nao zerarmos, ele
        // continuaria apontando para o no que vamos liberar com free()
        // logo abaixo — viraria um ponteiro para memoria invalida.
        f->fim = NULL;
    }
    free(removido);
    return valor;
}

// Devolve o valor da frente sem remover.
int fila_frente(Fila* f) {
    if (fila_vazia(f)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    return f->inicio->valor;
}

// Libera toda a memoria usada pela fila.
void fila_destruir(Fila* f) {
    No* atual = f->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(f);
}

// Programa demonstrativo.
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
