/**
 * @brief It implements the inventory module,it keeps the drop objects
 *
 * @file inventory.c
 * @version 1.0
 * @date 28-03-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "types.h"
#include "inventory.h"
/**
 * @brief defines structure of bag
 */
struct _Bag{
/**
 * @brief defines set
 */
Set *set;
/**
 * @brief defines max objects
 */
int max_obj;
};

/*CREATE*/

Bag* bag_create(){
Bag* newBag=NULL;

newBag=(Bag*)malloc(sizeof(Bag));

newBag->set=set_create();
newBag->max_obj=-1;

return newBag;

}

/*DESTROY*/

void bag_destroy(Bag *bag){
if (bag==NULL) return;

set_destroy(bag->set);
free(bag);

}

/*ADD OBJ*/

STATUS bag_addObj(Bag* bag, Id obj){
if (bag==NULL||obj==NO_ID||bag_numObj(bag)==bag_getMaxObj(bag)) return ERROR;

return set_id_add(bag->set, obj);

}

/*REMOVE OBJ*/

STATUS bag_removeObj(Bag* bag, Id id) {
if (bag==NULL||id==NO_ID) return ERROR;

return set_remov_id(bag->set, id);

}

/*CHECK OBJ*/

BOOL bag_checkObj(Bag* bag, int pos) {
if (bag==NULL||pos<0) return FALSE;

if (set_get_id(bag->set, pos)!=NO_ID) return TRUE;

return FALSE;

}

/*NUMBER OF ALLOCATED OBJECTS*/

int bag_numObj(Bag* bag) {
if (bag==NULL) return -1;

return set_getNum(bag->set);

}

/*SET MAX_OBJ*/

STATUS bag_setMaxObj(Bag* bag, int max_obj){
if (bag==NULL||max_obj<0) return ERROR;

bag->max_obj=max_obj;

return OK;

}

/* GET OBJECT */
Id bag_getObject(Bag *bag, int position){
  if(!bag || position < 0) return NO_ID;
  return set_get_id(bag->set, position);
}


STATUS bag_setObject(Bag* bag, Id id, int position) {
if (bag==NULL||id==NO_ID||position<0) return ERROR;
set_set_id(bag->set, id, position);
return OK;


}

/*GET (MAX_OBJ)*/

int bag_getMaxObj(Bag* bag) {
if (bag==NULL) return -1;

return bag->max_obj;

}

/*PRINT*/

void bag_print(Bag* bag){

printf("\nBAG CONTENTS\n");
set_print(bag->set);

printf("\nBAG MAX OBJECTS\n");
printf("%d", bag_getMaxObj(bag));

printf("\n");

}

