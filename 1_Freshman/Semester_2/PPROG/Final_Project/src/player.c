/** 
 * @brief It implements the player
 * 
 * @file player.c
 * @author Julia Simon y Miguel Rodriguez
 * @version 1.0 
 * @date 14-02-2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/player.h"

/**
* @brief Estructura del jugador
*/
struct _Player {
	Id id;                    /*!< Identificador del jugador */
	char name[WORD_SIZE];     /*!< Nombre del jugador */
	Id space;                 /*!< ID del espacio donde se encuentra */
	Inventory * inventory;    /*!< Inventario del jugador*/
};



Player* player_create(Id id) {

	Player *newPlayer = NULL;
	

	if (id == NO_ID)
		return NULL;

	newPlayer = (Player *) malloc(sizeof (Player));

	if (newPlayer == NULL) {
		return NULL;
	}
	newPlayer->id = id;

	bzero(newPlayer->name,WORD_SIZE);
	newPlayer->space = NO_ID;

	newPlayer->inventory = inventory_create();

	return newPlayer;
}




STATUS player_destroy(Player* player) {
  	if (!player) {
		return ERROR;
  	}

  	inventory_destroy(player->inventory);
  
  	free(player);
  	

  	return OK;
}


STATUS player_set_name(Player* player, char* name) {
  	if (!player || !name) {
		return ERROR;
  	}

  	if (!strcpy(player->name, name)) {
		return ERROR;
  	}

  	return OK;
}




STATUS player_set_space(Player* player, Id id) {
  	if (!player || id == NO_ID) {
		return ERROR;
  	}
  	player->space = id;
  	return OK;
}




STATUS player_set_object(Player* player, Id id) {
	if (!player) {
		return ERROR;
	}

	if(inventory_add_object(player->inventory, id)==ERROR)
		return ERROR;
	return OK;
}

STATUS player_set_inventory(Player* player, Inventory* inventorio){
	if (!player || !inventorio) {
		return ERROR;
	}
	player->inventory = inventorio;
	return OK;
}



const char * player_get_name(Player* player) {
  	if (!player) {
		return NULL;
  	}
  	return player->name;
}


Id player_get_id(Player* player) {
	if (!player) {
		return NO_ID;
	}
	return player->id;
}


Id player_get_space(Player* player) {
  	if (!player) {
		return NO_ID;
  	}
  	return player->space;
}


BOOL player_get_object(Player* player,Id id){

	if (!player) {
		return FALSE;
	}

	return inventory_object_exist(player->inventory, id);
	
}

Set* player_get_objects(Player* player){
	if (!player)
		return NULL;

	return inventory_get_objects(player->inventory);
}

Inventory* player_get_inventory(Player* player){
	if (!player)
		return NULL;

	return player->inventory;
}

size_t player_get_size(){
	return sizeof(struct _Player);
}

STATUS player_del_objects(Player* player, Id id){
	if (!player) {
		return ERROR;
	}
	
  	if(inventory_remove_object(player->inventory, id)==ERROR){
  		return ERROR;
 	}
	return OK;

}



STATUS player_print(Player* player) {
	Id idaux = NO_ID;

 	if (!player){
        return ERROR;
 	}

    idaux = player_get_space(player);

    if (NO_ID != idaux)
    {
        fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld) \n", player->id, player->name, player->space);
		inventory_print(stdout, player->inventory);
    }

    else if (NO_ID == idaux)
    {
        fprintf(stdout, "--> Player (Id: %ld; Name: %s; No location) \n",
		player->id, player->name);
		inventory_print(stdout,player->inventory);
    }

	return OK;
}
