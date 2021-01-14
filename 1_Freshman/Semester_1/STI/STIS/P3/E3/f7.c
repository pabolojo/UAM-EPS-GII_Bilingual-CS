#include <stdio.h>

#include <stdlib.h>
#include "fig.h"
 
#define SIZE (1 << 4)


void f7(int x, int y, int i) {
FILE *f=fopen("fig","w");
for (y = SIZE - 1; y >= 0; y--)
{
for (i = 0; i < y; i++);
for (i = 0; i+y  < SIZE; i++)
if((i & y));
else fprintf(f,"%d %d\n",i,y);}}
