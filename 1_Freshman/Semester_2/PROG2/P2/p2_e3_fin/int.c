#include "int.h"

void * int_copy(const void * src){
  int *aux=NULL;
  if(!src) return NULL;
  aux=(int*)malloc(sizeof(int));
  if(!aux)return NULL;
  *aux=*((const int*) src);
  return (void*)aux;
}

int int_print(FILE * pf, const void *a){
  if(!pf || !a) return -1;
  return fprintf(pf, "[%d]",*((const int *) a));
}

void int_destroy(void * src){
  free((int*) src);
}
