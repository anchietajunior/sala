// Classes comuns a todo botão: tamanho, fonte e o contorno de foco pelo teclado
const baseClasses = "rounded-lg px-4 py-2 text-sm font-semibold focus-visible:outline-2 focus-visible:outline-offset-2 focus-visible:outline-indigo-600";

// A aparência de cada variante: as classes ficam escritas por inteiro para o
// Tailwind encontrá-las ao gerar o CSS
const variantClasses = {
  primary: "bg-indigo-600 text-white shadow-xs hover:bg-indigo-500",
  secondary: "bg-white text-slate-700 shadow-xs ring-1 ring-slate-300 ring-inset hover:bg-slate-50",
  danger: "bg-white text-red-600 shadow-xs ring-1 ring-red-200 ring-inset hover:bg-red-50",
};

// Botão do sistema: a variante escolhe a cor; as demais props (onClick, type)
// vão direto para o <button>
export default function Button({ variant = "primary", children, ...props }) {
  return (
    <button className={`${baseClasses} ${variantClasses[variant]}`} {...props}>
      {children}
    </button>
  );
}
