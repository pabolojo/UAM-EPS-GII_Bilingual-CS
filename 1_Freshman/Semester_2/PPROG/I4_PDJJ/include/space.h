/**
 * @brief It defines a space
 *
 * @file space.h
 * @version 6.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"
#include "link.h"
/**
 * @brief defines the space structure
 *
 */
typedef struct _Space Space;
/**
 * @brief defines the max of spaces
 *
 */
#define MAX_SPACES 100
/**
 * @brief defines fisrt space
 *
 */
#define FIRST_SPACE 1
/**
 * @brief create the space in the game
 *
 * @param id
 *
 * @return space or in case of error NULL
 */
Space* space_create(Id id);
/**
 * @brief destroy the space in the game
 *
 * @param space
 *
 * @return OK, or ERROR
 */
STATUS space_destroy(Space* space);
/**
 * @brief get the id of space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_id(Space* space);
/**
 * @brief set the id of space
 *
 * @param space
 * @param name
 *
 * @return OK, or ERROR
 */
STATUS space_set_name(Space* space, char* name);
/**
 * @brief get the name of space
 *
 * @param space
 *
 * @return name of space or in case of error NULL
 */
const char* space_get_name(Space* space);
/**
 * @brief set the north id of space
 *
 * @param space
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS space_set_north(Space* space, Id id);
/**
 * @brief get the north id of space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_north(Space* space);
/**
 * @brief set the south id of space
 *
 * @param space
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS space_set_south(Space* space, Id id);
/**
 * @brief get the south id of space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_south(Space* space);
/**
 * @brief set the east id of space
 *
 * @param space
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS space_set_east(Space* space, Id id);
/**
 * @brief get the east id of space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_east(Space* space);
/**
 * @brief set the west id of space
 *
 * @param space
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS space_set_west(Space* space, Id id);
/**
 * @brief get the west id of space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_west(Space* space);
/**
 * @brief set up of the space
 *
 * @param space
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS space_set_up(Space* space, Id id);
/**
 * @brief get up of the space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_up(Space* space);
/**
 * @brief set down the space
 *
 * @param space
 * @param id
 *
 * @return OK, or ERROR
 */
STATUS space_set_down(Space* space, Id id);
/**
 * @brief get down to the space
 *
 * @param space
 *
 * @return id or in case of error NULL
 */
Id space_get_down(Space* space);
/**
 * @brief get the object to the space
 *
 * @param space
 * @param value
 *
 * @return id or in case of error NULL
 */
STATUS space_set_object(Space* space, Id value);
/**
 * @brief get the object to the space
 *
 * @param space
 *
 * @return set or in case of error NULL
 */
Set *space_get_object(Space* space);
/**
 * @brief print the object of the space
 *
 * @param space
 *
 * @return OK, or ERROR
 */
STATUS space_print(Space* space);
/**
 * @brief get the objec gdesc
 *
 * @param space
 * @param i
 *
 * @return char or in case of error NULL
 */
char *space_get_gdesc(Space *space,int i);
/**
 * @brief set the objec gdesc
 *
 *
 * @return char or in case of error NULL
 */
char *space_create_gdesc();
/**
 * @brief set the objec gdesc to space
 *
 * @param space
 * @param  i
 * @param  str
 *
 * @return OK, or ERROR
 */
STATUS space_set_gdesc(Space *space,char *str,int i);
/**
 * @brief set the descripcion of objects
 *
 * @param space
 * @param desc
 *
 * @return OK, or ERROR
 */
STATUS space_set_description(Space *space, char* desc);
/**
 * @brief set the ldescripcion of objects
 *
 * @param space
 * @param desc
 *
 * @return OK, or ERROR
 */
STATUS space_set_ldescription(Space *space, char* desc);
/**
 * @brief get the descripcion of objects
 *
 * @param space
 *
 * @return description or in case of error NULL
 */
const char *space_get_description(Space *space);
/**
 * @brief get the ldescripcion of objects
 *
 * @param space
 *
 * @return ldescription or in case of error NULL
 */
const char *space_get_ldescription(Space *space);
/**
 * @brief get the ilum of objects
 *
 * @param space
 *
 * @return TRUE or FALSE
 */
BOOL space_get_ilum(Space *space);
/**
 * @brief set the ilum of objects
 *
 * @param space
 * @param ilum
 *
 * @return OK, or ERROR
 */
STATUS space_set_ilum(Space *space, BOOL ilum);

#endif

