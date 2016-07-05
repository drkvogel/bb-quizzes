//---------------------------------------------------------------------------

#ifndef MatrixGameH
#define MatrixGameH

#include <vcl.h>
#include <time.h>
#include <string>
#include <vector>
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class MATRIX_GAME
{
private:
	bool	is_running;
	bool	ignore_click;

public:
	MATRIX_GAME( TImage *board, const TColor background,void (* setTimeOut)(bool),void (* setFlashTimeOut)(bool,int), TButton *NextButton, TButton *PrevButton);
	~MATRIX_GAME( void );
	bool initGame(const int gameid = 0); //layout game
	void initalise(); //load in graphics..etc ready
	void timeout();
	void flashTimeout();

	bool	handleClick( const int x, const int y );
	bool	run( );
	bool	isRunning( void );
	void 	abandon( void );
	int 	getRunTime( void );
	void 	runStart( void );
	int 	m_nextSelectedID;
	void 	NextClicked();
	void 	PrevClicked();

private:
	void doIntoScreen();
	void showButtons(bool show);
	void DrawQuestion(int level);
	void DrawAnswers(level);
	int getAnswer(int level,TPoint &clickPos);
	void DrawMissing(int level,int srcBlock);
	void drawGame();

	long milliSecondsToDeciSeconds(System::TDateTime &timeNow,System::TDateTime &timeThen);


	clock_t	start_level, end_level;
//call backs to kick off timers
	void 	(* setTimeOutFunction)(bool);
	void 	(* setFlashTimeOutFunction)(bool,int);

	void 	NewSaveRow();
    void drawArrow();
	void 	fillHeaderData();

	TButton *m_NextButton;
	TButton *m_PrevButton;

	bool 	m_timedOut;  //When the time is up, this is set. on next user input, the same is over
	int 	m_GameID; //track where we are in the test. Negivite is in intro/instrcutions.

	TImage 	*m_playing_board;
	int 	m_score;  //keeps a count of all sucessful attempts in live

	System::TDateTime m_started_ts; //The ts when this game started
	System::TDateTime m_liveGame_ts; //The time the live game has been running, we don't care about read text times I assume.
	System::TDateTime m_levelStart_ts; //The ts when the level begain
	System::TDateTime m_flashStart_ts; //The ts when the level begain
	bool isLive;
	int  m_toNextLevel;

	int m_ImageHeight;
	int m_ImageWidth;

	std::string stdstring( const UnicodeString& s )
	{
		AnsiString as( s.c_str() );
		return as.c_str();
	}

	#define NO_LEVELS 19
	#define LIVE_LEVELS_START 4

	static const char *m_levels[NO_LEVELS];
	static const int m_isLive[NO_LEVELS];
	static const int m_Buttons[NO_LEVELS];
	static const int m_Expected[NO_LEVELS];

	static const int m_layout_questions[19][8];
	static const int m_layout_buttons[19][8];

public:
	struct returnDataHeader
	{
		String partid;// value="456" />
		String dateStarted;// value="2013-08-30T10:16:30:000" />

		int abandon;// value="0" />
		int timedout; //
		int liveelapsed;//  = nowtime-changeStart[1];
		int totelapsed;// = nowtime-starttime;
		int instrelapsed;  //intro time
		int	 score;// = lastScore;
		int flashlapsed;
	};

	struct returnDataRow
	{
		int level; //which level.. 0 -> 13
		int expected;
		int selected;
		long elapsed;  //nowtime-digTime
		int complete; //is the data entry complete. will not be if aborted
	};

	returnDataRow *m_CurrentRow;
	returnDataHeader m_returnDataHeader;
	std::vector<returnDataRow *> m_returnDataRow;
};


//---------------------------------------------------------------------------
#endif

