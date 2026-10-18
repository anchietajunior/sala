import Button from "./Button";
import TextInput from "./TextInput";

// Formulário de livro: desenha os campos a partir das props e avisa a página
// a cada tecla e no envio; não guarda estado nem chama a API
export default function BookForm({ form, isEditing, onChange, onSubmit }) {
  return (
    <form onSubmit={onSubmit} className="grid gap-4">
      <TextInput label="Book name" name="name"
                 value={form.name} onChange={onChange} />
      <div className="grid grid-cols-2 gap-4">
        <TextInput label="Pages" name="pages" type="number" min="1"
                   value={form.pages} onChange={onChange} />
        <TextInput label="Current page" name="current_page" type="number" min="0"
                   value={form.current_page} onChange={onChange} />
      </div>
      {/* O mesmo formulário cria ou edita: o texto do botão diz em qual modo está */}
      <Button>{isEditing ? "Save" : "Add book"}</Button>
    </form>
  );
}
