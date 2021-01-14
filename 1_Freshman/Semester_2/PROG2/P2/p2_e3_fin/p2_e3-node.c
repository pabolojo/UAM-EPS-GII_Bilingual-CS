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
#include "node.h"
#include "stack_fp.h"
#define MAXSTACK 1064
#define EMPTY_STACK -1


/*
 *
 */

int cleanUp (int ret_value, Node *pn, Node *p2, Stack *s){
    node_destroy(pn);
    node_destroy(p2);
    stack_destroy(s);
    exit(ret_value);
}
int main(int argc, char** argv)
{
   /*variable declarations*/
   Node *node1=NULL;
   Node *node2=NULL;
   Node *nodeaux=NULL;
   FILE *pf;
   Stack *s = NULL;
   int var;
   int ret_value=EXIT_FAILURE;
   Status st;
   pf=stdout;


    s=stack_ini(node_destroy, node_copy, node_print);
    if(!s){
      printf("Error creating the stack\n");
      cleanUp(ret_value,node1,node2,s);}
    node1=node_ini();
    if(!node1){
      printf("Error creating node1\n");
      cleanUp(ret_value,node1,node2,s);}
    node2=node_ini();
    if(!node2){
      printf("Error creating node2\n");
      cleanUp(ret_value,node1,node2,s);}

    node1=node_setName(node1, "first");
    if(!node1){
      printf("Error naming node1\n");
      cleanUp(ret_value,node1,node2,s);}
    node1=node_setId(node1, 111);
    if(!node1){
      printf("Error setting id of node1\n");
      cleanUp(ret_value,node1,node2,s);}
    st=stack_push(s,node1);
    if(st==ERROR){
      printf("Error pushing node1 into the stack\n");
      cleanUp(ret_value,node1,node2,s);}
    node_destroy(node1);

    node2=node_setName(node2, "second");
    if(!node2){
      printf("Error naming node2\n");
      cleanUp(ret_value,node1,node2,s);}
    node2=node_setId(node2, 222);
    if(!node2){
      printf("Error setting id of node2\n");
      cleanUp(ret_value,node1,node2,s);}
    st=stack_push(s,node2);
    if(st==ERROR){
      printf("Error pushing node2 into the stack\n");
      cleanUp(ret_value,node1,node2,s);}
    node_destroy(node2);

     printf("Print the contents of the stack\n");
     var=stack_print(pf,s);
     printf("printed characters: %d \n",var);




     printf("Emptying stack\n");

     while(stack_isEmpty(s)==FALSE)
     {
         nodeaux=stack_pop(s);
         if(!nodeaux){
           printf("Error poping node from the stack\n");
           cleanUp(ret_value,node1,node2,s);}
         node_print(pf,nodeaux);
         node_destroy(nodeaux);

    }
    printf("\nPrint the contents of the stack after emptying:\n");
    var=stack_print(pf,s);
    printf("printed characters: %d \n",var);

    fclose(pf);
    cleanUp(EXIT_SUCCESS,NULL,NULL,s);
    return EXIT_SUCCESS;
}

