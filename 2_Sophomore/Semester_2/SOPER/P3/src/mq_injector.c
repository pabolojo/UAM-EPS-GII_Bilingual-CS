/**
* @brief Este programa abre un fichero, cuyo nombre recibe como primer argumento, y escribe en la cola de mensajes,
* cuyo nombre recibe como segundo argumento, trozos del fichero de longitud máxima 2 kB.
* Una vez terminado, envia un mensaje de finalización para notificar.
*
* @file mq_injector.c
* @date 15-04-2020
* @copyright Grupo 2292
*/

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_MESSAGES 10
#define MAX_MESSAGE_SIZE 2049 //2KB+1
/**
* @brief Función principal que realiza lo descrito en la cabecera.
* @param argc número de argumentos de entrada
* @param argv argumentos de entrada escritos por el usuario
* @return EXIT_SUCCESS si ha terminado correctamente o EXIT_FAILURE
* */
int main(int argc, char *argv[]) {
  FILE *fp = NULL;
  int bytes_read;
  char *message = NULL;

  struct mq_attr attributes = {
    .mq_flags = 0,
    .mq_maxmsg = MAX_MESSAGES,
    .mq_curmsgs = 0,
    .mq_msgsize = MAX_MESSAGE_SIZE
  };

  if (argc != 3)  {
    fprintf(stderr, "Parámetros de entrada requeridos: %s <nombre_fichero> <nombre_cola_mensajes> \n", argv[0]);
    return EXIT_FAILURE;
  }

  fp = fopen(argv[1], "r");
  if (fp == NULL)  {
    fprintf(stderr, "Error abriendo el archivo %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  mqd_t queue = mq_open(argv[2],
  O_CREAT | O_WRONLY, /* This process is only going to send messages */
  S_IRUSR | S_IWUSR,  /* The user can read and write */
  &attributes);

  if (queue == (mqd_t)-1)  {
    fprintf(stderr, "Error abriendo la cola\n");
    return EXIT_FAILURE;
  }

  message = (char *)malloc(MAX_MESSAGE_SIZE);

  if (message == NULL)  {
    fprintf(stderr, "Error inicializando memoria para el mensaje\n");
    fclose(fp);
    mq_close(queue);
    return EXIT_FAILURE;
  }

  fseek(fp, 0L, SEEK_END);
  int file_size = ftell(fp);

  if(file_size==0){
    bytes_read=0;
  }else{
    bytes_read=1;
  }

  fseek(fp, 0, SEEK_SET);

  while (bytes_read != 0)  {

    if(file_size>=MAX_MESSAGE_SIZE-1){
      bytes_read = fread(message, 1, MAX_MESSAGE_SIZE-1, fp);

      if(bytes_read==0){
        fprintf(stderr, "Error leyendo del archivo\n ");
        fclose(fp);
        mq_close(queue);
        free(message);
        return EXIT_FAILURE;
      }

      file_size-=bytes_read;

    }else{
      bytes_read = fread(message, 1, file_size, fp);
      if(bytes_read==0){
        fprintf(stderr, "Error leyendo del archivo\n ");
        fclose(fp);
        mq_close(queue);
        free(message);
        return EXIT_FAILURE;
      }

      file_size-=bytes_read;

      message[bytes_read] = '\0';

      if (mq_send(queue, message, bytes_read + sizeof(char), 1) == -1) {

        fprintf(stderr, "Error enviando el mensaje %s\n", message);
        fclose(fp);
        mq_close(queue);
        free(message);
        return EXIT_FAILURE;
      }

      break;
    }


    if (mq_send(queue, message, bytes_read, 1) == -1) {
      fprintf(stderr, "Error enviando el mensaje %s\n", message);
      fclose(fp);
      mq_close(queue);
      free(message);
      return EXIT_FAILURE;
    }
  }

  strcpy(message, "He acabado\0");

  if (mq_send(queue, message, 11 * sizeof(char), 1) == -1) {
    fprintf(stderr, "Error enviando el mensaje %s\n", message);
    fclose(fp);
    mq_close(queue);
    free(message);
    return EXIT_FAILURE;
  }

  fclose(fp);
  free(message);
  mq_close(queue);
  return EXIT_SUCCESS;
}

