#include "Header.h"

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void print_map()
{
    int i, j;
    char column_index = 'A';

    gotoxy(3, 0);
    for (i = 0; i < MAP_WIDTH; i++)
    {
        printf("%c ", column_index + i);
    }
    printf("\n");
    for (i = 0; i < MAP_WIDTH; i++)
    {

        if (i < 9)
        {
            printf("%d  ", i + 1);
        }
        else
        {
            printf("%d ", i + 1);
        }
        for (j = 0; j < MAP_HEIGHT; j++)
        {
            printf("^ ");
        }
        printf("\n");
    }
}

void imprime_tela(char player[DIM][DIM][2])
{

    int i, j, k, aux;

    aux = 'A';
    printf("    ");
    for (i = 0; i < DIM; i++)
    {
        printf("%c  ", aux); //Imprime letras superiores,coordenadas
        aux++;
    }
    printf("\n");
    for (i = 0; i < DIM; i++)
    {
        printf("%02i", i); //imprime as coordenadas laterais
        printf("|");
        for (j = 0; j < DIM; j++)
        {
            for (k = 0; k < 2; k++)
            {
                printf("%c", player[i][j][k]); //imprime os termos da posicao
            }

            printf("|");
        }
        printf("\n");
    }
}

void inicializa_player(char *ponteiro)
{
    int i, j, k;

    for (j = 0; j < DIM; j++)
    {
        for (i = 0; i < DIM; i++)
        {
            for (k = 0; k < 2; k++)
            {
                *ponteiro = '-'; //inicializa todas as posiçoes como o carsctere '-'
                ponteiro++;
            }
        }
    }
}

int aloca_barco(barco embarcacao, char direc, int l, int c, char *ponteiro)
{
    int i;

    switch (direc)
    {           //direção a direira ou para baixo
    case ('d'): //direita
        if (c + embarcacao.tamanho <= DIM)
        { //checa para ver se a embarcação não ultrapassará os limites do mapa
            for (i = 0; i < embarcacao.tamanho; i++)
            {
                if (*(ponteiro + 2 * (l * DIM + c + i)) != '-')
                {
                    printf("posicao invalida, encontro com embarcacao.\n"); //checa se há alguma embarcação na posição
                    getch();
                    return 0;
                    break;
                }
            }
            for (i = 0; i < embarcacao.tamanho; i++)
            {
                *(ponteiro + 2 * (l * DIM + c + i)) = embarcacao.tag; //caso a posição esteja livre é alocado a embarcação
                *(ponteiro + 2 * (l * DIM + c + i) + 1) = '1';
            }
            return 1;
            break;
        }
        else
        {
            printf("posicao invalida, ultrapassa o limite do mapa.\n");
            getch();
            return 0;
            break;
        }

    case ('b'): //baixo
        if (l + embarcacao.tamanho <= DIM)
        {
            for (i = 0; i < embarcacao.tamanho; i++)
            {
                if (*(ponteiro + 2 * ((l + i) * DIM + c)) != '-')
                {
                    printf("posicao invalida, encontro com embarcacao.\n");
                    getch();
                    return 0;
                    break;
                }
            }
            for (i = 0; i < embarcacao.tamanho; i++)
            {
                *(ponteiro + 2 * ((l + i) * DIM + c)) = embarcacao.tag;
                *(ponteiro + 2 * ((l + i) * DIM + c) + 1) = '1';
            }
            return 1;
            break;
        }
        else
        {
            printf("posicao invalida, ultrapassa o limite do mapa.\n");
            getch();
            return 0;
            break;
        }

    default:
        return 0;
        break;
    }
}

void imprimir_instrucoes(int nport, int ncour, int ntorp, int nhidro)
{
    printf("\n----------------------------------------------------------\n");
    printf("TIPOS DE EMBARCACOES:\n");
    printf("\t\t 1-PORTA AVIOES\t\t RESTANTES: %i\n", maxport - nport);
    printf("\t\t 2-COURACADO \t\t RESTANTES: %i\n", maxcour - ncour);
    printf("\t\t 3-TORPEDEIRO \t\t RESTANTES: %i\n", maxtorp - ntorp);
    printf("\t\t 4-HIDRO AVIAO \t\t RESTANTES: %i\n", maxhidro - nhidro);
    printf("DIRECAO:\n");
    printf("\t\t d-direita.\n");
    printf("\t\t b-baixo.\n");
    printf("------------------------------------------------------------\n");
}

int setar_tipo_embarcacao()
{
    int tipo_embarcacao;
    printf("Tipo de embarcacao: ");
    scanf("%d", &tipo_embarcacao);

    return tipo_embarcacao;
}
char setar_direcao_embarcacao()
{
    char direcao_embarcacao;

    printf("direcao: ");
    
    scanf(" %[^\n]c ", &direcao_embarcacao); //direção que será colocado a embarcação

    return direcao_embarcacao;
}
void setar_coordenadas_de_entrada(int *coord1, int *coord2)
{
    char coordenada_x;
    int coordenada_y;
    bool coordenada_invalida = true;
    while (coordenada_invalida)
    {
        printf("cordenadas de origem: ");
        scanf(" %c %i", &coordenada_x, &coordenada_y); //coordenadas do pivo da embarcação
        coordenada_x = toupper(coordenada_x);
        if (coordenada_x < 'A' || coordenada_x > 'P')
        {
            puts("ERRO! Valor da coordenada coluna esta fora do intervalo de A a P \n");
            coordenada_invalida = true;
        }
        else if (coordenada_y < 0 || coordenada_y > N_LINHAS)
        {
            puts("ERRO! Valor da coordenada linha esta fora do intervalo de 0 a 13 \n");
            coordenada_invalida = true;
        }
        else
        {
            *coord1 = coordenada_x - 'A';
            *coord2 = coordenada_y;
            coordenada_invalida = false;
        }
    }
}