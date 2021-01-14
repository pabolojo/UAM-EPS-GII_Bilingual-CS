/** 
 * @brief It implements the set
 * 
 * @file set.c
 * @author Julia Simon y Miguel Rodriguez
 * @version 1.0 
 * @date 14-02-2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/set.h"

/**
* @brief Estructura del set
*/
struct _Set {
	Id id[MAX_ID];  /*!< identificador del objeto */
	int nId;        /*!< numero de ids            */
};


Set* set_create() {

	Set *newSet = NULL;
	int i=0;

	newSet = (Set *) malloc(sizeof (Set));

	if (newSet == NULL)
		return NULL;
	
	for(i=0; i<MAX_ID;i++){
		newSet->id[i] = 0;
	}
	newSet->nId = 0;

	return newSet;
}


STATUS set_destroy(Set* set) {

	if (!set)
		return ERROR;
		
	free(set);
	set = NULL;

	return OK;
}

Id set_get_Id(Set * set, int i){
		
	if(!set || i > set->nId || i < 0)
		return NO_ID;
				
	return set->id[i];
}


int set_get_nId(Set* set){
		
	if(!set)
		return -1;
		
	return set->nId;
}

size_t set_get_size(){
    return sizeof(struct _Set);
}

STATUS set_add(Set* set, Id id){
		
	if(set == NULL || id == NO_ID)
		return ERROR;
				
	set->id[set->nId] = id;
	set->nId++;
		
	return OK;
}


STATUS set_del(Set* set, Id id){
		
	int i = 0, j = 0;
		
	if(set == NULL || id == NO_ID)
		return ERROR;

	for(i=0; i<set->nId; i++){
		if(set->id[i] == id){
			for(j=i; j<set->nId; j++){
				set->id[j] = set->id[j+1];
			}
			set->nId--;
		}
	}    
		
	return OK;
}


STATUS set_print(Set* set) {

	int i = 0;

	if (!set)
		return ERROR;
			
	fprintf(stdout, "--> set (nId: %d)\n", set->nId);
		
	if(set->nId == 0)
		return OK;
				
	fprintf(stdout, "--> set (Id: ");
		
	for(i=0; i<set->nId; i++)
		fprintf(stdout, "%ld ",set->id[i]);
		
	fprintf(stdout, ")\n");
	return OK;
}




