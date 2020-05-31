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
    int opicao, i = 0;
    int embarcacao;

    t_embarcacao battleship = {'B', "Battleship", 4, 2};
    t_embarcacao carier = {'C', "Carier", 5, 2};
    t_embarcacao destroyer = {'D', "Destroyer", 3, 2};
    t_embarcacao patrol_boat = {'P', "Patrol Boat", 2, 2};
    t_embarcacao submarine = {'S', "Submarine", 3, 2};

    t_embarcacao *embarcacoes[5] = {&battleship, &carier, &destroyer, &patrol_boat, &submarine};
    while (true){
    
    system("cls");

    imprime_capa(); //imprime a tela inicial com o desenho do barco

    scanf("%i", &opicao); //opição do modo de jogo

    switch (opicao)
    {
    case 1:
    
        system("cls");
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

        break;
    case 2:

        printf("\n\n           FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");

        break;
    
    case 3:

        printf("\n\n           FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");
        break;

    default:

        printf("\n\n           OPCAO INVALIDA.");
        system("pause");
        break;

    }

    }

    return 0;
}