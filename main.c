

#include "Game.h"
#include "Parser.h"
#include "MainAux.h"
#include "GameAux.h"

int main(){
    Game game;
    game.board=NULL;
    game.list=NULL;
    edit(&game,NULL);
    game.board[0][0].isInValidInBlock=1;
    game.mode=1;
    game.board[1][0].value=3;
    game.board[1][0].isFixed=1;
    game.board[8][0].value=3;
    game.board[2][2].value=3;
    game.board[7][3].value=3;

    save(&game,"C:\\Users\\danielpeer\\CLionProjects\\Sudoku-project\\r");
    updateCellValidity(&game);
    printerror(&game);
}