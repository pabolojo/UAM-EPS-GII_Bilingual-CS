/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   stack_fp.h
 *
 * Created on 5 de marzo de 2019, 12:41
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif
#include "int.h"
typedef struct _Stack Stack;

#define MAXSTACK 1064
#define EMPTY_STACK -1
/* Types of function pointers supported by the stack */
typedef void (*P_stack_ele_destroy)(void*);
typedef void* (*P_stack_ele_copy)(const void*);
typedef int (*P_stack_ele_print)(FILE *, const void*);
/* The stack_ini function will receive the values for the stack fields that are function pointers, that is, it will
receive the functions to, respectively, destroy, copy and print the elements of the created stack*/
Stack * stack_ini (P_stack_ele_destroy f1, P_stack_ele_copy f2, P_stack_ele_print f3);
void stack_destroy(Stack *);
Status stack_push(Stack *, const void *);
void * stack_pop(Stack *);
Bool stack_isEmpty(const Stack *);
Bool stack_isFull(const Stack *);
int stack_print(FILE*, const Stack*);


#ifdef __cplusplus
}
#endif

#endif /* STACK_FP_H */

