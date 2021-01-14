/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "queuel.h"
#define MAXQUEUE 1064

struct _Queue {
    List *plist;

    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

/**------------------------------------------------------------------
Initializes the queue: reserves memory for it and initializes all its elements to NULL.
------------------------------------------------------------------*/
Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3)
{
    Queue *q=NULL;
    if(!f1 || !f2 || !f3) return NULL;
    q=(Queue *)malloc(sizeof(Queue));
    if(!q){return NULL;}
    q->plist=NULL;
    q->plist=list_ini(f1,f2,f3,NULL);
    if(!q->plist){
      free(q);
      return NULL;
    }
    q->destroy_element_function=f1;
    q->copy_element_function=f2;
    q->print_element_function=f3;
    return q;

}
/**------------------------------------------------------------------
Free the queue, freeing all its elements.
------------------------------------------------------------------*/
void queue_destroy(Queue *q)
{
    if(q!=NULL)
    {
        if(q->plist){
          list_destroy(q->plist);
        }
        free(q);
    }
}
/**------------------------------------------------------------------
Checks if the queue is empty.
------------------------------------------------------------------*/
_Bool queue_isEmpty(const Queue *q)
{
if(!q){return TRUE;}
return list_isEmpty(q->plist);
}
/**------------------------------------------------------------------
Checks if the queue is full.
------------------------------------------------------------------*/
_Bool queue_isFull(const Queue* q)
{
    if(!q || !q->plist){return TRUE;}
    return FALSE;
}
/**------------------------------------------------------------------
Inserts a new node in the queue, reserving new memory for it and making a copy of the received element.
------------------------------------------------------------------*/
Queue* queue_insert(Queue *q, const void* pElem)
{
  if(q==NULL||pElem==NULL||queue_isFull(q)==TRUE){return NULL;}
  if(list_insertLast(q->plist,pElem)==ERROR){
    return NULL;
  }
  return q;

}
/**------------------------------------------------------------------
Extracts an element from the queue. Returns the pointer directly to the element (does not make a copy).
------------------------------------------------------------------*/
void * queue_extract(Queue *q)
{
  void *paux=NULL;
  if(q==NULL||queue_isEmpty(q)==TRUE){return NULL;}
  paux=list_extractFirst(q->plist);
  return paux;

}
/**------------------------------------------------------------------
Returns the number of queue elements.
------------------------------------------------------------------*/
int queue_size(const Queue *q)
{
    int dif;
    if(!q)return 0;
    dif=list_size(q->plist);
    return dif;
}
/**------------------------------------------------------------------
Prints all the queue, returning the number of written characters.
------------------------------------------------------------------*/
int queue_print(FILE *pf, const Queue *q)
{
  int var=0;
  if(!pf||!q){return ERROR;}
  var=list_print(stdout,q->plist);
  return var;
}
