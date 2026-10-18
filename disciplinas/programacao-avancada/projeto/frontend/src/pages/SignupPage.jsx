import { useState } from "react";
import Button from "../components/Button";
import Card from "../components/Card";
import ErrorMessage from "../components/ErrorMessage";
import TextInput from "../components/TextInput";
import { signup } from "../services/authService";

// Tela de cadastro: envia nome, e-mail e senha para a API
export default function SignupPage({ onDone }) {
  // Um estado por campo: o React redesenha o input a cada tecla
  const [name, setName] = useState("");
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");

  // Submit do formulário: evita o reload da página e chama a API
  async function handleSubmit(event) {
    event.preventDefault();
    try {
      await signup(name, email, password);
      onDone();
    } catch (err) {
      setError(err.message);
    }
  }

  // Inputs controlados: o estado é a fonte da verdade, não o DOM
  return (
    <main className="mx-auto max-w-sm px-4 py-16">
      <Card>
        <form onSubmit={handleSubmit} className="grid gap-4">
          <h1 className="text-2xl font-bold">Sign up</h1>
          <TextInput label="Name"
                     value={name} onChange={(e) => setName(e.target.value)} />
          <TextInput label="Email" type="email"
                     value={email} onChange={(e) => setEmail(e.target.value)} />
          <TextInput label="Password" type="password"
                     value={password} onChange={(e) => setPassword(e.target.value)} />
          <ErrorMessage text={error} />
          <Button>Create account</Button>
          <Button type="button" variant="secondary" onClick={onDone}>
            I already have an account
          </Button>
        </form>
      </Card>
    </main>
  );
}
