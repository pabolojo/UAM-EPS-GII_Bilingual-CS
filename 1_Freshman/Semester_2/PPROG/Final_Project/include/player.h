/** 
 * @brief It defines a player
 * 
 * @file player.h
 * @author Cristina Soria
 * @version 2.0 
 * @date 22/03/2018
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "../include/types.h"
#include "../include/set.h"
#include "../include/inventory.h"

/**
* @brief Estructura del jugador
*/
typedef struct _Player Player;


/**
* @brief Funcion para inicializar el jugador
* Funcion encargada de reservar espacio para el jugador e inizializar
* sus parametros.
* 
* @author Miguel Rodriguez
* @param id se corresponde con el id del jugador
* @return El jugador creado
*/
Player* player_create(Id id);

/**
* @brief Funcion encargada de liberar la memoria reservada para el jugador
* 
* @author Miguel Rodriguez
* @param player jugador a destruir
* @return si se ha hecho o no correctamente
*/
STATUS player_destroy(Player* player);



/**
* @brief Funcion encargada de cambiar el nombre del
* 
* @author Miguel Rodriguez
* @param player jugador 
* @param name nuevo nombre
* @return si se ha hecho o no correctamente
*/
STATUS player_set_name(Player* player, char* name);

/**
* @brief Funcion encargada de cambiar el espacio en el que se encuentra
* 
* @author Miguel Rodriguez
* @param player jugador 
* @param id id del nuevo espacio
* @return si se ha hecho o no correctamente
*/
STATUS player_set_space(Player* player, Id id);

/**
* @brief Funcion encargada de añadir un objeto al jugador
* 
* @author Julia Simon
* @param player jugador 
* @param value verdadero si tiene objeto, falso si no
* @return si se ha hecho o no correctamente
*/
STATUS player_set_object(Player* player, Id id);

/**
* @brief Funcion encargada de asignarle un inventorio al jugador
* Funcion usada para cargar los inventorios desde un archivo
* 
* @author Julia Simon
* @param player jugador 
* @param inventorio inventorio a añadir
* @return si se ha hecho o no correctamente
*/
STATUS player_set_inventory(Player* player, Inventory* inventorio);

/**
* @brief Funcion encargada de obtener el nombre del jugador
* 
* @author Miguel Rodriguez
* @param player jugador 
* @return nombre del jugador
*/
const char * player_get_name(Player* player);

/**
* @brief Funcion encargada de obtener el id del jugador
* 
* @author Miguel Rodriguez
* @param player jugador 
* @return nombre del jugador
*/
Id player_get_id(Player* player);

/**
* @brief Funcion encargada de obtener el id del espacio donde se 
* encuentra el jugador
* 
* @author Miguel Rodriguez
* @param player jugador 
* @return id del espacio
*/
Id player_get_space(Player* player);

/**
* @brief Funcion encargada de ver si el jugador tiene un objeto
* 
* @author Julia Simon
* @param player jugador 
* @return verdadero si tiene objeto, falso caso contrario
*/
BOOL player_get_object(Player* player,Id id);

/**
* @brief Funcion encargada de devolver los ids de los objetos del jugador
* 
* @author Julia Simon
* @param player jugador 
* @return verdadero si tiene objeto, falso caso contrario
*/
Set* player_get_objects(Player* player);

/**
* @brief Funcion para obtener el inventorio del jugador
* Esta función se usa para guardar en el fichero los datos del juego actual 
*
* @author Julia Simon
* @param player jugador 
* @return verdadero si tiene objeto, falso caso contrario
*/
Inventory* player_get_inventory(Player* player);

/**
* @brief Funcion encargada de devolver el tamaño del jugador
* 
* @author Julia Simon
* @return tamaño
*/
size_t player_get_size();

/**
* @brief Funcion encargada de borrar objetos del set del jugador
* 
* @author Julia Simon
* @param player jugador
* @param id id que quiero eliminar del set
* @return OK funcionamiento correcto, ERROR caso contrario
*/
STATUS player_del_objects(Player* player, Id id);



/**
* @brief Funcion para imprimir los datos del jugador
* 
* @author Miguel Rodriguez
* @param player jugador 
* @return si se ha hecho o no correctamente
*/
STATUS player_print(Player* player);

#endif
