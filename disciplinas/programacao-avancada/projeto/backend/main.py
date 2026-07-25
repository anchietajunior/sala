# Importa o FastAPI, a injeção de dependências (Depends) e a exceção de erros HTTP
from fastapi import Depends, FastAPI, HTTPException
# Base dos schemas, a sessão de banco e o construtor de consultas
from sqlmodel import Session, SQLModel, select

# Modelos (tabelas) e infraestrutura de conexão definidos nos outros módulos
import models
from database import engine, get_session

# Cria no banco as tabelas dos modelos registrados que ainda não existem
SQLModel.metadata.create_all(engine)

# Cria a instância da aplicação, que registra as rotas e atende as requisições
app = FastAPI()


# Schema de entrada: o corpo aceito ao criar/atualizar um livro (só o nome)
class BookCreate(SQLModel):
    name: str


# Schema de saída: o formato do livro devolvido pela API (com id)
class Book(SQLModel):
    id: int
    name: str


# Schema de entrada do cadastro de usuário
class UserCreate(SQLModel):
    name: str
    email: str
    password: str


# Schema de saída do usuário — sem a senha, que nunca volta na resposta
class UserRead(SQLModel):
    id: int
    name: str
    email: str


# "Banco de dados" em memória dos livros (migra para o MySQL na próxima aula)
books = [
    {"id": 1, "name": "Dom Casmurro"},
    {"id": 2, "name": "O Hobbit"},
    {"id": 3, "name": "Clean Code"},
]
# Contador do próximo id, para não depender do tamanho da lista
next_book_id = 4


# Rota GET /health, usada para verificar se a API está no ar
@app.get("/health")
def read_health():
    # Devolve um dicionário, que o FastAPI converte automaticamente em JSON
    return {"status": "Ok"}


# Lista os livros; response_model valida/filtra a resposta como lista de Book
@app.get("/api/books", response_model=list[Book])
def list_books(name: str = ""):
    # Sem filtro, devolve a lista completa
    if name == "":
        return books
    # Com filtro, devolve só os livros cujo nome contém o termo (ignorando maiúsculas)
    return [book for book in books if name.lower() in book["name"].lower()]


# Busca um livro pelo id vindo do path da URL
@app.get("/api/books/{book_id}", response_model=Book)
def read_book(book_id: int):
    # Percorre a lista procurando o livro com o id pedido
    for book in books:
        if book["id"] == book_id:
            return book
    # Não achou: responde 404 em vez de devolver vazio
    raise HTTPException(status_code=404, detail="Book not found")


# Cria um livro; o corpo é validado pelo schema BookCreate; 201 = criado
@app.post("/api/books", response_model=Book, status_code=201)
def create_book(book: BookCreate):
    # global: a função altera a variável de módulo, não uma cópia local
    global next_book_id
    # Monta o novo livro com o próximo id e avança o contador
    new_book = {"id": next_book_id, "name": book.name}
    next_book_id += 1
    # Guarda na lista em memória e devolve o livro criado
    books.append(new_book)
    return new_book


# Atualiza um livro existente; PUT substitui a representação inteira
@app.put("/api/books/{book_id}", response_model=Book)
def update_book(book_id: int, book: BookCreate):
    # Procura o livro e, se existir, troca o nome pelo novo
    for stored_book in books:
        if stored_book["id"] == book_id:
            stored_book["name"] = book.name
            return stored_book
    # Não achou: responde 404
    raise HTTPException(status_code=404, detail="Book not found")


# Remove um livro; 204 = sucesso sem corpo na resposta
@app.delete("/api/books/{book_id}", status_code=204)
def delete_book(book_id: int):
    # Procura o livro e, se existir, remove da lista
    for book in books:
        if book["id"] == book_id:
            books.remove(book)
            return
    # Não achou: responde 404
    raise HTTPException(status_code=404, detail="Book not found")


# Cadastra um usuário no banco; Depends(get_session) injeta a sessão na rota
@app.post("/signup", response_model=UserRead, status_code=201)
def signup(user: UserCreate, session: Session = Depends(get_session)):
    # Monta a consulta e executa: existe alguém com este email?
    statement = select(models.User).where(models.User.email == user.email)
    existing_user = session.exec(statement).first()
    # 409 = conflito: o email já está em uso
    if existing_user is not None:
        raise HTTPException(status_code=409, detail="Email already registered")
    # Senha guardada em texto puro de propósito — o hash chega
    # na aula de autenticação (ADR-0001)
    new_user = models.User(name=user.name, email=user.email, password=user.password)
    # add coloca na sessão, commit grava no banco, refresh traz o id gerado
    session.add(new_user)
    session.commit()
    session.refresh(new_user)
    return new_user
