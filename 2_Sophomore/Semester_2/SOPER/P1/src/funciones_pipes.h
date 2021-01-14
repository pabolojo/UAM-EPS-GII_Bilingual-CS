/** 
 * @brief Archivos header para las funciones del ejercicio de pipes
 * @file funciones_pipes.h
 * @date 24-02-2020 
 * @copyright Grupo 2292
 */

#ifndef FUNCIONES_PIPES_H
#define FUNCIONES_PIPES_H

int WriteOnFile(char * message, char * filename);
int SendMessage(int fd, char * message);
int ReadMessage(int fd, char * message);

#endif
