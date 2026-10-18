# Paleta institucional, tipografia e estilos

A disciplina tem identidade visual única, aplicada de forma consistente em **todos** os SVGs e em **todos** os slides. Mudanças à paleta requerem pedido explícito.

## Paleta

| Uso                                                                            | Cor       |
|--------------------------------------------------------------------------------|-----------|
| Primária — caixas em destaque, títulos, setas-chave                            | `#2c5d8a` |
| Secundária — texto auxiliar, setas neutras                                     | `#5a7a9a` |
| Borda neutra — caixas secundárias                                              | `#cfd6dd` |
| Fundo de caixa neutro                                                          | `#f7f9fc` |
| Fundo de caixa em destaque (interface, nós, células ocupadas)                  | `#e8f0f8` |
| Texto principal                                                                | `#222`    |
| Texto pálido — índices, NULL, anotações                                        | `#888`    |
| Cabeçalho de tabela                                                            | `#f0f4f8` |

## Tipografia

- **Texto geral**: `system-ui, -apple-system, "Segoe UI", Roboto, sans-serif`.
- **Monoespaçada (identificadores, valores, código)**: `ui-monospace, "SF Mono", Menlo, Consolas, monospace`.
- **Tamanho mínimo em SVG**: 14px (projeção precisa ler).
- **Padding interno em caixas**: ≥ 12px.

## SVG do bloco 2 — gabarito

Atributos do elemento raiz:

```xml
<svg xmlns="http://www.w3.org/2000/svg"
     viewBox="0 0 700 ALTURA"
     font-family="system-ui, -apple-system, 'Segoe UI', Roboto, sans-serif">
```

**Altura do viewBox** varia conforme o conteúdo:

- Estrutura vazia: `220`.
- 1 nó: `260`.
- 2 nós verticais (pilha pequena): `360`.
- 2–3 nós horizontais (fila/lista): `220` ou `260`.
- 3–4 nós verticais: `460–520`.

### Título do passo

```xml
<text x="350" y="40" text-anchor="middle"
      font-size="18" font-weight="600" fill="#2c5d8a">
  Passo N — operacao(args)
</text>
```

### Rótulo de ponteiro externo (topo, inicio, fim, raiz)

```xml
<text x="200" y="115" text-anchor="end"
      font-size="14" font-weight="600" fill="#2c5d8a">topo →</text>
```

### Caixa de nó (120×60, dividida ao meio)

```xml
<!-- borda + fundo da caixa -->
<rect x="215" y="100" width="120" height="60"
      fill="#e8f0f8" stroke="#2c5d8a" stroke-width="2.5" rx="4"/>
<!-- divisao interna entre 'valor' e 'proximo' -->
<line x1="295" y1="100" x2="295" y2="160" stroke="#2c5d8a" stroke-width="2"/>
<!-- valor monoespacado -->
<text x="255" y="138" text-anchor="middle"
      font-size="22" fill="#222"
      font-family="ui-monospace, 'SF Mono', Menlo, Consolas, monospace">10</text>
<!-- bolinha do ponteiro (se aponta para algo) -->
<circle cx="315" cy="130" r="3.5" fill="#2c5d8a"/>
<!-- OU símbolo de NULL (se o ponteiro é nulo) -->
<text x="315" y="138" text-anchor="middle" font-size="14" fill="#888">∅</text>
```

`stroke-width="2.5"` no nó **em destaque** (geralmente o novo nó ou o que está sendo lido); `stroke-width="2"` nos demais.

### Seta entre nós

Horizontal:

```xml
<path d="M 335 130 L 415 130" fill="none" stroke="#2c5d8a" stroke-width="2.5"/>
<polygon points="410,125 423,130 410,135" fill="#2c5d8a"/>
```

Vertical (descendo, pilha):

```xml
<path d="M 315 165 Q 315 200, 275 200 L 275 220" fill="none" stroke="#2c5d8a" stroke-width="2.5"/>
<polygon points="270,215 275,228 280,215" fill="#2c5d8a"/>
```

### NULL/fim de cadeia

Em texto cinza claro à direita do último nó ou abaixo dele:

```xml
<text x="355" y="138" font-size="13" fill="#888" font-style="italic">(NULL — fim)</text>
```

ou simbolicamente `∅` dentro da própria caixa.

### Nota de rodapé do SVG

Linha cinza separadora + texto cinza azulado em itálico:

```xml
<line x1="100" y1="315" x2="600" y2="315" stroke="#cfd6dd" stroke-width="1"/>
<text x="350" y="340" text-anchor="middle"
      font-size="13" fill="#5a7a9a" font-style="italic">
  o antigo topo "afunda" um nível · o novo nó é o topo
</text>
```

### Destaque em operação de leitura (Passo "consultar")

A operação de consulta NÃO altera a estrutura — mas o diagrama precisa **indicar** que ela está lendo o nó do topo/frente. Convenção: caixa pontilhada/asteriscos ao redor do valor, com seta tracejada de "olho":

```xml
<!-- caixa de leitura: tracejada -->
<rect x="215" y="100" width="120" height="60"
      fill="none" stroke="#2c5d8a" stroke-width="2.5"
      stroke-dasharray="6,4" rx="4"/>
```

### Destaque em operação de remoção

Convenção: o nó removido aparece com **fundo claro #f7f9fc** + **stroke tracejado cinza #cfd6dd** + texto cinza pálido + uma marca "x" pequena, sinalizando que foi liberado.

## Estilos das slides (CSS embutido no `apresentacao.html`)

O `<style>` que vai no `<head>` está copiado integralmente em `templates/apresentacao.html.template`. Pontos-chave:

- `:root` define `--cor-destaque: #2c5d8a` e `--cor-suave: #5a7a9a`.
- `h1, h2, h3, h4` em `var(--cor-destaque)`, sem `text-transform`.
- `.capa h1` 2.4em; `.capa h2` 1.4em com `var(--cor-suave)`.
- `.diagrama` (para `<img>` de SVG): max-width 100%, max-height 500–540px, centralizado.
- `.resposta` (caixa do gabarito do exercício): borda-esquerda 3px destaque, fundo `#f7f9fc`, texto-alinhamento à esquerda.
- `.destaque`: cor destaque + peso 600.
- `.nota-rodape`: 0.55em, itálico, cinza.
- `blockquote`: fundo `#f7f9fc`, borda-esquerda 4px destaque.
- `.titulo-bloco`: 0.5em, maiúsculas, cor suave (rótulo `Bloco N` / `Camada N`).
- `.duas-colunas`: flex com gap, alinhado-à-esquerda.

## O que não fazer

- **Não** usar Mermaid em apresentações Reveal.js — sempre SVG.
- **Não** usar PNG/JPG em diagramas técnicos (só em ilustrações de analogia, e mesmo assim só se o usuário pedir).
- **Não** carregar fonte externa (Google Fonts, etc.) — usar a stack de fontes do sistema.
- **Não** mudar a paleta. Se um diagrama pedir uma cor extra (ex.: vermelho para "erro"), use vermelho médio sóbrio compatível (`#b54040`) e documente o uso.
- **Não** usar tema escuro. A disciplina usa `white`.
- **Não** carregar de CDN — vendor sempre local em `../assets/vendor/`.
