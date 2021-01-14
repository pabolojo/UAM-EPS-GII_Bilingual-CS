/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Julia Simon
 * @version 2.0 
 * @date 30/03/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/game.h"

#define N_CALLBACK 19 /*!< Numero total de callbacks*/
#define MAX_ATACK 3 /*!< Numero total de intentos para matar al monstruo*/
/**
* @brief Estructura del game
*/
struct _Game{
  	Player* player;                        /*!< Jugador del juego  */
  	Object* objects[MAX_OBJECTS+1];        /*!< Objetos en el juego */
  	Space* spaces[MAX_SPACES + 1];         /*!< Espacios del juego */
	Link* links[MAX_LINKS + 1];            /*!< maximo links*/
	Die* die;                              /*!< Dado del juego */
	Command * last_cmd;                    /*!< Ultimo comando usado*/
  	STATUS last_cmd_status;	               /*!< Si se ha ejecutado correctamente o no el último comando */
  	Dialogue* dialogue;                    /*!< Dialogue sobre el último comando ejecutado */
  	BOOL over;                             /*!< Booleano que indica game_over cuando se llega al monstruo sin armas*/
  	int intentos_atack;                    /*!< Numero de intentos de ataque al monstruo*/
};

/**
	 Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
	 List of callbacks for each command in the game 
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_grasp(Game* game);
void game_callback_drop(Game* game);
void game_callback_left(Game* game);
void game_callback_right(Game* game);
void game_callback_die(Game* game);
void game_callback_check(Game* game);
void game_callback_move(Game* game);
void game_callback_turnon(Game* game);
void game_callback_turnoff(Game* game);
void game_callback_up(Game* game);
void game_callback_down(Game* game);
void game_callback_open(Game* game);
void game_callback_code(Game* game);
void game_callback_atack(Game* game);
void game_callback_examine(Game* game);
/*void game_callback_save(Game* game);
void game_callback_load(Game* game);*/

/**
* @brief Lista de callbacks
*/
static callback_fn game_callback_fn_list[N_CALLBACK]={
	game_callback_unknown,
	game_callback_exit,
	game_callback_following,
	game_callback_previous,
	game_callback_grasp, 
	game_callback_drop,    
	game_callback_left,
	game_callback_right,
	game_callback_die,
	game_callback_check,
	game_callback_move,
	game_callback_turnon,
	game_callback_turnoff,
	game_callback_down,
	game_callback_up,
	game_callback_open,
	game_callback_code,
	game_callback_atack,
	game_callback_examine
};

/**
	 Game interface implementation
*/

Game* game_create() {
	int i;
	Game* newGame=NULL;

	newGame = (Game *) malloc(sizeof (Game));

	if (newGame == NULL) {
		return NULL;
	}

	for (i = 0; i < MAX_SPACES; i++) {
		newGame->spaces[i] = NULL;
	}
		
	for (i = 0; i < MAX_OBJECTS; i++) {
		newGame->objects[i] = NULL;
	}

    for (i = 0; i < MAX_LINKS; i++) {
		newGame->links[i] = NULL;
	}

	newGame->last_cmd = NULL;

	newGame->last_cmd_status = ERROR;

	newGame->player = game_set_player(newGame);
	newGame->dialogue = dialogue_create();
	newGame->die = die_create(1234); 
	newGame->over =FALSE;
	
	newGame->intentos_atack = 0;
	return newGame;
}

STATUS game_destroy(Game* game) {
	int i = 0;
	
	for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
		space_destroy(game->spaces[i]);
	}
		
	for (i = 0; (i < MAX_OBJECTS) && (game->objects[i] != NULL); i++) {
		object_destroy(game->objects[i]);
	}

	for (i = 0; (i < MAX_LINKS) && (game->links[i] != NULL); i++) {
		link_destroy(game->links[i]);
	}

	dialogue_destroy(game->dialogue);
	player_destroy(game->player);
	die_destroy(game->die);
	free(game);
	return OK;
}

STATUS game_set_dialogue(Game*game,Dialogue*dialogue){
	if(!game || !dialogue)
		return ERROR;
	game->dialogue = dialogue;
	return OK;
}

STATUS game_set_die(Game*game,Die*die){
	if(!game || !die)
		return ERROR;
	game->die = die;
	return OK;
}

STATUS game_set_command(Game*game,Command*command){
	if(!game || !command)
		return ERROR;

	game->last_cmd = command;
	return OK;
}

STATUS game_set_last_command_status(Game*game,STATUS last_cmd_status){
	if(!game)
		return ERROR;

	game->last_cmd_status = last_cmd_status;
	return OK;
}

Player* game_set_player(Game* game){
	Player* player1 = NULL;
	player1 = player_create(0);

	if(player1!=NULL){
		player_set_name(player1, "player1");
	}
	

	return player1;
}

STATUS game_set_player_load(Game*game,Player*player){
	if(!game || !player)
		return ERROR;

	game->player = player;
	return OK;
}

STATUS game_set_player_location(Game* game, Id id) {
		
	if (id == NO_ID) {
		return ERROR;
	}
	
	player_set_space(game->player,id);

	return OK;
}

STATUS game_set_space_description_detallada(Game* game, Space* space){
	
	char str[WORD_SIZE + 1]="";
	char str2[WORD_SIZE + 1]="";
	Link* link =NULL;
	Id link_id = NO_ID;
	Set* objects=NULL;
	int j=0;
	Object* object = NULL;

	if(!space){
		return ERROR;
	}
	
	sprintf(str, "%s: ", space_get_name(space));
	
	link_id = space_get_north(space); 
	if(link_id!=NO_ID){
		link = game_get_link(game,link_id);
		sprintf(str2, "   Link north: %s", link_get_name(link));
		strcat(str, str2);
	}
	link_id = space_get_south(space); 
	if(link_id!=NO_ID){
		link = game_get_link(game,link_id);
		sprintf(str2, "   Link south: %s", link_get_name(link));
		strcat(str,str2);
	}
	link_id = space_get_east(space); 
	if(link_id!=NO_ID){
		link = game_get_link(game,link_id);
		sprintf(str2, "   Link east: %s", link_get_name(link));
		strcat(str,str2);
	}
	link_id = space_get_west(space); 
	if(link_id!=NO_ID){
		link = game_get_link(game,link_id);
		sprintf(str2, "   Link west: %s", link_get_name(link));
		strcat(str,str2);
	}
	link_id = space_get_up(space); 
	if(link_id!=NO_ID){
		link = game_get_link(game,link_id);
		sprintf(str2, "   Link up: %s", link_get_name(link));
		strcat(str,str2);
	}
	link_id = space_get_down(space); 
	if(link_id!=NO_ID){
		link = game_get_link(game,link_id);
		sprintf(str2, "   Link down: %s", link_get_name(link));
		strcat(str,str2);
	}

	/* Falta añadir los objetos */
	sprintf(str2, "   Objetos: ");
	strcat(str,str2);

	objects = space_get_objects(space); /* Conjunto de los objetos del espacio*/ 
	for(j=0;j<set_get_nId(objects);j++){
		object = game_get_object(game,set_get_Id(objects,j));
		if(object_get_oculto(object)==FALSE){
			sprintf(str2, " %s ", object_get_name(object));
			strcat(str,str2);	
		}

	}
	
	space_set_description_detallada(space,str);

	return OK;
}

STATUS game_actualizar_descripciones(Game* game){

	STATUS result = OK;
	int i=0;
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		result = game_set_space_description_detallada(game,game->spaces[i]);
		if(result==ERROR){
			return ERROR;
		}
	}
	return result;
}

STATUS game_add_space(Game* game, Space* space){

	int i=0;

	if (space == NULL) {
		return ERROR;
	}
	while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
		i++;
	}

	if (i >= MAX_SPACES) {
		return ERROR;
	}

	game->spaces[i] = space;
	return OK;

}



STATUS game_add_object(Game*game,Object* object){
	int i = 0;

	if (object == NULL) {
		return ERROR;
	}

	while ( (i < MAX_OBJECTS) && (game->objects[i] != NULL)){
		i++;
	}

	if (i >= MAX_OBJECTS) {
		return ERROR;
	}

	game->objects[i] = object;

	return OK;
}

STATUS game_add_link(Game* game, Link* link){
	
	int i=0;

	if (link == NULL) {
		return ERROR;
	}
	while ( (i < MAX_LINKS) && (game->links[i] != NULL)){
		i++;
	}

	if (i >= MAX_LINKS) {
		return ERROR;
	}

	game->links[i] = link;
	return OK;

}

Space* game_get_space_i(Game* game, int i){
	if(!game){
		return NULL;
	}
	return game->spaces[i];	
}

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
	/* Si no encuentra el espacio con ese id devuelve NULL */	
	return NULL;
}

const char* game_get_space_description(Game* game,Id id){
	if(!game)
		return NULL;
	return  space_get_description(game_get_space(game,id));

}

const char* game_get_space_description_check(Game* game,Id id){
	if(!game)
		return NULL;
	
	return  space_get_description_detallada(game_get_space(game,id));	

}

Link* game_get_link(Game* game, Id id){
	int i = 0;

	if (id == NO_ID) {
		return NULL;
	}
		
	for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++) {
		if (id == link_get_id(game->links[i])){
			return game->links[i];
		}
	}
	/* Si no encuentra el espacio con ese id devuelve NULL */	
	return NULL;
}

Link* game_get_link_i(Game* game, int i){
	
	if(!game){
		return NULL;
	}
	return game->links[i];

}

int game_get_num_links(Game* game){
	int cont = 0, i =0;

	if(!game){
		return -1;
	}
	for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++) {
		cont++;
	}
	/*for(cont=0; game->links[cont]!=NULL;cont++);*/

	return cont;
}

Player* game_get_player(Game* game){
	if(!game){
		return NULL;
	}
	return game->player;
}

Id game_get_player_location(Game* game) {
	return player_get_space(game->player);
}



Object* game_get_object(Game* game, Id id){
	int i = 0;

	if (id == NO_ID) {
		return NULL;
	}
		
	for (i = 0; i < MAX_SPACES && game->objects[i] != NULL; i++) {
		if (id == object_get_id(game->objects[i])){
			return game->objects[i];
		}
	}
	/* Si no encuentra el espacio con ese id devuelve NULL */	
	return NULL;
}


Id game_get_object_location(Game* game,Id id) {
		
	int i = 0, j=0;
	Set* objects=NULL;

	/* Primero miramos si lo tiene el jugador*/
	if(player_get_object(game->player, id)){
		return player_get_space(game->player);
	}

	/* Si no lo tiene el jugador vamos a buscar en los espacios */
	/* Para cada espacio miramos en su conjunto de objetos a ver si esta */
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		objects = space_get_objects(game->spaces[i]); /* Conjunto de los objetos del espacio*/ 
		for(j=0;j<set_get_nId(objects);j++){
			if(set_get_Id(objects,j)==id){
				return space_get_id(game->spaces[i]);
			}
		}
	}
	/* Si no lo tiene ni el jugador ni ningún espacio devuelve que no tiene ID su localizacion */
	return NO_ID;
}


Object* game_get_object_i(Game* game,int i){
	return game->objects[i];
}

int game_get_num_objects(Game* game){
	int cont = 0,i=0;

	if(!game){
		return -1;
	}
	for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
		cont++;
	}

	return cont;
}

int game_get_num_spaces(Game* game){
	int cont = 0, i=0;

	if(!game){
		return -1;
	}
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		cont++;
	}

	return cont;
}

Die* game_get_die(Game* game){
	if(!game){
		return NULL;
	}
	return game->die;	
}

Command* game_get_command(Game* game){
	if(!game){
		return NULL;
	}
	return game->last_cmd;	
}

T_Command game_get_last_command(Game* game){
	if(!game){
		return NO_CMD;
	}
	return command_get_type_command(game->last_cmd);
}


STATUS game_get_last_command_status(Game* game){
	if(!game){
		return ERROR;
	}
	return game->last_cmd_status;
}


const char*  game_get_grasp_object(Game* game){
	if(!game){
		return NULL;
	}
	return command_get_name_command(game->last_cmd);

}

Object* game_get_object_by_name(Game* game, const char* name){

    int i = 0;

    if (!game)
        return NULL;


    for (i = 0; i < MAX_OBJECTS; i++) {
        if (strcmp(object_get_name(game->objects[i]), name) == 0) {
            return game->objects[i];
        }
    }

	return NULL;
}

/*FUNCIONES PARA LAS REGLAS*/
/* Solo se ocultan los que estan en espacios, no los que tiene el jugador */
STATUS game_ocult_objects(Game* game, BOOL ocult){
	
	Object* object = NULL;
	Set * objects = NULL;
	int i = 0;

	objects = player_get_objects(game->player);


	for (i = 0; i < MAX_OBJECTS && game->objects[i]!=NULL; i++) {
		object = game->objects[i];
		if(object_set_oculto(object,ocult)==ERROR)
			return ERROR;
    }
    /* Ponemos visibles todos los del jugador */
    for(i=0; i< set_get_nId(objects) ;i++){
    	object = game_get_object(game,set_get_Id(objects,i));
		if(object_set_oculto(object,FALSE)==ERROR){
			return ERROR;
		}
    }
    return OK;
}

/* FUNCIONES PARA SABER LOS TAMAÑOS DE CADA UNO DE LOS ELEMENTOS DEL GAME */
size_t game_get_game_size(){
	return sizeof(struct _Game);
}

size_t game_get_space_size(){
	return space_get_size();
}

size_t game_get_object_size(){
	return object_get_size();
}

size_t game_get_player_size(){
	return player_get_size();
}

size_t game_get_link_size(){
	return link_get_size();
}

size_t game_get_die_size(){
	return die_get_size();
}

size_t game_get_set_size(){
	return set_get_size();
}

size_t game_get_command_size(){
	return command_get_size();
}

size_t game_get_inventory_size(){
	return inventory_get_size();
}

size_t game_get_dialogue_size(){
	return dialogue_get_size();
}

Dialogue* game_get_dialogue(Game* game){
	if (!game)
        return NULL;
    return game->dialogue;
}

char* game_get_dialogue_text(Game* game){
	if (!game)
        return NULL;
    return dialogue_get_data(game->dialogue);

}

STATUS game_update(Game* game, Command* cmd) {
	game->last_cmd = cmd;
	game_actualizar_descripciones(game);
	if(command_get_type_command(cmd)!=SAVE && command_get_type_command(cmd)!=LOAD){
		dialogue_set_comando(game->dialogue, game->last_cmd);
		(*game_callback_fn_list[command_get_type_command(cmd)])(game);
		dialogue_set_status(game->dialogue, game->last_cmd_status);
	}
	return OK;
}

void game_ilimina_space(Game*game){
	Set* objects =NULL;
	Object* obj_aux=NULL;
	Id space_id=NO_ID;
	int i=0;

	space_id = game_get_player_location(game);
	if (space_id == NO_ID){
		game->last_cmd_status = ERROR;
		return;
	}

	objects = player_get_objects(game->player);

	/* Recorremos los objetos del jugador para ver si tiene alguno encendido*/	
	for(i=0; i<set_get_nId(objects); i++){
		obj_aux = game_get_object(game,set_get_Id(objects, i)); /*Cogemos el objeto que tiene ese id */
		if(object_get_encendido(obj_aux)){
			space_set_iluminado(game_get_space(game,space_id),TRUE);
			return;
		}
	}
	return;
}

void game_print_data(Game* game) {
	int i = 0;
	
	printf("\n\n-------------\n\n");
	
	printf("=> Spaces: \n");
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		space_print(game->spaces[i]);
	}
	
	printf("=> Objects location: \n");

	while(game->objects[i]!=NULL){
		object_print(game->objects[i]);
		i++;
	} 

	printf("=> Player location: %d\n", (int) game_get_player_location(game));
	printf("prompt:> ");
}


BOOL game_is_over(Game* game) {

	if(game->over)
		return TRUE;
	return FALSE;
}

/**
	 Callbacks implementation for each action 
*/

/**
* Funcion del comando desconocido: Si no se reconoce el comando no hace nada
* 
* @param game juego
*/
void game_callback_unknown(Game* game){
}

/**
* Funcion del comando exit: para salir del juego, no escribe nada
* 
* @param game juego
*/
void game_callback_exit(Game* game){
}


/**
* @brief Comando following: mueve el jugador al siguiente espacio
* Cambia el id del espacio que ocupa el jugador al de la posicion siguiente
* 
* @author Miguel Rodriguez
* @param game juego
*/
void game_callback_following(Game* game) {
	int i = 0;
	Id current_id = NO_ID,id_next = NO_ID;
	Link* link = NULL;
	Id space_id = NO_ID;
	Space *space = NULL;

	space_id = game_get_player_location(game);
	if (space_id == NO_ID){
		game->last_cmd_status = ERROR;
		return;
	}
	
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		current_id = space_get_id(game->spaces[i]);
		if (current_id == space_id) {
			current_id = space_get_north(game->spaces[i]);
			link = game_get_link(game,current_id);
			id_next = link_space_connected_to(link,space_id);
			if (id_next != NO_ID) {
				if(link_get_status(link) == CLOSED){
					dialogue_set_link_name(game->dialogue,link_get_name(link));
					dialogue_set_link_cerrado(game->dialogue, TRUE);
					game->last_cmd_status = ERROR;
					return;
				} 
				game_set_player_location(game, id_next);
				space = game_get_space(game,id_next);
				/* Iluminamos el nuevo espacio al que llegamos */
				game_ilimina_space(game);
				dialogue_set_space(game->dialogue, space_get_name(space));
				game->last_cmd_status = OK;
			} else{
				game->last_cmd_status = ERROR;
			}
			return;
		}
	}
}

/**
* @brief Comando previous: mueve el jugador al espacio anterior
* Cambia el id del espacio que ocupa el jugador al de la posicion anterior
*
* @author Miguel Rodriguez
* @param game juego
*/
void game_callback_previous(Game* game) {
	int i = 0;
	Id current_id = NO_ID, id_next=NO_ID;
	Id space_id = NO_ID;
	Link* link = NULL; 
	Space* space = NULL;

	space_id = game_get_player_location(game);
	
	if (NO_ID == space_id) {
		game->last_cmd_status = ERROR;
		return;
	}
	
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		current_id = space_get_id(game->spaces[i]);
		if (current_id == space_id) {
			current_id = space_get_south(game->spaces[i]);
			link = game_get_link(game,current_id);
			id_next = link_space_connected_to(link,space_id);
			if (id_next != NO_ID) {
				if(link_get_status(link) == CLOSED){
					dialogue_set_link_name(game->dialogue,link_get_name(link));
					dialogue_set_link_cerrado(game->dialogue, TRUE);
					game->last_cmd_status = ERROR;
					return;
				} 
				game_set_player_location(game, id_next);
				space = game_get_space(game,id_next);
				/* Iluminamos el nuevo espacio al que llegamos */
				game_ilimina_space(game);
				dialogue_set_space(game->dialogue, space_get_name(space));
				game->last_cmd_status = OK;
			} else{
				game->last_cmd_status = ERROR;
			}
			return;
		}
	}
}

/**
* @brief Comando grasp: coge un objeto
* Funcion que cambia el objeto y pasa de estar en el espacio al inventorio del jugador
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_grasp(Game* game){

	const char* nombre = command_get_name_command(game->last_cmd);
	Set* objects = NULL;
	int i = 0;
	Id player_id = NO_ID;
	Object* object_aux = NULL;

	player_id = game_get_player_location(game);
	if (NO_ID == player_id){
		game->last_cmd_status = ERROR;
		return;
	}
	if(space_get_iluminado(game_get_space(game,player_id))==FALSE){
		/*No podemos coger objetos de espacios que no estan iluminados*/
		game->last_cmd_status = ERROR;
		return;
	}
	/*cogemos el set de los objetos del espacio en el que esta el jugador*/
	objects = space_get_objects(game_get_space(game, player_id));
	
	for(i=0; i<set_get_nId(objects) ;i++){
		
		object_aux = game_get_object(game,set_get_Id(objects,i));
		/*if(object_get_oculto(object_aux)){
			game->last_cmd_status=ERROR;
			return;
		}*/
		
		if(!strcmp(nombre,object_get_name(object_aux))){
			dialogue_set_object(game->dialogue,object_get_name(object_aux));
			if(object_get_movible(object_aux)==FALSE){
				dialogue_set_object_nomovible(game->dialogue,TRUE);
				game->last_cmd_status = ERROR;
				return;
			}
			if(object_get_oculto(object_aux)==TRUE){
				game->last_cmd_status = ERROR;
				return;
			}
			if(player_set_object(game->player, object_get_id(object_aux))==OK){
				object_set_movido(object_aux,TRUE);
				space_del_objects(game_get_space(game, player_id), object_get_id(object_aux));
				game->last_cmd_status = OK;
				return;
			}
		}			
	}

	game->last_cmd_status = ERROR;
	return;
			
}

/**
* @brief Comando drop: deja un objeto
* Deja el objeto en el espacio en el que se encuentra
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_drop(Game* game) {
	
	const char* nombre = command_get_name_command(game->last_cmd);
	Set* objects = NULL;
	int i = 0;
	Id player_id = NO_ID;
	Space* space_act=NULL;
	Object* object_aux=NULL;

	player_id = game_get_player_location(game);
	if (NO_ID == player_id){
		game->last_cmd_status = ERROR;
		return;
	}

	space_act = game_get_space(game, player_id);

	/*cogemos el set de los objetos del espacio en el que esta el jugador*/
	objects = player_get_objects(game->player);

	for(i=0; i< set_get_nId(objects) ;i++){
		object_aux = game_get_object(game,set_get_Id(objects,i));
		if(!strcmp(nombre,object_get_name(object_aux))){
			dialogue_set_object(game->dialogue,object_get_name(object_aux));
			if(object_get_movible(object_aux)==FALSE){
				dialogue_set_object_nomovible(game->dialogue,TRUE);
				game->last_cmd_status = ERROR;
				return;
			}
						space_add_objects(space_act, object_get_id(object_aux));
			player_del_objects(game->player, object_get_id(object_aux));
			game->last_cmd_status = OK;
			return;
		}				
	}
	game->last_cmd_status = ERROR;
	return;
}

/**
* @brief Comando left:  mueve el jugador al espacio de la izquierda
* Esto solo ocurre en algunas de las casillas especiales
* Cambia el id del espacio que ocupa el jugador al de la posicion de la casilla
* especial
* 
* @author Julia Simon
* @param game juego
*/

void game_callback_left(Game* game) {
	int i = 0;
	Id current_id = NO_ID,id_next = NO_ID, space_id = NO_ID;
	Link* link = NULL;
	Space* space = NULL;

	space_id = game_get_player_location(game);
	
	if (NO_ID == space_id) {
		game->last_cmd_status = ERROR;
		return;
	}	
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		current_id = space_get_id(game->spaces[i]);
		if (current_id == space_id) {
			current_id = space_get_west(game->spaces[i]);
			link = game_get_link(game,current_id);
			id_next = link_space_connected_to(link,space_id);
			if (id_next != NO_ID) {
				if(link_get_status(link) == CLOSED){
					dialogue_set_link_name(game->dialogue,link_get_name(link));
					dialogue_set_link_cerrado(game->dialogue, TRUE);
					game->last_cmd_status = ERROR;
					return;
				} 
				game_set_player_location(game, id_next);
				space = game_get_space(game,id_next);
				/* Iluminamos el nuevo espacio al que llegamos */
				game_ilimina_space(game);
				dialogue_set_space(game->dialogue, space_get_name(space));
				game->last_cmd_status = OK;
			} else{
				game->last_cmd_status = ERROR;
			}
			return;
		}
	}
}

/**
* @brief Comando right:  mueve el jugador al espacio de la derecha
* Esto solo ocurre en algunas de las casillas especiales
* Cambia el id del espacio que ocupa el jugador al de la posicion de la casilla
* especial
* 
* @author Miguel Rodriguez
* @param game juego
*/
void game_callback_right(Game* game) {
	int i = 0;
	Id current_id = NO_ID,id_next = NO_ID, space_id = NO_ID;  
	Link* link = NULL;
	Space* space = NULL;

	space_id = game_get_player_location(game);
	
	if (NO_ID == space_id) {
		game->last_cmd_status = ERROR;
		return;
	}	
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		current_id = space_get_id(game->spaces[i]);
		if (current_id == space_id) {
			current_id = space_get_east(game->spaces[i]);
			link = game_get_link(game,current_id);
			id_next = link_space_connected_to(link,space_id);
			if (id_next != NO_ID) {
				if(link_get_status(link) == CLOSED){
					dialogue_set_link_name(game->dialogue,link_get_name(link));
					dialogue_set_link_cerrado(game->dialogue, TRUE);
					game->last_cmd_status = ERROR;
					return;
				} 
				game_set_player_location(game, id_next);
				space = game_get_space(game,id_next);
				/* Iluminamos el nuevo espacio al que llegamos */
				game_ilimina_space(game);
				dialogue_set_space(game->dialogue, space_get_name(space));
				game->last_cmd_status = OK;
			} else{
				game->last_cmd_status = ERROR;
			}
			return;
		}
	}
}

/**
* @brief Comando up:  mueve el jugador al espacio de arriba
* Cambia el id del espacio que ocupa el jugador al del espacio de arriba
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_up(Game* game){
	int i = 0;
	Id current_id = NO_ID,id_next = NO_ID, space_id = NO_ID;  
	Link* link = NULL;
	Space* space = NULL;
	
	space_id = game_get_player_location(game);
	
	if (NO_ID == space_id) {
		game->last_cmd_status = ERROR;
		return;
	}	
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		current_id = space_get_id(game->spaces[i]);
		if (current_id == space_id) {
			current_id = space_get_up(game->spaces[i]);
			link = game_get_link(game,current_id);
			id_next = link_space_connected_to(link,space_id);
			if (id_next != NO_ID) {
				if(link_get_status(link) == CLOSED){
					dialogue_set_link_name(game->dialogue,link_get_name(link));
					dialogue_set_link_cerrado(game->dialogue, TRUE);
					game->last_cmd_status = ERROR;
					return;
				} 
				game_set_player_location(game, id_next);
				space = game_get_space(game,id_next);
				/* Iluminamos el nuevo espacio al que llegamos */
				game_ilimina_space(game);
				dialogue_set_space(game->dialogue, space_get_name(space));
				game->last_cmd_status = OK;
			} else{
				game->last_cmd_status = ERROR;
			}
			return;
		}
	}
}


/**
* @brief Comando up:  mueve el jugador al espacio de arriba
* Cambia el id del espacio que ocupa el jugador al del espacio de abajo
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_down(Game* game){
	int i = 0;
	Id current_id = NO_ID,id_next = NO_ID, space_id = NO_ID;  
	Link* link = NULL;
	Space* space= NULL;
	space_id = game_get_player_location(game);
	
	if (NO_ID == space_id) {
		game->last_cmd_status = ERROR;
		return;
	}	
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
		current_id = space_get_id(game->spaces[i]);
		if (current_id == space_id) {
			current_id = space_get_down(game->spaces[i]);
			link = game_get_link(game,current_id);
			id_next = link_space_connected_to(link,space_id);
			if (id_next != NO_ID) {
				if(link_get_status(link) == CLOSED){
					dialogue_set_link_name(game->dialogue,link_get_name(link));
					dialogue_set_link_cerrado(game->dialogue, TRUE);
					game->last_cmd_status = ERROR;
					return;
				} 
				game_set_player_location(game, id_next);
				space = game_get_space(game,id_next);
				/* Iluminamos el nuevo espacio al que llegamos */
				game_ilimina_space(game);
				dialogue_set_space(game->dialogue, space_get_name(space));
				game->last_cmd_status = OK;
			} else{
				game->last_cmd_status = ERROR;
			}
			return;
		}
	}
}

/**
* @brief comando die: sirve para tirar el dado
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_die(Game* game){

	if(die_roll(game->die,6,1)==ERROR){
		fprintf(stderr,"Error al tirar el dado");
		game->last_cmd_status = ERROR;
	}
	game->last_cmd_status = OK;
	return;
}

/**
* @brief comando check. Para ver la descripción de espacios y objetos
* 
* @author Miguel Rodriguez
* @param game juego
*/
void game_callback_check(Game* game){
    Set* objects=NULL;
	int i = 0;
	Id player_id = NO_ID;
	const char* object_name = command_get_name_command(game->last_cmd);
	Object* obj_aux=NULL;

	
	player_id = game_get_player_location(game);
	if(NO_ID == player_id){
		game->last_cmd_status = ERROR;
		return;
	}

	/*if(space_get_iluminado(game_get_space(game, player_id))==FALSE){
		if(strcmp(object_name, "space")==0 || strcmp(object_name, "s")==0){
			dialogue_set_check_space(game->dialogue,TRUE);
		}
		game->last_cmd_status = ERROR;
		return;
	}*/

	if(strcmp(object_name, "space")==0 || strcmp(object_name, "s")==0){
		dialogue_set_check_space(game->dialogue,TRUE);
		if(space_get_iluminado(game_get_space(game, player_id))==FALSE){
			game->last_cmd_status = ERROR;
		} else{
			game->last_cmd_status = OK;
		}
        return;
	} else{
	
		objects = space_get_objects(game_get_space(game, player_id));
		for(i=0; i<set_get_nId(objects); i++){
			obj_aux = game_get_object(game,set_get_Id(objects, i)); /*Cogemos el objeto que tiene ese id */
			if(object_get_oculto(obj_aux)){
				game->last_cmd_status=ERROR;
				return;
			}
			if(!strcmp(object_get_name(obj_aux),object_name)){
				dialogue_set_object(game->dialogue, object_get_name(obj_aux));
				if(space_get_iluminado(game_get_space(game, player_id))==FALSE || object_get_oculto(obj_aux)){
					game->last_cmd_status = ERROR;
					return;
				}
				game->last_cmd_status = OK;
				return;
			}
		}
		
		objects = player_get_objects(game->player);
		
		for(i=0; i<set_get_nId(objects); i++){
			obj_aux= game_get_object(game,set_get_Id(objects, i)); /*Cogemos el objeto que tiene ese id */
			if(object_get_oculto(obj_aux)){
				game->last_cmd_status=ERROR;
				return;
			}
			if(!strcmp(object_get_name(obj_aux),object_name)){
				dialogue_set_object(game->dialogue, object_get_name(obj_aux));
				if(space_get_iluminado(game_get_space(game, player_id))==FALSE){
					game->last_cmd_status = ERROR;
					return;
				}
				game->last_cmd_status = OK;
				return;
			}
		}
	}
	
	game->last_cmd_status = ERROR;
	return;
}

/**
* @brief comando move. Comando para moverse en cualquier direccion
* En funcion de lo segundo indicado se mueve al norte, sur, este u oeste. 
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_move(Game* game){
	const char* direction = command_get_name_command(game->last_cmd);
	Id player_id = NO_ID;

	player_id = game_get_player_location(game);
	
	if (NO_ID == player_id){
		game->last_cmd_status = ERROR;
		return;
	}

	if(strcmp(direction,"n")==0 || strcmp(direction,"north")==0){
		command_set_type_command(game->last_cmd, FOLLOWING);
		game_callback_following(game);
	}else if(strcmp(direction,"s")==0 || strcmp(direction,"south")==0){
		command_set_type_command(game->last_cmd, PREVIOUS);
		game_callback_previous(game);
	}else if(strcmp(direction,"e")==0 || strcmp(direction,"east")==0){
		command_set_type_command(game->last_cmd, RIGHT);
		game_callback_right(game);
	}else if(strcmp(direction,"w")==0 || strcmp(direction,"west")==0){
		command_set_type_command(game->last_cmd, LEFT);
		game_callback_left(game);
	}else if(strcmp(direction,"u")==0 || strcmp(direction,"up")==0){
		command_set_type_command(game->last_cmd, UP);
		game_callback_up(game);
	}else if(strcmp(direction,"dw")==0 || strcmp(direction,"down")==0){
		command_set_type_command(game->last_cmd, DOWN);
		game_callback_down(game);
	}else{
		game->last_cmd_status = ERROR;	
	}

	return;

}

/**
* @brief comando turnon. Comando para encender un objeto
* 
* @author Sergio de los Reyes
* @param game juego
*/
void game_callback_turnon(Game* game) {
    Id object_id = NO_ID, space_id = NO_ID;
    Object* object = NULL;
    int i = 0;
    Command *command = NULL;
    char *name_obj = NULL;

    if (!game)
        return;

    command = game->last_cmd;

    for (i = 0; i < MAX_OBJECTS && game->objects[i]!=NULL; i++) {
        name_obj = command_get_name_command(command);
        if (strcmp(object_get_name(game->objects[i]), name_obj) == 0) {
        	dialogue_set_object(game->dialogue,name_obj);
            object_id = object_get_id(game->objects[i]);
        }
    }

    if (object_id == NO_ID || player_get_object(game->player, object_id) == FALSE) {
        game->last_cmd_status = ERROR;
        return;
    }

    object = game_get_object(game, object_id);
    
    if(object_get_iluminado(object) == FALSE){
        game->last_cmd_status = ERROR;
        return;
    }

    if (object_set_encendido(object, TRUE) == ERROR) {
        game->last_cmd_status = ERROR;
        return;
    }

    /* Iluminamos el espacio en el que nos encontramos */
    space_id = game_get_player_location(game);
    space_set_iluminado(game_get_space(game,space_id),TRUE);

    game->last_cmd_status = OK;
}

/**
* @brief comando turnoff. Comando para apagar un objeto
* 
* @author Sergio de los Reyes
* @param game juego
*/
void game_callback_turnoff(Game* game) {
	Id object_id = NO_ID;
    Object* object = NULL;
    int i = 0;
    Command *command = NULL;
    char *name_obj = NULL;

    if (!game)
        return;

    command = game->last_cmd;

    for (i = 0; i < MAX_OBJECTS && game->objects[i]!=NULL; i++) {
        name_obj = command_get_name_command(command);
        if (strcmp(object_get_name(game->objects[i]), name_obj) == 0) {
        	dialogue_set_object(game->dialogue,name_obj);
            object_id = object_get_id(game->objects[i]);
        }
    }

    if (object_id == NO_ID || player_get_object(game->player, object_id) == FALSE) {
        game->last_cmd_status = ERROR;
        return;
    }

    object = game_get_object(game, object_id);

    
    if(object_get_iluminado(object) == FALSE){
        game->last_cmd_status = ERROR;
        return;
    }

    if (object_set_encendido(object, FALSE) == ERROR) {
        game->last_cmd_status = ERROR;
        return;
    }

    game->last_cmd_status = OK;
}

/**
* @brief comando open. Comando para abrin un enlace (link)
* 
* @author Sergio de los Reyes
* @param game juego
*/
void game_callback_open(Game* game) {
	Command* command=NULL;
    Id object_id = NO_ID;
    Id link_id = NO_ID;
    Link* link = NULL;
    Object* object=NULL;
    int i = 0;
	char* link_name = "";
	char* object_name = "";

    if (!game) {
        return;
    }

    command = game->last_cmd;
	link_name = command_get_name_command(command);
	object_name = command_get_key_command(command);

	for (i = 0; i < MAX_LINKS && game->links[i]!=NULL; i++) {
        if (strcmp(link_get_name(game->links[i]),link_name) == 0) {
            link_id = link_get_id(game->links[i]);
            link = game->links[i];
            dialogue_set_link_name(game->dialogue, link_get_name(link));
        }
    }

	/* Si el link ya esta abierto no necesita abrirse */
	if (link_get_status(link) == OPENNED) {
		dialogue_set_link_open(game->dialogue,TRUE);
        game->last_cmd_status = ERROR;
        return;
    }

    for (i = 0; i < MAX_OBJECTS && game->objects[i]!=NULL; i++) {
        if (strcmp(object_get_name(game->objects[i]), object_name) == 0) {
            object_id = object_get_id(game->objects[i]);
			object = game->objects[i];
			dialogue_set_object(game->dialogue, object_get_name(object));
        }
    }
	
    if (object_id == NO_ID || link_id == NO_ID){
        game->last_cmd_status = ERROR;
        return;
    }
    
    
    if (player_get_object(game->player, object_id) == FALSE) {
		printf("Error jugador no tiene el objeto\n");
        game->last_cmd_status = ERROR;
        return;
    }


    if (object_get_open(object) != link_id) {
		printf("Error objeto no abre ese link\n");
        game->last_cmd_status = ERROR;
        return;
    }

    if (link_set_status(link, OPENNED) == ERROR) {
		printf("Error fijando el nuevo status del link\n");
        game->last_cmd_status = ERROR;
        return;
    }

    game->last_cmd_status = OK;
}

/**
* @brief comando code. Comando para montar el codigo
* Para que se monte el objeto codigo necesitamos tener todos los objetos codigo
* 
* @author Miguel Rodriguez
* @param game juego
*/
void game_callback_code(Game * game){
    
    Object * codigo = NULL;
    
    if(player_get_object(game->player, 5) && player_get_object(game->player, 6) && player_get_object(game->player, 7)
                                          && player_get_object(game->player, 8) && player_get_object(game->player, 9)
                                          && player_get_object(game->player, 10)){
                                              
        player_del_objects(game->player, 5);
        player_del_objects(game->player, 6);
        player_del_objects(game->player, 7);
        player_del_objects(game->player, 8);
        player_del_objects(game->player, 9);
        player_del_objects(game->player, 10);
        
        codigo = object_create(34);
        object_set_name(codigo, "Codigo");
        object_set_description(codigo, "\"[ 8 7 3 2 9 1 ] -Con este codigo podré abrir la cerradura electronica que bloquea la puerta\"");
        object_set_open(codigo, 6); /* Codigo de la puerta que se abre con el codigo */
        game_add_object(game, codigo);
        player_set_object(game->player, object_get_id(codigo));
        game->last_cmd_status = OK;
    } else{
        game->last_cmd_status = ERROR;
    }
    
    return;
}

/**
* @brief comando atack. Sirve para atacar al monstruo
* Se matará al monstruo según lo que aparezca en el dado
* No se tendrá acceso a ninguno de los links del espacio en el que está el monstruo hasta que no lo maten
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_atack(Game* game){
	int i = 0, die=0;
	Set* objects=NULL;
	Id player_id = NO_ID;
	Space* space_act=NULL;
	Id object_id = NO_ID, monster_id = NO_ID;
	Link * link = NULL;

	player_id = game_get_player_location(game);
	if (NO_ID == player_id){
		game->last_cmd_status = ERROR;
		return;
	}
	
	space_act = game_get_space(game, player_id);
	objects = space_get_objects(space_act);

	/* Comprobamos que el monstruo esta en la habitacion */
	for(i=0; i<set_get_nId(objects) ;i++){
		monster_id = set_get_Id(objects,i);
		if(monster_id == 19){ /*Id correspondiente al monstruo */
			printf("Has encontrado al monstruo\n");
			break;
		} else{
			monster_id = NO_ID;
		}	
	}

	if(monster_id == NO_ID){
		/*El monstruo no esta en esa habitacion*/
		dialogue_set_no_monster(game->dialogue,TRUE);
		game->last_cmd_status = ERROR;
		return;
	}

	/*cogemos el set de los objetos del jugador para ver si tiene un arma para poder luchar*/
	objects = player_get_objects(game->player);

	for(i=0; i<set_get_nId(objects) ;i++){
		object_id = set_get_Id(objects,i);
		if(object_id == 11 || object_id == 20 || object_id == 23){ /*Ids correspondientes a las armas*/
			break;
		} else{
			object_id = NO_ID;
		}
		
	}

	if(object_id == NO_ID){
		/*El jugador no tiene armas para luchar, pierde la partida */
		game->over = TRUE;
		game->last_cmd_status = ERROR;
		return;
	}


	/* Luchamos contra el monstruo */
	die_roll(game->die,6,1);

	die = die_get_lastValue(game->die);

	game->intentos_atack++;
	if(die%2 == 0){
		/* Matamos al monstruo */
		link = game_get_link(game,7);
		space_set_north(space_act,link);
		link = game_get_link(game,19);
		space_set_east(space_act,link);
		link = game_get_link(game,20);
		space_set_west(space_act,link);

		for(i=0;i<3;i++){
			space_set_gdesc(space_act, "        ",i);
		}
		game->last_cmd_status=OK;
		return;
	} else{
		/* Luchamos pero sin éxito */
		if(game->intentos_atack>= MAX_ATACK){
			game->over = TRUE;
		}
		printf(" No has conseguido matar al monstruo ");
		game->last_cmd_status=ERROR;
		return;
	}



	
}

/**
* @brief comando examine. Sirve para buscar objetos ocultos en una habitación
* 
* @author Julia Simon
* @param game juego
*/
void game_callback_examine(Game* game){
	int i = 0;
	Object* object_aux = NULL;
	Set* objects=NULL;
	Id player_id = NO_ID;
	Space* space_act=NULL;

	player_id = game_get_player_location(game);
	if (NO_ID == player_id){
		game->last_cmd_status = ERROR;
		return;
	}
	
	space_act = game_get_space(game, player_id);
	objects = space_get_objects(space_act);

	for(i=0; i<set_get_nId(objects) ;i++){
		object_aux = game_get_object(game,set_get_Id(objects,i));
		if(object_get_oculto(object_aux)){
			object_set_oculto(object_aux,FALSE);
		}
	}
	game->last_cmd_status=OK;
	return;
		
}



