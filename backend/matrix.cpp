#include <stdlib.h>
#include <cstring>
#include "xquery.h"
#include "xexec.h"
#include "matrix.h"
#include "bbquiz.h"
#include "nxjson.h"

const bool DEBUG = true;
#define IFDEBUG if (DEBUG)

Matrix::vecRecord MatrixRecords;

void Matrix::printJSONAnswer(const nx_json* node) {
    printf("[node type: %s, length: %d]: count: %d, puzzle: %d, answer: %d, correct: %d, time: %d<br />",
        //nx_json_type_names[node->type],
        "[nx_json_type_names not implemented here]",
        node->length,
        nx_json_get(node, "count")->int_value,
        nx_json_get(node, "puzzle")->int_value,
        nx_json_get(node, "answer")->int_value,
        nx_json_get(node, "correct")->int_value,
        nx_json_get(node, "time")->int_value);
}

void Matrix::printAnswer(MatrixAnswer & ans) {
    printf("ans: duration: %d, elapsed: %d, answer: %d, correct: %d<br />\n",
            ans.duration, ans.elapsed, ans.answer, ans.correct);
}

void Matrix::parseResponses(MatrixRecord *rec) {
    IFDEBUG printf("<code>parseResponses():");
    try {
        char * buf = new char[rec->responses.length() + 1];
        strcpy(buf, rec->responses.c_str()); // nxson modifies string in place, don't destroy original responses
        const nx_json* arr = nx_json_parse(buf, 0);
        if (!arr) {
            printf("didn't get json<br />"); throw "Error parsing JSON";
        }
        //printf("got json node type: %s, arr->length: %d<br />", nx_json_type_names[arr->type], arr->length);
        IFDEBUG printf("ntests reported by payload: %d; number of tests in responses JSON blob: %d<br />", rec->ntests, arr->length);
        if (rec->ntests != arr->length) {
            const char * errmsg = "<p>ERROR: rec->ntests != arr->length</p>";
            printf("%s", errmsg); throw errmsg;
        }
        for (int i=0; i < arr->length; i++) {
            const nx_json* item = nx_json_item(arr, i);
            MatrixAnswer ans;
            ans.duration    = nx_json_get(item, "duration"  )->int_value / 10; // Time taken to answer puzzle
            if (ans.duration > SMALLINT_MAX) ans.duration = -2; // cap SMALLINT/INTEGER2 (-32768 to 32767) and save "overflow" value
            ans.elapsed     = nx_json_get(item, "elapsed"   )->int_value / 10; // Cumulative time elapsed since start of test, in deciseconds
            if (ans.elapsed > SMALLINT_MAX) ans.elapsed = -2;
            ans.answer      = nx_json_get(item, "answer"    )->int_value; // Answer given by user
            ans.correct     = nx_json_get(item, "correct"   )->int_value; // Correct answer
            rec->answers.push_back(ans);
        }
        nx_json_free(arr);
    } catch(...) {
        printf("Error parsing JSON");
    }
    printf("</code>\n");
}
            //ans.puzzle      = nx_json_get(item, "puzzle"    )->int_value; // Puzzle chosen by algorithm, as number
            //printf("%d ", nx_json_get(item, "count")->int_value);
            //printf("elapsed: %d<br />", nx_json_get(item, "elapsed")->int_value);
            //printJSONAnswer(item);
            //printHoopsAnswer(ans);

Matrix::MatrixRecord Matrix::getPayload(XCGI * x) { // get responses from frontend
    IFDEBUG printf("<code>this is getPayload() in %s.<br />\n", __FILE__); //int np = x->param.count();
    MatrixRecord rec;
    rec.sesh_id = x->getParamAsInt("sesh_id"); // up to date xcgi.cpp/h has getParam, paramExists, but not this copy
    if (0 == rec.sesh_id) { // something went wrong, e.g. didn't get form data
        throw "Form data error";
    }
    rec.tinstruct.set(x->param.getString("tinstruct").c_str()); //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
    rec.tstart.set(x->param.getString("tstart").c_str()); //nowString().c_str());
    rec.tfinish.set(x->param.getString("tfinish").c_str());
    //printf("<p>tinstruct.iso(): '%s', tstart.iso(): '%s', tfinish.iso(): '%s'</p>", rec.tinstruct.iso().c_str(), rec.tstart.iso().c_str(), rec.tfinish.iso().c_str());
    rec.responses = x->param.getString("responses");
    IFDEBUG printf("<p>responses:</p><pre>%s</pre>\n", rec.responses.c_str());
    rec.ntests = x->getParamAsInt("ntests");
    parseResponses(&rec); // rec.ntests can be determined from responses? or should be passed from frontend and checked
    IFDEBUG printf("sesh_id: %d", rec.sesh_id);
    IFDEBUG printf("<p>done</p>\n");
    return rec;
}
void Matrix::testInsert() {
    printf("Todo");
}

bool Matrix::insertRecord(const MatrixRecord *rec) {
    IFDEBUG printf("<p><code>Matrix::insertRecord()</p>\n");
    std::string sql =
        "INSERT INTO matrix (sesh_id, tinstruct, tstart, tfinish, tinsert, "
        " ntests,responses, "
        " duration1, elapsed1, answer1, correct1, "
        " duration2, elapsed2, answer2, correct2, "
        " duration3, elapsed3, answer3, correct3, "
        " duration4, elapsed4, answer4, correct4, "
        " duration5, elapsed5, answer5, correct5, "
        " duration6, elapsed6, answer6, correct6, "
        " duration7, elapsed7, answer7, correct7, "
        " duration8, elapsed8, answer8, correct8, "
        " duration9, elapsed9, answer9, correct9, "
        " duration10, elapsed10, answer10, correct10, "
        " duration11, elapsed11, answer11, correct11, "
        " duration12, elapsed12, answer12, correct12, "
        " duration13, elapsed13, answer13, correct13, "
        " duration14, elapsed14, answer14, correct14, "
        " duration15, elapsed15, answer15, correct15 "
        " )"
        " VALUES (:sesh_id, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :ntests, :responses, "
        " :duration1, :elapsed1, :answer1, :correct1, "
        " :duration2, :elapsed2, :answer2, :correct2, "
        " :duration3, :elapsed3, :answer3, :correct3, "
        " :duration4, :elapsed4, :answer4, :correct4, "
        " :duration5, :elapsed5, :answer5, :correct5, "
        " :duration6, :elapsed6, :answer6, :correct6, "
        " :duration7, :elapsed7, :answer7, :correct7, "
        " :duration8, :elapsed8, :answer8, :correct8, "
        " :duration9, :elapsed9, :answer9, :correct9, "
        " :duration10, :elapsed10, :answer10, :correct10, "
        " :duration11, :elapsed11, :answer11, :correct11, "
        " :duration12, :elapsed12, :answer12, :correct12, "
        " :duration13, :elapsed13, :answer13, :correct13, "
        " :duration14, :elapsed14, :answer14, :correct14, "
        " :duration15, :elapsed15, :answer15, :correct15 "
        " )";

    XEXEC xe(db, sql);

    xe.param.setInt("sesh_id",       rec->sesh_id);
    xe.param.setTime("tinstruct",    rec->tinstruct);
    xe.param.setTime("tstart",       rec->tstart);
    xe.param.setTime("tfinish",      rec->tfinish);
    xe.param.setInt("ntests",        rec->ntests);
    xe.param.setString("responses",  rec->responses);
    //IFDEBUG printf("added header fields...<br />\n");
    //printf("tinstruct: '%s', tstart: '%s', tfinish: '%s'...", rec->tinstruct.iso().c_str(), rec->tstart.iso().c_str(), rec->tfinish.iso().c_str());
    char fieldname[12];

    // insert answered puzzles
    for (int i=0; i<rec->answers.size(); i++) { // safer, should agree with rec->ntests
        //printf("answer %d/%d<br />", i+1, rec->answers.size());
        printf("%d ", i+1);
        sprintf(fieldname, "duration%d", i+1);  xe.param.setInt(fieldname,  rec->answers[i].duration); //printf("field: '%s', value: %d<br />\n", fieldname,  rec->answers[i].duration);
        sprintf(fieldname, "elapsed%d", i+1);   xe.param.setInt(fieldname,  rec->answers[i].elapsed);
        sprintf(fieldname, "answer%d", i+1);    xe.param.setInt(fieldname,  rec->answers[i].answer);
        sprintf(fieldname, "correct%d", i+1);   xe.param.setInt(fieldname,  rec->answers[i].correct);
    }
    IFDEBUG printf("added %d answered puzzles...<br />\n", rec->answers.size());

    // insert 'nulls' (-1) for the rest explicitly, otherwise fields have to have defaults
    for (int i = rec->answers.size()+1; i <= MAX_LEVELS; i++) {
        sprintf(fieldname, "duration%d", i);    xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
        sprintf(fieldname, "puzzle%d", i);      xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
        sprintf(fieldname, "elapsed%d", i);     xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
        sprintf(fieldname, "answer%d", i);      xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
        sprintf(fieldname, "correct%d", i);     xe.param.setInt(fieldname,  -1); //printf("field: '%s', value: %d<br />\n", fieldname, 0);
    }
    IFDEBUG printf("added %d null records...\n", MAX_LEVELS - rec->answers.size());
    //printf("<p>sql:</p><code>%s</code> ", sql.c_str());
    IFDEBUG printf("</p></code>\n");
    return (xe.exec());
}

void Matrix::getRecords() {
    std::string sql = "SELECT * FROM matrix";
    XQUERY q(db, sql);
    IFDEBUG printf("<p>this is %s</p>\n", __FILE__);
    if (!q.open()) {
        printf("Database error");
        throw "Database error";
    } else {
        IFDEBUG printf("Database open");
    }
    while (q.fetch()) {
        MatrixRecord rec;
        rec.sesh_id   = q.result.getInt("sesh_id");
        rec.tinstruct = q.result.getTime("tinstruct");      // getDate?
        rec.tstart    = q.result.getTime("tstart");
        rec.tfinish   = q.result.getTime("tfinish");
        rec.responses = q.result.getString("responses");    // JSON blob
        rec.ntests    = q.result.getInt("ntests");          // is ntests sane?
        for (int i = 0; i < rec.ntests && i < MAX_LEVELS; i++) {
            MatrixAnswer ans;
            char fieldname[16];
            sprintf(fieldname, "duration%d", i+1);  ans.duration = q.result.getInt(fieldname);
            sprintf(fieldname, "elapsed%d", i+1);   ans.elapsed = q.result.getInt(fieldname);
            sprintf(fieldname, "answer%d", i+1);    ans.answer = q.result.getInt(fieldname);
            sprintf(fieldname, "correct%d", i+1);   ans.correct = q.result.getInt(fieldname);
            rec.answers.push_back(ans);
        }
        MatrixRecords.push_back(rec);
    }
    q.close();
}

void Matrix::printRecords() {
    printf("<code>\n");
    printf("<h3>%d results:</h3>\n", MatrixRecords.size());
    printf("<table border=\"1\" cellspacing=\"0\">\n");

    // column headers
    printf("<thead><td>sesh_id</td><td>tinstruct</td><td>tstart</td><td>tfinish</td>\n");
    printf("<td>responses</td><td>ntests</td>");
    for (int i = 1; i <= MAX_LEVELS; i++) {
        printf("<td>duration%d</td><td>elapsed%d</td><td>answer%d</td><td>correct%d</td>", i, i, i, i, i);
    }
    printf("</thead>\n");

    // values
    for (vecRecord::const_iterator rec = MatrixRecords.begin(); rec != MatrixRecords.end(); rec++) { // records
        printRecord(*rec);
    }
    printf("</table>\n");
    printf("</code>");
}

void Matrix::printRecord(Matrix::MatrixRecord rec) {
    printf("<tr>");
    printf("<td>%d</td><td>%s</td><td>%s</td><td>%s</td>",
        rec.sesh_id, rec.tinstruct.iso().c_str(), rec.tstart.iso().c_str(), rec.tfinish.iso().c_str());
    printf("<td>%s</td>", rec.responses.c_str());
    //printf("<td>...</td>");
    printf("<td>%d</td>", rec.ntests);
    for (int i = 0; i < rec.answers.size(); i++) { // safer, should agree with rec->ntests
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>",
            rec.answers[i].duration, rec.answers[i].elapsed,
            rec.answers[i].answer, rec.answers[i].correct);
    }
    for (int i = rec.answers.size() + 1; i <= MAX_LEVELS; i++) { // fill remainder
        printf("<td>[%d]</td><td>-</td><td>-</td><td>-</td>", i);
    }
    printf("</tr>\n");
}
