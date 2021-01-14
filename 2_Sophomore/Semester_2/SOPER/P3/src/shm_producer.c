/**
* @brief Programa de productor con memoria compartida, donde con la ayuda de una cola en forma de memoria compartida
* se ha implementado el problema del productor consumidor
* @file shm_producer.c
* @date 15-04-2020
* @copyright Grupo 2292
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

#include "cola_prod_consum.h"

#define SHM_NAME "/shm_prod_cons"
#define SEM_SINC "/sem_sinc"
#define SEM_MUTEX "/sem_mutex"
#define SEM_VACIO "/sem_vacio"
#define SEM_LLENO "/sem_lleno"

/**
* @brief Función principal que realiza lo descrito en la cabecera.
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main(int argc, char **argv) {

  int N;
  int mode;
  sem_t *sem_sinc = NULL;
  sem_t *sem_mutex = NULL;
  sem_t *sem_vacio = NULL;
  sem_t *sem_lleno = NULL;

  if(argc != 3) {
    printf("./shm_producer <N> <0 o 1>\n");
    exit(EXIT_FAILURE);
  }
  N = atoi(argv[1]);

  if(N < 1 || N > CAPACIDAD) {
    printf("0 < N < %d\n", CAPACIDAD);
    exit(EXIT_FAILURE);
  }

  mode = atoi(argv[2]);

  if(mode != 0 && mode != 1) {
    printf("<0 o 1>\n");
    exit(EXIT_FAILURE);
  }

  if ((sem_sinc = sem_open(SEM_SINC, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }

  if ((sem_mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }

  if ((sem_vacio = sem_open(SEM_VACIO, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, CAPACIDAD)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }

  if ((sem_lleno = sem_open(SEM_LLENO, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }

  int fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);

  if (fd_shm == -1) {
    fprintf(stderr, "Error creating the shared memory segment\n");
    return EXIT_FAILURE;
  }

  if (ftruncate(fd_shm, sizeof(Cola)) == -1) {
    fprintf(stderr, "Error resizing the shared memory segment\n");
    shm_unlink(SHM_NAME);
    return EXIT_FAILURE;
  }

  Cola *cola = mmap(NULL, sizeof(*cola), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
  close(fd_shm);

  if (cola == MAP_FAILED) {
    fprintf(stderr, "Error mapping the shared memory segment\n");
    shm_unlink(SHM_NAME);
    return EXIT_FAILURE;
  }

  cola_init(cola);

  printf("Ejecute consumidor\n");

  sem_wait(sem_sinc);
  sem_close(sem_sinc);

  for(int i = 0; i < N + 1; i++) {
    sem_wait(sem_vacio);

    sem_wait(sem_mutex);
    if(i == N) {
      cola_producir(cola, -1);
    }
    else if(mode == 0) {
      cola_producir(cola, rand() % 10);
    }
    else{
      cola_producir(cola, i % 10);
    }
    sem_post(sem_mutex);

    sem_post(sem_lleno);
  }



  munmap(cola, sizeof(*cola));
  sem_close(sem_mutex);
  sem_close(sem_vacio);
  sem_close(sem_lleno);

  return EXIT_SUCCESS;
}

