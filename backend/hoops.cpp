#include "xquery.h"
#include "xexec.h"
#include "hoops.h"

bool insertHoopsRecord(const HoopsRecord *e) {
    XEXEC xe(db, "INSERT INTO hoops (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert,"
        " duration1, puzzle1, elapsed1, answer1, correct1,"
        " duration18, puzzle18, elapsed18, answer18, correct18"
        " )"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :duration1, :puzzle1, :elapsed1, :answer1, :correct1, "
        " :duration18, :puzzle18, :elapsed18, :answer18, :correct18"
        " )");
    xe.param.setInt("sesh_id",       e->sesh_id);
    xe.param.setInt("ntests",        e->ntests);
    xe.param.setTime("tinstruct",    e->tinstruct);
    xe.param.setTime("tstart",       e->tstart);
    xe.param.setTime("tfinish",      e->tfinish);
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

