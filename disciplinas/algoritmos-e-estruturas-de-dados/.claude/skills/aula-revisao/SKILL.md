---
name: aula-revisao
description: Revisa o conteúdo já escrito de uma aula da disciplina Algoritmos e Estruturas de Dados (UniRios) — o `.md` e, quando existir, a `apresentacao.html` — como última etapa do fluxo, depois de `aula-conteudo` e `aula-apresentacao`. Passa por cada bloco procurando e corrigindo cinco problemas: ambiguidades, itens sem explicação clara, contexto excessivo, tópicos sem conexão lógica com o anterior, e referências a outras aulas (poupando os que legitimamente iniciam um novo assunto). Use quando o usuário pedir "revise a aula NN", "passe o revisor na aula X", "limpe o conteúdo da aula", ou ao finalizar a produção de uma aula. Não use para produzir conteúdo novo (use `aula-conteudo`) nem para gerar a apresentação (use `aula-apresentacao`).
---

# Skill: aula-revisao

Revisor geral do **conteúdo já escrito** de uma aula. Não cria material novo — recebe o `.md` (e a `apresentacao.html`, se existir) pronto e o **limpa**, aplicando cinco critérios de qualidade e corrigindo o que encontra.

É a **terceira e última etapa do fluxo** da disciplina:

1. `aula-conteudo` — escreve o `.md` (e o `.c`, em aulas de implementação).
2. `aula-apresentacao` — monta a `apresentacao.html` e os SVGs.
3. **`aula-revisao`** — revisa e limpa o conteúdo dos dois.

## Quando usar

Aciona quando o usuário pedir uma **revisão/limpeza** do conteúdo de uma aula, ou ao concluir a produção de uma aula nova.

Frases-gatilho típicas:

- "Revise a aula 01."
- "Passe o revisor na aula sobre Pilha."
- "Limpe o conteúdo da Aula 05 — está com excesso de contexto."
- "Confere se a aula tem ambiguidade ou salto de raciocínio."

Se o `.md` ainda **não existir**, não é caso desta skill — use `aula-conteudo`. Esta skill **lê e edita** o que já existe; não escreve uma aula do zero.

## Pré-condições

Antes de começar, **sempre**:

1. Leia `CLAUDE.md` na raiz — é a fonte de verdade da disciplina. Boa parte dos critérios de revisão existe para **fazer cumprir** regras do `CLAUDE.md` (não supor conhecimento prévio, definir cada termo no primeiro uso, vocabulário canônico, uma ideia por slide).
2. Leia o `aulaNN_tema/aulaNN_tema.md` inteiro, de ponta a ponta, **antes** de editar qualquer coisa. A revisão de conexão lógica só funciona com o texto todo na cabeça.
3. Se existir `aulaNN_tema/apresentacao.html`, leia-a também — ela será revisada com a mesma lente e precisa terminar **consistente** com o `.md`.

## Os cinco critérios

A revisão inteira gira em torno de cinco eixos. O detalhamento — heurísticas e exemplos bom/ruim — está em `references/criterios-revisao.md`; **leia essa referência antes de revisar**. Em resumo:

1. **Ambiguidade** — toda frase admite uma única leitura? Pronomes (`isso`, `ele`, `essa`) têm antecedente claro? Critérios e instruções são precisos? → *Reescrever para leitura única.*
2. **Itens sem explicação clara** — todo termo técnico é definido no primeiro uso? Todo conceito citado é explicado **dentro desta aula**? Há salto de raciocínio? → *Definir/explicar; se o item não serve à aula, remover.* Remeter a outra aula **não** conta como explicação: ver o critério 5.
3. **Contexto excessivo** — cada parágrafo serve ao objetivo do bloco? Há digressão que não paga seu custo, repetição, ou frase que sai sem perda? → *Cortar.*
4. **Conexão lógica** — cada tópico decorre do anterior (consequência, detalhamento ou contraste), com ponte explícita? → *Adicionar ponte, realocar, ou remover o órfão.* **Exceção:** tópico que legitimamente **inicia um novo assunto** (novo bloco; nova camada prevista pela estrutura; virada anunciada) **não é defeito** — só garanta a frase de transição.
5. **Referência a outra aula** — o texto diz "como vimos na Aula NN", "ponte com a aula anterior", "tema de aula futura", "na próxima aula", "aula própria mais adiante"? → *Remover a referência.* Se o conceito referenciado é **necessário** aqui, substituir a remissão pela **explicação completa, com exemplo próprio** — repetir uma definição já dada em outra aula é o comportamento desejado. Se não é necessário, cortar o trecho inteiro. Nomear um tema da computação ("ordenação", "árvores de busca") continua permitido; anunciar aula, não.

## Fluxo de execução

### 1. Mapear a aula

Liste os blocos e (no bloco 1) as camadas. Tenha claro qual é o **objetivo de cada bloco** — é contra esse objetivo que se mede "contexto excessivo" e "conexão lógica". Consulte `aula-conteudo/references/estrutura-blocos.md` se precisar relembrar o que cada bloco deve conter.

### 2. Varrer bloco a bloco, montando a lista de achados

Percorra o `.md` na ordem. Em cada parágrafo, lista, tabela ou trecho de código, passe os **cinco critérios**. Para cada problema, anote: **local** (bloco/camada + trecho), **qual critério**, **o defeito** e a **ação** proposta (reescrever / explicar / cortar / religar / realocar).

**Não confunda "novo assunto" com "desconexão".** Antes de marcar uma quebra de conexão como defeito, faça as três perguntas da heurística em `references/criterios-revisao.md`. Um bloco novo, uma camada nova, ou uma seção que o roteiro da aula prevê ali são **inícios legítimos** — não os force a "decorrer" do anterior.

### 3. Aplicar as correções

Aplique os ajustes com `Edit`, do começo ao fim do arquivo:

- **Reescrever** ambiguidades para uma leitura única.
- **Definir/explicar** itens obscuros no primeiro uso — a correção padrão é **adicionar a explicação que falta**, não apagar o termo (o `CLAUDE.md` exige que o termo apareça e seja definido).
- **Cortar** contexto excessivo. Aqui a remoção é a ação certa: prefira deletar o parágrafo/digressão inteiro a encolhê-lo pela metade.
- **Religar** tópicos desconexos: adicionar a linha-ponte, ou mover o tópico para onde ele se conecta, ou remover se for órfão sem função na aula.
- **Desamarrar** referências a outras aulas: trocar a remissão pela explicação completa quando o conceito é necessário aqui, ou cortar o trecho quando não é. Uma frase que só existe para situar o aluno na sequência da disciplina sai inteira.

**Preserve o contrato didático.** Nunca remova um bloco ou camada obrigatória, um exercício com sua "Resposta mínima aceitável", ou uma citação inline da bibliografia. Se um trecho parece excessivo mas é exigido pela estrutura, mantenha e, se couber, aperte a redação.

### 4. Manter a apresentação consistente

Se a `apresentacao.html` existe:

- Aplique os **mesmos cinco critérios** aos slides (os slides têm ainda a regra "uma ideia por slide" — ver `aula-apresentacao/references/estrutura-slides.md`).
- Toda correção feita no `.md` que tenha slide correspondente deve ser **refletida no slide** (ou o slide reescrito no mesmo espírito). Ao final, `.md` e `apresentacao.html` não podem contar histórias diferentes.

### 5. Relatar

Ao terminar, reporte um **resumo agrupado pelos cinco critérios**: o que foi corrigido, onde, e o que foi cortado (liste explicitamente as remoções — o usuário precisa ver o que saiu). Se algo foi **sinalizado mas não corrigido** (ex.: exige decisão do usuário, ou tocaria conteúdo que ele pediu explicitamente), diga isso em vez de agir por conta própria.

## Regras inegociáveis (resumo)

- **Revisar, não reescrever a aula.** A skill melhora o texto existente; não troca a abordagem nem reordena blocos inteiros sem necessidade.
- **O contrato didático vence.** Não sacrificar regras do `CLAUDE.md` em nome de "enxugar": blocos/camadas obrigatórios, definição de cada termo no primeiro uso, exercícios com resposta mínima, citação inline da bibliografia — tudo permanece.
- **Correção padrão de item obscuro é explicar, não apagar.** Só remover quando o item de fato não serve à aula.
- **Contexto excessivo se corta inteiro.** Meia-digressão é pior que nenhuma.
- **Início de novo assunto não é desconexão.** Poupe blocos, camadas e viradas previstas — exija deles apenas a frase de transição.
- **Cada aula é uma unidade fechada.** Toda menção a outra aula sai — inclusive as que "só situam" o aluno. Conceito necessário vira explicação própria; conceito desnecessário vira corte.
- **`.md` e `apresentacao.html` terminam consistentes.**
- **Remoções são relatadas.** Nunca cortar conteúdo em silêncio.
- **PT-BR com acentuação correta** em todo o texto tocado.

## Saída final

Reporte em poucas frases:

- Arquivos revisados (`aulaNN_tema.md`, `apresentacao.html`).
- Contagem de achados por critério (ambiguidade / sem explicação / contexto excessivo / conexão lógica) e quantos foram corrigidos.
- Lista explícita do que foi **removido**.
- Qualquer ponto sinalizado que dependa de decisão do usuário.
