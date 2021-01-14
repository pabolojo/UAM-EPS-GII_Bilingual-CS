#include <stdio.h>
#include <stdlib.h>
#include "fig.h" 


void f3(int x, int y, int t) {
for(int i=0;i<y;i++){
        if(i<t){
            for(int k=0;k<x;k++){
                printf("*");
            }
            printf("\n");
        }
        else if(i<y-t){
            for(int k=0;k<t;k++){
                printf("*");
            }
            printf("\n");
        }
        else{
            for(int k=0;k<x;k++){
                printf("*");
            }
            printf("\n");
        }
    }}
