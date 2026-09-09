import { useState } from "react";
import Books from "./Books";
import Login from "./Login";
import Signup from "./Signup";

// Componente raiz: decide qual tela aparece a partir do estado
export default function App() {
  // O token guardado no navegador decide a tela: sem token, login; com, livros
  const [token, setToken] = useState(localStorage.getItem("token"));
  // Alterna entre as telas de login e de cadastro
  const [showSignup, setShowSignup] = useState(false);

  // Guarda o token no navegador: sobrevive ao F5 e vai em toda requisição
  function handleLogin(newToken) {
    localStorage.setItem("token", newToken);
    setToken(newToken);
  }

  // Sair é esquecer o token: a API não guarda sessão nenhuma
  function handleLogout() {
    localStorage.removeItem("token");
    setToken(null);
  }

  if (token) {
    return <Books onLogout={handleLogout} />;
  }
  if (showSignup) {
    return <Signup onDone={() => setShowSignup(false)} />;
  }
  return <Login onLogin={handleLogin} onShowSignup={() => setShowSignup(true)} />;
}
