/*
 * Pilha (LIFO) — implementacao em C
 *
 * Aula 04 — Algoritmos e Estruturas de Dados (UniRios).
 * Representacao: lista encadeada com um unico ponteiro topo.
 *
 * Compilar e rodar:
 *   gcc -Wall -Wextra -o pilha_demo pilha.c && ./pilha_demo
 */

#include <stdio.h>
#include <stdlib.h>

// Cada elemento da pilha vira um No com o valor e um
// ponteiro para o proximo No (o que esta logo abaixo).
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// A pilha guarda apenas o topo. O fundo e' alcancado seguindo
// os ponteiros proximo ate chegar em NULL.
typedef struct Pilha {
    No* topo;
} Pilha;

// Cria uma pilha vazia.
Pilha* pilha_criar(void) {
    Pilha* p = malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

// Verdadeiro (1) se a pilha nao tem nenhum elemento.
int pilha_vazia(Pilha* p) {
    return p->topo == NULL;
}

// Coloca um valor no topo da pilha.
void pilha_empilhar(Pilha* p, int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->valor = valor;

    // O proximo do novo no e' o antigo topo (que pode ser NULL
    // se a pilha estava vazia). O novo no passa a ser o topo.
    novo->proximo = p->topo;
    p->topo = novo;
}

// Remove e devolve o valor do topo.
// Pre-requisito: a pilha nao pode estar vazia.
int pilha_desempilhar(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("erro: pilha vazia\n");
        exit(1);
    }
    No* removido = p->topo;
    int valor = removido->valor;

    // O topo "afunda" um nivel: passa a apontar para o que estava
    // logo abaixo. Se o no removido era o ultimo, removido->proximo
    // era NULL e o topo vira NULL — sem caso especial.
    p->topo = removido->proximo;
    free(removido);
    return valor;
}

// Devolve o valor do topo sem remover.
int pilha_topo(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("erro: pilha vazia\n");
        exit(1);
    }
    return p->topo->valor;
}

// Libera toda a memoria usada pela pilha.
void pilha_destruir(Pilha* p) {
    No* atual = p->topo;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(p);
}

// Programa demonstrativo.
int main(void) {
    Pilha* p = pilha_criar();

    pilha_empilhar(p, 10);
    pilha_empilhar(p, 20);
    pilha_empilhar(p, 30);
    printf("Topo da pilha: %d\n", pilha_topo(p));

    printf("Desempilhando: ");
    while (!pilha_vazia(p)) {
        printf("%d ", pilha_desempilhar(p));
    }
    printf("\n");

    pilha_destruir(p);
    return 0;
}
