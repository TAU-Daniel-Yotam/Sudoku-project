

#ifndef SUDOKU_SOFTWARE_PROJECT_SOLVER_H
#define SUDOKU_SOFTWARE_PROJECT_SOLVER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Exceptions.h"
#include "stack.h"
#include "Game.h"

/*#define SUBDIM1  (game->rows)
#define SUBDIM2  (game->columns)
#define DIM    (SUBDIM1*SUBDIM2)*/

/**
 *
 * @param game - a pointer to the current game object that contains all game info
 * @param board - a 2d array that contains a copy (values only) of the current game board
 * @return 1 if solved, -1 if not feasible, 0 if an error occured
 */
int ILPSolve(Game*game,int**board);

/**
 *
 * @param game - a pointer to the current game object that contains all game info
 * @return count - the number of solutions found for the given game
 */
int countSolutions(Game* game);

#endif
