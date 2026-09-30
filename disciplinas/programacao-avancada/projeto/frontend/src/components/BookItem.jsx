import Button from "./Button";
import Card from "./Card";

// Um livro da lista: nome, páginas, a barra de progresso e os botões;
// editar e apagar são decisões da página, avisada pelos callbacks
export default function BookItem({ book, onEdit, onDelete }) {
  return (
    <li>
      <Card>
        <div className="flex items-baseline justify-between gap-4">
          <strong>{book.name}</strong>
          <span className="text-sm text-slate-500">
            {book.current_page}/{book.pages} pages · {book.progress}%
          </span>
        </div>
        {/* Reading Progress: a largura da barra é a porcentagem que a API calculou */}
        <div className="mt-3 h-2 rounded-full bg-slate-100">
          <div className="h-2 rounded-full bg-indigo-600" style={{ width: `${book.progress}%` }} />
        </div>
        <div className="mt-4 flex gap-2">
          <Button variant="secondary" onClick={() => onEdit(book)}>Edit</Button>
          <Button variant="danger" onClick={() => onDelete(book.id)}>Delete</Button>
        </div>
      </Card>
    </li>
  );
}
