

#include "Solver.h"
int addConstrains();
void allocateArrays(Game*game,int*,double*,double*,char*,char**,char*);

int ILPSolve(Game*game,int**board){
    GRBenv   *env   = NULL;
    GRBmodel *model = NULL;
    int       *ind=NULL;
    double    *val=NULL;
    double    *lb=NULL;
    char      *vtype=NULL;
    char     **names=NULL;
    char      *namestorage=NULL;
    char      *cursor;
    int        optimstatus;
    double     objval;
    int        i, j, v, ig, jg, count;
    int        error = 0;

    allocateArrays(game,ind,val,lb,vtype,names,namestorage);

    /* Create an empty model */
    cursor = namestorage;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                if (board[i][j] == v)
                    lb[i*DIM*DIM+j*DIM+v] = 1;
                else
                    lb[i*DIM*DIM+j*DIM+v] = 0;
                vtype[i*DIM*DIM+j*DIM+v] = GRB_BINARY;

                names[i*DIM*DIM+j*DIM+v] = cursor;
                sprintf(names[i*DIM*DIM+j*DIM+v], "x[%d,%d,%d]", i, j, v+1);
                cursor += strlen(names[i*DIM*DIM+j*DIM+v]) + 1;
            }
        }
    }

    /* Create environment */

    error = GRBloadenv(&env, "sudoku.log");
    if (error) goto QUIT;

    /* Create new model */

    error = GRBnewmodel(env, &model, "sudoku", DIM*DIM*DIM, NULL, lb, NULL,
                        vtype, names);
    if (error) goto QUIT;

    /* Each cell gets a value */

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                ind[v] = i*DIM*DIM + j*DIM + v;
                val[v] = 1.0;
            }

            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) goto QUIT;
        }
    }

    /* Each value must appear once in each row */

    for (v = 0; v < DIM; v++) {
        for (j = 0; j < DIM; j++) {
            for (i = 0; i < DIM; i++) {
                ind[i] = i*DIM*DIM + j*DIM + v;
                val[i] = 1.0;
            }

            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) goto QUIT;
        }
    }

    /* Each value must appear once in each column */

    for (v = 0; v < DIM; v++) {
        for (i = 0; i < DIM; i++) {
            for (j = 0; j < DIM; j++) {
                ind[j] = i*DIM*DIM + j*DIM + v;
                val[j] = 1.0;
            }

            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) goto QUIT;
        }
    }

    /* Each value must appear once in each block */

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
                if (error) goto QUIT;
            }
        }
    }

    /* Optimize model */

    error = GRBoptimize(model);
    if (error) goto QUIT;

    /* Write model to 'sudoku.lp' */

    error = GRBwrite(model, "sudoku.lp");
    if (error) goto QUIT;

    /* Capture solution information */

    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) goto QUIT;

    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) goto QUIT;

    printf("\nOptimization complete\n");
    if (optimstatus == GRB_OPTIMAL)
        printf("Optimal objective: %.4e\n", objval);
    else if (optimstatus == GRB_INF_OR_UNBD)
        printf("Model is infeasible or unbounded\n");
    else
        printf("Optimization was stopped early\n");
    printf("\n");

    QUIT:

    /* Error reporting */

    if (error) {
        printf("ERROR: %s\n", GRBgeterrormsg(env));
        exit(1);
    }

    /* Free model */

    GRBfreemodel(model);

    /* Free environment */

    GRBfreeenv(env);

    return 0;
}

void allocateArrays(Game*game,int*ind,double*val,double*lb,char*vtype,char**names,char*namestorage){
    ind=(int*)calloc(DIM, sizeof(int));
    val=(double*)calloc(DIM, sizeof(double));
    lb=(double*)calloc(DIM*DIM*DIM, sizeof(double));
    vtype=(char*)calloc(DIM*DIM*DIM, sizeof(char));
    names=(char**)calloc(DIM*DIM*DIM, sizeof(char*));
    namestorage=(char*)calloc(10*DIM*DIM*DIM, sizeof(char));

    if(ind==NULL || val==NULL || lb==NULL || vtype==NULL || names==NULL || namestorage==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
}