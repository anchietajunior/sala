# Slides do aluno - Programação Avançada

Formato e didática do `aulas/aula-NN/slides.html`, o deck que o aluno assiste em sala e usa para estudar depois.
Os slides apresentam o conteúdo do roteiro da mesma aula (`aulas/aula-NN/roteiro.html`), na mesma ordem.

## Formato

- Arquivo `.html` único, com o reveal.js do vendor `aulas/assets/reveal/`, referenciado pelo caminho relativo `../assets/reveal/`. Tema claro `white`.
- Título em pt-BR; código em inglês com syntax highlight.
- **Capa com o repositório**: logo abaixo do título, a URL onde ficam os slides e o código da disciplina, como texto e link: `https://github.com/anchietajunior/sala/tree/main/disciplinas/programacao-avancada`.
- Número de aula só na capa.

## Didática

- **Uma ideia por slide**, com título afirmativo: a mensagem, não o assunto ("O servidor nunca confia no cliente", não "Segurança").
- **Todo tema teórico apresenta origem e definição**: quem criou, para que serve e a definição formal citada da fonte, sem intitular o slide de "definição formal".
- **Diagrama sempre que um desenho explicar melhor que texto**: cliente↔servidor, ciclo da requisição com DNS, anatomia de uma URI, fluxo do JWT, relações 1:N. Simples, com poucas cores e legendas em pt-BR.
  Desenhe em SVG, salve a fonte em `aulas/aula-NN/img/nome.svg`, exporte PNG em 2x (`rsvg-convert -z 2 -o img/nome.png img/nome.svg`) e referencie `<img src="img/nome.png">`.
- O primeiro slide de conteúdo mostra **o código atual e o problema que ele tem**, no presente.
- Progressão: motivação (problema concreto no código) → conceito → como fica no código → recapitulação.
- Trechos de código curtos (até 15 linhas por slide), extraídos do código real da aula.
- Slide de recapitulação ao final de cada tema teórico, sobre o que acabou de ser ensinado nesta aula.
- **Último slide: Referências** - as obras de `aulas/bibliografia.md` relevantes à aula, em formato autor-título-ano; ao longo dos slides, marque no rodapé de onde cada conceito vem ("Fowler, PoEAA" no slide de ORM).
