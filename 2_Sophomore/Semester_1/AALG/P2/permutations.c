 /**
 *
 * Description: Implementation of functions for permutation generation
 *
 * File: permutations.c
 * Version: 1.0
 * Data: 20-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date: 20/09/2019           */
/*                                                 */
/* Rutine that generates random numbers	  		   */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: inferior limit                         */
/* int sup: superior limit       	               */
/* Output:                                         */
/* int: random number	                           */
/***************************************************/
int random_num(int inf, int sup){
  if(inf>sup){
    return -1;
  }
  return (int)((sup - inf + 1.0)*rand()/(RAND_MAX + 1.0)+ inf);
}

/***************************************************/
/* Function: genera_perm Date: 20/09/2019          */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                               	       */
/* int n: Number of permutation elements           */
/* Output:                                         */
/* int *: punter to an integer array that 		   */
/* contains the permutation            			   */
/* or NULL if error		                           */
/***************************************************/
int* generate_perm(int N){
    int i=1, a=0, random=0;
    int *perm;
    if(N<1){
        return NULL;
    }
    perm = (int*)malloc(N*sizeof(int));
    if(!perm){
        return NULL;
    }
    for(;i<=N;i++){
        perm[i-1] = i;
    }
    for(i=0;i<N;i++){
        a = perm[i];
        random = random_num(i, N-1);
        if(random==-1){
            free(perm);
            return NULL;
        }
        perm[i] = perm[random];
        perm[random] = a;
    }
    return perm;
}

/***************************************************/
/* Function: genera_permutaciones Date: 20/09/2019 */
/*                                                 */
/* Funcion that generates n_perms random		   */
/* permutations of N elements                 	   */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements of each permutation   */
/* Output:                                         */
/* int**: Array of integer pointers that point 	   */
/* to each of the permutations 		               */
/* NULL if error          		                   */
/***************************************************/
int** generate_permutations(int n_perms, int N){
    int i,j;
    int **perms;
    if(n_perms<1 || N<1){
        return NULL;
    }
    perms = (int**)malloc(n_perms*sizeof(int*));
    if(!perms){
        return NULL;
    }
    for(i=0; i<n_perms; i++){
        perms[i] = generate_perm(N);
        if(!perms[i]){
            for(j=0; j<i; j++){
                free(perms[j]);
            }
            free(perms);
            return NULL;
        }
    }
    return perms;
}

