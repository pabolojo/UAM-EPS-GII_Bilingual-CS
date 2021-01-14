/** 
 * @brief It defines the game management interface
 * 
 * @file game_management.h
 * @author Julia Simon
 * @version 1.0 
 * @date 02/05/2018
 */
 #ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "../include/game.h"

/**
* Funcion que crea el juego, cargando la informacion necesaria desde un archivo 
* 
* @author Julia Simon 
* @param filename nombre del fichero a leer
* @return juego creado
*/
Game* game_management_game_create_from_file(char* filename);

/**
* Funcion que carga los espacios y objetos segun el fichero
* 
* @author Miguel Rodriguez
* @param game juego
* @param filename nombre del fichero a leer
* @return si se ha hecho o no correctamente
*/
STATUS game_management_game_load(Game* game, char* filename);


/**
* Funcion que guarda el game
* Esta funcion guarda el estado actual del juego en un fichero de datos para despues
* poder cargarlo
* 
* @author Julia Simon
* @param game juego
* @return si se ha hecho o no correctamente
*/

STATUS game_management_save(Game* game, char* filename);


/**
* Funcion que carga el game
* Esta funcion carga el estado actual del juego desde un fichero de datos 
*
* @author Julia Simon
* @param game juego
* @return si se ha hecho o no correctamente
*/
Game* game_management_load(char* filename);


#endif
