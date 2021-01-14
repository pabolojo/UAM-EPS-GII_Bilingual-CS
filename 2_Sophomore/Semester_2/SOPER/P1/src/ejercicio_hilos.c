/**
 * @brief Programa el cual crea tantos hilos como el número pasado de argumento, los cuales esperan un número de segundos aleatorio
 * entre 0 y 10, y a continuación calculan el cubo del número del hilo creado.
 * @file ejercicio_hilos.c
 * @date 24-02-2020
 * @copyright Grupo 2292
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "funciones_hilos.h"

/**
 * @brief Función principal que crea los hilose imprime por pantalla los resultados
 * @param argc número de argumentos de entrada
 * @param argv argumentos de entrada escritos por el usuario
 * @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE si ha habido un error
 * */
int main(int argc, char *argv[]) {

  if(argc != 2){
    printf("Un argumento con el numero de hilos\n");
    exit(EXIT_FAILURE);
  }

  int num_hilos = atoi(argv[1]);
  if(num_hilos <= 0){
    printf("Numero positivo\n");
    exit(EXIT_FAILURE);
  }

  int error;
  pthread_t hilos[num_hilos];
  Params params[num_hilos];

  for(int i = 0; i < num_hilos; i++){

    params[i].random = rand() % 11;
    params[i].x = i + 1;

    error = pthread_create(&hilos[i], NULL, CalculateCube, &params[i]);
  	if(error != 0){
  		fprintf(stderr, "pthread_create: %s\n", strerror(error));
  		exit(EXIT_FAILURE);
  	}

  }

  for(int i = 0; i < num_hilos; i++){

    void *result;

    error = pthread_join(hilos[i], &result);
  	if(error != 0){
  		fprintf(stderr, "pthread_join: %s\n", strerror(error));
  		exit(EXIT_FAILURE);
  	}
    printf("Hilo %d resultado = %d\n", i + 1, *(int*)result);
    free(result);
  }

	printf("El programa %s termino correctamente \n", argv[0]);
	exit(EXIT_SUCCESS);
}

