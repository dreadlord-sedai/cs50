-- top 5 Longest song names Sort by duration_ms DESC --
SELECT name
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;
