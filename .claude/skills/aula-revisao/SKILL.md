---
name: aula-revisao
description: Revisa e corrige uma aula pronta de qualquer disciplina do repositório - revisão severa dos slides e conferência de consistência entre slides, código, README e índices. Use quando o professor pedir para revisar, criticar, sincronizar ou fechar uma aula ("revise a aula 05", "revisão severa dos slides da aula 02", "sincroniza a aula 08").
---

# Revisão da aula

Recebe a aula pronta e a endurece, corrigindo direto nos arquivos.
São duas passadas. Rode a que o pedido pede ("revisão severa dos slides" é a passada 1; "sincroniza" é a passada 2) e, ao fechar uma aula, as duas. A passada 2 roda sempre que algo for editado.

## Antes de revisar

1. Leia o perfil `disciplinas/<disciplina>/CLAUDE.md` e o `CLAUDE.md` da raiz: boa parte dos critérios existe para fazer cumprir essas regras.
2. Leia os slides da aula inteiros antes de editar. Conexão lógica e repetição só se julgam com a aula toda na cabeça.
3. Para a passada 1, leia também as outras aulas prontas da disciplina, para reconhecer o que é tema de outra aula (critério de excesso). Elas servem de régua, nunca de remissão.

## Passada 1 - slides (severa)

Leia `references/criterios-slides.md` antes. Critérios: **1** termo órfão, **2** registro de palestra e jargão, **3** excesso e repetição, **4** conceito sem código, **5** conceito sem visualização, **6** referência a outra aula, **7** ambiguidade, **8** conexão lógica. Ordem por slide: 3 → 6 → 1 → 2 → 7 → 4 → 5 → 8.

- Inventarie todas as `<section>` com título e contagem. Marque as intocáveis: capa, título, encerramento, Referências e as que o perfil protege.
- Pergunta de corte, para todo slide: "se eu apagar este slide, o que o aluno perde que nenhum outro dá?" Nada, ou só a repetição: corta.
- Cortar é o padrão, e todo corte é relatado. Termo obscuro se corrige explicando; só sai quando não serve à aula.
- Assunto novo previsto pela estrutura (bloco, camada, seção) é início legítimo: exija só a frase de transição.
- O contrato didático do perfil permanece: blocos, camadas, citações inline.
- Código e diagrama novos seguem o perfil, e o código da aula acompanha toda mudança no código mostrado.

## Passada 2 - consistência

Rode o checklist **Consistência** do perfil, mais estes itens comuns:

- [ ] Todo código dos slides existe no código real da aula, e todo código da aula aparece nos slides.
- [ ] Aula fechada: busque nos slides por `aula 0`, `aula 1`, `próxima aula`, `aula anterior`, `vimos na`, `onde paramos`, `semana que vem`. Fora da capa e do título, cada ocorrência é defeito.
- [ ] Todo arquivo local referenciado existe e nenhum recurso vem de fora.

Reporte cada item ✅/❌ antes de corrigir.
O slide é a fonte da verdade: em divergência, o código segue o slide. Quando o código evoluiu por bom motivo e o slide é que ficou para trás, pergunte ao professor antes de mexer.

## Pronto quando

Cada critério das passadas pedidas foi aplicado a cada slide, e cada item do checklist tem ✅ ou um ❌ justificado.
Reporte, agrupado por passada e critério: achados, correções, a lista explícita de tudo que foi removido (slides pelo título), a contagem de `<section>` antes → depois, o checklist e o que ficou pendente por depender do professor.
