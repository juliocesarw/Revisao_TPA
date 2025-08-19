#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cstring>
#include <ctime>

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[70];
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
int repetidos = 0;

void inicializa(){
    for (int i = 0; i < 100; i++) // vou alterar de acordo com a necessidade
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
int compareString(const void *a, const void *b);

//============================================================================================
bool insere(Aluno *y, int indiceHash) {
    if (y == NULL) return false;

    // Lista vazia
    if (a[indiceHash].quantidade == 0) {
        a[indiceHash].inicio = a[indiceHash].fim = y;
        a[indiceHash].quantidade++;
        return true;
    }

    // Percorre para achar a posição correta por nome
    Aluno *atual = a[indiceHash].inicio;
    while (atual != NULL && strcmp(atual->cpf, y->cpf) < 0) {
        atual = atual->prox;
    }

    //ja existe igual
    if (atual != NULL && strcmp(atual->cpf, y->cpf) == 0){
        repetidos++;
        return false;
    }
    
    if (atual == a[indiceHash].inicio) {
        // Inserir no início
        y->prox = a[indiceHash].inicio;
        a[indiceHash].inicio->ante = y;
        a[indiceHash].inicio = y;
    } else if (atual == NULL) {
        // Inserir no final
        y->ante = a[indiceHash].fim;
        a[indiceHash].fim->prox = y;
        a[indiceHash].fim = y;
    } else {
        // Inserir no meio
        y->prox = atual;
        y->ante = atual->ante;
        atual->ante->prox = y;
        atual->ante = y;
    }

    a[indiceHash].quantidade++;
    return true;
}

//funcao para fazer alocacao de memoria do tananho da struct
Aluno *lerAluno(){
    
    Aluno *b = new Aluno;
    b->ante = NULL;
    b->prox = NULL;
    return b;
}

//funcao para imprimir o aluno na busca
void imprimirAlunos(){
    int contador = 0;
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
            contador++;
        }
    }
    printf("\nprintou %d\n", contador);
    system("pause");
}

//funcao para abrir o arquivo
FILE * abrir_arquivo(const char * arquivo, const char * modo){

	FILE * arq;
	arq = fopen(arquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        //system("pause");
    }
	return arq;
}

//funcao para fazer todo o processo de insercao, desde a leitura ate a gravacao na struct
void processoInsercao(){
    FILE * arq;
    arq = abrir_arquivo("../alunos_completos.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        int ultimosDigitos = retornaValorCPF(c->cpf);
        insere(c, ultimosDigitos);
    }
    fclose(arq);
}

//funcao de menu
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

//funcao de menu
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

//funcao que verifica se o CPF ja foi cadastrado e printa quantos indices estao sendo vistos
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

//funcao de pesquisar e imprimir, dando a opcao de excluir o cpf desejado
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

//funcao para excluir o aluno do sistema
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

// funcao para retornar o indice para a tabela hash
int retornaValorCPF(char * cpf){

    char var[3];
    var[0] = cpf[12];
    var[1] = cpf[13];
    var[2] = '\0';
    return atoi(var);
}

int compareString(const void *a, const void *b) {

    const Aluno * aa = (const Aluno *)a;
    const Aluno * bb = (const Aluno*)b; 

    return strcmp(aa->nome, bb->nome);
}

void ordenar(){

    
    for (int i = 0; i < 100; i++)
    {
        Aluno * array[a[i].quantidade];
        Aluno * ponteiro = a[i].inicio;

        for (int j = 0; j < a[i].quantidade; j++)
        {
            array[j] = ponteiro;
            ponteiro = ponteiro->prox;
        }//for

        qsort(array, a[i].quantidade, sizeof(array[0]), compareString);
        
        // fazendo os apontamentos corretos
        for ( int r = 0; r < a[i].quantidade; r++)
        {
            if(r == 0){
                array[r]->prox = array[r + 1];
                array[r]->ante = NULL;
            }//if
            else if (r == 99){
                array[r]->prox == NULL;
                array[r]->ante = array[r - 1];
            }//else if
            else{
                array[r]->ante = array[r - 1];
                array[r]->prox = array[r + 1];
            }//else
        }//for

        // for (int x = 0; x < a[i].quantidade; x++)
        // {
        //     ponteiro 
        // }
        


    }//for

    //ordernar

    

    // devolvendo para  a lista os nomes em ordem
    // for (int i = 0; i < 100; i++)
    // {
    //     Aluno * ponteiro = a[i].inicio;
    //     for (int i = 0; i < a[i].quantidade; i++)
    //     {
    //         ponteiro-
    //     }
    // }
    

    
}

//funcao principal
int main(){

    char nomes[10][21] = {
        "Joao"
        "Bruno",
        "Diego",
        "Carla",
        "Henrique",
        "Ana",
        "Gabriela",
        "Isabela",
        "Felipe",
        "Eduarda",
    };
    qsort(nomes, 10, sizeof(nomes[0]), compareString);

    for (int i = 0; i < 10; i++)
    {
        printf("%s\n", nomes[i]);
    }
    


    // time_t inicio, fim;
    // inicializa();
    
    // inicio = clock();
    // processoInsercao();
    // fim = clock();

    // printf("Tempo de leitura: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    // printf("Foram lidos %d repetidos\n", repetidos);
    // system("pause");
    // menu();

    return 0;
}
