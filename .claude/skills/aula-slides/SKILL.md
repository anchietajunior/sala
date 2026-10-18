---
name: aula-slides
description: Gera a apresentação Reveal.js de uma aula de qualquer disciplina do repositório a partir do material principal já escrito, com os diagramas da aula e o vendor local. Use quando o professor pedir slides ou apresentação de uma aula ("slides da aula 08", "monte a apresentação da aula sobre fila").
---

# Slides da aula

Monta o deck projetado em sala a partir do material principal da aula.
O material principal é a fonte: quando os slides precisarem de algo que ele não tem, ajuste-o primeiro com a skill `aula-conteudo`.

## Antes de escrever

1. Leia o perfil `disciplinas/<disciplina>/CLAUDE.md` e o `CLAUDE.md` da raiz.
2. Leia o material principal da aula inteiro.
3. Leia tudo o que a seção **Slides** do perfil manda ler: referências em `references/<disciplina>/`, templates em `templates/<disciplina>/` e a bibliografia da disciplina.
4. Confira que o vendor do Reveal.js existe onde o perfil diz. Se faltar, avise e pare: as bibliotecas vêm só do vendor local.

## Montar

- Percorra o material principal na mesma ordem. **Uma ideia por slide**: um parágrafo denso quase sempre vira dois ou três slides.
- Produza os diagramas que faltam, no formato e no estilo do perfil.
- Trechos de código são curtos e extraídos do código real da aula; dentro de `<pre><code>`, escape `<`, `>` e `&`.
- Feche com o slide de Referências no formato do perfil.

## Pronto quando

- Todo `src` e `href` local referenciado existe; todo SVG novo passa em `xmllint --noout`.
- Scripts, estilos e imagens vêm só de caminhos locais; `http(s)://` aparece apenas em links de texto, como o repositório na capa.
- Os itens de slides da seção **Consistência** do perfil estão ✅.

Reporte: arquivo gerado, diagramas criados (e quantos já existiam), contagem de slides e o comando para abrir (`open <caminho>` no macOS).
