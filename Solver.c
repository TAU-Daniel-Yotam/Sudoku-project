
#include "Solver.h"

void createModel(Game*game,int**board,double*lb,char*vtype);
int addConstrains_noEmptyCells(GRBmodel*model,Game*game,int*ind,double*val);
int addConstrains_onceInRow(GRBmodel*model,Game*game,int*ind,double*val);
int addConstrains_onceIncolumn(GRBmodel*model,Game*game,int*ind,double*val);
int addConstrains_onceInBlock(GRBmodel*model,Game*game,int*ind,double*val);
void freeResources(GRBenv*env,GRBmodel*model,void*a,void*b,void*c,void*d,void*e);
void updateBoard(Game*game,int**board,double*obj);
void incrementXY(Game * game,int * x,int* y);
int findRightMove(Game* game, int x, int y, int from);


int ILPSolve(Game*game,int**board){
    GRBenv    *env;
    GRBmodel  *model;
    int        error,optimstatus;
    int       *ind=(int*)calloc((unsigned int)DIM, sizeof(int));
    double    *val=(double*)calloc((unsigned int)DIM, sizeof(double));
    double    *lb=(double*)calloc((unsigned int)DIM*DIM*DIM, sizeof(double));
    double    *obj=(double*)calloc((unsigned int)DIM*DIM*DIM, sizeof(double));
    char      *vtype=(char*)calloc((unsigned int)DIM*DIM*DIM, sizeof(char));
    error = 0;
    env=NULL;
    model=NULL;

    if(ind==NULL || val==NULL || lb==NULL || vtype==NULL || obj==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    /* Create new model and environment */
    createModel(game,board,lb,vtype);
    error = GRBloadenv(&env, NULL) +
            GRBnewmodel(env, &model, NULL, DIM*DIM*DIM, NULL, lb, NULL, vtype, NULL);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    /* Each cell gets a value */
    error = addConstrains_noEmptyCells(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    /* Each value must appear once in each row */
    error = addConstrains_onceInRow(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    /* Each value must appear once in each column */
    error = addConstrains_onceIncolumn(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    /* Each value must appear once in each block */
    error = addConstrains_onceInBlock(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (error) {
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    error = GRBupdatemodel(model);
    if (error) {
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    /* Optimize model */
    error = GRBoptimize(model);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    /* Check if model was solved */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) {
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    if(optimstatus!=3 && optimstatus!=4 && optimstatus!=5){
        /* Get the solved board */
        error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, DIM*DIM*DIM, obj);
        if (error) {
            printError(game,ILP_ERROR);
            freeResources(env,model,val,obj,vtype,lb,ind);
            return 0;
        }
    }
    else{
        freeResources(env,model,val,obj,vtype,lb,ind);
        return -1;
    }
    updateBoard(game,board,obj);
    free(ind); free(lb); free(vtype); free(obj); free(val);
    GRBfreemodel(model);
    GRBfreeenv(env);
    /*freeResources(env,model,val,obj,vtype,lb,ind);*/
    return 1;
}

void createModel(Game*game,int**board,double*lb,char*vtype){
    int i,j,v;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 1; v <= DIM; v++) {
                if (board[i][j] == v){
                    lb[i*DIM*DIM+j*DIM+v-1] = 1;
                }
                else{
                    lb[i*DIM*DIM+j*DIM+v-1] = 0;
                }
                vtype[i*DIM*DIM+j*DIM+v-1] = GRB_BINARY;
            }
        }
    }
}

int addConstrains_noEmptyCells(GRBmodel*model,Game*game,int*ind,double*val){
    int i,j,v,error=0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                ind[v] = i*DIM*DIM + j*DIM + v;
                val[v] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
        }
    }
    return error;
}

int addConstrains_onceInRow(GRBmodel*model,Game*game,int*ind,double*val){
    int i,j,v,error=0;
    for (v = 0; v < DIM; v++) {
        for (j = 0; j < DIM; j++) {
            for (i = 0; i < DIM; i++) {
                ind[i] = i*DIM*DIM + j*DIM + v;
                val[i] = 1.0;
            }

            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
        }
    }
    return error;
}

int addConstrains_onceIncolumn(GRBmodel*model,Game*game,int*ind,double*val){
    int i,j,v,error=0;
    for (v = 0; v < DIM; v++) {
        for (i = 0; i < DIM; i++) {
            for (j = 0; j < DIM; j++) {
                ind[j] = i*DIM*DIM + j*DIM + v;
                val[j] = 1.0;
            }

            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
        }
    }
    return error;
}

int addConstrains_onceInBlock(GRBmodel*model,Game*game,int*ind,double*val){
    int i,j,v,error,ig,jg,count;
    error=0;
    for (v = 0; v < DIM; v++) {
        for (ig = 0; ig < SUBDIM1; ig++) {
            for (jg = 0; jg < SUBDIM2; jg++) {
                count = 0;
                for (i = ig*SUBDIM1; i < (ig+1)*SUBDIM1; i++) {
                    for (j = jg*SUBDIM2; j < (jg+1)*SUBDIM2; j++) {
                        ind[count] = i*DIM*DIM + j*DIM + v;
                        val[count] = 1.0;
                        count++;
                    }
                }

                error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            }
        }
    }
    return error;
}

void freeResources(GRBenv*env,GRBmodel*model,void*a,void*b,void*c,void*d,void*e){
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    if(env!=NULL)
        GRBfreemodel(model);
    if(model!=NULL)
        GRBfreeenv(env);
}


void updateBoard(Game*game,int**board,double*obj){
    int i,j,v;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 1; v <= DIM; v++) {
                if(obj[i*DIM*DIM + j*DIM + v-1]){
                    board[i][j]=v;
                }
            }
        }
    }
}

int detSolve(Game* game) {
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
