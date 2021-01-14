#include "tree.h"
#include "node.h"
#include <string.h>
#include <errno.h>
#define MAX 255
extern int errno;

void mainCleanUp (Tree *t, FILE *pf) {
 if (t) tree_free(t);
 if (pf) fclose (pf);
}
int main(int argc, char** argv) {
 FILE *pf=NULL;
 Tree *t=NULL;
 int i;
 Node *aux=NULL;
 Status s;
 char name[MAX]="";
 if (argc != 2) {
 fprintf(stderr, " Error: Enter as argument the name of the file with the nodes.\n");
 return EXIT_FAILURE;
 }
 pf = fopen(argv[1], "r");
 if (pf==NULL){
 fprintf (stderr, " File opening error: %s\n", strerror(errno));
 return EXIT_FAILURE;
 }
 if(!(t=tree_ini(node_destroy,node_copy,node_print,node_cmp))){
   fprintf(stderr, " Error creating tree\n");
   mainCleanUp (t, pf);
   return EXIT_FAILURE;
 }
 aux=node_ini();
 if(!aux){
   fprintf(stderr, " Error creating auxialiary elements\n");
   mainCleanUp (t, pf);
   return EXIT_FAILURE;
 }

 while(fscanf(pf, "%d %s",&i,name) == 2){
   if(!node_setName(aux,name)){
     fprintf(stderr, " Error setting info of auxialiary elements\n");
     node_destroy(aux);
     mainCleanUp (t, pf);
     return EXIT_FAILURE;
   }
   if(!node_setId(aux,i)){
     fprintf(stderr, " Error setting info of auxialiary elements\n");
     node_destroy(aux);
     mainCleanUp (t, pf);
     return EXIT_FAILURE;
   }
   s=tree_insert(t,aux);
   if(s==ERROR){
     fprintf(stderr, " Error inserting element in tree\n");
     node_destroy(aux);
     mainCleanUp(t, pf);
     return EXIT_FAILURE;
   }
 }

 fprintf(stdout,"Number of nodes: %d\n",tree_numNodes(t));
 fprintf(stdout,"Depth: %d\n",tree_depth(t));

 if(tree_print(stdout,t)==ERROR){
   fprintf(stderr, " Error printing tree\n");
   node_destroy(aux);
   mainCleanUp(t, pf);
   return EXIT_FAILURE;
 }
 fprintf(stdout,"Enter a number: ");
 scanf("%d",&i);
 if(!node_setId(aux,i)){
   fprintf(stderr, " Error setting info of auxialiary elements\n");
   node_destroy(aux);
   mainCleanUp (t, pf);
   return EXIT_FAILURE;
 }
 fprintf(stdout,"Number entered: %d\n",i);
 if((tree_find(t,(const void*)aux))==TRUE){
   fprintf(stdout,"The data %d is inside the Tree\n",i);
 }
 else{
   fprintf(stdout,"The data %d is NOT inside the Tree\n",i);
 }
 /* Free everything*/
 node_destroy(aux);
 mainCleanUp(t, pf);
 return EXIT_SUCCESS;
}
