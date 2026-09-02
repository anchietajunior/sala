from datetime import datetime

# Tipos e funções do SQLAlchemy usados para definir as colunas
from sqlalchemy import ForeignKey, String, func
from sqlalchemy.orm import Mapped, mapped_column

# Classe-mãe declarativa, definida junto da infraestrutura de conexão
from database import Base


# Modelo User: o lado 1 da relação — um usuário possui vários livros
class User(Base):
    __tablename__ = "users"

    # Chave primária: inteiro + primary_key → PRIMARY KEY e AUTO_INCREMENT
    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(100))
    # unique=True: o banco recusa dois usuários com o mesmo email
    email: Mapped[str] = mapped_column(String(255), unique=True)
    # Guarda o hash bcrypt da senha — nunca a senha em texto puro
    password: Mapped[str] = mapped_column(String(255))
    # O próprio banco preenche com a data/hora do INSERT
    created_at: Mapped[datetime] = mapped_column(server_default=func.now())


# Modelo Book: cada atributo Mapped vira uma coluna da tabela "books"
class Book(Base):
    __tablename__ = "books"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(255))
    # Chave estrangeira obrigatória: todo livro pertence a um usuário
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"))
    created_at: Mapped[datetime] = mapped_column(server_default=func.now())
