/**
* @brief Implementación de las funciones de la cola
* @file cola_prod_consum.c
* @date 15-04-2020
* @copyright Grupo 2292
*/

#include "cola_prod_consum.h"

/**
* @brief Función para introducir elementos en la cola
* @param cola puntero a cola
* @param valor valor a insertar en la cola
* */
void cola_producir(Cola *cola, int valor) {
  if(!cola) {
    return;
  }
  if ((cola->ultimo == 0 && cola->primero == CAPACIDAD-1) || (cola->primero == (cola->ultimo-1)%(CAPACIDAD-1))) {
    printf("\nCola llena");
    return;
  }
  else if(cola->ultimo == -1) {
    cola->ultimo = cola->primero = 0;
    cola->elem[cola->primero] = valor;
  }
  else if(cola->primero == CAPACIDAD-1 && cola->ultimo != 0) {
    cola->primero = 0;
    cola->elem[cola->primero] = valor;
  }
  else {
    cola->primero++;
    cola->elem[cola->primero] = valor;
  }
}

/**
* @brief Función para sacar elementos de la cola
* @param cola puntero a cola
* @return entero sacado de la cola
* */
int cola_consumir(Cola *cola) {
  if(!cola) {
    return INT_MIN;
  }
  if (cola->ultimo == -1) {
    printf("\nCola Vacía");
    return INT_MIN;
  }

  int data = cola->elem[cola->ultimo];
  cola->elem[cola->ultimo] = -1;
  if (cola->ultimo == cola->primero) {
    cola->ultimo = -1;
    cola->primero = -1;
  }
  else if (cola->ultimo == CAPACIDAD-1)
  cola->ultimo = 0;
  else
  cola->ultimo++;

  return data;
}

/**
* @brief Función para inicializar la cola
* @param cola puntero a cola
* */
void cola_init(Cola *cola) {
  if(!cola) {
    return;
  }
  for(int i = 0; i < CAPACIDAD; i++) {
    cola->elem[i] = -1;
  }
  cola->primero = -1;
  cola->ultimo = -1;

}

