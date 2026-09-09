# Base dos schemas, leitura de objetos do ORM, regras de campo, e-mail válido
# e validação que envolve mais de um campo
from pydantic import BaseModel, ConfigDict, EmailStr, Field, model_validator


# Schema de entrada: o corpo aceito ao criar ou atualizar um livro
class BookCreate(BaseModel):
    # As regras da coluna valem também na porta da API: nome não-vazio,
    # até 255 caracteres (o String(255) do model) — quem erra recebe 422
    name: str = Field(min_length=1, max_length=255)
    # Um livro tem ao menos uma página; a leitura começa na página 0
    pages: int = Field(gt=0)
    current_page: int = Field(default=0, ge=0)

    # Regra entre dois campos: a página atual não passa do total de páginas
    @model_validator(mode="after")
    def check_current_page(self):
        if self.current_page > self.pages:
            raise ValueError("current_page must not exceed pages")
        return self


# Schema de saída: o formato do livro devolvido pela API (com dono e progresso)
class BookRead(BaseModel):
    # from_attributes: permite montar o schema a partir de um objeto do ORM
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    pages: int
    current_page: int
    # progress é uma property do model: from_attributes a lê como um campo
    progress: int
    user_id: int


# Schema de entrada do cadastro de usuário
class UserCreate(BaseModel):
    # Nome não-vazio, até 100 caracteres (o String(100) do model)
    name: str = Field(min_length=1, max_length=100)
    # EmailStr valida o formato do e-mail antes de a rota executar
    email: EmailStr = Field(max_length=255)
    # Mínimo de 8 por política de senha; máximo de 72 é o limite do bcrypt
    password: str = Field(min_length=8, max_length=72)


# Schema de saída do usuário — sem a senha, que nunca volta na resposta
class UserRead(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    email: str


# Schema de entrada do login: as credenciais do usuário
class LoginRequest(BaseModel):
    email: EmailStr
    password: str


# Schema de saída do login: o token que autentica as próximas requisições
class TokenResponse(BaseModel):
    access_token: str
    token_type: str = "bearer"
