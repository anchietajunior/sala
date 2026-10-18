// Mensagem de erro em destaque; sem texto, o componente não desenha nada
export default function ErrorMessage({ text }) {
  if (!text) {
    return null;
  }
  // role="alert": o leitor de tela anuncia a mensagem assim que ela aparece
  return (
    <p role="alert" className="rounded-lg bg-red-50 px-3 py-2 text-sm text-red-700 ring-1 ring-red-200 ring-inset">
      {text}
    </p>
  );
}
