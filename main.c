

#include "Game.h"
#include "Parser.h"
#include "MainAux.h"
#include "GameAux.h"

int main() {
            int exit, type, erroneous, valid;
            /*int eof;*/
            int inta[3];
            Game game;
            game.board=NULL;
            game.list=NULL;
            Command parsedCommand;
            parsedCommand.intArgs=inta;


            char command[1024];
            game.mode = 0;
            erroneous=0;
            exit=0;
            printf("Sudoku\n------\n");
            while (!exit) {
                /*eof = getInput(command, 1024);*/
                getInput(command, 1024);
                type = parseCommand(&game, command, &parsedCommand);
                if (type == -1) {
                    printError(&game, INVALID_COMMAND_ERROR);
                    continue;
                }
                if (erroneous && type != 8) {
                    printf("Puzzle solution erroneous\n");
                    continue;
                }
                switch (type) {
                    case 1:
                        solve(&game, parsedCommand.strArg);
                        break;
                    case 2:
                        edit(&game,parsedCommand.strArg);
                        break;
                    case 3:
                        mark_errors(&game, parsedCommand.intArgs[0]);
                        break;
                    case 4:
                        printBoard(&game);
                        break;
                    case 5:
                        set(&game, parsedCommand.intArgs[0], parsedCommand.intArgs[1], parsedCommand.intArgs[2]);
                        if (checkWinningGame(&game) && validate(&game)) {
                            printf("Puzzle solved successfully\n");
                            game.mode = 0;
                        } else if (checkWinningGame(&game) && !validate(&game)) {
                            printf("Puzzle solution erroneous\n");
                            erroneous = 1;
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
                        break;
                    case 8:
                        if (erroneous == 1)
                            erroneous = 0;
                        undo(&game);
                        break;
                    case 9:
                        redo(&game);
                        break;
                    case 10:
                        save(&game, parsedCommand.strArg);
                        break;
                    case 11:
                        hint(&game, parsedCommand.intArgs[0], parsedCommand.intArgs[1]);
                        break;
                    case 13:
                        autofill(&game);
                        break;
                    case 14:
                        reset(&game);
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
