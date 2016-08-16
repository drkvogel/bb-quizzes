### hoops order

The order of the puzzles is pseudo-random. There are 18 levels and the sequence of correct answers will always be the same - `m_sudoRndLevelList` - but which puzzle with that particular answer is picked from a pool - `m_TOLgameData`. `m_answers` says which is which:

`m_TOLgameData` shows what to draw for each of the 18 games - 6-tuples where 0 is no hoop, 1, 2, 3 are each colour hoops, and the 3-tuple, pair and single values are what's on each stick. 0 = no hoop; 1 = black; 2 = white; 3 = yellow. e.g.

    {0, 1, 2, 0, 0, 3} -> { 0, 1, 2 } { 0, 0 } { 3 } -> 
    3-hoop stick has nothing, black, white
    2-hoop stick has nothing, nothing
    1-hoop stick has yellow
    or t3bw21y.png in my naming scheme

```cpp
    // levelData.cpp
    const int levelData::m_answers[MAX_LEVELS] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};
    int levelData::m_rndLevel[MAX_LEVELS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    int levelData::m_sudoRndLevelList[MAX_LEVELS] = {1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5};

    // TowerOfLondonGame.cpp
    const int TOWEROFLONDON_GAME::m_TOLgameData[18][6] =
    /* 1 */    {0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0}, {0, 0, 2, 0, 3, 1},  // t3bw21y-, t3ybw21-, t3w2by1?, t3w2y1b?
    /* 2 */    {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3}, {0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1},  // t32wy1b-, t3w2b1y-, t32by1w-, t3yw21b-
    /* 3 */    {0, 3, 2, 0, 1, 0}, {0, 0, 2, 3, 1, 0},                                          // t3yw2b1-, t3w2yb1-
    /* 4 */    {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0}, {0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2},  // t3wb2y1-, t3y2wb1?, t3yb21w-, t32yb3w?
    /* 5 */    {0, 2, 3, 0, 1, 0}, {0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0};  // t3wy2b1-, t3y2b1w-, t3ywb21-, t3wyb21?
    const int TOWEROFLONDON_GAME::m_TOL_wantedGameData[6] = {0, 1, 2, 0, 3, 0}; // fixed configuration which was at the bottom, now at top - t3bw2y1
    for (int i = 0; i < 6; i++) m_toparray[i] = m_TOLgameData[index][i];    // top images
    for (int i = 0; i < 6; i++) m_bottomarray[i] = m_TOL_wantedGameData[i]; // bottom image

    int index = m_levelData->getGameLevel(m_GameID);

    // 0 = no hoop; 1 = black; 2 = white; 3 = yellow
    if (Ball == 1) m_playing_board->Canvas->Brush->Color = clBlack;
    else if (Ball == 2) m_playing_board->Canvas->Brush->Color = clWhite;
    else m_playing_board->Canvas->Brush->Color = clYellow;
```

    2016-08-16 10:58:41 cbird@q108-vlubuntu ~/Projects/bb-quizzes/hoops/yo/app/images
    $ ls -1
    top-constant.png t3bw2y1 check - same as m_TOL_wantedGameData
    t32by1w.png-
    t32wy1b.png-
    t3bw21y.png-
    t3w2b1y.png-
    t3w2yb1.png-
    t3wb2y1.png-
    t3wy2b1.png-
    t3y2b1w.png-
    t3yb21w.png-
    t3ybw21.png-
    t3yw21b.png-
    t3yw2b1.png-
    t3ywb21.png- # 13, need 18 - 5 missing
    intro1.png
    intro2.png
    intro3.png
    intro4.png
    intro5-orig.png
    intro5.png

    missing: t3w2by1, t3w2y1b, t3y2wb1, t32yb3w, t3wyb21