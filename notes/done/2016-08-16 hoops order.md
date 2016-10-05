
## done

### hoops order

The order of the puzzles is pseudo-random. There are 18 levels and the sequence of correct answers will always be the same - `m_sudoRndLevelList` - but which puzzle with that particular answer is picked from a pool - `m_TOLgameData`. `m_answers` says which is which:

`m_TOLgameData` shows what to draw for each of the 18 games - 6-tuples where 0 is no hoop, 1, 2, 3 are each colour hoops, and the 3-tuple, pair and single values are what's on each stick. 0 = no hoop; 1 = black; 2 = white; 3 = yellow. e.g.

    {0, 1, 2, 0, 0, 3} -> { 0, 1, 2 } { 0, 0 } { 3 } -> 
    3-hoop stick has nothing, black, white; 2-hoop stick has nothing, nothing; 1-hoop stick has yellow - or t3bw21y.png in my naming scheme

```cpp

// TowerOfLondonGame.cpp
// 0 = no hoop; 1 = black; 2 = white; 3 = yellow
const int TOWEROFLONDON_GAME::m_TOLgameData[18][6] =
/* 1 */    {0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0}, {0, 0, 2, 0, 3, 1},  // t3bw21y-, t3ybw21-, t3w2by1?, t3w2y1b?
/* 2 */    {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3}, {0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1},  // t32wy1b-, t3w2b1y-, t32by1w-, t3yw21b-
/* 3 */    {0, 3, 2, 0, 1, 0}, {0, 0, 2, 3, 1, 0},                                          // t3yw2b1-, t3w2yb1-
/* 4 */    {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0}, {0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2},  // t3wb2y1-, t3y2wb1?, t3yb21w-, t32yb3w?
/* 5 */    {0, 2, 3, 0, 1, 0}, {0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0};  // t3wy2b1-, t3y2b1w-, t3ywb21-, t3wyb21?
const int TOWEROFLONDON_GAME::m_TOL_wantedGameData[6] = {0, 1, 2, 0, 3, 0}; // fixed configuration which was at the bottom, now at top - t3bw2y1
for (int i = 0; i < 6; i++) m_toparray[i] = m_TOLgameData[index][i];    // top images
for (int i = 0; i < 6; i++) m_bottomarray[i] = m_TOL_wantedGameData[i]; // bottom image

levelData *m_levelData;
int index = m_levelData->getGameLevel(m_GameID); // just returns m_rndLevel[m_GameID], which is the same as m_GameID?

// levelData.cpp
const int levelData::m_answers[MAX_LEVELS] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};
int levelData::m_rndLevel[MAX_LEVELS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
int levelData::m_sudoRndLevelList[MAX_LEVELS] = {1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5};

m_levelData = levelData::getRandomiseWithFixedDifficulty();
    pLevelData->rndFixedLevels();

void levelData::rndFixedLevels() //{
    rndIntArray m_newRndLevel[5]; // rndIntArray.h

    for (int i=0; i<MAX_LEVELS; i++) //{
        int forLevel = m_answers[ i ];
        m_newRndLevel[ forLevel-1 ].push( i ); // populate m_newRndLevel with wanted 'level' (number of moves, i.e. the answer)
    }

    for (int i=0; i<MAX_LEVELS; i++) //{
        int wantedLevel = m_sudoRndLevelList[ i ];
        m_rndLevel[ i ] = m_newRndLevel[ wantedLevel-1 ].pop();
    }
}

```

/home/cbird/Projects/bb-quizzes/dev/jonathanpr/BioBankQuizGames/rndIntArray.h

    2016-08-16 10:58:41 cbird@q108-vlubuntu ~/Projects/bb-quizzes/hoops/yo/app/images
    $ ls -1
    top-constant.png t3bw2y1 check - same as m_TOL_wantedGameData
    t32by1w.png- t32wy1b.png- t3bw21y.png- t3w2b1y.png- t3w2yb1.png- t3wb2y1.png- t3wy2b1.png- t3y2b1w.png- t3yb21w.png- t3ybw21.png- t3yw21b.png- t3yw2b1.png-
    t3ywb21.png- # 13, need 18 - 5 missing
    intro1.png intro2.png intro3.png intro4.png intro5-orig.png intro5.png

    missing: 
    t3w2by1 white, black + yellow, none
    t3w2y1b white, yellow, black
    t3y2wb1 yellow, white + black, none
    t32yb3w none, yellow + black, white
    t3wyb21 white + yellow + black, none, none

C:\Users\cbird\Projects\general\personal\todos\2016-08-19 missing hoops.md




```cpp
/*
    t3w2by1 white, black + yellow, none         {0, 0, 2, 1, 3, 0} 2
    t3w2y1b white, yellow, black                {0, 0, 2, 0, 3, 1} 3
    t3y2wb1 yellow, white + black, none         {0, 0, 3, 2, 1, 0} 11
    t32yb1w none, yellow + black, white         {0, 0, 0, 3, 1, 2} 13
    t3wyb21 white + yellow + black, none, none  {2, 3, 1, 0, 0, 0} 17

const int TOWEROFLONDON_GAME::m_TOLgameData[18][6] = {
    {0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0},    2
    {0, 0, 2, 0, 3, 1}, {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3},    5
    {0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1}, {0, 3, 2, 0, 1, 0},    8
    {0, 0, 2, 3, 1, 0}, {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0},    11
    {0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2}, {0, 2, 3, 0, 1, 0},    14
    {0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0}};   17
    */

bool TOWEROFLONDON_GAME::initGame(const int gameid) 
    int index = m_levelData->getGameLevel(m_GameID);
    for (int i = 0; i < 6; i++) 
        //m_bottomarray[i] = m_TOLgameData[index][i];
        m_bottomarray[i] = m_TOLgameData[17][i];
    }
}
```

    2016-08-19 21:41:51 cbird@Q108 ~/Projects/bb-quizzes
    $ gst
    # On branch master
    # Changes to be committed:
    #   (use "git reset HEAD <file>..." to unstage)
    #
    #       new file:   hoops/dev/images/missing/t32yb1w.png
    #       new file:   hoops/dev/images/missing/t3w2by1.png
    #       new file:   hoops/dev/images/missing/t3w2y1b.png
    #       new file:   hoops/dev/images/missing/t3wyb21.png
    #       new file:   hoops/dev/images/missing/t3y2wb1.png
    #

    /* 1 */    {0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0}, {0, 0, 2, 0, 3, 1},  // t3bw21y-, t3ybw21-, t3w2by1?, t3w2y1b?
    /* 2 */    {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3}, {0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1},  // t32wy1b-, t3w2b1y-, t32by1w-, t3yw21b-
    /* 3 */    {0, 3, 2, 0, 1, 0}, {0, 0, 2, 3, 1, 0},                                          // t3yw2b1-, t3w2yb1-
    /* 4 */    {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0}, {0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2},  // t3wb2y1-, t3y2wb1?, t3yb21w-, t32yb3w?
    /* 5 */    {0, 2, 3, 0, 1, 0}, {0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0};  // t3wy2b1-, t3y2b1w-, t3ywb21-, t3wyb21?

    't3bw21y', 't3ybw21', 't3w2by1', 't3w2y1b',
    't32wy1b', 't3w2b1y', 't32by1w', 't3yw21b',
    't3yw2b1', 't3w2yb1',
    't3wb2y1', 't3y2wb1', 't3yb21w', 't32yb3w',
    't3wy2b1', 't3y2b1w', 't3ywb21', 't3wyb21'