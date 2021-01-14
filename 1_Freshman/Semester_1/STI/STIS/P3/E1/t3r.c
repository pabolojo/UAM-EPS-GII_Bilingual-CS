#include <stdio.h>

int main(){
    int x,y,t,k=0;
    printf("X: ");
    scanf("%d",&x);
    printf("Y: ");
    scanf("%d",&y);
    printf("T: ");
    scanf("%d",&t);
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
    }
    return 0;
}
