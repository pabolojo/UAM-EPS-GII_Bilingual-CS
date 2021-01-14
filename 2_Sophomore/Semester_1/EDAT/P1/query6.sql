SELECT rental.customer_id, 
       category.name
FROM   inventory, 
       rental, 
       film, 
       film_category, 
       category 
WHERE  rental.customer_id IN(SELECT customer_id 
                             FROM   rental 
                             GROUP  BY customer_id 
                             HAVING Count(*) IN (SELECT Count(*) 
                                                 FROM   rental 
                                                 GROUP  BY customer_id 
                                                 ORDER  BY Count(*) DESC 
                                                 LIMIT  1)) 
       AND rental.inventory_id = inventory.inventory_id 
       AND inventory.film_id = film.film_id 
       AND film.film_id = film_category.film_id 
       AND film_category.category_id = category.category_id 
GROUP  BY category.category_id, 
          rental.customer_id, 
          category.name 
HAVING ( customer_id, Count(*) ) IN (SELECT customer_id, 
                                            Max(x) 
                                     FROM   (SELECT rental.customer_id, 
                                                    category.category_id, 
                                                    Count(*) x, 
                                                    category.name 
                                             FROM   inventory, 
                                                    rental, 
                                                    film, 
                                                    film_category, 
                                                    category 
                                             WHERE 
              rental.customer_id IN(SELECT customer_id 
                                    FROM   rental 
                                    GROUP  BY customer_id 
                                    HAVING Count(*) IN (SELECT Count(*) 
                                                        FROM   rental 
                                                        GROUP  BY customer_id 
                                                        ORDER  BY Count(*) 
                                                       DESC 
                                                        LIMIT  1)) 
              AND rental.inventory_id = inventory.inventory_id 
              AND inventory.film_id = film.film_id 
              AND film.film_id = film_category.film_id 
              AND film_category.category_id = category.category_id 
                                             GROUP  BY category.category_id, 
                                                       rental.customer_id, 
                                                       category.name 
                                             ORDER  BY Count(*) DESC) tmp 
                                     GROUP  BY customer_id) 
ORDER  BY Count(*) DESC  
