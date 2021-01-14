/**
 * @brief It defines the header of link
 *
 * @file link.h
 * @version 2.0
 * @date 27-03-2019
 * @copyright GNU Public License
 */
#ifndef LINK_H
#define LINK_H

#include "types.h"
/**
 * @brief defines the link structure
 *
 */
typedef struct _Link Link;
/**
 * @brief defines max number of links
 *
 */
#define MAX_LINKS 100
/**
 * @brief defines first link
 *
 */
#define FIRST_LINK 1

/**
 * @brief create the link in the game
 *
 * @param id
 * 
 * @return link or in case of error NULL
 */
Link* link_create(Id id);
/**
 * @brief destroy the link in the game
 *
 * @param link
 * 
 * @return OK, or ERROR
 */
STATUS link_destroy(Link* link);
/**
 * @brief get a specific link 
 *
 * @param link
 * 
 * @return link or in case of error NULL
 */
Id link_get_id(Link* link);
/**
 * @brief set a name to the link
 *
 * @param link
 * @param name
 * 
 * @return OK, or ERROR
 */
STATUS link_set_name(Link* link, char* name);
/**
 * @brief get the name of the link
 *
 * @param link
 * 
 * @return name or in case of Error NULL
 */
const char* link_get_name(Link* link);
/**
 * @brief set the space of the link
 *
 * @param link
 * @param id
 * 
 * @return OK, or ERROR
 */
STATUS link_set_space1(Link* link, Id id);
/**
 * @brief get the id space of the link 
 *
 * @param link
 * 
 * @return id or in case of error NULL
 */
Id link_get_space1(Link* link);
/**
 * @brief set the space2 of the link
 *
 * @param link
 * @param id
 * 
 * @return OK, or ERROR
 */
STATUS link_set_space2(Link* link, Id id);
/**
 * @brief get the id space2 of the link 
 *
 * @param link
 * 
 * @return id or in case of error NULL
 */
Id link_get_space2(Link* link);
/**
 * @brief set the status of the link(open or close)
 *
 * @param link
 * @param st
 * 
 * @return OK, or ERROR
 */
STATUS link_set_status(Link* link, Id st);
/**
 * @brief get the status of the link(open or close)
 *
 * @param link
 * 
 * @return id or in case of error NULL
 */
Id link_get_status(Link* link);
/**
 * @brief prints the link 
 *
 * @param link
 * 
 * @return OK, or ERROR
 */
STATUS link_print(Link* link);

#endif

