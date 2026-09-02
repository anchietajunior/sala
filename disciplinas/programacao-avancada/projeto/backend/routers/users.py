# APIRouter registra rotas fora do main.py; Depends injeta as dependências
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import select
from sqlalchemy.orm import Session

import models
from database import get_session
from schemas import LoginRequest, TokenResponse, UserCreate, UserRead
from security import create_access_token, hash_password, verify_password

# Todas as rotas deste arquivo aparecem no Swagger sob o recurso "users"
router = APIRouter(tags=["users"])


# Cadastra um usuário; e-mail repetido responde 409 (conflito)
@router.post("/signup", response_model=UserRead, status_code=201)
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
@router.post("/login", response_model=TokenResponse)
def login(credentials: LoginRequest, session: Session = Depends(get_session)):
    statement = select(models.User).where(models.User.email == credentials.email)
    user = session.scalars(statement).first()
    # Mensagem única para email inexistente e senha errada:
    # não entregar a um atacante a lista de quem tem conta
    if user is None or not verify_password(credentials.password, user.password):
        raise HTTPException(status_code=401, detail="Invalid email or password")
    return TokenResponse(access_token=create_access_token(user.id))
