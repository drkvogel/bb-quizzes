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

typedef std::vector< BBQuizRecord > tdvecBBQuizRecord;

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

// typedef struct {
//     int msgid;
//     // char src_app[SMSQ_LEN_SRCAPP+1];
//     // char origin [SMSQ_LEN_ORIGIN+1];
//     XTIME added;
//     XTIME depart;
//     int status;
//     int retries;
//     XTIME updatetime;
// } BBQUIZ_USER_MESSAGES_RECORD;
