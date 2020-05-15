#include "Header.h"

int main()
{
    int coord1, coord2, tipo, nport = 0, ncour = 0, ntorp = 0, nhidro = 0;
    char direcao;
    char player1[DIM][DIM][2];

    barco porta_aviao, couracado, torpedeiro, hidroaviao;

    porta_aviao.tamanho = 5; //define os tipos de embarcações
    porta_aviao.tag = 'P';
    couracado.tamanho = 4;
    couracado.tag = 'C';
    torpedeiro.tamanho = 3;
    torpedeiro.tag = 'T';
    hidroaviao.tamanho = 2;
    hidroaviao.tag = 'H';

    inicializa_player(&player1); //inicializa o player

    imprime_tela(player1);

    while (nport < maxport || ncour < maxcour || ntorp < maxtorp || nhidro < maxhidro)
    { //aloca todas as embarcações
        printf("\n------------------------------------------\n");
        printf("TIPOS DE EMBARCACOES:\n");
        printf("                     1-PORTA AVIOES.\n");
        printf("                     2-COURACADO.\n");
        printf("                     3-TORPEDEIRO.\n");
        printf("                     4-HIDRO AVIAO.\n");
        printf("DIRECAO:.\n");
        printf("                     d-direita.\n");
        printf("                     b-baixo.\n");
        printf("------------------------------------------\n");
        printf("Tipo de embarcacao:");
        scanf("%i", &tipo);
        printf("cordenadas de origem:");
        scanf("%i %i", &coord1, &coord2); //coordenadas do pivo da embarcação
        printf("direcao:");
        scanf(" %c", &direcao); //direção que será colocado a embarcação

        switch (tipo)
        {
        case (1):
            if (nport < maxport)
                nport = nport + aloca_barco(porta_aviao, direcao, coord1, coord2, &player1); //porta avioes

            else
                printf("ja foram utilizadas todas os porta avioes.\n");

            break;
        case (2):
            if (ncour < maxcour)
                ncour = ncour + aloca_barco(couracado, direcao, coord1, coord2, &player1); //couraçado

            else
                printf("ja foram utilizadas todas os couracados.\n");

            break;
        case (3):
            if (ntorp < maxtorp)
                ntorp = ntorp + aloca_barco(torpedeiro, direcao, coord1, coord2, &player1); //torpedeiro

            else
                printf("ja foram utilizadas todas os torpedeiros.\n");

            break;
        case (4):
            if (nhidro < maxhidro)
                nhidro = nhidro + aloca_barco(hidroaviao, direcao, coord1, coord2, &player1); //hidro avião

            else
                printf("ja foram utilizadas todas os hidroavioes.\n");

            break;

        default:
            break;
        }
        system("cls");
        imprime_tela(player1);
    }

    getch();

    return 0;
}