---
name: aula-roteiro
description: Gera o roteiro do professor em .html para uma aula da disciplina Programação Avançada (rastreador de leituras com FastAPI + React). Use quando o usuário pedir para criar, escrever ou revisar o roteiro/conteúdo do professor de uma aula (ex. "escreva a aula 03", "roteiro da aula de JWT").
---

# Roteiro do professor

Gera `aulas/aula-NN/roteiro.html` — o guia que o professor segue em sala durante ~2h.

## Antes de escrever

Leia, nesta ordem:

1. `docs/plano-de-aulas.md` — escopo, teoria **[T-n]** e prática da aula NN.
2. `docs/convencoes.md` — stack, formatos, regras do repositório.
3. `CONTEXT.md` — use exatamente os termos do glossário (User, Book, Reading Update...).
4. A branch da aula anterior em `projeto/` (se existir) — o roteiro parte do código onde a aula anterior terminou.

## Estrutura do roteiro

HTML simples e legível (sem reveal.js — isso é a skill `aula-slides`), em pt-BR, código em inglês. Seções:

1. **Cabeçalho** — número, título, duração, objetivos de aprendizagem (3–5, verbos observáveis). É o único lugar onde cabe informação operacional (nome da branch).
2. **Ponto de partida** — em até 5 min, **o código que já está na tela e o problema que ele tem**, no presente. Não é retomada da aula anterior: nada de "onde paramos", nada de citar de que aula veio.
3. **Blocos de aula** — alternando teoria e live-coding, com minutagem (ex. `[20 min]`):
   - Teoria: os pontos a explicar, analogia que **esclarece o conceito** (nunca decorativa), perguntas para lançar à turma.
   - Live-coding: **o código exato a digitar, passo a passo**, com o porquê de cada passo. Todo comando de terminal em duas variantes: **Mac e Windows**.
4. **Checkpoint** — como verificar que funcionou (o que abrir no navegador/Swagger, o que a turma deve ver).
5. **Exercício em sala** — pequeno, resolvível em 10–15 min com o que foi visto.
6. **Fechamento** — síntese do que foi ensinado hoje. **Sem gancho para a próxima aula.**

## Regras

- **Aula autocontida** (regra canônica em `docs/convencoes.md`): a aula depende do código da branch anterior, mas não fala sobre outras aulas. Não cite número de aula, não recapitule a anterior, não anuncie a próxima. Uma decisão que só se explicaria pelo que vem depois é justificada pelo **mérito técnico**: em vez de "o Pydantic fecha esse buraco na aula 03", escreva "um dicionário cru aceita qualquer coisa; validar exige declarar a forma esperada".
- **Sem enrolação.** Corte meta-comentário sobre a própria aula, frase de efeito e recado de bastidor pedagógico ("deixamos essa falha de propósito", "guarde o incômodo", "a dívida que abre a próxima aula"). Um problema deixado em aberto é apresentado como **problema técnico em aberto**, não como plano de curso.
- O código do roteiro é **idêntico** ao que vai para a branch `aula-NN-slug` — nunca invente código que não estará lá (a skill `aula-sync` confere).
- **Tom acadêmico**: é disciplina de graduação em Sistemas de Informação — linguagem formal, sem gírias nem tom de marketing. Cada tema teórico traz origem (quem criou, quando), propósito e definição formal com a fonte (RFC, tese, livro) — os slides derivam daqui e precisam desse material.
- Respeite as decisões dos ADRs em `docs/adr/` (ex. rotas nascem inseguras antes do JWT — ADR-0001).
- Legibilidade acima de performance; sem abstrações que a turma ainda não viu.
- Salve em `aulas/aula-NN/roteiro.html`; o título completo da aula vai no `<title>` e no `<h1>`.
