#!/usr/bin/python
# (on xrat and red)

# general
def print_commit():
    print "\p\g"

# hoops
hoops_last = 18

def print_hoops_puzzle_fields():
    print """
CREATE TABLE hoops (
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER    NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',
"""  
    for i in range(1, hoops_last + 1):
        print "    duration" + str(i) + "    DATE          NOT NULL,"
        print "    puzzle" + str(i) + "      INTEGER       NOT NULL,"
        print "    elapsed" + str(i) + "     DATE          NOT NULL,"
        print "    answer" + str(i) + "      INTEGER       NOT NULL,"
        if i == hoops_last:
            print "    correct" + str(i) + "     INTEGER       NOT NULL", # take off final comma and no newline
        else:
            print "    correct" + str(i) + "     INTEGER       NOT NULL,"
        print   # separate groups with newline
    print ");"

def print_hoops_comments():
    print "COMMENT ON COLUMN hoops.sesh_id IS 'Session ID';"
    print "COMMENT ON COLUMN hoops.ntests IS 'Number of puzzles completed';"
    print "COMMENT ON COLUMN hoops.tinstruct IS 'Time the instructions were shown to the user';"
    print "COMMENT ON COLUMN hoops.tstart IS 'Time the quiz was started';"
    print "COMMENT ON COLUMN hoops.tfinish IS 'Time the quiz was finished';"
    print "COMMENT ON COLUMN hoops.tinsert IS 'Time the row was inserted into the database (default ''now'')';"
   
    for i in range(1, hoops_last + 1):
        print "COMMENT ON COLUMN hoops.duration" + str(i) + " IS 'Time taken to answer puzzle';"
        print "COMMENT ON COLUMN hoops.puzzle" + str(i) + " IS 'Puzzle chosen by algorithm';"
        print "COMMENT ON COLUMN hoops.elapsed" + str(i) + " IS 'Cumulative time elapsed';"
        print "COMMENT ON COLUMN hoops.answer" + str(i) + " IS 'Answer given by user';"
        print "COMMENT ON COLUMN hoops.correct" + str(i) + " IS 'Correct answer';"


print_hoops_puzzle_fields()
print_commit()
print_hoops_comments()
print_commit()

# matrix
matrix_last = 18

def print_matrix_puzzle_fields():
    print """
CREATE TABLE matrix (
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER    NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',
"""  
    for i in range(1, matrix_last + 1):
        print "    duration" + str(i) + "    DATE          NOT NULL,"
        print "    elapsed" + str(i) + "     DATE          NOT NULL,"
        print "    answer" + str(i) + "      INTEGER       NOT NULL,"
        if i == matrix_last:
            print "    correct" + str(i) + "     INTEGER       NOT NULL", # take off final comma and no newline
        else:
            print "    correct" + str(i) + "     INTEGER       NOT NULL,"
        print   # separate groups with newline
    print ");"

def print_commit():
    print "\p\g"

def print_matrix_comments():  
    print "COMMENT ON COLUMN matrix.sesh_id IS 'Session ID';"
    print "COMMENT ON COLUMN matrix.ntests IS 'Number of puzzles completed';"
    print "COMMENT ON COLUMN matrix.tinstruct IS 'Time the instructions were shown to the user';"
    print "COMMENT ON COLUMN matrix.tstart IS 'Time the quiz was started';"
    print "COMMENT ON COLUMN matrix.tfinish IS 'Time the quiz was finished';"
    print "COMMENT ON COLUMN matrix.tinsert IS 'Time the row was inserted into the database (default ''now'')';"
   
    for i in range(1, matrix_last + 1):
        print "COMMENT ON COLUMN matrix.duration" + str(i) + " IS 'Time taken to answer puzzle';"
        print "COMMENT ON COLUMN matrix.elapsed" + str(i) + " IS 'Cumulative time elapsed';"
        print "COMMENT ON COLUMN matrix.answer" + str(i) + " IS 'Answer given by user';"
        print "COMMENT ON COLUMN matrix.correct" + str(i) + " IS 'Correct answer';"

print_matrix_puzzle_fields()
print_commit()
print_matrix_comments()
print_commit()
