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
int printData(int ** data,int size);
int deleteAtPosition(List *list,int pos);
/*int insertAtHead(List * list,int ** data);
int deleteAfterSet(List *list,Node * node);
int delete2(List  *list,Node * node);
int printList(List * list);
int movePointer(List * list,int move);*/
int deleteTail(List *list,Node * node);
int addLast(List * list,int ** data,int size);
void freeList(List*list);
void freeNode(Node*n);


#endif

