# Plano de aulas — Programação Avançada (proposta)

16 encontros de ~2h. Cada aula tem uma pasta `aulas/aula-NN/` (slides) e o código que ela constrói entra em `projeto/`, na `main`. Os 10 temas teóricos da ementa estão marcados como **[T-n]**.

## Bloco 1 — Fundamentos e primeiras rotas (backend)

**Aula 01 — Início do projeto e frameworks**
Teoria: o que são frameworks **[T-1]**, modelo cliente-servidor **[T-2]**, gerenciamento de dependências **[T-6]**.
Prática: venv (Mac e Windows), `pip install fastapi uvicorn`, `requirements.txt`, primeira rota respondendo JSON, testada no navegador.

**Aula 01.2 — Programação Orientada a Objetos com Python** _(aula extra, não toca o projeto)_
Aula complementar de fundamentos: não evolui o projeto, prepara a turma para lê-lo das aulas 03 em diante.
Teoria: origem da POO (Simula 67, Smalltalk), objeto como estado + comportamento + identidade, encapsulamento e ocultamento de informação (Parnas), herança e substituição (Liskov), polimorfismo e _duck typing_, composição vs. herança (GoF).
Prática: laboratório em `oop_lab.py` fora do repositório — classes, `__init__`, `self`, `__repr__`, `@property` para dado derivado (o Reading Progress), herança com `super()`, composição `User`→`Books`; leitura das classes declarativas do projeto (anotações de tipo, `Mapped`/`mapped_column`, decorators).

**Aula 01.3 — Concorrência, paralelismo e o modelo de execução do FastAPI** _(aula extra, não toca o projeto)_
Aula complementar teórica, sem laboratório: não evolui o projeto, explica por que ele é escrito como é.
Teoria: o problema C10K (Kegel, 1999); concorrência ≠ paralelismo (Dijkstra, 1965; Pike, 2012); corrotinas (Conway, 1963); tarefas I/O-bound e CPU-bound, com a escala de latências de Jeff Dean; as três arquiteturas de servidor (processo por requisição, thread por requisição, event loop) e o `select`/`epoll`/`kqueue` por baixo; o GIL do CPython e a PEP 703; `asyncio` (PEP 3156) e a sintaxe `async`/`await` (PEP 492); o modelo do FastAPI — `async def` no event loop, `def` na threadpool do AnyIO (40 threads); a Lei de Little (1961) para estimar quantas requisições o servidor sustenta.
Demonstrações projetadas pelo professor em `async_lab.py`, fora do repositório. Fecha decidindo o critério do **ADR-0003**, que passa a valer no projeto a partir daqui.

**Aula 02 — Ciclo de vida de uma requisição**
Teoria: DNS, HTTP, o caminho navegador→servidor→resposta **[T-4]**, servidores web e o papel do uvicorn **[T-5]**, path vs query params.
Prática: inspecionar headers e status codes, path/query params, explorar o Swagger (`/docs`); primeiras rotas do recurso books **em memória** (lista Python) sob `/api/books` — listar, buscar por nome (`?name=`), obter por id (404) e criar via POST (dict cru, sem validação).

**Aula 03 — APIs REST e URIs**
Teoria: o conceito de API (Parnas, ocultação de informação), REST, verbos, estrutura de uma URI **[T-3]**.
Prática: modelar Book como classe Python e trocar a lista de dicionários por lista de objetos; completar o CRUD em memória com DELETE e PUT; geração de id a partir do último da lista (1 se vazia); desenhar os recursos do projeto (users, books); trocar o dict cru do POST pelo schema de entrada `BookCreate` (500 → 422). O schema de saída e o `response_model` ficam para a aula 04, onde `User.password` dá o motivo (ver ADR-0002).

## Bloco 2 — Persistência (backend)

**Aula 04 — Banco de dados e ORMs**
Teoria: o que é um ORM, SQL vs ORM **[T-7]**.
Prática: MySQL, SQLAlchemy, model `Book`, `create_all`, migração do CRUD de Books da memória para o banco — o auto-increment aposenta o id artesanal e os dados sobrevivem ao restart. Users ficam para quando a relação 1:N der o motivo.

**Aula 05 — Users e autenticação com JWT**
Teoria: relação 1:N e chave estrangeira (aprofundamento do T-7); formas de autenticação — cookies, sessions, tokens — e anatomia de um JWT **[T-8]**.
Prática: model `User` (tabela `users`), FK obrigatória `books.user_id` (todo livro tem dono), `POST /signup` com hash de senha (bcrypt), `POST /login` emitindo JWT (PyJWT) e a dependency `get_current_user`: o CRUD de books passa a operar apenas sobre os livros do usuário logado — o dono vem do token, e livro alheio responde 404.

## Bloco 3 — Frontend entra em cena

**Aula 06 - Frontend com React e o consumo da API**
Teoria: aplicações de página única (Garrett, 2005), React - componentes, props, estado e efeitos (UI = f(estado)), Vite, Tailwind e npm; política de mesma origem (RFC 6454) e CORS, com o preflight visto ao vivo pelo `curl`; separação de responsabilidades no frontend (Dijkstra, 1974; Parnas, 1972); bibliotecas de estilo e de componentes - Bootstrap, utility-first e as bibliotecas sobre o Tailwind (Tailwind Plus, Headless UI, daisyUI, Flowbite, shadcn/ui); o token no navegador - header `Authorization: Bearer` (RFC 6750), `localStorage` e o custo XSS vs CSRF.
Prática: `Book` ganha `pages` e `current_page` (validação `pages > 0`, `0 ≤ current_page ≤ pages` com `model_validator`) e o Reading Progress nasce como dado derivado - `@property progress` no model, publicada pelo `BookRead`, nunca armazenada; `CORSMiddleware` liberando a origem do Vite antes de o frontend existir (preflight `OPTIONS` com `curl`: 405 sem o middleware, 200 com ele, 400 para origem fora da lista); frontend React criado com `npm create vite` + Tailwind, sem biblioteca de rotas, organizado em `services/` (`api.js` com fetch, token do `localStorage` no header e erro da API virando exceção; `authService` e `bookService`), `pages/` (signup, login e Books) e `components/` - os estilizados `Button`, `TextInput`, `ErrorMessage` e `Card` (padrão copiar e adaptar, sem dependência nova, com rótulo, foco visível e `role="alert"`) e `BookForm`, `BookItem` com a barra de progresso; demonstração com dois usuários de que a regra de dono é garantida pela API (404), não pela interface.
_O histórico de Reading Updates (segunda relação 1:N, `POST /books/{id}/progress`) fica para um dos slots abaixo: nesta aula o avanço da leitura é atualizar `current_page` do próprio livro._

**Aula 07 - Autorização e controle de acesso baseado em papéis**
Teoria: autenticação vs autorização (RFC 4949), matriz de acesso (Lampson, 1971) e RBAC (Ferraiolo e Kuhn, 1992; Sandhu et al., 1996) **[T-9]**, com a regra de dono como controle baseado na relação entre usuário e recurso; princípios de proteção de Saltzer e Schroeder (1975) - padrões à prova de falha, mediação completa e menor privilégio; OWASP API Security Top 10 (2023) - BOLA, mass assignment e BFLA; 401, 403 e o 404 que esconde a existência do recurso (RFC 9110); a interface esconde, a API proíbe.
Prática, na linha de construção banco de dados → backend → frontend:
1. **Banco de dados** - enum `Role` (`admin`/`user`) e coluna `role` no model `User`, `ENUM` no MySQL com `DEFAULT 'user'`; o `INSERT` do cadastro não cita o papel e o banco grava `user`; a promoção a Admin é um `UPDATE` no MySQL, fora da API.
2. **Backend** - a API analisa o papel: o `"role"` enviado no corpo do signup é ignorado; `User.can_access(book)` concentra a regra de acesso a Books - o Admin lê, edita e apaga qualquer livro e lista todos, o User só os próprios (404 para o alheio); dependency `require_admin` declarada no router `/api/admin` e `GET /api/admin/stats` com as quantidades de Users e de Books (403 para quem não é Admin); o login devolve o `role`.
3. **Frontend** - o Admin Dashboard em `/admin` escolhido pelo endereço no `App.jsx`, sem biblioteca de rotas (`AdminDashboardPage`, `StatCard`, `TextLink` e `adminService`), visível só para o Admin - e a demonstração de que alterar o papel no `localStorage` abre a tela, mas não os dados.

**Aula 08 - Testes automatizados**
Teoria: o que são testes automatizados - testar é executar o programa com a intenção de encontrar defeitos (Myers, 1979) e testes mostram a presença de defeitos, nunca a ausência (Dijkstra, 1970); a família xUnit (SUnit, Beck, 1994; JUnit, Beck e Gamma, 1997; pytest, Krekel, 2004) e o padrão Arrange-Act-Assert; a pirâmide de testes (Cohn, 2009; Vocke, 2018); caixa preta e caixa branca (Myers, 1979); níveis de teste - unidade, integração e aceitação (glossário ISTQB); testes de regressão; dublês de teste (Meszaros, 2007); o princípio da Testing Library (Dodds, 2018).
Prática, do backend para o frontend:
1. **Backend** - pytest e httpx2 no `requirements.txt` e `pytest.ini`; testes de unidade do `Book.progress` (parametrizados) e do `User.can_access` (caixa branca, um teste por caminho); `conftest.py` com SQLite em memória, `dependency_overrides` do `get_session` e fixtures de usuários (User comum e Admin promovido no banco); testes de integração caixa preta das rotas de books, admin e users; teste de regressão para um defeito real - nome de livro só com espaços aceito com 201 - escrito antes da correção (vermelho), corrigido com `str_strip_whitespace` no `BookCreate` (verde).
2. **Frontend, unidade** - Vitest com jsdom e Testing Library: teste de componente do `BookItem` (o que aparece e os callbacks dos botões) e teste do `authService.login` com o `fetch` trocado por um dublê.
3. **Frontend, aceitação** - Playwright: dois testes de ponta a ponta num navegador de verdade, com backend e frontend rodando - o leitor cadastra um livro e acompanha o progresso; quem não é Admin não chega ao Admin Dashboard.

**Aula 09 - Consumo de APIs e modelos de linguagem**
Teoria, aprofundando cliente-servidor **[T-2]** e APIs **[T-3]**: o backend como cliente de uma API de terceiros - a chave de API, a configuração no ambiente (Wiggins, *The Twelve-Factor App*, 2011), a chamada direta do navegador que exporia a chave; chamadas remotas falham (Deutsch, falácias da computação distribuída, 1994) - timeout, 429 (RFC 6585) e o 502 que a nossa API devolve (RFC 9110); modelos de linguagem - definição (Jurafsky e Martin), Transformer (Vaswani et al., 2017), tokens (Sennrich et al., 2016), geração por amostragem e não determinismo, modelos que seguem instruções (Ouyang et al., 2022) e alucinação (Ji et al., 2023); o Gemini (Google DeepMind, 2023) e a Interactions API; prompt - instrução de sistema separada dos dados, restrições explícitas e uma saída para "não conheço"; injeção de prompt (Willison, 2022; OWASP Top 10 for LLM Applications, 2025); saída estruturada - JSON Schema, decodificação restrita (Willard e Louf, 2023) e a validação pelo Pydantic.
Prática, na linha chave → banco de dados → backend → frontend:
1. **Chave** - criação no Google AI Studio, restrição à Gemini API e a variável `GEMINI_API_KEY` no terminal (Mac e Windows).
2. **Banco de dados** - coluna `ai_summary` (`TEXT`, `NULL`) no model `Book`; `DROP TABLE books` para o `create_all` recriar a tabela.
3. **Backend** - schema `BookSummary` (`known_book`, `summary`), cujo JSON Schema vai na requisição; `gemini.py` com a instrução de sistema e o `httpx2.post` para a Interactions API (`gemini-3.5-flash-lite`, `response_format`, `store: false`, timeout de 30 s); `POST /api/books/{book_id}/summary` - 404 pela regra de acesso, 502 quando o Gemini falha, 422 quando o modelo declara não conhecer o livro; teste de integração com o Gemini trocado por um dublê (`monkeypatch`).
4. **Frontend** - `summarizeBook` no `bookService`, o botão *AI summary* no `BookItem`, desabilitado durante a geração, e o resumo abaixo da barra de progresso.

**Aula 10 - Engenharia de software e arquitetura de software (proposta, escopo a confirmar)**
Teoria: engenharia de software (Conferência da OTAN, 1968; IEEE 610.12-1990); o produto antes da tecnologia - complexidade essencial e acidental (Brooks, 1986), integridade conceitual (Brooks, 1975), linguagem ubíqua (Evans, 2003), o mundo e a máquina (Jackson, 1995); arquitetura e a visão de conjunto (ISO/IEC/IEEE 42010; Bass, Clements e Kazman; modelo C4); separação de responsabilidades (Dijkstra, 1974; Parnas, 1972); Ports and Adapters (Cockburn, 2005) e a família Onion e Clean.
Prática: refatoração do backend para Ports and Adapters protegida pelos testes automatizados existentes, que funcionam como testes de caracterização (Feathers, 2004), sem mudar o contrato da API; o fechamento é um pedido de mudança do produto que passa a tocar um único lugar do código. Pode ocupar também a aula 11.

## Bloco 4 — Autenticação e autorização

**Aula 11 — slot a reescopar**
O conteúdo original das aulas 10 e 11 (JWT em duas partes **[T-8]**; autorização e RBAC **[T-9]**) foi antecipado para as aulas 05 e 07, e a aula 09 passou a ser a de consumo de APIs e modelos de linguagem. Candidatos para o slot: a continuação da arquitetura, se ela ocupar duas aulas; model `ReadingUpdate` como histórico de leitura (segunda relação 1:N) com o Reading Progress derivado do update mais recente; tratamento do 401 e expiração do token no front (logout automático); busca por nome na tela de livros; aprofundamento de segurança (expiração e renovação de token); rotas administrativas para listar os Users e os Books de cada um; exercícios integradores.

**Aula 12 — Admin Dashboard**
Prática: navegação pelos Users e seus Books a partir do Admin Dashboard - as quantidades de Users e de Books já existem desde a aula 07.

## Bloco 5 — Features finais

**Aula 13 — Upload de capas**
Teoria: multipart/form-data **[T-10]**.
Prática: `UploadFile` no FastAPI, salvar em disco, servir estático; input de arquivo com preview no front.

**Aula 14 — Geração de PDF**
Prática: Reading Report do User (livros, porcentagens, histórico de updates) com **fpdf2**, rota de download, botão no front.

**Aula 15 — Integração e encerramento técnico**
Prática: tratamento de erros e mensagens no front, revisão do fluxo completo signup→login→livros→relatório; panorama do que ficou fora (migrations, deploy, testes).

**Aula 16 — Apresentação de trabalhos**
Apresentação e avaliação dos trabalhos finais dos alunos.

## Trabalho final

Cada aluno/grupo constrói um **sistema novo, de domínio livre, com a mesma stack da disciplina**. Requisitos mínimos: FastAPI + MySQL no backend, React no frontend, autenticação JWT, alguma regra de autorização, upload de arquivo e geração de PDF. O enunciado deve ser divulgado até o fim do Bloco 4 (aula ~11), para que os alunos desenvolvam em paralelo às últimas aulas.
