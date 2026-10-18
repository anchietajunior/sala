# Fixtures compartilhadas por todos os testes: o banco de teste, o cliente HTTP
# da API e os usuários já autenticados
import pytest
from fastapi.testclient import TestClient
from sqlalchemy import create_engine, select
from sqlalchemy.orm import Session
# StaticPool: uma única conexão, para que o SQLite em memória seja o mesmo banco
# durante todo o teste
from sqlalchemy.pool import StaticPool

import models
from database import Base, get_session
from main import app

PASSWORD = "segredo123"


# Banco de teste: SQLite em memória, criado vazio para cada teste e descartado
# no fim; o banco de desenvolvimento nunca recebe dado de teste
@pytest.fixture
def engine():
    test_engine = create_engine("sqlite://", connect_args={"check_same_thread": False},
                                poolclass=StaticPool)
    Base.metadata.create_all(test_engine)
    yield test_engine
    Base.metadata.drop_all(test_engine)


# Cliente HTTP da API: a dependency get_session é trocada por uma que abre a
# sessão no banco de teste; as rotas não percebem a troca
@pytest.fixture
def client(engine):
    def get_test_session():
        with Session(engine) as session:
            yield session

    app.dependency_overrides[get_session] = get_test_session
    yield TestClient(app)
    app.dependency_overrides.clear()


# Cadastra e faz login pela própria API; devolve o header com o token
def signup_and_login(client, name, email):
    client.post("/signup", json={"name": name, "email": email, "password": PASSWORD})
    response = client.post("/login", json={"email": email, "password": PASSWORD})
    return {"Authorization": f"Bearer {response.json()['access_token']}"}


# Clarice: uma User comum, já autenticada
@pytest.fixture
def clarice(client):
    return signup_and_login(client, "Clarice Lispector", "clarice@exemplo.com")


# Machado: promovido a Admin direto no banco, como o UPDATE feito no cliente mysql
@pytest.fixture
def machado_admin(client, engine):
    headers = signup_and_login(client, "Machado de Assis", "machado@exemplo.com")
    with Session(engine) as session:
        statement = select(models.User).where(models.User.email == "machado@exemplo.com")
        machado = session.scalars(statement).one()
        machado.role = models.Role.ADMIN
        session.commit()
    return headers
