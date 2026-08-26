from datetime import datetime

# Tipos e funções do SQLAlchemy usados para definir as colunas
from sqlalchemy import String, func
from sqlalchemy.orm import Mapped, mapped_column

# Classe-mãe declarativa, definida junto da infraestrutura de conexão
from database import Base


# Modelo User: cada atributo Mapped vira uma coluna da tabela "user"
class User(Base):
    __tablename__ = "user"

    # Chave primária: inteiro + primary_key → PRIMARY KEY e AUTO_INCREMENT
    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(100))
    # unique=True: o banco recusa dois usuários com o mesmo email
    email: Mapped[str] = mapped_column(String(255), unique=True)
    password: Mapped[str] = mapped_column(String(255))
    # O próprio banco preenche com a data/hora do INSERT
    created_at: Mapped[datetime] = mapped_column(server_default=func.now())
