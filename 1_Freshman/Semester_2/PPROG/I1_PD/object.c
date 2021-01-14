/** 
 * 
 * this document is object.c and exports the functions of object on game.c
 * @author Domingo and Andres 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "game.h"

struct _Object {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
};

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

STATUS object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS object_set_location(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->location = id;
  return OK;
}


const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

Id object_get_location(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->location;
}


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



