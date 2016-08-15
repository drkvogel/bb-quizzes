

last = 18

for i in range(1, last + 1):
    print "    duration" + str(i) + "    DATE          NOT NULL,"
    print "    puzzle" + str(i) + "      INTEGER       NOT NULL,"
    print "    elapsed" + str(i) + "     DATE          NOT NULL,"
    print "    answer" + str(i) + "      INTEGER       NOT NULL,"
    if i == last:
        print "    correct" + str(i) + "     INTEGER       NOT NULL" # take off final comma
    else:
        print "    correct" + str(i) + "     INTEGER       NOT NULL,"    
    print

