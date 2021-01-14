#include <stdlib.h>
#include <stdio.h>
#include "integer.h"

void *int_ini ()
{
    int *num=NULL;
    num=(int *)malloc (sizeof(int));
    return (void *)num;
}
void int_destroy(void* e)
{
    free(e);
}

int int_print(FILE * f, const void* e)
{
   if(!f || !e) return -1;
  return fprintf(f, "[%d]\n",*((const int *) e));

}
int int_cmp(const void* e1, const void* e2)
{
    if(!e1||!e2)return ERROR;
    if(*(const int*)e1==*(const int*)e2){return 0;}
    else if(*(const int*)e1>=*(const int*)e2){
      return 1;
    }
    else
    {
    return -2;
    }
}



void * int_setInfo (void *e, int v)
{
  int *aux=NULL;
  aux=(int *)e;
  if(!e||!v)return NULL;
  *(aux)=v;
  return (void *)aux;
}

void * int_copy(const void* e)
{
    if(!e)return NULL;
    void *aux=NULL;
    aux=int_ini();
    if(!aux) return NULL;
    aux=int_setInfo(aux,*((const int*)e));
    return aux;


}
