# Algoritmos e Estruturas de Dados — UniRios

Materiais didáticos da disciplina **Algoritmos e Estruturas de Dados** da graduação na **UniRios**.

Cada aula vive em sua própria pasta (`aulaNN_tema/`) e contém:

- O conteúdo escrito em Markdown (`aulaNN_tema.md`) — referência completa para o aluno, com os blocos pedagógicos da disciplina (conceito em camadas progressivas, visualização gráfica, problema motivador, analogias, exercícios e referências; aulas de implementação adicionam o bloco de código em C).
- A apresentação em Reveal.js (`apresentacao.html`) — usada em sala, com tema claro e transições suaves.
- Diagramas em SVG (`img/`) — visualizações reaproveitadas tanto no `.md` quanto nos slides.
- Em aulas de implementação: um único arquivo `.c` autossuficiente ao lado do `.md` (sem `.h` — modularização é tema de aula futura).

A bibliografia segue a ementa oficial da disciplina: **Backes — Algoritmos e Estruturas de Dados em Linguagem C**, **Veloso & Pereira — Estruturas de Dados em C: Uma Abordagem Didática**, **Toscani & Veloso — Complexidade de Algoritmos** e **Schildt — C Completo e Total** como básica; **Wirth**, **Damas**, **Azevedo**, **Forouzan & Gilbert**, **Ford & Topp** e **Jamsa & Klander** como complementar.

## Aulas

| # | Tema | Tipo | Conteúdo (`.md`) | Apresentação |
|---|------|------|------------------|--------------|
| 01 | Fundamentos: Algoritmos, Linguagem C, Listas Sequenciais e Complexidade (Big O) | Conceitual | [aula01_fundamentos/aula01_fundamentos.md](aula01_fundamentos/aula01_fundamentos.md) | [aula01_fundamentos/apresentacao.html](aula01_fundamentos/apresentacao.html) |
| 02 | Análise de Complexidade na Prática: Busca Linear e Busca Binária | Implementação | [aula02_complexidade/aula02_complexidade.md](aula02_complexidade/aula02_complexidade.md) | [aula02_complexidade/apresentacao.html](aula02_complexidade/apresentacao.html) |
| 03 | Funções e Recursão (anatomia, parâmetros, retorno, fatorial e Fibonacci) | Conceitual | [aula03_funcoes_recursao/aula03_funcoes_recursao.md](aula03_funcoes_recursao/aula03_funcoes_recursao.md) | [aula03_funcoes_recursao/apresentacao.html](aula03_funcoes_recursao/apresentacao.html) |
| 04 | Ordenação: Bubble Sort, Merge Sort e Quick Sort | Implementação | [aula04_ordenacao/aula04_ordenacao.md](aula04_ordenacao/aula04_ordenacao.md) | [aula04_ordenacao/apresentacao.html](aula04_ordenacao/apresentacao.html) |
| 06 | Matriz (alocação dinâmica com ponteiro duplo) | Implementação | [aula06_matriz/aula06_matriz.md](aula06_matriz/aula06_matriz.md) | [aula06_matriz/apresentacao.html](aula06_matriz/apresentacao.html) |
| 08 | Listas Encadeadas (FIFO/LIFO, duplas, circulares) | Conceitual | [aula08_listas_encadeadas/aula08_listas_encadeadas.md](aula08_listas_encadeadas/aula08_listas_encadeadas.md) | [aula08_listas_encadeadas/apresentacao.html](aula08_listas_encadeadas/apresentacao.html) |
| 09 | Fila (Queue) | Implementação | [aula09_fila/aula09_fila.md](aula09_fila/aula09_fila.md) | [aula09_fila/apresentacao.html](aula09_fila/apresentacao.html) |
| 10 | Pilha (Stack) | Implementação | [aula10_pilha/aula10_pilha.md](aula10_pilha/aula10_pilha.md) | [aula10_pilha/apresentacao.html](aula10_pilha/apresentacao.html) |
| 11 | Árvores e Árvores Binárias (BST + 3 travessias) | Implementação | [aula11_arvore_binaria/aula11_arvore_binaria.md](aula11_arvore_binaria/aula11_arvore_binaria.md) | [aula11_arvore_binaria/apresentacao.html](aula11_arvore_binaria/apresentacao.html) |

## Convenções

- **Idioma**: PT-BR com acentuação completa.
- **Numeração**: pastas com dois dígitos (`aula02_`, `aula03_`, ...).
- **Diagramas**: SVG é o padrão da disciplina (paleta institucional `#2c5d8a` / `#5a7a9a` / `#cfd6dd` / `#f7f9fc` / `#e8f0f8`).
- **Apresentações**: Reveal.js 5.x, tema `white`, transição `fade`, capa fixa "Algoritmos e Estruturas de dados / Unirios".
- **Exercícios**: ordem crescente de dificuldade implícita (sem rótulos), apenas 1 desafio por aula (o último), e cada exercício acompanha "Resposta mínima aceitável".

> Este README é atualizado a cada nova aula adicionada à disciplina.
