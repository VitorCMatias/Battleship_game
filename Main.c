#include "Header.h"

int main()
{

    //enum e_coluna aux;
    //int coord1, coord2, tipo, nport = 0, ncour = 0, ntorp = 0, nhidro = 0;
    int coord_x, coord_y;
    char tag;
    char orientacao;
    char *player1[N_LINHAS][N_COLUNAS];
    bool t = 0;
    int opicao,i = 0;
    int embarcacao;

    t_embarcacao battleship = {'B', "Battleship", 4, 2};
    t_embarcacao carier = {'C', "Carier", 5, 2};
    t_embarcacao destroyer = {'D', "Destroyer", 3, 2};
    t_embarcacao patrol_boat = {'P', "Patrol Boat", 2, 2};
    t_embarcacao submarine = {'S', "Submarine", 3, 2};

    t_embarcacao *embarcacoes[5] = {&battleship, &carier, &destroyer, &patrol_boat, &submarine};
    imprime_capa(); //imprime a tela inicial com o desenho do barco

    scanf("%i",&opicao); //opição do modo de jogo
    
    switch (opicao){
    case 1:
        system("cls");
        inicializa_player(&player1); //inicializa o player
    //Inicializar Jogo
    inicializar_jogo(player1);
    imprimir_tela(player1);
    imprimir_instrucoes(embarcacoes);

    do
    {
        //Obter input
        embarcacao = setar_tipo_embarcacao();
        //fazer um f para verificar dsponibilidade de embarcacao, se quant > 0
        orientacao = setar_direcao_embarcacao();
        setar_coordenadas_de_entrada(&coord_x, &coord_y);

        //Alocar embarcacao
        alocar_embarcacao(coord_x, coord_y, orientacao, player1, embarcacoes[embarcacao]);
        Atualizar_contagem_embarcacao(embarcacoes[embarcacao]);
        // Reimprimir tela
        imprimir_tela(player1);
        imprimir_instrucoes(embarcacoes);
    } while (verificar_embarcacoes_disponiveis(embarcacoes));

    /*while(battleship.max_quantidade || carier.max_quantidade || destroyer.max_quantidade || patrol_boat.max_quantidade || submarine.max_quantidade)
    {

        scanf(" %[^\n]c ", &tag);
        tag = toupper(tag);
        Atualizar_contagem_embarcacao(tag, embarcacoes);
        
    }

    for (i = 0; i < 5; i++)
    {
        printf("%c - %s - %d - %d \n", embarcacoes[i]->tag, embarcacoes[i]->nome, embarcacoes[i]->tamanho, embarcacoes[i]->max_quantidade);
    }

    /*while (nport < MAX_PORT || ncour < MAX_COUR || ntorp < MAX_TORP || nhidro < MAX_HIDRO)
    {

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
        break;
    
    default:
        break;
    }
*/
    return 0;
}