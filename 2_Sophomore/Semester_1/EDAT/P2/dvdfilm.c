#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "functions.h"

int main(int argc, char** argv) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    int i=0;
    long film_id;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);


    if (argc < 2) {
    	fprintf(stderr, "Error in the input parameters:\n\n");
    	fprintf(stderr, "%s\n", argv[0]);
    	return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "remove") == 0) {
        
        if (argc != 3) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s <film id>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " <film id>: Id of the film to remove.\n");
    	    return EXIT_FAILURE;
        }
        film_id=atol(argv[2]);

        remove_film(stmt, ret, film_id);

    }else {
        fprintf(stderr, "Parameter %s is incorrect\n", argv[i]);
    }

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
