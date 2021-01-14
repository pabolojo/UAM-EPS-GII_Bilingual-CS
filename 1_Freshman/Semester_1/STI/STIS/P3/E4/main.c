#include <stdio.h>
#include <stdlib.h>
#include "fig.h"
int main() {
int choice,T,X,Y,i;
printf("What do you want to draw? ");
printf("Select one of these options: \n 1: Rectangle \n 2: Right triangle \n 3: Letter C \n 4: Christmas tree \n 5: Circle \n 6: Perimeter of an empty rectangle \n 7: Sierpinski Fractal \n\n");
scanf("%d", &choice);
switch(choice) {
case 1:
do{
    printf("X: ");
    scanf("%d", &X);
    printf("Y: ");
    scanf("%d", &Y);
if(X<=0 || Y<=0) {
	printf("The X and Y must be bigger than 0\n"); }
} while(X<=0 || Y<=0);

f1(X, Y);
break;

case 2:
    do{
    printf("X: ");
    scanf("%d", &X);
    printf("Y: ");
    scanf("%d", &Y);
if(X<=0 || Y<=0) {
	printf("The X and Y must be bigger than 0\n"); }
} while(X<=0 || Y<=0);

f2(X, Y);
break;

case 3:

    do{
    printf("X: ");
    scanf("%d", &X);
    printf("Y: ");
    scanf("%d", &Y);
    printf("T: ");
    scanf("%d", &T);
if(X<=0 || Y<=0 || T<=0) {
	printf("The X, Y and T must be bigger than 0\n"); }
} while(X<=0 || Y<=0 || T<=0);

f3(X, Y, T);
break;

case 4:


do{
    printf("The width of the tree: ");
    scanf("%d", &X);
    printf("The height of the tree: ");
    scanf("%d", &Y);
if(X<2 || Y<2) {
	printf("The X and Y must be bigger than 2\n"); }
} while(X<2 || Y<2);

f4(X, Y);
break;

case 5:

    do{
    printf("Radius: ");
    scanf("%d", &X);
if(X<=0) {
	printf("The radius must be bigger than 0\n"); }
} while(X<=0);

f5(X);
break;

case 6:

do{
    printf("X: ");
    scanf("%d", &X);
    printf("Y: ");
    scanf("%d", &Y);
if(X<=0 || Y<=0) {
	printf("The X and Y must be bigger than 0\n"); }
} while(X<=0 || Y<=0);

f6(X, Y);
break;

case 7:

f7(X,Y,i);
break;

default: printf("Please write a number between 1 and 7"); }
return 0; }
