/** 
 * @brief It implements the game_reader interface
 * 
 * @file game_management.c
 * @author Julia Simon
 * @version 1.2 
 * @date 26/04/2018
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/game.h"
#include "../include/game_management.h"


Game* game_management_game_create_from_file(char* filename) {
    Space* space_aux=NULL;
    Game* game = NULL;

    game = game_create();
    if (!game)
        return NULL;
    if (game_management_game_load(game, filename) == ERROR){
        printf("Error en el load\n");
        return NULL;
    }
    
    /* El jugador empieza en la primera casilla*/
    space_aux = game_get_space_i(game,0);
    if(player_set_space(game_get_player(game), space_get_id(space_aux))==ERROR)
        return NULL;
    return game;

}

STATUS game_management_game_load(Game* game, char* filename) {
    FILE* file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char pos1[WORD_SIZE] = "       ";
    char pos2[WORD_SIZE] = "       ";
    char pos3[WORD_SIZE] = "       ";
    char name_object[WORD_SIZE] = "";
    char name_link[WORD_SIZE] = "";
    char description[WORD_SIZE] = "";
    char* toks = NULL;
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
    Id id_object = NO_ID, space_object = NO_ID;
    Id id_link = NO_ID, space_link = NO_ID, space_link2 = NO_ID;
	Id open = NO_ID;
    Link* link;
    Space* space = NULL;
    Object* object = NULL;
    DOOR puerta = OPENNED;
    STATUS status = OK;
    int iluminado = 0, movible=0,oculto=0,comprobante=0;
	


    bzero(name_object,WORD_SIZE);
    bzero(name_link,WORD_SIZE);
    bzero(description,WORD_SIZE);

    if (!filename) {
        return ERROR;
    }
    
    file = fopen(filename, "r");
    if (file == NULL) {
        return ERROR;
    }
    
    while (fgets(line, WORD_SIZE, file)) {

        /* Creacion de los links */
        if (strncmp("#l:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id_link = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name_link, toks);
            toks = strtok(NULL, "|");
            space_link = atol(toks);
            toks = strtok(NULL, "|");
            space_link2 = atol(toks);
            toks = strtok(NULL, "|");
            puerta = atol(toks);

   
            link = link_create(id_link);
            
            if(link != NULL) {
                link_set_name(link, name_link);
                link_set_link(link, space_link,space_link2);
				if(puerta==0){
					link_set_status(link, OPENNED);
                }
                game_add_link(game, link);
            }
        }
		
        if (strncmp("#s:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            south = atol(toks);
            toks = strtok(NULL, "|");
            west = atol(toks);
            toks = strtok(NULL, "|");
            north = atol(toks);
            toks = strtok(NULL, "|");
            east = atol(toks);
            toks = strtok(NULL, "|");
            up = atol(toks);
            toks = strtok(NULL, "|");
            down = atol(toks);
            toks = strtok(NULL, "|");
            iluminado = atol(toks);
			toks = strtok(NULL, "|");
            strcpy(description, toks);
            toks = strtok(NULL, "|");
			if(toks!=NULL){
            	strcpy(pos1, toks);
            	toks = strtok(NULL, "|");
            	strcpy(pos2, toks);
            	toks = strtok(NULL, "|");
            	strcpy(pos3, toks);
				comprobante = 1;
			}
            
            space = space_create(id);
            if (space != NULL) {
                space_set_name(space, name);
                space_set_north(space,game_get_link(game,north));
                space_set_south(space,game_get_link(game,south));           
                space_set_east(space,game_get_link(game,east));
                space_set_west(space,game_get_link(game,west));
                space_set_up(space, game_get_link(game, up));
                space_set_down(space, game_get_link(game, down));
                if(iluminado == 1)
                    space_set_iluminado(space, TRUE);
                else
                    space_set_iluminado(space, FALSE);

				space_set_description(space,description);
				if(comprobante==1){
                	space_set_gdesc(space, pos1,0);
                	space_set_gdesc(space, pos2,1);
                	space_set_gdesc(space, pos3,2);
				}
                game_add_space(game, space);
				comprobante =0;
            }
        }
        if(strncmp("#o:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id_object = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name_object, toks);
            toks = strtok(NULL, "|");
            space_object = atol(toks);
			toks = strtok(NULL, "|");
			movible = atol(toks);
			toks = strtok(NULL, "|");
			oculto = atol(toks);
			toks = strtok(NULL, "|");
			open = atol(toks);
			toks = strtok(NULL, "|");
			iluminado = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(description, toks);
			
            
            object = object_create(id_object);
            object_print(object);
            if(object != NULL) {
                object_set_name(object, name_object);
                object_set_description(object, description);
				if(movible==0)
					object_set_movible(object,FALSE);
				if(oculto==1)
					object_set_oculto(object,TRUE);
				if(iluminado==1)
					object_set_iluminado(object,TRUE);
				if(open!=NO_ID)
					object_set_open(object,open);
                space_add_objects(game_get_space(game, space_object), id_object);
                object_set_pos_inicial(object,space_object);
                game_add_object(game,object);
            }
        }

    }
    if (ferror(file)) {
        status = ERROR;
    }
    
    fclose(file);
    
    return status;
}

STATUS game_management_save(Game* game, char* filename){
    
    FILE *outfile=NULL;
	Link * link=NULL;
	Object* object =NULL;
	Player* player=NULL;
	Space* space=NULL;
	Inventory* inventory =NULL;
	Die* die=NULL;
	Command* command=NULL;
	Set* set=NULL;
	Dialogue* dialogue=NULL;

    size_t s=0,s2=0;
    int num = 0,num2=0,i=0;

    if (!game){
        return ERROR;
    }

    outfile = fopen(filename,"wb");
    if(outfile==NULL){
        printf("Error abriendo el archivo que guarda la partida\n");
        return ERROR;
    }

	num = 10000;
    fwrite(&num,sizeof(int),1,outfile);
    /* Guardamos el game */
    if(fwrite(game, game_get_game_size(),1,outfile)!=1){
        printf("Error guardando el game\n");
        return ERROR;
    }

    /* Guardamos los links */
    /* Primero guardamos cuantos links hay */
    num = game_get_num_links(game);
    if(fwrite(&s, sizeof(int),1,outfile)!=1){
        printf("Error guardando el numero de links\n");
        return ERROR;
    }
    /* Vamos guardando cada link */
    s = game_get_link_size();
	
    for (i=0;i<num;i++){
		link = game_get_link_i(game,i);
		printf("link%d\n",(int)link_get_id(link));
        if(fwrite(link, s ,1,outfile)!=1){
            printf("Error guardando el link\n");
            return ERROR;
        }
    }

	printf("despues links\n");
    /* Guardamos los espacios */
    /* Primero guardamos cuantos espacios hay */
    num = game_get_num_spaces(game);
    if(fwrite(&num, sizeof(int),1,outfile)!=1){
        printf("Error guardando el numero de espacios\n");
        return ERROR;
    }
	printf("%d\n",num);
	printf("despues num spaces\n");
    /* Vamos guardando cada espacio */
    s = game_get_space_size();
    for (i=0;i<num;i++){
        /* Guardamos el espacio */
		space = game_get_space_i(game,i);
        if(fwrite(space, s ,1,outfile)!=1){
            printf("Error guardando el espacio\n");
            return ERROR;
        }
		printf("%d\n",i);
        /* Guardamos el set del espacio */
        s2 = game_get_set_size();
		set = space_get_objects(game_get_space_i(game,i));
        if(fwrite(set, s2,1,outfile)!=1){
            printf("Error guardando el set del espacio\n");
            return ERROR;
        }
    }
	printf("despues spaces\n");




    /* Guardamos los objetos */
    /* Primero guardamos cuantos objetos hay */
    num = game_get_num_objects(game);
    if(fwrite(&num2, sizeof(int),1,outfile)!=1){
        printf("Error guardando el numero de objetos\n");
        return ERROR;
    }
	printf("despues objects\n");
    /* Vamos guardando cada objeto */
    s = game_get_object_size();
    for (i=0;i<num;i++){
		object = game_get_object_i(game,i);
        if(fwrite(object, s ,1,outfile)!=1){
            printf("Error guardando el objeto\n");
            return ERROR;
        }
    }
	printf("despues objects\n");


    /* Guardamos el JUGADOR */
    /* Tamaño del jugador */
    s = game_get_player_size();
	player = game_get_player(game);
    if(fwrite(player, s ,1,outfile)!=1){
        printf("Error guardando el tamaño del player\n");
        return ERROR;
    }
	printf("despues 5556\n");
    /* Tamaño del inventorio del jugador */
    s = game_get_inventory_size();
	inventory = player_get_inventory(game_get_player(game));
    if(fwrite(inventory, s ,1,outfile)!=1){
        printf("Error guardando el inventory\n");
        return ERROR;
    }
	printf("despues sdf\n");
    /* Guardamos el set del inventory */
    s = game_get_set_size();
	set = inventory_get_objects(player_get_inventory(game_get_player(game)));
    if(fwrite(set, s ,1,outfile)!=1){
        printf("Error guardando el set del inventory\n");
        return ERROR;
    }
    printf("despues inventory y player\n");



    /* Guardamos el dado */
    /* Tamaño del dado */
    s = game_get_die_size();
	die = game_get_die(game);
    if(fwrite(die, s ,1,outfile)!=1){
        printf("Error guardando el dado\n");
        return ERROR;
    }


	printf("despues die\n");

    /* Guardamos el comando */
    /* Tamaño del comando */
    s = game_get_command_size();
	command = game_get_command(game);
    if(fwrite(command, s,1,outfile)!=1){
        printf("Error guardando el comando\n");
        return ERROR;
    }

	/* Guardamos el dialogue */
	s = game_get_dialogue_size();
	dialogue = game_get_dialogue(game);
	if(fwrite(dialogue, s,1,outfile)!=1){
        printf("Error guardando el comando\n");
        return ERROR;
    }
	printf("despues command\n");
    fclose(outfile);
	printf("despues fclose\n");
    return OK;        
}

Game* game_management_load(char* filename){

    Game* game = NULL;
    FILE *inputfile = NULL;
    Link * link = NULL;
    Object* object = NULL;
    Player* player = NULL;
    Space* space = NULL;
    Inventory* inventory = NULL;
    Die* die = NULL;
    Command* command = NULL;
    Set* set = NULL;
	Dialogue* dialogue=NULL;

    size_t s=0,s2=0;
    int num = 0,i=0;

    inputfile = fopen(filename,"r");
    if(inputfile==NULL){
        printf("Error abriendo el archivo que carga la partida\n");
        return NULL;
    }

    /* Leemos el game */
    if(fread(&game, game_get_game_size(),1,inputfile)!=1){
        printf("Error leyendo el game\n");
        return NULL;
    }
	printf("Se lee bien el game\n");
    /* Leemos los links */
    /* Primero leemos cuantos links hay */
    if(fread(&s, sizeof(int),1,inputfile)!=1){
        printf("Error leyendo el numero de links\n");
        return NULL;
    }

	printf("Se lee bien el numero de links en game\n");
    /* Vamos leyendo cada link */
    s = game_get_link_size();
    for (i=0;i<num;i++){
        if(fread(&link, s ,1,inputfile)!=1){
            printf("Error leyendo el link\n");
            return NULL;
        }
        game_add_link(game,link);
    }




    /* Leemos los espacios */
    /* Primero leemos cuantos espacios hay */
    if(fread(&num, sizeof(int),1,inputfile)!=1){
        printf("Error leyendo el numero de espacios\n");
        return NULL;
    }
    /* Vamos leyendo cada espacio */
    s = game_get_space_size();
    for (i=0;i<num;i++){
        /* Leemos el espacio */
        if(fread(&space, s ,1,inputfile)!=1){
            printf("Error guardando el espacio\n");
            return ERROR;
        }
		game_add_space(game,space);
        /* Leemos el set del espacio */
        s2 = game_get_set_size();
        if(fread(&set, s2 ,1,inputfile)!=1){
            printf("Error guardando el set del espacio\n");
            return ERROR;
        }
        if(space_set_objects(space,set)==ERROR){
            printf("Error añadiendo el set del espacio\n");
			return ERROR;
        }
    }





    /* Leemos los objetos */
    /* Primero guardamos cuantos objetos hay */
    if(fread(&num, sizeof(int),1,inputfile)!=1){
        printf("Error leyendo el numero de objetos\n");
        return ERROR;
    }
    /* Vamos leyendo cada objeto */
    s = game_get_object_size();
    for (i=0;i<num;i++){
        if(fread(&object, s ,1,inputfile)!=1){
            printf("Error leyendo el objeto\n");
            return ERROR;
        }
        game_add_object(game,object);
    }



    /* Leemos el JUGADOR */
    /* Tamaño del jugador */
    s = game_get_player_size();
    if(fread(&player, s ,1,inputfile)!=1){
        printf("Error leyendo el tamaño del link\n");
        return ERROR;
    }
    game_set_player_load(game,player);

    /* Tamaño del inventorio del jugador */
    s = game_get_inventory_size();
    if(fread(&inventory, s ,1,inputfile)!=1){
        printf("Error leyendo el inventory\n");
        return ERROR;
    }
    player_set_inventory(player, inventory);

    /* Leemos el set del inventory */
    s = game_get_set_size();
    if(fread(&set, s ,1,inputfile)!=1){
        printf("Error leyendo el set del inventory\n");
        return ERROR;
    }
    inventory_set_objects(inventory,set);


    /* Leemos el dado */
    /* Tamaño del dado */
    s = game_get_die_size();
    if(fread(&die, s ,1,inputfile)!=1){
        printf("Error leyendo el dado\n");
        return ERROR;
    }
    game_set_die(game,die);




    /* Leemos el comando */
    /* Tamaño del comando */
    s = game_get_command_size();
    if(fread(&command, s,1,inputfile)!=1){
        printf("Error leyendo el comando\n");
        return ERROR;
    }
    game_set_command(game,command);

	/* Leemos el dialogue */
    /* Tamaño del dialogue */
    s = game_get_dialogue_size();
    if(fread(&dialogue, s,1,inputfile)!=1){
        printf("Error leyendo el comando\n");
        return ERROR;
    }
    game_set_dialogue(game,dialogue);

    fclose(inputfile);
    return game;
}





