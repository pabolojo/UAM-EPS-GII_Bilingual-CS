/**
 * @brief It defines the header of set
 *
 * @file set.h
 * @version 2.0
 * @date 21-02-2019
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "types.h"

typedef struct _Dialogue Dialogue;
Dialogue* dial_create();
STATUS dial_destroy(Dialogue *aux);
char* dial_get_sentence(void *g,char *cmd);
#endif

