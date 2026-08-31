#include <stdio.h>
#include <stdlib.h>

/*
 * Aula 04 - Ordenacao: bubble sort, merge sort e quick sort.
 *
 * Os tres algoritmos resolvem exatamente o mesmo problema: rearranjar um
 * vetor de inteiros em ordem crescente. O que muda de um para o outro e a
 * ESTRATEGIA - e, por causa dela, o CUSTO: quantas comparacoes entre
 * elementos cada um faz e quantos elementos cada um movimenta.
 *
 * Os printf de dentro dos algoritmos existem so para esta aula: eles tornam
 * visivel cada passagem, cada intercalacao e cada particao. Um algoritmo de
 * ordenacao de verdade nao imprime nada - apenas deixa o vetor ordenado.
 */

/*
 * Contadores de instrumentacao. Sao variaveis globais (declaradas fora de
 * qualquer funcao, visiveis para todas elas) porque merge sort e quick sort
 * chamam a si mesmos varias vezes: carregar a contagem como parametro
 * obrigaria a passa-la para dentro e traze-la de volta em cada chamada, o
 * que so atrapalharia a leitura do algoritmo. Fora da aula, esses contadores
 * nao existiriam.
 */
int comparacoes = 0;
int trocas = 0;
int copias = 0;

/* Imprime as posicoes de inicio ate fim no formato [7, 3, 9], seguidas de
   quebra de linha. Serve para mostrar tanto o vetor inteiro quanto um pedaco
   dele, que e o que os algoritmos recursivos desta aula manipulam. */
void imprimir_trecho(int vetor[], int inicio, int fim) {
    int i;

    printf("[");
    for (i = inicio; i <= fim; i++) {
        printf("%d", vetor[i]);
        if (i < fim) {
            printf(", ");
        }
    }
    printf("]\n");
}

/* Imprime o vetor inteiro: o trecho que vai da primeira a ultima posicao. */
void imprimir_vetor(int vetor[], int tamanho) {
    imprimir_trecho(vetor, 0, tamanho - 1);
}

/* Copia todos os elementos de origem para destino. Cada algoritmo trabalha
   sobre uma copia do vetor original, para que os tres recebam a mesma
   entrada e as contagens sejam comparaveis. */
void copiar_vetor(int origem[], int destino[], int tamanho) {
    int i;

    for (i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

/*
 * Troca de lugar os elementos das posicoes i e j.
 *
 * A variavel guardado e indispensavel: sem ela, a primeira atribuicao
 * sobrescreveria vetor[i] e o valor antigo estaria perdido antes de ser
 * copiado para vetor[j].
 */
void trocar(int vetor[], int i, int j) {
    int guardado = vetor[i];

    vetor[i] = vetor[j];
    vetor[j] = guardado;
    trocas++;
}

/* ------------------------------------------------------------------ */
/* Bubble sort                                                         */
/* ------------------------------------------------------------------ */

/*
 * Bubble sort: compara elementos VIZINHOS e troca os que estao fora de
 * ordem. Cada passagem completa pelo vetor arrasta o maior elemento ainda
 * solto ate o fim do trecho nao ordenado - dai o nome (o maior "borbulha"
 * para cima).
 *
 * Depois da passagem numero i, as i ultimas posicoes ja guardam os maiores
 * elementos em ordem definitiva. Por isso o laco interno para em
 * tamanho - 1 - i: reexaminar o que ja esta no lugar seria trabalho jogado
 * fora.
 */
void bubble_sort(int vetor[], int tamanho) {
    int i, j;
    int houve_troca;

    for (i = 0; i < tamanho - 1; i++) {
        houve_troca = 0;

        for (j = 0; j < tamanho - 1 - i; j++) {
            comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                trocar(vetor, j, j + 1);
                houve_troca = 1;
            }
        }

        printf("  passagem %d: ", i + 1);
        imprimir_vetor(vetor, tamanho);

        /* Uma passagem inteira sem nenhuma troca significa que nao existe
           mais nenhum par vizinho fora de ordem - ou seja, o vetor ja esta
           ordenado e continuar seria desperdicio. */
        if (houve_troca == 0) {
            printf("  nenhuma troca nesta passagem: o vetor ja esta ordenado\n");
            return;
        }
    }
}

/* ------------------------------------------------------------------ */
/* Merge sort                                                          */
/* ------------------------------------------------------------------ */

/*
 * Intercala dois trechos VIZINHOS e ja ordenados do mesmo vetor -
 * [inicio..meio] e [meio+1..fim] - produzindo um unico trecho ordenado.
 *
 * A intercalacao nao troca elementos de lugar: ela le os dois trechos em
 * paralelo, sempre copiando o menor dos dois valores da frente para um vetor
 * auxiliar, e no final devolve o auxiliar ja ordenado para o vetor original.
 * Esse vetor auxiliar e a memoria extra que o merge sort cobra.
 */
void intercalar(int vetor[], int inicio, int meio, int fim) {
    int tamanho = fim - inicio + 1;
    int i = inicio;    /* proxima posicao a ser lida na metade esquerda */
    int j = meio + 1;  /* proxima posicao a ser lida na metade direita */
    int k = 0;         /* proxima posicao a ser escrita no auxiliar */
    int* auxiliar = malloc(tamanho * sizeof(int));

    if (auxiliar == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }

    /* Enquanto as duas metades ainda tem elementos, a comparacao decide de
       qual delas sai o proximo menor valor. */
    while (i <= meio && j <= fim) {
        comparacoes++;
        if (vetor[i] <= vetor[j]) {
            auxiliar[k] = vetor[i];
            i++;
        } else {
            auxiliar[k] = vetor[j];
            j++;
        }
        k++;
    }

    /* Uma das metades acabou antes da outra. O que sobrou na outra ja esta
       ordenado e e maior que tudo o que ja foi copiado, entao vai direto,
       sem comparacao nenhuma. */
    while (i <= meio) {
        auxiliar[k] = vetor[i];
        i++;
        k++;
    }
    while (j <= fim) {
        auxiliar[k] = vetor[j];
        j++;
        k++;
    }

    for (k = 0; k < tamanho; k++) {
        vetor[inicio + k] = auxiliar[k];
        copias++;
    }

    printf("  intercalando [%d..%d] com [%d..%d]: ", inicio, meio, meio + 1, fim);
    imprimir_vetor(auxiliar, tamanho);

    free(auxiliar);
}

/*
 * Merge sort: ordena o trecho [inicio..fim] ordenando cada metade dele e
 * intercalando as duas metades ja ordenadas.
 *
 * A funcao chama a si mesma - e uma funcao recursiva. Toda funcao recursiva
 * precisa de um caso base, uma situacao em que ela responde sem chamar a si
 * mesma de novo; aqui, um trecho de zero ou um elemento ja esta ordenado por
 * definicao e nada precisa ser feito.
 */
void merge_sort(int vetor[], int inicio, int fim) {
    int meio;

    if (inicio >= fim) {
        return;
    }

    meio = (inicio + fim) / 2;
    merge_sort(vetor, inicio, meio);
    merge_sort(vetor, meio + 1, fim);
    intercalar(vetor, inicio, meio, fim);
}

/* ------------------------------------------------------------------ */
/* Quick sort                                                          */
/* ------------------------------------------------------------------ */

/*
 * Particiona o trecho [inicio..fim] em torno de um pivo, aqui escolhido como
 * o ultimo elemento do trecho. Ao terminar, todos os elementos menores ou
 * iguais ao pivo estao a esquerda dele e todos os maiores estao a direita, e
 * a funcao devolve a posicao final do pivo.
 *
 * A variavel menor marca a fronteira: ate ela, ja se sabe que todos os
 * elementos sao menores ou iguais ao pivo. Ela comeca em inicio - 1 porque a
 * regiao dos menores nasce vazia.
 */
int particionar(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];
    int menor = inicio - 1;
    int j;

    for (j = inicio; j < fim; j++) {
        comparacoes++;
        if (vetor[j] <= pivo) {
            menor++;
            /* Quando menor e j sao a mesma posicao, esta troca e do elemento
               com ele mesmo: nao muda nada e so acontece porque o elemento ja
               estava no lado certo. */
            trocar(vetor, menor, j);
        }
    }

    /* O pivo estava guardado no fim do trecho. Agora ele vai para a primeira
       posicao depois da regiao dos menores - a sua posicao DEFINITIVA no
       vetor ordenado, que nenhuma chamada seguinte vai mexer. */
    trocar(vetor, menor + 1, fim);

    printf("  pivo %d no trecho [%d..%d]: ", pivo, inicio, fim);
    imprimir_trecho(vetor, inicio, fim);

    return menor + 1;
}

/*
 * Quick sort: coloca um elemento na posicao definitiva dele e ordena, com o
 * mesmo metodo, o que ficou de cada lado.
 *
 * Tambem e recursiva, e o caso base tambem e o trecho de zero ou um
 * elemento. A diferenca para o merge sort esta em ONDE mora o trabalho: aqui
 * ele acontece na ida, dentro de particionar, e a volta nao faz nada.
 */
void quick_sort(int vetor[], int inicio, int fim) {
    int posicao_pivo;

    if (inicio >= fim) {
        return;
    }

    posicao_pivo = particionar(vetor, inicio, fim);
    quick_sort(vetor, inicio, posicao_pivo - 1);
    quick_sort(vetor, posicao_pivo + 1, fim);
}

/* ------------------------------------------------------------------ */
/* Programa demonstrativo                                              */
/* ------------------------------------------------------------------ */

/* Zera os contadores antes de cada algoritmo, para que as contagens dos tres
   se refiram a mesma entrada e possam ser comparadas. */
void zerar_contadores(void) {
    comparacoes = 0;
    trocas = 0;
    copias = 0;
}

int main(void) {
    int original[] = {7, 3, 9, 1, 5, 8, 2, 6};
    int tamanho = 8;  /* o vetor declarado acima tem 8 elementos */
    int vetor[8];

    int comparacoes_bubble, trocas_bubble;
    int comparacoes_merge, copias_merge;
    int comparacoes_quick, trocas_quick;

    printf("Vetor original: ");
    imprimir_vetor(original, tamanho);
    printf("\n");

    printf("[1] Bubble sort\n");
    copiar_vetor(original, vetor, tamanho);
    zerar_contadores();
    bubble_sort(vetor, tamanho);
    comparacoes_bubble = comparacoes;
    trocas_bubble = trocas;
    printf("  resultado: ");
    imprimir_vetor(vetor, tamanho);
    printf("  %d comparacoes, %d trocas\n\n", comparacoes_bubble, trocas_bubble);

    printf("[2] Merge sort\n");
    copiar_vetor(original, vetor, tamanho);
    zerar_contadores();
    merge_sort(vetor, 0, tamanho - 1);
    comparacoes_merge = comparacoes;
    copias_merge = copias;
    printf("  resultado: ");
    imprimir_vetor(vetor, tamanho);
    printf("  %d comparacoes, %d copias de volta do auxiliar para o vetor\n\n",
           comparacoes_merge, copias_merge);

    printf("[3] Quick sort\n");
    copiar_vetor(original, vetor, tamanho);
    zerar_contadores();
    quick_sort(vetor, 0, tamanho - 1);
    comparacoes_quick = comparacoes;
    trocas_quick = trocas;
    printf("  resultado: ");
    imprimir_vetor(vetor, tamanho);
    printf("  %d comparacoes, %d trocas\n\n", comparacoes_quick, trocas_quick);

    printf("Resumo para n = %d\n", tamanho);
    printf("  bubble sort: %2d comparacoes\n", comparacoes_bubble);
    printf("  merge sort:  %2d comparacoes\n", comparacoes_merge);
    printf("  quick sort:  %2d comparacoes\n", comparacoes_quick);

    return 0;
}
