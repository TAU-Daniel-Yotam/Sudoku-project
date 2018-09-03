#include "stack.h"


void init(Stack * stack,int size ){
    int i;
    int ** array=(int**)calloc((unsigned int)size, sizeof(int));
    if(array==NULL) {
        printError(NULL, MEMORY_ALLOC_ERROR);
        return;
    }
    for(i=0;i<size;i++){
        array[i]=(int*)calloc(3, sizeof(int));
        if (array[i]==NULL){
            printError(NULL,MEMORY_ALLOC_ERROR);
            return;
        }
    }
    stack->size=0;
    stack->array=array;
}
void push(Stack * stack ,int x,int y){
    int * data =(int*)calloc(2, sizeof(int));
    if(data==NULL) {
        printError(NULL, MEMORY_ALLOC_ERROR);
        return;
    }
    data[0]=x;
    data[1]=y;
    stack->array[stack->size]=data;
    stack->size++;

}
int * pop(Stack * stack){
    stack->size--;
    return stack->array[stack->size];


}
