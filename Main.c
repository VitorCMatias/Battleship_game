#include "Header.h"

int main()
{
    bool jogo_salvo = false;
    int coord_x, coord_y;
    char tag;
    char orientacao;
    char nome_partida[TAM_NOME_PARTIDA];
    char escolha;
    bool t = 0;
    int opicao;
    int embarcacao;
    int i;
    int contagem_de_rodadas = 0, seleciona_player;
    int incremento;
    int instrucao;

    FILE *arq;

    PLAYER player[2];

    t_embarcacao battleship = {'B', "Battleship", BATTLESHIP, MAX_BATTLESHIP};
    t_embarcacao carier = {'C', "Carrier", CARRIER, MAX_CARRIER};
    t_embarcacao destroyer = {'D', "Destroyer", DESTROYER, MAX_DESTROYER};
    t_embarcacao patrol_boat = {'P', "Patrol Boat", PATROL_BOAT, MAX_PATROL_BOAT};
    t_embarcacao submarine = {'S', "Submarine", SUBMARINE, MAX_SUBMARINE};

    t_embarcacao *embarcacoes[5] = {&battleship, &carier, &destroyer, &patrol_boat, &submarine};
    system("MODE 115,45");
    while (true)
    {

        system("cls");

        imprime_capa(); //imprime a tela inicial com o desenho do barco

        scanf("%i", &opicao); //opição do modo de jogo
        system("MODE 100,45");

        switch (opicao)
        {
        case 1:

            jogo_salvo = false;

            for (i = 0; i < 2; i++)
            {
                
                imprimir_tela_de_instrucoes(player, i, embarcacoes);

                do
                {
                    //Obter input
                    embarcacao = setar_tipo_embarcacao();
                    //fazer um f para verificar dsponibilidade de embarcacao, se quant > 0
                    orientacao = setar_direcao_embarcacao();
                    setar_coordenadas_de_entrada(&coord_x, &coord_y);

                    //Alocar embarcacao
                    if (alocar_embarcacao(coord_x, coord_y, orientacao, player[i].armada, embarcacoes[embarcacao], i))
                        Atualizar_contagem_embarcacao(embarcacoes[embarcacao]);
                    // Reimprimir tela
                    imprimir_selecao_embarcacao(player, i, embarcacoes);
                    Sleep(TEMPO_DE_ATRASO);

                } while (verificar_embarcacoes_disponiveis(embarcacoes));
            }

            inicializar_jogadores(player[0].ataque, player[1].ataque);

            //inicializa os pontos dos players.
            player[0].pontos = calcular_pontos();
            player[1].pontos = calcular_pontos();

            while (player[0].pontos != 0 && player[1].pontos != 0 && jogo_salvo == false) //ciclo até alguem perder
            {
                seleciona_player = contagem_de_rodadas % 2; //alterna os players que jogam

                incremento = (seleciona_player == 0) ? PLAYER1 : PLAYER2; //incremento altera conforme o player

                instrucao = gerenciar_tela_de_instrucoes(player, seleciona_player);

                if (instrucao == SALVAR_JOGO)
                {
                    system("cls");
                    criar_arquivo(&jogo_salvo, player, contagem_de_rodadas);
                }

                player[seleciona_player + incremento].pontos -= instrucao; //retira um ponto do adversário caso acerte o barco
                contagem_de_rodadas++;
                getch();
            }

            if (instrucao == SALVAR_JOGO)
                break;

            if (player[0].pontos == 0)
                mensagem_vencedor(1); //imprime a tela de vitória
            else
                mensagem_vencedor(2);

            break;














        case 2:

            system("cls");
            fflush(stdin);
            printf("Digite o nome da partida que deseja resgatar:");
            scanf(" %s", nome_partida);

            strcat(nome_partida, ".bin");

            arq = fopen(nome_partida, "rb");

            if (arq == NULL)
            {
                printf("PROBLEMAS AO ABRIR O ARQUIVO.\n");
                getch();
                break;
            }
            else
            {

                inicializar_player(&player[0]);
                inicializar_player(&player[1]);

                fread(&player, sizeof(PLAYER), 2, arq);
                fread(&contagem_de_rodadas, sizeof(int), 1, arq);

                while (player[0].pontos != 0 && player[1].pontos != 0) //ciclo até alguem perder
                {
                    seleciona_player = contagem_de_rodadas % 2; //alterna os players que jogam

                    if (seleciona_player == 0)
                        incremento = 1; //incremento altera conforme o player
                    else
                        incremento = -1;

                    imprimir_tela(player[seleciona_player].ataque, seleciona_player);
                    imprimir_pontuacao(player[seleciona_player].pontos, player[seleciona_player + incremento].pontos);
                    instrucao = obter_instrucao(player[seleciona_player].ataque, player[seleciona_player + incremento].armada);

                    if (instrucao == SALVAR_JOGO)
                    {
                        system("cls");
                        criar_arquivo(&jogo_salvo, player, contagem_de_rodadas);
                    }

                    player[seleciona_player + incremento].pontos -= instrucao; //retira um ponto do adversário caso acerte o barco
                    contagem_de_rodadas++;
                    getch();
                }

                if (instrucao == SALVAR_JOGO)
                    break;

                if (player[0].pontos == 0)
                    mensagem_vencedor(1); //imprime a tela de vitória
                else
                    mensagem_vencedor(2);

                break;
            }

        case 3:

            printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.  ");
            system("pause");
            break;

        case 4:

            printf("\n\n                FUNCAO AINDA NAO IMPLEMENTADA.  ");
            system("pause");
            break;

        case 5:

            imprimir_creditos();
            break;

        default:

            printf("\n\n                OPCAO INVALIDA.  ");
            system("pause");
            break;
        }
    }

    return 0;
}