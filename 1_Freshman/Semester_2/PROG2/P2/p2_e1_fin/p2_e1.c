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
#include "stack_elestack.h"
#define MAXSTACK 1064
#define EMPTY_STACK -1


/*
 *
 */
int cleanUp (int ret_value, Node *pn, Node *p2,EleStack *ele1, EleStack *ele2, Stack *s){
    if(pn){
      node_destroy(pn);
      pn=NULL;}
    if(p2){
      node_destroy(p2);
    p2=NULL;}
    if(ele1){
      EleStack_destroy(ele1);
    ele1=NULL;}
    if(ele2){
      EleStack_destroy(ele2);
    ele2=NULL;}
    if(s){
      stack_destroy(s);
    s=NULL;}
    exit(ret_value);
}
int main(int argc, char** argv)
{
    /*variable declarations*/
   Node *node1=NULL;
   Node *node2=NULL;
   Stack *s = NULL;
   EleStack *ele1 =NULL;
   EleStack *ele2 =NULL;
   EleStack *eleaux =NULL;
   int var;
   int ret_value=EXIT_FAILURE;
   Status st;

    s=stack_ini();
    if(!s){
      printf("Error creating the stack\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    ele1=EleStack_ini();
    if(!ele1){
      printf("Error creating ele1\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    ele2=EleStack_ini();
    if(!ele2){
      printf("Error creating ele2\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    node1=node_ini();
    if(!node1){
      printf("Error creating node1\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    node2=node_ini();
    if(!node2){
      printf("Error creating node2\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}

    node1=node_setName(node1, "first");
    if(!node1){
      printf("Error naming node1\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    node1=node_setId(node1, 111);
    if(!node1){
      printf("Error setting id of node1\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    st=EleStack_setInfo(ele1,node1);
    if(st==ERROR){
      printf("Error stting ele1 info into node1\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    node_destroy(node1);
    st=stack_push(s,ele1);
    if(st==ERROR){
      printf("Error pushing ele1 into the stack\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    EleStack_destroy(ele1);

    node2=node_setName(node2, "second");
    if(!node2){
      printf("Error naming node2\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    node2=node_setId(node2, 222);
    if(!node2){
      printf("Error setting id of node2\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    st=EleStack_setInfo(ele2,node2);
    if(st==ERROR){
      printf("Error stting ele2 info into node2\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    node_destroy(node2);
    st=stack_push(s,ele2);
    if(st==ERROR){
      printf("Error pushing ele2 into the stack\n");
      cleanUp(ret_value,node1,node2,ele1,ele2,s);}
    EleStack_destroy(ele2);

     printf("Print the contents of the stack\n");
     var=stack_print(stdout,s);
     printf("printed characters: %d \n",var);




     printf("Emptying stack\n");

     while(stack_isEmpty(s)==FALSE)
     {
         eleaux=stack_pop(s);
         if(!eleaux){
           printf("Error poping element from the stack\n");
           cleanUp(ret_value,node1,node2,ele1,ele2,s);}
         EleStack_print(stdout,eleaux);
         EleStack_destroy(eleaux);

    }
    printf("\nPrint the contents of the stack after emptying:\n");
    var=stack_print(stdout,s);
    printf("printed characters: %d \n",var);
    cleanUp(EXIT_SUCCESS,NULL,NULL,NULL,NULL,s);
    return (EXIT_SUCCESS);
}

