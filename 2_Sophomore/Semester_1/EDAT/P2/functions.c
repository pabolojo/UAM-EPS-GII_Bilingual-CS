#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include "functions.h"



void customer(SQLHSTMT stmt,SQLRETURN ret, char *first_name, char *last_name){

    char query[512];
    int flag=0;
    SQLINTEGER customer_id;
    SQLCHAR c_first_name[SIZE];
    SQLCHAR c_last_name[SIZE];
    SQLCHAR create_date[SIZE];
    SQLCHAR address[SIZE];
    SQLCHAR city[SIZE];
    SQLINTEGER postal_code;


    sprintf(query, "select customer.customer_id,  customer.first_name, customer.last_name, customer.create_date, address.address, city.city, address.postal_code from customer INNER JOIN address ON customer.address_id=address.address_id INNER JOIN city ON address.city_id=city.city_id where customer.first_name='%s' or customer.last_name='%s' ;", first_name,last_name);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

	SQLBindCol(stmt, 1, SQL_C_SLONG, &customer_id, sizeof(customer_id), NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, c_first_name, sizeof(c_first_name), NULL);
	SQLBindCol(stmt, 3, SQL_C_CHAR, c_last_name, sizeof(c_last_name), NULL);
	SQLBindCol(stmt, 4, SQL_C_CHAR, create_date, sizeof(create_date), NULL);
	SQLBindCol(stmt, 5, SQL_C_CHAR, address, sizeof(address), NULL);
	SQLBindCol(stmt, 6, SQL_C_CHAR, city, sizeof(city), NULL);
	SQLBindCol(stmt, 7, SQL_C_SLONG, &postal_code, sizeof(postal_code), NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("customer_id = %d\n", customer_id);
	    printf("first name = %s\n", c_first_name);
	    printf("last name = %s\n", c_last_name);
	    printf("create date = %s\n", create_date);
        printf("adress = %s\n", address);
        printf("city = %s\n", city);
        printf("postal code = %d\n", postal_code);
        printf("\n");
        flag++;
    }
    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt)) && flag==0){
        printf("Error in customer first name or last name. It does not exist in the database\n");
        printf("\n");
    }

    SQLCloseCursor(stmt);
    printf("\n");

    return;
}



void film(SQLHSTMT stmt, SQLRETURN ret, SQLHDBC dbc, char *title){
    char query[512];
    char query_aux[512];
    int flag=0;
    SQLINTEGER film_id;
    SQLCHAR f_title[SIZE];
    SQLCHAR release_year[SIZE];
    SQLINTEGER length;
    SQLCHAR description[SIZE];
    SQLCHAR first_name[SIZE];
    SQLCHAR last_name[SIZE];
    SQLCHAR language[SIZE];
    SQLHSTMT stmt_aux;

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt_aux);


    sprintf(query, " select film.film_id,film.title, film.release_year,film.length,film.description,language.name from film, language where film.title like '%%%s%%' and film.language_id=language.language_id ", title);


    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

	SQLBindCol(stmt, 1, SQL_C_SLONG, &film_id, sizeof(film_id), NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, f_title, sizeof(f_title), NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, release_year, sizeof(release_year), NULL);
    SQLBindCol(stmt, 4, SQL_C_SLONG, &length, sizeof(length), NULL);
    SQLBindCol(stmt, 5, SQL_C_CHAR, description, sizeof(description), NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, language, sizeof(language), NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("film_id = %d\n", film_id);
	    printf("film title = %s\n", f_title);
	    printf("release year = %s\n", release_year);
        printf("length = %d\n", length);
	    printf("description = %s\n", description);
        printf("language of the film = %s\n", language);
        printf("\n");
        printf("Actors that appear in %s : \n", f_title);

        sprintf(query_aux,"select actor.first_name, actor.last_name from actor,film_actor,film where film.film_id=film_actor.film_id and film_actor.actor_id=actor.actor_id and film.film_id= %d", film_id);

        SQLExecDirect(stmt_aux, (SQLCHAR*) query_aux, SQL_NTS);

        SQLBindCol(stmt_aux, 1, SQL_C_CHAR, first_name, sizeof(first_name), NULL);
        SQLBindCol(stmt_aux, 2, SQL_C_CHAR, last_name, sizeof(last_name), NULL);

        /* Loop through the rows in the result-set */
	    while (SQL_SUCCEEDED(ret = SQLFetch(stmt_aux))) {
            printf("first name of the actor = %s\n", first_name);
            printf("last name of the actor = %s\n", last_name);
        }

        SQLCloseCursor(stmt_aux);

        printf("\n");
        printf("\n");
        flag++;
    }
    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt)) && flag==0){
        printf("Error in film title. It does not exist in the database\n");
        printf("\n");

    }


    SQLCloseCursor(stmt);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt_aux);

    printf("\n");


    return;

}

void rent(SQLHSTMT stmt, SQLRETURN ret, long customer_id, char* initial_date, char *end_date){
    char query[512];
    int flag=0;
    SQLINTEGER rental_id;
    SQLINTEGER film_id;
    SQLINTEGER staff_id;
    SQLINTEGER store_id;
    SQLCHAR rental_date[SIZE];
    SQLCHAR title[SIZE];
    SQLCHAR first_name[SIZE];
    SQLDOUBLE amount;



    sprintf(query, " select rental.rental_id, rental.rental_date, inventory.film_id, film.title, rental.staff_id, staff.first_name, staff.store_id, payment.amount from rental inner join inventory on inventory.inventory_id=rental.inventory_id inner join film on film.film_id=inventory.film_id inner join staff on staff.staff_id=rental.staff_id inner join payment on payment.rental_id=rental.rental_id where rental.rental_date>'%s' and rental.rental_date<'%s' and payment.customer_id=%ld order by rental.rental_date", initial_date , end_date, customer_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

	SQLBindCol(stmt, 1, SQL_C_SLONG, &rental_id, sizeof(rental_id), NULL);
	SQLBindCol(stmt, 2, SQL_C_CHAR, rental_date, sizeof(rental_date), NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, &film_id, sizeof(film_id), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, title, sizeof(title), NULL);
    SQLBindCol(stmt, 5, SQL_C_SLONG, &staff_id, sizeof(staff_id), NULL);
	SQLBindCol(stmt, 6, SQL_C_CHAR, first_name, sizeof(first_name), NULL);
    SQLBindCol(stmt, 7, SQL_C_SLONG, &store_id, sizeof(store_id), NULL);
	SQLBindCol(stmt, 8, SQL_C_DOUBLE, &amount, sizeof(amount), NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("rental id = %d\n", rental_id);
	    printf("rental date = %s\n", rental_date);
        printf("film_id = %d\n", film_id);
        printf("film title = %s\n", title);
        printf("staff id = %d\n", staff_id);
        printf("first name of the staff = %s\n", first_name);
	    printf("store id = %d\n", store_id);
        printf("amount payed = %f\n", amount);
        printf("\n");
        flag++;
    }
    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt)) && flag==0){
        printf("Error in customer id, initial date or end date. It does not exist in the database\n");
        printf("\n");
    }

    SQLCloseCursor(stmt);
    printf("\n");

    return;

}

void recommend(SQLHSTMT stmt, SQLRETURN ret, SQLHDBC dbc, long customer_id){
    char *query;
    char *query2;
    int flag=0;
    char string_customer_id[10];
    char string_category_id[10];
    SQLINTEGER film_id;
    SQLINTEGER category_id;
    SQLCHAR title[SIZE];
    SQLCHAR category[SIZE];

    SQLHSTMT stmt_aux;

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt_aux);


    query=(char *)malloc(1000*sizeof(char));

    if(!query){
        return;
    }

    query2=(char *)malloc(1000*sizeof(char));

    if(!query2){
        return;
    }

    sprintf(string_customer_id," %ld", customer_id);

    strcpy(query, "select category.category_id from customer,rental, inventory,film,film_category, category where customer.customer_id= ");
    strcat(query, string_customer_id);
    strcat(query, " and rental.customer_id=customer.customer_id	AND rental.inventory_id = inventory.inventory_id AND inventory.film_id = film.film_id AND film.film_id = film_category.film_id AND film_category.category_id = category.category_id group by category.category_id,category.name	having count(*) in 	(select count(*) from customer,rental, inventory,film,film_category, category where customer.customer_id= ");
    strcat(query, string_customer_id);
    strcat(query, " and rental.customer_id=customer.customer_id AND rental.inventory_id = inventory.inventory_id AND inventory.film_id = film.film_id AND film.film_id = film_category.film_id AND film_category.category_id = category.category_id group by category.category_id,category.name order by count(*) desc limit 1)");


    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLBindCol(stmt, 1, SQL_C_SLONG, &category_id, sizeof(film_id), NULL);


    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        sprintf(string_category_id," %d", category_id);
        strcpy(query2,"select film.film_id, film.title, category.name from customer,rental, inventory,film,film_category, category where rental.customer_id=customer.customer_id AND rental.inventory_id = inventory.inventory_id AND inventory.film_id = film.film_id AND film.film_id = film_category.film_id AND film_category.category_id = category.category_id AND category.category_id= ");
        strcat(query2, string_category_id);
        strcat(query2," and film.film_id not in (select film.film_id from customer,rental,film, inventory where customer.customer_id= ");
        strcat(query2, string_customer_id);
        strcat(query2, " and rental.customer_id=customer.customer_id AND rental.inventory_id = inventory.inventory_id  AND inventory.film_id = film.film_id ) group by category.category_id,film.film_id, film.title order by count(*) desc limit 3");

        SQLExecDirect(stmt_aux, (SQLCHAR*) query2, SQL_NTS);

        SQLBindCol(stmt_aux, 1, SQL_C_SLONG, &film_id, sizeof(film_id), NULL);
        SQLBindCol(stmt_aux, 2, SQL_C_CHAR, title, sizeof(title), NULL);
	    SQLBindCol(stmt_aux, 3, SQL_C_CHAR, category, sizeof(category), NULL);
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt_aux))) {
            printf("film_id = %d\n", film_id);
	        printf("film title = %s\n", title);
	        printf("category = %s\n", category);
            printf("\n");
        }
        SQLCloseCursor(stmt_aux);
        flag++;
    }
    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt)) && flag==0){
        printf("Error in customer id. It does not exist in the database\n");
        printf("\n");
    }
    SQLCloseCursor(stmt);
    printf("\n");


    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt_aux);


    free(query);
    free(query2);
    return;
}


void new_rental(SQLHSTMT stmt, SQLRETURN ret, long customer_id, long film_id, long staff_id, long store_id, char *amount){
    char query[512];
    SQLINTEGER aux, inventory_id;
    double p;
    sscanf(amount, "%lf", &p);
    
    if(p<=0){
        printf("Error in amount\n");
	   return;
    }


    sprintf(query, "select customer_id from customer where customer_id=%ld",customer_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLBindCol(stmt, 1, SQL_C_SLONG, &aux, sizeof(aux), NULL);

    if (!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("Customer_Id ERROR\n");
      SQLCloseCursor(stmt);
      return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "select staff_id from staff where staff_id=%ld and store_id=%ld",staff_id, store_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLBindCol(stmt, 1, SQL_C_SLONG, &aux, sizeof(aux), NULL);

    if (!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("Staff_Id and/or Store_Id ERROR\n");
      SQLCloseCursor(stmt);
      return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "select inventory_id from inventory where film_id=%ld and store_id=%ld and inventory_id not in(select rental.inventory_id from rental inner join inventory on rental.inventory_id=inventory.inventory_id where film_id=%ld and rental.return_date is NULL)",film_id, store_id, film_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLBindCol(stmt, 1, SQL_C_SLONG, &inventory_id, sizeof(inventory_id), NULL);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("No DVD available\n");
      return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "INSERT INTO rental VALUES ((SELECT MAX(rental_id)+1 FROM rental), now(), %d, %ld, NULL, %ld, now())", inventory_id, customer_id, staff_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLBindCol(stmt, 1, SQL_C_SLONG, &aux, sizeof(aux), NULL);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("Rental recorded\n");
    }
    else{
      printf("ERROR creating new rental\n");
      SQLCloseCursor(stmt);
      return;
    }
    SQLCloseCursor(stmt);

    sprintf(query, "INSERT INTO payment VALUES ((SELECT MAX(payment_id)+1 FROM payment), %ld, %ld, (SELECT MAX(rental_id) FROM rental), '%s', now())", customer_id, staff_id, amount);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLBindCol(stmt, 1, SQL_C_SLONG, &aux, sizeof(aux), NULL);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("Payment recorded\n");
    }
    else{
      printf("ERROR storing payment\n");
      SQLCloseCursor(stmt);
      return;
    }

    SQLCloseCursor(stmt);
    return;
}


void remove_rental(SQLHSTMT stmt, SQLRETURN ret, long rental_id){
  char query[512];

  sprintf(query, "select rental_id from rental where rental_id=%ld",rental_id);

  SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

  if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
    printf("ERROR deleting rental from the databse with id: %ld. It doesn't exist\n", rental_id);
    SQLCloseCursor(stmt);
    return;
  }

  SQLCloseCursor(stmt);

  sprintf(query, "delete from payment where rental_id=%ld",rental_id);

  SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

  if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("Rental removed from payment\n");
  }else{
      printf("ERROR deleting rental on payment from the databse with id: %ld\n", rental_id);
      SQLCloseCursor(stmt);
      return;
  }

  sprintf(query, "delete from rental where rental_id=%ld",rental_id);

  SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

  if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("Rental removed from rentals\n");
  }else{
      printf("ERROR deleting rental on rentals from the databse with id: %ld\n", rental_id);
      SQLCloseCursor(stmt);
      return;
  }

  SQLCloseCursor(stmt);
  return;
}


void remove_film(SQLHSTMT stmt, SQLRETURN ret, long film_id){
    char query[512];

    sprintf(query, "select film_id from film where film_id=%ld",film_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("ERROR deleting film from the databse with id: %ld. It doesn't exist\n", film_id);
      SQLCloseCursor(stmt);
      return;
    }

    SQLCloseCursor(stmt);

    sprintf(query, "delete from payment using inventory, rental where  inventory.film_id =%ld and rental.inventory_id = inventory.inventory_id and rental.rental_id = payment.rental_id ",film_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Film removed from payment\n");
    }else{
        printf("ERROR deleting film on payment from the databse with id: %ld\n", film_id);
        SQLCloseCursor(stmt);
        return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "delete from rental using inventory where inventory.film_id = %ld and rental.inventory_id = inventory.inventory_id", film_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Film removed from rental\n");
    }else{
        printf("ERROR deleting film on rental from the databse with id: %ld\n", film_id);
        SQLCloseCursor(stmt);
        return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "delete from inventory where  film_id = %ld", film_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Film removed from inventory\n");
    }else{
        printf("ERROR deleting film on inventory from the databse with id: %ld\n", film_id);
        SQLCloseCursor(stmt);
        return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "delete from film_actor where  film_id = %ld", film_id);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Film removed from film_actor\n");
    }else{
        printf("ERROR deleting film on film_actor from the databse with id: %ld\n", film_id);
        SQLCloseCursor(stmt);
        return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "delete from film_category where  film_id = %ld", film_id);
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Film removed from film_category\n");
    }else{
        printf("ERROR deleting film on film_category from the databse with id: %ld\n", film_id);
        SQLCloseCursor(stmt);
        return;
    }

    SQLCloseCursor(stmt);


    sprintf(query, "delete from film where film_id = %ld", film_id);
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    if(!SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Film removed from database\n");
    }else{
        printf("ERROR deleting film on film from the databse with id: %ld\n", film_id);
    }

    SQLCloseCursor(stmt);
    return;

}
