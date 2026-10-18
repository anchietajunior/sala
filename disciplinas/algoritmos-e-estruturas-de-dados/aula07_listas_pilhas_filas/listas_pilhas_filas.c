/*
 * Listas encadeadas, pilhas e filas — implementacao em C
 *
 * As tres estruturas deste arquivo sao construidas com o mesmo tipo de no:
 *   - Lista: guarda o ponteiro inicio; insere no inicio e no fim, busca e remove.
 *   - Pilha (LIFO): guarda o ponteiro topo; tudo acontece no inicio da cadeia.
 *   - Fila (FIFO): guarda os ponteiros inicio e fim; entra pelo fim, sai pelo inicio.
 *
 * Compilar e rodar:
 *   gcc -Wall -Wextra -o listas_pilhas_filas listas_pilhas_filas.c
 *   ./listas_pilhas_filas
 */

#include <stdio.h>
#include <stdlib.h>

/* ================================================================== */
/* O no: a peca comum as tres estruturas                               */
/* ================================================================== */

// Cada no guarda um valor e o endereco do no seguinte.
// O campo proximo e' um ponteiro para outro No: e' ele que encadeia os nos.
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Reserva memoria para um novo no, ainda desligado de qualquer outro.
No* criar_no(int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Devolve ao sistema a memoria de todos os nos, do primeiro ate o fim da cadeia.
void liberar_cadeia(No* primeiro) {
    No* atual = primeiro;
    while (atual != NULL) {
        // Guardamos o endereco do seguinte ANTES do free: depois dele,
        // o campo atual->proximo nao pode mais ser lido.
        No* seguinte = atual->proximo;
        free(atual);
        atual = seguinte;
    }
}

/* ================================================================== */
/* Lista encadeada                                                     */
/* ================================================================== */

// A lista conhece apenas o endereco do primeiro no; o resto se alcanca
// seguindo os campos proximo.
typedef struct Lista {
    No* inicio;
} Lista;

// Cria uma lista vazia: inicio NULL significa "nenhum no".
Lista* lista_criar(void) {
    Lista* lista = malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    lista->inicio = NULL;
    return lista;
}

// Verdadeiro (1) se a lista nao tem nenhum no.
int lista_vazia(Lista* lista) {
    return lista->inicio == NULL;
}

// Insere um valor antes do primeiro no. Custo O(1): nao depende do tamanho.
void lista_inserir_no_inicio(Lista* lista, int valor) {
    No* novo = criar_no(valor);
    // Passo 1: o novo no aponta para quem era o primeiro (NULL se a lista
    // estava vazia — por isso este caso nao precisa de tratamento especial).
    novo->proximo = lista->inicio;
    // Passo 2: o novo no passa a ser o primeiro.
    lista->inicio = novo;
}

// Insere um valor depois do ultimo no. Custo O(n): e' preciso caminhar ate o fim.
void lista_inserir_no_fim(Lista* lista, int valor) {
    No* novo = criar_no(valor);
    if (lista_vazia(lista)) {
        // Sem nenhum no, o novo e' ao mesmo tempo o primeiro e o ultimo.
        lista->inicio = novo;
        return;
    }
    // A lista so guarda o primeiro no. Para achar o ultimo, caminhamos
    // ate encontrar o no cujo proximo e' NULL.
    No* ultimo = lista->inicio;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = novo;
}

// Devolve o endereco do primeiro no com o valor procurado, ou NULL se nao houver.
No* lista_buscar(Lista* lista, int valor) {
    No* atual = lista->inicio;
    // A ordem das condicoes importa: primeiro confirmamos que atual existe,
    // so depois lemos atual->valor. O && para na primeira condicao falsa.
    while (atual != NULL && atual->valor != valor) {
        atual = atual->proximo;
    }
    return atual;
}

// Remove o primeiro no com o valor informado. Devolve 1 se removeu, 0 se nao achou.
int lista_remover(Lista* lista, int valor) {
    // Caminhamos com dois ponteiros lado a lado: para desligar atual da
    // cadeia, e' o campo proximo do no ANTERIOR que precisa mudar.
    No* anterior = NULL;
    No* atual = lista->inicio;
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;  // percorremos a lista inteira sem encontrar o valor
    }
    if (anterior == NULL) {
        // O no removido era o primeiro: quem muda e' o ponteiro inicio.
        lista->inicio = atual->proximo;
    } else {
        // O anterior "pula" o no removido e passa a apontar para o seguinte.
        anterior->proximo = atual->proximo;
    }
    // So liberamos depois de religar a cadeia: nenhum ponteiro da lista
    // aponta mais para este no.
    free(atual);
    return 1;
}

// Mostra os valores do primeiro ao ultimo no, no formato [5, 10, 30].
void lista_imprimir(Lista* lista) {
    printf("[");
    No* atual = lista->inicio;
    while (atual != NULL) {
        printf("%d", atual->valor);
        if (atual->proximo != NULL) {
            printf(", ");
        }
        atual = atual->proximo;
    }
    printf("]\n");
}

// Libera todos os nos e, por fim, a propria lista.
void lista_destruir(Lista* lista) {
    liberar_cadeia(lista->inicio);
    free(lista);
}

/* ================================================================== */
/* Pilha (LIFO): o ultimo a entrar e' o primeiro a sair                */
/* ================================================================== */

// Toda operacao da pilha acontece numa unica ponta da cadeia, o topo.
// Por isso basta um ponteiro, que faz o papel do inicio da lista.
typedef struct Pilha {
    No* topo;
} Pilha;

// Cria uma pilha vazia.
Pilha* pilha_criar(void) {
    Pilha* pilha = malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    pilha->topo = NULL;
    return pilha;
}

// Verdadeiro (1) se a pilha nao tem nenhum elemento.
int pilha_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

// Coloca um valor no topo. Sao os mesmos dois passos de inserir no inicio da lista.
void pilha_empilhar(Pilha* pilha, int valor) {
    No* novo = criar_no(valor);
    novo->proximo = pilha->topo;  // o novo no fica "em cima" do antigo topo
    pilha->topo = novo;           // e passa a ser o topo
}

// Remove o elemento do topo e devolve seu valor.
// Pre-condicao: a pilha nao pode estar vazia.
int pilha_desempilhar(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        printf("erro: pilha vazia\n");
        exit(1);
    }
    No* removido = pilha->topo;
    int valor = removido->valor;
    // Primeiro o topo desce para o no de baixo; so depois liberamos o removido.
    // Na ordem inversa, topo ficaria apontando para memoria ja devolvida.
    pilha->topo = removido->proximo;
    free(removido);
    return valor;
}

// Devolve o valor do topo sem remover nada.
// Pre-condicao: a pilha nao pode estar vazia.
int pilha_consultar_topo(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        printf("erro: pilha vazia\n");
        exit(1);
    }
    return pilha->topo->valor;
}

// Libera todos os nos e, por fim, a propria pilha.
void pilha_destruir(Pilha* pilha) {
    liberar_cadeia(pilha->topo);
    free(pilha);
}

/* ================================================================== */
/* Fila (FIFO): o primeiro a entrar e' o primeiro a sair               */
/* ================================================================== */

// A fila usa as duas pontas da cadeia: sai pelo inicio e entra pelo fim.
// Guardar o fim evita percorrer a cadeia inteira a cada insercao.
typedef struct Fila {
    No* inicio;  // o proximo elemento a sair
    No* fim;     // o ultimo elemento que entrou
} Fila;

// Cria uma fila vazia: sem nenhum no, inicio e fim sao ambos NULL.
Fila* fila_criar(void) {
    Fila* fila = malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Verdadeiro (1) se a fila nao tem nenhum elemento.
int fila_vazia(Fila* fila) {
    return fila->inicio == NULL;
}

// Coloca um valor no fim da fila. Custo O(1), gracas ao ponteiro fim.
void fila_enfileirar(Fila* fila, int valor) {
    No* novo = criar_no(valor);
    if (fila_vazia(fila)) {
        // O unico no da fila e' ao mesmo tempo o primeiro e o ultimo.
        fila->inicio = novo;
    } else {
        // O antigo ultimo passa a apontar para o novo no.
        fila->fim->proximo = novo;
    }
    fila->fim = novo;
}

// Remove o elemento do inicio da fila e devolve seu valor.
// Pre-condicao: a fila nao pode estar vazia.
int fila_desenfileirar(Fila* fila) {
    if (fila_vazia(fila)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    No* removido = fila->inicio;
    int valor = removido->valor;
    fila->inicio = removido->proximo;  // o segundo da fila passa a ser o primeiro
    if (fila->inicio == NULL) {
        // A fila esvaziou. O fim ainda aponta para o no que vamos liberar;
        // se nao virar NULL, o proximo enfileirar escreveria em memoria devolvida.
        fila->fim = NULL;
    }
    free(removido);
    return valor;
}

// Devolve o valor do inicio da fila sem remover nada.
// Pre-condicao: a fila nao pode estar vazia.
int fila_consultar_frente(Fila* fila) {
    if (fila_vazia(fila)) {
        printf("erro: fila vazia\n");
        exit(1);
    }
    return fila->inicio->valor;
}

// Libera todos os nos e, por fim, a propria fila.
void fila_destruir(Fila* fila) {
    liberar_cadeia(fila->inicio);
    free(fila);
}

/* ================================================================== */
/* Programa demonstrativo                                              */
/* ================================================================== */

int main(void) {
    printf("== Lista encadeada ==\n");
    Lista* lista = lista_criar();
    lista_inserir_no_fim(lista, 10);
    lista_inserir_no_fim(lista, 20);
    lista_inserir_no_inicio(lista, 5);
    lista_inserir_no_fim(lista, 30);
    printf("Lista montada: ");
    lista_imprimir(lista);

    if (lista_buscar(lista, 20) != NULL) {
        printf("Buscar 20: encontrado\n");
    } else {
        printf("Buscar 20: nao encontrado\n");
    }
    if (lista_buscar(lista, 99) != NULL) {
        printf("Buscar 99: encontrado\n");
    } else {
        printf("Buscar 99: nao encontrado\n");
    }

    lista_remover(lista, 20);
    printf("Depois de remover 20: ");
    lista_imprimir(lista);
    lista_remover(lista, 5);
    printf("Depois de remover 5: ");
    lista_imprimir(lista);
    lista_destruir(lista);

    printf("\n== Pilha (LIFO) ==\n");
    Pilha* pilha = pilha_criar();
    pilha_empilhar(pilha, 10);
    pilha_empilhar(pilha, 20);
    pilha_empilhar(pilha, 30);
    printf("Topo: %d\n", pilha_consultar_topo(pilha));
    printf("Desempilhando:");
    while (!pilha_vazia(pilha)) {
        printf(" %d", pilha_desempilhar(pilha));
    }
    printf("\n");
    pilha_destruir(pilha);

    printf("\n== Fila (FIFO) ==\n");
    Fila* fila = fila_criar();
    fila_enfileirar(fila, 10);
    fila_enfileirar(fila, 20);
    fila_enfileirar(fila, 30);
    printf("Frente: %d\n", fila_consultar_frente(fila));
    printf("Desenfileirando:");
    while (!fila_vazia(fila)) {
        printf(" %d", fila_desenfileirar(fila));
    }
    printf("\n");
    fila_destruir(fila);

    return 0;
}
