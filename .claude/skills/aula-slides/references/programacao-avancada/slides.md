# Slides - Programação Avançada

Estrutura e formato do `aulas/aula-NN/slides.html`: a aula inteira, projetada em sala (~2h) e usada pelo aluno para estudar depois.
O código que os slides constroem é o código de `projeto/`.

## Formato

- Arquivo `.html` único, com o reveal.js do vendor da própria aula, `aula-NN/reveal/`, referenciado pelo caminho relativo `reveal/`. Aula nova copia o `reveal/` de uma aula existente. Tema claro `white`.
- Título em pt-BR; código em inglês com syntax highlight.
- **Capa com o repositório**: logo abaixo do título, a URL onde ficam os slides e o código da disciplina, como texto e link: `https://github.com/anchietajunior/sala/tree/main/disciplinas/programacao-avancada`.
- Número de aula só na capa.

## Estrutura

1. **Capa** - título da aula e o repositório.
2. **Objetivos** - 3-5 objetivos de aprendizagem, com verbos observáveis.
3. **Ponto de partida** - **o código que já está em `projeto/` e o problema que ele tem**, no presente.
4. **Blocos de aula** - alternando teoria e live-coding, na progressão motivação (problema concreto no código) → conceito → como fica no código.
   - Teoria: origem, propósito e definição formal com a fonte de cada tema; analogia só quando esclarece o conceito.
   - Live-coding: **o código exato a digitar, passo a passo**, um passo por slide, com o porquê de cada passo. Todo comando de terminal em duas variantes: **Mac e Windows**.
   - Recapitulação ao final de cada tema teórico, sobre o que acabou de ser ensinado nesta aula.
5. **Checkpoint** - como verificar que funcionou: o que abrir no navegador ou no Swagger e o que a turma deve ver.
6. **Exercício em sala** - pequeno, resolvível em 10-15 min com o que foi visto. Exercício descartável é desfeito ao final; o projeto segue com o código dos slides.
7. **Referências** - as obras de `aulas/bibliografia.md` relevantes à aula, em formato autor-título-ano.

## Didática

- **Uma ideia por slide**, com título afirmativo: a mensagem, não o assunto ("O servidor nunca confia no cliente", não "Segurança").
- **Todo tema teórico apresenta origem e definição**: quem criou, para que serve e a definição formal citada da fonte, sem intitular o slide de "definição formal".
- **Diagrama sempre que um desenho explicar melhor que texto**: cliente↔servidor, ciclo da requisição com DNS, anatomia de uma URI, fluxo do JWT, relações 1:N. Simples, com poucas cores e legendas em pt-BR, em `aulas/aula-NN/img/nome.svg`, referenciado por `<img src="img/nome.svg" style="width:100%;max-width:760px">`.
- Trechos de código curtos (até 15 linhas por slide), sempre idênticos ao código real de `projeto/`.
- Ao longo dos slides, marque no rodapé de onde cada conceito vem ("Fowler, PoEAA" no slide de ORM).
- Legibilidade acima de performance, sem abstração que a turma ainda não viu.
