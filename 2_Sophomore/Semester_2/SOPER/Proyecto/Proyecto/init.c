/**
* @brief Archivo que contiene las funciones para inicializar recursos.
* @file init.c
* @date 8-04-2020
* @copyright Grupo 2292
*/

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <mqueue.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "sort.h"
#include "utils.h"
#include "init.h"

Status init_shared_memory(Sort **sort)
{
    int fd_shm;
    /*Creamos el segmento de msemoria compartida.*/
    fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd_shm == -1)
    {
        fprintf(stderr, " Error creating the shared memory segment \n ");
        free_sort();
        return ERROR;
    }

    shm_unlink(SHM_NAME);

    if (ftruncate(fd_shm, sizeof(Sort)) == -1)
    {
        fprintf(stderr, " Error resizing the shared memory segment \n ");
        shm_unlink(SHM_NAME);
        free_sort();
        return ERROR;
    }

    /*Añadimos el segmento de memoria compartida al proceso.*/
    *sort = mmap(NULL, sizeof(Sort), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    if (sort == MAP_FAILED)
    {
        fprintf(stderr, " Error mapping the shared memory segment \n ");
        shm_unlink(SHM_NAME);
        free_sort();
        return ERROR;
    }

    (*sort)->fd_shm = fd_shm;

    return OK;
}

Status init_queue(Sort *sort)
{

    struct mq_attr attributes;

    attributes.mq_flags = 0;
    attributes.mq_maxmsg = MAX_MESSAGES;
    attributes.mq_curmsgs = 0;
    attributes.mq_msgsize = sizeof(Message);

    sort->queue = mq_open(MQ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attributes);

    if (sort->queue == (mqd_t)-1)
    {
        fprintf(stderr, "Error opening the queue\n");
        free_sort();
        return ERROR;
    }

    mq_unlink(MQ_NAME);
    return OK;
}

Status init_sort(Sort **asort, char *file_name, int n_levels, int n_processes, int delay)
{
    char string[MAX_STRING];
    FILE *file = NULL;
    int i, j, log_data;
    int block_size, modulus;
    Sort *sort;

    if (!(file_name))
    {
        fprintf(stderr, "init_sort - Incorrect arguments\n");
        return ERROR;
    }

    if (init_shared_memory(asort) == ERROR)
    {
        perror("init_shared_memory");
        return ERROR;
    }

    sort = *asort;
    /* At most MAX_LEVELS levels. */
    sort->n_levels = MAX(1, MIN(n_levels, MAX_LEVELS));
    /* At most MAX_PARTS processes can work together. */
    sort->n_processes = MAX(1, MIN(n_processes, MAX_PARTS));
    /* The main process PID is stored. */
    sort->ppid = getpid();
    /* Delay for the algorithm in ns (less than 1s). */
    sort->delay = MAX(1, MIN(999999999, delay));

    if (sem_init(&sort->mutex, 1, 1) == -1)
    {
        perror("sem_open");
        return ERROR;
    }
    if (sem_init(&sort->mutex2, 1, 1) == -1)
    {
        perror("sem_open");
        return ERROR;
    }
    sort->procids = (int *)malloc(n_processes * sizeof(int));

    if (sort->procids == NULL)
    {
        fprintf(stderr, "malloc\n");
        return ERROR;
    }

    if (init_queue(sort) == ERROR)
    {
        perror("init_queue");
        return ERROR;
    }

    if (!(file = fopen(file_name, "r")))
    {
        perror("init_sort - fopen");
        return ERROR;
    }

    /* The first line contains the size of the data, truncated to MAX_DATA. */
    if (!(fgets(string, MAX_STRING, file)))
    {
        fprintf(stderr, "init_sort - Error reading file\n");
        fclose(file);
        return ERROR;
    }
    sort->n_elements = atoi(string);
    if (sort->n_elements > MAX_DATA)
    {
        sort->n_elements = MAX_DATA;
    }

    /* The remaining lines contains one integer number each. */
    for (i = 0; i < sort->n_elements; i++)
    {
        if (!(fgets(string, MAX_STRING, file)))
        {
            fprintf(stderr, "init_sort - Error reading file\n");
            fclose(file);
            return ERROR;
        }
        sort->data[i] = atoi(string);
    }
    fclose(file);

    /* Each task should have at least one element. */
    log_data = compute_log(sort->n_elements);
    if (n_levels > log_data)
    {
        n_levels = log_data;
    }
    sort->n_levels = n_levels;

    /* The data is divided between the tasks, which are also initialized. */
    block_size = sort->n_elements / get_number_parts(0, sort->n_levels);
    modulus = sort->n_elements % get_number_parts(0, sort->n_levels);
    sort->tasks[0][0].completed = INCOMPLETE;
    sort->tasks[0][0].ini = 0;
    sort->tasks[0][0].end = block_size + (modulus > 0);
    sort->tasks[0][0].mid = NO_MID;
    for (j = 1; j < get_number_parts(0, sort->n_levels); j++)
    {
        sort->tasks[0][j].completed = INCOMPLETE;
        sort->tasks[0][j].ini = sort->tasks[0][j - 1].end;
        sort->tasks[0][j].end = sort->tasks[0][j].ini + block_size + (modulus > j);
        sort->tasks[0][j].mid = NO_MID;
    }
    for (i = 1; i < n_levels; i++)
    {
        for (j = 0; j < get_number_parts(i, sort->n_levels); j++)
        {
            sort->tasks[i][j].completed = INCOMPLETE;
            sort->tasks[i][j].ini = sort->tasks[i - 1][2 * j].ini;
            sort->tasks[i][j].mid = sort->tasks[i - 1][2 * j].end;
            sort->tasks[i][j].end = sort->tasks[i - 1][2 * j + 1].end;
        }
    }

    return OK;
}
