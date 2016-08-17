
CREATE TABLE hoops (
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER    NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',

    duration1    INTEGER    NOT NULL,
    puzzle1      INTEGER    NOT NULL,
    elapsed1     INTEGER    NOT NULL,
    answer1      INTEGER    NOT NULL,
    correct1     INTEGER    NOT NULL,

    duration2    INTEGER    NOT NULL,
    puzzle2      INTEGER    NOT NULL,
    elapsed2     INTEGER    NOT NULL,
    answer2      INTEGER    NOT NULL,
    correct2     INTEGER    NOT NULL,

    duration3    INTEGER    NOT NULL,
    puzzle3      INTEGER    NOT NULL,
    elapsed3     INTEGER    NOT NULL,
    answer3      INTEGER    NOT NULL,
    correct3     INTEGER    NOT NULL,

    duration4    INTEGER    NOT NULL,
    puzzle4      INTEGER    NOT NULL,
    elapsed4     INTEGER    NOT NULL,
    answer4      INTEGER    NOT NULL,
    correct4     INTEGER    NOT NULL,

    duration5    INTEGER    NOT NULL,
    puzzle5      INTEGER    NOT NULL,
    elapsed5     INTEGER    NOT NULL,
    answer5      INTEGER    NOT NULL,
    correct5     INTEGER    NOT NULL,

    duration6    INTEGER    NOT NULL,
    puzzle6      INTEGER    NOT NULL,
    elapsed6     INTEGER    NOT NULL,
    answer6      INTEGER    NOT NULL,
    correct6     INTEGER    NOT NULL,

    duration7    INTEGER    NOT NULL,
    puzzle7      INTEGER    NOT NULL,
    elapsed7     INTEGER    NOT NULL,
    answer7      INTEGER    NOT NULL,
    correct7     INTEGER    NOT NULL,

    duration8    INTEGER    NOT NULL,
    puzzle8      INTEGER    NOT NULL,
    elapsed8     INTEGER    NOT NULL,
    answer8      INTEGER    NOT NULL,
    correct8     INTEGER    NOT NULL,

    duration9    INTEGER    NOT NULL,
    puzzle9      INTEGER    NOT NULL,
    elapsed9     INTEGER    NOT NULL,
    answer9      INTEGER    NOT NULL,
    correct9     INTEGER    NOT NULL,

    duration10    INTEGER   NOT NULL,
    puzzle10      INTEGER   NOT NULL,
    elapsed10     INTEGER   NOT NULL,
    answer10      INTEGER   NOT NULL,
    correct10     INTEGER   NOT NULL,

    duration11    INTEGER   NOT NULL,
    puzzle11      INTEGER   NOT NULL,
    elapsed11     INTEGER   NOT NULL,
    answer11      INTEGER   NOT NULL,
    correct11     INTEGER   NOT NULL,

    duration12    INTEGER   NOT NULL,
    puzzle12      INTEGER   NOT NULL,
    elapsed12     INTEGER   NOT NULL,
    answer12      INTEGER   NOT NULL,
    correct12     INTEGER   NOT NULL,

    duration13    INTEGER   NOT NULL,
    puzzle13      INTEGER   NOT NULL,
    elapsed13     INTEGER   NOT NULL,
    answer13      INTEGER   NOT NULL,
    correct13     INTEGER   NOT NULL,

    duration14    INTEGER   NOT NULL,
    puzzle14      INTEGER   NOT NULL,
    elapsed14     INTEGER   NOT NULL,
    answer14      INTEGER   NOT NULL,
    correct14     INTEGER   NOT NULL,

    duration15    INTEGER   NOT NULL,
    puzzle15      INTEGER   NOT NULL,
    elapsed15     INTEGER   NOT NULL,
    answer15      INTEGER   NOT NULL,
    correct15     INTEGER   NOT NULL,

    duration16    INTEGER   NOT NULL,
    puzzle16      INTEGER   NOT NULL,
    elapsed16     INTEGER   NOT NULL,
    answer16      INTEGER   NOT NULL,
    correct16     INTEGER   NOT NULL,

    duration17    INTEGER   NOT NULL,
    puzzle17      INTEGER   NOT NULL,
    elapsed17     INTEGER   NOT NULL,
    answer17      INTEGER   NOT NULL,
    correct17     INTEGER   NOT NULL,

    duration18    INTEGER   NOT NULL,
    puzzle18      INTEGER   NOT NULL,
    elapsed18     INTEGER   NOT NULL,
    answer18      INTEGER   NOT NULL,
    correct18     INTEGER   NOT NULL
);
\p\g
