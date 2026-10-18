# Testes de unidade: cada model é testado sozinho, sem banco de dados e sem HTTP
import pytest

from models import Book, Role, User


# Um caso por linha: página atual, total de páginas e a porcentagem esperada;
# o pytest executa o mesmo teste uma vez para cada linha
@pytest.mark.parametrize(
    ("current_page", "pages", "expected_progress"),
    [(0, 300, 0), (120, 300, 40), (1, 3, 33), (300, 300, 100)],
)
def test_progress_is_the_current_page_over_the_total_of_pages(current_page, pages, expected_progress):
    book = Book(name="Dom Casmurro", pages=pages, current_page=current_page, user_id=1)

    assert book.progress == expected_progress


# Caixa branca: can_access é "is_admin or book.user_id == self.id"; os três
# testes abaixo percorrem os três caminhos possíveis dessa expressão
def test_admin_can_access_a_book_of_another_user():
    admin = User(id=1, role=Role.ADMIN)
    book_of_another_user = Book(user_id=2)

    assert admin.can_access(book_of_another_user)


# Caminho 2: não é Admin, mas é o dono do livro
def test_user_can_access_own_book():
    user = User(id=2, role=Role.USER)
    own_book = Book(user_id=2)

    assert user.can_access(own_book)


# Caminho 3: não é Admin nem dono; a regra nega o acesso
def test_user_cannot_access_a_book_of_another_user():
    user = User(id=2, role=Role.USER)
    book_of_another_user = Book(user_id=1)

    assert not user.can_access(book_of_another_user)
