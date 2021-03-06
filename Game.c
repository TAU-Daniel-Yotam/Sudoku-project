
#include "Game.h"

int solve(Game* game, char * filePath){
    FILE * file;
    file = fopen(filePath,"r");
    if(file==NULL){
        printError(NULL,SOLVE_IO_ERROR);
        return 0;
    }
    readFromFile(file,game,1);
    fclose(file);
    return 1;
}
int edit(Game * game, char * filePath){
    FILE * file;
    if (filePath!=NULL) {
        file = fopen(filePath, "r");
        if (file == NULL) {
            printError(NULL, EDIT_IO_ERROR);
            return 0;

        }
        readFromFile(file, game,2);
        fclose(file);
    }
    else {
        initGame(game,2,3,3);
        game->board = createBoard(3, 3);
    }
    return 1;
}

int mark_errors(Game* game, int arg){
    if(arg!=0 && arg!=1){
        printError(game,BINARY_RANGE_ERROR);
        return 0;
    }
    game->markError=arg;
    return 1;
}

void printBoard(Game * game) {
    int i, j;
    Cell index;
    for (i = 0; i < DIM; i++) {
        if (!(i % game->blockHeight))
            printDashes(game->blockWidth, game->blockHeight);
        for (j = 0; j < game->blockWidth*game->blockHeight; j++) {
            if (!(j % game->blockWidth))
                printf("|");
            index = game->board[i][j];
            if (index.isFixed)
                printf(" %2d.", index.value);

            else if (isInvalid(&index) && (game->markError||game->mode==2)&&index.value)
                printf(" %2d*", index.value);
            else {

                if (index.value != 0)
                    printf(" %2d ", index.value);
                else
                    printf("    ");

            }
        }
        printf("|\n");
    }
    printDashes(game->blockWidth, game->blockHeight);
}

int set(Game* game,int x,int y,int value){
    int** listData ;
    if(!checkRange(game,x+1,0) || !checkRange(game,y+1,0) || !checkRange(game,value,1)){
        printError(game,VALUE_RANGE_ERROR);
        return 0;
    }
     if(game->board[x][y].isFixed){
        printError(game,CELL_FIXED_ERROR);
        return 0;
    }
    listData=(int**)calloc(1, sizeof(int *));/* list data format: 0:x,1:y,2:from,3:to */
    if(listData==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
        return 0;
    }
    listData[0]=(int*)calloc(4, sizeof(int));
    if(listData[0]==NULL){
        printError(game,MEMORY_ALLOC_ERROR);
        return 0;
    }
    listData[0][0]=x;
    listData[0][1]=y;
    listData[0][2]=game->board[x][y].value;
    listData[0][3]=value;
    addLast(game->list,listData,1);

    game->board[x][y].value=value;
    checkBlock(game,x,y);
    checkColumns(game, x);
    checkRows(game, y);
    return 1;
}

int validate(Game *game,int toPrint) {
    int**board,res;
    if(!checkError(game)){
        printError(NULL,ERRONEOUS_BOARD_ERROR);
        return 0;
    }
    board=copyBoard(game);
    res=ILPSolve(game,board);
    if(res==-1){
        freeMemory((void*)board,DIM);
        if(toPrint)
            printf("Validation failed: board is unsolvable\n");
        return 0;
    }
    if(toPrint)
        printf("Validation passed: board is solvable\n");
    freeMemory((void**)board,DIM);
    return 1;

}

int generate(Game*game,int x,int y){
    int i,j,tries,removed,solved;
    int ** listData, **board;
    removed=0;
    tries=0;
    solved=-1;
    if(x<0 || x>DIM*DIM || y<0 || y>DIM*DIM){
        printError(game,VALUE_RANGE_ERROR);
        return 0;
    }
    if(!checkEmpty(game)){
        printError(game,BOARD_NOT_EMPTY_ERROR);
        return 0;
    }
    do { /* fill X values and then solve the board */
        emptyBoard(game);
        tries += fillXvalues(game, x);
        if(tries==1001){
            printError(game,GENERATOR_FAILED_ERROR);
            return 0;
        }
        board = copyBoard(game);
        solved = ILPSolve(game,board);
        if(solved==-1) tries++;
    }while (solved==-1);
    updateGameBoard(game,board);
    freeMemory((void**)board,DIM);
    while(removed < DIM*DIM-y){ /* remove all but y cells */
        do {
            i = rand() % DIM;
            j = rand() % DIM;
        } while (!game->board[i][j].value);
        game->board[i][j].value=0;
        removed++;
    }
    listData = (int**)calloc(y, sizeof(int*));
    if(listData==NULL){
        printError(NULL,MEMORY_ALLOC_ERROR);
        return 0;
    }
    createListDataGenerate(game,listData);
    addLast(game->list,listData,y);
    return 1;
}
int undo(Game * game) {
    int i;
    char from,to;
    int *move;
    if (!game->list->length || game->list->pointer == NULL) {
        printError(game,UNDO_ERROR);
        return 0;
    }
    for (i = 0; i < game->list->pointer->size; i++) {
        move = game->list->pointer->data[i];
        game->board[move[0]][move[1]].value = move[2];
        checkColumns(game, move[0]);
        checkRows(game, move[1]);
        checkBlock(game, move[0], move[1]);
    }
    printBoard(game);
    for (i=0;i<game->list->pointer->size;i++){
        move = game->list->pointer->data[i];
        from = (char)(move[2] == 0 ? '_' : move[2] + '0');
        to = (char)(move[3] == 0 ? '_' : move[3] + '0');
        printf("Undo %d,%d: from %c to %c\n", move[1]+1, move[0]+1, to, from);
    }
    game->list->pointer = game->list->pointer->previous;
    if(i==0) printBoard(game);
    return 1;
}


int redo(Game *game) {
    char from;
    char to;
    int i;
    int *move;
    if (!game->list->length || game->list->pointer== game->list->tail) {
        printError(game,REDO_ERROR);
        return 0;
    }
    if(game->list->pointer!=NULL)
        game->list->pointer = game->list->pointer->next;
    else
        game->list->pointer=game->list->head;
    for (i = 0; i < game->list->pointer->size; i++) {
        move = game->list->pointer->data[i];
        game->board[move[0]][move[1]].value = move[3];
        checkColumns(game, move[0]);
        checkRows(game, move[1]);
        checkBlock(game, move[0], move[1]);
    }
    printBoard(game);
    for(i=0;i<game->list->pointer->size;i++){
        move = game->list->pointer->data[i];
        from = (char)(move[2] == 0 ? '_' : move[2] + '0');
        to = (char)(move[3] == 0 ? '_' : move[3] + '0');
        printf("Redo %d,%d: from %c to %c\n", move[1]+1, move[0]+1, from, to);
    }
    return 1;
}

int save(Game *game, char *path) {
    FILE *file=fopen(path,"w");
    if (file == NULL) {
        printError(game,SOLVE_IO_ERROR);
        return 0;
    }
    if (game->mode == 2 && !checkError(game)) {
        printError(game,ERRONEOUS_BOARD_ERROR);
        return 0;
    }
    if (game->mode == 2 && !validate(game,0)) {
        printError(game,VALIDATION_FAILED_ERROR);
        return 0;
    }
    writeToFile(game,file);
    printf("Saved to: %s\n",path);
    fclose(file);
    return 1;
}

int hint(Game* game, int x, int y){
    int**board;
    if(!checkRange(game,x,0) || !checkRange(game,y,0)){
        printError(game,VALUE_RANGE_ERROR);
        return 0;
    }
    if(!checkError(game)){
        printError(game,ERRONEOUS_BOARD_ERROR);
        return 0;
    }
    if(game->board[x][y].isFixed){
        printError(game,CELL_FIXED_ERROR);
        return 0;
    }
    if(game->board[x][y].value){
        printError(game,CELL_HAS_VALUE_ERROR);
        return 0;
    }
    board=copyBoard(game);
    if(!ILPSolve(game,board)){
        printError(game,BOARD_UNSOLVABLE_ERROR);
        return 0;
    }
    printf("Hint: set cell to %d\n",board[x][y]);
    return 1;
}

int numSolution(Game * game){
    int number;
    Game * newGame;
    if(!checkError(game)) {
        printError(game, ERRONEOUS_BOARD_ERROR);
        return 0;
    } /* create a copy of the game so changes won't affect the game */
    newGame=(Game*)calloc(1, sizeof(Game));
    newGame->blockWidth=game->blockWidth;
    newGame->blockHeight=game->blockHeight;
    newGame->list=NULL;
    newGame->board=copyCellBoard(game);
    number=countSolutions(newGame);
    printf("Number of solutions: %d\n",number);
    if(number == 1){
        printf("This is a good board!\n");
    }
    else if(number > 1){
        printf("The puzzle has more than 1 solution, try to edit it further\n");
    }
    freeGame(newGame);
    free(newGame);
    return 1;
}

int autofill(Game*gamea){
    Game*game=gamea;
    size_t count;
    int i,j,k,first=1;
    int num_val[2]={0};
    int**cellsToFill=NULL;
    count=0;
    if(!checkError(game)){
        printError(game,ERRONEOUS_BOARD_ERROR);
        return 0;
    }
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(!game->board[i][j].value){/* if cell is empty */
                countPossibleValues(game,num_val,i,j); /* after execution: num_val[0]=number of possible values, num_val[1]=lowest possible value */
                if(num_val[0]==1) {
                    if(first){
                        /* cellsToFill is used both for filling trivial values and to store the move in the list */
                        cellsToFill=(int**)realloc(NULL, (sizeof(int*))*(++count));
                        first=0;
                    }
                    else{
                        cellsToFill=(int**)realloc(cellsToFill,(sizeof(int*))*(++count));
                    }
                    if(cellsToFill==NULL) {
                        printError(game,MEMORY_ALLOC_ERROR);
                        return 0;
                    }
                    cellsToFill[count-1]=(int*)calloc(4, sizeof(int)); /* 0:x,1:y,2:from,3:to */
                    if(cellsToFill[count-1]==NULL) {
                        printError(game,MEMORY_ALLOC_ERROR);
                        return 0;
                    }
                    cellsToFill[count-1][0]=i;
                    cellsToFill[count-1][1]=j;
                    cellsToFill[count-1][2]=0;
                    cellsToFill[count-1][3]=num_val[1];
                }
            }
        }
    }

    if(cellsToFill!=NULL) {
        for (k = 0; k < (int)count; k++) { /* fill board with values */
            game->board[cellsToFill[k][0]][cellsToFill[k][1]].value = cellsToFill[k][3];
        }
        updateCellValidity(game);
        addLast(game->list, cellsToFill, (int) count);
    }
    return 1;
}

int reset(Game *game) {
    int i;
    int *move;
    if (!game->list->length)
        return 1;
    while (game->list->pointer != NULL) { /* undo all moves */
        for (i = 0; i < game->list->pointer->size; i++) {
            move = game->list->pointer->data[i];
            game->board[move[0]][move[1]].value = move[2];
            checkColumns(game, move[0]);
            checkRows(game, move[1]);
            checkBlock(game, move[0], move[1]);
        }
        game->list->pointer = game->list->pointer->previous;
    }
    deleteTail(game->list, game->list->head); /* clear list */
    deleteAtPosition(game->list, 0);
    printf("Board reset\n");
    return 1;
}

void exitGame(Game*game){
    freeGame(game);
}



























