/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elestack.h"
#define MAXSTACK 1064
#define EMPTY_STACK -1

struct _EleStack {
    int* e;
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
    elestack->e=NULL;
    elestack->e=(int*)malloc(sizeof(int));
    if(elestack->e==NULL){return NULL;}
    return elestack;
}
/**------------------------------------------------------------------
Remove an EleStack. Entry: EleStack to destroy.
------------------------------------------------------------------*/
void EleStack_destroy(EleStack * ele){


    free(ele->e);
    free(ele);


}
/**------------------------------------------------------------------
Modify the data of an EleStack. Entry: The EleStack to be modified and the content to be saved in that
EleStack. Output: OK or ERROR
------------------------------------------------------------------*/
Status EleStack_setInfo(EleStack *ele , void* p){
    if(!ele||!p){
        return ERROR;
    }
    *(ele->e)=*((int *)p);

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

    return ele->e;
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
    *(ele1->e)=*(ele->e);

    if(!ele1->e){
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

    if(!ele || !ele1){
        return FALSE;
    }

   if(*(ele->e)==*(ele1->e)){
    return 0;
  }
   else if(*(ele->e)<*(ele1->e)){
    return -2;
  }
  else{
    return 1;
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

  return fprintf(pf,"%d",*ele->e);
}
