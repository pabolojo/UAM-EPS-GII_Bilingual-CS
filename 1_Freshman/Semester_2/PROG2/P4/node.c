#include "node.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#define NAME_L 255

struct _Node {
 char name[NAME_L];
 int id;
};

Node * node_ini(){
    Node *n=(Node*)malloc(sizeof(Node));
    int i;
     if (!n) {
        return NULL;
    }
    n->id=-1;
    for(i=0;i<NAME_L;i++){
    n->name[i]=0;}
    return n;
}

Node * node_setId(Node * n, const int id){
    if(n==NULL){
        return NULL;
    }
    n->id=id;
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

  return (void *)nc;
}



int node_print(FILE *pf, const void * n){
    int i;
    const Node *aux=(const Node *)n;
    if (!pf || !aux ) return -1;
    i  = fprintf(pf,"[%d, %s]\n",aux->id,aux->name);

    /*check if there were errors in the outflow*/
    if (ferror (pf)) {
        fprintf(stderr, "fprintf failed\n");
    }
  return i;
}
