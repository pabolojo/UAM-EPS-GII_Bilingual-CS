#ifndef INT_H
#define INT_H
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
void int_destroy(void * src);
void * int_copy(const void * src);
int int_print(FILE * pf, const void *a);
#endif
