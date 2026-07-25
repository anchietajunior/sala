from datetime import datetime

# Field configura as colunas e SQLModel é a classe-mãe dos modelos
from sqlmodel import Field, SQLModel


# Modelo User: table=True transforma a classe na tabela "user" do banco
class User(SQLModel, table=True):
    # Chave primária: nasce None e o banco preenche no INSERT
    id: int | None = Field(default=None, primary_key=True)
    name: str = Field(max_length=100)
    # unique=True: o banco recusa dois usuários com o mesmo email
    email: str = Field(max_length=255, unique=True)
    password: str = Field(max_length=255)
    # Preenchido na criação do objeto, com a data/hora daquele momento
    created_at: datetime = Field(default_factory=datetime.now)
