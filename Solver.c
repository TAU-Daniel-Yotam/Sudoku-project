
#include "Solver.h"

void incrementXY(Game*game, int*x, int*y);
int findRightMove(Game* game, int x, int y, int from);

int ILPSolve(Game*game,int**board){
    if(game->mode==1 || board==NULL) {
        printf("hi");
    }
    printf("bye");
    return 1;
}
int detSolve(Game* game) {
    Stack stack;
    int * data;
    int counter;
    int rightMove,x,y;
    init(&stack,DIM*DIM);
    x=0;
    y=0;
    counter=0;
    init(&stack,DIM*DIM);
    while(!(x==0&&y==0&&!findRightMove(game,x,y,game->board[x][y].value))){
        while(x!=-1&&(game->board[x][y].isFixed || (game->board[x][y].isPlayerMove))) {
            incrementXY(game, &x, &y);
        }
        if (x==-1) {
            counter += 1;
            data = pop(&stack);
            x = data[0];
            y = data[1];
        }
        else if ((rightMove=findRightMove(game ,x,y,game->board[x][y].value+1))) {
            game->board[x][y].value = rightMove;
            push(&stack, x, y);
            incrementXY(game, &x, &y);
        }

        else {
            data=pop(&stack);
            x=data[0];
            y=data[1];
        }

    }
    return counter;
}

void incrementXY(Game * game,int * x,int* y){
    if(*y<DIM-1)
        (*y)++;
    else if(*x<DIM -1) {
        (*x)++;
        (*y) = 0;
    }
    else {
        (*x) = -1;
        (*y) = -1;
    }

}

int findRightMove(Game* game, int x, int y, int from) {
    int rightMove = 0;
    while (from <= game->blockHeight*game->blockWidth) {
        if (!checkInvalid(game,x,y,from)){
            rightMove = from;
            break;
        }
        from++;

    }
    return rightMove;
}
