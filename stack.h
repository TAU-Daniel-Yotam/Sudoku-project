#ifndef STACK
#define STACK
/**
* stack.h summary:
*                 This module contains a Stack struct and functions that are related to the backtrack algorithm to solve Sudoku puzzles
* Structs:
* struct Stack                                 - contains objects -(x,y)- when x represents a column and y represents a row
* Functions:
* void init(Stack * stack ,int size)            -receives a pointer to Stack instance and initializes its values
* void push(Stack * stack ,int x,int y)         -Pushes an item-(x,y)- onto the top of this Stack.
* int * pop(Stack * stack)                      -Removes the object-(x,y)- at the top of this Stack and returns
 *                                              that object as the value of this function.
*/

/**@property array- contains objects of the shape(x,y) - representing coordinates
 * @property size- current array size - The number of objects that the array contains
 * @property
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
 * @param size -the size requested for the stack maximal size
 */
void init(Stack * stack ,int size);
/**
 * @pre-the stack is not full
 * @param stack -a pointer to a Stack instance
 * @param x - x represent a column
 * @param y- y represent a row
 **/

void push(Stack * stack ,int x,int y);
/**
 * @pre-the stack is not empty
 * @param stack -a pointer to a Stack instance
 * @return -an object-(x,y)
 */
int * pop(Stack * stack);


#endif