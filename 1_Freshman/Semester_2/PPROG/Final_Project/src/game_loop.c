/** 
 * @brief It defines the game loop 
 * 
 * @file game_loop.c
 * @author Julia Simon
 * @version 1.3
 * @date 08-03-2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graphic_engine.h"
#include "../include/game_rules.h"

int main(int argc, char *argv[]){
	GameRules* gameRules = NULL;
	Game* game=NULL;
	/*Game* game_aux = NULL;*/
	Command* command = NULL;
	Graphic_engine *gengine;
	extern char *cmd_to_str[];
	T_Command last_cmd = UNKNOWN;
	STATUS cmd_status=ERROR;
	FILE* file = NULL;
	BOOL no_rule = FALSE;
	int contador_reglas = 0;
	
	srand(time(NULL));

	if (argc < 4){
		fprintf(stderr, "Use: %s <game_data_file> -l <game_log_file>\n", argv[0]);
		fprintf(stderr, "or Use: %s <game_data_file> -l <game_log_file> NO_RULE\n", argv[0]);
		return 1;
	}
	if((command = command_create())==ERROR){
		fprintf(stderr, "Error while initializing the command.\n");
		return 1;
	}
	game = game_management_game_create_from_file(argv[1]);
	/*game = game_management_load("fichero.dat");*/
	if ( game == NULL){
		fprintf(stderr, "Error while initializing game.\n"); 
		command_destroy(command);
		return 1;
	}
	if ((gengine = graphic_engine_create()) == NULL){
		fprintf(stderr, "Error while initializing graphic engine.\n");
		command_destroy(command);
		game_destroy(game); 
		return 1;
	}
	
	gameRules = game_rules_create();
	if(gameRules == NULL){
		fprintf(stderr, "Error while initializing game rules.\n"); 
		command_destroy(command);
		game_destroy(game); 
		graphic_engine_destroy(gengine);
		return 1;
	}
	
	file = fopen(argv[3], "w");
  	if (file == NULL){
  		fprintf(stderr, "Error while opening the log file.\n");
  		command_destroy(command);
  		graphic_engine_destroy(gengine);
  		game_destroy(game);
    	return ERROR;
  	}

	if(argc > 4){
		if(strcmp(argv[4],"NO_RULE")==0)
			no_rule = TRUE;
	}
	
	
	while ((command_get_type_command(command) != EXIT) && !game_is_over(game) ){

		graphic_engine_paint_game(gengine, game);
		command = command_get_user_input(command);
		game_update(game, command);
		last_cmd = game_get_last_command(game);
		cmd_status = game_get_last_command_status(game);

		if(last_cmd ==SAVE){
			/*if(game_management_save(game,command_get_name_command(command))==ERROR){
				printf("Error guardando el game\n");
				game_set_last_command_status(game,ERROR);
			}else{
				game_set_last_command_status(game,OK);
			}*/
			dialogue_set_comando(game_get_dialogue(game), command);
		} else if(last_cmd == LOAD){
			/*game_aux = game_management_load(command_get_name_command(command));
			if(game_aux != NULL){
				game_destroy(game);
				game = game_aux;
			} else{
				printf("Error cargando el game\n");
			}
			game_set_last_command_status(game,OK);*/
			dialogue_set_comando(game_get_dialogue(game), command);
		}
		

		/* Guardamos la informacion en el fichero de log */
		if(last_cmd-NO_CMD<3){
			fprintf(file, "%s\n",cmd_to_str[last_cmd-NO_CMD]);
		} else {
			if(last_cmd == FOLLOWING || last_cmd == PREVIOUS){
				if(cmd_status==OK){
					fprintf(file, "%s\n",cmd_to_str[last_cmd-NO_CMD]);	
				}else{
					fprintf(file, "%s\n",cmd_to_str[last_cmd-NO_CMD]);	
				}
			} else{
				if(cmd_status==OK){
					fprintf(file, "%s %s\n",cmd_to_str[last_cmd-NO_CMD], command_get_name_command(command));	
				}else{
					fprintf(file, "%s %s\n",cmd_to_str[last_cmd-NO_CMD], command_get_name_command(command));	
				}
			}
		} 
		/* Ejecutamos el modulo de las reglas */
		if(contador_reglas<10){
			contador_reglas++;
		}else{
			game_rules_play(gameRules,game, no_rule);
			contador_reglas = 0;	
		}
		
	}

	fclose(file);
	command_destroy(command);
	game_destroy(game);
	graphic_engine_destroy(gengine);
	game_rules_destroy(gameRules);
	return 0;
}
