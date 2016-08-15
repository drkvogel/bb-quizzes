#include "xquery.h"
#include "xexec.h"
#include "hoops.h"

bool insertHoopsRecord(const HoopsRecord *e) {
    std::string sql =
        "INSERT INTO hoops (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert,"
        " duration1, puzzle1, elapsed1, answer1, correct1, "
        " duration2, puzzle2, elapsed2, answer2, correct2, "
        " duration3, puzzle3, elapsed3, answer3, correct3, "
        " duration4, puzzle4, elapsed4, answer4, correct4, "
        " duration5, puzzle5, elapsed5, answer5, correct5, "
        " duration6, puzzle6, elapsed6, answer6, correct6, "
        " duration7, puzzle7, elapsed7, answer7, correct7, "
        " duration8, puzzle8, elapsed8, answer8, correct8, "
        " duration9, puzzle9, elapsed9, answer9, correct9, "
        " duration10, puzzle10, elapsed10, answer10, correct10, "
        " duration11, puzzle11, elapsed11, answer11, correct11, "
        " duration12, puzzle12, elapsed12, answer12, correct12, "
        " duration13, puzzle13, elapsed13, answer13, correct13, "
        " duration14, puzzle14, elapsed14, answer14, correct14, "
        " duration15, puzzle15, elapsed15, answer15, correct15, "
        " duration16, puzzle16, elapsed16, answer16, correct16, "
        " duration17, puzzle17, elapsed17, answer17, correct17, "
        " duration18, puzzle18, elapsed18, answer18, correct18 "
        " )"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :duration1, :puzzle1, :elapsed1, :answer1, :correct1, "
        " :duration2, :puzzle2, :elapsed2, :answer2, :correct2, "
        " :duration3, :puzzle3, :elapsed3, :answer3, :correct3, "
        " :duration4, :puzzle4, :elapsed4, :answer4, :correct4, "
        " :duration5, :puzzle5, :elapsed5, :answer5, :correct5, "
        " :duration6, :puzzle6, :elapsed6, :answer6, :correct6, "
        " :duration7, :puzzle7, :elapsed7, :answer7, :correct7, "
        " :duration8, :puzzle8, :elapsed8, :answer8, :correct8, "
        " :duration9, :puzzle9, :elapsed9, :answer9, :correct9, "
        " :duration10, :puzzle10, :elapsed10, :answer10, :correct10, "
        " :duration11, :puzzle11, :elapsed11, :answer11, :correct11, "
        " :duration12, :puzzle12, :elapsed12, :answer12, :correct12, "
        " :duration13, :puzzle13, :elapsed13, :answer13, :correct13, "
        " :duration14, :puzzle14, :elapsed14, :answer14, :correct14, "
        " :duration15, :puzzle15, :elapsed15, :answer15, :correct15, "
        " :duration16, :puzzle16, :elapsed16, :answer16, :correct16, "
        " :duration17, :puzzle17, :elapsed17, :answer17, :correct17, "
        " :duration18, :puzzle18, :elapsed18, :answer18, :correct18 "
        " )";

    XEXEC xe(db, sql);

    xe.param.setInt("sesh_id",       e->sesh_id);
    xe.param.setInt("ntests",        e->ntests);
    xe.param.setTime("tinstruct",    e->tinstruct);
    xe.param.setTime("tstart",       e->tstart);
    xe.param.setTime("tfinish",      e->tfinish);

    xe.param.setInt("duration1",     e->duration1);
    xe.param.setInt("puzzle1",       e->puzzle1);
    xe.param.setInt("elapsed1",      e->elapsed1);
    xe.param.setInt("answer1",       e->answer1);
    xe.param.setInt("correct1",      e->correct1);

    xe.param.setInt("duration2",     e->duration2);
    xe.param.setInt("puzzle2",       e->puzzle2);
    xe.param.setInt("elapsed2",      e->elapsed2);
    xe.param.setInt("answer2",       e->answer2);
    xe.param.setInt("correct2",      e->correct2);

    xe.param.setInt("duration3",     e->duration3);
    xe.param.setInt("puzzle3",       e->puzzle3);
    xe.param.setInt("elapsed3",      e->elapsed3);
    xe.param.setInt("answer3",       e->answer3);
    xe.param.setInt("correct3",      e->correct3);

    xe.param.setInt("duration4",     e->duration4);
    xe.param.setInt("puzzle4",       e->puzzle4);
    xe.param.setInt("elapsed4",      e->elapsed4);
    xe.param.setInt("answer4",       e->answer4);
    xe.param.setInt("correct4",      e->correct4);

    xe.param.setInt("duration5",     e->duration5);
    xe.param.setInt("puzzle5",       e->puzzle5);
    xe.param.setInt("elapsed5",      e->elapsed5);
    xe.param.setInt("answer5",       e->answer5);
    xe.param.setInt("correct5",      e->correct5);

    xe.param.setInt("duration6",     e->duration6);
    xe.param.setInt("puzzle6",       e->puzzle6);
    xe.param.setInt("elapsed6",      e->elapsed6);
    xe.param.setInt("answer6",       e->answer6);
    xe.param.setInt("correct6",      e->correct6);

    xe.param.setInt("duration7",     e->duration7);
    xe.param.setInt("puzzle7",       e->puzzle7);
    xe.param.setInt("elapsed7",      e->elapsed7);
    xe.param.setInt("answer7",       e->answer7);
    xe.param.setInt("correct7",      e->correct7);

    xe.param.setInt("duration8",     e->duration8);
    xe.param.setInt("puzzle8",       e->puzzle8);
    xe.param.setInt("elapsed8",      e->elapsed8);
    xe.param.setInt("answer8",       e->answer8);
    xe.param.setInt("correct8",      e->correct8);

    xe.param.setInt("duration9",     e->duration9);
    xe.param.setInt("puzzle9",       e->puzzle9);
    xe.param.setInt("elapsed9",      e->elapsed9);
    xe.param.setInt("answer9",       e->answer9);
    xe.param.setInt("correct9",      e->correct9);

    xe.param.setInt("duration10",     e->duration10);
    xe.param.setInt("puzzle10",       e->puzzle10);
    xe.param.setInt("elapsed10",      e->elapsed10);
    xe.param.setInt("answer10",       e->answer10);
    xe.param.setInt("correct10",      e->correct10);

    xe.param.setInt("duration11",     e->duration11);
    xe.param.setInt("puzzle11",       e->puzzle11);
    xe.param.setInt("elapsed11",      e->elapsed11);
    xe.param.setInt("answer11",       e->answer11);
    xe.param.setInt("correct11",      e->correct11);

    xe.param.setInt("duration12",     e->duration12);
    xe.param.setInt("puzzle12",       e->puzzle12);
    xe.param.setInt("elapsed12",      e->elapsed12);
    xe.param.setInt("answer12",       e->answer12);
    xe.param.setInt("correct12",      e->correct12);

    xe.param.setInt("duration13",     e->duration13);
    xe.param.setInt("puzzle13",       e->puzzle13);
    xe.param.setInt("elapsed13",      e->elapsed13);
    xe.param.setInt("answer13",       e->answer13);
    xe.param.setInt("correct13",      e->correct13);

    xe.param.setInt("duration14",     e->duration14);
    xe.param.setInt("puzzle14",       e->puzzle14);
    xe.param.setInt("elapsed14",      e->elapsed14);
    xe.param.setInt("answer14",       e->answer14);
    xe.param.setInt("correct14",      e->correct14);

    xe.param.setInt("duration15",     e->duration15);
    xe.param.setInt("puzzle15",       e->puzzle15);
    xe.param.setInt("elapsed15",      e->elapsed15);
    xe.param.setInt("answer15",       e->answer15);
    xe.param.setInt("correct15",      e->correct15);

    xe.param.setInt("duration16",     e->duration16);
    xe.param.setInt("puzzle16",       e->puzzle16);
    xe.param.setInt("elapsed16",      e->elapsed16);
    xe.param.setInt("answer16",       e->answer16);
    xe.param.setInt("correct16",      e->correct16);

    xe.param.setInt("duration17",     e->duration17);
    xe.param.setInt("puzzle17",       e->puzzle17);
    xe.param.setInt("elapsed17",      e->elapsed17);
    xe.param.setInt("answer17",       e->answer17);
    xe.param.setInt("correct17",      e->correct17);

    xe.param.setInt("duration18",     e->duration18);
    xe.param.setInt("puzzle18",       e->puzzle18);
    xe.param.setInt("elapsed18",      e->elapsed18);
    xe.param.setInt("answer18",       e->answer18);
    xe.param.setInt("correct18",      e->correct18);

    printf("<p>sql:</p><pre>%s</pre> ", sql.c_str());

    return (xe.exec());
}

void getHoopsRecords() {
    vecHoopsRecord records;
    HoopsRecord rec;
    std::string sql = "SELECT * FROM hoops";
    XQUERY q(db, sql);
    printf("this is %s\n", __FILE__);
    if (!q.open()) {
        printf("Database error");
        throw "Database error";
    }
    printf("<p>q.fetch():</p>");
    while (q.fetch()) {
        rec.sesh_id   = q.result.getInt("sesh_id");
        rec.ntests    = q.result.getInt("ntests");
        rec.tinstruct = q.result.getTime("tinstruct"); // getDate?
        rec.tstart    = q.result.getTime("tstart");
        rec.tfinish   = q.result.getTime("tstart");
        records.push_back(rec);
    }
    q.close();

    printf("<h3>Results:</h3>\n");
    printf("<table>\n");
    //vecHoopsRecord::const_iterator it;
    for (vecHoopsRecord::const_iterator it = records.begin(); it != records.end(); it++) {
        printf("<tr><td>%d</td><td>%d</td><td>%s</td><td>%s</td><td>%s</td>");
        printf("</tr>\n");
    }
    printf("</table>\n");
}

/*
    int total_count = 0;
    std::string tab, chk, ack;
    DATABASE_ENTRY  e;
    std::vector<DATABASE_ENTRY> cent;
    const   std::vector<DATABASE_ENTRY> *acks_todo = NULL;
    if ( use_cache )
        {refreshCache();
        acks_todo = getAcks();
        }
    else                // LOAD FROM CENTRAL ACKS_TODO TABLE
        {std::string    sql = "SELECT DISTINCT trid,cid,tabl"
            " FROM ack_todo WHERE ";
        XQUERY  q( db, sql );
        if ( target_comp )      // TARGET IS A COMPUTER
            {q.extendSQL( "xu_hid= :h" );
            q.param.setInt( "h", target_id );
            }
        else                // TARGET IS A WHOLE CENTRE
            {q.extendSQL( "aid= :a" );
            q.param.setInt( "a", target_id );
            }
        if ( ! q.open() )
            {return( -1 );
            }
        while ( q.fetch() )
            {
            e.trid = q.result.getInt(0);
            e.cid  = q.result.getInt(1);
            tab    = q.result.getString(2);
            strncpy( e.tabl, tab.c_str(), 12 );
            cent.push_back( e );
            }
        q.close();
        acks_todo = &cent;
        }
    std::vector<DATABASE_ENTRY>::const_iterator ai = acks_todo->begin();    int total_count = 0;
    std::string tab, chk, ack;
    DATABASE_ENTRY  e;
    std::vector<DATABASE_ENTRY> cent;
    const   std::vector<DATABASE_ENTRY> *acks_todo = NULL;
    if ( use_cache )
        {refreshCache();
        acks_todo = getAcks();
        }
    else                // LOAD FROM CENTRAL ACKS_TODO TABLE
        {std::string    sql = "SELECT DISTINCT trid,cid,tabl"
            " FROM ack_todo WHERE ";
        XQUERY  q( db, sql );
        if ( target_comp )      // TARGET IS A COMPUTER
            {q.extendSQL( "xu_hid= :h" );
            q.param.setInt( "h", target_id );
            }
        else                // TARGET IS A WHOLE CENTRE
            {q.extendSQL( "aid= :a" );
            q.param.setInt( "a", target_id );
            }
        if ( ! q.open() )
            {return( -1 );
            }
        while ( q.fetch() )
            {
            e.trid = q.result.getInt(0);
            e.cid  = q.result.getInt(1);
            tab    = q.result.getString(2);
            strncpy( e.tabl, tab.c_str(), 12 );
            cent.push_back( e );
            }
        q.close();
        acks_todo = &cent;
        }
    std::vector<DATABASE_ENTRY>::const_iterator ai = acks_todo->begin();
*/

