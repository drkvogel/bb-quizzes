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


```cpp
class rndIntArray //}
public:
    rndIntArray(int size = 18) //{}
        srand(time(NULL));
        m_size = size;
        m_used = 0;
        m_data = NULL; // int *m_data;
    }

    ~rndIntArray() //{
        if (m_data)
            delete []m_data;
    }

    void push(int newInt) //{
        checkGrow();                            // check if the size of the array needs to grow
        m_data[m_used] = newInt;                // push the value onto the stack
        m_used++;
    }

    int pop() //{
        if (isEmpty()) 
            throw Exception_rndIntArray_Empty();

        int index = 0;
        if (m_used > 1)
            index = (rand() % (m_used-1));      // pick a random element from the list
        int result = m_data[index];             // that's your popped result

        for (int i=index;i<m_used-1;i++)
            m_data[i] = m_data[i+1];            // shuffle the others left to fill gap
        m_used--;                               // number of elements is one less
        return result;
    }

    bool isEmpty() //{
        return (m_used==0);
    }
private:
    void checkGrow() //{
        if (m_data == NULL) //{                   // no data yet, initialise at m_size
            m_data = new int[m_size];
        } else if (m_used == m_size) //{
            int *m_biggerData = new int[m_size*2]; // create new twice as big
            if (m_biggerData == NULL) 
                throw std::bad_alloc();         // if it fails
            for (int i=0;i<m_size;i++) 
                m_biggerData[i] = m_data[i];    // copy old to new
            delete []m_data;                    // delete old
            m_data = m_biggerData;              // swap
            m_size *=2;                         // size is double
        }
    }
    int *m_data;
    int m_size;
    int m_used;
};
```


## defer

detect rotation w js?

## done

top-constant.png
The C++ Builder `.exe`, `C:\Users\cbird\Dropbox\work\bb-quizzes\Jon-touchscreens.exe`, seems to use a lot of CPU on my laptop - up to 25%.
