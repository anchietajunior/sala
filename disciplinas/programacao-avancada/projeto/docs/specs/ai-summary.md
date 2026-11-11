# Spec: AI Summary

## Objetivo

O User pede um resumo curto de um Book, sem revelar o final, gerado por um modelo de linguagem.

## Regras

- O resumo fica gravado no Book. Cada novo pedido substitui o anterior.
- Se o modelo declara não conhecer o livro, nenhum resumo é gravado.
- Só quem pode acessar o Book pede o resumo dele.

## Critérios de aceitação

- Dado um Book que o User pode acessar, quando ele pede o resumo, então a API responde 200 e o Book traz o `ai_summary` gerado.
- Dado um Book que o modelo declara não conhecer, quando o User pede o resumo, então a API responde 422 e o `ai_summary` não muda.
- Dado um Book inexistente ou que o User não pode acessar, quando ele pede o resumo, então a API responde 404.
- Dada uma falha do serviço de IA, quando o User pede o resumo, então a API responde 502 e o `ai_summary` não muda.

## Fora do escopo

- Histórico dos resumos anteriores.
- Edição do resumo pelo User.
