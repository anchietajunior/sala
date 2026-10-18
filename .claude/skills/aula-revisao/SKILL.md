---
name: aula-revisao
description: Revisa e corrige uma aula pronta de qualquer disciplina do repositório - o material principal, os slides em revisão severa e a consistência entre material, slides, código, README e índices. Use quando o professor pedir para revisar, criticar, sincronizar ou fechar uma aula ("revise a aula 05", "revisão severa dos slides da aula 02", "sincroniza a aula 08").
---

# Revisão da aula

Recebe a aula pronta e a endurece, corrigindo direto nos arquivos.
São três passadas. Rode as que o pedido pede ("revisão severa dos slides" é a passada 2) e, ao fechar uma aula, as três. A passada 3 roda sempre que algo for editado.

## Antes de revisar

1. Leia o perfil `disciplinas/<disciplina>/CLAUDE.md` e o `CLAUDE.md` da raiz: boa parte dos critérios existe para fazer cumprir essas regras.
2. Leia o material principal e os slides da aula inteiros antes de editar. Conexão lógica e repetição só se julgam com o texto todo na cabeça.
3. Para a passada 2, leia também as outras aulas prontas da disciplina, para reconhecer o que é tema de outra aula (critério de excesso). Elas servem de régua, nunca de remissão.

## Passada 1 - material principal

Leia `references/criterios-conteudo.md` antes. Critérios: **1** ambiguidade, **2** item sem explicação clara, **3** contexto excessivo, **4** conexão lógica, **5** referência a outra aula. Ordem por trecho: 1 → 2 → 3 → 5 → 4.

- Item obscuro se corrige explicando; só sai quando não serve à aula.
- Contexto excessivo sai inteiro.
- Assunto novo previsto pela estrutura (bloco, camada, seção) é início legítimo: exija só a frase de transição.
- O contrato didático do perfil permanece: blocos, camadas, citações inline, cabeçalho do roteiro.

## Passada 2 - slides (severa)

Leia `references/criterios-slides.md` antes. Critérios: **1** termo órfão, **2** registro de palestra e jargão, **3** excesso e repetição, **4** conceito sem código, **5** conceito sem visualização, **6** referência a outra aula. Ordem por slide: 3 → 6 → 1 → 2 → 4 → 5.

- Inventarie todas as `<section>` com título e contagem. Marque as intocáveis: capa, título, encerramento, Referências e as que o perfil protege.
- Pergunta de corte, para todo slide: "se eu apagar este slide, o que o aluno perde que nenhum outro dá?" Nada, ou só a repetição: corta.
- Cortar é o padrão, e todo corte é relatado. Código e diagrama novos seguem o perfil.
- Slides e material principal terminam contando a mesma história: se um corte muda a história, ajuste o material ou desfaça o corte.

## Passada 3 - consistência

Rode o checklist **Consistência** do perfil, mais estes itens comuns:

- [ ] Material principal e slides cobrem os mesmos tópicos, na mesma ordem; todo código dos slides existe no código real.
- [ ] Aula fechada: busque no material e nos slides por `aula 0`, `aula 1`, `próxima aula`, `aula anterior`, `vimos na`, `onde paramos`, `semana que vem`. Fora das exceções do perfil, cada ocorrência é defeito.
- [ ] Todo arquivo local referenciado existe e nenhum recurso vem de fora.

Reporte cada item ✅/❌ antes de corrigir.
Em divergência entre código e material principal, pergunte qual é a fonte da verdade antes de mexer: via de regra o material manda, mas código que evoluiu por bom motivo puxa o material junto.

## Pronto quando

Cada critério das passadas pedidas foi aplicado a cada trecho e a cada slide, e cada item do checklist tem ✅ ou um ❌ justificado.
Reporte, agrupado por passada e critério: achados, correções, a lista explícita de tudo que foi removido (slides pelo título), a contagem de `<section>` antes → depois, o checklist e o que ficou pendente por depender do professor.
