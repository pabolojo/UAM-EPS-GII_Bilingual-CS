/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Julia Simon
 * @version 1.0
 * @date 30-03-2018
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /*!< Tamano maximo de palabra para los nombres */
#define NO_ID -1       /*!< Constante para cuando no hay ID definido  */

/**
* @brief deifinicion del tipo de id
*/
typedef long Id;

/**
* @brief deifinicion del tipo de BOOL
*/
typedef enum {
  FALSE, TRUE
} BOOL;

/**
* @brief deifinicion del tipo status, OK o ERROR
*/
typedef enum {
  ERROR, OK
} STATUS;

/**
* @brief lista de direcciones de desplazamiento
*/
typedef enum {
  N, S, E, W
} DIRECTION;

/**
* @brief deifinicion del tipo de la puerta de los links
*/
typedef enum{
  OPENNED, CLOSED
} DOOR;

#endif
