SELECT name 
FROM   language 
WHERE  language_id IN(SELECT language_id 
                      FROM   film 
                      GROUP  BY language_id 
                      HAVING Count(*) IN(SELECT Count(*) 
                                         FROM   film 
                                         GROUP  BY language_id 
                                         LIMIT  1)) 
