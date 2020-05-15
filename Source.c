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

    aux = 65; //A em ascii
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