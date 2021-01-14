/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   p2_e2.c
 *
 * Created on 28 de febrero de 2019, 18:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "stack_elestack.h"


/*
 *
 */
int cleanUp (int ret_value, EleStack *ele, Stack *s){
    EleStack_destroy(ele);
    stack_destroy(s);
    exit(ret_value);
}
double meanElementStack( Stack *s) {
    Stack *aux=NULL;
    EleStack * ele=NULL;
    Status st;
    int i=0,num=0;
    if(!s) return ERROR;
    aux=stack_ini();
    if(!aux){return ERROR;}

    while(stack_isEmpty(s)==FALSE){
      ele=stack_pop(s);
      if(!ele){
        stack_destroy(aux);
        return -1;}
        num+=*((int*)EleStack_getInfo(ele));
        if(!ele){
          stack_destroy(aux);
          return -1;}
        st=stack_push(aux,ele);
        if(st==ERROR){
          stack_destroy(aux);
          return -1;}
        i++;
        EleStack_destroy(ele);
        ele=NULL;
        /*add the value of the element in our counter   (BEWARE get returns a pointer to void..we need THE VALUE OF and INT POINTER)
        keep track of how many values we add
        destroy the element we have just pop*/
    }
    while(stack_isEmpty(aux)==FALSE){
        ele=stack_pop(aux);
        if(!ele){
          stack_destroy(aux);
          return -1;}
        st=stack_push(s,ele);
        if(st==ERROR){
          stack_destroy(aux);
          return -1;
        }
        EleStack_destroy(ele);
    }
        /*another function we need to creat is the one that computes the mean of the stack values. In the practice it says : "The function that calculates the average must NOT modify the stack", this means that as we are doing pop etc and we are changing the stack we need to create an auxliliary stack, to be adding everything that we remove from the original..and then seting the original to the copied one
        push into the original stack the elements from the aux
        (remember to destroy the elements you pop)*/
    stack_destroy(aux);
    return num/(double)i;/*mean of the values you have added (remember to use castings if needed)*/
}

/*main function*/
int main(int argc, char **argv) {
/*declar vars*/
   int stlen=0;
   Stack *s=NULL;
   EleStack *ele=NULL;
   Status st;
   double mean;
   int i;
   /*check argument count is 2 otherwise return EXIT_FAILURE*/
   if(argc!=2){
     printf("Execution command must be %s integer\n",argv[0]);
     return EXIT_FAILURE;}
  stlen=atol(argv[1]);
  /*retrieve the lenght of the stack from the argument vector*/
  if(stlen>MAXSTACK-1 || stlen<1){
    printf("Lenght not valid\n");
    return EXIT_FAILURE;
  }
   /*init the stack*/
  s=stack_ini();
  /*if errors call cleanup*/
  if(!s){
    printf("Error creating the stack\n");
    cleanUp(EXIT_FAILURE, ele, s);}
  /*init the element of the stack*/

  ele=EleStack_ini();
   /*if errors call cleanup*/
   if(!ele){
     printf("Error creating the element\n");
     cleanUp(EXIT_FAILURE, ele, s);}
    /*insert in the stack until you reach the desired size*/
  for(i=0;i<stlen+1;i++){
        /*note that elestack_setInfo returns a Status so does*/
        st=EleStack_setInfo(ele,&i);
        if(st==ERROR){
          printf("Error setting integer value to the element\n");
          cleanUp(EXIT_FAILURE, ele, s);}
        /*stack_push  hence you need to retrieve the status and in case there are errors exit and call cleanup*/
        st=stack_push(s,ele);
        if(st==ERROR){
          printf("Error pushing element to the stack\n");
          cleanUp(EXIT_FAILURE, ele, s);}
    }

    printf("Stack before the call to the function\n");
    /*print the stack*/
    stack_print(stdout,s);
   /*compute the mean*/
   mean=meanElementStack(s);
   if(mean==-1){
     printf("Error calculating the mean of the stack\n");
     cleanUp(EXIT_FAILURE, ele, s);
   }
   /*print the mean*/
   printf("Mean: %f\n",mean);
   /*print the stack*/
   printf("Stack after the call to the function\n");
   stack_print(stdout,s);
   /*free resources by calling cleanup with success*/
   cleanUp(EXIT_SUCCESS, ele, s);
   return EXIT_SUCCESS;
}

