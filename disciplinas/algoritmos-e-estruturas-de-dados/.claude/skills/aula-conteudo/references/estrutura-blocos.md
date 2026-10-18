# Estrutura dos blocos da aula

Este documento detalha o que entra em cada bloco. As regras vêm do `CLAUDE.md` da raiz; aqui estão organizadas como **checklist de execução**.

A numeração canônica abaixo é a das **aulas de implementação (7 blocos)**. Em **aulas conceituais**, o bloco 5 (Código em C) é **omitido** e os seguintes são renumerados:

| Implementação (7)         | Conceitual (6)         |
|---------------------------|------------------------|
| 1. Conceito               | 1. Conceito            |
| 2. Visualização Gráfica   | 2. Visualização Gráfica|
| 3. Problema Motivador     | 3. Problema Motivador  |
| 4. Analogias              | 4. Analogias           |
| 5. Código em C            | —                      |
| 6. Exercícios             | 5. Exercícios          |
| 7. Referências            | 6. Referências         |

---

## Preâmbulo (antes do bloco 1)

Antes do "## 1. Conceito", a aula traz um único `>` (blockquote) curto:

```
> **Tipo desta aula**: implementação | conceitual. <Frase curta justificando a escolha da representação interna, OU situando o conceito no mapa da disciplina.>
```

Exemplo (Pilha): `> **Tipo desta aula**: implementação. A Pilha é o gêmeo conceitual da Fila — mesma família, política oposta. Representação escolhida: lista simplesmente encadeada com um único ponteiro topo.`

---

## Bloco 1 — Conceito (Aprofundamento Progressivo)

**6 camadas, todas obrigatórias e em ordem**. Detalhes de cada camada em `camadas-bloco1.md`.

Cabeçalho do bloco: `## 1. Conceito — Aprofundamento Progressivo`

Cada camada vira um subheading: `### Camada N — <Nome da camada>`.

Nomes canônicos das camadas:

1. Introdução
2. Definição informal com vocabulário básico
3. Propriedades e comportamento
4. Definição formal e notação
5. Análise de complexidade
6. Conexões e variantes

**Citações inline** da bibliografia já a partir da camada 2 (Backes cap. X; Veloso & Pereira cap. Y).

---

## Bloco 2 — Visualização Gráfica

Cabeçalho: `## 2. Visualização Gráfica`

Uma frase introdutória curta descrevendo o ciclo a ser ilustrado (ex.: "Ciclo de vida completo: criação, três `empilhar`, uma consulta `topo`, dois `desempilhar` até esvaziar.").

Cada passo é um subheading `### Passo N: nome_da_operacao(args)`, seguido de:

1. Um `![alt descritivo](img/NN_descritor.svg)`.
2. **1 ou 2 frases** explicando o que mudou em relação ao passo anterior — destacando ponteiros que se alteraram.

**Convenção dos passos**:

- Comece pelo passo "criar" (estrutura vazia).
- Faça 2–3 inserções até a estrutura ter conteúdo significativo.
- Faça pelo menos 1 operação de leitura (`frente`, `topo`, `buscar`).
- Faça 1–2 remoções, incluindo o caso "remover o último elemento" se isso ativar caso especial na estrutura.

**Nomes de arquivo SVG**: `NN_descritor.svg`, zero-padded, snake_case sem acento. Exemplos:

- `01_criar.svg`, `02_empilhar_10.svg`, `03_empilhar_20.svg`
- `05_frente.svg`, `06_desenfileirar.svg`, `07_desenfileirar_2.svg`

---

## Bloco 3 — Problema Motivador

Cabeçalho: `## 3. Problema Motivador`

Começa com uma **citação destacada** (`>`) contendo uma pergunta concreta no formato *"Como o X faz Y?"*. Exemplos:

- *"Como o botão Ctrl+Z funciona?"*
- *"Como o Spotify mantém o histórico de músicas tocadas?"*
- *"Como o Git detecta conflitos entre branches?"*

Depois, **2 a 4 parágrafos** explicando como a estrutura/algoritmo da aula resolve esse problema. Sempre que possível, dar um **segundo exemplo** num parágrafo final (a pilha de chamadas reforça o Ctrl+Z; o histórico do navegador reforça a pilha de páginas).

O aluno deve sair pensando: *"ah, então é por isso que isso existe."*

---

## Bloco 4 — Analogias

Cabeçalho: `## 4. Analogias`

**1 a 2 analogias** do mundo real, cada uma num parágrafo:

- `**1. <Título curto da analogia>.**` Texto explicando como o cotidiano espelha a estrutura/algoritmo.
- (opcional) `**2. <Outro título>.**` Segunda analogia.

Cenários **universais**, sem siglas locais (sem "RU", "DCE", etc.). Fila do banco, pilha de bandejas, agenda, árvore genealógica, lista de chamada — esses funcionam.

---

## Bloco 5 — Código em C *(SOMENTE em aulas de implementação)*

Cabeçalho: `## 5. Código em C`

Frase introdutória curta. Em seguida um `>` blockquote explicando que **tudo vive em um único arquivo `tema.c`** — `#include`s, structs, funções e `main()` — para que o aluno leia o programa inteiro de cima a baixo. **Não** anunciar aula futura sobre modularização: a aula é uma unidade fechada.

Subheading `### tema.c — arquivo único` (ou similar) seguido do bloco de código completo em fence ` ```c `:

```c
#include <stdio.h>
#include <stdlib.h>

// typedef struct No { ... } No;
// typedef struct Tema { ... } Tema;

// funcoes do TAD na ordem: criar, vazia, inserir, remover,
// consulta, destruir.

int main(void) {
    // demonstracao do ciclo completo.
}
```

Depois do código, subheading `### Compilando e rodando`:

```sh
gcc -Wall -Wextra -o tema_demo tema.c
./tema_demo
```

E o **bloco de saída esperada** em fence simples (sem `c`), permitindo ao aluno comparar:

```
Topo da pilha: 30
Desempilhando: 30 20 10
```

Regras de código detalhadas em `codigo-c-regras.md`.

---

## Bloco 6 — Exercícios Práticos *(bloco 5 em aulas conceituais)*

Cabeçalho: `## 6. Exercícios Práticos` (ou `## 5.` em aulas conceituais).

**3 a 5 exercícios** em ordem crescente de dificuldade. **Não rotular** com "fácil/médio/difícil" — a progressão fica implícita.

Cada exercício no formato:

```
**Exercício N — <Título curto descritivo>.**
<Enunciado claro, 1–3 parágrafos.>

*Critério de aceitação*: <condição de sucesso, entrada/saída esperadas, ou estado final esperado.>

> **Resposta mínima aceitável**
>
> <Resposta direta ou código mínimo. Para enunciados objetivos, uma tabela ou frase + axioma aplicado. Para abertos, código enxuto ou especificação mínima de TAD.>
```

Detalhes da progressão em `exercicios.md`.

---

## Bloco 7 — Referências *(bloco 6 em aulas conceituais)*

Cabeçalho: `## 7. Referências` (ou `## 6.`).

Sempre na ordem (bibliografia básica da ementa — citar as que forem pertinentes ao tema):

1. **Backes** — *Algoritmos e Estruturas de Dados em Linguagem C*. Capítulo X (nome do capítulo) — descrição da relevância (1 linha).
2. **Veloso & Pereira** — *Estruturas de Dados em C — Uma Abordagem Didática*. Capítulo Y (nome) — descrição (1 linha).
3. **Toscani & Veloso** — *Complexidade de Algoritmos* — quando a aula envolver análise de complexidade.
4. **Schildt** — *C Completo e Total* — quando a aula apoiar-se em recursos da linguagem C (ponteiros, structs, alocação).

Em seguida, um separador `**Leituras complementares**:` e lista com as que agregarem (bibliografia complementar da ementa):

- **Wirth** — *Algoritmos e Estruturas de Dados* — visão clássica do tema.
- **Damas** — *Linguagem C* — aprofundamento na linguagem.
- **Azevedo** — *Tabelas: organização e pesquisa* — quando o tema for hash/pesquisa em tabelas.
- **Forouzan & Gilbert** / **Ford & Topp** — contraste em pseudocódigo/C++ quando útil.
- **Jamsa & Klander** — *Programando em C/C++: a bíblia* — referência adicional de C.

**Nunca inventar página/capítulo.** Em caso de dúvida, citar genericamente ("ver capítulo de pilhas em Backes").
