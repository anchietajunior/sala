---
name: aula-revisao-slides
description: Revisão severa dos slides (`apresentacao.html`) de uma aula da disciplina Algoritmos e Estruturas de Dados (UniRios). Audita cinco defeitos recorrentes — termo jogado sem explicação, registro de palestra em vez de aula, excesso e repetição do que já foi dado, conceito sem código C ilustrando, e conceito sem visualização — corrige direto no HTML e relata o que mudou e o que saiu. Use quando o usuário pedir "revisão severa dos slides", "critique os slides da aula NN", "os slides estão repetitivos / sem código / fracos", ou ao finalizar uma apresentação. Para revisar o `.md` da aula use `aula-revisao`; para gerar a apresentação do zero use `aula-apresentacao`.
---

# Skill: aula-revisao-slides

Revisor **severo** e **slides-first** da `apresentacao.html`. Não gera apresentação nova — recebe a pronta e a **endurece**: corta o que não se sustenta, ancora cada termo, exige código e imagem onde eles fazem o conceito aterrissar.

Difere da `aula-revisao`, que é `.md`-first e trata os slides como checagem de consistência. Esta skill assume que o slide tem **exigências próprias**: ele é projetado em sala, lido em 5–10 segundos, e não tem o texto em volta para socorrê-lo.

**Severo significa**: o padrão é **cortar**, não remendar. Todo slide precisa justificar sua existência.

## Quando usar

- "Faça uma revisão severa nos slides da Aula 02."
- "Critique a apresentação — está parecendo palestra."
- "Os slides estão repetindo a aula anterior."
- "Faltam exemplos de código e diagramas nos slides."

Se a `apresentacao.html` ainda não existe, é caso de `aula-apresentacao`.

## Pré-condições

1. Leia `CLAUDE.md` na raiz — fonte de verdade. Em conflito, **`CLAUDE.md` vence** qualquer referência de skill.
2. Leia a `aulaNN_tema/apresentacao.html` inteira antes de editar.
3. Leia o `aulaNN_tema/aulaNN_tema.md` — é o contrato de conteúdo que os slides espelham.
4. **Leia a aula anterior** (`aula(NN-1)_*/`, `.md` e slides). Sem isso é impossível detectar o critério 3 (repetição entre aulas).
5. Leia `references/criterios-slides.md` desta skill — heurísticas e exemplos ruim → bom.

## Os cinco critérios

Detalhamento e exemplos em `references/criterios-slides.md`. Em resumo:

1. **Termo órfão** — termo, símbolo ou notação que aparece sem ter sido definido antes **nem no próprio slide**. → *Definir no slide, ou remover o termo se ele não serve à aula.*
2. **Registro de palestra** — slide que informa/emociona como keynote em vez de ensinar: frase de efeito, metáfora solta, conclusão vaga, sem o **termo formal** do tema. → *Ancorar a intuição no vocabulário canônico da disciplina.*
3. **Excesso e repetição** — slide que repete aula anterior, repete outro slide da mesma aula, ou não acrescenta nada. → *Cortar.* Retomada só vale quando **referencia** o que já foi visto para fazer uma conexão nova.
4. **Conceito sem código** — conceito que ficaria evidente em 3–8 linhas de C e está só em prosa; ou código exibido complexo demais para quem nunca viu C. → *Adicionar o trecho curto, ou simplificar o existente.*
5. **Conceito sem visualização** — estrutura, processo ou comparação explicada só em texto, quando um diagrama a tornaria imediata. → *Criar o SVG e embutir.*

**Precedência entre critérios**: 3 (cortar) roda **antes** de 4 e 5 — não se investe código nem diagrama em slide que vai sair.

## Fluxo de execução

### 1. Inventariar

Liste todas as `<section>` na ordem, com título e bloco. Anote a contagem inicial. Marque as **intocáveis**: capa, título, encerramento, slides do Eddy, **o exercício único** com sua resposta, bloco de referências.

**Checagem de contrato no bloco de exercícios**: a apresentação traz **exatamente 1 exercício**, o de implementação. Se houver mais de um, os excedentes são **corte obrigatório** — eles vivem só no `.md`.

### 2. Varrer e julgar cada slide

Para cada slide, nesta ordem: **3 → 1 → 2 → 4 → 5**. Registre local, critério, defeito e ação.

A pergunta de corte, aplicada a todo slide: *"se eu apagar este slide, o que exatamente o aluno perde que nenhum outro slide dá?"* Se a resposta for "nada" ou "só a repetição", **corta**.

### 3. Aplicar as correções

Na ordem: **cortar → ancorar termos → corrigir registro → adicionar código → adicionar visualização**.

- **Código novo**: siga `aula-conteudo/references/codigo-c-regras.md` (proibições e estilo). Limites do slide: trecho ilustrativo **≤ 8 linhas**, fatia do bloco 5 **≤ 20 linhas**, legível isolado, `<pre><code class="language-c">` com `<`, `>` e `&` escapados.
- **SVG novo**: siga `aula-apresentacao/references/paleta-e-estilos.md`. Arquivo em `img/NN_descritor.svg`, embutido como `<img class="diagrama">` com `alt` descritivo. **Sem CDN, sem PNG/JPG, sem Mermaid.**
- Todo slide com `<h3>` mantém sua **linha-ponte** após o título (`aula-apresentacao/references/estrutura-slides.md`).

### 4. Validar

Antes de declarar pronto, rodar de fato:

- Todo `src="img/..."` referenciado **existe**; todo SVG novo é XML bem-formado (`xmllint --noout`).
- Zero referência a CDN ou `http(s)://` no HTML.
- Contagem final de `<section>` e de `eddy-slide` (Eddy permanece 3–4).

### 5. Relatar

Agrupado pelos cinco critérios: achados, corrigidos, e a **lista explícita de todo slide removido, pelo título**. Contagem antes → depois. O que foi sinalizado mas não corrigido por depender de decisão do usuário.

## Regras inegociáveis

- **Cortar é o padrão.** Em dúvida entre remendar e remover, remova — e relate.
- **Nunca cortar em silêncio.** Todo slide removido aparece no relatório pelo título.
- **O contrato didático vence a severidade.** Não removem-se: capa, título, encerramento, o **exercício único** com sua "Resposta mínima aceitável", bloco de Referências, nem os 3–4 slides do Eddy. Bloco previsto pela estrutura não desaparece inteiro.
- **Exercício é sempre 1, e é o de implementação.** Mais de um exercício no slide é defeito, não riqueza.
- **Intuição nunca anda sozinha.** Analogia e frase de efeito são permitidas **acompanhadas** do termo formal — nunca no lugar dele.
- **Matemática segue a dose mínima** de `aula-apresentacao/references/estrutura-slides.md`: sem quantificadores nem prova formal no slide; o rigor vive no `.md`.
- **Uma ideia por slide** continua sendo a regra principal de design — cortar não pode gerar slide-tijolo com três ideias empilhadas.
- **Slides e `.md` terminam consistentes.** Se um corte deixa o slide contando história diferente do `.md`, ajuste o `.md` ou desfaça o corte.
- **Vendor local, PT-BR acentuado** em todo texto tocado.

## Saída final

Reporte em poucas frases: arquivo revisado, contagem de `<section>` antes → depois, achados por critério, lista de slides removidos, SVGs e trechos de código adicionados, e o comando para reabrir (`open aulaNN_tema/apresentacao.html` — lembrar que o Reveal.js exige recarregar a aba).
