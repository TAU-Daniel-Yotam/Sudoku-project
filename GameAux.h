#ifndef SUDOKU_SOFTWARE_PROJECT_GAMEAUX_H
#define SUDOKU_SOFTWARE_PROJECT_GAMEAUX_H
#include "Exceptions.h"
/**
 * Model Summary:
 *  This module contains all the auxiliary functions needed to execute the different game commands
 *
 * Functions:
 *  readFromFile -  Reads the information from the given file and updates the game  accordingly - dimensions, values, errors, etc.
 *  initGame - Releases resources of the previous game if such a game exists and updates the game according to the arguments
 *  createBoard - Creates a new empty sudoku game board instance according to given block dimensions
 *  printDashes - an auxiliary function for the "printBoard" function ,print dashes
 *  checkRange - Checks whether a given number is in a specific range according to the game parameters
 *  isInvalid - checks whether the value of a cell already appears in another cell in its row or in its block or column
 *  checkBlock - given coordinates of a cell, it updates the errors of the block in which it is located
 *  freeMemory - frees memory of a two-dimensional array (of any type)
 *  checkColumns - update the errors in specific columns
 *  checkRow - update the errors in specific rows
 *  fillXvalues - Fills x legal values in an empty given board
 *  emptyBoard -  Empties the board of a given game
 *  createListDataGenerate - Creates a 2d array to store in the moves list for future undo/redo commands
 *  updateGameBoard - Fills the board with trivial values after an 'autofill' command
 *  writeToFile - writes the dimensions of the game and its board in a file
 *  copyBoard - Creates a values-only copy of the game's board
 *  copyCellBoard - Creates a full copy of the game's board
 *  countPossibleValues - Counts the number of possible values in a given cell in the board
 *  updateCellValidity - updates the following fields for each cell-isInValidInRow,isInValidInColumns and isInValidInBlock.
 *  freeGame - Frees all game resources
 *  freeBoard - Frees the memory allocated for the game board (used in 'freeGame')
 *  checkInvalid - Checks whether the given value in the given cell will cause errors or not
 *  checkError - checks whether the value of any cell already appears in another cell in its row or in its block or column

**/




/**
 *
 * @param file - a file that contains a saved game that the user wants to read
 * @param game - a pointer to the current Game instance
 * @param mode - the game's mode
 * @return - 1 if the file was readable and the current game was updated,or 0 o.w
 */
int     readFromFile(FILE *file,Game * game,int mode);

/**
 *
 * @param game - a pointer  to the current Game instance
 * @param mode - the games mode
 * @param blockHeight - the game's block height
 * @param blockWidth- the game's block width
 */
void    initGame(Game * game,int mode,int blockHeight,int blockWidth);

/**
 *
 * @param game - a pointer  to the current Game instance
 * @return - 1 if the borad is valid (has no errors) or 0 o.w
 */
int     checkBoard(Game * game);

/**
 *
 * @param blockHeight - the game's block height
 * @param blockWidth- the game's block width
 * @return board - a pointer to a 2d Cell array that represents the board
 */
Cell  **createBoard(int blockHeight,int blockWidth);

/**
 *
 * @param blockWidth -the games block width
 * @param blockHeight- the games block height
 */
void    printDashes(int blockWidth,int blockHeight);

/**
 *
 * @param game - a pointer  to the current Game instance
 * @param a - a value to check if in the correct range
 * @param type - 0 if checking an index or 1 if checking a value
 * @return 1 if a is in range or 0 o.w
 */
int     checkRange(Game* game,int a,int type);

/**
 *
 * @param cell - a pointer to a Cell instance
 * @return 1 if one of the following values is equal to 1 :isInValidInRow,isInValidInColumns and isInValidInBlock.or 0 o.w
 */
int     isInvalid(Cell * cell);
/**
 *
 * @param game - a pointer to a current Game instance
 * @param x - represents a columns
 * @param y - represents a row
 */
void    checkBlock(Game * game,int x,int y);
/**
 *
 * @param array - 2d array
 * @param size - the size of the external array
 */
void    freeMemory(void ** array,int size);
/**
 *
 * @param game- a pointer to a current Game instance
 * @param x - column index
 */
void    checkColumns(Game *game, int x);
/**
 *
 * @param game - a pointer to a current Game instance
 * @param x - row index
 */
void    checkRows(Game *game, int x);

/**
 *
 * @param game - a pointer to a current Game instance
 * @param x - the number of values to fill in the board
 * @return - the number of attempts ot took to fill x values in the board
 */
int     fillXvalues(Game*game,int x);

/**
 *
 * @param game - a pointer to a current Game instance
 * @return 1 if the game board is empty or 0 o.w
 */
int     checkEmpty(Game*game);

/**
 *
 * @param game - a pointer to a current Game instance
 * @param listData - a 2d array to store in the moves list (formatted correctly)
 */
void    createListDataGenerate(Game*game,int**listData);

/**
 *
 * @param game - a pointer to a current Game instance
 * @param board - a 2d array that contains values to fill in the game board
 */
void    updateGameBoard(Game*game,int**board);

/**
 *
 * @param game - a pointer to a current Game instance
 */
void    emptyBoard(Game*game);
/**
 *
 * @param game - a pointer to the current Game instance
 * @param file - The file in which the game will be saved.
 * @return 1 if the file was written successfully ,or 0 o.w
 */
int     writeToFile(Game *game, FILE *file);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return a 2d array that contains a copy of the game's board (values only)
 */
int   **copyBoard(Game*game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return a full copy of the game's board
 */
Cell  **copyCellBoard(Game * game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param num_val - num_val[0]: the number of possible values in the given cell,
 *                  num_val[1]: the lowest legal value in the cell
 * @param x,y - indices of a cel in the board
 * @return num_val[0]
 */
int     countPossibleValues(Game*game,int*num_val,int x, int y);

/**
 *
 * @param game -a pointer to a current Game instance
 * @post - game->board[x][y].inInvalid holds the correct value for every x,y
 */
void    updateCellValidity(Game*game);

/**
 *
 * @param game - a pointer to a current Game instance to be freed
 */
void    freeGame(Game*game);

/**
 *
 * @param game - a pointer to a current Game instance which board is to be freed
 */
void    freeBoard(Game*game);
/**
 *
 * @param game -a pointer to the current Game instance
 * @param x -the column of the cell to be check
 * @param y the row of the cell to be check
 * @param value -the value  that will be check
 * @return 0 if the value is legal in column x and in row y, or 1 o.w
 * */
int     checkInvalid(Game* game, int x, int y, int value);
/**
 *
 * @param game -a pointer to a current Game instance
 * @return 1 if the board is valid,or 0 o.w
 * */
int checkError(Game *game);
#endif
