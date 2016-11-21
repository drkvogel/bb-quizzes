#include "xquery.h"
#include "xexec.h"
#include "trails.h"
#include "bbquiz.h"
//#include <iostream>
#include <cstring>

const bool DEBUG = true;
#define IFDEBUG if (DEBUG)

using namespace std;

Trails::vecTrailsRecord TrailsRecords;

// const char Trails::nx_json_type_names[7][20] =
//     "NX_JSON_NULL", "NX_JSON_OBJECT", "NX_JSON_ARRAY", "NX_JSON_STRING", "NX_JSON_INTEGER", "NX_JSON_DOUBLE", "NX_JSON_BOOL"
// ;

// Trails::vecTrailsRecord records;

void Trails::printJSONAnswer(const nx_json* node) {
    printf("[node type: %s, length: %d]: count: %d, puzzle: %d, answer: %d, correct: %d, time: %d<br />",
        //nx_json_type_names[node->type], node->length,
        "[nx_json_type_names] not implemented",
        nx_json_get(node, "count")->int_value,
        nx_json_get(node, "puzzle")->int_value,
        nx_json_get(node, "answer")->int_value,
        nx_json_get(node, "correct")->int_value,
        nx_json_get(node, "time")->int_value);
}

void Trails::printTrailsAnswer(TrailsAnswer & ans) {
    printf("ans: puzzle: %d, wrongClicks: %d, duration: %d, elapsed: %d<br />\n",
            ans.puzzle.c_str(), ans.wrongClicks, ans.duration, ans.elapsed);
}

void Trails::parseResponses(TrailsRecord *rec) {
    IFDEBUG printf("<code>parseResponses():");
    try {
        char * buf = new char[rec->responses.length() + 1];
        strcpy(buf, rec->responses.c_str()); // nxson modifies string in place, don't destroy original responses
            // db row may be fixed width, but user might not have finished
        const nx_json* arr = nx_json_parse(buf, 0); // needs char *, not const
        if (!arr) {
            printf("didn't get json<br />"); throw "Error parsing JSON";
        }
        IFDEBUG printf("got json node type: %d, arr->length: %d<br />", arr->type, arr->length); // "nx_json_type_names[arr->type]"
        IFDEBUG printf("ntests reported by payload: %d; number of tests in responses JSON blob: %d<br />", rec->ntests, arr->length);
        if (rec->ntests != arr->length) {
            const char * errmsg = "<p>ERROR: rec->ntests != arr->length</p>";
            printf("%s", errmsg); throw errmsg;
        }

        // element: element,                      // id of element clicked on by user
        // duration: timer.getElapsed(),          // Time taken to click on next correct element
        // wrongClicks: wrongClicks,              // number of wrong clicks before correct
        // puzzle: page.name,                     // name of puzzle/practice
        // elapsed: timerWholeTest.getElapsed()

// (1) INT2 capped at 9999 (16 mins): time it was correctly clicked (deciseconds); Absolute time since the screen was first displayed.
// (2) INT1 capped at 99: number of incorrect clicks made between previous circle and this one.
// SMALLINT_MAX
// 32000 deciseconds = 53 minutes
#define MAX_DURATION 32000
#define MAX_WRONGCLICKS 99
        IFDEBUG printf("about to parse answers");
        for (int i=0; i < arr->length; i++) {
            const nx_json* item = nx_json_item(arr, i);
            TrailsAnswer ans;
            ans.wrongClicks = nx_json_get(item, "wrongClicks"   )->int_value;       // Number of wrong clicks before correct
            ans.duration    = nx_json_get(item, "duration"      )->int_value / 100; // Time taken to click correct, already converted to deciseconds
            ans.elapsed     = nx_json_get(item, "elapsed"       )->int_value / 100; // Cumulative time elapsed since start of test, already converted to deciseconds
            if (ans.wrongClicks > MAX_WRONGCLICKS) ans.wrongClicks = MAX_WRONGCLICKS; // cap
            if (ans.duration > MAX_DURATION) ans.duration = MAX_DURATION; // cap at ~1hr
            if (ans.elapsed > MAX_DURATION) ans.elapsed = MAX_DURATION; // cap at ~1hr
            printf("elapsed (JSON): %d<br />", nx_json_get(item, "elapsed")->int_value);
            printf("elapsed (deciseconds, capped): %d<br />", ans.elapsed);
            //printf("%d ", nx_json_get(item, "count")->int_value);
            //printJSONAnswer(item);
            //printTrailsAnswer(ans);
            rec->answers.push_back(ans);
        }
        nx_json_free(arr);
        delete [] buf;
    } catch(...) {
        printf("Error parsing JSON");
    }
    IFDEBUG printf("</code>\n");
}

string Trails::nowString() { // UNIX time in seconds
    time_t  tnow;
    char timestring[32];
    strcpy(timestring, ctime(&tnow)); //time(&tnow);
    timestring[24] = '\0'; // remove annoying non-configurable newline added by ctime
    return string(timestring);
}

Trails::TrailsRecord Trails::getPayload(XCGI * x) { // get responses from frontend
    IFDEBUG printf("<code>this is getPayload() in %s.<br />\n", __FILE__); //int np = x->param.count();
    TrailsRecord rec;
    rec.sesh_id = x->getParamAsInt("sesh_id"); // up to date xcgi.cpp/h has getParam, paramExists, but not this copy
    if (0 == rec.sesh_id) { // something went wrong, e.g. didn't get form data
        throw "Form data error";
    }
    IFDEBUG printf("sesh_id: %d", rec.sesh_id);
    rec.tinstruct.set(x->param.getString("tinstruct").c_str()); //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
    rec.tstart.set(x->param.getString("tstart").c_str()); //nowString().c_str());
    rec.tfinish.set(x->param.getString("tfinish").c_str());
    IFDEBUG printf("<p>tinstruct.iso(): '%s'<br />tstart.iso(): '%s'<br />tfinish.iso(): '%s'<br />",
        rec.tinstruct.iso().c_str(), rec.tstart.iso().c_str(), rec.tfinish.iso().c_str());
    rec.responses = x->param.getString("responses");
    IFDEBUG printf("<p>responses:</p><pre>%s</pre>\n", rec.responses.c_str());
    rec.ntests = x->getParamAsInt("ntests");
    parseResponses(&rec); // rec.ntests can be determined from responses? or should be passed from frontend and checked
    IFDEBUG printf("sesh_id: %d", rec.sesh_id);
    IFDEBUG printf("<p>done</p>\n");
    return rec;
}

void Trails::insertAnswer(int i, const TrailsAnswer * ans, XEXEC & x) {
    //IFDEBUG printf("insertAnswer(): i: %d, ans: %s<br />\n", i, NULL == ans ? "NULL" : "");
    const char * section;
    if (i < NUM_POINTS_AP) {                                        // practice-a
        section = "ap";
    } else if (i < NUM_POINTS_AP + NUM_POINTS_AR) {                 // part-a
        section = "ar";
        i -= NUM_POINTS_AP;
    } else if (i < NUM_POINTS_AP + NUM_POINTS_AR + NUM_POINTS_BP) { // practice-b
        section = "bp";
        i -= (NUM_POINTS_AP + NUM_POINTS_AR);
    } else if (i < NUM_POINTS_TOTAL) {                              // part-b
        section = "br";
        i -= (NUM_POINTS_AP + NUM_POINTS_AR + NUM_POINTS_BP);
    }
    //IFDEBUG printf("section: %s<br />\n", section);
    IFDEBUG printf("wrong: %d, time: %d, total: %d<br />\n", NULL == ans ? -1 : ans->wrongClicks, NULL == ans ? -1 : ans->duration, NULL == ans ? -1 : ans->elapsed);

    char fieldname[16];
    sprintf(fieldname, "%s_%d_wrong", section, i+1);    x.param.setInt(fieldname, NULL == ans ? -1 : ans->wrongClicks); //IFDEBUG printf("fieldname: %s<br />\n", fieldname);
    sprintf(fieldname, "%s_%d_time",  section, i+1);    x.param.setInt(fieldname, NULL == ans ? -1 : ans->duration); //IFDEBUG printf("fieldname: %s<br />\n", fieldname);
    sprintf(fieldname, "%s_%d_total", section, i+1);    x.param.setInt(fieldname, NULL == ans ? -1 : ans->elapsed); //IFDEBUG printf("fieldname: %s<br />\n", fieldname);
}
    // for (int i = 0; i < rec.ntests && i < numFields; i++) {
        //TrailsAnswer ans;
        //sprintf(fieldname, "puzzle%d", i+1);    ans.puzzle = q.result.getInt(fieldname);
        //rec.answers.push_back(ans);
    // }
            // insertValues(xe, rec, "ap", NUM_POINTS_AP);
            // insertValues(xe, rec, "ar", NUM_POINTS_AR);
            // insertValues(xe, rec, "bp", NUM_POINTS_BP);
            // insertValues(xe, rec, "br", NUM_POINTS_BR);

bool Trails::insertRecord(const TrailsRecord *rec) {
    IFDEBUG printf("<p><code>Trails::insertRecord()</p>\n");
    const char responseFields[] = "ap_1_wrong, ap_1_time, ap_1_total, ap_2_wrong, ap_2_time, ap_2_total, ap_3_wrong, ap_3_time, ap_3_total, ap_4_wrong, ap_4_time, ap_4_total, ap_5_wrong, ap_5_time, ap_5_total, ap_6_wrong, ap_6_time, ap_6_total, ap_7_wrong, ap_7_time, ap_7_total, ap_8_wrong, ap_8_time, ap_8_total, ar_1_wrong, ar_1_time, ar_1_total, ar_2_wrong, ar_2_time, ar_2_total, ar_3_wrong, ar_3_time, ar_3_total, ar_4_wrong, ar_4_time, ar_4_total, ar_5_wrong, ar_5_time, ar_5_total, ar_6_wrong, ar_6_time, ar_6_total, ar_7_wrong, ar_7_time, ar_7_total, ar_8_wrong, ar_8_time, ar_8_total, ar_9_wrong, ar_9_time, ar_9_total, ar_10_wrong, ar_10_time, ar_10_total, ar_11_wrong, ar_11_time, ar_11_total, ar_12_wrong, ar_12_time, ar_12_total, ar_13_wrong, ar_13_time, ar_13_total, ar_14_wrong, ar_14_time, ar_14_total, ar_15_wrong, ar_15_time, ar_15_total, ar_16_wrong, ar_16_time, ar_16_total, ar_17_wrong, ar_17_time, ar_17_total, ar_18_wrong, ar_18_time, ar_18_total, ar_19_wrong, ar_19_time, ar_19_total, ar_20_wrong, ar_20_time, ar_20_total, ar_21_wrong, ar_21_time, ar_21_total, ar_22_wrong, ar_22_time, ar_22_total, ar_23_wrong, ar_23_time, ar_23_total, ar_24_wrong, ar_24_time, ar_24_total, ar_25_wrong, ar_25_time, ar_25_total, bp_1_wrong, bp_1_time, bp_1_total, bp_2_wrong, bp_2_time, bp_2_total, bp_3_wrong, bp_3_time, bp_3_total, bp_4_wrong, bp_4_time, bp_4_total, bp_5_wrong, bp_5_time, bp_5_total, bp_6_wrong, bp_6_time, bp_6_total, bp_7_wrong, bp_7_time, bp_7_total, bp_8_wrong, bp_8_time, bp_8_total, br_1_wrong, br_1_time, br_1_total, br_2_wrong, br_2_time, br_2_total, br_3_wrong, br_3_time, br_3_total, br_4_wrong, br_4_time, br_4_total, br_5_wrong, br_5_time, br_5_total, br_6_wrong, br_6_time, br_6_total, br_7_wrong, br_7_time, br_7_total, br_8_wrong, br_8_time, br_8_total, br_9_wrong, br_9_time, br_9_total, br_10_wrong, br_10_time, br_10_total, br_11_wrong, br_11_time, br_11_total, br_12_wrong, br_12_time, br_12_total, br_13_wrong, br_13_time, br_13_total, br_14_wrong, br_14_time, br_14_total, br_15_wrong, br_15_time, br_15_total, br_16_wrong, br_16_time, br_16_total, br_17_wrong, br_17_time, br_17_total, br_18_wrong, br_18_time, br_18_total, br_19_wrong, br_19_time, br_19_total, br_20_wrong, br_20_time, br_20_total, br_21_wrong, br_21_time, br_21_total, br_22_wrong, br_22_time, br_22_total, br_23_wrong, br_23_time, br_23_total, br_24_wrong, br_24_time, br_24_total, br_25_wrong, br_25_time, br_25_total";
    const char responseParams[] = ":ap_1_wrong, :ap_1_time, :ap_1_total, :ap_2_wrong, :ap_2_time, :ap_2_total, :ap_3_wrong, :ap_3_time, :ap_3_total, :ap_4_wrong, :ap_4_time, :ap_4_total, :ap_5_wrong, :ap_5_time, :ap_5_total, :ap_6_wrong, :ap_6_time, :ap_6_total, :ap_7_wrong, :ap_7_time, :ap_7_total, :ap_8_wrong, :ap_8_time, :ap_8_total, :ar_1_wrong, :ar_1_time, :ar_1_total, :ar_2_wrong, :ar_2_time, :ar_2_total, :ar_3_wrong, :ar_3_time, :ar_3_total, :ar_4_wrong, :ar_4_time, :ar_4_total, :ar_5_wrong, :ar_5_time, :ar_5_total, :ar_6_wrong, :ar_6_time, :ar_6_total, :ar_7_wrong, :ar_7_time, :ar_7_total, :ar_8_wrong, :ar_8_time, :ar_8_total, :ar_9_wrong, :ar_9_time, :ar_9_total, :ar_10_wrong, :ar_10_time, :ar_10_total, :ar_11_wrong, :ar_11_time, :ar_11_total, :ar_12_wrong, :ar_12_time, :ar_12_total, :ar_13_wrong, :ar_13_time, :ar_13_total, :ar_14_wrong, :ar_14_time, :ar_14_total, :ar_15_wrong, :ar_15_time, :ar_15_total, :ar_16_wrong, :ar_16_time, :ar_16_total, :ar_17_wrong, :ar_17_time, :ar_17_total, :ar_18_wrong, :ar_18_time, :ar_18_total, :ar_19_wrong, :ar_19_time, :ar_19_total, :ar_20_wrong, :ar_20_time, :ar_20_total, :ar_21_wrong, :ar_21_time, :ar_21_total, :ar_22_wrong, :ar_22_time, :ar_22_total, :ar_23_wrong, :ar_23_time, :ar_23_total, :ar_24_wrong, :ar_24_time, :ar_24_total, :ar_25_wrong, :ar_25_time, :ar_25_total, :bp_1_wrong, :bp_1_time, :bp_1_total, :bp_2_wrong, :bp_2_time, :bp_2_total, :bp_3_wrong, :bp_3_time, :bp_3_total, :bp_4_wrong, :bp_4_time, :bp_4_total, :bp_5_wrong, :bp_5_time, :bp_5_total, :bp_6_wrong, :bp_6_time, :bp_6_total, :bp_7_wrong, :bp_7_time, :bp_7_total, :bp_8_wrong, :bp_8_time, :bp_8_total, :br_1_wrong, :br_1_time, :br_1_total, :br_2_wrong, :br_2_time, :br_2_total, :br_3_wrong, :br_3_time, :br_3_total, :br_4_wrong, :br_4_time, :br_4_total, :br_5_wrong, :br_5_time, :br_5_total, :br_6_wrong, :br_6_time, :br_6_total, :br_7_wrong, :br_7_time, :br_7_total, :br_8_wrong, :br_8_time, :br_8_total, :br_9_wrong, :br_9_time, :br_9_total, :br_10_wrong, :br_10_time, :br_10_total, :br_11_wrong, :br_11_time, :br_11_total, :br_12_wrong, :br_12_time, :br_12_total, :br_13_wrong, :br_13_time, :br_13_total, :br_14_wrong, :br_14_time, :br_14_total, :br_15_wrong, :br_15_time, :br_15_total, :br_16_wrong, :br_16_time, :br_16_total, :br_17_wrong, :br_17_time, :br_17_total, :br_18_wrong, :br_18_time, :br_18_total, :br_19_wrong, :br_19_time, :br_19_total, :br_20_wrong, :br_20_time, :br_20_total, :br_21_wrong, :br_21_time, :br_21_total, :br_22_wrong, :br_22_time, :br_22_total, :br_23_wrong, :br_23_time, :br_23_total, :br_24_wrong, :br_24_time, :br_24_total, :br_25_wrong, :br_25_time, :br_25_total";
    string sql =
        "INSERT INTO Trails (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert,"
        " responses, " + string(responseFields) + " )\n"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :responses, " + string(responseParams) + " )\n";
    //IFDEBUG printf("sql:\n%s\n<br />", sql.c_str());
    XEXEC xe(db, sql); IFDEBUG printf("made XEXEC object...\n");
    xe.param.setInt("sesh_id",       rec->sesh_id);
    xe.param.setTime("tinstruct",    rec->tinstruct);
    xe.param.setTime("tstart",       rec->tstart);
    xe.param.setTime("tfinish",      rec->tfinish);
    xe.param.setInt("ntests",        rec->ntests);
    xe.param.setString("responses",  rec->responses);
    IFDEBUG printf("added header fields...<br />\n"); //printf("tinstruct: '%s', tstart: '%s', tfinish: '%s'...", rec->tinstruct.iso().c_str(), rec->tstart.iso().c_str(), rec->tfinish.iso().c_str());
    IFDEBUG printf("adding answers...<br />\n");

    for (int i=0; i<rec->answers.size(); i++) { // safer, should agree with rec->ntests
        insertAnswer(i, &rec->answers[i], xe);
    }
    IFDEBUG printf("adding blanks...<br />\n");
    for (int i=rec->answers.size(); i<NUM_POINTS_TOTAL; i++) { // safer, should agree with rec->ntests
        insertAnswer(i, NULL, xe);
    }
    IFDEBUG printf("about to exec query...<br />\n");

    //#define NUM_POINTS_TOTAL NUM_POINTS_AP + NUM_POINTS_AR + NUM_POINTS_BP + NUM_POINTS_BR

    // insert answered puzzles
    // copied from hoops, trails will be different
    // char fieldname[12];s
    // for (int i=0; i<rec->answers.size(); i++) { // safer, should agree with rec->ntests
    //     IFDEBUG printf("%d ", i+1); //printf("answer %d/%d<br />", i+1, rec->answers.size());
    //     sprintf(fieldname, "duration%d", i+1);  xe.param.setInt(fieldname,  rec->answers[i].duration); //printf("field: '%s', value: %d<br />\n", fieldname,  rec->answers[i].duration);
    //     sprintf(fieldname, "puzzle%d", i+1);    xe.param.setInt(fieldname,  rec->answers[i].puzzle);
    //     sprintf(fieldname, "elapsed%d", i+1);   xe.param.setInt(fieldname,  rec->answers[i].elapsed);
    //     sprintf(fieldname, "answer%d", i+1);    xe.param.setInt(fieldname,  rec->answers[i].answer);
    //     sprintf(fieldname, "correct%d", i+1);   xe.param.setInt(fieldname,  rec->answers[i].correct);
    // }
    // IFDEBUG printf("<br />added %d answered puzzles...<br />\n", rec->answers.size());

    // // insert 'nulls' (-1) for the rest explicitly, otherwise fields have to have defaults
    // for (int i = rec->answers.size()+1; i <= MAX_LEVELS; i++) {
    //     sprintf(fieldname, "duration%d", i);    xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
    //     sprintf(fieldname, "puzzle%d", i);      xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
    //     sprintf(fieldname, "elapsed%d", i);     xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
    //     sprintf(fieldname, "answer%d", i);      xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
    //     sprintf(fieldname, "correct%d", i);     xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
    // }
    // IFDEBUG printf("added %d null records...<br />\n", MAX_LEVELS - rec->answers.size());
    return (xe.exec());
}

void Trails::getRecords() {
    TrailsRecords.clear();
    std::string sql = "SELECT * FROM Trails";
    XQUERY q(db, sql);
    IFDEBUG printf("this is %s<br />\n", __FILE__);
    if (!q.open()) {
        printf("Database error"); throw "Database error";
    } else {
        IFDEBUG printf("Database open");
    }
    while (q.fetch()) {
        TrailsRecord rec;
        rec.sesh_id   = q.result.getInt("sesh_id");
        rec.tinstruct = q.result.getTime("tinstruct");      // getDate?
        rec.tstart    = q.result.getTime("tstart");
        rec.tfinish   = q.result.getTime("tfinish");
        rec.responses = q.result.getString("responses");    // JSON blob
        rec.ntests    = q.result.getInt("ntests");          // is ntests sane?
        getResults(q, rec, "ap", NUM_POINTS_AP);
        getResults(q, rec, "ar", NUM_POINTS_AR);
        getResults(q, rec, "bp", NUM_POINTS_BP);
        getResults(q, rec, "br", NUM_POINTS_BR);
        TrailsRecords.push_back(rec);
    }
    q.close();
}
        // for (int i = 0; i < rec.ntests && i < NUM_POINTS_TOTAL; i++) {
        //     TrailsAnswer ans;
        //     char fieldname[16];
        //     sprintf(fieldname, "duration%d", i+1);  ans.duration = q.result.getInt(fieldname);
        //     sprintf(fieldname, "puzzle%d", i+1);    ans.puzzle = q.result.getInt(fieldname);
        //     sprintf(fieldname, "elapsed%d", i+1);   ans.elapsed = q.result.getInt(fieldname);
        //     sprintf(fieldname, "answer%d", i+1);    ans.answer = q.result.getInt(fieldname);
        //     sprintf(fieldname, "correct%d", i+1);   ans.correct = q.result.getInt(fieldname);
        //     rec.answers.push_back(ans);
        // }

void Trails::getResults(XQUERY & q, TrailsRecord & rec, const char * section, int numFields) {
    char fieldname[16];
    for (int i = 0; i < rec.ntests && i < numFields; i++) {
        TrailsAnswer ans;
        //sprintf(fieldname, "puzzle%d", i+1);    ans.puzzle = q.result.getInt(fieldname);
        sprintf(fieldname, "%s_%d_wrong", section, i+1);     ans.wrongClicks = q.result.getInt(fieldname);
        sprintf(fieldname, "%s_%d_time", section, i+1);      ans.duration = q.result.getInt(fieldname);
        sprintf(fieldname, "%s_%d_total", section, i+1);     ans.elapsed = q.result.getInt(fieldname);
        rec.answers.push_back(ans);
    }
}

void Trails::printRecords() {
    printf("<code>\n");
    printf("<h3>%d results:</h3>\n", TrailsRecords.size());
    printf("<table border=\"1\" cellspacing=\"0\">\n");
    printf("<thead><td>sesh_id</td><td>tinstruct</td><td>tstart</td><td>tfinish</td>\n"); // column headers
    printf("<td>responses</td><td>ntests</td>");
    for (int i = 1; i <= NUM_POINTS_TOTAL; i++) {
        printf("<td>wrong_%d</td><td>time_%d</td><td>total_%d</td>", i, i, i);
    }
    printf("</thead>\n");
    for (vecTrailsRecord::const_iterator rec = TrailsRecords.begin(); rec != TrailsRecords.end(); rec++) { // records
        printRecord(*rec);
    }
    printf("</table>\n");
    printf("</code>");
}

void Trails::printRecord(Trails::TrailsRecord rec) {
    printf("<tr>");
    printf("<td>%d</td><td>%s</td><td>%s</td><td>%s</td>",
        rec.sesh_id, rec.tinstruct.iso().c_str(), rec.tstart.iso().c_str(), rec.tfinish.iso().c_str());
    printf("<td>%s</td>", rec.responses.c_str());
    //printf("<td>...</td>");
    printf("<td>%d</td>", rec.ntests);
    // for (int i=0; i<rec.answers.size(); i++) { // safer, should agree with rec->ntests
    for (int i=0; i<rec.ntests; i++) { // safer, should agree with rec->ntests
        printf("<td>%d</td><td>%d</td><td>%d</td>",
            rec.answers[i].wrongClicks, rec.answers[i].duration, rec.answers[i].elapsed);
    }
    // for (int i = rec.answers.size()+1; i <= NUM_POINTS_TOTAL; i++) { // fill remainder
    for (int i = rec.ntests+1; i <= NUM_POINTS_TOTAL; i++) { // fill remainder
        printf("<td>[%d]</td><td>-</td><td>-</td>", i);
    }
    printf("</tr>\n");
}

// void Trails::testInsert() { // insert some dummy data
//     TrailsRecord rec;
//     rec.sesh_id = -1;//x->param.getIntDefault("sesh_id", -1);
//     rec.ntests = -1; //x->param.getIntDefault("ntests", -1);
//     rec.tinstruct.set("2000-01-01T00:00:00"); //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
//     rec.tstart.set("2000-01-01T00:00:00");
//     rec.tfinish.set("2000-01-01T00:00:00");
//     rec.responses = "[{\"puzzle\":\"t3w2by1.png\",\"answer\":\"4\",\"correct\":false,\"time\":761},{\"puzzle\":\"t3yw2b1.png\",\"answer\":\"4\",\"correct\":false,\"time\":628},{\"puzzle\":\"t32by1w.png\",\"answer\":\"4\",\"correct\":false,\"time\":3380},{\"puzzle\":\"t3bw21y.png\",\"answer\":\"4\",\"correct\":false,\"time\":509},{\"puzzle\":\"t3y2wb1.png\",\"answer\":\"4\",\"correct\":true,\"time\":320},{\"puzzle\":\"t3w2b1y.png\",\"answer\":\"4\",\"correct\":false,\"time\":401},{\"puzzle\":\"t3y2b1w.png\",\"answer\":\"4\",\"correct\":false,\"time\":384},{\"puzzle\":\"t3yw21b.png\",\"answer\":\"4\",\"correct\":false,\"time\":369},{\"puzzle\":\"t32wy1b.png\",\"answer\":\"4\",\"correct\":false,\"time\":354},{\"puzzle\":\"t3w2yb1.png\",\"answer\":\"4\",\"correct\":false,\"time\":369},{\"puzzle\":\"t3w2y1b.png\",\"answer\":\"4\",\"correct\":false,\"time\":333},{\"puzzle\":\"t3wy2b1.png\",\"answer\":\"4\",\"correct\":false,\"time\":394},{\"puzzle\":\"t3wb2y1.png\",\"answer\":\"4\",\"correct\":true,\"time\":364},{\"puzzle\":\"t32yb1w.png\",\"answer\":\"4\",\"correct\":true,\"time\":385},{\"puzzle\":\"t3ywb21.png\",\"answer\":\"4\",\"correct\":false,\"time\":358},{\"puzzle\":\"t3yb21w.png\",\"answer\":\"4\",\"correct\":true,\"time\":452},{\"puzzle\":\"t3ybw21.png\",\"answer\":\"4\",\"correct\":false,\"time\":376},{\"puzzle\":\"t3wyb21.png\",\"answer\":\"4\",\"correct\":false,\"time\":384}]";
//     for (int i=0; i<MAX_LEVELS; i++) { // fill remainder
//         TrailsAnswer ans;
//         ans.puzzle = "";
//         ans.wrongClicks = -1;
//         ans.duration = -1;
//         ans.elapsed = -1;
//         rec.answers.push_back(ans);
//     }
//     if (Trails::insertRecord(&rec)) {
//         printf("<p>Dummy data inserted.</p>\n");
//     } else {
//         printf("<p>Not inserted!</p>\n");
//     }
// }

    //printf("<code>there are %d params</code>", np);
    //printf("<p>sesh_id (string param): '%s'</p>", x->param.getStringDefault("sesh_id", "(default)").c_str()); // should be getInt? no, use getString and convert
    //rec.sesh_id = atoi(x->param.getString("sesh_id").c_str());
    //printf("<p>sesh_id (rec.sesh_id = atoi(getString(\"sesh_id\"))): %d</p>", rec.sesh_id);

    //printf("<p>sesh_id: '%d'</p>", rec.sesh_id);
/*
    printf("about to get int");
    try {
        rec.sesh_id = x->param.getInt("sesh_id"); // seems to crash it
    } catch (std::string e) {
        printf("caught exception: '%s'", e.c_str());
        // terminate called after throwing an instance of std::string
    }*/


    //rec.tinsert.set(""); // set in SQL - shouldn't be in struct
//     rec.tstart.set(x->param.getString("tstart").c_str());
//     rec.tfinish.set(x->param.getString("tfinish").c_str());
//     rec.tinsert.set(x->param.getString("tinsert").c_str());

    //printf("<p>nowString().c_str(): '%s'</p>", nowString().c_str()); // bad format for XTIME::set()
    //rec.tinstruct.set("2016-08-15T16:30:00"); // nowString().c_str()); //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
