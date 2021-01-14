#include <stdio.h>
#include <stdlib.h>

int main (){
    double total;
    double num;
    for(int i=0;i<10;i++){
        printf("Number %d: ",i+1);
        scanf("%lf",&num);
        total+=num;
    }
    printf("Total: %.2lf\n",total);
    
    return 0;
}
