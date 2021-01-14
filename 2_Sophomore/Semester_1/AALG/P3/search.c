/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order){
    PDICT dictionary=NULL; 
	int *table=NULL;
    

    if(size<=0 || (order!=SORTED && order!=NOT_SORTED)){
        return NULL;
    }
    
    dictionary=(PDICT)malloc(sizeof(DICT));
    if(dictionary==NULL){
        return NULL;
    }

    table=(int *)malloc(size*sizeof(int));
    if(table==NULL){
        free_dictionary(dictionary);
        return NULL;
    }

    dictionary->size=size;
    dictionary->n_data=0;
    dictionary->order=order;
    dictionary->table=table;
    
    
    return dictionary;
}

void free_dictionary(PDICT pdict){
	if(pdict==NULL){
        return;
    }

    if(pdict->table==NULL){
        free(pdict);
        return;
    }
    
    free(pdict->table);
    free(pdict);
    
    return;
}

int insert_dictionary(PDICT pdict, int key){
    int count=0;
    int i;

    if(!pdict || !pdict->table || pdict->n_data==pdict->size){
        return ERR;
    }   

    pdict->table[pdict->n_data]=key;
    pdict->n_data++;  

    if(pdict->order==SORTED){
        i=pdict->n_data-2;
        while(i >= 0 && pdict->table[i] > key){
            count++;
            pdict->table[i+1] = pdict->table[i];
            i--;
        }
        if(i>=0){
           count++; 
        }
        pdict->table[i+1] = key;
    }   

    return count;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys){
	int answer=0;
    int counter=0;
    int i;
    
    if(pdict==NULL || !pdict->table || keys==NULL || n_keys<0){
        return ERR;
    }

    for(i=0; i<n_keys; i++){
        answer=insert_dictionary(pdict, keys[i]);
        if(answer==ERR){
            return ERR;
        }
        counter+=answer;
    }

    return counter;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){
	int count;

    if(!pdict || !pdict->table || !ppos || !method){
        return ERR;
    }   
    count = method(pdict->table, 0, pdict->n_data-1, key, ppos);   

    return count;
}


/* Search functions of the Dictionary ADT */

int bin_search(int *table,int F,int L,int key, int *ppos){
    int mid, count=0, aux;

    if(!table || F<0 || L<F || ppos==NULL){
        return ERR;
    }

    mid = (F+L)/2;
    if(table[mid]==key){
        *ppos=mid;
        return 1;
    }

    count+=1;
    
    if(F==L){
        *ppos=NOT_FOUND;
        return 1;
    }
        
    if(table[mid]>key && F<mid){
        aux=bin_search(table, F, mid-1, key, ppos);   
        if(aux==ERR){
            return ERR;
        }
        count+=aux;
    }else if(mid<L){
        aux=bin_search(table, mid+1, L, key, ppos);
        if(aux==ERR){
            return ERR;
        }
        count+=aux;
    }
    return count;
}

int lin_search(int *table,int F,int L,int key, int *ppos){
    int counter=0;
    int i;

	if(table==NULL || F<0 || F>L || ppos==NULL){
        return ERR;
    }
    
    for(i=F; i<=L; i++){
        counter++;
        if(table[i]==key){
            *ppos=i;
            return counter;
        }
    }
    *ppos=NOT_FOUND;
    return counter;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos){
	int counter=0;
    int i;
    int a;

	if(table==NULL || F<0 || F>L || ppos==NULL){
        return ERR;
    }
    
    for(i=F; i<=L; i++){
        counter++;
        if(table[i]==key){
            *ppos=i;
            if(i!=F){
                a=table[i-1];
                table[i-1]=table[i];
                table[i]=a;
                *ppos=i-1;
            }
            return counter;
        }
    }
    *ppos=NOT_FOUND;
    return counter;
}
