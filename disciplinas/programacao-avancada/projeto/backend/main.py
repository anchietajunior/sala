from fastapi import FastAPI, HTTPException

app = FastAPI()

books = [
    {"id": 1, "name": "Dom Casmurro"},
    {"id": 2, "name": "O Hobbit"},
    {"id": 3, "name": "Clean Code"},
]


@app.get("/health")
def read_health():
    return {"status": "Ok"}


@app.get("/api/books")
def list_books(name: str = ""):
    if name == "":
        return books
    return [book for book in books if name.lower() in book["name"].lower()]


@app.get("/api/books/{book_id}")
def read_book(book_id: int):
    for book in books:
        if book["id"] == book_id:
            return book
    raise HTTPException(status_code=404, detail="Book not found")


@app.post("/api/books", status_code=201)
def create_book(book: dict):
    new_book = {"id": len(books) + 1, "name": book["name"]}
    books.append(new_book)
    return new_book
