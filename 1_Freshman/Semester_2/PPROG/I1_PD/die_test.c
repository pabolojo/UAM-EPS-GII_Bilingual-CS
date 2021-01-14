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
if(!(d=die_create((Id) 1))) return -1;
die_roll(d);
die_roll(d);
die_roll(d);
die_roll(d);
die_roll(d);
die_roll(d);
die_destroy(d);
return 0;
}

