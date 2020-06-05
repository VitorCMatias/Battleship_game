#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define N_LINHAS 16
#define N_COLUNAS 16

#define DIM 16
#define MAX_PORT 2
#define MAX_COUR 2
#define MAX_TORP 2
#define MAX_HIDRO 2

#define CARRIER 5
#define BATTLESHIP 4
#define DESTROYER 3
#define SUBMARINE 3
#define PATROL_BOAT 2

#define MAX_CARRIER 0
#define MAX_BATTLESHIP 1
#define MAX_DESTROYER 0
#define MAX_SUBMARINE 0
#define MAX_PATROL_BOAT 0
#define MAX_NUM_BARCO 2
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
    char tag;
    char *nome;
    int tamanho;
    int max_quantidade;
} t_embarcacao;

typedef struct
{
    int tamanho; //tamanho do embarcacao unidimensional
    char tag;    //tag da embarcacao
} barco;

typedef struct
{
    char *armada[N_LINHAS][N_COLUNAS];
    char *ataque[N_LINHAS][N_COLUNAS];
    int pontos;
}PLAYER;

void imprimir_tela(char *player[N_LINHAS][N_COLUNAS], int contador);
void inicializar_jogo(char *mapa[N_LINHAS][N_COLUNAS]);
int aloca_barco(barco embarcacao, char direc, int l, int c, char *ponteiro);
void gotoxy(short x, short y);
void print_map();

int setar_tipo_embarcacao();
void setar_coordenadas_de_entrada();
void verificar_coordenadas_de_entrada(int *coord1, int *coord2);
void imprime_capa();
void imprimir_instrucoes(t_embarcacao *embarcacoes[5]);

bool alocar_embarcacao(int coord_coluna, int coord_linha, char embarcacao_orientacao, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao);
char *replaceWord(const char *s, const char *oldW, const char *newW);
bool testar_posicao_embarcacao_horizontal(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao);
bool testar_posicao_embarcacao_vertical(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao);
void teste(t_embarcacao *embarcacoes[5]);
void Atualizar_contagem_embarcacao(t_embarcacao *embarcacao);
char setar_direcao_embarcacao();
bool verificar_embarcacoes_disponiveis(t_embarcacao *embarcacoes[5]);
bool verificar_sobreposicao_de_embarcacoes_horizontal(int coord_linha, int coord_coluna, int tamanho_embarcacao, char *mapa[N_LINHAS][N_COLUNAS]);
bool verificar_sobreposicao_de_embarcacoes_vertical(int coord_linha, int coord_coluna, int tamanho_embarcacao, char *mapa[N_LINHAS][N_COLUNAS]);
int atirar(char *ataque[N_LINHAS][N_COLUNAS],char *armada[N_LINHAS][N_COLUNAS]);
void imprimir_pontuacao(int atacante,int defensor);
void mensagem_vencedor(int player);
