#include <stdio.h>
#include <stdlib.h>
#include "fig.h"

void f4(int X, int Y) {
FILE *out = fopen ( "fig", "w" );
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
 fprintf(out, "%d %d\n", b,a);}
}
}
if(X%2==1){
  fprintf(out, "%d %d \n%d %d\n",(X/2),-1, (X/2) +1, -1); }
else { fprintf(out, "%d %d \n%d %d\n %d %d\n", (X/2)-1,-1, (X/2),-1, (X/2) +1, -1); }
fclose(out);
}
