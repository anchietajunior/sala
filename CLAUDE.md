# Sala - material de aula do professor José Anchieta (UniRios)

Este repositório guarda tudo o que é usado em sala: aulas, slides, código e projetos de cada disciplina.
O repositório é público: provas, gabaritos e dados de alunos ficam em `disciplinas/<disciplina>/atividades/`, que o git ignora.

## Mapa

- `disciplinas/<disciplina>/` - uma pasta por disciplina, com o perfil da disciplina em `CLAUDE.md` e as aulas em `aulas/`.
  - `algoritmos-e-estruturas-de-dados/` - slides e código C de cada aula, em `aulas/aulaNN_tema/`.
  - `programacao-avancada/` - slides em `aulas/aula-NN/` e o projeto da disciplina em `projeto/` (rastreador de leituras, FastAPI + React).
- `projetos/` - projetos que atravessam disciplinas.
  - `faculdade/` - jogo 3D em C/WebAssembly que publica os slides das duas disciplinas (`make deploy`).
- `.claude/skills/` - as skills de aula, as mesmas para todas as disciplinas.

## Como uma aula é produzida

**O slide é a única fonte da verdade de cada aula.** A aula é a apresentação Reveal.js; o código da aula (o `.c` em AED, `projeto/` em Programação Avançada) é exatamente o que os slides mostram e constroem.

Todas as disciplinas usam as mesmas três skills.
O perfil da disciplina (`disciplinas/<disciplina>/CLAUDE.md`) diz onde ficam os artefatos, quais referências cada skill lê e o que a revisão confere.

- `aula-slides` - escreve ou altera a aula: slides, diagramas e código.
- `aula-revisao` - revisão severa dos slides e conferência de consistência entre slides, código, README e índices.
- `aula-completa` - o fluxo inteiro: aula, revisão, commit e push.

Tudo vive na `main`.
O trabalho de cada aula entra em commit com a mensagem `<sigla> aula NN: <o que a aula construiu, em inglês>`; a sigla está no perfil.

## Regras de toda aula

Valem para qualquer disciplina e qualquer pedido, inclusive parcial ("só o código", "só os slides").
O perfil da disciplina acrescenta regras e exceções; em conflito, o perfil vence.

- **Idioma.** Material didático em PT-BR com acentuação correta ("não", nunca "nao"). Termos técnicos consagrados e identificadores de código mantêm a forma original.
- **Cada aula é uma unidade fechada.** Nenhum material (slides, código, comentários) menciona outra aula.
  Nem anterior ("como vimos na aula 02", "onde paramos", "a estrutura da aula passada"), nem posterior ("na próxima aula", "tema de aula futura"), nem a posição na sequência ("agora que já temos vetor e custo").
  Número de aula não aparece no material, salvo na capa e no título da apresentação.
  Todo conceito de que a aula depende é apresentado nela mesma, com definição e exemplo próprios; o que não couber assim fica de fora.
  Quando o ponto de partida precisa ser mostrado, mostre o estado atual e o problema que ele tem, no presente.
  Uma decisão que só se explicaria pelo que vem depois é justificada pelo mérito técnico: em vez de "esse contador será substituído na aula 04", escreva "um id calculado a partir do estado atual reaproveita números; um contador que só cresce, como o de um banco de dados, não".
  Nomear um tema da computação ("ordenação", "árvores de busca") é permitido; anunciar aula, não.
- **Registro acadêmico, sem jargão.** A aula é de graduação e apresentada em sala.
  Nada de coloquialismo ("tripa", "espiar", "cuspir"), gíria técnica ("rodar", "printar", "setar"), expressão de palco ("mágica", "de graça", "joga fora"), humor, tom de marketing, bordão de mercado ("React: a interface é uma função do estado") nem sigla local.
  No lugar, uma frase formal que fundamente o conteúdo: a definição, a propriedade ou o resultado, com a fonte quando couber.
  Termo técnico consagrado (ponteiro, struct, `malloc`, big-O, endpoint) não é jargão.
- **Direta, sem enrolação.** Corte meta-comentário sobre a estrutura da aula, frase de efeito, analogia decorativa e recado de bastidor pedagógico ("deixamos essa falha de propósito", "guarde o incômodo"). Cada slide, parágrafo e passo ensina algo, ou sai.
- **Não supor conhecimento prévio.** Cada termo técnico é definido no primeiro uso. Termo em inglês entra com a tradução em português e o original em itálico no primeiro uso: "remover (*delete*)".
- **A intuição nunca anda sozinha.** Analogia entra só quando esclarece o conceito, sempre acompanhada do termo formal, nunca no lugar dele.
- **Fonte sempre.** A bibliografia é citada ao longo da aula (no texto e no rodapé do slide), não só na lista final de referências.
  Nunca inventar capítulo, página, data ou autor: na dúvida, citar genericamente ("ver capítulo de pilhas em Backes") ou omitir.
- **O código acompanha os slides.** Todo trecho de código exibido existe no código real da aula, e todo código da aula aparece nos slides.
- **Slides.** Reveal.js vendorado dentro da disciplina, sem CDN nem recurso externo, para funcionar offline em sala; tema claro `white`.
  Uma ideia por slide, frases curtas.
- **Diagramas em SVG.** Sempre que um desenho explicar melhor que texto, um arquivo `.svg` na pasta `img/` da aula, referenciado por `<img>` com `alt` descritivo e dimensionado como o perfil define. Captura de tela fica em PNG.
- **Código didático.** Legibilidade e clareza acima de performance, sem abstração que a turma ainda não viu.
