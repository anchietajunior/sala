from fastapi import Depends, FastAPI, HTTPException
from pydantic import BaseModel, ConfigDict
from sqlalchemy import select
from sqlalchemy.orm import Session

import models
from database import Base, SessionLocal, engine

Base.metadata.create_all(bind=engine)

app = FastAPI()


class BookCreate(BaseModel):
    name: str


class Book(BaseModel):
    id: int
    name: str


class UserCreate(BaseModel):
    name: str
    email: str
    password: str


class UserRead(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    email: str


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


books = [
    {"id": 1, "name": "Dom Casmurro"},
    {"id": 2, "name": "O Hobbit"},
    {"id": 3, "name": "Clean Code"},
]
next_book_id = 4


@app.get("/health")
def read_health():
    return {"status": "Ok"}


@app.get("/api/books", response_model=list[Book])
def list_books(name: str = ""):
    if name == "":
        return books
    return [book for book in books if name.lower() in book["name"].lower()]


@app.get("/api/books/{book_id}", response_model=Book)
def read_book(book_id: int):
    for book in books:
        if book["id"] == book_id:
            return book
    raise HTTPException(status_code=404, detail="Book not found")


@app.post("/api/books", response_model=Book, status_code=201)
def create_book(book: BookCreate):
    global next_book_id
    new_book = {"id": next_book_id, "name": book.name}
    next_book_id += 1
    books.append(new_book)
    return new_book


@app.put("/api/books/{book_id}", response_model=Book)
def update_book(book_id: int, book: BookCreate):
    for stored_book in books:
        if stored_book["id"] == book_id:
            stored_book["name"] = book.name
            return stored_book
    raise HTTPException(status_code=404, detail="Book not found")


@app.delete("/api/books/{book_id}", status_code=204)
def delete_book(book_id: int):
    for book in books:
        if book["id"] == book_id:
            books.remove(book)
            return
    raise HTTPException(status_code=404, detail="Book not found")


@app.post("/signup", response_model=UserRead, status_code=201)
def signup(user: UserCreate, db: Session = Depends(get_db)):
    existing_user = db.scalar(select(models.User).where(models.User.email == user.email))
    if existing_user is not None:
        raise HTTPException(status_code=409, detail="Email already registered")
    # password stored in plain text on purpose — hashing arrives
    # in the authentication lesson (ADR-0001)
    new_user = models.User(name=user.name, email=user.email, password=user.password)
    db.add(new_user)
    db.commit()
    db.refresh(new_user)
    return new_user
