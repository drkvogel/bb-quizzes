-- see hoops.sql, matrix.sql

    -- sesh_id     incremental int8 session id, allocate from counter when test first cgi starts and passed to Javascript to be returned with results
    -- tinstruct   client time when instructions started
    -- tstart      client time when test started
    -- tfinish     client time when test completed
    -- tinsert
    -- ntests      number of puzzles completed
    -- durationN   duration of puzzle
    -- puzzleN     identifier for which puzzle is being shown
    -- elapsedN    time elapsed since tstart
    -- answerN     answer given
    -- correctN    whether answer is correct

-- CREATE TABLE matrix (
--     sesh_id     INTEGER       NOT NULL,
--     ntests      INTEGER       NOT NULL,
--     tinstruct   DATE          NOT NULL,
--     tstart      DATE          NOT NULL,
--     tfinish     DATE          NOT NULL,
--     tinsert     DATE          NOT NULL WITH DEFAULT 'now',

--     duration    DATE          NOT NULL,
--     puzzle      INTEGER       NOT NULL,  
--     elapsed     DATE          NOT NULL,
--     answer      INTEGER       NOT NULL,  
--     correct     INTEGER       NOT NULL,
-- );
-- \p\g


    -- id          INTEGER       NOT NULL,
    -- name        NVARCHAR(200) NOT NULL,
    -- indx        INTEGER       NOT NULL,
    -- nperson     INTEGER       NOT NULL WITH DEFAULT -1,
    -- np_info     NVARCHAR(100) NOT NULL WITH DEFAULT '',
    -- typ         INTEGER       NOT NULL,
    -- summary     NVARCHAR(100) NOT NULL,
    -- full        NVARCHAR(1000) NOT NULL,
    -- status      INTEGER       NOT NULL WITH DEFAULT 0,
    -- auth        VARCHAR(20)   NOT NULL,
    -- tinsert     DATE          NOT NULL WITH DEFAULT 'now',
    -- vid         INTEGER       NOT NULL WITH DEFAULT 0,
    -- tupdate     DATE          NOT NULL WITH DEFAULT 'now'



-- CREATE TABLE arm
--     (
--     id          INTEGER       NOT NULL,
--     name        NVARCHAR(200) NOT NULL,
--     indx        INTEGER       NOT NULL,
--     nperson     INTEGER       NOT NULL WITH DEFAULT -1,
--     np_info     NVARCHAR(100) NOT NULL WITH DEFAULT '',
--     typ         INTEGER       NOT NULL,
--     summary     NVARCHAR(100) NOT NULL,
--     full        NVARCHAR(1000) NOT NULL,
--     status      INTEGER       NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20)   NOT NULL,
--     tinsert     DATE          NOT NULL WITH DEFAULT 'now',
--     vid         INTEGER       NOT NULL WITH DEFAULT 0,
--     tupdate     DATE          NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE contact
--     (
--     id          INTEGER       NOT NULL,
--     id_owner    INTEGER       NOT NULL,
--     typ         INTEGER       NOT NULL,
--     location    INTEGER       NOT NULL,
--     priority    FLOAT8        NOT NULL WITH DEFAULT 0,
--     accuracy    INTEGER     NOT NULL,
--     value       NVARCHAR(200) NOT NULL,
--     comment     LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid         INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE creport
--     (
--     id      INTEGER     NOT NULL,
--     name        LONG NVARCHAR   NOT NULL,
--     rep_type    INTEGER     NOT NULL,
--     instruct    LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE date_range
--     (
--     id      INTEGER     NOT NULL,
--     id_owner    INTEGER     NOT NULL,
--     begin_txt   VARCHAR(80) NOT NULL,
--     begin_earliest  DATE        NOT NULL WITH DEFAULT '1/1/1900',
--     begin_latest    DATE        NOT NULL WITH DEFAULT '30/12/2037',
--     end_txt     VARCHAR(80) NOT NULL,
--     end_earliest    DATE        NOT NULL WITH DEFAULT '1/1/1900',
--     end_latest  DATE        NOT NULL WITH DEFAULT '30/12/2037',
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \g

-- CREATE TABLE dict_meaning
--     (
--     id      INTEGER     NOT NULL,
--     id_master   INTEGER     NOT NULL WITH DEFAULT 0,
--     name        LONG NVARCHAR   NOT NULL,
--     item_type   INTEGER     NOT NULL,
--     meaning     LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE dict_insert
--     (
--     id         INTEGER      NOT NULL,
--     name       LONG NVARCHAR    NOT NULL,
--     full       VARCHAR(80)  NOT NULL,
--     status     INTEGER      NOT NULL WITH DEFAULT 0,
--     auth       VARCHAR(20)  NOT NULL,
--     tinsert    DATE     NOT NULL WITH DEFAULT 'now',
--     vid        INTEGER      NOT NULL WITH DEFAULT 0,
--     tupdate    DATE     NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE email_def
--     (
--     id          INTEGER     NOT NULL,
--     name        NVARCHAR    NOT NULL,
--     descript    LONG NVARCHAR   NOT NULL,
--     auto_cc     LONG NVARCHAR   NOT NULL,
--     auto_bcc    LONG NVARCHAR   NOT NULL,
--     subject     LONG NVARCHAR   NOT NULL,
--     body        LONG NVARCHAR   NOT NULL,
--     access_read INTEGER     NOT NULL WITH DEFAULT 0,
--     access_edit INTEGER     NOT NULL WITH DEFAULT 0,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE email_priv
--     (
--     id      INTEGER     NOT NULL,
--     id_email    INTEGER     NOT NULL,
--     name        NVARCHAR(20)    NOT NULL,
--     priv_read   INTEGER     NOT NULL WITH DEFAULT 0,
--     priv_edit   INTEGER     NOT NULL WITH DEFAULT 0,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE fork
--     (
--     id      INTEGER     NOT NULL,
--     name        NVARCHAR(200)   NOT NULL,
--     nperson     INTEGER     NOT NULL WITH DEFAULT -1,
--     np_info     NVARCHAR(30)    NOT NULL WITH DEFAULT '',
--     eligibility LONG NVARCHAR   NOT NULL,
--     extras      LONG NVARCHAR   NOT NULL,
--     comment     LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE groop
--     (
--     id      INTEGER     NOT NULL,
--     name        NVARCHAR(200)   NOT NULL,
--     short_name  NVARCHAR(50)    NOT NULL,
--     city        NVARCHAR(100)   NOT NULL,
--     country     NVARCHAR(50)    NOT NULL,
--     comment     LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- /*---- INTER-OBJECT LINKAGES, N.B. ALWAYS "TYP_A < TYP_B" ----*/

-- CREATE TABLE linkz
--     (
--     id      INTEGER     NOT NULL,
--     typ_a       INTEGER     NOT NULL,
--     typ_b       INTEGER     NOT NULL,
--     id_a        INTEGER     NOT NULL,
--     id_b        INTEGER     NOT NULL,
--     id_domain   INTEGER     NOT NULL WITH DEFAULT 0,
--     link_type   INTEGER     NOT NULL WITH DEFAULT 0,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     descript    NVARCHAR(30)    NOT NULL WITH DEFAULT '',
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE meet
--     (
--     id         INTEGER      NOT NULL,
--     name       NVARCHAR(80) NOT NULL,
--     locatioN   NVARCHAR(80) NOT NULL,
--     city       NVARCHAR(50) NOT NULL,
--     country    NVARCHAR(50) NOT NULL,
--     year       INTEGER      NOT NULL,
--     start      DATE        NOT NULL,
--     end        DATE        NOT NULL,
--     status     INTEGER     NOT NULL WITH DEFAULT 0,
--     auth       VARCHAR(20) NOT NULL,
--     tinsert    DATE        NOT NULL WITH DEFAULT 'now',
--     vid        INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate    DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE oview
--     (
--     id      INTEGER     NOT NULL,
--     name        NVARCHAR(20)    NOT NULL,
--     title       NVARCHAR(50)    NOT NULL,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE staff
--     (
--     id      INTEGER     NOT NULL,
--     title       NVARCHAR(50)    NOT NULL,
--     given_name  NVARCHAR(50)    NOT NULL,
--     family_name NVARCHAR(50)    NOT NULL,
--     pref_name   NVARCHAR(50)    NOT NULL,
--     is_male     INTEGER     NOT NULL WITH DEFAULT -1,
--     institute   NVARCHAR(80)    NOT NULL,
--     department  NVARCHAR(80)    NOT NULL,
--     position    NVARCHAR(80)    NOT NULL,
--     comment     LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );

-- \p\g

-- CREATE TABLE steering_file
--     (
--     id          INTEGER         NOT NULL,
--     filename    NVARCHAR(150)    NOT NULL,
--     location    NVARCHAR(150)    NOT NULL,
--     long_title  NVARCHAR(150)    NOT NULL,
--     short_title NVARCHAR(150)    NOT NULL,
--     descrip     LONG NVARCHAR   NOT NULL,
-- --     descrip     VARCHAR(150),
--     status      INTEGER         NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20)     NOT NULL,
--     tinsert     DATE            NOT NULL WITH DEFAULT 'now',
--     vid         INTEGER         NOT NULL WITH DEFAULT 0,
--     tupdate     DATE            NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE steering_file_entry
--     (
--     id          INTEGER         NOT NULL,
--     id_file     INTEGER         NOT NULL,
--     id_fork     INTEGER         NOT NULL,
--     comparison  NVARCHAR(50)     NOT NULL,
--     notes       NVARCHAR(150)    NOT NULL,
--     status      INTEGER         NOT NULL WITH DEFAULT 0,  -- 0: normal, 1: high priority, 99: deleted
--     auth        VARCHAR(20)     NOT NULL,
--     tedit       DATE            NOT NULL WITH DEFAULT 'now', -- time of last edit
--     tinsert     DATE            NOT NULL WITH DEFAULT 'now',
--     vid         INTEGER         NOT NULL WITH DEFAULT 0,
--     tupdate     DATE            NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE trial
--     (
--     id      INTEGER     NOT NULL,
--     name        NVARCHAR(150)   NOT NULL,
--     nperson     INTEGER     NOT NULL WITH DEFAULT -1,
--     np_info     NVARCHAR(30)    NOT NULL WITH DEFAULT '',
--     eligibility LONG NVARCHAR   NOT NULL,
--     comment     LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );

-- \p\g

-- CREATE TABLE vconfig
--     (
--     id_domain   INTEGER     NOT NULL,
--     param       VARCHAR(20) NOT NULL,
--     ival        INTEGER     NOT NULL WITH DEFAULT 0,
--     sval        NVARCHAR(200)   NOT NULL WITH DEFAULT '',
--     tval        DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g

-- CREATE TABLE visit_event
-- (
--     id      INTEGER     NOT NULL,
--     id_link     INTEGER     NOT NULL,
--     event_code  INTEGER     NOT NULL,
--     note        LONG NVARCHAR   NOT NULL,
--     status      INTEGER     NOT NULL WITH DEFAULT 0,
--     auth        VARCHAR(20) NOT NULL,
--     tinsert     DATE        NOT NULL WITH DEFAULT 'now',
--     vid     INTEGER     NOT NULL WITH DEFAULT 0,
--     tupdate     DATE        NOT NULL WITH DEFAULT 'now'
--     );
-- \p\g
