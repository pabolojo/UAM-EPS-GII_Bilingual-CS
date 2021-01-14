/**
* @brief Archivo que contiene la función principal del programa y varias auxiliares.
* @file sort.c
* @date 8-04-2020
* @copyright Grupo 2292
*/

#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <mqueue.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "sort.h"
#include "utils.h"
#include "init.h"

static volatile sig_atomic_t sigusr1f = 1, sigtermf = 0; /* Banderas usadas en los manejadores */
Sort *sort = NULL;  /* Estructura sort */
int fdt_ida[2];     /* Pipe con sentido trabajador->ilustrador */
int fdt_vuelta[2];  /* Pipe con sentido ilustrador->trabajador */
Message msag;       /* Estructura usada para enviar mensajes por el pipe y por la cola */
Message *ms = NULL; /* Estructura usada para guardar los datos que recibe el ilustrador */
int *aux = NULL;    /* Variable auxiliar usada en merge(). Si no se declara como global y se libera, al hacer CTRL+C, hay leaks */

Status bubble_sort(int *vector, int n_elements, int delay)
{
    int i, j;
    int temp;

    if ((!(vector)) || (n_elements <= 0))
    {
        return ERROR;
    }

    for (i = 0; i < n_elements - 1; i++)
    {
        for (j = 0; j < n_elements - i - 1; j++)
        {
            /* Delay. */
            fast_sleep(delay);
            if (vector[j] > vector[j + 1])
            {
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }

    return OK;
}

Status merge(int *vector, int middle, int n_elements, int delay)
{

    int i, j, k, l, m;

    if (!(aux = (int *)malloc(n_elements * sizeof(int))))
    {
        return ERROR;
    }

    for (i = 0; i < n_elements; i++)
    {
        aux[i] = vector[i];
    }

    i = 0;
    j = middle;
    for (k = 0; k < n_elements; k++)
    {
        /* Delay. */
        fast_sleep(delay);
        if ((i < middle) && ((j >= n_elements) || (aux[i] < aux[j])))
        {
            vector[k] = aux[i];
            i++;
        }
        else
        {
            vector[k] = aux[j];
            j++;
        }

        /* This part is not needed, and it is computationally expensive, but
        it allows to visualize a partial mixture. */
        m = k + 1;
        for (l = i; l < middle; l++)
        {
            vector[m] = aux[l];
            m++;
        }
        for (l = j; l < n_elements; l++)
        {
            vector[m] = aux[l];
            m++;
        }
    }

    free((void *)aux);
    aux = NULL;
    return OK;
}

int get_number_parts(int level, int n_levels)
{
    /* The number of parts is 2^(n_levels - 1 - level). */
    return 1 << (n_levels - 1 - level);
}

Bool check_task_ready(int level, int part)
{
    if (!(sort))
    {
        return FALSE;
    }

    if ((level < 0) || (level >= sort->n_levels) || (part < 0) || (part >= get_number_parts(level, sort->n_levels)))
    {
        return FALSE;
    }

    if (sort->tasks[level][part].completed != INCOMPLETE)
    {
        return FALSE;
    }

    /* The tasks of the first level are always ready. */
    if (level == 0)
    {
        return TRUE;
    }

    /* Other tasks depend on the hierarchy. */
    if ((sort->tasks[level - 1][2 * part].completed == COMPLETED) &&
        (sort->tasks[level - 1][2 * part + 1].completed == COMPLETED))
    {
        return TRUE;
    }

    return FALSE;
}

Status solve_task(int level, int part)
{
    /* In the first level, bubble-sort. */
    if (sort->tasks[level][part].mid == NO_MID)
    {
        return bubble_sort(
            sort->data + sort->tasks[level][part].ini,
            sort->tasks[level][part].end - sort->tasks[level][part].ini,
            sort->delay);
    }
    /* In other levels, merge. */
    else
    {
        return merge(
            sort->data + sort->tasks[level][part].ini,
            sort->tasks[level][part].mid - sort->tasks[level][part].ini,
            sort->tasks[level][part].end - sort->tasks[level][part].ini,
            sort->delay);
    }
}

void free_sort()
{
    if (aux)
    {
        free((void *)aux);
    }

    if (ms)
    {
        free(ms);
    }

    if (sort->procids)
    {
        free(sort->procids);
    }
    if (sort->queue)
    {
        mq_close(sort->queue);
    }
    if (&sort->mutex)
    {
        sem_destroy(&sort->mutex);
    }
    if (&sort->mutex2)
    {
        sem_destroy(&sort->mutex2);
    }
    if (sort->fd_shm > 0)
    {
        close(sort->fd_shm);
    }
    if (sort)
    {
        munmap(sort, sizeof(*sort));
    }
}

/**
* @brief Manejador de la señal SIGTERM
* */
void manejador_SIGTERM(int sig)
{
    free_sort();
    exit(EXIT_SUCCESS);
}

/**
* @brief Manejador de la señal SIGINT
* */
void manejador_SIGINT(int sig)
{
    int i;
    for (i = 0; i < sort->n_processes; i++)
    {
        kill(sort->procids[i], SIGTERM);
    }
    kill(sort->ilustrador, SIGTERM);
    for (i = 0; i < sort->n_processes + 1; i++)
    {
        wait(NULL);
    }

    free_sort(sort);
    exit(EXIT_SUCCESS);
}

/**
* @brief Manejador de la señal SIGUSR1
* */
void manejador_SIGUSR1(int sig)
{
    sigusr1f = 1;
}

/**
* @brief Manejador de la señal SIGALRM
* */
void manejador_SIGALRM(int sig)
{
    char readbuffer[9 * sizeof(char)];
    int value;
    sem_wait(&sort->mutex2);
    value = write(fdt_ida[1], &msag, sizeof(msag));
    if (value == -1)
    {
        sem_post(&sort->mutex2);
        perror("Error sending message on pipe. Worker");
        free_sort();
        exit(EXIT_FAILURE);
    }
    sem_post(&sort->mutex2);
    value = read(fdt_vuelta[0], &readbuffer, 9 * sizeof(char));
    if (value == -1)
    {
        perror("Error recieving message from pipe. Worker");
        free_sort();
        exit(EXIT_FAILURE);
    }
    alarm(1);
    return;
}

void init_handlers()
{
    struct sigaction act;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;
    act.sa_handler = manejador_SIGUSR1;
    if (sigaction(SIGUSR1, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    act.sa_handler = manejador_SIGTERM;
    if (sigaction(SIGTERM, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    act.sa_handler = manejador_SIGINT;
    if (sigaction(SIGINT, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    act.sa_handler = manejador_SIGALRM;
    if (sigaction(SIGALRM, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    return;
}

Status sort_multiple_process(char *file_name, int n_levels, int n_processes, int delay)
{
    int i, j;
    int pid = 0;
    int cont = 0, counter = 0, result = 0, total = 0;
    sigset_t mask;
    pid_t id_ilustrador;

    if (file_name == NULL)
    {
        fprintf(stderr, "sort_multiple_process - file_name\n");
        return ERROR;
    }

    if (n_levels < 1 || n_levels > MAX_LEVELS)
    {
        fprintf(stderr, "sort_multiple_process - number_levels\n");
        return ERROR;
    }

    if (n_processes < 1 || n_processes > MAX_PARTS)
    {
        fprintf(stderr, "sort_multiple_process - number_processes\n");
        return ERROR;
    }

    if (delay <= 0)
    {
        fprintf(stderr, "sort_multiple_process - delay\n");
        return ERROR;
    }

    init_handlers();

    /* The data is loaded and the structure initialized. */
    if (init_sort(&sort, file_name, n_levels, n_processes, delay) == ERROR)
    {
        fprintf(stderr, "sort_multiple_process - init_sort\n");
        return ERROR;
    }

    if (pipe(fdt_ida) == -1)
    {
        perror("pipe");
        free_sort();
        exit(EXIT_FAILURE);
    }

    if (pipe(fdt_vuelta) == -1)
    {
        perror("pipe");
        free_sort();
        exit(EXIT_FAILURE);
    }

    id_ilustrador = fork();
    if (!id_ilustrador)
    {
        sigset_t oset, set;
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        if (sigprocmask(SIG_BLOCK, &set, &oset) < 0)
        {
            perror("sigprocmask");
            free_sort();
            exit(EXIT_FAILURE);
        }

        /* Cierre del descriptor de salida en el ilustrador*/
        close(fdt_ida[1]);
        /* Cierre del descriptor de entrada en el ilustrador*/
        close(fdt_vuelta[0]);

        ilustrador();
    }

    sort->ilustrador = id_ilustrador;

    for (i = 0; i < n_processes; i++)
    {
        pid = fork();
        if (!pid)
        {

            break;
        }
        else if (pid < 0)
        {
            free_sort();
            fprintf(stderr, "Error fork\n");
            return EXIT_FAILURE;
        }
        else
        {
            sort->procids[i] = pid;
        }
    }

    if (!pid)
    {
        sigset_t oset, set;
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        if (sigprocmask(SIG_BLOCK, &set, &oset) < 0)
        {
            perror("sigprocmask");
            free_sort();
            exit(EXIT_FAILURE);
        }

        /* Cierre del descriptor de entrada en el trabajador*/
        close(fdt_ida[0]);
        /* Cierre del descriptor de salida en el trabajador*/
        close(fdt_vuelta[1]);

        alarm(1);

        while (!sigtermf)
        {
            trabajador();
            kill(sort->ppid, SIGUSR1);
        }

        free_sort();

        exit(EXIT_SUCCESS);
    }
    plot_vector((*sort).data, (*sort).n_elements);
    printf("\nStarting algorithm with %d levels and %d processes...\n", (*sort).n_levels, (*sort).n_processes);
    /* For each level, and each part, the corresponding task is solved. */
    cont = 0;

    for (i = 0; i < (*sort).n_levels; i++)
    {
        for (j = 0; j < get_number_parts(i, (*sort).n_levels); j++)
        {
            total++;
        }
    }

    while (1)
    {
        if (sigusr1f)
        {
            sigusr1f = 0;

            for (i = 0; i < (*sort).n_levels; i++)
            {
                for (j = 0; j < get_number_parts(i, (*sort).n_levels); j++)
                {
                    do
                    {
                        counter = 0;
                        result = sem_wait(&sort->mutex);
                        if (result == -1)
                        {
                            if (errno == EINTR)
                            {
                                counter = 1;
                            }
                        }
                    } while (counter);

                    if (check_task_ready(i, j))
                    {
                        sem_post(&sort->mutex);
                        send_task(i, j);
                    }
                    else
                    {
                        sem_post(&sort->mutex);
                    }
                }
            }
        }
        else
        {
            cont = 0;

            do
            {
                counter = 0;
                result = sem_wait(&sort->mutex);
                if (result == -1)
                {
                    if (errno == EINTR)
                    {
                        counter = 1;
                    }
                }
            } while (counter);

            for (i = 0; i < (*sort).n_levels; i++)
            {
                for (j = 0; j < get_number_parts(i, (*sort).n_levels); j++)
                {
                    if (sort->tasks[i][j].completed == COMPLETED)
                    {
                        cont++;
                    }
                }
            }

            sem_post(&sort->mutex);
            if (cont == total)
            {
                break;
            }
            sigemptyset(&mask);
            sigsuspend(&mask);
        }
    }

    for (i = 0; i < n_processes; i++)
    {
        kill(sort->procids[i], SIGTERM);
    }

    kill(sort->ilustrador, SIGTERM);

    plot_vector((*sort).data, (*sort).n_elements);

    for (i = 0; i < n_processes + 1; i++)
    {
        wait(NULL);
    }

    printf("\nAlgorithm completed\n");

    free_sort();
    return OK;
}

void ilustrador()
{

    char string[] = "CONTINUA";
    int value;
    int contador = 0, cont = 0, result = 0;
    int l;
    Completed status;

    ms = (Message *)malloc((*sort).n_processes * sizeof(Message));
    if (!ms)
    {
        perror("Error allocating memory. Ilustrator");
        free_sort();
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ms[contador].level = -1;
        ms[contador].part = -1;
        ms[contador].process = 0;
        value = read(fdt_ida[0], &ms[contador], sizeof(ms[contador]));

        if (value == -1)
        {
            perror("Error recieving message from pipe. Ilustrator");
            free_sort();
            exit(EXIT_FAILURE);
        }
        contador++;

        if (contador == (*sort).n_processes)
        {
            plot_vector((*sort).data, (*sort).n_elements);
            printf("\n%10s%10s%10s%10s%10s%10s\n", "PID", "LEVEL", "PART", "INI",
                   "END", "STATUS");

            contador = 0;
            for (l = 0; l < (*sort).n_processes; l++)
            {
                if (ms[l].level != -1 && ms[l].part != -1 && ms[l].process != 0)
                {
                    printf("%10d%10d%10d%10d%10d ", ms[l].process, ms[l].level, ms[l].part,
                           (*sort).tasks[ms[l].level][ms[l].part].ini, (*sort).tasks[ms[l].level][ms[l].part].end);
                    do
                    {
                        cont = 0;
                        result = sem_wait(&sort->mutex);
                        if (result == -1)
                        {
                            if (errno == EINTR)
                            {
                                cont = 1;
                            }
                        }
                    } while (cont);

                    status = (*sort).tasks[ms[l].level][ms[l].part].completed;

                    sem_post(&sort->mutex);

                    if (status == COMPLETED)
                    {
                        printf("%10s\n", "COMPLETED");
                    }
                    else if (status == SENT)
                    {
                        printf("%10s\n", "SENT");
                    }
                    else
                    {
                        printf("%10s\n", "PROCESSING");
                    }
                }
                else
                {
                    printf("%10d%40s %10s\n", ms[l].process, " ", "STOPPED");
                }

                value = write(fdt_vuelta[1], &string, strlen(string) + 1);

                if (value == -1)
                {
                    perror("Error sending message on pipe. Ilustrator");
                    free_sort();
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void trabajador()
{

    struct timespec req;
    int result = 0, cont = 0;
    clock_gettime(CLOCK_REALTIME, &req);
    req.tv_sec += 4;
    msag.level = -1;
    msag.part = -1;
    msag.process = getpid();
    do
    {
        cont = 1;
        result = 0;
        result = mq_timedreceive(sort->queue, (char *)&msag, sizeof(msag), NULL, &req);

        if (result == -1)
        {

            if (errno == EINTR)
            {
            }
            else if (errno == ETIMEDOUT)
            {
                return;
            }
            else
            {
                free_sort();
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cont = 0;
        }
    } while (cont);
    msag.process = getpid();
    do
    {
        cont = 0;
        result = sem_wait(&sort->mutex);
        if (result == -1)
        {
            if (errno == EINTR)
            {
                cont = 1;
            }
        }
    } while (cont);

    sort->tasks[msag.level][msag.part].completed = PROCESSING;
    sem_post(&sort->mutex);

    solve_task(msag.level, msag.part);

    do
    {
        cont = 0;
        result = sem_wait(&sort->mutex);
        if (result == -1)
        {
            if (errno == EINTR)
            {
                cont = 1;
            }
        }
    } while (cont);

    sort->tasks[msag.level][msag.part].completed = COMPLETED;

    sem_post(&sort->mutex);
}

void send_task(int i, int j)
{
    int cont = 0, result = 0;

    do
    {
        cont = 0;
        result = sem_wait(&sort->mutex);
        if (result == -1)
        {
            if (errno == EINTR)
            {
                cont = 1;
            }
        }
    } while (cont);

    if (sort->tasks[i][j].completed == INCOMPLETE)
    {
        sem_post(&sort->mutex);

        msag.level = i;
        msag.part = j;
        msag.process = 0;
        do
        {
            cont = 0;
            result = mq_send(sort->queue, (char *)&msag, sizeof(msag), 1);
            if (result == -1)
            {
                if (errno == EINTR)
                {
                    cont = 1;
                }
                else
                {
                    fprintf(stderr, "Error enviando el mensaje \n");
                    free_sort();
                    exit(EXIT_FAILURE);
                }
            }
        } while (cont);

        do
        {
            cont = 0;
            result = sem_wait(&sort->mutex);
            if (result == -1)
            {
                if (errno == EINTR)
                {
                    cont = 1;
                }
            }
        } while (cont);
        sort->tasks[i][j].completed = SENT;
        sem_post(&sort->mutex);
        return;
    }

    sem_post(&sort->mutex);
}
