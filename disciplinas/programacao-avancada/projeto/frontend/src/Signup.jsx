import { useState } from "react";
import { request } from "./api";

// Tela de cadastro: envia nome, e-mail e senha para POST /signup
export default function Signup({ onDone }) {
  // Um estado por campo: o React redesenha o input a cada tecla
  const [name, setName] = useState("");
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");

  // Submit do formulário: evita o reload da página e chama a API
  async function handleSubmit(event) {
    event.preventDefault();
    try {
      await request("/signup", { method: "POST", body: { name, email, password } });
      onDone();
    } catch (err) {
      setError(err.message);
    }
  }

  // Inputs controlados: o estado é a fonte da verdade, não o DOM
  return (
    <form onSubmit={handleSubmit} className="mx-auto mt-16 max-w-sm space-y-3">
      <h1 className="text-2xl font-bold">Sign up</h1>
      <input className="w-full rounded border p-2" placeholder="Name"
             value={name} onChange={(e) => setName(e.target.value)} />
      <input className="w-full rounded border p-2" type="email" placeholder="Email"
             value={email} onChange={(e) => setEmail(e.target.value)} />
      <input className="w-full rounded border p-2" type="password" placeholder="Password"
             value={password} onChange={(e) => setPassword(e.target.value)} />
      {error && <p className="text-red-600">{error}</p>}
      <button className="w-full rounded bg-blue-600 p-2 text-white">Create account</button>
      <button type="button" className="w-full text-blue-600" onClick={onDone}>
        I already have an account
      </button>
    </form>
  );
}
