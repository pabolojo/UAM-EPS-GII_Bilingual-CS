/** 
* @brief Implementación de las funciones del ejercicio 12
* @file funciones_prottemp_mejorado.c
* @date 24-02-2020
* @copyright Grupo 2292
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "funciones_prottemp_mejorado.h"

/**
* @brief Función que suma los números entre el 1 y 10/pid del proceso.
* @return suma resultado de la suma.
* */
long long suma_numeros(){
	pid_t pid = getpid();
	int i;
	long long suma = 0;

	for(i = 1; i <= (pid/10); i++){
		suma += i;
	}
	printf("Mi PID es %d, y el resultado de mi suma %lld\n", pid, suma);
	return suma;
}

/**
* @brief Función que escribe 0 0 en el fichero indicado por FILENAME.
* */
void escribir_inicio(){
	FILE *f;
	f=fopen(FILENAME,"w");
	if(f==NULL){
		perror("file");
		exit(EXIT_FAILURE);
	}
	fprintf(f,"0\n0\n");
	fclose(f);
}

/**
* @brief Función que aumenta en 1 el primer número del fichero y reescribe la suma en el fichero indicado por FILENAME.
* @param sem1 semáforo usado para sincronizar la lectura y escritura.
* @param suma número que se ha de añadir al acumulador ya escrito en el fichero.
* */
void escribir_resultado(sem_t *sem1,long long suma){
	FILE *f;
	long long acumulador=0;
	int procesos;
	int result=0;
	int flag=0;

	do{
		flag=0;
		result=sem_wait(sem1);
		if(result==-1){
			if(errno==EINTR){
				flag=1;
			}
		}
	}while(flag);

	f=fopen(FILENAME,"r+");
	if(f==NULL){
		perror("file");
		exit(EXIT_FAILURE);
	}
	fscanf(f,"%d %lld", &procesos,&acumulador);
	fseek(f, 0, SEEK_SET);
	fprintf(f,"%d\n%lld\n", procesos+1, acumulador+suma);

	fclose(f);
	sem_post(sem1);
	return;
}
/**
* @brief Función que lee el fichero indicado por FILENAME y devuelve el número de procesos y el resultado leído.
* @param sem1 semáforo usado para sincronizar la lectura.
* @param resultado variable dónde se guarda el resultado leído.
* @return procesos el número de procesos que han escrito en el archivo.
**/
double comprobar_resultado(sem_t *sem1, long long * resultado){
	FILE *f;
	int flag=0, result=0;
	int procesos;
	do{
		flag=0;
		result=sem_wait(sem1);
		if(result==-1){
			if(errno==EINTR){
				flag=1;
			}
		}
	}while(flag);
	f=fopen(FILENAME,"r");
	if(f==NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	fscanf(f,"%d%lld", &procesos,resultado);

	fclose(f);
	sem_post(sem1);
	return procesos;
}

