import { useEffect, useState } from "react";
import { request } from "./api";

// Formulário vazio: o estado inicial e o estado após salvar
const emptyForm = { name: "", pages: "", current_page: "" };

// Tela principal: os livros do usuário logado, com criação, edição,
// remoção e o progresso de leitura de cada um
export default function Books({ onLogout }) {
  const [books, setBooks] = useState([]);
  const [form, setForm] = useState(emptyForm);
  // id do livro em edição; null significa que o formulário cria um livro novo
  const [editingId, setEditingId] = useState(null);
  const [error, setError] = useState("");

  // Efeito: roda uma vez, quando o componente entra na tela, e busca os livros
  useEffect(() => {
    loadBooks();
  }, []);

  // Busca a lista na API: a fonte da verdade, nunca o estado local
  async function loadBooks() {
    try {
      setBooks(await request("/api/books"));
    } catch (err) {
      setError(err.message);
    }
  }

  // Um único handler para os três inputs: o name do input é a chave do estado
  function handleChange(event) {
    setForm({ ...form, [event.target.name]: event.target.value });
  }

  // Cria (POST) ou atualiza (PUT) conforme haja um livro em edição
  async function handleSubmit(event) {
    event.preventDefault();
    // Inputs entregam texto; a API espera números
    const body = {
      name: form.name,
      pages: Number(form.pages),
      current_page: Number(form.current_page),
    };
    try {
      if (editingId === null) {
        await request("/api/books", { method: "POST", body });
      } else {
        await request(`/api/books/${editingId}`, { method: "PUT", body });
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
      await request(`/api/books/${id}`, { method: "DELETE" });
      loadBooks();
    } catch (err) {
      setError(err.message);
    }
  }

  // Cabeçalho, o formulário (criar ou editar) e a lista com o progresso
  return (
    <main className="mx-auto mt-10 max-w-lg space-y-6 p-4">
      <header className="flex items-center justify-between">
        <h1 className="text-2xl font-bold">My books</h1>
        <button onClick={onLogout} className="text-sm text-gray-600">Log out</button>
      </header>

      <form onSubmit={handleSubmit} className="space-y-2 rounded border p-4">
        <input className="w-full rounded border p-2" name="name" placeholder="Book name"
               value={form.name} onChange={handleChange} />
        <div className="flex gap-2">
          <input className="w-full rounded border p-2" name="pages" type="number" min="1"
                 placeholder="Pages" value={form.pages} onChange={handleChange} />
          <input className="w-full rounded border p-2" name="current_page" type="number" min="0"
                 placeholder="Current page" value={form.current_page} onChange={handleChange} />
        </div>
        {error && <p className="text-red-600">{error}</p>}
        <button className="rounded bg-blue-600 px-4 py-2 text-white">
          {editingId === null ? "Add book" : "Save"}
        </button>
      </form>

      <ul className="space-y-3">
        {books.map((book) => (
          <li key={book.id} className="rounded border p-3">
            <div className="flex justify-between">
              <strong>{book.name}</strong>
              <span className="text-sm text-gray-600">
                {book.current_page}/{book.pages} pages · {book.progress}%
              </span>
            </div>
            {/* Reading Progress: a largura da barra é a porcentagem que a API calculou */}
            <div className="mt-2 h-2 rounded bg-gray-200">
              <div className="h-2 rounded bg-green-600" style={{ width: `${book.progress}%` }} />
            </div>
            <div className="mt-2 space-x-3 text-sm">
              <button onClick={() => startEditing(book)} className="text-blue-600">Edit</button>
              <button onClick={() => handleDelete(book.id)} className="text-red-600">Delete</button>
            </div>
          </li>
        ))}
      </ul>
    </main>
  );
}
