
/**
 * Module Summary:
 * This module contains general auxiliary functions (mostly for debugging)
 *
 * Functions:
 * printArray     - prints the values of a given array
 * arrComp        - compares the values of two given arrays
 * checkFullBoard - check if all cells in th game's board contain a value
 */

#ifndef SUDOKU_SOFTWARE_PROJECT_MAINAUX_H
#define SUDOKU_SOFTWARE_PROJECT_MAINAUX_H

#include <stdio.h>
#include "Game.h"

/**
 *
 * @param a - an int array
 * @param size - the array's size
 */
void printArray(void*a, int size);

/**
 *
 * @param a1,a2 - two arrays to be compared
 * @param size1,size 2 - the corresponding sizes of the given arrays
 * @return 1 if the arrays' values are equal or 0 o.w
 */
int arrComp(int*a1, int size1, int*a2, int size2);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return 1 if the board is full or 0 o.w
 */
int checkFullBoard(Game*game);
#endif 
