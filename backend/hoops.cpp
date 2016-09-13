#include "xquery.h"
#include "xexec.h"
#include "hoops.h"
#include "nxjson.h"


void Hoops::parseResponses(const HoopsRecord *e) {
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

void Hoops::insert(XCGI * x) { // real insert by frontend
    HoopsRecord rec;
    int np = x->param.count();
    printf("there are %s params", np);
    rec.sesh_id = -1;//x->param.getIntDefault("sesh_id", -1);
    rec.ntests = -1; //x->param.getIntDefault("ntests", -1);
    rec.tinstruct = ""; //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
    rec.tstart = "";
    rec.tfinish = "";
    rec.tinsert = "";
    rec.responses = "";
}

void Hoops::testInsert() { // insert some dummy data
    HoopsRecord rec;
    rec.sesh_id = -1;//x->param.getIntDefault("sesh_id", -1);
    rec.ntests = -1; //x->param.getIntDefault("ntests", -1);
    rec.tinstruct = "2016-08-15 16:30"; //x->param.getTime("tinstruct"); // "2016-08-15 16:30";
    rec.tstart = "";
    rec.tfinish = "";
    rec.tinsert = "";
    rec.responses = "[{\"puzzle\":\"t3w2by1.png\",\"answer\":\"4\",\"correct\":false,\"time\":761},{\"puzzle\":\"t3yw2b1.png\",\"answer\":\"4\",\"correct\":false,\"time\":628},{\"puzzle\":\"t32by1w.png\",\"answer\":\"4\",\"correct\":false,\"time\":3380},{\"puzzle\":\"t3bw21y.png\",\"answer\":\"4\",\"correct\":false,\"time\":509},{\"puzzle\":\"t3y2wb1.png\",\"answer\":\"4\",\"correct\":true,\"time\":320},{\"puzzle\":\"t3w2b1y.png\",\"answer\":\"4\",\"correct\":false,\"time\":401},{\"puzzle\":\"t3y2b1w.png\",\"answer\":\"4\",\"correct\":false,\"time\":384},{\"puzzle\":\"t3yw21b.png\",\"answer\":\"4\",\"correct\":false,\"time\":369},{\"puzzle\":\"t32wy1b.png\",\"answer\":\"4\",\"correct\":false,\"time\":354},{\"puzzle\":\"t3w2yb1.png\",\"answer\":\"4\",\"correct\":false,\"time\":369},{\"puzzle\":\"t3w2y1b.png\",\"answer\":\"4\",\"correct\":false,\"time\":333},{\"puzzle\":\"t3wy2b1.png\",\"answer\":\"4\",\"correct\":false,\"time\":394},{\"puzzle\":\"t3wb2y1.png\",\"answer\":\"4\",\"correct\":true,\"time\":364},{\"puzzle\":\"t32yb1w.png\",\"answer\":\"4\",\"correct\":true,\"time\":385},{\"puzzle\":\"t3ywb21.png\",\"answer\":\"4\",\"correct\":false,\"time\":358},{\"puzzle\":\"t3yb21w.png\",\"answer\":\"4\",\"correct\":true,\"time\":452},{\"puzzle\":\"t3ybw21.png\",\"answer\":\"4\",\"correct\":false,\"time\":376},{\"puzzle\":\"t3wyb21.png\",\"answer\":\"4\",\"correct\":false,\"time\":384}]";

// rec.duration1 = "";
// rec.puzzle1 = -1;
// rec.elapsed1 = -1;
// rec.answer1 = -1;
// rec.correct1 = -1;
//
// rec.duration2 = -1;
// rec.puzzle1 = -1;
// rec.elapsed1 = -1;
// rec.answer1 = -1;
// rec.correct1 = -1;

    if (Hoops::insertRecord(&rec)) {
        printf("<p>Data inserted.</p>\n");
    } else {
        printf("<p>Not inserted!</p>\n");
    }
}

bool Hoops::insertRecord(const HoopsRecord *e) {

    std::string sql =
        "INSERT INTO hoops (sesh_id, ntests, tinstruct, tstart, tfinish, tinsert,"
        " duration1, puzzle1, elapsed1, answer1, correct1, "
        " duration2, puzzle2, elapsed2, answer2, correct2, "
        " duration3, puzzle3, elapsed3, answer3, correct3, "
        " duration4, puzzle4, elapsed4, answer4, correct4, "
        " duration5, puzzle5, elapsed5, answer5, correct5, "
        " duration6, puzzle6, elapsed6, answer6, correct6, "
        " duration7, puzzle7, elapsed7, answer7, correct7, "
        " duration8, puzzle8, elapsed8, answer8, correct8, "
        " duration9, puzzle9, elapsed9, answer9, correct9, "
        " duration10, puzzle10, elapsed10, answer10, correct10, "
        " duration11, puzzle11, elapsed11, answer11, correct11, "
        " duration12, puzzle12, elapsed12, answer12, correct12, "
        " duration13, puzzle13, elapsed13, answer13, correct13, "
        " duration14, puzzle14, elapsed14, answer14, correct14, "
        " duration15, puzzle15, elapsed15, answer15, correct15, "
        " duration16, puzzle16, elapsed16, answer16, correct16, "
        " duration17, puzzle17, elapsed17, answer17, correct17, "
        " duration18, puzzle18, elapsed18, answer18, correct18 "
        " )\n"
        " VALUES (:sesh_id, :ntests, :tinstruct, :tstart, :tfinish, DATE('now'), "
        " :duration1, :puzzle1, :elapsed1, :answer1, :correct1, "
        " :duration2, :puzzle2, :elapsed2, :answer2, :correct2, "
        " :duration3, :puzzle3, :elapsed3, :answer3, :correct3, "
        " :duration4, :puzzle4, :elapsed4, :answer4, :correct4, "
        " :duration5, :puzzle5, :elapsed5, :answer5, :correct5, "
        " :duration6, :puzzle6, :elapsed6, :answer6, :correct6, "
        " :duration7, :puzzle7, :elapsed7, :answer7, :correct7, "
        " :duration8, :puzzle8, :elapsed8, :answer8, :correct8, "
        " :duration9, :puzzle9, :elapsed9, :answer9, :correct9, "
        " :duration10, :puzzle10, :elapsed10, :answer10, :correct10, "
        " :duration11, :puzzle11, :elapsed11, :answer11, :correct11, "
        " :duration12, :puzzle12, :elapsed12, :answer12, :correct12, "
        " :duration13, :puzzle13, :elapsed13, :answer13, :correct13, "
        " :duration14, :puzzle14, :elapsed14, :answer14, :correct14, "
        " :duration15, :puzzle15, :elapsed15, :answer15, :correct15, "
        " :duration16, :puzzle16, :elapsed16, :answer16, :correct16, "
        " :duration17, :puzzle17, :elapsed17, :answer17, :correct17, "
        " :duration18, :puzzle18, :elapsed18, :answer18, :correct18 "
        " )\n";

    XEXEC xe(db, sql);

    xe.param.setInt("sesh_id",       e->sesh_id);
    xe.param.setInt("ntests",        e->ntests);
    xe.param.setTime("tinstruct",    e->tinstruct);
    xe.param.setTime("tstart",       e->tstart);
    xe.param.setTime("tfinish",      e->tfinish);

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

    printf("<p>sql:</p><code>%s</code> ", sql.c_str());

    return (xe.exec());
}

void Hoops::getRecords() {
    vecHoopsRecord records;
    HoopsRecord rec;
    std::string sql = "SELECT * FROM hoops";
    XQUERY q(db, sql);
    printf("<p>this is %s</p>\n", __FILE__);
    if (!q.open()) {
        printf("Database error");
        throw "Database error";
    } else {
        printf("Database open");
    }
    while (q.fetch()) {
        rec.sesh_id   = q.result.getInt("sesh_id");
        rec.ntests    = q.result.getInt("ntests");
        rec.tinstruct = q.result.getTime("tinstruct"); // getDate?
        rec.tstart    = q.result.getTime("tstart");
        rec.tfinish   = q.result.getTime("tstart");
        rec.responses = q.result.getString("responses"); // JSON blob
        records.push_back(rec);
    }
    q.close();

    printf("<code>\n");
    printf("<h3>%d results:</h3>\n", records.size());
    printf("<table border=\"1\" cellspacing=\"0\">\n");

    // these are just the column headers:
    printf("<thead><td>sesh_id</td><td>ntests</td><td>tinstruct</td><td>tstart</td><td>tfinish</td>\n");
    printf("<td>responses</td>");
    printf("<td>duration1</td><td>puzzle1</td><td>elapsed1</td><td>answer1</td><td>correct1</td>");
    printf("<td>duration2</td><td>puzzle2</td><td>elapsed2</td><td>answer2</td><td>correct2</td>");
    printf("<td>duration3</td><td>puzzle3</td><td>elapsed3</td><td>answer3</td><td>correct3</td>");
    printf("<td>duration4</td><td>puzzle4</td><td>elapsed4</td><td>answer4</td><td>correct4</td>");
    printf("<td>duration5</td><td>puzzle5</td><td>elapsed5</td><td>answer5</td><td>correct5</td>");
    printf("<td>duration6</td><td>puzzle6</td><td>elapsed6</td><td>answer6</td><td>correct6</td>");
    printf("<td>duration7</td><td>puzzle7</td><td>elapsed7</td><td>answer7</td><td>correct7</td>");
    printf("<td>duration8</td><td>puzzle8</td><td>elapsed8</td><td>answer8</td><td>correct8</td>");
    printf("<td>duration9</td><td>puzzle9</td><td>elapsed9</td><td>answer9</td><td>correct9</td>");
    printf("<td>duration10</td><td>puzzle10</td><td>elapsed10</td><td>answer10</td><td>correct10</td>");
    printf("<td>duration11</td><td>puzzle11</td><td>elapsed11</td><td>answer11</td><td>correct11</td>");
    printf("<td>duration12</td><td>puzzle12</td><td>elapsed12</td><td>answer12</td><td>correct12</td>");
    printf("<td>duration13</td><td>puzzle13</td><td>elapsed13</td><td>answer13</td><td>correct13</td>");
    printf("<td>duration14</td><td>puzzle14</td><td>elapsed14</td><td>answer14</td><td>correct14</td>");
    printf("<td>duration15</td><td>puzzle15</td><td>elapsed15</td><td>answer15</td><td>correct15</td>");
    printf("<td>duration16</td><td>puzzle16</td><td>elapsed16</td><td>answer16</td><td>correct16</td>");
    printf("<td>duration17</td><td>puzzle17</td><td>elapsed17</td><td>answer17</td><td>correct17</td>");
    printf("<td>duration18</td><td>puzzle18</td><td>elapsed18</td><td>answer18</td><td>correct18</td>\n");
    printf("</thead>\n");
    for (vecHoopsRecord::const_iterator it = records.begin(); it != records.end(); it++) {
        printf("<tr>");
        printf("<td>%d</td><td>%d</td><td>%s</td><td>%s</td><td>%s</td>", it->sesh_id, it->ntests, it->tinstruct.iso().c_str(), it->tstart.iso().c_str(), it->tfinish.iso().c_str());
        printf("<td>%s</td>", it->responses.c_str());
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration1, it->puzzle1, it->elapsed1, it->answer1, it->correct1);
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
        printf("<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", it->duration18, it->puzzle18, it->elapsed18, it->answer18, it->correct18);
        printf("</tr>\n");
    }
    printf("</table>\n");
    printf("</code>");
}
