 /**
 *
 * Description: Implementation of sorting functions
 *
 * File: sorting.c
 * Version: 2.0
 * Date: 27-09-2019
 *
 */


#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

int merge(int* table, int ip, int iu, int imiddle);


int split(int* table, int ip, int iu,int *pos);
int split_median_avg(int* table, int ip, int iu,int *pos);
int split_median_stat(int* table, int ip, int iu,int *pos);

int median(int *table, int ip, int iu,int *pos);
int median_stat(int *table,int ip, int iu, int *pos);
int median_avg(int *table, int ip, int iu, int *pos);

/***************************************************/
/* Function: MergeSort    Date: 18/10/2019         */
/*                                                 */
/* Rutine that sorts an array	        		   */
/* using the MergeSort algorithm                   */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int MergeSort(int* table, int ip, int iu){
    int middle;
    int aux=0;
    int OB=0;
    if(ip>iu || !table || ip<0){
        return ERR;
    }else if(ip==iu){
        return OK;
    }else{
        middle=(ip+iu)/2;
        aux = MergeSort(table, ip, middle);
        if(aux==ERR){
            return aux;
        }
        OB+=aux;
        aux=0;
        aux= MergeSort(table, middle+1, iu);
        if(aux==ERR){
            return aux;
        }
        OB+=aux;
        aux=0;
        aux = merge(table, ip, iu, middle);
        if(aux==ERR){
            return aux;
        }
        return OB+aux;
    }
}

/***************************************************/
/* Function: merge   Date: 18/10/2019              */
/*                                                 */
/* Rutine that merges the array         		   */
/* sorting it                                      */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int imiddle: index of the middle number         */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int merge(int* table, int ip, int iu, int imiddle){
    int *aux=NULL;
    int i=ip,j=imiddle+1,k=0,count=0;
    if(!table || iu<ip || ip<0 || ip>imiddle || iu<imiddle){
      return ERR;
    }
    aux=(int*)malloc((iu-ip+1)*sizeof(int));
    if(!aux){
        return ERR;
    }
    while(i<=imiddle && j<=iu){
        count++;
        if(table[i]<table[j]){
            aux[k]=table[i];
            i++;
        }
        else{
          aux[k]=table[j];
          j++;
        }        
        k++;
    }
    if(i>imiddle){
        while(j<=iu){
            aux[k]=table[j];
            j++;
            k++;
        }
    }else if(j>iu){
        while(i<=imiddle){
            aux[k]=table[i];
            i++;
            k++;
        }
    }
    
    for(k=0;k<iu-ip+1;k++){
        table[k+ip]=aux[k];
    }
    free(aux);
    return count;
}


/***************************************************/
/* Function: quicksort    Date: 25/10/2019         */
/*                                                 */
/* Rutine that sorts an array	        		   */
/* using the quicksort algorithm                   */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/



int quicksort(int* table, int ip, int iu){
    int pos;
    int answer;
    int counter=0; 
    int aux;
    if(!table || ip>iu || ip<0){
        return ERR;
    }
    if (ip==iu){
        return OK;
    }else{
        answer=split(table, ip, iu, &pos);
        if(answer==ERR){
            return ERR;
        }
        if(ip<pos-1){
           aux=quicksort(table, ip, pos-1);
           counter+=aux;
            if(aux==ERR){
                return ERR;
            }
        }
        if(pos+1<iu){
            aux=quicksort(table, pos+1, iu);
            counter+=aux;
            if(aux==ERR){
                return ERR;
            }        
        }
    }
    return answer+counter;
}

/***************************************************/
/* Function: median       Date: 25/10/2019         */
/*                                                 */
/* Rutine that calculates the 	        		   */
/* pivot of the table for the                      */
/* quicksort algorithm (first element)             */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int *pos: pointer to store the pivot            */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int median(int *table, int ip, int iu,int *pos){
    
    if(!table || ip<0 || iu<ip || !pos){
        return ERR;
    }

    *pos=ip;

    return 0;
}

/***************************************************/
/* Function: median_stat     Date: 25/10/2019      */
/*                                                 */
/* Rutine that calculates the 	        		   */
/* pivot of the table for the                      */
/* quicksort algorithm (medium pivot)              */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int *pos: pointer to store the pivot            */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int median_stat(int *table,int ip, int iu, int *pos){
    int med;
    if(!table || ip<0 || iu<ip || !pos){
        return ERR;
    }
    med=(ip+iu)/2;
    
    if(table[ip]<=table[med]){
        if(table[ip]<=table[iu]){
            if(table[med]<=table[iu]){
                *pos=med;
                return 3;
            }else{
                *pos=iu;
                return 3;
            }
        }else{
            *pos=ip;
            return 2;
        }    
    }else{
        if(table[ip]<=table[iu]){
            *pos=ip;
            return 2;
        }else{
            if(table[med]<=table[iu]){
                *pos=iu;
                return 3;
            }else{
                *pos=med;
                return 3;
            }
        }    
    }
}

/***************************************************/
/* Function: median_avg     Date: 25/10/2019       */
/*                                                 */
/* Rutine that calculates the 	        		   */
/* pivot of the table for the                      */
/* quicksort algorithm (medium element of table)   */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int *pos: pointer to store the pivot            */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int median_avg(int *table, int ip, int iu, int *pos){
    
    if(!table || ip<0 || iu<ip || !pos){
        return ERR;
    }
    
    *pos=(ip + iu)/2;
    
    return 0;
}

/***************************************************/
/* Function: split    Date: 25/10/2019             */
/*                                                 */
/* Rutine that splits a table	        		   */
/* and sort it by a pivot (first element)          */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int *pos: pointer to store the pivot            */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int split(int* table, int ip, int iu,int *pos){
    int m,k,aux,i,count=0;
  
    if(!table || ip<0 || iu<ip || !pos){
        return ERR;
    }

    m=median(table, ip, iu, pos);
  
    if(m==ERR){
      return ERR;
    }
    count+=m;
    
    m=*pos;
    k=table[m];

    aux=table[m];
    table[m]=table[ip];
    table[ip]=aux;

    m=ip; 

    for(i=ip+1;i<=iu;i++){
        count++;
        if(table[i]<k){
            m++;
            aux=table[i];
            table[i]=table[m];
            table[m]=aux;
        }
    }
    
    *pos=m;
    aux=table[m];
    table[m]=table[ip];
    table[ip]=aux;

    return count;
}

/***************************************************/
/* Function: split_median_avg Date: 25/10/2019     */
/*                                                 */
/* Rutine that splits a table	        		   */
/* and sort it by a pivot (medium element of table)*/
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int *pos: pointer to store the pivot            */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int split_median_avg(int* table, int ip, int iu,int *pos){
    int m,k,aux,i,count=0;
  
    if(!table || ip<0 || iu<ip || !pos){
        return ERR;
    }

    m=median_avg(table, ip, iu, pos);
  
    if(m==ERR){
      return ERR;
    }
    count+=m;
    m=*pos;
    k=table[m];

    aux=table[m];
    table[m]=table[ip];
    table[ip]=aux;

    m=ip; 
    for(i=ip+1;i<=iu;i++){
        count++;
        if(table[i]<k){
            m++;
            aux=table[i];
            table[i]=table[m];
            table[m]=aux;
        }
    }
    *pos=m;
    aux=table[m];
    table[m]=table[ip];
    table[ip]=aux;

    return count;
}

/***************************************************/
/* Function: split_median_stat   Date: 25/10/2019  */
/*                                                 */
/* Rutine that splits a table	        	       */
/* and sort it by a pivot (medium pivot)           */
/*                                                 */
/* Input:                                          */
/* int* table: array of integers                   */
/* int ip: index of the first element              */
/* int iu: index of the last element               */
/* int *pos: pointer to store the pivot            */
/* Output:                                         */
/* int: ERR/ number of BO executed                 */
/***************************************************/

int split_median_stat(int* table, int ip, int iu,int *pos){
    int m,k,aux,i,count=0;
  
    if(!table || ip<0 || iu<ip || !pos){
        return ERR;
    }

    m=median_stat(table, ip, iu, pos);
  
    if(m==ERR){
      return ERR;
    }
    count+=m;
    m=*pos;
    k=table[m];

    aux=table[m];
    table[m]=table[ip];
    table[ip]=aux;

    m=ip; 
    for(i=ip+1;i<=iu;i++){
        count++;
        if(table[i]<k){
            m++;
            aux=table[i];
            table[i]=table[m];
            table[m]=aux;
        }
    }
    *pos=m;
    aux=table[m];
    table[m]=table[ip];
    table[ip]=aux;

    return count;
}

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
/* int: ERR/ number of BO executed                 */
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
/* int: ERR/ number of BO executed                 */
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

