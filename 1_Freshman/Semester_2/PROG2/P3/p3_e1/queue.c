/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "types.h"
#define MAXQUEUE 1064
struct _Queue {

 void* items [MAXQUEUE];
 int front;
 int rear;
 destroy_element_function_type f1;
 copy_element_function_type f2;
 print_element_function_type f3;


};

/**------------------------------------------------------------------
Initializes the queue: reserves memory for it and initializes all its elements to NULL.
------------------------------------------------------------------*/
Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3)
{
    Queue *q=NULL;
    int i;
    if(!f1 || !f2 || !f3) return NULL;
    q=(Queue *)malloc(sizeof(Queue));
    if(!q){return NULL;}
    q->front=0;
    q->rear=0;
    for(i=0;i<MAXQUEUE;i++)
    {
        q->items[i]=NULL;
    }
    q->f1=f1;
    q->f2=f2;
    q->f3=f3;
    return q;

}
/**------------------------------------------------------------------
Free the queue, freeing all its elements.
------------------------------------------------------------------*/
void queue_destroy(Queue *q)
{
    int i;
    if(q!=NULL)
    {
        i=q->front;
        while(i!=q->rear)
        {
            q->f1(q->items[i]);
            q->items[i]=NULL;
            i=(i+1)%MAXQUEUE;
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
    if(q->front==q->rear)
    {
        return TRUE;
    }return FALSE;
}
/**------------------------------------------------------------------
Checks if the queue is full.
------------------------------------------------------------------*/
_Bool queue_isFull(const Queue* q)
{
    if(!q){return TRUE;}
    if(q->front==(q->rear+1)%MAXQUEUE)
    {
        return TRUE;
    }return FALSE;
}
/**------------------------------------------------------------------
Inserts a new node in the queue, reserving new memory for it and making a copy of the received element.
------------------------------------------------------------------*/
Queue* queue_insert(Queue *q, const void* pElem)
{
  void *paux=NULL;
  if(q==NULL||pElem==NULL||queue_isFull(q)==TRUE){return NULL;}
  paux=q->f2(pElem);
  if(paux==NULL){return NULL;}
  q->items[q->rear]=paux;
  q->rear=(q->rear+1)%MAXQUEUE;
  return q;

}
/**------------------------------------------------------------------
Extracts an element from the queue. Returns the pointer directly to the element (does not make a copy).
------------------------------------------------------------------*/
void * queue_extract(Queue *q)
{
  void *paux=NULL;
  if(q==NULL||queue_isEmpty(q)==TRUE){return NULL;}
  paux=q->items[q->front];
  q->items[q->front]=NULL;
  q->front=(q->front+1)%MAXQUEUE;
  return paux;

}
/**------------------------------------------------------------------
Returns the number of queue elements.
------------------------------------------------------------------*/
int queue_size(const Queue *q)
{
    int dif;
    if(!q)return ERROR;
    if(q->front>q->rear)
    {
        dif=((q->front)-(q->rear))%MAXQUEUE;
        return dif;
    }
    else if(q->front<q->rear){
      dif=((q->rear)-(q->front))%MAXQUEUE;
      return dif;
    }
    return ERROR;
}
/**------------------------------------------------------------------
Prints all the queue, returning the number of written characters.
------------------------------------------------------------------*/
int queue_print(FILE *pf, const Queue *q)
{
  int i;
  int var=0;
  int size=-1;
  if(!pf||!q){return ERROR;}
  size=queue_size(q);
  if(size==ERROR){
    var+=fprintf(pf,"Queue empty.\n");
    if(!var)return ERROR;
  }
  else{
  var+=fprintf(pf,"Queue with %d elements:\n",size);
  for(i=q->front;i!=q->rear;i=(i+1)%MAXQUEUE)
  {
      var+=q->f3(pf,q->items[i]);
      if(!var)return ERROR;
      var+=fprintf(pf,"\n");
  }}
  return var;
}
