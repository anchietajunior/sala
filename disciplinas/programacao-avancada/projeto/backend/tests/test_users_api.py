# Testes de integração do cadastro e do login


# O papel enviado no cadastro é ignorado: todo cadastro nasce user
def test_signup_ignores_the_role_sent_by_the_client(client):
    client.post("/signup", json={"name": "Cecília Meireles", "email": "cecilia@exemplo.com",
                                 "password": "segredo123", "role": "admin"})

    response = client.post("/login", json={"email": "cecilia@exemplo.com", "password": "segredo123"})

    assert response.json()["role"] == "user"


# Senha errada responde 401 com a mesma mensagem de e-mail inexistente
def test_login_with_a_wrong_password_is_rejected(client, clarice):
    response = client.post("/login", json={"email": "clarice@exemplo.com", "password": "errada123"})

    assert response.status_code == 401
    assert response.json()["detail"] == "Invalid email or password"
