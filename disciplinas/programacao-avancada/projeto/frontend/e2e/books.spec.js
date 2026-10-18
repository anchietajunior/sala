import { expect, test } from "@playwright/test";

const password = "segredo123";

// Cadastra e entra pela tela, como uma pessoa faria; o e-mail leva um
// identificador aleatório para cada execução criar um usuário novo no banco,
// mesmo com testes rodando ao mesmo tempo
async function signUpAndLogIn(page) {
  const email = `leitor-${crypto.randomUUID()}@exemplo.com`;
  await page.goto("/");
  await page.getByRole("button", { name: "Create an account" }).click();
  await page.getByLabel("Name").fill("Leitor de Teste");
  await page.getByLabel("Email").fill(email);
  await page.getByLabel("Password").fill(password);
  await page.getByRole("button", { name: "Create account" }).click();
  // Espera a tela de login, como uma pessoa esperaria: sem isto, o teste
  // preencheria os campos do cadastro, que ainda estão na tela
  await expect(page.getByRole("heading", { name: "Log in" })).toBeVisible();
  await page.getByLabel("Email").fill(email);
  await page.getByLabel("Password").fill(password);
  await page.getByRole("button", { name: "Log in" }).click();
}

// Critério de aceitação: quem se cadastra registra um livro e acompanha o
// Reading Progress conforme avança a leitura
test("a new reader adds a book and follows the reading progress", async ({ page }) => {
  await signUpAndLogIn(page);

  await page.getByLabel("Book name").fill("Dom Casmurro");
  await page.getByLabel("Pages").fill("300");
  await page.getByRole("button", { name: "Add book" }).click();
  await expect(page.getByText("0/300 pages · 0%")).toBeVisible();

  await page.getByRole("button", { name: "Edit" }).click();
  await page.getByLabel("Current page").fill("120");
  await page.getByRole("button", { name: "Save" }).click();
  await expect(page.getByText("120/300 pages · 40%")).toBeVisible();
});

// Critério de aceitação: o Admin Dashboard não aparece para quem não é Admin,
// nem pelo link nem digitando o endereço
test("a reader who is not an admin does not reach the Admin Dashboard", async ({ page }) => {
  await signUpAndLogIn(page);
  await expect(page.getByRole("heading", { name: "My books" })).toBeVisible();
  await expect(page.getByRole("link", { name: "Admin Dashboard" })).toHaveCount(0);

  await page.goto("/admin");

  await expect(page.getByRole("heading", { name: "My books" })).toBeVisible();
  await expect(page.getByRole("heading", { name: "Admin Dashboard" })).toHaveCount(0);
});
