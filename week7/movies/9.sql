SELECT DISTINCT name
    FROM people
    WHERE id IN (

        SELECT stars.person_id
            FROM (stars
            INNER JOIN movies ON stars.movie_id = movies.id)
            WHERE movies.year = '2004'
    )
ORDER BY birth;
