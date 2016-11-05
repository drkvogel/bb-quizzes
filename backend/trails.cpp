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
    printf("ans: duration: %d, puzzle: %d, elapsed: %d, answer: %d, correct: %d<br />\n",
            ans.duration, ans.puzzle, ans.elapsed, ans.answer, ans.correct);
}

void Trails::parseResponses(TrailsRecord *rec) {
    IFDEBUG printf("<code>parseResponses():");
    try {
        char * buf = new char[rec->responses.length() + 1];
        strcpy(buf, rec->responses.c_str()); // nxson modifies string in place, don't destroy original responses
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
        for (int i=0; i < arr->length; i++) {
            const nx_json* item = nx_json_item(arr, i);
            TrailsAnswer ans;
            ans.puzzle      = nx_json_get(item, "puzzle"    )->int_value; // Puzzle chosen by algorithm, as number
            ans.duration    = nx_json_get(item, "duration"  )->int_value / 10; // Time taken to answer puzzle
            if (ans.duration > SMALLINT_MAX) ans.duration = -2;
            ans.elapsed     = nx_json_get(item, "elapsed"   )->int_value / 10; // Cumulative time elapsed since start of test, in deciseconds
            if (ans.elapsed > SMALLINT_MAX) ans.elapsed = -2;
            ans.answer      = nx_json_get(item, "answer"    )->int_value; // Answer given by user
            ans.correct     = nx_json_get(item, "correct"   )->int_value; // Correct answer
            //printf("%d ", nx_json_get(item, "count")->int_value);
            //printf("elapsed: %d<br />", nx_json_get(item, "elapsed")->int_value);
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

bool Trails::insertRecord(const TrailsRecord *rec) {
    IFDEBUG printf("<p><code>Trails::insertRecord()</p>\n");
    std::string sql =
        "INSERT INTO Trails (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert,"
        " responses"
        //" duration18, puzzle18, elapsed18, answer18, correct18 "
        " )\n"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :responses"
        //" :duration1, :puzzle1, :elapsed1, :answer1, :correct1 "
        " )\n";
    XEXEC xe(db, sql); IFDEBUG printf("made XEXEC object...\n");

    xe.param.setInt("sesh_id",       rec->sesh_id);
    xe.param.setTime("tinstruct",    rec->tinstruct);
    xe.param.setTime("tstart",       rec->tstart);
    xe.param.setTime("tfinish",      rec->tfinish);
    xe.param.setInt("ntests",        rec->ntests);
    xe.param.setString("responses",  rec->responses);
    IFDEBUG printf("added header fields...<br />\n"); //printf("tinstruct: '%s', tstart: '%s', tfinish: '%s'...", rec->tinstruct.iso().c_str(), rec->tstart.iso().c_str(), rec->tfinish.iso().c_str());

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
    // IFDEBUG printf("</code>\n"); //IFDEBUG printf("<p>sql:</p><code>%s</code> ", sql.c_str());
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
        // for (int i = 0; i < rec.ntests && i < MAX_LEVELS; i++) {
        //     TrailsAnswer ans;
        //     char fieldname[16];
        //     sprintf(fieldname, "duration%d", i+1);  ans.duration = q.result.getInt(fieldname);
        //     sprintf(fieldname, "puzzle%d", i+1);    ans.puzzle = q.result.getInt(fieldname);
        //     sprintf(fieldname, "elapsed%d", i+1);   ans.elapsed = q.result.getInt(fieldname);
        //     sprintf(fieldname, "answer%d", i+1);    ans.answer = q.result.getInt(fieldname);
        //     sprintf(fieldname, "correct%d", i+1);   ans.correct = q.result.getInt(fieldname);
        //     rec.answers.push_back(ans);
        // }
        TrailsRecords.push_back(rec);
    }
    q.close();
}

void Trails::printRecords() {
    printf("<code>\n");
    printf("<h3>%d results:</h3>\n", TrailsRecords.size());
    printf("<table border=\"1\" cellspacing=\"0\">\n");
    printf("<thead><td>sesh_id</td><td>tinstruct</td><td>tstart</td><td>tfinish</td>\n"); // column headers
    printf("<td>responses</td><td>ntests</td>");
    // for (int i = 1; i <= MAX_LEVELS; i++) {
    //     printf("<td>duration%d</td><td>puzzle%d</td><td>elapsed%d</td><td>answer%d</td><td>correct%d</td>", i, i, i, i, i);
    // }
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
    //     printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>",
    //         rec.answers[i].duration, rec.answers[i].puzzle, rec.answers[i].elapsed,
    //         rec.answers[i].answer, rec.answers[i].correct);
    // }
    // for (int i = rec.answers.size()+1; i <= MAX_LEVELS; i++) { // fill remainder
    //     printf("<td>[%d]</td><td>-</td><td>-</td><td>-</td><td>-</td>", i);
    // }
    printf("</tr>\n");
}

void Trails::testInsert() { // insert some dummy data
    TrailsRecord rec;
    rec.sesh_id = -1;//x->param.getIntDefault("sesh_id", -1);
    rec.ntests = -1; //x->param.getIntDefault("ntests", -1);
    rec.tinstruct.set("2000-01-01T00:00:00"); //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
    rec.tstart.set("2000-01-01T00:00:00");
    rec.tfinish.set("2000-01-01T00:00:00");
    rec.responses = "[{\"puzzle\":\"t3w2by1.png\",\"answer\":\"4\",\"correct\":false,\"time\":761},{\"puzzle\":\"t3yw2b1.png\",\"answer\":\"4\",\"correct\":false,\"time\":628},{\"puzzle\":\"t32by1w.png\",\"answer\":\"4\",\"correct\":false,\"time\":3380},{\"puzzle\":\"t3bw21y.png\",\"answer\":\"4\",\"correct\":false,\"time\":509},{\"puzzle\":\"t3y2wb1.png\",\"answer\":\"4\",\"correct\":true,\"time\":320},{\"puzzle\":\"t3w2b1y.png\",\"answer\":\"4\",\"correct\":false,\"time\":401},{\"puzzle\":\"t3y2b1w.png\",\"answer\":\"4\",\"correct\":false,\"time\":384},{\"puzzle\":\"t3yw21b.png\",\"answer\":\"4\",\"correct\":false,\"time\":369},{\"puzzle\":\"t32wy1b.png\",\"answer\":\"4\",\"correct\":false,\"time\":354},{\"puzzle\":\"t3w2yb1.png\",\"answer\":\"4\",\"correct\":false,\"time\":369},{\"puzzle\":\"t3w2y1b.png\",\"answer\":\"4\",\"correct\":false,\"time\":333},{\"puzzle\":\"t3wy2b1.png\",\"answer\":\"4\",\"correct\":false,\"time\":394},{\"puzzle\":\"t3wb2y1.png\",\"answer\":\"4\",\"correct\":true,\"time\":364},{\"puzzle\":\"t32yb1w.png\",\"answer\":\"4\",\"correct\":true,\"time\":385},{\"puzzle\":\"t3ywb21.png\",\"answer\":\"4\",\"correct\":false,\"time\":358},{\"puzzle\":\"t3yb21w.png\",\"answer\":\"4\",\"correct\":true,\"time\":452},{\"puzzle\":\"t3ybw21.png\",\"answer\":\"4\",\"correct\":false,\"time\":376},{\"puzzle\":\"t3wyb21.png\",\"answer\":\"4\",\"correct\":false,\"time\":384}]";
    for (int i=0; i<MAX_LEVELS; i++) { // fill remainder
        TrailsAnswer ans;
        ans.duration = -1;
        ans.puzzle = -1;
        ans.elapsed = -1;
        ans.answer = -1;
        ans.correct = -1;
        rec.answers.push_back(ans);
    }
    if (Trails::insertRecord(&rec)) {
        printf("<p>Dummy data inserted.</p>\n");
    } else {
        printf("<p>Not inserted!</p>\n");
    }
}

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
