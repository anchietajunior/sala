import { defineConfig } from "@playwright/test";

// Testes de ponta a ponta: um navegador de verdade abre o frontend, que conversa
// com a API de verdade; o frontend (npm run dev) e o backend (uvicorn) precisam
// estar rodando antes de npm run test:e2e
export default defineConfig({
  testDir: "e2e",
  use: {
    baseURL: "http://localhost:5173",
  },
});
