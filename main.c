#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int main(void){

    Filial* filial_ == NULL;
    Caminhao remover_caminhao(Filial *filiais, int codigo_filial);
    Filial *cadastrar_filial(Filial *filiais, int *n_filiais);
    void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial);
    void realizar_entrega(Filial *filiais, Produto produto, int n_filiais);
    void imprimir_filiais(Filial *filiais, int n_filiais);
    //Menu 

    do{ printf("........ Menu Principal............\n\n\n");
        printf("1. Cadastrar Filial\n 2. Cadastrar Caminhao\n 3. Realizar entrega\n 4. Imprimir Filiais 5. Sair\n");
        printf("O que voce quer fazer?\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1: cadastrar_filial(Filial *filiais, int *n_filiais); break;
            case 2: cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial); break;
            case 3: realizar_entrega(Filial *filiais, Produto produto, int n_filiais); break;
            case 4: imprimir_filiais(Filial *filiais, int n_filiais); break;
            case 5: printf("O programa ira encerrar agora"); break;
            default: printf("Opcao invalida"); break;
        }
    } while(opcao != 5);

    typedef struct{
        char placa[6];
    } Caminhao;

    typedef struct{
        int codigo;
        float loc_x, loc_y;
        Caminhao* caminhao;
        int n_caminhao;
    } Filial;

     typedef struct{
        float origem_x, origem_y;
        float destino_x, destino_y;
    } Produto;

}
int n_filiais = 0;

Filial *cadastrar_filial(Filial *filiais, int *n_filiais){
    Filial *filiais = *tmp;
    int codigo;
    printf("Digite o codigo da filial que voce deseja cadatrar:\n ");
    scanf("%d", Filial.codigo);
    printf("Digite a localizacao x e y, respectivamente, da filial que voce deseja cadastrar:\n ");
    scanf("%d %d", Filial.loc_x, loc_y);

    filiais = (Filiais *)realloc(filiais, (*n_filiais + 1) * sizeof(Filial));

    if(*filiais == NULL){
        printf("Realoc falhou.");
        free(tmp);
        exit (1);
    } else {
        *(n_filiais)++;
        strcpy(*filial[*(n_filiais) - 1]. codigo, codigo);
        strcpy(*filial[*(n_filiais) - 1].loc_x, loc_x );
        strcpy(*filial[*(n_filiais) - 1].loc_x, loc_y );

    }

    return;
    
    void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial);
    Filial *filiais = *tmp;
    Caminhao caminhao;
    int codigo_filial;
    int *n_filiais;

    printf("Digite a placa do caminhao que voce deseja cadastrar: \n");
    scanf("%d", placa_cam);
    printf("Digite o codigo da filial onde voce deseja cadastrar o caminhao:\n");
    scanf("%d", codigo_filial);

    filais[codigo_filial].caminhao = (Caminhao *)realloc(filiais[codigo_filial].caminhao, (*filial[codigo_filial].n_caminhao + 1) * sizeof(Caminhao));

     if(caminhao == NULL){
        printf("Realoc falhou.");
        free(tmp);
        exit (1);
    } else {
        *(n_caminhao)++;
        strcpy(caminhao[*(n_caminhoes) - 1]. placa, placa_cam);

    }
    return;
    printf("Digite os dados de origem (x e y, respectivamente) da entrega:\n ");
    scanf("%f %f", &Produto.origem_x, &Produto.origem_y);
    printf("Digite os dados de destino (x e y, respectivamente) da entrega:\n ");
    scanf("%f %f", &Produto.destino_x, &Produto.destino_y);

    void realizar_entrega(Filial *filiais, Produto produto, int n_filiais){
        float dX;
        //Calculando a distancia entre as filiais e a origem pra ver qual é menor
        for(int i=0; i<*(n_filiais); i++){
            if(filial[i].loc_x > Produto[i].origem_x){
            dX = filial[i].loc_x - Produto[i].origem_x;
            dY = filial[i].loc_y - Produto[i].origem_y;
            d_total[i] = pow(dX, 2) + pow(dY, 2); 
            }

            else{
                dX = Produto[i].origem_x -  filial[i].loc_x;
                dY = Produto[i].origem_y -  filial[i].loc_y;
                d_total [i]= pow(dX, 2) + pow(dY, 2); 
            }

            //comparando as distancias pra ver qual é menor
            int compara, aux;
            for(j=0; j<*(n_filiais); j++){
                compara = strcmp(d_total[j], dist_total[j+1]);
                //quero mudar toda minha struct filial de ordem
                if(compara>0){
                    aux = Filial[j]
                    Filial[j] = Filial[j + 1];
                    Filial[j + 1] = aux;
                }
            //tenho que tirar o ultimo caminhao do vetor de caminhoes
                if(*n_caminhao[i] == 0) {
                    printf("Nao ha caminhoes para entrega\n");
                    return;
                }
                *(n_caminhao)--;

                Filial *filial = tmp;
                *filial[codigo_filial].caminhao = (Lista*) realloc(*filial, (*n_caminhao) * sizeof(Lista));

                if(n_caminhao != 0 && *filial == NULL){
                    PRINTF("Realloc falhou");
                    free(tmp);
                    exit (1);
                }
            }
        }
    }
    
    void imprimir_filiais(Filial *filiais, int n_filiais){
        
         for(int m =0; m< n_filiais; m++){
            printf("Codigo da filial:\n");
            for(int k =0; k< n_filiais; k++){
                printf("%d\n", Filial[k].codigo);  
                printf("Placas dos caminhoes contidos nessa filial:\n");
                for(int m =0; m< n_filiais; m++){
                    printf("%d\n", Caminhao[codigo_filial].placa[m]);     
                }  
            }
         }
    return 0;
    }

    return 0;