/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "elestack.h"
#define MAXSTACK 1064
#define EMPTY_STACK -1

struct _EleStack {
    Node* info;
};

/**------------------------------------------------------------------
Initialize a stack EleStack. Output: Pointer to the initialized EleStack or NULL in case of error
------------------------------------------------------------------*/
EleStack * EleStack_ini(){

    EleStack * elestack=NULL;
    elestack=(EleStack*)malloc(sizeof(EleStack));
    if(!elestack){
        return NULL;
    }
    elestack->info=NULL;
    elestack->info=NULL;
    return elestack;
}
/**------------------------------------------------------------------
Remove an EleStack. Entry: EleStack to destroy.
------------------------------------------------------------------*/
void EleStack_destroy(EleStack * ele){

    node_destroy(ele->info);
    free(ele);


}
/**------------------------------------------------------------------
Modify the data of an EleStack. Entry: The EleStack to be modified and the content to be saved in that
EleStack. Output: OK or ERROR
------------------------------------------------------------------*/
Status EleStack_setInfo(EleStack *ele , void* p){
    Node *aux=NULL;
    if(!ele){
        return ERROR;
    }
    aux=node_copy((Node *)p);
     if(!aux){
        return ERROR;
    }
    ele->info=aux;

    return OK;
}
/**------------------------------------------------------------------
Returns the EleStack content. Entry: The EleStack. Output: The content of EleStack or NULL if there has been
an error.
------------------------------------------------------------------*/
void * EleStack_getInfo(EleStack *ele){

    if(!ele){
        return NULL;
    }

    return (Node *)ele->info;
}
/**------------------------------------------------------------------
Copy one EleStack in another, reserving memory. Input: the EleStack to copy. Output: Returns a pointer to the
copied EleStack or NULL in case of error.
------------------------------------------------------------------*/
EleStack * EleStack_copy(const EleStack *ele){

    EleStack *ele1=NULL;
    if(!ele){
        return NULL;
    }
    ele1=EleStack_ini();
    if(!ele1){
        return NULL;
    }
    ele1->info=node_copy(ele->info);
    if(!ele1->info){
        EleStack_destroy(ele1);
        return NULL;
    }

    return ele1;
}
/**------------------------------------------------------------------
Compares two EleStack. Entry: two EleStack to compare. Output: Returns TRUE if they are the same and if
not FALSE
------------------------------------------------------------------*/
Bool EleStack_equals(const EleStack *ele, const EleStack *ele1){
    int cmp=0;

    if(!ele || !ele1){
        return FALSE;
    }

    cmp = node_cmp(ele->info,ele1->info);
    if(cmp!=0){
        return FALSE;
    }
    return TRUE;

}
/**------------------------------------------------------------------
Print the EleStack in a file that is already open. Input: File in which it is printed and the EleStack to print.
Output: Returns the number of written characters.
------------------------------------------------------------------*/
int EleStack_print(FILE *pf, const EleStack *ele){

    if(!pf || !ele){
        return -1;
    }
    return node_print(pf,ele->info);
}
