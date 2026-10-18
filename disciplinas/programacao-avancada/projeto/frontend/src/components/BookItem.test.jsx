import { cleanup, fireEvent, render, screen } from "@testing-library/react";
import { afterEach, expect, test, vi } from "vitest";
import BookItem from "./BookItem";

// Um livro como a API devolve: com o progresso já calculado
const book = { id: 7, name: "Dom Casmurro", pages: 300, current_page: 120, progress: 40 };

// Cada teste começa com a tela vazia: o que um desenhou não vaza para o outro
afterEach(cleanup);

// O componente mostra o nome e o progresso como o usuário lê na tela
test("shows the book name and the reading progress", () => {
  render(<BookItem book={book} onEdit={vi.fn()} onDelete={vi.fn()} />);

  expect(screen.getByText("Dom Casmurro")).toBeTruthy();
  expect(screen.getByText("120/300 pages · 40%")).toBeTruthy();
});

// Clicar em Delete avisa a página com o id do livro; quem apaga é a página
test("calls onDelete with the book id when Delete is clicked", () => {
  const onDelete = vi.fn();
  render(<BookItem book={book} onEdit={vi.fn()} onDelete={onDelete} />);

  fireEvent.click(screen.getByRole("button", { name: "Delete" }));

  expect(onDelete).toHaveBeenCalledWith(7);
});

// Clicar em Edit entrega o livro inteiro para a página preencher o formulário
test("calls onEdit with the book when Edit is clicked", () => {
  const onEdit = vi.fn();
  render(<BookItem book={book} onEdit={onEdit} onDelete={vi.fn()} />);

  fireEvent.click(screen.getByRole("button", { name: "Edit" }));

  expect(onEdit).toHaveBeenCalledWith(book);
});
