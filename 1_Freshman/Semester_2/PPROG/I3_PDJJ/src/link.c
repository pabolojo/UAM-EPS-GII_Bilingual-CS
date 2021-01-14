/**
 * @brief It implements module of link, that joints the different spaces
 *
 * @file command.c
 * @version 1.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "link.h"
/**
 * @brief defines structure of link
 */
struct _Link {
/**
 * @brief defines id
 */
  Id id;
/**
 * @brief defines string name
 */
  char name[WORD_SIZE + 1];
/**
 * @brief defines space1
 */
  Id space1;
/**
 * @brief defines space2
 */
  Id space2;
/**
 * @brief defines sstatus
 */
  Id status;
};

/*Function to create an link, in case of error it returns ERROR*/
Link* link_create(Id id) {

  Link *newLink = NULL;

  if (id == NO_ID)
    return NULL;

  newLink = (Link *) malloc(sizeof (Link));

  if (newLink == NULL) {
    return NULL;
  }
  newLink->id = id;
 /*in case of allocation memory it set the characteristics of link name,location,id ,space1...*/
  newLink->name[0] = '\0';

  newLink->space1 = NO_ID;
  newLink->space2 = NO_ID;
  newLink->status = NO_ID;
  return newLink;
}

/*Function to destroy link, in case of error it returns ERROR*/
STATUS link_destroy(Link* link) {
  if (!link) {
    return ERROR;
  }

  free(link);
  link = NULL;

  return OK;
}

/*Function to set the name of scpace, in case of error it returns ERROR*/
STATUS link_set_name(Link* link, char* name) {
  if (!link || !name) {
    return ERROR;
  }

  if (!strcpy(link->name, name)) {
    return ERROR;
  }

  return OK;
}

/*Function to set the space1 of link, in case of error it returns ERROR*/
STATUS link_set_space1(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->space1 = id;
  return OK;
}

/*Function to set the space2 of link, in case of error it returns ERROR*/
STATUS link_set_space2(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->space2 = id;
  return OK;
}

/*Function to set object of link, in case of error it returns ERROR*/
STATUS link_set_status(Link* link, Id st) {
  if (!link) {
    return ERROR;
  }
  link->status=st;
  return OK;
}
/*Function to get the name of link, in case of error it returns NULL*/
const char * link_get_name(Link* link) {
  if (!link) {
    return NULL;
  }
  return link->name;
}
/*Function to get the
ID of link, in case of error it returns NO ID*/
Id link_get_id(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->id;
}
/*Function to get the
space1 of link, in case of error it returns NO ID*/
Id link_get_space1(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->space1;
}
/*Function to get the
space2 of link, in case of error it returns NO ID*/
Id link_get_space2(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->space2;
}
/*Function to get the
object of link, in case of error it returns NO ID*/
Id link_get_status(Link* link) {
  if (!link) {
    return 0;
  }
  return link->status;
}

/*Function to  print link, in case of error it returns ERROR*/
STATUS link_print(Link* link) {
  Id idaux = NO_ID;

  if (!link) {
    return ERROR;
  }

  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);
/*space1*/
  idaux = link_get_space1(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> space1 link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No space1 link.\n");
  }
/*space2*/
  idaux = link_get_space2(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> space2 link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No space2 link.\n");
  }

  if (link_get_status(link)!=NO_ID) {
    fprintf(stdout, "---> Link is open\n");
  } else {
    fprintf(stdout, "---> Link is close\n");
  }

  return OK;
}

