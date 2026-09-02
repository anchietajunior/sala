# APIRouter registra rotas fora do main.py; Depends injeta as dependências
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import select
from sqlalchemy.orm import Session

import models
from database import get_session
from schemas import BookCreate, BookRead
from security import get_current_user

# prefix: todas as rotas nascem sob /api/books; tags agrupa no Swagger
router = APIRouter(prefix="/api/books", tags=["books"])


# Lista os livros do usuário logado; query param opcional filtra pelo nome
@router.get("", response_model=list[BookRead])
def list_books(name: str = "", session: Session = Depends(get_session),
               current_user: models.User = Depends(get_current_user)):
    # O filtro pelo dono: a FK e o token se encontram nesta linha
    statement = select(models.Book).where(models.Book.user_id == current_user.id)
    # Com filtro de nome, só os cujo nome contém o termo (LIKE '%name%')
    if name != "":
        statement = statement.where(models.Book.name.contains(name))
    return session.scalars(statement).all()


# Busca um livro do usuário logado pelo id
@router.get("/{book_id}", response_model=BookRead)
def read_book(book_id: int, session: Session = Depends(get_session),
              current_user: models.User = Depends(get_current_user)):
    book = session.get(models.Book, book_id)
    # Livro inexistente e livro de outro dono respondem o mesmo 404:
    # a API não confirma a existência de recurso que não é seu
    if book is None or book.user_id != current_user.id:
        raise HTTPException(status_code=404, detail="Book not found")
    return book


# Cria um livro do usuário logado; o dono vem do token, nunca do corpo
@router.post("", response_model=BookRead, status_code=201)
def create_book(book: BookCreate, session: Session = Depends(get_session),
                current_user: models.User = Depends(get_current_user)):
    new_book = models.Book(name=book.name, user_id=current_user.id)
    # add coloca na sessão, commit grava no banco, refresh traz o que o banco gerou
    session.add(new_book)
    session.commit()
    session.refresh(new_book)
    return new_book


# Atualiza um livro do usuário logado; PUT substitui a representação inteira
@router.put("/{book_id}", response_model=BookRead)
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
@router.delete("/{book_id}", status_code=204)
def delete_book(book_id: int, session: Session = Depends(get_session),
                current_user: models.User = Depends(get_current_user)):
    book = session.get(models.Book, book_id)
    if book is None or book.user_id != current_user.id:
        raise HTTPException(status_code=404, detail="Book not found")
    # delete anota a remoção; commit executa o DELETE no banco
    session.delete(book)
    session.commit()
