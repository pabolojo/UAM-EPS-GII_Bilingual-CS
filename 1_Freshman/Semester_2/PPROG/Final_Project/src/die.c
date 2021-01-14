/** 
 * @brief It implements the die interpreter
 * 
 * @file die.c
 * @author Julia Simon 
 * @version 1.3
 * @date 20-02-2018
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/die.h"

/**
* @brief Estructura del die
*/
struct _Die {
	Id id;        /*!< Identificador del dado*/
	int last_num; /*!< Ultimo número del dado*/
};

Die* die_create(Id id) {

  Die *newDie = NULL;

  if (id == NO_ID)
    return NULL;

  newDie = (Die *) malloc(sizeof (Die));

  if (newDie == NULL) {
    return NULL;
  }
  newDie->id = id;
  newDie->last_num = -1;

  return newDie;
}

STATUS die_destroy(Die* die) {
  if (!die) {
    return ERROR;
  }

  free(die);
  die = NULL;

  return OK;
}

Id die_get_id(Die* die){
	if(!die){
		return NO_ID;
	}
	return die->id;
}

size_t die_get_size(){
	return sizeof(struct _Die);
}

STATUS die_roll(Die* dado, int sup, int inf){

	int num = -1;

	if(!dado){
		return ERROR;
	}
	if(inf < 0 || sup < 0){
		fprintf(stderr, "\n El límite inferior y superior debe ser un número mayor que 0.\n");
		return ERROR;
	} else if(sup < inf){
		fprintf(stderr, "\n El límite superior debe ser mayor que el límite inferior.\n");
		return ERROR;
	}
	
	num = rand()%(sup-inf+1)+inf;
	
	dado->last_num = num;
	return OK;	
}


STATUS die_print(Die* die) {

	if (!die) {
    	return ERROR;
  	}

  	fprintf(stdout, "--> Die (Id: %ld)\n", die->id);
	
	fprintf(stdout,"---> Last Num: %d.\n", die->last_num);

	return OK;
}

int die_get_lastValue(Die* die){
	if(!die)
		return -1;
	return die->last_num;
}




