#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minDistance(int dist[], bool sptSet[], int V)
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int **graph, int src, int src2, int V)
{
    int dist[V];

    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {

        int u = minDistance(dist, sptSet, V);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)

            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    if (dist[src2] != INT_MAX)
    {
        printf("%d\n", dist[src2]);
    }
    if (dist[src2] == INT_MAX)
    {
        printf("-1\n");
    }
}

/* // Calcula as distâncias de todos os pontos entres si
int** floyd_warshall(int** grafo, int n_vertices) {

    // Aloca a matriz que irá guardar as distâncias entre os vértices
    int** weights = new int*[n_vertices];
    for (register int j = 0; j < n_vertices; j++) weights[j] = new int[n_vertices];
    
    // Guarda os pesos mapeados do próprio grafo
    for (register int i = 0; i < n_vertices; i++) {
        for (register int j = 0; j < n_vertices; j++) {
            weights[i][j] = grafo[i][j];
        }
    }

    // Calcula as distâncias pelo floyd warshall
    for (register int k = 0; k < n_vertices; k++) {
        for (register int i = 0; i < n_vertices; i++) {
            for (register int j = 0; j < n_vertices; j++) {
                if (weights[i][j] > weights[i][k] + weights[k][j] && weights[k][j] != INT16_MAX) {
                    weights[i][j] = weights[i][k] + weights[k][j];
                }
            }
        }
    }

    // Retorna as distâncias calculadas  
    return weights;
} */

int main()
{

    int V, E; // número de vértices e arestas

    scanf("%d %d", &V, &E);

    int **grafo = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        grafo[i] = (int *)malloc(V * sizeof(int));
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                grafo[i][j] = 0;
            else
                grafo[i][j] = -1;
        }
    }

    int i;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                grafo[i][j] = 0;
            else
                grafo[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++)
    { // Preenchimento do grafo

        int a, b;
        scanf("%d", &a); // Primeiro v�rtice
        scanf("%d", &b); // Segundo v�rtice

        grafo[a][b] = 1;
        grafo[b][a] = 1;
    }

     for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
 
    char opr[4];
    int nos = V; // variável para contar a quantidade de vertices distintos;
    int grau = 0;
    int contraido[V];

    while (strcmp(opr, "END") != 0)
    {
        int A, B; // Vertices a serem trabalhados
        scanf(" %s %d %d", opr, &A, &B);

        if (strcmp(opr, "CTR") == 0)
        {
            nos--;
            grau = 0;
            for (int j = 0; j < V; j++)
            { // iguala a linha dos vertices contraídos
                if ((grafo[A][j] == 1 || grafo[B][j] == 1) && (j != A && j != B))
                {
                    grafo[A][j] = 1;
                    grafo[B][j] = 1;

                    grau++;
                }

                grafo[A][B] = 0;
                grafo[B][A] = 0;
            }

            for (int j = 0; j < V; j++)
            {
                if ((grafo[j][A] == 1 || grafo[j][B] == 1) && (j != A && j != B))
                {
                    grafo[j][A] = 1;
                    grafo[j][B] = 1;
                }
                grafo[A][B] = 0;
                grafo[B][A] = 0;
            }

             for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    printf("%d ", grafo[i][j]);
                }
                printf("\n");
            }

            printf("%d %d\n", nos, grau);
        } 

        else if (strcmp(opr, "DIS") == 0)
        {
            dijkstra(grafo, A, B, V);
        }
    }

    return 0;
}