# Reading Tracker

Projeto da disciplina Programação Avançada: um rastreador de leituras construído com FastAPI e React.

## Banco de dados

O backend usa MySQL. Antes de rodar pela primeira vez:

    # Mac: brew install mysql && brew services start mysql
    # Windows: MySQL Installer (Server only) — anote a senha do root

    mysql -u root          # Windows: MySQL Command Line Client
    CREATE DATABASE reading_tracker;

A conexão é definida em backend/database.py (DATABASE_URL). Root com
senha? Ajuste para mysql+pymysql://root:SUASENHA@127.0.0.1:3306/reading_tracker

Mudou um model? Dado de aula é descartável: `DROP TABLE books; DROP TABLE users;`
no cliente mysql e deixe o `create_all` recriar as tabelas na próxima subida.

## Papéis: User e Admin

Todo cadastro nasce com o papel `user` (coluna `users.role`, um `ENUM('admin','user')`
com `DEFAULT 'user'`). A API não oferece rota para conceder o papel de Admin: a
promoção é feita direto no banco, no cliente mysql (Mac e Windows):

    UPDATE users SET role = 'admin' WHERE email = 'machado@exemplo.com';

A API consulta o papel no banco a cada requisição: a promoção vale na hora para as
rotas. A interface recebe o papel no login - para o link e a página do Admin
aparecerem, saia e entre de novo.

## Backend — como rodar

    cd backend
    python3 -m venv .venv          # Windows: python -m venv .venv
    source .venv/bin/activate      # Windows: .venv\Scripts\Activate.ps1
    pip install -r requirements.txt
    uvicorn main:app --reload

Abra http://127.0.0.1:8000

## Frontend - como rodar

Requer Node.js LTS (nodejs.org, instalador para Mac e Windows). Em outro terminal,
com o backend já rodando:

    cd frontend
    npm install
    npm run dev

Abra exatamente http://localhost:5173 - é a única origem liberada no CORS da API
(backend/main.py, `allow_origins`). Se a porta 5173 estiver ocupada, o Vite sobe em
outra (5174) e o navegador bloqueia as requisições: libere a 5173 ou acrescente a
nova origem em `allow_origins`.

## Testes automatizados

Backend - testes de unidade e de integração com pytest. Rodam num banco SQLite em
memória, criado e descartado a cada teste: nenhum dado de teste chega ao MySQL. O
MySQL de desenvolvimento ainda precisa estar no ar, porque importar o `main.py`
executa o `create_all` dele. Com a venv ativa:

    cd backend
    pytest                 # todos os testes
    pytest -v              # um teste por linha, com o nome

Frontend - testes de componente e de service com Vitest e Testing Library, num
navegador simulado (jsdom):

    cd frontend
    npm test               # fica observando os arquivos; q para sair
    npm test -- --run      # roda uma vez e termina

Frontend - testes de ponta a ponta com Playwright, num navegador de verdade. Antes
da primeira vez, baixe o navegador que o Playwright controla:

    npx playwright install chromium

Com o backend (uvicorn) e o frontend (npm run dev) rodando, em outro terminal:

    cd frontend
    npm run test:e2e

Os testes de ponta a ponta cadastram usuários de verdade no banco de desenvolvimento,
com e-mails aleatórios (`leitor-<id>@exemplo.com`).

## Estrutura do backend

    backend/
    ├── main.py          ← ponto de entrada: app, create_all, include_router
    ├── database.py      ← conexão, Base e sessão do ORM
    ├── models.py        ← as tabelas (User, Book)
    ├── schemas.py       ← as classes Pydantic de entrada e saída
    ├── security.py      ← hash de senha, token JWT, get_current_user e require_admin
    ├── routers/         ← as rotas de cada recurso (users.py, books.py, admin.py)
    ├── pytest.ini       ← configuração do pytest: onde estão os testes
    └── tests/
        ├── conftest.py       ← fixtures: banco SQLite de teste, cliente HTTP e usuários
        ├── test_models.py    ← unidade: Reading Progress e regra de acesso (caixa branca)
        ├── test_books_api.py ← integração: rotas de books, inclusive o teste de regressão
        ├── test_admin_api.py ← integração: 401, 403 e 200 do Admin Dashboard
        └── test_users_api.py ← integração: cadastro e login

## Estrutura do frontend

    frontend/
    ├── index.html       ← o único HTML: a div#root e o script do main.jsx
    ├── vite.config.js   ← plugins do Vite (React e Tailwind) e configuração do Vitest
    ├── package.json     ← dependências e scripts (dev, build, test, test:e2e)
    ├── playwright.config.js ← testes de ponta a ponta: pasta e2e/ e endereço do frontend
    ├── e2e/
    │   └── books.spec.js    ← aceitação: cadastro, livro, progresso e acesso ao /admin
    └── src/
        ├── main.jsx           ← ponto de entrada: monta o App na div#root
        ├── index.css          ← importa o Tailwind
        ├── App.jsx            ← componente raiz: o token, o papel e o endereço decidem a página
        ├── services/          ← conversa com a API: URLs, verbos e formato das respostas
        │   ├── api.js          ← request(): fetch com JSON, token e tratamento de erro
        │   ├── authService.js  ← signup() e login()
        │   ├── bookService.js  ← listBooks(), createBook(), updateBook(), deleteBook()
        │   ├── adminService.js ← getStats(): as quantidades do Admin Dashboard
        │   └── authService.test.js ← teste do login com o fetch trocado por um dublê
        ├── pages/             ← telas inteiras: guardam o estado e chamam os services
        │   ├── SignupPage.jsx         ← cadastro
        │   ├── LoginPage.jsx          ← login; entrega o token e o papel ao App
        │   ├── BooksPage.jsx          ← livros: listar, criar, editar e apagar
        │   └── AdminDashboardPage.jsx ← Admin Dashboard (/admin): quantidades de Users e Books
        └── components/        ← pedaços de tela: recebem props, não chamam a API
            ├── Button.jsx       ← botão do sistema, com as variantes primary, secondary e danger
            ├── TextInput.jsx    ← campo com rótulo, borda e foco padronizados
            ├── ErrorMessage.jsx ← mensagem de erro em destaque (role="alert")
            ├── Card.jsx         ← superfície branca que envolve formulários e livros
            ├── TextLink.jsx     ← link de navegação entre páginas (/admin e /)
            ├── BookForm.jsx     ← formulário de criar ou editar um livro
            ├── BookItem.jsx     ← um livro da lista, com a barra de progresso
            ├── BookItem.test.jsx ← teste de componente: o que aparece e os cliques
            └── StatCard.jsx     ← uma quantidade do Admin Dashboard

Cada pasta tem uma responsabilidade: só os `services` falam com a API, as `pages`
guardam o estado de cada tela e os `components` desenham o que recebem por props.
A aparência vive em `Button`, `TextInput`, `ErrorMessage`, `Card` e `TextLink`,
estilizados com classes do Tailwind: as páginas usam esses componentes em vez de
repetir classes.

Não há biblioteca de rotas: o `App.jsx` lê `window.location.pathname` e, para o
endereço `/admin`, abre o Admin Dashboard - só se o papel recebido no login for
`admin`. Esconder a página é conveniência da interface; quem protege os dados é a
API, que responde 403 a quem não é Admin.

## Endpoints

| Método | Rota | Autenticação | O que faz |
| ------ | ---- | ------------ | --------- |
| GET | /health | — | Verifica se a API está no ar |
| POST | /signup | — | Cadastra um User (senha guardada como hash); e-mail repetido responde 409 |
| POST | /login | — | Troca e-mail e senha válidos por um token JWT e devolve o `role` do User (credencial inválida responde 401) |
| GET | /api/books | Bearer | Lista os livros do usuário logado (o Admin recebe os de todos); query param opcional name busca pelo nome |
| GET | /api/books/{book_id} | Bearer | Um livro pelo id (404 se não existir ou se for de outro User e quem pede não for Admin) |
| POST | /api/books | Bearer | Cria um livro do usuário logado; corpo `name`, `pages` (> 0) e `current_page` (opcional, ≥ 0 e ≤ pages), validado pelo schema BookCreate - o nome é gravado sem os espaços das pontas, e um nome só de espaços responde 422 |
| PUT | /api/books/{book_id} | Bearer | Atualiza `name`, `pages` e `current_page` de um livro (404 se não existir ou se for de outro User e quem pede não for Admin) |
| DELETE | /api/books/{book_id} | Bearer | Remove um livro; responde 204 sem corpo (404 se não existir ou se for de outro User e quem pede não for Admin) |
| GET | /api/admin/stats | Bearer, Admin | Quantidades de Users e de Books cadastrados (`users_count`, `books_count`); quem não é Admin recebe 403 |

As rotas marcadas com **Bearer** exigem o header `Authorization: Bearer <token>`,
com o token devolvido pelo `POST /login`. Sem token (ou com token inválido/vencido),
a resposta é **401**. As marcadas com **Admin** exigem ainda o papel `admin`: um User
autenticado sem esse papel recebe **403**.

Todo livro devolvido pela API traz `progress`: a porcentagem de leitura, calculada
a partir de `current_page` e `pages` (100 = concluído). É dado derivado - não existe
no banco.

A documentação interativa (Swagger) fica em http://127.0.0.1:8000/docs

## Tabela de Dependências

| Nome | Utilidade | Versão |
| ---- | --------- | ------ |
| annotated-doc | Documentação dentro de anotações de tipo (usada pelo FastAPI) | 0.0.4 |
| annotated-types | Restrições em anotações de tipo (usada pelo pydantic) | 0.7.0 |
| anyio | Camada assíncrona sobre a qual o starlette roda | 4.14.2 |
| bcrypt | Hash de senhas: mão única, com salt e custo ajustável | 5.0.0 |
| cffi | Ponte entre Python e código C (usada pela cryptography) | 2.1.0 |
| click | Criação de comandos de terminal (usada pelo uvicorn) | 8.4.2 |
| cryptography | Primitivas criptográficas; o PyMySQL a exige para a autenticação do MySQL 8+ | 49.0.0 |
| dnspython | Consultas DNS (usada pelo email-validator) | 2.8.0 |
| email-validator | Validação de formato de e-mail (o EmailStr do pydantic) | 2.3.0 |
| fastapi | Framework web: rotas, validação e documentação automática | 0.139.2 |
| h11 | Implementação do protocolo HTTP/1.1 (usada pelo uvicorn) | 0.16.0 |
| httpcore2 | Núcleo de transporte HTTP (usado pelo httpx2) | 2.13.1 |
| httpx2 | Cliente HTTP que o TestClient do FastAPI usa para chamar a API nos testes | 2.13.1 |
| idna | Suporte a nomes de domínio internacionais | 3.18 |
| iniconfig | Leitura de arquivos .ini (usada pelo pytest para o pytest.ini) | 2.3.1 |
| packaging | Comparação de versões de pacotes (usada pelo pytest) | 26.3 |
| pluggy | Sistema de plugins (usado pelo pytest) | 1.6.0 |
| pycparser | Interpretação de declarações C (usada pela cffi) | 3.0 |
| pydantic | Validação e conversão de dados | 2.13.4 |
| pydantic_core | Núcleo compilado do pydantic | 2.46.4 |
| Pygments | Realce de sintaxe nas mensagens de falha (usado pelo pytest) | 2.21.0 |
| PyJWT | Emissão e verificação de tokens JWT (RFC 7519) | 2.13.0 |
| PyMySQL | Driver MySQL em Python puro: fala o protocolo do banco na porta 3306 | 1.2.0 |
| pytest | Framework de testes: descobre, executa e relata os testes do backend | 9.1.1 |
| SQLAlchemy | ORM: mapeia classes Python em tabelas do banco | 2.0.51 |
| starlette | Base do FastAPI: HTTP, rotas e middlewares | 1.3.1 |
| truststore | Certificados do sistema operacional para conexões HTTPS (usado pelo httpx2) | 0.10.5 |
| typing-inspection | Inspeção de anotações de tipo (usada pelo pydantic) | 0.4.2 |
| typing_extensions | Recursos novos de tipagem para versões antigas do Python | 4.16.0 |
| uvicorn | Servidor web que executa a aplicação | 0.51.0 |

Instalamos diretamente apenas **fastapi**, **uvicorn**, **sqlalchemy**, **pymysql**, **cryptography**, **bcrypt**, **pyjwt**, o extra **pydantic[email]** (que traz email-validator e dnspython), **pytest** e **httpx2**; as demais vieram como dependências delas.

## Tabela de Dependências do frontend

Espelha o `package.json` (as versões abaixo são as instaladas; o `^` do arquivo
aceita atualizações compatíveis).

| Nome | Utilidade | Versão |
| ---- | --------- | ------ |
| @tailwindcss/vite | Plugin que integra o Tailwind ao build do Vite | 4.3.3 |
| react | Biblioteca de interfaces: componentes, estado e JSX | 19.3.0 |
| react-dom | Liga o React ao DOM do navegador (createRoot) | 19.3.0 |
| tailwindcss | CSS utilitário: as classes usadas no JSX viram estilo | 4.3.3 |
| @playwright/test | Testes de ponta a ponta num navegador de verdade (`npm run test:e2e`) (dev) | 1.64.1 |
| @testing-library/dom | Consultas ao DOM pelo que o usuário vê: texto, rótulo, papel (dev) | 10.4.2 |
| @testing-library/react | Desenha componentes React nos testes (`render`, `screen`) (dev) | 16.3.3 |
| @types/react | Tipos do React para o editor (dev) | 19.3.0 |
| @types/react-dom | Tipos do react-dom para o editor (dev) | 19.3.0 |
| @vitejs/plugin-react | Plugin que ensina o Vite a compilar JSX (dev) | 6.1.1 |
| jsdom | Navegador simulado em que o Vitest desenha os componentes (dev) | 30.1.2 |
| oxlint | Linter gerado pelo esqueleto do Vite (`npm run lint`) (dev) | 1.82.0 |
| vite | Servidor de desenvolvimento e ferramenta de build (dev) | 8.2.2 |
| vitest | Framework de testes de unidade e de componente (`npm test`) (dev) | 5.0.4 |

Instalamos diretamente apenas **tailwindcss**, **@tailwindcss/vite**, **vitest**,
**jsdom**, **@testing-library/react**, **@testing-library/dom** e **@playwright/test**;
as demais vieram com o esqueleto gerado por `npm create vite@latest`.
