/**
@date:18/02/20149
This file includes the graph.c , in this file are implemented all the function of graph.h
**/
#include <stdlib.h>
#include <string.h>
#include "graph.h"

# define MAX_NODES 1064
# define MAX_LINE 256



enum { NO_FILE_POS_VALUES = 2 };

struct _Graph {
    Node *nodes[MAX_NODES];
    Bool connections[MAX_NODES][MAX_NODES];

    int num_nodes;
    int num_edges;
};
/*###### Public Interface ###########*/

Graph * graph_ini(){
    Graph *g = NULL;
    int i;
    int j;
    g = (Graph*)malloc(sizeof(Graph));
    if(!g) {
        return NULL;
    }

    g->num_nodes = 0;
    g->num_edges = 0;

    /*go over all the possitions of nodes from 0 to MAX_NODES and assign nodes[i] to NULL in the graph*/
    for(i=0;i<MAX_NODES;i++){
        g->nodes[i]=NULL;
    }
    for(i=0;i<MAX_NODES;i++){
      for(j=0;j<MAX_NODES;j++){
        g->connections[i][j]=FALSE;
      }
    }
    return g;
}

void graph_destroy(Graph * g) {

    int i;
    /*go over all the nodes of the graph and destroy them with node destroy*/
    for(i=0;i<MAX_NODES;i++) {
        node_destroy(g->nodes[i]);
    }

    /*free graph*/
    free(g);

}

int graph_getNumberOfNodes(const Graph * g) {
    if(!g) return -1;

    return  g->num_nodes;
}

int graph_getNumberOfEdges(const Graph * g){
    if(!g) return -1;

    return g->num_edges;
}

Status graph_insertNode(Graph * g, const Node* n) {
    Node *aux;
    int i, id;

    if(!g || !n) return ERROR;

    /*get the node id*/
    id=node_getId(n);
    if(id==-1) return ERROR;
    /* search if in the graph there is already a node with the same id*/
    i = find_node_index(g,id);
    if (i!=-1) return ERROR;
    /* make a copy of the node*/
    aux=node_copy(n);
    if(!aux) return ERROR;
    /* assign the node to the array of nodes*/
    g->nodes[g->num_nodes]=aux;

    /* Assign to 0 the number of connections of the node*/
    aux=node_setConnect(aux,0);
    if(!aux){
      node_destroy(aux);
      return ERROR;
    }
    /* increase the number of nodes in the graph*/
    g->num_nodes++;
    /* assign the connections of the node in the connections matrix to FALSE*/
    for(i=0;i<g->num_nodes-1;i++){
        g->connections[g->num_nodes-1][i] = 0;
        g->connections[i][g->num_nodes-1] = 0;
    }
    return OK;
}

Status graph_insertEdge(Graph * g, const int nId1, const int nId2) {
    int from, to, n_from;
    if (!g) return ERROR;

    /*  get, indexes of the nodes*/
    from =find_node_index(g,nId1);
    if(from<0) return ERROR;

    to = find_node_index(g,nId2);
    if(to < 0) return ERROR;

    /* create the connection set it to TRUE*/

    g->connections[from][to]=TRUE;
    /* update the total of edges of the node*/
    n_from = node_getConnect(g->nodes[from]) + 1;
    if(n_from==0) return ERROR;
    if(!(node_setConnect(g->nodes[from],n_from))) return ERROR;

    /* update the total of edges of the graph*/
    g->num_edges++;
    return OK;
}

Node * graph_getNode(const Graph * g, int nId) {

    int index;
    Node *aux=NULL;
    if(!g) return NULL;

    index = find_node_index(g,nId);
    if (index < 0) return NULL;

    /*make a copy of the retrieved node*/
    aux=node_copy(g->nodes[index]);
    if(!aux) return NULL;
    return aux;
}

Status graph_setNode (Graph *g, const Node *n){

    int index=-1;
    Node *aux=NULL;
    if(!g || !n) return ERROR;

    index = find_node_index(g, node_getId(n));
    if(index<=-1) return ERROR;

    aux= node_copy(n);
    if(!aux) return ERROR;

    /* update node*/
    node_destroy(g->nodes[index]);
    /*assign in graph nodes[the index we have searched] the copied node*/
    g->nodes[index]=aux;

    return OK;
}

/*------------------------------------------------------------------------*/

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
    int ind1,ind2;

    if(!g){
       return FALSE;
    }
    ind1=find_node_index(g, nId1);

    if(ind1<0){
        return FALSE;
    }
    ind2=find_node_index(g, nId2);
    if(ind2<0){
        return FALSE;
    }
    return g->connections[ind1][ind2];
}

/*---------------------------------------------------------------------*/

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {

    int ind;
    if(!g){
        return -1;
    }

    ind=find_node_index(g,fromId);
    if(ind < 0){
        return -1;
    }

    return node_getConnect(g->nodes[ind]);
}

int *graph_getNodesId (const Graph *g){
    int *array,i;

    if(!g) return  NULL;
     /* create array of ints of size number of nodes of the graph*/
    array = (int*)malloc(sizeof(int) * g->num_nodes);
    if (!array) {
        return NULL;
    }

    /*from 0 to number of nodes in the graph fill the array by getting the node_getId of each node in the graph*/
    for(i=0;i<g->num_nodes;i++){
        array[i]=node_getId(g->nodes[i]);
        if(array[i]==-1){
          free(array);
          return NULL;
        }
    }

    return array;
}

/*-----------------------------------------------------------------*/

int* graph_getConnectionsFrom (const Graph * g, const int fromId) {

    int ind;
    int *array;
    int tam,i;
    Node *aux;

    if(!g){
        return NULL;
    }

    ind = find_node_index(g,fromId);

    if(ind < 0){
        return NULL;
    }

    tam = node_getConnect(g->nodes[ind]);
    if(tam==-1) return NULL;
    /* array with the indexes of the connected nodes*/
    array = graph_getConectionsIndex(g,ind);

    if(!array){
        return NULL;
    }

    /*for each one of them I get its Id and I overwrite the value of the index
      * for each Id */

    for(i=0;i<tam;i++){
        aux = g->nodes[array[i]];
        array[i] = node_getId(aux);
        if(array[i]==-1){
          free(array);
          return NULL;
        }
    }

    return array;
}

int graph_print(FILE *pf, const Graph * g) {

    int bytes=0;
    int id=-1,cn=-1;
    int *array=NULL,i,j;

    if(!g || !pf) return -1;

    for(i=0;i<g->num_nodes;i++){
        /*print the i-th node*/
        fputs("\n", pf);
        bytes = bytes + node_print(pf,g->nodes[i]);
        /* prints the connections of the i-th node*/
        cn = node_getConnect(g->nodes[i]);
        id = node_getId(g->nodes[i]);

        array = graph_getConnectionsFrom(g,id);
        if(!array) return -1;

        for(j=0;j<cn;j++){
            bytes = bytes + fprintf(pf, "%d ", array[j]);
        }
        /* free resources*/
        free(array);
    }

    /* check if there were errors in the outflow*/
    if (ferror (pf)) {
        fprintf(stderr, "fprintf failed\n");
    }
    fputs("\n", pf);
    return 0;/*bytes*/
}

int find_node_index(const Graph * g, int nId1) {
 int i;
 if (!g) return -1;

 for(i=0; i < g->num_nodes; i++) {
 if (node_getId (g->nodes[i]) == nId1) return i;
 }

 /* ID not found*/
 return -1;
}
int* graph_getConectionsIndex(const Graph * g, int index) {
 int *array = NULL, i=0, j=0, size=0;

 if (!g) return NULL;
 if (index < 0 || index >g->num_nodes) return NULL;
 /* get memory for the array with the connected nodes index*/
 size = node_getConnect (g->nodes[index]);
 if(size==-1) return NULL;
 array = (int *) malloc(sizeof(int) * size);
 if (!array) {
 return NULL;
 }
 for(i=0;i<size;i++){
   array[i]=0;
 }

 /* assign values to the array with the indexes of the connected nodes*/
 for(i = 0; i< g->num_nodes; i++) {
 if (g->connections[index][i] == TRUE) {
 array[j] = i;
 j++;
}
}

 return array;
}

Status graph_readFromFile (FILE *fin, Graph *g) {
 Node *n;
 char buff[MAX_LINE], name[MAX_LINE];
 int i, nnodes = 0, id1, id2;
 Status flag = ERROR;

 if(!fin || !g)return ERROR;
 /* read number of nodes*/
 if ( fgets (buff, MAX_LINE, fin) != NULL)
 if ( sscanf(buff, "%d", &nnodes) != 1) return ERROR;

 /* init buffer_node*/
 n = node_ini();
 if (!n) return ERROR;

 /* read nodes line by line*/
 for(i=0; i < nnodes; i++) {
 if ( fgets(buff, MAX_LINE, fin) != NULL)
 if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES) break;

 /* set node name and node id*/
 node_setName (n, name);
 node_setId (n, id1);

 /* insert node in the graph*/
if ( graph_insertNode (g, n) == ERROR) break;
 }

 /* Check if all node have been inserted*/
 if (i < nnodes) {
 node_destroy(n);
 return ERROR;
 }

 /* read connections line by line and insert it*/
 while ( fgets(buff, MAX_LINE, fin) ) {
 if ( sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES )
 if (graph_insertEdge(g, id1, id2) == ERROR) break;
 }

 /* check end of file*/
 if (feof(fin)) flag = OK;

 /* clean up, free resources*/
 node_destroy (n);
 return flag;
}

Node *graph_findDeepSearch (Graph *g, int from_id, int to_id){

  Stack *s=NULL;
  Node *aux=NULL;
  Status st;
  int i;
  P_stack_ele_destroy f1 = node_destroy;
  P_stack_ele_copy f2 = node_copy;
  P_stack_ele_print f3 = node_print;
  if(!g || find_node_index(g,from_id)==-1 || find_node_index(g,to_id)==-1) return NULL;
  s=stack_ini(f1,f2,f3);
  if(!s){
    stack_destroy(s);
    return NULL;
  }
  aux=graph_getNode(g,from_id);
  if(!aux){
    node_destroy(aux);
    stack_destroy(s);
    return NULL;
  }
  st=stack_push(s,(const void*)aux);
  if(st==ERROR){
    node_destroy(aux);
    stack_destroy(s);
    return NULL;
  }
  node_destroy(aux);
  while(stack_isEmpty(s)!=TRUE){

    aux=(Node *)stack_pop(s);
    if(!aux){
      node_destroy(aux);
      stack_destroy(s);
      return NULL;
    }
    if(node_getLabel(aux)==WHITE){
      int *array=NULL;
      int tam=node_getConnect(aux);
      if(tam==-1){
        node_destroy(aux);
        stack_destroy(s);
        return NULL;
      }
      aux=node_setLabel(aux,BLACK);
      if(!aux){
        node_destroy(aux);
        stack_destroy(s);
        return NULL;
      }
      st=graph_setNode(g,aux);
      if(st==ERROR){
        node_destroy(aux);
        stack_destroy(s);
        return NULL;
      }
      array = graph_getConnectionsFrom(g,node_getId(aux));
      if(!array){
        node_destroy(aux);
        stack_destroy(s);
        return NULL;
      }
      for(i=0;i<tam;i++){
        Node *aux2=NULL;
        aux2=graph_getNode(g,array[i]);
        if(!aux2){
          node_destroy(aux);
          stack_destroy(s);
          free(array);
          return NULL;
        }
        if(node_getId(aux2)==to_id){
          if(!(node_setAntecesorId(aux2,node_getId(aux)))){
            node_destroy(aux);
            stack_destroy(s);
            free(array);
            return NULL;
          }
          if(graph_setNode(g,aux2)==ERROR){
            node_destroy(aux);
            stack_destroy(s);
            free(array);
            return NULL;
          }
          free(array);
          node_destroy(aux);
          stack_destroy(s);
          return aux2;
        }
        else if(node_getLabel(aux2)==WHITE){
          if(!(node_setAntecesorId(aux2,node_getId(aux)))){
            node_destroy(aux);
            stack_destroy(s);
            free(array);
            return NULL;
          }
          if(graph_setNode(g,aux2)==ERROR){
            node_destroy(aux);
            stack_destroy(s);
            free(array);
            return NULL;
          }
          if(stack_push(s,(const void *) aux2)==ERROR){
            node_destroy(aux);
            stack_destroy(s);
            free(array);
            return NULL;
          }
        }
        node_destroy(aux2);
        aux2=NULL;
      }
      free(array);
      array=NULL;
    }
    node_destroy(aux);
    aux=NULL;
  }
  stack_destroy(s);
  s=NULL;
  return NULL;
}

void graph_printPath (FILE *pf, Graph *g, int idNode){
  /* declare variables*/
  Node *aux=NULL;
  int antec;
  Stack *s=NULL;
  P_stack_ele_destroy f1 = node_destroy;
  P_stack_ele_copy f2 = node_copy;
  P_stack_ele_print f3 = node_print;
  /*check for errors in input*/
  if(!pf || !g || find_node_index(g,idNode)==-1) return;
  /* find the node in the graph*/
  s=stack_ini(f1,f2,f3);
  if(!s) return;

  aux=graph_getNode(g,idNode);

  if(!aux){
    stack_destroy(s);
    return;}
  antec=node_getAntecesorId(aux);
  while(antec!=-1){
    if(stack_push(s,(const void *)aux)==ERROR){
      node_destroy(aux);
      stack_destroy(s);
      return;
    }
    node_destroy(aux);
    /* get its Antecesor*/
    aux=graph_getNode(g,antec);
    if(!aux){
      node_destroy(aux);
      stack_destroy(s);
      return;
    }
    antec=node_getAntecesorId(aux);
    /* repeat process with the antecesor*/
  }
  node_destroy(aux);
  stack_print(pf,s);
  /*print the id*/
  stack_destroy(s);
}

