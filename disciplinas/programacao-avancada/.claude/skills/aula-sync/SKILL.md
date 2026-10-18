---
name: aula-sync
description: Verifica e mantém o alinhamento entre os artefatos de uma aula da disciplina Programação Avançada — roteiro, slides, branch do projeto e README. Use quando o usuário pedir para sincronizar, conferir ou fechar uma aula (ex. "sincroniza a aula 04", "confere se a branch bate com o roteiro", "atualiza o README").
---

# Sincronização aula ↔ projeto

Confere que os quatro artefatos de uma aula contam a mesma história, e conserta o que divergir. Rode ao fechar cada aula.

## Os quatro artefatos

Para a aula NN:

1. **Roteiro** — `aulas/aula-NN/roteiro.html`
2. **Slides** — `projeto/slides/aula-NN/slides.html`
3. **Branch** — `aula-NN-slug-do-titulo` em `projeto/` (git)
4. **README** — `projeto/README.md`, que evolui a cada aula

## Checklist de verificação

Execute na ordem e reporte cada item como ✅/❌ antes de corrigir qualquer coisa:

- [ ] A branch `aula-NN-...` existe e o slug bate com o título do roteiro.
- [ ] `git diff aula-(NN-1)... aula-NN... -- backend frontend` contém exatamente o que o live-coding do roteiro constrói — nem código a mais (não ensinado), nem passo do roteiro sem código correspondente.
- [ ] `projeto/slides/` está idêntico em todas as branches (`git diff main aula-NN... -- slides` vazio) — os slides são replicados por cherry-pick, não pertencem a uma aula só.
- [ ] Slides e roteiro cobrem os mesmos tópicos na mesma ordem; trechos de código dos slides existem no código real.
- [ ] **Aula autocontida** (`docs/convencoes.md`): roteiro e slides não citam outras aulas. Grepe por `aula 0`, `aula 1`, `próxima aula`, `aula anterior`, `vimos na`, `semana que vem` — fora do cabeçalho operacional do roteiro e da bibliografia, cada ocorrência é um defeito. Sem seção "onde paramos" e sem gancho para a aula seguinte; consequências futuras justificadas por mérito técnico, não por calendário.
- [ ] Diagramas dos slides são `<img>` locais (`projeto/slides/aula-NN/img/*.png`, com fonte `.svg` ao lado) — nenhum SVG inline nem recurso externo.
- [ ] Blocos e instruções do código têm comentário explicativo imediatamente acima (em pt-BR).
- [ ] Código todo em inglês (comentários didáticos em pt-BR); termos do domínio conforme `CONTEXT.md`.
- [ ] Branch `aula-NN-...` pushada para `origin` (nenhum commit "ahead" em `git branch -vv`).
- [ ] Decisões dos ADRs (`docs/adr/`) respeitadas (ex. ADR-0001: nada de auth antes da aula de JWT).
- [ ] `projeto/README.md` reflete o estado **até esta aula**: como rodar backend/frontend (comandos Mac e Windows), tabela de endpoints existentes, variáveis de ambiente, estrutura de pastas.
- [ ] `projeto/README.md` escrito em **pt-BR** (só o código e os comandos ficam em inglês).
- [ ] README contém a **Tabela de Dependências** (colunas `Nome | Utilidade | Versão`) batendo com o `requirements.txt`: mesmas entradas, mesmas versões, na mesma ordem do arquivo. Dependência entrou/saiu/mudou de versão → a tabela acompanha.
- [ ] `docs/plano-de-aulas.md` ainda descreve o que a aula realmente ficou — se o conteúdo derrapou, atualize o plano (ou aponte a divergência ao usuário se for mudança de escopo).

## Correções

- Divergência de **código vs roteiro**: pergunte qual é a fonte da verdade antes de mexer — via de regra o roteiro manda, mas código que evoluiu por bom motivo deve puxar o roteiro junto.
- **README**: reescreva a seção desatualizada; o README nunca menciona aulas futuras.
- Ao final, resuma o que foi verificado, o que foi corrigido e o que ficou pendente.
