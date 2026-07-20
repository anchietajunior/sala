# Os quatro critérios de revisão — heurísticas e exemplos

Cada eixo abaixo tem: **o que procurar**, **como corrigir** e um par **ruim → bom**. Os exemplos usam o domínio da disciplina (algoritmos, C, estruturas).

---

## 1. Ambiguidade

**O que procurar**

- Pronomes e demonstrativos sem antecedente único: `isso`, `ele`, `ela`, `essa`, `o mesmo`. A que exatamente se referem?
- Frases que admitem duas leituras.
- Critérios e enunciados vagos: "rápido", "grande", "melhor" sem referência ("melhor em quê?").
- Referências posicionais frágeis: "o primeiro", "o de cima", "aquele" quando há mais de um candidato.

**Como corrigir**: reescrever para uma leitura única — troque o pronome pelo referente, quantifique o vago, desdobre a frase em duas se ela carrega duas leituras.

**Ruim**

> A lista encadeada é mais eficiente que o vetor, então use ela quando puder.

*(Eficiente em quê? "ela" = a lista? "quando puder" = quando?)*

**Bom**

> Inserir no início de uma lista encadeada custa O(1); no vetor, custa O(n), porque todos os elementos seguintes precisam ser deslocados. Quando as inserções acontecem sobretudo no início, a lista encadeada é preferível.

---

## 2. Itens sem explicação clara

**O que procurar** (isto faz cumprir a regra "não supor conhecimento prévio" do `CLAUDE.md`)

- Termo técnico usado **antes** de ser definido — ou nunca definido.
- Conceito citado de passagem como se o aluno já o conhecesse, sem ser dependência retomada de aula anterior.
- Salto de raciocínio: uma conclusão que não decorre visivelmente do que veio antes ("logo...", "portanto..." sem o passo do meio).
- Sigla ou notação apresentada sem expansão no primeiro uso.

**Como corrigir**: a ação **padrão é adicionar a explicação que falta**, definindo o termo no primeiro uso — **não** apagar o termo (o `CLAUDE.md` exige que ele apareça e seja definido). Só **remover** o item quando ele não serve a nenhum objetivo da aula.

**Ruim**

> A busca binária tem custo logarítmico, ao contrário da complexidade amortizada do vetor dinâmico.

*("logarítmico", "amortizada", "vetor dinâmico" caem sem definição na aula de abertura.)*

**Bom**

> A busca binária descarta metade dos candidatos a cada passo — para um milhão de itens, cerca de vinte passos bastam. Esse ritmo, em que dobrar a entrada custa só **um** passo a mais, tem nome: **crescimento logarítmico**.

---

## 3. Contexto excessivo

**O que procurar**

- Parágrafo que não serve ao objetivo do bloco onde está.
- Digressão histórica, curiosidade ou tangente que não paga seu custo de atenção.
- Repetição do que já foi dito com outras palavras.
- Frase ou oração que pode sair inteira sem que a explicação perca nada.
- Detalhe que pertence a uma aula futura e só antecipa confusão aqui.

**Como corrigir**: **cortar**. A remoção é a ação certa — prefira deletar a digressão inteira a encolhê-la pela metade (uma meia-digressão ainda desvia, e agora sem completar o raciocínio). Curiosidade histórica que valha a pausa cabe melhor numa fala do Eddy, na apresentação — não no corpo do texto.

**Ruim**

> A pilha segue a política LIFO. Vale lembrar que a palavra "pilha" também aparece em eletrônica (uma pilha AA), em geologia (pilhas de sedimento) e no dia a dia (uma pilha de roupa) — mas aqui o sentido é o de estrutura de dados. Voltando: LIFO significa...

**Bom**

> A pilha segue a política LIFO: o último elemento a entrar é o primeiro a sair.

---

## 4. Conexão lógica

**O que procurar**

- Um tópico que aparece **sem ponte** com o anterior — o texto pula de um assunto a outro e o aluno não vê o elo.
- Ordem que atrapalha: um tópico que depende de outro apresentado só depois.

**A distinção que importa: desconexão (defeito) × novo assunto (legítimo).**

Antes de marcar uma quebra como defeito, faça **três perguntas**:

1. **É consequência, detalhamento ou contraste do tópico anterior?** Se sim e não há ponte → **defeito**: adicione a linha-ponte.
2. **Abre um assunto que a estrutura da aula prevê aqui** — um bloco novo, uma camada nova, uma seção que o roteiro pede? Se sim → **início legítimo**: não force o elo; garanta só a frase de transição ("Com isso na mão, vejamos agora...").
3. **Não é nem continuação nem abertura prevista — surgiu do nada?** → **órfão**: realoque para onde se conecta, ou remova se não tem função na aula.

**Como corrigir**: adicionar a ponte; mover o tópico para junto do que se liga a ele; ou remover o órfão. Nunca "conectar" à força dois assuntos que não têm relação — se um novo assunto começa, o certo é anunciá-lo como novo, não fingir que decorre do anterior.

**Ruim (desconexão real)**

> ...e é por isso que o algoritmo das duas pontas gasta menos memória.
>
> Um vetor tem tamanho fixo, definido na criação.

*(O segundo parágrafo cai sem elo. O fato sobre vetor é relevante, mas precisa de ponte — ou de ser realocado para junto da apresentação do vetor.)*

**Bom (ponte adicionada)**

> ...e é por isso que o algoritmo das duas pontas gasta menos memória.
>
> Repare que ele só funciona porque a palavra está num vetor, que dá acesso direto à última posição. E é hora de olhar esse vetor de perto: um vetor tem tamanho fixo, definido na criação...

**Bom (novo assunto legítimo — não é defeito)**

> ## 3. Problema Motivador
>
> *"Como uma IA gera cada palavra da resposta em fração de segundo?"*

*(Novo bloco. Não precisa "decorrer" do bloco 2 — é uma virada prevista pela estrutura. Basta ser anunciado como tal.)*

---

## Ordem de aplicação

Numa passagem só, para cada trecho, rode os quatro na ordem: **ambiguidade → explicação → excesso → conexão**. Motivo prático: cortar excesso (3) antes de avaliar conexão (4) evita "consertar a ponte" de um parágrafo que ia ser removido de qualquer forma.
