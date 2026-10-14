# APIRouter registra rotas fora do main.py; Depends injeta as dependências
from fastapi import APIRouter, Depends
# func.count gera o COUNT(...) do SQL
from sqlalchemy import func, select
from sqlalchemy.orm import Session

import models
from database import get_session
from schemas import AdminStats
from security import require_admin

# dependencies: o require_admin vale para todas as rotas deste router —
# nenhuma rota administrativa nasce sem a verificação do papel
router = APIRouter(prefix="/api/admin", tags=["admin"],
                   dependencies=[Depends(require_admin)])


# As quantidades de usuários e de livros cadastrados no sistema
@router.get("/stats", response_model=AdminStats)
def read_stats(session: Session = Depends(get_session)):
    # SELECT COUNT(users.id) FROM users; scalar devolve o número da única linha
    users_count = session.scalar(select(func.count(models.User.id)))
    books_count = session.scalar(select(func.count(models.Book.id)))
    return AdminStats(users_count=users_count, books_count=books_count)
