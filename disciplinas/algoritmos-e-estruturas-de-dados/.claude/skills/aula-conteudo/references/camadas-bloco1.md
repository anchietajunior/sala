# Camadas do Bloco 1 (Aprofundamento Progressivo)

Bloco mais importante da aula. **Texto narrativo e extenso, não bullet seco.** As listas só aparecem onde naturalmente cabem (axiomas, propriedades enumeráveis, tabela de complexidade).

A regra de ouro: **a cada camada, o aluno só precisa do que veio nas camadas anteriores**. Termos novos são definidos no primeiro uso.

---

## Camada 1 — Introdução

**Tamanho**: 1 parágrafo curto (3 a 6 frases).

**Objetivo**: dar ao aluno uma imagem mental antes de qualquer terminologia.

**Estilo**: completamente coloquial, sem jargão. Tipo:

- "Imagine uma pilha de bandejas no balcão..."
- "Pense em uma fila do banco..."
- "Pense num caderno onde você anota..."

**Checklist**:

- [ ] Nenhum termo técnico (LIFO, FIFO, ponteiro, axioma, complexidade) é mencionado.
- [ ] Há uma analogia concreta ou cenário familiar.
- [ ] Termina apontando a propriedade essencial — em prosa, não em nome técnico ("a última coisa a entrar é a primeira a sair", não ainda "LIFO").

---

## Camada 2 — Definição informal com vocabulário básico

**Tamanho**: 2 a 4 parágrafos.

**Objetivo**: dar o nome técnico do que foi descrito na camada 1, introduzindo só os termos **estritamente necessários** para nomeá-lo.

**Checklist**:

- [ ] Define o nome canônico da estrutura/algoritmo, com tradução em inglês entre parênteses (`Pilha (stack)`, `Fila (queue)`, `quicksort`).
- [ ] Define a política/regra de acesso pelo nome técnico (LIFO, FIFO, divisão-e-conquista) na **primeira ocorrência**.
- [ ] Lista as **operações principais** com nome canônico em português + tradução em inglês entre parênteses:
  - `empilhar (push)`, `desempilhar (pop)`
  - `enfileirar (enqueue)`, `desenfileirar (dequeue)`
- [ ] Cita inline a bibliografia base (`Tenenbaum, cap. X`; `Sedgewick, Parte Y, cap. Z`).
- [ ] Encerra com a frase canônica `Note o que a <Estrutura> **não** oferece: ...` listando 2–3 operações que a estrutura **proíbe** — destacando que a restrição é a feature.

---

## Camada 3 — Propriedades e comportamento

**Tamanho**: vários parágrafos, com **listas e sub-headings (`####`)** onde fizer sentido.

**Objetivo**: descrever **como** a estrutura/algoritmo se comporta, ainda em prosa narrativa, sem formalismo simbólico pesado.

Sub-seções típicas:

### `#### Ponte com aula anterior` (opcional, mas comum)

Para aulas de estruturas encadeadas: retomar o **nó** apresentado na Aula 02 em 1–2 parágrafos, deixando claro que o nó não muda — o que muda é a política de acesso ou o estado externo.

### `#### Os ponteiros / variáveis de estado externo`

Descrever o estado interno mínimo (`topo`, `inicio`+`fim`, `raiz`, etc.) e **por que** ele é assim. Justificar com base em desempenho — sem invocar conceitos de SO/arquitetura proibidos pelo `CLAUDE.md`.

### `#### As operações em detalhe`

Bullet list com cada operação. Para cada uma:

- O que ela faz, passo a passo (sem código C ainda — é prosa).
- **Custo entre parênteses**: `Custo: **O(1)**.`
- Armadilhas conhecidas, em frases completas (ex.: "Atenção à ordem: primeiro atualizar `topo`, só depois chamar `free` — inverter cria um ponteiro suspenso (*dangling pointer*).").

### `#### Invariantes (propriedades que devem sempre valer)`

Lista em prosa, **sem rótulos abreviados (I1, I2)** — escrever frases completas:

- ✅ "Quando a fila está vazia, `inicio` e `fim` são ambos `NULL` ao mesmo tempo."
- ❌ "I1: vazia ⇒ inicio = fim = NULL"

---

## Camada 4 — Definição formal e notação

**Tamanho**: parágrafos + bloco de definição em fence simples.

**Objetivo**: rigor — TAD, axiomas, tupla de definição.

### `#### O TAD <Nome>`

Definir o TAD em bloco de código simples (fence sem linguagem):

```
TAD <Nome> de Inteiros

  Tipos:
    <Nome>
    Inteiro
    Booleano

  Operações:
    criar()                       -> <Nome>
    inserir(<Nome>, Inteiro)      -> <Nome>
    remover(<Nome>)               -> <Nome>     [erro se vazia]
    consultar(<Nome>)             -> Inteiro    [erro se vazia]
    vazia(<Nome>)                 -> Booleano

  Axiomas (para qualquer <nome> N, inteiro x):
    A1. ...
    A2. ...
```

Após o bloco, **explicar pelo menos 1 axioma "coração"** em prosa — qual deles captura a essência da estrutura (ex.: A4 da Pilha é o LIFO; A6 da Fila é o FIFO).

### `#### A representação interna como tupla`

Quando a aula tem código C (implementação), descrever a tupla matemática da representação:

`P = (N, valor, proximo, topo)`

E listar cada componente em bullet com **explicação por extenso**:

- **N** é o conjunto (possivelmente vazio) dos nós da pilha.
- **valor: N → V** associa cada nó a um inteiro.
- **proximo: N → N ∪ {NULL}** associa cada nó ao seguinte (mais perto do fundo).
- **topo ∈ N ∪ {NULL}** é o ponteiro externo para o último elemento empilhado.

Encerrar com a frase de fechamento que liga estado lógico a estado físico: "A invariante `vazia ⇔ topo = NULL` liga formalmente o estado lógico da pilha ao estado físico do ponteiro."

---

## Camada 5 — Análise de complexidade

**Tamanho**: 1 a 3 parágrafos + tabela.

**Objetivo**: complexidade de cada operação em **O(·)**, comparação entre representações quando relevante.

### A tabela canônica

| Operação    | Vetor com `topo`-índice | Lista encadeada com `topo` |
|-------------|--------------------------|-----------------------------|
| `empilhar`  | O(1)*                    | **O(1)**                    |
| `desempilhar` | O(1)                   | **O(1)**                    |
| `topo`      | O(1)                     | **O(1)**                    |
| `vazia`     | O(1)                     | **O(1)**                    |

A representação **escolhida pela aula** vai em **negrito** na coluna correspondente.

Marcar com `*` (ou similar) custos amortizados, e explicar a nota abaixo da tabela em itálico.

### Comparação entre alternativas

Em 1–2 parágrafos após a tabela, justificar a escolha da representação implementada **em termos do que o aluno já viu**:

- ✅ "O vetor faz uma única alocação (mais econômico em memória) mas tem capacidade fixa ou paga `realloc`."
- ✅ "A lista encadeada paga 8 bytes de ponteiro por nó e exige uma chamada a `malloc` por elemento empilhado."
- ❌ "A lista tem pior localidade de cache." ← proibido pelo `CLAUDE.md` numa aula introdutória.

---

## Camada 6 — Conexões e variantes

**Tamanho**: lista de bullets + parágrafo final opcional.

**Objetivo**: mostrar onde a estrutura aparece no mundo real e quais variantes existem.

### Lista de conexões

5 a 7 bullets curtos, cada um nomeando uma aplicação real:

- **Pilha de chamadas** que toda linguagem mantém durante a execução.
- **Histórico de "desfazer"** (Ctrl+Z) em editores e IDEs.
- **Histórico de navegação** ("voltar") em browsers.
- **Avaliação de expressões com parênteses**.
- **Algoritmos recursivos transformados em iterativos**.

### Variantes da própria estrutura

Parágrafo final listando 2–3 variantes principais (vetor × lista, dupla × simples, circular × linear) — apenas **sinalizando** que existem e o que motivaria escolher uma. Não desenvolver aqui.

Encerrar (opcional) apontando para uma **aula futura** que dependerá desta ("aparece naturalmente em aulas futuras quando estudarmos travessia de grafos e árvores").
