#ifndef SUDOKU_SOFTWARE_PROJECT_GAMEAUX_H
#define SUDOKU_SOFTWARE_PROJECT_GAMEAUX_H
#include "Exceptions.h"
/**
*int     readFromFile(FILE *file,Game * game,int mode)-  Reads the information from the given file and updates the game  accordingly - dimensions, values, errors, etc.
void    initGame(Game * game,int mode,int blockHeight,int blockWidth)- Releases resources of the previous game if such a game exists and updates the game according to the arguments
Cell  **createBoard(int blockHeight,int blockWidth);
void    printDashes(int blockWidth,int blockHeight)-an auxiliary function for the "printBoard" function ,print dashes
int     checkRange(Game* game,int a,int type);
int     isInvalid(Cell * cell)-checks whether the value of a cell already appears in another cell in its row or in its block or column
void    checkBlock(Game * game,int x,int y)-given coordinates of a cell, it updates the errors of the block in which it is located
void    freeMemory(void ** array,int size)-frees memory of a two-dimensional array
void   checkColumns(Game * game,int x)-update the errors in specific columns
void    checkRow(Game * game,int x)-update the errors in specific rows
int     fillXvalues(Game*game,int x);
void    emptyBoard(Game*game);
void    createValuesArray(Game*game,int x,int y,int* values);
void    createListDataGenerate(Game*game,int**listData);
void    updateGameBoard(Game*game,int**board);
int     writeToFile(Game *game, FILE *file)-writes the dimensions of the game and its board in a file
int   **copyBoard(Game*game);
Cell  **copyCellBoard(Game * game);
int     countPossibleValues(Game*game,int*num_val,int x, int y);
void    fillValues(Game*game,int**values,int size);
void    updateCellValidity(Game*game)-updates the following fields for each cell-isInValidInRow,isInValidInColumns and isInValidInBlock.
void    freeGame(Game*game);
void    freeBoard(Game*game);
int     checkInvalid(Game* game, int x, int y, int value)-Checks whether the given value in the given cell will cause errors or not
int     checkError(Game *game)-checks whether the value of any cell already appears in another cell in its row or in its block or column

**/




/**
 *
 * @param file-a file that contains a saved game that the user wants to read
 * @param game-a pointer to the current Game instance
 * @param mode -the game's mode
 * @return- 1 if the file was readable and the current game was updated,or 0 o.w
 */
int     readFromFile(FILE *file,Game * game,int mode);
/**
 *
 * @param game - a pointer  to the current Game instance
 * @param mode -the games mode
 * @param blockHeight - the games block height
 * @param blockWidth- the games block width
 */
void    initGame(Game * game,int mode,int blockHeight,int blockWidth);
int     checkBoard(Game * game);
Cell  **createBoard(int blockHeight,int blockWidth);
/**
 *
 * @param blockWidth -the games block width
 * @param blockHeight- the games block height
 */
void    printDashes(int blockWidth,int blockHeight);
int     checkRange(Game* game,int a,int type);
/**
 *
 * @param cell - a pointer to a Cell instance
 * @return 1 if one of the following values is equal to 1 :isInValidInRow,isInValidInColumns and isInValidInBlock.or 0 o.w
 */
int isInvalid(Cell * cell);
/**
 *
 * @param game - a pointer to a current Game instance
 * @param x - represents a columns
 * @param y - represents a row
 */
void    checkBlock(Game * game,int x,int y);
/**
 *
 * @param array -two-dimensional array
 * @param size- the size of the external array
 */
void    freeMemory(void ** array,int size);
/**
 *
 * @param game- a pointer to a current Game instance
 * @param x -represents a columns
 */
void    checkColumns(Game *game, int x);
/**
 *
 * @param game -a pointer to a current Game instance
 * @param x -represents a rows
 */
void    checkRows(Game *game, int x);
int     fillXvalues(Game*game,int x);
int     checkEmpty(Game*game);
void    createValuesArray(Game*game,int x,int y,int* values);
void    createListDataGenerate(Game*game,int**listData);
void    updateGameBoard(Game*game,int**board);
void    emptyBoard(Game*game);
/**
 *
 * @param game -a pointer to the current Game instance
 * @param file - The file in which the game will be saved.
 * @return-1 if the file was written  ,or 0 o.w
 */
int     writeToFile(Game *game, FILE *file);
int   **copyBoard(Game*game);
Cell  **copyCellBoard(Game * game);
int     countPossibleValues(Game*game,int*num_val,int x, int y);
void    fillValues(Game*game,int**values,int size);
/**
 *
 * @param game -a pointer to a current Game instance
 */
void    updateCellValidity(Game*game);
void    freeGame(Game*game);
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
