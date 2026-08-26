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

# Cria no banco as tabelas dos modelos registrados que ainda não existem
Base.metadata.create_all(engine)

# Cria a instância da aplicação, que registra as rotas e atende as requisições
app = FastAPI()


# Schema de entrada: o corpo aceito ao criar ou atualizar um livro (só o nome)
class BookCreate(BaseModel):
    name: str


# Schema de saída: o formato do livro devolvido pela API (com o id do banco)
class BookRead(BaseModel):
    # from_attributes: permite montar o schema a partir de um objeto do ORM
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str


# Rota GET /health, usada para verificar se a API está no ar
@app.get("/health")
def read_health():
    # Devolve um dicionário, que o FastAPI converte automaticamente em JSON
    return {"status": "Ok"}


# Lista os livros; response_model valida a resposta como lista de BookRead
@app.get("/api/books", response_model=list[BookRead])
def list_books(name: str = "", session: Session = Depends(get_session)):
    # Monta a consulta: todos os livros da tabela
    statement = select(models.Book)
    # Com filtro, só os cujo nome contém o termo (vira LIKE '%name%' no SQL)
    if name != "":
        statement = statement.where(models.Book.name.contains(name))
    # Executa e devolve os objetos Book encontrados
    return session.scalars(statement).all()


# Busca um livro pelo id vindo do path da URL
@app.get("/api/books/{book_id}", response_model=BookRead)
def read_book(book_id: int, session: Session = Depends(get_session)):
    # get busca direto pela chave primária; devolve o objeto ou None
    book = session.get(models.Book, book_id)
    # Não achou: responde 404 em vez de devolver vazio
    if book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    return book


# Cria um livro; o corpo é validado pelo schema BookCreate; 201 = criado
@app.post("/api/books", response_model=BookRead, status_code=201)
def create_book(book: BookCreate, session: Session = Depends(get_session)):
    # Entra BookCreate, sai models.Book: o dado do cliente vira linha do banco
    new_book = models.Book(name=book.name)
    # add coloca na sessão, commit grava no banco, refresh traz o que o banco gerou
    session.add(new_book)
    session.commit()
    session.refresh(new_book)
    return new_book


# Atualiza um livro existente; PUT substitui a representação inteira
@app.put("/api/books/{book_id}", response_model=BookRead)
def update_book(book_id: int, book: BookCreate, session: Session = Depends(get_session)):
    # Busca pela chave primária; sem o livro não há o que atualizar
    stored_book = session.get(models.Book, book_id)
    if stored_book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    # A sessão rastreia o objeto: trocar o atributo basta, o commit emite o UPDATE
    stored_book.name = book.name
    session.commit()
    session.refresh(stored_book)
    return stored_book


# Remove um livro; 204 = sucesso sem corpo na resposta
@app.delete("/api/books/{book_id}", status_code=204)
def delete_book(book_id: int, session: Session = Depends(get_session)):
    # Busca pela chave primária; sem o livro não há o que remover
    book = session.get(models.Book, book_id)
    if book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    # delete anota a remoção; commit executa o DELETE no banco
    session.delete(book)
    session.commit()
