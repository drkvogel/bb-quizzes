#ifndef _hoopsH_
#define _hoopsH_

extern XDB *db;

namespace Hoops {

typedef struct {
    int sesh_id;
    int ntests;
    XTIME tinstruct;
    XTIME tstart;
    XTIME tfinish;
    XTIME tinsert;

    std::string responses; //char responses[1600];

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
} HoopsRecord; //BBQuizRecord;
typedef std::vector< HoopsRecord > vecHoopsRecord;

void parseResponses(const HoopsRecord *e);
void testInsert();
bool insertRecord(const HoopsRecord *e);
void getRecords();

} // namespace Hoops

#endif
