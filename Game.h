
#ifndef SUDOKU_SOFTWARE_PROJECT_GAME_H
#define SUDOKU_SOFTWARE_PROJECT_GAME_H

#define SUBDIM1 (game->blockHeight)
#define SUBDIM2 (game->blockWidth)
#define DIM ((SUBDIM1)*(SUBDIM2))

typedef struct Cell{
    int value;
    int isFixed;
    int isInValidInRow;
    int isInValidInColumns;
    int isInValidInBlock;
    int isPlayerMove;
}Cell;

/*
 * mode: 0=init, 1=solve, 2=edit
 */
typedef struct Game{
    int blockHeight,blockWidth; /*num of rows and columns in a single block*/
    struct Cell ** board;
    int mode;
    int markError;
    struct List * list;
}Game;

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include "Solver.h"
#include "GameAux.h"

int     solve(Game * game,char * filepath);
int     edit(Game * game, char * filePath);
int     mark_errors(Game* game, int arg);
void    printBoard(Game* game);
int     set(Game* game,int x,int y,int value);
int     validate(Game *game);
int     generate(Game*game,int x,int y);
int     undo(Game * game);
int     redo(Game * game);
int     save(Game *game, char *path);
int     hint(Game * game,int x,int y);
int     numSolution(Game * game);
int     autofill(Game*game);
int     reset(Game * game);
void    exitGame(Game*game);




#endif




