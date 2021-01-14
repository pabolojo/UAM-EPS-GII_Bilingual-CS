/**
 * @brief It defines the header of die
 *
 * @file die.c
 * @version 1.0
 * @date 28-02-2019
 * @copyright GNU Public License
 */
#ifndef DIE_H
#define DIE_H

#include "types.h"
#define num_die 6

/*Structure of an die*/
typedef struct _Die Die;

/*Functions*/
Die* die_create(Id id);
void die_destroy(Die *die);
int die_roll(Die *die);
int die_get_value(Die *die);
#endif

