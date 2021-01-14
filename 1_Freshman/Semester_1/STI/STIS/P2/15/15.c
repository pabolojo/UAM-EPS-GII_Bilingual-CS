#include <stdio.h>
#include <stdlib.h>

int main (){
    int m,n;
    printf("M order of matrices: ");
    scanf("%d",&m);
    printf("N order of matrices: ");
    scanf("%d",&n);
    int matrix1[m][n],matrix2[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("Number %d,%d of matrix 1: ",i+1,j+1);
            scanf("%d",&matrix1[i][j]);
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("Number %d,%d of matrix 2: ",i+1,j+1);
            scanf("%d",&matrix2[i][j]);
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            matrix1[i][j]=matrix1[i][j]+matrix2[i][j];
        }
    }
    printf("Sum: \n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",matrix1[i][j]);
        }
        printf("\n");
    }
    return 0;
}
