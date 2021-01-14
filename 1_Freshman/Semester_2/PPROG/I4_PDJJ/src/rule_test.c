#include <stdio.h>
#include <stdlib.h>
#include "game_rules.h"
#include "types.h"

int main () {
Rules* rule = NULL;
STATUS st=1;

printf("\nWELCOME TO THE RULE TEST MODULE\n");

rule = RulesCreate();

printf("\n A new rule has been created");

printf("\n The function RandomRule can randomly choose a rule");

RandomRule(rule);

if (st==0) {printf ("\n ERROR RANDOM RULE");} else {printf("\nRANDOM RULE SUCCESS");}


printf("\n The function RulesStart links all future rules to the current game");

printf("\n so that the desired changes can be implemented");

printf("\n Now, the rule can be destroyed");

st = RulesDestroy(rule);

if (st==0) {printf ("\n Error destroying the rule \n");} else {printf("\nRule destroyed sucessfully\n");}

return 0;
}
