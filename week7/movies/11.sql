SELECT title
FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.id IN (

    SELECT id
        FROM movies
        INNER JOIN stars ON movies.id = stars.movie_id
        WHERE stars.person_id = (

            SELECT id
                FROM people
                INNER JOIN stars ON people.id = stars.person_id
                WHERE people.name = 'Chadwick Boseman'
        )
    LIMIT 5
)
ORDER BY ratings.rating DESC;
