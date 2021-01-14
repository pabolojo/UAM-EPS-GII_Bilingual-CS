/**
@date:18/02/2019
This file includes the node.c , in this file are implemented all the function of node.h 
**/
#include "node.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
extern int errno ;

struct _Node {
 char name[100];
 int id;
 int nConnect; };
//this function initialize the node and allocates memory for him 
Node * node_ini(){
    Node *n=(Node*)malloc(2*sizeof(Node));
     if (!n) {
        // print error message
        fprintf (stderr, "%s\n", strerror(errno));
        return NULL;
    }
    n->id=-1;
    n->nConnect=-1;
    for(int i=0;i<100;i++){
    n->name[i]=0;}
    return n;
}
//this function assign the name for the node 
Node * node_setName(Node * n, const char* name){
    int i=0;
    if(n==NULL){
        return NULL;
    }
    for(i=0;name[i]!=0;i++){
        n->name[i]=name[i];
    }
    return n;
}
/* Free the dynamic memory reserved for a node */
/* Returns the id of a given node, or -1 in case of error */
int node_getId(const Node * n){
    if(n==NULL){
        return -1;
    }
    return n->id;
}
/* Returns a pointer to the name of a given node, or NULL in case of error */
char* node_getName(const Node * n){
    if(n==NULL){
        return NULL;
    }
    char *str=NULL;
    str=(char*)malloc(100*sizeof(char));
    if(str==NULL){
        return NULL;
    }
    for(int i=0;i<100;i++){
        str[i]=0;
    }
    for(int i=0;n->name[i]!=0;i++){
        str[i]=n->name[i];
    }
    return str;
}
/* Returns the number of connections of a given node, or -1 in case of error */
int node_getConnect(const Node * n){
    if(n==NULL){
        return -1;
    }
    return n->nConnect;
}
/* Modifies the id of a given node, returns NULL in case of error */
Node * node_setId(Node * n, const int id){
    if(n==NULL){
        return NULL;
    }
    n->id=id;
    return n;
}
/* Modifies the number of connections of a given node, returns NULL in case of
error */
Node * node_setConnect(Node * n, const int cn){
    if(n==NULL){
        return NULL;
    }
    n->nConnect=cn;
    return n;
}
/* Compares two nodes by the id and then the name.
 * Returns 0 when both nodes have the same id, a smaller number than
 * 0 when n1 <n2 or one greater than 0 otherwise. */
/* Reserves memory for a node where it copies the data from the node src.
 * Returns the address of the copied node if everything went well, or NULL
otherwise */
/* Prints in pf the data of a node with the format: [id, name, nConnect]
 * Returns the number of characters that have been written successfully.
 * Checks if there have been errors in the Output flow, in that case prints
 * an error message in stderror*/

void node_destroy(Node * n){
  free(n);
}



int node_cmp (const Node * n1, const Node * n2){
  if(n1==NULL || n2==NULL){
    return ERROR;
  }
  if(n1->id==n2->id){
    return 0;
  }
  else if(n1->id<n2->id){
    return -2;
  }
  else{
    return 1;
  }
}


//this function recives a pointer of node and copy that node in a new pointer that is creating in the function
Node * node_copy(const Node * src){
  if(src==NULL){
    return NULL;
  }
  Node *nc=node_ini();

  if(nc==NULL){
    return NULL;
  }
  if(node_setId(nc,src->id)==ERROR){
    return NULL;
  }
  if(node_setName(nc,src->name)==ERROR){
    return NULL;
  }
  if(node_setConnect(nc,src->nConnect)==NULL){
    return NULL;
  }
  return nc;
}


//this function print in a file the information of the pointer 
int node_print(FILE *pf, const Node * n){
    int i;

    if (!pf || !n ) return -1;

    i  = fprintf(pf,"[%d, %s, %d]",n->id,n->name,n->nConnect);

    // check if there were errors in the outflow
    if (ferror (pf)) {
        fprintf(stderr, "fprintf failed\n");
    }
  return i;
}

