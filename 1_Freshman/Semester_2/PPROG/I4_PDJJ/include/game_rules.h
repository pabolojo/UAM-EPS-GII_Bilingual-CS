/** 
 * @brief Game Rules Header
 * 
 * @file game_rules.h
 * @version 1.0 
 * @date 02/05/2019
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "types.h"
#include "game.h"
#include "die.h"

/**
 * @brief defines rule list
 *
 */
typedef enum _RuleList {
	NO_RULE = -1, RULE_1, RULE_2, RULE_3, RULE_4
} RuleList;
/**
 * @brief defines the rules structure
 *
 */
typedef struct _Rules Rules;

/**
 * @brief  create a game rule
 *
 * @return Rule or NULL in case of error
 */
Rules* RulesCreate();
/**
 * @brief  destroy rule
 *
 * @param rules
 *
 * @return OK, or ERROR
 */
STATUS RulesDestroy(Rules* rules);
/**
 * @brief set rules start
 *
 * @param rules
 * @param game
 * @param disable
 * @param rule
 *
 * @return OK or ERROR
 */
STATUS RulesStart(Rules* rules, Game * game, BOOL disable, int rule);
/**
 * @brief set randum rules
 *
 * @param rules
 *
 * @return void
 */

void RandomRule(Rules* rules);

#endif

