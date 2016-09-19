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

// idserve.cpp
// idserve.cgi
// get next id, put in file for front end to get

// db stuff

FILE * logfile;

bool dbErrorCallback (const std::string object, const int instance, const int ecount, const int ecode, const std::string error_txt) {
    std::stringstream sstr;
    sstr <<"Database error:\n object: "<<object<<"\n instance: "<<instance<<"\n ecount: "<<ecount<<"\n ecode: "<<ecode<<"\n error_txt: "<<error_txt;
    printf("<p>Error:</p>\n<pre>%s</pre>\n", sstr.str().c_str()); //LOG_PRINT(sstr.str().c_str()); // crashes if logfile not set up
    return true; //XXX
}

// int initDB() { // no logging
//     db = new XDB(BBQUIZ_DBNAME);
//     db->setErrorCallBack(dbErrorCallback);
//     if (!db->open()) {  throw "Failed to open database"; }
//     return 0;
// }

XCGI * x;

int main(int argc, char **argv) {
    x = new XCGI(argc, argv); // global! naughty!
    x->writeHeader(XCGI::typeJSON);
    try {
        //initDB();
        time_t  tnow;
        time(&tnow); // ctime(&tnow)
        char timestring[32];
        strcpy(timestring, ctime(&tnow));
        timestring[24] = '\0'; // remove annoying non-configurable newline added by ctime
        //printf("{\n  \"session\": {\n    \"comment\" : \"some JSON\",\n    \"seshID\": \"%s\"\n  }\n}", timestring);
        printf("{\n  \"session\": {\n    \"comment\" : \"some JSON\",\n    \"seshID\": \"%d\"\n  }\n}", (int)tnow);
        printf("\n"); // always end with newline
    } catch (char * err) {
        printf("error: '%s'; exiting", err);
        //boilerplate_foot();
        return -1;
    }

/*    db->close();
    delete db;*/
    return(EXIT_SUCCESS);
}

//boilerplate_head();
//boilerplate_foot();
