/** 
 * @brief Comprueba la implementación del inventorio
 * @file space_test.c
 * @author Cristina Soria
 * @version 1.0 
 * @date 26-03-2018
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "../include/inventory.h"
#include "../include/set.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TEST 19

/** 
 * @brief Funcion principal de pruebas para el modulo Space. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 18 solo ejecuta la prueba indicada  
 *  
 */
int main(int argc, char** argv) {
    	int test = 0;
    	int all = 1;

if (argc < 2) {

		printf("Running all test for module Inventory:\n");
   	}else{

 
test = atoi(argv[1]);
        	all = 0;
        	printf("Running test %d: \n", test);
		if (test < 1 && test > MAX_TEST) {
			printf("Error: unknown test: \n");
			exit(EXIT_SUCCESS);
        	}
    	}

	if (all || test == 1) test1_inventory_create();
	if (all || test == 2) test2_inventory_create();
	if (all || test == 3) test1_inventory_destroy();
	if (all || test == 4) test2_inventory_destroy();
	if (all || test == 5) test1_inventory_set_dimension();
	if (all || test == 6) test2_inventory_set_dimension();
	if (all || test == 7) test1_inventory_get_number_objects();
	if (all || test == 8) test2_inventory_get_number_objects();
	if (all || test == 9) test1_inventory_get_id();
	if (all || test == 10) test2_inventory_get_id();
	if (all || test == 11) test1_inventory_get_objects();
	if (all || test == 12) test2_inventory_get_objects();
	if (all || test == 13) test1_inventory_add_object();
	if (all || test == 14) test2_inventory_add_object();
	if (all || test == 15) test1_inventory_remove_object();
	if (all || test == 16) test2_inventory_remove_object();
	if (all || test == 17)  test3_inventory_remove_object();
	if (all || test == 18) test1_inventory_object_exist();
	if (all || test == 19) test2_inventory_object_exist();
  

        PRINT_PASSED_PERCENTAGE;

    return 0;
}



void test1_inventory_create(){
    
    Inventory* inventory = NULL;
    inventory = inventory_create();
    PRINT_TEST_RESULT(inventory != NULL);
	inventory_destroy(inventory);
}

void test2_inventory_create() {
    
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory == NULL);
}

void test1_inventory_destroy(){
    
    Inventory* inventory = NULL;
    inventory = inventory_create();
    PRINT_TEST_RESULT(inventory_destroy(inventory) == OK);
}


void test2_inventory_destroy(){
   
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory_destroy(inventory) == ERROR);
}


void test1_inventory_set_dimension(){
    
    Inventory* inventory = NULL;
    inventory = inventory_create();
    PRINT_TEST_RESULT(inventory_set_dimension(inventory, 9) == OK);
	inventory_destroy(inventory);
}


void test2_inventory_set_dimension(){
    
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory_set_dimension(inventory, 9) == ERROR);
}

void test1_inventory_get_number_objects(){
    
    Inventory* inventory = NULL;
    inventory = inventory_create();
    inventory_add_object(inventory, 9);
    PRINT_TEST_RESULT(inventory_get_number_objects(inventory) == 1);
	inventory_destroy(inventory);
}

void test2_inventory_get_number_objects(){
    
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory_get_number_objects(inventory) == -1);
}

void test1_inventory_get_id(){
    
    Inventory* inventory = NULL;
    inventory = inventory_create();
    inventory_add_object(inventory, 9);
    PRINT_TEST_RESULT(inventory_get_id(inventory, 0) == 9);
	inventory_destroy(inventory);
}


void test2_inventory_get_id(){
    
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory_get_id(inventory, 9) == NO_ID);
}

void test1_inventory_get_objects(){
   
	Inventory* inventory = NULL;
	int i=0;
    	int ok = 1;
    	Id objects[2] = {3, 4};
    	Set * set_objects =NULL;

    	inventory = inventory_create();
    	inventory_add_object(inventory, 3);
	inventory_add_object(inventory, 4);
    	set_objects = inventory_get_objects(inventory);
    
    	for (i=0; i < 3; i++){
        	if(set_get_Id(set_objects,i) == objects[i]){
            		ok = 0;
        	}else{
            		ok = 1;
			break;
        	}
    	}

	PRINT_TEST_RESULT(ok);
    inventory_destroy(inventory);
}
void test2_inventory_get_objects(){
   
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory_get_objects(inventory)==NULL);
}


void test1_inventory_add_object(){
   
    Inventory* inventory = NULL;
    inventory = inventory_create();
    inventory_add_object(inventory, 1);
    inventory_add_object(inventory, 2);
    inventory_add_object(inventory, 3);
    inventory_add_object(inventory, 4);
    inventory_add_object(inventory, 5);
    inventory_add_object(inventory, 6);
    inventory_add_object(inventory, 7);
    inventory_add_object(inventory, 8);
    inventory_add_object(inventory, 9);
    inventory_add_object(inventory, 10);
    PRINT_TEST_RESULT(inventory_add_object(inventory,11) == ERROR);
	inventory_destroy(inventory);
}

void test2_inventory_add_object(){
   
    Inventory* inventory = NULL;
    PRINT_TEST_RESULT(inventory_add_object(inventory, NO_ID) == ERROR);
}

void test1_inventory_remove_object(){

	Inventory* inventory = NULL;
	inventory = inventory_create();
    inventory_add_object(inventory, 9);
	PRINT_TEST_RESULT(inventory_remove_object(inventory, 9) == OK);
	inventory_destroy(inventory);
}

void test2_inventory_remove_object(){

	Inventory* inventory = NULL;
	PRINT_TEST_RESULT(inventory_remove_object(inventory, 9) == ERROR); 
}

void test3_inventory_remove_object(){

	Inventory* inventory = NULL;
	inventory = inventory_create();
    inventory_add_object(inventory, 9);
	PRINT_TEST_RESULT(inventory_remove_object(inventory, NO_ID) == ERROR);
	inventory_destroy(inventory);
}

void test1_inventory_object_exist(){
	Inventory* inventory = NULL;
	inventory = inventory_create();
    inventory_add_object(inventory, 9);
	PRINT_TEST_RESULT(inventory_object_exist(inventory, 9) == TRUE);
	inventory_destroy(inventory);
}

void test2_inventory_object_exist(){
	
    Inventory* inventory = NULL;
	PRINT_TEST_RESULT(inventory_object_exist(inventory, 9) == FALSE);
	inventory_destroy(inventory);
}


