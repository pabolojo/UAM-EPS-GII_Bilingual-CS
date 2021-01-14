/**
 * @brief It defines the game interface
 * for each command
 *
 * @file game.h
 * @version 1.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "die.h"

typedef struct _Game{
  Object * object[MAX_IDs_SET];
  Player *player;
  Space* spaces[MAX_SPACES + 1];
  T_Command last_cmd;
  STATUS cmd_status;
  Die *die;
} Game;
/*Definition of fucntions*/
STATUS game_create(Game* game);
STATUS game_create_from_file(Game* game, char* filename);
STATUS game_update(Game* game, T_Command cmd);
STATUS game_destroy(Game* game);
BOOL   game_is_over(Game* game);
void   game_print_screen(Game* game);
void   game_print_data(Game* game);
Space* game_get_space(Game* game, Id id);
Id     game_get_player_location(Game* game);
Id     game_get_player_object(Game* game);
Id     game_get_object_location(Game* game,Id id);
T_Command game_get_last_command(Game* game);
int game_get_die_value(Game* game);
STATUS game_get_callback_status(Game* game);
STATUS game_add_object(Game* game, Object* object);
Id game_get_objectId(Game *game,int i);
Object *game_get_object(Game *g,Id id);

#endif

