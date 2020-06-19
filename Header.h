#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define N_LINHAS 16
#define N_COLUNAS 16

#define CARRIER 5
#define BATTLESHIP 4
#define DESTROYER 3
#define SUBMARINE 3
#define PATROL_BOAT 2

#define MAX_CARRIER 1
#define MAX_BATTLESHIP 1
#define MAX_DESTROYER 1
#define MAX_SUBMARINE 1
#define MAX_PATROL_BOAT 1


#define TAM_NOME_PARTIDA 20

#define PLAYER1 1
#define PLAYER2 -1

#define JOGADOR1 0
#define JOGADOR2 1



#define SALVAR_JOGO -1

#define TEMPO_DE_ATRASO 800
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


int setar_tipo_embarcacao();
void setar_coordenadas_de_entrada();
void verificar_coordenadas_de_entrada(int *coord1, int *coord2);
void imprime_capa();
void imprimir_instrucoes(t_embarcacao *embarcacoes[5]);

bool alocar_embarcacao(int coord_coluna, int coord_linha, char embarcacao_orientacao, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao,int player);
char *replaceWord(const char *s, const char *oldW, const char *newW);
bool testar_posicao_embarcacao_horizontal(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao,int player);
bool testar_posicao_embarcacao_vertical(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao,int player);
void Atualizar_contagem_embarcacao(t_embarcacao *embarcacao);
char setar_direcao_embarcacao();
bool verificar_embarcacoes_disponiveis(t_embarcacao *embarcacoes[5]);
bool verificar_sobreposicao_de_embarcacoes_horizontal(int coord_linha, int coord_coluna, int tamanho_embarcacao, char *mapa[N_LINHAS][N_COLUNAS]);
bool verificar_sobreposicao_de_embarcacoes_vertical(int coord_linha, int coord_coluna, int tamanho_embarcacao, char *mapa[N_LINHAS][N_COLUNAS]);
int obter_instrucao(char *ataque[N_LINHAS][N_COLUNAS],char *armada[N_LINHAS][N_COLUNAS]);
void imprimir_pontuacao(int atacante,int defensor);
void mensagem_vencedor(int player);


void salvar_jogo(char nome_partida[TAM_NOME_PARTIDA],char *ataque[N_LINHAS][N_COLUNAS],char *armada[N_LINHAS][N_COLUNAS],int pontos);
void ler_partida(char nome_partida[TAM_NOME_PARTIDA], PLAYER *player1, PLAYER *player2);

void salva_jogo(char nome_arquivo[TAM_NOME_PARTIDA],PLAYER player[2], int rodadas);
void le_jogo(char nome_arquivo[TAM_NOME_PARTIDA],PLAYER *player1,PLAYER *player2);
void inicializar_player(PLAYER *player);

void inicializar_embarcacoes(t_embarcacao **embarcacoes[5]);

int calcular_pontos();

void inicializar_jogadores(char *mapa_p1[N_LINHAS][N_COLUNAS],char *mapa_p2[N_LINHAS][N_COLUNAS]);


void criar_arquivo(bool *jogo_salvo, PLAYER player[2],int contagem_de_rodadas);
void imprimir_creditos();

int gerenciar_tela_de_instrucoes(PLAYER player[2], int seleciona_player);
void imprimir_selecao_embarcacao(PLAYER  player[2], int i, t_embarcacao * embarcacoes[5]);
void imprimir_tela_de_instrucoes(PLAYER  player[2], int i, t_embarcacao * embarcacoes[5]);
void adicionar_embarcacao(PLAYER player[2], int i, t_embarcacao *embarcacoes[5]);


int setar_tipo_embarcacao_aleatoria(t_embarcacao *embarcacoes[5]);
char setar_direcao_embarcacao_aleatoria();
void setar_coordenadas_de_entrada_aleatoria(int *coord_coluna, int *coord_linha);
bool alocar_embarcacao_aleatorio(int coord_coluna, int coord_linha, char embarcacao_orientacao, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao);
void Atualizar_contagem_embarcacao_aleatoria(t_embarcacao *embarcacao);
bool testar_posicao_embarcacao_vertical_aleatoria(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao);
bool testar_posicao_embarcacao_horizontal_aleatoria(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao);
void gerar_mapa_aleatorio(char *computer_map[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacoes[5]);


void imprimir_tela_debug(char *player[N_LINHAS][N_COLUNAS]);
