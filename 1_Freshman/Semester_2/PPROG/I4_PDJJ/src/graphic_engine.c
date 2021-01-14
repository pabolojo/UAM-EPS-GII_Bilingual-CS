/**
 * @brief It defines the module of graphic_engine
 *
 * @file graphic_engine.c
 * @version 3.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"
#include <string.h>
/**
 * @brief defines structure of graphic engine
 */
struct _Graphic_engine{
/**
 * @brief defines the area of map
 */
 Area *map;
/**
 * @brief defines the area of descript
 */
Area *descript;
/**
 * @brief defines the area of banner
 */
Area *banner;
/**
 * @brief defines the area of help
 */
Area  *help;
/**
 * @brief defines the area of feedback
 */
Area *feedback;
};
/*creation of graphic engine*/
Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

  ge->map      = screen_area_init( 1, 1, 48, 15);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,17, 23,  1);
  ge->help     = screen_area_init( 1,18, 78,  3);
  ge->feedback = screen_area_init( 1,22, 78,  3);

  return ge;
}
/*destroy of graphic engine*/
void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}
/*ii starts at NO_ID the differents id*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, FILE *f){
  Id id_act = NO_ID, id_next = NO_ID,objs_id[MAX_IDs_SET],objs_loc=NO_ID;
  Space* space_act = NULL;
  char objact[WORD_SIZE]="",objlocstr[WORD_SIZE]="";
  char objnext[WORD_SIZE]="";
  char str[255];
  char buff[WORD_SIZE]="",*str_dial;
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];
  int i, movements = -1;


  /* Paint the in the map area */
  for(i=0;i<MAX_IDs_SET;i++){
    if(game_get_object(game,i)!=NULL){
    objs_id[i]=game_get_objectId(game,i);}
    else{
      objs_id[i]=NO_ID;
    }
  }

  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    if(id_act == link_get_space1(game_get_link(game,space_get_south(space_act)))){
      id_next = link_get_space2(game_get_link(game,space_get_south(space_act)));
    }
    else{
      id_next = link_get_space1(game_get_link(game,space_get_south(space_act)));
    }

strcpy(objact,"");
strcpy(objnext,"");

for(i=0;i<MAX_IDs_SET;i++){
    if (game_get_object_location(game,objs_id[i]) == id_act){
      strcat(objact,object_get_name(game_get_object(game,objs_id[i])));
      strcat(objact," ");
    }
    if (game_get_object_location(game,objs_id[i]) == id_next){
    strcat(objnext,object_get_name(game_get_object(game,objs_id[i])));
    strcat(objnext," ");
  }
    }

if(strlen(objact)<11){
  while(strlen(objact)<11){
    strcat(objact," ");
  }
}

if(strlen(objnext)<11){
  while(strlen(objnext)<11){
    strcat(objnext," ");
  }
}


    if (id_act != NO_ID) {
      if(link_get_status(game_get_link(game,space_get_east(game_get_space(game,id_act))))==1 || link_get_status(game_get_link(game,space_get_west(game_get_space(game,id_act))))==1){
        if(space_get_east(game_get_space(game,id_act))!=NO_ID){
          sprintf(str, "  +-----------+ %ld",space_get_east(game_get_space(game,id_act)));
          screen_area_puts(ge->map, str);
          if(link_get_space1(game_get_link(game,space_get_east(game_get_space(game,id_act))))==id_act){
            sprintf(str, "  | 8D      %2d| -->%ld",(int) id_act,link_get_space2(game_get_link(game,space_get_east(game_get_space(game,id_act)))));
            screen_area_puts(ge->map, str);
          }
          else{
            sprintf(str, "  | 8D      %2d| -->%ld",(int) id_act,link_get_space1(game_get_link(game,space_get_east(game_get_space(game,id_act)))));
            screen_area_puts(ge->map, str);
          }
        }
        else{
          sprintf(str, "  +-----------+ %ld",space_get_west(game_get_space(game,id_act)));
          screen_area_puts(ge->map, str);
          if(link_get_space1(game_get_link(game,space_get_west(game_get_space(game,id_act))))==id_act){
            sprintf(str, "  | 8D      %2d| %ld<--",(int) id_act,link_get_space2(game_get_link(game,space_get_west(game_get_space(game,id_act)))));
            screen_area_puts(ge->map, str);
          }
          else{
            sprintf(str, "  | 8D      %2d| %ld<--",(int) id_act,link_get_space1(game_get_link(game,space_get_west(game_get_space(game,id_act)))));
            screen_area_puts(ge->map, str);
          }
        }
      }
      else{
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  | 8D      %2d|",(int) id_act);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  |%s|",space_get_gdesc(game_get_space(game, id_act),0));
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s|  %s",space_get_gdesc(game_get_space(game, id_act),1),space_get_description(game_get_space(game,id_act)));
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s|",space_get_gdesc(game_get_space(game, id_act),2));
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s|",objact);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    if (id_next != NO_ID) {
      sprintf(str, "        v %ld",link_get_id(game_get_link(game,space_get_south(game_get_space(game,id_act)))));
      screen_area_puts(ge->map, str);
      if(link_get_status(game_get_link(game,space_get_east(game_get_space(game,id_next))))==1 || link_get_status(game_get_link(game,space_get_west(game_get_space(game,id_next))))==1){
        if(space_get_east(game_get_space(game,id_next))!=NO_ID){
          sprintf(str, "  +-----------+ %ld",space_get_east(game_get_space(game,id_next)));
          screen_area_puts(ge->map, str);
          if(link_get_space1(game_get_link(game,space_get_east(game_get_space(game,id_next))))==id_next){
            sprintf(str, "  | 8D      %2d| -->%ld",(int) id_next,link_get_space2(game_get_link(game,space_get_east(game_get_space(game,id_next)))));
            screen_area_puts(ge->map, str);
          }
          else{
            sprintf(str, "  | 8D      %2d| -->%ld",(int) id_next,link_get_space1(game_get_link(game,space_get_east(game_get_space(game,id_next)))));
            screen_area_puts(ge->map, str);
          }
        }
        else{
          sprintf(str, "  +-----------+ %ld",space_get_west(game_get_space(game,id_next)));
          screen_area_puts(ge->map, str);
          if(link_get_space1(game_get_link(game,space_get_west(game_get_space(game,id_next))))==id_next){
            sprintf(str, "  | 8D      %2d| %ld<--",(int) id_next,link_get_space2(game_get_link(game,space_get_west(game_get_space(game,id_next)))));
            screen_area_puts(ge->map, str);
          }
          else{
            sprintf(str, "  | 8D      %2d| %ld<--",(int) id_next,link_get_space1(game_get_link(game,space_get_west(game_get_space(game,id_next)))));
            screen_area_puts(ge->map, str);
          }
        }
      }
      else{
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  | 8D      %2d|",(int) id_next);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  |%s|",space_get_gdesc(game_get_space(game, id_next),0));
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s|",space_get_gdesc(game_get_space(game, id_next),1));
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s|",space_get_gdesc(game_get_space(game, id_next),2));
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s|",objnext);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "  Objects locations:");
  screen_area_puts(ge->descript, str);
  for(i=0;objs_id[i]!=NO_ID && i<MAX_IDs_SET;i++){
    if ((objs_loc = game_get_object_location(game,object_get_id(game_get_objectbypos(game,i)))) != 0){
      strcat(objlocstr,object_get_name(game_get_objectbypos(game,i)));
      strcat(objlocstr,":");
      sprintf(buff, "%d", (int)objs_loc);
      strcat(objlocstr,buff);
      strcat(objlocstr," ");
    }
  }
  sprintf(str, "  %s", objlocstr);
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Objects in Inventory:");
  screen_area_puts(ge->descript, str);
  for (i=0; i<4 ; i++){
  if (strcmp(object_get_name(game_get_object(game,player_get_object(game_get_player(game),i))),">8D")){
  sprintf(str, "    Object %d: %s",i, object_get_name(game_get_object(game,player_get_object(game_get_player(game),i))));
  screen_area_puts(ge->descript, str);
  }
  }
  if (game_get_objdsc(game)!=NULL) {
  sprintf(str, "  Description:");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s", game_get_objdsc(game));
  screen_area_puts(ge->descript, str);
  }
  sprintf(str, "  Die last value: %d", game_get_die_value(game));
  screen_area_puts(ge->descript, str);

  if (!strcmp(game_get_rule(game), "maxbck")) {movements = game_get_rulevar(game);}

  if (movements!=-1) {
  sprintf(str, "  Rule: maxbck %d", game_get_rulevar(game));
  screen_area_puts(ge->descript, str);
}

  if (movements==-1) {
  sprintf(str, "  Rule: %s", game_get_rule(game));
  screen_area_puts(ge->descript, str);
  }

  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "      Next/n, Back/b, Left/l, Right/r, Up/u, Down/dw, Inspect/i, turnoff/tf");
  screen_area_puts(ge->help, str);
  sprintf(str, "      Exit/e, Pick/p, Drop/d, Roll/rl, Move/m, Save/s, Load/ld, turnon/to");
  screen_area_puts(ge->help, str);

  /* Paint the in the feedback area */
  last_cmd = game_get_last_command(game);
  if(game_get_callback_status(game)==OK){
    sprintf(str, " %s:OK", cmd_to_str[last_cmd-NO_CMD]);
    if(f)fprintf(f,"%s:OK\n",cmd_to_str[last_cmd-NO_CMD]);
  }
  else{
    sprintf(str, " %s:ERROR", cmd_to_str[last_cmd-NO_CMD]);
    if(f)fprintf(f,"%s:ERROR\n",cmd_to_str[last_cmd-NO_CMD]);
  }
  str_dial=dial_get_sentence((void*)game,str);
  screen_area_puts(ge->feedback, str_dial);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}

