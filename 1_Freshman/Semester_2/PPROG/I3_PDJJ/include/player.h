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

/**
 * @brief defines the Object structure
 *
 */
typedef struct _Player Player;

/**
 * @brief create the player in the game
 *
 * @param id
 * 
 * @return player or in case of error NULL
 */
Player* player_create(Id id);
/**
 * @brief destroy the player in the game
 *
 * @param player
 * 
 * @return OK, or ERROR
 */
STATUS player_destroy(Player* player);
/**
 * @brief set the name of player
 *
 * @param player
 * @param name
 *
 * @return OK, or ERROR
 */
STATUS player_set_name(Player* player, char* name);
/**
 * @brief set the location of player
 *
 * @param player
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS player_set_location(Player* player, Id id);
/**
 * @brief add an object to player
 *
 * @param player
 * @param value
 *
 * @return OK, or ERROR
 */
STATUS player_add_object(Player* player, Id value);
/**
 * @brief set an object to player
 *
 * @param player
 * @param value
 * @param pos
 *
 * @return OK, or ERROR
 */
STATUS player_set_object(Player* player, Id value, int pos);
/**
 * @brief object to player
 *
 * @param player
 * @param id 
 *
 * @return OK, or ERROR
 */
STATUS player_del_object(Player* player, Id id);
/**
 * @brief get the name of  player
 *
 * @param player
 *
 * @return name of player or in case of error NULL
 */
const char * player_get_name(Player* player);
/**
 * @brief get the id of player 
 *
 * @param player
 * 
 * @return id or in case of error NULL
 */
Id player_get_id(Player* player);
/**
 * @brief get the location of player
 *
 * @param player
 * 
 * @return id or in case of error NULL
 */
Id player_get_location(Player* player);
/**
 * @brief get the object of player
 *
 * @param player
 * @param pos
 *
 * @return id or in case of error NULL
 */
Id player_get_object(Player* player, int pos);
/**
 * @brief print the player
 *
 * @param player
 *
 * @return OK, or ERROR
 */
STATUS player_print(Player* player);

#endif

