#ifndef _SORT_H
#define _SORT_H

#include <mqueue.h>
#include <semaphore.h>
#include <sys/types.h>
#include "global.h"

/* Constants. */
#define MAX_DATA 100000
#define MAX_LEVELS 10
#define MAX_PARTS 512
#define MAX_STRING 1024
#define SHM_NAME "/shm_proyecto"
#define MQ_NAME "/mq_proyecto"

#define PLOT_PERIOD 1
#define NO_MID -1
#define MAX_MESSAGES 10

/* Type definitions. */

/* Completed flag for the tasks. */
typedef enum
{
    INCOMPLETE,
    SENT,
    PROCESSING,
    COMPLETED
} Completed;

/* Task. */
typedef struct
{
    Completed completed;
    int ini;
    int mid;
    int end;
} Task;

/* Structure for the sorting problem. */
typedef struct
{
    mqd_t queue;
    int *procids;
    int fd_shm;
    pid_t ilustrador;

    sem_t mutex; /* Semáforo que controla el acceso a las task */
    sem_t mutex2; /* Semáforo que controla el acceso a las task */
    Task tasks[MAX_LEVELS][MAX_PARTS];
    int data[MAX_DATA];
    int delay;
    int n_elements;
    int n_levels;
    int n_processes;
    pid_t ppid;
} Sort;

/* Message sent by a pipe or by a queue */
typedef struct
{
    int level;
    int part;
    pid_t process;

} Message;

/* Prototypes. */

/**
 * Sorts an array using bubble-sort.
 * @method bubble_sort
 * @date   2020-04-09
 * @author Teaching team of SOPER
 * @param  vector      Array with the data.
 * @param  n_elements  Number of elements in the array.
 * @param  delay       Delay for the algorithm.
 * @return             ERROR in case of error, OK otherwise.
 */
Status bubble_sort(int *vector, int n_elements, int delay);

/**
 * Merges two ordered parts of an array keeping the global order.
 * @method merge
 * @date   2020-04-09
 * @author Teaching team of SOPER
 * @param  vector     Array with the data.
 * @param  middle     Division between the first and second parts.
 * @param  n_elements Number of elements in the array.
 * @param  delay      Delay for the algorithm.
 * @return            ERROR in case of error, OK otherwise.
 */
Status merge(int *vector, int middle, int n_elements, int delay);

/**
 * Computes the number of parts (division) for a certain level of the sorting
 * algorithm.
 * @method get_number_parts
 * @date   2020-04-09
 * @author Teaching team of SOPER
 * @param  level            Level of the algorithm.
 * @param  n_levels         Total number of levels in the algorithm.
 * @return                  Number of parts in the level.
 */
int get_number_parts(int level, int n_levels);

/**
 * Checks if a task is ready to be solved.
 * @method check_task_ready
 * @date   2020-04-09
 * @author Teaching team of SOPER
 * @param  level            Level of the algorithm.
 * @param  part             Part inside the level.
 * @return                  FALSE if it is not ready, TRUE otherwise.
 */
Bool check_task_ready(int level, int part);

/**
 * Solves a single task of the sorting algorithm.
 * @method solve_task
 * @date   2020-04-09
 * @author Teaching team of SOPER
 * @param  level      Level of the algorithm.
 * @param  part       Part inside the level.
 * @return            ERROR in case of error, OK otherwise.
 */
Status solve_task(int level, int part);

/**
 * Solves a sorting problem using a single process.
 * @method sort_multiple_process
 * @date   2020-04-09
 * @param  file_name        File with the data.
 * @param  n_levels         Total number of levels in the algorithm.
 * @param  n_processes      Number of processes.
 * @param  delay            Delay for the algorithm.
 * @return                  ERROR in case of error, OK otherwise.
 */
Status sort_multiple_process(char *file_name, int n_levels, int n_processes, int delay);

/**
 * Frees all the resources
 * @method free_sort
 * @date   2020-05-03
 */
void free_sort();

/**
 * Method that includes functionality of the worker.
 * @method trabajador
 * @date   2020-05-03
 */
void trabajador();

/**
 * Method that includes functionality of the ilustrator.
 * @method ilustrador
 * @date   2020-05-03
 */
void ilustrador();

/**
 * Sends a task to a worker.
 * @method ilustrador
 * @date   2020-05-03
 * @param  i      Level of the algorithm.
 * @param  j      Part inside the level.
 */
void send_task(int i, int j);

/**
 * Initializates the signal handlers.
 * @method trabajador
 * @date   2020-05-03
 */
void init_handlers();

#endif

