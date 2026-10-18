#include <stdio.h>
#include <stdlib.h>

// Um Aluno agrupa, sob um unico nome, dados de tipos diferentes.
typedef struct Aluno {
    int matricula;
    char turma;
    double nota;
} Aluno;

// Recebe COPIAS dos valores de quem chamou. Trocar x e y aqui dentro
// nao altera as variaveis originais.
void trocar_por_valor(int x, int y) {
    int guardado = x;
    x = y;
    y = guardado;
}

// Recebe os ENDERECOS das variaveis de quem chamou. Escrevendo em *x e *y,
// a funcao altera as variaveis originais.
void trocar(int *x, int *y) {
    int guardado = *x;
    *x = *y;
    *y = guardado;
}

// Recebe uma COPIA do aluno: basta para ler os campos, nao para altera-los.
void aluno_imprimir(Aluno aluno) {
    printf("matricula %d, turma %c, nota %.1f\n",
           aluno.matricula, aluno.turma, aluno.nota);
}

// Recebe o ENDERECO do aluno, para que a alteracao valha no registro
// original de quem chamou, e nao numa copia.
void aluno_aplicar_bonus(Aluno *aluno, double bonus) {
    aluno->nota = aluno->nota + bonus;
}

// Cria um Aluno em memoria alocada dinamicamente. Diferente de uma variavel
// declarada dentro da funcao, esse registro continua existindo depois
// que a funcao termina, ate que alguem chame free.
Aluno *aluno_criar(int matricula, char turma, double nota) {
    Aluno *novo = malloc(sizeof(Aluno));
    if (novo == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }
    novo->matricula = matricula;
    novo->turma = turma;
    novo->nota = nota;
    return novo;
}

// Um ponteiro guarda o endereco de outra variavel e, por ele,
// e possivel ler e alterar essa variavel.
void demonstrar_ponteiro(void) {
    int idade = 19;
    int *p = &idade;   // p recebe o endereco de idade

    printf("idade = %d, *p = %d\n", idade, *p);
    printf("p == &idade vale %d\n", p == &idade);

    *p = 20;           // escreve na variavel idade passando pelo ponteiro
    printf("depois de *p = 20, idade = %d\n", idade);
}

// So a versao que recebe enderecos consegue trocar os valores de a e b.
void demonstrar_troca(void) {
    int a = 3;
    int b = 8;

    trocar_por_valor(a, b);
    printf("depois de trocar_por_valor(a, b): a = %d, b = %d\n", a, b);

    trocar(&a, &b);
    printf("depois de trocar(&a, &b): a = %d, b = %d\n", a, b);
}

// A quantidade de valores so e conhecida durante a execucao, entao a
// memoria e pedida com malloc e devolvida com free.
void demonstrar_alocacao(int quantidade) {
    int *valores = malloc(quantidade * sizeof(int));
    if (valores == NULL) {
        printf("erro: memoria insuficiente\n");
        exit(1);
    }

    for (int i = 0; i < quantidade; i++) {
        valores[i] = (i + 1) * 10;
    }
    printf("valores alocados:");
    for (int i = 0; i < quantidade; i++) {
        printf(" %d", valores[i]);
    }
    printf("\n");

    free(valores);    // devolve a memoria; o conteudo deixa de ser nosso
    valores = NULL;   // assim valores nao guarda mais um endereco invalido
}

// Campos acessados pelo ponto, pelo ponteiro com seta e por uma funcao
// que recebe o endereco do registro.
void demonstrar_struct(void) {
    Aluno aluno;
    aluno.matricula = 101;
    aluno.turma = 'A';
    aluno.nota = 7.5;
    aluno_imprimir(aluno);

    Aluno *pa = &aluno;
    pa->nota = 8.0;    // o mesmo que (*pa).nota = 8.0
    aluno_imprimir(aluno);

    aluno_aplicar_bonus(&aluno, 1.5);
    aluno_imprimir(aluno);
}

// Um aluno criado dinamicamente existe ate que free o devolva.
void demonstrar_struct_dinamica(void) {
    Aluno *novo = aluno_criar(102, 'B', 6.0);
    aluno_aplicar_bonus(novo, 1.0);
    aluno_imprimir(*novo);

    free(novo);       // devolve o registro criado por aluno_criar
    novo = NULL;
}

int main(void) {
    printf("== Ponteiro ==\n");
    demonstrar_ponteiro();

    printf("\n== Passagem por valor e por referencia ==\n");
    demonstrar_troca();

    printf("\n== Alocacao dinamica ==\n");
    demonstrar_alocacao(3);

    printf("\n== Struct ==\n");
    demonstrar_struct();

    printf("\n== Struct alocada dinamicamente ==\n");
    demonstrar_struct_dinamica();

    return 0;
}
