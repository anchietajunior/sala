# Importa o que cria a conexão com o banco, a base declarativa e a sessão do ORM
from sqlalchemy import create_engine
from sqlalchemy.orm import DeclarativeBase, Session

# Endereço do banco: dialeto+driver://usuário@host:porta/nome_do_banco
DATABASE_URL = "mysql+pymysql://root@127.0.0.1:3306/reading_tracker"

# Cria o "motor" de conexões; echo=True imprime no terminal o SQL gerado
engine = create_engine(DATABASE_URL, echo=True)


# Classe-mãe dos modelos: quem herda dela se registra como tabela no metadata
class Base(DeclarativeBase):
    pass


# Abre uma sessão de banco por requisição e fecha ao final
def get_session():
    # O with fecha a sessão sozinho, no fim da requisição ou se der erro
    with Session(engine) as session:
        yield session
