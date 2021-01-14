SELECT Extract(year FROM rental_date), 
       Count(*) 
FROM   rental 
GROUP  BY Extract(year FROM rental_date) 
