// Superfície branca com borda suave e sombra: o contêiner visual dos formulários
// e de cada livro; children é o conteúdo escrito entre <Card> e </Card>
export default function Card({ children }) {
  return <div className="rounded-xl bg-white p-6 shadow-sm ring-1 ring-slate-200">{children}</div>;
}
