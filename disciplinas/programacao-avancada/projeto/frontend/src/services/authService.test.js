import { afterEach, expect, test, vi } from "vitest";
import { login } from "./authService";

// Depois de cada teste, o fetch volta a ser o do navegador
afterEach(() => {
  vi.unstubAllGlobals();
});

// O fetch é trocado por um dublê que responde como a API: o teste não depende
// do backend rodando e controla exatamente o que chega
test("login sends the credentials and returns the token and the role", async () => {
  const fakeFetch = vi.fn().mockResolvedValue(
    new Response(JSON.stringify({ access_token: "abc", token_type: "bearer", role: "admin" }),
                 { status: 200 }),
  );
  vi.stubGlobal("fetch", fakeFetch);

  const result = await login("machado@exemplo.com", "segredo123");

  expect(result).toEqual({ token: "abc", role: "admin" });
  const [url, options] = fakeFetch.mock.calls[0];
  expect(url).toBe("http://127.0.0.1:8000/login");
  expect(JSON.parse(options.body)).toEqual({ email: "machado@exemplo.com", password: "segredo123" });
});

// Credencial errada: a mensagem que a API mandou chega como erro para a página
test("login rejects with the message sent by the API", async () => {
  vi.stubGlobal("fetch", vi.fn().mockResolvedValue(
    new Response(JSON.stringify({ detail: "Invalid email or password" }), { status: 401 }),
  ));

  await expect(login("machado@exemplo.com", "errada123")).rejects.toThrow("Invalid email or password");
});
