import { useState } from "react";
import BooksPage from "./pages/BooksPage";
import LoginPage from "./pages/LoginPage";
import SignupPage from "./pages/SignupPage";

// Componente raiz: decide qual página aparece a partir do estado
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
    return <BooksPage onLogout={handleLogout} />;
  }
  if (showSignup) {
    return <SignupPage onDone={() => setShowSignup(false)} />;
  }
  return <LoginPage onLogin={handleLogin} onShowSignup={() => setShowSignup(true)} />;
}
