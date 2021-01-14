/**
* @brief Archivos header para las funciones cola_prod_consum.c
* @file cola_prod_consum.h
* @date 15-04-2020
* @copyright Grupo 2292
*/

#ifndef COLA_PROD_CONSUM_H
#define COLA_PROD_CONSUM_H

#include <stdio.h>
#include <limits.h>
#define CAPACIDAD 100

typedef struct _Cola {
  int elem[100];
  int primero;
  int ultimo;
} Cola;

void cola_init(Cola *cola);
void cola_producir(Cola *cola, int valor);
int cola_consumir(Cola *cola);

#endif

