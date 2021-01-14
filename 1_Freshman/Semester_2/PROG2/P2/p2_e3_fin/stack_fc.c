#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "types.h"

struct _Stack {
 int top;
 void * item[MAXSTACK];

 P_stack_ele_destroy pf_destroy;
 P_stack_ele_copy pf_copy;
 P_stack_ele_print pf_print;
};

Stack *stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp) {
 Stack *s;
 int i;

 s = (Stack*) malloc(sizeof(Stack));
 if (!s) {
 return NULL;
 }
 /*Initialize top and assign function pointers*/
 s->top = -1;
 s->pf_copy = fc;
 s->pf_destroy = fd;
 s->pf_print = fp;

 /*assign the pointers of the elements*/
 for (i=0; i< MAXSTACK; i++)
 s->item[i] = NULL;

 return s;
}

void stack_destroy(Stack* stc) {
 if (!stc) return;

 while (stc->top != EMPTY_STACK) {
 stc->pf_destroy( stc->item[stc->top]); /*Call to the function whose pointer was stored as a stack field
 that is, using the pointer to the function*/
 stc->top --;
 }
 free(stc);
}

Status stack_push(Stack * stack, const void * ele){
void *eleaux = NULL;

if (stack==NULL || ele==NULL || stack_isFull(stack))
return ERROR;

eleaux=stack->pf_copy(ele);
if (eleaux == NULL) return ERROR;

stack->top++;

stack->item[stack->top] = eleaux;

return OK;
}
/**------------------------------------------------------------------
Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified
------------------------------------------------------------------*/
void * stack_pop(Stack *stc)
{

    void *eleaux=NULL;
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
    if(stc==NULL || stc->top==MAXSTACK){return TRUE; }else return FALSE;
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
           var+=stc->pf_print(pf,stc->item[i]);
           if(!var){return ERROR;}
           var+=fprintf(pf,"\n");
      }

    return var;
}
