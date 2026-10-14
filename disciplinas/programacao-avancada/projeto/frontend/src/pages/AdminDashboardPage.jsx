import { useEffect, useState } from "react";
import Button from "../components/Button";
import ErrorMessage from "../components/ErrorMessage";
import StatCard from "../components/StatCard";
import TextLink from "../components/TextLink";
import { getStats } from "../services/adminService";

// Admin Dashboard: as quantidades de Users e de Books cadastrados no sistema
export default function AdminDashboardPage({ onLogout }) {
  // null até a resposta chegar: sem números, nenhum card aparece
  const [stats, setStats] = useState(null);
  const [error, setError] = useState("");

  // Efeito: roda uma vez, quando a página entra na tela, e busca as quantidades;
  // a função mora dentro do efeito porque só ele a usa
  useEffect(() => {
    // Quem decide se os números chegam é a API: sem o papel admin, a resposta
    // é 403 e a página mostra a mensagem de erro
    async function loadStats() {
      try {
        setStats(await getStats());
      } catch (err) {
        setError(err.message);
      }
    }
    loadStats();
  }, []);

  // Cabeçalho com a volta para os livros, o erro e os cards das quantidades
  return (
    <main className="mx-auto grid max-w-lg gap-6 px-4 py-10">
      <header className="flex items-center justify-between">
        <h1 className="text-2xl font-bold">Admin Dashboard</h1>
        <div className="flex items-center gap-4">
          <TextLink href="/">Books</TextLink>
          <Button variant="secondary" onClick={onLogout}>Log out</Button>
        </div>
      </header>
      <ErrorMessage text={error} />
      {stats && (
        <div className="grid grid-cols-2 gap-4">
          <StatCard label="Users" value={stats.users_count} />
          <StatCard label="Books" value={stats.books_count} />
        </div>
      )}
    </main>
  );
}
