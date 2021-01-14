#include "tree.h"
#include "integer.h"
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
 void *aux=NULL;
 Status s;
 if (argc != 2) {
 fprintf(stderr, " Error: Enter as argument the name of the file with the nodes.\n");
 return EXIT_FAILURE;
 }
 pf = fopen(argv[1], "r");
 if (pf==NULL){
 fprintf (stderr, " File opening error: %s\n", strerror(errno));
 return EXIT_FAILURE;
 }
 if(!(t=tree_ini(int_destroy,int_copy,int_print,int_cmp))){
   fprintf(stderr, " Error creating tree\n");
   mainCleanUp (t, pf);
   return EXIT_FAILURE;
 }
 aux=int_ini();
 if(!aux){
   fprintf(stderr, " Error creating auxialiary elements\n");
   mainCleanUp (t, pf);
   return EXIT_FAILURE;
 }
 while(fscanf(pf, "%d\n", &i) == 1){
   aux=int_setInfo(aux,i);
   if(!aux){
     fprintf(stderr, " Error setting info of auxialiary elements\n");
     int_destroy(aux);
     mainCleanUp (t, pf);
     return EXIT_FAILURE;
   }
   s=tree_insert(t,aux);
   if(s==ERROR){
     fprintf(stderr, " Error inserting element in tree\n");
     int_destroy(aux);
     mainCleanUp(t, pf);
     return EXIT_FAILURE;
   }
 }
 int_destroy(aux);
 fprintf(stdout,"Number of nodes: %d\n",tree_numNodes(t));
 fprintf(stdout,"Depth: %d\n",tree_depth(t));
 fprintf(stdout,"Enter a number: ");
 scanf("%d",&i);
 fprintf(stdout,"Number entered: %d\n",i);
 if((tree_find(t,(const void*)&i))==TRUE){
   fprintf(stdout,"The data %d is inside the Tree\n",i);
 }
 else{
   fprintf(stdout,"The data %d is NOT inside the Tree\n",i);
 }
 /* Free everything*/
 mainCleanUp(t, pf);
 return EXIT_SUCCESS;
}
