
/**
@date:18/02/2019

This file makes the necesary calls to acomplish p1_e1, in this file is included the main file
**/

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

/*
 *
 */
int main()
{
//we initialize node1 and node 2 calling the function node_ini();
    Node *node1=NULL;
    node1=node_ini();
    Node *node2=NULL;
    node2=node_ini();
//we check if they are no errors and we assign the values for node1 and node2
    if(node1==NULL || node2==NULL){
        return EXIT_FAILURE;
    }
    if(node_setId(node1,111)==NULL || node_setId(node2,222)==NULL){
        return EXIT_FAILURE;
    }
    else if(node_setName(node1,"first")==NULL || node_setName(node2,"second")==NULL){
        return EXIT_FAILURE;
    }
    else if(node_setConnect(node1,0)==NULL || node_setConnect(node2,0)==NULL){
        return EXIT_FAILURE;
    }
//we call the rest of the functions of node.c and we assign the rest of the values 
    char *name1 = NULL;
    name1=node_getName(node1);
    int id1 = -1;
    id1=node_getId(node1);
    int cn1 = -1;
    cn1=node_getConnect(node1);
    char *name2 = NULL;
    name2=node_getName(node2);
    int id2 = -1;
    id2=node_getId(node2);
    int cn2 = -1;
    cn2=node_getConnect(node2);
    printf("[%d, %s, %d]",id1,name1,cn1);
    printf("[%d, %s, %d]\n",id2,name2,cn2);
    printf("Are they equal? ");
    if(node_cmp(node1,node2)!=0){
        printf("No\n");
    }
    else{
        printf("Yes\n");
    }
    printf("Id of the first node: %d\n",id1);
    printf("The name of the second node is: %s\n",name2);
    free(name2);
    node_destroy(node2);
    node2=node_copy(node1);
    if(node2==NULL){
        return EXIT_FAILURE;
    }
    name2 = node_getName(node2);
    id2 = node_getId(node2);
    cn2 = node_getConnect(node2);
    printf("[%d, %s, %d]",id1,name1,cn1);
    printf("[%d, %s, %d]\n",id2,name2,cn2);

    printf("Are they equal? ");
    if(node_cmp(node1,node2)!=0){
        printf("No\n");
    }
    else{
        printf("Yes\n");
    }
//we destroy all the memory
    free(name1);
    free(name2);
    node_destroy(node1);
    node_destroy(node2);
    return EXIT_SUCCESS;
}

