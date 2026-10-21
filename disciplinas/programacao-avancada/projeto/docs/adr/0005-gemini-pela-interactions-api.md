# AI Summary pelo Gemini, chamado com o httpx2 na Interactions API

O AI Summary de um Book é gerado por um modelo de linguagem de terceiros.
A turma cria a própria chave em sala, então o provedor precisa de cadastro rápido e nível gratuito.

## A decisão

- **Provedor: Gemini** (Google), modelo `gemini-3.5-flash-lite`.
  A chave sai do Google AI Studio com uma conta Google, e o nível gratuito atende a disciplina.
  O modelo é o mais rápido e mais barato da família, e um resumo de três frases não pede mais que isso.
- **API: a Interactions API** (`POST /v1beta/interactions`), que a documentação do Google recomenda para projetos novos.
  O `generateContent` continua suportado, mas os exemplos atuais da documentação usam a Interactions API.
- **Cliente: o `httpx2` direto, sem o SDK `google-genai`.**
  A aula é sobre integração de APIs: a requisição fica visível (URI, header da chave, corpo JSON, status, timeout), e a resposta é lida campo a campo.
  O `httpx2` já estava no `requirements.txt` por causa do `TestClient`, então nenhuma dependência nova entra.
- **Saída estruturada com o próprio Pydantic.** O `BookSummary.model_json_schema()` vai no `response_format`, e o `BookSummary.model_validate_json()` confere a resposta.
- **Chave em variável de ambiente** (`GEMINI_API_KEY`), lida na chamada. O repositório é público, e a chave nunca entra no código.
- **`store: false`.** O resumo não continua conversa nenhuma, e a interação não precisa ficar guardada nos servidores do Google.
- **A rota é `def`** (ADR-0003): ela usa a sessão do SQLAlchemy e o `httpx2.post`, as duas bloqueantes.

## Consequências

- No nível gratuito, o Google usa o conteúdo enviado para melhorar os próprios produtos. O prompt leva só o nome e o número de páginas do Book.
- Os testes trocam o `generate_book_summary` por um dublê (`monkeypatch`). Nenhum teste chama a API real: ela custa cota, depende da rede e não responde igual duas vezes.
- Falha do Gemini (rede, timeout, 4xx/5xx, JSON fora do schema) responde 502. Livro que o modelo declara não conhecer responde 422.

## Alternativas rejeitadas

- **OpenRouter.** A API compatível com a da OpenAI dá acesso a vários modelos com uma chave só.
  Mas o suporte a saída estruturada varia de modelo para modelo, e os modelos gratuitos têm limites mais apertados.
- **SDK `google-genai`.** É o caminho mais curto em linhas de código, mas esconde a requisição HTTP que a aula ensina e acrescenta várias dependências.
- **Chamar o Gemini direto do React.** A chave ficaria visível para qualquer um no navegador. A própria documentação do Google manda chamar a API pelo backend.
