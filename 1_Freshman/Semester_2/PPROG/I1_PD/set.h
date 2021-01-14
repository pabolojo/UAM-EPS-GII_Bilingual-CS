/**
 * @brief It defines the header of set
 *
 * @file set.c
 * @version 1.0
 * @date 21-02-2019
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H
#include "types.h"
#define  MAX_IDs_SET 4

typedef struct _Set Set;

Set* set_create();
STATUS set_destroy(Set *aux);
BOOL set_id_in(Set *aux,Id var);
STATUS set_id_add(Set *aux,Id new);
STATUS set_remov_id(Set *aux,Id rmv);
Id set_get_id(Set *aux,int pos);
STATUS set_print(Set *aux);

#endif

