#include "functions.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#define NAME_L 255

void destroy_string_function(void* e){
  free((char *)e);
}

void * copy_string_function(const void* e){
  char *aux;
  if(!e) return NULL;
  aux=(char*)malloc((1+strlen((char*)e))*sizeof(char));
  strcpy(aux,(char*)e);
  return aux;
}

int print_string_function(FILE * f, const void* e){
  if(!f || !e) return -1;
  return fprintf(f, "%s\n", (char*)e);
}

int cmp_string_function(const void* e1, const void* e2){
  if(!e1 || !e2) return -1;
  return strcmp((char*)e1,(char*)e2);
}
