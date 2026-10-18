# Roteiro do professor - Programação Avançada

Estrutura e regras do `aulas/aula-NN/roteiro.html`, o guia que o professor segue em sala durante ~2h.
O roteiro é o material principal da aula: os slides derivam dele e o código de `projeto/` é idêntico ao do live-coding.

## Formato

HTML simples e legível, sem reveal.js (isso é da skill `aula-slides`), em pt-BR, com código em inglês.
O título completo da aula vai no `<title>` e no `<h1>`.

## Seções

1. **Cabeçalho** - número, título, duração e objetivos de aprendizagem (3-5, verbos observáveis). É o único lugar onde cabe informação operacional do professor.
2. **Ponto de partida** - em até 5 min, **o código que já está na tela e o problema que ele tem**, no presente.
3. **Blocos de aula** - alternando teoria e live-coding, com minutagem (ex.: `[20 min]`):
   - Teoria: os pontos a explicar, com origem, propósito e definição formal com a fonte de cada tema (os slides precisam desse material), analogia que **esclarece o conceito** e perguntas para lançar à turma.
   - Live-coding: **o código exato a digitar, passo a passo**, com o porquê de cada passo. Todo comando de terminal em duas variantes: **Mac e Windows**.
4. **Checkpoint** - como verificar que funcionou: o que abrir no navegador ou no Swagger e o que a turma deve ver.
5. **Exercício em sala** - pequeno, resolvível em 10-15 min com o que foi visto.
6. **Fechamento** - síntese do que foi ensinado hoje; a aula termina no que ensinou.

## Regras

- O código do roteiro é **idêntico** ao que fica em `projeto/`: todo código mostrado existe lá, e todo código de lá foi mostrado (a `aula-revisao` confere).
- Exercício descartável é desfeito ao final; o projeto segue com o código do roteiro.
- Legibilidade acima de performance, sem abstração que a turma ainda não viu.
