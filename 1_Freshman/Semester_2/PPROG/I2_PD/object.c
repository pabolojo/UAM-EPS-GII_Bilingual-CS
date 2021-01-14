/**
 * @brief It defines the module object
 *
 * @file object.h
 * @version 5.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "game.h"

/*Structure of an object*/
struct _Object {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
};

/*Function to create an object, in case of error it returns ERROR*/
Object* object_create(Id id) {

  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));

  if (newObject == NULL) {
    return NULL;
  }
  newObject->id = id;

  newObject->name[0] = '\0';

  newObject->location = NO_ID;

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
/*Function to set the ID of an object, in case of error it returns ERROR*/
STATUS object_set_location(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->location = id;
  return OK;
}

/*Function to get the name of an object, in case of error it returns NULL. As the name is a string, it returns it as a pointer*/
const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
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




