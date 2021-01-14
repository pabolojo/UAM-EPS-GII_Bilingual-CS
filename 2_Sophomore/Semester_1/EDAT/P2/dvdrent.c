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
    long rental_id, customer_id, store_id, staff_id, film_id;
    char pay[100];
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

    if (strcmp(argv[1], "new") == 0) {

        if (argc != 7) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s <customer Id> <film id> <staff id> <store id> <amount>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " <customer Id>: Id of the customer.\n");
    	    fprintf(stderr, " <film id>: Id of the film.\n"); 
            fprintf(stderr, " <staff id>: Id of the staff member.\n");
            fprintf(stderr, " <store id>: Id of the store.\n");
            fprintf(stderr, " <amount>: Amount of many paid.\n");
    	    return EXIT_FAILURE;
        }
        
        customer_id=atol(argv[2]);
        film_id=atol(argv[3]);
        staff_id=atol(argv[4]);
        store_id=atol(argv[5]);
        strcpy(pay, argv[6]);
        new_rental(stmt, ret, customer_id, film_id, staff_id, store_id, pay);

    } else if(strcmp(argv[1], "remove") == 0) {

        if (argc != 3) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s <rent Id>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " <rent Id> Id of the rental to remove.\n");
    	    return EXIT_FAILURE;
        }
        rental_id=atol(argv[2]);
        remove_rental(stmt, ret, rental_id);
    }else {
        fprintf(stderr, "Parameter %s is incorrect\n", argv[1]);
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
