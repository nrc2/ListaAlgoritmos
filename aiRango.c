#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no{
	int id;
	int Z;

	struct no *prox;
	struct no *ant;
};

typedef struct no NO;

struct inicio{
	NO *primeiro;
	NO *ultimo;
	int tamanhoLista;
};

typedef struct inicio INICIO;

INICIO *inicializaLISTA(){
    INICIO *inicioLISTA = (INICIO*) malloc(sizeof (INICIO));
    inicioLISTA->primeiro = NULL;
    inicioLISTA->ultimo = NULL;
    inicioLISTA->tamanhoLista = 0;
    return inicioLISTA;
}

NO *criaNO(int a, int b){
    NO *aux = (NO*) malloc(sizeof (NO));
    aux->id = a;
    aux->Z = b;
    aux->ant = NULL;
    aux->prox = NULL;

    return aux;
}

void insereLista(NO *aux, INICIO *inicioLISTA){
    aux->prox = inicioLISTA->ultimo;
    if(inicioLISTA->tamanhoLista > 0)
        inicioLISTA->ultimo->ant = aux;
    inicioLISTA->ultimo = aux;
    inicioLISTA->tamanhoLista++;
    if(inicioLISTA->tamanhoLista == 1)
        inicioLISTA->primeiro = aux;
}

void cancelarPedido(INICIO *inicioLISTA, int a){
    NO *aux = inicioLISTA->ultimo;
    while(aux->id != a){
        aux = aux->prox;
        if(aux == NULL)//Caso o item não esteja na lista
            return;
    }
    if(aux->ant != NULL)
        aux->ant->prox = aux->prox;
    else{
        inicioLISTA->ultimo = aux->prox;
    }
    if(aux->prox != NULL)
        aux->prox->ant = aux->ant;
    else{
        inicioLISTA->primeiro = aux->ant;
    }
    free(aux);

    inicioLISTA->tamanhoLista--;
}

NO *entregarPedido(INICIO *inicioLISTA, int entregador){
    NO *aux = inicioLISTA->primeiro;
    if(aux == NULL){//Fila estava vazia
        return NULL;
    }
    if(inicioLISTA->tamanhoLista > 1){
        inicioLISTA->primeiro = aux->ant;
        aux->ant->prox = NULL;
    }
    else{
        inicioLISTA->primeiro = NULL;
        inicioLISTA->ultimo = NULL;
    }

    inicioLISTA->tamanhoLista--;
    return aux;
}

int descobreProximo(int **T, int numVert){
    int retorno = 0;
    int abertos = 0;
    int primeiro = 1;

    for(int i = 0; i < numVert; i++){
        if(T[1][i] == 1){
            if(T[0][i] <= T[0][retorno] || primeiro == 1){
                retorno = i;
                abertos = 1;
                primeiro = 0;
            }
        }
    }
    if(abertos == 0)
        return -1;

    return retorno;

}

void distColeta(int **t, int numVert, int **grafo, int inicial){
    int aux;

    for(int i = 0; i < numVert; i++){
        t[0][i] = 9999999; //Menor caminho ao vértice
        t[1][i] = 1;       //1 para aberto e 0 para fechado
    }
    aux = inicial;

    t[0][aux] = 0;    //Vértice onde começa o trajeto

    while(1){    //Enquanto houver vértice aberto
        if(aux == -1)   //Nao há vértices disponíveis
            break;

        t[1][aux] = 0;
        for(int i = 0; i < numVert; i++){
            if(grafo[aux][i] > 0){ //É um vértice adjacente
                if((grafo[aux][i] + t[0][aux]) < t[0][i]){
                    t[0][i] = grafo[aux][i] + t[0][aux];
                }
            }
        }
        aux = descobreProximo(t, numVert);
    }
}

void menorDistancia(int ***tabelasDijkstra, int **grafo, int *M, int a, NO *dlv, int numVert, int *N, int n){

    int Y = N[0];  //Local onde o pedido deve ser retirado
    int y = 0;

    int destino = dlv->Z;
    int ID = dlv->id;
    int custoTotal;

    if(M[a] != Y){  //O motorista não está em uma loja
        int custoFinal[n];

        for(int i = 0; i < n; i++){
            custoFinal[i] = tabelasDijkstra[M[a]][0][N[i]] + tabelasDijkstra[N[i]][0][destino];
        }
        custoTotal = custoFinal[0];
        y = 0;
        for(int i = 1; i < n; i++){
            if(custoFinal[i] < custoTotal){
                custoTotal = custoFinal[i];
                y = i;
            }
        }
    }
    else{
        custoTotal = tabelasDijkstra[M[a]][0][destino];
    }

    printf("%d %d %d %d %d\n", ID, M[a], N[y], destino, custoTotal);
    M[a] = destino;
}

int ***gerarTodasDistancias(int V, int **grafo){
    int ***t = (int ***)malloc(V * sizeof(int **));
    for(int i = 0; i < V; i++){
        t[i] = (int **)malloc(2 * sizeof(int *));
        for(int j = 0; j < 2; j++){
            t[i][j] = (int *)malloc(V * sizeof(int ));
        }
    }

    for(int i = 0; i < V; i++){
        distColeta(t[i], V, grafo, i);
    }

    return t;
}

int main()
{
    int x;
    INICIO *inicioLISTA = inicializaLISTA();

    scanf("%d", &x);
    int V = x;  //Número de localidades (vértices)

    scanf("%d", &x);
    int E = x;  //Número de vias interligando essas localidades (arestas)

    scanf("%d", &x);
    int N[x];   //Quantidade de lojas da rede
    int n = x;

    scanf("%d", &x);
    int M[x];   //Número de entregadores
    int m = x;

    int **grafo = (int **)malloc(V * sizeof(int *));
    for(int i = 0; i < V; i++){
        grafo[i] = (int *)malloc(V * sizeof(int));
    }

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(i == j) grafo[i][j] = 0;
            else grafo[i][j] = -1;
        }
    }

    for (int i = 0; i < E; i++){    //Preenchimento do grafo
        int a, b, c;

        scanf("%d", &a);    //Primeiro vértice
        scanf("%d", &b);    //Segundo vértice
        scanf("%d", &c);    //Tamanho da aresta

        grafo[a][b] = c;
        grafo[b][a] = c;
    }

    for (int i = 0; i < n; i++){    //Preenchimento das localidades dos restaurantes
        int a;
        scanf("%d", &a);
        N[i] = a;
    }

    for (int i = 0; i < m; i++){    //Preenchimento das localidades dos entregadores
        M[i] = N[0];
    }

    int ***tabelasDikjstra = gerarTodasDistancias(V, grafo);

    char tipo[4];
    while(1){
        int a, b;
        NO *aux = NULL;

        scanf("%s", tipo);

        if(strcmp(tipo, "NEW") == 0){
            scanf("%d", &a);    //id I
            scanf("%d", &b);    //localidade Z

            aux = criaNO(a, b);
            insereLista(aux, inicioLISTA);
            printf("+%d %d\n", a, inicioLISTA->tamanhoLista);
        }
        else if(strcmp(tipo, "CEL") == 0){
            scanf("%d", &a);    //id I

            cancelarPedido(inicioLISTA, a);
            printf("-%d %d\n", a, inicioLISTA->tamanhoLista);
        }
        else if(strcmp(tipo, "DLV") == 0){  //DLD D indica que o entregador D aceitou o próximo pedido da fila
            scanf("%d", &a);    //delivery D
            NO *dlv = entregarPedido(inicioLISTA, a); //Obter o pedido
            menorDistancia(tabelasDikjstra, grafo, M, a, dlv, V, N, n);
        }
        else break;
    }

    return 0;
}
