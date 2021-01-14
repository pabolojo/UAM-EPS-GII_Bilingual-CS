/**
 * @brief It defines the game loop, it contains the main function of the game
 *
 * @file game_loop.c
 * @version 4.0
 * @date 12-02-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
 /**
 * @brief main function of the game
 *
 * @param argc
 * @param argv
 *
 * @return number
 */
int main(int argc, char *argv[])
{
  Game *game=NULL;T_Command command = NO_CMD; Graphic_engine *gengine;
  FILE *log=NULL;
  game=game_create();
  if(!game){
    fprintf(stderr, "Error creating game\n");
   	return 1;
  }
if (argc < 2)
{
	fprintf(stderr, "Use: %s <game_data_file> you can also add -l <log_file>\n", argv[0]);
 	return 1;
}
if(argc==4){
  if(!strcmp("-l",argv[2])){
      log=fopen(argv[3],"w");
      if(!log) printf("Error creating log file\n");
      fprintf(log,"Log File:\n");
  }
}

if (game_create_from_file(game, argv[1]) == ERROR)
{
	fprintf(stderr, "Error while initializing game.\n");
	return 1;
}
if ((gengine = graphic_engine_create()) == NULL)
{
fprintf(stderr, "Error while initializing graphic engine.\n");
game_destroy(game);
return 1;
}
while ( (command != EXIT) && !game_is_over(game) )
{
graphic_engine_paint_game(gengine, game,log);
command = get_user_input();
game_update(game, command);
}
game_destroy(game);
graphic_engine_destroy(gengine);
if(log)fclose(log);
return 0;
}

