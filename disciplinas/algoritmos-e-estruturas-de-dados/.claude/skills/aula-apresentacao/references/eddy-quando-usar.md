# Eddy — quando e como usar

Eddy é o mascote-assistente da disciplina. Aparece em **slides dedicados** trazendo citações da bibliografia, curiosidades históricas, exemplos de aplicação ou dicas de armadilha. Slide dedicado é **inegociável** — cartão flutuante sobre outro slide é proibido porque sempre acaba sobrepondo conteúdo do slide vizinho.

## Quantidade por aula

- **3 a 4 aparições** por aula (raramente 5).
- **Aproximadamente 1 a cada 5–8 slides** — não amontoar.
- Em aula curta (≤ 35 slides), 2–3 aparições já bastam.

## Onde usar — checklist por bloco

| Bloco                    | Usar Eddy? | O quê                                                |
|--------------------------|------------|------------------------------------------------------|
| Bloco 1, Camada 2 ou 4   | **Sim**    | Citação inline da bibliografia (Cormen primeiro; Backes, Veloso & Pereira) |
| Bloco 1, Camada 6        | Opcional   | Nomeia um tema da computação onde o conceito reaparece (nunca "na próxima aula") |
| Bloco 3                  | **Sim**    | Exemplo de aplicação real ou curiosidade histórica   |
| Bloco 4 (código C)       | **Sim**    | Armadilha comum específica do trecho exibido          |

## Estrutura HTML padrão

```html
<section class="eddy-slide">
    <div class="eddy-card">
        <div class="eddy-avatar">
            <img src="../assets/bot/eddy.svg" alt="Eddy">
        </div>
        <div class="eddy-balao">
            <strong class="eddy-nome">Eddy</strong>
            <p class="eddy-fala">
                Turma, <conteúdo da fala>.
                <cite>Fonte (opcional)</cite>
            </p>
        </div>
    </div>
</section>
```

Para falas mais longas (citação com vários autores, lista de aplicações), trocar `eddy-card` por `eddy-card eddy-card--longo`:

```html
<div class="eddy-card eddy-card--longo">
```

## Regras do conteúdo da fala

- **Sempre começa com "Turma,"**.
- **Até 3–4 frases**. Slide é uma pausa, não uma palestra.
- **Cita fonte quando houver**. Formato `<cite>Backes, cap. X — Nome</cite>` ou `<cite>Veloso & Pereira, cap. Y</cite>`. Bibliografia da ementa no `CLAUDE.md`.
- **Não inventar fatos históricos**. Se não houver certeza sobre data/autor, omitir o detalhe ou dizer apenas "proposto na década de X". Datas como "1959", "Dijkstra em Amsterdã" são bem-vindas **só se forem corretas e verificáveis**.
- **Mesmas regras de linguagem** da disciplina: PT-BR com acentuação correta, sem coloquialismo nem jargão, sem siglas locais (RU, DCE).

## Exemplos por categoria

### Citação da bibliografia

```html
<p class="eddy-fala">
    Turma, segundo Veloso e Pereira, é justamente o axioma
    <code>desempilhar(empilhar(P, x)) = P</code> que define
    o comportamento LIFO de forma puramente algébrica,
    sem precisar falar em ponteiros ou memória.
    <cite>Veloso &amp; Pereira, capítulo de Pilhas</cite>
</p>
```

### Curiosidade histórica

```html
<p class="eddy-fala">
    Turma, o termo <em>pushdown stack</em>, comum na literatura clássica,
    vem dos anos 1950, da mesma época em que se começou a estudar
    formalmente compiladores — não é coincidência que a pilha apareça
    em todo lugar nessa área.
</p>
```

### Exemplo de aplicação real

```html
<p class="eddy-fala">
    Turma, o erro de <em>stack overflow</em> (estouro da pilha de chamadas)
    ocorre exatamente com <strong>essa</strong> pilha: cada chamada empilha
    um registro de ativação (<em>frame</em>), e quando há
    recursão sem caso base a pilha cresce sem parar até esgotar a
    região de memória reservada para ela.
</p>
```

### Dica de armadilha (bloco 4)

```html
<p class="eddy-fala">
    Turma, atenção à <strong>ordem</strong> em <code>desempilhar</code>:
    primeiro salvamos <code>removido-&gt;proximo</code> em <code>topo</code>,
    <strong>e só depois</strong> chamamos <code>free</code>.
    Inverter essa ordem deixa <code>topo</code> apontando para memória
    que acabou de ser liberada — um <em>ponteiro suspenso</em>.
</p>
```

## O que NÃO fazer

- **Não** colocar Eddy num cartão flutuante sobre outro slide. Slide dedicado, sempre.
- **Não** colocar 2 Eddys seguidos sem conteúdo entre eles.
- **Não** colocar Eddy no slide de capa/encerramento.
- **Não** colocar Eddy explicando o que já está perfeitamente claro no slide anterior — ele agrega contexto externo (citação, história, aplicação, dica), não repete o conteúdo da aula.
