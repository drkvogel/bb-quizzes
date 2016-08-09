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

#include "bbquiz.h"

#include "xdb.h"
#include "xquery.h"
#include "xexec.h"
#include "xhttp.h"
#include "xcgi.h"

// #include "clickatell.h"
// #include "smsq_exproc.h"
// #include "smsq_api.h"

// bbquiz.cpp
// c.bird 2016-08-08

// Biobank Cognitive Quizzes backend

// extern char smscstatus_descript[][50];
// extern char smsqstatus_descript[][30];
// extern session_data_st session_data;

/*XDB *db;
std::string timebuf;
XTIME logtime;
FILE * logfile; */

//tdvecSmsqRecord smsq_results;

// not presently used - runs as cron job instead
/*void daemonize(void) {

    int i, fd;
    pid_t pid;
    struct rlimit rlm;

    pid = fork();

    if (pid == -1) { // what happened there?
        exit(-1);
    }

    if (pid != 0) {  // my work here is done
        exit(0);
    }

    // create new session and process group
    if (setsid() == -1)
        exit(-1);

    // get max no of file descriptors
    if (getrlimit(RLIMIT_NOFILE, &rlm) < 0)
        exit(-1);

    // close all fd
//    for (i=0; i<rlm.rlim_max; i++)
//        close(i);

    errno = 0;

    // clear permissions
    umask(0);

    // chdir to root
    if (chdir("/") < 0)
        exit(-1);
}
*/

// void update_message_status(int msgid, int smsqstatus, int smscstatus, int errorcode) {
//     LOG_TIME fprintf(logfile, "update_message_status: msgid:%d, smsqstatus:%d [%s], smscstatus:%d [%s], errorcode:%d",
//                      msgid,
//                      smsqstatus, smsqstatus >= 0 ? smsqstatus_descript[smsqstatus] : "unchanged",
//                      smscstatus, smscstatus >= 0 ? smscstatus_descript[smscstatus] : "unchanged",
//                      errorcode); fflush(logfile);
//     try {
//         exproc_update_msg_status(msgid, smsqstatus, smscstatus, errorcode);
//     } catch (char * message) {
//         LOG_TIME
//         fprintf(logfile, "EXCEPTION: %s", message);
//     }
//     LOG_DOT
//     LOG_NL
// }

// void increment_message_retries(SmsqRecord msg) {
//     try {
//         if (msg.retries < session_data.retrylimit) {
//             LOG_TIME; fprintf(logfile, "increment retries for msgid: %d, retries so far: %d",
//                                         msg.msgid, msg.retries);
//             exproc_increment_retries(msg.msgid); LOG_DOT LOG_NL
//         } else {
//             LOG_TIME; fprintf(logfile, "retry limit reached for msgid: %d, retries: %d\n",
//                                         msg.msgid, msg.retries); LOG_NL
//             session_data.smsqstatus = SMSQ_MSG_CANCELLED;
//             update_message_status(msg.msgid, session_data.smsqstatus, session_data.smscstatus, -1);
//         }
//     } catch (char * message) {
//         LOG_TIME
//         fprintf(logfile, "EXCEPTION: %s", message);
//     }
// }

// void check_due(SmsqRecord msg) {
//     XTIME currentTime;
//     currentTime.setNow();
//     if (currentTime > msg.depart)
//         update_message_status(msg.msgid, SMSQ_MSG_CLEARED_SEND, -1, -1);
// }

////int get_messages (int status) {
    // int msgnum = 0;
    // smsq_results.clear();

    // // ignore messages more than SMSQ_DAYS_IGNORE days old
    // char query[256];
    // sprintf(query, "SELECT * FROM smsq WHERE smsqstatus = :ss AND depart > date('now') - date('%d days') ORDER BY destno, depart ASC", SMSQ_DAYS_IGNORE);
    // XQUERY q( db, query );
    // q.param.setInt( "ss", status );

    // if (!q.open()) { throw "Query open failed in get_messages()"; }

    // while (q.fetch()) {
    //     SmsqRecord smsq_record;
    //     smsq_record.msgnum      = ++msgnum;
    //     smsq_record.username    = q.result.getString( 0 );
    //     smsq_record.msgid       = q.result.getInt( 1 );
    //     smsq_record.src_app     = q.result.getString( 2 );
    //     smsq_record.origin      = q.result.getString( 3 );
    //     smsq_record.added       = q.result.getTime( 4 );
    //     smsq_record.depart      = q.result.getTime( 5 );
    //     smsq_record.destno      = q.result.getString( 6 );
    //     smsq_record.sender      = q.result.getString( 7 );
    //     smsq_record.text        = q.result.getString( 8 );
    //     smsq_record.valperiod   = q.result.getInt( 9 );
    //     smsq_record.priority    = q.result.getInt( 10 );
    //     smsq_record.smsqstatus  = q.result.getInt( 11 );
    //     smsq_record.smscstatus  = q.result.getInt( 12 );
    //     smsq_record.errorcode   = q.result.getInt( 13 );
    //     smsq_record.retries     = q.result.getInt( 14 );
    //     smsq_record.updatetime  = q.result.getTime( 15 );
    //     smsq_results.push_back(smsq_record);

    //     if (smsq_results.size() == 50)
    //         break; // XXX limit number of messages handled in any one sweep
    // }
    // q.close();

    // return smsq_results.size();
//}

// void list_messages(char *caption) {
//     if (0 == smsq_results.size()) return;

//     LOG_TIME fprintf(logfile, "Messages with status %s: %d records:\n", caption, smsq_results.size());
//     fprintf(logfile,
//     "msg id    username   src_app    origin     added             depart            destno       sender text                      val pt qs cs err r res             "
// //   1   1     test       smsq.c     10.1.6.111 09/02/02 12:12:12 09/02/02 12:12:12 447870478173 123456 blah blah blah blah blah  0    0 00 00 000 0 02092002 12:12:12
//           ); LOG_NL

//     tdvecSmsqRecord::const_iterator recIt;
//     for (recIt = smsq_results.begin(); recIt != smsq_results.end(); recIt++) {
//         fprintf(logfile,
// // msg   id    user     src      origin   added    depart   destno   sender   text     val   pt    qs    cs    err   retry resp
//   "%3.3d %5.5d %-10.10s %-10.10s %-10.10s %-17.17s %-17.17s %-12.12s %-6.6s %-25.25s %4.4d %1.1d %2.2d %2.2d %3.3d %1.1d %-17.17s",
//                 (*recIt).msgnum,
//                 (*recIt).msgid,
//                 (*recIt).username.c_str(),
//                 (*recIt).src_app.c_str(),
//                 (*recIt).origin.c_str(),
//                 (*recIt).added.iso().c_str(),
//                 (*recIt).depart.iso().c_str(),
//                 (*recIt).destno.c_str(),
//                 (*recIt).sender.c_str(),
//                 (*recIt).text.c_str(),
//                 (*recIt).valperiod,
//                 (*recIt).priority,
//                 (*recIt).smsqstatus,
//                 (*recIt).smscstatus,
//                 (*recIt).errorcode,
//                 (*recIt).retries,
//                 (*recIt).updatetime.iso().c_str()); LOG_NL
//     }
// }

// int send_message(SmsqRecord msg) {
//     int exitstatus;
//     update_message_status(msg.msgid, SMSQ_MSG_ABOUT_TO_SEND, -1, -1);
//     exitstatus = clickatell_send_single_message( msg.msgid,
//                                                  msg.sender,
//                                                  msg.text,
//                                                  msg.destno,
//                                                  0,                             // valperiod
//                                                  1                              // deliv_ack 0=off 1=on
//                                                  );
//     if (SMSQ_EXIT_SUCCESS == exitstatus) {
//         LOG_TIME LOG_PRINT2("send_message - message msgid:%d sent OK\n", msg.msgid);
//         update_message_status(msg.msgid, SMSQ_MSG_SENT_TO_PROVIDER, -1, -1);
//     } else if (SMSQ_EXIT_HTTP_ERROR == exitstatus) {
//         LOG_TIME LOG_PRINT2("send_message - HTTP error msgid:%d\n", msg.msgid);
//         update_message_status(msg.msgid, SMSQ_MSG_SEND_FAILED, -1, CLICKATELL_ERROR_HTTP);
//         increment_message_retries(msg);
//     } else if (SMSQ_EXIT_API_ERROR == exitstatus) {
//         LOG_TIME fprintf(logfile, "send_message - SMSC API error:%d msgid:%d", session_data.errornum, msg.msgid); LOG_NL
//         update_message_status(msg.msgid, SMSQ_MSG_SEND_FAILED, -1, session_data.errornum);
//         increment_message_retries(msg);
//     } else if (SMSQ_EXIT_STRING_TOO_LONG == exitstatus) {
//         LOG_TIME fprintf(logfile, "send_message - string too long error: msgid:%d", msg.msgid); LOG_NL
//         update_message_status(msg.msgid, SMSQ_MSG_CANCELLED, -1, -1);
//         increment_message_retries(msg);
//     } else {
//         LOG_TIME fprintf(logfile, "send_message - unknown error:%d msgid:%d", exitstatus, msg.msgid); LOG_NL
//         update_message_status(msg.msgid, SMSQ_MSG_SEND_FAILED, -1, session_data.errornum);
//         increment_message_retries(msg);
//     }
//     return EXIT_SUCCESS;
// }

// int get_message_status(SmsqRecord msg) {
//     int exit_status;
//     int days_queued;

//     exit_status = clickatell_query_status(msg.msgid);
    
//     if (SMSQ_EXIT_SUCCESS == exit_status) {
//         LOG_TIME;
//         fprintf(logfile, "get_message_status: msgnum:%d, msgid:%d, smsqstatus:%d, smscstatus:%d", 
//                 msg.msgnum,
//                 msg.msgid,
//                 msg.smsqstatus,
//                 session_data.smscstatus); LOG_NL

//         switch (session_data.smscstatus) {
//             case CLICKATELL_MSGSTATUS_OK:
//                 // shouldn't get here - status is discontinued
//                 printf("CLICKATELL_MSGSTATUS_OK for msgid:%d at ", msg.msgid); LOG_TIME
//                 fprintf(logfile, "CLICKATELL_MSGSTATUS_OK for msgid:%d at ", msg.msgid); LOG_TIME
                
//                 // get rid of it anyway
//                 update_message_status(msg.msgid, SMSQ_MSG_RECEIVED_OK, session_data.smscstatus, CLICKATELL_ERROR_STATUS_OK_RECEIVED);
//                 break;
//             case CLICKATELL_MSGSTATUS_QUEUED:
//             case CLICKATELL_MSGSTATUS_QUEUED_FOR_LATER:
//                 days_queued = logtime.asXDATE().daysSince(msg.depart.asXDATE());
//                 fprintf(logfile, "msg %d has been queued for %d days", msg.msgid, days_queued); LOG_NL

//                 if (days_queued > SMSQ_MAX_DAYS_QUEUED) {
//                     update_message_status(msg.msgid, SMSQ_MSG_SEND_FAILED, session_data.smscstatus, -1);
//                 } else if (msg.smsqstatus != SMSQ_MSG_SENT_TO_PROVIDER) {
//                     update_message_status(msg.msgid, SMSQ_MSG_SENT_TO_PROVIDER, session_data.smscstatus, -1);
//                 } else {
//                     update_message_status(msg.msgid, -1, session_data.smscstatus, -1);
//                 }
//                 break;
//             case CLICKATELL_MSGSTATUS_DELIVERED:
//                 update_message_status(msg.msgid, SMSQ_MSG_DELIVERED_OK, session_data.smscstatus, -1);
//                 break;
//             case CLICKATELL_MSGSTATUS_RECEIVED:
//                 update_message_status(msg.msgid, SMSQ_MSG_RECEIVED_OK, session_data.smscstatus, -1);
//                 break;
//             case CLICKATELL_MSGSTATUS_MSG_ERROR:
//             case CLICKATELL_MSGSTATUS_DELIVERY_ERROR:
//                 fprintf(logfile, "get_message_status: message with msgid %d send failed, retries: %d",
//                                                 msg.msgid,
//                                                 msg.retries); LOG_NL
//                 increment_message_retries(msg);
//                 if (session_data.smsqstatus != SMSQ_MSG_CANCELLED)
//                     send_message(msg);
//                 break;
//             case CLICKATELL_MSGSTATUS_USER_CANCELLED:
//             case CLICKATELL_MSGSTATUS_EXPIRED:
//             case CLICKATELL_MSGSTATUS_ROUTING_ERROR:
//                 update_message_status(msg.msgid, SMSQ_MSG_CANCELLED, session_data.smscstatus, -1);
//                 break;
//             case CLICKATELL_MSGSTATUS_UNKNOWN:                
//             default:
//                 // ??? SMSQ_MSG_SEND_FAILED ???
//                 update_message_status(msg.msgid, SMSQ_MSG_STATUS_UNKNOWN, CLICKATELL_MSGSTATUS_UNKNOWN, -1);
//                 increment_message_retries(msg);
//         }
//     } else if (SMSQ_EXIT_HTTP_ERROR == exit_status) {
//         fprintf(logfile, "HTTP error on query status msgid:%d", msg.msgid); LOG_NL
//         update_message_status(msg.msgid, SMSQ_MSG_STATUS_UNKNOWN, -1, session_data.errornum);
//         exproc_increment_retries(msg.msgid);
//     } else {
//         fprintf(logfile, "API error on query status msgid:%d, err: %d", msg.msgid, session_data.errornum); LOG_NL
//         update_message_status(msg.msgid, SMSQ_MSG_STATUS_UNKNOWN, -1, session_data.errornum);
//         exproc_increment_retries(msg.msgid);
//     }
    
//     return EXIT_SUCCESS;
// }

// int initSessionData() { // XXX need to intialize other members? no.
//     LOG_TIME fprintf(logfile, "initSessionData"); LOG_DOT
//     session_data.retrylimit = SMSQ_RETRY_LIMIT;
//     sprintf(session_data.api_id, "40510");
//     sprintf(session_data.username, "ctsu");
//     sprintf(session_data.password, "SMS123");
//     fprintf(logfile, "done"); LOG_NL
//     return EXIT_SUCCESS;
// }

// void readIniFile() {
//     FILE* inifile;
//     char debugstring[128]; //XXX

//     inifile = fopen("smsd.rc", "r");
//     if (inifile != NULL) {
//         while (fgets(debugstring, sizeof(debugstring), inifile));
//         session_data.debugflags = atoi(debugstring);
//         fclose(inifile);
//     } else {
//         fprintf(logfile, "no inifile\n"); fflush(logfile);
//         inifile = fopen("smsd.rc", "w");
//         if (NULL != inifile) {
//             fprintf(logfile, "creating new inifile\n"); fflush(logfile);
//             fprintf(inifile, "%d", DEBUG_APIRESPONSE | DEBUG_MESSAGES );
//             fclose(inifile);
//         } else {
//             fprintf(logfile, "couldn't create inifile\n"); fflush(logfile);
//         }
//         session_data.debugflags = DEBUG_MESSAGES;
//     }
// }

bool dbErrorCallback
(const std::string object, const int instance, const int ecount, const int ecode, const std::string error_txt)
{
    std::stringstream sstr;
    sstr << "Database error:\n  object: " << object << "\n  instance: " << instance << "\n  ecount: " << ecount
        << "\n  ecode: " << ecode << "\n  error_txt: " << error_txt;
    LOG_PRINT(sstr.str().c_str());
    return true; //XXX
}

void initDB() {
    LOG_TIME fprintf(logfile, "initDB: '%s'", BBQUIZ_DBNAME); LOG_DOT
    db = new XDB(BBQUIZ_DBNAME); LOG_DOT
    if (!db->open()) { throw "Failed to open database"; }
    db->setErrorCallBack(dbErrorCallback);
    fprintf(logfile, "done"); LOG_NL
}

// int authenticateWithProvider() {
//     LOG_TIME fprintf(logfile, "authenticating"); LOG_DOT
//     int exitstatus = clickatell_authenticate(   session_data.api_id,
//                                             session_data.username,
//                                             session_data.password); LOG_DOT
//     fprintf(logfile, "done"); LOG_DOT LOG_NL
//     return exitstatus;
// }

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
    fprintf(stderr, "stderr test"); // a little test
}

void boilerplate_head() {
    printf("<html><head><title></title></head><body>");
}

void boilerplate_foot() {
    printf("</body></html>");
}

#define DEBUG 0
// 0: off; 1: on


int main(int argc, char **argv) {
    int exitstatus, i;
    // tdvecSmsqRecord::const_iterator recIt;


    XCGI *x = new XCGI(argc, argv);
    x->writeHeader(XCGI::typeHtml);
    //printf("<HTML><BODY><H1>CTSU Web Quiz Service</h1>");//<p>Currently offline for testing</p>");
    boilerplate_head();

    if (DEBUG) { // from cgi_test.cpp
        printf("Method: %s", x->getMethodName().c_str());
        printf("<h3>%d parameters</h3>\n<table border cellspacing=\"0\">", x->param.count());
        int np = x->param.count();
        printf("\n\n<!-- XCGI found %d parameters -->\n", np);
        for (i = 0; i < np; i++) {
            printf( "<tr><td>%d</td><td>%s</td><td>%s</td></tr>", i, x->param.getName(i).c_str(), x->param.getString(i).c_str());
        }
        printf("</table>END");
    }

    // setUpLogfile();
    // readIniFile();
    // initDB();
    // initSessionData();

    //db->close(); LOG_DOT
    //delete db; LOG_DOT LOG_NL

    printf("<h1>bbquiz</h1><p>Hello, World</p>\n");

    //fclose(logfile); // is fclose causing a segfault? - cjb 2009-06-04
    boilerplate_foot();
    return(EXIT_SUCCESS);
}

    //sleep(SMSD_CHECK_PERIOD); XXX
    // exitstatus = authenticateWithProvider();
    // /* } catch (char * message) {
    //     LOG_TIME
    //     fprintf(logfile, "EXCEPTION: %s", message);
    // }*/
    // if (SMSQ_EXIT_SUCCESS == exitstatus) {
    //     LOG_TIME fprintf(logfile, "Begin session - "); fflush(logfile);

    //     clickatell_getbalance(&session_data.balance);
    //     fprintf(logfile, "balance: %dcr\n", session_data.balance); fflush(logfile);
    //     exproc_update_balance(session_data.balance);

    //     if (session_data.debugflags & DEBUG_SEND_FAILED) {
    //         get_messages(SMSQ_MSG_SEND_FAILED);
    //         list_messages("SMSQ_MSG_SEND_FAILED");
    //         for (recIt = smsq_results.begin(); recIt != smsq_results.end(); recIt++) {
    //             get_message_status(*recIt);
    //         }
    //     }

    //     get_messages(SMSQ_MSG_ADDED);
    //     //list_messages("SMSQ_MSG_ADDED");

    //     for (recIt = smsq_results.begin(); recIt != smsq_results.end(); recIt++) {
    //         check_due(*recIt);
    //     }

    //     get_messages(SMSQ_MSG_CLEARED_SEND);
    //     list_messages("SMSQ_MSG_CLEARED_SEND");

    //     std::string temp_destno = "dummy"; // dummy number
    //     for (recIt = smsq_results.begin(); recIt != smsq_results.end(); recIt++) {
    //         /* anti-spam filter - don't send more than one message to the same number this time */
    //         if (0 != (*recIt).destno.compare(temp_destno)) {
    //             temp_destno = (*recIt).destno;
    //             send_message(*recIt);
    //         } else {
    //             LOG_PRINT2("Msg id: %d queued until next sweep to avoid activating spam filter", (*recIt).msgid); LOG_NL;
    //         }
    //     }

    //     get_messages(SMSQ_MSG_SENT_TO_PROVIDER);
    //     list_messages("SMSQ_MSG_SENT_TO_PROVIDER");

    //     for (recIt = smsq_results.begin(); recIt != smsq_results.end(); recIt++) {
    //         get_message_status(*recIt);
    //     }

    //     // XXX handle UNKNOWN messages
    //     get_messages(SMSQ_MSG_STATUS_UNKNOWN);
    //     list_messages("SMSQ_MSG_STATUS_UNKNOWN");

    //     for (recIt = smsq_results.begin(); recIt != smsq_results.end(); recIt++) {
    //         get_message_status(*recIt); // increment retries?? have to stop querying at some point
    //     }

    //     LOG_TIME
    //     clickatell_getbalance(&session_data.balance); LOG_DOT
    //     fprintf(logfile, "End session - balance: %dcr", session_data.balance); LOG_DOT
    //     exproc_update_balance(session_data.balance); LOG_DOT
    // } else {
    //     fprintf(logfile, "Authentication failed at"); LOG_TIME LOG_NL
    //     switch (exitstatus) {
    //         case SMSQ_EXIT_HTTP_ERROR:
    //             LOG_PRINT2("SMSQ_EXIT_HTTP_ERROR: errno: %d\n", session_data.errornum);
    //             break;
    //         case SMSQ_EXIT_API_ERROR:
    //             LOG_PRINT2("SMSQ_EXIT_API_ERROR: errno: %d\n", session_data.errornum);
    //             break;
    //         default:
    //             LOG_PRINT2("unknown error: %d\n", session_data.errornum);
    //             break;
    //     }
    // }
