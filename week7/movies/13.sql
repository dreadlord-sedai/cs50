SELECT people.name
FROM people
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (

    -- Kevin Bacon Movies ID --
    SELECT movies.id
        FROM movies
        INNER JOIN stars ON movies.id = stars.movie_id
            WHERE stars.person_id = (

            -- Kevin Bacon's ID --
            SELECT id
                FROM people
                WHERE name = 'Kevin Bacon' AND birth = 1958

        )
    )
AND people.name != 'Kevin Bacon';
