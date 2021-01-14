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
Id id=NO_ID;
printf("Creating Set ..........");
if(!(d=set_create())){
  printf(" ERROR\n");
  return -1;
}
printf(" OK\n");

printf("Inserting 99 ..........");
if(set_id_add(d,99)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}
printf("Inserting 98 ..........");
if(set_id_add(d,98)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}
printf("Inserting 56 ..........");
if(set_id_add(d,56)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}
printf("Inserting 99 ..........");
if(set_id_add(d,99)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}
printf("Inserting 10 ..........");
if(set_id_add(d,10)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}

printf("Printig Set ..........\n");
if(set_print(d)==OK){
  printf("DONE\n");
}
else{
  printf("ERROR\n");
}

printf("Is 10 contained in the Set? ");
if(set_id_in(d,(Id)10)){
  printf("Yes\n");
}
else{
  printf("No\n");
}
printf("Is 11 contained in the Set? ");
if(set_id_in(d,(Id)11)){
  printf("Yes\n");
}
else{
  printf("No\n");
}

printf("Removing 98 from Set ..........");
if(set_remov_id(d,(Id)98)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}

printf("Printig Set ..........\n");
if(set_print(d)==OK){
  printf("DONE\n");
}
else{
  printf("ERROR\n");
}

printf("Getting Id from pos 1 ..........");
id=set_get_id(d,1);
if(id!=NO_ID){
  printf(" DONE\n");
  printf("Id 1: %ld\n",id);
}
else{
  printf(" ERROR\n");
}

printf("Destroying Set ..........");
if(set_destroy(d)==OK){
  printf(" DONE\n");
}
else{
  printf(" ERROR\n");
}
return 0;
}

