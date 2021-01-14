/**
* @brief Programa en el que los procesos hijos realizan unas sumas y acumulan su resultado en un fichero. El padre los espera y lee el resultado.
* @file ejercicio_prottemp_mejorado.c
* @date 16-03-2020
* @copyright Grupo 2292
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "funciones_prottemp_mejorado.h"

static volatile sig_atomic_t sigusr2f = 0, sigalarmf = 0, sigtermf = 0;


#define SEM_NAME_A "/sem_2"
#define FILENAME "datos.txt"

/**
* @brief Manejador de la señal SIGALRM.
* */
void manejador_SIGALRM(int sig) {
  sigalarmf = 1;
}

/**
* @brief Manejador de la señal SIGUSR2.
* */
void manejador_SIGUSR2(int sig) {
  sigusr2f = 1;
}

/**
* @brief Manejador de la señal SIGTERM.
* */
void manejador_SIGTERM(int sig) {
  sigtermf = 1;
}

/**
* @brief Función principal que
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main (int argc, char *argv[]){
  int i;
  int n,s;
  pid_t pid = 1, ppid;
  struct sigaction act;
  sem_t *sem1 = NULL;

  if(argc!=3){
    printf("Error: es necesario introducir dos parámetros: <N> <T>\n");
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);
  s = atoi(argv[2]);

  if(n <= 0 || s <= 0){
    printf("Error: es necesario introducir dos parámetros positivos: <N> <T>\n");
    exit(EXIT_FAILURE);
  }

  act.sa_handler = manejador_SIGALRM;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;
  if (sigaction(SIGALRM, &act, NULL) < 0) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }
  act.sa_handler = manejador_SIGUSR2;
  if (sigaction(SIGUSR2, &act, NULL) < 0) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }
  act.sa_handler = manejador_SIGTERM;
  if (sigaction(SIGTERM, &act, NULL) < 0) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  if ((sem1 = sem_open(SEM_NAME_A, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_NAME_A);

  /*Escribe 0 0 en el fichero datos.txt*/
  escribir_inicio();

  ppid = getpid();

  pid_t *procids = (pid_t *)malloc(n*sizeof(pid_t));
  if(procids==NULL){
    perror("Proces ids");
    exit(EXIT_FAILURE);
  }

  /*Bucle que crea los hijos*/
  for(i = 0; i < n && pid != 0; i++){
    pid = fork();
    if(pid < 0){
      perror("fork");
      exit(EXIT_FAILURE);
    } else if(pid > 0){
      procids[i] = pid;
    }
  }

  /*Dependiendo de si es padre o hijo el proceso que llega a aqui, hace lo primero o lo segundo*/
  if(pid > 0){
    long long resultado;
    int procesos;

    alarm(s);
    sigset_t mask;
    sigemptyset(&mask);

    while(!sigalarmf){
      sigsuspend(&mask);
      if(sigusr2f==1){
        sigusr2f = 0;
        procesos = comprobar_resultado(sem1, &resultado);
        if(procesos==n){
          printf("Han acabado todos, resultado: %lld \n", resultado);
          break;
        }
      }
    }

    if(sigalarmf==1){
      printf("Falta trabajo\n");
    }

    for(i = 0; i < n; i++){
      kill(procids[i], SIGTERM);
    }

    for(i = 0; i < n; i++){
      wait(NULL);
    }

    printf("Finalizado Padre\n");

  }
  else if(pid == 0){
    long long resultado;
    resultado = suma_numeros();

    escribir_resultado(sem1, resultado);

    kill(ppid, SIGUSR2);

    sigset_t mask;
    sigemptyset(&mask);

    while(!sigtermf){
      sigsuspend(&mask);
    }

    printf("Finalizado hijo con pid = %d\n", getpid());
  }
  sem_close(sem1);
  free(procids);
  exit(EXIT_SUCCESS);
}

