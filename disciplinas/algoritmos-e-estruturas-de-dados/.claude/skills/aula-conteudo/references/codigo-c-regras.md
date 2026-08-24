# Regras do código C didático

Aplicam-se **apenas a aulas de implementação** (bloco 5). Existem para que o aluno — que está vendo C pela primeira vez — consiga **ler o `.c` de cima a baixo** sem esbarrar em conceitos não ensinados.

## Organização

- **Um único arquivo `.c`** por aula, contendo:
  - `#include`s do sistema.
  - `typedef struct No { ... } No;` (e/ou outras structs).
  - Todas as funções da TAD na ordem `criar`, `vazia`, `inserir`, `remover`, `consultar`, `destruir`.
  - `main()` demonstrativa ao final.
- **Sem `.h`**. O aluno lê o programa inteiro de cima a baixo, sem saltar entre arquivos. (Motivo interno, **não** escrever na aula: modularização tem aula própria.)
- **Sem múltiplos `.c` ligados por `#include`**. Mesmo motivo.

## Proibido nesta fase da disciplina

- `<stdbool.h>` e o tipo `bool`. Use `int` retornando `0`/`1`.
- `const` em parâmetros.
- `fprintf(stderr, ...)`. Use `printf("erro: ...\n")` seguido de `exit(1)` quando for pré-condição violada.
- Funções não essenciais à TAD (contadores de tamanho, getters extras) — só incluir o que está no contrato mínimo do TAD do bloco 1.
- Tratamento defensivo de `NULL` em todos os pontos de entrada. Deixar a pré-condição clara em **comentário** basta nesta fase.
- Truques de ponteiro sem comentário explicativo adjacente.
- Aritmética de ponteiro críptica.

## Recomendado

- **Nomes descritivos em português** quando ajudar a clareza didática (`topo`, `inicio`, `fim`, `tamanho`, `chave`, `valor`, `proximo`, `anterior`).
- Termos universais em inglês (`malloc`, `printf`, `NULL`, `struct`).
- **`typedef struct Nome { ... } Nome;`** nomeado, não struct anônima.
- **Comentários explicam o porquê**, não o quê:
  - ❌ `// incrementa i`
  - ✅ `// avançamos para o próximo nó porque já processamos o atual`
- **Sempre liberar memória alocada** (`free`) — é didático.
- **Sempre tratar erro de `malloc`** com `if (p == NULL) { printf("erro: memoria insuficiente\n"); exit(1); }`.
- **Linhas-a-linha em partes críticas** (a primeira inserção, a remoção com cuidado de ordem).

## Comentários no `.c` — autoexplicativos

O aluno pode estar lendo o `.c` **sem** o `.md` ao lado. Comentários não podem depender do `.md`:

- ❌ `// preserva I1`
- ❌ `// veja invariante A4 no bloco 1`
- ✅ `// O fim tambem precisa virar NULL — caso contrario continuaria apontando para um no que vamos liberar com free()`

Acentos em comentários do `.c` são **opcionais** (alguns editores antigos ainda dão problema com UTF-8). Quando em dúvida, escrever sem acento — `proximo`, `nao`, `memoria` — e manter a frase clara mesmo assim. No `.md` e na apresentação, acentuação completa é obrigatória.

## A `main()` demonstrativa

A `main()` precisa **exercitar o ciclo completo** que será mostrado no bloco 2 (visualização gráfica):

- Criar a estrutura.
- Inserir 3 elementos.
- Consultar (uma operação de leitura sem alterar estado).
- Remover até esvaziar.
- Destruir.

Imprimir o estado em pontos-chave para que o aluno **veja** o comportamento — e que a saída sirva como prova empírica da política (LIFO devolve em ordem inversa; FIFO devolve em ordem de entrada).

## Compilação limpa

`gcc -Wall -Wextra -o demo tema.c && ./demo` precisa rodar **sem warnings** e sem erros em runtime. Se houver warning, corrigir antes de declarar pronto.

## Template mínimo

```c
#include <stdio.h>
#include <stdlib.h>

// Cada elemento da estrutura vira um No com o valor e um
// ponteiro para o proximo No.
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// A estrutura guarda apenas o(s) ponteiro(s) externo(s) minimo(s).
typedef struct Tema {
    No* ancora;  // ajuste conforme a estrutura: topo, inicio+fim, raiz, etc.
} Tema;

// Cria uma estrutura vazia.
Tema* tema_criar(void) {
    Tema* t = malloc(sizeof(Tema));
    if (t == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    t->ancora = NULL;
    return t;
}

// Verdadeiro (1) se a estrutura nao tem nenhum elemento.
int tema_vazia(Tema* t) {
    return t->ancora == NULL;
}

// ... demais funcoes do TAD ...

// Libera toda a memoria usada pela estrutura.
void tema_destruir(Tema* t) {
    No* atual = t->ancora;
    while (atual != NULL) {
        No* prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    free(t);
}

// Programa demonstrativo.
int main(void) {
    Tema* t = tema_criar();
    // ... ciclo completo demonstrativo ...
    tema_destruir(t);
    return 0;
}
```
