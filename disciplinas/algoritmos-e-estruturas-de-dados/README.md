# Algoritmos e Estruturas de Dados — UniRios

Materiais didáticos da disciplina **Algoritmos e Estruturas de Dados** da graduação na **UniRios**.

Cada aula vive em sua própria pasta (`aulaNN_tema/`) e contém:

- O conteúdo escrito em Markdown (`aulaNN_tema.md`) — referência completa para o aluno, com os blocos pedagógicos da disciplina (conceito em camadas progressivas, visualização gráfica, problema motivador, analogias, exercícios e referências; aulas de implementação adicionam o bloco de código em C).
- A apresentação em Reveal.js (`apresentacao.html`) — usada em sala, com tema claro e transições suaves.
- Diagramas em SVG (`img/`) — visualizações reaproveitadas tanto no `.md` quanto nos slides.
- Em aulas de implementação: arquivos `.h`, `.c` e `main.c` executáveis ao lado do `.md`.

A bibliografia base é **Tenenbaum — Estruturas de Dados Usando C** e **Sedgewick — Algoritmos em C**, com **CLRS** e **Ziviani** como leitura complementar.

## Aulas

| # | Tema | Tipo | Conteúdo (`.md`) | Apresentação |
|---|------|------|------------------|--------------|
| 02 | Listas Encadeadas (FIFO/LIFO, duplas, circulares) | Conceitual | [aula02_listas_encadeadas/aula02_listas_encadeadas.md](aula02_listas_encadeadas/aula02_listas_encadeadas.md) | [aula02_listas_encadeadas/apresentacao.html](aula02_listas_encadeadas/apresentacao.html) |
| 03 | Fila (Queue) | Implementação | [aula03_fila/aula03_fila.md](aula03_fila/aula03_fila.md) | [aula03_fila/apresentacao.html](aula03_fila/apresentacao.html) |
| 04 | Pilha (Stack) | Implementação | [aula04_pilha/aula04_pilha.md](aula04_pilha/aula04_pilha.md) | [aula04_pilha/apresentacao.html](aula04_pilha/apresentacao.html) |

## Convenções

- **Idioma**: PT-BR com acentuação completa.
- **Numeração**: pastas com dois dígitos (`aula02_`, `aula03_`, ...).
- **Diagramas**: SVG é o padrão da disciplina (paleta institucional `#2c5d8a` / `#5a7a9a` / `#cfd6dd` / `#f7f9fc` / `#e8f0f8`).
- **Apresentações**: Reveal.js 5.x, tema `white`, transição `fade`, capa fixa "Algoritmos e Estruturas de dados / Unirios".
- **Exercícios**: ordem crescente de dificuldade implícita (sem rótulos), apenas 1 desafio por aula (o último), e cada exercício acompanha "Resposta mínima aceitável".

> Este README é atualizado a cada nova aula adicionada à disciplina.
