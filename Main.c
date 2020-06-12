#include "Header.h"

int main()
{

    int coord_x, coord_y;
    char tag;
    char orientacao;
    char nome_partida[TAM_NOME_PARTIDA];
    char escolha;
    bool t = 0;
    int opicao;
    int embarcacao;
    int i;
    int contagem_de_rodadas=0,seleciona_player;
    int incremento;
    int acertou;

    FILE *arq;

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
                if(alocar_embarcacao(coord_x, coord_y, orientacao, player[i].armada, embarcacoes[embarcacao], i))Atualizar_contagem_embarcacao(embarcacoes[embarcacao]);
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
                
                system("cls");

                do{
                    printf("Deseja salvar o jogo?(Y/N)");
                    scanf(" %c",&escolha);

                    escolha=toupper(escolha);

                    if (escolha=='Y'){
                        printf("Digite um nome para salavar o jogo:");
                        scanf(" %s",nome_partida);

                        strcat(nome_partida,".bin");
                    }
                }while (escolha!='N' && escolha!='Y');

                if (escolha!='N'){

                    for ( i = 0; i < 2; i++){
                        salva_jogo(nome_partida,player[i],contagem_de_rodadas);    
                    }
                }

                break;
            } 

            player[seleciona_player+incremento].pontos-=acertou;//retira um ponto do adversário caso acerte o barco
            contagem_de_rodadas++;
            getch();
        }

        if (acertou==-1) break;


        if (player[0].pontos==0) mensagem_vencedor(1); //imprime a tela de vitória
        else mensagem_vencedor(2);
        
        break;

    case 2:

        system("cls");
        fflush(stdin);
        printf("Digite o nome da partida que deseja resgatar:");
        scanf(" %s",nome_partida);

        strcat(nome_partida,".bin");

        arq=fopen(nome_partida,"rb");

        if (arq==NULL){
            printf("PROBLEMAS AO ABRIR O ARQUIVO.\n");
            getch();
            break;
        }
        else{
            
            inicializar_player(&player[0]);
            inicializar_player(&player[1]);

            fread(&player,sizeof(PLAYER),2,arq);
            fread(&contagem_de_rodadas,sizeof(int),1,arq);

            while (player[0].pontos!=0 && player[1].pontos!=0) //ciclo até alguem perder
            {   
                seleciona_player=contagem_de_rodadas%2; //alterna os players que jogam

                if (seleciona_player==0) incremento=1; //incremento altera conforme o player
                else incremento=-1;
                
                imprimir_tela( player[seleciona_player].ataque, seleciona_player);
                imprimir_pontuacao(player[seleciona_player].pontos,player[seleciona_player+incremento].pontos);
                acertou=atirar(player[seleciona_player].ataque, player[seleciona_player+incremento].armada);

                if(acertou==-1){   
                    
                    system("cls");

                    do{
                        printf("Deseja salvar o jogo?(Y/N)");
                        scanf(" %c",&escolha);

                        escolha=toupper(escolha);

                        if (escolha=='Y'){
                            printf("Digite um nome para salavar o jogo:");
                            scanf(" %s",nome_partida);

                            strcat(nome_partida,".bin");
                        }
                    }while (escolha!='N' && escolha!='Y');

                    if (escolha!='N'){

                        for ( i = 0; i < 2; i++){
                            //salvar_jogo(nome_partida,player[i].armada,player[i].ataque,player[i].pontos);   
                            salva_jogo(nome_partida,player[i],seleciona_player);    
                        }
                    }

                    break;
                } 

                player[seleciona_player+incremento].pontos-=acertou;//retira um ponto do adversário caso acerte o barco
                contagem_de_rodadas++;
                getch();
            }

            if (acertou==-1) break;


            if (player[0].pontos==0) mensagem_vencedor(1); //imprime a tela de vitória
            else mensagem_vencedor(2);
            
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
        
        system("cls");
        printf("\n\n    JOGO DESENVOLVIDO PELOS ALUNOS:                                      ");
        printf("\n\n                                      MARLON DOMINGUES DE OLIVEIRA        ");
        printf("\n\n                                                     E                    ");
        printf("\n\n                                         VITOR DA COSTA MATIAS            ");
        printf("\n\n\n\n\n\n\n\n\n    PROJETO DESENVOLVIDO PARA A AVALIACAO NA MATERIA DE INTRODUCAO A PROGRAMACAO PARA ENGENHARIAS DO PRIMEIRO ");
        printf("\n    SEMESTRE DE 2020.");
        printf("\n\n\n    PROFESSOR RESPONSAVEL PELA DICIPLINA: JO UEYAMA.");
        printf("\n\n\n    UNIVERSIDADE: UNIVERSIDADE DE SAO PAULO-USP (CAMPUS SAO CARLOS)");
        getch();
        break;


    default:

        printf("\n\n                OPCAO INVALIDA.  ");
        system("pause");
        break;

    }

    }

    return 0;
}