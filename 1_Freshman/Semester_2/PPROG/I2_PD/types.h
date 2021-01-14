/**
 * @brief It defines common types
 *
 * @file types.h
 * @version 1.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */
/*this module defines all the possible answers thatbthe functions of teh proyect can return, it is very important to include this moduele in order to hace a proyect that works properly*/

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
  ERROR, OK
} STATUS;

typedef enum {
  N, S, E, W
} DIRECTION;

#endif

