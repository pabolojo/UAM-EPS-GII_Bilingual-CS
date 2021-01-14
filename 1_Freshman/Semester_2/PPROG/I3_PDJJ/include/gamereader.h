/**
 * @brief It defines the header of game_reader
 *
 * @file gamereader.h
 * @version 1.0
 * @date 09-02-2019
 * @copyright GNU Public License
 */
#ifndef GAME_READER_H
#define GAME_READER_H

#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "game.h"

/**
 * @brief  it load the spaces to the game to be able to play
 *
 * @param game
 * @param filename
 * 
 * @return OK, or ERROR
 */
STATUS game_load_spaces(Game* game, char* filename);
/**
 * @brief  it load the objects to the game to be able to play
 *
 * @param game
 * @param filename
 * 
 * @return OK, or ERROR
 */
STATUS game_load_objects(Game* game, char* filename);
/**
 * @brief  it load the links to the game to be able to play
 *
 * @param game
 * @param filename
 * 
 * @return OK, or ERROR
 */
STATUS game_load_links(Game* game, char* filename);

#endif

