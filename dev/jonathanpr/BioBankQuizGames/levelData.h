//---------------------------------------------------------------------------

#ifndef levelDataH
#define levelDataH
//---------------------------------------------------------------------------

#define MAX_LEVELS 18
#include "rndIntArray.h"

class levelData
{
public:
	static levelData *getRandomisedLevels();
	static levelData *getRandomiseWithFixedDifficulty();

	int getGameLevel(int index);
	int getExpectedAnswer(int index);
	~levelData() {;}
private:
	levelData();
	const int m_MAX_LEVEL;

	void rndLevels();
	void rndFixedLevels();

	bool m_isInitalised;

	static const int m_answers[MAX_LEVELS];
	static int m_rndLevel[MAX_LEVELS];

//the difficulty levels for 'FixedDifficulty'
	static int m_sudoRndLevelList[MAX_LEVELS];
};


#endif
