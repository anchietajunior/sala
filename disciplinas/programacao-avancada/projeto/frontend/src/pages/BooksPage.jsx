import { useEffect, useState } from "react";
import BookForm from "../components/BookForm";
import BookItem from "../components/BookItem";
import Button from "../components/Button";
import Card from "../components/Card";
import ErrorMessage from "../components/ErrorMessage";
import TextLink from "../components/TextLink";
import { createBook, deleteBook, listBooks, updateBook } from "../services/bookService";

// Formulário vazio: o estado inicial e o estado após salvar
const emptyForm = { name: "", pages: "", current_page: "" };

// Tela principal: guarda o estado dos livros que o usuário logado acessa e
// chama a API; o desenho do formulário e de cada livro fica nos componentes
export default function BooksPage({ isAdmin, onLogout }) {
  const [books, setBooks] = useState([]);
  const [form, setForm] = useState(emptyForm);
  // id do livro em edição; null significa que o formulário cria um livro novo
  const [editingId, setEditingId] = useState(null);
  const [error, setError] = useState("");

  // Efeito: roda uma vez, quando a página entra na tela, e busca os livros
  useEffect(() => {
    loadBooks();
  }, []);

  // Busca a lista na API: a fonte da verdade, nunca o estado local
  async function loadBooks() {
    try {
      setBooks(await listBooks());
    } catch (err) {
      setError(err.message);
    }
  }

  // Um único handler para os três inputs: o name do input é a chave do estado
  function handleChange(event) {
    setForm({ ...form, [event.target.name]: event.target.value });
  }

  // Cria ou atualiza conforme haja um livro em edição
  async function handleSubmit(event) {
    event.preventDefault();
    // Inputs entregam texto; a API espera números
    const book = {
      name: form.name,
      pages: Number(form.pages),
      current_page: Number(form.current_page),
    };
    try {
      if (editingId === null) {
        await createBook(book);
      } else {
        await updateBook(editingId, book);
      }
      setForm(emptyForm);
      setEditingId(null);
      setError("");
      loadBooks();
    } catch (err) {
      setError(err.message);
    }
  }

  // Leva o livro para o formulário: o mesmo formulário passa a editar
  function startEditing(book) {
    setEditingId(book.id);
    setForm({ name: book.name, pages: book.pages, current_page: book.current_page });
  }

  // Apaga na API e recarrega a lista
  async function handleDelete(id) {
    try {
      await deleteBook(id);
      loadBooks();
    } catch (err) {
      setError(err.message);
    }
  }

  // Cabeçalho, o formulário (criar ou editar), o erro e a lista de livros
  return (
    <main className="mx-auto grid max-w-lg gap-6 px-4 py-10">
      <header className="flex items-center justify-between">
        {/* O Admin recebe da API os livros de todos; o título acompanha */}
        <h1 className="text-2xl font-bold">{isAdmin ? "All books" : "My books"}</h1>
        <div className="flex items-center gap-4">
          {/* O link para o Admin Dashboard só aparece para o Admin */}
          {isAdmin && <TextLink href="/admin">Admin Dashboard</TextLink>}
          <Button variant="secondary" onClick={onLogout}>Log out</Button>
        </div>
      </header>

      <Card>
        <BookForm form={form} isEditing={editingId !== null}
                  onChange={handleChange} onSubmit={handleSubmit} />
      </Card>
      <ErrorMessage text={error} />

      <ul className="grid gap-4">
        {books.map((book) => (
          <BookItem key={book.id} book={book} onEdit={startEditing} onDelete={handleDelete} />
        ))}
      </ul>
    </main>
  );
}
