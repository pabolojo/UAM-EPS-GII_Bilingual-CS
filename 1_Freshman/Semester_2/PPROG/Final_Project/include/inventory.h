/** 
 * @brief It implements the inventory interpreter
 * 
 * @file inventory.h
 * @author Cristina Soria
 * @version 1.0 
 * @date 08/03/2018 
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/set.h"
#include "../include/types.h"

/**
* @brief Estructura del inventorio
*/
typedef struct _Inventory Inventory;

/**
* @brief Inicializar el inventory
* Funcion encargada de reservar espacio para el inventory e inizializar
* sus parametros. De momento todos los inventory tienen un máximo de 5 objetos
* 
* @author Cristina Soria
* @return El inventory creado
*/
Inventory * inventory_create();

/**
* @brief Funcion encargada de liberar la memoria reservada para el inventorio
* 
* @author Cristina Soria
* @param inventory inventorio a destruir
* @return si se ha hecho o no correctamente
*/
STATUS inventory_destroy(Inventory *inventory);

/**
* @brief Funcion encargada de cambiar la dimension del inventory
* 
* @author Cristina Soria
* @param inventory inventorio
* @param i nuevo tamaño
* @return OK funcionamiento correcto, ERROR caso contrario
*/
STATUS inventory_set_dimension(Inventory *inventory, int i);

/**
* @brief Funcion encargada de asignar un set con objetos a un inventorio
* Esta funcion se usa para cuando cargamos del fichero binario de datos
*
* @author Julia Simon
* @param inventory inventorio
* @param objects set de objetos a asociar
* @return OK funcionamiento correcto, ERROR caso contrario
*/
STATUS inventory_set_objects(Inventory *inventory, Set* objects);

/**
* @brief Funcion que te dice el numero de objetos que hay en un inventorio
* 
* @author Cristina Soria
* @param inventory inventorio
* @return numero de objetos o -1 en caso de error
*/
int inventory_get_number_objects(Inventory *inventory);

/**
* @brief Funcion que te dice el id del objeto que hay en una posicion
* 
* @author Cristina Soria
* @param inventory inventorio
* @param pos_id posicion del objeto
* @return id del objeto en esa posicion
*/
Id inventory_get_id(Inventory *inventory, int pos_id);

/**
* @brief Funcion que te devuelve el set de los objetos del inventorio
* 
* @author Julia Simon
* @param inventory inventorio
* @return set de objetos
*/
Set* inventory_get_objects(Inventory* inventory);

/**
* @brief Funcion que te devuelve el tamaño en memoria del inventory
* 
* @author Julia Simon
* @return tamaño inventory
*/
size_t inventory_get_size();

/**
* @brief Funcion encargada de añadir objetos al set
* 
* @author Cristina Soria
* @param inventory inventorio
* @param id id que quiero añadir al set
* @return si se ha hecho o no correctamente
*/
STATUS inventory_add_object(Inventory *inventory, Id id);

/**
* @brief Funcion encargada de borrar objetos del set del inventorio
* 
* @author Cristina Soria
* @param inventory inventorio
* @param id id que quiero eliminar del set
* @return OK funcionamiento correcto, ERROR caso contrario
*/
STATUS inventory_remove_object(Inventory *inventory, Id id);

/**
* @brief Funcion que te dice si un objeto esta o no en un inventorio
* 
* @author Cristina Soria
* @param inventory inventorio
* @param id id del objeto que queremos saber si esta
* @return true en caso de que si, false caso contrario
*/
BOOL inventory_object_exist(Inventory *inventory, Id id);


/**
* @brief Funcion para imprimir el inventorio
* 
* @author Cristina Soria
* @param pf file donde se va a escribir (por defecto stdout)
* @param inventory inventorio
* @return si se ha hecho o no correctamente
*/
STATUS inventory_print(FILE*pf, Inventory *inventory);

#endif /*INVENTORY_H*/
