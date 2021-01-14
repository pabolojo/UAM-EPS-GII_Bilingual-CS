/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Julia Simon
 * @version 3.0 
 * @date 03/04/2018
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "../include/command.h"
#include "../include/space.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/die.h"
#include "../include/dialogue.h"

/**
* @brief Estructura de game
*/
typedef struct _Game Game;


/**
* Funcion encargada de reservar espacio para el juego e inizializar
* sus parametros.
* 
* @author Julia Simon
* @return juego creado
*/
Game* game_create();

/**
* Funcion encargada de liberar la memoria reservada para los 
* componentes del juego
* 
* @author Julia Simon
* @param game juego a destruir
* @return si se ha hecho o no correctamente
*/
STATUS game_destroy(Game* game);

/**
* @brief Funcion para inicializar el dialogue
* Esta funcion se usa cuando leemos del fichero
*
* @author Julia Simon
* @param game juego
* @param dialogue dado que añadimos al juego
* @return si se ha hecho o no correctamente
*/
STATUS game_set_dialogue(Game*game,Dialogue*dialogue);

/**
* @brief Funcion para inicializar el dado
* Esta funcion se usa cuando leemos del fichero
*
* @author Julia Simon
* @param game juego
* @param die dado que añadimos al juego
* @return si se ha hecho o no correctamente
*/
STATUS game_set_die(Game*game, Die*die);

/**
* @brief Funcion para inicializar el comando
* Esta funcion se usa cuando leemos del fichero
*
* @author Julia Simon
* @param game juego
* @param command comando a añadir
* @return si se ha hecho o no correctamente
*/
STATUS game_set_command(Game*game,Command*command);

/**
* @brief Funcion para dar valor al estado del comando (ERROR o OK)
* Se usa para los comandos de save y load que no se hacen dentro del modulo game
*
* @author Julia Simon
* @param game juego
* @param last_cmd_status estado del comando
* @return si se ha hecho o no correctamente
*/
STATUS game_set_last_command_status(Game*game,STATUS last_cmd_status);

/**
* @brief Funcion para inicializar al jugador
*
* @author Julia Simon
* @param game juego
* @return jugador
*/
Player* game_set_player(Game* game);

/**
* @brief Funcion para inicializar la posicion del jugador
*
* @author Julia Simon
* @param game juego
* @param id id del espacio en el que se encuentra
* @return si se ha hecho o no correctamente
*/
STATUS game_set_player_location(Game* game, Id id);

/**
* @brief Funcion para inicializar al jugador leyendo del fichero binario
*
* @author Julia Simon
* @param game juego
* @param player jugador
* @return si se ha hecho o no correctamente
*/
STATUS game_set_player_load(Game*game,Player*player);
/**
* @brief Funcion para dar una descripcion detallada al objeto
*
* @author Julia Simon
* @param game juego
* @param space espacio al que queremos dar descripcion
* @return si se ha hecho o no correctamente
*/
STATUS game_set_space_description_detallada(Game* game, Space* space);

/**
* @brief Funcion para actualizar todas las descripciones detalladas de los espacios del juego
*
* @author Julia Simon
* @param game juego
* @return si se ha hecho o no correctamente
*/
STATUS game_actualizar_descripciones(Game* game);

/**
* @brief Funcion para añadir un nuevo espacio en el juego
*
* @param game juego
* @param space espacio a añadir
* @return si se ha hecho o no correctamente
*/
STATUS game_add_space(Game* game, Space* space);

/**
* @brief Funcion para inicializar añadir un objeto al game
* 
* @author Julia Simon 
* @param game juego 
* @param object objeto a añadir
* @return si se ha hecho o no correctamente
*/
STATUS game_add_object(Game* game, Object* object);

/**
* @brief Funcion que añade un link al juego 
* 
* @author Sergio de los Reyes
* @param game juego 
* @param link link que queremos añadir
* @return si se ha hecho o no correctamente
*/
STATUS game_add_link(Game* game, Link* link);



/**
* @brief Funcion que devuelve el espacio de cierta posicion
*
* @author Julia Simon
* @param game juego
* @param i posicion
* @return espacio correspondiente
*/
Space* game_get_space_i(Game* game, int i);

/**
* @brief Funcion que devuelve el espacio que corresponde con el id
* 
* @author Julia Simon
* @param game juego 
* @param id id del espacio que buscamos
* @return espacio buscado
*/
Space* game_get_space(Game* game, Id id);

/**
* @brief Funcion que devuelve la descripcion del espacio con ese id
* 
* @author Julia Simon
* @param game juego 
* @param id id del espacio 
* @return descripcion del espacio
*/
const char* game_get_space_description(Game* game,Id id);

/**
* @brief Funcion que devuelve la descripcion detallada del espacio con ese id en caso de que este iluminado
* 
* @author Julia Simon
* @param game juego 
* @param id id del espacio 
* @return descripcion del espacio
*/
const char* game_get_space_description_check(Game* game,Id id);

/**
* @brief Funcion que devuelve el Link que tiene un cierto id
* 
* @author Sergio de los Reyes
* @param game juego 
* @param id id del link
* @return link que corresponde a ese id
*/
Link* game_get_link(Game* game, Id id);

/**
* @brief Funcion que devuelve el Link de la posicion i
* 
* @author Julia Simon
* @param game juego 
* @return link 
*/
Link* game_get_link_i(Game* game, int i);

/**
* @brief Funcion que devuelve el numero de links
* 
* @author Julia Simon
* @param game juego 
* @return numero links 
*/
int game_get_num_links(Game* game);


/**
* @brief Funcion que devuelve el jugador 
*
* @author Julia Simon
* @param game juego
* @return jugador del juego
*/
Player* game_get_player(Game* game);

/**
* @brief Funcion que devuelve la posicion donde se encuentra el jugador
* 
* @param game juego 
* @return id del espacio donde esta el jugador
*/
Id     game_get_player_location(Game* game);

/**
* @brief Funcion que devuelve el objeto que corresponde con el id
* 
* @author Julia Simon
* @param game juego 
* @param id id del objeto que buscamos
* @return objeto buscado
*/
Object* game_get_object(Game* game, Id id);

/**
* @brief Funcion que devuelve la posicion donde se encuentra el objeto
* 
* @author Julia Simon
* @param game juego 
* @param id id del objeto que queremos encontrar
* @return id del espacio donde esta el objeto
*/
Id     game_get_object_location(Game* game,Id id);

/**
* @brief Funcion que devuelve el objecto de una posicion
*
* @author Julia Simon
* @param game juego
* @param i posicion
* @return objeto
*/
Object* game_get_object_i(Game* game,int i);

/**
* @brief Funcion que devuelve cuantos objetos hay en game
*
* @author Julia Simon
* @param game juego
* @return numero objetos
*/
int game_get_num_objects(Game* game);

/**
* @brief Funcion que devuelve cuantos espacios hay en game
*
* @author Julia Simon
* @param game juego
* @return numero espacios
*/
int game_get_num_spaces(Game* game);

/**
* @brief Funcion que devuelve el dado
*
* @author Julia Simon
* @param game juego
* @return dado del juego
*/
Die* game_get_die(Game* game);

/**
* @brief Funcion que devuelve el comando guardado en el juego
* 
* @author Julia Simon
* @param game juego 
* @return comando 
*/
Command* game_get_command(Game* game);

/**
* @brief Funcion que coge el comando introducido
* 
* @param game juego 
* @return comando ultimo comando
*/
T_Command game_get_last_command(Game* game);

/**
* @brief Funcion que devuelve si se ha podido realizar o no el último comando
* 
* @author Julia Simon
* @param game juego 
* @return status del ultimo comando, ERROR si no se ha podido ejecutar, OK si se ha ejecutado
*/
STATUS game_get_last_command_status(Game* game);


/**
* @brief Funcion que devuelve el nombre del objeto a coger
* 
* @author Julia Simon
* @param game juego 
* @return nombre del objeto
*/
const char*  game_get_grasp_object(Game* game);

/**
* @brief Funcion que devuelve el objeto que corresponde con un nombre
* 
* @author Julia Simon
* @param game juego 
* @param name nombre del objeto
* @return objeto
*/
Object* game_get_object_by_name(Game* game, const char* name);


/**
* @brief Funcion que oculta o pone visibles todos los objetos del juego
* 
* @author Julia Simon
* @param game juego 
* @param ocult indica si se ocultan o se muestran los objetos
* @return si se ha hecho o no correctamente
*/
STATUS game_ocult_objects(Game* game, BOOL ocult);

/**
* @brief Funcion encargada devolver el tamaño del game en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_game_size();

/**
* @brief Funcion encargada devolver el tamaño del espacio en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_space_size();

/**
* @brief Funcion encargada devolver el tamaño del objeto en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_object_size();

/**
* @brief Funcion encargada devolver el tamaño del jugador en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_player_size();

/**
* @brief Funcion encargada devolver el tamaño del link en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_link_size();

/**
* @brief Funcion encargada devolver el tamaño del dado en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_die_size();

/**
* @brief Funcion encargada devolver el tamaño del set en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_set_size();

/**
* @brief Funcion encargada devolver el tamaño del command en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_command_size();

/**
* @brief Funcion encargada devolver el tamaño del inventory en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_inventory_size();

/**
* @brief Funcion encargada devolver el tamaño del dialogue en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t game_get_dialogue_size();

/**
* @brief Funcion encargada devolver el dialogue del game
* 
* @author Julia Simon
* @param game juego
* @return dialogue
*/
Dialogue* game_get_dialogue(Game* game);

/**
* @brief Funcion encargada devolver el texto a mostrar por pantalla
* 
* @author Julia Simon
* @param game juego
* @return texto para mostrar por pantalla
*/
char* game_get_dialogue_text(Game* game);

/**
* @brief Funcion que actualiza la situacion del juego 
* La actualizacion es en  funcion del comando recibido llamando al callback correspondiente
* 
* @author Julia Simon
* @param game juego 
* @param cmd comando introducido
* @return si se ha hecho o no correctamente
*/
STATUS game_update(Game* game, Command* cmd);

/**
* @brief Funcion para que se acabe el juego
* 
* @param game juego
* @return Siempre FALSE en esta fase
*/
BOOL   game_is_over(Game* game);

/*void   game_print_screen(Game* game);*/

/**
* @brief Funcion para imprimir los datos del juego
* 
* @author Miguel Rodriguez
* @param game juego 
*/
void   game_print_data(Game* game);

/**
* @brief Funcion para iluminar los espacios
* 
* @author Julia Simon
* @param game juego 
*/
void game_ilimina_space(Game*game);

#endif

