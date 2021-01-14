/** 
 * @brief It defines the game rules interface
 * 
 * @file game_rules.h
 * @author Julia Simon
 * @version 1.0 
 * @date 02/05/2018
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "../include/types.h"
#include "../include/game.h"

/**
* @brief Lista de posibles reglas
*/
typedef enum enum_Rules {
	NO_RULE = -1, OCULT, OFF, ON,CLOSE,SHOW,CHANGE,ELIMINATE, REGENERATE, NEWEXIT
} T_Rule;

/*

NO_RULE - no se ejecuta ninguna regla
OCULT - Oculta todos los objetos
OFF - Apaga algunos espacios de manera aleatoria
ON - Enciende algunos espacios de manera aleatoria
CLOSE - Cierra algun link, se crea la llave que lo abre, en la posicion que esta el jugador, pero esta oculta
		Los posibles links a cerrar son entre el 7 y 11
SHOW - Desoculta los objetos, los pone todos a visibles
CHANGE - Cambia los enlaces del piso de arriba
ELIMINATE - Elimina el link 34 o 35 de los enlaces del sotano (se quitan de los espacios, no del juego)
REGENERATE - Crea de nuevo los links 34 o 35 si han sido eliminados
NEWEXIT - el link de la salida cambia de espacio, pero sigue estando cerrado, se sigue necesitando la misma llave para abrirlo

MONSTER - Mueve el monstruo por las casillas del sotano******************NO IMPLEMENTADO**********************
*/

/**
* @brief Estructura del gameRules
*/
typedef struct _GameRules GameRules;

/**
* @brief Funcion para reservar memoria para el modulo de las reglas
* 
* @author Julia Simon
* @return puntero al modulo
*/
GameRules* game_rules_create();

/**
* @brief Funcion que libera memoria
* 
* @author Julia Simon
* @param gameRules modulo a destruir
* @return Ok O ERROR si se libera bien o no
*/
STATUS game_rules_destroy(GameRules* gameRules);

/**
* @brief Funcion para jugar
*
* @author Julia SImon
* @param gameRules modulo de reglas
* @param game juego
* @param no_rules para indicar que queremos jugar sin reglas
* @return Ok O ERROR si se libera bien o no
*/
STATUS game_rules_play(GameRules* gameRules, Game * game, BOOL no_rules);


#endif
