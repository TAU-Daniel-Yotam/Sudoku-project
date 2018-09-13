#ifndef STACK
#define STACK
/**
 * stack.h summary:
 * This module defines a Stack and functions that are related to the backtrack algorithm to solve Sudoku puzzles
 *
 * Structs:
 * Stack - an array based stack
 *
 * Functions:
 * init      - receives a pointer to Stack instance and initializes its fields and values
 * push      - Pushes an item (x,y) into the top of the Stack.
 * pop       - Removes the object (x,y) at the top of this Stack and returns it
 * freeStack - frees all resources allocated for the stack
*/

/**@property array - contains the data of the stack - a 2d array, array[i] = {x,y} where x,y are indices in the board
 * @property size - current stack size - The number of objects pushed to the stack
 */
typedef struct Stack{
    int ** array;
    int size;
}Stack;

#include <stdlib.h>
#include "Exceptions.h"
/**
 *
 * @param stack - a pointer to a Stack instance
 * @param size - the maximal stack size
 */
void init(Stack * stack ,int size);
/**
 * @pre - the stack is not full
 * @param stack - a pointer to a Stack instance
 * @param x,y - indices in the game board
 **/

void push(Stack * stack ,int x,int y);
/**
 * @pre - the stack is not empty
 * @param stack - a pointer to a Stack instance
 * @return an array {x,y} where x,y are indices in the board
 */
int * pop(Stack * stack);

/**
 *
 * @param stack - a pointer to the stack to be freed
 * @param size - the size of the array allocated in the stack
 */
void freeStack(Stack*stack, int size);

#endif