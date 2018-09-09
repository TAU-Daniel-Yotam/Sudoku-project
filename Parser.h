/**
 * Parser Summary:
 * This module contains all the structures and function related to receiving and interpreting the input from the user
 *
 * Structs:
 *
 * Command: type:    -1 if invalid, or 1-15 according to the instructions
 *          numArgs: The number of expected arguments for the command
 *          intArgs: An array of size 3 that contains integer arguments for the command.
 *                   if a command of certain type expects less than 3 int arguments or
 *                   no int arguments, the value of unneeded cells will be -1
 *          strArgs: A pointer to a string argument for the command (like "save xxx") or NULL if
 *                   no string argument expected (like "set")
 *
 * Functions:
 *
 * getInput                - receives input from the user.
 * parseCommand            - Interprets the command that the user wants to invoke.
 * initCommand             - Resets the data of the last command, freeing previous arguments
 * isInt (private)         - Checks if the received string represents an int
 * parseInt (private)      - Converts a string to a number in base 10
 * parseArg (private)      - Parses the raw input received after the command type (the argument)
 * validateArgs (private)  - Confirms that the input command contains the minimum number
 *                           of arguments expected (while ignoring extra arguments)
*/



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

/**
 *
 * @param size - initial size of expected input to allocate in the memory
 * @param eof - the function sets *eof to 1 if the input contains eof or 0 o.w
 * @return str - the raw user input
 */
char* getInput(int size,int*eof);

/**
 *
 * @param game - a pointer to the current game object that contains all game info
 * @param command  - the raw user input
 * @param parsedCommand - an object of type "Command" the contains the relevant data prased from the raw input
 * @return type - the type of the command parsed from the input (-1 if invalid or 1-15 o.w according to the pdf file)
 */
int parseCommand(Game* game, char*command, Command* parsedCommand);

/**
 *
 * @param c - the command to be initialized
 * @post c->type=-1, c->numArgs=-1, c->strArg=NULL, c->intArgs[i]=-1
 */
void initCommand(Command* c);

#endif
