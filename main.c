

#include "Game.h"
#include "Parser.h"
#include "MainAux.h"
#include "GameAux.h"


#include "Game.h"
#include "Parser.h"
#include "MainAux.h"
#include "GameAux.h"

int main() {
    int exit, type, erroneous, valid,done;
    Game game;
    game.board=NULL;
    game.list=NULL;
    Command parsedCommand;
    parsedCommand.intArgs=NULL;
    char command[1024];
    game.mode = 0;
    exit=0;
    printf("Sudoku\n------\n");
    while (!exit) {
        printf("Enter your command:\n");
        getInput(command, 1024);
        type = parseCommand(&game, command, &parsedCommand);
        if (type == -1) {
            printError(&game, INVALID_COMMAND_ERROR);
            continue;
        }
        switch (type) {
            case 1:
                done=solve(&game, parsedCommand.strArg);
                if(done) {
                    updateCellValidity(&game);
                    printBoard(&game);
                }
                break;
            case 2:
                done=edit(&game, parsedCommand.strArg);
                if(done) {
                    updateCellValidity(&game);
                    printBoard(&game);
                }
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
                    if (checkValidGame(&game)) {
                        printf("Puzzle solved successfully\n");
                        game.mode = 0;
                    } else
                        printf("Puzzle solution erroneous\n");
                }
                break;
            case 6:
                valid = validate(&game);
                if (valid == 1)
                    printf("Validation passed board is solvable\n");
                else
                    printf("Validation failed: board is unsolvable\n");
                break;
            case 7:
                generate(&game, parsedCommand.intArgs[0], parsedCommand.intArgs[1]);
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
                break;
            case 11:
                hint(&game, parsedCommand.intArgs[1], parsedCommand.intArgs[0]);
                break;
            case 12:
                numSolution(&game);
                break;
            case 13:
                autofill(&game);
                break;
            case 14:
                reset(&game);
                printBoard(&game);
                break;
            case 15:
                exitGame(&game);
                exit = 1;
                break;
            default:
                break;
        }

    }
    return 0;


}