/*
    Project: EDAT Lab 3 test program
    File:    table.h
    Author:  Simone Santini
    Rev.     1.0
    Date:    10/13/2019  (check it out: it's Sunday!
                          and I am here, working for you.
                          Praise to the commmitted professor.)

    File in which YOU (Yes: you!) have to implement the functions defined in
    the file table.h. The functions are defined in this file, but they are
    left empty or return dummy values. It is up to you to implement them
    to guarantee the functionality expressed in table.h
*/
#include "table.h"
#include "type.h"

/*
    This is the structure that contains the data relative to a table. You
    have to implement it. Keep in mind that all the information about the table
    that the functions have is in this structure, so you must put in there
    all that is needed for the correct work of the functions
*/

struct table_ {
    FILE *fp;
	int columns;
    int row;
    type_t *types;
    long fpos;
    void **last_row;
};

/*
    void table_create(char* path, int ncols, type_t* types);

    Stores an empty table in a newly created file.

    Note that this function does not return any value nor does it do anything
    in memory. It creates a new file, stores in it a header that indicates
    the number of columns, the types of these columns, and that the table
    has 0 records. Then closes the file and returns.

    Parameters:
    path:    path name (referred to the current directory) of the file
             where the table is to be stored.
    ncols:   number of columns of the table.
    types:   array of ncols elements of type type_t with the type of each
             one of the columns (see type.h and type.c for details on the
             types recognized by the table).

    Returns:
        1: table created
        0: error in creation

    WARNING: if the file specified in path already exists, this function
    erases it and creates a new one. That is, all the data contained in the
    file will be lost.
*/
int table_create(char* path, int ncols, type_t* types) {
    FILE *fp=NULL;
    int nrows=0;
    if(!path || ncols<1 || !types){
        return 0;
    }
    fp=fopen(path, "w");
    if(fp==NULL){
        return 0;
    }

    fwrite(&ncols,1,  sizeof(int),fp);
    fwrite(types, ncols, sizeof(type_t),  fp);


    fwrite(&nrows, 1, sizeof(int),  fp);

    fclose(fp);
    return 1;
}

/*
    table_t* table_open(char* path)

    Opens a table and returns the structure necessary to use it. The file
    <path> must exist for this function to succeeds. This functions
    allocates a table_t structure and fills in the necessary fields so that
    the other functions defined here can operate on the table.

    Parameters:
    path:   path name (referred to the current directory) of the file
            where the table is stored. The file must exist.

    Returns:
    A pointer to a newly allocated table_t structure with the information
    necessary to operate on the table (the table is NOT read in memory), or
    NULL is the file <path> does not exist.

    NOTE: The calling program should not release the structure returned
    by this function. Use table_close instead.
*/
table_t* table_open(char* path) {
    table_t *table=NULL;
    int pt=0;
    int i;
    int ncols, nrows;
	if(!path){
		return NULL;
	}

	table=(table_t *)malloc(sizeof(table_t));
	if(table==NULL){
		return NULL;
	}

    table->fp=NULL;
    table->fp=fopen(path,"r+");
    if(table->fp==NULL){
        table_close(table);
        return NULL;
    }

    fseek(table->fp, pt, SEEK_SET);

    if(fread(&ncols, sizeof(int), 1, table->fp)!=1){
        table_close(table);
        return NULL;
    }

    table->columns=(int)ncols;

    table->types=NULL;
    table->types=(type_t *)malloc((table->columns)*sizeof(type_t));

    if(table->types==NULL){
        table_close(table);
        return NULL;
    }

    for(i=0; i<table->columns; i++){
        if(fread(&table->types[i], sizeof(type_t),1, table->fp)!=1){
            table_close(table);
            return NULL;
        }
    }

    if(fread(&nrows, sizeof(int),1, table->fp)!=1){
        table_close(table);
        return NULL;
    }

    table->row=(int) nrows;

    table->fpos = ftell(table->fp);
    table->last_row=NULL;
    table->last_row=(void **)malloc(table->columns*sizeof(void *));

    if(table->last_row==NULL){
        table_close(table);
        return NULL;
    }
    table->last_row[0]=NULL;
    table->last_row[0] = (void **)malloc(sizeof(void *));
    if(table->last_row[0]==NULL){
        table_close(table);
        return NULL;
    }
  	return table;
}


/*
    void table_close(table_t* table);

    Closes a table freeing all the resources allocated. This function must
    leave the whole system in the state it was before the table was opened:
    all files closed, all memory released.

    Note that after calling this function, it will no longer be possible
    to operate on the table <table>.

    Parameters:
    table:  The table that we want to close.

    Returns:
        Nothing
*/
void table_close(table_t* table) {

    if(table==NULL){
        return;
    }

    free(table->types);
    if(table->last_row[0]!=NULL){
        free(table->last_row[0]);
        table->last_row[0]=NULL;
    }
    if(table->last_row!=NULL){
        free(table->last_row);
    }
    fclose(table->fp);
    table->fp=NULL;
    free(table);
    return;
}

/*
    int table_ncols(table_t* table);

    Returns the number of columns of the table <table>

    Parameters:
    table:  The table on which we want to operate.

    Returns:
        n>0:    The table has n columns
        n<0:    Incorrect parameter
*/
int table_ncols(table_t* table) {

    if(table==NULL){
        return -1;
    }

    return table->columns;
}


/*
    type_t*table_types(table_t* table);

    Returns an array containing the types of the columns of the table
    <table>.

    Parameters:
    table:  The table on which we want to operate.

    Returns:
    An array of table_ncols(table) element. Each element is of type type_t,
    and contains the type of the corresponding column. For the definition
    of type_t, see the file type.h/type.c. Returns NULL if the parameter
    is invalid.

    WARNING: The array that is returned is not a copy of the one used
    internally by these functions, but a pointer to the same array. The
    caller should not free the pointer returned by this function nor
    should it modify it in any way.
*/
type_t*table_types(table_t* table) {

    if(table==NULL){
        return NULL;
    }

    return table->types;
}

/*
    long table_first_pos(table_t* table);

    Returns the position of the file where the first record begin. Calling
    table_read_record with this value as position will result in reading
    the first record of the table (see the example at the beginning of this
    file.

    Parameters:
    table:  The table on which we want to operate.

    Returns:
    n>0:    the first record begins at position n in the file
    n<0:    error in the parameter
*/
long table_first_pos(table_t* table) {

    if(table==NULL){
      return -1;
    }

    return table->fpos;
}

/*
    long table_last_pos(table_t* table);

    Returns the last position of the file, that is, the position where a new
    record will be inserted upon calling table_insert_record. Note that
    table_insert_record does not use this function, which is used simply to
    give information to the calling program.

    Parameters:
    table:  The table on which we want to operate.

    Returns:
    n>0:    the new record begins at position n in the file
    n<=0:   error in the parameter
*/
long table_last_pos(table_t* table) {

    if(!table || !table->types || !table->fp){
      return -1;
    }

    fseek(table->fp, 0, SEEK_END);

    return ftell(table->fp);
}

/*
    long table_read_record(table_t* table, long pos);

    Reads a record that begins at a given position in the table file.

    Parameters:
    table:  The table on which we want to operate.
    pos:    Position in the file where the record begins. The pos-th byte
            in the file must be the beginning of a record; if it is not, the
            result of the call will be unpredictable.

    Returns:
    n>0:     The next record in the file begins at position n
    n<0:     No record read, we had already reached the end of the file

    Note: this function reads the record, but it returns no data from that
    record. Use the function table_get_col to read the data of the record
    after it has been read.
*/
long table_read_record(table_t* table, long pos) {

    char *buffer, *temp;
    int len,i;
    if(!table || !table->types || !table->fp){
        return -1;
    }
    if(table_last_pos(table)<pos || table_first_pos(table) > pos){
        return -1;
    }
    if(table->last_row[0]!=NULL){
        free(table->last_row[0]);
        table->last_row[0]=NULL;
    }
    fseek(table->fp, pos, SEEK_SET);
    if(fread(&len, sizeof(int), 1, table->fp)!=1){
        return -1;
    }

    buffer = (char *) malloc(len);

    if(fread(buffer, len, 1, table->fp)!=1){
        return -1;
    }

    temp=buffer;

    for(i=0; i<table->columns; i++){
      table->last_row[i]=(void *)temp;
      temp += value_length(table->types[i], temp);
    }
    return ftell(table->fp);
}


/*
    void *table_get_col(table_t* table, int col)

    Returns the pointer to the data contained in the col-th column of the
    record currently in memory. The record must have been previpusly read
    using table_read_record. If no record was read in memory, the result
    will be unpredictable.

    Parameters:
    table:  The table on which we want to operate.
    col:    The column that we want to read, 0<=col<ncol,

    Returns:
    A pointer to the data that is contained in the column, or MULL if the
    column number is out of range. The way the data are interpreted
    depends on the type of the column, as specified by the col-th element
    of the array returned by table_types (see the example at the beginning
    of the file).
*/
void *table_get_col(table_t* table, int col) {

    if(!table || !table->types || !table->fp){
        return NULL;
    }
    return table->last_row[col];
}

/*  void table_insert_record(table_t* table, void** values);

    Inserts a record at the end of the file given the pointers to the
    values of each column.

    Parameters:
    table:  The table on which we want to operate.
    values: Array of ncol pointers to the data that are to be stored in the
            record. The element values[i] must be a pointer to a datum of the
            same type as the i-th column of the file. If this constraint is
            not respected, the results will be unpredictable.

    Returns:
    1: inserted OK
    0: error
*/
int table_insert_record(table_t* t, void** values) {
    int i;
    int nrows=t->row+1;
    int size=0;

    if(!t || !t->types || !t->fp){
        return 0;
    }
    if(table_last_pos(t)<0){
        return 0;
    }

    for(i=0; i<t->columns; i++){
        size += value_length(t->types[i], values[i]);
    }

    fwrite(&size,1 , sizeof(int), t->fp);
    for(i=0; i<t->columns; i++){
        if(t->types[i]==STR){
            fwrite((char *)values[i],1 ,  value_length(t->types[i], values[i]), t->fp);
        }else if(t->types[i]==INT){
            fwrite((int *)values[i], 1, value_length(t->types[i], values[i]), t->fp);
        }else if(t->types[i]==LLNG){
            fwrite((long long int *)values[i], 1,  value_length(t->types[i], values[i]), t->fp);
        }else if(t->types[i]==DBL){
            fwrite((double *)values[i], 1,  value_length(t->types[i], values[i]), t->fp);
        }
    }

    fseek(t->fp, t->fpos-sizeof(int), SEEK_SET);
    fwrite(&nrows, 1, sizeof(int),  t->fp);
    t->row+=1;

    return 1;
}
