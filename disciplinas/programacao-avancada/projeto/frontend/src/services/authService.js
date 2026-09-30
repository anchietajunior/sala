import { request } from "./api";

// Cadastra um User: POST /signup com nome, e-mail e senha
export function signup(name, email, password) {
  return request("/signup", { method: "POST", body: { name, email, password } });
}

// Troca e-mail e senha pelo token: POST /login; quem chama recebe só o token,
// sem precisar conhecer o formato da resposta da API
export async function login(email, password) {
  const data = await request("/login", { method: "POST", body: { email, password } });
  return data.access_token;
}
