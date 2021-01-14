#include <stdio.h>
#include <stdlib.h>
#include "fig.h"


void f6(int x, int y) {
for(int i=0;i<y;i++){
if(i==0 || i==y-1){
for(int j=0;j<x;j++){
printf("*");   }
printf("\n");  }
else{
for(int j=0;j<x;j++){
if(j==0 || j==x-2){


 printf("*");

              }
printf(" "); }
printf("\n"); }}}