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

typedef struct _Object Object;
Object* object_create(Id id);
STATUS object_destroy(Object* object);
STATUS object_set_name(Object* object, char* name);
STATUS object_set_location(Object* object, Id id);
const char * object_get_name(Object* object);
Id object_get_id(Object* object);
Id object_get_location(Object* object);
STATUS object_print(Object* object);
#endif

