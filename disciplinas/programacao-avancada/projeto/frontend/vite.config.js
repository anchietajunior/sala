import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";
import { defineConfig } from "vite";

// https://vite.dev/config/
// Plugins do Vite: o do React entende JSX; o do Tailwind gera o CSS das
// classes utilitárias encontradas nos componentes
export default defineConfig({
  plugins: [react(), tailwindcss()],
});
