/**
 * @brief It defines the module SET
 *
 * @file set.c
 * @version 1.0
 * @date 21-02-2019
 * @copyright GNU Public License
 */
/*libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "object.h"
#include "game.h"
#include "space.h"
#include "types.h"
#include "set.h"

/*global variables*/
extern int errno;

/*Structure of set with 2 variables*/
struct _Set {
  Id ids[MAX_IDs_SET];
  int card;
};
/*Function begin set*/
Set* set_create(){
int i=0;
Set *n_set=NULL;
if(!(n_set=(Set*)malloc(sizeof(Set)))){
    return NULL;
	}
for(i=0;i<MAX_IDs_SET;i++){
	n_set->ids[i]=NO_ID;
}
n_set->card=0;
return n_set;
}
/*NO TENDRIA QUE SER DE TIPO VOID? NO RETURNEA NADA SI NO*/
/*it frees the set*/
STATUS set_destroy(Set *aux){
	if(!aux) return ERROR;
	free(aux);
  return OK;
}
/*it set id */
BOOL set_id_in(Set *aux,Id var){
	int i=0;
	if(!aux || !var) return FALSE;
	for(i=0;i<aux->card && aux->ids[i]!=var;i++);
	if(i<aux->card) return TRUE;
	return FALSE;
}
/*HABRA QUE METER EL NUEVO ID NO?*/
/*func adds id*/
STATUS set_id_add(Set *aux,Id new){
	if(!aux || !new) return ERROR;
	if(set_id_in(aux,new)) return OK;
	if(aux->card==MAX_IDs_SET) return ERROR;
  aux->ids[aux->card]=new;
  aux->card++;
  return OK;/*??*/
}
/*ACABA PONINENDO TODOS A NO_ID A PARTIR DEL QUE SE QUIERE ELIMINAR*/
/*func removes id*/
STATUS set_remov_id(Set *aux,Id rmv){
	int i=0,j=0;
	if(!aux || !rmv) return ERROR;
	if(aux->card==0) return ERROR;
	for(i=0;i<aux->card && aux->ids[i]!=rmv;i++);
	if(i<aux->card){
		for(j=i+1;j<aux->card;i++,j++){
			aux->ids[i]=aux->ids[j];
		}
    aux->card--;
    aux->ids[aux->card]=NO_ID;
	}
  return OK;
}
/*NO SERIA POS>=MAX_IDS_SET?*/
/*func gets id*/
Id set_get_id(Set *aux,int pos){
	if(!aux || pos<0 ||pos>=MAX_IDs_SET) return NO_ID;
	return aux->ids[pos];
}
/*func prints id*/
STATUS set_print(Set *aux){
	int i=0;
	if(!aux) return ERROR;
	fprintf(stdout,"Set %d\n",aux->card);
	for(i=0;i<aux->card;i++){
		fprintf(stdout,"id [%d]: %ld\n",i,aux->ids[i]);}
  return OK;
}

