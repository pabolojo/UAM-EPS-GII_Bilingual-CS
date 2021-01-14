#include "types.h"
#include "list.h"
#include "integer.h"

typedef struct _NodeList { /* Private EdD, necessary to implement list */
 void* info;
 struct _NodeList *next;
} NodeList; /* Private NodeList type */

struct _List {
 NodeList *last; /* The LEC points to the last node and the last to the
first */
 destroy_element_function_type destroy_element_function;
 copy_element_function_type copy_element_function;
 print_element_function_type print_element_function;
 cmp_element_function_type cmp_element_function;
};

NodeList* nodelist_ini(){
    NodeList *pn;

    if ((pn = (NodeList*) malloc(sizeof(NodeList))) ==NULL)
        return NULL;

    pn->info = pn->next = NULL;

    return pn;
}

void nodelist_free(NodeList *pn, destroy_element_function_type f){
    if (pn != NULL){
        if (pn->info != NULL)
            f(pn->info);
        free(pn);
    }
}

List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3,
cmp_element_function_type f4){
  List *pl = NULL;
  if(!f1 || !f2 || !f3 || !f4) return NULL;
  pl = (List *)malloc(sizeof(List));
  if (pl == NULL) {
    return NULL;
  }
  pl->last = NULL;
  pl->destroy_element_function=f1;
  pl->copy_element_function=f2;
  pl->print_element_function=f3;
  pl->cmp_element_function=f4;
  return pl;
}

void list_destroy (List* list){
  if (list == NULL) {
    return;
  }
  while (list_isEmpty(list) == FALSE) {
    list->destroy_element_function(list_extractFirst(list));
  }
  free(list);
}

Bool list_isEmpty (const List* list){
  if (list == NULL) {
    return TRUE;
  }
  if (list->last == NULL) {
    return TRUE;
  }
  return FALSE;
}

Status list_insertFirst (List* list, const void *pelem){
  void *eleaux=NULL;
  NodeList *nodeaux=NULL;
  if (list == NULL || pelem == NULL) return ERROR;
  nodeaux=nodelist_ini();
  if(!nodeaux) return ERROR;
  eleaux = list->copy_element_function(pelem);
  if (eleaux == NULL) {
    nodelist_free(nodeaux,list->destroy_element_function);
    return ERROR;
  }
  nodeaux->info=eleaux;
  if(list_isEmpty(list)==TRUE){
    nodeaux->next=nodeaux;
    list->last=nodeaux;
  }
  else{
    nodeaux->next = list->last->next;
    list->last->next = nodeaux;
  }
  return OK;
}

Status list_insertLast (List* list, const void *pelem){
  void *eleaux=NULL;
  NodeList *nodeaux=NULL;
  if (list == NULL || pelem == NULL) return ERROR;
  nodeaux=nodelist_ini();
  if(!nodeaux) return ERROR;
  eleaux = (void *)list->copy_element_function(pelem);
  if (eleaux == NULL) {
    nodelist_free(nodeaux,list->destroy_element_function);
    return ERROR;
  }

  nodeaux->info=eleaux;
  if(list_isEmpty(list)==TRUE){
    nodeaux->next=nodeaux;
    list->last=nodeaux;
  }
  else{
    nodeaux->next = list->last->next;
    list->last->next = nodeaux;
    list->last = nodeaux;
  }
  return OK;
}

int list_size (const List* list){
  NodeList *aux=NULL;
  int i=1;
  if(!list) return 0;
  if(!list->last) return 0;
  aux=list->last->next;
  while(aux!=list->last){
    i++;
    aux=aux->next;
  }
  return i;
}

const void* list_get (const List* list, int index){
  NodeList *aux=NULL;
  int i=0;
  if(!list || index>list_size(list) || index<0 || list_isEmpty(list)==TRUE) return NULL;
  aux=list->last->next;
  while(i!=index && aux!=list->last->next){
    i++;
    aux=aux->next;
  }
  if(aux==list->last->next) return NULL;

  return (const void*)list->copy_element_function(aux->info);
}

int list_print (FILE *fd, const List* list){
  int i=0;
  NodeList *aux=NULL;
  if(!fd || !list) return 0;
  if(list_isEmpty(list)==TRUE){
    i+=fprintf(fd,"Queue empty.\n");
  }
  else{
  i+=fprintf(fd,"Size: %d\n",list_size(list));
  aux=list->last->next;
  i+=list->print_element_function(fd,aux->info);
  while(aux!=list->last){
    aux=aux->next;
    i+=list->print_element_function(fd,aux->info);
  }}
  return i;
}

Status list_insertInOrder (List *list, const void *pelem){
  void *eleaux=NULL;
  NodeList *nodeaux=NULL;
  NodeList *aux=NULL;
  if (list == NULL || pelem == NULL) return ERROR;
  nodeaux=nodelist_ini();
  if(!nodeaux) return ERROR;
  eleaux = (void *)list->copy_element_function(pelem);
  if (eleaux == NULL) {
    nodelist_free(nodeaux,list->destroy_element_function);
    return ERROR;
  }
  nodeaux->info=eleaux;
  if(list_isEmpty(list)==TRUE){
    nodeaux->next=nodeaux;
    list->last=nodeaux;
  }
  else{
    aux=list->last->next;
    if(list->cmp_element_function(aux->info,nodeaux->info)>0){
      nodelist_free(nodeaux,list->destroy_element_function);
      if((list_insertFirst(list,pelem))==ERROR){
        return ERROR;
      }
      }
    else{
        while(aux!=list->last && list->cmp_element_function(aux->info,nodeaux->info)>0){
          aux=aux->next;
        }
        if(aux==list->last){
          list->last=nodeaux;
        }
        nodeaux->next=aux->next;
        aux->next=nodeaux;
      }
  }
  return OK;
}

void * list_extractFirst (List* list){
  void * eleaux=NULL;
  NodeList *nodeaux=NULL;
  if(!list) return NULL;
  if(list_isEmpty(list)==TRUE) return NULL;
  eleaux=list->last->next->info;
  list->last->next->info=NULL;
  if(list->last->next==list->last){
    nodelist_free(list->last,list->destroy_element_function);
    list->last=NULL;
  }
  else{
    nodeaux=list->last->next;
    list->last->next=nodeaux->next;
    nodelist_free(nodeaux,list->destroy_element_function);
  }
  return eleaux;
}

void * list_extractLast (List* list){
  void * eleaux=NULL;
  NodeList *nodeaux=NULL;
  if(!list) return NULL;
  if(list_isEmpty(list)==TRUE) return NULL;
  eleaux=list->last->info;
  list->last->info=NULL;
  if(list->last->next==list->last){
    nodelist_free(list->last,list->destroy_element_function);
    list->last=NULL;
    return eleaux;
  }
  for(nodeaux=list->last;nodeaux->next!=list->last;nodeaux=nodeaux->next){}
  nodeaux->next=list->last->next;
  nodelist_free(list->last,list->destroy_element_function);
  list->last=nodeaux;
  return eleaux;
}
