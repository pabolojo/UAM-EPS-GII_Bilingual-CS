#include <stdio.h>


#include "fig.h"
#include <stdlib.h>

void f2(int x, int y) {
    double xh;
    for(int i=0;i<y;i++){
        xh=(i*(x-1))/(y-1);
        for(int j=0;j<=xh;j++){
            printf("*");
        }
        printf("\n");
    }}
