/** 
 * @brief It implements the link
 * 
 * @file link.c
 * @author Sergio de los Reyes
 * @version 1.0 
 * @date 14-02-2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/types.h"
#include "../include/link.h"

#define LINK_SPACES 2
/**
* @brief Estructura del link
*/
struct _Link {
    Id id;                /*!< Identificador del link */
    Id spaces[LINK_SPACES];		  /*!< Identificadores de los espacios */
    char name[WORD_SIZE]; /*!< Nombre del enlace */
    DOOR status;          /*!< Estado del enlace */
};


Link* link_create(Id id) {
    Link* link = NULL;

    if (id == NO_ID)
        return NULL;

    link = (Link*) malloc(sizeof (Link));

    if (link == NULL)
        return NULL;

    link->id = id;
	bzero(link->name,WORD_SIZE);

    link->spaces[0] = NO_ID;
    link->spaces[1] = NO_ID;
    link->status = CLOSED;

    return link;
}


STATUS link_destroy(Link* link) {
    if (link == NULL)
        return ERROR;

    free(link);

    return OK;
}


STATUS link_set_name(Link* link, char* name) {
    if (link == NULL || name == NULL)
        return ERROR;

    strcpy(link->name, name);

    return OK;
}


STATUS link_set_link(Link* link, Id space1, Id space2) {
    if (link == NULL || space1 == NO_ID || space2 == NO_ID)
        return ERROR;

    link->spaces[0] = space1;
    link->spaces[1] = space2;

    return OK;
}


STATUS link_set_status(Link* link, DOOR status) {
    if (link == NULL)
        return ERROR;

    link->status = status;

    return OK;
}



Id link_get_id(Link* link) {
    if (link == NULL)
        return NO_ID;

    return link->id;
}


char* link_get_name(Link* link) {
    if (link == NULL)
        return NULL;

    return link->name;
}


DOOR link_get_status(Link* link) {
    if (link == NULL)
        return CLOSED;

    return link->status;
}


Id* link_get_link(Link* link) {

    if (link == NULL)
        return NULL;

    return link->spaces;
}

size_t link_get_size(){
    return sizeof(struct _Link);
}

Id link_space_connected_to(Link* link, Id space) {
    if (link == NULL) {
        return NO_ID;
    }

    if (link->spaces[0] == space) {
        return link->spaces[1];
    } else if (link->spaces[1] == space) {
        return link->spaces[0];
    }

    return NO_ID;

}

STATUS link_print(Link* link) {
    if (link == NULL)
        return ERROR;

    fprintf(stdout, "Link id: %li\n", link->id);

    fprintf(stdout, "Link name: %s\n", link->name);

    if (link->status == OPENNED)
        fprintf(stdout, "Link status: open\n");
    else if (link->status == CLOSED)
        fprintf(stdout, "Link status: closed\n");
    else
        fprintf(stdout, "Link status: unknown\n");

    fprintf(stdout, "Linked spaces: space %li and space %li\n", link->spaces[0],
            link->spaces[1]);

    return OK;
}
