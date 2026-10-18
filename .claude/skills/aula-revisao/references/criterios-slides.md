# Os seis critérios da revisão severa de slides

Cada eixo tem **o que procurar**, **como corrigir** e um par **ruim → bom**. Os exemplos são defeitos reais encontrados em apresentações de Algoritmos e Estruturas de Dados; os critérios valem para os slides de qualquer disciplina.

O slide é uma mídia diferente do `.md`: projetado em sala, lido em 5–10 segundos, **sem o texto em volta para socorrê-lo**. Um trecho que funciona no material escrito pode ser defeituoso como slide — e o contrário também.

---

## 1. Termo órfão

**O que procurar**

- Termo técnico, sigla, símbolo ou notação que aparece no slide **sem definição prévia na aula nem no próprio slide**.
- Termo em inglês usado como se fosse conhecido (*in-place*, *trade-off*, *search key*, *divide and conquer*).
- Notação matemática (Ω, Θ, ⌊ ⌋, log₂) sem leitura em linguagem natural ao lado.
- Termo **no título** do slide cujo corpo nunca o explica — o caso mais comum e o mais grave, porque o título é o que o aluno lê primeiro.

**Teste rápido**: cubra tudo que veio antes na apresentação. O slide sozinho ainda se sustenta, ou depende de o aluno já saber o termo?

**Como corrigir**: definir no próprio slide, em uma linha, na forma "ideia em português → **termo formal**". Só remover o termo quando ele não serve a nenhum objetivo da aula. A regra do `CLAUDE.md` é definir cada termo no primeiro uso — apagar o termo é a última opção, não a primeira.

**Ruim** *(real — Aula 02)*

```html
<h3>Espaço: as duas são <em>in-place</em></h3>
<p>Espaço mede a memória <strong>adicional</strong>, sem contar o vetor de entrada.</p>
<ul>
    <li>Linear — o índice e o contador</li>
    <li>Binária — <code>inicio</code>, <code>fim</code>, <code>meio</code></li>
</ul>
```

*"in-place" está no título e não é traduzido em lugar nenhum do slide.*

**Bom**

```html
<h3>Espaço: nenhuma das duas gasta memória extra</h3>
<p>Espaço mede a memória <strong>adicional</strong>, sem contar o vetor de entrada.</p>
<ul>
    <li>Linear — o índice e o contador</li>
    <li>Binária — <code>inicio</code>, <code>fim</code>, <code>meio</code></li>
</ul>
<blockquote>
    O número de variáveis não depende de <code>n</code> → espaço <span class="destaque">O(1)</span>.
    Um algoritmo que trabalha sobre a entrada sem construir cópia chama-se
    <span class="destaque">in-place</span>.
</blockquote>
```

---

## 2. Registro de palestra e jargão

**O que procurar**

Slide que **informa ou impressiona** como keynote, em vez de **ensinar** como aula:

- Frase de efeito que fecha o slide sem nomear nada ("é diferença de natureza", "muda tudo", "aqui mora a mágica").
- Metáfora ou analogia **solta**, sem o termo formal ao lado — o aluno sai com a imagem e sem o vocabulário.
- Conclusão vaga e não avaliável ("é muito mais rápido", "não escala", "é o segredo dos grandes sistemas").
- Tom motivacional/jornalístico onde cabia o termo canônico da disciplina.
- **Jargão** — linguagem de nicho ou informal, que não pertence ao registro acadêmico:
  - gíria técnica e anglicismo desnecessário: "rodar" (→ executar), "printar" (→ imprimir, exibir), "setar" (→ atribuir), "deletar" (→ remover), "debugar" (→ depurar);
  - bordão, slogan ou máxima de mercado, em geral atrelado a um produto: "React: a interface é uma função do estado";
  - expressão de palco ou coloquial: "mágica", "segredo", "pulo do gato", "de graça", "joga fora", "vira", "dá pra", "a gente".

  Termo técnico consagrado (ponteiro, struct, `malloc`, big-O) não é jargão. Termo em inglês entra como tradução em português + original em itálico no primeiro uso: "remover (*delete*)".

**A distinção que importa — e ela NÃO contradiz "frases curtas"**

`estrutura-slides.md` manda usar frases curtas, diretas, sem subordinação pesada. Isso é **sintaxe** e continua valendo integralmente.

Este critério é sobre **registro e vocabulário**: o slide de sala de aula usa os **termos formais ligados ao tema**. Frase curta e termo técnico preciso convivem — o inimigo é a frase curta e **vazia**.

> **Regra prática: a intuição nunca anda sozinha.** Analogia, imagem mental e frase de efeito são permitidas **acompanhadas** do termo formal, nunca no lugar dele. Ancore sempre: *imagem → nome canônico*.

**Como corrigir**: manter a frase curta, trocar o vago pelo canônico e nomear o fenômeno. Para jargão: substituir por uma **frase formal que fundamente o conteúdo** — a definição, a propriedade ou o resultado, com a fonte quando couber.

**Ruim** — bordão de mercado

```html
<p>React: a interface é uma função do estado.</p>
```

**Bom** — a mesma ideia, dita como propriedade

```html
<p>A saída exibida é determinada inteiramente pelos dados armazenados: os mesmos dados produzem sempre a mesma saída.</p>
```

**Ruim** — expressões de palco

```html
<p>A outra abre no meio, cai no P, e joga fora metade do livro de uma vez.</p>
<p>A busca binária não é rápida "de graça": ela cobra a ordenação.</p>
```

**Bom**

```html
<p>A outra abre no meio, compara a palavra procurada com a da página e descarta a metade em que ela não pode estar.</p>
<p>A busca binária tem uma pré-condição: o vetor precisa estar ordenado, e o custo de ordená-lo entra na conta.</p>
```

**Ruim** *(real — Aula 02)*

```html
<p class="nota-rodape">Não é diferença de velocidade — é diferença de natureza.</p>
```

*Efeito de palco. "Natureza" não é termo da disciplina e não é avaliável.*

**Bom**

```html
<p class="nota-rodape">
    Não é diferença de velocidade: são <strong>classes de complexidade</strong>
    distintas — O(n) contra O(log n). Trocar de máquina muda a velocidade, nunca a classe.
</p>
```

---

## 3. Excesso e repetição

**O que procurar**

- **Slide inteiro sobre tema de outra aula** — o slide desenvolve, do começo, um assunto que não é o desta aula e do qual o argumento daqui não depende. (Exige ter lido as outras aulas; é o achado mais invisível.)
- **Repetição interna** — dois slides da mesma aula dizendo o mesmo com outras palavras.
- **Slide de passagem** — não acrescenta ideia, só faz ponte que o slide seguinte já faria sozinho.
- **Sub-bullet redundante** — item que reformula o item acima.

**Pré-requisito legítimo × slide fora do tema (a distinção que salva o critério)**

Cada aula é uma unidade fechada, então **conteúdo que também aparece em outra aula não é defeito** — a mesma definição pode e deve ser repetida em toda aula que dependa dela. O defeito é de **proporção**: um assunto de que a aula depende cabe em **uma linha dentro do slide que precisa dele**; se virou slide próprio com desenvolvimento completo, a aula saiu do seu tema.

- ✅ *"Acesso por índice custa O(1) — uma multiplicação e uma soma, independentemente do tamanho. É disso que a busca binária depende."* → dá o pré-requisito em uma linha, dentro do slide que o usa, e sem citar outra aula.
- ❌ Um slide inteiro reexplicando complexidade de tempo e de espaço, do começo, numa aula cujo tema não é complexidade.
- ❌ *"Da Aula 01: acesso por índice custa O(1)."* → o conteúdo está certo, a remissão é proibida (critério 6).

**Como corrigir**: **cortar o slide** e, se o conteúdo for dependência real, comprimir em **uma linha** dentro do slide que precisa dela — escrita nas palavras desta aula, sem apontar para outra. Menos slides é o objetivo declarado — as faixas de contagem do perfil da disciplina, quando houver, são **teto, não meta**.

**Ruim** *(slide próprio para um pré-requisito, numa aula cujo tema é busca)*

```html
<h3>O que exatamente contamos</h3>
<p>A análise não cronometra segundos — segundos dependem da máquina.
   Ela conta <strong>comparações</strong> em função de <code>n</code>.</p>
<ul>
    <li><strong>Tempo</strong> — quantas comparações o algoritmo faz</li>
    <li><strong>Espaço</strong> — quanta memória <em>adicional</em> ele usa</li>
</ul>
```

**Bom** — vira uma linha dentro do slide que de fato precisa dela, e o slide próprio some

```html
<h3>A operação básica desta aula: a comparação</h3>
<p>Medimos <strong>tempo</strong> em passos e <strong>espaço</strong> em memória adicional.
   Aqui o passo tem nome — cada <strong>comparação</strong> entre a chave e um elemento.</p>
```

---

## 4. Conceito sem código

**O que procurar**

- Conceito operacional (laço, condição, índice, ponteiro, invariante, caso-base) explicado **só em prosa**, quando 3–8 linhas de código o tornariam evidente.
- A parte conceitual da aula inteiramente sem código, com todo o código represado no fim — o aluno passa metade da aula ouvindo falar de algo que nunca vê escrito.
- Armadilha descrita verbalmente ("trocar isto por aquilo causa laço infinito") sem mostrar **as duas linhas** em questão.
- E o inverso: código exibido **complexo demais** — função longa, muitas responsabilidades, recursos que a turma nunca viu.

**Como corrigir**

Adicionar o trecho mínimo, no slide onde o conceito é apresentado, seguindo as regras de código do perfil da disciplina. Em AED: `aula-conteudo/references/algoritmos-e-estruturas-de-dados/codigo-c-regras.md` (sem `<stdbool.h>`, sem `const` em parâmetro, sem `fprintf(stderr)`, nomes descritivos em PT, comentário explica o **porquê**). Em Programação Avançada, o trecho existe no código real de `projeto/`.

Limites próprios do slide (o perfil pode apertar, como os 15 linhas de Programação Avançada):

- Trecho ilustrativo em parte conceitual: **≤ 8 linhas**.
- Fatia de código na parte de implementação: **≤ 20 linhas**.
- **Legível isolado** — sem depender de declarações que ficaram em outro slide.
- `<pre><code class="language-...">` na linguagem da aula, com `<`, `>` e `&` escapados.
- Comentário no trecho é opcional; quando houver, explica a decisão, não a sintaxe.

**Ruim** *(real — Aula 02: a armadilha do laço infinito, só em prosa)*

```html
<h3>Armadilha 1 — o <code>meio ± 1</code></h3>
<p>Escrever <code>inicio = meio</code> em vez de <code>inicio = meio + 1</code>
   dá <strong>laço infinito</strong>: num trecho de dois elementos, o meio cai
   sempre no primeiro e o trecho nunca encolhe.</p>
```

**Bom** — a mesma ideia, com as duas linhas lado a lado

```html
<h3>Armadilha 1 — o <code>meio ± 1</code></h3>
<p>Num trecho de dois elementos a divisão inteira devolve sempre o primeiro.
   Sem o <code>+ 1</code>, o trecho nunca encolhe — <strong>laço infinito</strong>.</p>
<pre><code class="language-c">inicio = meio;      /* ERRADO: [6..7] continua [6..7] para sempre */
inicio = meio + 1;  /* certo: o meio ja foi comparado, sai do trecho */</code></pre>
```

---

## 5. Conceito sem visualização

**O que procurar**

Conceito que é **espacial, estrutural, sequencial ou comparativo** e está só em texto:

- Estado de uma estrutura (vetor, nó, trecho, ponteiro) descrito em palavras.
- Processo com passos ("a cada volta o trecho encolhe") sem os passos desenhados.
- Comparação de duas grandezas ou estratégias sem quadro visual.
- Antes → depois de uma operação, narrado em prosa.

**Teste rápido**: se o professor precisaria **desenhar no quadro** para explicar aquele slide, o desenho está faltando no slide.

**Como corrigir**

Criar o diagrama no formato e no estilo do perfil da disciplina. Em AED, o SVG segue `aula-slides/references/algoritmos-e-estruturas-de-dados/paleta-e-estilos.md` — paleta institucional, texto ≥ 14px, `viewBox="0 0 700 ALTURA"`. Salvar em `img/NN_descritor.svg` (próximo número livre) e embutir:

```html
<img class="diagrama" src="img/08_descritor.svg" alt="<descrição clara do que o diagrama mostra>">
```

Regras firmes: o formato do diagrama é o do perfil (AED: SVG embutido como `<img class="diagrama">`; Programação Avançada: PNG exportado do SVG mantido ao lado), sem Mermaid, sem CDN. O `alt` é obrigatório e descreve o conteúdo, não o nome do arquivo. Todo slide com diagrama mantém a **linha-ponte** dizendo o que enxergar nele.

**Reaproveitar um SVG já exibido é permitido e barato** quando serve para conectar — e não conta como repetição (critério 3), desde que a linha-ponte explique o que mudou de leitura desta vez.

**Ruim** *(real — Aula 02: a armadilha do laço infinito não tem imagem)*

Slide inteiro em prosa + código descrevendo um trecho de dois elementos que não encolhe. O aluno precisa **simular na cabeça** a divisão inteira para entender por que trava.

**Bom**

Acrescentar `img/08_laco_infinito.svg`: o trecho `[6..7]` com `meio = 6` destacado, uma seta circular voltando ao mesmo estado, e a nota de rodapé *"sem o + 1, o próximo trecho é idêntico ao atual"*. A prosa encolhe para uma linha-ponte e o diagrama carrega a explicação.

---

## 6. Referência a outra aula

Cada aula é uma **unidade fechada**. O aluno que assiste só a esta aula precisa sair dela inteiro; slide que aponta para fora manda ele buscar o que deveria estar aqui.

**O que procurar** — em qualquer lugar do slide: corpo, `nota-rodape`, linha-ponte, `blockquote`, fala do Eddy, `alt` de imagem, comentário de código, encerramento.

- Remissão ao passado: *"na Aula 02 vimos"*, *"a estrutura da aula passada"*, *"retomando o que já sabemos"*.
- Remissão ao futuro: *"na próxima aula"*, *"tema de aula futura"*, *"aula própria mais adiante"*.
- Posicionamento na sequência: *"já temos vetor e custo, agora recursão"*, *"até o fim da disciplina"*, *"tudo que vem daqui para frente"*.
- Encerramento que anuncia o conteúdo do próximo encontro.

**Como corrigir** — decidir pela necessidade do conceito **nesta** aula:

- **Necessário** → apagar a remissão e dar o conceito em **uma linha**, nas palavras desta aula, dentro do slide que o usa. Ver a distinção de proporção no critério 3.
- **Não necessário** → cortar a frase, ou o slide inteiro se ele só existia para isso.

Nomear um **tema da computação** é permitido — *"a ordenação eficiente depende disso"*, *"é a base das árvores de busca"*. Transformar o tema em **anúncio de aula**, não.

**Ruim**

```html
<p class="nota-rodape">Pilha é uma estrutura de dados com aula própria mais adiante.</p>
```

**Bom**

```html
<p class="nota-rodape">"Pilha" aqui é o nome dessa cadeia de chamadas à espera.</p>
```

---

## Ordem de aplicação

Numa passagem só, por slide, rode nesta ordem:

**3 (cortar) → 6 (desamarrar remissão) → 1 (ancorar termo) → 2 (registro) → 4 (código) → 5 (visualização)**

Dois motivos, ambos econômicos. Decidir os cortes primeiro evita escrever código e desenhar SVG para um slide que ia sair de qualquer forma. E desamarrar as remissões logo em seguida evita ancorar termo (1) num slide cujo texto ainda vai ser reescrito — trocar *"na Aula 02 vimos X"* pela explicação de X muda o slide inteiro.
