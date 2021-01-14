/** 
 * @brief It implements the game_rules module
 * 
 * @file game_rules.c
 * @author Julia Simon
 * @version 1.0 
 * @date 02-05-2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game_rules.h"

#define N_RULES 10     /*!< numero de reglas */
#define NUM_SPACES 34  /*!< numero de espacios en el juego*/

/**
* @brief Estructura del game_rules
*/
struct _GameRules{
  	T_Rule rule;       /*!< Ultima regla ejecutada */
	Die* die;          /*!< Dado para las reglas   */
	Game*game;         /*!< Juego                  */
	BOOL alreadyClose; /*!< Para que la que cierra un link solo se haga una vez*/
};



/**
	 Define the function type for the callbacks
*/
typedef void (*callback_fn)(GameRules* gameRules);

/**
	 List of callbacks for each rule
*/
void gameRules_callback_noRule(GameRules* gameRules);
void gameRules_callback_ocult(GameRules* gameRules);
void gameRules_callback_on(GameRules* gameRules);
void gameRules_callback_off(GameRules* gameRules);
void gameRules_callback_close(GameRules* gameRules);
void gameRules_callback_show(GameRules* gameRules);
void gameRules_callback_change(GameRules* gameRules);
void gameRules_callback_eliminate(GameRules* gameRules);
void gameRules_callback_regenerate(GameRules* gameRules);
void gameRules_callback_newexit(GameRules* gameRules);

/**
* @brief Lista de callbacks
*/
static callback_fn gameRules_callback_fn_list[N_RULES]={
	gameRules_callback_noRule,
	gameRules_callback_ocult,
	gameRules_callback_on, 
	gameRules_callback_off,    
	gameRules_callback_close,
	gameRules_callback_show,
	gameRules_callback_change,
	gameRules_callback_eliminate,
	gameRules_callback_regenerate,
	gameRules_callback_newexit
};

GameRules* game_rules_create(){

	GameRules* gameRules = NULL;

	gameRules = (GameRules*) malloc(sizeof(GameRules));

	if(!gameRules)
		return NULL;

	gameRules->die = die_create(3); 
	gameRules->rule = NO_RULE;
	gameRules->game = NULL;
	gameRules->alreadyClose= FALSE;
	return gameRules;
}

STATUS game_rules_destroy(GameRules* gameRules){
	if(!gameRules)
		return ERROR;

	die_destroy(gameRules->die);

	free(gameRules);
	return OK;
}

STATUS game_rules_play(GameRules* gameRules, Game * game, BOOL no_rules){
	if(!gameRules)
		return ERROR;
	if(!game)
		return ERROR;

	gameRules->game = game;

	if(no_rules){
		gameRules->rule = NO_RULE;
	} else{
		if(die_roll(gameRules->die,N_RULES,1)==ERROR){
			printf("Error tirando el dado");
			return ERROR;
		}
		gameRules->rule = die_get_lastValue(gameRules->die)-1;
	}
	(*gameRules_callback_fn_list[gameRules->rule+1])(gameRules);
	return OK;

}
 

/**
* @brief Funcion de la regla noRule: no se ejecuta ninguna regla
* 
* @param gameRules reglas del juego
*/     
void gameRules_callback_noRule(GameRules* gameRules){

}

/**
* @brief Funcion de la regla ocult
* Este comando va a ocultar todos los objetos del juego
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_ocult(GameRules* gameRules){
	game_ocult_objects(gameRules->game, TRUE);
	return;
}

/**
* @brief Funcion de la regla on
* Este comando va iluminar algún espacio de manera aleatoria
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_on(GameRules* gameRules){
	int value = 0,i =0;
	Space* space = NULL;

	for(i=0;i<3;i++){
		if(die_roll(gameRules->die,NUM_SPACES,1)==ERROR){
			printf("Error tirando el dado");
			return;
		}
		value = die_get_lastValue(gameRules->die);
		space = game_get_space_i(gameRules->game,value);
		space_set_iluminado(space, TRUE);
	}
	return;

}

/**
* @brief Funcion de la regla off
* Este comando va a apagar algun espacio de manera aleatoria
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_off(GameRules* gameRules){
	int value = 0, i=0;
	Space* space = NULL;

	for(i=0;i<3;i++){
		if(die_roll(gameRules->die,NUM_SPACES,1)==ERROR){
			printf("Error tirando el dado");
			return;
		}
		value = die_get_lastValue(gameRules->die);
		if(value!=6){ /*No apagamos nunca la casilla 6 ya que es en la que está la antorcha*/
			space = game_get_space_i(gameRules->game,value);
			space_set_iluminado(space, FALSE);	
		}
		
	}
	return;
}
/**
* @brief Funcion de la regla  close
* Cierra alguno de los links entre el 7 y el 11 y crea un objeto que lo abre 
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_close(GameRules* gameRules){
	int value = 0;
	Link* link = NULL;
	Object* llave = NULL;
	Id space_id = NO_ID, object_id=NO_ID;

	if(gameRules->alreadyClose==FALSE){
		if(die_roll(gameRules->die,11,7)==ERROR){
			printf("Error tirando el dado");
			return;
		}
		value = die_get_lastValue(gameRules->die);

		link = game_get_link_i(gameRules->game,value);

		link_set_status(link,CLOSED);

		llave = object_create(35);
		object_set_name(llave, "Llave5");
		object_set_description(llave, "Esta llave abre el link que se acaba de cerrar ");
		object_set_open(llave, link_get_id(link)); /* Codigo de la puerta que se abre con el codigo */
		object_set_oculto(llave,TRUE);

		space_id = game_get_player_location(gameRules->game);
		object_id = object_get_id(llave);

		space_add_objects(game_get_space(gameRules->game, space_id), object_id);

		object_set_pos_inicial(llave,space_id);

		game_add_object(gameRules->game, llave);
		gameRules->alreadyClose = TRUE;
	}
	
	return;

}

/**
* @brief Funcion de la regla  show
* Este comando va a mostrar todos los objetos del juego
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_show(GameRules* gameRules){
	game_ocult_objects(gameRules->game, FALSE);
}

/**
* @brief Funcion de la regla change
* Este comando va a cambiar alguno de los links del piso de arriba
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_change(GameRules* gameRules){
	int value = 0;
	Space* space =NULL;
	Link* link = NULL;

	if(die_roll(gameRules->die,5,1)==ERROR){
		printf("Error tirando el dado");
		return;
	}
	value = die_get_lastValue(gameRules->die);

	if(value==1){ /* Cambiamos el link 23*/
		if(value%2==0){
			link = game_get_link(gameRules->game,23);
			link_set_link(link,23,24);
			space = game_get_space(gameRules->game, 23);
			space_set_south(space,link);
			space_set_west(space,NULL);
			space = game_get_space(gameRules->game, 24);
			space_set_north(space,link);
			space = game_get_space(gameRules->game, 32);
			space_set_east(space,NULL);
			
		} else{
			link = game_get_link(gameRules->game,23);
			link_set_link(link,23,32);
			space = game_get_space(gameRules->game, 23);
			space_set_west(space,link);
			space_set_south(space,NULL);
			space = game_get_space(gameRules->game, 24);
			space_set_north(space,NULL);
			space = game_get_space(gameRules->game, 32);
			space_set_east(space,link);
			
		}
		
	}else if(value ==2){ /* Cambiamos el link 25*/
		if(value%2==0){
			link = game_get_link(gameRules->game,25);
			link_set_link(link,25,26);
			space = game_get_space(gameRules->game, 26);
			space_set_south(space,link);
			space_set_north(space,NULL);
			space = game_get_space(gameRules->game, 25);
			space_set_north(space,link);
			space = game_get_space(gameRules->game, 24);
			space_set_south(space,NULL);
			
		} else{
			link = game_get_link(gameRules->game,25);
			link_set_link(link,24,26);
			space = game_get_space(gameRules->game, 26);
			space_set_south(space,NULL);
			space_set_north(space,link);
			space = game_get_space(gameRules->game, 25);
			space_set_north(space,NULL);
			space = game_get_space(gameRules->game, 24);
			space_set_south(space,link);
			
		}
	}else if(value==3){ /* Cambiamos el link 32*/
		if(value%2==0){
			link = game_get_link(gameRules->game,32);
			link_set_link(link,32,33);
			space = game_get_space(gameRules->game, 32);
			space_set_north(space,link);
			space = game_get_space(gameRules->game, 31);
			space_set_north(space,NULL);
			
		} else{
			link = game_get_link(gameRules->game,32);
			link_set_link(link,31,33);
			space = game_get_space(gameRules->game, 32);
			space_set_north(space,NULL);
			space = game_get_space(gameRules->game, 31);
			space_set_north(space,link);
			
		}
	}else if(value == 4){ /* Cambiamos el link 26*/
		if(value%2==0){
			link = game_get_link(gameRules->game,26);
			space = game_get_space(gameRules->game, 25);
			space_set_south(space,link);
			space_set_west(space,NULL);
			space = game_get_space(gameRules->game, 27);
			space_set_north(space,link);
			space_set_east(space,NULL);
		} else{
			link = game_get_link(gameRules->game,26);
			space = game_get_space(gameRules->game, 25);
			space_set_south(space,NULL);
			space_set_west(space,link);
			space = game_get_space(gameRules->game, 27);
			space_set_north(space,NULL);
			space_set_east(space,link);
		}
	} else{   /* Cambiamos el link 33*/
		if(value%2==0){
			link = game_get_link(gameRules->game,33);
			link_set_link(link,32,34);
			space = game_get_space(gameRules->game, 32);
			space_set_south(space,link);
			space = game_get_space(gameRules->game, 31);
			space_set_south(space,NULL);
			
		} else{
			link = game_get_link(gameRules->game,33);
			link_set_link(link,32,34);
			space = game_get_space(gameRules->game, 32);
			space_set_south(space,NULL);
			space = game_get_space(gameRules->game, 31);
			space_set_south(space,link);
			
		}
	}
	return;
}

/**
* @brief Funcion de la regla eliminate
* Este comando va a eliminar el link 34 o el 35 de los espacios
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_eliminate(GameRules* gameRules){
	Space* space = NULL;

	if(die_get_lastValue(gameRules->die)%2==0){  /* quitamos el link 34*/
		space = game_get_space(gameRules->game, 17);
		space_set_south(space,NULL);
		space = game_get_space(gameRules->game, 20);
		space_set_north(space,NULL);
	} else { /* quitamos el link 35*/
		space = game_get_space(gameRules->game, 18);
		space_set_south(space,NULL);
		space = game_get_space(gameRules->game, 21);
		space_set_north(space,NULL);

	}
	return;
}

/**
* @brief Funcion de la regla regenerate
* Este comando va a crear el link 34 o el 35 en los espacios
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_regenerate(GameRules* gameRules){
	Space* space = NULL;
	Link * link = NULL;
	
	

	if(die_get_lastValue(gameRules->die)%2==0){ /* rehacemos el link 34*/
		link = game_get_link(gameRules->game,34);
		space = game_get_space(gameRules->game, 17);
		space_set_south(space,link);
		space = game_get_space(gameRules->game, 20);
		space_set_north(space,link);
	} else { /* rehacemos el link 35*/
		link = game_get_link(gameRules->game,35);
		space = game_get_space(gameRules->game, 18);
		space_set_south(space,link);
		space = game_get_space(gameRules->game, 21);
		space_set_north(space,link);

	}
	return;
}

/**
* @brief Funcion de la regla newexit
* Este comando va a cambiar la salida de sitio. Puede estar conectada al 12 o al 19
* 
* @param gameRules reglas del juego
*/ 
void gameRules_callback_newexit(GameRules* gameRules){
	/*Se cambia la salida de estar conectada con la 12 a estar conectada con la 19 que es la del monstruo */

	int value = 0;
	Space* space =NULL;
	Link* link = NULL;


	if(die_roll(gameRules->die,34,1)==ERROR){
		printf("Error tirando el dado");
		return;
	}
	value = die_get_lastValue(gameRules->die);

	if(value%2==0){
		link = game_get_link(gameRules->game,13);
		link_set_link(link,12,13);
		space = game_get_space(gameRules->game, 12);
		space_set_south(space,link);
		space = game_get_space(gameRules->game, 21);
		space_set_south(space,NULL);
	
	} else{
		link = game_get_link(gameRules->game,13);
		link_set_link(link,13,21);
		space = game_get_space(gameRules->game, 12);
		space_set_south(space,NULL);
		space = game_get_space(gameRules->game, 21);
		space_set_south(space,link);
		
	}

	return;
}










