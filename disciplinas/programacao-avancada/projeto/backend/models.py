from datetime import datetime

# Tipos e funções do SQLAlchemy usados para definir as colunas
from sqlalchemy import String, func
from sqlalchemy.orm import Mapped, mapped_column

# Classe-mãe declarativa, definida junto da infraestrutura de conexão
from database import Base


# Modelo Book: cada atributo Mapped vira uma coluna da tabela "book"
class Book(Base):
    __tablename__ = "books"

    # Chave primária: inteiro + primary_key → PRIMARY KEY e AUTO_INCREMENT
    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(255))
    # O próprio banco preenche com a data/hora do INSERT
    created_at: Mapped[datetime] = mapped_column(server_default=func.now())
