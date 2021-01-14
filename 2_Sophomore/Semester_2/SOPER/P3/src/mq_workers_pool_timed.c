/**
* @brief Este programa instanciará N trabajadores como procesos hijo y esperará una señal SIGUSR2 que provocará la finalización
* de los procesos hijo mediante una señal SIGTERM.
* Cada proceso hijo (cada trabajador), inicializará su contador a 0, leerá el siguiente mensaje de la cola.
* Si el mensaje es de finalización, enviará una señal SIGUSR2 al proceso padre.
* Si no, incrementará su contador con el número de apariciones del carácter a buscar.
* Al recibir la señal SIGTERM , mostrará una estadı́stica que indique el número de mensajes procesados,
* y el valor de su contador del carácter a buscar.
*
* @file mq_workers_pool.c
* @date 15-04-2020
* @copyright Grupo 2292
*/

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#define MAX_MESSAGES 10
#define MAX_MESSAGE_SIZE 2049 //2KB+1

static volatile sig_atomic_t sigusr2f = 0, sigtermf = 0;

/**
* @brief Manejador de la señal SIGTERM
* */
void manejador_SIGTERM(int sig) {
  sigtermf = 1;
}

/**
* @brief Manejador de la señal SIGUSR2
* */
void manejador_SIGUSR2(int sig) {
  sigusr2f = 1;
}

/**
* @brief Función principal que realiza lo descrito en la cabecera.
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main(int argc, char *argv[]) {

  int trabajadores;

  int pid;

  struct sigaction act;

  if (argc != 4) {

    fprintf(stderr, "Uso: %s <n_trabajadores> </cola> <caracter>\n", argv[0]);
    return EXIT_FAILURE;

  }

  trabajadores = atoi(argv[1]);

  if (trabajadores < 1 || trabajadores > 10) {

    fprintf(stderr, "Trabajadores 1-10\n");
    return EXIT_FAILURE;
  }

  struct mq_attr attributes = {

    .mq_flags = 0,

    .mq_maxmsg = MAX_MESSAGES,

    .mq_curmsgs = 0,

    .mq_msgsize = MAX_MESSAGE_SIZE};

    mqd_t queue = mq_open(argv[2], O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &attributes);

    if (queue == (mqd_t)-1) {

      fprintf(stderr, "Error opening the queue\n");
      return EXIT_FAILURE;
    }

    mq_unlink(argv[2]);

    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;
    act.sa_handler = manejador_SIGUSR2;
    if (sigaction(SIGUSR2, &act, NULL) < 0) {
      mq_close(queue);
      perror("sigaction");
      exit(EXIT_FAILURE);
    }
    act.sa_handler = manejador_SIGTERM;
    if (sigaction(SIGTERM, &act, NULL) < 0) {
      mq_close(queue);
      perror("sigaction");
      exit(EXIT_FAILURE);
    }

    int procids[trabajadores];
    int ppid = getpid();

    for (int i = 0; i < trabajadores; i++) {
      pid = fork();
      if (!pid) {
        break;
      }
      else if (pid < 0)  {
        mq_close(queue);
        fprintf(stderr, "Error fork\n");
        return EXIT_FAILURE;
      }
      else {
        procids[i] = pid;
      }
    }

    if (!pid) {
      int contador = 0;
      int mensajes = 0;
      char msg[MAX_MESSAGE_SIZE];
      struct timespec req;

      while (1) {

        if(sigtermf){
          printf("Hijo <%d>: %d mensajes procesados, '%c' contado %d veces\n", getpid(), mensajes, argv[3][0], contador);
          mq_close(queue);
          exit(EXIT_SUCCESS);
        }

        clock_gettime(CLOCK_REALTIME, &req);
        req.tv_nsec += 100000000; //1 ms

        for(int i = 0; i < MAX_MESSAGE_SIZE; i++) {
          msg[i] = 0;
        }
        int n_bytes = mq_timedreceive(queue, (char *)&msg, sizeof(msg), NULL, &req);
        if (n_bytes == -1) {
          mq_close(queue);
          if (errno == EINTR) {
            printf("Hijo <%d>: %d mensajes procesados, '%c' contado %d veces\n", getpid(), mensajes, argv[3][0], contador);
            exit(EXIT_SUCCESS);
          }else if(errno == ETIMEDOUT){
            printf("Hijo <%d>: %d mensajes procesados, '%c' contado %d veces. No se me necesita más\n", getpid(), mensajes, argv[3][0], contador);
            exit(EXIT_SUCCESS);
          }else{
            fprintf(stderr, "Error receiving message\n");
            exit(EXIT_FAILURE);
          }
        }
        printf("Hijo con pid: %d ha leído un mensaje\n", getpid());
        if (strcmp(msg, "He acabado\0") == 0) {
          printf("Acabando...\n");
          kill(ppid, SIGUSR2);
        }else {
          mensajes++;
          for (int i = 0; msg[i] != 0 && i < MAX_MESSAGE_SIZE; i++) {
            if (msg[i] == argv[3][0]) {
              contador++;
            }
          }
        }
      }
    }

    sigset_t mask;
    sigemptyset(&mask);

    while (!sigusr2f) {
      sigsuspend(&mask);
    }

    for (int i = 0; i < trabajadores; i++) {
      kill(procids[i], SIGTERM);
    }

    for (int i = 0; i < trabajadores; i++) {
      printf("Esperando\n");
      wait(NULL);
    }

    mq_close(queue);
    return EXIT_SUCCESS;
  }

