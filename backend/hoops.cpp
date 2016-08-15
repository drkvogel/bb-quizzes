#include "xquery.h"
#include "xexec.h"
#include "hoops.h"

bool insertHoopsRecord(const HoopsRecord *e) {
    XEXEC xe(db, "INSERT INTO hoops (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert, "
        " duration1, puzzle1, elapsed1, answer1, correct1, "
        " )"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :duration1, :puzzle1, :elapsed1, :answer1, :correct1, "
        " )");
    xe.param.setInt("sesh_id",      e->sesh_id);
    xe.param.setInt("ntests",       e->ntests);
    xe.param.setInt("tinstruct",    e->tinstruct);
    xe.param.setInt("tstart",       e->tstart);
    xe.param.setInt("tstart",       e->tstart);
    xe.param.setString( "tb", tab );
    return( xe.exec() );
}

