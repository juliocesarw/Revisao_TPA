#include <cstdio>
#include <cstdlib>
#include <ctype.h>

//Matricula,CPF,Nome,Nota,Idade,Curso,Cidade
//A0000000,915.216.859-08,Wallace Sampaio,20.35,23,Direito,Rio de Janeiro

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *prox;
    Aluno *ante;
};

struct Alunos{
    Aluno *inicio;
    Aluno *fim;
    int quantidade;
};

Alunos a;

void inicializa(){
    a.inicio = NULL;
    a.fim = NULL;
    a.quantidade = 0;
}

bool insere(Aluno *y){
    if(y == NULL) return false;
    if(a.quantidade == 0){
        a.inicio = y;
        a.fim = y;
        a.quantidade++;
    }
    else{
        Aluno * var = a.inicio;
        while (var->prox != NULL)
        {
            var = var->prox;
        }
        var->prox = y;
        y->ante = var;
        a.fim = y;
        a.quantidade++;
    }
    return true;
}


Aluno *lerAluno(){
    
    Aluno *b = new Aluno;
    b->ante = NULL;
    b->prox = NULL;
    return b;
}

void imprimirAlunos(){
    Aluno * x = a.inicio;

    while (x != NULL){
        printf("\n\n");
        printf("%s -", x->matricula);
        printf(" %s -", x->cpf);
        printf(" %s -", x->nome);
        printf(" %.2lf -", x->nota);
        printf(" %d -", x->idade);
        printf(" %s -", x->curso);
        printf(" %s", x->cidade);
        printf("\n\n");
        x = x->prox;

    }
}

FILE * abrir_arquivo(char * arquivo, char * modo){

	FILE * arq;
	arq = fopen(arquivo, modo);
    if (arq == NULL){
        printf("Erro");
    }
    else{
        printf("Arquivo abeto com sucesso\n\n");
    }
	return arq;

}

void processoInsercao(){
    FILE * arq;
    arq = abrir_arquivo("../teste.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        insere(c);
    }
    fclose(arq);
}

int escolha(){
    
    int op;
    system("cls");
    printf("\n\n\t\tMENU DE PESQUISA\n\n");
    printf("1 - PESQUISAR POR CPF\n");
    printf("2 - PESQUISAR POR MATRICULA\n");
    printf("4 - IMPRIMIR\n");
    printf("0 - SAIR\n\n");
    
    printf("Opcao: ");
    scanf("%d", &op);
    return op;
}

void menu(int op){
    int x;
    do
    {
        x = escolha();
        switch (x)
        {
        case 1:

        break;
        case 2:
        break;
        
        default:
            break;
        }
    } while (op != 0);
    
}

bool buscarPorMatricula(){
    char matricula[9];
    printf("\nDigite a Matricula: ");
    scanf("%s", matricula);

    Aluno * percorre = a.inicio;
    

}

int main(){

    inicializa();
    processoInsercao();
    imprimirAlunos();

    return 0;
}
