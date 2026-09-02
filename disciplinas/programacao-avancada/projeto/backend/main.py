# Importa o FastAPI, a injeção de dependências (Depends) e a exceção de erros HTTP
from fastapi import Depends, FastAPI, HTTPException
# Base dos schemas e configuração para ler objetos do ORM
from pydantic import BaseModel, ConfigDict
# select monta consultas SQL; Session é a sessão de banco do ORM
from sqlalchemy import select
from sqlalchemy.orm import Session

# Modelos (tabelas) e infraestrutura de conexão definidos nos outros módulos
import models
from database import Base, engine, get_session
# Hash de senha, emissão de token e a dependency do usuário logado
from security import (create_access_token, get_current_user, hash_password,
                      verify_password)

# Cria no banco as tabelas dos modelos registrados que ainda não existem
Base.metadata.create_all(engine)

# Cria a instância da aplicação, que registra as rotas e atende as requisições
app = FastAPI()


# Schema de entrada: o corpo aceito ao criar ou atualizar um livro (só o nome)
class BookCreate(BaseModel):
    name: str


# Schema de saída: o formato do livro devolvido pela API (com id e dono)
class BookRead(BaseModel):
    # from_attributes: permite montar o schema a partir de um objeto do ORM
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    user_id: int


# Schema de entrada do cadastro de usuário
class UserCreate(BaseModel):
    name: str
    email: str
    password: str


# Schema de saída do usuário — sem a senha, que nunca volta na resposta
class UserRead(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    email: str


# Schema de entrada do login: as credenciais do usuário
class LoginRequest(BaseModel):
    email: str
    password: str


# Schema de saída do login: o token que autentica as próximas requisições
class TokenResponse(BaseModel):
    access_token: str
    token_type: str = "bearer"


# Rota GET /health, usada para verificar se a API está no ar (pública)
@app.get("/health")
def read_health():
    # Devolve um dicionário, que o FastAPI converte automaticamente em JSON
    return {"status": "Ok"}


# Cadastra um usuário; e-mail repetido responde 409 (conflito)
@app.post("/signup", response_model=UserRead, status_code=201)
def signup(user: UserCreate, session: Session = Depends(get_session)):
    # Consulta preventiva: já existe alguém com este email?
    statement = select(models.User).where(models.User.email == user.email)
    existing_user = session.scalars(statement).first()
    if existing_user is not None:
        raise HTTPException(status_code=409, detail="Email already registered")
    # O que desce para o banco é o hash — a senha existe só em trânsito
    new_user = models.User(name=user.name, email=user.email,
                           password=hash_password(user.password))
    session.add(new_user)
    session.commit()
    session.refresh(new_user)
    return new_user


# Troca credenciais válidas por um token JWT
@app.post("/login", response_model=TokenResponse)
def login(credentials: LoginRequest, session: Session = Depends(get_session)):
    statement = select(models.User).where(models.User.email == credentials.email)
    user = session.scalars(statement).first()
    # Mensagem única para email inexistente e senha errada:
    # não entregar a um atacante a lista de quem tem conta
    if user is None or not verify_password(credentials.password, user.password):
        raise HTTPException(status_code=401, detail="Invalid email or password")
    return TokenResponse(access_token=create_access_token(user.id))


# Lista os livros do usuário logado; query param opcional filtra pelo nome
@app.get("/api/books", response_model=list[BookRead])
def list_books(name: str = "", session: Session = Depends(get_session),
               current_user: models.User = Depends(get_current_user)):
    # O filtro pelo dono: a FK e o token se encontram nesta linha
    statement = select(models.Book).where(models.Book.user_id == current_user.id)
    # Com filtro de nome, só os cujo nome contém o termo (LIKE '%name%')
    if name != "":
        statement = statement.where(models.Book.name.contains(name))
    return session.scalars(statement).all()


# Busca um livro do usuário logado pelo id
@app.get("/api/books/{book_id}", response_model=BookRead)
def read_book(book_id: int, session: Session = Depends(get_session),
              current_user: models.User = Depends(get_current_user)):
    book = session.get(models.Book, book_id)
    # Livro inexistente e livro de outro dono respondem o mesmo 404:
    # a API não confirma a existência de recurso que não é seu
    if book is None or book.user_id != current_user.id:
        raise HTTPException(status_code=404, detail="Book not found")
    return book


# Cria um livro do usuário logado; o dono vem do token, nunca do corpo
@app.post("/api/books", response_model=BookRead, status_code=201)
def create_book(book: BookCreate, session: Session = Depends(get_session),
                current_user: models.User = Depends(get_current_user)):
    new_book = models.Book(name=book.name, user_id=current_user.id)
    # add coloca na sessão, commit grava no banco, refresh traz o que o banco gerou
    session.add(new_book)
    session.commit()
    session.refresh(new_book)
    return new_book


# Atualiza um livro do usuário logado; PUT substitui a representação inteira
@app.put("/api/books/{book_id}", response_model=BookRead)
def update_book(book_id: int, book: BookCreate,
                session: Session = Depends(get_session),
                current_user: models.User = Depends(get_current_user)):
    stored_book = session.get(models.Book, book_id)
    if stored_book is None or stored_book.user_id != current_user.id:
        raise HTTPException(status_code=404, detail="Book not found")
    # A sessão rastreia o objeto: trocar o atributo basta, o commit emite o UPDATE
    stored_book.name = book.name
    session.commit()
    session.refresh(stored_book)
    return stored_book


# Remove um livro do usuário logado; 204 = sucesso sem corpo na resposta
@app.delete("/api/books/{book_id}", status_code=204)
def delete_book(book_id: int, session: Session = Depends(get_session),
                current_user: models.User = Depends(get_current_user)):
    book = session.get(models.Book, book_id)
    if book is None or book.user_id != current_user.id:
        raise HTTPException(status_code=404, detail="Book not found")
    # delete anota a remoção; commit executa o DELETE no banco
    session.delete(book)
    session.commit()
