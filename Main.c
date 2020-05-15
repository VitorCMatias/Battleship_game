#include "Header.h"

int main()
{
    //enum e_coluna aux;
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

    printf("\n\n                   BATALHA NAVAL\n\n");

    imprime_tela(player1);

    while (nport < maxport || ncour < maxcour || ntorp < maxtorp || nhidro < maxhidro)
    {

        //aloca todas as embarcações
        imprimir_instrucoes(nport, ncour, ntorp, nhidro);

        tipo = setar_tipo_embarcacao();
        setar_coordenadas_de_entrada(&coord1, &coord2);
        direcao = setar_direcao_embarcacao();

        switch (tipo)
        {
        case (1):
            if (nport < maxport)
                nport = nport + aloca_barco(porta_aviao, direcao, coord1, coord2, &player1); //porta avioes

            else
            {
                printf("ja foram utilizadas todas os porta avioes.\n");
                getch();
            }

            break;
        case (2):
            if (ncour < maxcour)
                ncour = ncour + aloca_barco(couracado, direcao, coord1, coord2, &player1); //couraçado

            else
            {
                printf("ja foram utilizadas todas os couracados.\n");
                getch();
            }

            break;
        case (3):
            if (ntorp < maxtorp)
                ntorp = ntorp + aloca_barco(torpedeiro, direcao, coord1, coord2, &player1); //torpedeiro

            else
            {
                printf("ja foram utilizadas todas os torpedeiros.\n");
                getch();
            }

            break;
        case (4):
            if (nhidro < maxhidro)
                nhidro = nhidro + aloca_barco(hidroaviao, direcao, coord1, coord2, &player1); //hidro avião

            else
            {
                printf("ja foram utilizadas todas os hidroavioes.\n");
                getch();
            }

            break;

        default:
            printf("Embarcacao inexistente.");
            getch();
            break;
        }
        system("cls");
        printf("\n\n                   BATALHA NAVAL\n\n");
        imprime_tela(player1);
    }

    getch();

    return 0;
}