// Link de navegação com a cor e o foco do sistema; é um <a>, não um <button>,
// porque leva a outro endereço em vez de executar uma ação
export default function TextLink({ href, children }) {
  return (
    <a href={href} className="rounded text-sm font-semibold text-indigo-600 hover:text-indigo-500 focus-visible:outline-2 focus-visible:outline-offset-2 focus-visible:outline-indigo-600">
      {children}
    </a>
  );
}
