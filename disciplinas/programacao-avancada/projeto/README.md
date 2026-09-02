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

## Backend — como rodar

    cd backend
    python3 -m venv .venv          # Windows: python -m venv .venv
    source .venv/bin/activate      # Windows: .venv\Scripts\Activate.ps1
    pip install -r requirements.txt
    uvicorn main:app --reload

Abra http://127.0.0.1:8000

## Endpoints

| Método | Rota | Autenticação | O que faz |
| ------ | ---- | ------------ | --------- |
| GET | /health | — | Verifica se a API está no ar |
| POST | /signup | — | Cadastra um User (senha guardada como hash); e-mail repetido responde 409 |
| POST | /login | — | Troca e-mail e senha válidos por um token JWT (credencial inválida responde 401) |
| GET | /api/books | Bearer | Lista os livros do usuário logado; query param opcional name busca pelo nome |
| GET | /api/books/{book_id} | Bearer | Um livro do usuário logado pelo id (404 se não existir ou não for dele) |
| POST | /api/books | Bearer | Cria um livro do usuário logado; corpo validado pelo schema BookCreate |
| PUT | /api/books/{book_id} | Bearer | Atualiza o nome de um livro do usuário logado (404 se não existir ou não for dele) |
| DELETE | /api/books/{book_id} | Bearer | Remove um livro do usuário logado; responde 204 sem corpo (404 se não existir ou não for dele) |

As rotas marcadas com **Bearer** exigem o header `Authorization: Bearer <token>`,
com o token devolvido pelo `POST /login`. Sem token (ou com token inválido/vencido),
a resposta é **401**.

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
| fastapi | Framework web: rotas, validação e documentação automática | 0.139.2 |
| h11 | Implementação do protocolo HTTP/1.1 (usada pelo uvicorn) | 0.16.0 |
| idna | Suporte a nomes de domínio internacionais | 3.18 |
| pycparser | Interpretação de declarações C (usada pela cffi) | 3.0 |
| pydantic | Validação e conversão de dados | 2.13.4 |
| pydantic_core | Núcleo compilado do pydantic | 2.46.4 |
| PyJWT | Emissão e verificação de tokens JWT (RFC 7519) | 2.13.0 |
| PyMySQL | Driver MySQL em Python puro: fala o protocolo do banco na porta 3306 | 1.2.0 |
| SQLAlchemy | ORM: mapeia classes Python em tabelas do banco | 2.0.51 |
| starlette | Base do FastAPI: HTTP, rotas e middlewares | 1.3.1 |
| typing-inspection | Inspeção de anotações de tipo (usada pelo pydantic) | 0.4.2 |
| typing_extensions | Recursos novos de tipagem para versões antigas do Python | 4.16.0 |
| uvicorn | Servidor web que executa a aplicação | 0.51.0 |

Instalamos diretamente apenas **fastapi**, **uvicorn**, **sqlalchemy**, **pymysql**, **cryptography**, **bcrypt** e **pyjwt**; as demais vieram como dependências delas.
