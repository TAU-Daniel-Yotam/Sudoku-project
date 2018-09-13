/**
 * Module Summary:
 * This module defines the 'Cell' and 'Game' structures needed to represents a game
 * and contains implementations of all 15 commands from the instructions pdf
 *
 * Structs:
 * Cell: used as a single board element and contains all relevant data for a single cell
 * Game: contains all the info relevant to manage the a Sudoku game
 *
 * Functions: a function for each command from the instructions pdf (no further description is needed)
 *
 */



#ifndef SUDOKU_SOFTWARE_PROJECT_GAME_H
#define SUDOKU_SOFTWARE_PROJECT_GAME_H

#define SUBDIM1 (game->blockHeight)
#define SUBDIM2 (game->blockWidth)
#define DIM ((SUBDIM1)*(SUBDIM2))
/**
 * @property value - the value of the cell
 * @property isFixed - 1 if the cell is fixed or 0 o.w
 * @property isInValidInRow - 1 if the cell's value appears more than ones in it's row or 0 o.w
 * @property isInValidInColumns - 1 if the cell's value appears more than ones in it's column or 0 o.w
 * @property isInValidInBlock - 1 if the cell's value appears more than ones in it's block or 0 o.w
 * @property isPlayerMove - 1 if cell was given a value by the player or 0 o.w
 */
typedef struct Cell{
    int value;
    int isFixed;
    int isInValidInRow;
    int isInValidInColumns;
    int isInValidInBlock;
    int isPlayerMove;
}Cell;

/**
 * @property blockHeight - the number of rows in a single block
 * @property blockWidth - the number of columns in a single block
 * @property board - a 2d 'Cell' array that represents the board
 * @property mode - represents the game mode: 0=init, 1=solve, 2=edit
 * @property markError - 1 if the user decides to mark errors on the board or 0 o.w
 * @property list - the game's move list to support undo/redo commands
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

/**
 *
 * @param game - a pointer to the current game instance
 * @param filepath - a full or relative file path to load the game from
 * @return 1 if execution was successful or 0 o.w
 */
int     solve(Game * game,char * filepath);

/**
 *
 * @param game - a pointer to the current game instance
 * @param filepath - a full or relative file path to load the game from
 * @return 1 if execution was successful or 0 o.w
 */
int     edit(Game * game, char * filePath);

/**
 *
 * @param game - a pointer to the current game instance
 * @param arg - an argument to the mark_errors command
 * @return 1 if execution was successful or 0 o.w
 */
int     mark_errors(Game* game, int arg);

/**
 *
 * @param game - a pointer to the current game instance
 */
void    printBoard(Game* game);

/**
 *
 * @param game - a pointer to the current game instance
 * @param x,y - indices in the game board
 * @param value - the value to fill in the selected cell
 * @return 1 if execution was successful or 0 o.w
 */
int     set(Game* game,int x,int y,int value);

/**
 *
 * @param game - a pointer to the current game instance
 * @param toPrint - 1 if a print is needed or 0 o.w
 * @return 1 if board is solvable or 0 o.w
 */
int     validate(Game *game,int toPrint);

/**
 *
 * @param game - a pointer to the current game instance
 * @param x - the number of legal values to 'guess'
 * @param y - the number of values to leave on the board after solving it
 * @return 1 if execution was successful or 0 o.w
 */
int     generate(Game*game,int x,int y);

/**
 *
 * @param game - a pointer to the current game instance
 * @return 1 if execution was successful or 0 o.w
 */
int     undo(Game * game);

/**
 *
 * @param game - a pointer to the current game instance
 * @return 1 if execution was successful or 0 o.w
 */
int     redo(Game * game);

/**
 *
 * @param game - a pointer to the current game instance
 * @param path - a full or relative path to save the game file in
 * @return 1 if execution was successful or 0 o.w
 */
int     save(Game *game, char *path);

/**
 *
 * @param game - a pointer to the current game instance
 * @param x,y - indices in the game board
 * @return 1 if execution was successful or 0 o.w
 */
int     hint(Game * game,int x,int y);

/**
 *
 * @param game - a pointer to the current game instance
 * @return the number of solutions found for the game
 */
int     numSolution(Game * game);

/**
 *
 * @param gamea - a pointer to the current game instance
 * @return 1 if execution was successful or 0 o.w
 */
int     autofill(Game*gamea);

/**
 * @pre game is initialized
 * @param game - a pointer to the current game instance
 * @return 1
 */
int     reset(Game * game);

/**
 *
 * @param game - a pointer to the current game instance
 */
void    exitGame(Game*game);




#endif




