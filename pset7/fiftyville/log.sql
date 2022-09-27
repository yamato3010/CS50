-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports;
SELECT * FROM interviews;
--crime reportsに7月28日の10時に～で行われたと書いてあったため
SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10;
--インタビューから、盗難から十五分以内に出ていったと書いてあるので15分いない位に出てきた人を調べる
SELECT * FROM people WHERE license_plate = "5P2BI95" OR license_plate =SE "94KL13X" OR license_plate = "6P58WS2"  OR license_plate = "4328GD8"  OR license_plate = "G412CB7"  OR license_plate = "L93JTIZ" OR license_plate = "322W7JE" OR license_plate = "0NTHK55";
--インタビューから逃走後電話したらしいのでその日に電話した人をあぶりだす
SELECT * FROM phone_calls WHERE month = 7 AND day = 28;
--インタビューから29日の一ヴァン速いフライトなので
SELECT * FROM flights WHERE month = 7 AND day = 29;
--一番早いフライトはフライトid 36番 8 → 4 の Fiftyville→Londonだったので
SELECT * FROM passengers WHERE flight_id = 36;
--載っていた人の名前を求める
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
--ATM
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND  atm_location = "Fifer Street" AND transaction_type = "withdraw";
--インタビューに基づいてatm_transactionsの情報を求める
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND  atm_location = "Fifer Street" AND transaction_type = "withdraw";
--bank_accountsから事件当日に取引をしたaccount_numberを求める
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND  atm_location = "Fifer Street" AND transaction_type = "withdraw");
--ATMから金を下ろし、電話もかけ、飛行機にも乗っていたので犯人はErnest
SELECT name FROM people WHERE id = 686048;
--事件日に犯人と1分以内電話した人の電話番号を取得
SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND caller = "(367) 555-5533" AND duration < "60" ;
--共犯者を取得
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND caller = "(367) 555-5533" AND duration < "60");