#include "List.h"
/*check*/

Node  * createNode(int ** data,int size){
    Node * node=calloc(1, sizeof(Node));
    if(node==NULL){
        printError(NULL,MEMORY_ALLOC_ERROR);
        return NULL;
    }
    node->size=size;
    node->data=data;
    node->previous=NULL;
    node->next=NULL;
    return node;
}
/*check*/
List * createList(){
    List * list=calloc(1, sizeof(List));
    if(list==NULL){
        printError(NULL,MEMORY_ALLOC_ERROR);
        return NULL;
    }
    list->head=NULL;
    list->tail=NULL;
    list->pointer=NULL;
    return list;
}
/*check*/
void printList(List * list){
    Node * node;
    for(node=list->head;node!=NULL;node=node->next){
        printData(node->data,node->size);
    }
}
/*check*/
void printData(int **data,int size){
    int r,g;
    for(r=0;r<size;r++) {
        for ( g=0; g < 4; g++) {
            printf("%d ", data[r][g]);
        }
        printf("\n");
    }
}


/*check*/
int deleteAtPosition(List *list,int pos) {
    int j;
    Node *node = list->head;
    for (j = 0; j < pos; j++) {
        node = node->next;
    }
    if (node->next != NULL)
        node->next->previous = node->previous;
    if (node->previous != NULL)
        node->previous->next = node->next;
    if (pos == 0) {
        list->head = node->next;
        if (list->length == 1) {
            list->tail = node->next;
        }
    } else if (pos == list->length - 1) {
        list->tail = node->previous;
    }
    freeNode(node);
    list->length--;
    return 1;
}

/*check*/
int deleteTail(List *list,Node * node){
    while(node->next!=NULL){
        Node * temp=node->next;
        node->next=node->next->next;
        if(node->next!=NULL){
            node->next->previous=node;
        }
        freeNode(temp);
        list->length--;
    }
    return 1;
}
/*check*/
int addLast(List * list,int ** data,int size){
    Node * node;
    if(list->pointer!=list->tail){
        if(list->pointer==NULL) {
            while (list->length > 0)
                deleteAtPosition(list, 0);
        }
        else
            deleteTail(list,list->pointer);
    }
    node=createNode(data,size);
    if(list->length==0)
        list->head=node;
    else{
        node->previous=list->pointer;
        list->pointer->next = node;}
        list->tail = node;
        list->pointer = node;
        list->length++;;
        return 1;

}
/*check*/
void freeNode(Node*n){
    int i;
    for(i=0;i<n->size;i++){
        free(n->data[i]);
    }
    free(n);
}
/*check*/
void freeList(List*list){
    Node * node;
    if(list==NULL)
        return ;
    while(list->head!=NULL){
        node=list->head;
        list->head=list->head->next;
        freeNode(node);
    }
    free(list);
}
