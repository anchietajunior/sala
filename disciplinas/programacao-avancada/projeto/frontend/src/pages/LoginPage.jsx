import { useState } from "react";
import Button from "../components/Button";
import Card from "../components/Card";
import ErrorMessage from "../components/ErrorMessage";
import TextInput from "../components/TextInput";
import { login } from "../services/authService";

// Tela de login: troca e-mail e senha pelo token
export default function LoginPage({ onLogin, onShowSignup }) {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");

  // Submit do formulário: evita o reload da página e chama a API
  async function handleSubmit(event) {
    event.preventDefault();
    try {
      const token = await login(email, password);
      // O token sobe para o App, que o guarda e troca de tela
      onLogin(token);
    } catch (err) {
      setError(err.message);
    }
  }

  // Inputs controlados: o estado é a fonte da verdade, não o DOM
  return (
    <main className="mx-auto max-w-sm px-4 py-16">
      <Card>
        <form onSubmit={handleSubmit} className="grid gap-4">
          <h1 className="text-2xl font-bold">Log in</h1>
          <TextInput label="Email" type="email"
                     value={email} onChange={(e) => setEmail(e.target.value)} />
          <TextInput label="Password" type="password"
                     value={password} onChange={(e) => setPassword(e.target.value)} />
          <ErrorMessage text={error} />
          <Button>Log in</Button>
          <Button type="button" variant="secondary" onClick={onShowSignup}>
            Create an account
          </Button>
        </form>
      </Card>
    </main>
  );
}
