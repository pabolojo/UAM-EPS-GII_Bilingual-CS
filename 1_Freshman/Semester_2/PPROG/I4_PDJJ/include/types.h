/**
 * @brief It defines common types
 *
 * @file types.h
 * @version 2.0
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H
/**
 * @brief macro that defines word size
 *
 */
#define WORD_SIZE 1000
/**
 * @brief macro that defines NO ID
 *
 */
#define NO_ID -1
/**
 * @brief definition of structure id
 *
 */
typedef long Id;
/**
 * @brief defines STATUS
 *
 */
typedef enum {
  FALSE, TRUE
} BOOL;
/**
 * @brief defines BOOL
 *
 */
typedef enum {
  ERROR, OK
} STATUS;

/**
 * @brief defines directions
 *
 */
typedef enum {
  N, S, E, W
} DIRECTION;

#endif

