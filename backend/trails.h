#ifndef _trailsH_
#define _trailsH_

#include "xcgi.h"
#include "nxjson.h"
//#include "bbquiz.h"

extern XDB *db;

namespace Trails {
    const short MAX_LEVELS = 18;
    typedef struct {
        int duration;
        int puzzle;
        int elapsed;
        int answer;
        int correct;
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
//     vecTrailsRecord records;

    void parseResponses(TrailsRecord *rec);
    void printAnswer(const nx_json* node);
    void printJSONAnswer(const nx_json* node);
    void printTrailsAnswer(TrailsAnswer & ans);

    TrailsRecord getPayload(XCGI * x);
    void testInsert();
    bool insertRecord(const TrailsRecord *e);
    void getRecords();
    void printRecords();
    void printRecord(TrailsRecord rec);
} // namespace Trails

#endif



