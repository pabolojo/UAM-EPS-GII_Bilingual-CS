/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @version 2.0 
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engine_create();
void graphic_engine_destroy(Graphic_engine *ge);
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, FILE *f);
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif

