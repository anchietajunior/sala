---
name: aula-apresentacao
description: Monta a apresentação Reveal.js (`apresentacao.html`) de uma aula da disciplina Algoritmos e Estruturas de Dados (UniRios) a partir do `.md` correspondente, e produz os SVGs do bloco 2 quando ainda não existirem. Aplica a paleta institucional, distribui slides do mascote Eddy (~1 a cada 5–8 slides) em pontos pedagógicos, embute SVGs como `<img class="diagrama">` e usa vendor relativo (sem CDN). Use quando o usuário pedir "monte a apresentação da aula NN", "gere o reveal.js da aula sobre X", "crie os slides", ou quando o `.md` já existe e falta o `apresentacao.html` ou os SVGs. Não use para produzir o conteúdo escrito da aula — para isso, use `aula-conteudo`.
---

# Skill: aula-apresentacao

Monta o `apresentacao.html` (Reveal.js) e os SVGs do bloco 2 de uma aula da disciplina, **a partir do `.md` já existente** na pasta `aulaNN_tema/`.

## Quando usar

Use quando o conteúdo escrito da aula (`aulaNN_tema/aulaNN_tema.md`) **já existe** e falta:

- A apresentação (`apresentacao.html`); e/ou
- Os SVGs referenciados no bloco 2 (`img/NN_descritor.svg`).

Frases-gatilho:

- "Monte a apresentação da Aula 05."
- "Gere o Reveal.js da aula sobre árvore binária."
- "Crie os slides e os SVGs da Aula 7."
- "Falta a apresentação da Pilha — faz aí."

Se o `.md` **não existir** ainda, invocar primeiro a skill `aula-conteudo`. Esta skill **lê** o `.md`; não o reescreve.

## Pré-condições

Antes de começar, **sempre**:

1. Leia `CLAUDE.md` na raiz — fonte de verdade para paleta, estrutura de slides, regras do Eddy e vendor.
2. Leia o `aulaNN_tema/aulaNN_tema.md` da aula em questão — é o **roteiro** que a apresentação espelha.
3. Confira que `assets/vendor/reveal.js@5.1.0/` e `assets/bot/bot.css` existem. Se faltarem, avisar o usuário e parar — esta skill **não** baixa libs de CDN.

## Fluxo de execução

### 1. Mapear o `.md` para slides

Cada bloco do `.md` vira um conjunto de `<section>` aninhados (slide pai + sub-slides verticais). O mapeamento canônico está em `references/estrutura-slides.md` — consulte-o antes de escrever HTML.

**Regra de ouro (principal — vence as demais em caso de conflito): um slide = uma ideia, voz que conversa.** Veja a regra 5 de "Pedagogia e Linguagem" no `CLAUDE.md`. Em termos práticos ao mapear o `.md`:

- **Um parágrafo denso do `.md` quase nunca vira um único slide.** Releia o parágrafo e identifique quantas ideias distintas ele carrega. Cada ideia ganha sua própria `<section>`.
- **Limites de texto por slide**: corpo de prosa pura ≤ **~40 palavras**; prosa + bullet ≤ **~80 palavras**; bullet pura ≤ 5 itens de até 12 palavras cada.
- **Datas, autores, citações secundárias, exceções, asteriscos** → vão para slide do Eddy ou `nota-rodape`. **Nunca** para o corpo.
- Se um slide está espremido, **fatie**. Se está vazio, **junte com o adjacente**. O risco da disciplina é o primeiro caso, quase nunca o segundo.

### 2. Produzir os SVGs do bloco 2

Olhe a sequência de passos no bloco 2 do `.md` (`### Passo N: operacao(args)`). Para cada passo que ainda não tem SVG correspondente em `img/`, gerar o arquivo SVG.

Regras visuais em `references/paleta-e-estilos.md`. Em resumo:

- **Paleta institucional fixa** (`#2c5d8a`, `#5a7a9a`, `#cfd6dd`, `#f7f9fc`, `#e8f0f8`).
- **Tipografia**: `system-ui, -apple-system, 'Segoe UI', Roboto, sans-serif` no texto; `ui-monospace, 'SF Mono', Menlo, Consolas, monospace` em valores/código.
- **Texto mínimo 14px**; padding ≥ 12px.
- **ViewBox típico**: `0 0 700 ALTURA` — altura varia conforme número de nós (220 para vazio, 360+ para 2–3 nós).
- **Caixas de nó**: 120×60 com cantos `rx="4"`, divisão interna no meio para separar valor + ponteiro.
- **Setas**: stroke `#2c5d8a`, width 2.5, com `<polygon>` de ponta em triângulo.
- **NULL**: texto cinza `#888`, símbolo `∅` ou palavra `NULL`.

Modelos de SVG por padrão estão em `templates/svg/` (vazio, 1-nó, 2-nós-vertical, 2-nós-horizontal, destaque, remoção).

### 3. Distribuir os slides do Eddy

Aproximadamente **1 aparição a cada 5–8 slides**, **3 a 4 por aula no total**. Cada uma em sua **própria `<section class="eddy-slide">`** — nunca sobreposta a outro slide.

Pontos pedagógicos onde o Eddy faz mais sentido (do `CLAUDE.md`):

- Camada 2 ou 4 do bloco 1 — citação inline da bibliografia.
- Final do bloco 3 (problema motivador) — exemplo de aplicação real.
- Bloco 5 (código) — armadilha comum específica do trecho exibido.
- Bloco 6 (exercícios) — apenas **provoca**, nunca dá a resposta.

Regras de conteúdo da fala em `references/eddy-quando-usar.md`. Em resumo:

- Sempre começa com "**Turma,**".
- Até 3–4 frases.
- Cita fonte quando aplicável (`<cite>Backes, cap. X — Pilhas</cite>`).
- Sem inventar fatos históricos.

### 4. Montar o `apresentacao.html`

Use `templates/apresentacao.html.template` como esqueleto. Ele contém:

- `<head>` com vendor relativo (`../assets/vendor/...`) e `../assets/bot/bot.css`.
- `<style>` com as classes-padrão da disciplina (`.capa`, `.titulo-bloco`, `.diagrama`, `.resposta`, `.destaque`, `.nota-rodape`, `.duas-colunas`, `.eddy-slide`).
- Estrutura inicial com **capa institucional + slide-título da aula** (sem slide de "Roteiro" — proibido pelo `CLAUDE.md`).
- Script de inicialização do Reveal com transição `fade`.

Acrescente os blocos na ordem do `.md`, cada bloco numa `<section>` pai com sub-slides verticais.

### 5. Validar

Antes de declarar pronto:

- Abrir `apresentacao.html` no navegador (ou pelo menos validar mentalmente):
  - Todas as imagens `img/...svg` resolvem.
  - Caminho `../assets/vendor/...` e `../assets/bot/bot.css` está correto.
  - Não há referência a CDN externa (`cdn.jsdelivr.net`, `unpkg.com`, etc.).
- Conferir contagem aproximada de slides:
  - Aula de implementação típica: **45–65** `<section>` (incluindo verticais).
  - Aula conceitual típica: **35–50** `<section>`.
- Conferir contagem de slides do Eddy: **3 a 4**.

### 6. Atualizar o `README.md`

Confirmar que a linha da aula no `README.md` aponta tanto para o `.md` quanto para `apresentacao.html`. Se a linha já existia (criada pela skill `aula-conteudo`), só conferir.

## Regras inegociáveis (resumo)

- **Vendor sempre local** (`../assets/vendor/...`). Sem CDN.
- **Reveal.js 5.1.0 + highlight.js 11.9.0** (versões fixadas na pasta `vendor/`).
- **Tema `white`**, transição `fade`, capa institucional fixa.
- **Sem slide de "Roteiro/Sumário"** — capa institucional + título da aula vão direto para o bloco 1.
- **Eddy sempre em `<section>` dedicada**, nunca flutuando sobre outro slide.
- **SVG é o único tipo de diagrama em apresentação** — sem Mermaid em `.html`, sem PNG/JPG (a menos que o usuário peça explicitamente para uma analogia ilustrada).
- **Respostas mínimas dos exercícios** entram como `<div class="resposta fragment fade-in">`, reveladas por clique.
- **Não inventar fatos históricos** nas falas do Eddy. Se não houver certeza sobre data/autor, omitir.
- **Acentuação PT-BR completa** em todo texto visível.
- **Todo slide com `<h3>` tem uma linha-ponte logo abaixo do título**, antes de qualquer tabela, fórmula, `<pre><code>`, lista de axiomas, notação simbólica ou diagrama. A linha-ponte (**1 frase**, no máximo 2, em prosa, fonte normal) diz **o que** o aluno vai ver e **por que** importa. Detalhes e exemplos em `references/estrutura-slides.md` (seção *Linha-ponte: contexto antes do conteúdo técnico*) e na regra 4 de "Pedagogia e Linguagem" no `CLAUDE.md`. Exceções: slide do Eddy e slides puramente narrativos (já são contexto).
- **REGRA PRINCIPAL DE DESIGN DE SLIDE — uma ideia por slide, voz que conversa.** Vence as demais em conflito. Detalhes e exemplos em `references/estrutura-slides.md` (seção *Uma ideia por slide*) e na regra 5 de "Pedagogia e Linguagem" no `CLAUDE.md`. Em resumo: prosa pura ≤ ~40 palavras; prosa + bullet ≤ ~80 palavras; linguagem coloquial, frases curtas, sem subordinação pesada; se há 2+ ideias num rascunho de slide, fatie em 2+ slides.

## Saída final

Reporte em 2–3 frases:

- Arquivo gerado: `aulaNN_tema/apresentacao.html`.
- Quantos SVGs foram gerados (e quantos já existiam).
- Contagem de slides total e slides do Eddy.
- Comando para abrir: `open aulaNN_tema/apresentacao.html` (macOS) ou equivalente.
