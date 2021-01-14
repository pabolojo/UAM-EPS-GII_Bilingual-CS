/** 
 * @brief Comprueba la implementación del jugador
 * @file player_test.c
 * @author Cristina Soria
 * @version 1.0 
 * @date 26-03-2018
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "../include/player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TEST 22

/** 
 * @brief Funcion principal de pruebas para el modulo Player. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y 22 solo ejecuta la prueba indicada  
 *  
 */
int main(int argc, char** argv) {
    	int test = 0;
    	int all = 1;

	if (argc < 2) {
		printf("Running all test for module Player:\n");
   	}else{

		test = atoi(argv[1]);
        	all = 0;
        	printf("Running test %d: \n", test);
		if (test < 1 && test > MAX_TEST) {
			printf("Error: unknown test: \n");
			exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_player_create();
	if (all || test == 2) test2_player_create();
	if (all || test == 3) test1_player_destroy();
	if (all || test == 4) test2_player_destroy();
	if (all || test == 5) test1_player_set_name();
	if (all || test == 6) test2_player_set_name();
	if (all || test == 7) test1_player_set_space();
	if (all || test == 8) test2_player_set_space();
	if (all || test == 9) test1_player_set_object();
	if (all || test == 10) test2_player_set_object();
	if (all || test == 11) test1_player_get_name();
	if (all || test == 12) test2_player_get_name();
	if (all || test == 13) test1_player_get_id();
	if (all || test == 14) test2_player_get_id();
	if (all || test == 15) test1_player_get_space();
	if (all || test == 16) test2_player_get_space();
	if (all || test == 17) test1_player_get_object();
	if (all || test == 18) test2_player_get_object();
	if (all || test == 19) test1_player_get_objects();
	if (all || test == 20) test2_player_get_objects();
	if (all || test == 21) test1_player_del_objects();
	if (all || test == 22) test2_player_del_objects();


      PRINT_PASSED_PERCENTAGE;

    return 0;
}




void test1_player_create(){
	Player* player=NULL;
	player = player_create(5);
    PRINT_TEST_RESULT(player!=NULL);
	player_destroy(player);
}

void test2_player_create(){
    
    Player* player=NULL;
    player = player_create(NO_ID);
    PRINT_TEST_RESULT(player == NULL);
}

void test1_player_destroy(){
    
    Player* player=NULL;
    player = player_create(18);
    PRINT_TEST_RESULT(player_destroy(player) == OK);
}

void test2_player_destroy(){
 
    Player* player = NULL;
    PRINT_TEST_RESULT(player_destroy(player) == ERROR);
}

void test1_player_set_name(){
    
    Player *player = NULL;
    player = player_create(5);
    PRINT_TEST_RESULT(player_set_name(player, "Funciona") == OK);
	player_destroy(player);
}

void test2_player_set_name(){
    
    Player *player = NULL;
    PRINT_TEST_RESULT(player_set_name(player, "Error") == ERROR);


}

void test1_player_set_space(){
    
    Player *player = NULL;
    player = player_create(5); 
    PRINT_TEST_RESULT(player_set_space(player, 5) == OK);
	player_destroy(player);
}

void test2_player_set_space(){
    
    Player *player = NULL;
    PRINT_TEST_RESULT(player_set_space(player, 5) == ERROR);
}

void test1_player_set_object(){

    Player *player = NULL;
    player = player_create(6); 
    PRINT_TEST_RESULT(player_set_object(player, 5) == OK);
	player_destroy(player);
}

void test2_player_set_object(){
    
    Player * player = NULL;
    PRINT_TEST_RESULT(player_set_object(player, 5) == ERROR);
}

void test1_player_get_name(){
    
    Player *player = NULL;
    player = player_create(5);
    player_set_name(player, "Funciona");
    PRINT_TEST_RESULT(strcmp(player_get_name(player), "Funciona") == 0);
	player_destroy(player);

}

void test2_player_get_name(){
    
    Player *player = NULL;
    PRINT_TEST_RESULT(player_get_name(player) == NULL);
}

void test1_player_get_id(){
    
    Player *player = NULL;
    player = player_create(18);
    PRINT_TEST_RESULT(player_get_id(player) == 18);
	player_destroy(player);
}

void test2_player_get_id(){
    
    Player* player = NULL;
    PRINT_TEST_RESULT(player_get_id(player) == NO_ID);
}

void test1_player_get_space(){
    
    Player* player;
    player = player_create(5);
    player_set_space(player, 6);
    PRINT_TEST_RESULT(player_get_space(player) == 6);
	player_destroy(player);
}
void test2_player_get_space(){
    
    Player* player = NULL;
    PRINT_TEST_RESULT(player_get_space(player) == NO_ID);
}
void test1_player_get_object(){
    
    Player *player = NULL;
    player = player_create(5);
    player_set_object(player, 6);
    PRINT_TEST_RESULT(player_get_object(player, 6) == TRUE);
	player_destroy(player);
}
void test2_player_get_object(){
    
    Player* player = NULL;
    PRINT_TEST_RESULT(player_get_object(player, 4) == FALSE);
}

void test1_player_get_objects(){
    
	Player *player = NULL;
	int i=0;
    int ok = 1;
    Id objects[2] = {3, 4};
    Set * set_objects =NULL;

	player = player_create(5);
	player_set_object(player, 3);
	player_set_object(player, 4);
    set_objects = player_get_objects(player);
    
	for (i=0; i < 3; i++){
	  	if(set_get_Id(set_objects,i) == objects[i]){
			ok = 0;
		}else{
			ok = 1;
			break;
		}
	}

	PRINT_TEST_RESULT(ok);
    player_destroy(player);
}

void test2_player_get_objects(){
    
    Player* player = NULL;
    PRINT_TEST_RESULT(player_get_objects(player) == NULL);

}
void test1_player_del_objects(){
    
    Player *player = NULL;
    player = player_create(5);
    player_set_object(player, 5); 
    PRINT_TEST_RESULT(player_del_objects(player, 5) == OK);
	player_destroy(player);
}
void test2_player_del_objects(){

    Player *player = NULL;
    PRINT_TEST_RESULT(player_del_objects(player, 5) == ERROR);
}
