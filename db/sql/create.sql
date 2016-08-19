
CREATE TABLE hoops (
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER    NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',

    duration1    DATE          NOT NULL,
    puzzle1      INTEGER       NOT NULL,
    elapsed1     DATE          NOT NULL,
    answer1      INTEGER       NOT NULL,
    correct1     INTEGER       NOT NULL,

    duration2    DATE          NOT NULL,
    puzzle2      INTEGER       NOT NULL,
    elapsed2     DATE          NOT NULL,
    answer2      INTEGER       NOT NULL,
    correct2     INTEGER       NOT NULL,

    duration3    DATE          NOT NULL,
    puzzle3      INTEGER       NOT NULL,
    elapsed3     DATE          NOT NULL,
    answer3      INTEGER       NOT NULL,
    correct3     INTEGER       NOT NULL,

    duration4    DATE          NOT NULL,
    puzzle4      INTEGER       NOT NULL,
    elapsed4     DATE          NOT NULL,
    answer4      INTEGER       NOT NULL,
    correct4     INTEGER       NOT NULL,

    duration5    DATE          NOT NULL,
    puzzle5      INTEGER       NOT NULL,
    elapsed5     DATE          NOT NULL,
    answer5      INTEGER       NOT NULL,
    correct5     INTEGER       NOT NULL,

    duration6    DATE          NOT NULL,
    puzzle6      INTEGER       NOT NULL,
    elapsed6     DATE          NOT NULL,
    answer6      INTEGER       NOT NULL,
    correct6     INTEGER       NOT NULL,

    duration7    DATE          NOT NULL,
    puzzle7      INTEGER       NOT NULL,
    elapsed7     DATE          NOT NULL,
    answer7      INTEGER       NOT NULL,
    correct7     INTEGER       NOT NULL,

    duration8    DATE          NOT NULL,
    puzzle8      INTEGER       NOT NULL,
    elapsed8     DATE          NOT NULL,
    answer8      INTEGER       NOT NULL,
    correct8     INTEGER       NOT NULL,

    duration9    DATE          NOT NULL,
    puzzle9      INTEGER       NOT NULL,
    elapsed9     DATE          NOT NULL,
    answer9      INTEGER       NOT NULL,
    correct9     INTEGER       NOT NULL,

    duration10    DATE          NOT NULL,
    puzzle10      INTEGER       NOT NULL,
    elapsed10     DATE          NOT NULL,
    answer10      INTEGER       NOT NULL,
    correct10     INTEGER       NOT NULL,

    duration11    DATE          NOT NULL,
    puzzle11      INTEGER       NOT NULL,
    elapsed11     DATE          NOT NULL,
    answer11      INTEGER       NOT NULL,
    correct11     INTEGER       NOT NULL,

    duration12    DATE          NOT NULL,
    puzzle12      INTEGER       NOT NULL,
    elapsed12     DATE          NOT NULL,
    answer12      INTEGER       NOT NULL,
    correct12     INTEGER       NOT NULL,

    duration13    DATE          NOT NULL,
    puzzle13      INTEGER       NOT NULL,
    elapsed13     DATE          NOT NULL,
    answer13      INTEGER       NOT NULL,
    correct13     INTEGER       NOT NULL,

    duration14    DATE          NOT NULL,
    puzzle14      INTEGER       NOT NULL,
    elapsed14     DATE          NOT NULL,
    answer14      INTEGER       NOT NULL,
    correct14     INTEGER       NOT NULL,

    duration15    DATE          NOT NULL,
    puzzle15      INTEGER       NOT NULL,
    elapsed15     DATE          NOT NULL,
    answer15      INTEGER       NOT NULL,
    correct15     INTEGER       NOT NULL,

    duration16    DATE          NOT NULL,
    puzzle16      INTEGER       NOT NULL,
    elapsed16     DATE          NOT NULL,
    answer16      INTEGER       NOT NULL,
    correct16     INTEGER       NOT NULL,

    duration17    DATE          NOT NULL,
    puzzle17      INTEGER       NOT NULL,
    elapsed17     DATE          NOT NULL,
    answer17      INTEGER       NOT NULL,
    correct17     INTEGER       NOT NULL,

    duration18    DATE          NOT NULL,
    puzzle18      INTEGER       NOT NULL,
    elapsed18     DATE          NOT NULL,
    answer18      INTEGER       NOT NULL,
    correct18     INTEGER       NOT NULL
);
\p\g
COMMENT ON COLUMN hoops.sesh_id IS 'Session ID';
COMMENT ON COLUMN hoops.ntests IS 'Number of puzzles completed';
COMMENT ON COLUMN hoops.tinstruct IS 'Time the instructions were shown to the user';
COMMENT ON COLUMN hoops.tstart IS 'Time the quiz was started';
COMMENT ON COLUMN hoops.tfinish IS 'Time the quiz was finished';
COMMENT ON COLUMN hoops.tinsert IS 'Time the row was inserted into the database (default ''now'')';
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

    duration1    DATE          NOT NULL,
    elapsed1     DATE          NOT NULL,
    answer1      INTEGER       NOT NULL,
    correct1     INTEGER       NOT NULL,

    duration2    DATE          NOT NULL,
    elapsed2     DATE          NOT NULL,
    answer2      INTEGER       NOT NULL,
    correct2     INTEGER       NOT NULL,

    duration3    DATE          NOT NULL,
    elapsed3     DATE          NOT NULL,
    answer3      INTEGER       NOT NULL,
    correct3     INTEGER       NOT NULL,

    duration4    DATE          NOT NULL,
    elapsed4     DATE          NOT NULL,
    answer4      INTEGER       NOT NULL,
    correct4     INTEGER       NOT NULL,

    duration5    DATE          NOT NULL,
    elapsed5     DATE          NOT NULL,
    answer5      INTEGER       NOT NULL,
    correct5     INTEGER       NOT NULL,

    duration6    DATE          NOT NULL,
    elapsed6     DATE          NOT NULL,
    answer6      INTEGER       NOT NULL,
    correct6     INTEGER       NOT NULL,

    duration7    DATE          NOT NULL,
    elapsed7     DATE          NOT NULL,
    answer7      INTEGER       NOT NULL,
    correct7     INTEGER       NOT NULL,

    duration8    DATE          NOT NULL,
    elapsed8     DATE          NOT NULL,
    answer8      INTEGER       NOT NULL,
    correct8     INTEGER       NOT NULL,

    duration9    DATE          NOT NULL,
    elapsed9     DATE          NOT NULL,
    answer9      INTEGER       NOT NULL,
    correct9     INTEGER       NOT NULL,

    duration10    DATE          NOT NULL,
    elapsed10     DATE          NOT NULL,
    answer10      INTEGER       NOT NULL,
    correct10     INTEGER       NOT NULL,

    duration11    DATE          NOT NULL,
    elapsed11     DATE          NOT NULL,
    answer11      INTEGER       NOT NULL,
    correct11     INTEGER       NOT NULL,

    duration12    DATE          NOT NULL,
    elapsed12     DATE          NOT NULL,
    answer12      INTEGER       NOT NULL,
    correct12     INTEGER       NOT NULL,

    duration13    DATE          NOT NULL,
    elapsed13     DATE          NOT NULL,
    answer13      INTEGER       NOT NULL,
    correct13     INTEGER       NOT NULL,

    duration14    DATE          NOT NULL,
    elapsed14     DATE          NOT NULL,
    answer14      INTEGER       NOT NULL,
    correct14     INTEGER       NOT NULL,

    duration15    DATE          NOT NULL,
    elapsed15     DATE          NOT NULL,
    answer15      INTEGER       NOT NULL,
    correct15     INTEGER       NOT NULL,

    duration16    DATE          NOT NULL,
    elapsed16     DATE          NOT NULL,
    answer16      INTEGER       NOT NULL,
    correct16     INTEGER       NOT NULL,

    duration17    DATE          NOT NULL,
    elapsed17     DATE          NOT NULL,
    answer17      INTEGER       NOT NULL,
    correct17     INTEGER       NOT NULL,

    duration18    DATE          NOT NULL,
    elapsed18     DATE          NOT NULL,
    answer18      INTEGER       NOT NULL,
    correct18     INTEGER       NOT NULL
);
\p\g
COMMENT ON COLUMN matrix.sesh_id IS 'Session ID';
COMMENT ON COLUMN matrix.ntests IS 'Number of puzzles completed';
COMMENT ON COLUMN matrix.tinstruct IS 'Time the instructions were shown to the user';
COMMENT ON COLUMN matrix.tstart IS 'Time the quiz was started';
COMMENT ON COLUMN matrix.tfinish IS 'Time the quiz was finished';
COMMENT ON COLUMN matrix.tinsert IS 'Time the row was inserted into the database (default ''now'')';
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
