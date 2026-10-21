import Button from "./Button";
import Card from "./Card";

// Um livro da lista: nome, páginas, a barra de progresso, o AI Summary e os
// botões; editar, apagar e resumir são decisões da página, avisada pelos callbacks
export default function BookItem({ book, isSummarizing, onEdit, onDelete, onSummarize }) {
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
        {/* AI Summary: só aparece depois de gerado; o React escapa o texto, então
            nada que o modelo escreva vira HTML na página */}
        {book.ai_summary && (
          <p className="mt-3 text-sm text-slate-600">
            <strong>AI summary:</strong> {book.ai_summary}
          </p>
        )}
        <div className="mt-4 flex gap-2">
          <Button variant="secondary" onClick={() => onEdit(book)}>Edit</Button>
          <Button variant="danger" onClick={() => onDelete(book.id)}>Delete</Button>
          {/* Desabilitado durante a geração: um segundo clique seria um segundo
              pedido pago à API */}
          <Button variant="secondary" disabled={isSummarizing} onClick={() => onSummarize(book.id)}>
            {isSummarizing ? "Generating..." : "AI summary"}
          </Button>
        </div>
      </Card>
    </li>
  );
}
