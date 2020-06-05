#include "Header.h"

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void inicializar_jogo(char *mapa[N_LINHAS][N_COLUNAS])
{
    int i, j;

    for (i = 0; i < N_LINHAS; i++)
    {
        for (j = 0; j < N_LINHAS; j++)
        {
            mapa[i][j] = "--";
        }
    }
}

void imprimir_tela(char *player[N_LINHAS][N_COLUNAS], int contador)
{
    system("cls");

    int i, j, k;
    char identificador_coluna = 'A';

    printf("\n\n                   BATALHA NAVAL\n\n");
    printf("\n\n                     PLAYER%i\n\n",contador+1);
    printf("    ");
    for (i = 0; i < N_COLUNAS; i++)
    {
        printf("%c  ", identificador_coluna); //Imprime letras superiores,coordenadas
        identificador_coluna++;
    }
    printf("\n");

    for (i = 0; i < N_LINHAS; i++)
    {
        printf("%02i|", i); //imprime as coordenadas laterais
        for (j = 0; j < N_COLUNAS; j++)
        {
            printf("%s|", player[i][j]); //imprime os termos da posicao
        }
        printf("\n");
    }
}

void imprimir_instrucoes(t_embarcacao *embarcacoes[5])
{
    int i;

    printf("\n----------------------------------------------------------\n");
    printf("TIPOS DE EMBARCACOES:\n");
    for (i = 0; i < 5; i++)
    {
        printf("\t\t %d-%s \t\t RESTANTES: %d\n", i + 1, embarcacoes[i]->nome, embarcacoes[i]->max_quantidade);
    }

    printf("DIRECAO:\n");
    printf("\t\t H - horizontal.\n");
    printf("\t\t V - vertical.\n");
    printf("------------------------------------------------------------\n");
}

int setar_tipo_embarcacao()
{
    int tipo_embarcacao;

    do
    {
        printf("Tipo de embarcacao: ");
        scanf("%d", &tipo_embarcacao);
        if (tipo_embarcacao < 1 || tipo_embarcacao > 5)
            printf("O valorinformado, %d, nao representa nenhuma embarcacao! \n", tipo_embarcacao);
    } while (tipo_embarcacao < 1 || tipo_embarcacao > 5);

    return tipo_embarcacao - 1;
}

char setar_direcao_embarcacao()
{
    char direcao_embarcacao;
    do
    {
        printf("direcao: ");
        scanf(" %[^\n]c ", &direcao_embarcacao); //direção que será colocado a embarcação
        direcao_embarcacao = toupper(direcao_embarcacao);
        if (direcao_embarcacao != 'H' && direcao_embarcacao != 'V')
            printf("O valor informado nao representa uma direcao, %c, use os caracteres H ou V para isso\n", direcao_embarcacao);
    } while (direcao_embarcacao != 'H' && direcao_embarcacao != 'V');

    return direcao_embarcacao;
}

void setar_coordenadas_de_entrada(int *coord_coluna, int *coord_linha)
{
    char coordenada_x;
    int coordenada_y;
    bool coordenada_invalida;
    do
    {
        printf("cordenadas de origem: ");
        scanf(" %c%i", &coordenada_x, &coordenada_y); //coordenadas do pivo da embarcação
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
            *coord_coluna = coordenada_x - 'A';
            *coord_linha = coordenada_y;
            coordenada_invalida = false;
        }
    } while (coordenada_invalida);
}

bool alocar_embarcacao(int coord_coluna, int coord_linha, char embarcacao_orientacao, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao)
{
    bool alocacao_bem_sucedida =false;

    if (embarcacao->max_quantidade>0)
    {
        switch (embarcacao_orientacao)
        {
        case 'H':
            alocacao_bem_sucedida = testar_posicao_embarcacao_horizontal(coord_linha, coord_coluna, mapa, embarcacao);
            break;
        case 'V':
            alocacao_bem_sucedida = testar_posicao_embarcacao_vertical(coord_linha, coord_coluna, mapa, embarcacao);
            break;

        default:
            puts("Orientacao invalida!");
            alocacao_bem_sucedida = false;
            break;
        }
        return alocacao_bem_sucedida;
    }

    return alocacao_bem_sucedida;
}

bool testar_posicao_embarcacao_horizontal(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao)
{
    int i;
    char *str = malloc(2 * sizeof(char));
    sprintf(str, "%c%d", embarcacao->tag, MAX_NUM_BARCO - embarcacao->max_quantidade);

    if (coord_linha > N_LINHAS)
    {
        printf("A posicao da linha informada, %d, excede o tamanho do mapa que eh %d\n", coord_linha, N_LINHAS);
        return false;
    }
    else if (coord_coluna + embarcacao->tamanho > N_COLUNAS)
    {
        printf("Nao ah espaco suficiente para embarcacao!\nA embarcacao informada tem o tamanho de %d, excedendo o tamanho do mapa em %d. Informe outro valor!\n", embarcacao->tamanho, (coord_coluna + embarcacao->tamanho) - N_COLUNAS);
        return false;
    }
    else if (verificar_sobreposicao_de_embarcacoes_horizontal(coord_linha, coord_coluna, embarcacao->tamanho, mapa))
    {
        puts("Jah existe uma embarcacao nessa coordenada, tente outra");
        return false;
    }

    else
    {

        for (i = coord_coluna; i < (coord_coluna + embarcacao->tamanho); i++)
        {
            mapa[coord_linha][i] = str;
        }
        return true;
    }
}

bool verificar_sobreposicao_de_embarcacoes_horizontal(int coord_linha, int coord_coluna, int tamanho_embarcacao, char *mapa[N_LINHAS][N_COLUNAS])
{
    int i;
    for (i = coord_coluna; i < (coord_coluna + tamanho_embarcacao); i++)
    {

        if (strcmp(mapa[coord_linha][i], "--") != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool testar_posicao_embarcacao_vertical(int coord_linha, int coord_coluna, char *mapa[N_LINHAS][N_COLUNAS], t_embarcacao *embarcacao)
{
    int i;
    char *str = malloc(2 * sizeof(char));
    bool posicao_valida;
    sprintf(str, "%c%d", embarcacao->tag, MAX_NUM_BARCO - embarcacao->max_quantidade);

    if (coord_linha > N_COLUNAS)
    {
        printf("A posicao da coluna informada, %d, excede o tamanho do mapa que eh %d\n", coord_linha, N_COLUNAS);
        posicao_valida = false;
    }
    else if (coord_coluna + embarcacao->tamanho > N_LINHAS)
    {
        printf("Nao ah espaco suficiente para embarcacao!\nA embarcacao informada tem o tamanho de %d, excedendo o tamanho do mapa em %d. Informe outro valor!\n", embarcacao->tamanho, (coord_coluna + embarcacao->tamanho) - N_LINHAS);
        posicao_valida = false;
    }
    else if (verificar_sobreposicao_de_embarcacoes_vertical(coord_linha, coord_coluna, embarcacao->tamanho, mapa))
    {
        puts("Jah existe uma embarcacao nessa coordenada, tente outra");
        posicao_valida = false;
    }
    else
    {

        for (i = coord_linha; i < (coord_linha + embarcacao->tamanho); i++)
        {
            mapa[i][coord_coluna] = str;
        }
        posicao_valida = true;
    }

    return posicao_valida;
}

bool verificar_sobreposicao_de_embarcacoes_vertical(int coord_linha, int coord_coluna, int tamanho_embarcacao, char *mapa[N_LINHAS][N_COLUNAS])
{
    int i;
    for (i = coord_linha; i < (coord_linha + tamanho_embarcacao); i++)
    {

        if (strcmp(mapa[i][coord_coluna], "--") != 0)
        {
            return true;
        }
    }
    return false;
}

bool verificar_embarcacoes_disponiveis(t_embarcacao *embarcacoes[5])
{   
    bool condicao;

    if(embarcacoes[0]->max_quantidade > 0 || embarcacoes[1]->max_quantidade > 0 || embarcacoes[2]->max_quantidade > 0 || embarcacoes[3]->max_quantidade > 0 || embarcacoes[4]->max_quantidade > 0) condicao=1;
    else{
        condicao=0;
        embarcacoes[0]->max_quantidade=MAX_BATTLESHIP;
        embarcacoes[1]->max_quantidade=MAX_CARRIER;
        embarcacoes[2]->max_quantidade=MAX_DESTROYER;
        embarcacoes[3]->max_quantidade=MAX_PATROL_BOAT;
        embarcacoes[4]->max_quantidade=MAX_SUBMARINE;
    }

    return condicao;
}

/*void inicializar_embarcacao(t_embarcacao *embarcacao[5])
{
    //t_embarcacao *embarcacao[5];
    
    embarcacao[0]->tag = 'C';
    embarcacao[0]->tamanho = 5;
    embarcacao[0]->max_quantidade = 2;

    embarcacao[1]->tag = 'B';
    embarcacao[1]->tamanho = 4;
    embarcacao[1]->max_quantidade = 2;

    embarcacao[2]->tag = 'D';
    embarcacao[2]->tamanho = 3;
    embarcacao[2]->max_quantidade = 2;

    embarcacao[3]->tag = 'S';
    embarcacao[3]->tamanho = 3;
    embarcacao[3]->max_quantidade = 2;

    embarcacao[4]->tag = 'P',
    embarcacao[4]->tamanho = 2;
    embarcacao[4]->max_quantidade = 2;

    return embarcacao;
}*/

void Atualizar_contagem_embarcacao(t_embarcacao *embarcacao)
{
    if (embarcacao->max_quantidade > 0)
    {
        embarcacao->max_quantidade -= 1;
    }
    else
    {
        printf("Voce jah utilizou todas as embarcacoes do tipo %s, selecione outra unidade!\n", embarcacao->nome);
        getch();
    }

    /*
    switch (tag)
    {
    case 'B':
        embarcacoes[0]->max_quantidade -= 1;
        break;
    case 'C':
        embarcacoes[1]->max_quantidade -= 1;
        break;
    case 'D':
        embarcacoes[2]->max_quantidade -= 1;
        break;
    case 'P':
        embarcacoes[3]->max_quantidade -= 1;
        break;
    case 'S':
        embarcacoes[4]->max_quantidade -= 1;
        break;

    default:
        printf("O valor informado %c, nao representa nenhuma embarcacao! Digite novamente\n", tag);
        break;
    }
    */
}

char *replaceWord(const char *s, const char *oldW, const char *newW)
{
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s)
    {
        // compare the substring with the result
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
}

void imprime_capa(){ //le o arquivo .txt e imprime a tela inicial com o barco.
    FILE *arq;

    int i,LIN=100;
    char linha[100];

    arq=fopen("tela_batalha-naval.txt","r");

    if (arq==NULL) printf("Erro ao abrir o arquivo.");

    while ((fgets(linha,LIN,arq))!=NULL){
        printf("%s",linha);

    }
    
    fclose(arq);

    printf("\n\n\n       1-PLAYER VS PLAYER.");
    printf("\n       2-CONTINUAR UM JOGO.");
    printf("\n       3-JOGAR CONTRA A MAQUINA.");
    printf("\n       4-DICAS SOBRE O JOGO.");
    printf("\n       5-DESENVOLVEDORES.");
    printf("\n\n\n       MODO DE JOGO:");
}

int atirar(char *ataque[N_LINHAS][N_COLUNAS],char *armada[N_LINHAS][N_COLUNAS]){
    
    char coord_xc;
    int coord_y,coord_x;
    int acertou=0;


    do{
        printf("\n\n\n      ATIRAR:");
        scanf(" %c",&coord_xc);
        coord_xc = toupper(coord_xc);

        if (coord_xc=='S') return -1;
      
        scanf(" %i",&coord_y);

        if(coord_xc< 'A' || coord_xc> 'P' || coord_y<0 || coord_y>N_LINHAS) printf("\n    Cordenadas nao pertencentes ao mapa.\n");

    } while (coord_xc< 'A' || coord_xc> 'P' || coord_y<0 || coord_y>N_LINHAS);
    
    coord_x= coord_xc-'A';

    if (armada[coord_x][coord_y]!="--") {
        if (ataque[coord_x][coord_y]!=armada[coord_x][coord_y]){
            printf("\n\n             TIRO NO BARCO!!!!");
            ataque[coord_x][coord_y]=armada[coord_x][coord_y];
            acertou=1;
        }
        else printf("\n\n             TIRO NO BARCO...MAS NO MESMO LOCAL...TIRO PERDIDO."); 
    }

    else{
        printf("\n\n             TIRO NA AGUA!!!!");
        ataque[coord_x][coord_y]="**";

    } 
    return acertou;
}

void imprimir_pontuacao(int atacante,int defensor){

    printf("\n\n      POSICOES INIMIGAS RESTANTES: %i\n",defensor);
    printf("      POSICOES AMIGAS SOBREVIVENTES: %i\n", atacante);

    printf("\n       Para sair digite 'S'.");
}

void mensagem_vencedor(int player){

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n                                                     FIM DO JOGO");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n                                                PLAYER%i FOI O VENCEDOR",player);

    getch();
}

void salvar_jogo( PLAYER player[2]){

    char nome[20];
    char escolha;

    FILE *arq;

    system("cls");

    do{
        printf("Deseja salvar o jogo?(Y/N)");
        scanf(" %c",&escolha);

        escolha=toupper(escolha);

        if (escolha=='Y'){
            printf("Digite um nome para salavar o jogo:");
            scanf(" %s",nome);
            getch();
        }
        
    } while (escolha!='Y' && escolha!='N');
    

}