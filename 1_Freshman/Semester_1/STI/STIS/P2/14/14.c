#include <stdio.h>
#include <stdlib.h>

int main (){
    int array[4][4];
    int num=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("Number %d,%d: ",i+1,j+1);
            scanf("%d",&array[i][j]);
	    if(array[i][j]==0){
                num++;
            }

        }
    }

    printf("Matrix:\n");

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",array[i][j]);
        }
	printf("\n");
    }
    printf("Number of Zeros: %d\n",num);
    
    return 0;
}
