#define ROW 3
#define COL 3
int main(int argc, char *argv[])
{
    int i, j;
    int um = 1;
    char buffer[2];
    char *matrix[ROW][COL];/* = {
        {"aa", "bb", "cc"},
        {"dd", "ee", "ff"},
        {"gg", "hh", "ii"},
    };*/

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            matrix[i][j] = "--";
        }
    }
    sprintf(buffer,"P%d", 1);
    matrix[1][1] = buffer;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            printf("%s\t", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}