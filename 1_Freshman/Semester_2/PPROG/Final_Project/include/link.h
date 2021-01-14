/** 
 * @brief It implements the link interpreter
 * 
 * @file link.h
 * @author Sergio de los Reyes
 * @version 1.0 
 * @date 08/03/2018 
 */

#ifndef LINK_H
#define LINK_H

#include "../include/types.h"
/**
* @brief Estructura del link
*/
typedef struct _Link Link;

#define MAX_LINKS 35 /*!< Número máximo de links */
#define FIRST_LINK 1 /*!< Identificador del primer link */

/**
* @brief Funcion que inicializa el link
* Funcion encargada de reservar espacio para el link e inizializar sus parametros.
* 
* @author Sergio de los Reyes
* @param id se corresponde con el id del link
* @return El link creado
*/
Link* link_create(Id id);

/**
* @brief Funcion encargada de liberar la memoria reservada para el link
* 
* @author Sergio de los Reyes
* @param link link a destruir
* @return si se ha hecho o no correctamente
*/
STATUS link_destroy(Link* link);



/**
* @brief Funcion encargada de cambiar el nombre del link
* 
* @author Sergio de los Reyes
* @param link link 
* @param name nombre del link
* @return si se ha hecho o no correctamente
*/
STATUS link_set_name(Link* link, char* name);

/**
* @brief Funcion encargada de conectar dos espacios con un link
* 
* @author Sergio de los Reyes
* @param link link 
* @param space1 id del primer espacio
* @param space2 id del segundo espacio
* @return si se ha hecho o no correctamente
*/
STATUS link_set_link(Link* link, Id space1, Id space2);

/**
* @brief Funcion encargada de cambiar el estado de la puerta del link
* 
* @author Sergio de los Reyes
* @param link link 
* @param status estado de la puerta (abierto o cerrado)
* @return si se ha hecho o no correctamente
*/
STATUS link_set_status(Link* link, DOOR status);


/**
* @brief Funcion encargada de darnos el id del link
* 
* @author Sergio de los Reyes
* @param link link 
* @return id del link
*/
Id link_get_id(Link* link);

/**
* @brief Funcion que devuelve el nombre del link
* 
* @author Sergio de los Reyes
* @param link link 
* @return nombre del link
*/
char* link_get_name(Link* link);

/**
* @brief Funcion encargada devolver el estado de la puerta
* 
* @author Sergio de los Reyes
* @param link link 
* @return si se ha hecho o no correctamente
*/
DOOR link_get_status(Link* link);

/**
* @brief Funcion encargada devolver los ids de los espacios que forman el link
* 
* @author Sergio de los Reyes
* @param link link 
* @return array de 2 ids con los ids de los espacios del link
*/
Id* link_get_link(Link* link);

/**
* @brief Funcion encargada devolver el tamaño del link en memoria
* 
* @author Julia Simon
* @return tamaño
*/
size_t link_get_size();

/**
* @brief Funcion encargada devolver el espacio al que esta conectado otro espacio con ese link
* 
* @author Sergio de los Reyes
* @param link link 
* @param space espacio del que queremos buscar a cual se conecta
* @return id del espacio al que esta conectado space
*/
Id link_space_connected_to(Link* link, Id space);

/**
* @brief Funcion encargada de imprimir el link
* 
* @author Sergio de los Reyes
* @param link link 
* @return si se ha hecho o no correctamente
*/
STATUS link_print(Link* link);

#endif


