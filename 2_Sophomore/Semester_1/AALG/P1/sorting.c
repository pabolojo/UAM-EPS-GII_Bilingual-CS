 /**
 *
 * Description: Implementation of sorting functions
 *
 * File: sorting.c
 * Version: 1.0
 * Date: 27-09-2019
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date: 27/09/2019        */
/*                                                 */
/* Rutine that sorts an array	        		   */
/* using the InsertSort algorithm                  */
/*                                                 */
/* Input:                                          */
/* int* list: array of integers                    */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* short: ERR/ number of BO executed               */
/***************************************************/
int InsertSort(int* list, int ip, int iu){
    int i, j, a,counter=0;  

    if(!list || ip<0 || iu<ip){
        return ERR;
    }

    for(i=ip+1; i<=iu; i++){
        a = list[i];
        j = i-1;
        while(j>=ip && list[j]>a){
            counter++;
            list[j+1]=list[j];
            j--;
        }
        if(j>=ip){
            counter++;
        }
        list[j+1] = a;

    }   

    return counter;
}


/***************************************************/
/* Function: InsertSortInv    Date: 27/09/2019     */
/*                                                 */
/* Rutine that sorts an array 	        		   */
/* on the inverse direction                        */
/* using an algorithm like the InsertSort          */
/*                                                 */
/* Input:                                          */
/* int* list: array of integers                    */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* short: ERR/ number of BO executed               */
/***************************************************/
int InsertSortInv(int* list, int ip, int iu){
    int i, j, a,counter=0;  

    if(!list || ip<0 || iu<ip){
        return ERR;
    }
    
    for(i=ip+1; i<=iu; i++){
        a = list[i];
        j = i-1;
        while(j>=ip && list[j]<a){
            counter++;
            list[j+1]=list[j];
            j--;
        }
        if(j>=ip){
            counter++;
        }
        list[j+1] = a;
    }   

    return counter;
}

