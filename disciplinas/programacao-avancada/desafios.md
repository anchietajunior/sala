# Desafios em equipe - Programação Avançada

Cada equipe recebe um desafio e constrói um sistema com FastAPI no backend, React no frontend e a tecnologia indicada no desafio.
Cada desafio tem uma pergunta central.
A equipe resolve o problema, justifica as decisões e responde à pergunta central na apresentação.

## Entregas comuns a todas as equipes

- Repositório com `README.md` em pt-BR: como executar o sistema no Mac e no Windows, e as decisões da equipe.
- Docker Compose para os serviços extras do desafio (Redis, RabbitMQ, Meilisearch, PostGIS etc.).
- Testes automatizados com pytest para a regra central do desafio.
- Apresentação que responde à pergunta central e executa a demonstração pedida.

---

## 1. Detecção de possíveis fraudes em transações bancárias

- **Contexto:** o arquivo `transacoes.txt` contém 2.000 transações bancárias.
- **Construir:** um sistema que classifica as transações e marca as possíveis fraudes, segundo critérios que a equipe define a partir dos dados. Um painel (*dashboard*) mostra as transações marcadas.
- **Tecnologia:** a equipe escolhe as ferramentas de análise de dados e de gráficos e justifica a escolha.
- **Pergunta central:** quais critérios a equipe definiu, e por quê? Como a equipe construiu a classificação? Por que a equipe escolheu esta forma de mostrar os dados no painel?
- **Demonstração:** o painel com as transações marcadas e, para cada transação, o critério que a marcou.

## 2. Encurtador de URL com cache

- **Contexto:** um serviço de encurtamento de URL em que cada URL pertence a um usuário.
- **Construir:** cadastro e login de usuários. O usuário cria e lista as URLs curtas dele. O acesso a uma URL curta redireciona para a URL original.
- **Tecnologia:** Redis.
- **Pergunta central:** como o sistema redireciona uma URL usada nos últimos 6 meses sem consultar o banco de dados? Uma URL sem acesso há 6 meses sai do cache e só volta para o cache quando alguém a acessa de novo: como a equipe implementou esta regra? Qual código de redirecionamento a equipe usa (301 ou 302), e por quê?
- **Demonstração:** o primeiro acesso a uma URL consulta o banco; o segundo acesso vem do Redis. O comando `TTL` no `redis-cli` mostra o prazo de expiração da chave.

## 3. Venda de ingressos com assento marcado

- **Contexto:** um teatro com 300 assentos abre a venda de um espetáculo. Muitos usuários tentam comprar o mesmo assento no mesmo segundo.
- **Construir:** um mapa de assentos. O assento escolhido fica reservado por 10 minutos para o pagamento (simulado). Se o pagamento não acontece, o assento fica livre de novo.
- **Tecnologia:** transações e bloqueio de linha no MySQL (`SELECT ... FOR UPDATE`) ou restrição `UNIQUE`. Teste de carga com Locust.
- **Pergunta central:** como garantir que dois usuários nunca comprem o mesmo assento? Como a reserva expira sem um processo que verifica o banco a cada segundo?
- **Demonstração:** 100 requisições simultâneas para o mesmo assento. Exatamente uma tem sucesso. As outras recebem `409 Conflict`.

## 4. Emissão de certificados em lote

- **Contexto:** um evento acadêmico tem 5.000 participantes no arquivo `participantes.csv`. Cada participante recebe um certificado em PDF por e-mail.
- **Construir:** upload do CSV. A API responde logo com `202 Accepted`, e os *workers* (processos que executam tarefas em segundo plano) geram os PDFs. O painel mostra o progresso ("3.120 de 5.000") e a lista de falhas.
- **Tecnologia:** Celery + RabbitMQ (fila de mensagens), fpdf2 e Mailpit (servidor de e-mail de teste).
- **Pergunta central:** por que a requisição HTTP não pode esperar o fim do lote? Um worker para no meio do trabalho: o participante recebe dois certificados ou nenhum? Como a equipe garante a idempotência (repetir a mesma tarefa não muda o resultado) e a nova tentativa (*retry*)?
- **Demonstração:** encerrar um worker durante o processamento. O lote termina sem certificado duplicado e sem certificado perdido.

## 5. Leilão em tempo real

- **Contexto:** uma plataforma de leilão de itens com encerramento em horário fixo. Todos os participantes veem cada lance no momento em que ele acontece.
- **Construir:** cadastro de itens com lance mínimo e horário de encerramento. A sala do item mostra o lance atual, o histórico e o tempo restante, sem recarregar a página. Regra contra o lance de último segundo (*anti-sniping*): um lance nos 2 minutos finais prorroga o encerramento por mais 2 minutos.
- **Tecnologia:** WebSockets no FastAPI. Redis Pub/Sub se a API tiver mais de uma instância (opcional).
- **Pergunta central:** por que a consulta periódica (*polling*, o cliente pergunta ao servidor a cada segundo) é pior que o WebSocket neste caso? Dois lances de mesmo valor chegam no mesmo milissegundo: qual lance vale, e quem decide, o cliente ou o servidor?
- **Demonstração:** três navegadores na mesma sala. Um lance aparece nos três, e um lance no último minuto prorroga o leilão.

## 6. Busca tolerante a erros de digitação

- **Contexto:** o arquivo `acervo.json` contém 20.000 livros (título, autor, sinopse, gênero e ano). O usuário digita "harry poter" ou "machado de asis" e espera encontrar o livro.
- **Construir:** busca instantânea (o resultado aparece enquanto o usuário digita), filtros por gênero e ano (facetas) e destaque do trecho encontrado.
- **Tecnologia:** Meilisearch ou Elasticsearch, comparado com `LIKE '%termo%'` no MySQL.
- **Pergunta central:** por que o `LIKE` não trata erro de digitação nem acentuação? O que é um índice invertido? Como a equipe definiu a relevância (o título pesa mais que a sinopse?)? Como o índice de busca fica sincronizado com o MySQL quando um livro muda?
- **Demonstração:** uma tabela com 10 buscas com erro de digitação, com o tempo de resposta e os resultados das duas abordagens.

## 7. Ponto de coleta mais próximo

- **Contexto:** o arquivo `pontos_coleta.csv` contém 8.000 pontos de coleta de recicláveis (nome, materiais aceitos, latitude e longitude).
- **Construir:** um mapa com a posição do usuário (Geolocation API do navegador) e os pontos mais próximos dentro de um raio, com filtro por material e a distância até cada ponto.
- **Tecnologia:** PostGIS, ou os tipos espaciais do MySQL com índice `SPATIAL`. Leaflet + OpenStreetMap no frontend.
- **Pergunta central:** calcular a distância até os 8.000 pontos em cada busca é viável quando o número de pontos cresce? Como o índice espacial (*R-tree*) evita esse cálculo? Por que a distância entre duas coordenadas não é a distância euclidiana (fórmula de Haversine)?
- **Demonstração:** o `EXPLAIN` e o tempo da consulta, com e sem o índice espacial.

## 8. Checkout com gateway de pagamento e webhooks

- **Contexto:** uma loja virtual em que o gateway de pagamento confirma o pagamento depois, por uma notificação HTTP (*webhook*). O gateway reenvia a notificação quando não recebe `200`. A mesma notificação pode chegar duplicada ou fora de ordem.
- **Construir:** carrinho, pedido, pagamento no modo de teste do gateway e um endpoint de webhook que muda o estado do pedido (pendente → pago → enviado, ou recusado, ou estornado).
- **Tecnologia:** Stripe ou Mercado Pago em modo de teste (*sandbox*), assinatura HMAC-SHA256 do webhook e o header `Idempotency-Key`.
- **Pergunta central:** o usuário clica duas vezes em "Pagar": como a equipe evita a cobrança dupla? O mesmo webhook chega três vezes: como processá-lo uma só vez? Como saber que a notificação vem do gateway e não de um atacante? "Pago" chega depois de "estornado": qual estado vale (máquina de estados)?
- **Demonstração:** reenviar o mesmo webhook 5 vezes e enviar um webhook com assinatura falsa.

## 9. Deduplicação de cadastros de clientes

- **Contexto:** o arquivo `clientes.csv` contém 3.000 cadastros, juntados de três sistemas antigos. A mesma pessoa aparece como "José da Silva", "JOSE SILVA" e "José d. Silva". O telefone aparece com e sem DDD, e uma parte dos registros não tem CPF.
- **Construir:** o sistema agrupa os registros que provavelmente são da mesma pessoa e dá uma pontuação de confiança para cada grupo. Numa tela de revisão, um operador aprova ou rejeita cada fusão. O sistema guarda o histórico das fusões e permite desfazer uma fusão.
- **Tecnologia:** pandas + RapidFuzz (similaridade de texto: distância de Levenshtein e *token sort ratio*).
- **Pergunta central:** quais critérios definem "mesma pessoa", e qual é o peso de cada critério? Qual limiar de pontuação a equipe escolheu, e quantos falsos positivos e falsos negativos ele produz? Comparar todos os registros com todos são cerca de 4,5 milhões de pares: como a equipe reduz esse número (agrupamento prévio, *blocking*)?
- **Demonstração:** a precisão e a revocação do sistema, medidas contra um gabarito que a equipe marca à mão numa amostra de 100 registros.

## 10. Assistente do regulamento acadêmico

- **Contexto:** o regulamento acadêmico e o manual do aluno, em PDFs com dezenas de páginas. O aluno pergunta "quantas faltas posso ter?" ou "como faço o trancamento da matrícula?".
- **Construir:** o sistema divide o texto em trechos, gera vetores que representam o significado de cada trecho (*embeddings*) e guarda esses vetores num banco vetorial. A resposta cita o artigo e a página usados. Se o sistema não encontra a informação, ele responde que não a encontrou.
- **Tecnologia:** API do Gemini (embeddings e geração de texto), ChromaDB ou pgvector, e pypdf para extrair o texto dos PDFs.
- **Pergunta central:** por que não enviar o PDF inteiro em cada pergunta (custo e limite de contexto do modelo)? Como a equipe escolheu o tamanho dos trechos e a sobreposição entre eles? Como a equipe mede se a busca devolve o trecho certo? Como a equipe evita uma resposta inventada?
- **Demonstração:** 15 perguntas de teste com a resposta esperada, a taxa de acerto e uma pergunta sobre um assunto que não está no regulamento.
