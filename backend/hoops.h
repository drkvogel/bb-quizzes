#ifndef _hoopsH_
#define _hoopsH_

#include "xcgi.h"
#include "nxjson.h"
//#include "bbquiz.h"

extern XDB *db;

namespace Hoops {
    typedef struct {
        int duration;
        int puzzle;
        int elapsed;
        int answer;
        int correct;
    } HoopsAnswer;
    typedef std::vector< HoopsAnswer > vecHoopsAnswer;
    
    typedef struct {
        int sesh_id;
        XTIME tinstruct;
        XTIME tstart;
        XTIME tfinish;
        // tinsert set in SQL
        int ntests;
        std::string responses; //char responses[1600];
        vecHoopsAnswer answers;    
    } HoopsRecord; //BBQuizRecord;
    typedef std::vector< HoopsRecord > vecHoopsRecord;

    void parseResponses(HoopsRecord *rec);
    void printAnswer(const nx_json* node);

    void printJSONAnswer(const nx_json* node);
    void printHoopsAnswer(HoopsAnswer & ans);

    HoopsRecord getPayload(XCGI * x);
    void testInsert();
    bool insertRecord(const HoopsRecord *e);
    void getRecords();
    void printRecords();
    void printRecord(HoopsRecord rec);
} // namespace Hoops

#endif



