#include <stdio.h>

int main(){
    int x,y;
    double xh;
    printf("X: ");
    scanf("%d",&x);
    printf("Y: ");
    scanf("%d",&y);
    if(x<=1 || y<=1){
        return 1;
    }
    for(int i=0;i<y;i++){
        xh=(i*(x-1))/(y-1);
        for(int j=0;j<=xh;j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
