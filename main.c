

#include "Game.h"
#include "Parser.h"
#include "MainAux.h"
#include <time.h>

int main() {
    int exit, type, eof, done;
    Game game;
    char *command;
    Command parsedCommand;
    srand(time(NULL));
    game.board=NULL;
    game.list=NULL;
    game.markError=1;
    parsedCommand.intArgs=NULL;
    parsedCommand.strArg=NULL;
    command=NULL;
    game.mode = 0;
    eof=0;
    exit=0;
    printf("Sudoku\n------\n");
    while (!exit) {
        printf("Enter your command:\n");
        if(!eof){
            command = getInput(1024,&eof);
            type = parseCommand(&game, command, &parsedCommand);
            free(command);
        }
        else{ /* EOF is interpreted as an exit command */
            printf("\n");
            command=(char*)calloc(5, sizeof(char));
            if(command==NULL){
                printError(NULL,MEMORY_ALLOC_ERROR);
                return 0;
            }
            command[0]='e';command[1]='x';command[2]='i';command[3]='t';command[4]='\0';
            type = parseCommand(&game, command, &parsedCommand);
        }
        if (type == -1) {
            printError(&game, INVALID_COMMAND_ERROR);
            continue;
        }
        switch (type) { /* which command to execute */
            case 1:
                done=solve(&game, parsedCommand.strArg);
                if(done) {
                    updateCellValidity(&game);
                    printBoard(&game);
                }
                free(parsedCommand.strArg);
                break;
            case 2:
                done=edit(&game, parsedCommand.strArg);
                if(done) {
                    updateCellValidity(&game);
                    printBoard(&game);
                }
                free(parsedCommand.strArg);
                break;
            case 3:
                mark_errors(&game, parsedCommand.intArgs[0]);
                break;
            case 4:
                printBoard(&game);
                break;
            case 5:
                done=set(&game, parsedCommand.intArgs[1]-1, parsedCommand.intArgs[0]-1, parsedCommand.intArgs[2]);
                if (done)
                    printBoard(&game);
                if (checkFullBoard(&game)&&game.mode==1&&done) {
                    if (checkError(&game)) {
                        printf("Puzzle solved successfully\n");
                        game.mode = 0;
                    } else
                        printf("Puzzle solution erroneous\n");
                }
                break;
            case 6:
                validate(&game,1);
                break;
            case 7:
                done=generate(&game, parsedCommand.intArgs[0], parsedCommand.intArgs[1]);
                if(done)
                    printBoard(&game);
                break;
            case 8:
                undo(&game);
                break;
            case 9:
                redo(&game);
                break;
            case 10:
                save(&game, parsedCommand.strArg);
                free(parsedCommand.strArg);
                break;
            case 11:
                hint(&game, parsedCommand.intArgs[1]-1, parsedCommand.intArgs[0]-1);
                break;
            case 12:
                numSolution(&game);
                break;
            case 13:
                done=autofill(&game);
                printBoard(&game);
                if (checkFullBoard(&game) && game.mode==1 && done) {
                    if (checkError(&game)) {
                        printf("Puzzle solved successfully\n");
                        game.mode = 0;
                    } else
                        printf("Puzzle solution erroneous\n");
                }
                break;
            case 14:
                reset(&game);
                printBoard(&game);
                break;
            case 15:
                exitGame(&game);
                exit = 1;
                printf("Exiting...\n");
                break;
            default:
                break;
        }

    }
    return 0;


}