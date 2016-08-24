#!/usr/bin/python

import sys

# python avoid new line with print: sys.stdout.write or trailing comma
# http://stackoverflow.com/questions/11266068/python-avoid-new-line-with-print-command
# bidirectional clipboard not working virtual box windows to linux


puzzles = [ "t3bw21y", "t3ybw21", "t3w2by1", "t3w2y1b",     # level 1
            "t32wy1b", "t3w2b1y", "t32by1w", "t3yw21b",     # level 2
            "t3yw2b1", "t3w2yb1",                           # level 3
            "t3wb2y1", "t3y2wb1", "t3yb21w", "t32yb3w",     # level 4
            "t3wy2b1", "t3y2b1w", "t3ywb21", "t3wyb21"];    # level 5

last = 18

for i in range(1, last + 1):
#for i in range(0, last):
    
    # " duration1, puzzle1, elapsed1, answer1, correct1, "
    #sys.stdout.write("\" duration" + str(i) + ", puzzle" + str(i) + ", elapsed" + str(i) + ", answer" + str(i) + ", correct" + str(i))
    # if i == last:
    #     print "", # take off final comma
    # else:
    #     print ",",
    # print "\""
    
    # " :duration1, :puzzle1, :elapsed1, :answer1, :correct1, "
    # sys.stdout.write("\" :duration" + str(i) + ", :puzzle" + str(i) + ", :elapsed" + str(i) + ", :answer" + str(i) + ", :correct" + str(i))
    # if i == last:
    #     print "", # take off final comma
    # else:
    #     print ",",
    # print "\""

    # xe.param.setInt("duration1",     e->duration1);
    # xe.param.setInt("puzzle1",       e->puzzle1);
    # xe.param.setInt("elapsed1",      e->elapsed1);
    # xe.param.setInt("answer1",       e->answer1);
    # xe.param.setInt("correct1",      e->correct1);
    # print 'xe.param.setInt("duration' + str(i) + '",     e->duration' + str(i) + ');'
    # print 'xe.param.setInt("puzzle' + str(i) + '",       e->puzzle' + str(i) + ');'
    # print 'xe.param.setInt("elapsed' + str(i) + '",      e->elapsed' + str(i) + ');'
    # print 'xe.param.setInt("answer' + str(i) + '",       e->answer' + str(i) + ');'
    # print 'xe.param.setInt("correct' + str(i) + '",      e->correct' + str(i) + ');'
    # print

    # printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration1, it->puzzle1, it->elapsed1, it->answer1, it->correct1);
    #print 'printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration' + str(i) + ', it->puzzle' + str(i) + ', it->elapsed' + str(i) + ', it->answer' + str(i) + ', it->correct' + str(i) + ');'

    # printf("<td>duration1</td><td>puzzle1</td><td>elapsed1</td><td>answer1</td><td>correct1</td>\n");
    #print 'printf("<td>duration' + str(i) + '</td><td>puzzle' + str(i) + '</td><td>elapsed' + str(i) + '</td><td>answer' + str(i) + '</td><td>correct' + str(i) + '</td>\\n");'

    '''
        {
            "name": "ex",
            "type" : "game",
            "templateId": "game",
            "images": ["t3bw21y", "t3ybw21", "t3w2by1", "t3w2y1b",
                "t32wy1b", "t3w2b1y", "t32by1w", "t3yw21b",
                "t3yw2b1", "t3w2yb1",
                "t3wb2y1", "t3y2wb1", "t3yb21w", "t32yb3w",
                "t3wy2b1", "t3y2b1w", "t3ywb21", "t3wyb21"],
            "correct": -1
        },
        {
            "name": "ex18",
            "type" : "game",
            "templateId": "game",
            "image": "t3y2b1w.png",
            "correct": -1
        },
    '''


    print '    {'
    print '        "name": "' + puzzles[i-1] + '",'
    print '        "type" : "game",'
    print '        "templateId": "game",'
    print '        "image": "' + puzzles[i-1] + '.png",'
    print '        "puzzle": "' + str(i) + '",'
    print '        "level": "",'
    print '        "correct": -1'
    print '    },'
