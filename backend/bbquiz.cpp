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
#include "hoops.h"
#include "matrix.h"
#include "bbquiz.h"

// 0: off; 1: on
#define DEBUG 1
#define OFFLINE 0

// bbquiz.cpp
// c.bird 2016-08-08
// Biobank Cognitive Quizzes backend

XDB *db;
// BBQuizRecord rec;
// tdvecBBQuizRecord results;

bool dbErrorCallback (const std::string object, const int instance, const int ecount, const int ecode, const std::string error_txt) {
    std::stringstream sstr;
    sstr << "Database error:\n  object: " << object << "\n  instance: " << instance << "\n  ecount: " << ecount
        << "\n  ecode: " << ecode << "\n  error_txt: " << error_txt;
    //LOG_PRINT(sstr.str().c_str()); // crashes if logfile not set up
    printf("error: '%s'\n", sstr.str().c_str());
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
    //printf("<h2>Parameters</h2>");
    printf("<code>Method: %s; %d parameters", x->getMethodName().c_str(), x->param.count());
    printf("<table border cellspacing=\"0\">");
    int np = x->param.count();
    printf("\n\n<!-- XCGI found %d parameters -->\n", np);
    for (int i = 0; i < np; i++) {
        printf( "<tr><td>%d</td><td>%s</td><td>%s</td></tr>", i, x->param.getName(i).c_str(), x->param.getString(i).c_str());
    }
    printf("</table></code>");
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
    printf("<h1>BB Quizzes Backend</h1>");
    printf("<form action=\"#\">\n"
        "<button type=\"submit\" name=\"action\" value=\"insert\" />Insert</button>\n"
        "<button type=\"submit\" name=\"action\" value=\"view\" />View</button>\n"
        "</form>");
}

void boilerplate_foot() {
    printf("</body></html>");
}

    //setUpLogfile();
    // readIniFile();
    // initSessionData();

int main(int argc, char **argv) {
    XCGI *x = new XCGI(argc, argv);
    x->writeHeader(XCGI::typeHtml);
    boilerplate_head();

    //if (DEBUG)
    showParams(x); // from cgi_test.cpp
    if (OFFLINE) {
        printf("<p>Currently offline</p>");
        boilerplate_foot();
        return -1;
    }

    //printf("<h1>bbquiz</h1><p>Hello, World</p>\n");
    try {
        initDB();
        printf("<p><code>db opened. built: %s %s. action: '%s'</code></p>", __DATE__, __TIME__, x->param.getStringDefault("action", "").c_str());
        if (0 == strcmp("insert", x->param.getStringDefault("action", "").c_str())) {
            HoopsRecord rec;
            rec.sesh_id = x->param.getIntDefault("sesh_id", -1);
            rec.ntests = x->param.getIntDefault("ntests", -1);
            rec.tinstruct = "2016-08-15 16:30"; //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
            rec.tstart = "";
            rec.tfinish = "";
            rec.tinsert = "";

            rec.duration1 = -1;
            rec.puzzle1 = -1;
            rec.elapsed1 = -1;
            rec.answer1 = -1;
            rec.correct1 = -1;

            rec.duration2 = -1;
            rec.puzzle1 = -1;
            rec.elapsed1 = -1;
            rec.answer1 = -1;
            rec.correct1 = -1;

            if (insertHoopsRecord(&rec)) {
                printf("<p>Data inserted.</p>");
            } else {
                printf("<p>Not inserted!</p>");
            }
        } else if (0 == strcmp("view", x->param.getStringDefault("action", "").c_str())) {
            getHoopsRecords();
            getMatrixRecords();
        } else {
            printf("<p>No action selected.</p>");
        }
    } catch (char const* err) {
        printf("error: '%s'; exiting", err);
        boilerplate_foot();
        return -1;
    }

    db->close(); //LOG_DOT
    boilerplate_foot();
    return(EXIT_SUCCESS);
}
