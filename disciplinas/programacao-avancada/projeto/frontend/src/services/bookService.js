import { request } from "./api";

// Os livros que o usuário logado acessa (todos, para o Admin): GET /api/books
export function listBooks() {
  return request("/api/books");
}

// Cria um livro: POST /api/books com name, pages e current_page
export function createBook(book) {
  return request("/api/books", { method: "POST", body: book });
}

// Atualiza um livro: PUT /api/books/{id} com os três campos
export function updateBook(id, book) {
  return request(`/api/books/${id}`, { method: "PUT", body: book });
}

// Remove um livro: DELETE /api/books/{id}, que responde 204 sem corpo
export function deleteBook(id) {
  return request(`/api/books/${id}`, { method: "DELETE" });
}

// Pede o AI Summary de um livro: POST /api/books/{id}/summary, sem corpo; a
// resposta é o livro com o resumo já gravado
export function summarizeBook(id) {
  return request(`/api/books/${id}/summary`, { method: "POST" });
}
