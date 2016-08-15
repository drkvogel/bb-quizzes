#ifndef _BBQUIZ_
#define _BBQUIZ_
#include "xtime.h"
#include "xdb.h"
#include "live_or_test.h"

#ifdef __LIVE__
#define BBQUIZ_DBNAME "cp_web_live"
#else
#define BBQUIZ_DBNAME "cp_web_test"
#endif
#define XHTTP_HOST_NAME "red.ctsu.ox.ac.uk/~cp/cjb/matrix"
#define XHTTP_HOST_PORT 80
#define DBG_SET(x) session_data.debugflags & x
#define LOG_TIME logtime.setNow();                          \
                 timebuf = logtime.iso();                   \
                 fprintf(logfile, "%s ", timebuf.c_str()); fflush(logfile);
#define LOG_DOT fprintf(logfile, "."); fflush(logfile);
#define LOG_NL fprintf(logfile, "\n"); fflush(logfile);
#define LOG_NUM(X) fprintf(logfile, "%d: ", X); fflush(logfile);
#define LOG_PRINT(x) fprintf(logfile, "%s", x); fflush(logfile);
#define LOG_PRINT2(x,y) fprintf(logfile, x, y); fflush(logfile);
#define DIR_LOG "./log/"

std::string timebuf;
XTIME logtime;
FILE * logfile;
//using std::string;

typedef struct {
    int sesh_id;
    int ntests;
    XTIME tinstruct;
    XTIME tstart;
    XTIME tfinish;
    XTIME tinsert;
} BBQuizRecord;
typedef std::vector< BBQuizRecord > tdvecBBQuizRecord;


class Utilities {
public:
    bool alphanumeric(string);
    bool numeric(string);
    string escapequotes(string);
    string create_sql_add_msg(string, string, string, string, string, string, string, string, int, int);
};

#endif
