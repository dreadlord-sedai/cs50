-- Keep a log of any SQL queries you execute as you solve the mystery.

-- The THIEF is:
-- The city the thief ESCAPED TO:
-- The ACCOMPLICE is:

-- Crime Scene Description --
SELECT description
    FROM crime_scene_reports
    WHERE year = 2023 AND month = 7
    AND day = 28 AND street = 'Humphrey Street';

    -- Thief stole duck at 10:15 am


-- Witness Interviews --
SELECT transcript
    FROM interviews
    WHERE year = 2023 AND month = 7
    AND day = 28;

    /*

    1. Thief got away car
        (bakery security footage)

    2. Suspect Recognized at ATM on Legget street before 10.15 am (money withdrawal)
             (atm_transactions)
             (bank accounts)

    3. Suspect called accomplice call < 1min.
            (Phone calls)
        Earliest flight out of fiftyville.
            Flight ticket
                (flights, airports)
                (passengers)

    */

-- Bakery Security cam footage --
SELECT activity, license_plate
    FROM bakery_security_logs
    WHERE year = 2023 AND month = 7
    AND day = 28 AND hour = 10
    AND minute > 15 AND activity = 'exit';

-- Licence plate from Bakery Footage of cars exiting after 10am and 15 min --
SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023 AND month = 7
    AND day = 28 AND hour = 10
    AND minute > 15 AND activity = 'exit';


-- Name of Licesce plate holders (Suspects at car)--
SELECT DISTINCT people.id, people.name
    FROM people
    INNER JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE people.license_plate IN (

        SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2023 AND month = 7
            AND day = 28 AND hour = 10
            AND minute > 15 AND activity = 'exit'
    );


-- Suspect account No at ATM in Legget street ---
SELECT account_number
    FROM atm_transactions
    WHERE year = 2023 AND month = 7
    AND day = 28 AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street';

-- id of Suspect with account number --
SELECT bank_accounts.person_id
    FROM bank_accounts
    INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE bank_accounts.account_number IN (

        SELECT account_number
            FROM atm_transactions
            WHERE year = 2023 AND month = 7
            AND day = 28 AND transaction_type = 'withdraw'
            AND atm_location = 'Leggett Street'

    );

-- Suspects Who at ATM--
SELECT people.id, people.name
    FROM people
    INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE people.id IN (

        SELECT bank_accounts.person_id
            FROM bank_accounts
            INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            WHERE bank_accounts.account_number IN (

                SELECT account_number
                    FROM atm_transactions
                    WHERE year = 2023 AND month = 7
                    AND day = 28 AND transaction_type = 'withdraw'
                    AND atm_location = 'Leggett Street'

            )

    );


-- Cross reference Suspects at Car and Suspects at ATM --

SELECT people.id, people.name
    FROM people
    WHERE people.id IN (

        SELECT DISTINCT people.id
            FROM people
            INNER JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
            WHERE people.license_plate IN (

                SELECT license_plate
                    FROM bakery_security_logs
                    WHERE year = 2023 AND month = 7
                    AND day = 28 AND hour = 10
                    AND minute > 15 AND activity = 'exit'
            )
    )
    AND people.id IN (

        SELECT people.id
            FROM people
            INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
            WHERE people.id IN (

                SELECT bank_accounts.person_id
                    FROM bank_accounts
                    INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    WHERE bank_accounts.account_number IN (

                        SELECT account_number
                            FROM atm_transactions
                            WHERE year = 2023 AND month = 7
                            AND day = 28 AND transaction_type = 'withdraw'
                            AND atm_location = 'Leggett Street'

                    )

            )
    );


-- Phone calls at 28th less than 60s  --
SELECT id, caller, receiver
    FROM phone_calls
    WHERE year = 2023 AND month = 7
    AND day = 28 AND duration < 60;

-- Suspects through Phone number --
SELECT DISTINCT people.id, people.name
    FROM people
    INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE people.phone_number IN (

        SELECT caller
            FROM phone_calls
            WHERE year = 2023 AND month = 7
            AND day = 28 AND duration < 60
    );


-- [FINAL SUSPECT LIST]Cross Reference Suspects Car,ATM and Phone calls --
SELECT people.id, people.name
    FROM people
    WHERE people.id IN (

        SELECT DISTINCT people.id
            FROM people
            INNER JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
            WHERE people.license_plate IN (

                SELECT license_plate
                    FROM bakery_security_logs
                    WHERE year = 2023 AND month = 7
                    AND day = 28 AND hour = 10
                    AND minute > 15 AND activity = 'exit'
            )
    )
    AND people.id IN (

        SELECT people.id
            FROM people
            INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
            WHERE people.id IN (

                SELECT bank_accounts.person_id
                    FROM bank_accounts
                    INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    WHERE bank_accounts.account_number IN (

                        SELECT account_number
                            FROM atm_transactions
                            WHERE year = 2023 AND month = 7
                            AND day = 28 AND transaction_type = 'withdraw'
                            AND atm_location = 'Leggett Street'

                    )

            )
    )
    AND people.id IN (

        SELECT DISTINCT people.id
            FROM people
            INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
            WHERE people.phone_number IN (

                SELECT caller
                    FROM phone_calls
                    WHERE year = 2023 AND month = 7
                    AND day = 28 AND duration < 60
            )

    );

-- Find first flight out of fiftyville --
SELECT id
    FROM flights
    WHERE year = 2023 AND month = 7
    AND day = 29 AND origin_airport_id = 8
    ORDER BY hour
    LIMIT 1;

-- Destination airport of first flight out of fiftyville --
SELECT *
    FROM airports
    INNER JOIN flights ON airports.id = flights.destination_airport_id
    WHERE flights.destination_airport_id = (

        SELECT destination_airport_id
            FROM flights
            WHERE year = 2023 AND month = 7
            AND day = 29 AND origin_airport_id = 8
            ORDER BY hour
            LIMIT 1

    );


-- Find passport numbers in passenger List in The flight --
SELECT passport_number
    FROM passengers
    INNER JOIN flights ON passengers.flight_id = flights.id
    WHERE passengers.flight_id IN (

        SELECT id
            FROM flights
            WHERE year = 2023 AND month = 7
            AND day = 29 AND origin_airport_id = 8
            ORDER BY hour
            LIMIT 1
    );


-- Find id of people with passport number in Passport number list --
SELECT people.id
    FROM people
    WHERE people.passport_number IN (

        SELECT passport_number
            FROM passengers
            INNER JOIN flights ON passengers.flight_id = flights.id
            WHERE passengers.flight_id IN (

                SELECT id
                    FROM flights
                    WHERE year = 2023 AND month = 7
                    AND day = 29 AND origin_airport_id = 8
                    ORDER BY hour
                    LIMIT 1
            )

    );

-- Cross reference Passport list and Final suspect list --
SELECT people.id, name
    FROM people
    WHERE people.id IN (

        SELECT DISTINCT people.id
            FROM people
            INNER JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
            WHERE people.license_plate IN (

                SELECT license_plate
                    FROM bakery_security_logs
                    WHERE year = 2023 AND month = 7
                    AND day = 28 AND hour = 10
                    AND minute > 15 AND activity = 'exit'
            )
    )
    AND people.id IN (

        SELECT people.id
            FROM people
            INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
            WHERE people.id IN (

                SELECT bank_accounts.person_id
                    FROM bank_accounts
                    INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                    WHERE bank_accounts.account_number IN (

                        SELECT account_number
                            FROM atm_transactions
                            WHERE year = 2023 AND month = 7
                            AND day = 28 AND transaction_type = 'withdraw'
                            AND atm_location = 'Leggett Street'

                    )

            )
    )
    AND people.id IN (

        SELECT DISTINCT people.id
            FROM people
            INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
            WHERE people.phone_number IN (

                SELECT caller
                    FROM phone_calls
                    WHERE year = 2023 AND month = 7
                    AND day = 28 AND duration < 60
            )

    )
    AND people.id IN (

        SELECT people.id
            FROM people
            WHERE people.passport_number IN (

                SELECT passport_number
                    FROM passengers
                    INNER JOIN flights ON passengers.flight_id = flights.id
                    WHERE passengers.flight_id IN (

                        SELECT id
                            FROM flights
                            WHERE year = 2023 AND month = 7
                            AND day = 29 AND origin_airport_id = 8
                            ORDER BY hour
                            LIMIT 1
                    )

            )
    );









/*

    SUSPECTS:
+--------+--------+
|   id   |  name  |
+--------+--------+
| 449774 | Taylor |
| 686048 | Bruce  |
+--------+--------+
 */
