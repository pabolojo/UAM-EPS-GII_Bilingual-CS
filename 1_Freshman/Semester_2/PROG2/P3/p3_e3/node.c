#include "node.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#define NAME_L 64

struct _Node {
 char name[NAME_L];
 int id;
 int nConnect;
 Label etq;
 int antecesor_id;
};

Node * node_ini(){
    Node *n=(Node*)malloc(sizeof(Node));
    int i;
     if (!n) {
        return NULL;
    }
    n->id=-1;
    n->nConnect=0;
    n->etq=WHITE;
    n->antecesor_id=-1;
    for(i=0;i<NAME_L;i++){
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
    for(i=0;i<NAME_L;i++){
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

void node_destroy(void * n){
  free((Node *)n);
}



int node_cmp (const void * n1, const void * n2){
  const Node * aux1=(const Node *)n1;
  const Node * aux2=(const Node *)n2;
  if(aux1==NULL || aux2==NULL){
    return ERROR;
  }
  if(aux1->id==aux2->id){
    return 0;
  }
  else if(aux1->id<aux2->id){
    return -2;
  }
  else{
    return 1;
  }
}



void * node_copy(const void * src){
  Node *nc=node_ini();
  const Node *aux=(const Node *)src;
  if(aux==NULL){
    return NULL;
  }

  if(nc==NULL){
    return NULL;
  }
  if(node_setId(nc,aux->id)==ERROR){
    node_destroy(nc);
    return NULL;
  }
  if(node_setName(nc,aux->name)==ERROR){
    node_destroy(nc);
    return NULL;
  }
  if(node_setConnect(nc,aux->nConnect)==NULL){
    node_destroy(nc);
    return NULL;
  }
  if(node_setLabel(nc,aux->etq)==NULL){
    node_destroy(nc);
    return NULL;
  }
  if(node_setAntecesorId(nc,aux->antecesor_id)==NULL){
    node_destroy(nc);
    return NULL;
  }
  return (void *)nc;
}



int node_print(FILE *pf, const void * n){
    int i;
    const Node *aux=(const Node *)n;
    if (!pf || !aux ) return -1;
    i  = fprintf(pf,"[%s, %d, %d]\n",aux->name,aux->id,aux->nConnect);

    /*check if there were errors in the outflow*/
    if (ferror (pf)) {
        fprintf(stderr, "fprintf failed\n");
    }
  return i;
}

Label node_getLabel(const Node*n){

    if(!n) return WHITE;
    return n->etq;

}

int node_getAntecesorId(const Node*n){

  if(!n) return -1;
  return n->antecesor_id;

}

Node* node_setLabel( Node *n, Label l){

  if(!n) return NULL;
  n->etq=l;
  return n;

}

Node* node_setAntecesorId(Node *n, int id){

  if(!n) return NULL;
  n->antecesor_id=id;
  return n;

}
