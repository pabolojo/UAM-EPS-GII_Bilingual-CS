#include <stdio.h>
#include <stdlib.h>

int main (){
    int worknum;
    double total=0;
    double salph;
    printf("Salary per hour: ");
    scanf("%lf",&salph);
    printf("Number of workers: ");
    scanf("%d",&worknum);
    for(int i=0;i<worknum;i++){
        int daysaweek=0;
        int hours=0;
        double sal=0;
        printf("Worker %d days a week: ",i+1);
        scanf("%d",&daysaweek);
        for(int j=0;j<daysaweek;j++){
            printf("Worker %d hours of day %d: ",i+1,j+1);
            scanf("%d",&hours);
            sal+=hours*salph;
        }
        printf("Worker %d salary: %.2lf\n",i+1,sal);
        total+=sal;
    }
    printf("Total: %.2lf\n",total);
    
    return 0;
}
