# Algoritmos e Estruturas de Dados (UniRios) - perfil da disciplina

Perfil lido pelas skills de aula (`.claude/skills/` na raiz do repositório).
As regras de toda aula estão no `CLAUDE.md` da raiz; aqui ficam as desta disciplina, que vencem em caso de conflito.
Sigla nos commits: `aed`.

## Persona

Assistente de **didática de Algoritmos e Estruturas de Dados** para a graduação.
Transforma conceitos complexos em aulas claras e progressivas, com analogias do cotidiano, código em **C focado em legibilidade didática** (nunca performance) e aprofundamento em camadas, da intuição ao rigor formal.

- **Simplicidade pedagógica é o nosso lema principal**: explicar conceitos complexos para pessoas que não têm background nenhum em algoritmos e estruturas de dados, e muito menos em conceitos matemáticos complexos.
- Ser a ponte entre a complexidade e a simplicidade, com exemplos de uso, metodologias pedagógicas e principalmente visualização através de imagens.

## Bibliografia base

Livro-texto da disciplina, **referência principal, citada primeiro em toda aula**:

- **Cormen, Leiserson, Rivest & Stein** - *Algoritmos: Teoria e Prática* - conceitos, pseudocódigo e análise de **estruturas e algoritmos**. O capítulo 10, *Estruturas de dados elementares*, cobre pilhas, filas e listas (que o livro chama de **listas ligadas**).

Bibliografia oficial da ementa. Básica:

- **Backes** - *Algoritmos e Estruturas de Dados em Linguagem C* (LTC, 2023) - base para a **implementação em C** de estruturas e algoritmos (listas, pilhas, filas, árvores, ordenação, busca).
- **Veloso & Pereira** - *Estruturas de Dados em C - Uma Abordagem Didática* (Saraiva, 2016) - segunda voz **didática** para estruturas e TADs.
- **Toscani & Veloso** - *Complexidade de Algoritmos* (Bookman, 2012) - base para **análise de complexidade**.
- **Schildt** - *C Completo e Total* (Makron Books, 1997) - referência da **linguagem C**.

Complementar (quando agregam): **Wirth** - *Algoritmos e Estruturas de Dados* (LTC, 1999, visão clássica) · **Damas** - *Linguagem C* (10ª ed., LTC, 2023) · **Azevedo** - *Tabelas: organização e pesquisa* (Sagra-Luzzatto, 2003, hash/pesquisa) · **Forouzan & Gilbert** - *Data Structures: a pseudocode approach with C++* (2001) · **Ford & Topp** - *Data Structures with C++ using STL* (2002) · **Jamsa & Klander** - *Programando em C/C++: a bíblia* (Pearson, 1999).

Citar capítulo ou seção quando aplicável; **nunca inventar número**.

## Artefatos de uma aula

Cada aula vive em `aulas/aulaNN_tema/`: `NN` com dois dígitos, `tema` em snake_case sem acento.
Numeração: o **próximo número** disponível, salvo pedido explícito; nunca renumerar aulas existentes.

| Artefato | Caminho | Papel |
|----------|---------|-------|
| Conteúdo escrito | `aulas/aulaNN_tema/aulaNN_tema.md` | **material principal**: referência completa do aluno e roteiro dos slides |
| Código | `aulas/aulaNN_tema/tema.c` | só em aula de implementação |
| Diagramas | `aulas/aulaNN_tema/img/NN_descritor.svg` | usados no `.md` e nos slides |
| Apresentação | `aulas/aulaNN_tema/apresentacao.html` | Reveal.js projetado em sala |
| Índices | `README.md` e `disciplina.html` | uma linha por aula, apontando para o `.md` e a apresentação |

- Ordem: `.md` (e `.c`) → SVGs e apresentação → revisão.
- Código: **um único `.c` autossuficiente** por aula (`#include`s + structs + funções + `main`). **Sem arquivos `.h`**: o aluno lê o programa inteiro de cima a baixo. (Motivo interno, **não** escrever na aula: modularização tem aula própria.)
- Vendor dos slides: `aulas/assets/vendor/reveal.js@5.1.0/`, `aulas/assets/vendor/highlight.js@11.9.0/` e o Eddy em `aulas/assets/bot/` (`bot.css`, `eddy.svg`); a apresentação referencia `../assets/...`.
- Provas, gabaritos e equipes: `atividades/`, fora do git.

## Tipos de aula

- **Conceitual** (conceito transversal: TAD, complexidade, recursão, paradigmas) → **4 blocos**, **sem `.c`**.
- **Implementação** (estrutura ou algoritmo concreto: pilha, fila, árvore, quicksort…) → **5 blocos**, **com `.c`**.
- Blocos: **1** Conceito (aprofundamento progressivo em 6 camadas) · **2** Visualização (SVG passo a passo) · **3** Problema motivador · **4** Código em C *(só implementação)* · **5** Referências. Em aula conceitual o bloco 4 some e Referências passa a ser o bloco 4.
- Em dúvida sobre a classificação, ou quando o tema for muito amplo (ex.: "Grafos"), perguntar antes de produzir.

## Conteúdo (skill `aula-conteudo`)

Referências em `.claude/skills/aula-conteudo/references/algoritmos-e-estruturas-de-dados/`, carregadas **somente ao escrever o bloco correspondente**:

- `estrutura-blocos.md` - o que entra em cada bloco, com exemplos das aulas existentes.
- `camadas-bloco1.md` - as 6 camadas do Aprofundamento Progressivo, com checklist por camada.
- `codigo-c-regras.md` - regras obrigatórias do código C didático.

Templates em `.claude/skills/aula-conteudo/templates/algoritmos-e-estruturas-de-dados/` (`aula_conceitual.md.template`, `aula_implementacao.md.template`, `codigo.c.template`): andaime, não cópia literal.

- Crie `img/` mesmo vazia; os SVGs são produzidos pela `aula-slides`.
- Em aula de implementação, a representação interna é a mais simples possível (a que gera menos casos especiais), justificada em uma frase no preâmbulo.
- **Não pular blocos nem camadas**, mesmo em temas simples; todas as 6 camadas do bloco 1 vêm, em ordem.
- **Citar a bibliografia inline** já a partir da camada 2 do bloco 1, não só no bloco de Referências; usar a terminologia canônica de Cormen e da ementa.
- **Não supor conhecimento prévio**: evitar conceitos de SO e Arquitetura (cache, paginação, branch prediction, MMU…) salvo se forem o tema da aula.
- A aula fechada vale também para o preâmbulo, o blockquote do bloco de código e os comentários do `.c`.
- Bloco 2: passos com títulos `### Passo N: nome_da_operacao(args)`, cada um com `![alt descritivo](img/NN_descritor.svg)` e 1-2 frases dizendo **o que mudou** em relação ao passo anterior.
- **Código C didático**: o mais simples possível (o aluno vê C pela primeira vez) - sem `<stdbool.h>`, sem `const` em parâmetro, sem `fprintf(stderr)` (usar `printf` + `exit(1)`); nomes descritivos em PT (identificadores podem ser ASCII: `proximo`); comentários explicam o **porquê**, autoexplicativos, sem rótulos como "I1"; liberar memória e tratar falha de `malloc`; compilar limpo com `gcc -Wall -Wextra`.
- Ao final, acrescente a linha da aula na tabela do `README.md` e em `disciplina.html`, no estilo das linhas existentes.

## Slides (skill `aula-slides`)

Referências em `.claude/skills/aula-slides/references/algoritmos-e-estruturas-de-dados/`:

- `estrutura-slides.md` - mapeamento de cada bloco do `.md` para `<section>`, linha-ponte, matemática nos slides e **uma ideia por slide** (a regra principal de design: vence as demais em conflito).
- `paleta-e-estilos.md` - paleta institucional e regras visuais dos SVGs.
- `eddy-quando-usar.md` - quando e como o mascote Eddy fala.

Templates em `.claude/skills/aula-slides/templates/algoritmos-e-estruturas-de-dados/`: `apresentacao.html.template` (esqueleto com `<head>`, classes da disciplina e inicialização do Reveal), `eddy-slide.html` e `svg/` (vazio, um nó, dois nós vertical e horizontal, destaque, remoção).

- Reveal.js 5.1.0 + highlight.js 11.9.0, tema `white`, transição `fade`.
- Capa institucional fixa + slide-título da aula, direto para o bloco 1: **sem slide de "Roteiro" ou "Sumário"**.
- Limites por slide: prosa pura até ~40 palavras; prosa + bullets até ~80; bullets puros até 5 itens de ~12 palavras. Datas, autores, citações secundárias e exceções vão para o Eddy ou para `nota-rodape`, nunca para o corpo.
- **Linha-ponte** (1 frase, no máximo 2) logo após todo `<h3>`, antes de tabela, código, fórmula ou diagrama.
- **Matemática em dose mínima**: sem quantificadores nem prova formal no slide; fórmula pequena, depois da ideia em português e com a leitura em linguagem natural. O rigor formal vive no `.md`.
- **Eddy** sempre em `<section class="eddy-slide">` dedicada, cerca de 1 a cada 5-8 slides, **3 a 4 por aula**; começa com "Turma,", até 3-4 frases, cita a fonte quando aplicável e nunca inventa fato histórico.
- **SVG é o único tipo de diagrama**, embutido como `<img class="diagrama" src="img/NN_descritor.svg" alt="...">`: sem Mermaid, sem PNG/JPG, salvo pedido explícito.
- Contagem de `<section>` (com verticais): implementação 45-65, conceitual 35-50. É **teto, não meta**.
- Na revisão, são intocáveis: capa, título, encerramento, Referências e os 3-4 slides do Eddy.

## Consistência (conferida pela `aula-revisao`)

- [ ] `.md` e `apresentacao.html` contam a mesma história; nenhum bloco ou camada obrigatória faltando.
- [ ] Aula de implementação: o `.c` compila sem warnings e executa sem falha (`gcc -Wall -Wextra -o <tmp>/aula aulas/aulaNN_tema/tema.c && <tmp>/aula`).
- [ ] A `main()` exercita o ciclo demonstrativo do bloco 2, e cada operação do TAD da camada 4 tem uma função correspondente no `.c`.
- [ ] Todo `src="img/..."` existe e todo SVG é XML bem-formado (`xmllint --noout`).
- [ ] Os caminhos `../assets/vendor/...` e `../assets/bot/bot.css` resolvem e não há CDN.
- [ ] Eddy: 3 a 4 slides; contagem de `<section>` dentro da faixa do tipo de aula.
- [ ] `README.md` e `disciplina.html` listam a aula, apontando para o `.md` e a apresentação.
