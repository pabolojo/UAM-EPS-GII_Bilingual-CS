/**
 * @brief It defines the header of the module object
 *
 * @file object.h
 * @version 3.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
/**
 * @brief defines the Object structure
 *
 */
typedef struct _Object Object;
/**
 * @brief create the object in the game
 *
 * @param id
 * 
 * @return object or in case of error NULL
 */
Object* object_create(Id id);
/**
 * @brief destroy the object in the game
 *
 * @param object
 * 
 * @return OK, or ERROR
 */
STATUS object_destroy(Object* object);
/**
 * @brief set a name to the object
 *
 * @param object
 * @param name
 * 
 * @return OK, or ERROR
 */
STATUS object_set_name(Object* object, char* name);
/**
 * @brief set a  location to the name of the object
 *
 * @param object
 * @param id
 * 
 * @return OK, or ERROR
 */
STATUS object_set_location(Object* object, Id id);
/**
 * @brief set a INIT location to the name of the object
 *
 * @param object
 * @param id
 * 
 * @return OK, or ERROR
 */
STATUS object_set_InitLocation(Object* object, Id id);
/**
 * @brief get the name of the object
 *
 * @param object
 * 
 * @return name of the object or in case of Error NULL
 */
const char * object_get_name(Object* object);
/**
 * @brief get the id of the object
 *
 * @param object
 * 
 * @return id or in case of error NULL
 */
Id object_get_id(Object* object);
/**
 * @brief get the location of the object
 *
 * @param object
 * 
 * @return id or in case of error NULL
 */
Id object_get_location(Object* object);
/**
 * @brief get the init location of the object
 *
 * @param object
 * 
 * @return id or in case of error NULL
 */
Id object_get_InitLocation(Object* object);
/**
 * @brief print the object
 *
 * @param object
 * 
 * @return OK, or ERROR
 */
STATUS object_print(Object* object);
/**
 * @brief set the descripcion of object
 *
 * @param object
 * @param desc
 * 
 * @return OK, or ERROR
 */
STATUS object_set_description(Object* object, char* desc);
/**
 * @brief gives the descripcion of object
 *
 * @param object
 * @param desc
 * 
 * @return name or NULL in case of error
 */

STATUS object_set_altdescription(Object* object, char* desc);
/**
 * @brief get the descripcion of object
 *
 * @param object
 * 
 * @return object name or NULL
 */

const char * object_get_description(Object* object);
/**
 * @brief set the movable of object
 *
 * @param object
 * @param b
 * 
 * @return OK, or ERROR
 */

STATUS object_set_movable (Object *object, BOOL b);
/**
 * @brief set the moved of object
 *
 * @param object
 * @param b
 * 
 * @return OK, or ERROR
 */

STATUS object_set_moved (Object *object, BOOL b);
/**
 * @brief set the hidden of object
 *
 * @param object
 * @param b
 * 
 * @return OK, or ERROR
 */

STATUS object_set_hidden (Object *object, BOOL b);
/**
 * @brief set the illuminate of object
 *
 * @param object
 * @param b
 * 
 * @return OK, or ERROR
 */

STATUS object_set_illuminate (Object *object, BOOL b);
/**
 * @brief set the turnedOn of object
 *
 * @param object
 * @param b
 * 
 * @return OK, or ERROR
 */

STATUS object_set_turnedOn (Object *object, BOOL b);
/**
 * @brief set the open of object
 *
 * @param object
 * @param id
 * 
 * @return OK, or ERROR
 */

STATUS object_set_open (Object *object, Id id);   
/**
 * @brief get the movable of object
 *
 * @param object
 * 
 * @return TRUE or FALSE
 */

BOOL object_get_movable (Object *object);
/**
 * @brief get the moved of object
 *
 * @param object
 * 
 * @return TRUE or FALSE
 */

BOOL object_get_moved (Object *object);
/**
 * @brief get the hidden of object
 *
 * @param object
 * 
 * @return TRUE or FALSE
 */

BOOL object_get_hidden (Object *object);
/**
 * @brief get the illuminate of object
 *
 * @param object
 * 
 * @return TRUE or FALSE
 */

BOOL object_get_illuminate (Object *object);
/**
 * @brief get the turnedOn of object
 *
 * @param object
 * 
 * @return TRUE or FALSE
 */

BOOL object_get_turnedOn (Object *object);
/**
 * @brief get the open of object
 *
 * @param object
 * 
 * @return TRUE or FALSE  
 */

BOOL object_get_open (Object *object);
/**
 * @brief get the altdescription of object
 *
 * @param object
 * 
 * @return altdescription or NULL in case of error
 */


const char * object_get_altdescription(Object* object);


#endif

