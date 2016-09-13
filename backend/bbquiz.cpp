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
    sstr <<"Database error:\n object: "<<object<<"\n instance: "<<instance<<"\n ecount: "<<ecount<<"\n ecode: "<<ecode<<"\n error_txt: "<<error_txt;
    printf("error: '%s'\n", sstr.str().c_str()); //LOG_PRINT(sstr.str().c_str()); // crashes if logfile not set up
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
    printf("<code>"); //<p; %d parameters</p>\n", x->getMethodName().c_str(), x->param.count());
    int np = x->param.count();
    printf("<table border cellspacing=\"0\">\n");
    printf("<thead><th colspan=\"3\">XCGI method %s found %d parameters</td>\n", x->getMethodName().c_str(), np);
    if (np > 0) {
        for (int i = 0; i < np; i++) {
            printf( "<tr><td>%d</td><td>%s</td><td>%s</td></tr>\n", i, x->param.getName(i).c_str(), x->param.getString(i).c_str());
        }
    }
    printf("</table>\n");
    printf("</code>\n");
#ifdef __LIVE__
    printf("<p>We're live!</p>\n");
    boilerplate_foot();
    return -1;
#else
    printf("<!-- Not __LIVE__ -->\n");
#endif
}

int initDB() { // no logging
    db = new XDB(BBQUIZ_DBNAME);
    db->setErrorCallBack(dbErrorCallback);
    if (!db->open()) {  throw "Failed to open database"; }
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
    printf("<html><head><title>BB Quizzes Backend</title></head>\n<body>\n");
    printf("<h1><a href=\".\">BB Quizzes Backend</a></h1>\n");
/*    printf("<form action=\"#\">\n"
        "<table border=1 cellspacing=0>\n"
        "<tr><td>\n"
        "<input type=\"radio\" name=\"quiz\" value=\"hoops\" checked>Hoops</input>"
        "<input type=\"radio\" name=\"quiz\" value=\"matrix\">Matrix</input>"
        "</td></tr>\n"
        "<tr><td>\n"
        "<button type=\"submit\" name=\"action\" value=\"view\" />View</button>\n"
        "<button type=\"submit\" name=\"action\" value=\"insert\" />Insert</button>\n"
        "</tr></td>\n"
        "</table>\n"
        "</form>\n");*/
}

void boilerplate_foot() {
    printf("</body>\n</html>\n");
}

bool paramIs(const char * param, const char * value) {
    bool result = (0 == strcmp(value, x->param.getStringDefault(param, "").c_str()));
    //printf("<p><code>paramIs(): param: '%s', value: '%s'; result: %s</code></p>", param, value, result ? "yes":"no");
    return result;
}


void showOptions() {
    //printf("<h3>Options</h3>\n<ul>\n");
/*    printf("<li><a href=\"?quiz=matrix&action=start\">Start Matrix Quiz</a></li>\n");
    printf("<li><a href=\"?quiz=hoops&action=start\">Start Hoops Quiz</a></li>\n");*/
    printf("<table border=1 cellspacing=0><thead><tr><th>Quiz</th><th colspan=3>Actions</th></tr></thead>\n");
    printf("<tr><td>Matrix</td>");
    printf("<td><a href=\"?quiz=matrix&action=start\">Start</a></td>");
    printf("<td><a href=\"?quiz=matrix&action=view\">View responses</a></td>");
    printf("<td><a href=\"?quiz=matrix&action=insertDummy\">Insert dummy data</a></td>");
    printf("</tr>\n");
    printf("<tr><td>Hoops</td>");
    printf("<td><a href=\"?quiz=hoops&action=start\">Start</a></td>");
    printf("<td><a href=\"?quiz=hoops&action=view\">View responses</a></td>");
    printf("<td><a href=\"?quiz=hoops&action=insertDummy\">Insert dummy data</a></td>");
    printf("</tr>\n");
    printf("</table>\n");
}

void startMatrix() {
    printf("startMatrix()");
}

void startHoops() {
    printf("startHoops()");
}

int main(int argc, char **argv) {
    x = new XCGI(argc, argv); // global! naughty!
    x->writeHeader(XCGI::typeHtml);
    boilerplate_head();

    if (OFFLINE) {
        printf("<p>Currently offline</p>");
        boilerplate_foot();
        return -1;
    }

    try {
        initDB();
        printf("<p><code>db opened. built: %s %s.</code></p>\n", __DATE__, __TIME__);
        showOptions();
        if (x->param.isEmpty()) {
            printf("<p>No action selected.</p>\n");
        } else if (paramIs("action", "insert") && paramIs("quiz", "hoops")) { // real insert by frontend
            Hoops::insert();
        } else if (paramIs("action", "insert") && paramIs("quiz", "matrix")) {
            Matrix::insert();
        } else if (paramIs("action", "insertDummy") && paramIs("quiz", "hoops")) {
            Hoops::testInsert();
        } else if (paramIs("action", "insertDummy") && paramIs("quiz", "matrix")) {
            Matrix::testInsert();
        } else if (paramIs("action", "view") && paramIs("quiz", "hoops")) {
            Hoops::getRecords();
        } else if (paramIs("action", "view") && paramIs("quiz", "matrix")) {
            Matrix::getRecords();
        } else if (paramIs("action", "start") && paramIs("quiz", "matrix")) {
            startMatrix();
        } else if (paramIs("action", "start") && paramIs("quiz", "hoops")) {
            startHoops();
        } else {
            printf("<p>Parameters not understood.</p>");
            showParams(x); // from cgi_test.cpp //if (DEBUG)
            throw "abort";
        }
    } catch (char * err) {
        printf("error: '%s'; exiting", err);
        boilerplate_foot();
        return -1;
    }

    db->close(); //LOG_DOT
    delete db;
    boilerplate_foot();
    return(EXIT_SUCCESS);
}

    //setUpLogfile();
    // readIniFile();
    // initSessionData();
        //printf("<p><code>action: '%s'</code></p>\n", x->param.getStringDefault("action", "").c_str());
        //printf("<p><code>quiz: '%s'</code></p>\n", x->param.getStringDefault("quiz", "").c_str());
