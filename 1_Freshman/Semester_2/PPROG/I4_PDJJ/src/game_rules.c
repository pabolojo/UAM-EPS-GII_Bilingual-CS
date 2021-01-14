/** 
 * @brief Game Rules Module
 * 
 * @file game_rules.c
 * @version 1.0 
 * @date
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_rules.h"

/**
 * @brief defines the macro for the number of rules
 */	
#define N_RULES 6
/**
 * @brief defines the macro for the number of spaces
 */	
#define N_SPACES 20

/**
 * @brief defines the rules structure
 */
struct _Rules{
/**
 * @brief defines the variable rulelist
 */
  	RuleList rulelist;  
/**
 * @brief defines the variable die
 */	
	Die* die;          
/**
 * @brief defines the variable game
 */	
	Game* game;       
};
/**
 * @brief defines callbacks
 */
typedef void (*callback_fn)(Rules* rules);
/**
 * @brief  callback for R0
 *
 * @param gameRules
 *
 * @return void
 */
void rules_callback_R0(Rules* gameRules);
/**
 * @brief  callback for R1
 *
 * @param rules
 *
 * @return void
 */
void rules_callback_R1(Rules* rules);
/**
 * @brief  callback for R2
 *
 * @param rules
 *
 * @return void
 */
void rules_callback_R2(Rules* rules);
/**
 * @brief  callback for R3
 *
 * @param rules
 *
 * @return void
 */
void rules_callback_R3(Rules* rules);
/**
 * @brief  callback for R4
 *
 * @param rules
 *
 * @return void
 */
void rules_callback_R4(Rules* rules);
/**
 * @brief  callback for R5
 *
 * @param rules
 *
 * @return void
 */
void rules_callback_R5(Rules* rules);

/*static callback_fn rules_callback_fn_list[N_RULES]={
	rules_callback_R0,
	rules_callback_R1,
	rules_callback_R2, 
	rules_callback_R3,    
	rules_callback_R4,
	rules_callback_R5,
};

*/

Rules* RulesCreate() {
    Rules* rules = NULL;
    rules = (Rules*)malloc(sizeof(Rules));
    if (!rules) return NULL;

	rules->rulelist = NO_RULE;
	rules->die = die_create(3); 
	rules->game = NULL;
	return rules;
}

STATUS RulesDestroy(Rules* rules) {
    if (!rules) return ERROR;
    die_destroy(rules->die);
    free(rules);
    return OK;
}

STATUS RulesStart(Rules* rules, Game * game, BOOL disable, int rule) {
 
 if (!rules||!game) return ERROR;
    rules->game=game;
   
 if (disable) {
    rules_callback_R0(rules);
    return OK;
    }

RandomRule(rules);

return OK;

}

void RandomRule (Rules* rules){

	int value;

	die_roll(rules->die);

	value = die_get_value(rules->die);

	
	switch( value )
	{	
    case 1:
        rules_callback_R0(rules);
	break;
    case 2:
        rules_callback_R1(rules);
	break;
    case 3:
        rules_callback_R2(rules);
	break;
    case 4:
        rules_callback_R3(rules);
	break;
    case 5:
        rules_callback_R4(rules);
	break;
    case 6:
        rules_callback_R5(rules);
	break;
    default :
        rules_callback_R0(rules);
	break;
	} 

}

    /*CALLBACKS*/

/*R0: NO RULE*/
void rules_callback_R0(Rules* rules){
game_set_rule(rules->game, "NO_RULE");
}

/*R1: RANDOM OBJECT HIDING*/
void rules_callback_R1(Rules* rules){
int i, value;

game_set_rule(rules->game, "rndhide");

for(i=20; i>0; i--) {
value = die_roll(rules->die);
if (value > 4) {
game_set_object_hidden(rules->game, TRUE, i);
}
}

for(i=20; i>0; i--) {
value = die_roll(rules->die);
if (value > 4) {
game_set_object_hidden(rules->game, FALSE, i);
}
}
}

/*R2: MAX BACK MOVEMENTS 8*/
void rules_callback_R2(Rules* rules) {
game_set_rule(rules->game, "maxbck");
game_set_rulevar(rules->game, 4);
}

/*R3: NO SAVE OR LOAD GAME*/
void rules_callback_R3(Rules* rules){
game_set_rule(rules->game, "!save");
}

/*R4: NO SPACE OR OBJ INSPECTION*/
void rules_callback_R4(Rules* rules){
game_set_rule(rules->game, "!inspect");
}

/*R5: RANDOM LIGHTING*/
void rules_callback_R5(Rules* rules){
int i, value;

game_set_rule(rules->game, "rndlight");

for(i=20; i>0; i--) {
value = die_roll(rules->die);
if (value > 4) {
game_set_space_illum(rules->game, TRUE, i);
}
}

for(i=20; i>0; i--) {
value = die_roll(rules->die);
if (value > 4) {
game_set_space_illum(rules->game, FALSE, i);
}
}

}

			


