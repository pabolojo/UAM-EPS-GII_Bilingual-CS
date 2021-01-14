#ifndef _INIT_H
#define _INIT_H

#include "global.h"

/* Constants. */
#define SHM_NAME "/shm_proyecto"
#define MQ_NAME "/mq_proyecto"

#define MAX_MESSAGES 10

/* Prototypes. */

/**
 * Initializes the message queue.
 * @method init_queue
 * @date   2020-05-02
 * @param  sort   The sort structure
 * @return        ERROR in case of error, OK otherwise.
 */
Status init_queue(Sort *sort);

/**
 * Initializes the shared memory segment.
 * @method init_shared_memory
 * @date   2020-05-02
 * @param  sort   The sort structure
 * @return        ERROR in case of error, OK otherwise.
 */
Status init_shared_memory(Sort **sort);

/**
 * Initializes the sort structure.
 * @method init_sort
 * @date   2020-04-09
 * @author Teaching team of SOPER
 * @param  asort   The sort structure
 * @param  file_name   File with the data.
 * @param  n_levels    Total number of levels in the algorithm.
 * @param  n_processes Number of processes.
 * @param  delay       Delay for the algorithm.
 * @return             ERROR in case of error, OK otherwise.
 */
Status init_sort(Sort **asort, char *file_name, int n_levels, int n_processes, int delay);
#endif
