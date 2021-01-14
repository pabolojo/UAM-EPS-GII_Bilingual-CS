/**
* @brief Programa en el que el padre crea N hijos. Cada hijo ha de escribir en la estructura guardada en el segmento de memoria compartida.
* Tras esto, envía una señal al padre (SIGUSR1). El padre lee e imprime por pantalla los campos que ha modificado el hijo en la estructura.
* @file shm_concurrence_solved.c
* @date 15-04-2020
* @copyright Grupo 2292
*/

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_NAME "/shm_eje3"
#define SEM_NAME "/sem_espera"

#define MAX_MSG 2000

static volatile sig_atomic_t sigusr1f = 0, n=0,m=0;
/**
* @brief Función que escribe la hora actual en una string.
* @param buf puntero al lugar dónde se ha de escribir la hora
* */
static void getMilClock(char *buf) {
    int millisec;
	char aux[100];
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);
	millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }
    tm_info = localtime(&tv.tv_sec);
    strftime(aux, 10, "%H:%M:%S", tm_info);
	sprintf(buf, "%s.%03d", aux, millisec);
}

/**
* @brief Estructura que formará parte de la memoria compartida.
* */
typedef struct {
	sem_t mutex;		   /* Semáforo que controla el acceso a la estructura */
	pid_t processid;       /* Logger process PID */
	long logid;            /* Id of current log line */
	char logtext[MAX_MSG]; /* Log text */

} ClientLog;

ClientLog *shm_struct;

/**
* @brief Manejador de la señal SIGUSR1. Imprimirá lo que han escrito los hijos en la estructura.
* */
void manejador_SIGUSR1 (int sig) {
	printf ("Log %ld: Pid %d: %s\n",shm_struct->logid, shm_struct->processid, shm_struct->logtext);
	if((n*m)-1==shm_struct->logid){
		sigusr1f=1;
	}
	sem_post(&shm_struct->mutex);

}

/**
* @brief Función principal que realiza lo descrito en la cabecera.
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main(int argc, char *argv[]) {
	int i, cont=0, result=0;
	int ret = EXIT_FAILURE;
	pid_t pid = 1, ppid;
	struct sigaction act;
	int fd_shm;

	if (argc < 3) {
		fprintf(stderr,"usage: %s <n_process> <n_logs> \n",argv[0]);
		return ret;
	}

	n = atoi(argv[1]);
	m = atoi(argv[2]);

  	if(n <= 0 || m<=0){
   		printf("Error: es necesario introducir dos parámetros positivos: <N> <M>\n");
   		return ret;
 	}

 	// Definimos el manejador de la señal SIGUSR1.
 	act.sa_handler = manejador_SIGUSR1;
  	sigemptyset(&(act.sa_mask));
  	act.sa_flags = 0;
  	
  	if (sigaction(SIGUSR1, &act, NULL) < 0) {
  	  	perror("sigaction");
   		return ret;
  	}

  	// Creamos el segmento de memoria compartida.
  	fd_shm = shm_open(SHM_NAME ,O_RDWR | O_CREAT | O_EXCL ,S_IRUSR | S_IWUSR);
  	if (fd_shm==-1) {
		fprintf(stderr , " Error creating the shared memory segment \n ");
		return ret;
	}

	// Modificamos el tamaño del segmento de memoria compartida.
	if (ftruncate(fd_shm , sizeof (shm_struct)) == -1) {
		fprintf(stderr , " Error resizing the shared memory segment \n " );
		shm_unlink(SHM_NAME);
		return ret;
	}

	// Añadimos el segmento de memoria compartida al proceso.
	shm_struct = mmap(NULL , sizeof (* shm_struct) ,PROT_READ| PROT_WRITE ,MAP_SHARED ,fd_shm ,0);
	close(fd_shm);
	if (shm_struct == MAP_FAILED) {
		fprintf(stderr , " Error mapping the shared memory segment \n " );
		return ret;
	}
	shm_unlink(SHM_NAME);

	shm_struct->logid=-1;
	if (sem_init(&shm_struct->mutex,1,1) == -1) {
    	perror("sem_open");
    	return ret;
  	}

 	ppid = getpid();


	/*Bucle que crea los hijos*/
	for(i = 0; i < n && pid != 0; i++){
	 	pid = fork();
	 	if(pid < 0){
	   		perror("fork");
	    	exit(EXIT_FAILURE);
	  	}
 	}

 	if(pid > 0){ // Código que realiza el padre
 		sigset_t set_vacio;
 		sigemptyset(&set_vacio);

 		while(!sigusr1f){
 			sigsuspend(&set_vacio);
 		}

 		for(i = 0; i < n; i++){
      		wait(NULL);
      	}      	

      	sem_destroy(&shm_struct->mutex);

 	} else if(pid==0){ // Código que realizan los hijos
 		int j;
 		pid_t id = getpid();
 		char *date;
 		char *string;
 		struct timespec req;

 		srand(id);

 		date = (char *)malloc(13*sizeof(char));
 		if(date==NULL){
 		 	perror("Error inicializando Date");
 		 	munmap(shm_struct , sizeof (* shm_struct));
 			exit(EXIT_FAILURE);
 		}

 		string = (char *)malloc(50*sizeof(char));
 		if(string==NULL){
 		 	perror("Error inicializando la string del proceso hijo");
 		 	free(date);
 		 	munmap(shm_struct , sizeof (* shm_struct));
 			exit(EXIT_FAILURE);
 		}
 		req.tv_sec=0;
 		
 		for(j=0; j<m; j++){
 			// Se genera el número aleatorio.
 			req.tv_nsec=((801.0)*rand()/(RAND_MAX + 1.0)+ 100)*1000000;
 			nanosleep(&req, NULL);

 			do{
   		   		cont=0;
   		   		result=sem_wait(&shm_struct->mutex);
   		   		if(result==-1){
   		    		if(errno==EINTR){
   		       			cont=1;
   		     		}
   		   		}
   			}while(cont);

 			shm_struct->logid=shm_struct->logid+1;
 			shm_struct->processid=id;
 			getMilClock(date);
 			sprintf(string,"Soy el proceso %d a las %s", id, date);
 			strcpy(shm_struct->logtext,string);

 			kill(ppid, SIGUSR1);
 		}

 		free(date);
 		free(string);
 	}
 	
 	munmap(shm_struct , sizeof (* shm_struct));
 	exit(EXIT_SUCCESS);
}
