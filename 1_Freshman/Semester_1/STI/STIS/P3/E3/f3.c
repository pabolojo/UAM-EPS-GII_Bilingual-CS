#include <stdio.h>
#include <stdlib.h>
#include "fig.h" 


void f3(int x, int y, int t) {
FILE *f=fopen("fig","w");
for(int i=0;i<y;i++){
        if(i<t){
            for(int k=0;k<x;k++){
                fprintf(f,"%d %d\n",k,i);
            }
        }
        else if(i<y-t){
            for(int k=0;k<t;k++){
                fprintf(f,"%d %d\n",k,i);
            }
        }
        else{
            for(int k=0;k<x;k++){
                fprintf(f,"%d %d\n",k,i);
            }
        }
    }}
