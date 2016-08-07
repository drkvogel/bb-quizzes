# Hoops quiz

bb-quizzes/jonathanpr/BioBankQuizGames/TowerOfLondonGame.cpp

One of the pictures is the same for each puzzle - in the desktop version, the bottom "Picture B" always looks like this:

      |
    black       |     
    white    yellow     |  (none)

So that the top picture ("Picture A") changes for each puzzle, and the subject is required to guess how many moves would make each top picture into the same bottom picture. In the web version, this is to be reversed, so that the top picture remains constant, and the subject is asked how many moves are required to make each different bottom picture. The number of moves are, of course, the same for each puzzle.



const int TOWEROFLONDON_GAME::m_TOLgameData[18][6] = {
    {0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0},
    {0, 0, 2, 0, 3, 1}, {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3},
    {0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1}, {0, 3, 2, 0, 1, 0},
    {0, 0, 2, 3, 1, 0}, {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0},
    {0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2}, {0, 2, 3, 0, 1, 0},
    {0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0}};

const int TOWEROFLONDON_GAME::m_TOL_wantedGameData[6] = {0, 1, 2, 0, 3, 0};

    int     m_toparray[8];
    int     m_bottomarray[8];

    int index = m_levelData->getGameLevel(m_GameID);
    for (int i = 0; i < 6; i++)
        m_toparray[i] = m_TOLgameData[index][i];




## defer

detect rotation w js?

## done

top-constant.png
The C++ Builder `.exe`, `C:\Users\cbird\Dropbox\work\bb-quizzes\Jon-touchscreens.exe`, seems to use a lot of CPU on my laptop - up to 25%.
