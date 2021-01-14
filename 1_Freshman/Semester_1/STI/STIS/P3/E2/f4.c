#include <stdio.h>
#include <stdlib.h>
#include "fig.h"

void f4(int X, int Y) {
  double m;
if(Y%2==1){
Y--;
}
Y--;
X--;
m= (double)Y/((double)X/2);
for(int a=Y; a>=0; a--){
for(int b=0; b<=X; b++){
if((a+(m*b)<= 2*Y)&&(a-(m*b)<=0)){
int x=rand()%3;
if(x==0){ printf("%c", '&'); }
else if(x==1){ printf("%c",'$');  }
else if(x==2){ printf("%c", '%'); } }
else    { printf(" ");   }}
printf("\n"); }
if(X%2==1){
for(int o=0; o<=(X/2)-1; o++){
printf(" "); }
printf("TT\n"); }
else
{ for(int o=0; o<=(X/2)-2; o++){ printf(" "); }
printf("TTT\n"); }
}
