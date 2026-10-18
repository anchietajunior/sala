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
| Apresentação | `aulas/aulaNN_tema/apresentacao.html` | **a aula inteira**: fonte da verdade, projetada em sala e usada para estudo |
| Código | `aulas/aulaNN_tema/tema.c` | só em aula de implementação: exatamente o código que os slides mostram |
| Diagramas | `aulas/aulaNN_tema/img/NN_descritor.svg` | exibidos nos slides |
| Índices | `README.md` e `disciplina.html` | uma linha por aula, apontando para a apresentação (e o `.c`) |

- Código: **um único `.c` autossuficiente** por aula (`#include`s + structs + funções + `main`). **Sem arquivos `.h`**: o aluno lê o programa inteiro de cima a baixo. (Motivo interno, **não** escrever na aula: modularização tem aula própria.)
- Vendor dos slides: `aulas/assets/vendor/reveal.js@5.1.0/`, `aulas/assets/vendor/highlight.js@11.9.0/` e o Eddy em `aulas/assets/bot/` (`bot.css`, `eddy.svg`); a apresentação referencia `../assets/...`.
- Provas, gabaritos e equipes: `atividades/`, fora do git.

## Tipos de aula

- **Conceitual** (conceito transversal: TAD, complexidade, recursão, paradigmas) → **4 blocos**, **sem `.c`**.
- **Implementação** (estrutura ou algoritmo concreto: pilha, fila, árvore, quicksort…) → **5 blocos**, **com `.c`**.
- Blocos: **1** Conceito (aprofundamento progressivo em 6 camadas) · **2** Visualização (SVG passo a passo) · **3** Problema motivador · **4** Código em C *(só implementação)* · **5** Referências. Em aula conceitual o bloco 4 some e Referências passa a ser o bloco 4.
- Em dúvida sobre a classificação, ou quando o tema for muito amplo (ex.: "Grafos"), perguntar antes de produzir.

## Slides (skill `aula-slides`)

Referências em `.claude/skills/aula-slides/references/algoritmos-e-estruturas-de-dados/`:

- `estrutura-blocos.md` - o que entra em cada bloco.
- `camadas-bloco1.md` - as 6 camadas do Aprofundamento Progressivo, com checklist por camada.
- `estrutura-slides.md` - a forma de cada bloco em `<section>`, linha-ponte, matemática nos slides e **uma ideia por slide** (a regra principal de design: vence as demais em conflito).
- `codigo-c-regras.md` - regras obrigatórias do código C didático.
- `paleta-e-estilos.md` - paleta institucional e regras visuais dos SVGs.
- `eddy-quando-usar.md` - quando e como o mascote Eddy fala.

Templates em `.claude/skills/aula-slides/templates/algoritmos-e-estruturas-de-dados/`: `apresentacao.html.template` (esqueleto com `<head>`, classes da disciplina e inicialização do Reveal), `codigo.c.template`, `eddy-slide.html` e `svg/` (vazio, um nó, dois nós vertical e horizontal, destaque, remoção).

### Conteúdo

- **Não pular blocos nem camadas**, mesmo em temas simples; todas as 6 camadas do bloco 1 vêm, em ordem.
- **Citar a bibliografia inline** já a partir da camada 2 do bloco 1, não só no slide de Referências; usar a terminologia canônica de Cormen e da ementa.
- **Não supor conhecimento prévio**: evitar conceitos de SO e Arquitetura (cache, paginação, branch prediction, MMU…) salvo se forem o tema da aula.
- Em aula de implementação, a representação interna é a mais simples possível (a que gera menos casos especiais), justificada no slide-título.
- A aula fechada vale também para os comentários do `.c`.
- **Código C didático**: o mais simples possível (o aluno vê C pela primeira vez) - sem `<stdbool.h>`, sem `const` em parâmetro, sem `fprintf(stderr)` (usar `printf` + `exit(1)`); nomes descritivos em PT (identificadores podem ser ASCII: `proximo`); comentários explicam o **porquê**, autoexplicativos, sem rótulos como "I1"; liberar memória e tratar falha de `malloc`; compilar limpo com `gcc -Wall -Wextra`.
- Ao final, acrescente a linha da aula na tabela do `README.md` e em `disciplina.html`, no estilo das linhas existentes.

### Forma

- Reveal.js 5.1.0 + highlight.js 11.9.0, tema `white`, transição `fade`.
- Capa institucional fixa + slide-título da aula, direto para o bloco 1: **sem slide de "Roteiro" ou "Sumário"**.
- Limites por slide: prosa pura até ~40 palavras; prosa + bullets até ~80; bullets puros até 5 itens de ~12 palavras. Datas, autores, citações secundárias e exceções vão para o Eddy ou para `nota-rodape`, nunca para o corpo.
- **Linha-ponte** (1 frase, no máximo 2) logo após todo `<h3>`, antes de tabela, código, fórmula ou diagrama.
- **Matemática em dose mínima**: sem quantificadores nem prova formal no slide; fórmula pequena, depois da ideia em português e com a leitura em linguagem natural. A definição simbólica completa é remetida à bibliografia, sem inventar capítulo.
- **Eddy** sempre em `<section class="eddy-slide">` dedicada, cerca de 1 a cada 5-8 slides, **3 a 4 por aula**; começa com "Turma,", até 3-4 frases, cita a fonte quando aplicável e nunca inventa fato histórico.
- **Diagramas** embutidos como `<img class="diagrama" src="img/NN_descritor.svg" alt="...">`: a classe dimensiona o SVG. Sem Mermaid, sem PNG/JPG, salvo pedido explícito.
- Contagem de `<section>` (com verticais): implementação 45-65, conceitual 35-50. É **teto, não meta**.
- Na revisão, são intocáveis: capa, título, encerramento, Referências e os 3-4 slides do Eddy.

## Consistência (conferida pela `aula-revisao`)

- [ ] Os slides trazem todos os blocos e as 6 camadas, em ordem, com citações inline a partir da camada 2.
- [ ] Aula de implementação: o `.c` compila sem warnings e executa sem falha (`gcc -Wall -Wextra -o <tmp>/aula aulas/aulaNN_tema/tema.c && <tmp>/aula`), e a saída bate com a saída esperada exibida nos slides.
- [ ] A `main()` exercita o ciclo demonstrativo do bloco 2, e cada operação do TAD da camada 4 tem uma função correspondente no `.c`.
- [ ] Todo `src="img/..."` existe e todo SVG é XML bem-formado (`xmllint --noout`).
- [ ] Os caminhos `../assets/vendor/...` e `../assets/bot/bot.css` resolvem e não há CDN.
- [ ] Eddy: 3 a 4 slides; contagem de `<section>` dentro da faixa do tipo de aula.
- [ ] `README.md` e `disciplina.html` listam a aula, apontando para a apresentação (e o `.c`).
