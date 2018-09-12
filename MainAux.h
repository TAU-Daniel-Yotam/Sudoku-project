
#ifndef SUDOKU_SOFTWARE_PROJECT_MAINAUX_H
#define SUDOKU_SOFTWARE_PROJECT_MAINAUX_H

#include<stdio.h>
#include "Game.h"

void printArray(void*a, int size);
int arrComp(int*a1, int size1, int*a2, int size2);
int checkFullBoard(Game*game);
#endif 
