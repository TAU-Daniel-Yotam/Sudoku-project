
#include "MainAux.h"


int arrComp(int*a1, int size1, int*a2, int size2){
   int i;
    if(a1!=NULL && a2!=NULL){
        if (size1!=size2) return 0;
        for(i=0;i<size1;i++){
            if(a1[i]!=a2[i]) return 0;
        }
        return 1;
    }
    else{
        return a1==a2;
    }
}

void printArray(void*a, int size) {
    int i;
    int*x = (int*)a;
    for (i = 0; i<size; i++) {
        printf("a[%d]=%d ", i, x[i]);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}

int initArray(int*a, int size, int initValue){
    int i;
    for(i=0;i<size;i++){
        a[i]=initValue;
    }
    return 0;
}

int checkWinningGame(Game*game){
    if(game!=NULL) return 1;
    return 0;
}


/*int checkValid(Game* game, int x, int y, int value) {
    if(!value) return 1;
    return checkBlock(game, x, y, value) || checkRowColumn(game, x, y, value);
}

int checkBlock(Game* game, int x, int y, int value) {
    int k, r, i=x, j=y,sign=0;
    while (x%game->columns != 1)x--;
    while (y%game->rows != 1)y--;
    for (k = 0; k<game->rows; k++) {
        for (r = 0; r<game->columns; r++) {
            if (game->board[x][y].value == value && k!=j && r!=i){
                sign=1;
                game->board[x][y].isInValid=1;
            }

            x++;
        }
        y++;
    }
    return sign;
}
int checkRowColumn(Game* game, int x, int y, int value) {
    int i,sign=0;
    for(i=0;i<game->rows*game->columns;i++) {
        if (i != y && game->board[x][i].value == value) {
            sign = 1;
            game->board[x][i].isInValid = 1;
        }
    }
    for(i=0;i<game->columns;i++){
        if(i!=x && game->board[i][y].value==value) {
            game->board[i][y].isInValid=1;
            sign=1;

        }
    }
    return sign;
}*/

