/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @version 5.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "gamereader.h"
/**
 * @brief It defines the number of callbacks
 */
#define N_CALLBACK 11
/**
 * @brief defines structure of game
 */
struct _Game{
/**
 * @brief defines array of object
 */
  Object * object[MAX_IDs_SET];
/**
 * @brief defines pointer to player
 */
  Player *player;
/**
 * @brief defines pointer to array of spaces
 */
  Space* spaces[MAX_SPACES + 1];
/**
 * @brief defines last_cmd
 */
  T_Command last_cmd;
/**
 * @brief defines cmd_status
 */
  STATUS cmd_status;
/**
 * @brief defines pointer to die
 */
  Die *die;
/**
 * @brief definesarray of  objdsc
 */
  char objdsc[WORD_SIZE + 1];
/**
 * @brief defines array of links
 */
  Link* links[MAX_SPACES + 1];
};
/**
   Define the function type for the callbacks
*/
typedef STATUS (*callback_fn)(Game* game);

/**
 * @brief callback to unknown
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_unknown(Game* game);
/**
 * @brief callback to exit
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_exit(Game* game);
/**
 * @brief callback to next
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_next(Game* game);
/**
 * @brief callback to back
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_back(Game* game);
/**
 * @brief callback to pick
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Pick(Game* game);
/**
 * @brief callback to drop
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Drop(Game* game);
/**
 * @brief callback to roll
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Roll(Game* game);
/**
 * @brief callback to left
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Left(Game* game);
/**
 * @brief callback to right
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Right(Game* game);
/**
 * @brief callback to move
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Move(Game* game);
/**
 * @brief callback to inspect
 *
 * @param game
 *
 * @return OK or ERROR
 */
STATUS game_callback_Inspect(Game* game);
/**
 * @brief  get callback
 *
 * @param game
 *
 * @return OK or ERROR
 */
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
  game_callback_Move,
  game_callback_Inspect,
};

/**
   Private functions
*/
/**
 * @brief load spaces
 *
 * @param game
 * @param filename
 *
 * @return OK or ERROR
 */
STATUS game_load_spaces(Game* game, char* filename);
/**
 * @brief get spaces
 *
 * @param game
 * @param position
 *
 * @return id or NULL
 */
Id     game_get_space_id_at(Game* game, int position);
/**
 * @brief set player location
 *
 * @param game
 * @param id
 *
 * @return OK or ERROR
 */
STATUS game_set_player_location(Game* game, Id id);
/**
 * @brief set object location
 *
 * @param game
 * @param id
 * @param loc
 *
 * @return OK or ERROR
 */
STATUS game_set_object_location(Game* game, Id id, Id loc);

Game *game_create() {
  int i;
  Game *game=NULL;
  game=(Game*)malloc(sizeof(Game));
  if(!game) return NULL;
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++) {
    game->links[i] = NULL;
  }

  game->player=player_create(0);
  player_set_location(game->player,NO_ID);
  player_set_name(game->player,">8D");
  for(i=0;i<MAX_IDs_SET;i++){
    game->object[i]=NULL;
  }

  game->die=die_create((Id)1);
  game->objdsc[0]='\0';
  game->last_cmd = NO_CMD;
  game->cmd_status=OK;

  return game;
}
/*Function to create a game file, in case of error it returns ERROR*/
STATUS game_create_from_file(Game* game, char* filename) {

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_load_objects(game, filename) == ERROR)
      return ERROR;

  if (game_load_links(game, filename) == ERROR)
      return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));

  return OK;
}
/*Function to destoy a game, in case of error it returns ERROR*/
STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0;i < MAX_SPACES; i++) {
    space_destroy(game->spaces[i]);
  }
  for (i = 0;i < MAX_LINKS; i++) {
    link_destroy(game->links[i]);
  }
  for (i = 0; (i < MAX_IDs_SET) && (game->object[i] != NULL); i++) {
    object_destroy(game->object[i]);
  }
  player_destroy(game->player);
  die_destroy(game->die);
  free(game);
  return OK;
}

/*Game set active object description*/
STATUS game_set_objdsc(Game* game, char* objdsc){
if (!game||!objdsc) return ERROR;
strcpy(game->objdsc,objdsc);
return OK;}

/*Game get active object description*/
char* game_get_objdsc(Game* game){
if (!game) return NULL;
return game->objdsc;}

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
/**
 * @brief updates the game
 *
 * @param game
 * @param cmd
 *
 * @return OK or ERROR
 */
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
    if (current_id == space_id && link_get_status(game_get_link(game,space_get_south(game->spaces[i])))==1) {
      if(current_id==link_get_space1(game_get_link(game,space_get_south(game->spaces[i])))){
        current_id=link_get_space2(game_get_link(game,space_get_south(game->spaces[i])));
      }
      else{
        current_id=link_get_space1(game_get_link(game,space_get_south(game->spaces[i])));
      }
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
    if (current_id == space_id && link_get_status(game_get_link(game,space_get_north(game->spaces[i])))==1) {
      if(current_id==link_get_space1(game_get_link(game,space_get_north(game->spaces[i])))){
        current_id=link_get_space2(game_get_link(game,space_get_north(game->spaces[i])));
      }
      else{
        current_id=link_get_space1(game_get_link(game,space_get_north(game->spaces[i])));
      }
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
if(player_location==object_location){

player_add_object(game->player,object_get_id(game->object[i]));
object_set_location(game->object[i],0);
return OK;

}
return ERROR;
}
/*
for(j=0, j<MAX_IDs_SET, j++){
if (player_get_object(game->player, j)==object_id){
player_add_object(game->player,object_get_id(game->object[i]));

object_set_location(game->object[i],0);
return OK;
}
}
*/
STATUS game_callback_Drop(Game* game)
{
char objectstr[WORD_SIZE]="";
int i, j, found=0;
Id object_id=NO_ID;
if(!game) return ERROR;

scanf("%s",objectstr);
/*Buscamos en game el objeto con ese nombre*/
for(i=0;i<MAX_IDs_SET && game->object[i]!=NULL;i++){
  if(!strcmp(object_get_name(game_get_object(game,game_get_objectId(game,i))),objectstr)) break;
}
/*Sacamos su correspondiente id*/
object_id=game_get_objectId(game, i);
if (object_id==NO_ID) return ERROR;
/*Buscamos esa id en la bolsa del player*/
for(j=0; j<MAX_IDs_SET; j++) {
if (player_get_object(game->player, j)==object_id) {
found=1;
break;
}
}
/*Salimos si no lo tiene*/
if (found==0) return ERROR;
/*Quitamos el objeto del jugador*/
player_del_object(game->player,object_id);
object_set_location(game->object[i],player_get_location(game->player));
return OK;
}

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
    if (current_id == space_id && link_get_status(game_get_link(game,space_get_west(game->spaces[i])))==1) {
      if(current_id==link_get_space1(game_get_link(game,space_get_west(game->spaces[i])))){
        current_id=link_get_space2(game_get_link(game,space_get_west(game->spaces[i])));
      }
      else{
        current_id=link_get_space1(game_get_link(game,space_get_west(game->spaces[i])));
      }
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
    if (current_id == space_id && link_get_status(game_get_link(game,space_get_east(game->spaces[i])))==1) {
      if(current_id==link_get_space1(game_get_link(game,space_get_east(game->spaces[i])))){
        current_id=link_get_space2(game_get_link(game,space_get_east(game->spaces[i])));
      }
      else{
        current_id=link_get_space1(game_get_link(game,space_get_east(game->spaces[i])));
      }
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
  return OK;
      }
      return ERROR;
    }
  }

  return ERROR;
}
/*MOVE*/
STATUS game_callback_Move(Game* game){
char input[WORD_SIZE]="";
scanf("%s",input);

 if (strcmp(input, "n")==0 || strcmp(input, "north")==0) {
    return game_callback_back(game);
 }else if(strcmp(input, "s")==0 || strcmp(input, "south")==0) {
    return game_callback_next(game);
 }else if(strcmp(input, "e")==0 || strcmp(input, "east")==0) {
    return game_callback_Right(game);
 }else if(strcmp(input, "w")==0 || strcmp(input, "west")==0) {
    return game_callback_Left(game);
 }

return ERROR;

}

/*Inspect*/
STATUS game_callback_Inspect(Game* game){
char objectstr[WORD_SIZE]="";
int i, j, found =0;
char desc[WORD_SIZE]="";
Id playerlocation=NO_ID;
if(!game) return ERROR;

scanf("%s",objectstr);
if (strcmp(objectstr, "s")==0){
  playerlocation = game_get_player_location(game);
  strcpy(desc, space_get_description(game_get_space(game, playerlocation)));
  game_set_objdsc(game, desc);

  return OK;
}
for(i=0;i<MAX_IDs_SET && game->object[i]!=NULL;i++){
  if(!strcmp(object_get_name(game_get_object(game,game_get_objectId(game,i))),objectstr)) break;
}
  for(j=0; j<MAX_IDs_SET; j++) {
  if (player_get_object(game->player, j)==game_get_objectId(game,i)) {
  found=1;
  break;
  }
  }
  if(game_get_object_location(game,game_get_objectId(game,i))==game_get_player_location(game) || found ==1){

    strcpy(desc, object_get_description(game_get_object(game, game_get_objectId(game,i))));

    game_set_objdsc(game, desc);

    return OK;
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
/**
 * @brief get the object in the game
 *
 * @param g
 * @param id
 *
 * @return id or in case of error NULL
 */
Object *game_get_object(Game *g,Id id){
  int i;
  if(!g) return NULL;
  for(i=0;i<MAX_IDs_SET;i++){
    if(object_get_id(g->object[i])==id) break;
  }
  return g->object[i];
}

Link *game_get_link(Game *game,Id id){
  int i;
  if(!game || id==NO_ID) return NULL;

  for(i=0;(i<MAX_LINKS) && (game->links[i]!=NULL);i++){
    if(link_get_id(game->links[i])==id) break;
  }
  if(!game->links[i]) return NULL;

  return game->links[i];
}

Object *game_get_objectbypos(Game *game,Id i){
  if(!game || i<0 || i>MAX_IDs_SET) return NULL;
  return game->object[i];
}

STATUS game_set_objectbypos(Game *game,Id i,Object *object){
  if(!game || i<0 || i>MAX_SPACES || !object) return ERROR;
  game->object[i]=object;
  return OK;
}

Player *game_get_player(Game *game){
  if(!game) return NULL;
  return game->player;
}

Space *game_get_spacebypos(Game *game,Id i){
  if(!game || i<0 || i>MAX_SPACES) return NULL;
  return game->spaces[i];
}

STATUS game_set_spacebypos(Game *game,Id i,Space *space){
  if(!game || i<0 || i>MAX_SPACES || !space) return ERROR;
  game->spaces[i]=space;
  return OK;
}

Link *game_get_linkbypos(Game *game,Id i){
  if(!game || i<0 || i>MAX_SPACES) return NULL;
  return game->links[i];
}

STATUS game_set_linkbypos(Game *game,Id i,Link *link){
  if(!game || i<0 || i>MAX_SPACES || !link) return ERROR;
  game->links[i]=link;
  return OK;
}

