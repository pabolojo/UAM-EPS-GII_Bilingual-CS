/**
 * @brief It tests set module
 *
 * @file die_test.c
 * @version 1.0
 * @date 28-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
/*main that checks if set moduel is correct*/
int main(){

Set *d=NULL;
if(!(d=set_create())) return -1;
set_id_add(d,99);
set_id_add(d,98);
set_id_add(d,56);
set_id_add(d,99);
set_id_add(d,10);
if(set_id_in(d,(Id)10)) printf("está\n");
if(!set_id_in(d,(Id)11)) printf("no está\n");
set_print(d);
printf("eliminando...\n");
set_remov_id(d,(Id)98);
set_print(d);
printf("Id pos 1: %ld\n",set_get_id(d,1));
set_destroy(d);
return 0;
}

