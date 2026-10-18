# Testes de integração da rota do Admin Dashboard: 401, 403 e 200


# Sem token: 401, a API não sabe quem chama
def test_stats_without_a_token_are_rejected(client):
    response = client.get("/api/admin/stats")

    assert response.status_code == 401


# User comum autenticado: 403, a API sabe quem é e recusa
def test_stats_are_forbidden_for_a_user(client, clarice):
    response = client.get("/api/admin/stats", headers=clarice)

    assert response.status_code == 403


# Admin: 200 com as quantidades de Users e de Books do sistema
def test_admin_gets_the_counts_of_users_and_books(client, clarice, machado_admin):
    client.post("/api/books", json={"name": "Dom Casmurro", "pages": 300}, headers=machado_admin)
    client.post("/api/books", json={"name": "A Hora da Estrela", "pages": 90}, headers=clarice)

    response = client.get("/api/admin/stats", headers=machado_admin)

    assert response.status_code == 200
    assert response.json() == {"users_count": 2, "books_count": 2}
