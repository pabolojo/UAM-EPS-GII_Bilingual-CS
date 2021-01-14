/**
 * @brief It defines the module of space
 *
 * @file space.c
 * @version 2.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

/**
 * @brief defines the structure of space
 */
struct _Space {
/**
 * @brief defines id
 */
  Id id;
/**
 * @brief defines string name
 */
  char name[WORD_SIZE + 1];
/**
 * @brief defines id north
 */
  Id north;
/**
 * @brief defines id south
 */
  Id south;
/**
 * @brief defines id east
 */
  Id east;
/**
 * @brief defines id west
 */
  Id west;
/**
 * @brief defines set of objects
 */
  Set *object;
/**
 * @brief defines gdesc1
 */
  char *gdesc1;
/**
 * @brief defines gdesc2
 */
  char *gdesc2;
/**
 * @brief defines gdesc3
 */
  char *gdesc3;
/**
 * @brief defines description
 */
  char description[WORD_SIZE + 1];
};

/*Function to create an space, in case of error it returns ERROR*/
Space* space_create(Id id) {

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;
 /*in case of allocation memory it set the characteristics of space name,location,id ,north...*/
  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->object=set_create();
  newSpace->gdesc1=space_create_gdesc();
  newSpace->gdesc2=space_create_gdesc();
  newSpace->gdesc3=space_create_gdesc();
  newSpace->description[0]='\0';
  if(!newSpace->gdesc1 || !newSpace->gdesc2 || !newSpace->gdesc3){
    space_destroy(newSpace);
    return NULL;
  }

  return newSpace;
}

/*Function to destroy space, in case of error it returns ERROR*/
STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }
  set_destroy(space->object);
  free(space->gdesc1);
  space->gdesc1=NULL;
  free(space->gdesc2);
  space->gdesc2=NULL;
  free(space->gdesc3);
  space->gdesc3=NULL;
  free(space);
  space = NULL;

  return OK;
}

/*Function to set the name of scpace, in case of error it returns ERROR*/
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}
/*Funtion to set the description of space, in case of error it returns ERROR*/
STATUS space_set_description(Space *space, char* desc){
  if (!space || !desc) return ERROR;
  if (!strcpy(space->description, desc)) return ERROR;
  return OK;
}

/*Function to set the north of space, in case of error it returns ERROR*/
STATUS space_set_north(Space* space, Id id) {
  if (!space || id==NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

/*Function to set the south of space, in case of error it returns ERROR*/
STATUS space_set_south(Space* space, Id id) {
  if (!space || id==NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

/*Function to set the east of space, in case of error it returns ERROR*/
STATUS space_set_east(Space* space, Id id) {
  if (!space || id==NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

/*Function to set the west of space, in case of error it returns ERROR*/
STATUS space_set_west(Space* space, Id id) {
  if (!space || id==NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/*Function to set object of space, in case of error it returns ERROR*/
STATUS space_set_object(Space* space, Id value) {
  if (!space) {
    return ERROR;
  }
  set_id_add(space->object,value);
  return OK;
}
/*Function to get the description of space, in case of error it returns NULL*/
const char *space_get_description(Space *space){
  if (!space) return NULL;
  return space->description;
}

/*Function to get the name of space, in case of error it returns NULL*/
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}
/*Function to get the
ID of space, in case of error it returns NO ID*/
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}
/*Function to get the
north of space, in case of error it returns NO ID*/
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}
/*Function to get the
south of space, in case of error it returns NO ID*/
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}
/*Function to get the
east of space, in case of error it returns NO ID*/
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}
/*Function to get the
west of space, in case of error it returns NO ID*/
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

/*Function to get the
object of space, in case of error it returns NO ID*/
Set *space_get_object(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->object;
}

/*Function to  print space, in case of error it returns ERROR*/
STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  Set *aux=NULL;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
/*NORTH*/
  idaux = space_get_north(space);
  if (idaux) {
    fprintf(stdout, "---> North space %ld.\n",idaux);
  } else {
    fprintf(stdout, "---> No north space.\n");
  }
/*SOUTH*/
  idaux = space_get_south(space);
  if (idaux) {
    fprintf(stdout, "---> North space %ld.\n",idaux);
  } else {
    fprintf(stdout, "---> No south space.\n");
  }

  idaux = space_get_east(space);
  if (idaux) {
    fprintf(stdout, "---> North space %ld.\n",idaux);
  } else {
    fprintf(stdout, "---> No east space.\n");
  }
/*EAST*/
  idaux = space_get_west(space);
  if (idaux) {
    fprintf(stdout, "---> North space %ld.\n",idaux);
  } else {
    fprintf(stdout, "---> No west space.\n");
  }
/*WEST*/
  if ((aux=space_get_object(space))) {
    fprintf(stdout, "---> Objects in the space:\n");
    set_print(aux);
  } else {
    fprintf(stdout, "---> No objects in the space.\n");
  }

  fprintf(stdout,"|%s|\n",space->gdesc1);
  fprintf(stdout,"|%s|\n",space->gdesc2);
  fprintf(stdout,"|%s|\n",space->gdesc3);

  return OK;
}

char *space_get_gdesc(Space *space,int i){

  if(!space || i<0 || i>2) return NULL;
  if(i==0)return space->gdesc1;
  else if(i==1) return space->gdesc2;
  else return space->gdesc3;

}

char *space_create_gdesc(){

  char * aux=NULL;
  int i;
  aux=(char *)malloc(12*sizeof(char));
  if(!aux) return NULL;
  for(i=0;i<12;i++){
    aux[i]=0;
  }
  return aux;
}

STATUS space_set_gdesc(Space *space,char *str,int i){

  int j;
  if(!space || i<0 || i>2) return ERROR;
  if(i==0){
    for(j=0;j<11;j++){
      space->gdesc1[j]=str[j];
    }
  }
  else if(i==1){
    for(j=0;j<11;j++){
      space->gdesc2[j]=str[j];
    }
  }
  else{
    for(j=0;j<11;j++){
      space->gdesc3[j]=str[j];
    }
  }
  return OK;

}

