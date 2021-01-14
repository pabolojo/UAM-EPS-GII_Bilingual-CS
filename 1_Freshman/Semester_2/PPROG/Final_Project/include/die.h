/** 
 * @brief It implements the die interpreter
 * 
 * @file die.h
 * @author Julia Simon
 * @version 1.0 
 * @date 20/02/2018 
 */

#ifndef DIE_H
#define DIE_H

#include "../include/types.h"

/**
* @brief Estructura del dado
*/
typedef struct _Die Die;

/** 
* @brief Funcion encargada de reservar memoria para el dado
* 
* @author Julia Simon 
* @param Id id del dado que se va a crear
* @return dado que se ha creado 
*/
Die* die_create(Id id);

/** 
* @brief Funcion encargada de liberar la memoria reservada para el dado
* 
* @author Julia Simon
* @param die dado que se quiere liberar
* @return OK si se ha liberado la memoria correctamente y ERROR en caso de error
*/
STATUS die_destroy(Die* die);

/** 
* @brief Funcion encargada de obtener el id del dado
* 
* @author Julia Simon
* @param die dado del que se quiere saber el id
* @return id del dado
*/
Id die_get_id(Die* die);

/** 
* @brief Funcion encargada de devolver el tamaño en memoria del dado
* 
* @author Julia Simon
* @return tamaño del dado
*/
size_t die_get_size();

/** 
* @brief Funcion para lanzar el dado
* 
* @author Julia Simon
* @param dado dado que queremos tirar
* @param sup numero máximo del dado
* @param inf numero mínimo del dado
* @return OK si no ha habido problemas, ERROR en caso de fallo
*/
STATUS die_roll(Die* dado, int sup, int inf);

/** 
* @brief Funcion encargada de darnos toda la informacion de un dado
* 
* @author Julia Simon
* @param die dado del que se quiere saber toda la informacion
* @return OK si se ha impreso correctamente la informacion en el fichero, y ERROR en caso contrario
*/
STATUS die_print(Die* die);


/** 
* @brief Funcion encargada de darnos el ultimo valor del dado
* 
* @author Julia Simon
* @param die dado del que se quiere saber 
* @return int con el numero correspondiente
*/
int die_get_lastValue(Die* die);

#endif
