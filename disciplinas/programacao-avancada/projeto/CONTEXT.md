# Reading Tracker — Programação Avançada (Unirios)

Projeto didático da disciplina Programação Avançada: um rastreador de leituras onde usuários cadastram livros e acompanham o progresso de leitura. O código é escrito em inglês; o material didático, em português.

## Language

**User**:
Pessoa cadastrada no sistema, dona dos próprios livros. Um User comum só enxerga os Books que ele mesmo cadastrou.
_Avoid_: conta, account, member

**Role**:
Papel de um User no controle de acesso: `user`, o padrão de todo cadastro, ou `admin`. O Role decide quais Books o User acessa e se ele entra no Admin Dashboard. Conceder o Role `admin` não é uma operação da API.
_Avoid_: perfil, permissão, tipo de usuário

**Admin**:
User com o Role `admin`. Acessa o Admin Dashboard e lê, edita e apaga os Books de todos os Users — a regra de dono não se aplica a ele.
_Avoid_: superuser, staff

**Book**:
Livro cadastrado por um User, com quantidade total de páginas informada no cadastro. Pertence exclusivamente ao User que o cadastrou.
_Avoid_: título, obra

**AI Summary**:
Resumo curto de um Book, sem revelar o final, gerado por um modelo de linguagem a pedido do User. Fica gravado no Book, e cada novo pedido o substitui. Se o modelo declara não conhecer o livro, nenhum resumo é gravado.
_Avoid_: sinopse, descrição, resenha

**Cover**:
Imagem da capa enviada pelo User para um Book.
_Avoid_: imagem, foto, thumbnail

**Reading Update**:
Registro de uma atualização de leitura: a página em que o User estava em um Book em um dado momento. Um Book acumula um histórico de Reading Updates.
_Avoid_: check-in, sessão de leitura

**Reading Progress**:
Estado atual da leitura de um Book, derivado do Reading Update mais recente. A porcentagem de leitura é a página atual sobre o total de páginas; um Book está concluído quando atinge 100% — não existe status armazenado.
_Avoid_: status de leitura, andamento

**Reading Report**:
PDF gerado pelo sistema com os Books do User, suas porcentagens de leitura e o histórico de Reading Updates. Cada User só gera o próprio relatório.
_Avoid_: extrato, exportação

**Admin Dashboard**:
Tela visível apenas para Admins, exibindo a quantidade de Users e a quantidade de Books cadastrados no sistema, com acesso aos Users e seus Books.
_Avoid_: painel, backoffice
