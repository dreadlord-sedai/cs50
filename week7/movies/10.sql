SELECT DISTINCT name
    FROM people
    INNER JOIN directors ON people.id = directors.person_id
    WHERE directors.movie_id IN (

        SELECT id
            FROM movies
            INNER JOIN ratings ON movies.id = ratings.movie_id
            WHERE ratings.rating >= 9.0
);
