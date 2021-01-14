/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @author Julia Simon
 * @version 2.0 
 * @date 03-04-2018
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "../include/game_management.h"

/**
* @brief Estructura del graphic engine
*/
typedef struct _Graphic_engine Graphic_engine;

/**
* @brief Funcion encargada de crear la interfaz grafica
* 
* @author Julia Simon
* @return interfaz
*/
Graphic_engine* graphic_engine_create();

/**
* @brief Funcion encargada de destruir la interfaz grafica
* Para ello va destruyendo cada una de sus partes.
* 
* @param ge interfaz
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
* @brief Funcion encargada de pintar la interfaz grafica
* 
* @author Julia Simon
* @param ge interfaz
* @param game juego
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);
/*void graphic_engine_write_command(Graphic_engine *ge, char *str);*/

#endif
