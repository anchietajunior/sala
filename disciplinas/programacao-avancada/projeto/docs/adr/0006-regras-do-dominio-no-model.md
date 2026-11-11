# Regras do domínio no model, rotas só com HTTP

O ADR-0002 definiu a estrutura por tipo de arquivo, sem dizer em qual arquivo fica uma regra do domínio.
Sem essa decisão, cada rota nova escolhe um lugar: a regra de acesso a Books já aparece em `models.py` e em `routers/books.py`.

## A decisão

- O backend segue a separação do MVC: `routers/` é o Controller, `models.py` é o Model e `schemas.py` define a representação.
- Regra do domínio é método do model. A rota lê a requisição, aciona o model e devolve o status e o schema de saída.
- As restrições que decorrem desta decisão ficam em `docs/rules/architecture.md`.

## Consequências

- Uma regra do domínio é testada no model, sem HTTP.
- O model continua ligado ao SQLAlchemy: testar uma regra que consulta o banco exige um banco.
- O código atual diverge em três pontos de `routers/books.py`, registrados como problema em aberto.

## Alternativas rejeitadas

- **Ports and Adapters.** Isola as regras do domínio de FastAPI, SQLAlchemy e httpx2, e permite testá-las com dublês. O AI Summary passaria de quatro para sete arquivos. O projeto tem uma tecnologia por porta e poucas regras: hoje o custo supera o ganho. A decisão muda se surgir um segundo provedor de IA ou uma segunda forma de entrada.
- **Deixar sem registro.** Cada pessoa e cada agente de IA inferem uma organização diferente a partir do código.
