/** 
 * @brief Archivos header para las funciones del ejercicio de hilos
 * @file funciones_hilos.h
 * @date 24-02-2020 
 * @copyright Grupo 2292
 */
#ifndef FUNCIONES_HILOS_H
#define FUNCIONES_HILOS_H

typedef struct _Params{
  int random;
  int x;
} Params;

void * CalculateCube(void * arg);

#endif
