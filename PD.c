#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    
    int n, m; // tam do índ das var, tam do índ das const

    while(scanf("%d %d", &n, &m) != EOF){

    int V[n], C[m]; // vetor de variáveis, vetor de constantes

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &V[i]);
        // printf("%d ", V[i]);
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &C[i]);
        // printf("%d ", C[i]);
    }
    int valor; // para auxiliar em algumas contas

    int **matriz = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i < (m + 1); i++)
    {
        matriz[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i < m + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (i == 0 || j == 0)
                matriz[i][j] = -9999999;

            else
                matriz[i][j] = 0;

            // printf("%d ", matriz[i][j]);
        }
        // printf("\n");
    }


int flag = 0;
    for (int i = 1; i < (m + 1); i++)
    {
        for (int j = 1; j < (n - (m - i - 1)); j++)
        {
            if(i == 2){
                    flag = 1;
            }
            // printf("\n%d\n", i);
            if (matriz[i - 1][j - 1] == -9999999 && flag == 0)
            {
                valor = ((C[i - 1]) * (V[j - 1]));
                //printf("%d\n", C[i - 1]);
                //printf("%d\n", V[j - 1]);
                //printf("\nvalor: %d\n\n", valor);
                if (valor > matriz[i][j - 1])
                {
                    matriz[i][j] = valor;
                    //printf("na matriz: %d\n\n", matriz[i][j]);

                    /* for (int i = 0; i < m + 1; i++)
                    {
                        for (int j = 0; j < n + 1; j++)
                        {
                             printf("%d ", matriz[i][j]);
                        }
                         printf("\n");
                    } */
                }
                else
                {
                    matriz[i][j] = matriz[i][j - 1];
                     //printf("%d\n\n", matriz[j][i]);
                     /* for (int i = 0; i < m + 1; i++)
                    {
                        for (int j = 0; j < n + 1; j++)
                        {
                             printf("%d ", matriz[i][j]);
                        }
                         printf("\n");
                    } */
                }
            }

            else
            {

                if (matriz[i - 1][j - 1] + (C[i - 1] * V[j - 1]) > matriz[i][j - 1])
                {

                    matriz[i][j] = matriz[i - 1][j - 1] + (C[i - 1] * V[j - 1]);
                     /* for (int i = 0; i < m + 1; i++)
                    {
                        for (int j = 0; j < n + 1; j++)
                        {
                             printf("%d ", matriz[i][j]);
                        }
                         printf("\n");
                    } */
                }

                else
                {
                    matriz[i][j] = matriz[i][j - 1];
                    /*  for (int i = 0; i < m + 1; i++)
                    {
                        for (int j = 0; j < n + 1; j++)
                        {
                             printf("%d ", matriz[i][j]);
                        }
                         printf("\n");
                    } */
                }
            }
        }
    }

    printf("%d\n", matriz[m][n]);

    int aux = m;
    int ind[m];
    int j = 0;

    for (int i = n; i > 0; i--)
    {

        if (matriz[aux][i] != matriz[aux][i - 1])
        {
            ind[j] = (i-1);
            aux--;
            j++;
        }
    }

    for (int i = m-1; i >= 0; i--)
    {
        if(i != 0)printf("%d ", ind[i]);
        else printf("%d", ind[i]);
    }
    }
    //printf("AIN\n\n");
    return 0;
}