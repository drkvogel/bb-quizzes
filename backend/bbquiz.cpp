#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <malloc.h>
#ifndef __WIN32__
#include <sys/resource.h>
#endif
#include "xdb.h"
#include "xquery.h"
#include "xexec.h"
#include "xhttp.h"
#include "xcgi.h"
#include "bbquiz.h"

// 0: off; 1: on
#define DEBUG 0
#define OFFLINE 0

// bbquiz.cpp
// c.bird 2016-08-08

// Biobank Cognitive Quizzes backend

XDB *db;

BBQuizRecord rec;
tdvecBBQuizRecord results;


bool dbErrorCallback
(const std::string object, const int instance, const int ecount, const int ecode, const std::string error_txt)
{
    std::stringstream sstr;
    sstr << "Database error:\n  object: " << object << "\n  instance: " << instance << "\n  ecount: " << ecount
        << "\n  ecode: " << ecode << "\n  error_txt: " << error_txt;
    LOG_PRINT(sstr.str().c_str());
    return true; //XXX
}

// int initDB() {
//     LOG_TIME fprintf(logfile, "initDB: '%s'\n", BBQUIZ_DBNAME); LOG_DOT
//     db = new XDB(BBQUIZ_DBNAME); LOG_DOT
//     if (!db->open()) {  throw "Failed to open database"; }
//     db->setErrorCallBack(dbErrorCallback);
//     fprintf(logfile, "done"); LOG_NL
//     return 0;
// }

void showParams(XCGI * x) {
    printf("Method: %s", x->getMethodName().c_str());
    printf("<h3>%d parameters</h3>\n<table border cellspacing=\"0\">", x->param.count());
    int np = x->param.count();
    printf("\n\n<!-- XCGI found %d parameters -->\n", np);
    for (int i = 0; i < np; i++) {
        printf( "<tr><td>%d</td><td>%s</td><td>%s</td></tr>", i, x->param.getName(i).c_str(), x->param.getString(i).c_str());
    }
    printf("</table>END");
#ifdef __LIVE__
    printf("<p>We're live!</p>");
    boilerplate_foot();
    return -1;
#else
    printf("<!-- Not __LIVE__ -->");
#endif
}

int initDB() { // no logging
    db = new XDB(BBQUIZ_DBNAME);
    if (!db->open()) {  throw "Failed to open database"; }
    db->setErrorCallBack(dbErrorCallback);
    return 0;
}

void setUpLogfile() {
    char logfilename[32];
    logtime.setNow();
    sprintf(logfilename, DIR_LOG "bbquiz_%4.4d-%2.2d.log", logtime.asXDATE().getYear(), logtime.asXDATE().getMonth());
    logfile = fopen(logfilename, "a");
    if (NULL == logfile) printf("couldn't open logfile"); //XXX
#ifndef __WIN32__
    struct rlimit coredumplimit;
    // p.s. if setting a specific size, these limits are in bytes,
    // whilst those set by ulimit (in bash) are in 1k blocks
    coredumplimit.rlim_cur = RLIM_INFINITY; //XXX ?
    coredumplimit.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &coredumplimit);
#endif
    //fprintf(stderr, "stderr test"); // a little test
}

void boilerplate_head() {
    printf("<html><head><title></title></head><body>");
}

void boilerplate_foot() {
    printf("</body></html>");
}

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

int main(int argc, char **argv) {
    int exitstatus, i;
    //tdvecHoopsRecord::const_iterator recIt;

    //setUpLogfile();
    // readIniFile();
    // initSessionData();

    XCGI *x = new XCGI(argc, argv);
    x->writeHeader(XCGI::typeHtml);
    boilerplate_head();

    if (DEBUG) showParams(x); // from cgi_test.cpp
    if (OFFLINE) {
        printf("<p>Currently offline</p>");
        boilerplate_foot();
        return -1;
    }

    printf("<h1>bbquiz</h1><p>Hello, World</p>\n");

    try {
        initDB();
        printf("db opened");
    } catch (char const* err) {
        printf("db problem: '%s'; exiting", err);
        boilerplate_foot();
        return -1;
    }

    //x->param.getStringDefault("destno", "");

    db->close(); //LOG_DOT
    boilerplate_foot();
    return(EXIT_SUCCESS);
}
