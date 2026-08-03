#include <stdio.h>

/*
 * Aula 02 - Analise de complexidade na pratica.
 *
 * Tres algoritmos resolvem exatamente o mesmo problema: dizer em que
 * posicao de um vetor esta um valor procurado, ou -1 quando ele nao esta
 * la. O que muda de um para o outro e o CUSTO: quantas comparacoes cada
 * um faz (tempo) e quanta memoria adicional cada um gasta (espaco).
 *
 * Os printf de dentro das buscas existem so para esta aula: eles tornam
 * visivel cada comparacao. Um algoritmo de busca de verdade nao imprime
 * nada - apenas devolve a posicao.
 */

/* Maior valor que a tabela de presenca consegue registrar. */
#define LIMITE 100

/*
 * Busca linear: olha os elementos um a um, do inicio para o fim, ate
 * encontrar o valor procurado. Nao exige nada do vetor - funciona com os
 * elementos em qualquer ordem.
 */
int busca_linear(int vetor[], int tamanho, int procurado) {
    int comparacoes = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        comparacoes++;
        printf("    comparacao %d: vetor[%d] = %d\n", comparacoes, i, vetor[i]);
        if (vetor[i] == procurado) {
            printf("  encontrado na posicao %d com %d comparacoes\n", i, comparacoes);
            return i;
        }
    }

    printf("  nao encontrado; foram %d comparacoes\n", comparacoes);
    return -1;
}

/*
 * Busca binaria: exige o vetor ORDENADO em ordem crescente. A cada volta
 * do laco olha o elemento do meio do trecho que ainda pode conter o valor
 * e descarta a metade que com certeza nao o contem.
 */
int busca_binaria(int vetor[], int tamanho, int procurado) {
    int inicio = 0;
    int fim = tamanho - 1;
    int comparacoes = 0;

    /* Enquanto o trecho [inicio..fim] ainda tem pelo menos um elemento. */
    while (inicio <= fim) {
        /* Divisao inteira: o meio de [0..7] e 3, e o de [0..6] tambem e 3. */
        int meio = (inicio + fim) / 2;

        comparacoes++;
        printf("    comparacao %d: trecho [%d..%d], meio %d, vetor[%d] = %d\n",
               comparacoes, inicio, fim, meio, meio, vetor[meio]);

        if (vetor[meio] == procurado) {
            printf("  encontrado na posicao %d com %d comparacoes\n", meio, comparacoes);
            return meio;
        }

        if (vetor[meio] < procurado) {
            /* O elemento do meio ja foi comparado e nao serve. Comecar o
               novo trecho em meio + 1 (e nao em meio) e o que garante que
               o trecho encolhe de verdade e o laco termina. */
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("  nao encontrado; foram %d comparacoes\n", comparacoes);
    return -1;
}

/*
 * Monta a tabela de presenca: em tabela[v] fica a posicao em que o valor v
 * aparece no vetor, ou -1 se ele nao aparece. Gasta um vetor auxiliar de
 * LIMITE + 1 posicoes e uma passada por cada um dos dois vetores - memoria
 * paga adiantado para que cada busca seguinte custe uma unica leitura.
 * So funciona para valores inteiros de 0 ate LIMITE.
 */
void montar_tabela(int vetor[], int tamanho, int tabela[]) {
    int i;

    for (i = 0; i <= LIMITE; i++) {
        tabela[i] = -1;
    }
    for (i = 0; i < tamanho; i++) {
        tabela[vetor[i]] = i;
    }
}

/*
 * Busca por tabela de presenca: uma unica leitura, sem laco nenhum.
 * Pre-condicao: 0 <= procurado <= LIMITE.
 */
int busca_por_tabela(int tabela[], int procurado) {
    return tabela[procurado];
}

/* Programa demonstrativo: o mesmo vetor, o mesmo alvo, tres custos. */
int main(void) {
    int vetor[] = {4, 8, 15, 16, 23, 42, 55, 68};
    int tamanho = 8;  /* o vetor declarado acima tem 8 elementos */
    int tabela[LIMITE + 1];
    int posicao;

    printf("Vetor ordenado: 4 8 15 16 23 42 55 68   (n = %d)\n\n", tamanho);

    printf("[1] Procurando 55 (existe) com busca linear:\n");
    posicao = busca_linear(vetor, tamanho, 55);
    printf("  posicao devolvida: %d\n\n", posicao);

    printf("[2] Procurando 55 (existe) com busca binaria:\n");
    posicao = busca_binaria(vetor, tamanho, 55);
    printf("  posicao devolvida: %d\n\n", posicao);

    /* O valor ausente e o pior caso das duas buscas: nenhuma delas pode
       parar antes de esgotar o trecho que ainda poderia conte-lo. */
    printf("[3] Procurando 50 (nao existe) com busca linear:\n");
    posicao = busca_linear(vetor, tamanho, 50);
    printf("  posicao devolvida: %d\n\n", posicao);

    printf("[4] Procurando 50 (nao existe) com busca binaria:\n");
    posicao = busca_binaria(vetor, tamanho, 50);
    printf("  posicao devolvida: %d\n\n", posicao);

    printf("[5] Montando a tabela de presenca (%d posicoes de memoria)\n", LIMITE + 1);
    montar_tabela(vetor, tamanho, tabela);
    printf("  procurando 55: posicao %d com 1 leitura\n", busca_por_tabela(tabela, 55));
    printf("  procurando 50: posicao %d com 1 leitura\n", busca_por_tabela(tabela, 50));

    return 0;
}
