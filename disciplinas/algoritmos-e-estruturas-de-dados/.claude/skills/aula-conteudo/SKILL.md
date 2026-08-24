---
name: aula-conteudo
description: Monta o conteúdo Markdown de uma nova aula da disciplina Algoritmos e Estruturas de Dados (UniRios), seguindo a estrutura de blocos definida em CLAUDE.md — 6 blocos para aulas conceituais, 7 para aulas de implementação. Para aulas de implementação, também produz o arquivo `.c` único e autossuficiente. Use quando o usuário pedir "monte a aula sobre X", "crie a aula NN sobre Y", "gere o conteúdo da aula de Z" ou equivalente. Não use para produzir apenas a apresentação Reveal.js — para isso, use `aula-apresentacao`.
---

# Skill: aula-conteudo

Monta o **conteúdo escrito** (`aulaNN_tema.md`) de uma aula da disciplina, mais o arquivo `.c` único quando a aula for de implementação.

## Quando usar

Aciona quando o usuário pedir o **conteúdo da aula** (`.md`), ou quando pedir uma aula "completa" sem qualificar. Para apenas a apresentação Reveal.js, use a skill `aula-apresentacao`. Para apenas os exercícios ou apenas o código, atenda diretamente sem invocar a skill inteira — mas mantenha as mesmas regras de progressão e legibilidade.

Frases-gatilho típicas:

- "Monte a aula sobre Pilha."
- "Crie o conteúdo da aula 7 sobre Árvore Binária."
- "Gere a aula de implementação de Tabela Hash."
- "Faça uma aula conceitual sobre análise de complexidade."

## Pré-condições

Antes de começar, **sempre**:

1. Leia `CLAUDE.md` na raiz do projeto. Ele é a fonte de verdade — esta skill é um guia de execução, não substituto. Em caso de conflito, o `CLAUDE.md` vence.
2. Liste as pastas `aulaNN_*` existentes para decidir o número da nova aula (próximo disponível, salvo pedido explícito do usuário).
3. Classifique a aula em **conceitual** (6 blocos, sem `.c`) ou **implementação** (7 blocos, com `.c`). Em caso de dúvida real, pergunte ao usuário **antes** de produzir; em casos óbvios, decida e diga em uma linha qual classificação foi adotada.

## Fluxo de execução

Sigo este fluxo em ordem. Quando um passo for trivial, executo direto; quando exigir decisão, faço uma escolha razoável e prossigo.

### 1. Coletar contexto

- Tema da aula (`tema` em snake_case sem acento) e número (`NN` com dois dígitos).
- Tipo (conceitual / implementação).
- Representação interna a ser implementada (apenas para implementação). Por padrão, a mais simples possível — a que dá origem ao menor número de casos especiais. Justifico a escolha em uma frase no preâmbulo da aula.
- Se a aula depender de um conceito já tratado em outra aula (ex.: o **nó** das estruturas encadeadas), **apresentar esse conceito do zero aqui**, com definição e exemplo próprios — sem citar a outra aula. A aula é uma unidade fechada; ver *Regras inegociáveis*.

### 2. Criar a pasta e o esqueleto

- Pasta: `aulaNN_tema/`.
- Arquivo principal: `aulaNN_tema/aulaNN_tema.md`.
- Subpasta para diagramas: `aulaNN_tema/img/` (criar mesmo que comece vazia — os SVGs serão produzidos pela skill `aula-apresentacao` ou em iteração separada).
- Em aula de implementação: `aulaNN_tema/tema.c` (um único arquivo, `#include`s + structs + funções + `main()`).

### 3. Escrever os blocos

Use o template adequado em `templates/` como **andaime**, não como cópia literal — cada aula tem nuances. A sequência canônica:

**Aula de implementação (7 blocos)**:
1. Conceito — Aprofundamento Progressivo (6 camadas)
2. Visualização Gráfica (sequência de passos com referência a `img/NN_descritor.svg`)
3. Problema Motivador
4. Analogias (1–2)
5. Código em C (`tema.c` único)
6. Exercícios Práticos (3–5, progressão implícita, último é o desafio)
7. Referências

**Aula conceitual (6 blocos)** — sem o bloco 5 acima, e a renumeração desloca os seguintes (Exercícios vira 5, Referências vira 6).

Detalhes de cada parte estão em `references/`:

- `references/estrutura-blocos.md` — o que entra em cada bloco, com exemplos das aulas existentes.
- `references/camadas-bloco1.md` — as 6 camadas do Aprofundamento Progressivo, com checklist por camada.
- `references/codigo-c-regras.md` — regras obrigatórias do código C didático (sem `<stdbool.h>`, sem `const`, sem `fprintf(stderr)`, etc.).
- `references/exercicios.md` — progressão de dificuldade, formato da "Resposta mínima aceitável", o que cada exercício deve conter.

Carregue cada referência **somente quando** for escrever o bloco correspondente.

### 4. Atualizar o `README.md` da raiz

Adicionar uma linha na tabela de aulas. Manter o estilo das linhas existentes.

### 5. Validar (aula de implementação)

Antes de declarar pronto, em aula de implementação:

- Compilar o `.c` mentalmente (ou de fato, com `gcc -Wall -Wextra -o /tmp/demo aulaNN_tema/tema.c && /tmp/demo`) — não pode produzir warnings nem segfaults.
- Conferir que a `main()` exercita o ciclo completo demonstrativo descrito no bloco 2.
- Conferir que cada operação do TAD definido no bloco 1, camada 4, tem uma função correspondente no `.c`.

## Regras inegociáveis (resumo)

Estas são extraídas do `CLAUDE.md` e existem para garantir consistência entre aulas. Quebrá-las requer pedido explícito do usuário.

- **PT-BR com acentuação correta** em todo texto. Identificadores em código podem ser ASCII (`proximo` no lugar de `próximo`).
- **Não pular blocos nem camadas** — todos os 6/7 blocos vêm, em ordem; todas as 6 camadas do bloco 1 vêm, em ordem.
- **Citações inline** da bibliografia base já a partir da camada 2 do bloco 1, **não** apenas no bloco de Referências.
- **Não cunhar coloquialismos** para conceitos técnicos (sem "tripa", "miolo", "espiar", "cuspir" etc.); use a terminologia canônica de Backes/Veloso & Pereira/Toscani & Veloso.
- **Não supor conhecimento prévio** — cada termo técnico definido no primeiro uso. Conceitos avançados de SO/arquitetura (cache, paginação, branch prediction, MMU…) ficam fora salvo se forem o tema da aula.
- **Cada aula é uma unidade fechada.** Nenhum trecho do `.md`, do `.c` ou dos comentários menciona outra aula — nem anterior ("como vimos na Aula 02", "ponte com a Aula 01"), nem posterior ("tema de aula futura", "na próxima aula"). Conceito de que a aula depende é apresentado **nela mesma**, com definição e exemplo próprios; o que não couber assim, fica de fora. Vale inclusive para o blockquote do bloco de código e para o preâmbulo.
- **Um único `.c` por aula**, sem `.h` separado. (Motivo, para o agente — **não** escrever isto na aula: modularização é tema de outra aula.)
- **Comentários no `.c` autoexplicativos** — não usar rótulos abreviados (I1, I2…) que só fazem sentido com a tabela do `.md` aberta ao lado.
- **Exercícios sem rótulos de dificuldade** (não escreva "fácil/médio/difícil") — a progressão fica implícita na ordem. Apenas 1 desafio por aula, sempre o último. Cada exercício acompanha **"Resposta mínima aceitável"** explicitamente rotulada.
- **Bibliografia** (ementa oficial — lista completa no `CLAUDE.md`): básica = Backes, Veloso & Pereira, Toscani & Veloso (complexidade), Schildt (linguagem C); complementar = Wirth, Damas, Azevedo, Forouzan & Gilbert, Ford & Topp, Jamsa & Klander. Nunca inventar página/capítulo — se não souber, citar genericamente ("ver capítulo de pilhas em Backes").

## Sobre os SVGs do bloco 2

O `.md` referencia SVGs em `img/NN_descritor.svg`, mas **gerar os SVGs em si é responsabilidade da skill `aula-apresentacao`** (ou de uma sessão dedicada a diagramas). O que esta skill produz no bloco 2 é:

- A sequência de passos, **com títulos no formato `### Passo N: nome_da_operacao(args)`**.
- Para cada passo, um `![alt descritivo](img/NN_descritor.svg)` e 1–2 frases explicando **o que mudou** em relação ao passo anterior.
- Os nomes de arquivo SVG seguem o padrão `NN_descritor.svg` (zero-padded, snake_case sem acento).

Se a pasta `img/` estiver vazia ao final, ok — a próxima skill cuida disso. Sinalize ao usuário no resumo final.

## Saída final

Ao terminar, reporte em 2–3 frases:

- Quais arquivos foram criados (`aulaNN_tema.md`, `tema.c`, `img/` vazia ou não).
- Linha adicionada ao `README.md`.
- Próximo passo recomendado: produzir os SVGs + apresentação com `aula-apresentacao`.
