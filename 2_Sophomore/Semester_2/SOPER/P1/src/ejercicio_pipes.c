/** 
 * @brief Programa en el que el proceso padre crea un proceso hijo y este a su vez genera un número aleatorio que enviará al
 * padre a través de un pipe. El padre creará a continuación otro hijo y le enviará el número recibido a través de otro pipe.
 * Por último, el segundo hijo deberá imprimir el número recibido en el fichero numero_leido.txt
 * @file ejercicio_pipes.c
 * @date 24-02-2020 
 * @copyright Grupo 2292
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "funciones_pipes.h"

/**
 * @brief Función principal que crea ambos pipes e hijos y llama a funciones del archivo 
 * funciones_pipes.c para comunicar los procesos y escribir el valor en el fichero correspondiente
 * @param argc número de argumentos de entrada
 * @param argv argumentos de entrada escritos por el usuario
 * @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE si ha habido algun error
 * */

int main(int argc, char *argv[]) {
	int fd1[2];
	int value;

	/*Crea el 1º pipe*/
	int pipe_status1 = pipe(fd1);
	if(pipe_status1 == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	/*Crea el 1º proceso hijo*/
	pid_t pid1=fork();
	if(pid1<0){
		perror("fork");
		exit(EXIT_FAILURE);
	}else if(pid1==0){

		char message[90];

		/* Cierre del descriptor de entrada en el 1º hijo*/
		close(fd1[0]);

		/*Creación del numero aleatorio*/
		srand(time(NULL));
		int n=rand();
		sprintf(message,"%d", n);

		/*Envío del mensaje al padre*/
		value=SendMessage(fd1[1], message);
		if(value==-1){
			exit(EXIT_FAILURE);
		}

		printf("El número generado es: %d\n", n);
		exit(EXIT_SUCCESS);

	}else{
		char string[90];

		/* Cierre del descriptor de salida en el padre*/
		close(fd1[1]);

		/* Lectura del mensaje enviado por el primer hijo*/
		value=ReadMessage(fd1[0], string);
		if(value==-1){
			exit(EXIT_FAILURE);
		}
	
		wait(NULL);

		/*Crea el 2º pipe*/
		int fd2[2];
		int pipe_status2 = pipe(fd2);
		if(pipe_status2 == -1){
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		/*Crea el 2º proceso hijo*/
		pid_t pid2=fork();

		if(pid2<0){
			perror("fork");
			exit(EXIT_FAILURE);
		}else if(pid2==0){

			char message[90];
			/* Cierre del descriptor de salida en el 2º hijo*/
			close(fd2[1]);

			/* Lectura del mensaje enviado por el padre*/
			value=ReadMessage(fd2[0], message);
			if(value==-1){
				exit(EXIT_FAILURE);
			}

			/*Escritura del mensaje en el desrciptor de fichero*/
			value=WriteOnFile(message, "numero_leido.txt");
			if(value==-1){
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);

		}else{

			/* Cierre del descriptor de entrada en el padre*/
			close(fd2[0]);

			/*Envío del mensaje al segundo hijo*/
			value=SendMessage(fd2[1], string);
			if(value==-1){
				exit(EXIT_FAILURE);
			}

			close(fd2[1]);

			wait(NULL);
			exit(EXIT_SUCCESS);
		}
			
	}
}
