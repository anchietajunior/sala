# Rotas de livros nascem inseguras e são protegidas depois (naive → retrofit)

> **Status: revogado na reestruturação das aulas 04–05.** O JWT foi antecipado para a aula 05: as rotas de books nascem autenticadas e com dono (o `user_id` vem do token, nunca da URL), e a senha nasce com hash bcrypt — a fase naive não existe mais. Mantido como registro da decisão original.

As primeiras aulas constroem as rotas de livros recebendo `user_id` explicitamente (ex.: `GET /users/{user_id}/books`), sem nenhuma autenticação — qualquer um pode passar qualquer id. Isso é deliberado: a aula de JWT começa demonstrando a falha em sala ("troque o id e veja os livros de outro usuário") e então protege as rotas, extraindo o `user_id` do token. O problema motiva a solução, e as branches por aula preservam essa evolução como material didático.

Alternativa rejeitada: ensinar JWT antes do CRUD de livros. Ficaria "correto desde o início", mas o aluno enfrentaria o tema mais difícil (auth) antes de ter completado um CRUD, e perderíamos a demonstração concreta do porquê da autenticação.
