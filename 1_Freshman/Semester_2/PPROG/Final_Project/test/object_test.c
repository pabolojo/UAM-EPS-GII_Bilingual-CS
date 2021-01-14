/** 
 * @brief Comprueba la implementación del objeto
 * @file object_test.c
 * @author Julia Simon
 * @version 1.0 
 * @date 08-04-2018
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "../include/object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TEST 38

/** 
 * @brief Funcion principal de pruebas para el modulo Object. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 16 solo ejecuta la prueba indicada     
 *  
 */
int main(int argc, char** argv) {
    int test = 0;
    int all = 1;

	if (argc < 2) {
		printf("Running all test for module Object:\n");
   	}else{
		test = atoi(argv[1]);
       	all = 0;
       	printf("Running test %d: \n", test);
		if (test < 1 && test > MAX_TEST) {
			printf("Error: unknown test: \n");
			exit(EXIT_SUCCESS);
       	}
   	}

	if (all || test == 1) test1_object_create();
	if (all || test == 2) test2_object_create();
	if (all || test == 3) test1_object_destroy();
	if (all || test == 4) test2_object_destroy();

	if (all || test == 5) test1_object_set_name();
	if (all || test == 6) test2_object_set_name();
	if (all || test == 7) test1_object_set_description();
	if (all || test == 8) test1_object_set_description();

	if (all || test == 9) test1_object_get_name();
	if (all || test == 10) test2_object_get_name();
	if (all || test == 11) test1_object_get_id();
	if (all || test == 12) test2_object_get_id();
	if (all || test == 13) test1_object_print();
	if (all || test == 14) test2_object_print();
    
    if (all || test == 15) test1_object_get_movible();
    if (all || test == 16) test2_object_get_movible();
    if (all || test == 17) test1_object_set_movible();
    if (all || test == 18) test2_object_set_movible();
    if (all || test == 19) test1_object_get_movido();
    if (all || test == 20) test2_object_get_movido();
    if (all || test == 21) test1_object_set_movido();
    if (all || test == 22) test2_object_set_movido();
    if (all || test == 23) test1_object_get_oculto();
    if (all || test == 24) test2_object_get_oculto();
    if (all || test == 25) test1_object_set_oculto();
    if (all || test == 26) test2_object_set_oculto();
    if (all || test == 27) test1_object_get_open();
    if (all || test == 28) test2_object_get_open();
    if (all || test == 29) test1_object_set_open();
    if (all || test == 30) test2_object_set_open();
    if (all || test == 31) test1_object_get_iluminado();
    if (all || test == 32) test2_object_get_iluminado();
    if (all || test == 33) test1_object_set_iluminado();
    if (all || test == 34) test2_object_set_iluminado();
    if (all || test == 35) test1_object_get_encendido();
    if (all || test == 36) test2_object_get_encendido();
    if (all || test == 37) test1_object_set_encendido();
    if (all || test == 38) test2_object_set_encendido();


      PRINT_PASSED_PERCENTAGE;

    return 0;
}




void test1_object_create(){
	Object*object=NULL;
	object = object_create(5);
    PRINT_TEST_RESULT(object!=NULL);
	object_destroy(object);
}

void test2_object_create(){
    
    Object* object=NULL;
    object = object_create(NO_ID);
    PRINT_TEST_RESULT(object == NULL);
}

void test1_object_destroy(){
    
    Object* object=NULL;
    object = object_create(18);
    PRINT_TEST_RESULT(object_destroy(object) == OK);
}

void test2_object_destroy(){
 
    Object* object = NULL;
    PRINT_TEST_RESULT(object_destroy(object) == ERROR);
}

void test1_object_set_name(){
    
    Object *object = NULL;
    object = object_create(5);
    PRINT_TEST_RESULT(object_set_name(object, "Funciona") == OK);
	object_destroy(object);
}

void test2_object_set_name(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_name(object, "Error") == ERROR);


}

void test1_object_set_description(){
    
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_description(object, "Funciona") == OK);
	object_destroy(object);
}

void test2_object_set_description(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_description(object, "Error") == ERROR);
}

void test1_object_get_name(){

    Object *object = NULL;
    object = object_create(6); 
    object_set_name(object,"Funciona");
    PRINT_TEST_RESULT(strcmp(object_get_name(object), "Funciona") == 0);
	object_destroy(object);
}

void test2_object_get_name(){
    
    Object * object = NULL;
    PRINT_TEST_RESULT(object_get_name(object) == NULL);
}

void test1_object_get_id(){
    
    Object *object = NULL;
    object = object_create(5);
    PRINT_TEST_RESULT(object_get_id(object) == 5);
	object_destroy(object);

}

void test2_object_get_id(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_id(object) == NO_ID);
}

void test1_object_print(){
    Object*object =NULL;
    object = object_create(18);
    PRINT_TEST_RESULT(object_print(object) == OK);
	object_destroy(object);
}

void test2_object_print(){
    Object*object =NULL;
    PRINT_TEST_RESULT(object_print(object) == ERROR);
}



/***********  NUEVAS   **************/

void test1_object_get_movible(){
    
    Object *object = NULL;
    object = object_create(5);
    object_set_movible(object, TRUE);
    PRINT_TEST_RESULT(object_get_movible(object) == TRUE);
    object_destroy(object);

}

void test2_object_get_movible(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_movible(object) == FALSE);
}

void test1_object_set_movible(){
    
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_movible(object, TRUE) == OK);
    object_destroy(object);
}

void test2_object_set_movible(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_movible(object, FALSE) == ERROR);
}


void test1_object_get_movido(){
    
    Object *object = NULL;
    object = object_create(5);
    object_set_movido(object, TRUE);
    PRINT_TEST_RESULT(object_get_movido(object) == TRUE);
    object_destroy(object);

}

void test2_object_get_movido(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_movido(object) == FALSE);
}

void test1_object_set_movido(){
    
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_movido(object, TRUE) == OK);
    object_destroy(object);
}

void test2_object_set_movido(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_movido(object, FALSE) == ERROR);
}


void test1_object_get_oculto(){
    
    Object *object = NULL;
    object = object_create(5);
    object_set_oculto(object, TRUE);
    PRINT_TEST_RESULT(object_get_oculto(object) == TRUE);
    object_destroy(object);

}

void test2_object_get_oculto(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_oculto(object) == FALSE);
}

void test1_object_set_oculto(){
    
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_oculto(object, TRUE) == OK);
    object_destroy(object);
}

void test2_object_set_oculto(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_oculto(object, FALSE) == ERROR);
}



void test1_object_get_open(){
    Id id=8;
    Object *object = NULL;
    object = object_create(5);
    object_set_open(object, id);
    PRINT_TEST_RESULT(object_get_open(object) == id);
    object_destroy(object);

}

void test2_object_get_open(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_open(object) == NO_ID);
}

void test1_object_set_open(){
    Id id=6;
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_open(object, id) == OK);
    object_destroy(object);
}

void test2_object_set_open(){
    Id id=6;
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_open(object, id) == ERROR);
}




void test1_object_get_iluminado(){
    
    Object *object = NULL;
    object = object_create(5);
    object_set_iluminado(object, TRUE);
    PRINT_TEST_RESULT(object_get_iluminado(object) == TRUE);
    object_destroy(object);

}

void test2_object_get_iluminado(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_iluminado(object) == FALSE);
}

void test1_object_set_iluminado(){
    
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_iluminado(object, TRUE) == OK);
    object_destroy(object);
}

void test2_object_set_iluminado(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_iluminado(object, FALSE) == ERROR);
}



void test1_object_get_encendido(){
    
    Object *object = NULL;
    object = object_create(5);
    object_set_encendido(object, TRUE);
    PRINT_TEST_RESULT(object_get_encendido(object) == TRUE);
    object_destroy(object);

}

void test2_object_get_encendido(){
    
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_encendido(object) == FALSE);
}

void test1_object_set_encendido(){
    
    Object *object = NULL;
    object = object_create(5); 
    PRINT_TEST_RESULT(object_set_encendido(object, TRUE) == OK);
    object_destroy(object);
}

void test2_object_set_encendido(){
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_encendido(object, FALSE) == ERROR);
}

