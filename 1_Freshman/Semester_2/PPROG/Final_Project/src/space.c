/** 
 * @brief It implements the space
 * 
 * @file space.c
 * @author Julia Simon
 * @version 1.2 
 * @date 29/04/2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/space.h"

#define COL 9
#define ROW 3
/**
* @brief Estructura del espacio
*/
struct _Space {
	Id id;                           /*!< Identificador del espacio */
	char name[WORD_SIZE];            /*!< Nombre del espacio */
	Id north;                        /*!< Identificador del link al norte */
	Id south;                        /*!< Identificador del link al sur */
	Id east;                         /*!< Identificador del link al este */
	Id west;                         /*!< Identificador del link al oeste */
	Id up;                           /*!< Identificador del link arriba */
	Id down;                         /*!< Identificador del link abajo */
	Set* objects;                    /*!< Conjunto de espacios que hay en el espacio*/
	char gdesc[ROW][COL];            /*!< Descripción gráfica (ASCII) del espacio */
	char description[WORD_SIZE];     /*!< Descripcion del espacio */
	char desc_det[WORD_SIZE];        /*!< Descripcion detallada del espacio */
	BOOL iluminado;                  /*!< Indicador de si el espacio se encuentra iluminado o no */
};


Space* space_create(Id id) {
		
	int i=0, j=0;
	Space *newSpace = NULL;
	Set *objects = NULL;

	if (id == NO_ID)
		return NULL;

	newSpace = (Space *) malloc(sizeof (Space));

	if (newSpace == NULL) {
		return NULL;
	}
	newSpace->id = id;

	bzero(newSpace->name,WORD_SIZE);
	bzero(newSpace->description,WORD_SIZE);
	bzero(newSpace->desc_det,WORD_SIZE);

	newSpace->north = NO_ID;
	newSpace->south = NO_ID;
	newSpace->east = NO_ID;
	newSpace->west = NO_ID;
	newSpace->up = NO_ID;
	newSpace->down = NO_ID;
	newSpace->iluminado = FALSE;

	for(i=0; i<3; i++){
		for(j=0; j<7; j++){
			newSpace->gdesc[i][j] = ' ';
		}
		newSpace->gdesc[i][8]='\0';
	}
	
	objects = set_create();
	if(objects!=NULL)
		newSpace->objects = objects;

	return newSpace;
}


STATUS space_destroy(Space* space) {
	
	if (!space) {
		return ERROR;
	}
	set_destroy(space->objects);
	free(space);
	space = NULL;

	return OK;
}


STATUS space_set_name(Space* space, char* name) {
	if (!space || !name) {
		return ERROR;
	}

	if (!strcpy(space->name, name)) {
		return ERROR;
	}
	return OK;
}

/*En la descripcion basica solo aparece el nombre del espacio */
STATUS space_set_description(Space* space, char* string){

	if(!space){
		return ERROR;
	}
	
	strcpy(space->description, string);
	
	return OK;

}

/*En la descripcion detallada aparecen los objetos del espacio, y los links */
STATUS space_set_description_detallada(Space* space, char* string){
	
	if(!space){
		return ERROR;
	}
	
	strcpy(space->desc_det, string);
	
	return OK;

}


STATUS space_set_north(Space* space, Link* link) {
	
	if (!space) {
		return ERROR;
	}
	
	space->north = link_get_id(link);
	return OK;
}


STATUS space_set_south(Space* space,Link* link) {
	if (!space ) {
		return ERROR;
	}
	space->south = link_get_id(link);
	return OK;
}


STATUS space_set_east(Space* space, Link* link) {
	if (!space)
		return ERROR;
	space->east = link_get_id(link);
	return OK;
}


STATUS space_set_west(Space* space, Link* link) {
	if (!space ) {
		return ERROR;
	}
	space->west = link_get_id(link);
	return OK;
}

STATUS space_set_up(Space* space, Link* link) {
	if (!space) {
		return ERROR;
	}
	space->up = link_get_id(link);
	return OK;
}

STATUS space_set_down(Space* space, Link* link) {
	if (!space) {
		return ERROR;
	}
	space->down = link_get_id(link);
	return OK;
}


STATUS space_set_gdesc(Space* space, char* string, int i){
	if(!space)
		return ERROR;
		
	strcpy(space->gdesc[i], string);
		
	return OK;
}
/***************************************************************/
/***************************************************************/
/***************************************************************/
STATUS space_set_objects(Space* space, Set* objetos){
	if(!space)
		return ERROR;

	space->objects = objetos;
	return OK;
}

STATUS space_set_iluminado(Space* space, BOOL iluminado){
	if(!space)
		return ERROR;
		
	space->iluminado = iluminado;
		
	return OK;
}

char * space_get_name(Space* space) {
	if (!space) {
		return NULL;
	}
	return space->name;
}

char* space_get_description(Space* space){

	if(!space){
		return NULL;
	}
	return space->description;

}

char* space_get_description_detallada(Space* space){

	if(!space){
		return NULL;
	}

	if(space_get_iluminado(space)){
		return space->desc_det;
	}
	return NULL;

}

Id space_get_id(Space* space) {
	if (!space) {
		return NO_ID;
	}
	return space->id;
}

Id space_get_north(Space* space) {
	if (!space) {
		return NO_ID;
	}

	return space->north;
}


Id space_get_south(Space* space) {
	if (!space) {
		return NO_ID;
	}
	return space->south;
}

Id space_get_east(Space* space) {
	if (!space) {
		return NO_ID;
	}
	return space->east;
}

Id space_get_west(Space* space) {
	if (!space) {
		return NO_ID;
	}
	return space->west;
}

Id space_get_up(Space* space) {
	if (!space) {
		return NO_ID;
	}
	return space->up;
}

Id space_get_down(Space* space) {
	if (!space) {
		return NO_ID;
	}
	return space->down;
}

Set* space_get_objects(Space* space) {
	if (!space) {
		return NULL;
	}
	return space->objects;
}

char* space_get_gdesc(Space* space,int position){
	if(!space)
		return ERROR;
	return space->gdesc[position];
}

BOOL space_get_iluminado(Space* space){
	if(!space)
		return FALSE;

	return space->iluminado;
}

size_t space_get_size(){
	return sizeof(struct _Space);
}

STATUS space_add_objects(Space* space, Id id) {
	if (!space) {
		return ERROR;
	}
	set_add(space->objects, id);
	
	return OK;
}

STATUS space_del_objects(Space* space, Id id) {
	if (!space) {
		return ERROR;
	}
	if(set_del(space_get_objects(space), id)==ERROR)
		return ERROR;
	
	return OK;
}

BOOL space_object_in(Space* space, Id id){
	int i; 
	if(!space || id == NO_ID)
		return FALSE;
		
	
	
	for(i=0; i<set_get_nId(space->objects); i++){
		if(set_get_Id(space->objects, i) == id)
			return TRUE;
	}
	
	return FALSE;
}


STATUS space_print(Space* space) {
	Id idaux = NO_ID;
	int i;

	if (!space) {
		return ERROR;
	}

	fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

	if(space->iluminado)
		fprintf(stdout, "--> Space esta iluminado\n");
	else
		fprintf(stdout, "--> Space no iluminado\n");


	fprintf(stdout, "--> ASCII description: \n");
	for(i=0; i<3; i++){
		fprintf(stdout,"%s\n", space->gdesc[i]);
	}

	idaux = space_get_north(space);
	if (NO_ID != idaux) {
		fprintf(stdout, "---> North link: %ld.\n", idaux);
	} else {
		fprintf(stdout, "---> No north link.\n");
	}

	idaux = space_get_south(space);
	if (NO_ID != idaux) {
		fprintf(stdout, "---> South link: %ld.\n", idaux);
	} else {
		fprintf(stdout, "---> No south link.\n");
	}

	idaux = space_get_east(space);
	if (NO_ID != idaux) {
		fprintf(stdout, "---> East link: %ld.\n", idaux);
	} else {
		fprintf(stdout, "---> No east link.\n");
	}

	idaux = space_get_west(space);
	if (NO_ID != idaux) {
		fprintf(stdout, "---> West link: %ld.\n", idaux);
	} else {
		fprintf(stdout, "---> No west link.\n");
	}

	if(set_get_nId(space->objects) > 0){
		fprintf(stdout, "The space have the following objects: ");
		set_print(space->objects);
	} else {
		fprintf(stdout, "No objects in the space");
	}

	return OK;
}
