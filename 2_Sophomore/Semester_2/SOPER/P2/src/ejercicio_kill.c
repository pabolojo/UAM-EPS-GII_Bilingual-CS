/**
* @brief Programa reproduce de forma limitada la funcionalidad del comando de shell kill con un formato similar:
* ejercicio_kill <signal> <pid>
* @file ejercicio_kill.c
* @date 16-03-2020
* @copyright Grupo 2292
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief Función principal que llama a la función kill() para mandar una señal a un proceso
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE si ha habido un error
* */
int main(int argc, char** argv){

  int pid, sig;
  if(argc != 3){
    printf("<SIG> <PID>\n");
    exit(EXIT_FAILURE);
  }
  if(!(pid = atoi(argv[2]))){
    printf("Error argumentos\n");
    exit(EXIT_FAILURE);
  }
  if(!(sig = atoi(argv[1]))){
    printf("Error argumentos\n");
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strerror(kill(pid, sig)));
  return 0;
}

