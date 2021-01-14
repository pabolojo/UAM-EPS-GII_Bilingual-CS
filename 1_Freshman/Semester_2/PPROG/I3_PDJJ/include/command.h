/**
 * @brief It defines the module of command 
 *
 * @file command.h
 * @version 2.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */


#ifndef COMMAND_H
#define COMMAND_H

/**
 * @brief It defines the header of command 
 */
typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  NEXT,
  BACK,
  PICK,
  DROP,
  ROLL} T_Command;
/**
 * @brief it gets the input of user 
 */
T_Command get_user_input();

#endif

