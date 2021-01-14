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
/**
 * @brief defines the graphic engine structure
 *
 */
typedef struct _Graphic_engine Graphic_engine;
/**
 * @brief  it creates graphic engine in the game to be able to play
 * 
 * @return graphic engine or in case of error NULL
 */
Graphic_engine* graphic_engine_create();
/**
 * @brief  destroys graphic engine in the game
 *
 * @param ge
 * 
 * @return void
 */
void graphic_engine_destroy(Graphic_engine *ge);
/**
 * @brief paints graphic engine in the game
 *
 * @param ge
 * @param game
 * @param f
 * 
 * @return void
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, FILE *f);
/**
 * @brief  write a command of graphic engine in the game
 *
 * @param ge
 * @param str
 * 
 * @return void
 */
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif

