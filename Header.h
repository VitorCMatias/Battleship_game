#include<stdio.h>
#include<conio.h>
#include<Windows.h>


#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define DIM 16
#define maxport 2
#define maxcour 2
#define maxtorp 2
#define maxhidro 2

typedef struct{
    int tamanho;  //tamnho do embarcacao unidimensional
    char tag;     // tag da embarcacao
}barco;


void imprime_tela(char player[DIM][DIM][2]);
void imprime_tela(char player[DIM][DIM][2]);
void inicializa_player(char *ponteiro);
int aloca_barco(barco embarcacao,char direc,int l, int c,char *ponteiro);
void gotoxy(short x, short y);
void print_map();