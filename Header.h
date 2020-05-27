#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

#define N_LINHAS 16
#define N_COLUNAS 16
#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define DIM 16
#define maxport 2
#define maxcour 2
#define maxtorp 2
#define maxhidro 2
#define teste 1

enum e_coluna
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P
};

typedef struct
{
    int tamanho; //tamanho do embarcacao unidimensional
    char tag;    //tag da embarcacao
} barco;

void imprime_tela(char player[DIM][DIM][2]);
void imprime_tela(char player[DIM][DIM][2]);
void inicializa_player(char *ponteiro);
int aloca_barco(barco embarcacao, char direc, int l, int c, char *ponteiro);
void gotoxy(short x, short y);
void print_map();
void imprimir_instrucoes(int nport, int ncour, int ntorp, int nhidro);
int setar_tipo_embarcacao();
void setar_coordenadas_de_entrada();
void verificar_coordenadas_de_entrada(int *coord1, int *coord2);
void imprime_capa();