# fastapi-best-practices como camada de decisões, com adaptações didáticas

Adotamos o guia [zhanymkanov/fastapi-best-practices](https://github.com/zhanymkanov/fastapi-best-practices) como referência de decisões prontas para o backend — em vez de pesquisar cada convenção do zero. Mas o guia é escrito para sistemas em produção e o nosso é um projeto para ensinar; onde os dois conflitam, a pedagogia vence. O que fica valendo:

## Adotado

- **Follow the REST** — URIs por recurso, mesmos nomes de variável de path entre rotas relacionadas (ex.: sempre `book_id`). Já era o plano da aula 03 [T-3]; o guia confirma.
- **Convenções de nomes no banco** — `lower_case_snake`, tabelas no **plural** (`users`, `books`, `reading_updates`), sufixo `_at` para datetime. Aqui divergimos do guia, que usa singular: adotamos o plural, convenção consagrada pelo Rails e majoritária no mercado. Entra na aula 04 junto com o SQLAlchemy.
- **Docs bem geradas** — declarar `status_code` nas rotas desde a aula 03 e `response_model` a partir da aula 04. O `/docs` fica sempre visível: aqui ele é ferramenta de ensino, não superfície de ataque (o guia manda esconder em produção — mencionar isso em aula).
- **Pydantic para toda entrada/saída** — validar na borda, nunca dicionário cru vindo do cliente. **Ordem didática:** o schema de **entrada** entra na aula 03, onde há um defeito real para corrigir (o POST sem `name` responde 500). O schema de **saída** entra na aula 04, com a migração do CRUD para o banco: as rotas passam a devolver objetos do ORM, e o `BookRead` (com `from_attributes`) declara o contrato — publica `id` e `name` e deixa `created_at` de fora: a resposta é o que o cliente precisa, não a tabela inteira. O caso mais forte do filtro — `User.password` nunca sair na resposta — chega na aula 05, com o signup.
- **Estrutura por tipo de arquivo** (`models.py`, `schemas.py`, `routers/`, `database.py`) quando `main.py` precisar ser dividido. O próprio guia admite que estrutura por tipo "works well for smaller projects" — a estrutura por domínio dele (pacote `auth/`, `books/` com 8 arquivos cada) é para monólitos grandes e seria abstração antes da necessidade.

## Rejeitado

- **Alembic** — já decidido em `docs/convencoes.md`: `create_all()` + dropar o banco entre aulas. Migração é teoria mencionada, não prática.
- ~~**Rotas `async` por padrão** — rotas síncronas (`def`) em todo o curso; FastAPI as roda em threadpool sem problema na nossa escala. `async/await` é carga cognitiva que não é tema da disciplina.~~ **Revisado pelo [ADR-0003](0003-async-onde-ha-motivo.md)**: com a aula 01.3 ensinando o modelo de execução, o projeto passa a usar `async def` onde há motivo (sem I/O ou I/O assíncrono) e `def` onde há chamada bloqueante. Continua valendo o que a decisão original protegia: nada de `async` em tudo, por moda.
- **Custom Base Model, BaseSettings por módulo, cadeias de dependências, SQL-first, requirements base/dev/prod, ruff** — preocupações de produção; contra o critério "legibilidade acima de tudo, sem abstrações que a turma ainda não viu".

Alternativa rejeitada: seguir o guia integralmente. O aluno abriria na aula 04 um projeto com 20 arquivos que ele não escreveu — o oposto do método da disciplina, onde cada arquivo existe porque uma aula o criou.
