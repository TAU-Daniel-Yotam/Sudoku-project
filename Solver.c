
#include "stack.h"
#include "Solver.h"
#include "Game.h"

int ILPSolve(Game*game,int**board){
    if(game->mode==1 || board==NULL) {
        printf("hi");
    }
    printf("bye");
    return 1;
}
int detSolve(Game* game, int**solution) {
    Stack stack;
    init(&stack,DIM*DIM);
    int x=0;
    int y=0;
    int * data;
    int counter;
    int rightMove;
    while(!(x==0&&y==0&&!findRightMove(game,x,y,game->board[x][y].value))){
        while(x!=-1&&(game->board[x][y].isFixed || (game->board[x][y].isPlayerMove))) {
            incrementXY(game, x, y);
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

int incrementXY(Game * game,int * x,int* y){
        if(*y<DIM-1)
            *y++;
        else if(*x<DIM -1) {
            *x++;
            *y = 0;
        }
        else {
            *x == -1;
            *y = -1;
        }

}

int findRightMove(Game* game, int x, int y, int from) {
    int rightMove = 0;
    while (from <= game->blockHeight*game->blockWidth) {
        if (!checkInvalid(&game,x,y,from)){
            rightMove = from;
            break;
        }
        from++;

    }
    return rightMove;
}
