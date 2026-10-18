# Convenções da disciplina

Decisões de formato e processo tomadas durante o planejamento. O que for conceito de domínio fica no `CONTEXT.md`; aqui ficam as convenções de produção do material.

## Estrutura de pastas

```
progavancada/
├── aulas/
│   ├── assets/reveal/     ← reveal.js vendorado (offline)
│   └── aula-01/
│       ├── roteiro.html   ← guia do professor
│       ├── slides.html    ← deck do aluno (reveal.js)
│       └── img/           ← diagramas em PNG (fonte .svg ao lado)
└── projeto/          ← um único repositório git
    ├── backend/      ← FastAPI + MySQL
    └── frontend/     ← React (JS, sem TS)
```

## Aulas

Cada aula vive na pasta `aulas/aula-NN/` com **dois artefatos** (o título completo da aula fica no `<title>`/`<h1>` de cada arquivo):

- **Roteiro do professor**: `roteiro.html` — guia que o professor segue em sala (teoria, live-coding passo a passo, exercícios).
- **Slides do aluno**: `slides.html` — deck **reveal.js com tema claro**, explicações didáticas, **diagramas como imagens PNG locais** em `aula-NN/img/` (fonte `.svg` mantida ao lado; nunca SVG inline nem recurso externo — máquinas da universidade já falharam ao exibi-los), e **referências bibliográficas renomadas** por tema (último slide + rodapés). reveal.js vendorado em `aulas/assets/reveal/` para funcionar offline em sala.

Regras:

- Disciplina semestral: **~16 encontros de ~2h**.
- Sempre que exibir comandos de terminal (criar venv, instalar dependências etc.), mostrar **as duas variantes: Mac e Windows**.
- Slides nunca divergem do roteiro; o roteiro nunca diverge do código da branch.

### Aula autocontida

Cada aula é uma **unidade fechada**. Ela depende do que veio antes — o código da branch anterior é o ponto de partida — mas não conversa sobre isso com o aluno. A aula ensina; não narra a própria trajetória.

- **Não cita outras aulas.** Nada de "como vimos na aula 02", "o Pydantic fecha esse buraco na aula 03", "na aula 04 o banco entra". Número de aula não aparece no material.
- **Não recapitula a aula anterior.** Sem seção "onde paramos". Quando o ponto de partida precisa ser mostrado, mostre o **código atual e o problema que ele tem, no presente** — sem contar como se chegou até ali.
- **Não anuncia a próxima.** A aula termina no que ensinou.
- **Justifica pelo mérito técnico, não pelo calendário.** Se uma decisão só se explica pelo que vem depois, explique tecnicamente. Em vez de "esse contador será substituído pelo `AUTO_INCREMENT` na aula 04", escreva "um id calculado a partir do estado atual reaproveita números; um contador que só cresce, como o de um banco de dados, não".
- **Conceito necessário é apresentado aqui.** Se a aula depende de algo já ensinado, reapresente em uma frase — sem dizer onde apareceu antes.
- **Direta, sem enrolação.** Corte meta-comentário sobre a estrutura da aula, frase de efeito, analogia decorativa e recado de bastidor pedagógico ("deixamos essa falha de propósito", "guarde o incômodo"). Cada slide, parágrafo e passo ensina algo — ou sai.

Exceção única: o **cabeçalho operacional do roteiro** (branch, duração, objetivos) e a **bibliografia** — informação de trabalho do professor e fonte citada não são referência cruzada a outra aula.

### Skills do projeto (`.claude/skills/`)

- **aula-completa** — comando único: roteiro → código na branch → slides → sync (orquestra as três abaixo).
- **aula-roteiro** — gera o roteiro do professor.
- **aula-slides** — gera os slides reveal.js (bibliografia canônica em `references/bibliografia.md` da skill).
- **aula-sync** — confere roteiro ↔ slides ↔ branch ↔ README ao fechar cada aula.

## Stack e ferramentas

- **Backend**: Python + FastAPI, **SQLAlchemy** como ORM, MySQL.
- **Convenções de backend**: seguimos o guia [fastapi-best-practices](https://github.com/zhanymkanov/fastapi-best-practices) com adaptações didáticas — o que vale e o que não vale está no **ADR-0002**. Destaques: REST por recurso, tabelas `lower_case_snake` no plural, sufixo `_at`, `response_model`/`status_code` nas rotas, estrutura por tipo de arquivo quando `main.py` for dividido.
- **`async def` ou `def` nas rotas**: decidido caso a caso pelo critério do **ADR-0003** — `async def` quando não há I/O ou o I/O é assíncrono; `def` quando a rota chama biblioteca bloqueante (banco, PDF, disco). Nunca `async def` com chamada bloqueante dentro. O modelo de execução é ensinado na aula 01.3.
- **Schema do banco**: `Base.metadata.create_all()` na subida da app — sem Alembic. Quando o modelo mudar entre aulas, dropa-se o banco (dado de aula é descartável). Migrations são mencionadas só na teoria.
- **Autenticação**: JWT (**PyJWT**, HMAC-SHA256) com hash de senha **bcrypt**; o token viaja no header `Authorization: Bearer` e as rotas de dados operam sobre o usuário do token.
- **Frontend**: React com JavaScript (sem TypeScript), **Vite** como build tool, **Tailwind** para estilo.
- **Estrutura do frontend** (`frontend/src/`): `services/` falam com a API (só eles chamam `request`), `pages/` são telas inteiras que guardam estado e chamam os services, `components/` desenham o que recebem por props e avisam o pai por callbacks; `App.jsx` na raiz escolhe a página pelo estado e pelo endereço (`window.location.pathname`, sem biblioteca de rotas; a navegação entre endereços é um `<a>` comum). A aparência vive nos componentes estilizados (`Button`, `TextInput`, `ErrorMessage`, `Card`, `TextLink`): as páginas não repetem classes Tailwind de campo, botão ou link, e nenhuma biblioteca de componentes é instalada.
- **PDF**: **fpdf2** para o Reading Report.
- **Testes** (**ADR-0004**): no backend, pytest + `TestClient` (httpx2) em `backend/tests/`, com SQLite em memória por teste; no frontend, Vitest + Testing Library (jsdom) em arquivos `.test.jsx`/`.test.js` ao lado do código, e Playwright em `frontend/e2e/` para os testes de ponta a ponta. Nomes de teste em inglês, como frases que descrevem o comportamento.

## Repositório do projeto

- `backend/` e `frontend/` vivem no **mesmo repositório git** (`projeto/`).
- Cada aula gera uma **branch em formato slug** (ex.: `aula-01-inicio-do-projeto-e-frameworks`) — o repositório serve como histórico de evolução da disciplina. O nome completo da aula vive só no arquivo `.html`.
- Todo o código é escrito em **inglês**; a documentação do projeto (`README.md`) é escrita em **pt-BR**.
- O `README.md` mantém uma **Tabela de Dependências** (`Nome | Utilidade | Versão`) espelhando o `requirements.txt` — mesmas entradas e versões.
- Critério de qualidade: **legibilidade e clareza acima de performance** — é código para ensinar.
