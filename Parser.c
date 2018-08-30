
#include "Parser.h"
int isInt(char c);
int parseInt(char* str, int size);
int parseArg(Command* command, char* arg, int argIndex);
int validateArgs(Command* c);


int getInput(char* command, int size){
    if(fgets(command,size,stdin)==NULL){
        return 1;
    }
    return 0;
}

int parseCommand(Game* game, char*command, Command* parsedCommand){
    char* word;
    int i;
    initCommand(parsedCommand,NULL);
    i=0;
    if(strlen(command)>256){
        parsedCommand->type=-1;
        return -1;
    }
    word=strtok(command," \t\r\n");
    while(word!=NULL){
        if(i==0){
            if(!strcmp(word,"solve")){
                parsedCommand->type=1;
                parsedCommand->numArgs=1;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
            }
            else if(!strcmp(word,"edit")){
                parsedCommand->type=2;
                parsedCommand->numArgs=1;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
            }
            else if(!strcmp(word,"mark_errors") && game->mode==1){
                parsedCommand->type=3;
                parsedCommand->numArgs=1;
                parsedCommand->strArg=NULL;
                parsedCommand->saveToList=0;
            }
            else if(!strcmp(word,"print_board") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=4;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"set") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=5;
                parsedCommand->numArgs=3;
                parsedCommand->strArg=NULL;
                parsedCommand->saveToList=1;
            }
            else if(!strcmp(word,"validate") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=6;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"generate") && game->mode==2){
                parsedCommand->type=7;
                parsedCommand->numArgs=2;
                parsedCommand->saveToList=1;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"undo") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=8;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"redo") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=9;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"save") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=10;
                parsedCommand->numArgs=1;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
            }
            else if(!strcmp(word,"hint") && game->mode==1){
                parsedCommand->type=11;
                parsedCommand->numArgs=2;
                parsedCommand->strArg=NULL;
                parsedCommand->saveToList=0;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"num_solutions") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=12;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"autofill") && game->mode==1){
                parsedCommand->type=13;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=1;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"reset") && (game->mode==1 || game->mode==2)){
                parsedCommand->type=14;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else if(!strcmp(word,"exit")){
                parsedCommand->type=15;
                parsedCommand->numArgs=0;
                parsedCommand->saveToList=0;
                parsedCommand->intArgs=NULL;
                parsedCommand->strArg=NULL;
            }
            else{
                parsedCommand->type=-1;
                break;
            }
        }
        else if(i<=parsedCommand->numArgs){
            parseArg(parsedCommand,word,i);
        }
        i++;
        word=strtok(NULL," \t\r\n");

    }
    if(i==0 && word==NULL){
        parsedCommand->type=-1;
    }
    if(!validateArgs(parsedCommand)){
        parsedCommand->type=-1;
    }
    return parsedCommand->type;
}

int parseArg(Command* command, char* arg, int argIndex){
    unsigned int i;
    switch(command->type){
        case 3:
        case 5:
        case 7:
        case 11:
            for(i=0;i<strlen(arg);i++){
                if(!isInt(arg[i])){
                    command->type=-1;
                    break;
                }
            }
            command->intArgs[argIndex-1]=parseInt(arg,(int)strlen(arg));
            break;
        case 1:
        case 2:
        case 10:
            command->strArg=arg;
        default:
            break;
    }
    return 1;
}

int isInt(char c){
    if(c>=48 && c<=57)
        return 1;
    return 0;
}

int parseInt(char* str, int size){
    int result=0;
    int pow=1;
    int i;
    for(i=size-1; i>=0; i--){
        if(!isInt(str[i]))
            return -1;
        result += pow*(str[i]-48);
        pow*=10;
    }
    return result;
}

int validateArgs(Command* c){
    switch(c->type){
        case 1: case 10:
            if(c->strArg==NULL || c->intArgs!=NULL) return 0;
            break;
        case 2:
            if(c->intArgs!=NULL) return 0;
            break;
        case 3: case 5: case 7: case 11:
            if(c->intArgs==NULL || c->strArg!=NULL || c->intArgs[c->numArgs-1]==-1) return 0;
            break;
        case 4: case 6: case 8: case 9: case 12: case 13: case 14: case 15:
            if(c->strArg!=NULL || c->intArgs!=NULL) return 0;
        default:
            break;
    }
    return 1;
}

void initCommand(Command* c,int*a){
    int i;
    c->strArg=NULL;
    if(c->intArgs!=NULL){
        for(i=0;i<3;i++)
            c->intArgs[i]=-1;
    }
    else{
        c->intArgs=a;
        for(i=0;i<3;i++)
            c->intArgs[i]=-1;
    }
    c->type=-1;
    c->numArgs=-1;
    c->saveToList=-1;
}