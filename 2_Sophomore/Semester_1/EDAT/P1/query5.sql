SELECT language.name 
FROM   language 
WHERE  language.language_id IN(SELECT film.language_id 
                               FROM   rental, 
                                      inventory, 
                                      film 
                               WHERE  rental.inventory_id = 
                                      inventory.inventory_id 
                                      AND inventory.film_id = film.film_id 
                               GROUP  BY film.language_id 
                               HAVING Count(film.language_id) IN 
                                      (SELECT 
                                      Count(film.language_id) 
                                                                  FROM   rental, 
                                      inventory, 
                                      film 
                                                                  WHERE 
                                      rental.inventory_id = 
       inventory.inventory_id 
       AND inventory.film_id = film.film_id 
       GROUP  BY film.language_id 
       ORDER  BY Count(film.language_id) DESC 
       LIMIT  1))
