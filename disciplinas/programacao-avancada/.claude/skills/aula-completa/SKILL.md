---
name: aula-completa
description: Executa o fluxo completo de uma aula da disciplina Programação Avançada em um único comando — roteiro do professor, código na branch do projeto e slides do aluno, fechando com o checklist de sincronização. Use quando o usuário pedir a aula inteira (ex. "cria a aula 02", "monta a aula 05", "faz a aula 03 completa").
---

# Aula completa (roteiro → branch → slides → sync)

Orquestra as skills do projeto na ordem canônica de `como-criar-uma-aula.html`. Em cada etapa, leia o `SKILL.md` da skill correspondente e execute-o como se ela tivesse sido invocada — as regras de cada artefato vivem lá, não aqui.

## Etapas

1. **Escopo** — localize a aula NN em `docs/plano-de-aulas.md`. Se a aula não existir no plano, pare e avise.
2. **Roteiro** — execute `.claude/skills/aula-roteiro/SKILL.md` → gera `aulas/aula-NN/roteiro.html`.
3. **Branch e código** — em `projeto/`:
   - Primeira aula (ainda sem repositório): `git init`, commit vazio `start of the course project`, `git branch -M main`.
   - Crie a branch `aula-NN-slug` a partir da branch da aula anterior (na aula 01, a partir de `main`).
   - Implemente **exatamente** o que o live-coding do roteiro constrói — nem código a mais, nem passo sem código.
   - Comandos do roteiro que produzem arquivos (ex. `pip freeze > requirements.txt`) são executados de verdade, não simulados.
   - Todo bloco ou instrução do código leva um comentário **imediatamente acima**, em pt-BR, explicando o que as instruções fazem (identificadores e strings continuam em inglês).
   - Commite na branch com mensagem em inglês: `aula NN: <o que foi construído>`.
   - Após o commit, faça push automático: `git push -u origin aula-NN-slug` (na primeira aula, push de `main` também). Se o remote `origin` não estiver configurado, avise o professor em vez de criar um repositório.
4. **Slides** — execute `.claude/skills/aula-slides/SKILL.md` → gera `projeto/slides/aula-NN/slides.html`.
   - Commite os slides sozinhos (`slides: aula NN`) e replique em todas as branches do projeto com `git cherry-pick -x <sha>`, para que o aluno veja o material completo em qualquer aula. Push de cada branch tocada.
5. **Sync** — execute `.claude/skills/aula-sync/SKILL.md` e reporte o checklist ✅/❌.

## Regras

- Ordem fixa: roteiro → código → slides → sync. Slides derivam do roteiro; o sync confere tudo.
- **Aula autocontida** (`docs/convencoes.md`): a aula NN parte do código da aula NN−1, mas o material não menciona nenhuma outra aula — sem retomada, sem gancho, sem número de aula no texto. Vale para roteiro e slides.
- ADRs em `docs/adr/` valem em todas as etapas.
- Não deixe servidores rodando em foreground; valide o código com uma chamada rápida (ex. `python -c "import main"` ou TestClient) e derrube o que subir.
- Pare e pergunte apenas se o pedido divergir do plano (mudança de escopo é decisão do professor).
