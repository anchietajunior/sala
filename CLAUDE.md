# Sala - material de aula do professor José Anchieta (UniRios)

Este repositório guarda tudo o que é usado em sala: aulas, slides, código e projetos de cada disciplina.
O repositório é público: provas, gabaritos e dados de alunos ficam em `disciplinas/<disciplina>/atividades/`, que o git ignora.

## Mapa

- `disciplinas/<disciplina>/` - uma pasta por disciplina, com o perfil da disciplina em `CLAUDE.md` e as aulas em `aulas/`.
  - `algoritmos-e-estruturas-de-dados/` - aulas em C, em `aulas/aulaNN_tema/`.
  - `programacao-avancada/` - roteiros e slides em `aulas/aula-NN/` e o projeto da disciplina em `projeto/` (rastreador de leituras, FastAPI + React).
- `projetos/` - projetos que atravessam disciplinas.
  - `faculdade/` - jogo 3D em C/WebAssembly que publica os slides das duas disciplinas (`make deploy`).
- `.claude/skills/` - as skills de aula, as mesmas para todas as disciplinas.

## Como uma aula é produzida

Todas as disciplinas usam as mesmas quatro skills.
O perfil da disciplina (`disciplinas/<disciplina>/CLAUDE.md`) diz quais artefatos a aula tem, onde ficam, quais referências cada skill lê e o que a revisão confere.

- `aula-completa` - o fluxo inteiro: conteúdo, slides, revisão e commit.
- `aula-conteudo` - o material principal da aula (texto ou roteiro, e o código).
- `aula-slides` - a apresentação Reveal.js derivada do material principal.
- `aula-revisao` - revisão severa do conteúdo e dos slides e conferência de consistência entre os artefatos.

Tudo vive na `main`, sem branch por aula.
O trabalho de cada aula entra em commit com a mensagem `<sigla> aula NN: <o que a aula construiu, em inglês>`; a sigla está no perfil.

## Regras de toda aula

Valem para qualquer disciplina e qualquer pedido, inclusive parcial ("só o código", "só os slides").
O perfil da disciplina acrescenta regras e exceções; em conflito, o perfil vence.

- **Idioma.** Material didático em PT-BR com acentuação correta ("não", nunca "nao"). Termos técnicos consagrados e identificadores de código mantêm a forma original.
- **Cada aula é uma unidade fechada.** Nenhum material (texto, roteiro, slides, código, comentários) menciona outra aula.
  Nem anterior ("como vimos na aula 02", "onde paramos", "a estrutura da aula passada"), nem posterior ("na próxima aula", "tema de aula futura"), nem a posição na sequência ("agora que já temos vetor e custo").
  Número de aula não aparece no material, salvo na capa e no título da apresentação e na informação operacional do professor que o perfil admitir.
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
- **Os slides derivam do material principal.** Apresentam o mesmo conteúdo, na mesma ordem, e não introduzem o que não está nele; se faltar algo, ajuste o material principal primeiro.
  Todo trecho de código exibido existe no código real da aula.
- **Slides.** Reveal.js vendorado dentro da disciplina, sem CDN nem recurso externo, para funcionar offline em sala; tema claro `white`.
  Uma ideia por slide, frases curtas.
  Diagrama sempre que um desenho explicar melhor que texto, no formato que o perfil define.
- **Código didático.** Legibilidade e clareza acima de performance, sem abstração que a turma ainda não viu.
