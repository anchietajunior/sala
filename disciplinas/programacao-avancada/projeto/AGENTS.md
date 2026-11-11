# Reading Tracker

Rastreador de leituras: um User cadastra Books e acompanha o Reading Progress.
Backend em FastAPI, SQLAlchemy e MySQL. Frontend em React, Vite e Tailwind.

## Comandos

- Backend, em `backend/` com a venv ativa: `uvicorn main:app --reload`
- Testes do backend, em `backend/` e com o MySQL no ar: `pytest`
- Frontend, em `frontend/`: `npm run dev`
- Testes do frontend, em `frontend/`: `npm test -- --run`

## Onde estão as decisões

- `CONTEXT.md`: o glossário do domínio. Use os termos exatamente como estão lá.
- `docs/adr/`: as decisões do projeto e o motivo de cada uma. Leia o ADR antes de alterar o que ele decide.
- `docs/specs/`: o comportamento esperado de cada funcionalidade e os critérios de aceitação. Leia a spec antes de alterar a funcionalidade.
- `README.md`: como executar, os endpoints e as dependências. Atualize-o quando um deles mudar.

## Arquitetura do backend

O backend segue a separação do MVC, com um tipo de arquivo para cada responsabilidade:

- `routers/` é o Controller: recebe a requisição, aciona o model e devolve o status e o schema de saída.
- `models.py` é o Model: as tabelas e as regras do domínio, como `User.can_access` e `Book.progress`.
- `schemas.py` define a representação: o formato de entrada e de saída da API.
- A integração com um serviço externo fica num módulo próprio, como `gemini.py`.

## Regras

Leia a regra antes de alterar os arquivos que ela cobre:

- `docs/rules/architecture.md`: a arquitetura do backend. Vale para todo arquivo de `backend/`.
- `docs/rules/api.md`: as rotas da API. Vale para os arquivos de `backend/routers/`.

## Convenções

- Código em inglês. Comentário em pt-BR imediatamente acima de cada bloco.
- Toda mudança de comportamento tem um teste, e o `pytest` passa antes de a tarefa terminar.
- Segredos ficam em variáveis de ambiente, nunca no código.

## Limites

- Não instale dependência nova sem perguntar.
- Não altere `CONTEXT.md` nem `docs/adr/` sem pedido explícito.
