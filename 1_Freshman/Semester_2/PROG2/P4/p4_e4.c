#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "functions.h"
#include "types.h"
#include <errno.h>
extern int errno;

#define MAX_LINE 350
#define MAX 300

char* read_string_from_file(FILE* f_in){
    char* str;
    char chararr[255];

    fscanf(f_in, "%s\n", chararr);
    str=(char*)malloc((1+strlen(chararr))*sizeof(char));
    strcpy(str,chararr);

    return str;
}

void mainCleanUp (Tree *t, FILE *pf) {
 if (t) tree_free(t);
 if (pf) fclose (pf);
}
int main(int argc, char** argv) {
 FILE *pf=NULL;
 Tree *t=NULL;
 char *str=NULL;
 Status s;
 if (argc != 2) {
 fprintf(stderr, " Error: Enter as argument the name of the file with the strings.\n");
 return EXIT_FAILURE;
 }
 pf = fopen(argv[1], "r");
 if (pf==NULL){
 fprintf (stderr, " File opening error: %s\n", strerror(errno));
 return EXIT_FAILURE;
 }
 if(!(t=tree_ini(destroy_string_function,copy_string_function,print_string_function,cmp_string_function))){
   fprintf(stderr, " Error creating tree\n");
   mainCleanUp (t, pf);
   return EXIT_FAILURE;
 }

 while(!feof(pf)){
   str=read_string_from_file(pf);
   if(!str){
     fprintf(stderr, " Error setting info of auxialiary elements\n");
		 free(str);
     mainCleanUp (t, pf);
     return EXIT_FAILURE;
   }
   s=tree_insert(t,str);
   if(s==ERROR){
     fprintf(stderr, " Error inserting element in tree\n");
     free(str);
     mainCleanUp(t, pf);
     return EXIT_FAILURE;
   }
	 free(str);
 }

 fprintf(stdout,"Number of nodes: %d\n",tree_numNodes(t));
 fprintf(stdout,"Depth: %d\n",tree_depth(t));

 if(tree_print(stdout,t)==ERROR){
   fprintf(stderr, " Error printing tree\n");
   mainCleanUp(t, pf);
   return EXIT_FAILURE;
 }
 fprintf(stdout,"Enter a string: ");
 str=(char*)malloc(255*sizeof(char));
 fscanf(stdin,"%s",str);
 fprintf(stdout,"String entered: %s\n",str);
 if((tree_find(t,(const void*)str))==TRUE){
   fprintf(stdout,"The data %s is inside the Tree\n",str);
 }
 else{
   fprintf(stdout,"The data %s is NOT inside the Tree\n",str);
 }
 /* Free everything*/
 free(str);
 mainCleanUp(t, pf);
 return EXIT_SUCCESS;
}
