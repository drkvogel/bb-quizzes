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

// cruft.cpp
// unused code

void setUpLogfile() {
    char logfilename[32];
    logtime.setNow();
    sprintf(logfilename, DIR_LOG "bbquiz_%4.4d-%2.2d.log", logtime.asXDATE().getYear(), logtime.asXDATE().getMonth());
    logfile = fopen(logfilename, "a");
    if (NULL == logfile) printf("couldn't open logfile"); //XXX
#ifndef __WIN32__
    struct rlimit coredumplimit;
    // n.b. if setting a specific size, these limits are in bytes, whilst those set by ulimit (in bash) are in 1k blocks
    coredumplimit.rlim_cur = RLIM_INFINITY; //XXX ?
    coredumplimit.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &coredumplimit);
#endif
    //fprintf(stderr, "stderr test"); // a little test
}

    setUpLogfile();
    readIniFile();
    initSessionData();
        printf("<p><code>action: '%s'</code></p>\n", x->param.getStringDefault("action", "").c_str());
        printf("<p><code>quiz: '%s'</code></p>\n", x->param.getStringDefault("quiz", "").c_str());
    printf("<form action=\"#\">\n"
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
        "</form>\n");
int initDB() {
    LOG_TIME fprintf(logfile, "initDB: '%s'\n", BBQUIZ_DBNAME); LOG_DOT
    db = new XDB(BBQUIZ_DBNAME); LOG_DOT
    if (!db->open()) {  throw "Failed to open database"; }
    db->setErrorCallBack(dbErrorCallback);
    fprintf(logfile, "done"); LOG_NL
    return 0;
}
    printf("<li><a href=\"?quiz=matrix&action=start\">Start Matrix Quiz</a></li>\n");
    printf("<li><a href=\"?quiz=hoops&action=start\">Start Hoops Quiz</a></li>\n");

/*        } else if (paramIs("action", "start") && paramIs("quiz", "matrix")) {
            startMatrix();
        } else if (paramIs("action", "start") && paramIs("quiz", "hoops")) {
            startHoops();*/

// void startMatrix() {
//     printf("<p>startMatrix()</p>");
// }
// 
// void startHoops() {
//     printf("<p>startHoops()</p>");
// }


// string nowString() { // UNIX time in seconds
//     time_t  tnow;
//     char timestring[32];
//     strcpy(timestring, ctime(&tnow));
//     timestring[24] = '\0'; // remove annoying non-configurable newline added by ctime
//     //time(&tnow); // ctime(&tnow)
//     return string(timestring);
// }

/*    char timestring[32];
    strcpy(timestring, ctime(&tnow));
    timestring[24] = '\0'; // remove annoying non-configurable newline added by ctime
    //printf("{\n  \"session\": {\n    \"comment\" : \"some JSON\",\n    \"seshID\": \"%s\"\n  }\n}", timestring);*/
    //printf("{\n  \"session\": {\n    \"comment\" : \"some JSON\",\n    \"seshID\": \"%d\"\n  }\n}", (int)tnow);


/*    printf("<tr><td>-</td>");
    printf("<td colspan=3><a href=\"idserve.cgi\">idserve.cgi</a></td>");
    printf("</tr>\n");*/

//printf("arr[%d]=(%d) %ld %lf %s<br />\n", i, (int)item->type, item->int_value, item->dbl_value, item->text_value);

//         // get first item in array, should be NX_JSON_OBJECT
//         const nx_json* node = nx_json_item(arr, 0);
//         if (NX_JSON_NULL == node->type) {
//             printf("NX_JSON_NULL node<br />");
//             throw "Error parsing JSON";
//         }
//         printf("got json node type: %s, length: %d<br />", nx_json_type_names[node->type], node->length);
//         printAnswer(node);
// 
//         const nx_json* ans;
//         while ((ans = nx_json_item(json, idx++)) && ans->type != NX_JSON_NULL) { // doesn't finish...
//             printf("ans %d: ", idx);
//             printAnswer(ans);
//             if (idx > 20) return;
//         }

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


    //fclose(logfile); // fclose causing segfault - cjb 2009-06-04, 2016-08-09
    //delete db; LOG_DOT LOG_NL // segfault
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

// int authenticateWithProvider() {
//     LOG_TIME fprintf(logfile, "authenticating"); LOG_DOT
//     int exitstatus = clickatell_authenticate(   session_data.api_id,
//                                             session_data.username,
//                                             session_data.password); LOG_DOT
//     fprintf(logfile, "done"); LOG_DOT LOG_NL
//     return exitstatus;
// }

// extern char smscstatus_descript[][50];
// extern char smsqstatus_descript[][30];
// extern session_data_st session_data;

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

/*
    int total_count = 0;
    std::string tab, chk, ack;
    DATABASE_ENTRY  e;
    std::vector<DATABASE_ENTRY> cent;
    const   std::vector<DATABASE_ENTRY> *acks_todo = NULL;
    if ( use_cache )
        {refreshCache();
        acks_todo = getAcks();
        }
    else                // LOAD FROM CENTRAL ACKS_TODO TABLE
        {std::string    sql = "SELECT DISTINCT trid,cid,tabl"
            " FROM ack_todo WHERE ";
        XQUERY  q( db, sql );
        if ( target_comp )      // TARGET IS A COMPUTER
            {q.extendSQL( "xu_hid= :h" );
            q.param.setInt( "h", target_id );
            }
        else                // TARGET IS A WHOLE CENTRE
            {q.extendSQL( "aid= :a" );
            q.param.setInt( "a", target_id );
            }
        if ( ! q.open() )
            {return( -1 );
            }
        while ( q.fetch() )
            {
            e.trid = q.result.getInt(0);
            e.cid  = q.result.getInt(1);
            tab    = q.result.getString(2);
            strncpy( e.tabl, tab.c_str(), 12 );
            cent.push_back( e );
            }
        q.close();
        acks_todo = &cent;
        }
    std::vector<DATABASE_ENTRY>::const_iterator ai = acks_todo->begin();    int total_count = 0;
    std::string tab, chk, ack;
    DATABASE_ENTRY  e;
    std::vector<DATABASE_ENTRY> cent;
    const   std::vector<DATABASE_ENTRY> *acks_todo = NULL;
    if ( use_cache )
        {refreshCache();
        acks_todo = getAcks();
        }
    else                // LOAD FROM CENTRAL ACKS_TODO TABLE
        {std::string    sql = "SELECT DISTINCT trid,cid,tabl"
            " FROM ack_todo WHERE ";
        XQUERY  q( db, sql );
        if ( target_comp )      // TARGET IS A COMPUTER
            {q.extendSQL( "xu_hid= :h" );
            q.param.setInt( "h", target_id );
            }
        else                // TARGET IS A WHOLE CENTRE
            {q.extendSQL( "aid= :a" );
            q.param.setInt( "a", target_id );
            }
        if ( ! q.open() )
            {return( -1 );
            }
        while ( q.fetch() )
            {
            e.trid = q.result.getInt(0);
            e.cid  = q.result.getInt(1);
            tab    = q.result.getString(2);
            strncpy( e.tabl, tab.c_str(), 12 );
            cent.push_back( e );
            }
        q.close();
        acks_todo = &cent;
        }
    std::vector<DATABASE_ENTRY>::const_iterator ai = acks_todo->begin();
*/

/*    int duration1;
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
    int correct18;*/

    /*        xe.param.setInt(string("duration") + string(i), -1);
        xe.param.setInt(string("puzzle") + string(i),   -1);
        xe.param.setInt(string("elapsed") + string(i),  -1);
        xe.param.setInt(string("answer") + string(i),   -1);
        xe.param.setInt(string("correct") + string(i),  -1);*/


//     xe.param.setInt("duration1",     e->duration1);
//     xe.param.setInt("puzzle1",       e->puzzle1);
//     xe.param.setInt("elapsed1",      e->elapsed1);
//     xe.param.setInt("answer1",       e->answer1);
//     xe.param.setInt("correct1",      e->correct1);
// 
//     xe.param.setInt("duration2",     e->duration2);
//     xe.param.setInt("puzzle2",       e->puzzle2);
//     xe.param.setInt("elapsed2",      e->elapsed2);
//     xe.param.setInt("answer2",       e->answer2);
//     xe.param.setInt("correct2",      e->correct2);
// 
//     xe.param.setInt("duration3",     e->duration3);
//     xe.param.setInt("puzzle3",       e->puzzle3);
//     xe.param.setInt("elapsed3",      e->elapsed3);
//     xe.param.setInt("answer3",       e->answer3);
//     xe.param.setInt("correct3",      e->correct3);
// 
//     xe.param.setInt("duration4",     e->duration4);
//     xe.param.setInt("puzzle4",       e->puzzle4);
//     xe.param.setInt("elapsed4",      e->elapsed4);
//     xe.param.setInt("answer4",       e->answer4);
//     xe.param.setInt("correct4",      e->correct4);
// 
//     xe.param.setInt("duration5",     e->duration5);
//     xe.param.setInt("puzzle5",       e->puzzle5);
//     xe.param.setInt("elapsed5",      e->elapsed5);
//     xe.param.setInt("answer5",       e->answer5);
//     xe.param.setInt("correct5",      e->correct5);
// 
//     xe.param.setInt("duration6",     e->duration6);
//     xe.param.setInt("puzzle6",       e->puzzle6);
//     xe.param.setInt("elapsed6",      e->elapsed6);
//     xe.param.setInt("answer6",       e->answer6);
//     xe.param.setInt("correct6",      e->correct6);
// 
//     xe.param.setInt("duration7",     e->duration7);
//     xe.param.setInt("puzzle7",       e->puzzle7);
//     xe.param.setInt("elapsed7",      e->elapsed7);
//     xe.param.setInt("answer7",       e->answer7);
//     xe.param.setInt("correct7",      e->correct7);
// 
//     xe.param.setInt("duration8",     e->duration8);
//     xe.param.setInt("puzzle8",       e->puzzle8);
//     xe.param.setInt("elapsed8",      e->elapsed8);
//     xe.param.setInt("answer8",       e->answer8);
//     xe.param.setInt("correct8",      e->correct8);
// 
//     xe.param.setInt("duration9",     e->duration9);
//     xe.param.setInt("puzzle9",       e->puzzle9);
//     xe.param.setInt("elapsed9",      e->elapsed9);
//     xe.param.setInt("answer9",       e->answer9);
//     xe.param.setInt("correct9",      e->correct9);
// 
//     xe.param.setInt("duration10",     e->duration10);
//     xe.param.setInt("puzzle10",       e->puzzle10);
//     xe.param.setInt("elapsed10",      e->elapsed10);
//     xe.param.setInt("answer10",       e->answer10);
//     xe.param.setInt("correct10",      e->correct10);
// 
//     xe.param.setInt("duration11",     e->duration11);
//     xe.param.setInt("puzzle11",       e->puzzle11);
//     xe.param.setInt("elapsed11",      e->elapsed11);
//     xe.param.setInt("answer11",       e->answer11);
//     xe.param.setInt("correct11",      e->correct11);
// 
//     xe.param.setInt("duration12",     e->duration12);
//     xe.param.setInt("puzzle12",       e->puzzle12);
//     xe.param.setInt("elapsed12",      e->elapsed12);
//     xe.param.setInt("answer12",       e->answer12);
//     xe.param.setInt("correct12",      e->correct12);
// 
//     xe.param.setInt("duration13",     e->duration13);
//     xe.param.setInt("puzzle13",       e->puzzle13);
//     xe.param.setInt("elapsed13",      e->elapsed13);
//     xe.param.setInt("answer13",       e->answer13);
//     xe.param.setInt("correct13",      e->correct13);
// 
//     xe.param.setInt("duration14",     e->duration14);
//     xe.param.setInt("puzzle14",       e->puzzle14);
//     xe.param.setInt("elapsed14",      e->elapsed14);
//     xe.param.setInt("answer14",       e->answer14);
//     xe.param.setInt("correct14",      e->correct14);
// 
//     xe.param.setInt("duration15",     e->duration15);
//     xe.param.setInt("puzzle15",       e->puzzle15);
//     xe.param.setInt("elapsed15",      e->elapsed15);
//     xe.param.setInt("answer15",       e->answer15);
//     xe.param.setInt("correct15",      e->correct15);
// 
//     xe.param.setInt("duration16",     e->duration16);
//     xe.param.setInt("puzzle16",       e->puzzle16);
//     xe.param.setInt("elapsed16",      e->elapsed16);
//     xe.param.setInt("answer16",       e->answer16);
//     xe.param.setInt("correct16",      e->correct16);
// 
//     xe.param.setInt("duration17",     e->duration17);
//     xe.param.setInt("puzzle17",       e->puzzle17);
//     xe.param.setInt("elapsed17",      e->elapsed17);
//     xe.param.setInt("answer17",       e->answer17);
//     xe.param.setInt("correct17",      e->correct17);
// 
//     xe.param.setInt("duration18",     e->duration18);
//     xe.param.setInt("puzzle18",       e->puzzle18);
//     xe.param.setInt("elapsed18",      e->elapsed18);
//     xe.param.setInt("answer18",       e->answer18);
//     xe.param.setInt("correct18",      e->correct18);


/*        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration1, it->puzzle1, it->elapsed1, it->answer1, it->correct1);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration2, it->puzzle2, it->elapsed2, it->answer2, it->correct2);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration3, it->puzzle3, it->elapsed3, it->answer3, it->correct3);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration4, it->puzzle4, it->elapsed4, it->answer4, it->correct4);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration5, it->puzzle5, it->elapsed5, it->answer5, it->correct5);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration6, it->puzzle6, it->elapsed6, it->answer6, it->correct6);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration7, it->puzzle7, it->elapsed7, it->answer7, it->correct7);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration8, it->puzzle8, it->elapsed8, it->answer8, it->correct8);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration9, it->puzzle9, it->elapsed9, it->answer9, it->correct9);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration10, it->puzzle10, it->elapsed10, it->answer10, it->correct10);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration11, it->puzzle11, it->elapsed11, it->answer11, it->correct11);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration12, it->puzzle12, it->elapsed12, it->answer12, it->correct12);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration13, it->puzzle13, it->elapsed13, it->answer13, it->correct13);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration14, it->puzzle14, it->elapsed14, it->answer14, it->correct14);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration15, it->puzzle15, it->elapsed15, it->answer15, it->correct15);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration16, it->puzzle16, it->elapsed16, it->answer16, it->correct16);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration17, it->puzzle17, it->elapsed17, it->answer17, it->correct17);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration18, it->puzzle18, it->elapsed18, it->answer18, it->correct18);*/

//printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>",

//     printf("<td>duration1</td><td>puzzle1</td><td>elapsed1</td><td>answer1</td><td>correct1</td>");
//     printf("<td>duration2</td><td>puzzle2</td><td>elapsed2</td><td>answer2</td><td>correct2</td>");
//     printf("<td>duration3</td><td>puzzle3</td><td>elapsed3</td><td>answer3</td><td>correct3</td>");
//     printf("<td>duration4</td><td>puzzle4</td><td>elapsed4</td><td>answer4</td><td>correct4</td>");
//     printf("<td>duration5</td><td>puzzle5</td><td>elapsed5</td><td>answer5</td><td>correct5</td>");
//     printf("<td>duration6</td><td>puzzle6</td><td>elapsed6</td><td>answer6</td><td>correct6</td>");
//     printf("<td>duration7</td><td>puzzle7</td><td>elapsed7</td><td>answer7</td><td>correct7</td>");
//     printf("<td>duration8</td><td>puzzle8</td><td>elapsed8</td><td>answer8</td><td>correct8</td>");
//     printf("<td>duration9</td><td>puzzle9</td><td>elapsed9</td><td>answer9</td><td>correct9</td>");
//     printf("<td>duration10</td><td>puzzle10</td><td>elapsed10</td><td>answer10</td><td>correct10</td>");
//     printf("<td>duration11</td><td>puzzle11</td><td>elapsed11</td><td>answer11</td><td>correct11</td>");
//     printf("<td>duration12</td><td>puzzle12</td><td>elapsed12</td><td>answer12</td><td>correct12</td>");
//     printf("<td>duration13</td><td>puzzle13</td><td>elapsed13</td><td>answer13</td><td>correct13</td>");
//     printf("<td>duration14</td><td>puzzle14</td><td>elapsed14</td><td>answer14</td><td>correct14</td>");
//     printf("<td>duration15</td><td>puzzle15</td><td>elapsed15</td><td>answer15</td><td>correct15</td>");
//     printf("<td>duration16</td><td>puzzle16</td><td>elapsed16</td><td>answer16</td><td>correct16</td>");
//     printf("<td>duration17</td><td>puzzle17</td><td>elapsed17</td><td>answer17</td><td>correct17</td>");
//     printf("<td>duration18</td><td>puzzle18</td><td>elapsed18</td><td>answer18</td><td>correct18</td>\n");



