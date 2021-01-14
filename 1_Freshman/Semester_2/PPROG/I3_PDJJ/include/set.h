/**
 * @brief It defines the header of set
 *
 * @file set.h
 * @version 2.0
 * @date 21-02-2019
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H
#include "types.h"
/**
 * @brief defines max number of ids
 *
 */
#define  MAX_IDs_SET 4
/**
 * @brief defines structure of set
 *
 */
typedef struct _Set Set;
/**
 * @brief create the set in the game
 *
 * @return set or in case of error NULL
 */
Set* set_create();
/**
 * @brief destroy the set in the game
 *
 * @param aux 
 * 
 * @return OK, or ERROR
 */
STATUS set_destroy(Set *aux);
/**
 * @brief set the id in the game
 *
 * @param aux
 * @param var
 * 
 * @return TRUE or FALSE
 */
BOOL set_id_in(Set *aux,Id var);
/**
 * @brief  set the id add in the game
 *
 * @param aux
 * @param new
 * 
 * @return OK, or ERROR
 */
STATUS set_id_add(Set *aux,Id new);
/**
 * @brief  remove the id add in the game
 *
 * @param aux
 * @param rmv
 * 
 * @return OK, or ERROR
 */
STATUS set_remov_id(Set *aux,Id rmv);

/**
 * @brief  set the id add in the game
 *
 * @param aux
 * @param pos
 * 
 * @return id or in case of error NULL
 */

Id set_get_id(Set *aux,int pos);

/**
 * @brief  set the id  in the game
 *
 * @param aux
 * @param pos
 * @param id
 * 
 * @return OK, or ERROR
 */

STATUS set_set_id(Set* aux, Id id, int pos);
/**
 * @brief  set get number in the game
 *
 * @param set
 * 
 * @return number of sets
 */

int set_getNum(Set* set);
/**
 * @brief prints the set 
 *
 * @param aux
 * 
 * @return OK, or ERROR
 */

STATUS set_print(Set *aux);

#endif

