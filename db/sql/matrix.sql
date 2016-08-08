
CREATE TABLE matrix (
    sesh_id     INTEGER       NOT NULL,
    ntests      INTEGER       NOT NULL,
    tinstruct   DATE          NOT NULL,
    tstart      DATE          NOT NULL,
    tfinish     DATE          NOT NULL,
    tinsert     DATE          NOT NULL WITH DEFAULT 'now',

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
    correct18     INTEGER       NOT NULL,


);
\p\g