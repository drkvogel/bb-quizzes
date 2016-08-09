# bbquiz backend

### database

see bbquizzes/db/db.md
one table for each quiz

    sesh_id     incremental int8 session id, allocate from counter when test first cgi starts and passed to Javascript to be returned with results
    tinstruct   client time when instructions started
    tstart      client time when test started
    tfinish     client time when test completed
    tinsert
    ntests      number of puzzles completed
    durationN   duration of puzzle
    puzzleN     identifier for which puzzle is being shown
    elapsedN    time elapsed since tstart
    answerN     answer given
    correctN    whether answer is correct
    ...


    2016-08-08 16:07:16 cp@xrat ~/Projects
    $ git clone git@drkvogel.unfuddle.com:drkvogel/bb-quizzes.git

    cp_web_test
    2016-08-08 16:13:35 cp@xrat ~/Projects/bb-quizzes/db/sql
    $ ./create.sh