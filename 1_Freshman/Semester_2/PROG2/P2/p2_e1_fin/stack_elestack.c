/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack_elestack.h"
#define MAXSTACK 1064
#define EMPTY_STACK -1
struct _Stack {

    int top;
    EleStack * item[MAXSTACK];

};


Stack * stack_ini()
{
    Stack *stack=NULL;
    stack=(Stack *)malloc(sizeof(Stack));
    if(!stack){
        return NULL;
    }
    stack->top=EMPTY_STACK;
    return stack;
}

void stack_destroy(Stack *stc)
{
while(stc->top>-1)
{
    EleStack_destroy(stc->item[stc->top]);
    stc->top--;
}
    free(stc);
}
/**------------------------------------------------------------------
Insert an EleStack in the stack. Input: an EleStack and the stack where to insert it. Output: NULL if you can
not insert it or the resulting stack if it succeeds
------------------------------------------------------------------*/
Status stack_push(Stack * stack, const EleStack * ele){
EleStack *eleaux = NULL;

if (stack==NULL || ele==NULL || stack_isFull(stack))
return ERROR;

eleaux=EleStack_copy(ele);
if (eleaux == NULL) return ERROR;

stack->top++;

stack->item[stack->top] = eleaux;

return OK;
}
/**------------------------------------------------------------------
Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *stc)
{

    EleStack *eleaux=NULL;
    if(!stc)
      {
        return ERROR;
      }

    if (stack_isEmpty(stc)==TRUE)
    {
        return NULL;
    }
    eleaux = stc->item[stc->top];
    if(!eleaux){return NULL;}
    stc->item[stc->top]=NULL;
    stc->top--;
    return eleaux;

}
/**------------------------------------------------------------------
Check if the stack is empty. Input: stack. Output: TRUE if it is empty or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *stc)
{
    if(stc==NULL||stc->top==EMPTY_STACK){return TRUE; }else return FALSE;
}
/**------------------------------------------------------------------
Check if the stack is full. Input: stack. Exit: TRUE if it is full or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *stc)
{
    if(stc->top==MAXSTACK){return TRUE; }else return FALSE;
}
/**------------------------------------------------------------------
Print the entire stack, placing the EleStack on top at the beginning of printing (and one EleStack per line).
Input: stack and file where to print it. Output: Returns the number of written characters.
------------------------------------------------------------------*/
int stack_print(FILE*pf, const Stack*stc)
{
    int i;
    int var=0;
      if(!pf||!stc){return ERROR;}
      for(i=stc->top;i>-1;i--)
      {
           var+=EleStack_print(pf,stc->item[i]);
           if(!var){return ERROR;}
           var+=fprintf(pf,"\n");
      }

    return var;
}
