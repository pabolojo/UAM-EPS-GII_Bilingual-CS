/**
 * @brief Programa que actúa como una shell sencilla, que utiliza stdin y stdout como entrada y salida, respectivamente.
 * @file ejercicio_shell_spawn.c
 * @date 24-02-2020
 * @copyright Grupo 2292
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <spawn.h>
#include <string.h>

#define MAX 100

extern char **environ;
int status;

/**
 * @brief Función principal que crea la shell descrita 
 * @param argc número de argumentos de entrada
 * @param argv argumentos de entrada escritos por el usuario
 * @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE si ha habido un error
 * */
int main(int argc, char *argv[]) {
  char buf[MAX];
  char **comando;
  pid_t pid;

  while(fgets(buf, MAX, stdin)){
    *comando = NULL;
    comando[0] = strtok(buf, " ");
    int i = 0;
    while(comando[i]){
      i++;
      comando[i] = strtok(NULL, " ");
    }

    comando[i - 1][strlen(comando[i - 1]) - 1] = 0;

    status = posix_spawnp(&pid, comando[0], NULL, NULL, comando, environ);

    waitpid(pid, &status, 0);

    if(WIFSIGNALED(status)){
      fprintf(stderr, "Terminated by signal %s\n", strerror(WTERMSIG(status)));
    }
    else{
      fprintf(stderr, "Exited with value %s\n", strerror(WEXITSTATUS(status)));
    }
  }
  exit(EXIT_SUCCESS);
}

