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

// Alunos a[100]; //100
// Alunos a[1000]; //mil 
// Alunos a[10000]; //10k
Alunos a[100000]; //100k

// struct para armazenar os 10 nomes
struct nomes
{
    char nome [70];
    nomes *prox;
};

struct ponteiroNome
{
    nomes * inicio;
    nomes * final;
    int quantidade;
};

ponteiroNome n;

int insercao = 0;
int cpfRepetido = 0;

void inicializa(){
    for (int i = 0; i < 100000; i++) // vou alterar de acordo com a necessidade
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
// bool pesquisaGeral();

//============================================================================================
bool insere(Aluno *y, int indiceHash) {
    if (y == NULL) return false;

    Alunos &lista = a[indiceHash];

    // Verifica se o CPF já existe
    if (verificacaoCPF(y->cpf, indiceHash) != NULL) {
        cpfRepetido++;
        return false;
    }

    // Lista vazia
    if (lista.quantidade == 0) {
        lista.inicio = lista.fim = y;
        lista.quantidade++;
        insercao++;
        return true;
    }

    // Percorre para achar a posição correta por nome
    Aluno *atual = lista.inicio;
    while (atual != NULL && strcmp(atual->nome, y->nome) < 0) {
        atual = atual->prox;
    }

    if (atual == lista.inicio) {
        // Inserir no início
        y->prox = lista.inicio;
        lista.inicio->ante = y;
        lista.inicio = y;
    } else if (atual == NULL) {
        // Inserir no final
        y->ante = lista.fim;
        lista.fim->prox = y;
        lista.fim = y;
    } else {
        // Inserir no meio
        y->prox = atual;
        y->ante = atual->ante;
        atual->ante->prox = y;
        atual->ante = y;
    }

    lista.quantidade++;
    insercao++;
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

    // system("cls");

    for ( int i = 0; i < 1000; i++)
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

    char var[6];
    var[0] = cpf[8];
    var[1] = cpf[9];
    var[2] = cpf[10];
    var[3] = cpf[12];
    var[4] = cpf[13];
    var[5] = '\0';
    return atoi(var);
}

bool pesquisaPorNome(char * nome){

    for (int i = 0; i < 100000; i++)
    {
        Aluno * percorre = a[i].inicio;
        while (percorre != NULL){
            if(strcmp(percorre->nome, nome) == 0){
                return true;
            }
            else if (strcmp(percorre->nome, nome) > 0){
                break;
            }
            else{
                percorre = percorre->prox;
            }
        }
    }
    return false;
}

void pesquisaGeral(){
    nomes *ponteiro = n.inicio;

    while (ponteiro != NULL) { // percorre até acabar a lista
        if (pesquisaPorNome(ponteiro->nome)) {
            // printf("%s foi encontrado\n\n", ponteiro->nome);
        }
        ponteiro = ponteiro->prox; // sempre avança
    }
}

void inicializaNomes(){
    n.inicio = NULL;
    n.final = NULL;
    n.quantidade = 0;
}

//função para inserir nomes
void insereNomes(){
    FILE * p = abrir_arquivo("../nomes.csv", "r");

    while (!feof(p)){
        nomes *c = new nomes;
        c->prox = NULL;
        fscanf(p, "%[^\n]\n", c->nome);

        if(n.inicio == NULL){
            n.inicio = c;
            n.final = c;
        }
        else{
            n.final->prox = c;
            n.final = c;
        }
        n.quantidade++;
    }
}

void tempo() {
    clock_t inicio, fim;
    double soma = 0.0;

    for (int i = 0; i < 100; i++) {
        inicio = clock();
        pesquisaGeral();
        fim = clock();
        soma += (double)(fim - inicio);
    }

    double media = soma / 100; // média em ticks
    printf("Tempo médio de leitura: %.6lf segundos\n", media / CLOCKS_PER_SEC);
}

void imprimirNomes(){
    nomes * c = n.inicio;

    while (c != NULL)
    {
        printf("%s\n", c->nome);
        c = c->prox;
    }
    
}

//funcao principal
int main(){

    time_t inicio, fim;
    inicializa();
    
    inicio = clock();
    processoInsercao();
    fim = clock();

    printf("Tempo de leitura: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("A o numero de insercao foi %d\n", insercao);
    printf("A o numero de CPF repetido foi %d\n", cpfRepetido);
    system("pause");
    // menu();

    inicializaNomes();
    insereNomes();
    printf("Foram inseridos %d nomes\n", n.quantidade);
    // imprimirNomes();
    
    tempo();

    // HASH DE 100 - MELHOR TEMPO: 10 MINUTOS NA INSERÇÃO E 0.1 SEGUNDOS NA BUSCA DE 10 NOMES
    // HASH DE 1000 - MELHOR TEMPO: 2 MINUTO E 6 SEGUNDOS NA INSERÇÃO E 0.1 SEGUNDOS NA BUSCA DE 10 NOMES
    // HASH DE 10000 - MELHOR TEMPO: 1 MINUTO E 14 SEGUNDOS MINUTOS NA INSERÇÃO E 0.1 SEGUNDOS NA BUSCA DE 10 NOMES
    // HASH DE 100000 - MELHOR TEMPO: 57 SEGUNDOS NA INSERÇÃO E 0.2 SEGUNDOS NA BUSCA DE 10 NOMES

    return 0;
}
