/*
 * Palindromo — dois algoritmos para o mesmo problema
 *
 * Aula 01 — Algoritmos e Estruturas de Dados (UniRios).
 * Uma palavra e' palindromo quando se le igual nos dois sentidos
 * (arara, radar, ovo).
 *
 * Compilar e rodar:
 *   gcc -Wall -Wextra -o palindromo_demo palindromo.c && ./palindromo_demo
 */

#include <stdio.h>
#include <string.h>

// Devolve 1 se a palavra e' palindromo e 0 caso contrario — custo O(n).
//
// Compara a primeira letra com a ultima e caminha um passo de cada
// lado em direcao ao centro. Basta uma diferenca para a resposta ser
// nao; se i e j se encontrarem, todos os pares ja foram conferidos.
// A letra do meio de uma palavra impar nao tem par e nao e' comparada.
int eh_palindromo_duas_pontas(char palavra[]) {
    int i = 0;
    int j = strlen(palavra) - 1;

    while (i < j) {
        if (palavra[i] != palavra[j]) {
            return 0;
        }
        i = i + 1;
        j = j - 1;
    }

    return 1;
}

// Devolve 1 se a palavra e' palindromo e 0 caso contrario — custo O(n^2).
//
// Monta uma copia invertida inserindo cada letra na PRIMEIRA posicao da
// copia. Como o vetor da acesso direto mas nao abre buracos sozinho, para
// liberar a posicao 0 todas as letras ja copiadas precisam andar uma casa
// para a direita. Sao n insercoes e cada uma desloca ate n letras: n * n
// passos no total, contra os n/2 do algoritmo das duas pontas. No fim, a
// copia invertida so precisa ser comparada com a palavra original.
int eh_palindromo_copia_invertida(char palavra[]) {
    char copia[100];
    int n = strlen(palavra);

    for (int i = 0; i < n; i = i + 1) {
        for (int j = i; j > 0; j = j - 1) {
            copia[j] = copia[j - 1];
        }
        copia[0] = palavra[i];
    }
    copia[n] = '\0';

    return strcmp(copia, palavra) == 0;
}

int main(void) {
    // Troque a palavra abaixo para testar outros casos (casa, ovo, a).
    char palavra[] = "arara";

    // Mesma pergunta, mesma resposta, custos diferentes: os dois
    // algoritmos sempre concordam — o que muda e' quanto trabalho deu.
    if (eh_palindromo_duas_pontas(palavra)) {
        printf("duas pontas:     %s e' palindromo\n", palavra);
    } else {
        printf("duas pontas:     %s nao e' palindromo\n", palavra);
    }

    if (eh_palindromo_copia_invertida(palavra)) {
        printf("copia invertida: %s e' palindromo\n", palavra);
    } else {
        printf("copia invertida: %s nao e' palindromo\n", palavra);
    }

    return 0;
}
