/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Version: 1.0
 * Fecha: 11-10-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
/***************************************************/
/* Function: average_sorting_time Date: 04/10/2019 */
/*                                                 */
/* Rutine that generates a structure	  		   */
/* with information about the different            */
/*  run times of an algorithm                      */
/*                                                 */
/* Input:                                          */
/* pfunc_sort method: function to measure          */
/* int n_perms: number of permutations             */
/* int N: size of permutations                     */
/* PTIME_AA ptime: structure to save the data      */
/* Output:                                         */
/* short: ERR/OK                                   */
/***************************************************/
short average_sorting_time(pfunc_sort method, int n_perms, int N, PTIME_AA ptime){

    int i, **perms, res;
    struct timespec start, stop;

    if(!method || n_perms<0 || N<0 || !ptime){
        return ERR;
    }
    ptime->average_ob=0;
    ptime->N=N;
    ptime->n_elems=n_perms;

    perms = generate_permutations(n_perms, N);
    if(perms==NULL){
        return ERR;
    }
    
    clock_gettime(CLOCK_REALTIME, &start);


    for(i=0; i<n_perms; i++){
        res = method(perms[i], 0, N-1);
        if(res==ERR){
            for(i=0; i<n_perms; i++){
                free(perms[i]);
            }
            free(perms);
            clock_gettime(CLOCK_REALTIME, &stop);
            return ERR;
        }

        if(i==0){
            ptime->min_ob=res;
            ptime->max_ob=res;
        }

        if(res<ptime->min_ob){
            ptime->min_ob=res;
        }else if(res>ptime->max_ob){
            ptime->max_ob=res;
        }
       ptime->average_ob+=(double)res/n_perms;

    }
    clock_gettime(CLOCK_REALTIME, &stop);


    ptime->time = (((double)( stop.tv_sec - start.tv_sec )/(double)n_perms) + ((double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION)/(double)n_perms);
    
    for(i=0; i<n_perms; i++){
        free(perms[i]);
    }
    free(perms);
    return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:04/10/2019*/
/*                                                 */
/* Rutine that goes from the num_min 	  		   */
/*  to num_max with an increment                   */
/*  and call in that loops to the                  */
/*  method function                                */
/*                                                 */
/* Input:                                          */
/* pfunc_sort method: function to measure          */
/* char* file: name of the file                    */
/* int num_min: inferior limit                     */
/* int num_max: superior limit                     */
/* int incr: size of increments                    */
/* int n_perms:  number of permutations            */
/* Output:                                         */
/* short: ERR/OK                                   */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file,  int num_min, int num_max,  int incr, int n_perms){
    PTIME_AA ptime=NULL;
    int i,j;
    int n_times;

    if(!method || !file || num_min<0 || num_max<num_min || incr<1 || n_perms<0){
        return ERR;
    }
    
    n_times=((num_max-num_min)/incr) +1;
    
    ptime = (PTIME_AA)malloc(n_times*sizeof(TIME_AA));

    if(!ptime){
        return ERR;
    }

    for(i=num_min, j=0;i<=num_max;i+=incr, j++){
        if(average_sorting_time(method, n_perms, i, &ptime[j])==ERR){
            free(ptime);
            return ERR;
        }
    }

    if(save_time_table(file, ptime, n_times)==ERR){
        free(ptime);
        return ERR;
    }
    free(ptime);

    return OK;
}

/***************************************************/
/* Function: save_time_table Date: 04/10/2019      */
/*                                                 */
/* Rutine that writes the data in the PTIME_AA     */
/* structure into a file                           */
/*                                                 */
/* Input:                                          */
/* char* file: name of the file                    */
/* PTIME_AA ptime: structure to read the data      */
/* int n_times:  number of array elements          */
/* Output:                                         */
/* short: ERR/OK                                   */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times){

    FILE *f;
    int i;

    if(!file || !ptime || n_times<0){
        return ERR;
    }

    f=fopen(file, "w");
    if(!f){
        return ERR;
    }

    for(i=0; i<n_times; i++){
        fprintf(f,"%d %lf %lf %d %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
    }

    fclose(f);

    return OK;
}

