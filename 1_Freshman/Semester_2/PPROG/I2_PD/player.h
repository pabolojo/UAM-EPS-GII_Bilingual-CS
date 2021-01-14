/**
 * @brief It defines the header of the module player
 *
 * @file player.h
 * @version 1.0
 * @date 15-02-2019
 * @copyright GNU Public License
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"


typedef struct _Player Player;

Player* player_create(Id id);
STATUS player_destroy(Player* player);
STATUS player_set_name(Player* player, char* name);
STATUS player_set_location(Player* player, Id id);
STATUS player_set_object(Player* player, Id value);
const char * player_get_name(Player* player);
Id player_get_id(Player* player);
Id player_get_location(Player* player);
Id player_get_object(Player* player);
STATUS player_print(Player* player);

#endif

