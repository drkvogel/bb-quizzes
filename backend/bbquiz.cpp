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
#include "xcgi.h"
#include "matrix.h"
#include "hoops.h"
#include "trails.h"
#include "bbquiz.h"

// 0: off; 1: on
#define DEBUG 1
#define OFFLINE 0

// bbquiz.cpp
// Biobank Cognitive Quizzes backend
// c.bird 2016-08-08

std::string timebuf;
XTIME logtime;
FILE * logfile;
XCGI * x;
XDB *db;

bool dbErrorCallback (const std::string object, const int instance, const int ecount, const int ecode, const std::string error_txt) {
    std::stringstream sstr;
    sstr <<"Database error:\n object: "<<object<<"\n instance: "<<instance<<"\n ecount: "<<ecount<<"\n ecode: "<<ecode<<"\n error_txt: "<<error_txt;
    printf("<p>Error:</p>\n<pre>%s</pre>\n", sstr.str().c_str()); //LOG_PRINT(sstr.str().c_str()); // crashes if logfile not set up
    return true; //XXX
}

void showParams(XCGI * x) {
    int np = x->param.count();
    printf("<code><table border cellspacing=\"0\">\n");
    printf("<thead><th colspan=\"3\">XCGI method %s found %d parameters</td>\n", x->getMethodName().c_str(), np);
    if (np > 0) {
        for (int i = 0; i < np; i++) {
            printf( "<tr><td>%d</td><td>%s</td><td>%s</td></tr>\n", i, x->param.getName(i).c_str(), x->param.getString(i).c_str());
        }
    }
    printf("</table></code>\n");
#ifdef __LIVE__
    printf("<p>We're live!</p>\n");
    boilerplate_foot();
    return -1;
#else
    printf("Not __LIVE__\n");
#endif
}

int initDB() { // no logging
    db = new XDB(BBQUIZ_DBNAME);
    db->setErrorCallBack(dbErrorCallback);
    if (!db->open()) {  throw "Failed to open database"; }
    return 0;
}

void boilerplate_head() {
    printf("<html>\n<head>\n");
    printf("<title>BB Quizzes Backend</title>\n");
    printf("<meta charset=\"utf-8\">\n<meta name=\"description\" content="">\n<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n");
    printf("<link rel=\"stylesheet\" href=\"http://yui.yahooapis.com/pure/0.6.0/pure-min.css\">\n");
    printf("<link rel=\"stylesheet\" href=\"./main.css\">\n");
    printf("</head>\n<body>\n");
    printf("<h2><a href=\".\">BB Quizzes Backend</a></h2>\n");
}

void boilerplate_foot() {
    printf("</body>\n</html>\n");
}

bool paramIs(const char * param, const char * value) {
    bool result = (0 == strcmp(value, x->param.getStringDefault(param, "").c_str()));
    //printf("<p><code>paramIs(): param: '%s', value: '%s'; result: %s</code></p>", param, value, result ? "yes":"no");
    return result;
}

int nowUNIX() { // UNIX time in seconds
    time_t  tnow;
    time(&tnow); // ctime(&tnow)
    return (int)tnow;
}

void showOptions() {
    printf("<table border=1 cellspacing=0><thead><tr><th>Quiz</th><th colspan=2>Actions</th></tr></thead>\n");
    printf("<tr><td>Matrix</td>");
    printf("<td><a href=\"matrix/?sesh_id=%d\">Start</a></td>", nowUNIX());
    printf("<td><a href=\"?quiz=matrix&action=view\">View responses</a></td>");
    printf("</tr>\n");
    printf("<tr><td>Hoops</td>");
    printf("<td><a href=\"hoops/?sesh_id=%d\">Start</a></td>", nowUNIX());
    printf("<td><a href=\"?quiz=hoops&action=view\">View responses</a></td>");
    printf("</tr>\n");
    printf("<tr><td>Trails</td>");
    printf("<td><a href=\"trails/?sesh_id=%d\">Start</a></td>", nowUNIX());
    printf("<td><a href=\"?quiz=trails&action=view\">View responses</a></td>");
    printf("</tr>\n");
    printf("</table>\n");
    printf("<hr>\n");
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
        printf("<p><code>db opened. built: %s %s. %d params.</code></p>\n", __DATE__, __TIME__, x->param.count());
        printf("\n\n<!-- "); showParams(x); printf("-->\n\n"); // always show params in comments
        showOptions();
        if (x->param.isEmpty()) {
            printf("<p>No action selected.</p>\n");
        } else if (paramIs("action", "insert") && paramIs("quiz_id", "2222")) { // real insert by frontend
            try {
                Hoops::HoopsRecord rec = Hoops::getPayload(x);
                Hoops::insertRecord(&rec);
                printf("<p>insert succeeded</p>\n");
            } catch (...) {
                printf("<p>insert did not succeed...</p>\n");
            }
        } else if (paramIs("action", "insert") && paramIs("quiz_id", "1111")) {
            try {
                Matrix::MatrixRecord rec = Matrix::getPayload(x);
                Matrix::insertRecord(&rec);
                printf("<p>insert succeeded</p>\n");
            } catch (...) {
                printf("<p>insert did not succeed...</p>\n");
            }
        } else if (paramIs("action", "insert") && paramIs("quiz_id", "3333")) {
            try {
                Trails::TrailsRecord rec = Trails::getPayload(x);
                Trails::insertRecord(&rec);
                printf("<p>insert succeeded</p>\n");
            } catch (...) {
                printf("<p>insert did not succeed...</p>\n");
            }
        } else if (paramIs("action", "insertDummy") && paramIs("quiz", "hoops")) {
            printf("<p>Not implemented</p>\n");
        } else if (paramIs("action", "insertDummy") && paramIs("quiz", "matrix")) {
            printf("<p>Not implemented</p>\n");
        } else if (paramIs("action", "insertDummy") && paramIs("quiz", "trails")) {
            printf("<p>Not implemented</p>\n");
        } else if (paramIs("action", "view") && paramIs("quiz", "hoops")) {
            Hoops::getRecords();
            Hoops::printRecords();
        } else if (paramIs("action", "view") && paramIs("quiz", "matrix")) {
            Matrix::getRecords();
            Matrix::printRecords();
        } else if (paramIs("action", "view") && paramIs("quiz", "trails")) {
            Trails::getRecords();
            Trails::printRecords();
        } else {
            printf("<p>Parameters not understood.</p>");
            showParams(x); // from cgi_test.cpp //if (DEBUG)
            //throw "abort";
        }
    } catch (char * err) {
        printf("error: '%s'; exiting", err);
        boilerplate_foot();
        return -1;
    }

    db->close();
    delete db;
    boilerplate_foot();
    return(EXIT_SUCCESS);
}

