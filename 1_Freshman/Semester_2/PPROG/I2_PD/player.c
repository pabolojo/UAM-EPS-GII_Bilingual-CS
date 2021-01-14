/**
 * @brief It defines the header of the module player
 *
 * @file player.c
 * @version 2.0
 * @date 15-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"
#include "game.h"

/*Structure of a Player*/
struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Id object;
};

/*Function to create a player, in case of error it returns NULL*/
Player* player_create(Id id) {

  Player *newPlayer = NULL;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *) malloc(sizeof (Player)); /*if allocation memory of player is ok, it is set the id, name location of the newplayer*/

  if (newPlayer == NULL) {
    return NULL;
  }
  newPlayer->id = id;

  newPlayer->name[0] = '\0';

  newPlayer->location = NO_ID;

  newPlayer->object = NO_ID;

  return newPlayer;
}

/*Function to destroy an player, in case of error it returns ERROR*/
STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  player = NULL;

  return OK;
}

/*Function to set the name of an object, in case of error it returns ERROR*/
STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

/*Function to set the ID of an player, in case of error it returns ERROR*/
STATUS player_set_location(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->location = id;
  return OK;
}

/*Function to set the location of a player, in case of error it returns ERROR*/
STATUS player_set_object(Player* player, Id object) {
  if (!player) {
    return ERROR;
  }
  player->object = object;
  return OK;
}

/*Function to get the name of a player, in case of error it returns ERROR*/
const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}
/*Function to get the id of a player, in case of error it returns ERROR*/
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}
/*Function to get the location of a player, in case of error it returns ERROR*/
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}


Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;
}
/*printf player with all its characteristics, name location id, south,north..., in case of error it returns ERROR*/
STATUS player_print(Player* player) {
  Id idaux = NO_ID;

  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  idaux = player_get_location(player);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }


  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }

  return OK;
}

