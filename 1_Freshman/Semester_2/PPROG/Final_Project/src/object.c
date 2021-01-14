/** 
 * @brief It implements the object
 * 
 * @file object.c
 * @author Julia Simon y Miguel Rodriguez
 * @version 1.2 
 * @date 15/02/2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/types.h"
#include "../include/object.h"

/**
* @brief Estructura del objeto
*/
struct _Object {
	Id id;                           /*!< identificador del objeto.          */
	Id pos_original;                 /*!< identificador del espacio original */
	char name[WORD_SIZE];            /*!< nombre del objeto                  */
	char description[WORD_SIZE];     /*!< Descripcion del objeto pos inicial */
	char des_movido[WORD_SIZE];      /*!< Descripcion del objeto movido.     */
	BOOL movible;					 /*!< Objecto movible o no               */
	BOOL movido;                     /*!< Objeto ha sido movido.             */
	BOOL oculto;                     /*!< Objecto oculto o no                */
	Id open;                         /*!< Id del link que abre               */
	BOOL iluminado;                  /*!< Objecto puede iluminar o no        */
	BOOL encendido;                  /*!< Objecto encendido o no             */
};

Object* object_create(Id id) {

	Object *newObject = NULL;

	if (id == NO_ID)
		return NULL;

	newObject = (Object *) malloc(sizeof (Object));

	if (newObject == NULL) {
		return NULL;
	}
	newObject->id = id;

	bzero(newObject->name,WORD_SIZE);
	bzero(newObject->description,WORD_SIZE);
	bzero(newObject->des_movido,WORD_SIZE);
	newObject->pos_original = NO_ID;
	newObject->movido = FALSE;
	newObject->movible = TRUE;
	newObject->oculto = FALSE;
	newObject->iluminado = FALSE;
	newObject->encendido = FALSE;
	newObject->open = NO_ID;
	
	
	return newObject;
}


STATUS object_destroy(Object* object) {
	if (!object) {
		return ERROR;
	}

	free(object);
	object = NULL;

	return OK;
}


STATUS object_set_name(Object* object, char* name) {
	if (!object || !name) {
		return ERROR;
	}

	if (!strcpy(object->name, name)) {
		return ERROR;
	}

	return OK;
}

STATUS object_set_description(Object* object, char* string) {
	
	char str[WORD_SIZE + 1] = "";

	if (!object) {
		return ERROR;
	}
	sprintf(str,"%s   ", object_get_name(object));
	strcpy(object->description, str);

	strcat(object->description, string);

	
	return OK;
}

STATUS object_set_des_movido(Object* object){

	char str[WORD_SIZE + 1] = "";

	if (!object) {
		return ERROR;
	}

	strcpy(object->des_movido,object->description);

	sprintf(str,"--- Este objeto ha sido movido de su posicion inicial que era: %2d ", (int)object_get_pos_inicial(object));
	strcat(object->des_movido, str);

	return OK;
} 

STATUS object_set_pos_inicial(Object* object, Id space){
	if (!object) {
		return ERROR;
	}
	object->pos_original = space;
	return OK;
}

char * object_get_name(Object* object) {
	if (!object) {
		return NULL;
	}
	return object->name;
}


Id object_get_id(Object* object) {
	if (!object) {
		return NO_ID;
	}
	return object->id;
}


char* object_get_description(Object* object) {
	if (!object) {
		return NULL;
	}
	if(object->movido){
		return object->des_movido;
	} else{
		return object->description;
	}
	
}

Id object_get_pos_inicial(Object* object){
	if (!object) {
		return NO_ID;
	}
	return object->pos_original;
}

STATUS object_print(Object* object) {

	if (!object) {
		return ERROR;
	}

	fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

	return OK;
}


BOOL object_get_movible(Object* object){

	if (!object) {
        return FALSE;
    }
    return object->movible;

}

STATUS object_set_movible(Object* object, BOOL movible){

    if (!object) {
        return ERROR;
    }

    object->movible = movible;

    return OK;

}

BOOL object_get_movido(Object* object){

	if (!object) {
        return FALSE;
    }
    return object->movido;

}

STATUS object_set_movido(Object* object, BOOL movido){

    if (!object) {
        return ERROR;
    }

	/* Actualizamos la descripcion del objeto */
	object_set_des_movido(object);

    object->movido = movido;

    return OK;

}

BOOL object_get_oculto(Object* object){

	if (!object) {
        return FALSE;
    }
    return object->oculto;

}

STATUS object_set_oculto(Object* object, BOOL oculto){

    if (!object) {
        return ERROR;
    }

    object->oculto = oculto;

    return OK;

}

Id object_get_open(Object* object){

    if (!object) {
        return NO_ID;
    }
    return object->open;

}

STATUS object_set_open(Object* object, Id open){

    if (!object) {
        return ERROR;
    }

    object->open = open;

    return OK;

}

BOOL object_get_iluminado(Object* object){

	if (!object) {
        return FALSE;
    }
    return object->iluminado;

}

STATUS object_set_iluminado(Object* object, BOOL iluminado){

    if (!object) {
        return ERROR;
    }

    object->iluminado = iluminado;

    return OK;

}

BOOL object_get_encendido(Object* object){

	if (!object) {
        return FALSE;
    }
    return object->encendido;

}

STATUS object_set_encendido(Object* object, BOOL encendido){

    if (!object) {
        return ERROR;
    }

    object->encendido = encendido;

    return OK;

}

size_t object_get_size(){
	return sizeof(struct _Object);
}




