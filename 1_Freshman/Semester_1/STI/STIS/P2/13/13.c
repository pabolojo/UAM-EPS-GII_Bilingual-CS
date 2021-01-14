#include <stdio.h>
#include <stdlib.h>

int main (){
    double vector[6];
    for(int i=0;i<6;i++){
        printf("Number %d: ",i+1);
        scanf("%lf",&vector[-1*(i-5)]);
    }
    printf("Vector: %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf\n",vector[0],vector[1],vector[2],vector[3],vector[4],vector[5]);
    
    return 0;
}
