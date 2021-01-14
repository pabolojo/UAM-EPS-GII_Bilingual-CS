#include <stdio.h>
#include <stdlib.h> 
#include "fig.h"


void f5(int r) {
int x,y,N;
N = 2*r+1;
for (int i = 0; i < N; i++)
{ for (int j = 0; j < N; j++) {
x = i-r;
y = j-r;
if (x*x + y*y <= r*r+1 ){
printf("*");
 } else{
printf(" "); }
printf(" "); }
printf("\n"); }}
