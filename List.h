#ifndef SUDOKU_SOFTWARE_PROJECT_LIST_H
#define SUDOKU_SOFTWARE_PROJECT_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include "Exceptions.h"


/**List.h goal:
 * This module contains all functions and structs that are related to the ability to undo or redo game moves
 *
 * Structs:
 * struct Node                                    -each Node represents a single move in the game and contains the changes made during that move:
 *                                                 the coordinates, the initial values, and the new values .
 *
 * struct List-                                   - the List contains  all the moves - which can be undo or redo in the game,
 *                                                  in order of execution
 *
 * Function :
 * Node * createNode(int ** data,int size)         - creates a new Node instance and initializes its fields
 * List * createList()                              -creates a new List instance and initializes its fields
 * int deleteAtPosition(List *list,int pos)         -given a position in the list, the function deletes the node in that position
 * int deleteTail(List *list,Node * node)           -the function receives a node and deletes all the nodes in the list that follow it
 * int addLast(List * list,int ** data,int size)    -adds a node to the end of the list
 * void freeNode(Node*n);                           -an auxiliary function for the "freeList" functions ,frees memory of single node
 * void freeList(List*list);                        -release all the memory allocated to the List instance
 * */


/**@property data        - all changes made in one single move in the game.
 *                         data[i][0]-x,data[i][1]-y,data[i][2]-the value before the move ,data[i][3]-the value after the move
 *                         i>=0 and i<size
 *
 *
* @property size - number of actions in a one single move
* @property next- a pointer to the next move in the game if such a move exists,or NULL o.w
 *@property previous-a pointer to the previous move in the game if such a move exists,or NULL o.w
*/
typedef struct  Node {
    int ** data;
    int size;
    struct Node * next;
    struct Node * previous;
}Node ;



/**@property head -a pointer to the first move in the game if such exists, or NULL o.w
 * @property tail -a pointer to the last move in the game if such exists, or NULL o.w
 * @property pointer- a pointer to the first move can be undo if such exists,or NULL o.w
 */
typedef struct List{
    struct Node * head;
    struct Node * tail;
    struct Node * pointer;
    int length;
} List;
/**
 *
 * @param data -actions performed in the the last move in the game , represented by a two-dimensional array
 * @param size- the number of actions
 * @return-a pointer to a Node instance that contains the given information
 */
Node * createNode(int ** data,int size);
/**
 *
 * @return a pointer to a  new List instance
 */
List * createList();

/**
 *
 * @param list -a pointer to a List instance
 * @param pos -position of a node in a the list
 * @return 1
 */
int deleteAtPosition(List *list,int pos);
/**
 *
 * @param list -a pointer to a List instance
 * @param node -a pointer to a Node that appears in the list before all the nodes which will be deleted
 * @return
 */
int deleteTail(List *list,Node * node);
/**
 *
 * @param list -a pointer to a List instance
 * @param data - actions performed in the the last move  in the  game , represented by a two-dimensional array
 * @param size -number of actions taken
 * @return
 */
int addLast(List * list,int ** data,int size);
/**
 *
 * @param n -a pointer to a Node instance
 */
void freeNode(Node*n);
/**
 *
 * @param list-a pointer to a List instance
 */
void freeList(List*list);



#endif

