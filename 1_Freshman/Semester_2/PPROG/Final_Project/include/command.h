/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author Julia Simon
 * @version 1.0 
 * @date 08/03/2018 
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "../include/types.h"

/**
* @brief Lista de posibles comandos
*/
typedef enum enum_Command {
	NO_CMD = -1, UNKNOWN, EXIT, FOLLOWING, PREVIOUS, GRASP, DROP, LEFT, RIGHT, DIE, CHECK, MOVE, TURNON, TURNOFF, UP, DOWN, OPEN, CODE,ATACK, EXAMINE, SAVE, LOAD
} T_Command;


/**
* @brief Estructura del comando
*/
typedef struct _Command Command;

/**
* @brief Funcion para reservar memoria e inicializar el comando
* 
* @author Julia Simon
* @return Comando creado
*/
Command* command_create();

/**
* @brief Funcion encargada de liberar la memoria reservada para el comando
* 
* @author Julia Simon
* @param command comando a destruir
* @return si se ha hecho o no correctamente
*/
STATUS command_destroy(Command* command);

/**
* @brief Funcion que lee el comando introducido por el usuario
* 
* @author Julia Simon
* @param comando inicializado
* @return comando introducido
*/
Command* command_get_user_input(Command* comando);

/**
* @brief Funcion para fijar el tipo de comando
* Esta función se utiliza para facilitar el dialogue
*
* @author Julia Simon
* @param command comando
* @param type tipo de comando
* @return si se ha hecho o no correctamente
*/
STATUS command_set_type_command(Command* command, T_Command type);

/**
* @brief Funcion que devuelve el ultimo comando introducido 
*
* @author Julia Simon
* @param command comando
* @return comando (enumerado) 
*/
T_Command command_get_type_command(Command* command);

/**
* @brief Funcion que devuelve el ultimo nombre introducido.
* Puede ser para el objeto a coger, espacio a examinar o direccion en la
* que tiene que desplazarse con move.
*
* @author Julia Simon
* @param command comando
* @return nombre 
*/
char* command_get_name_command(Command* command);

/**
* @brief Funcion que devuelve el ultimo objeto que quiere abrir una puerta
*
*
* @author Julia Simon
* @param command comando
* @return nombre del objeto
*/
char* command_get_key_command(Command* command);
/**
* @brief Funcion que devuelve el tamaño del comando en memoria
*
* @author Julia Simon
* @return tamaño
*/
size_t command_get_size();

void command_print(Command* cmd);
#endif
