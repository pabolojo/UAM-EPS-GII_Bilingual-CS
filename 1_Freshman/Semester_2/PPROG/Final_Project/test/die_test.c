/** 
 * @brief Comprueba la funcionalidad del módulo Die (dado).
 * @file die_test.c
 * @author Sergio de los Reyes
 * @version 1.0 
 * @date 03-04-2018
 */


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/die.h"
#include "die_test.h"
#include "test.h"

#define MAX_TESTS 9


/** 
 * @brief Funcion principal de pruebas para el modulo Die. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 9 solo ejecuta la prueba indicada  
 *  
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Die:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_die_create();
    if (all || test == 2) test1_die_create();  
    if (all || test == 3) test1_die_destroy();  
    if (all || test == 4) test1_die_destroy();  
    if (all || test == 5) test1_die_roll();
    if (all || test == 6) test2_die_roll();
    if (all || test == 7) test1_die_get_Value();
    if (all || test == 8) test2_die_get_Value();
    if (all || test == 9) test2_die_get_Value();

    PRINT_PASSED_PERCENTAGE;
    return 1;
}


void test1_die_create() {
	Die* dado =NULL;
	dado = die_create(5);
    
    PRINT_TEST_RESULT(dado!=NULL);
	die_destroy(dado);
}

void test2_die_create() {
    Die* dado = NULL;
    dado = die_create(5);
    PRINT_TEST_RESULT(die_get_id(dado) == 5);
	die_destroy(dado);
}

void test1_die_destroy(){
    
    Die* dado = NULL;
    dado = die_create(5);
    PRINT_TEST_RESULT(die_destroy(dado) == OK);

}

void test2_die_destroy(){

    Die* dado = NULL;
    PRINT_TEST_RESULT(die_destroy(dado) == ERROR);
}

void test1_die_roll() {
    Die * d = NULL;
    PRINT_TEST_RESULT(die_roll(d,6,1) == ERROR);
}

void test2_die_roll() {
    Die *d = NULL;
    d = die_create(4);
    PRINT_TEST_RESULT(die_roll(d,6,1) == OK);
	die_destroy(d);
}

void test1_die_get_Value() {
    Die *d = NULL;
    d = die_create(4);
    die_roll(d,6,1);
    PRINT_TEST_RESULT(die_get_lastValue(d) != -1);
	die_destroy(d);
}

void test2_die_get_Value() {
    Die *d = NULL;
    d = die_create(4);
    PRINT_TEST_RESULT(die_get_lastValue(d) == -1);
	die_destroy(d);
}

void test3_die_get_Value() {
    Die *d = NULL;
    PRINT_TEST_RESULT(die_get_lastValue(d) == -1);
}
