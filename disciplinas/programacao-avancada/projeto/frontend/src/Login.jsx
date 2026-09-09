import { useState } from "react";
import { request } from "./api";

// Tela de login: troca e-mail e senha pelo token em POST /login
export default function Login({ onLogin, onShowSignup }) {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");

  // Submit do formulário: evita o reload da página e chama a API
  async function handleSubmit(event) {
    event.preventDefault();
    try {
      const data = await request("/login", { method: "POST", body: { email, password } });
      // O token sobe para o App, que o guarda e troca de tela
      onLogin(data.access_token);
    } catch (err) {
      setError(err.message);
    }
  }

  // Inputs controlados: o estado é a fonte da verdade, não o DOM
  return (
    <form onSubmit={handleSubmit} className="mx-auto mt-16 max-w-sm space-y-3">
      <h1 className="text-2xl font-bold">Log in</h1>
      <input className="w-full rounded border p-2" type="email" placeholder="Email"
             value={email} onChange={(e) => setEmail(e.target.value)} />
      <input className="w-full rounded border p-2" type="password" placeholder="Password"
             value={password} onChange={(e) => setPassword(e.target.value)} />
      {error && <p className="text-red-600">{error}</p>}
      <button className="w-full rounded bg-blue-600 p-2 text-white">Log in</button>
      <button type="button" className="w-full text-blue-600" onClick={onShowSignup}>
        Create an account
      </button>
    </form>
  );
}
