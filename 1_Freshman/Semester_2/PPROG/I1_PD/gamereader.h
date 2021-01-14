#ifndef GAME_READER_H
#define GAME_READER_H

#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "space.h"
#include "game.h"

STATUS game_load_spaces(Game* game, char* filename);

#endif
