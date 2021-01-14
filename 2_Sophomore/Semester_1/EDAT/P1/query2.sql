SELECT customer.customer_id, 
       customer.first_name, 
       customer.last_name, 
       Count(*) 
FROM   rental, 
       customer 
WHERE  rental.customer_id = customer.customer_id 
GROUP  BY customer.customer_id, 
          customer.first_name 
HAVING Count(*) IN (SELECT Count(*) 
                    FROM   rental 
                    GROUP  BY customer_id 
                    ORDER  BY Count(*) DESC 
                    LIMIT  1) 
