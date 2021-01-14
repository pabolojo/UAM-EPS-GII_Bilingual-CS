/**
* @brief Programa de consumidor con memoria compartida, donde con la ayuda de una cola en forma de memoria compartida
* se ha implementado el problema del productor consumidor
* @file shm_consumer.c
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
* @param void nada
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main(void) {

  sem_t *sem_sinc = NULL;
  sem_t *sem_mutex = NULL;
  sem_t *sem_vacio = NULL;
  sem_t *sem_lleno = NULL;

  if ((sem_sinc = sem_open(SEM_SINC, O_EXCL, S_IRUSR | S_IWUSR)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_SINC);

  if ((sem_mutex = sem_open(SEM_MUTEX, O_EXCL, S_IRUSR | S_IWUSR)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_MUTEX);

  if ((sem_vacio = sem_open(SEM_VACIO, O_EXCL, S_IRUSR | S_IWUSR)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_VACIO);

  if ((sem_lleno = sem_open(SEM_LLENO, O_EXCL, S_IRUSR | S_IWUSR)) == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  sem_unlink(SEM_LLENO);

  int fd_shm = shm_open(SHM_NAME, O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);

  if (fd_shm == -1) {
    fprintf(stderr, "Error opening the shared memory segment\n");
    return EXIT_FAILURE;
  }
  shm_unlink(SHM_NAME);

  Cola *cola = mmap(NULL, sizeof(*cola), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
  close(fd_shm);

  if (cola == MAP_FAILED) {
    fprintf(stderr, "Error mapping the shared memory segment\n");
    return EXIT_FAILURE;
  }

  sem_post(sem_sinc);
  sem_close(sem_sinc);

  int elem = 0;
  int histograma[10] = {0};

  while(elem != -1) {
    sem_wait(sem_lleno);

    sem_wait(sem_mutex);
    elem = cola_consumir(cola);
    sem_post(sem_mutex);

    sem_post(sem_vacio);

    if(elem != -1) {
      histograma[elem]++;
    }
  }

  for(int i = 0; i < 10; i++) {
    printf("Número %d recibido %d veces\n", i, histograma[i]);
  }

  munmap(cola, sizeof(*cola));
  sem_close(sem_sinc);
  sem_close(sem_mutex);
  sem_close(sem_vacio);
  sem_close(sem_lleno);

  return EXIT_SUCCESS;
}

