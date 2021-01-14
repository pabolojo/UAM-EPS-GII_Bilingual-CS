#include <stdio.h>
#include <stdlib.h>
#include "fig.h"


void f6(int x, int y) {
FILE *out = fopen ( "fig", "w" );
for(int i=0;i<y;i++){
if(i==0 || i==y-1){
for(int j=0;j<x;j++){
  fprintf(out,"%d %d\n",j,i);   }
  }
else{
  fprintf(out, "%d %d\n %d %d\n",0,i,x-1,i);
             
 }}}
