#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cstring>

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

//declaracao de funcoes
bool insere(Aluno *y); 
Aluno *lerAluno();
void imprimirAlunos();  
FILE * abrir_arquivo( const char * arquivo, const char * modo);
void processoInsercao();
void menu();
int escolha();
int compararString(char * a, char * b);
bool insere(Aluno *y, char * nome, char * cpf);
bool buscarPorMatricula(char * matricula);
bool buscarPorCpf(char * cpf);

//============================================================================================
bool insere(Aluno *y){
    if(y == NULL) return false;
    if(a.quantidade == 0){
        a.inicio = y;
        a.fim = y;
        a.quantidade++;
    }
    else{
        Aluno * var = a.inicio;
        while ( var->prox != NULL && compararString(var->nome, y->nome) < 0){
            var = var->prox;
        }

        if(buscarPorCpf(y->cpf) == false && buscarPorMatricula(y->matricula) == false){
            //esse CPF nao foi cadastrado
            if(var->prox == NULL && var->ante != NULL){
                //ultimo
                int n = compararString(var->nome, y->nome);
                if(n < 0){
                    var->prox = y;
                    y->ante = var;
                    y->prox = NULL;
                    a.fim = y;
                }
                else{
                    var->ante->prox = y;
                    y->prox = var;
                    var->ante = y;
                    a.fim = var;
                }
                
            }
            else if (var->ante == NULL){
                //primeiro
                a.inicio = y;
                y->prox = var;
                a.quantidade++;
                var->ante = y;
            }
            else{
                //meio
                var->ante->prox = y;
                var->ante = y;
                y->prox = var;
            }
        }
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

    system("cls");

    Aluno * x = a.inicio;

    while (x != NULL){
        printf("%s -", x->matricula);
        printf(" %s -", x->cpf);
        printf(" %s -", x->nome);
        printf(" %.2lf -", x->nota);
        printf(" %d -", x->idade);
        printf(" %s -", x->curso);
        printf(" %s", x->cidade);
        printf("\n");
        x = x->prox;

    }

    system("pause");
}

FILE * abrir_arquivo(const char * arquivo, const char * modo){

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

int compararString(char * a, char * b){
    int n = strcmp(a, b);
    if(n == 0) return 1; //iguais
    else if (n < 0) return -1; // a vem primeiro que b
    else return 0; // b vem primeiro que a
}

int escolha(){
    
    int op;
    system("cls");
    printf("\t\tMENU DE PESQUISA\n\n");
    printf("1 - PESQUISAR POR CPF\n");
    printf("2 - PESQUISAR POR MATRICULA\n");
    printf("3 - EXCLUIR\n");
    printf("4 - IMPRIMIR\n");
    printf("0 - SAIR\n\n");
    
    printf("Opcao: ");
    scanf("%d", &op);
    return op;
}

void menu(){
    int x;
    do
    {
        x = escolha();
        switch (x)
        {
        case 1:
            //buscarPorCpf(); não funciona ainda
        break;
        case 2:
            //buscarPorMatricula(); 
        break;
        case 3:
        break;
        case 4:
            imprimirAlunos();
        break;
        default:
            break;
        }
    } while (x != 0);
}

bool buscarPorMatricula(char * matricula){

    system("cls");
    
    Aluno * percorre = a.inicio;

    while (percorre != NULL){
        if(strcmp(percorre->matricula, matricula) == 0){
            return true;
            break;
        }
        percorre = percorre->prox;
    }
    
    return false;
}

bool buscarPorCpf(char * cpf){

    system("cls");
    
    Aluno * percorre = a.inicio;

    while (percorre != NULL){
        if(strcmp(percorre->cpf, cpf) == 0){
            return true;
            break;
        }
        percorre = percorre->prox;
    }
    
    return false;
}

int main(){

    inicializa();
    processoInsercao();
    menu();

    return 0;
}
