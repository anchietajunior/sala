# Sala

Material de estudos e projetos construídos em sala de aula pelo professor José Anchieta na UniRios.

## Disciplinas

| Disciplina | Aulas | Projeto |
|------------|-------|---------|
| [Algoritmos e Estruturas de Dados](disciplinas/algoritmos-e-estruturas-de-dados/) | [`aulas/`](disciplinas/algoritmos-e-estruturas-de-dados/aulas/): conteúdo em Markdown, código em C e apresentação de cada aula | - |
| [Programação Avançada](disciplinas/programacao-avancada/) | [`aulas/`](disciplinas/programacao-avancada/aulas/): roteiro e slides de cada aula | [`projeto/`](disciplinas/programacao-avancada/projeto/): rastreador de leituras com FastAPI e React |

Cada disciplina tem um `disciplina.html` com a visão geral das aulas.
Os slides abrem direto no navegador e funcionam offline: o Reveal.js está vendorado em `aulas/assets/` de cada disciplina.

## Projetos

- [`projetos/faculdade/`](projetos/faculdade/) - uma faculdade 3D, escrita em C e compilada para WebAssembly, em que cada sala é uma disciplina e cada livro do armário abre a apresentação de uma aula. `make servir` monta o site e o serve em `http://localhost:8000`; `make deploy` publica.

## Como as aulas são produzidas

As aulas são escritas com o Claude Code, por quatro skills que valem para todas as disciplinas (`.claude/skills/`):

| Skill | O que faz |
|-------|-----------|
| `aula-completa` | o fluxo inteiro: conteúdo, slides, revisão e commit |
| `aula-conteudo` | o material principal da aula (texto ou roteiro, e o código) |
| `aula-slides` | a apresentação Reveal.js derivada do material principal |
| `aula-revisao` | revisão severa do conteúdo e dos slides e conferência de consistência |

As regras comuns a toda aula estão no [`CLAUDE.md`](CLAUDE.md) da raiz.
O que muda de uma disciplina para outra está no perfil de cada uma, `disciplinas/<disciplina>/CLAUDE.md`.
