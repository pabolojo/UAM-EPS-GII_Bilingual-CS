/** 
 * @brief It implements the dialogue interpreter
 * 
 * @file dialogue.c
 * @author Julia Simon
 * @version 1.3
 * @date 02-05-2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <strings.h>
#include "../include/dialogue.h"

/**
* @brief Estructura del dialogue
*/
struct _Dialogue{
	int repeat;                               /*!< Contador de repeticiones */
	Command* last_command;                    /*!< Comando anterior */
	T_Command previous_command;               /*!< Tipo de comando anterior */ 
	char previous_command_name[WORD_SIZE];    /*!< Nombre del comando anterior */
	STATUS status_command;                    /*!< Si se ha hecho la accion*/
	BOOL status_link;                         /*!< Para indicar si el link esta cerrado */
	BOOL status_object;                       /*!< Para indicar que es un objeto no movible */
	BOOL status_space;                        /*!< Para indicar que lo que se checkea es un espacio*/
	BOOL link_already_open;                   /*!< Para indicar que un link ya esta abierto*/
	BOOL no_monster;                          /*!< Para indicar que no se puede luchar con el monstruo porque no esta ahí*/
	char object[WORD_SIZE];                   /*!< Nombre del objeto*/
	char link[WORD_SIZE];                     /*!< Nombre del link*/
	char space[WORD_SIZE];                    /*!< Nombre del espacio al que llegamos*/
	char text[WORD_SIZE];                     /*!< Texto del respuesta del dialogue*/
};


Dialogue * dialogue_create(){
	Dialogue * newDialogue = NULL;

	newDialogue = (Dialogue *)malloc(sizeof(Dialogue));
	if(newDialogue==NULL){
		printf("Error reservando memoria\n");
		return NULL;
	}
	
	newDialogue->previous_command = 10;
    newDialogue->repeat = 0;
    newDialogue->last_command = NULL;
    newDialogue->status_command = FALSE;
    newDialogue->status_link = FALSE;
    newDialogue->status_object = FALSE;
    newDialogue->status_space = FALSE;
    newDialogue->link_already_open = FALSE;
    newDialogue->no_monster = FALSE;
	bzero(newDialogue->object,WORD_SIZE);
	bzero(newDialogue->link,WORD_SIZE);
	bzero(newDialogue->space,WORD_SIZE);
	bzero(newDialogue->previous_command_name,WORD_SIZE);
	bzero(newDialogue->text,WORD_SIZE);

    return newDialogue;

}


STATUS dialogue_destroy(Dialogue * d){
	
	if(d==NULL){
		return ERROR;
	}
	free(d);

	return OK;
}

size_t dialogue_get_size(){
	return sizeof(struct _Dialogue);
}

STATUS dialogue_set_comando(Dialogue* dialogue, Command* comando){

	if(!dialogue){
		return ERROR;
	}

	if(dialogue->previous_command==command_get_type_command(comando) && dialogue->status_command==ERROR && dialogue->previous_command!=ATACK){

		if(!strcmp(command_get_name_command(comando),dialogue->previous_command_name)){
			dialogue->repeat++;
		} else{
			dialogue->repeat = 0;
		}
	}else{
		dialogue->repeat = 0;
	}

	/*De predefinidos los objetos y los links son movibles, en caso contrario el game se encargaría de 
	actualizarlos despues de haber hecho ya el set_comando */

	/*De predefinido no tenemos objetos ni espacios ni links asociados al comando*/
	/*dialogue->object[0] =  '\0';
    dialogue->link[0] = '\0';
    dialogue->space[0] = '\0';*/
	bzero(dialogue->object,WORD_SIZE);
	bzero(dialogue->link,WORD_SIZE);
	bzero(dialogue->space,WORD_SIZE);
	dialogue->last_command = comando;
	dialogue->previous_command = command_get_type_command(comando);
	strcpy(dialogue->previous_command_name, command_get_name_command(comando));
	dialogue->status_command = ERROR;
    dialogue->status_link = FALSE;
    dialogue->status_object = FALSE;
    dialogue->status_space = FALSE;
    dialogue->link_already_open = FALSE;
    dialogue->no_monster = FALSE;

	return OK;
}

STATUS dialogue_set_status(Dialogue* dialogue, STATUS status_cmd){
	if(!dialogue){
		return ERROR;
	}
	dialogue->status_command=status_cmd;
	return OK;
}
STATUS dialogue_set_object_nomovible(Dialogue* dialogue, BOOL object){
	if(!dialogue){
		return ERROR;
	}
	dialogue->status_object=object;
	return OK;
}

STATUS dialogue_set_check_space(Dialogue* dialogue, BOOL space){
	if(!dialogue){
		return ERROR;
	}
	dialogue->status_space=space;
	return OK;
}

STATUS dialogue_set_link_cerrado(Dialogue* dialogue, BOOL link){
	if(!dialogue){
		return ERROR;
	}
	dialogue->status_link = link;
	return OK;	
}

STATUS dialogue_set_link_open(Dialogue* dialogue, BOOL link){
	if(!dialogue){
		return ERROR;
	}
	dialogue->link_already_open = link;
	return OK;	
}

STATUS dialogue_set_no_monster(Dialogue* dialogue, BOOL monster){
	if(!dialogue){
		return ERROR;
	}
	dialogue->no_monster = monster;
	return OK;	
}

STATUS dialogue_set_space(Dialogue* dialogue, char* space){
	if(!dialogue){
		return ERROR;
	}
	strcpy(dialogue->space,space);
	return OK;
}


STATUS dialogue_set_object(Dialogue* dialogue, char* object){
	if(!dialogue){
		return ERROR;
	}
	strcpy(dialogue->object,object);
	return OK;
}

STATUS dialogue_set_link_name(Dialogue* dialogue, char* link){
	if(!dialogue){
		return ERROR;
	}
	strcpy(dialogue->link,link);
	return OK;
}

char * dialogue_get_data(Dialogue * dialogue){

	/*Debe decir algo para cada uno de los posibles comandos*/
	char str[WORD_SIZE]= "";
	char comando[WORD_SIZE] = "";
	
	T_Command cmd = NO_CMD;

	if(dialogue == NULL){
		return NULL;
	}
	if(command_get_type_command(dialogue->last_command) == UNKNOWN){
		sprintf(str, "This is not a valid action. Try again.");
		strcpy(dialogue->text,str);
		return dialogue->text;
	}

	if(dialogue->repeat > 0){
		sprintf(str, "You have done this without succes");
		strcpy(dialogue->text,str);
		return dialogue->text;
	}

	/* Comandos de movimiento */
	cmd = command_get_type_command(dialogue->last_command);
	if(cmd == PREVIOUS || cmd == FOLLOWING || cmd == LEFT || cmd == RIGHT || cmd == UP || cmd == DOWN || cmd == MOVE){
		/* Comando intentar pasar a un link */
		if(dialogue->status_link ){
			sprintf(str,"The link %s is closed, try to find a key or a code to open it.", dialogue->link);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}

		if(cmd == LEFT)
			strcpy(comando, "west");
		if(cmd == RIGHT)
			strcpy(comando, "east");
		if(cmd == PREVIOUS)
			strcpy(comando, "south");
		if(cmd == FOLLOWING)
			strcpy(comando, "north");
		if(cmd == UP)
			strcpy(comando, "up");
		if(cmd == DOWN)
			strcpy(comando, "down");

		if(cmd == MOVE){
			sprintf(str, "You have to introduce a right direction: north, south, east, west, up or down");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}

		if(dialogue->status_command){
			sprintf(str, "You have move %s. Now you are in %s", comando, dialogue->space);
			strcpy(dialogue->text,str);
			return dialogue->text;
		} else{
			sprintf(str, "You can not move %s",comando);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}	
	}
	
	/* Comandos de coger y dejar objetos */

	if(cmd == GRASP){
		if(dialogue->status_object){
			sprintf(str,"You cannot move %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(!strcmp(dialogue->object,"")){
			sprintf(str, "This is not a valid object");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have grasp %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You cannot grasp %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		
	}
	if(cmd == DROP){
		if(!strcmp(dialogue->object,"")){
			sprintf(str, "This is not a valid object");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have drop %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You cannot drop %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		
	}

	/* Comando encencer y apargar objetos */
	if(cmd == TURNON){
		if(!strcmp(dialogue->object,"")){
			sprintf(str, "This is not a valid object");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have turn on the %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You can't turn on the %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}
	if(cmd == TURNOFF){
		if(!strcmp(dialogue->object,"")){
			sprintf(str, "This is not a valid object");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have turn off the %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You can't turn off the %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}
	
	/* Dado */
	if(cmd == DIE){
		if(dialogue->status_command){
			sprintf(str, "You have throw the die");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You have throw the die without succes");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}

	/* Check */
	if(cmd == CHECK){
		if(dialogue->status_space && dialogue->status_command){
			sprintf(str,"You have check the space.");
			strcpy(dialogue->text,str);
			return dialogue->text;
		} else if(dialogue->status_space){
			sprintf(str,"You cannot check the space.");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(!strcmp(dialogue->object,"")){
			sprintf(str, "This is not a valid object");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have check the object %s", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You cannot check the object %s ", dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}

	}

	/* Open */
	if(cmd == OPEN){
		if(dialogue->link_already_open){
			sprintf(str, "This link is already open");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(!strcmp(dialogue->object,"") || !strcmp(dialogue->link,"")){
			sprintf(str, "This is not a valid object or link");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have open %s with %s",dialogue->link, dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You cannot open %s with %s ",dialogue->link, dialogue->object);
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}

	/* Save */
	if(cmd == SAVE){
		if(dialogue->status_command){
			sprintf(str, "You have save succesfully");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "The game couldn't be save... there was a problem ");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}

	/* Load */
	if(cmd == LOAD){
		if(dialogue->status_command){
			sprintf(str, "You have load succesfully");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "The game couldn't be load... you have to continue using this game.");
			strcpy(dialogue->text,str);
			return dialogue->text;	
		}
	}

	/* Code */
	if(cmd == CODE){
		if(dialogue->status_command){
			sprintf(str, "You create a new code to open a link");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}else{
			sprintf(str, "You couldn't create the code. You need more numbers to create it");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}

	/* Examine */
	if(cmd == EXAMINE){
		sprintf(str, "You have examine the room");
		strcpy(dialogue->text,str);
		return dialogue->text;
	}

	/* Atack */
	if(cmd == ATACK){
		if(dialogue->no_monster){
			sprintf(str, "There is no monster in this room");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
		if(dialogue->status_command){
			sprintf(str, "You have killed the monster");
			strcpy(dialogue->text,str);
			return dialogue->text;;
		}else{
			sprintf(str, "You have missed... try again");
			strcpy(dialogue->text,str);
			return dialogue->text;
		}
	}

	strcpy(dialogue->text,str);
	return dialogue->text;

}

