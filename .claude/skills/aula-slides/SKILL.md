---
name: aula-slides
description: Escreve ou altera uma aula de qualquer disciplina do repositório - os slides Reveal.js, única fonte da verdade da aula, com os diagramas e o código que eles mostram. Use quando o professor pedir para criar, escrever ou mudar uma aula ou seus slides ("escreva a aula sobre pilha", "slides da aula 09", "acrescenta o login na aula 05").
---

# Aula (slides)

Os slides são a aula inteira: o que não está neles não faz parte da aula.
O código da aula é exatamente o código que os slides mostram e constroem.
O perfil da disciplina diz onde cada artefato fica, o que ler antes e como validar.

## Antes de escrever

1. Identifique a disciplina (pedido ou pasta; em dúvida, pergunte) e leia o perfil `disciplinas/<disciplina>/CLAUDE.md` inteiro e o `CLAUDE.md` da raiz. O perfil vence esta skill em conflito.
2. Aula nova: o número é o próximo disponível em `aulas/`, salvo pedido explícito; aulas existentes mantêm o número. Aula existente: leia os slides inteiros antes de editar.
3. Leia tudo o que a seção **Slides** do perfil manda ler: plano, glossário, código atual, referências em `references/<disciplina>/` e templates em `templates/<disciplina>/` desta skill.
4. Se o perfil classifica aulas por tipo, classifique. Em dúvida real, pergunte antes de produzir; em caso óbvio, decida e diga em uma linha.
5. Confira que o vendor do Reveal.js existe onde o perfil diz. Se faltar, avise e pare: as bibliotecas vêm só do vendor local.

## Escrever

- Siga a estrutura de aula que as referências da disciplina definem; templates são andaime, adaptados a cada aula.
- **Uma ideia por slide**: um parágrafo denso quase sempre vira dois ou três slides.
- Todo conceito de que a aula depende é apresentado nela, com definição e exemplo próprios (aula fechada).
- Diagramas em SVG, no estilo do perfil, na pasta `img/` da aula.
- Escreva o código de verdade, idêntico ao que os slides mostram; dentro de `<pre><code>`, escape `<`, `>` e `&`. Comandos que produzem arquivos (ex.: `pip freeze > requirements.txt`) são executados.
- Atualize os índices e o README que o perfil lista.

## Pronto quando

- Cada bloco ou seção que a estrutura da disciplina exige está presente, na ordem.
- O código foi validado como o perfil pede, e o que subiu foi derrubado.
- Todo `src` e `href` local existe e todo SVG passa em `xmllint --noout`; scripts, estilos e imagens vêm só de caminhos locais (`http(s)://` aparece apenas em links de texto, como o repositório na capa).
- Os itens da seção **Consistência** do perfil estão ✅.

Reporte: arquivos criados ou alterados, diagramas criados, contagem de slides, índices atualizados e o comando para abrir (`open <caminho>` no macOS).
