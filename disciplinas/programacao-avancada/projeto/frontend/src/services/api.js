// Endereço da API: o React roda em outra origem (porta 5173), a API na 8000
const API_URL = "http://127.0.0.1:8000";

// Faz uma requisição à API e devolve o JSON da resposta: monta os headers,
// anexa o token guardado (se houver) e transforma resposta de erro em
// exceção com a mensagem que a API enviou
export async function request(path, { method = "GET", body } = {}) {
  const headers = { "Content-Type": "application/json" };
  // O token vive no localStorage; com ele no header, a API sabe quem pede
  const token = localStorage.getItem("token");
  if (token) {
    headers["Authorization"] = `Bearer ${token}`;
  }
  const response = await fetch(API_URL + path, {
    method,
    headers,
    body: body ? JSON.stringify(body) : undefined,
  });
  // 204 (DELETE) é sucesso sem corpo: não há JSON para ler
  if (response.status === 204) {
    return null;
  }
  const data = await response.json();
  // 4xx/5xx: a API explica o erro em "detail" (texto, ou lista no 422)
  if (!response.ok) {
    const error = new Error(
      Array.isArray(data.detail) ? data.detail[0].msg : data.detail,
    );
    error.status = response.status;
    throw error;
  }
  return data;
}
