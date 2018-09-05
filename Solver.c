
#include "Solver.h"

void allocateArrays(Game*game,int*ind,double*val,double*lb,double*obj,char*vtype);
int createEnv(GRBmodel*model,GRBenv*env,Game*game,int**board,double*lb,char*vtype);
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
    int       *ind;
    double    *val;
    double    *lb;
    double    *obj;
    char      *vtype;
    int        optimstatus;
    int        error = 0;
    printf("s0\n");
    /*allocateArrays(game,ind,val,lb,obj,vtype);*/

    ind=(int*)calloc((unsigned int)DIM, sizeof(int));
    val=(double*)calloc((unsigned int)DIM, sizeof(double));
    lb=(double*)calloc((unsigned int)DIM*DIM*DIM, sizeof(double));
    vtype=(char*)calloc((unsigned int)DIM*DIM*DIM, sizeof(char));
    obj=(double*)calloc((unsigned int)DIM*DIM*DIM, sizeof(double));

    if(ind==NULL || val==NULL || lb==NULL || vtype==NULL || obj==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    printf("s1\n");
    /* Create new model and environment */
    error = createEnv(model,env,game,board,lb,vtype);
    printf("s1.5\n");
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s2\n");
    /* Each cell gets a value */
    error = addConstrains_noEmptyCells(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s3\n");
    /* Each value must appear once in each row */
    error = addConstrains_onceInRow(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s4\n");
    /* Each value must appear once in each column */
    error = addConstrains_onceIncolumn(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s5\n");
    /* Each value must appear once in each block */
    error = addConstrains_onceInBlock(model,game,ind,val);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s6\n");
    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (error) {
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s7\n");
    error = GRBupdatemodel(model);
    if (error) {
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s8\n");
    /* Optimize model */
    error = GRBoptimize(model);
    if(error){
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s9\n");
    /* Check if model was solved */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) {
        printError(game,ILP_ERROR);
        freeResources(env,model,val,obj,vtype,lb,ind);
        return 0;
    }
    printf("s10\n");
    if(optimstatus!=3 && optimstatus!=4 && optimstatus!=5){
        /* Get the solved board */
        error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, DIM*DIM*DIM, obj);
        printf("s11\n");
        if (error) {
            printError(game,ILP_ERROR);
            freeResources(env,model,val,obj,vtype,lb,ind);
            return 0;
        }
    }
    else{
        printf("s12\n");
        freeResources(env,model,val,obj,vtype,lb,ind);
        return -1;
    }
    printf("s13\n");
    updateBoard(game,board,obj);
    freeResources(env,model,val,obj,vtype,lb,ind);
    printf("s14\n");
    return 1;
}

void allocateArrays(Game*game,int*ind,double*val,double*lb,double*obj,char*vtype){
    ind=(int*)calloc((unsigned int)DIM, sizeof(int));
    val=(double*)calloc((unsigned int)DIM, sizeof(double));
    lb=(double*)calloc((unsigned int)DIM*DIM*DIM, sizeof(double));
    vtype=(char*)calloc((unsigned int)DIM*DIM*DIM, sizeof(char));
    obj=(double*)calloc((unsigned int)DIM*DIM*DIM, sizeof(double));

    if(ind==NULL || val==NULL || lb==NULL || vtype==NULL || obj==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
}


int createEnv(GRBmodel*model,GRBenv*env,Game*game,int**board,double*lb,char*vtype){
    int i,j,v,error;
    printf("create model 0");
    error=0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 1; v <= DIM; v++) {
                if (board[i][j] == v){
                    lb[i*DIM*DIM+j*DIM+v-1] = 1;
                    printf("create model 1");
                }
                else{
                    lb[i*DIM*DIM+j*DIM+v-1] = 0;
                    printf("create model 2");
                }
                vtype[i*DIM*DIM+j*DIM+v-1] = GRB_BINARY;
                printf("create model 3");
            }
        }
    }
    printf("create model 4");
    error = GRBloadenv(&env, NULL) + GRBnewmodel(env, &model, NULL, DIM*DIM*DIM, NULL, lb, NULL,
                                                         vtype, NULL);
    printf("create model 5");
    return error;
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
