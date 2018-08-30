#include "GameAux.h"

int readFromFile2(FILE *file,Game * game,int mode,int markError) {
    int a, b, num, i, j;
    Cell **index;
    fscanf(file, "%d", &a);
    fscanf(file, "%d", &b);
    initGame(game,mode,markError,b,a);
    index = createBoard(a,b);
    game->board = index;
    for (i = 0; i < a * b; i++) {
        for (j = 0; j < a * b; j++) {
            fscanf(file, "%d", &num);
            game->board[i][j].value = num;
            if (getc(file) == '.')
                game->board[i][j].isFixed = 1;
        }
    }
    return 1;
}

void initGame(Game * game,int mode,int markError,int blockHeight,int blockWidth){
    game->blockWidth=blockWidth;
    game->blockHeight=blockHeight;
    game->mode=mode;
    game->markError=markError;
    freeList(game->list);
    game->list=createList();
}

Cell ** createBoard(int columns,int row){
    int i;
    Cell ** board;
    board = (Cell **)calloc((unsigned int)columns * row, sizeof(Cell *));
    if(board==NULL){
        printError(NULL,MEMORY_ALLOC_ERROR);
        return 0;
    }
    for (i = 0; i < columns * row; i++) {
        board[i] = (Cell *)calloc((unsigned int)columns * row, sizeof(Cell));
        if(board[i]==NULL){
            printError(NULL,MEMORY_ALLOC_ERROR);
            return 0;
        }
    }
    return board;
}

void printDashes(int blockWidth,int blockHeight){
    int j;
    for ( j=0;j<4*blockWidth*blockHeight+blockWidth +1;j++){
        printf("-");
        if(j==(4*blockWidth*blockHeight+blockWidth))
            printf("\n");
    }
}


int checkRange(Game* game,int a){
    if(a<0 || a>game->blockHeight*game->blockHeight) return 0;
    return 1;
}


void checkBlock(Game * game,int x,int y){
    int i,j;
    int ** table;
    while (x%game->blockHeight != 1)x--;
    while (y%game->blockWidth != 1)y--;
    table=(int**)calloc((unsigned int)DIM, sizeof(int*));
    if(table==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    for(i=0;i<DIM;i++){
        table[i]=(int*)calloc(2, sizeof(int));
        if(table[i]==NULL){
            printError(game,MEMORY_ALLOC_ERROR);
        }
    }
    for (i=0;i<game->blockHeight;i++){
        for(j=0;j<game->blockWidth;j++){
            if (table[game->board[i+x][j+y].value-1][0]==0){
                table[game->board[i+x][j+y].value-1][0]=x+i+1;
                table[game->board[i+x][j+y].value-1][1]=y+j+1;
            }
            if (table[game->board[i+x][j+y].value-1][0]==-1) {
                game->board[x + i][j + y].isInValid = 1;
            }
            else{
                game->board[table[game->board[i+x][j+y].value-1][0]-1,table[game->board[i+x][j+y].value-1][1]-1]->isInValid=1;
                table[game->board[i+x][j+y].value-1][0]=-1;
                game->board[i+x][y+j].isInValid=1;
            }
        }
    }
    freeMemory((void**)table,DIM,2);
}

void freeMemory(void ** array,int size,int size2){
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size2;j++){
            free(array[j]);
        }
        free(array[i]);
    }
}


void checkRow(Game * game,int x) {
    int i;
    int *line = calloc((unsigned int)DIM, sizeof(int));
    if(line==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    for (i = 0; i < DIM; i++) {
        if (line[game->board[x][i].value - 1] >0) {
            game->board[x][line[game->board[x][i].value - 1] - 1].isInValid = 1;
            line[game->board[x][line[game->board[x][i].value - 1]-1].value]= -1;
            game->board[x][i].isInValid = 1;

        } else if (line[game->board[x][i].value - 1] == -1) {
            game->board[x][i].isInValid = 1;
        } else {
            line[game->board[x][i].value - 1] = i + 1;
        }
    }
    free(line);
}


void checkColumns(Game * game,int x) {
    int i;
    int *line = calloc((unsigned int)DIM, sizeof(int));
    if(line==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    for (i = 0; i < DIM; i++) {
        if (line[game->board[i][x].value - 1] != 0) {
            game->board[line[i] - 1][x].isInValid = 1;
            line[game->board[i][x].value - 1] = -1;
            game->board[i][x].isInValid = 1;

        } else if (line[game->board[i][x].value - 1] == -1) {
            game->board[i][x].isInValid = 1;
        } else {
            line[game->board[i][x].value - 1] = i + 1;
        }
    }
    free(line);
}
int fillXvalues(Game*game,int x){
    int tries,count,i,j,size;
    int*values;
    int a[2]={0};
    tries=0;
    count=0;
    while (tries<1000 && count<x) {
        do {
            i = rand() % DIM;
            j = rand() % DIM;
        } while (game->board[i][j].value);
        size = countPossibleValues(game,a,i,j);
        if(size>0) {
            values = (int *) calloc((unsigned int)size, sizeof(int));
            if (values == NULL) {
                printError(game, MEMORY_ALLOC_ERROR);
                return 0;
            }
            createValuesArray(game,i,j,values);
            game->board[i][j].value = values[rand() % size];
            count++;
            free(values);
            continue;
        }
        tries++;
    }
    if(count<x) tries++;
    return tries;
}
int checkEmpty(Game*game){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(game->board[i][j].value) return 0;
        }
    }
    return 1;
}

void createValuesArray(Game*game,int x,int y,int* values){
    int i=1,j=0;
    for(;i<DIM;i++){
        game->board[x][y].value=i;
        checkBlock(game,x,y);
        checkRow(game,y);
        checkColumns(game,x);
        if(!game->board[x][y].isInValid){
            values[j]=i;
            j++;
        }
        game->board[x][y].value=0;
        checkBlock(game,x,y);
        checkRow(game,y);
        checkColumns(game,x);
    }
}

void createListDataGenerate(Game*game,int**listData){
    int i,j,count;
    count=0;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(game->board[i][j].value){
                listData[count]=(int*)calloc(4, sizeof(int));
                if(listData[count]==NULL){
                    printError(game,MEMORY_ALLOC_ERROR);
                }
                listData[count][0]=i;
                listData[count][1]=j;
                listData[count][2]=0;
                listData[count][3]=game->board[i][j].value;
            }
        }
    }
}

int checkError(Game *game) {

    int i,j;
    for (i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(game->board[i][j].isInValid){
                return 0;
            }
        }
    }
    return 1;

}

int writeToFile(Game *game, FILE *file) {
    Cell **index;
    int i, j;
    fprintf(file, "%d ", game->blockWidth);
    fprintf(file, "%d\n", game->blockHeight);
    index = game->board;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            fprintf(file, "%d", index[i][j].value);
            if (index[i][j].isFixed == 1||(game->mode==2&&index[i][j].value!=0))
                fprintf(file, ".");
            if (j == (DIM - 1))
                fprintf(file, "\n");
            else
                fprintf(file, "\t");

        }
    }
    return 1;
}


int**copyBoard(Game*game){
    int size,i,j;
    int**board;
    size=DIM;
    board=(int**)calloc((unsigned int)size,sizeof(int*));
    if(board==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
        return NULL;
    }
    for(i=0;i<size;i++){
        board[i]=(int*)calloc((unsigned int)size, sizeof(int));
        if(board[i]==NULL){
            printError(game,MEMORY_ALLOC_ERROR);
            return NULL;
        }
        for(j=0;j<size;j++){
            board[i][j]=game->board[i][j].value;
        }
    }
    return board;
}
int countPossibleValues(Game*game,int*num_val,int x, int y){
    int i,first=1;
    num_val[0]=0;
    num_val[1]=0;
    for(i=1;i<=DIM;i++){
        if(!checkInvalid(game,x,y,i)){
            if(first){
                num_val[1]=i;
                first=0;
            }
            num_val[0]++;
        }
    }
    return num_val[0];
}


void fillValues(Game*game,int**values,int size){
    int i;
    for(i=0;i<size;i++){
        game->board[values[i][0]][values[i][1]].value=values[i][3];
        game->board[values[i][0]][values[i][1]].isPlayerMove=1;
        printf("Cell <%d,%d> set to %d\n",values[i][0],values[i][1],values[i][3]);
    }
}

void updateCellValidity(Game*game){
    int i,j;
    for (i=0;i<DIM;i++) {
        checkRow(game, i);
    }
    for ( j=0;j<DIM;j++) {
        checkColumns(game, j);
    }
    for(i=0;i<DIM;i++){
        for(j=0;DIM;j++){
            if(i%game->blockHeight==0 &&j%game->blockWidth==0){
                checkBlock(game,i,j);
            }
        }
    }
}

void freeGame(Game*game){
    freeBoard(game);
    freeList(game->list);
}

void freeBoard(Game*game){
    int i;
    for(i=0;i<DIM;i++){
        free(game->board[i]);
    }
    free(game->board);
}


/*
void clearBoard(Game*game){
    int i,j;
    for(i=0;i<Line(game->blockWidth,game->blockHeight);i++){
        for(j=0;j<Line(game->blockWidth,game->blockHeight);j++){
            game->board[i][j].value=0;
        }
    }

}

*/













