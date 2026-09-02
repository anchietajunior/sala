from datetime import datetime, timedelta, timezone

# bcrypt gera e verifica hashes de senha; jwt emite e valida tokens
import bcrypt
import jwt
from fastapi import Depends, HTTPException
# HTTPBearer extrai o token do header Authorization: Bearer <token>
from fastapi.security import HTTPAuthorizationCredentials, HTTPBearer
from sqlalchemy.orm import Session

import models
from database import get_session

# Chave que assina os tokens (mínimo de 32 bytes para o HMAC-SHA256);
# em produção viria de variável de ambiente
SECRET_KEY = "change-me-in-production-32-bytes-min!"
ALGORITHM = "HS256"
# Validade do token: a resposta ao problema da revogação
TOKEN_LIFETIME = timedelta(hours=2)

# auto_error=False: header ausente cai no nosso if e respondemos 401
bearer_scheme = HTTPBearer(auto_error=False)


# Gera o hash bcrypt da senha, com salt embutido no resultado
def hash_password(password: str) -> str:
    return bcrypt.hashpw(password.encode(), bcrypt.gensalt()).decode()


# Refaz o hash da senha digitada e compara com o hash guardado
def verify_password(password: str, hashed: str) -> bool:
    return bcrypt.checkpw(password.encode(), hashed.encode())


# Emite um JWT com os claims sub (quem é) e exp (até quando vale)
def create_access_token(user_id: int) -> str:
    payload = {
        # sub é texto por exigência da RFC 7519
        "sub": str(user_id),
        "exp": datetime.now(timezone.utc) + TOKEN_LIFETIME,
    }
    return jwt.encode(payload, SECRET_KEY, algorithm=ALGORITHM)


# Dependency: verifica o token da requisição e devolve o usuário logado
def get_current_user(
    credentials: HTTPAuthorizationCredentials | None = Depends(bearer_scheme),
    session: Session = Depends(get_session),
) -> models.User:
    # Sem header Authorization: 401 — a API não sabe quem chama
    if credentials is None:
        raise HTTPException(status_code=401, detail="Not authenticated")
    # decode valida assinatura e expiração; falhou em qualquer uma → 401
    try:
        payload = jwt.decode(credentials.credentials, SECRET_KEY,
                             algorithms=[ALGORITHM])
    except jwt.InvalidTokenError:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    # O sub do token é o id do usuário; ele precisa existir no banco
    user = session.get(models.User, int(payload["sub"]))
    if user is None:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    return user
