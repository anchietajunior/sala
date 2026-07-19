# Importa o que cria a conexão com o banco e a base do ORM
from sqlalchemy import create_engine
from sqlalchemy.orm import DeclarativeBase, sessionmaker

# Endereço do banco: dialeto+driver://usuário@host:porta/nome_do_banco
DATABASE_URL = "mysql+pymysql://root@127.0.0.1:3306/reading_tracker"

# Cria o "motor" de conexões; echo=True imprime no terminal o SQL gerado
engine = create_engine(DATABASE_URL, echo=True)
# Fábrica de sessões: cada requisição abre a sua sessão a partir daqui
SessionLocal = sessionmaker(bind=engine)


# Classe-base da qual todos os modelos (tabelas) do projeto herdam
class Base(DeclarativeBase):
    pass
