//---------------------------------------------------------------------------

#pragma hdrstop

#include <assert.h>
#include <list>
#include "rand.h"
#include "System.DateUtils.hpp"

#include "levelData.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)

levelData *levelData::getRandomisedLevels() { // not used
	levelData *pLevelData = new levelData();
	pLevelData->rndLevels();
	return pLevelData;
}

levelData *levelData::getRandomiseWithFixedDifficulty() {
	levelData *pLevelData = new levelData();
	pLevelData->rndFixedLevels();
	return pLevelData;
}

void levelData::rndLevels() // not random at all! and not used
{
	rndIntArray m_newRndLevel;
	for(int i = 0; i<m_MAX_LEVEL;i++)
		m_newRndLevel.push(i);					// push 0-17 onto m_newRndLevel

	for(int i = 0; i<m_MAX_LEVEL;i++)
		m_rndLevel[i] = m_newRndLevel.pop();	// pop them back off into m_rndLevel in a random order

	m_isInitalised = true;
}

void levelData::rndFixedLevels()
{
	rndIntArray m_newRndLevel[5]; //should called default constuctor.. check this
	for (int i=0;i<MAX_LEVELS;i++) {
		int forLevel = m_answers[i];
		m_newRndLevel[forLevel-1].push(i);
	}

	//and serve up
	for (int i=0;i<MAX_LEVELS;i++) {
		int wantedLevel = m_sudoRndLevelList[i];
		m_rndLevel[i] = m_newRndLevel[wantedLevel-1].pop();
	}

	m_isInitalised = true;
}

levelData::levelData() : m_MAX_LEVEL(MAX_LEVELS) {
	m_isInitalised = false;
}

int levelData::getGameLevel(int index) {
	assert(m_isInitalised);
	assert(index < MAX_LEVELS);
	return m_rndLevel[index];
}

int levelData::getExpectedAnswer(int index) {
	assert(m_isInitalised);
	assert(index < MAX_LEVELS);
	return m_answers[m_rndLevel[index]];
}

const int levelData::m_answers[MAX_LEVELS] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};

int levelData::m_rndLevel[MAX_LEVELS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};

int levelData::m_sudoRndLevelList[MAX_LEVELS] = {1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5};
