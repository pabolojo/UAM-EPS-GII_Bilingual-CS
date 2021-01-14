#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/screen.h"
#include "../include/graphic_engine.h"

/**
* @brief Estructura opaca de graphic engine
*/
struct _Graphic_engine{
	Area *map, *descript, *banner, *help, *feedback; /*!< Diferentes areas de graphic engine*/
};


Graphic_engine *graphic_engine_create(){
	static Graphic_engine *ge = NULL;

	if (ge)
		return ge;
	
	screen_init();
	ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));
	
	ge->map      = screen_area_init( 1, 1, 48, 15);
	ge->descript = screen_area_init(50, 1, 29, 15);
	ge->banner   = screen_area_init(28,17, 23,  1);
	ge->help     = screen_area_init( 1,18, 78,  3);
	ge->feedback = screen_area_init( 1,24, 78,  2);

	return ge;
}

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


void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
	Id id_act = NO_ID,id_object=NO_ID;
	Id id_link_east=NO_ID, id_link_west=NO_ID, id_link_north=NO_ID,id_link_south=NO_ID,id_link_up=NO_ID,id_link_down=NO_ID;
	Id id_south =NO_ID,id_north =NO_ID,id_down =NO_ID,id_up =NO_ID,id_east=NO_ID, id_west =NO_ID;
	Object* obj=NULL;
	BOOL space_iluminado = TRUE;
	Link* link=NULL;
	int comprobante =0;
	Space* space_act = NULL;
	char str[WORD_SIZE]="";
	char str3[WORD_SIZE]="";
	char input_aux2[WORD_SIZE] = "";
	char* str_salida = "";
	T_Command last_cmd = UNKNOWN;
	STATUS cmd_status=ERROR;
	int i=0;


	/* Paint the in the map area */
	screen_area_clear(ge->map);
	id_act = game_get_player_location(game);

	/* Para que se vean los links tiene que estar iluminado */
	if (id_act != NO_ID){

		space_act = game_get_space(game, id_act);
		space_iluminado = space_get_iluminado(space_act);
		
		/* Obtenemos todos los links que tenemos */
		id_link_south = space_get_south(space_act);
		link = game_get_link(game,id_link_south);
		id_south = link_space_connected_to(link,id_act);

		id_link_north = space_get_north(space_act);
		link = game_get_link(game,id_link_north);
		id_north = link_space_connected_to(link,id_act);

		id_link_east = space_get_east(space_act);
		link = game_get_link(game,id_link_east);
		id_east = link_space_connected_to(link,id_act);

		id_link_west = space_get_west(space_act);
		link = game_get_link(game,id_link_west);
		id_west = link_space_connected_to(link,id_act);

		id_link_up = space_get_up(space_act);
		link = game_get_link(game,id_link_up);
		id_up = link_space_connected_to(link,id_act);

		id_link_down = space_get_down(space_act);
		link = game_get_link(game,id_link_down);
		id_down = link_space_connected_to(link,id_act);

		sprintf(str, "                     ");
		screen_area_puts(ge->map, str);

		/* Pintamos el norte */
		if(id_north!=NO_ID && space_iluminado){
			sprintf(str, "             %2d       ", (int)id_north);
			screen_area_puts(ge->map, str);
			sprintf(str, "              ^       ");
			screen_area_puts(ge->map, str);	
			sprintf(str, "              |%2d     ", (int)id_link_north);
			screen_area_puts(ge->map, str);
			
		} else {
			sprintf(str, "                      ");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      ");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      ");
			screen_area_puts(ge->map, str);
		}

		/* Pintamos el este */
		if(id_east!=NO_ID && space_iluminado){
			sprintf(str, "        +------------+  %2d", (int)id_link_east);
			screen_area_puts(ge->map, str);
			sprintf(str, "        | P1      %2d |--->%2d",(int) id_act, (int)id_east) ;
			screen_area_puts(ge->map, str);
		} else{
			sprintf(str, "        +------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "        | P1      %2d |",(int) id_act);
			screen_area_puts(ge->map, str);
		}

		/* Pintamos el oeste */
		if(id_west!=NO_ID && space_iluminado){
			sprintf(str, "      %2d|  %s  |",(int)id_link_west, space_get_gdesc(space_act,0));
			screen_area_puts(ge->map, str);

			sprintf(str, "  %2d<---|  %s  |",(int)id_west,space_get_gdesc(space_act,1)) ;
			screen_area_puts(ge->map, str);	
		}else{

			sprintf(str, "        |  %s  |", space_get_gdesc(space_act,0));
			screen_area_puts(ge->map, str);

			sprintf(str, "        |  %s  |",space_get_gdesc(space_act,1));
			screen_area_puts(ge->map, str);
		}
			
		sprintf(str, "        |  %s  |",space_get_gdesc(space_act,2)) ;
		screen_area_puts(ge->map, str);
		sprintf(str, "        |            |");
		screen_area_puts(ge->map, str);
		sprintf(str, "        +------------+");
		screen_area_puts(ge->map, str);

		/* Pintamos el sur */
		if(id_south!=NO_ID && space_iluminado){
			sprintf(str, "              | %2d    ",(int)id_link_south);
			screen_area_puts(ge->map, str);
			sprintf(str, "             %2d     ", (int)id_south);
			screen_area_puts(ge->map, str);	
		} else {
			sprintf(str, "               ");
			screen_area_puts(ge->map, str);
			sprintf(str, "               ");
			screen_area_puts(ge->map, str);
		}
			

		/* Pintamos arriba y abajo */
		if(id_down!=NO_ID && space_iluminado){
			sprintf(str, "Conexion abajo con el espacio: %2d, por el link: %2d",(int)id_down, (int)id_link_down);
			screen_area_puts(ge->map, str);
		}
		if(id_up!=NO_ID && space_iluminado){
			sprintf(str, "Conexion arriba con el espacio: %2d, por el link: %2d",(int)id_up,(int)id_link_up);
			screen_area_puts(ge->map, str);
		}

	}

	/* Paint the in the description area */
	screen_area_clear(ge->descript);

	/* Imprimir el jugador y sus objetos */
	sprintf(str, " Player objects: ");
	screen_area_puts(ge->descript, str);

	for(i = 0; i<set_get_nId(player_get_objects(game_get_player(game)));i++){
		comprobante = 1;
		id_object = set_get_Id(player_get_objects(game_get_player(game)), i);
		obj = game_get_object(game,id_object);
		sprintf(str, " %s ", object_get_name(obj));
		strcat(str3,str);
	}
	if(comprobante==1)
		screen_area_puts(ge->descript, str3);


	/*Imprimimos la descripcion del objeto*/

	last_cmd = game_get_last_command(game);
	cmd_status = game_get_last_command_status(game);

	if(last_cmd==CHECK && cmd_status==OK){
		if(strcmp(game_get_grasp_object(game), "space")==0 || strcmp(game_get_grasp_object(game), "s")==0){
			if(game_get_space_description_check(game,space_get_id(space_act))!=NULL){
				sprintf(str, " Space description: ");
				screen_area_puts(ge->descript, str);
				sprintf(str, " %s", game_get_space_description_check(game,space_get_id(space_act)));
				screen_area_puts(ge->descript, str);	
			}
			
		} else{
			/* Imprimimos la descripcion del espacio en el juego (descripcion basica) */
			sprintf(str, " Space description: ");
			screen_area_puts(ge->descript, str);
			sprintf(str, " %s", game_get_space_description(game,space_get_id(space_act)));
			screen_area_puts(ge->descript, str);


			sprintf(str, " Object description: ");
			screen_area_puts(ge->descript, str);

			strcpy(input_aux2, object_get_description(game_get_object_by_name(game,game_get_grasp_object(game))));
			if(input_aux2[strlen(input_aux2) - 1] == '\n'){
    			input_aux2[strlen(input_aux2) - 1] = '\0';
			}
			sprintf(str, "%s", input_aux2);
			screen_area_puts(ge->descript, str);
		}
	} else if (space_iluminado) {
		/* Imprimimos la descripcion del espacio en el juego (descripcion basica) */
		sprintf(str, " Space description: ");
		screen_area_puts(ge->descript, str);
		sprintf(str, " %s", game_get_space_description(game,space_get_id(space_act)));
		screen_area_puts(ge->descript, str);
		/* Faltaría imprimir los objetos que hay en el espacio. */
	} else{
		sprintf(str, " Space description: ");
		screen_area_puts(ge->descript, str);
		sprintf(str, " Se encuentra en una habitacion oscura, iluminela para ver lo que hay y a donde ir ");
		screen_area_puts(ge->descript, str);
	}
			


	/* Paint the in the banner area */
	screen_area_puts(ge->banner, " Find the way out ");



	/* Paint the in the help area */
	screen_area_clear(ge->help);
	sprintf(str, " The commands you can use are:");
	screen_area_puts(ge->help, str);
	sprintf(str, " following or f, previous or p, grasp or g, drop or d, left or l, right or r, up or u, down or dw,  die or x,check or c, move or m, turnon or on, turnoff or off, open or o, code or cd, atack or a, examine or ex, save or s, load or lo, or exit or e");
	screen_area_puts(ge->help, str);


	str_salida = game_get_dialogue_text(game);
	screen_area_puts(ge->feedback, str_salida);
	
	/* Dump to the terminal */
	screen_paint();
	printf("prompt:> ");
}
	

	

	


	
	

	

	
	

