// Campo de formulário do sistema: o rótulo envolve o input, o que liga os dois
// sem precisar de id; as demais props (value, onChange, type, name) vão para o <input>
export default function TextInput({ label, ...props }) {
  return (
    <label className="grid gap-1 text-sm font-medium text-slate-700">
      {label}
      <input
        className="w-full rounded-lg border border-slate-300 bg-white px-3 py-2 text-base text-slate-900 shadow-xs focus:border-indigo-600 focus:outline-2 focus:outline-indigo-600/20"
        {...props}
      />
    </label>
  );
}
