#!/usr/bin/python
# (on xrat and red)

# general
def print_commit():
    print "\p\g"

# trails

# practice-a    8 buttons
# part-a        25 buttons
# practice-b    8 buttons
# part-b        25 buttons

# ap == part a practice
# ar == part a real
# bp == part b practice
# br == part b real

ap_last = 8
ar_last = 25
bp_last = 8
br_last = 25
ap_last + ar_last + bp_last + br_last = trails_last

# std::string puzzle; # don't need
# int wrongClicks;  ->  wrong
# int duration;     ->  time
# int elapsed;      ->  total

def print_section(section, num):
    for i in range(1, num + 1):
        print "    " + section + "_"  + str(i) +  "_wrong    INTEGER2 NOT NULL,"
        print "    " + section + "_"  + str(i) +  "_time     INTEGER2 NOT NULL,"
        if section == 'br' and i == num:
            print "    " + section + "_"  + str(i) +  "_total    INTEGER1 NOT NULL", # take off final comma and no newline (comma after string)
        else:
            print "    " + section + "_"  + str(i) +  "_total    INTEGER1 NOT NULL,"
        print   # separate groups with newline

def print_trails_puzzle_fields():
    print """
CREATE TABLE trails ( NOT NULL
    sesh_id      INTEGER    NOT NULL,
    ntests       INTEGER2   NOT NULL,
    tinstruct    DATE       NOT NULL,
    tstart       DATE       NOT NULL,
    tfinish      DATE       NOT NULL,
    tinsert      DATE       NOT NULL WITH DEFAULT 'now',
    responses    LONG VARCHAR,
"""  

    print_section('ap', ap_last)
    print_section('ar', ar_last)
    print_section('bp', bp_last)
    print_section('br', br_last)

    comment_section('ap', ap_last)
    comment_section('ar', ar_last)
    comment_section('bp', bp_last)
    comment_section('br', br_last)

    print ");"

def comment_section(section, num):
    for i in range(1, num + 1):
        print "COMMENT ON COLUMN trails." + section + "_"  + str(i) +  "_wrong IS 'Number of wrong clicks before correct one';"
        print "COMMENT ON COLUMN trails." + section + "_"  + str(i) +  "_puzzle IS 'Time taken to click correct next circle since start of puzzle';"
        print "COMMENT ON COLUMN trails." + section + "_"  + str(i) +  "_elapsed IS 'Total time elapsed since start of whole game';"

def print_trails_comments():
    print "COMMENT ON COLUMN trails.sesh_id IS 'Session ID';"
    print "COMMENT ON COLUMN trails.ntests IS 'Number of puzzles completed';"
    print "COMMENT ON COLUMN trails.tinstruct IS 'Time the instructions were shown to the user';"
    print "COMMENT ON COLUMN trails.tstart IS 'Time the quiz was started';"
    print "COMMENT ON COLUMN trails.tfinish IS 'Time the quiz was finished';"
    print "COMMENT ON COLUMN trails.tinsert IS 'Time the row was inserted into the database (default ''now'')';"
    print "COMMENT ON COLUMN trails.responses IS 'Responses from quiz - blob of JSON data to be parsed by backend';"
    

print_trails_puzzle_fields()
print_commit()
print_trails_comments()
print_commit()


# cruft
    #     print "COMMENT ON COLUMN trails.duration" + str(i) + " IS 'Time taken to answer puzzle';"
    #     print "COMMENT ON COLUMN trails.puzzle" + str(i) + " IS 'Puzzle chosen by algorithm';"
    #     print "COMMENT ON COLUMN trails.elapsed" + str(i) + " IS 'Cumulative time elapsed';"
    #     print "COMMENT ON COLUMN trails.answer" + str(i) + " IS 'Answer given by user';"
    #     print "COMMENT ON COLUMN trails.correct" + str(i) + " IS 'Correct answer';"
    # Number of wrong clicks before correct one
    # Time taken to click correct next circle since start of puzzle
    # Total time elapsed since start of whole game
