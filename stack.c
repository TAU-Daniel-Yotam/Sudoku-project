#include "stack.h"

/* stack data format: array[i] = {x,y} where x,y are indices in the board*/
void init(Stack * stack,int size ){
    int i;
    int ** array=(int **)calloc((unsigned int)size+1, sizeof(int * ));
    if(array==NULL) {
        printError(NULL, MEMORY_ALLOC_ERROR);
        return;
    }
    for(i=0;i<size+1;i++){
        array[i]=(int*)calloc(2, sizeof(int));
        if (array[i]==NULL){
            printError(NULL,MEMORY_ALLOC_ERROR);
            return;
        }
    }
    stack->size=0;
    stack->array=array;
}
void push(Stack * stack ,int x,int y){

    stack->array[stack->size][0]=x;
    stack->array[stack->size][1]=y;

    stack->size++;

}
int * pop(Stack * stack){
    stack->size--;
    return stack->array[stack->size];
}

void freeStack(Stack*stack, int size){
    int i;
    for(i=0;i<=size;i++){
        free(stack->array[i]);
    }
    free(stack->array);
    free(stack);
}