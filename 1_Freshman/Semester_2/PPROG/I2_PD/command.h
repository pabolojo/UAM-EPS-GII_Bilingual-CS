/**
 * @brief It implements the command interpreter
 *
 * @file command.h
 * @version 1.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */


#ifndef COMMAND_H
#define COMMAND_H

typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  NEXT,
  BACK,
  PICK,
  DROP,
  ROLL} T_Command;

T_Command get_user_input();

#endif

