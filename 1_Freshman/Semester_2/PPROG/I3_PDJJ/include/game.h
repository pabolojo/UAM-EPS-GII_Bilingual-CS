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
#include "link.h"
#include "die.h"
/**
 * @brief defines the game structure
 *
 */
typedef struct _Game Game;

/**
 * @brief  create a game
 *
 * @return OK, or ERROR
 */
Game *game_create();
/**
 * @brief  create file in  game
 *
 * @param game
 * @param filename
 *
 * @return OK, or ERROR
 */
STATUS game_create_from_file(Game* game, char* filename);
/**
 * @brief  update the game with a comand
 *
 * @param cmd
 *
 * @return OK, or ERROR
 */
STATUS game_update(Game* game, T_Command cmd);
/**
 * @brief  destroy game
 *
 * @param game
 *
 * @return OK, or ERROR
 */
STATUS game_destroy(Game* game);
/**
 * @brief  Tells if game is over
 *
 * @param game
 *
 * @return TRUE or FALSE
 */
BOOL   game_is_over(Game* game);
/**
 * @brief  prints game in screen
 *
 * @param game
 *
 * @return void
 */
void   game_print_screen(Game* game);
/**
 * @brief  prints data in screen
 *
 * @param game
 *
 * @return void
 */
void   game_print_data(Game* game);
/**
 * @brief get space in game
 *
 * @param game
 * @param id
 *
 * @return space or in case of error NULL
 */
Space* game_get_space(Game* game, Id id);
/**
 * @brief get player location in game
 *
 * @param game
 *
 * @return id or in case of error NULL
 */
Id     game_get_player_location(Game* game);
/**
 * @brief get player object in game
 *
 * @param game
 *
 * @return id or in case of error NULL
 */
Id     game_get_player_object(Game* game);
/**
 * @brief get objcet location in game
 *
 * @param game
 * @param id
 *
 * @return id or in case of error NULL
 */
Id     game_get_object_location(Game* game,Id id);
/**
 * @brief get last command in the game
 *
 * @param game
 *
 * @return id or in case of error NULL
 */
T_Command game_get_last_command(Game* game);
/**
 * @brief get die value
 *
 * @param game
 *
 * @return the die valuie(int) or -1 in case of error
 */
int game_get_die_value(Game* game);
/**
 * @brief  get callback
 *
 * @param game
 *
 * @return OK, or ERROR
 */
STATUS game_get_callback_status(Game* game);
/**
 * @brief  add an object to the game
 *
 * @param game
 * @param object
 *
 * @return OK, or ERROR
 */
STATUS game_add_object(Game* game, Object* object);
/**
 * @brief get the id of object in the game
 *
 * @param game
 * @param i
 *
 * @return id or in case of error NULL
 */
Id game_get_objectId(Game *game,int i);
/**
 * @brief get the  object in the game
 *
 * @param g
 * @param id
 *
 * @return object or in case of error NULL
 */
Object *game_get_object(Game *g,Id id);
/**
 * @brief get the link in the game to be able to go to another space
 *
 * @param game
 * @param id
 *
 * @return link or in case of error NULL
 */
Link *game_get_link(Game *game,Id id);
/**
 * @brief get the object of id i
 *
 * @param game
 * @param i
 *
 * @return object or in case of error NULL
 */
Object *game_get_objectbypos(Game *game,Id i);
/**
 * @brief set the object of id i in the game
 *
 * @param game
 * @param i
 * @param object
 *
 * @return OK or ERROR
 */
STATUS game_set_objectbypos(Game *game,Id i,Object *object);
/**
 * @brief get player
 *
 * @param game
 *
 * @return player or in case of error NULL
 */
Player *game_get_player(Game *game);
/**
 * @brief get spaces of id i
 *
 * @param game
 * @param i
 *
 * @return player or in case of error NULL
 */
Space *game_get_spacebypos(Game *game,Id i);
/**
 * @brief set spaces of id i in the game
 *
 * @param game
 * @param i
 * @param space
 *
 * @return OK or ERROR
 */
STATUS game_set_spacebypos(Game *game,Id i,Space *space);
/**
 * @brief set links of id i in the game
 *
 * @param game
 * @param i
 *
 * @return link or in case of error NULL
 */
Link *game_get_linkbypos(Game *game,Id i);
/**
 * @brief get links of id i in the game
 *
 * @param game
 * @param i
 * @param link
 *
 * @return OK or ERROR
 */
STATUS game_set_linkbypos(Game *game,Id i,Link *link);
/**
 * @brief set objects of id i in the game
 *
 * @param game
 * @param objdsc
 *
 * @return OK or ERROR
 */
STATUS game_set_objdsc(Game* game, char* objdsc);
/**
 * @brief get the name of objects
 *
 * @param game
 *
 * @return object or in case of error NULL
 */
char* game_get_objdsc(Game* game);

#endif

