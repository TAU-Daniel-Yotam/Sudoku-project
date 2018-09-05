
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
    Stack  stack;
    init(&stack,DIM*DIM);
    int x=0;
    int y=0;
    int from;
    int * data;
    int counter;
    int rightMove;
    int value=0;

    counter=0;
    push(&stack,-2,-2);
    while(x!=-2){
        printf("%d",x);
        printf("%d",y);
        while(x!=-1&&(game->board[x][y].isFixed || (game->board[x][y].isPlayerMove))) {
            incrementXY(game, &x, &y);
            value=0;
        }
        if (x==-1) {
            counter += 1;
            data = pop(&stack);
            x = data[0];
            y = data[1];
            value=1;
        }
        else if ((rightMove=findRightMove(game ,x,y,game->board[x][y].value+value))) {
            game->board[x][y].value = rightMove;
            push(&stack, x, y);
            incrementXY(game, &x, &y);
            value=0;
        }

        else {
            game->board[x][y].value=0;
            data=pop(&stack);
            x=data[0];
            y=data[1];
            value=1;
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
    from=from==0?1:from;
    printf("hi");
    while (from <= game->blockHeight*game->blockWidth) {
        if (!checkInvalid(game,x,y,from)){
            rightMove = from;
            break;
        }
        from++;

    }
    return rightMove;
}
