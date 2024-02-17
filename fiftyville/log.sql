-- Keep a log of any SQL queries you execute as you solve the mystery.
--Crime log
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

--See interviews from the day the crime happened
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

--ATM Transactions on Leggett Street
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';

--Bakery secutriy logs within 10 minutes - shows license plate
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 and minute < 25;

--Phone calls on the day that were under a minute long
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

--Find people with bank account from ATM withdrawl
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street');

--The theif
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 and minute < 25)
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29 AND hour < 11))
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'));

--The city the theif escaped too
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name = 'Bruce')));

--
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce' AND year = 2021 AND month = 7 AND day = 28 AND duration < 60));