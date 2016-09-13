
CREATE TABLE hoops (
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER    NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',
    responses    LONG VARCHAR,   

    duration1    INTEGER,
    puzzle1      INTEGER,
    elapsed1     INTEGER,
    answer1      INTEGER,
    correct1     INTEGER,

    duration2    INTEGER,
    puzzle2      INTEGER,
    elapsed2     INTEGER,
    answer2      INTEGER,
    correct2     INTEGER,

    duration3    INTEGER,
    puzzle3      INTEGER,
    elapsed3     INTEGER,
    answer3      INTEGER,
    correct3     INTEGER,

    duration4    INTEGER,
    puzzle4      INTEGER,
    elapsed4     INTEGER,
    answer4      INTEGER,
    correct4     INTEGER,

    duration5    INTEGER,
    puzzle5      INTEGER,
    elapsed5     INTEGER,
    answer5      INTEGER,
    correct5     INTEGER,

    duration6    INTEGER,
    puzzle6      INTEGER,
    elapsed6     INTEGER,
    answer6      INTEGER,
    correct6     INTEGER,

    duration7    INTEGER,
    puzzle7      INTEGER,
    elapsed7     INTEGER,
    answer7      INTEGER,
    correct7     INTEGER,

    duration8    INTEGER,
    puzzle8      INTEGER,
    elapsed8     INTEGER,
    answer8      INTEGER,
    correct8     INTEGER,

    duration9    INTEGER,
    puzzle9      INTEGER,
    elapsed9     INTEGER,
    answer9      INTEGER,
    correct9     INTEGER,

    duration10    INTEGER,
    puzzle10      INTEGER,
    elapsed10     INTEGER,
    answer10      INTEGER,
    correct10     INTEGER,

    duration11    INTEGER,
    puzzle11      INTEGER,
    elapsed11     INTEGER,
    answer11      INTEGER,
    correct11     INTEGER,

    duration12    INTEGER,
    puzzle12      INTEGER,
    elapsed12     INTEGER,
    answer12      INTEGER,
    correct12     INTEGER,

    duration13    INTEGER,
    puzzle13      INTEGER,
    elapsed13     INTEGER,
    answer13      INTEGER,
    correct13     INTEGER,

    duration14    INTEGER,
    puzzle14      INTEGER,
    elapsed14     INTEGER,
    answer14      INTEGER,
    correct14     INTEGER,

    duration15    INTEGER,
    puzzle15      INTEGER,
    elapsed15     INTEGER,
    answer15      INTEGER,
    correct15     INTEGER,

    duration16    INTEGER,
    puzzle16      INTEGER,
    elapsed16     INTEGER,
    answer16      INTEGER,
    correct16     INTEGER,

    duration17    INTEGER,
    puzzle17      INTEGER,
    elapsed17     INTEGER,
    answer17      INTEGER,
    correct17     INTEGER,

    duration18    INTEGER,
    puzzle18      INTEGER,
    elapsed18     INTEGER,
    answer18      INTEGER,
    correct18     INTEGER
);
\p\g
COMMENT ON COLUMN hoops.sesh_id IS 'Session ID';
COMMENT ON COLUMN hoops.ntests IS 'Number of puzzles completed';
COMMENT ON COLUMN hoops.tinstruct IS 'Time the instructions were shown to the user';
COMMENT ON COLUMN hoops.tstart IS 'Time the quiz was started';
COMMENT ON COLUMN hoops.tfinish IS 'Time the quiz was finished';
COMMENT ON COLUMN hoops.tinsert IS 'Time the row was inserted into the database (default ''now'')';
COMMENT ON COLUMN hoops.responses IS 'Responses from quiz - blob of JSON data to be parsed by backend';
COMMENT ON COLUMN hoops.duration1 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle1 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed1 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer1 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct1 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration2 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle2 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed2 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer2 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct2 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration3 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle3 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed3 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer3 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct3 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration4 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle4 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed4 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer4 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct4 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration5 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle5 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed5 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer5 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct5 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration6 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle6 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed6 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer6 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct6 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration7 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle7 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed7 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer7 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct7 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration8 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle8 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed8 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer8 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct8 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration9 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle9 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed9 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer9 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct9 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration10 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle10 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed10 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer10 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct10 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration11 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle11 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed11 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer11 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct11 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration12 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle12 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed12 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer12 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct12 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration13 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle13 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed13 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer13 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct13 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration14 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle14 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed14 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer14 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct14 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration15 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle15 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed15 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer15 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct15 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration16 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle16 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed16 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer16 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct16 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration17 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle17 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed17 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer17 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct17 IS 'Correct answer';
COMMENT ON COLUMN hoops.duration18 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN hoops.puzzle18 IS 'Puzzle chosen by algorithm';
COMMENT ON COLUMN hoops.elapsed18 IS 'Cumulative time elapsed';
COMMENT ON COLUMN hoops.answer18 IS 'Answer given by user';
COMMENT ON COLUMN hoops.correct18 IS 'Correct answer';
\p\g

CREATE TABLE matrix (
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER    NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',
    responses    LONG VARCHAR,   

    duration1    INTEGER,
    elapsed1     INTEGER,
    answer1      INTEGER,
    correct1     INTEGER,

    duration2    INTEGER,
    elapsed2     INTEGER,
    answer2      INTEGER,
    correct2     INTEGER,

    duration3    INTEGER,
    elapsed3     INTEGER,
    answer3      INTEGER,
    correct3     INTEGER,

    duration4    INTEGER,
    elapsed4     INTEGER,
    answer4      INTEGER,
    correct4     INTEGER,

    duration5    INTEGER,
    elapsed5     INTEGER,
    answer5      INTEGER,
    correct5     INTEGER,

    duration6    INTEGER,
    elapsed6     INTEGER,
    answer6      INTEGER,
    correct6     INTEGER,

    duration7    INTEGER,
    elapsed7     INTEGER,
    answer7      INTEGER,
    correct7     INTEGER,

    duration8    INTEGER,
    elapsed8     INTEGER,
    answer8      INTEGER,
    correct8     INTEGER,

    duration9    INTEGER,
    elapsed9     INTEGER,
    answer9      INTEGER,
    correct9     INTEGER,

    duration10    INTEGER,
    elapsed10     INTEGER,
    answer10      INTEGER,
    correct10     INTEGER,

    duration11    INTEGER,
    elapsed11     INTEGER,
    answer11      INTEGER,
    correct11     INTEGER,

    duration12    INTEGER,
    elapsed12     INTEGER,
    answer12      INTEGER,
    correct12     INTEGER,

    duration13    INTEGER,
    elapsed13     INTEGER,
    answer13      INTEGER,
    correct13     INTEGER,

    duration14    INTEGER,
    elapsed14     INTEGER,
    answer14      INTEGER,
    correct14     INTEGER,

    duration15    INTEGER,
    elapsed15     INTEGER,
    answer15      INTEGER,
    correct15     INTEGER,

    duration16    INTEGER,
    elapsed16     INTEGER,
    answer16      INTEGER,
    correct16     INTEGER,

    duration17    INTEGER,
    elapsed17     INTEGER,
    answer17      INTEGER,
    correct17     INTEGER,

    duration18    INTEGER,
    elapsed18     INTEGER,
    answer18      INTEGER,
    correct18     INTEGER
);
\p\g
COMMENT ON COLUMN matrix.sesh_id IS 'Session ID';
COMMENT ON COLUMN matrix.ntests IS 'Number of puzzles completed';
COMMENT ON COLUMN matrix.tinstruct IS 'Time the instructions were shown to the user';
COMMENT ON COLUMN matrix.tstart IS 'Time the quiz was started';
COMMENT ON COLUMN matrix.tfinish IS 'Time the quiz was finished';
COMMENT ON COLUMN matrix.tinsert IS 'Time the row was inserted into the database (default ''now'')';
COMMENT ON COLUMN matrix.responses IS 'Responses from quiz - blob of JSON data to be parsed by backend';
COMMENT ON COLUMN matrix.duration1 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed1 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer1 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct1 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration2 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed2 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer2 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct2 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration3 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed3 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer3 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct3 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration4 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed4 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer4 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct4 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration5 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed5 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer5 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct5 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration6 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed6 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer6 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct6 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration7 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed7 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer7 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct7 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration8 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed8 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer8 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct8 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration9 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed9 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer9 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct9 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration10 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed10 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer10 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct10 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration11 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed11 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer11 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct11 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration12 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed12 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer12 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct12 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration13 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed13 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer13 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct13 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration14 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed14 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer14 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct14 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration15 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed15 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer15 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct15 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration16 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed16 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer16 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct16 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration17 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed17 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer17 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct17 IS 'Correct answer';
COMMENT ON COLUMN matrix.duration18 IS 'Time taken to answer puzzle';
COMMENT ON COLUMN matrix.elapsed18 IS 'Cumulative time elapsed';
COMMENT ON COLUMN matrix.answer18 IS 'Answer given by user';
COMMENT ON COLUMN matrix.correct18 IS 'Correct answer';
\p\g
