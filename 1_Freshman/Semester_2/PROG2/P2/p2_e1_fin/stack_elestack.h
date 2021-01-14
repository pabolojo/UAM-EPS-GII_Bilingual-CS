/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stack_elstack.h
 *
 * Created on 19 de febrero de 2019, 12:39
 */

#ifndef STACK_ELSTACK_H
#define STACK_ELSTACK_H
#include "elestack.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Stack Stack;
/**------------------------------------------------------------------
Initialize the stack reserving memory. Output: NULL if there was an error or the stack if it went well
----------------------------------------------------*/
Stack * stack_ini();
/**------------------------------------------------------------------
Remove the stack Input: the stack to be removed
------------------------------------------------------------------*/
void stack_destroy(Stack *);
/**------------------------------------------------------------------
Insert an EleStack in the stack. Input: an EleStack and the stack where to insert it. Output: NULL if you can
not insert it or the resulting stack if it succeeds
------------------------------------------------------------------*/
Status  stack_push(Stack *, const EleStack *);
/**------------------------------------------------------------------
Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *);
/**------------------------------------------------------------------
Check if the stack is empty. Input: stack. Output: TRUE if it is empty or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *);
/**------------------------------------------------------------------
Check if the stack is full. Input: stack. Exit: TRUE if it is full or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *);
/**------------------------------------------------------------------
Print the entire stack, placing the EleStack on top at the beginning of printing (and one EleStack per line).
Input: stack and file where to print it. Output: Returns the number of written characters.
------------------------------------------------------------------*/
int stack_print(FILE*, const Stack*);



#ifdef __cplusplus
}
#endif

#endif /* STACK_ELSTACK_H */


