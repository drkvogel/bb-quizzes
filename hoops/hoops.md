# Hoops quiz

bb-quizzes/jonathanpr/BioBankQuizGames/TowerOfLondonGame.cpp

One of the pictures is the same for each puzzle - in the desktop version, the bottom "Picture B" always looks like this:

      |
    black       |     
    white    yellow     |  (none)

So that the top picture ("Picture A") changes for each puzzle, and the subject is required to guess how many moves would make each top picture into the same bottom picture. In the web version, this is to be reversed, so that the top picture remains constant, and the subject is asked how many moves are required to make each different bottom picture. The number of moves are, of course, the same for each puzzle.

### hoops order

The order of the puzzles is pseudo-random. There are 18 levels and the sequence of correct answers will always be the same - `m_sudoRndLevelList` - but which puzzle with that particular answer is picked from a pool - `m_TOLgameData`. `m_answers` says which is which:

```cpp
// levelData.cpp
const int levelData::m_answers[MAX_LEVELS] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};
int levelData::m_rndLevel[MAX_LEVELS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
int levelData::m_sudoRndLevelList[MAX_LEVELS] = {1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5};
```

this is what to draw for each of the 18 games - 6-tuples where 0 is no hoop, 1, 2, 3 are each colour hoops, and the 3-tuple, pair and single values are what's on each stick:

```cpp
// TowerOfLondonGame.cpp
const int TOWEROFLONDON_GAME::m_TOLgameData[18][6] =
    {0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0}, 
    {0, 0, 2, 0, 3, 1}, {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3},
    {0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1}, {0, 3, 2, 0, 1, 0},
    {0, 0, 2, 3, 1, 0}, {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0},
    {0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2}, {0, 2, 3, 0, 1, 0},
    {0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0};
const int TOWEROFLONDON_GAME::m_TOL_wantedGameData[6] = {0, 1, 2, 0, 3, 0};

    int     m_toparray[8];
    int     m_bottomarray[8];

    int index = m_levelData->getGameLevel(m_GameID);
    for (int i = 0; i < 6; i++)
        m_toparray[i] = m_TOLgameData[index][i];

```


## defer

detect rotation w js?

## done

top-constant.png
The C++ Builder `.exe`, `C:\Users\cbird\Dropbox\work\bb-quizzes\Jon-touchscreens.exe`, seems to use a lot of CPU on my laptop - up to 25%.
