/**
 * @brief It defines the module SET
 *
 * @file set.c
 * @version 1.0
 * @date 21-02-2019
 * @copyright GNU Public License
 */
/*libraries*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"

struct _Dialogue {
  char command[WORD_SIZE];
  char prevcommand[WORD_SIZE];
  char sentence[WORD_SIZE];
};

Dialogue* dial_create(){
Dialogue *dial=NULL;
int i;
dial=(Dialogue*)malloc(sizeof(Dialogue));
if(!dial){
    return NULL;
	}
for(i=0;i<WORD_SIZE;i++){
  dial->command[i]=0;
  dial->prevcommand[i]=0;
  dial->sentence[i]=0;
}
return dial;
}

STATUS dial_destroy(Dialogue *aux){
	if(!aux) return ERROR;
	free(aux);
  return OK;
}

STATUS dial_set_command(Dialogue *dial,char *cmd){
	if(!dial || !cmd) return ERROR;
  strcpy(dial->prevcommand,dial->command);
  strcpy(dial->command,cmd);
  return OK;
}

char* dial_get_sentence(void *g,char *cmd){
  char *actcom,*actstatus,*prevstatus,actcommand[WORD_SIZE]="",prevcommand[WORD_SIZE]="";
  Dialogue *dial=NULL;
  Game *game=(Game*)g;
  if(!game || !cmd) return ERROR;
  dial=game_get_dial((Game*)game);
  if(!dial) return ERROR;
  strcpy(actcommand,cmd);
  strcpy(prevcommand,dial->command);
  strcpy(dial->prevcommand,dial->command);
  strcpy(dial->command,cmd);
  actcom = strtok(actcommand, ":");
  actstatus = strtok(NULL, ":");
  strtok(prevcommand, ":");
  prevstatus = strtok(NULL, ":");
  if(!prevstatus){
    prevstatus=prevcommand;
  }
  printf("%s\n",actcommand);
  if(strcmp(actcommand," Unknown")==0){
    strcpy(dial->sentence,"This is not a valid action. Try again.");
  }
  else if(strcmp(prevstatus,"ERROR")==0 && strcmp(actstatus,"ERROR")==0 && strcmp(prevcommand,actcommand)==0){
    strcpy(dial->sentence,"You have tried to do this before without success.");
  }
  else{
    if(strcmp(actstatus,"OK")==0){
      if(strcmp(actcom," Next")==0 || strcmp(actcom," next")==0 || strcmp(actcom,"n")==0 || strcmp(actcom,"N")==0){
        strcpy(dial->sentence,"You've gone north. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Back")==0 || strcmp(actcom," back")==0 || strcmp(actcom,"b")==0 || strcmp(actcom,"B")==0){
        strcpy(dial->sentence,"You've gone south. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Right")==0 || strcmp(actcom," right")==0 || strcmp(actcom,"r")==0 || strcmp(actcom,"R")==0){
        strcpy(dial->sentence,"You've gone east. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Left")==0 || strcmp(actcom," left")==0 || strcmp(actcom,"l")==0 || strcmp(actcom,"L")==0){
        strcpy(dial->sentence,"You've gone west. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Up")==0 || strcmp(actcom," up")==0 || strcmp(actcom,"u")==0 || strcmp(actcom,"U")==0){
        strcpy(dial->sentence,"You've gone up. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Down")==0 || strcmp(actcom," down")==0 || strcmp(actcom,"dw")==0 || strcmp(actcom,"Dw")==0){
        strcpy(dial->sentence,"You've gone down. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Inspect")==0 || strcmp(actcom," inspect")==0 || strcmp(actcom,"i")==0 || strcmp(actcom,"I")==0){
        strcpy(dial->sentence,"You've inspected something.");
      }
      else if(strcmp(actcom," Turnoff")==0 || strcmp(actcom," turnoff")==0 || strcmp(actcom,"tf")==0 || strcmp(actcom,"Tf")==0){
        strcpy(dial->sentence,"You've turned off an object.");
      }
      else if(strcmp(actcom," Turnon")==0 || strcmp(actcom," turnon")==0 || strcmp(actcom,"to")==0 || strcmp(actcom,"To")==0){
        strcpy(dial->sentence,"You've turned on an object.");
      }
      else if(strcmp(actcom," Pick")==0 || strcmp(actcom," pick")==0 || strcmp(actcom,"p")==0 || strcmp(actcom,"P")==0){
        strcpy(dial->sentence,"You've picked ");
        strcat(dial->sentence,object_get_description(game_get_object(game,player_get_object(game_get_player(game),bag_numObj(player_get_bag(game_get_player(game)))-1))));
      }
      else if(strcmp(actcom," Drop")==0 || strcmp(actcom," drop")==0 || strcmp(actcom,"d")==0 || strcmp(actcom,"D")==0){
        strcpy(dial->sentence,"You've dropped an object.");
      }
      else if(strcmp(actcom," Roll")==0 || strcmp(actcom," roll")==0 || strcmp(actcom,"rl")==0 || strcmp(actcom,"Rl")==0){
        sprintf(dial->sentence,"Rolling... %d!",game_get_die_value(game));
      }
      else if(strcmp(actcom," Save")==0 || strcmp(actcom," save")==0 || strcmp(actcom,"s")==0 || strcmp(actcom,"S")==0){
        strcpy(dial->sentence,"You've saved the game.");
      }
      else if(strcmp(actcom," Load")==0 || strcmp(actcom," load")==0 || strcmp(actcom,"ld")==0 || strcmp(actcom,"Ld")==0){
        strcpy(dial->sentence,"You've loaded the game.");
      }
      else if(strcmp(actcom," Move")==0 || strcmp(actcom," move")==0 || strcmp(actcom,"m")==0 || strcmp(actcom,"M")==0){
        strcpy(dial->sentence,"You've moved. Now you are in ");
        strcat(dial->sentence,space_get_description(game_get_space(game,game_get_player_location(game))));
      }
      else if(strcmp(actcom," Open")==0 || strcmp(actcom," open")==0 || strcmp(actcom,"O")==0 || strcmp(actcom,"o")==0){
        strcpy(dial->sentence,"You've opened something...");
      }
      else{
        strcpy(dial->sentence,"Command executed");
      }
    }
    else{
      if(strcmp(actcom," Next")==0 || strcmp(actcom," next")==0 || strcmp(actcom,"n")==0 || strcmp(actcom,"N")==0){
        strcpy(dial->sentence,"You cannot go north. Try another action.");
      }
      else if(strcmp(actcom," Back")==0 || strcmp(actcom," back")==0 || strcmp(actcom,"b")==0 || strcmp(actcom,"B")==0){
        strcpy(dial->sentence,"You cannot go south. Try another action.");
      }
      else if(strcmp(actcom," Right")==0 || strcmp(actcom," right")==0 || strcmp(actcom,"r")==0 || strcmp(actcom,"R")==0){
        strcpy(dial->sentence,"You cannot go east. Try another action.");
      }
      else if(strcmp(actcom," Left")==0 || strcmp(actcom," left")==0 || strcmp(actcom,"l")==0 || strcmp(actcom,"L")==0){
        strcpy(dial->sentence,"You cannot go west. Try another action.");
      }
      else if(strcmp(actcom," Up")==0 || strcmp(actcom," up")==0 || strcmp(actcom,"u")==0 || strcmp(actcom,"U")==0){
        strcpy(dial->sentence,"You cannot go up. Try another action.");
      }
      else if(strcmp(actcom," Down")==0 || strcmp(actcom," down")==0 || strcmp(actcom,"dw")==0 || strcmp(actcom,"Dw")==0){
        strcpy(dial->sentence,"You cannot go down. Try another action.");
      }
      else if(strcmp(actcom," Inspect")==0 || strcmp(actcom," inspect")==0 || strcmp(actcom,"i")==0 || strcmp(actcom,"I")==0){
        strcpy(dial->sentence,"You cannot inspect that.");
      }
      else if(strcmp(actcom," Turnoff")==0 || strcmp(actcom," turnoff")==0 || strcmp(actcom,"tf")==0 || strcmp(actcom,"Tf")==0){
        strcpy(dial->sentence,"You cannot turn off that object.");
      }
      else if(strcmp(actcom," Turnon")==0 || strcmp(actcom," turnon")==0 || strcmp(actcom,"to")==0 || strcmp(actcom,"To")==0){
        strcpy(dial->sentence,"You cannot turn on that object.");
      }
      else if(strcmp(actcom," Pick")==0 || strcmp(actcom," pick")==0 || strcmp(actcom,"p")==0 || strcmp(actcom,"P")==0){
        strcpy(dial->sentence,"You cannot pick that object.");
      }
      else if(strcmp(actcom," Drop")==0 || strcmp(actcom," drop")==0 || strcmp(actcom,"d")==0 || strcmp(actcom,"D")==0){
        strcpy(dial->sentence,"You cannot drop that object.");
      }
      else if(strcmp(actcom," Roll")==0 || strcmp(actcom," roll")==0 || strcmp(actcom,"rl")==0 || strcmp(actcom,"Rl")==0){
        strcpy(dial->sentence,"The die has died.");
      }
      else if(strcmp(actcom," Save")==0 || strcmp(actcom," save")==0 || strcmp(actcom,"s")==0 || strcmp(actcom,"S")==0){
        strcpy(dial->sentence,"There was an error saving the game.");
      }
      else if(strcmp(actcom," Load")==0 || strcmp(actcom," load")==0 || strcmp(actcom,"ld")==0 || strcmp(actcom,"Ld")==0){
        strcpy(dial->sentence,"There was an error loading the game.");
      }
      else if(strcmp(actcom," Move")==0 || strcmp(actcom," move")==0 || strcmp(actcom,"m")==0 || strcmp(actcom,"M")==0){
        strcpy(dial->sentence,"You cannot move there. Try another action.");
      }
      else if(strcmp(actcom," Open")==0 || strcmp(actcom," open")==0 || strcmp(actcom,"O")==0 || strcmp(actcom,"o")==0){
        strcpy(dial->sentence,"You cannot open that.");
      }
      else{
        strcpy(dial->sentence,"Command NOT executed");
      }
    }
  }
  return dial->sentence;
}

