# Testes: pytest com SQLite em memória no backend; Vitest e Playwright no frontend

A aula 08 introduz testes automatizados nas duas pontas do projeto, e as aulas seguintes passam a rodar sobre eles - a refatoração de arquitetura, em especial, depende de uma suíte que prove que o comportamento não mudou.

## A decisão

- **Backend: pytest + `TestClient` do FastAPI**, com o **httpx2** como cliente HTTP (o Starlette marca o `httpx` como obsoleto para o `TestClient`). As dependências de teste entram no mesmo `requirements.txt` - o ADR-0002 já rejeitou a divisão em base/dev/prod.
- **Banco dos testes: SQLite em memória**, um banco novo por teste, ligado às rotas pelo `app.dependency_overrides[get_session]`. É o padrão da documentação do FastAPI, não exige criar nada no MySQL, roda igual em Mac e Windows e isola cada teste sem limpeza manual.
- **Frontend, unidade e componente: Vitest + Testing Library + jsdom.** O Vitest reaproveita o `vite.config.js` que o projeto já tem; a Testing Library consulta a tela pelo que o usuário vê (texto, rótulo, papel), não pela estrutura interna do componente.
- **Frontend, ponta a ponta: Playwright** com o Chromium, contra o backend e o frontend rodando. Os testes de aceitação percorrem a aplicação inteira pela tela.

## Consequências

- O SQLite não é o MySQL: o `ENUM` vira `VARCHAR`, a chave estrangeira não é imposta por padrão e a comparação de texto pode diferir. Comportamento que depende do banco (o `ENUM` recusando um papel inválido, por exemplo) continua sendo verificado no MySQL, à mão ou pelos testes de ponta a ponta.
- Importar o `main.py` executa o `create_all` no MySQL de desenvolvimento: para rodar o pytest, o MySQL precisa estar no ar, embora nenhum dado de teste chegue a ele. É um efeito colateral no import, registrado como problema em aberto.
- Os testes de ponta a ponta gravam usuários no banco de desenvolvimento, com e-mails aleatórios (`crypto.randomUUID`), para não colidirem nem quando rodam em paralelo.
- O Playwright exige baixar o navegador uma vez (`npx playwright install chromium`) - fazer antes da aula.

## Alternativas rejeitadas

- **Um banco MySQL de teste (`reading_tracker_test`).** Mesmo dialeto da produção, mas exige criar o banco em cada máquina, limpar as tabelas entre testes e deixa a suíte mais lenta - custo alto para o ganho, numa suíte em que o MySQL já é exercitado pelos testes de ponta a ponta.
- **Jest no lugar do Vitest.** Exigiria configurar a transformação de JSX e de ES modules à parte; o Vitest usa o mesmo pipeline do Vite.
- **Cypress no lugar do Playwright.** Atende o mesmo papel; o Playwright tem API `async/await` alinhada ao JavaScript que a turma já escreve e roda os testes em paralelo sem configuração.
