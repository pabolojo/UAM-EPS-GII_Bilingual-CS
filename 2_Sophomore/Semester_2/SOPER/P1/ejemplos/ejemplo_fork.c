#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define NUM_PROC 3

int main ( void ){
	pid_t pid ;
	pid_t ppid;

	for ( int i = 0; i < NUM_PROC ; i ++){
		ppid=getpid();
		pid=fork();
		if(pid < 0){
			perror(" fork ") ;
			exit(EXIT_FAILURE) ;
		}else if(pid == 0){
			printf(" Hijo con pid: %d , su padre es: %d  \n " , getpid(), ppid);
			exit(EXIT_SUCCESS) ;
		}else if(pid > 0){
			printf(" Padre %d \n " , i);
		}
	}
	wait(NULL);
	exit(EXIT_SUCCESS);
}
