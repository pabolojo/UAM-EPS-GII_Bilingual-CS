/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @version 3.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include "command.h"
/**
 * @brief It defines the lenght of cmd
 */
#define CMD_LENGHT 30
/**
 * @brief It defines the number of cmd
 */
#define N_CMD 19
/**
 * @brief it defines the commands that can be used in the game
 */
char
*cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Next", "Back","Pick","Drop","Roll","Left","Right", "Up", "Down", "Move", "Inspect", "Open", "Turnon","Turnoff","Save","Load"};
/**
 * @brief it defines the commands that can be used in the game
 */
char *short_cmd_to_str[N_CMD] = {"","","e","n","b","p","d","rl","l","r","u","dw","m","i","o","to","tf","s","ld"};

T_Command
/**
 * @brief it gives the indication of what to do when receiving a command
 */
get_user_input()
{
T_Command cmd = NO_CMD;char
input[CMD_LENGHT] = "";int i=UNKNOWN
- NO_CMD + 1;

if (scanf("%s", input) > 0){
cmd = UNKNOWN;while(cmd == UNKNOWN && i < N_CMD){
  if (!strcasecmp(
input,short_cmd_to_str[i]
) || !strcasecmp(input,
cmd_to_str[i])){cmd = i + NO_CMD;}
  else
    {
	i++;
}
}
}
  return cmd;
}

