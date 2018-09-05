#include "stack.h"


void init(Stack * stack,int size ){
    int i;
    int ** array=(int **)calloc(size+1, sizeof(int * ));
    if(array==NULL) {
        printError(NULL, MEMORY_ALLOC_ERROR);
        return;
    }
    for(i=0;i<size+1;i++){
        array[i]=calloc(3, sizeof(int));
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
