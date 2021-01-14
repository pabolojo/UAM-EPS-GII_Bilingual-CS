/** 
* @brief Archivos header para las funciones del ejercicio 12
* @file funciones_prottemp_mejorado.h
* @date 24-02-2020
* @copyright Grupo 2292
*/

#ifndef FUNCIONES_PROTTEMP_MEJORADO_H
#define FUNCIONES_PROTTEMP_MEJORADO_H

#define SEM_NAME_A "/sem_2"
#define FILENAME "datos.txt"

long long suma_numeros();
void escribir_inicio();
void escribir_resultado(sem_t *sem1,long long suma);
double comprobar_resultado(sem_t *sem1, long long * resultado);

#endif

