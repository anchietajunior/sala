# Aula 04 — Pilha (Stack)

> **Tipo desta aula**: implementação. A Pilha é o gêmeo conceitual da Fila — mesma família (estrutura linear), política de acesso oposta (LIFO em vez de FIFO). A representação interna escolhida aqui é **lista simplesmente encadeada com um único ponteiro `topo`** — ainda mais simples que a da Fila.

---

## 1. Conceito — Aprofundamento Progressivo

### Camada 1 — A intuição inicial

Imagine uma pilha de bandejas no balcão de um restaurante self-service. Bandejas novas vão **em cima** das que já estavam ali; quem precisa usar uma pega sempre **a do topo**, nunca uma do meio nem a do fundo. Essa restrição extremamente simples — *"só vejo e só mexo no topo"* — é toda a ideia da estrutura de dados chamada **Pilha**: a última coisa a entrar é a primeira a sair, e o que está embaixo só fica acessível depois que tudo em cima foi retirado.

### Camada 2 — Definição informal com vocabulário básico

Uma **Pilha** (em inglês, *stack*) é uma estrutura linear de elementos com a seguinte restrição de acesso: **insere-se e remove-se sempre na mesma extremidade**, chamada **topo** (em inglês, *top*). Os elementos abaixo do topo ficam ocultos: não há operação que os acesse diretamente. Essa política de acesso recebe o nome **LIFO** (*Last-In, First-Out*) — o último elemento que entrou é o primeiro a sair (Tenenbaum, cap. 2 — *Pilhas*; Sedgewick, *Algoritmos em C*, Parte 1, cap. 4 — seção sobre *pushdown stacks*; referência histórica em Knuth, *TAOCP* vol. 1, §2.2.1).

Para que essa restrição seja útil em prática, a Pilha oferece um conjunto pequeno de operações:

- **empilhar** (*push*) — coloca um novo elemento no **topo**.
- **desempilhar** (*pop*) — remove e devolve o elemento do **topo**.
- **topo** — apenas **lê** o elemento do topo, sem removê-lo.
- **vazia** — informa se há ou não elementos na pilha.

Note o que a Pilha **não** oferece: você não pode olhar o terceiro elemento, nem inserir no meio, nem remover o do fundo. Como na Fila, **a restrição é a feature**, não a limitação — é justamente o que torna a Pilha simples, previsível e rápida.

### Camada 3 — Propriedades e comportamento

> A representação interna desta aula é construída sobre o **nó** apresentado na sub-seção *"O nó — unidade de construção das estruturas encadeadas"* da Aula 02. O nó da Pilha é exatamente o nó da lista simplesmente encadeada — um campo de valor (a carga útil) e um campo `proximo` (o ponteiro de ligação). O que muda não é o nó: é a **política de acesso** (LIFO em vez de FIFO) e o **estado externo enxuto** — apenas o ponteiro `topo`, sem `fim`.

#### Um único ponteiro torna tudo simples

Onde a Fila precisa de **dois** ponteiros externos (`inicio` e `fim`) para que `enfileirar` e `desenfileirar` operem ambos em O(1), a Pilha precisa de **um só**: o ponteiro `topo`. Toda operação acontece no início da lista — empilhar é "inserir no início", desempilhar é "remover do início". Não é preciso ter `fim` porque ninguém nunca acessa o fim da pilha.

Esse "estado externo enxuto" tem uma consequência muito didática: o código da Pilha **não tem casos especiais**. Diferente da Fila — onde `desenfileirar` precisa cuidar do caso "removeu o último, agora a pilha ficou vazia, preciso zerar `fim`" —, na Pilha o `desempilhar` simplesmente faz `topo = topo->proximo`, e se isso resultar em `NULL` está tudo certo: a pilha ficou vazia. Não há armadilha.

#### As operações em detalhe

- **Inserção (`empilhar`)**. Aloca-se um novo nó com o valor desejado. O `proximo` do novo nó passa a apontar para o **antigo topo** (que pode ser `NULL` se a pilha estava vazia — sem caso especial). Em seguida, `topo` é atualizado para o nó novo. Custo: **O(1)**.

- **Remoção (`desempilhar`)**. Lê-se o valor do nó apontado por `topo`. Salva-se o `proximo` desse nó em `topo`. Libera-se o nó antigo com `free`. **Atenção à ordem**: primeiro atualizar `topo`, **só depois** chamar `free` — inverter essa ordem deixa `topo` apontando para memória já liberada, criando um **ponteiro suspenso** (*dangling pointer*) que provoca falhas obscuras na próxima operação. Custo: **O(1)**.

- **Consulta (`topo`)**. Retorna o valor do nó apontado por `topo` sem alterar nada. Custo: **O(1)**.

- **Vazia**. Testa se `topo == NULL`. Custo: **O(1)**.

#### Invariantes (propriedades que devem sempre valer)

Algumas propriedades têm de continuar verdadeiras antes e depois de cada operação — chamamos isso de **invariantes** da estrutura. Para esta Pilha são duas:

- **Quando a pilha está vazia**, o ponteiro `topo` é `NULL`.
- **Quando a pilha tem ao menos um elemento**, `topo` é diferente de `NULL` e, seguindo os ponteiros `proximo` a partir do nó apontado por `topo`, chega-se a um nó cujo `proximo` é `NULL` — o fundo da pilha.

A Pilha tem **menos invariantes** que a Fila porque tem menos estado interno (um ponteiro em vez de dois). É realmente uma das estruturas de dados mais simples que existe — e, como veremos na Camada 6, uma das mais utilizadas.

### Camada 4 — Definição formal e notação

Um **TAD** (Tipo Abstrato de Dados) define uma estrutura pelo seu **contrato observável** — os valores que armazena, as operações que oferece e os axiomas que essas operações satisfazem — sem comprometer-se com nenhuma representação interna específica. Para a Pilha, o TAD é (Tenenbaum, cap. 2):

```
TAD Pilha de Inteiros

  Tipos:
    Pilha
    Inteiro
    Booleano

  Operações:
    criar()                       -> Pilha
    empilhar(Pilha, Inteiro)      -> Pilha
    desempilhar(Pilha)            -> Pilha       [erro se vazia]
    topo(Pilha)                   -> Inteiro     [erro se vazia]
    vazia(Pilha)                  -> Booleano

  Axiomas (para qualquer pilha P, inteiro x):
    A1. vazia(criar())                                = verdadeiro
    A2. vazia(empilhar(P, x))                         = falso
    A3. topo(empilhar(P, x))                          = x
    A4. desempilhar(empilhar(P, x))                   = P
    A5. topo(criar())                                 = erro
    A6. desempilhar(criar())                          = erro
```

O **axioma A4** é o **coração do LIFO**: ele diz que *"empilhar `x` e em seguida desempilhar devolve a pilha original"*. Em palavras: o último elemento a entrar é exatamente o primeiro a sair, sem afetar nada do que estava embaixo. Compare com o axioma análogo da Fila — `desenfileirar(enfileirar(F, x)) = enfileirar(desenfileirar(F), x)`. Lá o `x` "passa por dentro" da remoção; aqui, ele simplesmente sai. Tenenbaum (cap. 2) apresenta exatamente esse contraste de axiomas como definição operacional de Pilha vs. Fila.

#### A representação interna como tupla

Para a versão simplesmente encadeada com ponteiro `topo`, a Pilha pode ser descrita pela tupla:

`P = (N, valor, proximo, topo)`

onde:

- **N** é o conjunto (possivelmente vazio) dos nós da pilha.
- **valor: N → V** associa cada nó a um inteiro.
- **proximo: N → N ∪ {NULL}** associa cada nó ao seguinte (mais perto do fundo da pilha), ou `NULL` se for o nó de fundo.
- **topo ∈ N ∪ {NULL}** é o ponteiro externo para o último elemento empilhado (`NULL` se a pilha estiver vazia).

A invariante "vazia ⇔ topo = NULL" liga formalmente o estado lógico da pilha ao estado físico do ponteiro.

### Camada 5 — Análise de complexidade

A análise se faz em termos de **n**, o número de elementos da pilha. Comparando as duas representações canônicas (CLRS, cap. 10.1; Tenenbaum, cap. 2):

| Operação        | Vetor com `topo`-índice | Lista encadeada com `topo` |
|-----------------|--------------------------|-----------------------------|
| `empilhar`      | O(1)*                    | **O(1)**                    |
| `desempilhar`   | O(1)                     | **O(1)**                    |
| `topo`          | O(1)                     | **O(1)**                    |
| `vazia`         | O(1)                     | **O(1)**                    |

\* O vetor pode precisar de `realloc` quando esgota a capacidade — operação eventual de O(n) que, distribuída entre todos os `empilhar`, dá um custo amortizado de O(1). Em vetor de tamanho fixo, simplesmente acontece *overflow*.

Todas as operações principais em **O(1)** independentemente da representação. A diferença entre as duas está em outros eixos: o vetor faz **uma única alocação** (mais econômico em memória, ótimo desempenho de acesso) mas tem **capacidade fixa** ou paga por `realloc`; a lista encadeada **cresce sob demanda** e tem capacidade ilimitada (até o limite da memória do sistema), mas **paga 8 bytes de ponteiro por nó** e exige uma chamada a `malloc` por elemento empilhado.

A escolha entre as duas é uma decisão de engenharia que depende do uso. Pilhas pequenas e bem-conhecidas favorecem o vetor; pilhas que podem crescer arbitrariamente — como a pilha de chamadas de uma linguagem de propósito geral — favorecem a lista. Esta aula implementa a versão encadeada por ser **mais simples de codificar**, sem casos especiais, e ter **tamanho dinâmico**. O *overhead* de ponteiros é exatamente o "preço do ponteiro" discutido na sub-seção *"O nó"* da Aula 02.

### Camada 6 — Conexões e variantes

A Pilha é onipresente em computação, e os exemplos cobrem áreas muito distintas:

- **Pilha de chamadas** que toda linguagem de programação mantém durante a execução. Cada chamada de função empilha um *frame* com variáveis locais e endereço de retorno; o `return` desempilha. A mensagem de erro *stack overflow* é literalmente essa pilha estourando — recursão sem caso base faz a pilha crescer sem parar até esgotar a memória reservada para ela.
- **Histórico de "desfazer"** (Ctrl+Z) em editores, IDEs e ferramentas gráficas. Cada ação executada vira uma entrada empilhada; cada desfazer desempilha. O "refazer" (Ctrl+Y) usa uma **segunda pilha** que recebe o que foi desfeito.
- **Histórico de navegação** ("voltar") em browsers e em apps mobile. Cada página/tela visitada vai para a pilha; o botão "voltar" desempilha.
- **Avaliação de expressões com parênteses**. Ao percorrer a expressão, parênteses de abertura são empilhados e os de fechamento desempilham e conferem com o topo, validando o pareamento.
- **Algoritmos recursivos transformados em iterativos**. A recursão usa a pilha implícita do programa; a versão iterativa usa uma pilha explícita.

A própria implementação da Pilha admite duas variantes principais — **vetor com `topo`-índice** (com ou sem `realloc`) e **lista simplesmente encadeada com `topo`** (a desta aula). Lista duplamente encadeada e lista circular não trazem ganho para a Pilha: todas as operações já estão em O(1) com lista simples, e ponteiros adicionais só acrescentariam custo de memória sem benefício observável. A Pilha é também peça de construção de algoritmos clássicos — **DFS** (busca em profundidade) em grafos é o exemplo mais conhecido; surge naturalmente em aulas futuras quando estudarmos travessia de grafos e árvores.

---

## 2. Visualização Gráfica

Ciclo de vida completo: criação, três `empilhar`, uma consulta `topo`, dois `desempilhar` até esvaziar.

### Passo 1: pilha_criar()

![Pilha vazia: ponteiro topo apontando para NULL](img/01_criar.svg)

A pilha começa vazia: `topo = NULL`. Não há nó algum sendo apontado.

### Passo 2: empilhar(10)

![Pilha com um nó (10): topo aponta para o nó; o nó aponta para NULL](img/02_empilhar_10.svg)

Cria-se um nó `[10|NULL]`. Como a pilha estava vazia, o `proximo` do nó novo já nasce como `NULL` (a pilha é o "fundo da pilha"). `topo` passa a apontar para o nó novo.

### Passo 3: empilhar(20)

![Pilha com dois nós: topo aponta para 20; 20 aponta para 10; 10 aponta para NULL](img/03_empilhar_20.svg)

Cria-se um nó `[20|*]` cujo `proximo` aponta para o **antigo topo** (`[10]`). Em seguida, `topo` passa a apontar para o nó novo. **O antigo topo "afunda" um nível**.

### Passo 4: empilhar(30)

![Pilha com três nós: topo aponta para 30; 30 aponta para 20; 20 aponta para 10; 10 aponta para NULL](img/04_empilhar_30.svg)

Mesma lógica: cria nó, liga ao topo antigo, atualiza topo. A pilha cresce **para cima**.

### Passo 5: topo() retorna 30

![Pilha com três nós; setinha destacando que topo() lê o valor do nó apontado por topo sem alterar nada](img/05_topo.svg)

`topo()` apenas **lê** o valor do nó apontado por `topo`. **Não altera** a estrutura. Retorna `30` (o último a entrar).

### Passo 6: desempilhar() remove 30

![Pilha com dois nós (20, 10): topo agora aponta para 20; nó 30 foi liberado](img/06_desempilhar.svg)

O nó do topo é "destacado": `topo` passa a apontar para o `proximo` dele (`[20]`), e o nó antigo `[30]` é **liberado** com `free`. **O elemento mais recente foi o primeiro a sair** — LIFO em ação.

### Passo 7: desempilhar() remove 20

![Pilha com um nó (10): topo aponta para 10; 10 aponta para NULL](img/07_desempilhar_2.svg)

Mesma lógica. Resta o nó `[10]`, com `proximo == NULL` (volta a ser o fundo da pilha). Note como o código da operação **não muda** entre o caso "havia 3 elementos" e "havia 2 elementos" — diferentemente da Fila, **não há caso especial** para o último elemento, porque a Pilha não mantém um ponteiro `fim`.

---

## 3. Problema Motivador

> *"Como o botão Ctrl+Z funciona?"*

Quando você está editando um documento e aperta Ctrl+Z, o editor desfaz a **última** ação. Aperta de novo, desfaz a **penúltima**. Aperta uma terceira vez, desfaz a **antepenúltima**. As ações são desfeitas exatamente **na ordem inversa** de execução.

Como o editor sabe qual é a "última ação"? Ele mantém uma **Pilha de ações**:

- Cada vez que o usuário faz alguma coisa (digita uma letra, deleta uma palavra, cola um trecho), o editor cria uma representação dessa ação e a **empilha**.
- Cada Ctrl+Z **desempilha** a ação do topo e a reverte.
- Cada Ctrl+Y (refazer) costuma usar uma **segunda pilha**, que recebe o que foi desfeito.

A Pilha é a estrutura natural porque LIFO **é exatamente o comportamento** de "desfazer na ordem inversa de execução". Tentar usar uma Fila aqui seria desastroso — Ctrl+Z começaria desfazendo a **primeira** ação que você fez no documento (provavelmente "abrir o arquivo"), não a mais recente.

Outro caso clássico: a **pilha de chamadas** que toda linguagem mantém em execução. Quando uma função `A` chama `B`, que chama `C`, o sistema operacional / runtime da linguagem mantém uma pilha:

```
[ frame de C ]   ← topo (executando)
[ frame de B ]
[ frame de A ]
[ ... main ... ]
```

Cada `return` **desempilha** o frame do topo e devolve o controle para quem chamou (o frame que ficou exposto). É **literalmente uma Pilha** — e o nome não é coincidência.

A Pilha aparece em qualquer situação que pede *"o mais recente é o mais relevante"* ou *"desfaça na ordem inversa"*.

---

## 4. Analogias

**1. Pilha de bandejas no balcão de um restaurante self-service.**
As bandejas chegam limpas e são colocadas **em cima** da pilha existente. Quando você precisa de uma, pega a **do topo** — não a do meio, não a do fundo. A pilha cresce para cima quando vêm bandejas novas; encolhe pelo topo quando os clientes as retiram. Você nunca vê a do meio. Esse é o **LIFO** literal.

**2. Pilha de pratos sujos na pia.**
Você termina uma refeição: o prato vai **em cima** da pilha de pratos sujos. Quando vai lavar, **começa pelo do topo** — o último que foi colocado, que é o que está exposto. O do fundo é o que **sujou primeiro** e será o **último a ser lavado**. (Engraçado: "última coisa suja, primeira coisa limpa".)

---

## 5. Código em C

Note como o código é **mais curto** que o da Fila — menos casos especiais, menos invariantes, mesma legibilidade.

> **Sobre a organização do arquivo.** Tudo o que vem a seguir vive em **um único arquivo** chamado `pilha.c`: `#include`s, struct do nó, struct da pilha, todas as funções da TAD e a `main()` demonstrativa. A separação em arquivo de cabeçalho (`pilha.h`) e arquivo de implementação (`pilha.c`) — ou seja, o uso de *interface* explícita imposta pelo compilador — é assunto da aula futura sobre **organização de projetos em C**. Por enquanto, manter tudo num lugar só facilita ler de cima a baixo.

### `pilha.c` — arquivo único

```c
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
```

### Compilando e rodando

Como tudo está em um só arquivo, a linha de compilação é direta:

```sh
gcc -Wall -Wextra -o pilha_demo pilha.c
./pilha_demo
```

Saída esperada:

```
Topo da pilha: 30
Desempilhando: 30 20 10
```

A linha `Desempilhando: 30 20 10` é a **prova empírica do LIFO** — exatamente a **ordem inversa** da entrada. Compare com a Fila, em que a saída foi `10 20 30` (mesma ordem da entrada).

Esse contraste é didaticamente precioso: **mesma representação interna** (lista encadeada), **resultados opostos** — porque o **contrato** (TAD) é diferente. É o que o TAD promete: o comportamento observável é definido pelo contrato, não pela estrutura escolhida para implementá-lo.

---

## 6. Exercícios Práticos

**Exercício 1 — Trace na mão.**
Considere uma pilha vazia e a sequência: `empilhar(7)`, `empilhar(3)`, `empilhar(11)`, `desempilhar`, `empilhar(5)`, `topo`, `desempilhar`, `desempilhar`. Para cada operação, escreva o estado da pilha (do topo para a base) e o valor retornado quando aplicável.

*Critério de aceitação*: 8 estados + retornos. Estado final esperado: `[7]` no topo (pilha de um único elemento).

> **Resposta mínima aceitável**
>
> | Operação           | Estado (topo → base) | Retorno |
> |--------------------|---------------------|---------|
> | `empilhar(7)`      | `[7]`               | —       |
> | `empilhar(3)`      | `[3, 7]`            | —       |
> | `empilhar(11)`     | `[11, 3, 7]`        | —       |
> | `desempilhar`      | `[3, 7]`            | `11`    |
> | `empilhar(5)`      | `[5, 3, 7]`         | —       |
> | `topo`             | `[5, 3, 7]`         | `5`     |
> | `desempilhar`      | `[3, 7]`            | `5`     |
> | `desempilhar`      | `[7]`               | `3`     |

**Exercício 2 — Função `pilha_imprimir`.**
Adicione ao `pilha.c` uma função `void pilha_imprimir(Pilha* p)` que imprime os valores **do topo para a base** no formato `[30, 20, 10]`, ou `[]` se vazia. Não pode usar `desempilhar` (a função imprime sem alterar a pilha). Acrescente chamadas a essa função na `main()` antes e depois das operações.

*Critério de aceitação*: a função fica no mesmo `pilha.c`, junto às outras operações; a `main()` chama antes e depois; saída coincide com o estado esperado.

> **Resposta mínima aceitável**
>
> ```c
> void pilha_imprimir(Pilha* p) {
>     printf("[");
>     No* atual = p->topo;
>     while (atual != NULL) {
>         printf("%d", atual->valor);
>         if (atual->proximo != NULL) printf(", ");
>         atual = atual->proximo;
>     }
>     printf("]\n");
> }
> ```
>
> O percurso é a partir de `topo`, na direção do `proximo` — exatamente a ordem topo → base.

---

## 7. Referências

- **Tenenbaum, A. M.; Langsam, Y.; Augenstein, M. J.** — *Estruturas de Dados Usando C*. Capítulo 2, *"Pilhas"*, com a discussão de implementação por vetor e por lista encadeada, e o exemplo clássico do verificador de parênteses balanceados.

- **Sedgewick, R.** — *Algoritmos em C*, Parte 1, capítulo 4, *"Abstract Data Types"*, seção sobre **pushdown stacks**. Discussão sucinta com diagramas excelentes e o paralelo entre pilha e recursão.

**Leituras complementares**:
- **CLRS** — *Algoritmos: Teoria e Prática*. Capítulo 10, seção 10.1 — *"Pilhas e filas"*. Implementação por vetor com pseudocódigo claro.
- **Ziviani, N.** — *Projeto de Algoritmos com Implementações em Pascal e C*. Capítulo de pilhas — útil para contraste em Pascal.
- **Knuth, D.** — *The Art of Computer Programming*, vol. 1, seção 2.2.1 — referência histórica sobre pilhas e filas como conceitos fundamentais.
