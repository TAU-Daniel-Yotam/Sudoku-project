#include "stack.h"


void init(Stack * stack,int size ){
    int i;
    int ** array=calloc(size, sizeof(int));
    if(array==NULL)
        printError(NULL,MEMORY_ALLOC_ERROR);
    for(i=0;i<size;i++){
        array[i]=calloc(3, sizeof(int));
        if (array[i]==NULL){
            printError(NULL,MEMORY_ALLOC_ERROR);
        }
    }
    stack->size=0;
    stack->array=array;
}
void push(Stack * stack ,int x,int y){
    int * data =calloc(2, sizeof(int));
    if(data==NULL)
        printError(NULL,MEMORY_ALLOC_ERROR);
    data[0]=x;
    data[1]=y;
    stack->array[stack->size]=data;
    stack->size++;

}
int * pop(Stack * stack){
    stack->size--;
    return stack->array[stack->size];


}
