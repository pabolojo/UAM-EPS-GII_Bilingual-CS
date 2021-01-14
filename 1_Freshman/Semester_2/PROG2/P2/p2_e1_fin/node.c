#include "node.h"
#include <stdlib.h>
#include <string.h>

struct _Node {
 char name[100];
 int id;
 int nConnect; };

Node * node_ini(){
    Node *n=(Node*)malloc(sizeof(Node));
    int i;
     if (!n) {
        return NULL;
    }
    n->id=-1;
    n->nConnect=0;
    for(i=0;i<100;i++){
    n->name[i]=0;}
    return n;
}

Node * node_setName(Node * n, const char* name){

    if(n==NULL || name==NULL){
        return NULL;
    }
    strcpy(n->name,name);
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
    char *str=NULL;
    int i;
    if(n==NULL){
        return NULL;
    }
    str=(char*)malloc(100*sizeof(char));
    if(str==NULL){
        return NULL;
    }
    for(i=0;i<100;i++){
        str[i]=0;
    }
    strcpy(str,n->name);
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



Node * node_copy(const Node * src){
  Node *nc=node_ini();
  if(src==NULL){
    return NULL;
  }

  if(nc==NULL){
    return NULL;
  }
  if(node_setId(nc,src->id)==ERROR){
    node_destroy(nc);
    return NULL;
  }
  if(node_setName(nc,src->name)==ERROR){
    node_destroy(nc);
    return NULL;
  }
  if(node_setConnect(nc,src->nConnect)==NULL){
    node_destroy(nc);
    return NULL;
  }
  return nc;
}



int node_print(FILE *pf, const Node * n){
    int i;

    if (!pf || !n ) return -1;

    i  = fprintf(pf,"[%s, %d, %d]",n->name,n->id,n->nConnect);

    /*check if there were errors in the outflow*/
    if (ferror (pf)) {
        fprintf(stderr, "fprintf failed\n");
    }
  return i;
}
