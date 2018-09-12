
#include "Solver.h"

/**
 *
 * @param game      - a pointer to the current game object that contains all game info
 * @param board     - a 2d int array that contains a copy of the game board (values only)
 * @param lb        - an int array that contains lower bounds for the ILP variables
 *                    (i.e marks the values already in the board)
 * @param vtype     - specifies the type of varibale for the Gurobi model (binary for this case)
 */
/*void createModel(Game*game,int**board,double*lb,char*vtype);*/

/**
 *
 * @param model     - a pointer to the current Gurobi model
 * @param game      - a pointer to the current game object that contains all game info
 * @param ind       - an array that contains the indices of coefficients of the variables
 * @param val       - an array that contains the values of coefficients of the variables
 * @return          - the error code returned from the function "GRBaddconstr"
 */
/*int addConstrains_noEmptyCells(GRBmodel*model,Game*game,int*ind,double*val);*/

/**
 *
 * @param model     - a pointer to the current Gurobi model
 * @param game      - a pointer to the current game object that contains all game info
 * @param ind       - an array that contains the indices of coefficients of the variables
 * @param val       - an array that contains the values of coefficients of the variables
 * @return          - the error code returned from the function "GRBaddconstr"
 */
/*int addConstrains_onceInRow(GRBmodel*model,Game*game,int*ind,double*val);*/

/**
 *
 * @param model     - a pointer to the current Gurobi model
 * @param game      - a pointer to the current game object that contains all game info
 * @param ind       - an array that contains the indices of coefficients of the variables
 * @param val       - an array that contains the values of coefficients of the variables
 * @return          - the error code returned from the function "GRBaddconstr"
 */
/*int addConstrains_onceIncolumn(GRBmodel*model,Game*game,int*ind,double*val);*/

/**
 *
 * @param model     - a pointer to the current Gurobi model
 * @param game      - a pointer to the current game object that contains all game info
 * @param ind       - an array that contains the indices of coefficients of the variables
 * @param val       - an array that contains the values of coefficients of the variables
 * @return          - the error code returned from the function "GRBaddconstr"
 */
/*int addConstrains_onceInBlock(GRBmodel*model,Game*game,int*ind,double*val);*/

/**
 *
 * @param env       - a pointer to the current Gurobi environment
 * @param model     - a pointer to the current Gurobi model
 * @param a,b,c,d,e - pointers to be freed
 */
/*void freeResources(GRBenv*env,GRBmodel*model,void*a,void*b,void*c,void*d,void*e);*/

/**
 *
 * @param game      - a pointer to the current game object that contains all game info
 * @param board     - a 2d int array to be filled with values after optimization
 * @param obj       - a binary array, each cell contains a 1 if the corresponding value should be on the board
 *                    or 0 o.w
 */
/*void updateBoard(Game*game,int**board,double*obj);*/

/**
 *
 * @param game - a pointer to the current game object that contains all game info
 * @param x,y - indices in the game board
 */
void incrementXY(Game * game,int * x,int* y);

/**
 *
 * @param game - a pointer to the current game object that contains all game info
 * @param x,y - indices of the cell to find a legal value to
 * @param from - a lower bound to the values to check if legal
 * @return rightMove - the lowest legal value for the cell (above the lower bound)
 */
int findRightMove(Game* game, int x, int y, int from);


int ILPSolve(Game*game,int**board){
    if(game->mode==1 || board==NULL) {
        printf("hi");
    }
    printf("bye");
    return 1;
}
int countSolutions(Game* game) {
    int x,y,*data,counter,rightMove,value;
    Stack * stack =calloc(1, sizeof(Stack));
    init(stack,DIM*DIM);
    x=0;
    y=0;
    value=0;
    counter=0;
    push(stack,-2,-2);
    while(x!=-2){

        while(x!=-1&&(game->board[x][y].isFixed || (game->board[x][y].isPlayerMove))) {
            incrementXY(game, &x, &y);
            value=0;
        }
        if (x==-1) {
            counter += 1;
            data = pop(stack);
            x = data[0];
            y = data[1];
            value=1;
        }
        else if ((rightMove=findRightMove(game ,x,y,game->board[x][y].value+value))) {
            game->board[x][y].value = rightMove;
            push(stack, x, y);
            incrementXY(game, &x, &y);
            value=0;
        }

        else {
            game->board[x][y].value=0;
            data=pop(stack);
            x=data[0];
            y=data[1];
            value=1;
        }

    }
    freeStack(stack,DIM*DIM);
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
    while (from <= game->blockHeight*game->blockWidth) {
        if (!checkInvalid(game,x,y,from)){
            rightMove = from;
            break;
        }
        from++;

    }
    return rightMove;
}
