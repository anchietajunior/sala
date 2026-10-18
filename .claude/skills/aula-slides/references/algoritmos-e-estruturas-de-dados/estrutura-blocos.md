# Estrutura dos blocos da aula

Este documento detalha **o que** entra em cada bloco da aula, como checklist de execução.
A forma de cada bloco em slides (`<section>`, classes, limites de texto) está em `estrutura-slides.md`; as regras gerais, no perfil da disciplina.

A numeração canônica abaixo é a das **aulas de implementação (5 blocos)**. Em **aulas conceituais**, o bloco 4 (Código em C) é **omitido** e Referências passa a ser o bloco 4:

| Implementação (5)         | Conceitual (4)         |
|---------------------------|------------------------|
| 1. Conceito               | 1. Conceito            |
| 2. Visualização Gráfica   | 2. Visualização Gráfica|
| 3. Problema Motivador     | 3. Problema Motivador  |
| 4. Código em C            | —                      |
| 5. Referências            | 4. Referências         |

---

## Slide-título (antes do bloco 1)

Traz o tipo da aula e uma linha curta de framing: a justificativa da representação interna escolhida (implementação) ou o lugar do conceito na computação (conceitual).

Exemplo (Pilha): *Aula de implementação — lista simplesmente encadeada com um único ponteiro `topo`.*

---

## Bloco 1 — Conceito (Aprofundamento Progressivo)

**6 camadas, todas obrigatórias e em ordem**. O conteúdo de cada camada está em `camadas-bloco1.md`.

Nomes canônicos das camadas:

1. Introdução
2. Definição informal com vocabulário básico
3. Propriedades e comportamento
4. Definição formal e notação
5. Análise de complexidade
6. Conexões e variantes

**Citações inline** da bibliografia já a partir da camada 2 (Backes cap. X; Veloso & Pereira cap. Y), no corpo, na `nota-rodape` ou na fala do Eddy.

---

## Bloco 2 — Visualização Gráfica

Abre com uma frase descrevendo o ciclo a ser ilustrado (ex.: "Ciclo de vida completo: criação, três `empilhar`, uma consulta `topo`, dois `desempilhar` até esvaziar.").

Cada passo é um slide `Passo N — nome_da_operacao(args)` com o diagrama do estado e **1 ou 2 frases** dizendo o que mudou em relação ao passo anterior, destacando os ponteiros que se alteraram.

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

Abre com uma **pergunta concreta** em destaque, no formato *"Como o X faz Y?"*. Exemplos:

- *"Como o botão Ctrl+Z funciona?"*
- *"Como o Spotify mantém o histórico de músicas tocadas?"*
- *"Como o Git detecta conflitos entre branches?"*

Depois, como a estrutura ou o algoritmo da aula resolve esse problema, em passos. Sempre que possível, um **segundo exemplo** (a pilha de chamadas reforça o Ctrl+Z; o histórico do navegador reforça a pilha de páginas).

O aluno deve sair pensando: *"ah, então é por isso que isso existe."*

---

## Bloco 4 — Código em C *(SOMENTE em aulas de implementação)*

O código vive no arquivo `tema.c` da pasta da aula e é **exatamente** o que os slides mostram.

- Um slide explica que **tudo vive em um único arquivo `tema.c`** — `#include`s, structs, funções e `main()` — para que o aluno leia o programa inteiro de cima a baixo. A aula é uma unidade fechada: o slide não anuncia aula sobre modularização.
- Funções do TAD na ordem: criar, vazia, inserir, remover, consulta, destruir.
- A `main()` demonstra o ciclo completo do bloco 2.
- O código aparece em fatias, uma por slide, seguidas de um slide com a compilação e a saída esperada, para o aluno comparar:

```sh
gcc -Wall -Wextra -o tema_demo tema.c
./tema_demo
```

```
Topo da pilha: 30
Desempilhando: 30 20 10
```

Regras de código detalhadas em `codigo-c-regras.md`; esqueleto do arquivo em `templates/algoritmos-e-estruturas-de-dados/codigo.c.template`.

---

## Bloco 5 — Referências *(bloco 4 em aulas conceituais)*

Sempre na ordem (bibliografia básica da ementa — citar as que forem pertinentes ao tema):

1. **Backes** — *Algoritmos e Estruturas de Dados em Linguagem C*. Capítulo X (nome do capítulo) — descrição da relevância (1 linha).
2. **Veloso & Pereira** — *Estruturas de Dados em C — Uma Abordagem Didática*. Capítulo Y (nome) — descrição (1 linha).
3. **Toscani & Veloso** — *Complexidade de Algoritmos* — quando a aula envolver análise de complexidade.
4. **Schildt** — *C Completo e Total* — quando a aula apoiar-se em recursos da linguagem C (ponteiros, structs, alocação).

Em seguida, **Leituras complementares**, com as que agregarem (bibliografia complementar da ementa):

- **Wirth** — *Algoritmos e Estruturas de Dados* — visão clássica do tema.
- **Damas** — *Linguagem C* — aprofundamento na linguagem.
- **Azevedo** — *Tabelas: organização e pesquisa* — quando o tema for hash/pesquisa em tabelas.
- **Forouzan & Gilbert** / **Ford & Topp** — contraste em pseudocódigo/C++ quando útil.
- **Jamsa & Klander** — *Programando em C/C++: a bíblia* — referência adicional de C.

**Nunca inventar página/capítulo.** Em caso de dúvida, citar genericamente ("ver capítulo de pilhas em Backes").
