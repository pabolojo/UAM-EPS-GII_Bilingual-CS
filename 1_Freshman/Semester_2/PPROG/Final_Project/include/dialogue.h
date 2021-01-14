/** 
 * @brief It implements the dialogue interpreter
 * Finalidad:
 * A) Para comando ejecutado por el usuario se acabe mostrando una
 * frase indicativa de qué acción ha realizado y si esta se ha llevado a cabo con exito o no
 * B) Tiene que identificarse si el usuario ha ejecutado de forma consecutiva un mismo  
 * comando sin exito o si ha intentado ejecutar un comando que no existe
 *
 * @file dialogue.h
 * @author Cristina Soria
 * @version 1.0 
 * @date 23/04/2018 
 */

#ifndef DIALOGE_H
#define DIALOGE_H
#include "../include/types.h"
#include "../include/command.h"


typedef struct _Dialogue Dialogue;

/**
* @brief Funcion que crea dialogo
* 
* @author Cristina Soria
* @return dialogo creado 
*/
Dialogue * dialogue_create();

/**
* @brief Funcion que libera memoria
* @author Cristina Soria
* @param Datos a liberar
* @return OK O ERROR si se libera bien o no
*/
STATUS dialogue_destroy(Dialogue * d);


/**
* @brief Funcion que guarda la informacion del comando ejecutado
*
* @author Julia Simon
* @param dialogue dialogo
* @param comando ejecutado
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_comando(Dialogue* dialogue, Command* comando);

/**
* @brief Funcion que guarda el estado del comando ejecutaod
*
* @author Julia Simon
* @param dialogue dialogo
* @param status_cmd indica si el comando se ha realizado correctamente o no
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_status(Dialogue* dialogue, STATUS status_cmd);

/**
* @brief Funcion que guarda si el objeto se puede mover o no
* Necesaria para el comando grasp. En el resto de casos no se usa
*
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_object_nomovible(Dialogue* dialogue, BOOL object);

/**
* @brief Funcion que guarda si se examina un espacio
* Necesaria para el comando check. En el resto de casos no se usa
*
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_check_space(Dialogue* dialogue, BOOL space);

/**
* @brief Funcion que guarda si el link esta cerrado
* Necesaria para los comandos de movimiento. 
*
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_link_cerrado(Dialogue* dialogue, BOOL link);

/**
* @brief Funcion que guarda si el link esta abierto
* Necesaria para el comando open. En el resto de casos no se usa
*
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_link_open(Dialogue* dialogue, BOOL link);

/**
* @brief Funcion que guarda si hay monstruo
* Necesaria para el comando atack. En el resto de casos no se usa
*
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_no_monster(Dialogue* dialogue, BOOL monster);

/**
* @brief Funcion que guarda el nombre del espacio
* 
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_space(Dialogue* dialogue, char* space);

/**
* @brief Funcion que guarda el nombre del objeto
* 
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_object(Dialogue* dialogue, char* object);

/**
* @brief Funcion que guarda el nombre del link
* 
* @author Julia Simon
* @param dialogue dialogo
* @return si se ha hecho o no correctamente
*/
STATUS dialogue_set_link_name(Dialogue* dialogue, char* link);

/**
* @brief Funcion que saca los datos del dialogo
* 
* @author Julia Simon
* @param dialogue estructura
* @return Cadena con la frase a mostrar por pantalla
*/
char * dialogue_get_data(Dialogue * dialogue);

/** 
* @brief Funcion encargada de devolver el tamaño en memoria del dialogue
* 
* @author Julia Simon
* @return tamaño del dialogue
*/

size_t dialogue_get_size();

#endif
