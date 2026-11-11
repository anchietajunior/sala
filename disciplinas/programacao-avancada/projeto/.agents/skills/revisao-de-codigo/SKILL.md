---
name: revisao-de-codigo
description: Revisa o código do Reading Tracker contra as decisões do projeto. Use quando pedirem revisão de código (code review), antes de um commit ou de um pull request.
---

# Revisão de código

Aponte o que diverge das decisões do projeto, com evidência.
A revisão só relata: não altere arquivos.

## Antes de revisar

1. Leia `AGENTS.md`, `CONTEXT.md`, as rules em `docs/rules/` e os ADRs em `docs/adr/`.
2. Se o pedido indica arquivos, revise esses arquivos.
3. Sem indicação, revise as mudanças pendentes: `git status` e `git diff`.

## O que conferir, nesta ordem

1. **Arquitetura**: cada responsabilidade está no arquivo que a rule de arquitetura define? As dependências apontam na direção permitida?
2. **Correção**: o código faz o que promete? Quais entradas o quebram?
3. **Segurança**: toda rota sob `/api` exige autenticação e aplica a regra de acesso? Há segredo no código?
4. **Testes**: o caminho de sucesso e cada caminho de erro têm teste?
5. **Clareza**: os nomes revelam a intenção? Os termos do domínio seguem o `CONTEXT.md`?

## Como relatar

Para cada achado, informe o arquivo e a linha, a regra ou o ADR violado, a consequência e a correção sugerida.

Classifique cada achado:

- **bloqueia**: viola uma regra ou um ADR, ou quebra um comportamento;
- **melhoria**: não viola regra, mas reduz risco ou esforço;
- **dúvida**: depende de uma decisão que o projeto ainda não registrou.

Sem achados numa etapa, escreva o que foi conferido nela.
