---
name: aula-conteudo
description: Escreve o material principal de uma aula de qualquer disciplina do repositório - o conteúdo em Markdown e o `.c` em Algoritmos e Estruturas de Dados, o roteiro do professor e o código do projeto em Programação Avançada. Use quando o professor pedir o conteúdo, o roteiro ou o código de uma aula ("monte a aula sobre pilha", "escreva a aula 09", "roteiro da aula de JWT").
---

# Material principal da aula

Escreve o artefato do qual tudo deriva: os slides espelham o material principal e a revisão o usa como contrato.
O perfil da disciplina diz qual artefato é o material principal, onde fica e o que lê antes.

## Antes de escrever

1. Identifique a disciplina (pedido ou pasta; em dúvida, pergunte) e leia o perfil `disciplinas/<disciplina>/CLAUDE.md` inteiro. O perfil vence esta skill em conflito; o `CLAUDE.md` da raiz traz as regras de toda aula.
2. Defina o número: o próximo disponível em `aulas/`, salvo pedido explícito. Aulas existentes mantêm o número.
3. Leia tudo o que a seção **Conteúdo** do perfil manda ler: plano, glossário, ADRs, código atual, referências e templates desta skill em `references/<disciplina>/` e `templates/<disciplina>/`.
4. Se o perfil classifica aulas por tipo, classifique. Em dúvida real, pergunte antes de produzir; em caso óbvio, decida e diga em uma linha.

## Escrever

- Siga a estrutura que as referências da disciplina definem; templates são andaime, adaptados a cada aula.
- Todo conceito de que a aula depende é apresentado aqui, com definição e exemplo próprios (aula fechada).
- Escreva o código de verdade, idêntico ao que o material mostra. Comandos que produzem arquivos (ex.: `pip freeze > requirements.txt`) são executados.
- Atualize os índices e o README que o perfil lista.

## Pronto quando

- Cada bloco, seção ou passo que a estrutura da disciplina exige está presente, na ordem.
- O código foi validado como o perfil pede (compilar, importar, testes), e o que subiu foi derrubado.
- Os itens da seção **Consistência** do perfil que já se aplicam ao material principal estão ✅.

Reporte em 2-3 frases: arquivos criados ou alterados, índices atualizados e o próximo passo (`aula-slides`).
