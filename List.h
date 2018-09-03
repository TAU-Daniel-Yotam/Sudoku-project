#ifndef SUDOKU_SOFTWARE_PROJECT_LIST_H
#define SUDOKU_SOFTWARE_PROJECT_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include "Exceptions.h"

typedef struct  Node {
    int ** data;
    int size;
    struct Node * next;
    struct Node * previous;
}Node ;


typedef struct List{
    struct Node * head;
    struct Node * tail;
    struct Node * pointer;
    int length;
} List;

Node * createNode(int ** data,int size);
List * createList();
int printList(List * list);
int printData(int ** data,int size);
int deleteAtPosition(List *list,int pos);
int deleteTail(List *list,Node * node);
int addLast(List * list,int ** data,int size);
void freeNode(Node*n);
void freeList(List*list);



#endif

