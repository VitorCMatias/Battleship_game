#include "Header.h"

int main()
{

    //enum e_coluna aux;
    //int coord1, coord2, tipo, nport = 0, ncour = 0, ntorp = 0, nhidro = 0;
    int coord_x, coord_y;
    char tag;
    char orientacao;
    //char *player1[N_LINHAS][N_COLUNAS];
    bool t = 0;
    int opicao;
    int embarcacao;
    int i;

    player player[2];

    t_embarcacao battleship = {'B', "Battleship", BATTLESHIP, MAX_BATTLESHIP};
    t_embarcacao carier = {'C', "Carrier", CARRIER, MAX_CARRIER};
    t_embarcacao destroyer = {'D', "Destroyer", DESTROYER, MAX_DESTROYER};
    t_embarcacao patrol_boat = {'P', "Patrol Boat",PATROL_BOAT, MAX_PATROL_BOAT};
    t_embarcacao submarine = {'S', "Submarine", SUBMARINE, MAX_SUBMARINE};

    t_embarcacao *embarcacoes[5] = {&battleship, &carier, &destroyer, &patrol_boat, &submarine};

    while (true){
    
    system("cls");

    imprime_capa(); //imprime a tela inicial com o desenho do barco

    scanf("%i", &opicao); //opição do modo de jogo

    switch (opicao)
    {
    case 1:

        for ( i = 0; i < 2; i++)
        {
            system("cls");
            //Inicializar Jogo
            inicializar_jogo(player[i].armada);
            imprimir_tela( player[i].armada, i);
            imprimir_instrucoes(embarcacoes);
            do
            {
                //Obter input
                embarcacao = setar_tipo_embarcacao();
                //fazer um f para verificar dsponibilidade de embarcacao, se quant > 0
                orientacao = setar_direcao_embarcacao();
                setar_coordenadas_de_entrada(&coord_x, &coord_y);




                //Alocar embarcacao
                alocar_embarcacao(coord_x, coord_y, orientacao, player[i].armada, embarcacoes[embarcacao]);
                Atualizar_contagem_embarcacao(embarcacoes[embarcacao]);
                // Reimprimir tela
                imprimir_tela( player[i].armada, i);
                imprimir_instrucoes(embarcacoes);
            } while (verificar_embarcacoes_disponiveis(embarcacoes));
        }
        
        break;
    case 2:

        printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");

        break;
    
    case 3:

        printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");
        break;

    default:

        printf("\n\n                OPCAO INVALIDA.");
        system("pause");
        break;

    }

    }

    return 0;
}