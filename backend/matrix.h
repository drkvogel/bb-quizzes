#ifndef _matrixH_
#define _matrixH_

extern XDB *db;

namespace Matrix {

typedef struct {
    int sesh_id;
    int ntests;
    XTIME tinstruct;
    XTIME tstart;
    XTIME tfinish;
    XTIME tinsert;
    std::string responses;

    int duration1;
    int elapsed1;
    int answer1;
    int correct1;

    int duration2;
    int elapsed2;
    int answer2;
    int correct2;

    int duration3;
    int elapsed3;
    int answer3;
    int correct3;

    int duration4;
    int elapsed4;
    int answer4;
    int correct4;

    int duration5;
    int elapsed5;
    int answer5;
    int correct5;

    int duration6;
    int elapsed6;
    int answer6;
    int correct6;

    int duration7;
    int elapsed7;
    int answer7;
    int correct7;

    int duration8;
    int elapsed8;
    int answer8;
    int correct8;

    int duration9;
    int elapsed9;
    int answer9;
    int correct9;

    int duration10;
    int elapsed10;
    int answer10;
    int correct10;

    int duration11;
    int elapsed11;
    int answer11;
    int correct11;

    int duration12;
    int elapsed12;
    int answer12;
    int correct12;

    int duration13;
    int elapsed13;
    int answer13;
    int correct13;

    int duration14;
    int elapsed14;
    int answer14;
    int correct14;

    int duration15;
    int elapsed15;
    int answer15;
    int correct15;

    int duration16;
    int elapsed16;
    int answer16;
    int correct16;

    int duration17;
    int elapsed17;
    int answer17;
    int correct17;

    int duration18;
    int elapsed18;
    int answer18;
    int correct18;
} MatrixRecord; //BBQuizRecord;
typedef std::vector< MatrixRecord > vecMatrixRecord;

void parseResponses(const MatrixRecord *e);
void insert();
void testInsert();
bool insertRecord(const MatrixRecord *e);
void getRecords();

} // namespace Matrix

#endif
