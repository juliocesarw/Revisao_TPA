#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cstring>
#include <ctime>

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

Alunos a[100];

int insercao = 0;

void inicializa(){
    for (int i = 0; i < 100; i++)
    {
        a[i].inicio = NULL;
        a[i].fim = NULL;
        a[i].quantidade = 0;
    }
    
}

//declaracao de funcoes
Aluno *lerAluno();
void imprimirAlunos();  
FILE * abrir_arquivo( const char * arquivo, const char * modo);
void processoInsercao();
void menu();
int escolha();
bool insere(Aluno *y, int indiceHash);
Aluno * verificacaoCPF(char * cpf, int indice);
void pesquisarPorCPF();
void excluir(Aluno * ponteiro, int indice);
int retornaValorCPF(char * cpf);

//============================================================================================
bool insere(Aluno *y, int indiceHash){

    if(y == NULL) return false;
    if(a[indiceHash].quantidade == 0){
        a[indiceHash].inicio = y;
        a[indiceHash].fim = y;
        a[indiceHash].quantidade++;
    }
    else{
        Aluno * percorre = a[indiceHash].inicio;
        while (percorre->prox != NULL && strcmp(percorre->nome, y->nome) < 0)
        {
            percorre = percorre->prox;
        }

        if(verificacaoCPF(y->cpf, indiceHash) == NULL){
            if(percorre->ante == NULL){
                //talvez vai ser o primeiro da lista
                if(percorre->prox == NULL){
                    //so tinha um elemento na lista
                    if(strcmp(percorre->nome, y->nome) < 0){
                        //o elemento a ser inserido deve ser o ultimo
                        a[indiceHash].inicio->prox = y;
                        y->ante = a[indiceHash].inicio;
                        a[indiceHash].fim = y;
                        a[indiceHash].quantidade++;
                    }
                    else{
                        //o elemento inserido deve ser o primeiro
                        a[indiceHash].inicio->ante = y;
                        y->prox = a[indiceHash].inicio;
                        a[indiceHash].inicio = y;
                        a[indiceHash].quantidade++;
                    }
                }
                else{
                    //tinha mais que um, entao o codigo brekou porque ele deveria realmente ser o primeiro
                    a[indiceHash].inicio->ante = y;
                    y->prox = a[indiceHash].inicio;
                    a[indiceHash].inicio = y;
                    a[indiceHash].quantidade++;
                }
            }
            else if(percorre->prox == NULL){
                // talvez vai ser o ultimo da lista
                if(strcmp(percorre->nome, y->nome) < 0){
                    //realmente vai ser o ultimo da litsa
                    a[indiceHash].fim->prox = y;
                    y->ante = a[indiceHash].fim;
                    a[indiceHash].fim = y;
                }
                else{
                    //vai ser o penultimo
                    y->ante = a[indiceHash].fim->ante;
                    a[indiceHash].fim->ante->prox = y;
                    y->prox = a[indiceHash].fim;
                    a[indiceHash].fim->ante = y;

                }
                a[indiceHash].quantidade++;
            }
            else{
                //ta no meio
                y->prox = percorre;
                percorre->ante->prox = y;
                y->ante = percorre->ante;
                percorre->ante = y;
                a[indiceHash].quantidade++;
            }
            insercao++;
        }
        else{
            return false;        
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

    // system("cls");

    for ( int i = 0; i < 100; i++)
    {
        Aluno * x = a[i].inicio;
    
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
    }
    

    system("pause");
}

FILE * abrir_arquivo(const char * arquivo, const char * modo){

	FILE * arq;
	arq = fopen(arquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        //system("pause");
    }
	return arq;

}

void processoInsercao(){
    FILE * arq;
    arq = abrir_arquivo("../alunos.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        int ultimosDigitos = retornaValorCPF(c->cpf);
        insere(c, ultimosDigitos);
    }
    fclose(arq);
}

int escolha(){
    
    int op;
    system("cls");
    printf("\t\tMENU DE PESQUISA\n\n");
    printf("1 - PESQUISAR POR CPF\n");
    printf("2 - IMPRIMIR\n");
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
            imprimirAlunos();
        break;
        default:
            printf("\n\nopcao inválida!!\n\n");
            system("pause");
        break;
        }
    } while (x != 0);
}

// Aluno * verificacaoCPF(char * cpf, int indice){

//     //system("cls");
    
//     Aluno * percorre = a[indice].inicio;

//     while (percorre != NULL){
//         if(strcmp(percorre->cpf, cpf) == 0){
//             return percorre;
//             break;
//         }
//         percorre = percorre->prox;
//     }
    
//     return NULL;
// }

Aluno * verificacaoCPF(char * cpf, int indice){

    //system("cls");
    int contador=0;
    int digito = retornaValorCPF(cpf);
    Aluno * percorre = a[indice].inicio;

    while (percorre != NULL){
        if(strcmp(percorre->cpf, cpf) == 0){
            printf("indice %d: %d\n",digito,contador);
            return percorre;
            break;
        }
        contador++;
        percorre = percorre->prox;
    }
    printf("indice %d: %d\n",digito,contador);
    return NULL;
}

void pesquisarPorCPF(){
    //system("cls");
    char cpf[15];
    printf("Digite o CPF: ");
    scanf("%s", cpf);
    int i = retornaValorCPF(cpf);
    Aluno * existe = verificacaoCPF(cpf, i); // retorna um ponteiro para o registo

    if(existe != NULL){
        printf("\nMatricula: %s\n", existe->matricula);
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
            excluir(existe, i);
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

void  excluir(Aluno * ponteiro, int indice){
    Aluno * aux = ponteiro;
    if(aux == a[indice].inicio && aux == a[indice].fim){
        //so tem um aluno
        a[indice].inicio = NULL;
        a[indice].fim = NULL;
    }
    else if(aux == a[indice].inicio){
        //primeiro
        a[indice].inicio = aux->prox;
        a[indice].inicio->ante = NULL;
        free(aux);
    }
    else if(aux == a[indice].fim){
        //ultimo
        a[indice].fim = aux->ante;
        a[indice].fim->prox = NULL;
        free(aux);
    }
    else{
        //meio
        aux->ante->prox = aux->prox;
        aux->prox->ante = aux->ante;
        free(aux);
    }
}

int retornaValorCPF(char * cpf){
    char var[3];
    var[0] = cpf[12];
    var[1] = cpf[13];
    var[2] = '\0';
    return atoi(var);
}

int main(){

    time_t inicio, fim;
    inicio = clock();

    inicializa();
    processoInsercao();

    fim = clock();
    printf("Tempo de leitura: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("A o numero de insercao foi %d\n", insercao);
    system("pause");
    menu();

    //17 MINUTOS DE INSERCAO PELO TERMINAL DO VSCODE
    //13 MINUTOS DE INSERCAO PELO TERMINAL DO WINDOWNS

    return 0;
}