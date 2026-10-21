# Sala

Material de estudos e projetos construídos em sala de aula pelo professor José Anchieta na UniRios.

## Disciplinas

| Disciplina | Aulas | Projeto |
|------------|-------|---------|
| [Algoritmos e Estruturas de Dados](disciplinas/algoritmos-e-estruturas-de-dados/) | [`aulas/`](disciplinas/algoritmos-e-estruturas-de-dados/aulas/): os slides e o código em C de cada aula | - |
| [Programação Avançada](disciplinas/programacao-avancada/) | [`aulas/`](disciplinas/programacao-avancada/aulas/): os slides de cada aula | [`projeto/`](disciplinas/programacao-avancada/projeto/): rastreador de leituras com FastAPI e React |

Cada aula é a sua apresentação: os slides são a única fonte da verdade, e o código de cada aula é o que eles mostram.
Cada disciplina tem um `disciplina.html` com a visão geral das aulas.
Os slides abrem direto no navegador e funcionam offline: o Reveal.js está vendorado em `aulas/assets/` em Algoritmos e Estruturas de Dados e dentro de cada aula (`aula-NN/reveal/`) em Programação Avançada, onde baixar só a pasta da aula basta.

## Projetos

- [`projetos/faculdade/`](projetos/faculdade/) - uma faculdade 3D, escrita em C e compilada para WebAssembly, em que cada sala é uma disciplina e cada livro do armário abre a apresentação de uma aula. `make servir` monta o site e o serve em `http://localhost:8000`; `make deploy` publica.

## Como as aulas são produzidas

As aulas são escritas com o Claude Code, por três skills que valem para todas as disciplinas (`.claude/skills/`):

| Skill | O que faz |
|-------|-----------|
| `aula-slides` | escreve ou altera a aula: slides, diagramas e código |
| `aula-revisao` | revisão severa dos slides e conferência de consistência com o código e os índices |
| `aula-completa` | o fluxo inteiro: aula, revisão, commit e push |

As regras comuns a toda aula estão no [`CLAUDE.md`](CLAUDE.md) da raiz.
O que muda de uma disciplina para outra está no perfil de cada uma, `disciplinas/<disciplina>/CLAUDE.md`.
