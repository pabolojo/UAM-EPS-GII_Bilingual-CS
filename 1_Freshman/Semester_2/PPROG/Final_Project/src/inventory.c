/** 
 * @brief It implements the inventory
 * 
 * @file inventory.c
 * @author Cristina Soria
 * @version 1.0 
 * @date 13-03-2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/inventory.h"

#define MAX_OBJECTS_INVENTORY 10
/**
* @brief Estructura del inventory
*/
struct _Inventory{
	Set* objects;      /*!< Set de objetos    */
	int max_objects;   /*!< Maximo de objetos */  
};


Inventory * inventory_create(){

	Inventory *newInventory;

	newInventory =(Inventory*) malloc(sizeof(Inventory));

	if (newInventory == NULL) {
		return NULL;
	}

	newInventory->objects = set_create();
	newInventory->max_objects = MAX_OBJECTS_INVENTORY;

	return newInventory;
}


STATUS inventory_destroy(Inventory *inventory){

	if (inventory == NULL){
		return ERROR;
	}

	set_destroy(inventory->objects);
	free(inventory);

	return OK;
}


STATUS inventory_set_dimension(Inventory *inventory, int i){
	if (inventory==NULL || i < 0){
		return ERROR;
	}

	inventory->max_objects = i;

	return OK;
}

STATUS inventory_set_objects(Inventory *inventory, Set* objects){
	if (inventory==NULL || !objects){
		return ERROR;
	}
	inventory->objects = objects;
	return OK;
}

Id inventory_get_id(Inventory *inventory, int pos_id){
	if (inventory==NULL || pos_id < 0 || pos_id >= inventory->max_objects){
		return NO_ID;
	}

	return set_get_Id(inventory->objects, pos_id);
}


int inventory_get_number_objects(Inventory *inventory){
	if (inventory==NULL){
		return -1;
	}

	return set_get_nId(inventory->objects);
}


Set* inventory_get_objects(Inventory* inventory){
	if (!inventory){
		return NULL;
	}
	return inventory->objects;
}

size_t inventory_get_size(){
	return sizeof(struct _Inventory);
}

STATUS inventory_add_object(Inventory *inventory, Id id){
	int object_number=0;
	int max_objects=0;

	if (inventory==NULL || id == NO_ID){
		return ERROR;
	}

	max_objects = inventory->max_objects;
	object_number = set_get_nId(inventory->objects);

	if (object_number == max_objects){
		return ERROR;
	}

	return set_add(inventory->objects, id);
}


STATUS inventory_remove_object(Inventory *inventory, Id id){
	if (inventory==NULL || id == NO_ID){
		return ERROR;
	}

	return set_del(inventory->objects, id);
}


BOOL inventory_object_exist(Inventory *inventory, Id id){
	int i=0;
	if (inventory==NULL || id == NO_ID)
		return FALSE;


	for(i=0;i<set_get_nId(inventory->objects);i++){
		if(set_get_Id(inventory->objects,i)==id)
			return TRUE;		
	}
	
	return FALSE;

}


STATUS inventory_print(FILE* pf, Inventory *inventory){
	if (pf==NULL || inventory==NULL){
		return ERROR;
	}

	set_print( inventory->objects);
	fprintf(pf, "\n");
	fprintf(pf, "--> Limite inventario: %d \n", inventory->max_objects);

	return OK;
}




