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
BOOL player_get_object(Player* player);
STATUS player_print(Player* player);

#endif
