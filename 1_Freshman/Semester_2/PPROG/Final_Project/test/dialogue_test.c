/** 
 * @brief Comprueba la implementación del dialogo
 * @file dialogue_test.c
 * @author Cristina Soria
 * @version 1.0 
 * @date 26-04-2018
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "../include/dialogue.h"
#include "../include/command.h"
#include "dialogue_test.h"
#include "test.h"

#define MAX_TEST 24


/** 
 * @brief Funcion principal de pruebas para el modulo dialogue. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 24 solo ejecuta la prueba indicada  
 *  
 */
int main(int argc, char** argv) {
    	int test = 0;
    	int all = 1;

if (argc < 2) {

		printf("Running all test for module Dialogue:\n");
   	}else{

 
test = atoi(argv[1]);
        	all = 0;
        	printf("Running test %d: \n", test);
		if (test < 1 && test > MAX_TEST) {
			printf("Error: unknown test: \n");
			exit(EXIT_SUCCESS);
        	}
    	}

	if (all || test == 1) test1_dialogue_create();
	if (all || test == 2) test2_dialogue_create();
	if (all || test == 3) test1_dialogue_destroy();
	if (all || test == 4) test2_dialogue_destroy();
    if (all || test == 5) test1_dialogue_set_comando();
    if (all || test == 6) test2_dialogue_set_comando();
    if (all || test == 7) test1_dialogue_set_status();
    if (all || test == 8) test2_dialogue_set_status();
    if (all || test == 9) test1_dialogue_set_object_nomovible();
    if (all || test == 10) test2_dialogue_set_object_nomovible();
    if (all || test == 11) test1_dialogue_set_check_space();
    if (all || test == 12) test2_dialogue_set_check_space();
    if (all || test == 13) test1_dialogue_set_link_cerrado();
    if (all || test == 14) test2_dialogue_set_link_cerrado();
    if (all || test == 15) test1_dialogue_set_link_open();
    if (all || test == 16) test2_dialogue_set_link_open();
    if (all || test == 17) test1_dialogue_set_no_monster();
    if (all || test == 18) test2_dialogue_set_no_monster();
    if (all || test == 19) test1_dialogue_set_space();
    if (all || test == 20) test2_dialogue_set_space();
    if (all || test == 21) test1_dialogue_set_object();
    if (all || test == 22) test2_dialogue_set_object();
    if (all || test == 23) test1_dialogue_set_link_name();
    if (all || test == 24) test2_dialogue_set_link_name();


        PRINT_PASSED_PERCENTAGE;

    return 0;
}



void test1_dialogue_create(){
    
    Dialogue* dialogue = NULL;
    dialogue = dialogue_create();
    PRINT_TEST_RESULT(dialogue != NULL);
	dialogue_destroy(dialogue);
}

void test2_dialogue_create() {
    
    Dialogue* dialogue = NULL;
    PRINT_TEST_RESULT(dialogue == NULL);
}

void test1_dialogue_destroy(){
    
    Dialogue* dialogue = NULL;
    dialogue = dialogue_create();
    PRINT_TEST_RESULT(dialogue_destroy(dialogue) == OK);
}

void test2_dialogue_destroy(){
   
    Dialogue* dialogue = NULL;
    PRINT_TEST_RESULT(dialogue_destroy(dialogue) == ERROR);
}

void test1_dialogue_set_comando(){
    Dialogue* dialogue =NULL;
    Command* cmd=NULL;
    dialogue = dialogue_create();
    cmd = command_create();
    PRINT_TEST_RESULT(dialogue_set_comando(dialogue,cmd)==OK);
    dialogue_destroy(dialogue);
    command_destroy(cmd);
}

void test2_dialogue_set_comando(){
    Dialogue* dialogue =NULL;
    Command* cmd=NULL;
    PRINT_TEST_RESULT(dialogue_set_comando(dialogue,cmd)==ERROR);
}

void test1_dialogue_set_status(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_status(dialogue,OK)==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_status(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_status(dialogue,OK)==ERROR);
}

void test1_dialogue_set_object_nomovible(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_object_nomovible(dialogue,FALSE)==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_object_nomovible(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_object_nomovible(dialogue,TRUE)==ERROR);
}

void test1_dialogue_set_check_space(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_check_space(dialogue,TRUE)==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_check_space(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_check_space(dialogue,TRUE)==ERROR);
}

void test1_dialogue_set_link_cerrado(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_link_cerrado(dialogue,FALSE)==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_link_cerrado(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_link_cerrado(dialogue,FALSE)==ERROR);
}

void test1_dialogue_set_link_open(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_link_open(dialogue,TRUE)==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_link_open(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_link_open(dialogue,FALSE)==ERROR);
}

void test1_dialogue_set_no_monster(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_no_monster(dialogue,TRUE)==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_no_monster(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_no_monster(dialogue,FALSE)==ERROR);
}

void test1_dialogue_set_space(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_space(dialogue,"Space1")==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_space(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_space(dialogue,"Space2")==ERROR);
}

void test1_dialogue_set_object(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_object(dialogue,"object1")==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_object(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_object(dialogue,"object2")==ERROR);
}

void test1_dialogue_set_link_name(){
    Dialogue* dialogue =NULL;
    dialogue = dialogue_create();    
    PRINT_TEST_RESULT(dialogue_set_link_name(dialogue,"link1")==OK);
    dialogue_destroy(dialogue);
}

void test2_dialogue_set_link_name(){
    Dialogue* dialogue =NULL;
    PRINT_TEST_RESULT(dialogue_set_link_name(dialogue,"link2")==ERROR);
}

