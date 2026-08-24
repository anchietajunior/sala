# Bloco de Exercícios

**3 a 5 exercícios**, em ordem crescente de dificuldade. **Não rotular** com "fácil/médio/difícil" — a progressão fica implícita pela ordem.

**Apenas 1 desafio por aula**, sempre o **último exercício**. Não criar múltiplos exercícios "de desafio".

## Progressão típica (5 exercícios)

| # | Tipo                         | O que pede                                                                                          |
|---|------------------------------|-----------------------------------------------------------------------------------------------------|
| 1 | Trace na mão                 | Executar a sequência de operações sobre estado inicial, escrever estado e retornos a cada passo.    |
| 2 | Adicionar uma função simples | Implementar uma operação derivada (ex.: `pilha_imprimir`, `fila_tamanho`) no `.c` da aula.          |
| 3 | Aplicar a um cenário real    | Resolver um sub-problema usando a estrutura (validação de parênteses, inversão de string com pilha).|
| 4 | Variação na estrutura        | Modificar uma operação para um caso especial (ex.: pilha com limite de capacidade, fila circular).  |
| 5 | **Desafio**                  | Extensão ampla — combinar estruturas ou exigir raciocínio mais profundo, sempre com o que a própria aula deu. |

Para aulas conceituais (sem código C), o **Exercício 1** costuma ser identificar o conceito no cotidiano, e os do meio são aplicação de axiomas / escrita de TAD curto. O desafio final pode ser "escreva um TAD para X" ou "prove por axiomas que Y".

## Formato canônico de cada exercício

```markdown
**Exercício N — <Título curto descritivo>.**
<Enunciado claro, 1–3 parágrafos. Sem ambiguidade.>

*Critério de aceitação*: <condição de sucesso, entrada/saída esperadas, ou estado final esperado.>

> **Resposta mínima aceitável**
>
> <Resposta direta, OU tabela, OU código mínimo em fence ` ```c `>
```

A "Resposta mínima aceitável" é **explícita e rotulada**, e serve como gabarito para o professor + auto-conferência para o aluno após tentar. Em uma apresentação Reveal.js, ela vira fragmento (`class="fragment fade-in"`) revelado por clique.

## Forma da resposta mínima

**Exercícios objetivos** (cálculos, classificações, aplicação de axiomas): resposta direta + 1 linha citando o axioma/critério aplicado.

Exemplo:

```markdown
> **Resposta mínima aceitável**
>
> | Operação          | Estado (topo → base) | Retorno |
> |-------------------|----------------------|---------|
> | `empilhar(7)`     | `[7]`                | —       |
> | `empilhar(3)`     | `[3, 7]`             | —       |
> | `desempilhar`     | `[7]`                | `3`     |
>
> Aplicação direta do axioma A4 (`desempilhar(empilhar(P, x)) = P`).
```

**Exercícios abertos** (especificar um TAD, escrever axiomas, implementar uma função): resposta-exemplo **enxuta** — operações com assinaturas e o conjunto mínimo de axiomas que satisfazem o critério. **Não é a única resposta válida**; é o gabarito de mínimo aceitável.

Exemplo:

```markdown
> **Resposta mínima aceitável**
>
> ```c
> void pilha_imprimir(Pilha* p) {
>     printf("[");
>     No* atual = p->topo;
>     while (atual != NULL) {
>         printf("%d", atual->valor);
>         if (atual->proximo != NULL) printf(", ");
>         atual = atual->proximo;
>     }
>     printf("]\n");
> }
> ```
>
> Percurso a partir de `topo` na direção do `proximo` — ordem topo → base.
```

## Estilo dos enunciados

- **Verbo no imperativo** ou substantivado: "Considere uma pilha vazia...", "Adicione ao `pilha.c` uma função...", "Implemente...".
- **Concreto**: dar valores específicos (`7, 3, 11, 5`), não variáveis abstratas (`x, y, z`).
- **Sem ambiguidade**: se o exercício pede uma saída específica, mostrar o formato exato (`[30, 20, 10]`, não "imprima os elementos").
- **Dica opcional** em uma frase, somente quando o exercício for médio/desafio.

## Limites

- **Mínimo 3, máximo 5** exercícios por aula. Mais que 5 dilui; menos que 3 deixa o aluno sem prática suficiente.
- **Apenas 1 desafio**, sempre o último.
- **Ao menos 1 exercício de prática de algoritmo** por aula, sem exceção: em aula de implementação, implementar ou modificar uma função no `.c`; em aula conceitual, executar um algoritmo passo a passo na mão (trace com valores concretos).
- Em aulas conceituais, exercícios são **conceituais** — não pedem código C. Quando um exercício precisar de notação formal/axiomas para funcionar, **inlinear** o conteúdo no próprio enunciado (não remeter de volta ao bloco 1).
