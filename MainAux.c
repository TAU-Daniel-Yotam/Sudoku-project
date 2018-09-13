
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

int checkFullBoard(Game*game){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(game->board[i][j].value==0)
                return 0;
        }
    }

    return 1;
}
