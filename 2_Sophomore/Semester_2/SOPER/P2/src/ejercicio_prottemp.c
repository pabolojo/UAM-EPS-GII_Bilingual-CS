/**
* @brief Programa en el que los procesos hijos realizan unas sumas y el padre los espera.
* @file ejercicio_prottemp.c
* @date 16-03-2020
* @copyright Grupo 2292
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static volatile sig_atomic_t sigusr2f = 0, sigalarmf = 0, sigtermf = 0;
/**
* @brief Manejador de la señal SIGALRM
* */
void manejador_SIGALRM(int sig) {
  sigalarmf = 1;
}

/**
* @brief Manejador de la señal SIGUSR2
* */
void manejador_SIGUSR2(int sig) {
  sigusr2f++;
}

/**
* @brief Manejador de la señal SIGTERM
* */
void manejador_SIGTERM(int sig) {
  sigtermf = 1;
}

/**
* @brief Función que suma los números entre el 1 y 10/pid del proceso.
* */
void suma_numeros(){

  pid_t pid = getpid();
  int i;
  long long suma = 0;

  for(i = 1; i <= (pid/10); i++){
    suma += i;
  }
  printf("Mi PID es %d, y el resultado de mi suma %lld\n", pid, suma);

  return;
}

/**
* @brief Función principal que crea un número determinado de hijos. El padre espera un determinado tiempo,
* envía una señal a los hijos y los espera. Los hijos realizan una función y envían una señal al padre.
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main (int argc, char *argv[]){
  int i;
  int n,s;
  pid_t pid = 1, ppid;
  struct sigaction act;

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


  ppid = getpid();

  pid_t procids[n];

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
    alarm(s);
    sigset_t mask;
    sigemptyset(&mask);

    while(!sigalarmf){
      sigsuspend(&mask);
    }

    for(i = 0; i < n; i++){
      kill(procids[i], SIGTERM);
    }
    for(i = 0; i < n; i++){
      wait(NULL);
    }
    printf("Se han recibido %d señales de los hijos\n", sigusr2f);
    printf("Finalizado Padre\n");
    exit(EXIT_SUCCESS);
  }
  else if(pid == 0){
    suma_numeros();
    kill(ppid, SIGUSR2);

    sigset_t mask;
    sigemptyset(&mask);

    while(!sigtermf){
      sigsuspend(&mask);
    }

    printf("Finalizado hijo con pid = %d\n", getpid());
  }

  exit(EXIT_SUCCESS);
}

