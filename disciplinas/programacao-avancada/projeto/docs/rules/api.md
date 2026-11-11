# Rotas da API

- URI por recurso, no plural, sob `/api`: `/api/books/{book_id}`. As rotas de autenticação `/signup` e `/login` são a exceção.
- Toda rota com corpo de resposta declara `response_model`; o `status_code` é declarado quando não for 200.
- Toda rota sob `/api` exige `get_current_user`. Recurso inexistente e recurso sem acesso respondem o mesmo 404.
- `def` quando a rota usa a sessão do banco ou outra chamada bloqueante; `async def` quando não há chamada bloqueante (ADR-0003).
- O corpo da requisição é um schema Pydantic, nunca um dicionário.
