from fastapi import FastAPI

app = FastAPI()


@app.get("/health")
def read_health():
    return {"status": "Ok"}


@app.get("/greetings/{name}")
def read_greeting(name: str):
    return {"message": f"Hello, {name}!"}


@app.get("/progress/{current_page}")
def read_progress(current_page: int, total_pages: int = 100):
    percentage = round(current_page / total_pages * 100)
    return {
        "current_page": current_page,
        "total_pages": total_pages,
        "percentage": percentage,
    }
