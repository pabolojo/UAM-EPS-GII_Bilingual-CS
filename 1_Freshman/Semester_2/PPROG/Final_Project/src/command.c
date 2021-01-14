/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Julia Simon
 * @version 1.3
 * @date 30-03-2018
 */

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/command.h"

#define CMD_LENGHT 30 /*! tamano maximo del comando introducido*/
#define N_CMD 22      /*! numero de comandos */

/**
* @brief Estructura del command
*/
struct _Command{
  	T_Command cmd;                           /*!< Ultimo comando introducido */
	char name_action[WORD_SIZE];             /*!< nombre del objeto que hay que coger o dejar  o direccion n,s,e,w */
	Id id_check;                             /*!< Id del objeto a chekear */
	char name_key[WORD_SIZE];                /*!< Nombre del objeto que abre un link */
};

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Grasp", "Drop", "Left", "Right", "Die", "Check", "Move","TurnOn","TurnOff","Up", "Down","Open","Code","Atack","Examine","Save", "Load"};
char *short_cmd_to_str[N_CMD] = {"","","e","f","p", "g", "d", "l", "r", "x","c", "m","on","off", "u","dw","o","cd","a","ex","s", "lo"};


Command* command_create(){
	Command* command = NULL;

	command = (Command*) malloc(sizeof(Command));
	if(!command)
		return NULL;

	command->cmd = UNKNOWN;
	bzero(command->name_action,WORD_SIZE);
	bzero(command->name_key,WORD_SIZE);
	return command;
}


STATUS command_destroy(Command* command){
	if(!command)
		return ERROR;

	free(command);

	return OK;
}



Command* command_get_user_input(Command* comando){
	T_Command cmd = NO_CMD;
	char input[CMD_LENGHT] = "";
	char input_aux[CMD_LENGHT] = "";
	char input_aux2[CMD_LENGHT] = "";
	int i = UNKNOWN - NO_CMD + 1;
	char* toks = NULL;
        
	if(!comando)
		return NULL;
	
	comando->name_action[0] = '\0';
	comando->name_key[0] = '\0';
	if (fgets(input,CMD_LENGHT,stdin)){
		
		toks = strtok(input, " ");
      	strcpy(input_aux, toks);
		if(input_aux[strlen(input_aux) - 1] == '\n'){
    		input_aux[strlen(input_aux) - 1] = '\0';
		}

      	toks = strtok(NULL, " ");
      	
      	/* Miramos el comando introducido */
      	cmd = UNKNOWN;
		while(cmd == UNKNOWN && i < N_CMD){
  			if (!strcasecmp(input_aux,short_cmd_to_str[i]) || !strcasecmp(input_aux,cmd_to_str[i])){
  				cmd = i + NO_CMD;
  			}
  			else{
				i++;
			}
		}
		comando->cmd = cmd;

      	/* Comprobamos si se ha introducido un nombre detras del comando */
		if(toks!=NULL){
			strcpy(input_aux2, toks);
			if(input_aux2[strlen(input_aux2) - 1] == '\n'){
    			input_aux2[strlen(input_aux2) - 1] = '\0';
			}
			strcpy(comando->name_action, input_aux2);
			toks = strtok(NULL, " ");
			if(toks!=NULL){
				strcpy(input_aux2, toks);
				if(input_aux2[strlen(input_aux2) - 1] == '\n'){
					input_aux2[strlen(input_aux2) - 1] = '\0';
				}
				if(!strcmp(input_aux2,"with")){
					toks = strtok(NULL, " ");
					if(toks!=NULL){
						strcpy(input_aux2, toks);
						if(input_aux2[strlen(input_aux2) - 1] == '\n'){
							input_aux2[strlen(input_aux2) - 1] = '\0';
						}
						strcpy(comando->name_key, input_aux2);
					}else{
						comando->name_key[0] = '\0';
					}
				}else{
					comando->name_key[0] = '\0';
				}
			} else{
				comando->name_key[0] = '\0';
			}
		} else{
			comando->name_action[0] = '\0';
			comando->name_key[0] = '\0';
		}

		
	}		
  	return comando;
}


STATUS command_set_type_command(Command* command, T_Command type){
	if(!command){
		return ERROR;	
	}
	command->cmd = type;
	return OK;
}

T_Command command_get_type_command(Command* command){
	if(!command){
		return NO_CMD;	
	}
	return command->cmd;
}


char* command_get_name_command(Command* command){
	if(!command)
		return NULL;
	return command->name_action;
}

char* command_get_key_command(Command* command){
	if(!command)
		return NULL;
	return command->name_key;
}

size_t command_get_size(){
	return sizeof(struct _Command);
}


