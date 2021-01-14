/**
 * @brief It defines the header of game_reader
 *
 * @file game_reader.h
 * @version 1.0
 * @date 09-02-2019
 * @copyright GNU Public License
 */
#ifndef GAME_READER_H
#define GAME_READER_H

#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "space.h"
#include "game.h"

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_load_objects(Game* game, char* filename);

#endif

