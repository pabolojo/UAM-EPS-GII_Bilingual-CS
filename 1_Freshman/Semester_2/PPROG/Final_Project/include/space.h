/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Julia Simon
 * @version 3.0 
 * @date 03-04-2018
 */

#ifndef SPACE_H
#define SPACE_H

#include "../include/types.h"
#include "../include/set.h"
#include "../include/link.h"

/**
* @brief Estructura  del espacio
*/
typedef struct _Space Space;

#define MAX_SPACES 100 /*!< numero maximo de espacio */
#define FIRST_SPACE 1  /*!< posicion del primer espacio*/

/** 
* @brief Funcion encargada de reservar memoria para un espacio
* 
* @author Miguel Rodriguez
* @param Id id del espacio que se va a crear
* @return espacio que se ha creado 
*/
Space* space_create(Id id);

/** 
* @brief Funcion encargada de liberar la memoria reservada para el espacio
* 
* @author Miguel Rodriguez
* @param space espacio que se quiere liberar
* @return OK si se ha liberado la memoria correctamente y ERROR en caso de error
*/
STATUS space_destroy(Space* space);



/** 
* @brief Funcion encargada de cambiar el nombre de un espacio
* 
* @param space espacio al que se le va a cambiar el nombre
* @param name nuevo nombre que se le va a asignar al espacio
* @return OK si se ha cambiado el nombre correctamente y ERROR en caso de error
*/
STATUS space_set_name(Space* space, char* name);

/** 
* @brief Funcion encargada de actualizar la descripcion de un espacio
* 
* @param space espacio al que se le va a cambiar la descripcion
* @return OK si se ha cambiado correctamente y ERROR en caso de contrario
*/
STATUS space_set_description(Space* space,char* string);

/** 
* @brief Funcion encargada de actualizar la descripcion detallada de un espacio
* 
* @param space espacio al que se le va a cambiar la descripcion detallada
* @return OK si se ha cambiado correctamente y ERROR en caso de contrario
*/
STATUS space_set_description_detallada(Space* space, char* string);
/** 
* @brief Funcion encargada de fijar que espacio hay al norte del espacio
* 
* @param space espacio actual
* @param Id id del espacio que se encuentra al norte
* @return OK si se ha cambiado el id correctamente y ERROR en caso de error
*/
STATUS space_set_north(Space* space, Link* link);

/** 
* @brief Funcion encargada de fijar que espacio hay al sur del espacio
* 
* @param space espacio actual
* @param Id id del espacio que se encuentra al sur
* @return OK si se ha cambiado el id correctamente y ERROR en caso de error
*/
STATUS space_set_south(Space* space, Link* link);

/** 
* @brief Funcion encargada de fijar que espacio hay al este del espacio
* 
* @param space espacio actual
* @param Id id del espacio que se encuentra al este
* @return OK si se ha cambiado el id correctamente y ERROR en caso de error
*/
STATUS space_set_east(Space* space, Link* link);

/** 
* @brief Funcion encargada de fijar que espacio hay al oeste del espacio
* 
* @param space espacio actual
* @param Id id del espacio que se encuentra al oeste
* @return OK si se ha cambiado el id correctamente y ERROR en caso de error
*/
STATUS space_set_west(Space* space, Link* link);

/** 
* @brief Funcion encargada de fijar que espacio hay arriba del espacio
* 
* @param space espacio actual
* @param Id id del espacio que se encuentra aarriba
* @return OK si se ha cambiado el id correctamente y ERROR en caso de error
*/
STATUS space_set_up(Space* space, Link* link);

/** 
* @brief Funcion encargada de fijar que espacio hay abajo del espacio
* 
* @param space espacio actual
* @param Id id del espacio que se encuentra abajo
* @return OK si se ha cambiado el id correctamente y ERROR en caso de error
*/
STATUS space_set_down(Space* space, Link* link);

/** 
* @brief Funcion encargada de establecer la descripcion grafica de un espacio
* 
* @author Miguel Rodriguez
* @param space espacio del que se quiere saber la descripcion grafica
* @param string trozo de la descripcion grafica que se va a poner  
* @param i entero que indica la linea en la que se tiene que escribir
* @return OK si se ha impreso correctamente la informacion en el fichero, y ERROR en caso contrario
*/
STATUS space_set_gdesc(Space* space, char* string, int i);

/** 
* @brief Funcion encargada de establecer si el espacio esta iluminado o no
* 
* @author Julia Simon
* @param space espacio 
* @param iluminado true indica que se va a iluminar, falso que no
* @return OK si se ha hecho correctamente, y ERROR en caso contrario
*/
STATUS space_set_iluminado(Space* space, BOOL iluminado);

/** 
* @brief Funcion encargada de establecer el set del espacio
* Esta funcion se usa para cuando se lee del fichero binario
* 
* @author Julia Simon
* @param space espacio 
* @param objetos set con los objetos del espacio
* @return OK si se ha hecho correctamente, y ERROR en caso contrario
*/
STATUS space_set_objects(Space* space, Set* objetos);

/** 
* @brief Funcion encargada de decirnos el nombre del espacio
* 
* @param space espacio del que se quiere saber el nombre
* @return nombre del espacio
*/
char* space_get_name(Space* space);

/** 
* @brief Funcion encargada de decirnos la descripcion del espacio
* 
* @param space espacio del que se quiere saber la descripcion
* @return descripcion del espacio
*/
char* space_get_description(Space* space);

/** 
* @brief Funcion encargada de decirnos la descripcion detallada del espacio
* 
* @param space espacio del que se quiere saber la descripcion
* @return descripcion detalla del espacio
*/
char* space_get_description_detallada(Space* space);

/** 
* @brief Funcion encargada de decirnos el id del espacio
* 
* @param space espacio del que se quiere saber el id
* @return id del espacio
*/
Id space_get_id(Space* space);

/** 
* @brief Funcion encargada de decirnos el id del espacio que se encuentra al norte
* 
* @param space espacio del que se quiere saber que espacio tiene al norte
* @return id del espacio que se encuentra al norte
*/
Id space_get_north(Space* space); /*Devuelve el id del link */

/** 
* @brief Funcion encargada de decirnos el id del espacio que se encuentra al sur
* 
* @param space espacio del que se quiere saber que espacio tiene al sur
* @return id del espacio que se encuentra al sur
*/
Id space_get_south(Space* space);

/** 
* @brief Funcion encargada de decirnos el id del espacio que se encuentra al este
* 
* @param space espacio del que se quiere saber que espacio tiene al este
* @return id del espacio que se encuentra al este
*/
Id space_get_east( Space* space);

/** 
* @brief Funcion encargada de decirnos el id del espacio que se encuentra al oeste
* 
* @param space espacio del que se quiere saber que espacio tiene al oeste
* @return id del espacio que se encuentra al oeste
*/
Id space_get_west(Space* space);

/** 
* @brief Funcion encargada de decirnos el id del espacio que se encuentra arriba
* 
* @param space espacio del que se quiere saber que espacio tiene arriba
* @return id del espacio que se encuentra abajo
*/
Id space_get_up(Space* space);

/** 
* @brief Funcion encargada de decirnos el id del espacio que se encuentra abajo
* 
* @param space espacio del que se quiere saber que espacio tiene abajo
* @return id del espacio que se encuentra abajo
*/
Id space_get_down(Space* space);

/** 
* @brief Funcion encargada de decirnos los objetos del espacio
* 
* @author Julia Simon 
* @param space espacio del que se quiere saber que objeto tiene
* @return si hay o no objeto en el espacio o FALSE en caso de error
*/
Set* space_get_objects(Space* space);

/** 
* @brief Funcion encargada de darnos la descripcion grafica de un espacio
* 
* @author Miguel Rodriguez
* @param space espacio del que se quiere saber la descripcion grafica
* @return OK si se ha impreso correctamente la informacion en el fichero, y ERROR en caso contrario
*/
char* space_get_gdesc(Space* space, int position);

/** 
* @brief Funcion que te dice si un espacio esta iluminado o no
* 
* @author Julia Simon
* @param space espacio 
* @return OK si se ha hecho correctamente, y ERROR en caso contrario
*/
BOOL space_get_iluminado(Space* space);

/** 
* @brief Funcion encargada de darnos el tamaño del espacio
* Esta funcion se va a utilizar para guardar los espacios en un fichero
* 
* @author Julia Simon
* @return tamaño de la estructura space
*/
size_t space_get_size();

/**
* @brief Funcion encargada de añadir un objeto en el conjunto de objetos del espacio
* 
* @author Julia Simon 
* @param space espacio actual
* @param id  del objeto que se va a añadir al conjunto de objetos del espacio
* @return OK si se ha añadido el objeto correctamente y ERROR en caso de error
*/
STATUS space_add_objects(Space* space, Id id);

/**
* @brief Funcion encargada de eliminar un objeto en el conjunto de objetos del espacio
* 
* @author Miguel Rodriguez
* @param space espacio actual
* @param id del objeto que se va a eliminar del conjunto de objetos del espacio
* @return OK si se ha eliminadp el objeto correctamente y ERROR en caso de error
*/
STATUS space_del_objects(Space* space, Id id);


/** 
* @brief Funcion encargada de decirnos si un objeto esta en el espacio
* 
* @author Julia Simon 
* @param space espacio del que se quiere saber si tiene cierto objeto
* @return TRUE si el objeto se encuentra en el espacio o FALSE en caso contrario/error
*/
BOOL space_object_in(Space* space, Id id);



/** 
* @brief Funcion encargada de darnos toda la informacion de un espacio
* 
* @author Miguel Rodriguez
* @param space espacio del que se quiere saber toda la informacion
* @return OK si se ha impreso correctamente la informacion en el fichero, y ERROR en caso contrario
*/
STATUS space_print(Space* space);

#endif
