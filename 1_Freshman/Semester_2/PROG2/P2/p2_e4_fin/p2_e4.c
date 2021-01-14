#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
extern int errno ;


int mainCleanUp (int ret_value, Graph *gc)
{
   graph_destroy(gc);
   exit(ret_value);

}
int main(int argc, char** argv)
{
int in,out;
int ret_value=EXIT_FAILURE;
Status s;

Node *aux=NULL;
FILE *read=NULL;
Graph *gc=NULL;

if(argc!=4){
  printf("Execution command should be like: %s graph_file idNode_from idNode_to\n",argv[0]);
  return ERROR;
}

gc=graph_ini();
if(!gc){
  printf("Error creating graph\n");
  mainCleanUp(ret_value,gc);}

in = atoi(argv[2]);
out = atoi(argv[3]);
read=fopen(argv[1],"r");

if(!read){
fprintf (stderr, "%s\n", strerror(errno));
mainCleanUp(ret_value,gc);
}

s=graph_readFromFile (read,gc);
if(s==ERROR){
  printf("Error reading graph from file\n");
  return ERROR;}
graph_print(stdout,gc);
fclose(read);

aux=graph_findDeepSearch(gc,in,out);
if(aux==NULL)
{
    fprintf(stdout,"\nNo path has been found on %s\n",argv[1]);
}
else
{
      node_destroy(aux);
      aux=graph_getNode (gc,out);
      if(!aux){
        printf("Error getting node from graph\n");
        mainCleanUp(ret_value,gc);}
      fprintf(stdout,"\nThere is a path from %d to %d\n",in,out);
      node_print(stdout,aux);
      node_destroy(aux);
      fprintf(stdout,"\n\nHere is the path:\n\n");
      graph_printPath (stdout, gc,out);

}

mainCleanUp(EXIT_SUCCESS,gc);
return 0;


}
