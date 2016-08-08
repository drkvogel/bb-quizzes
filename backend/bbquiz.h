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

// extern XDB *db;
// extern std::string timebuf;
// extern XTIME logtime;
// extern FILE * logfile;

XDB *db;
std::string timebuf;
XTIME logtime;
FILE * logfile;

using std::string;

typedef struct {
    int msgid;
    // char src_app[SMSQ_LEN_SRCAPP+1];
    // char origin [SMSQ_LEN_ORIGIN+1];
    XTIME added;
    XTIME depart;
    int status;
    int retries;
    XTIME updatetime;
} SMSQ_USER_MESSAGES_RECORD;

// enum smsq_status {
//     SMSQ_MSG_ADDED,
//     SMSQ_MSG_CLEARED_SEND,
//     SMSQ_MSG_SENT_TO_PROVIDER,
//     SMSQ_MSG_DELIVERED_OK,
//     SMSQ_MSG_RECEIVED_OK,
//     SMSQ_MSG_SEND_FAILED,
//     SMSQ_MSG_CANCELLED,
//     SMSQ_MSG_STATUS_UNKNOWN,
//     SMSQ_MSG_ABOUT_TO_SEND
// };

class Utilities {
public:
    bool alphanumeric(string);
    bool numeric(string);
    string escapequotes(string);
    string create_sql_add_msg(string, string, string, string, string, string, string, string, int, int);
};

#endif

// #define SMSQ_ADDMSG_BAD_PASSWORD    -1
// #define SMSQ_ADDMSG_NO_QUOTA        -2
// #define SMSQ_ADDMSG_INSERT_FAILED   -3
// #define SMSQ_LEN_PROP_PARAM 20
// #define SMSQ_LEN_PROP_SVAL  20
// #define SMSQ_LEN_USERNAME   10
// #define SMSQ_LEN_PASSWORD   10
// #define SMSQ_LEN_DESCRIPT   25
// #define SMSQ_LEN_SRCAPP     25
// #define SMSQ_LEN_ORIGIN     25
// #define SMSQ_LEN_DESTNO     16
// #define SMSQ_LEN_SENDER     16
// #define SMSQ_LEN_TEXT      160
