---
name: aula-completa
description: Fluxo completo de uma aula de qualquer disciplina do repositório - material principal, slides, revisão e commit na main. Use quando o professor pedir a aula inteira ("cria a aula 09", "monta a aula sobre fila", "faz a aula 05 completa").
---

# Aula completa

Orquestra as outras três skills de aula, em ordem fixa.
Em cada etapa, leia o `SKILL.md` da skill e execute-o como se ela tivesse sido invocada: as regras de cada artefato vivem lá e no perfil da disciplina.

## Etapas

1. **Disciplina e escopo.** Identifique a disciplina pelo pedido ou pela pasta em que se está trabalhando; em dúvida, pergunte. Leia o perfil `disciplinas/<disciplina>/CLAUDE.md`. Pronto quando a disciplina, o número e o tema da aula estão definidos e, se o perfil tem plano de aulas, a aula consta nele.
2. **Material principal.** Execute `.claude/skills/aula-conteudo/SKILL.md`. Pronto quando o material principal e o código existem e o código foi validado como o perfil pede.
3. **Slides.** Execute `.claude/skills/aula-slides/SKILL.md`. Pronto quando a apresentação abre com todos os recursos locais resolvidos.
4. **Revisão.** Execute `.claude/skills/aula-revisao/SKILL.md` com as três passadas. Pronto quando o checklist de consistência está todo ✅, ou os ❌ restantes dependem de decisão do professor e foram reportados.
5. **Commit.** Na `main`, um commit com a mensagem `<sigla> aula NN: <o que a aula construiu, em inglês>`, a sigla do perfil, e push para `origin`. Se o `origin` não estiver configurado, avise em vez de criar repositório.

## Regras

- Mudança de escopo em relação ao plano ou ao perfil é decisão do professor: pare e pergunte. No resto, decida e siga.
- Servidores sobem só para validar e são derrubados em seguida.
