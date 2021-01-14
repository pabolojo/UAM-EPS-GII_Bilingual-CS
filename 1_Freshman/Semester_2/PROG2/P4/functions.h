#ifndef FUCNTIONS_H_
#define FUNCTIONS_H_
#include <stdio.h>
#include "types.h"

void destroy_string_function(void* e);

void * copy_string_function(const void* e);

int print_string_function(FILE * f, const void* e);

int cmp_string_function(const void* e1, const void* e2);

#endif /* FUNCTIONS_H_ */
