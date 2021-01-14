/** 
 * @brief Comprueba la implementación del link
 * @file link_test.c
 * @author Sergio de los Reyes
 * @version 1.0 
 * @date 26-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 25 

/** 
 * @brief Funcion principal de pruebas para el modulo Link. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 25 solo ejecuta la prueba indicada     
 *  
 */
int main(int argc, char **argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module LINK:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_link_create();
    if (all || test == 2) test2_link_create();
    if (all || test == 3) test1_link_destroy();
    if (all || test == 4) test2_link_destroy();

    if (all || test == 5) test1_link_set_name();
    if (all || test == 6) test2_link_set_name();
    if (all || test == 7) test3_link_set_name();
    if (all || test == 8) test1_link_set_link();
    if (all || test == 9) test2_link_set_link();
    if (all || test == 10) test3_link_set_link();
	if (all || test == 11) test1_link_set_status();
	if (all || test == 12) test2_link_set_status();    

    if (all || test == 13) test1_link_get_id();
    if (all || test == 14) test2_link_get_id();
    if (all || test == 15) test1_link_get_name();
    if (all || test == 16) test2_link_get_name();
    if (all || test == 17) test1_link_get_status();
    if (all || test == 18) test1_link_get_status();
    if (all || test == 19) test1_link_get_link();
    if (all || test == 20) test2_link_get_link();

    if (all || test == 21) test1_link_space_connected_to();
    if (all || test == 22) test2_link_space_connected_to();
    if (all || test == 23) test2_link_space_connected_to();
    if (all || test == 24) test1_link_print();
    if (all || test == 25) test2_link_print();

    PRINT_PASSED_PERCENTAGE;

    return EXIT_SUCCESS;
}

void test1_link_create() {
	int result=0;
	Link* l=NULL;
	l = link_create(5);
	result = l != NULL;
	PRINT_TEST_RESULT(result);
	link_destroy(l);
}

void test2_link_create() {
    Link *l=NULL;
    l = link_create(NO_ID);
    PRINT_TEST_RESULT(l==NULL);
}

void test1_link_destroy(){
	Link* l=NULL;
    l = link_create(18);
    PRINT_TEST_RESULT(link_destroy(l) == OK);
}

void test2_link_destroy(){
	Link* l=NULL;
    PRINT_TEST_RESULT(link_destroy(l) == ERROR);
}

void test1_link_set_name() {
    Link *l;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_name(l, "hola") == OK);
    link_destroy(l);
}

void test2_link_set_name() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_name(l, "hola") == ERROR);
}

void test3_link_set_name() {
    Link *l;
    l = link_create(5);
    PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
    link_destroy(l);
}

void test1_link_set_link() {
    Link *l = NULL;
    Id space1 = 3, space2 = 4;
    PRINT_TEST_RESULT(link_set_link(l, space1, space2) == ERROR);
}

void test2_link_set_link() {
    Link *l;
    Id space1, space2;

    l = link_create(4);
    space1 = 3, space2 = NO_ID;
    PRINT_TEST_RESULT(link_set_link(l, space1, space2) == ERROR);
    link_destroy(l);
}

void test3_link_set_link() {
    Link *l;
    Id space1, space2;
    space1 = 3, space2 = NO_ID;
    l = link_create(4);
    PRINT_TEST_RESULT(link_set_link(l, space1, space2) == ERROR);
    link_destroy(l);
}

void test1_link_set_status(){
	Link *l = NULL;
	l = link_create(4);
    	PRINT_TEST_RESULT(link_set_status(l,OPENNED) == OK);
	link_destroy(l);
}

void test2_link_set_status(){
	Link *l = NULL;
    PRINT_TEST_RESULT(link_set_status(l,OPENNED) == ERROR);
}

void test1_link_get_id() {
    Link *l;
    l = link_create(25);
    PRINT_TEST_RESULT(link_get_id(l) == 25);
	link_destroy(l);
}

void test2_link_get_id() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
}

void test1_link_get_name() {
    Link *l;
    l = link_create(1);
    link_set_name(l, "adios");
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "adios") == 0);
    link_destroy(l);
}

void test2_link_get_name() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

void test1_link_get_status(){
	Link *l;
    l = link_create(25);
    link_set_status(l,OPENNED);
    PRINT_TEST_RESULT(link_get_status(l) == OPENNED);
	link_destroy(l);
}

void test2_link_get_status(){
	Link *l = NULL;
    PRINT_TEST_RESULT(link_get_status(l) == CLOSED);
}

void test1_link_get_link() {
    Link *l=NULL;
    Id space1, space2;

    space1 = 3, space2 = 4;
    l = link_create(4);

    link_set_link(l, space1, space2);

    PRINT_TEST_RESULT(link_get_link(l) !=NULL);
    link_destroy(l);
}

void test2_link_get_link() {
    Link *l = NULL;
    int result;
    result = link_get_link(l) == NULL;

    PRINT_TEST_RESULT(result);
}

void test1_link_space_connected_to(){
	Link *l=NULL;
    Id space1, space2;

    space1 = 3, space2 = 4;
    l = link_create(4);

    link_set_link(l, space1, space2);

    PRINT_TEST_RESULT(link_space_connected_to(l,3)==4);
    link_destroy(l);
}

void test2_link_space_connected_to(){
	Link *l=NULL;
    Id space1, space2;

    space1 = 3, space2 = 4;
    l = link_create(4);

    link_set_link(l, space1, space2);

    PRINT_TEST_RESULT(link_space_connected_to(l,5)==NO_ID);
    link_destroy(l);
}

void test3_link_space_connected_to(){
	Link *l=NULL;

    PRINT_TEST_RESULT(link_space_connected_to(l,5)==NO_ID);
    link_destroy(l);
}

void test1_link_print(){
	Link*l =NULL;
	l=link_create(5);
    PRINT_TEST_RESULT(link_print(l) == OK);
	link_destroy(l);
}
void test2_link_print(){
	Link*l =NULL;
    PRINT_TEST_RESULT(link_print(l) == ERROR);
}



