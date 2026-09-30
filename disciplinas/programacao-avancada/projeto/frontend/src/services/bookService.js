import { request } from "./api";

// Os livros do usuário logado: GET /api/books
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
