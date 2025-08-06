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
Aluno * verificacaoMatricula(char * matricula);
Aluno * verificacaoCPF(char * cpf);
void pesquisaPorMatricula();
void pesquisarPorCPF();
void excluir(Aluno * aluno);

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

        if(verificacaoCPF(y->cpf) == NULL && verificacaoMatricula(y->matricula) == NULL){
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
            pesquisarPorCPF();
        break;
        case 2:
            pesquisaPorMatricula(); 
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

Aluno * verificacaoMatricula(char * matricula){

    system("cls");
    
    Aluno * percorre = a.inicio;

    while (percorre != NULL){
        if(strcmp(percorre->matricula, matricula) == 0){
            return percorre;
            break;
        }
        percorre = percorre->prox;
    }
    
    return NULL;
}

Aluno * verificacaoCPF(char * cpf){

    system("cls");
    
    Aluno * percorre = a.inicio;

    while (percorre != NULL){
        if(strcmp(percorre->cpf, cpf) == 0){
            return percorre;
            break;
        }
        percorre = percorre->prox;
    }
    
    return NULL;
}

void pesquisaPorMatricula(){
    system("cls");
    char matricula[9];
    printf("Digite a matricula: ");
    scanf("%s", matricula);

    Aluno * existe = verificacaoMatricula(matricula);
    if(existe != NULL){
        printf("Matricula: %s\n", existe->matricula);
        printf("CPF: %s\n", existe->cpf);
        printf("Nome: %s\n", existe->nome);
        printf("Nota: %.2lf\n", existe->nota);
        printf("Idade: %d\n", existe->idade);
        printf("Curso: %s\n", existe->curso);
        printf("Cidade: %s\n", existe->cidade);

        printf("\nDeseja excluir esse aluno? (S/N): ");
        char opcao;
        scanf(" %c", &opcao);       
        if(toupper(opcao) == 'S'){
            excluir(existe);
            printf("Aluno excluido com sucesso.\n");
        }
        else{
            printf("Exclusao cancelada.\n");
        }
    }
    else{
        printf("Matricula nao encontrada.\n");
    }
    system("pause");
}

void pesquisarPorCPF(){
    system("cls");
    char cpf[15];
    printf("Digite o CPF: ");
    scanf("%s", cpf);

    Aluno * existe = verificacaoCPF(cpf);
    if(existe != NULL){
        printf("Matricula: %s\n", existe->matricula);
        printf("CPF: %s\n", existe->cpf);
        printf("Nome: %s\n", existe->nome);
        printf("Nota: %.2lf\n", existe->nota);
        printf("Idade: %d\n", existe->idade);
        printf("Curso: %s\n", existe->curso);
        printf("Cidade: %s\n", existe->cidade);

        printf("\nDeseja excluir esse aluno? (S/N): ");
        char opcao;   
        scanf(" %c", &opcao);       
        if(toupper(opcao) == 'S'){  
            excluir(existe);
            printf("Aluno excluido com sucesso.\n");
        }
        else{
            printf("Exclusao cancelada.\n");
        }
    }
    else{
        printf("CPF nao encontrado.\n");
    }
    system("pause");
}

void  excluir(Aluno * aluno){
    Aluno * aux = aluno;
    if(aux == a.inicio && aux == a.fim){
        //so tem um aluno
        a.inicio = NULL;
        a.fim = NULL;
    }
    else if(aux == a.inicio){
        //primeiro
        a.inicio = aux->prox;
        aux->prox->ante = NULL;
    }
    else if(aux == a.fim){
        //ultimo
        a.fim = aux->ante;
        aux->ante->prox = NULL;
    }
    else{
        //meio
        aux->ante->prox = aux->prox;
        aux->prox->ante = aux->ante;
    }
}

int main(){

    inicializa();
    processoInsercao();
    menu();

    return 0;
}
