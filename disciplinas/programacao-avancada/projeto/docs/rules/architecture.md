# Arquitetura do backend

- Uma rota trata de HTTP: lê a requisição, aciona o model e devolve o status e o schema de saída.
- Regra do domínio é método do model. Uma rota não decide quem acessa um Book nem quando um AI Summary é gravado.
- Cada regra do domínio existe em um só lugar. O acesso a Books é `User.can_access`.
- As dependências apontam para o model: `routers/` conhece `models` e `schemas`; `models.py` não importa `fastapi`, `schemas` nem `routers`.
- Só o módulo de uma integração conhece a biblioteca que ela usa. Uma rota não importa `httpx2`.
