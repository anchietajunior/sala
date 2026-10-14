import { useState } from "react";
import AdminDashboardPage from "./pages/AdminDashboardPage";
import BooksPage from "./pages/BooksPage";
import LoginPage from "./pages/LoginPage";
import SignupPage from "./pages/SignupPage";

// Componente raiz: decide qual página aparece a partir do estado e do endereço
export default function App() {
  // O token guardado no navegador decide a tela: sem token, login; com, livros
  const [token, setToken] = useState(localStorage.getItem("token"));
  // O papel recebido no login decide o que a interface mostra; o que cada
  // usuário pode acessar quem decide é a API
  const [role, setRole] = useState(localStorage.getItem("role"));
  // Alterna entre as telas de login e de cadastro
  const [showSignup, setShowSignup] = useState(false);

  // Guarda o token e o papel no navegador: sobrevivem ao F5
  function handleLogin(newToken, newRole) {
    localStorage.setItem("token", newToken);
    localStorage.setItem("role", newRole);
    setToken(newToken);
    setRole(newRole);
  }

  // Sair é esquecer o token e o papel: a API não guarda sessão nenhuma
  function handleLogout() {
    localStorage.removeItem("token");
    localStorage.removeItem("role");
    setToken(null);
    setRole(null);
  }

  if (token) {
    const isAdmin = role === "admin";
    // O endereço /admin abre o Admin Dashboard, só para quem tem o papel admin
    if (window.location.pathname === "/admin" && isAdmin) {
      return <AdminDashboardPage onLogout={handleLogout} />;
    }
    return <BooksPage isAdmin={isAdmin} onLogout={handleLogout} />;
  }
  if (showSignup) {
    return <SignupPage onDone={() => setShowSignup(false)} />;
  }
  return <LoginPage onLogin={handleLogin} onShowSignup={() => setShowSignup(true)} />;
}
