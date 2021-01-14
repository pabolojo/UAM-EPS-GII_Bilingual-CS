#include <stdio.h>

int main(){
    int x,y;
    printf("X: ");
    scanf("%d",&x);
    printf("Y: ");
    scanf("%d",&y);
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
