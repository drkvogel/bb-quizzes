#include "xquery.h"
#include "xexec.h"
#include "matrix.h"
#include "nxjson.h"

void Matrix::parseResponses(const MatrixRecord *e) {
    char buf[1600];
    strcpy(buf, e->responses.c_str());
    const nx_json* json = nx_json_parse(buf, 0);

    if (json) {
        const nx_json* arr = nx_json_get(json, "array");
    
        for (int i = 0; i < arr->length; i++) {
            const nx_json* item = nx_json_item(arr, i);
            printf("arr[%d]=(%d) %ld %lf %s\n", i, (int)item->type, item->int_value, item->dbl_value, item->text_value);
        }
        nx_json_free(json);
    } else {
        throw "Error parsing JSON";
    }
}

void Matrix::testInsert() {
    //
    printf("Todo");    
}

void Matrix::insert() {
    //
    printf("Todo");    
}

bool Matrix::insertRecord(const MatrixRecord *e) {
    std::string sql =
        "INSERT INTO matrix (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert,"
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
        " duration15, elapsed15, answer15, correct15, "
        " duration16, elapsed16, answer16, correct16, "
        " duration17, elapsed17, answer17, correct17, "
        " duration18, elapsed18, answer18, correct18 "
        " )"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
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
        " :duration15, :elapsed15, :answer15, :correct15, "
        " :duration16, :elapsed16, :answer16, :correct16, "
        " :duration17, :elapsed17, :answer17, :correct17, "
        " :duration18, :elapsed18, :answer18, :correct18 "
        " )";

    XEXEC xe(db, sql);

    xe.param.setInt("sesh_id",       e->sesh_id);
    xe.param.setInt("ntests",        e->ntests);
    xe.param.setTime("tinstruct",    e->tinstruct);
    xe.param.setTime("tstart",       e->tstart);
    xe.param.setTime("tfinish",      e->tfinish);

    xe.param.setInt("duration1",     e->duration1);
    xe.param.setInt("elapsed1",      e->elapsed1);
    xe.param.setInt("answer1",       e->answer1);
    xe.param.setInt("correct1",      e->correct1);

    xe.param.setInt("duration2",     e->duration2);
    xe.param.setInt("elapsed2",      e->elapsed2);
    xe.param.setInt("answer2",       e->answer2);
    xe.param.setInt("correct2",      e->correct2);

    xe.param.setInt("duration3",     e->duration3);
    xe.param.setInt("elapsed3",      e->elapsed3);
    xe.param.setInt("answer3",       e->answer3);
    xe.param.setInt("correct3",      e->correct3);

    xe.param.setInt("duration4",     e->duration4);
    xe.param.setInt("elapsed4",      e->elapsed4);
    xe.param.setInt("answer4",       e->answer4);
    xe.param.setInt("correct4",      e->correct4);

    xe.param.setInt("duration5",     e->duration5);
    xe.param.setInt("elapsed5",      e->elapsed5);
    xe.param.setInt("answer5",       e->answer5);
    xe.param.setInt("correct5",      e->correct5);

    xe.param.setInt("duration6",     e->duration6);
    xe.param.setInt("elapsed6",      e->elapsed6);
    xe.param.setInt("answer6",       e->answer6);
    xe.param.setInt("correct6",      e->correct6);

    xe.param.setInt("duration7",     e->duration7);
    xe.param.setInt("elapsed7",      e->elapsed7);
    xe.param.setInt("answer7",       e->answer7);
    xe.param.setInt("correct7",      e->correct7);

    xe.param.setInt("duration8",     e->duration8);
    xe.param.setInt("elapsed8",      e->elapsed8);
    xe.param.setInt("answer8",       e->answer8);
    xe.param.setInt("correct8",      e->correct8);

    xe.param.setInt("duration9",     e->duration9);
    xe.param.setInt("elapsed9",      e->elapsed9);
    xe.param.setInt("answer9",       e->answer9);
    xe.param.setInt("correct9",      e->correct9);

    xe.param.setInt("duration10",     e->duration10);
    xe.param.setInt("elapsed10",      e->elapsed10);
    xe.param.setInt("answer10",       e->answer10);
    xe.param.setInt("correct10",      e->correct10);

    xe.param.setInt("duration11",     e->duration11);
    xe.param.setInt("elapsed11",      e->elapsed11);
    xe.param.setInt("answer11",       e->answer11);
    xe.param.setInt("correct11",      e->correct11);

    xe.param.setInt("duration12",     e->duration12);
    xe.param.setInt("elapsed12",      e->elapsed12);
    xe.param.setInt("answer12",       e->answer12);
    xe.param.setInt("correct12",      e->correct12);

    xe.param.setInt("duration13",     e->duration13);
    xe.param.setInt("elapsed13",      e->elapsed13);
    xe.param.setInt("answer13",       e->answer13);
    xe.param.setInt("correct13",      e->correct13);

    xe.param.setInt("duration14",     e->duration14);
    xe.param.setInt("elapsed14",      e->elapsed14);
    xe.param.setInt("answer14",       e->answer14);
    xe.param.setInt("correct14",      e->correct14);

    xe.param.setInt("duration15",     e->duration15);
    xe.param.setInt("elapsed15",      e->elapsed15);
    xe.param.setInt("answer15",       e->answer15);
    xe.param.setInt("correct15",      e->correct15);

    xe.param.setInt("duration16",     e->duration16);
    xe.param.setInt("elapsed16",      e->elapsed16);
    xe.param.setInt("answer16",       e->answer16);
    xe.param.setInt("correct16",      e->correct16);

    xe.param.setInt("duration17",     e->duration17);
    xe.param.setInt("elapsed17",      e->elapsed17);
    xe.param.setInt("answer17",       e->answer17);
    xe.param.setInt("correct17",      e->correct17);

    xe.param.setInt("duration18",     e->duration18);
    xe.param.setInt("elapsed18",      e->elapsed18);
    xe.param.setInt("answer18",       e->answer18);
    xe.param.setInt("correct18",      e->correct18);

    printf("<p>sql:</p>\n<p>%s</p>\n", sql.c_str());

    return (xe.exec());
}

void Matrix::getRecords() {
    vecMatrixRecord records;
    MatrixRecord rec;
    std::string sql = "SELECT * FROM matrix";
    XQUERY q(db, sql);
    printf("<p>this is %s</p>\n", __FILE__);
    if (!q.open()) {
        printf("Database error");
        throw "Database error";
    }
    //printf("<p>q.fetch():</p>\n");
    while (q.fetch()) {
        rec.sesh_id   = q.result.getInt("sesh_id");
        rec.ntests    = q.result.getInt("ntests");
        rec.tinstruct = q.result.getTime("tinstruct"); // getDate?
        rec.tstart    = q.result.getTime("tstart");
        rec.tfinish   = q.result.getTime("tstart");

        rec.duration1 = q.result.getInt("duration1");
        rec.elapsed1  = q.result.getInt("elapsed1");
        rec.answer1   = q.result.getInt("answer1");
        rec.correct1  = q.result.getInt("correct1");

        records.push_back(rec);
    }
    q.close();

    printf("<code>\n");
    printf("<h3>%d results:</h3>\n", records.size());
    printf("<table border=\"1\" cellspacing=\"0\">\n");

    // column headers
    printf("<thead><td>sesh_id</td><td>ntests</td><td>tinstruct</td><td>tstart</td><td>tfinish</td>");
    printf("<td>responses</td>");
    printf("<td>duration1</td><td>elapsed1</td><td>answer1</td><td>correct1</td>");
    printf("<td>duration2</td><td>elapsed2</td><td>answer2</td><td>correct2</td>");
    printf("<td>duration3</td><td>elapsed3</td><td>answer3</td><td>correct3</td>");
    printf("<td>duration4</td><td>elapsed4</td><td>answer4</td><td>correct4</td>");
    printf("<td>duration5</td><td>elapsed5</td><td>answer5</td><td>correct5</td>");
    printf("<td>duration6</td><td>elapsed6</td><td>answer6</td><td>correct6</td>");
    printf("<td>duration7</td><td>elapsed7</td><td>answer7</td><td>correct7</td>");
    printf("<td>duration8</td><td>elapsed8</td><td>answer8</td><td>correct8</td>");
    printf("<td>duration9</td><td>elapsed9</td><td>answer9</td><td>correct9</td>");
    printf("<td>duration10</td><td>elapsed10</td><td>answer10</td><td>correct10</td>");
    printf("<td>duration11</td><td>elapsed11</td><td>answer11</td><td>correct11</td>");
    printf("<td>duration12</td><td>elapsed12</td><td>answer12</td><td>correct12</td>");
    printf("<td>duration13</td><td>elapsed13</td><td>answer13</td><td>correct13</td>");
    printf("<td>duration14</td><td>elapsed14</td><td>answer14</td><td>correct14</td>");
    printf("<td>duration15</td><td>elapsed15</td><td>answer15</td><td>correct15</td>");
    printf("<td>duration16</td><td>elapsed16</td><td>answer16</td><td>correct16</td>");
    printf("<td>duration17</td><td>elapsed17</td><td>answer17</td><td>correct17</td>");
    printf("<td>duration18</td><td>elapsed18</td><td>answer18</td><td>correct18</td>");
    printf("</thead>\n");
    for (vecMatrixRecord::const_iterator it = records.begin(); it != records.end(); it++) {
        printf("<tr>");
        printf("<td>%d</td><td>%d</td><td>%s</td><td>%s</td><td>%s</td>", it->sesh_id, it->ntests, it->tinstruct.iso().c_str(), it->tstart.iso().c_str(), it->tfinish.iso().c_str());
        printf("<td>%s</td>", it->responses.c_str());
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration1, it->elapsed1, it->answer1, it->correct1);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration2, it->elapsed2, it->answer2, it->correct2);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration3, it->elapsed3, it->answer3, it->correct3);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration4, it->elapsed4, it->answer4, it->correct4);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration5, it->elapsed5, it->answer5, it->correct5);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration6, it->elapsed6, it->answer6, it->correct6);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration7, it->elapsed7, it->answer7, it->correct7);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration8, it->elapsed8, it->answer8, it->correct8);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration9, it->elapsed9, it->answer9, it->correct9);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration10, it->elapsed10, it->answer10, it->correct10);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration11, it->elapsed11, it->answer11, it->correct11);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration12, it->elapsed12, it->answer12, it->correct12);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration13, it->elapsed13, it->answer13, it->correct13);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration14, it->elapsed14, it->answer14, it->correct14);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration15, it->elapsed15, it->answer15, it->correct15);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration16, it->elapsed16, it->answer16, it->correct16);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration17, it->elapsed17, it->answer17, it->correct17);
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration18, it->elapsed18, it->answer18, it->correct18);
        printf("</tr>\n");
    }
    printf("</table>\n");
    printf("</code>\n");
}
