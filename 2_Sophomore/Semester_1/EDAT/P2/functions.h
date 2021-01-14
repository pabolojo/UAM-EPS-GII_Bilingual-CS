#ifndef FUNCTIONS_H
#define FUNCTIONS_H



#define SIZE 100

void customer(SQLHSTMT stmt, SQLRETURN ret, char *first_name, char *last_name);
void film(SQLHSTMT stmt, SQLRETURN ret, SQLHDBC dbc, char *title);
void rent(SQLHSTMT stmt, SQLRETURN ret, long customer_id, char* initial_date, char *end_date);
void recommend(SQLHSTMT stmt, SQLRETURN ret, SQLHDBC dbc, long customer_id);
void remove_film(SQLHSTMT stmt, SQLRETURN ret, long film_id);
void remove_rental(SQLHSTMT stmt, SQLRETURN ret, long rental_id);
void new_rental(SQLHSTMT stmt, SQLRETURN ret, long customer_id, long film_id, long staff_id, long store_id, char *amount);

#endif
