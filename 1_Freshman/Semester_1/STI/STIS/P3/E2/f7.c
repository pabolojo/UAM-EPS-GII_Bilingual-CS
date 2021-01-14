#include <stdio.h>

#include <stdlib.h>
#include "fig.h"
 
#define SIZE (1 << 4)


void f7(int x, int y, int i) {
for (y = SIZE - 1; y >= 0; y--, putchar('\n'))
{
for (i = 0; i < y; i++) putchar(' ');
for (i = 0; i+y  < SIZE; i++)
if((i & y)) printf("  ") ;
else printf("* "); }}
