
#ifndef SUDOKU_SOFTWARE_PROJECT_PARSER_H
#define SUDOKU_SOFTWARE_PROJECT_PARSER_H

typedef struct Command{
    int type,numArgs;
    int* intArgs;
    char* strArg;
} Command;

#include "Exceptions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char* getInput(int size,int*eof);
int parseCommand(Game* game, char*command, Command* parsedCommand);
void initCommand(Command* c);

#endif
