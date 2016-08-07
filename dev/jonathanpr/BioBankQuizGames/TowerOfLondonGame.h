//---------------------------------------------------------------------------

#ifndef TowerOfLondonGameH
#define TowerOfLondonGameH

//---------------------------------------------------------------------------
#include "windef.h"
#include <System.Math.hpp>
#include <vcl.h>
#include <vector>
#include <string>
#include <time.h>
#include "levelData.h"

#define START_LEVEL -6

//---------------------------------------------------------------------------
class TOWEROFLONDON_GAME
{
private:
	bool	is_running;
	bool	ignore_click;

public:
	TOWEROFLONDON_GAME( TImage *board, const TColor background,void (* setTimeOut)(bool),void (* setFlashTimeOut)(bool), TButton *NextButton, TButton *PrevButton);
	~TOWEROFLONDON_GAME( void );
	bool initGame(const int gameid = START_LEVEL); //layout game
	void initalise(); //load in graphics..etc ready
	void drawGameBoard();
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
	clock_t	start_level, end_level;
//call backs to kick off timers
	void 	(* setTimeOutFunction)(bool);
	void 	(* setFlashTimeOutFunction)(bool);

	void 	showButtons(bool show);
	void 	NewSaveRow();
	void 	doIntoTextScreen();
	int 	getGamePadSize();
	int 	getGamePadPadding();
	int 	getGamePadX();
	int 	getGamePadY();
	void 	drawExampleBoard();
	void 	drawGameText();
	void 	drawBall(int posY,int Ball,int Pos);
	void 	drawNumberPad();
	void	NumberPadDisabled();
	void 	drawNumberPadFlash();
	void 	drawBlock(String Image, TColor PenCol,TColor BrushCol, int PosX, int PosY);
	void 	drawBoard(int Bottom);
	void 	fillHeaderData();

	TButton *m_NextButton;
	TButton *m_PrevButton;

	bool 	m_timedOut;  //When the time is up, this is set. on next user input, the same is over
	int 	m_GameID; //track where we are in the test. Negivite is in intro/instrcutions.

	TImage 	*m_playing_board;
	levelData *m_levelData;

	long TOWEROFLONDON_GAME::milliSecondsToDeciSeconds(System::TDateTime &timeNow,System::TDateTime &timeThen);

//Const game data
	static const String m_inGameText[1];
	static const String m_introText_7[6];
	static const String m_introText_6[8];
	static const String m_introText_5[5];
	static const String m_introText_4[1];
	static const String m_introText_3[3];
	static const String m_introText_2[2];

	static const int m_TOLgameData[18][6];
	static const int m_TOL_wantedGameData[6];

//last user input
	int 	m_iuserkeyinput;

//What Discs are to be displaced on each board
	int 	m_toparray[8];
	int 	m_bottomarray[8];

	int 	m_score;  //keeps a count of all sucessful attempts in live
	System::TDateTime m_londonstarted_ts; //The ts when this game started
	System::TDateTime m_liveGame_ts; //The time the live game has been running, we don't care about read text times I assume.
	System::TDateTime m_levelStart_ts; //The ts when the level begain
	System::TDateTime m_flashStart_ts; //The ts when the level begain

//sets up the m_DRAW_* vars below
	void SetUpConsts();

//vars used in rendering the board and Discs
	int 	m_DRAW_paddingX;
	int 	m_DRAW_paddingY;

	int 	m_DRAW_board_Left;
	int 	m_DRAW_board_Right;

	int 	m_DRAW_board1_Top;
	int 	m_DRAW_board1_Bottom;
	int 	m_DRAW_board2_Top;
	int 	m_DRAW_board2_Bottom;

	int 	m_DRAW_board_Width;
	int 	m_DRAW_board_Height;

	int 	m_DRAW_unitHight;

	int 	m_DRAW_blockWidth;
	int 	m_DRAW_halfBlockWidth;

	int 	m_DRAW_middle;
	int 	m_DRAW_rightpos;
	int 	m_DRAW_leftpos;

//Set these below to position, size the boards
	int 	ajust_boardHeight;  //ajustment of the hight of the board
	int 	ajust_paddingBetweenBoards;  //ajustment to the padding between top and bottom board
	int 	ajust_offsetFromScreenTop;  //offset of the board from the top of the screen
	int 	ajust_widthofboard; //width the boarder width around the board, or at least the ajustment

//flashing
	int 	m_flashCounter;
	int 	m_disabledCounter;


	std::string stdstring( const UnicodeString& s )
	{
		AnsiString as( s.c_str() );
		return as.c_str();
	}

public:
	struct returnDataHeader
	{
		String partid;// value="456" />
		String dateStarted;// value="2013-08-30T10:16:30:000" />

		int abandon;// value="0" />
		int timedout; //
		long liveelapsed;//  = nowtime-changeStart[1];
		long totelapsed;// = nowtime-starttime;
		long instrelapsed;  //intro time
		int	 score;// = lastScore;
		long flashlapsed;
	};

	struct returnDataRow
	{
		int level; //which level.. 0 -> 13
		int game_index; //index into the game level array
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
