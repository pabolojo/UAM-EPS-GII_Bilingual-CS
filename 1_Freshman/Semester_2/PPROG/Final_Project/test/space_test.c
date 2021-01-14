/** 
 * @brief Comprueba la implementación del espacio
 * @file space_test.c
 * @author Cristina Soria
 * @version 1.0 
 * @date 26-03-2018
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "../include/space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TEST 59

/** 
 * @brief Funcion principal de pruebas para el modulo Space. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 60 solo ejecuta la prueba indicada  
 *  
 */
int main(int argc, char** argv) {
        int test = 0;
        int all = 1;

if (argc < 2) {

        printf("Running all test for module Space:\n");
    }else{

 
test = atoi(argv[1]);
            all = 0;
            printf("Running test %d: \n", test);
        if (test < 1 && test > MAX_TEST) {
            printf("Error: unknown test: \n");
            exit(EXIT_SUCCESS);
            }
        }

    if (all || test == 1) test1_space_create();
    if (all || test == 2) test2_space_create();
    if (all || test == 3) test1_space_destroy();
    if (all || test == 4) test2_space_destroy();
    if (all || test == 5) test1_space_get_id();
    if (all || test == 6) test2_space_get_id();
    if (all || test == 7) test1_space_set_name();
    if (all || test == 8) test2_space_set_name();
    if (all || test == 9) test1_space_get_name();
    if (all || test == 10) test2_space_get_name();
    if (all || test == 11) test1_space_set_north();
    if (all || test == 12) test2_space_set_north();
    if (all || test == 13) test1_space_get_north();
    if (all || test == 14) test2_space_get_north();
    if (all || test == 15) test1_space_set_south();
    if (all || test == 16) test2_space_set_south();
    if (all || test == 17) test1_space_get_south();
    if (all || test == 18) test2_space_get_south();
    if (all || test == 19) test1_space_set_east();
    if (all || test == 20) test2_space_set_east();
    if (all || test == 21) test1_space_get_east();
    if (all || test == 22) test2_space_get_east();
    if (all || test == 23) test1_space_set_west();
    if (all || test == 24) test2_space_set_west();
    if (all || test == 25) test1_space_get_west();
    if (all || test == 26) test2_space_get_west();

    if (all || test == 27) test1_space_add_objects();
    if (all || test == 28) test2_space_add_objects();
    if (all || test == 29) test1_space_del_objects();
    if (all || test == 30) test2_space_del_objects();
    if (all || test == 31) test1_space_get_objects();
    if (all || test == 32) test2_space_get_objects();

    if (all || test == 33) test1_space_object_in();
    if (all || test == 34) test2_space_object_in();
    if (all || test == 35) test1_space_set_gdesc();
    if (all || test == 36) test2_space_set_gdesc();
    if (all || test == 37) test1_space_get_gdesc();
    if (all || test == 38) test2_space_get_gdesc();
    if (all || test == 39) test1_space_set_description();
    if (all || test == 40) test2_space_set_description();
    if (all || test == 41) test1_space_set_description_detallada();
    if (all || test == 42) test2_space_set_description_detallada();
    if (all || test == 43) test1_space_set_up();
    if (all || test == 44) test2_space_set_up();
    if (all || test == 45) test1_space_set_down();
    if (all || test == 46) test2_space_set_down();
    if (all || test == 47) test1_space_set_iluminado();
    if (all || test == 48) test2_space_set_iluminado();
    if (all || test == 49) test1_space_get_description();
    if (all || test == 50) test2_space_get_description();
    if (all || test == 51) test1_space_get_description_detallada();
    if (all || test == 52) test2_space_get_description_detallada();
	if (all || test == 53) test3_space_get_description_detallada();
    if (all || test == 54) test1_space_get_up();
    if (all || test == 55) test2_space_get_up();
    if (all || test == 56) test1_space_get_down();
    if (all || test == 57) test2_space_get_down();
    if (all || test == 58) test1_space_get_iluminado();
    if (all || test == 59) test2_space_get_iluminado();
    
        PRINT_PASSED_PERCENTAGE;

    return 0;
}



void test1_space_create(){
    Space * space=NULL;
	space=space_create(4);
    int result = space!=NULL ;
    PRINT_TEST_RESULT(result);
	space_destroy(space);

}
void test2_space_create(){
    
    Space *space =NULL;
    space = space_create(4);
    PRINT_TEST_RESULT(space_get_id(space) == 4);
	space_destroy(space);
}

void test1_space_destroy(){
    
    Space *space =NULL;
    space = space_create(18);
    PRINT_TEST_RESULT(space_destroy(space) == OK);
}

void test2_space_destroy(){
    
    Space* space = NULL;
    PRINT_TEST_RESULT(space_destroy(space) == ERROR);
}

void test1_space_set_name(){
   
    Space *space =NULL;
    space = space_create(5);
    PRINT_TEST_RESULT(space_set_name(space, "Funciona") == OK);
	space_destroy(space);
}

void test2_space_set_name(){
    
    Space *space =NULL;
    PRINT_TEST_RESULT(space_set_name(space, "funciona") == ERROR);
}

void test1_space_get_id(){
    
    Space *space =NULL;
    space = space_create(20);
    PRINT_TEST_RESULT(space_get_id(space) == 20);
	space_destroy(space);
}

void test2_space_get_id(){
    
    Space *space = NULL;
    PRINT_TEST_RESULT(space_get_id(space) == NO_ID);
}


void test1_space_get_name(){
    
    Space *space = NULL;
    space = space_create(4);
    space_set_name(space, "funciona");
    PRINT_TEST_RESULT(strcmp(space_get_name(space), "funciona") == 0);
	space_destroy(space);
}

void test2_space_get_name(){
    
    Space *space = NULL;
    PRINT_TEST_RESULT(space_get_name(space) == NULL);

}

void test1_space_set_north(){
   
	Space *space =NULL;
	Link *link =NULL;
	link=link_create(5);
    space = space_create(4);
    PRINT_TEST_RESULT(space_set_north(space, link) == OK);
	space_destroy(space);
	link_destroy(link);
}

void test2_space_set_north(){
    
    Space *space =NULL;
	Link *link =NULL;
	link=link_create(5);
    PRINT_TEST_RESULT(space_set_north(space, link) == ERROR);
	link_destroy(link);
}

void test1_space_get_north(){
    
    Space* space = NULL;
	Link *link =NULL;
	space = space_create(18);
	link=link_create(5);
    space_set_north(space, link);
    PRINT_TEST_RESULT(space_get_north(space) == 5);
	space_destroy(space);
	link_destroy(link);
}

void test2_space_get_north(){
    
    Space* space = NULL;
    PRINT_TEST_RESULT(space_get_north(space) == NO_ID);
}

void test1_space_set_south(){
    
    Space * space = NULL;
	Link *link = NULL;
	link=link_create(5);
    space = space_create(4);
    PRINT_TEST_RESULT(space_set_south(space, link) == OK);
	space_destroy(space);
	link_destroy(link);
}

void test2_space_set_south(){
  
    Space* space = NULL;
	Link *link =NULL;
	link=link_create(5);
    PRINT_TEST_RESULT(space_set_south(space, link) == ERROR);

	link_destroy(link);
}


void test1_space_get_south(){
    
    Space* space = NULL;
	Link *link =NULL;
	link=link_create(5);
    space = space_create(18);
    space_set_south(space, link);
    PRINT_TEST_RESULT(space_get_south(space) == 5);
	space_destroy(space);
	link_destroy(link);
}


void test2_space_get_south(){
    
    Space* space = NULL;
    PRINT_TEST_RESULT(space_get_south(space) == NO_ID);
}
void test1_space_set_east(){
    
    Space* space=NULL;
	Link *link =NULL;
	link=link_create(5);
    space = space_create(4);
    PRINT_TEST_RESULT(space_set_east(space, link) == OK);
	space_destroy(space);
	link_destroy(link);
}

void test2_space_set_east(){
    
    Space* space = NULL;
	Link *link =NULL;
	link=link_create(5);
    PRINT_TEST_RESULT(space_set_east(space, link) == ERROR);

	link_destroy(link);
}
void test1_space_get_east(){
    
    Space* space;
	Link *link =NULL;
	link=link_create(5);
    space = space_create(18);
    space_set_east(space, link);
    PRINT_TEST_RESULT(space_get_east(space) == 5);
	space_destroy(space);
	link_destroy(link);
}

void test2_space_get_east(){
    
    Space * space = NULL;
    PRINT_TEST_RESULT(space_get_east(space) == NO_ID);
}

void test1_space_set_west(){
    
    Space * space = NULL;
	Link *link =NULL;
	link=link_create(5);
    space = space_create(4);
    PRINT_TEST_RESULT(space_set_west(space, link) == OK);
	space_destroy(space);
	link_destroy(link);
}

void test2_space_set_west(){
    
    Space * space = NULL;
	Link *link =NULL;
	link=link_create(5);
    PRINT_TEST_RESULT(space_set_west(space, link) == ERROR);

	link_destroy(link);
}

void test1_space_get_west(){
    
    Space * space = NULL;
	Link *link =NULL;
	link=link_create(5);
    space = space_create(18);
    space_set_west(space, link);
    PRINT_TEST_RESULT(space_get_west(space) == 5);
	space_destroy(space);
	link_destroy(link);
}


void test2_space_get_west(){
   
    Space * space = NULL;
    PRINT_TEST_RESULT(space_get_west(space) == NO_ID);
}

void test1_space_add_objects(){

    Space * space = NULL;
    space = space_create(5);
    PRINT_TEST_RESULT(space_add_objects(space, 9) == OK);
	space_destroy(space);

}
void test2_space_add_objects(){
    
    Space* space = NULL;
    PRINT_TEST_RESULT(space_add_objects(space, 8) == ERROR);
}

void test1_space_del_objects(){
   
    Space *space = NULL;
    space=space_create(1);
    space_add_objects(space,2);
    PRINT_TEST_RESULT(space_del_objects(space,2)== OK);
	space_destroy(space);
}

void test2_space_del_objects(){
   
    Space *space =NULL;
    space_add_objects(space,2);
    PRINT_TEST_RESULT(space_del_objects(space,2)== ERROR);
	space_destroy(space);
}

void test1_space_get_objects(){
    
    Space *space= NULL;  
    int i;
    int ok = 1;
    Id objects[2] = {3, 4};
    Set * set_objects =NULL;

    space = space_create(4);
    space_add_objects(space, 3);
    space_add_objects(space, 4);
    set_objects = space_get_objects(space);
    
    for (i=0; i < 3; i++){
        if(set_get_Id(set_objects,i) == objects[i]){
            ok = 0;
        }else{
            ok = 1;
			break;
        }
    }
    PRINT_TEST_RESULT(ok);
	space_destroy(space);

}

void test2_space_get_objects(){
   
    Space* space = NULL;
    PRINT_TEST_RESULT(space_get_objects(space) == NULL);

}

void test1_space_object_in(){
   
    Space* space = NULL;
	space = space_create(4);
	space_add_objects(space, 4);
    PRINT_TEST_RESULT(space_object_in(space,4) ==TRUE);
	space_destroy(space);

}
void test2_space_object_in(){
   
    Space* space = NULL;
    PRINT_TEST_RESULT(space_object_in(space,4) == FALSE);
}

void test1_space_set_gdesc(){
   
    Space* space = NULL;
    space=space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc(space,"Funciona", 1)== OK);
	space_destroy(space);
}

void test2_space_set_gdesc(){
   
    Space* space = NULL;
    PRINT_TEST_RESULT(space_set_gdesc(space,"Funciona", 1)== ERROR);
}

void test1_space_get_gdesc(){
   
    Space* space = NULL;
    space=space_create(1);
    space_set_gdesc(space,"Funciona", 1);
    PRINT_TEST_RESULT(!strcmp(space_get_gdesc(space,1),"Funciona"));
	space_destroy(space);
}

void test2_space_get_gdesc(){
    
    Space* space = NULL;
    space_set_gdesc(space,"Funciona", 1);
    PRINT_TEST_RESULT(space_get_gdesc(space,2)== NULL);
}


/*************** NUEVAS IMPLEMENTACIONES **************/

void test1_space_set_description(){
   
    Space* space = NULL;
    space=space_create(1);
    PRINT_TEST_RESULT(space_set_description(space,"Funciona")== OK);
    space_destroy(space);
}

void test2_space_set_description(){
   
    Space* space = NULL;
    PRINT_TEST_RESULT(space_set_description(space,"Funciona")== ERROR);
}



void test1_space_set_description_detallada(){
   
    Space* space = NULL;
    space=space_create(1);
    PRINT_TEST_RESULT(space_set_description_detallada(space,"Funciona")== OK);
    space_destroy(space);
}

void test2_space_set_description_detallada(){
   
    Space* space = NULL;
    PRINT_TEST_RESULT(space_set_description_detallada(space,"Funciona")== ERROR);
}



void test1_space_set_up(){
    
    Space * space = NULL;
    Link *link =NULL;
    link=link_create(5);
    space = space_create(4);
    PRINT_TEST_RESULT(space_set_up(space, link) == OK);
    space_destroy(space);
    link_destroy(link);
}

void test2_space_set_up(){
    
    Space * space = NULL;
    Link *link =NULL;
    link=link_create(5);
    PRINT_TEST_RESULT(space_set_up(space, link) == ERROR);

    link_destroy(link);
}


void test1_space_set_down(){
    
    Space * space = NULL;
    Link *link =NULL;
    link=link_create(5);
    space = space_create(4);
    PRINT_TEST_RESULT(space_set_down(space, link) == OK);
    space_destroy(space);
    link_destroy(link);
}

void test2_space_set_down(){
    
    Space * space = NULL;
    Link *link =NULL;
    link=link_create(5);
    PRINT_TEST_RESULT(space_set_down(space, link) == ERROR);

    link_destroy(link);
}

void test1_space_set_iluminado(){
   
    Space *space =NULL;
    space = space_create(5);
    PRINT_TEST_RESULT(space_set_iluminado(space, TRUE) == OK);
    space_destroy(space);
}

void test2_space_set_iluminado(){
    
    Space *space =NULL;
    PRINT_TEST_RESULT(space_set_iluminado(space, FALSE) == ERROR);
}

void test1_space_get_description(){
   
    Space* space = NULL;
    space=space_create(1);
    space_set_description(space,"Funciona");
    PRINT_TEST_RESULT(!strcmp(space_get_description(space),"Funciona"));
    space_destroy(space);
}

void test2_space_get_description(){
    
    Space* space = NULL;
    space_set_description(space,"Funciona");
    PRINT_TEST_RESULT(space_get_description(space)== NULL);
}


void test1_space_get_description_detallada(){
   
    Space* space = NULL;
    space = space_create(1);
    space_set_description_detallada(space,"Funciona");
	space_set_iluminado(space,TRUE);
    PRINT_TEST_RESULT(!strcmp(space_get_description_detallada(space),"Funciona"));
    space_destroy(space);
}

void test2_space_get_description_detallada(){
    
    Space* space = NULL;
	space=space_create(1);
    space_set_description_detallada(space,"Funciona");
	space_set_iluminado(space,FALSE);
    PRINT_TEST_RESULT(space_get_description_detallada(space)== NULL);
	space_destroy(space);
}

void test3_space_get_description_detallada(){
    
    Space* space = NULL;
    space_set_description_detallada(space,"Funciona");
    PRINT_TEST_RESULT(space_get_description_detallada(space)== NULL);
}

void test1_space_get_up(){
    
    Space * space = NULL;
    Link *link =NULL;
    link=link_create(5);
    space = space_create(18);
    space_set_up(space, link);
    PRINT_TEST_RESULT(space_get_up(space) == 5);
    space_destroy(space);
    link_destroy(link);
}


void test2_space_get_up(){
   
    Space * space = NULL;
    PRINT_TEST_RESULT(space_get_up(space) == NO_ID);
}

void test1_space_get_down(){
    
    Space * space = NULL;
    Link *link =NULL;
    link=link_create(5);
    space = space_create(18);
    space_set_down(space, link);
    PRINT_TEST_RESULT(space_get_down(space) == 5);
    space_destroy(space);
    link_destroy(link);
}


void test2_space_get_down(){
   
    Space * space = NULL;
    PRINT_TEST_RESULT(space_get_down(space) == NO_ID);
}


void test2_space_get_iluminado(){
    
    Space* space = NULL;
    space_set_iluminado(space, TRUE);
    PRINT_TEST_RESULT(space_get_iluminado(space)== FALSE);
}

void test1_space_get_iluminado(){
   
    Space* space = NULL;
    space=space_create(1);
	space_set_iluminado(space, TRUE);
    PRINT_TEST_RESULT(space_get_iluminado(space)== TRUE);
    space_destroy(space);
}

