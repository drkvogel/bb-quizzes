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

/*
typedef struct {
    int sesh_id;
    int ntests;
    XTIME tinstruct;
    XTIME tstart;
    XTIME tfinish;
    XTIME tinsert;

    int duration1;
    int puzzle1;
    int elapsed1;
    int answer1;
    int correct1;

    int duration2;
    int puzzle2;
    int elapsed2;
    int answer2;
    int correct2;

    int duration3;
    int puzzle3;
    int elapsed3;
    int answer3;
    int correct3;

    int duration4;
    int puzzle4;
    int elapsed4;
    int answer4;
    int correct4;

    int duration5;
    int puzzle5;
    int elapsed5;
    int answer5;
    int correct5;

    int duration6;
    int puzzle6;
    int elapsed6;
    int answer6;
    int correct6;

    int duration7;
    int puzzle7;
    int elapsed7;
    int answer7;
    int correct7;

    int duration8;
    int puzzle8;
    int elapsed8;
    int answer8;
    int correct8;

    int duration9;
    int puzzle9;
    int elapsed9;
    int answer9;
    int correct9;

    int duration10;
    int puzzle10;
    int elapsed10;
    int answer10;
    int correct10;

    int duration11;
    int puzzle11;
    int elapsed11;
    int answer11;
    int correct11;

    int duration12;
    int puzzle12;
    int elapsed12;
    int answer12;
    int correct12;

    int duration13;
    int puzzle13;
    int elapsed13;
    int answer13;
    int correct13;

    int duration14;
    int puzzle14;
    int elapsed14;
    int answer14;
    int correct14;

    int duration15;
    int puzzle15;
    int elapsed15;
    int answer15;
    int correct15;

    int duration16;
    int puzzle16;
    int elapsed16;
    int answer16;
    int correct16;

    int duration17;
    int puzzle17;
    int elapsed17;
    int answer17;
    int correct17;

    int duration18;
    int puzzle18;
    int elapsed18;
    int answer18;
    int correct18;
} BBQuizRecord;
*/

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
