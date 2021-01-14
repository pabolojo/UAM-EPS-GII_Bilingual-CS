/** 
 * @brief Programa en el cuál el proceso padre genera un proceso hijo, que a su vez generará otro hijo, y ası́ hasta llegar
 * a NUM_PROC procesos en total.
 * @file ejercicio_arbol.c
 * @date 24-02-2020 
 * @copyright Grupo 2292
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define NUM_PROC 3

/**
 * @brief Función principal que crea el arbol de procesos ya descrito 
 * @param argc número de argumentos de entrada
 * @param argv argumentos de entrada escritos por el usuario
 * @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE si ha habido un problema en la creación del proceso hijo
 * */
int main (int argc, char *argv[]){
	int i;
	pid_t pid;
	for(i=0; i<NUM_PROC; i++){
		pid=fork();
		if(pid<0){
			perror("fork");
			exit(EXIT_FAILURE);
		}else if(pid>0){
			wait(NULL);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}

