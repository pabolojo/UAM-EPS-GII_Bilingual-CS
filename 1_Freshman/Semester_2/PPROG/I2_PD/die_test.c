/**
 * @brief It tests die module
 *
 * @file die_test.c
 * @version 1.0
 * @date 28-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "die.h"
/*main that checks if die moduel is correct*/
int main(){

Die *d=NULL;
printf("Creating die 1 ..........");
if(!(d=die_create((Id) 1))){
  printf(" ERROR\n");
  return -1;
}
printf(" OK\n");
printf("Rolling die .......... %d\n",die_roll(d));
printf("Rolling die .......... %d\n",die_roll(d));
printf("Rolling die .......... %d\n",die_roll(d));
printf("Rolling die .......... %d\n",die_roll(d));
printf("Rolling die .......... %d\n",die_roll(d));
printf("Rolling die .......... %d\n",die_roll(d));
printf("Destroying die 1 ..........");
die_destroy(d);
printf(" OK\n");
return 0;
}

