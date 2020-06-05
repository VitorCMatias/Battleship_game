#include "Header.h"

int main()
{

    int coord_x, coord_y;
    char tag;
    char orientacao;
    bool t = 0;
    int opicao;
    int embarcacao;
    int i;
    int contagem_de_rodadas=0,seleciona_player;
    int incremento;
    int acertou;

    PLAYER player[2];

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

        inicializar_jogo(player[0].ataque); //inicializa o mapa de ataque dos jogadores.
        inicializar_jogo(player[1].ataque);

        //inicializa os pontos dos players.
        player[0].pontos=player[1].pontos= MAX_CARRIER*CARRIER+MAX_BATTLESHIP*BATTLESHIP+MAX_DESTROYER*DESTROYER+MAX_SUBMARINE*SUBMARINE+MAX_PATROL_BOAT*PATROL_BOAT;

        while (player[0].pontos!=0 && player[1].pontos!=0) //ciclo até alguem perder
        {   
            seleciona_player=contagem_de_rodadas%2; //alterna os players que jogam

            if (seleciona_player==0) incremento=1; //incremento altera conforme o player
            else incremento=-1;
            
            imprimir_tela( player[seleciona_player].ataque, seleciona_player);
            imprimir_pontuacao(player[seleciona_player].pontos,player[seleciona_player+incremento].pontos);
            acertou=atirar(player[seleciona_player].ataque, player[seleciona_player+incremento].armada);

            if(acertou==-1){
                salvar_jogo(player);
                break;
            } 

            player[seleciona_player+incremento].pontos-=acertou;//retira um ponto do adversário caso acerte o barco
            contagem_de_rodadas++;
            getch();
        }

        if (acertou==-1) break;// se decidir sair do jogo para aqui

        if (player[0].pontos==0) mensagem_vencedor(1); //imprime a tela de vitória
        else mensagem_vencedor(2);
        
        break;

    case 2:

        printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");

        break;
    
    case 3:

        printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");
        break;

    case 4:

        printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.");
        system("pause");
        break;
    
    case 5:

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