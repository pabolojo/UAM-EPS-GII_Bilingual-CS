/** 
 * @brief Implementación de las funciones del ejercicio de hilos
 * @file funciones_hilos.c
 * @date 24-02-2020 
 * @copyright Grupo 2292
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones_hilos.h"

/**
 * @brief Función que espera un número determinado de segundos y calcula el cúbo de un número
 * @param arg argumentos de entrada con los que se realizará la función
 * @return resultado de la operaciń o NULL si hay un error
 * */

void * CalculateCube(void * arg){
 	if(!arg){
 	 	return NULL;
 	}
	Params * params = (Params *) arg;
  	int * result = (int*)malloc(sizeof(int));
  	if(!result){
    	return NULL;
  	}
  	sleep(params->random);
  	*result = params->x * params->x * params->x;

	return result;
}
