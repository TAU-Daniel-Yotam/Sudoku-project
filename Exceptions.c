
#include "Exceptions.h"

void printError(struct Game*game,Exception e){
    switch(e){
        case MEMORY_ALLOC_ERROR:
            printf("Error: memory could not be allocated\nExiting...");
            abort();
        case INVALID_COMMAND_ERROR:
            printf("ERROR: invalid command\n");
            break;
        case SOLVE_IO_ERROR:
            printf("Error: File doesn't exist or cannot be opened\n");
            break;
        case EDIT_IO_ERROR:
            printf("Error: File cannot be opened\n");
            break;
        case BINARY_RANGE_ERROR:
            printf("Error: the value should be 0 or 1\n");
            break;
        case VALUE_RANGE_ERROR:
            printf("Error: value not in range 0-%d\n",DIM);
            break;
        case CELL_FIXED_ERROR:
            printf("Error: cell is fixed\n");
            break;
        case ERRONEOUS_BOARD_ERROR:
            printf("Error: board contains erroneous values\n");
            break;
        case BOARD_NOT_EMPTY_ERROR:
            printf("Error: board is not empty\n");
            break;
        case GENERATOR_FAILED_ERROR:
            printf("Error: puzzle generator failed\n");
            break;
        case UNDO_ERROR:
            printf("Error: no moves to undo\n");
            break;
        case REDO_ERROR:
            printf("Error: no moves to redo\n");
            break;
        case VALIDATION_FAILED_ERROR:
            printf("Error: board validation failed\n");
            break;
        case SAVE_IO_ERROR:
            printf("Error: File cannot be created or modified\n");
            break;
        case CELL_HAS_VALUE_ERROR:
            printf("Error: cell already contains a value\n");
            break;
        case BOARD_UNSOLVABLE_ERROR:
            printf("Error: board is unsolvable\n");
            break;
        case ILP_ERROR:
            printf("Error: Gurobi error");
            break;
    }
}
