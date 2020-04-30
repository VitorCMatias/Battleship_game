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

    gotoxy(3,0);
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