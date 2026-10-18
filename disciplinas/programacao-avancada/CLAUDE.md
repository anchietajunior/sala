# Programação Avançada (UniRios) - perfil da disciplina

Perfil lido pelas skills de aula (`.claude/skills/` na raiz do repositório).
As regras de toda aula estão no `CLAUDE.md` da raiz; aqui ficam as desta disciplina, que vencem em caso de conflito.
Sigla nos commits: `pa`.

Disciplina semestral da graduação em Sistemas de Informação: **~16 encontros de ~2h**.
Ao longo do semestre a turma constrói um único projeto, o rastreador de leituras em `projeto/` (FastAPI + React).
O glossário do domínio fica em `projeto/CONTEXT.md`; aqui ficam as convenções de produção do material.

## Estrutura de pastas

```
programacao-avancada/
├── CLAUDE.md              ← este perfil
├── disciplina.html        ← visão geral das aulas
├── aulas/
│   ├── plano-de-aulas.md  ← escopo de cada aula e temas teóricos [T-n]
│   ├── bibliografia.md    ← referências canônicas por tema [T-n]
│   ├── assets/reveal/     ← reveal.js vendorado (offline)
│   └── aula-NN/
│       ├── roteiro.html   ← guia do professor
│       ├── slides.html    ← deck do aluno (reveal.js)
│       └── img/           ← diagramas em PNG (fonte .svg ao lado)
└── projeto/
    ├── CONTEXT.md         ← glossário do domínio
    ├── README.md          ← como rodar, endpoints e dependências
    ├── docs/adr/          ← decisões que valem para todas as aulas
    ├── backend/           ← FastAPI + MySQL
    └── frontend/          ← React (JS, sem TS)
```

## Artefatos de uma aula

| Artefato | Caminho | Papel |
|----------|---------|-------|
| Roteiro do professor | `aulas/aula-NN/roteiro.html` | **material principal**: teoria, live-coding passo a passo e exercício |
| Código | `projeto/` | exatamente o que o live-coding do roteiro constrói |
| Slides do aluno | `aulas/aula-NN/slides.html` | deck reveal.js derivado do roteiro |
| README do projeto | `projeto/README.md` | estado do projeto até esta aula |

- Ordem: roteiro → código → slides → revisão. Slides nunca divergem do roteiro; o roteiro nunca diverge do código.
- O título completo da aula fica no `<title>` e no `<h1>` de cada arquivo.
- O código evolui na `main`: o projeto parte do estado deixado pela aula anterior, sem branch por aula.

## Regras da disciplina

- **Tom acadêmico.** Títulos sóbrios: "Correção: um contador monotônico", não "O conserto: um contador que só cresce".
- **Todo tema teórico apresenta origem e definição**: quem criou (autor, ano, contexto), para que serve e a definição formal citada da fonte (RFC, tese, livro). Ferramentas também (ex.: Pydantic - Samuel Colvin, 2017).
- **Comandos de terminal** (criar venv, instalar dependências etc.) sempre em duas variantes: **Mac e Windows**.
- **Termos do domínio** exatamente como no `projeto/CONTEXT.md` (User, Book, Reading Update...).
- **ADRs** em `projeto/docs/adr/` valem em todas as aulas (ex.: ADR-0001, rotas nascem sem autenticação até a aula de JWT).
- **Exceção à aula fechada**: o cabeçalho operacional do roteiro (duração, objetivos) e a bibliografia; informação de trabalho do professor e fonte citada não são referência cruzada a outra aula.
- **Um problema deixado em aberto** é apresentado como problema técnico em aberto, nunca como plano de curso.

## Conteúdo (skill `aula-conteudo`)

Leia antes de escrever:

1. `aulas/plano-de-aulas.md` - escopo, teoria **[T-n]** e prática da aula NN. Se a aula não está no plano, pare e avise.
2. `projeto/CONTEXT.md` e os ADRs em `projeto/docs/adr/`.
3. O código atual de `projeto/` - o roteiro parte dele.
4. `.claude/skills/aula-conteudo/references/programacao-avancada/roteiro.md` - estrutura e regras do roteiro.

O código da aula é implementado em `projeto/` seguindo o live-coding do roteiro, nem código a mais, nem passo sem código:

- Todo bloco ou instrução do código leva um comentário **imediatamente acima**, em pt-BR, explicando o que as instruções fazem; identificadores e strings ficam em inglês.
- Valide com uma chamada rápida (`python -c "import main"` ou `TestClient`) e com os testes existentes (`pytest` em `backend/`, `npm test` em `frontend/`); derrube o que subir.
- Atualize o `projeto/README.md` para o estado desta aula.

## Slides (skill `aula-slides`)

- Formato e didática: `.claude/skills/aula-slides/references/programacao-avancada/slides.md`.
- Bibliografia canônica por tema: `aulas/bibliografia.md`.
- **Diagramas como imagens PNG locais** em `aulas/aula-NN/img/`, exportados do `.svg` mantido ao lado: nunca SVG inline nem recurso externo, porque máquinas da universidade já falharam ao exibi-los.

## Stack e ferramentas

- **Backend**: Python + FastAPI, **SQLAlchemy** como ORM, MySQL.
- **Convenções de backend**: seguimos o guia [fastapi-best-practices](https://github.com/zhanymkanov/fastapi-best-practices) com adaptações didáticas; o que vale e o que não vale está no **ADR-0002**. Destaques: REST por recurso, tabelas `lower_case_snake` no plural, sufixo `_at`, `response_model`/`status_code` nas rotas, estrutura por tipo de arquivo quando `main.py` for dividido.
- **`async def` ou `def` nas rotas**: decidido caso a caso pelo critério do **ADR-0003** - `async def` quando não há I/O ou o I/O é assíncrono; `def` quando a rota chama biblioteca bloqueante (banco, PDF, disco). Nunca `async def` com chamada bloqueante dentro. O modelo de execução é ensinado na aula 01.3.
- **Schema do banco**: `Base.metadata.create_all()` na subida da app, sem Alembic. Quando o modelo mudar entre aulas, dropa-se o banco (dado de aula é descartável). Migrations são mencionadas só na teoria.
- **Autenticação**: JWT (**PyJWT**, HMAC-SHA256) com hash de senha **bcrypt**; o token viaja no header `Authorization: Bearer` e as rotas de dados operam sobre o usuário do token.
- **Frontend**: React com JavaScript (sem TypeScript), **Vite** como build tool, **Tailwind** para estilo.
- **Estrutura do frontend** (`frontend/src/`): `services/` falam com a API (só eles chamam `request`), `pages/` são telas inteiras que guardam estado e chamam os services, `components/` desenham o que recebem por props e avisam o pai por callbacks; `App.jsx` na raiz escolhe a página pelo estado e pelo endereço (`window.location.pathname`, sem biblioteca de rotas; a navegação entre endereços é um `<a>` comum). A aparência vive nos componentes estilizados (`Button`, `TextInput`, `ErrorMessage`, `Card`, `TextLink`): as páginas não repetem classes Tailwind de campo, botão ou link, e nenhuma biblioteca de componentes é instalada.
- **PDF**: **fpdf2** para o Reading Report.
- **Testes** (**ADR-0004**): no backend, pytest + `TestClient` (httpx2) em `backend/tests/`, com SQLite em memória por teste; no frontend, Vitest + Testing Library (jsdom) em arquivos `.test.jsx`/`.test.js` ao lado do código, e Playwright em `frontend/e2e/` para os testes de ponta a ponta. Nomes de teste em inglês, como frases que descrevem o comportamento.

## Projeto

- Todo o código é escrito em **inglês**; a documentação do projeto (`README.md`) é escrita em **pt-BR**.
- O `README.md` mantém uma **Tabela de Dependências** (`Nome | Utilidade | Versão`) espelhando o `requirements.txt`: mesmas entradas, mesmas versões, mesma ordem.
- O `README.md` nunca menciona aulas futuras.
- Critério de qualidade: **legibilidade e clareza acima de performance** - é código para ensinar.

## Consistência (conferida pela `aula-revisao`)

- [ ] O código da aula contém exatamente o que o live-coding do roteiro constrói: confira o `git diff` de `projeto/` (trabalho ainda não commitado, ou os commits `pa aula NN:`).
- [ ] Os trechos de código dos slides existem no código real.
- [ ] Diagramas dos slides são `<img>` PNG locais em `aulas/aula-NN/img/`, com a fonte `.svg` ao lado.
- [ ] Blocos e instruções do código têm comentário explicativo imediatamente acima, em pt-BR; código em inglês; termos do domínio conforme `projeto/CONTEXT.md`.
- [ ] Decisões dos ADRs respeitadas.
- [ ] O backend importa e os testes existentes passam.
- [ ] `projeto/README.md` reflete o estado **até esta aula**, em pt-BR: como rodar backend e frontend (Mac e Windows), tabela de endpoints, variáveis de ambiente, estrutura de pastas.
- [ ] A Tabela de Dependências bate com o `requirements.txt`: dependência entrou, saiu ou mudou de versão, a tabela acompanha.
- [ ] `aulas/plano-de-aulas.md` ainda descreve o que a aula realmente ficou; se o conteúdo derrapou, atualize o plano ou aponte a divergência ao professor se for mudança de escopo.
