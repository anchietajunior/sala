# Estrutura de slides — como mapear o `.md` para a apresentação

Cada bloco do `.md` vira um conjunto de `<section>` Reveal.js. **Slides verticais** (sub-slides aninhados dentro de um `<section>` pai) são usados para agrupar slides que pertencem ao mesmo bloco.

> **Regra transversal antes de qualquer mapeamento**: leia a seção *Linha-ponte: contexto antes do conteúdo técnico* mais adiante neste arquivo. Ela define a forma **mínima** de cada slide com `<h3>` — independente do bloco. Sem ela, os slides ficam órfãos (título grudado em fórmula/tabela) e a aula não funciona em sala.

A estrutura geral do `apresentacao.html`:

```html
<div class="slides">
    <!-- 1. CAPA INSTITUCIONAL (fixa) -->
    <section class="capa">...</section>

    <!-- 2. TÍTULO DA AULA -->
    <section>...</section>

    <!-- BLOCO 1 — pai com vários verticais -->
    <section>
        <section>...</section>   <!-- abertura do bloco 1 -->
        <section>...</section>   <!-- camada 1 -->
        <section>...</section>   <!-- camada 2 -->
        ...
    </section>

    <!-- BLOCO 2 — pai com vários verticais -->
    <section>...</section>

    <!-- ... blocos 3 a 7 ... -->

    <!-- ENCERRAMENTO -->
    <section class="capa">...</section>
</div>
```

**Não criar slide de Roteiro/Sumário** entre o título e o bloco 1 — proibido pelo `CLAUDE.md`.

---

## 0. Capa institucional (fixa)

```html
<section class="capa">
    <h1>Algoritmos e Estruturas de dados</h1>
    <h2>Unirios</h2>
    <div class="rodape-capa">Prof. José Anchieta</div>
</section>
```

Texto **literal** desta forma em todas as aulas.

---

## 0.5. Título da aula

```html
<section>
    <p class="titulo-bloco">Aula NN</p>
    <h1>Tema</h1>
    <p style="font-size: 0.85em; color: #666; margin-top: 0.4em;">
        <Subtítulo curto — política/política · característica chave>
    </p>
    <p style="margin-top: 1.5em; font-size: 0.7em; color: #666;">
        Aula <strong>de <implementação|conceitual></strong> — <linha curta de framing>.
    </p>
</section>
```

---

## Bloco 1 — Conceito (Aprofundamento Progressivo)

`<section>` pai contendo diretamente os slides das camadas — **não inclua slide de capa/abertura do bloco** ("Bloco 1 — Conceito — aprofundamento progressivo" com lista enumerada das 6 camadas). A apresentação entra direto na Camada 1.

1. **Slides das 6 camadas**. Cada camada tipicamente ocupa **1 a 3 slides**, conforme tamanho do conteúdo no `.md`. Comece cada camada com `<p class="titulo-bloco">Camada N</p>` seguido de `<h3>Nome da camada</h3>`.

   - **Camada 1** — 1 slide. Texto coloquial + blockquote com a frase essencial.
   - **Camada 2** — 1–2 slides. Definição + operações em bullet.
   - **Camada 3** — 2–4 slides. Sub-divida em "ponteiros / estado externo", "operações em detalhe", "invariantes".
   - **Camada 4** — 2–3 slides. Um para o TAD (com `<pre><code class="language-c">...</code></pre>`), um para axiomas em bullet, um para a tupla. Quando a camada 4 do `.md` for matemática (definição formal, notação assintótica), **não transplantar a definição para o slide** — ver seção *Matemática nos slides* adiante.
   - **Camada 5** — 1–2 slides. Um para a tabela de complexidade, outro para a comparação em prosa (use `.duas-colunas`).
   - **Camada 6** — 1–2 slides. Lista de aplicações + lista de variantes.

2. **Slide do Eddy** — 1 aparição neste bloco, tipicamente após a Camada 2 ou 4 com citação inline da bibliografia.

---

## Bloco 2 — Visualização Gráfica

`<section>` pai com:

1. Slide de abertura do bloco.
2. Um slide por passo, no formato:

   ```html
   <section>
       <h3>Passo N — operacao(args)</h3>
       <img class="diagrama" src="img/NN_descritor.svg" alt="<descrição clara>">
   </section>
   ```

3. Opcional: `<p class="nota-rodape">` em alguns slides destacando o que mudou em relação ao anterior, especialmente no passo de remoção que **ativaria** caso especial.

---

## Bloco 3 — Problema Motivador

`<section>` pai com:

1. Slide de abertura do bloco com a pergunta destacada (`<h2>` ou `<blockquote>`).
2. 1–2 slides explicando como a estrutura resolve o problema, com listas de passos.
3. Opcional: 1 slide com um segundo exemplo (ex.: pilha de chamadas para a Pilha).
4. **Slide do Eddy** — tipicamente com exemplo de aplicação real ou curiosidade.

---

## Bloco 4 — Analogias

`<section>` pai com:

1. Slide de abertura do bloco.
2. **1 slide por analogia** (1 ou 2 no total).

Aqui o Eddy é opcional — pode aparecer se tiver curiosidade histórica relacionada à analogia.

---

## Bloco 5 — Código em C *(somente em aulas de implementação)*

`<section>` pai com:

1. Slide de abertura.
2. Slide "Um único arquivo: `tema.c`" com o blockquote explicando que tudo vive num arquivo só, para ler de cima a baixo. **Sem** anunciar aula futura sobre modularização.
3. **Vários slides com fatias do código**, em vez de um único slide gigante. Tipicamente:
   - includes + structs + `criar`
   - `inserir` (ou `empilhar`/`enfileirar`)
   - `remover` (ou `desempilhar`/`desenfileirar`)
   - `consultar` + `vazia` + `destruir`
   - `main()`
   - Compilação + saída esperada

   Cada slide com `<pre><code class="language-c">...</code></pre>`. **HTML-escape** `<`, `>`, `&` no código.

4. **Slide do Eddy** — armadilha comum (ordem do `free`, esquecer de zerar o `fim`, ponteiro suspenso, etc.).

---

## Bloco 6 — Exercício Prático

> **Regra fixa da disciplina: a apresentação traz SEMPRE apenas 1 exercício** — e ele é o **exercício de implementação**: colocar de pé, em C, a estrutura ou o algoritmo que a aula acabou de mostrar. Em aula conceitual, onde não há código, o exercício é executar o algoritmo **na mão** (trace).
>
> Os outros exercícios do `.md` (que continua com 3–5, incluindo o desafio) **não viram slide**. O slide é o que a turma faz em sala; o `.md` é o material de estudo.

`<section>` pai com:

1. Slide de abertura, anunciando o exercício único.
2. Opcional: **Slide do Eddy**, **provocando** antes da tentativa ("Turma, antes de escrever qualquer linha, prevejam no papel quantas comparações..."). Nunca dá a resposta.
3. **O slide do exercício**:

   ```html
   <section>
       <h3>Exercício — implemente <o quê></h3>
       <p style="text-align: left; font-size: 0.78em;">
           <enunciado: o que escrever, sobre quais dados, e como testar>
       </p>
       <div class="resposta fragment fade-in">
           <strong>Resposta mínima aceitável:</strong>
           <critério objetivo de aceitação — saída esperada, contagens, comportamento>
       </div>
   </section>
   ```

   A classe `fragment fade-in` faz a resposta aparecer **apenas após clique** — o professor faz a turma tentar primeiro.

   A "Resposta mínima aceitável" do slide deve ser **verificável**: saída esperada, contagens concretas, ou o comportamento que prova que funcionou. Não é a solução comentada — é o critério pelo qual o aluno sabe que acertou.

---

## Bloco 7 — Referências

**1 único slide**, sem verticais. Lista a bibliografia base + complementares.

```html
<section>
    <h2>Referências</h2>
    <ul style="text-align: left; font-size: 0.75em;">
        <li><strong>Backes, A. R.</strong> ...</li>
        <li><strong>Veloso &amp; Pereira</strong> ...</li>
    </ul>
    <p class="nota-rodape" style="text-align: left;">Leituras complementares:</p>
    <ul style="text-align: left; font-size: 0.7em; color: #666;">
        <li>Wirth — ...</li>
        <li>Schildt — ...</li>
    </ul>
</section>
```

---

## Encerramento (fixo)

```html
<section class="capa">
    <h1>Fim — Tema</h1>
    <h2>Perguntas</h2>
    <p style="margin-top: 2em; font-size: 0.7em; color: #666;">
        <Frase curta fechando o que ESTA aula entregou. Sem teaser da aula seguinte
         e sem retrospectiva das anteriores — a aula é uma unidade fechada.>
    </p>
</section>
```

---

## Convenções gerais

- **Texto à esquerda** em parágrafos longos: `style="text-align: left;"`.
- **Tamanhos**: corpo principal `0.85em` em parágrafos; listas `0.78em`; notas `0.7em` ou `nota-rodape`.
- **Destaque**: `<span class="destaque">termo</span>` para palavras-chave em azul `#2c5d8a`.
- **Blockquotes**: para frases-síntese curtas (1–2 linhas). Pré-formatados pelo CSS da disciplina.
- **Tabelas**: `<table>` simples; o CSS já aplica fundo `#f0f4f8` no cabeçalho.
- **`.duas-colunas`**: usar para comparações lado-a-lado (vetor × lista, antes × depois).
- **Código inline**: `<code>palavra</code>` sempre que mencionar identificador, função ou tipo.
- **HTML-escape**: dentro de `<pre><code>`, sempre escapar `<`, `>`, `&`. Em texto corrido `<code>`, fazer o mesmo.

---

## Linha-ponte: contexto antes do conteúdo técnico

A disciplina é apresentada **em sala, projetada para a turma**. O aluno olha para o slide por segundos e precisa entender, sozinho, do que ele trata — **mesmo antes** de o professor abrir a boca. Slides que vão direto do título para uma fórmula, tabela, lista de axiomas, bloco de código ou notação simbólica deixam o aluno olhando símbolos sem chave de leitura.

### Regra

Em **toda** `<section>` da apresentação que tem `<h3>`, logo após o título deve vir uma **linha-ponte**: **1 frase** (no máximo 2), em prosa, na fonte normal do slide, que responde a uma ou às duas perguntas abaixo — não as duas se uma já basta:

1. **O que o aluno está prestes a ver?**
2. **Por que aquilo importa / qual a chave de leitura?**

Só **depois** dessa linha-ponte aparecem `<table>`, `<pre><code>`, fórmulas tipo `A = (N, valor, esq, dir, raiz)`, listas de axiomas (A1, A2, ...) ou listas técnicas densas.

### Exemplo ruim — slide órfão

O título "Representação interna como tupla" colado na fórmula. O aluno vê a tupla cair do céu, sem entender o que é uma "tupla" ou por que estamos formalizando agora.

```html
<section>
    <h3>Representação interna como tupla</h3>
    <p style="text-align: center;">
        A = (N, valor, esq, dir, raiz)
    </p>
    <ul>
        <li><strong>N</strong> — conjunto dos nós da árvore.</li>
        ...
    </ul>
</section>
```

### Exemplo bom — com linha-ponte

```html
<section>
    <h3>Representação interna como tupla</h3>
    <p style="text-align: left;">
        Agora vamos <strong>formalizar</strong> a árvore: listar, em uma única
        expressão compacta, tudo que a define — o conjunto de nós, as funções
        que ligam cada nó ao seu valor e aos seus filhos, e o ponteiro externo
        de entrada. Cada componente da tupla abaixo é detalhado em seguida.
    </p>
    <p style="text-align: center; font-family: ui-monospace, monospace;">
        A = (N, valor, esq, dir, raiz)
    </p>
    <ul>
        <li><strong>N</strong> — conjunto dos nós da árvore.</li>
        ...
    </ul>
</section>
```

### Exemplo bom — tabela de complexidade

```html
<section>
    <h3>Análise — tudo depende da altura <em>h</em></h3>
    <p style="text-align: left;">
        Toda operação de busca, inserção e remoção em uma BST percorre um
        caminho da <strong>raiz até uma folha</strong>. Por isso, o custo
        cresce com a <strong>altura <em>h</em> da árvore</strong> — e <em>h</em>
        muda drasticamente conforme a árvore esteja equilibrada ou degenerada,
        como a tabela compara.
    </p>
    <table>...</table>
</section>
```

### Estilo da linha-ponte

- **Curta** (1 frase; 2 só se realmente necessário). Não é explicação completa; é **moldura**.
- **Em prosa**, na fonte normal do corpo do slide. **Não** usar `<small>`, `<p class="nota-rodape">` ou estilo de rodapé — a linha-ponte é conteúdo principal.
- **Conecta com a narrativa**: "Agora vamos...", "Lado a lado vemos...", "Aqui aparece...", "Para entender por que isso importa, observe que...".
- **Nunca repete literalmente o título**.
- **Aplica-se também a**:
  - Slides com tabela de complexidade.
  - Slides com axiomas do TAD (A1, A2, ...).
  - Slides com representação em tupla.
  - Slides com bloco `<pre><code class="language-c">` de implementação.
  - Slides com `<img class="diagrama">` (a linha-ponte diz o que enxergar no diagrama).
  - Slides com lista de propriedades, invariantes, ou variantes.

### Exceções

- **Slide do Eddy** (`<section class="eddy-slide">`): a fala dentro do balão **já é** o contexto autocontido.
- **Slides puramente narrativos** (uma `<section>` com só `<h3>` + parágrafos de prosa contínua, sem nenhum bloco técnico): já são contexto puro, não precisam de moldura adicional.
- **Slides-capa de bloco** (quando existirem) e o **slide-título da aula**: função puramente de transição.

---

## Matemática nos slides — dose mínima, sempre contextualizada

**Não estamos ensinando matemática — estamos ensinando algoritmos a uma turma sem conhecimento prévio.** Fórmula em notação simbólica projetada na parede afugenta o aluno do conteúdo que queremos passar. A camada formal existe e é importante — mas ela vive no `.md` (camada 4), que o aluno lê no próprio ritmo, com o texto em volta. O slide é outra mídia: 5–10 segundos de olhar, em sala.

### Regras

1. **Notação simbólica pesada não entra em slide**: quantificadores (∀, ∃), conectivos lógicos (⇔, ⇒), definições com constantes (c, n₀), provas formais. Nem no corpo, nem em `.formula`.
2. **Matemática entra como referência e contagem concreta**: "Euclides, ~300 a.C.", "1.000.000 de comparações contra ~20", tabelas com números reais. Números concretos convencem sem assustar.
3. **Fórmula só quando indispensável, e então**:
   - **Pequena** — uma expressão curta: `3n + 5 → O(n)`, `meio = (inicio + fim) / 2`.
   - **Depois da ideia em português** — o slide diz a ideia em prosa primeiro; a fórmula aparece como resumo, nunca como apresentação.
   - **Com leitura em linguagem natural ao lado** — "lê-se: cresce no ritmo de n".
4. **A definição formal completa é remetida ao material escrito** — use `<p class="nota-rodape">A definição matemática completa está no material escrito da aula.</p>`.
5. **Exercícios formais do `.md`** viram enunciado em linguagem de gente no slide ("encontre um multiplicador que cubra...", "explique por que nenhum multiplicador basta..."); a resposta pode conter a expressão curta.

### Exemplo ruim — definição transplantada do `.md`

```html
<p><span class="formula">f(n) = O(g(n)) ⇔ ∃ c &gt; 0, n₀ ≥ 1 : f(n) ≤ c·g(n) ∀ n ≥ n₀</span></p>
```

O aluno de primeiro período vê ∃ e ∀ pela primeira vez na vida, no meio de uma aula que não é de lógica. Custo alto, ganho zero — a definição está no `.md`.

### Exemplo bom — mesma ideia, em português com fórmula mínima

```html
<p style="text-align: left;">
    Não contamos passos exatos — respondemos só uma pergunta:
    <strong>quando a entrada cresce, o trabalho cresce em que ritmo?</strong>
</p>
<p><span class="formula">3n + 5 passos → O(n)</span></p>
<p style="text-align: left; font-size: 0.8em;">Lê-se: "cresce no ritmo de n".</p>
<p class="nota-rodape">A definição matemática completa está no material escrito da aula.</p>
```

---

## Uma ideia por slide — regra principal de design

> **Esta é a regra mais importante** de design de slide. Em caso de conflito com qualquer outra regra deste arquivo (incluindo a linha-ponte), **esta vence**.

### O problema que essa regra resolve

A aula é projetada em sala. Aluno em sala lê o slide em 5–10 segundos e volta a ouvir o professor. Se o slide despeja **três ideias em dois parágrafos densos**, o aluno fica preso lendo, a fala do professor passa por cima sem ancorar em nada visual, e o slide passa a **competir** com a aula em vez de apoiar.

### Os três princípios

1. **Uma ideia por slide.** Se o rascunho tem 2 ou 3 ideias, **fatie em 2 ou 3 slides** (todos dentro da mesma `<section>` pai do bloco). Cada slide carrega um único ponto que o professor destaca de viva voz.

2. **Voz que conversa, não que disserta.** Frases curtas. Linguagem do dia a dia. Sem subordinação pesada (*"e isso faz com que, por sua vez, ..."*). Quando der para usar bullet curto em vez de parágrafo, prefira bullet.

3. **Texto enxuto.** Limite prático para o corpo do slide:
   - **Prosa pura**: até ~40 palavras.
   - **Prosa + bullet list**: até ~80 palavras combinadas.
   - **Bullet list pura**: até 5 itens de até ~12 palavras cada.
   - Datas, autores, citações secundárias, exceções, asteriscos → **slide do Eddy** (se vale uma pausa) ou `nota-rodape` (se é detalhe). Nunca para o corpo.

### Exemplo ruim — três ideias num só slide

```html
<section>
    <h3>Por que árvore binária balanceada importa</h3>
    <p>Inserções aleatórias tendem, na média, a altura O(log n). Mas inserções
    em ordem crescente (1, 2, 3, 4, ...) degeneram a BST: cada nova vai à direita
    do anterior, formando uma cadeia linear. A altura passa a n − 1, e a busca
    volta a ser O(n) — toda a vantagem da estrutura se perde.</p>
    <p>A solução são as árvores binárias balanceadas — AVL (1962) e rubro-negra
    (1972/1978) são as mais conhecidas. Executam rotações ao final de cada
    inserção/remoção para manter altura O(log n) garantida, não apenas esperada.</p>
</section>
```

Três ideias empilhadas: (a) caso médio é bom; (b) caso ordenado degenera; (c) solução é balancear com rotações. Mais história e datas. O aluno lê isso por 30 segundos enquanto o professor já saiu para outro ponto.

### Exemplo bom — mesma matéria, fatiada em 2+1 slides

```html
<section>
    <h3>E se inserirmos em ordem?</h3>
    <p>Insira 1, 2, 3, 4, 5 numa BST vazia. <strong>Cada novo vai à direita</strong>
    do anterior — a árvore vira uma fila vertical.</p>
    <blockquote>Altura = <em>n</em>. Busca volta a O(<em>n</em>). Perdemos tudo.</blockquote>
</section>

<section>
    <h3>A correção: rotações</h3>
    <p>Árvores <strong>balanceadas</strong> fazem pequenas rotações depois de
    cada inserção para manter a altura próxima de log <em>n</em> —
    <strong>sempre</strong>, não só na média.</p>
    <p class="nota-rodape">As mais conhecidas: AVL e rubro-negra. Implementação
    fica para a aula dedicada.</p>
</section>

<section class="eddy-slide">
    <!-- Eddy traz a história: AVL (1962) e rubro-negra (1972). -->
</section>
```

Cada slide tem **uma ideia**. O professor pode parar em cada um, pedir para a turma desenhar o caso degenerado, fazer perguntas. As datas históricas vão para o Eddy, onde se justificam como pausa narrativa.

### Diretrizes complementares

- **Cortar > acrescentar.** Antes de "publicar" um slide, releia e pergunte: *"que palavras posso remover sem perder o ponto?"*. Quase sempre sobra texto.
- **Bullets ganham de parágrafos** quando há comparação ou enumeração. Mas bullets longos viram parágrafos disfarçados — limite item a ~12 palavras.
- **Negrito é seu amigo.** Em vez de escrever mais para dar ênfase, **negrite** a palavra-chave. O olho do aluno pula direto para ela.
- **O professor preenche o resto.** Se o slide tem título + ideia central + um destaque visual (bullet, blockquote, código curto), o professor tem espaço para improvisar e dialogar com a turma. Slide cheio rouba esse espaço.
