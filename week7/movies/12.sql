-- MAIN --
SELECT title
    FROM movies
    WHERE movies.id IN (

        SELECT id
            FROM movies
            INNER JOIN stars ON movies.id = stars.movie_id
            WHERE stars.person_id IN (

                SELECT id
                    FROM people
                    WHERE people.name = 'Jennifer Lawrence'
            )

    )
    AND movies.id IN (

        SELECT id
            FROM movies
            INNER JOIN stars ON movies.id = stars.movie_id
            WHERE stars.person_id = (

                SELECT id
                    FROM people
                    WHERE people.name = 'Bradley Cooper'
            )

    )


