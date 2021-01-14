/**
 * @brief It defines the module of die
 *
 * @file die.c
 * @version 1.0
 * @date 28-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "die.h"

/*Structure of an die*/
struct _Die{
  Id id;
  int number;
};


/*Function to create a Die, in case of error it returns ERROR*/
Die* die_create(Id id) {
Die *n=NULL;
if(id==NO_ID) return NULL;
if(!(n=(Die*)malloc(sizeof(Die)))) return NULL;
n->number=0;
n->id=id;
srand(time(NULL));
return n;
}

/*Function to destroy a Die, in case of error it returns ERROR*/
void die_destroy(Die *die){
if(!die) return;
free(die);
}

/*Function to roll a Die, in case of error it returns ERROR*/
int die_roll(Die *die){
die->number=((rand()%num_die)+1);
return die->number;
}

int die_get_value(Die *die){
  return die->number;
}

