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

## Backend — como rodar

    cd backend
    python3 -m venv .venv          # Windows: python -m venv .venv
    source .venv/bin/activate      # Windows: .venv\Scripts\Activate.ps1
    pip install -r requirements.txt
    uvicorn main:app --reload

Abra http://127.0.0.1:8000

## Endpoints

| Método | Rota | O que faz |
| ------ | ---- | --------- |
| GET | /health | Verifica se a API está no ar |
| GET | /api/books | Lista os livros; query param opcional name busca pelo nome |
| GET | /api/books/{book_id} | Um livro pelo id (404 se não existir) |
| POST | /api/books | Cria um livro; corpo validado pelo schema BookCreate |
| PUT | /api/books/{book_id} | Atualiza o nome de um livro (404 se não existir) |
| DELETE | /api/books/{book_id} | Remove um livro; responde 204 sem corpo (404 se não existir) |
| POST | /signup | Cadastra um User; e-mail repetido responde 409 |

A documentação interativa (Swagger) fica em http://127.0.0.1:8000/docs

## Tabela de Dependências

| Nome | Utilidade | Versão |
| ---- | --------- | ------ |
| annotated-doc | Documentação dentro de anotações de tipo (usada pelo FastAPI) | 0.0.4 |
| annotated-types | Restrições em anotações de tipo (usada pelo pydantic) | 0.7.0 |
| anyio | Camada assíncrona sobre a qual o starlette roda | 4.14.2 |
| cffi | Ponte entre Python e código C (usada pela cryptography) | 2.1.0 |
| click | Criação de comandos de terminal (usada pelo uvicorn) | 8.4.2 |
| cryptography | Primitivas criptográficas; o PyMySQL a exige para a autenticação do MySQL 8+ | 49.0.0 |
| fastapi | Framework web: rotas, validação e documentação automática | 0.139.2 |
| h11 | Implementação do protocolo HTTP/1.1 (usada pelo uvicorn) | 0.16.0 |
| idna | Suporte a nomes de domínio internacionais | 3.18 |
| pycparser | Interpretação de declarações C (usada pela cffi) | 3.0 |
| pydantic | Validação e conversão de dados | 2.13.4 |
| pydantic_core | Núcleo compilado do pydantic | 2.46.4 |
| PyMySQL | Driver MySQL em Python puro: fala o protocolo do banco na porta 3306 | 1.2.0 |
| SQLAlchemy | ORM: mapeia classes Python em tabelas do banco | 2.0.51 |
| starlette | Base do FastAPI: HTTP, rotas e middlewares | 1.3.1 |
| typing-inspection | Inspeção de anotações de tipo (usada pelo pydantic) | 0.4.2 |
| typing_extensions | Recursos novos de tipagem para versões antigas do Python | 4.16.0 |
| uvicorn | Servidor web que executa a aplicação | 0.51.0 |

Instalamos diretamente apenas **fastapi**, **uvicorn**, **sqlalchemy**, **pymysql** e **cryptography**; as demais vieram como dependências delas.
