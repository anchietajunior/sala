---
name: aula-slides
description: Gera os slides do aluno em reveal.js (tema claro) para uma aula da disciplina Programação Avançada, com explicações didáticas, diagramas em SVG e referências bibliográficas renomadas. Use quando o usuário pedir para criar ou revisar slides/apresentação de uma aula (ex. "slides da aula 02", "apresentação de REST").
---

# Slides do aluno (reveal.js)

Gera `projeto/slides/aula-NN/slides.html` — o deck que o aluno assiste em sala e usa para estudar depois.

## Antes de escrever

1. Leia o roteiro da mesma aula (`aulas/aula-NN/roteiro.html`) — os slides apresentam **o mesmo conteúdo**, na mesma ordem; nunca divergem do roteiro.
2. Leia `CONTEXT.md` — termos do glossário, sempre.
3. Consulte [references/bibliografia.md](references/bibliografia.md) — as referências canônicas por tema **[T-n]**.

## Formato

- Arquivo .html único: reveal.js do vendor local `projeto/slides/assets/reveal/`, referenciado com caminho relativo `../assets/reveal/` (na primeira geração, baixe a release do reveal.js para lá — os slides precisam funcionar **offline** em sala). Tema claro (`white`).
- Título em pt-BR; código em inglês com syntax highlight.
- **Capa com o repositório:** logo abaixo do título, a URL do repositório onde ficam os slides e o código da disciplina - `https://github.com/anchietajunior/programacao-avancada-6` -, como texto e link.

## Didática dos slides

- **Tom acadêmico e formal** — é disciplina de graduação em Sistemas de Informação, não curso comercial: títulos sóbrios, sem gírias, humor ou tom de marketing ("Correção: um contador monotônico", não "O conserto: um contador que só cresce").
- **Todo tema teórico apresenta origem e definição**: quem criou (autor, ano, contexto), para que serve, e a definição formal citada da fonte — sem intitular o slide de "definição formal". Ferramentas também (ex.: Pydantic — Samuel Colvin, 2017).
- **Uma ideia por slide.** Título afirmativo (a mensagem, não o assunto: "O servidor nunca confia no cliente", não "Segurança").
- **Diagrama sempre que um desenho explicar melhor que texto**: cliente↔servidor, ciclo da requisição com DNS, anatomia de uma URI, fluxo do JWT, relações 1:N. Simples, com poucas cores, legendas em pt-BR. Desenhe em SVG, salve a fonte em `projeto/slides/aula-NN/img/nome.svg`, exporte PNG em 2x (`rsvg-convert -z 2 -o img/nome.png img/nome.svg`) e referencie `<img src="img/nome.png">` — **nunca SVG inline nem recurso externo** (máquinas da universidade já falharam ao exibi-los).
- **Aula autocontida** (regra canônica em `docs/convencoes.md`): o deck não cita outras aulas — nem para trás, nem para frente. **Número de aula não aparece em slide algum**, salvo na capa. Sem slide "Revisão da aula anterior" e sem slide "Próxima aula". O primeiro slide de conteúdo mostra **o código atual e o problema que ele tem**, no presente. Uma consequência futura é apresentada pelo mérito técnico ("um contador que só cresce, como o de um banco de dados, não reaproveita ids"), nunca pela agenda ("na aula 04 o banco resolve").
- **Sem enrolação.** Cada slide ensina uma coisa. Corte meta-comentário sobre a estrutura da aula, frase de efeito, analogia decorativa e bastidor pedagógico. Analogia entra só quando **esclarece o conceito** melhor que a definição.
- Progressão: motivação (problema concreto no código) → conceito → como fica no código → recapitulação.
- Trechos de código curtos (≤ 15 linhas por slide), extraídos do código real da aula.
- Slide de recapitulação ao final de cada tema teórico — recapitula **o que acabou de ser ensinado nesta aula**, nunca conteúdo de outra.
- **Último(s) slide(s): Referências** — cite as obras de [references/bibliografia.md](references/bibliografia.md) relevantes à aula, em formato autor–título–ano; durante os slides, marque de onde cada conceito vem ("Fowler, PoEAA" no rodapé do slide de ORM).

## Regras

- Slides não introduzem conteúdo que não está no roteiro; se sentir falta de algo, ajuste o roteiro primeiro (skill `aula-roteiro`).
- Salve em `projeto/slides/aula-NN/slides.html`.
