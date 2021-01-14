/**
 * @brief It defines the header of die
 *
 * @file die.h
 * @version 1.0
 * @date 28-02-2019
 * @copyright GNU Public License
 */
#ifndef DIE_H
#define DIE_H

#include "types.h"
/**
 * @brief defines the number of dies
 *
 */
#define num_die 6

/**
 * @brief defines the die structure
 *
 */
typedef struct _Die Die;

/**
 * @brief  create a Die
 *
 * @param id
 * 
 * @return die n or in case of error it returns ERROR
 */
Die* die_create(Id id);
/**
 * @brief  destroy a Die
 *
 * @param die
 * 
 * @return void
 */
void die_destroy(Die *die);
/**
 * @brief  roll a Die
 *
 * @param die
 * 
 * @return int die number,in case of error -1 
 */
int die_roll(Die *die);
/**
 * @brief  get value of die
 *
 * @param die
 * 
 * @return int die number,in case of error -1 
 */
int die_get_value(Die *die);
#endif

