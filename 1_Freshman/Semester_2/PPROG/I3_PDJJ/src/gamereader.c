/**
 * @brief It defines the module of gamereader, contains different function of game, link,space
 *
 * @file gamereader.c
 * @version 2.0
 * @date 21-02-2019
 * @copyright GNU Public License
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamereader.h"
#define DEBUG

/**
   Private functions
*/
STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game_get_spacebypos(game,i) != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game_set_spacebypos(game,i,space);

  return OK;
}
/*module of game reader*/
STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL,*gdesc1=NULL,*gdesc2=NULL,*gdesc3=NULL,*gdesc4=NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }
  /*open the file*/
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      gdesc1 = strtok(NULL, "|");
      gdesc2 = strtok(NULL, "|");
      gdesc3 = strtok(NULL, "|");
      gdesc4 = strtok(NULL, "|");
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s|%s|\n", id, name, north, east, south, west, gdesc1,gdesc2,gdesc3, gdesc4);
#endif
/*set the location and ame*/
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_north(space, north);
	space_set_east(space, east);
	space_set_south(space, south);
	space_set_west(space, west);
  space_set_gdesc(space,gdesc1,0);
  space_set_gdesc(space,gdesc2,1);
  space_set_gdesc(space,gdesc3,2);
  space_set_description(space, gdesc4);
	game_add_space(game, space);
      }

    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}


STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* desc0=NULL;
  char* toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Object* object = NULL;
  STATUS status = OK;
  int i=0;

  if (!filename) {
    return ERROR;
  }
  /*open the file*/
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      desc0 = strtok(NULL, "|");

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|\n", id, name, location);
#endif
/*set the location and ame*/
if(i<MAX_IDs_SET){
      object = object_create(id);
      if (object != NULL) {
	object_set_name(object, name);
	object_set_location(object, location);
        object_set_description(object, desc0);
	game_add_object(game, object);
}}
i++;
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }
  fclose(file);

  return status;
}

STATUS game_add_object(Game* game, Object* object){
  int i = 0;

  if (object == NULL) {
    return ERROR;
  }

  while ( (i < MAX_IDs_SET) && (game_get_objectbypos(game,i) != NULL)){
    i++;
  }

  if (i >= MAX_IDs_SET) {
    return ERROR;
  }

  game_set_objectbypos(game,i,object);

  return OK;
}

/*Links-----------------------------------------------*/
/**
 * @brief add links
 *
 * @param game
 * @param link
 *
 * @return OK or ERROR
 */
STATUS game_add_link(Game* game, Link* link) {
  int i = 0;

  if (link == NULL) {
    return ERROR;
  }

  while ( (i < MAX_LINKS) && (game_get_linkbypos(game,i) != NULL)){
    i++;
  }

  if (i >= MAX_LINKS) {
    return ERROR;
  }

  game_set_linkbypos(game,i,link);

  return OK;
}
/*module of game reader*/
STATUS game_load_links(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, space1 = NO_ID, space2 = NO_ID, st = NO_ID;
  Link* link = NULL;
  STATUS status=OK;

  if (!filename) {
    return ERROR;
  }
  /*open the file*/
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      space1 = atol(toks);
      toks = strtok(NULL, "|");
      space2 = atol(toks);
      toks = strtok(NULL, "|");
      st = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|\n", id, name, space1, space2,st);
#endif
/*set the location and ame*/
      link = link_create(id);
      if (link != NULL) {
	link_set_name(link, name);
	link_set_space1(link, space1);
	link_set_space2(link, space2);
  link_set_status(link, st);
	game_add_link(game, link);
      }

    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

