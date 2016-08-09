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

using std::string;

typedef struct {
    sesh_id
    ntests
    tinstruct
    tstart
    tfinish
    tinsert

    duration1
    puzzle1
    elapsed1
    answer1
    correct1    

    duration2 
    puzzle2   
    elapsed2  
    answer2   
    correct2  
    
    duration3 
    puzzle3   
    elapsed3  
    answer3   
    correct3  
    
    duration4 
    puzzle4   
    elapsed4  
    answer4   
    correct4  
    
    duration5 
    puzzle5   
    elapsed5  
    answer5   
    correct5  
    
    duration6 
    puzzle6   
    elapsed6  
    answer6   
    correct6  
    
    duration7 
    puzzle7   
    elapsed7  
    answer7   
    correct7  
    
    duration8 
    puzzle8   
    elapsed8  
    answer8   
    correct8  
    
    duration9 
    puzzle9   
    elapsed9  
    answer9   
    correct9  
    
    duration10
    puzzle10  
    elapsed10 
    answer10  
    correct10 
    
    duration11
    puzzle11  
    elapsed11 
    answer11  
    correct11 
    
    duration12
    puzzle12  
    elapsed12 
    answer12  
    correct12 
    
    duration13
    puzzle13  
    elapsed13 
    answer13  
    correct13 
    
    duration14
    puzzle14  
    elapsed14 
    answer14  
    correct14 
    
    duration15
    puzzle15  
    elapsed15 
    answer15  
    correct15 
    
    duration16
    puzzle16  
    elapsed16 
    answer16  
    correct16 
    
    duration17
    puzzle17  
    elapsed17 
    answer17  
    correct17 
    
    duration18
    puzzle18  
    elapsed18 
    answer18  
    correct18 
};


typedef struct {
    int msgid;
    // char src_app[SMSQ_LEN_SRCAPP+1];
    // char origin [SMSQ_LEN_ORIGIN+1];
    XTIME added;
    XTIME depart;
    int status;
    int retries;
    XTIME updatetime;
} BBQUIZ_USER_MESSAGES_RECORD;

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
