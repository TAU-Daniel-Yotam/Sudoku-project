
#ifndef SUDOKU_SOFTWARE_PROJECT_PARSER_H
#define SUDOKU_SOFTWARE_PROJECT_PARSER_H

typedef struct Command{
    int type,numArgs,saveToList;
    int* intArgs;
    char* strArg;
} Command;

#include "Exceptions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int getInput(char* command, int size);
int parseCommand(Game* game, char*command, Command* parsedCommand);
void initCommand(Command* c,int*a);

#endif
