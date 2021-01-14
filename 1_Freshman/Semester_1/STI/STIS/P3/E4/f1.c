#include <stdio.h>
#include <stdlib.h>
#include "fig.h" 


void f1(int x, int y)  {
FILE *f=fopen("fig","w");
for(int i=0;i<y;i++){
for(int j=0;j<x;j++){
fprintf(f,"%d %d\n",j,i); }}}
