# Reading Tracker

Course project: a reading tracker built with FastAPI and React.

## Backend — how to run

    cd backend
    python3 -m venv .venv          # Windows: python -m venv .venv
    source .venv/bin/activate      # Windows: .venv\Scripts\Activate.ps1
    pip install -r requirements.txt
    uvicorn main:app --reload

Open http://127.0.0.1:8000
