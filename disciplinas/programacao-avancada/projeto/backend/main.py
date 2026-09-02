# Importa o FastAPI, que cria a aplicação e atende as requisições
from fastapi import FastAPI

# Importar models registra as tabelas no metadata antes do create_all
import models
from database import Base, engine
# Cada recurso da API vive em um router próprio
from routers import books, users

# Cria no banco as tabelas dos modelos registrados que ainda não existem
Base.metadata.create_all(engine)

# Cria a instância da aplicação: o main.py é só o ponto de entrada
app = FastAPI()

# Registra as rotas de cada recurso na aplicação
app.include_router(users.router)
app.include_router(books.router)


# Rota GET /health, usada para verificar se a API está no ar (pública)
@app.get("/health")
def read_health():
    # Devolve um dicionário, que o FastAPI converte automaticamente em JSON
    return {"status": "Ok"}
