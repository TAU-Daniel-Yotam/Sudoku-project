/**
 * Exceptions Summary: This module handles the printing of all runtime errors that may occur.
 *
 * enum Exception: An enum that lists all possible runtime errors specified in the instructions pdf and more
 *
 * Functions:
 *      printError - prints the relevant error according to the received arguments
 *
 * */

#ifndef SUDOKU_SOFTWARE_PROJECT_EXCEPTIONS_H
#define SUDOKU_SOFTWARE_PROJECT_EXCEPTIONS_H
#include "Game.h"



typedef enum Exception{
    MEMORY_ALLOC_ERROR,
    INVALID_COMMAND_ERROR,
    CELL_FIXED_ERROR,
    SOLVE_IO_ERROR,
    EDIT_IO_ERROR,
    BINARY_RANGE_ERROR,
    VALUE_RANGE_ERROR,
    ERRONEOUS_BOARD_ERROR,
    BOARD_NOT_EMPTY_ERROR,
    GENERATOR_FAILED_ERROR,
    UNDO_ERROR,
    REDO_ERROR,
    VALIDATION_FAILED_ERROR,
    SAVE_IO_ERROR,
    CELL_HAS_VALUE_ERROR,
    BOARD_UNSOLVABLE_ERROR,
    ILP_ERROR
}Exception;

/**
 *
 * @param game - A pointer to the current Game instance that contains all game info
 * @param e - An enum instance that decides which error to print
 */
void printError(Game*game,Exception e);

#endif
