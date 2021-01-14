/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 *
 * Created on 19 de febrero de 2019, 12:27
 */


/*
falta control de errores y valgrind
*/
#include <stdio.h>
#include <stdlib.h>
#include "int.h"
#include "stack_fp.h"
#include <string.h>
#define EMPTY_STACK -1


/*
 *
 */
int cleanUp (int ret_value, Stack *s){

    stack_destroy(s);
    exit(ret_value);
}

double meanElementStack( Stack *s, P_stack_ele_destroy f1, P_stack_ele_copy f2, P_stack_ele_print f3) {
    Stack *aux=NULL;
    int * ele=NULL;
    Status st;
    int i=0,num=0;
    if(!s) return ERROR;
    aux=stack_ini(f1, f2, f3);
    if(!aux){return ERROR;}

    while(stack_isEmpty(s)==FALSE){
        ele=stack_pop(s);
        if(!ele){
          stack_destroy(aux);
          return -1;}
        num+=*(ele);
        st=stack_push(aux,(const void *)ele);
        if(st==ERROR){
          stack_destroy(aux);
          return -1;}
        i++;
        free(ele);
        ele=NULL;
        /*add the value of the element in our counter   (BEWARE get returns a pointer to void..we need THE VALUE OF and INT POINTER)
        keep track of how many values we add
        destroy the element we have just pop*/
    }
    while(stack_isEmpty(aux)==FALSE){
        ele=(int *)stack_pop(aux);
        if(!ele){
          stack_destroy(aux);
          return -1;}
        st=stack_push(s,(const void *)ele);
        if(st==ERROR){
          stack_destroy(aux);
          return -1;
        }
        free(ele);
      }
      stack_destroy(aux);
      return num/(double)i;/*mean of the values you have added (remember to use castings if needed)*/
}

int main(int argc, char** argv)
{
  /*variable declarations*/
   P_stack_ele_destroy f1 = int_destroy;
   P_stack_ele_copy f2 = int_copy;
   P_stack_ele_print f3 = int_print;
    int stlen=0;
    Stack *s=NULL;
    Status st;
    double mean;
    int i;
    /*check argument count is 2 otherwise return EXIT_FAILURE*/
    stlen=atol(argv[1]);
    /*retrieve the lenght of the stack from the argument vector*/
    if(stlen>MAXSTACK-1 || stlen<1){
      printf("Lenght not valid\n");
      return EXIT_FAILURE;
    }
   /*init the stack*/
   s=stack_ini(f1, f2, f3);
   /*if errors call cleanup*/
   if(!s){
   printf("Error creating the stack\n");
   cleanUp(EXIT_FAILURE, s);}
   /*init the element of the stack
   insert in the stack until you reach the desired size*/
   for(i=0;i<stlen+1;i++){
         /*note that elestack_setInfo returns a Status so does
         stack_push  hence you need to retrieve the status and in case there are errors exit and call cleanup*/
         st=stack_push(s,(const void *)&i);
         if(st==ERROR)
          {printf("Error pushing integer to the stack\n");
          cleanUp(EXIT_FAILURE, s);}
     }

     printf("Stack before the call to the function\n");
     /*print the stack*/
     stack_print(stdout,s);
    /*compute the mean*/
    mean=meanElementStack(s,f1,f2,f3);
    if(mean==-1){
      printf("Error calculating the mean of the stack\n");
      cleanUp(EXIT_FAILURE, s);
    }
    /*print the mean*/
    printf("Mean: %f\n",mean);
    /*print the stack*/
    printf("Stack after the call to the function\n");
    stack_print(stdout,s);
     /*free resources by calling cleanup with success*/
    cleanUp(EXIT_SUCCESS, s);
    return EXIT_SUCCESS;
}

