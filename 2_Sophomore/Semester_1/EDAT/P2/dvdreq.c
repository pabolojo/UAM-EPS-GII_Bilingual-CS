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
    char first_name[SIZE];
    char last_name[SIZE];
    char title[SIZE];
    char initial_date[SIZE];
    char end_date[SIZE];
    int i=0;
    long customer_id;

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

    if (strcmp(argv[1], "customer") == 0) {

        if (argc != 6) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s -n <First Name> -a <Last Name>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " -n: Name of the customer.\n");
    	    fprintf(stderr, " -a: Last name of the customer.\n");
    	    return EXIT_FAILURE;
        }

        for(i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0) {
                strcpy(first_name, argv[++i]);
            } else if (strcmp(argv[i], "-a") == 0) {
                strcpy(last_name, argv[++i]);
            } else {
              fprintf(stderr, "Parameter %s is incorrect\n", argv[i]);
              return EXIT_FAILURE;
            }
        }

        customer(stmt, ret, first_name, last_name);

    } else if(strcmp(argv[1], "film") == 0) {

        if (argc < 3) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s <title>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " <title>: Title of the film.\n");
    	    return EXIT_FAILURE;
        }

        for(i = 2; i < argc; i++){
            if(i==2){
                strcpy(title, argv[i]);
            } else {
                strcat(title," ");
                strcat(title,argv[i]);
            }
        }

        film(stmt, ret, dbc, title);
    }else if(strcmp(argv[1], "rent") == 0) {
        if (argc != 5) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s <customer Id> <init date> <end date>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " <customer Id>: Id of the customer.\n");
            fprintf(stderr, " <init date>: Initial date of the rental in format YYYY-MM-DD.\n");
            fprintf(stderr, " <end date>: End date of the rental in format YYYY-MM-DD.\n");
    	    return EXIT_FAILURE;
        }

        for(i = 2; i < argc; i++){
            if(i==2){
                customer_id=atoi(argv[i]);
            } else if (i==3){
                strcpy(initial_date, argv[i]);
            } else if (i==4){
                strcpy(end_date, argv[i]);
            }else{
                return EXIT_FAILURE;
            }
        }

        rent(stmt, ret, customer_id, initial_date, end_date);

    }else if(strcmp(argv[1], "recommend") == 0) {

        if (argc != 3) {
    	    fprintf(stderr, "Error in the input parameters:\n\n");
    	    fprintf(stderr, "%s <customer Id>\n", argv[0]);
    	    fprintf(stderr, "Where:\n");
    	    fprintf(stderr, " <customer Id>: Id of the customer.\n");
    	    return EXIT_FAILURE;
        }

        customer_id=atoi(argv[2]);

        recommend(stmt, ret, dbc, customer_id);

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
