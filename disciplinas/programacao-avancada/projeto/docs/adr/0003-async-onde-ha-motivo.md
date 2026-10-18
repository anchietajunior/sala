# Rotas `async` onde há motivo, síncronas no resto (revisa o ADR-0002)

O ADR-0002 rejeitou rotas `async` com a justificativa de que `async/await` seria "carga cognitiva que não é tema da disciplina". A premissa deixou de valer: a **aula 01.3** passa a ensinar concorrência, paralelismo, I/O-bound × CPU-bound e o modelo de execução do FastAPI. A partir dela, o modelo é conteúdo dado — e manter todo o projeto síncrono passaria a ser uma omissão, não uma simplificação.

Também havia uma dívida didática: `async` já fora citado em sala como uma das vantagens do FastAPI, sem nunca ter sido explicado. A aula 01.3 fecha essa dívida e o projeto passa a exercitar o que ela ensina.

## A regra

A decisão **não** é "usar `async` em tudo". É escolher com critério, e o critério é um só — *nada que bloqueie pode rodar no event loop*:

- **`async def`** quando a função só faz `await` de I/O assíncrono, ou não faz I/O nenhum (devolve dado em memória ou já calculado). Roda no próprio event loop, sem o custo de saltar para uma thread.
- **`def`** quando a função chama qualquer biblioteca bloqueante — sessão do SQLAlchemy, geração de PDF com fpdf2, escrita em disco. O FastAPI a executa na threadpool do AnyIO (40 threads por padrão) e o event loop segue livre.
- **Nunca `async def` chamando biblioteca bloqueante.** É o pior dos dois mundos: perde-se a threadpool e congela-se o event loop para todos os outros clientes. É o erro mais comum em projetos FastAPI e vira demonstração em sala.

## Consequências por aula

| Aula | Rota | Declaração | Motivo |
| --- | --- | --- | --- |
| 01 | `GET /health` | `async def` | não faz I/O; responde na hora |
| 02–03 | books em memória (lista Python) | `async def` | lista em memória, sem I/O |
| 04+ | rotas com `Session` do SQLAlchemy | `def` | driver do banco é bloqueante |
| 13 | upload de capa | `async def` | `await file.read()` é I/O assíncrono |
| 14 | geração do Reading Report | `def` | fpdf2 é **CPU-bound** — o contraexemplo da regra |

A tabela é material de aula: a coluna "motivo" é a pergunta que o aluno deve saber responder sozinho a partir da aula 01.3.

## Alternativas rejeitadas

- **Manter tudo síncrono** (decisão anterior, ADR-0002). Era coerente enquanto o modelo de execução não era ensinado; depois da aula 01.3, vira código que contradiz a própria aula.
- **Tornar tudo `async def`**, como faz a maioria dos tutoriais de FastAPI. Seria ativamente incorreto: com sessão síncrona do SQLAlchemy, cada consulta ao banco passaria a bloquear o event loop — pior desempenho que o código síncrono que substituiria, e pela razão exata que a aula 01.3 ensina a evitar.
