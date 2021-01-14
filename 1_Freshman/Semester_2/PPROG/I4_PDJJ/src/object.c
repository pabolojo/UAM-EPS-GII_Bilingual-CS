/**
 * @brief It defines the module object
 *
 * @file object.h
 * @version 7.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "game.h"

/**
 * @brief defines object structure
 */
struct _Object {
/**
 * @brief defines id
 */
  Id id;
/**
 * @brief defines string name
 */
  char name[WORD_SIZE + 1];
/**
 * @brief defines string description
 */
  char description[WORD_SIZE + 1];
/**
 * @brief defines id location
 */
  Id location;
/**
 * @brief defines id location
 */
  Id InitLocation;
/**
 * @brief defines movable
 */
BOOL movable;
/**
 * @brief defines moved
 */
BOOL moved;
/**
 * @brief defines hidden
 */
BOOL hidden;
/**
 * @brief defines illuminate
 */
BOOL illuminate;
/**
 * @brief defines turnedOn
 */
BOOL turnedOn;
/**
 * @brief defines open
 */
Id open;
/**
 * @brief defines altdescription with WORD_SIZE + 1 size
 */
char altdescription[WORD_SIZE + 1];

};

/*Function to create an object, in case of error it returns ERROR*/
Object* object_create(Id id) {

  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));

  if (newObject == NULL) return NULL;
  
  newObject->id = id;

  newObject->name[0] = '\0';
 
  newObject->description[0] = '\0'; 

  newObject->altdescription[0] = '\0'; 

  newObject->location = NO_ID;

  newObject->InitLocation = NO_ID;

  newObject->movable = FALSE;
 
  newObject->moved = FALSE; 

  newObject->hidden = FALSE; 

  newObject->illuminate = FALSE;

  newObject->turnedOn = FALSE;

  newObject->open = NO_ID;

  return newObject;
}

/*Function to destroy an object, in case of error it returns ERROR*/
STATUS object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

/*Function to set the name of an object, in case of error it returns ERROR*/
STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

/*Function to set the description of an object, in case of error it returns ERROR*/
STATUS object_set_description(Object* object, char* desc) {
  if (!object || !desc) {
    return ERROR;
  }

  if (!strcpy(object->description, desc)) {
    return ERROR;
  }

  return OK;
}
/*Function to set the ID of an object, in case of error it returns ERROR*/
STATUS object_set_location(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->location = id;
  return OK;
}

/*Function to set the ID of an object, in case of error it returns ERROR*/
STATUS object_set_InitLocation(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->InitLocation = id;
  return OK;
}
/*Function to get the name of an object, in case of error it returns NULL. As the name is a string, it returns it as a pointer*/
const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

/*Function to get the description of an object, in case of error it returns NULL. As the description is a string, it returns it as a pointer*/
const char * object_get_description(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->description;
}

/*Function to get the ID of an object, in case of error it returns NO_ID. */
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

/*Function to get the location of an object, in case of error it returns NO_ID. */
Id object_get_location(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->location;
}

/*Function to get the location of an object, in case of error it returns NO_ID. */
Id object_get_InitLocation(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->InitLocation;
}

/*Function to print the name and id of an object*/
STATUS object_print(Object* object) {
  Id idaux = NO_ID;

  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  idaux = object_get_location(object);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }

  return OK;
}

/*SETS*/

STATUS object_set_movable (Object *object, BOOL b) {
if (!object) return ERROR;

object->movable=b;

return OK;
}

STATUS object_set_moved (Object *object, BOOL b) {
if (!object || !object_get_movable(object)) return ERROR;

object->moved=b;

return OK;
}

STATUS object_set_hidden (Object *object, BOOL b) {
if (!object) return ERROR;

object->hidden=b;

return OK;
}

STATUS object_set_illuminate (Object *object, BOOL b) {
if (!object) return ERROR;

object->illuminate=b;

return OK;
}

STATUS object_set_turnedOn (Object *object, BOOL b) {
if (!object || !object_get_illuminate(object)) return ERROR;

object->turnedOn=b;

return OK;
}

STATUS object_set_open (Object *object, Id id) {
if (!object) return ERROR;

object->open=id;

return OK;
}

/*GETS*/

BOOL object_get_movable (Object *object) {
return object->movable; 
}

BOOL object_get_moved (Object *object) {
return object->moved; 
}

BOOL object_get_hidden (Object *object) {
return object->hidden; 
}

BOOL object_get_illuminate (Object *object) {
return object->illuminate; 
}

BOOL object_get_turnedOn (Object *object) {
return object->movable; 
}

BOOL object_get_open (Object *object) {
return object->open; 
}

STATUS object_set_altdescription(Object* object, char* desc) {
  if (!object || !desc) {
    return ERROR;
  }

  if (!strcpy(object->altdescription, desc)) {
    return ERROR;
  }

  return OK;
}

const char * object_get_altdescription(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->altdescription;
}


