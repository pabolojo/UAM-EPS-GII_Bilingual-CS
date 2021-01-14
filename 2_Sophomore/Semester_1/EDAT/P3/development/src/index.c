#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index.h"

struct index_ {
    int n_records;
    irecord_t **recs;
    FILE *fp;
    type_t type;
};

struct irecord_ {
    void * key;
    int n_records;
    long *rec;
};

int binary(irecord_t **array, void *key, int n, type_t type);

/*
   Function: int index_create(char *path, int type)

   Creates a file for saving an empty index. The index is initialized
   to be of the specific tpe (in the basic version this is always INT)
   and to contain 0 entries.

   Parameters:
   path:  the file where the index is to be created
   type:  the type of the index (always INT in this version)

   Returns:
   1:   index created
   0:   parameter error or file creation problem. Index not created.
 */
int index_create(char *path, type_t type) {
    FILE *fp=NULL;
    int n_records=0;
    if(!path){
        return 0;
    }

    fp=fopen(path, "w");
    if(fp==NULL){
        return 0;
    }

    fwrite(&n_records,1,  sizeof(int),fp);
    fwrite(&type, 1, sizeof(type_t),  fp);

    fclose(fp);
    return 1;
}



/*
   Opens a previously created index: reads the contents of the index
   in an index_t structure that it allocates, and returns a pointer to
   it (or NULL if the files doesn't exist or there is an error).

   NOTE: the index is stored in memory, so you can open and close the
   file in this function. However, when you are asked to save the
   index, you will not be given the path name again, so you must store
   in the structure either the FILE * (and in this case you must keep
   the file open) or the path (and in this case you will open the file
   again).

   Parameters:
   path:  the file where the index is

   Returns:
   pt:   index opened
   NULL: parameter error or file opening problem. Index not opened.

 */
index_t* index_open(char* path) {
    index_t *index;
    int n_records;
    if(!path){
        return NULL;
    }

    index=(index_t *)malloc(sizeof(index_t));
    if(index==NULL){
        return NULL;
    }

    index->fp=NULL;
    index->fp=fopen(path,"r+");
    if(index->fp==NULL){
        index_close(index);
        return NULL;
    }

    fseek(index->fp, 0, SEEK_SET);

    if(fread(&n_records, sizeof(int), 1, index->fp)!=1){
        index_close(index);
        return NULL;
    }
    index->n_records=(int)n_records;

    if(fread(&index->type, sizeof(type_t),1, index->fp)!=1){
        index_close(index);
        return NULL;
    }
    index->recs=NULL;
    if(n_records!=0){
        index->recs=(irecord_t **)malloc(n_records*sizeof(irecord_t *));
        if(index->recs==NULL){
            index_close(index);
            return NULL;
        }
        for(int i=0; i<n_records; i++){
        	if(fread(&index->recs[i]->key, sizeof(int), 1, index->fp)!=1){
        		index_close(index);
        		return NULL;
   			}
   			if(fread(&index->recs[i]->n_records, sizeof(int), 1, index->fp)!=1){
        		index_close(index);
        		return NULL;
   			}
   			index->recs[i]->rec=(long *)malloc(n_records*sizeof(long));
   			if(!index->recs[i]->rec){
   				index_close(index);
        		return NULL;
   			}
   			for(int j;j<index->recs[i]->n_records; j++){
   				if(fread(&index->recs[i]->rec[j], sizeof(long), 1, index->fp)!=1){
        			index_close(index);
        			return NULL;
   				}
   			}

        }
    }
    return index;
}


/*
   int index_save(index_t* index);

   Saves the current state of index in the file it came from. Note
   that the name of the file in which the index is to be saved is not
   given.  See the NOTE to index_open.

   Parameters:
   index:  the index the function operates upon

   Returns:
   1:  index saved
   0:  error saving the index (cound not open file)

*/
int index_save(index_t* idx) {
    int i,j;
    if(idx==NULL){
        return 0;
    }
    fseek(idx->fp, 0, SEEK_SET);
    fwrite(&idx->n_records,1,  sizeof(int),idx->fp);
    fwrite(&idx->type, 1, sizeof(type_t), idx->fp);
    for(i=0; i<idx->n_records;i++){
        if(idx->type==STR){
            fwrite((char *)idx->recs[i]->key, 1, value_length(idx->type,idx->recs[i]->key), idx->fp);
        }else if(idx->type==INT){
            fwrite((int *)idx->recs[i]->key,1, value_length(idx->type,idx->recs[i]->key), idx->fp);
        }else if(idx->type==LLNG){
            fwrite((long long int *)idx->recs[i]->key, 1, value_length(idx->type,idx->recs[i]->key), idx->fp);
        }else if(idx->type==DBL){
            fwrite((double *)idx->recs[i]->key, 1, value_length(idx->type,idx->recs[i]->key), idx->fp);
        }
        
        fwrite(&idx->recs[i]->n_records, 1, sizeof(int), idx->fp);
        for(j=0; j<idx->recs[i]->n_records; j++){
            fwrite(&idx->recs[i]->rec[j], 1, sizeof(long), idx->fp);
        }
    }

    return 1;
}

int binary(irecord_t **array, void *key, int n, type_t type) {
    int low = 0;
    int high = n-1;
    int middle;
    if(array==NULL || key==NULL || n<1){
        return -1;
    }
    while(low <= high) {
        middle = (low+high) >> 1;
        if (value_cmp(type, array[middle]->key, (void*) key) == 0){
            return middle;
        }
        else if(value_cmp(type, array[middle]->key, (void*) key) > 0){
            high = middle - 1;
        }
        else{
            low = middle + 1;
        }
    }
    return -(middle+1); // Key not found.
}

/*
   Function: int index_put(index_t *index, int key, long pos);

   Puts a pair key-position in the index. Note that the key may be
   present in the index or not... you must manage both situation. Also
   remember that the index must be kept ordered at all times.

   Parameters:
   index:  the index the function operates upon
   key: the key of the record to be indexed (may or may not be already
        present in the index)
   pos: the position of the corresponding record in the table
        file. This is the datum that we will want to recover when we
        search for the key.

   Return:
   n>0:  after insertion the file now contains n unique keys
   0:    error inserting the key

*/

int index_put(index_t *idx, int key, long pos) {
    int m;
    if(idx==NULL || pos<0 ){
        return 0;
    }
    m = binary(idx->recs, (void *) &key, idx->n_records, idx->type);
    if(m >= 0){
        idx->recs[m]->n_records++;
        idx->recs[m]->rec = (long*) realloc(idx->recs[m]->rec, idx->recs[m]->n_records*sizeof(long));
        idx->recs[m]->rec[idx->recs[m]->n_records - 1] = pos;
    }
    else{
        m = -(m + 1);
        idx->n_records++;
        idx->recs = (irecord_t **)realloc(idx->recs, idx->n_records*sizeof(irecord_t));
        if(idx->n_records>1){
            if(value_cmp(idx->type,idx->recs[m]->key, (void *) &key)>0){
                for(int i = idx->n_records - 1; i > m; i--){
                    idx->recs[i] = idx->recs[i - 1];
                }
            } else if(value_cmp(idx->type,idx->recs[m]->key, (void *) &key)<0){
                for(int i = idx->n_records - 1; i > m+1; i--){
                    idx->recs[i] = idx->recs[i - 1];
                }
                m++;
            }else{
                return 0;
            }
        }

        idx->recs[m] = (irecord_t*)malloc(sizeof(irecord_t));
        if(idx->recs[m]==NULL){
            return 0;
        }

        idx->recs[m]->key=NULL;
        idx->recs[m]->key = (void*)malloc(sizeof(int));
        if(idx->recs[m]->key==NULL){
            return 0;
        }

        *((int *)idx->recs[m]->key) = key;
        idx->recs[m]->n_records = 1;

        idx->recs[m]->rec=NULL;
        idx->recs[m]->rec = (long*)malloc(sizeof(long));
        if(idx->recs[m]->rec==NULL){
            return 0;
        }

        idx->recs[m]->rec[0] = pos;
    }

    return idx->n_records;
}


/*
   Function: long *index_get(index_t *index, int key, int* nposs);

   Retrieves all the positions associated with the key in the index.

   Parameters:
   index:  the index the function operates upon
   key: the key of the record to be searched
   nposs: output paramters: the number of positions associated to this key

   Returns:

   pos: an array of *nposs long integers with the positions associated
        to this key
   NULL: the key was not found

   NOTE: the parameter nposs is not an array of integers: it is
   actually an integer variable that is passed by reference. In it you
   must store the number of elements in the array that you return,
   that is, the number of positions associated to the key. The call
   will be something like this:

   int n
   long **poss = index_get(index, key, &n);

   for (int i=0; i<n; i++) {
       Do something with poss[i]
   }

   ANOTHER NOTE: remember that the search for the key MUST BE DONE
   using binary search.

   FURTHER NOTE: the pointer returned belongs to this module. The
   caller guarantees that the values returned will not be changed.

*/
long *index_get(index_t *idx, int key, int* nposs) {
    int m;
    if(idx==NULL || nposs==NULL){
        return NULL;
    }
    m = binary(idx->recs, (void*) &key, idx->n_records, idx->type);
    if (m>=0) {
        *nposs=idx->recs[m]->n_records;
        return idx->recs[m]->rec;
    }else {
        return NULL;
    }

}


/*
   Closes the index by freeing the allocated resources. No operation
   on the index will be possible after calling this function.

   Parameters:
   index:  the index the function operates upon

   Returns:
   Nothing

   NOTE: This function does NOT save the index on the file: you will
   have to call the function index_save for this.
*/
void index_close(index_t *idx) {
    int i;
    if(idx->recs!=NULL){
        for(i=0; i<idx->n_records; i++){
            free(idx->recs[i]->rec);
            free(idx->recs[i]->key);
            free(idx->recs[i]);
        }
        free(idx->recs);
    }
    fclose(idx->fp);
    free(idx);
    return;
}

/*
  Function: long **index_get_order(index_t *index, int n, int* nposs);

  Function useful for debugging but that should not be used otherwise:
  returns the nth record in the index. DO NOT USE EXCEPT FOR
  DEBUGGING. The test program uses it.

   Parameters:
   index:  the index the function operates upon
   n: number of the record to be returned
   key: output parameter: the key of the record
   nposs: output parameter: the number of positions associated to this key
   
   Returns:

   pos: an array of *nposs long integers with the positions associated
        to this key
   NULL: the key was not found   


   See index_get for explanation on nposs and pos: they are the same stuff
*/
long *index_get_order(index_t *index, int n, int *key, int* nposs) {
    
    if(index==NULL || n<0 || nposs==NULL || key==NULL || n>=index->n_records){
        return NULL;
    }
    *key=*(int *)index->recs[n]->key;
    *nposs=index->recs[n]->n_records;
    return index->recs[n]->rec;   
}