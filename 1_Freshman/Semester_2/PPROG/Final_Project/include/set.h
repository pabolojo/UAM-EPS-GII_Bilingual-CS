/** 
 * @brief It defines a set
 * 
 * @file set.h
 * @author Julia Simon y Miguel Rodriguez
 * @version 1.2 
 * @date 02/03/2018
 */
#ifndef SET_H
#define SET_H

#include "../include/types.h"

/**
* @brief Estructura  del set
*/
typedef struct _Set Set;

#define MAX_ID 100 /*!< numero maximo de ids*/

/** 
* @brief Funcion encargada de reservar memoria para un conjunto
* 
* @author Miguel Rodriguez
* @return conjunto que se ha creado 
*/
Set* set_create();

/** 
* @brief Funcion encargada de liberar la memoria reservada para el conjunto
* 
* @author Miguel Rodriguez
* @param set conjunto que se va a liberar
* @return OK si se ha liberado la memoria correctamente y ERROR en caso de error
*/
STATUS set_destroy(Set* set);


/** 
* @brief Funcion encargada de darnos el id que hay en una posicion del conjunto
* 
* @author Miguel Rodriguez
* @param set conjunto en el que buscamos
* @param i posicion de de la que queremos saber el id
* @return Id del elemento del conjunto
*/
Id set_get_Id(Set* set, int i);

/** 
* @brief Funcion encargada de darnos el numero de elementos del conjunto
* 
* @author Miguel Rodriguez
* @param set conjunto 
* @return numero de elementos del conjunto
*/
int set_get_nId(Set* set);

/**
* @brief Funcion encargada devolver el tamaño del set en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t set_get_size();

/** 
* @brief Funcion encargada de añadir ids al conjunto
* 
* @author Miguel Rodriguez
* @param set conjunto al que se le va a añadir alguna id
* @return OK si se ha añadido correctamente la id y ERROR en caso de error
*/
STATUS set_add(Set* set, Id id);

/** 
* @brief Funcion encargada de eliminar ids del conjunto
* 
* @author Miguel Rodriguez
* @param set conjunto del que se va a eliminar alguna id
* @return OK si se ha eliminado correctamente la id y ERROR en caso de error
*/
STATUS set_del(Set* set, Id id);

/** 
* @brief Funcion encargada de darnos toda la informacion de un conjunto
* 
* @author Miguel Rodriguez
* @param set set del que se quiere saber toda la informacion
* @return OK si se ha impreso correctamente la informacion en el fichero, y ERROR en caso contrario
*/
STATUS set_print(Set* set);



#endif