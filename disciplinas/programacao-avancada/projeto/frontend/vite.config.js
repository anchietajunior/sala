import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";
import { defineConfig } from "vite";

// https://vite.dev/config/
// Plugins do Vite: o do React entende JSX; o do Tailwind gera o CSS das
// classes utilitárias encontradas nos componentes
export default defineConfig({
  plugins: [react(), tailwindcss()],
  // Vitest: os testes rodam num navegador simulado (jsdom) e só os arquivos
  // .test.js e .test.jsx de src/ entram; os de ponta a ponta ficam em e2e/
  test: {
    environment: "jsdom",
    include: ["src/**/*.test.{js,jsx}"],
  },
});
