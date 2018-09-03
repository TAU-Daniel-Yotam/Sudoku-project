#ifndef STACK
#define STACK

typedef struct Stack{
    int ** array;
    int size;
}Stack;

#include "stdlib.h"
#include "Exceptions.h"

void init(Stack * stack ,int size);
void push(Stack * stack ,int x,int y);
int * pop(Stack * stack);
int * top(Stack * stack);

#endif