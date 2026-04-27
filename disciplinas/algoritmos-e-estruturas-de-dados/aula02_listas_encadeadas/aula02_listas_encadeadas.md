# Aula 02 — Listas Encadeadas, FIFO e LIFO, Duplamente Encadeadas e Circulares

> **Tipo desta aula**: conceitual / meta. Apresentamos a **família** das listas encadeadas e os **padrões de acesso** (FIFO, LIFO) que serão usados pelas estruturas concretas das próximas aulas. Implementação em C começa na Aula 03 (Fila) e segue na Aula 04 (Pilha).

---

## 1. Conceito — Nível Profundo

### Lista encadeada, em uma frase

Uma **lista encadeada** é uma sequência linear de elementos em que cada elemento — chamado **nó** — guarda o **valor** que armazena e uma **referência** (em C, um ponteiro) para o próximo nó da sequência. O fim da lista é marcado por uma referência especial, `NULL`, que significa *"não há próximo"* (Tenenbaum, cap. 5, *"Listas em C"*; Sedgewick, *Algoritmos em C*, Parte 1, cap. 3 — *Estruturas de dados elementares*).

A diferença essencial em relação a um vetor é a **fonte da ordem**. No vetor, a ordem dos elementos é dada pela **posição contígua na memória**: o elemento de índice `i+1` está sempre no endereço imediatamente seguinte ao de índice `i`. Na lista encadeada, a ordem é dada **pelas próprias ligações**: cada nó "aponta" para o próximo, e os nós podem estar **espalhados** pela memória em endereços não relacionados.

### Os três ingredientes do nó

Um nó de lista encadeada simples tem **três informações** (representadas em C tipicamente como uma `struct`):

- **Valor** (também chamado *carga útil* ou *payload*): o dado que esse nó está guardando — um inteiro, uma string, uma struct mais complexa.
- **Próximo** (`proximo` ou `prox`): um ponteiro para o nó seguinte da lista, ou `NULL` se este for o último.
- **(Opcional) Anterior** (`anterior` ou `ant`): só existe em listas **duplamente encadeadas** — é um ponteiro para o nó imediatamente anterior, ou `NULL` se este for o primeiro.

A lista inteira é referenciada externamente por **um ou dois ponteiros âncora** (em geral chamados `inicio`, `cabeca`, `head`, `fim`, `tail`) que apontam para os nós das extremidades. Esses ponteiros âncora **não são nós** — são apenas o "endereço de entrada" que permite ao programa achar o primeiro elemento.

### Variantes da família

Toda variante de lista encadeada parte do mesmo princípio (nós + ponteiros) e muda **uma decisão de projeto**: quantos ponteiros cada nó tem e como o último nó se conecta. Tenenbaum (cap. 5) cobre as três variantes em sequência, com diagramas e código para cada uma; Sedgewick (Parte 1, cap. 3) traz a comparação visual entre as variantes em um único diagrama.

- **Lista simplesmente encadeada**. Cada nó tem **um** ponteiro (`proximo`). Percorrer a lista é unidirecional — só do início para o fim. O último nó aponta para `NULL`.
- **Lista duplamente encadeada**. Cada nó tem **dois** ponteiros (`anterior` e `proximo`). Pode-se percorrer nos dois sentidos. Inserções e remoções no meio ficam mais simples — basta o ponteiro do nó alvo. Custo: um ponteiro extra por nó.
- **Lista circular**. O último nó **não** aponta para `NULL`; aponta de volta para o primeiro. A lista vira um anel sem fim explícito. Útil em situações que pedem rotação (escalonamento round-robin de processos, *playlists* em loop). Pode ser circular simples (um ponteiro por nó) ou circular dupla (dois ponteiros por nó). Tenenbaum dedica seção específica às listas circulares no cap. 5.

### Complexidade das operações principais

A análise é feita em termos de **n**, o número de elementos da lista, e usa a notação **O(...)** (lê-se *"ordem de"*) — uma forma de indicar como o tempo cresce com `n`. **O(1)** significa *"tempo constante, não depende de n"*. **O(n)** significa *"tempo proporcional a n"*. A tabela abaixo segue a análise canônica encontrada em CLRS (cap. 10, seção 10.2) e em Tenenbaum (cap. 5).

| Operação                                | Lista simples | Lista dupla | Vetor (para comparação) |
|-----------------------------------------|---------------|-------------|--------------------------|
| Acessar o primeiro elemento              | O(1)          | O(1)        | O(1)                     |
| Acessar o k-ésimo elemento (qualquer k) | O(n)          | O(n)        | O(1)                     |
| Inserir no início                        | O(1)          | O(1)        | O(n) (precisa deslocar)  |
| Inserir no fim (com ponteiro `fim`)     | O(1)          | O(1)        | O(1) (amortizado)        |
| Remover o primeiro                       | O(1)          | O(1)        | O(n) (precisa deslocar)  |
| Remover um nó específico (com ponteiro) | O(n)*         | O(1)        | O(n)                     |

\* Na lista simples, ao remover um nó você precisa do nó **anterior** para "religar" a lista — e achá-lo custa O(n). Na dupla, o nó anterior já é conhecido pelo próprio nó alvo.

A consequência prática: **listas são fortes onde vetores são fracos** (inserir e remover sem custo de deslocamento), e **fracas onde vetores são fortes** (acesso direto por índice).

### FIFO e LIFO — padrões de acesso, não estruturas

Aqui está o ponto que costuma confundir: **FIFO** (*First-In-First-Out*) e **LIFO** (*Last-In-First-Out*) **não são estruturas de dados**. São **padrões de comportamento** — políticas que descrevem **qual elemento sai quando se pede para retirar um**. Tenenbaum dedica capítulos próprios a cada um (cap. 2 — Pilhas, LIFO; cap. 4 — Filas, FIFO), exatamente porque o comportamento é o que define a estrutura.

- **FIFO**: o **primeiro** elemento que entrou é o **primeiro** a sair. É o comportamento da **Fila** (queue). Modela qualquer situação de espera por ordem de chegada.
- **LIFO**: o **último** elemento que entrou é o **primeiro** a sair. É o comportamento da **Pilha** (stack). Modela qualquer situação que precisa "desfazer na ordem inversa" — chamadas de função, Ctrl+Z, navegação para trás.

Como a Aula 01 já estabeleceu, o **TAD** (o contrato) descreve esses comportamentos via axiomas. A lista encadeada é uma das **representações internas** possíveis para ambos. Uma Pilha pode ser construída sobre lista simples encadeada empilhando no início; uma Fila pode ser construída sobre lista simples encadeada com dois ponteiros (início e fim) inserindo no fim e removendo do início.

### Vantagens e custos das listas encadeadas

**Vantagens.**
- Tamanho **dinâmico**: cresce e encolhe sob demanda, sem precisar declarar capacidade máxima a priori.
- Inserções e remoções nas extremidades em **tempo constante** (com os ponteiros âncora certos).
- Sem **desperdício** de memória reservada e nunca usada (como pode acontecer em vetor sobre-alocado).

**Custos.**
- **Acesso aleatório lento**: para chegar ao k-ésimo elemento, é preciso percorrer os anteriores.
- **Memória extra por nó**: cada nó carrega ao menos um ponteiro (8 bytes em sistemas de 64 bits). Para listas de muitos elementos pequenos, esse *overhead* é considerável.
- **Cada nó é uma alocação individual**: criar um nó significa chamar `malloc` (que tem custo próprio) e destruí-lo significa chamar `free`. Um vetor faz **uma única** alocação para todos os elementos. Quanto mais nós, mais chamadas de alocação/liberação a lista paga.

A escolha entre vetor e lista, portanto, **não é dogmática** — depende do padrão de uso da estrutura.

---

## 2. Conceito — Nível Simplificado

Imagine uma **caça ao tesouro** em que cada pista te diz **onde está a próxima pista**. Você só conhece a primeira pista (o ponto de partida); a segunda você só descobre depois de ler a primeira; a terceira, depois de ler a segunda; e assim por diante. Quando uma pista diz *"fim do jogo"*, acabou.

Uma lista encadeada funciona desse jeito. Cada **pista** é um **nó**: tem um pedaço de informação (o **valor** que ele guarda) e um pedaço que diz *"a próxima fica naquele lugar ali"* (o **ponteiro `proximo`**). O `NULL` é o cartão *"fim do jogo"*.

As variantes mudam só pequenos detalhes da brincadeira:

- **Dupla**: cada pista também diz onde estava a **anterior**, então você pode voltar.
- **Circular**: a última pista, em vez de dizer *"fim do jogo"*, te manda **de volta para a primeira**. Você fica girando para sempre se não decidir parar.

E **FIFO/LIFO** são duas formas de **decidir quem sai primeiro** quando você precisa tirar alguém da lista:

- **FIFO** = quem chegou primeiro vai embora primeiro (fila do banco).
- **LIFO** = quem chegou por último vai embora primeiro (pilha de livros — você só pega o de cima).

---

## 3. Visualização Gráfica

### Passo 1: o nó e a lista simples encadeada

A unidade básica é o **nó**: uma caixinha com dois campos — `valor` e `proximo`. Vários nós ligados por setas formam a lista; o ponteiro âncora `inicio` aponta para o primeiro; o último aponta para `NULL`.

![Lista simplesmente encadeada com três nós e ponteiro de início; o último aponta para NULL](img/01_lista_simples.svg)

### Passo 2: variantes — dupla e circular

A lista **duplamente encadeada** acrescenta um ponteiro `anterior` em cada nó, permitindo percorrer nos dois sentidos. A lista **circular** liga o último de volta ao primeiro, formando um anel.

![Lista duplamente encadeada (com anterior e próximo) e lista circular (último liga ao primeiro), lado a lado](img/02_dupla_e_circular.svg)

### Passo 3: FIFO e LIFO — dois padrões sobre a mesma estrutura

A mesma lista encadeada pode servir tanto a uma **Fila** (FIFO — sai pela frente, entra atrás) quanto a uma **Pilha** (LIFO — entra e sai pelo mesmo lado). O que muda é a **política de acesso**, não a estrutura.

![FIFO (fila) e LIFO (pilha) ilustrando a ordem de saída dos elementos](img/03_fifo_lifo.svg)

---

## 4. Problema Motivador

> *"Por que não usar sempre vetor?"*

Um sistema de mensageria precisa armazenar **mensagens em trânsito**: chegam mensagens novas o tempo todo, mensagens antigas são entregues e removidas, e o **número total varia muito** ao longo do dia — de zero, em horários de baixa demanda, a milhares, em picos.

**Tentativa 1 — vetor de tamanho fixo.** Você reserva, na inicialização, um vetor de 10.000 posições. Em horários de pico, lota e o sistema começa a recusar mensagens. Em horários de calmaria, 9.900 posições ficam vazias ocupando memória inútil.

**Tentativa 2 — vetor que cresce dinamicamente** (`realloc` quando enche). Funciona melhor, mas cada `realloc` pode ter de **copiar** todo o conteúdo para uma nova região contígua maior — operação O(n) que congela o sistema por alguns milissegundos quando o vetor está grande. Pior: ao remover mensagens entregues, todas as outras precisam **deslocar** uma posição para preencher o buraco — outro O(n).

**Solução com lista encadeada**: cada mensagem é um **nó** alocado individualmente. Inserir no fim da lista é O(1) (com ponteiro `fim`). Remover da frente é O(1) (avança `inicio`). A memória usada é **exatamente** a necessária, nem mais nem menos. Não há cópias massivas; não há limite estático.

Esse é o padrão **FIFO** — e é exatamente assim que funcionam:
- Filas de impressão.
- *Buffers* de pacotes de rede em roteadores.
- Filas de tarefas em sistemas de mensageria (RabbitMQ, Kafka — na essência conceitual).

Para o padrão **LIFO** (Pilha), o exemplo análogo é a **pilha de chamadas** que toda linguagem de programação mantém para você: cada chamada de função empilha um *frame* com variáveis locais; o `return` desempilha. Como o número de chamadas aninhadas varia, lista encadeada é uma representação natural.

A lição: **estrutura dinâmica** + **acesso só nas extremidades** = lista encadeada brilha.

---

## 5. Analogias

**1. Fila do banco.**
A entrada da fila é o **fim** (último a chegar fica atrás de todos); a saída é o **início** (o próximo a ser atendido). Cada pessoa "aponta" mentalmente para a pessoa da frente — é a sua referência de *"próximo a sair"*. Quando alguém é atendido, ele sai pela frente e a fila **avança**. Quando alguém chega, ele entra pelo fundo. Ninguém precisa "deslocar" fisicamente — cada pessoa só precisa lembrar quem está na sua frente. Isso é uma **lista simplesmente encadeada operada como FIFO** (Fila).

**2. Pilha de provas para corrigir.**
O professor coloca cada prova **em cima** da última. Quando começa a corrigir, **pega a do topo** — que é a última que foi colocada. Não há esforço para chegar à do meio: você não a acessa. A pilha cresce e encolhe pelo mesmo lado. Isso é uma **lista simplesmente encadeada operada como LIFO** (Pilha).

---

## 6. Exercícios Práticos

> Estes exercícios são **conceituais** — não envolvem programar em C. Eles testam se você consegue **identificar a variante** adequada para um problema e **escolher** entre vetor e lista a partir do padrão de uso.

**Exercício 1 — Identificando a variante.**
Para cada situação abaixo, indique a variante de lista encadeada mais adequada (simples, dupla, circular simples, circular dupla) e justifique em uma linha:
- a) Histórico de comandos de um shell em que se navega com setas para cima e para baixo.
- b) Música em uma *playlist* que toca em modo "repetir tudo" sem parar.
- c) Buffer de mensagens em um sistema FIFO em que se insere atrás e remove na frente.
- d) Cursor de um editor de texto que precisa caminhar caractere a caractere para esquerda e direita.
- e) Escalonador *round-robin* de processos: o sistema operacional dá 10 ms para o processo atual e passa para o próximo, voltando ao primeiro após o último.

*Critério de aceitação*: para cada item, indicar a variante + 1 linha de justificativa baseada **na operação dominante** (sentido de navegação, repetição cíclica, padrão de inserção/remoção).

> **Resposta mínima aceitável**
>
> - a) **Lista duplamente encadeada** — navegação em dois sentidos exige ponteiro para o anterior e para o próximo.
> - b) **Lista circular** (simples basta) — o último item retorna ao primeiro, sem fim explícito.
> - c) **Lista simplesmente encadeada** com ponteiros `inicio` e `fim` — inserção atrás e remoção na frente são ambas O(1) sem precisar do anterior.
> - d) **Lista duplamente encadeada** — caminhar para a esquerda exige ponteiro para o anterior.
> - e) **Lista circular** — round-robin é repetição cíclica natural; o ponteiro "atual" avança e ao chegar ao último volta ao primeiro automaticamente.

**Exercício 2 — Escolhendo entre vetor e lista.**
Para cada cenário, decida se a melhor representação é **vetor** ou **lista encadeada**, e justifique em duas linhas baseado em qual operação domina o uso e em qual é a mais cara em cada estrutura.
- a) Tabela de notas dos 50 alunos da disciplina, acessada repetidamente por **número de matrícula** (índice).
- b) Lista de tarefas pendentes que muda muito ao longo do dia, com inserções e remoções frequentes na **frente** e no **fim**, e raros acessos ao meio.
- c) Histórico de operações de um editor para suportar Ctrl+Z (desfazer), com inserção e remoção apenas no **topo**.
- d) Coleção de 10 milhões de pontos `(x, y)` para um cálculo numérico que faz **uma única passada** sequencial sobre todos.

*Critério de aceitação*: indicar vetor ou lista + dois pontos de justificativa (operação dominante e custo da operação cara em cada alternativa).

> **Resposta mínima aceitável**
>
> - a) **Vetor**. Acesso por índice é O(1) em vetor e O(n) em lista; o uso é dominado por acesso aleatório.
> - b) **Lista encadeada** (com ponteiros `inicio` e `fim`). Inserção/remoção nas extremidades é O(1) em lista e O(n) em vetor (deslocamento); o uso é dominado por essas operações.
> - c) **Lista encadeada** (operada como Pilha) — também aceitável vetor dinâmico, pois inserção/remoção só no fim do vetor é O(1) amortizado. Lista tem tamanho exato e evita realocações; vetor é mais simples de implementar e usa apenas uma alocação.
> - d) **Vetor**. 10 M de elementos em lista exigiriam 10 M de chamadas a `malloc` e cerca de 80 MB só de ponteiros (8 bytes × 10 M), além da memória dos próprios pontos. O vetor faz **uma única** alocação para todos os 10 M e armazena somente os pontos. Como o uso é apenas uma passada sequencial, nenhuma vantagem da lista (inserção/remoção rápida) é aproveitada.

---

## 7. Referências

- **Tenenbaum, A. M.; Langsam, Y.; Augenstein, M. J.** — *Estruturas de Dados Usando C*. Capítulo 4, *"Filas e listas"*, e capítulo 5, *"Listas em C"*. Apresenta a lista simples e a duplamente encadeada com o nível de detalhe canônico da disciplina.

- **Sedgewick, R.** — *Algoritmos em C*, Parte 1, capítulo 3 (*"Estruturas de dados elementares"*), seção sobre **listas ligadas**. Discussão sucinta com diagramas excelentes.

**Leituras complementares**:
- **CLRS** — *Algoritmos: Teoria e Prática*. Capítulo 10, seção 10.2 — *"Listas ligadas"*. Cobre a versão dupla e tem exercícios sobre listas circulares.
- **Ziviani, N.** — *Projeto de Algoritmos com Implementações em Pascal e C*. Capítulo sobre estruturas lineares — cobre as variantes em texto em português.
