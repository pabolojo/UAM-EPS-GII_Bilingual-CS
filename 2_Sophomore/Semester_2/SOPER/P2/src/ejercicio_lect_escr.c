/**
* @brief Programa en el que los procesos hijos realizan lecturas y el proceso padre escritura. Al llegarle al padre SIGINT acaba con todos los hijos, los recoge, libera recursos y acaba.
* @file ejercicio_lect_escr.c
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


static volatile sig_atomic_t sigtermf = 0, sigintf = 0;

#define SEM_NAME_A "/sem_2"
#define SEM_NAME_B "/sem_1"
#define SEM_NAME_C "/sem_l"

#define SECS 1
#define N_READ 10

/**
* @brief Manejador de la señal SIGTERM.
* */
void manejador_SIGTERM(int sig) {
  sigtermf = 1;
}

/**
* @brief Manejador de la señal SIGINT.
* */
void manejador_SIGINT(int sig) {
  sigintf = 1;
}

/**
* @brief Función principal que se encarga de crear a los hijos, y que dependiendo de los parámetros SECS y N_READ se encarga de realizar las lecturas/escrituras hasta que le llega SIGINT al padre.
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main (int argc, char *argv[]){
  int i;
  pid_t pid = 1;
  struct sigaction act;
  sem_t *sem1 = NULL;
  sem_t *sem2 = NULL;
  sem_t *semlect = NULL;

  if(SECS < 0 || N_READ <= 0){
    printf("Error: es necesario introducir dos parámetros positivos: SECS N_READ\n");
    exit(EXIT_FAILURE);
  }

  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;
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

  if ((sem2 = sem_open(SEM_NAME_B, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_NAME_B);

  if ((semlect = sem_open(SEM_NAME_C, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_NAME_C);

  pid_t *procids = (pid_t *)malloc(N_READ*sizeof(pid_t));
  if(procids==NULL){
    perror("Proces ids");
    exit(EXIT_FAILURE);
  }
  /*Bucle que crea los hijos*/
  for(i = 0; i < N_READ && pid != 0; i++){
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

    act.sa_handler = manejador_SIGINT;
    if (sigaction(SIGINT, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }

    while(!sigintf){
      sem_wait(sem2);

      printf("W-INI %d\n", getpid());
      sleep(1);
      printf("W-FIN %d\n", getpid());

      sem_post(sem2);

      sleep(SECS);
    }

    for(i = 0; i < N_READ; i++){
      kill(procids[i], SIGTERM);
    }
    for(i = 0; i < N_READ; i++){
      wait(NULL);
    }
    printf("Finalizado Padre\n");
  }

  else if(pid == 0){
    while(!sigtermf){
      int value = 0;
      sem_wait(sem1);
      sem_post(semlect);
      sem_getvalue(semlect, &value);
      if(value == 1){
        sem_wait(sem2);
      }
      sem_post(sem1);

      printf("R-INI %d\n", getpid());
      sleep(1);
      printf("R-FIN %d\n", getpid());

      sem_wait(sem1);
      sem_wait(semlect);
      sem_getvalue(semlect, &value);
      if(value == 0){
        sem_post(sem2);
      }
      sem_post(sem1);

      sleep(SECS);
    }
  }

  sem_close(sem1);
  sem_close(sem2);
  sem_close(semlect);
  free(procids);

  exit(EXIT_SUCCESS);
}

