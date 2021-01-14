/** 
 * @brief Implementación de las funciones del ejercicio de pipes
 * @file funciones_pipes.c
 * @date 24-02-2020 
 * @copyright Grupo 2292
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "funciones_pipes.h"

/**
 * @brief Función que manda un mensaje a través del descriptor de fichero recibido
 * @param fd descriptor de fichero desde el que se envía el mensaje
 * @param message mensaje que se desea enviar
 * @return número de bytes escritos o -1 si hay un error
 * */
int SendMessage(int fd, char * message){

	if(message==NULL){
		return -1;
	}
	ssize_t nbytes = write(fd, message, strlen(message) + 1);
	if(nbytes == -1){
		perror("write");
		return -1;
	}
	return nbytes; 
}

/**
 * @brief Función que lee un mensaje a través del descriptor de fichero recibido
 * @param fd descriptor de fichero desde el que se debe leer el mensaje
 * @param message parámetro en el que se guarda el mensaje recibido
 * @return número de bytes leidos o -1 si hay un error
 * */
int ReadMessage(int fd, char * message){
	size_t nbytes = 0;

	do{
		nbytes = read(fd, message, 2*sizeof(message));
		if(nbytes == -1){
			return -1;
		}
	} while(nbytes != 0);
	return nbytes;
}

/**
 * @brief Función que abre un descriptor de fichero con el nombre filename y escribe el mensaje pasado como parámetro
 * @param message mensaje que se desea escribir
 * @param filename nombre del fichero en el que se desea escribir
 * @return número de bytes escritos o -1 si hay un error
 * */
int WriteOnFile(char * message, char * filename){
	ssize_t total_size_written = 0;
	int file;
	size_t target_size;
	if(message==NULL || filename==NULL){
		perror(" No mesage or file");
		return -1;
	}
	/*Apertura del descriptor de fichero donde vamos a escribir*/
	file = open ( filename , O_CREAT | O_TRUNC | O_WRONLY , S_IRUSR | S_IWUSR| S_IRGRP | S_IWGRP );
	if (file == -1){
		perror(" open ");
		return -1;
	}

	/*Escritura del mensaje en el desrciptor de fichero*/

	target_size = sizeof(char)* strlen(message);

	do{
		ssize_t size_written = write(file , message + total_size_written ,target_size - total_size_written);
		if(size_written == -1){
			perror(" write ");
			return -1;
		}
		total_size_written += size_written;
	}while(total_size_written != target_size);

	/*Cierre del descriptor de fichero*/
	close(file);

	return total_size_written;
}
