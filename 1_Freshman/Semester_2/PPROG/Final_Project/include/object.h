/** 
 * @brief It defines a object
 * 
 * @file object.h
 * @author Julia Simon y Miguel Rodriguez
 * @version 1.0 
 * @date 13-02-2018
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "../include/types.h"

#define MAX_OBJECTS 100 /*!< numero maximo de objetos */

/**
* @brief Estructura del objeto
*/
typedef struct _Object Object;

/** 
* @brief Funcion encargada de reservar memoria para un objeto
* 
* @author Miguel Rodriguez
* @param Id id del objeto que se va a crear
* @return objeto que se ha creado 
*/

Object* object_create(Id id);

/** 
* @brief Funcion encargada de liberar la memoria reservada para el objeto
* 
* @author Miguel Rodriguez
* @param object objecto que se va a liberar
* @return OK si se ha liberado la memoria correctamente y ERROR en caso de error
*/
STATUS object_destroy(Object* object);

/** 
* @brief Funcion encargada de cambiar el nombre de un objeto
* 
* @author Miguel Rodriguez
* @param object objeto al que se le va a cambiar el nombre
* @param name nuevo nombre que se le va a asignar al objeto
* @return OK si se ha cambiado el nombre correctamente y ERROR en caso de error
*/
STATUS object_set_name(Object* object, char* name);

/** 
* @brief Funcion encargada de cambiar la descripción del objeto
* 
* @author Miguel Rodriguez
* @param object objeto al que se quiere cambiar la descripción
* @param string descripcion del objeto
* @return si se ha hecho correctamente o no
*/
STATUS object_set_description(Object* object, char* string);

/** 
* @brief Funcion encargada de cambiar la descripción del objeto cuando ha sido movido
* 
* @author Julia Simon
* @param object objeto al que se quiere cambiar la descripción
* @return si se ha hecho correctamente o no
*/
STATUS object_set_des_movido(Object* object);

/** 
 * @brief Funcion que guarda la posicion inicial del objeto
 *
 * @author Julia Simon
 * @param object el objeto
 * @param Id id del espacio inicial
 * @return si se ha hecho o no correctamente
 */
STATUS object_set_pos_inicial(Object* object, Id space);

/** 
* @brief Funcion encargada de decirnos el id del objeto
* 
* @author Miguel Rodriguez
* @param object objeto del que se quiere saber el id
* @return id del objeto
*/
Id object_get_id(Object* object);

/** 
* @brief Funcion encargada de decirnos el nombre del objeto
* 
* @author Miguel Rodriguez
* @param object objeto del que se quiere saber el nombre
* @return nombre del objeto
*/
char* object_get_name(Object* object);

/** 
* @brief Funcion encargada de decirnos la descripción del objeto
* Nos devuelve una descripcion u otra en función de si ha sido o no movido
* respecto de su posicion original.
* 
* @author Julia Simon
* @param object objeto del que se quiere saber la descripción
* @return descripcion del objeto
*/
char* object_get_description(Object* object);

/** 
 * @brief Funcion que devuelve la posicion inicial del objeto
 *
 * @author Julia Simon
 * @param object el objeto
 * @return Id del espacio inicial
 */
Id object_get_pos_inicial(Object* object);

/** 
* @brief Funcion encargada de darnos toda la informacion de un objeto
* 
* @author Miguel Rodriguez
* @param object objeto del que se quiere saber toda la informacion
* @return OK si se ha impreso correctamente la informacion en el fichero, y ERROR en caso contrario
*/
STATUS object_print(Object* object);

/** 
 * @brief Devuelve la movilidad del objeto
 * Es decir, indica si el objeto se va a poder mover o no de su posicion inicial.
 *
 * @author Sergio de los Reyes
 * @param object el objeto
 * @return un booleano (BOOL): la movilidad
 */
BOOL object_get_movible(Object* object);

/** 
 * @brief Establece la movilidad del objeto
 *
 * @author Sergio de los Resyes
 * @param object el objeto
 * @param movible si el objeto es movible
 * @return STATUS: OK o ERROR
 */
STATUS object_set_movible(Object* object, BOOL movible);

/** 
 * @brief Devuelve si el objeto se ha movido
 *
 * @author Sergio de los Reyes
 * @param object: el objeto
 * @return un booleano (BOOL): si se ha movido
 */
BOOL object_get_movido(Object* object);

/** 
 * @brief Establece si el objeto se ha movido
 *
 * @author Sergio de los Resyes
 * @param object: el objeto
 * @param movido: si el objeto se ha movido
 * @return STATUS: OK o ERROR
 */
STATUS object_set_movido(Object* object, BOOL movido);

/** 
 * @brief Devuelve si el objeto esta oculto

 * @author Sergio de los Reyes
 * @param object: el objeto
 * @return un booleano (BOOL): si esta oculto
 */
BOOL object_get_oculto(Object* object);

/** 
 * @brief Establece la visibilidad del objetp
 *
 * @author Sergio de los Resyes
 * @param object: el objeto
 * @param oculto: si el objeto esta oculto
 * @return STATUS: OK o ERROR
 */
STATUS object_set_oculto(Object* object, BOOL oculto);

/** 
 * @brief Devuelve el id del link que abre
 *
 * @author Sergio de los Reyes
 * @param object: el objeto
 * @return un int(id): id
 */
Id object_get_open(Object* object);

/** 
 * @brief Establece que abre el objeto
 *
 * @author Sergio de los Resyes
 * @param object: el objeto
 * @param open: el link que abre
 * @return STATUS: OK o ERROR
 */
STATUS object_set_open(Object* object, Id open);

/** 
 * @brief Devuelve si el objeto esta ilumonado

 * @author Sergio de los Reyes
 * @param object: el objeto
 * @return un booleano (BOOL): si esta iluminado
 */
BOOL object_get_iluminado(Object* object);

/** 
 * @brief Establece la iluminacion del objeto
 *
 * @author Sergio de los Resyes
 * @param object: el objeto
 * @param iluminado: si el objeto ilumina
 * @return STATUS: OK o ERROR
 */
STATUS object_set_iluminado(Object* object, BOOL iluminado);

/** 
 * @brief Devuelve si el objeto esta encendido

 * @author Sergio de los Reyes
 * @param object: el objeto
 * @return un booleano (BOOL): si esta encendido
 */
BOOL object_get_encendido(Object* object);

/** 
 * @brief Establece si el objeto esta encendido
 *
 * @author Sergio de los Resyes
 * @param object: el objeto
 * @param encendido: si el objeto esta encendido
 * @return STATUS: OK o ERROR
 */
STATUS object_set_encendido(Object* object, BOOL encendido);


/** 
* @brief Funcion encargada de darnos el tamaño del objeto en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t object_get_size();

#endif
