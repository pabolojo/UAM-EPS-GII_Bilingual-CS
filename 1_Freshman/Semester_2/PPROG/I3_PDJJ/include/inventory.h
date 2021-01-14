/**
 * @brief It defines the header of inventory
 *
 * @file inventory.h
 * @version 1.0
 * @date 30-03-2019
 * @copyright GNU Public License
 */
#include "types.h"
#include "set.h"
#ifndef INVENTORY_H
#define INVENTORY_H
/**
 * @brief defines the bag structure
 *
 */
typedef struct _Bag Bag;

/**
 * @brief create a bag
 * @return bag, in case of error NULL
 */

Bag* bag_create();

/**
 * @brief destroy bag
 *
 * @param bag
 * @return bag, in case of error NULL
 */

void bag_destroy(Bag *bag);

/**
 * @brief  add an object
 *
 * @param bag
 * @param obj
 * 
 * @return OK, or ERROR
 */
STATUS bag_addObj(Bag* bag, Id obj);
/**
 * @brief  remove an object
 *
 * @param bag
 * @param id
 * 
 * @return OK, or ERROR
 */

STATUS bag_removeObj(Bag* bag, Id id);

/**
 * @brief  checks objects
 *
 * @param bag
 * @param pos
 * 
 * @return TRUE or FALSE
 */

BOOL bag_checkObj(Bag* bag, int pos);

/**
 * @brief  GET THE NUMBER OF ALLOCATED OBJECT
 *
 * @param bag
 * 
 * @return NUMBER OF ALLOCATED OBJECT or -1 in case of error
 */

int bag_numObj(Bag* bag);

/**
 * @brief  set max objects in game
 *
 * @param bag
 * @param max_obj
 * 
 * @return OK, or ERROR
 */


STATUS bag_setMaxObj(Bag* bag, int max_obj);

/**
 * @brief  GET MAX  OBJECT
 *
 * @param bag
 * 
 * @return NUMBER OF MAX OBJECT or -1 in case of error
 */

int bag_getMaxObj(Bag* bag);
/**
 * @brief get objcet bag in game
 *
 * @param bag
 * @param position
 * 
 * @return bah or in case of error NULL
 */

Id bag_getObject(Bag *bag, int position);

/**
 * @brief  set id psoition of bag in game
 *
 * @param bag
 * @param id
 * @param position
 * 
 * @return OK, or ERROR
 */
STATUS bag_setObject(Bag* bag, Id id, int position);

/**
 * @brief  prints the bag in the game
 *
 * @param bag
 * 
 * @return void
 */

void bag_print(Bag* bag);

#endif

