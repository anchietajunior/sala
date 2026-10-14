# Testes de integração: rotas, schemas, regra de acesso e banco trabalhando
# juntos; caixa preta, porque o teste só conhece o contrato HTTP da API


# Cria um livro pela API e devolve o JSON da resposta
def create_book(client, headers, name="Dom Casmurro", pages=300):
    response = client.post("/api/books", json={"name": name, "pages": pages}, headers=headers)
    return response.json()


# Sem token, a API não sabe quem chama: 401
def test_listing_books_without_a_token_is_rejected(client):
    response = client.get("/api/books")

    assert response.status_code == 401


# O Reading Progress chega calculado na resposta
def test_created_book_has_its_progress_calculated(client, clarice):
    response = client.post("/api/books", json={"name": "A Hora da Estrela", "pages": 90,
                                               "current_page": 45}, headers=clarice)

    assert response.status_code == 201
    assert response.json()["progress"] == 50


# A User comum lista só os próprios livros
def test_user_lists_only_own_books(client, clarice, machado_admin):
    create_book(client, machado_admin, name="Dom Casmurro")
    create_book(client, clarice, name="A Hora da Estrela")

    response = client.get("/api/books", headers=clarice)

    assert [book["name"] for book in response.json()] == ["A Hora da Estrela"]


# Livro de outro User responde 404 em todas as rotas de um livro só
def test_user_gets_404_for_a_book_of_another_user(client, clarice, machado_admin):
    book_of_machado = create_book(client, machado_admin)
    path = f"/api/books/{book_of_machado['id']}"

    assert client.get(path, headers=clarice).status_code == 404
    assert client.put(path, json={"name": "x", "pages": 10}, headers=clarice).status_code == 404
    assert client.delete(path, headers=clarice).status_code == 404


# O Admin lista os livros de todos os Users
def test_admin_lists_books_of_every_user(client, clarice, machado_admin):
    create_book(client, machado_admin, name="Dom Casmurro")
    create_book(client, clarice, name="A Hora da Estrela")

    response = client.get("/api/books", headers=machado_admin)

    assert sorted(book["name"] for book in response.json()) == ["A Hora da Estrela", "Dom Casmurro"]


# Teste de regressão: um nome feito só de espaços era aceito e aparecia em branco
# na lista; o teste reproduz o defeito e impede que ele volte
def test_book_name_made_only_of_spaces_is_rejected(client, clarice):
    response = client.post("/api/books", json={"name": "   ", "pages": 10}, headers=clarice)

    assert response.status_code == 422


# O Admin edita o livro de outro User, e o dono continua o mesmo
def test_admin_updates_a_book_of_another_user(client, clarice, machado_admin):
    book_of_clarice = create_book(client, clarice, name="A Hora da Estrela", pages=90)

    response = client.put(f"/api/books/{book_of_clarice['id']}",
                          json={"name": "A Hora da Estrela", "pages": 90, "current_page": 90},
                          headers=machado_admin)

    assert response.status_code == 200
    assert response.json()["progress"] == 100
    assert response.json()["user_id"] == book_of_clarice["user_id"]
