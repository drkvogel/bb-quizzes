## todo


### hoops order

pseudo-random - there are 18 levels and the sequence of correct answers will always be the same - `m_sudoRndLevelList` - but which puzzle with that particular answer is picked from a pool - 4 for each answer - from `m_TOLgameData` - `m_answers` says which is which:

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
```

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops

* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208


determine the scaling in each of the horizontal and vertical directions required to fit the window
  scaling of what? 
  height and width of whole thing without scaling? which is what? the natural size? depends on how big the viewport is...
then resize using the smaller of these factors as a parameter

### scaleImagesCBnew()

get the various heights with jquery
max height of 
width-wise, if there is enough height, there will be no margins on the images and they will scale to fit anyway (width: 100%)
// missing some widths and heights?


Galaxy Core Prime - 800 x 480


get code to print worked examples
hoops scales but not brilliantly - text, buttons scroll off bottom. margin-left, margin-right being calculated and inserted on resize - scaleImages()
fossilize... look at fossil bugs bb-quizzes.fossil
aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start


