#ifndef _trailsH_
#define _trailsH_

#include "xcgi.h"
#include "nxjson.h"
//#include "bbquiz.h"

extern XDB *db;

#define NUM_POINTS_AP 8
#define NUM_POINTS_AR 25
#define NUM_POINTS_BP 8
#define NUM_POINTS_BR 25
#define NUM_POINTS_TOTAL NUM_POINTS_AP + NUM_POINTS_AR + NUM_POINTS_BP + NUM_POINTS_BR

namespace Trails {
    const short MAX_LEVELS = 18;

    // element: element,                      // id of element clicked on by user
        // needed? can be determined by position in list
    // duration: timer.getElapsed(),          // Time taken to click on next correct element
    // wrongClicks: wrongClicks,              // number of wrong clicks before correct
    // puzzle: page.name,                     // name of puzzle/practice
    // elapsed: timerWholeTest.getElapsed()
    typedef struct {
        std::string puzzle;
        int duration;
        int elapsed;
        int wrongClicks;
    } TrailsAnswer;
    typedef std::vector< TrailsAnswer > vecTrailsAnswer;

    typedef struct {
        int sesh_id;
        XTIME tinstruct;
        XTIME tstart;
        XTIME tfinish;
        // tinsert set in SQL
        int ntests;
        std::string responses; //char responses[1600];
        vecTrailsAnswer answers;
    } TrailsRecord; //BBQuizRecord;
    typedef std::vector< TrailsRecord > vecTrailsRecord;
    //static const char * const nx_json_type_names[]; // else "error: storage size of ‘Trails::nx_json_type_names’ isn’t known"
    //static const char Trails::nx_json_type_names[7][20];
//     vecTrailsRecord records;

    std::string nowString(); // should be in BBQuiz:: namespace
    void parseResponses(TrailsRecord *rec);
    void printAnswer(const nx_json* node);
    void printJSONAnswer(const nx_json* node);
    void printTrailsAnswer(TrailsAnswer & ans);

    TrailsRecord getPayload(XCGI * x);
    void testInsert();
    bool insertRecord(const TrailsRecord *e);
    void getRecords();
    void getResults(XQUERY & q, TrailsRecord & rec, const char * section, int numFields);
    void printRecords();
    void printRecord(TrailsRecord rec);
} // namespace Trails

#endif



