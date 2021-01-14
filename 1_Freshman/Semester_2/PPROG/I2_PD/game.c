/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @version 3.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "gamereader.h"

#define N_CALLBACK 9

/**
   Define the function type for the callbacks
*/
typedef STATUS (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
STATUS game_callback_unknown(Game* game);
STATUS game_callback_exit(Game* game);
STATUS game_callback_next(Game* game);
STATUS game_callback_back(Game* game);
STATUS game_callback_Pick(Game* game);
STATUS game_callback_Drop(Game* game);
STATUS game_callback_Roll(Game* game);
STATUS game_callback_Left(Game* game);
STATUS game_callback_Right(Game* game);
STATUS game_get_callback_status(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_next,
  game_callback_back,
  game_callback_Pick,
  game_callback_Drop,
  game_callback_Roll,
  game_callback_Left,
  game_callback_Right,
};

/**
   Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
/*STATUS game_add_space(Game* game, Space* space);
STATUS game_add_object(Game* game, Object* object);*/
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id, Id loc);

/**
   Game interface implementation
*/
/*Function to create a game, in case of error it returns ERROR*/
STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->player=player_create(0);
  player_set_location(game->player,NO_ID);
  player_set_name(game->player,">8D");
  for(i=0;i<MAX_IDs_SET;i++){
    game->object[i]=NULL;
  }

  game->die=die_create((Id)1);
  game->last_cmd = NO_CMD;
  game->cmd_status=OK;

  return OK;
}
/*Function to create a game file, in case of error it returns ERROR*/
STATUS game_create_from_file(Game* game, char* filename) {
  if (game_create(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_load_objects(game, filename) == ERROR)
      return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));

  return OK;
}
/*Function to destoy a game, in case of error it returns ERROR*/
STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }
  for (i = 0; (i < MAX_IDs_SET) && (game->object[i] != NULL); i++) {
    object_destroy(game->object[i]);
  }
  player_destroy(game->player);
  die_destroy(game->die);
  return OK;
}

/*Function to get id od game, in case of error it returns no id*/
Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}
/*Function to get space of game, in case of error it returns no id*/
Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}
/*Function to set location of game, in case of error it returns no ERROR*/
STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }
  return player_set_location(game->player,id);


}
/*Function to set object location of game, in case of error it returns no ERROR*/
STATUS game_set_object_location(Game* game, Id id, Id loc) {

  int i = 0;

  if (id == NO_ID) {
    return ERROR;
  }
  for(i=0;i<MAX_IDs_SET;i++){
    if(object_get_id(game->object[i])==id) break;
  }
  return object_set_location(game->object[i],loc);

  return OK;
}
/*Function to get player of game, in case of error it returns no ERROR*/
Id game_get_player_location(Game* game) {
  return player_get_location(game->player);
}
/*Function to get object of game, in case of error it returns no ERROR*/
Id game_get_object_location(Game* game,Id id) {
  int i=0;
  for(i=0;i<MAX_IDs_SET;i++){
    if(object_get_id(game->object[i])==id) break;
  }
  return object_get_location(game->object[i]);
}

STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  game->cmd_status=(*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}
/*Function to print the game data*/
void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object locations:\n");
  for(i=0;i<MAX_IDs_SET;i++){
    printf("%d:%d\n",(int)object_get_id(game->object[i]),(int) object_get_location(game->object[i]));
  }
  printf("=> Player location: %d\n", (int) player_get_location(game->player));
  printf("prompt:> ");
}
/*chech if game is over*/
BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action
*/
/*f checks callbacks */
STATUS game_callback_unknown(Game* game) {
  return OK;
}
/*f checks callbacks */
STATUS game_callback_exit(Game* game) {
  return OK;
}
/*f checks callbacks */
STATUS game_callback_next(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
  return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}
/*f checks callbacks */
STATUS game_callback_back(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
  return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_callback_Pick(Game* game)
{
  /*NO SE UPDATEA EN EL GRAPHIC ENGINE*/
 char objectstr[WORD_SIZE]="";
 Id player_location;
 Id object_location;
 int i;

 scanf("%s",objectstr);
 player_location=player_get_location(game->player);
 for(i=0;i<MAX_IDs_SET && game->object[i]!=NULL;i++){
   if(!strcmp(object_get_name(game_get_object(game,game_get_objectId(game,i))),objectstr)) break;
 }

 if(i==MAX_IDs_SET) return ERROR;

 object_location=object_get_location(game->object[i]);
if(player_location==object_location)
{
  if(player_get_object(game->player)==NO_ID){
player_set_object(game->player,object_get_id(game->object[i]));
object_set_location(game->object[i],0);
return OK;}
}
return ERROR;
}

STATUS game_callback_Drop(Game* game)
{
char objectstr[WORD_SIZE]="";
int i;
if(!game) return ERROR;

scanf("%s",objectstr);

for(i=0;i<MAX_IDs_SET && game->object[i]!=NULL;i++){
  if(!strcmp(object_get_name(game_get_object(game,game_get_objectId(game,i))),objectstr)) break;
}

if(player_get_object(game->player)==object_get_id(game->object[i]))
{
player_set_object(game->player,NO_ID);
object_set_location(game->object[i],player_get_location(game->player));
return OK;
}
return ERROR;
}
/*f checks callbacks */
STATUS game_callback_Roll(Game* game){
  die_roll(game->die);
  return OK;
}

int game_get_die_value(Game* game){
  return die_get_value(game->die);
}

STATUS game_callback_Left(Game* game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
  return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_callback_Right(Game* game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
  return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_get_callback_status(Game* game){
  return game->cmd_status;
}

Id game_get_objectId(Game *game,int i){
  if(!game) return NO_ID;
  return object_get_id(game->object[i]);
}

Object *game_get_object(Game *g,Id id){
  int i;
  if(!g) return NULL;
  for(i=0;i<MAX_IDs_SET;i++){
    if(object_get_id(g->object[i])==id) break;
  }
  return g->object[i];
}

