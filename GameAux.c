#include "GameAux.h"

int readFromFile(FILE *file,Game * game,int mode) {
    int a, b, num, i, j,eof;
    Cell **index;
    eof=fscanf(file, "%d", &a);
    if(!eof){
        printError(game,SOLVE_IO_ERROR);
    }
    eof=fscanf(file, "%d", &b);
    if(!eof){
        printError(game,SOLVE_IO_ERROR);
    }
    initGame(game,mode,a,b);
    index = createBoard(b,a);
    game->board = index;
    for (i = 0; i < a * b; i++) {
        for (j = 0; j < a * b; j++) {
            eof=fscanf(file, "%d", &num);
            if(!eof){
                printError(game,SOLVE_IO_ERROR);
                freeGame(game);
                return 0;
            }
            if(num)
                game->board[i][j].isPlayerMove=1;
            game->board[i][j].value = num;
            if (getc(file) == '.' && game->mode==1)
                game->board[i][j].isFixed = 1;
        }
    }
    return 1;
}

/* init current game instance */
void initGame(Game * game,int mode,int blockHeight,int blockWidth){
    if(game->board!=NULL){
        freeBoard(game);
    }
    if(game->list!=NULL)
        freeList(game->list);
    game->blockWidth=blockWidth;
    game->blockHeight=blockHeight;
    game->mode=mode;
    game->list=createList();

}

Cell ** createBoard(int columns,int row){
    int i;
    Cell ** board;
    board = (Cell**)calloc((unsigned int)(columns * row), sizeof(Cell*));
    if(board==NULL){
        printError(NULL,MEMORY_ALLOC_ERROR);
        return 0;
    }
    for (i = 0; i < columns * row; i++) {
        board[i] = (Cell *)calloc((unsigned int)(columns * row), sizeof(Cell));
        if(board[i]==NULL){
            printError(NULL,MEMORY_ALLOC_ERROR);
            return 0;
        }
    }
    return board;
}

/* used in printBoard function */
void printDashes(int blockWidth,int blockHeight){
    int j;
    for ( j=0;j<4*blockWidth*blockHeight+blockHeight +1;j++){
        printf("-");
        if(j==(4*blockWidth*blockHeight+blockHeight))
            printf("\n");
    }
}

/*type: 0 for 0-N or 1 for 1-N */
int checkRange(Game* game,int a,int type){
    if((a<0 || a > DIM) && type==1) return 0;
    if((a<=0 || a> DIM) && type==0) return 0;
    return 1;
}

/* return 1 if *NOT* valid */
int isInvalid(Cell * cell){
return cell->isInValidInColumns||cell->isInValidInBlock||cell->isInValidInRow;
}

void checkBlock(Game * game,int x,int y){
    int i,j;
    int ** table;
    while (x%game->blockHeight != 0)x--;
    while (y%game->blockWidth != 0)y--;
    table=(int**)calloc((unsigned int)DIM, sizeof(int*));
    if(table==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    for(i=0;i<DIM;i++){
        table[i]=(int*)calloc(3, sizeof(int));
        if(table[i]==NULL){
            printError(game,MEMORY_ALLOC_ERROR);
        }
    }
    for (i=0;i<game->blockHeight;i++){
        for(j=0;j<game->blockWidth;j++){
            if(game->board[i+x][j+y].value==0){
                game->board[i+x][j+y].isInValidInBlock=0;
                continue;
            }
            if (table[game->board[i+x][j+y].value-1][0]==0){
                table[game->board[i+x][j+y].value-1][0]=x+i+1;
                table[game->board[i+x][j+y].value-1][1]=y+j+1;
                game->board[i+x][j+y].isInValidInBlock=0;
            }
            else if (table[game->board[i+x][j+y].value-1][0]==-1) {
                game->board[x + i][j + y].isInValidInBlock= 1;
            }
            else{
                game->board[table[game->board[i+x][j+y].value-1][0]-1][table[game->board[i+x][j+y].value-1][1]-1].isInValidInBlock=1;
                table[game->board[i+x][j+y].value-1][0]=-1;
                game->board[i+x][y+j].isInValidInBlock=1;
            }
        }
    }
    freeMemory((void**)table,DIM);
}

void freeMemory(void ** array,int size){
    int i;
    for(i=0;i<size;i++) {
        free(array[i]);
    }
    free(array);
}

void checkColumns(Game *game, int x) {
    int i;
    int *line = calloc((unsigned int)DIM, sizeof(int));
    if(line==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    for (i = 0; i < DIM; i++) {
        if (game->board[x][i].value==0){
            game->board[x][i].isInValidInRow=0;
            continue;
        }

        if (line[game->board[x][i].value - 1] >0) {
            game->board[x][line[game->board[x][i].value - 1] - 1].isInValidInRow = 1;
            line[game->board[x][i].value - 1]=-1;
            game->board[x][i].isInValidInRow = 1;

        }
        else if (line[game->board[x][i].value - 1] == -1) {
            game->board[x][i].isInValidInRow = 1;
        }
        else {
            line[game->board[x][i].value - 1] = i + 1;
            game->board[x][i].isInValidInRow=0;
        }
    }
    free(line);
}

void checkRows(Game *game, int x) {
    int i;
    int *line = calloc((unsigned int)DIM, sizeof(int));
    if(line==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
    }
    for (i = 0; i < DIM; i++) {
        if (game->board[i][x].value==0){
            game->board[i][x].isInValidInColumns=0;
            continue;
        }
        if (line[game->board[i][x].value - 1] >0) {
            game->board[line[game->board[i][x].value - 1] - 1][x].isInValidInColumns = 1;
            line[game->board[i][x].value - 1]=-1;
            game->board[i][x].isInValidInColumns = 1;

        } else if (line[game->board[i][x].value - 1] == -1) {
            game->board[i][x].isInValidInColumns = 1;
        } else {
            line[game->board[i][x].value - 1] = i + 1;
            game->board[i][x].isInValidInColumns=0;
        }
    }
    free(line);
}

/* used by the 'generate' function */
int fillXvalues(Game*game,int x){
    int tries,count,i,j,size;
    int value;
    int a[2]={0};
    tries=0;
    count=0;
    value=1;
    while (tries<1000 && count<x) {
        do {
            i = rand() % DIM;
            j = rand() % DIM;
        } while (game->board[i][j].value);
        size = countPossibleValues(game,a,i,j);
        if(size>0) {
            while(checkInvalid(game,i,j,value)){
                value = rand()%DIM +1;
            }
            game->board[i][j].value = value;
            count++;
            continue;
        }
        tries++;
    }
    if(count<x) tries++;
    return tries;
}


/* used by the 'generate' function */
int checkEmpty(Game*game){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(game->board[i][j].value) return 0;
        }
    }
    return 1;
}

/* used by the 'generate' function */
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
                count++;
            }
        }
    }
}

void updateGameBoard(Game*game,int**board){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            game->board[i][j].value=board[i][j];
        }
    }
}



int writeToFile(Game *game, FILE *file) {
    Cell **index;
    int i, j;
    fprintf(file, "%d ", game->blockHeight);
    fprintf(file, "%d\n", game->blockWidth);
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

/* creates a 'light' copy of the board - values only */
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

/* creates a 'deep' copy of the board - full cells properties */
Cell ** copyCellBoard(Game * game){
    int i,j;
    Cell ** board= createBoard(game->blockHeight,game->blockWidth);
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(game->board[i][j].value)
                board[i][j].isPlayerMove=1;
            board[i][j].value=game->board[i][j].value;
            board[i][j].isFixed=game->board[i][j].isFixed;
            board[i][j].isInValidInBlock=game->board[i][j].isInValidInBlock;
            board[i][j].isInValidInRow=game->board[i][j].isInValidInRow;
            board[i][j].isInValidInColumns=game->board[i][j].isInValidInColumns;
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


void emptyBoard(Game*game){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            game->board[i][j].value=0;
        }
    }
}

void updateCellValidity(Game*game) {
    int i, j;
    for (i = 0; i < DIM; i++) {/* check all columns */
        checkColumns(game, i);
    }
    for (j = 0; j < DIM; j++) {/* check all rows */
        checkRows(game, j);
    }
    for (i = 0; i < DIM; i++) { /* check all blocks */
        for (j = 0; j<DIM; j++) {
            if (i % game->blockHeight == 0 && j % game->blockWidth == 0) {
                checkBlock(game, i, j);
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


int checkInvalid(Game* game, int x, int y, int value) {
    int result;
    int temp = game->board[x][y].value;
    game->board[x][y].value = value; /* change the value */
    checkBlock(game, x, y);
    checkColumns(game, x); /* update validity */
    checkRows(game, y);
    result = isInvalid(&game->board[x][y]); /* check it's validity */
    game->board[x][y].value = temp; /* change back to original value */
    checkBlock(game, x, y);
    checkColumns(game, x);
    checkRows(game, y); /* restore previous validity */
    return result;
}


int checkError(Game *game) {

    int i,j;
    for (i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(isInvalid(&(game->board[i][j]))){
                return 0;
            }
        }
    }
    return 1;

}













