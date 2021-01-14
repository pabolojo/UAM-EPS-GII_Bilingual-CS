/** 
 * @brief Comprueba la implementación del set
 * @file set_test.c
 * @author Cristina Soria
 * @version 1.0 
 * @date 26-03-2018
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "../include/set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TEST 13

/** 
 * @brief Funcion principal de pruebas para el modulo Set. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 13 solo ejecuta la prueba indicada  
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


if (all || test == 1) test1_set_create();
    if (all || test == 2) test2_set_create();
    if (all || test == 3) test1_set_destroy();
    if (all || test == 4) test2_set_destroy();
    if (all || test == 5) test1_set_add();
    if (all || test == 6) test2_set_add();
    if (all || test == 7) test1_set_del();
    if (all || test == 8) test2_set_del();
    if (all || test == 9) test1_set_get_id();
    if (all || test == 11) test2_set_get_id();
    if (all || test == 12) test1_set_get_nId();
    if (all || test == 13) test2_set_get_nId();
        PRINT_PASSED_PERCENTAGE;

    return 0;
}



void test1_set_create(){
    
    Set* set = NULL;
    set= set_create();
    PRINT_TEST_RESULT(set!=NULL);
	set_destroy(set);
}

void test2_set_create(){
    
    Set* set= NULL;
    PRINT_TEST_RESULT(set == NULL);
}

void test1_set_destroy(){
    
   Set* set = NULL;
    set = set_create();
    PRINT_TEST_RESULT(set_destroy(set) == OK);
}

void test2_set_destroy(){
    
    Set* set = NULL;
    PRINT_TEST_RESULT(set_destroy(set) == ERROR);
}


void test1_set_get_id(){ 
   
    Set* set = NULL;
    set = set_create();
    set_add(set, 4);
    PRINT_TEST_RESULT(set_get_Id(set, 0) == 4);
	set_destroy(set);
}

void test2_set_get_id(){
    
    Set* set = NULL;
    PRINT_TEST_RESULT(set_get_Id(set, 5) == NO_ID);
}


void test1_set_get_nId(){
    
    Set* set = NULL;
    set = set_create();
    set_add(set, 4);
    PRINT_TEST_RESULT(set_get_nId(set) == 1);
	set_destroy(set);
}

void test2_set_get_nId(){
  
    Set* set = NULL;
    PRINT_TEST_RESULT(set_get_nId(set) == NO_ID);
}


void test1_set_add(){
   
    Set* set = NULL;
    Id id = 8;
    PRINT_TEST_RESULT(set_add(set, id) == ERROR);
}

void test2_set_add(){
   
    Set* set = NULL;
    Id id=8;
    set = set_create();
    PRINT_TEST_RESULT(set_add(set, id) == OK);
	set_destroy(set);
}


void test1_set_del(){
   
    Set *set = NULL;
    Id id_set = 10;
    set = set_create();
    set_add(set, id_set);
    PRINT_TEST_RESULT(set_del(set, id_set)== OK);
	set_destroy(set);
}

void test2_set_del(){
    
    Set *set = NULL;
    Id id_set = 10;
    PRINT_TEST_RESULT(set_del(set, id_set)== ERROR);
}
