//---------------------------------------------------------------------------

#pragma hdrstop

#include "MatrixGame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// 3 mins to complete as many as possible or complete 18
// elpased times in DeciSeconds

// ---------------------------------------------------------------------------

#include <vcl.h>
#include <sstream>
#include <iostream>  //cout

#include "rand.h"
#include "System.DateUtils.hpp"
#define	PLAY_BACKGROUND	((TColor) 0xffffff)
#define PLAY_BOARD ((TColor) 0x505050)
#define	USERINPUT_WHITE	((TColor) 0xFFFFFF)
#define USERINPUT_NUMBERPAD_GRAY ((TColor) 0xCCCCCC)
#define	USERINPUT_BORDER	((TColor) 0x6F5F00)

#define level_LIVE 1
#define level_PRACTICE 0
#define level_TRANSITION -1

#define width32 210
#define height32 170

#define width42 170
#define height42 135

#define answerPadding 25

// ===========================================================================
MATRIX_GAME::MATRIX_GAME(TImage *board, const TColor background,void(* setTimeOut)(bool),void(* setFlashTimeOut)(bool,int), TButton *NextButton, TButton *PrevButton)
	: m_NextButton(NextButton),m_PrevButton(PrevButton), setTimeOutFunction(setTimeOut), setFlashTimeOutFunction(setFlashTimeOut)
{
	m_returnDataHeader.flashlapsed = 0;
	m_playing_board = board;
	m_CurrentRow = NULL;
	m_ImageHeight = 0;
	m_ImageWidth = 0;
}

// ---------------------------------------------------------------------------
MATRIX_GAME::~MATRIX_GAME(VOID)
{
	if (m_CurrentRow)
	{
		delete m_CurrentRow;
		m_CurrentRow = NULL;
	}
	while (!m_returnDataRow.empty())
	{
		delete m_returnDataRow.back();
		m_returnDataRow.pop_back();
	}
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::NewSaveRow()
{
	if (m_CurrentRow)
	{
		m_returnDataRow.push_back(m_CurrentRow);
		m_CurrentRow = NULL;
	}
	// fill out the basic details of this new row
	m_CurrentRow = new returnDataRow();
	m_CurrentRow->complete = false;
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::timeout()
{
	m_timedOut = true;
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::flashTimeout()
{
	setFlashTimeOutFunction(false,0);
	if (m_isLive[m_GameID] == level_PRACTICE)
	{
		if (!m_toNextLevel)      //wrong answer?
		{
			doIntoScreen();
		}
		else
		{
			m_GameID++;
			doIntoScreen();
		}
	}
	else if (m_isLive[m_GameID] == level_LIVE)
	{
		initGame(m_GameID + 1);
	}
	ignore_click = false;
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::initalise()
{
	isLive = false;
	m_timedOut = false;
	if (m_CurrentRow)
	{
		delete m_CurrentRow;
		m_CurrentRow = NULL;
	}

	while (!m_returnDataRow.empty())
	{
		delete m_returnDataRow.back();
		m_returnDataRow.pop_back();
	}
	m_score = 0;
	m_returnDataHeader.flashlapsed = 0;
	m_returnDataHeader.totelapsed = 0;
	m_returnDataHeader.liveelapsed = 0;
	m_returnDataHeader.instrelapsed = 0;

	m_started_ts = Now();
	NewSaveRow();
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::showButtons(bool show)
{
	if (!show)
	{
		m_NextButton->Hide();
		m_PrevButton->Hide();
		return;
	}

	m_playing_board->Canvas->Font->Size = 15;
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	int YPos = 400;

	if (m_GameID == 0)
	{
		m_NextButton->Left = ((m_playing_board->Width / 2) - m_NextButton->Width / 2);
		m_NextButton->Top = YPos;
		m_NextButton->Show();
		m_PrevButton->Hide();
	}
	else
	{
		m_NextButton->Left = ((m_playing_board->Width / 2) - m_NextButton->Width / 2) + m_NextButton->Width;
		m_NextButton->Top = YPos;
		m_NextButton->Show();

		m_PrevButton->Left = ((m_playing_board->Width / 2) - m_NextButton->Width / 2) - m_PrevButton->Width;
		m_PrevButton->Top = YPos;
		m_PrevButton->Show();
	}
}
// ---------------------------------------------------------------------------

void MATRIX_GAME::drawArrow()
{
	m_playing_board->Canvas->Pen->Width = 7.0;
	m_playing_board->Canvas->Pen->Color = clGray;
	m_playing_board->Canvas->MoveTo(250,280);
	m_playing_board->Canvas->LineTo(580,700);
	m_playing_board->Canvas->MoveTo(580-24,700-2);
	m_playing_board->Canvas->LineTo(580,700);
	m_playing_board->Canvas->MoveTo(580-3,700-30);
	m_playing_board->Canvas->LineTo(580,700);

	m_playing_board->Canvas->Pen->Width = 5.0;
	m_playing_board->Canvas->Pen->Color = clBlack;
	m_playing_board->Canvas->MoveTo(250,280);
	m_playing_board->Canvas->LineTo(580,700);
	m_playing_board->Canvas->MoveTo(580-24,700-2);
	m_playing_board->Canvas->LineTo(580,700);
	m_playing_board->Canvas->MoveTo(580-3,700-30);
	m_playing_board->Canvas->LineTo(580,700);

	m_playing_board->Canvas->Pen->Width = 1.0;
	m_playing_board->Canvas->Pen->Color = USERINPUT_BORDER;
}
// ---------------------------------------------------------------------------

void MATRIX_GAME::doIntoScreen()
{
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	m_playing_board->Canvas->FillRect(m_playing_board->ClientRect);
	m_playing_board->Canvas->Font->Name = "Arial";

//Is this the last screen before we start the real quiz?
	if (m_isLive[m_GameID] == level_TRANSITION)
	{
		int Y = 320;
		m_playing_board->Canvas->Font->Size = 15;

		String text1 = "You will have 2 minutes to do as many puzzles as you can.";
		TSize textSize = m_playing_board->Canvas->TextExtent(text1);

		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), Y,text1);
		Y+=25;
		text1 = "Touch Next when you are ready to begin.";
		textSize = m_playing_board->Canvas->TextExtent(text1);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), Y, text1);
		showButtons(true);
	}
	else
	{
		showButtons(false);
		DrawQuestion(m_GameID);
		DrawAnswers(m_GameID);

		m_playing_board->Canvas->Pen->Width = 4.0;
		m_playing_board->Canvas->Pen->Color = USERINPUT_BORDER;
		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		if (m_GameID == 0)
		{
			int X = 20;
			int Y = 24;
			m_playing_board->Canvas->Font->Size = 18;
			m_playing_board->Canvas->TextOutW(X, Y, "Here is a design which is missing");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "a piece on the lower right hand");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "corner. At the bottom are shown six");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "pieces which would fit the missing");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "corner. Your task is to touch the");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "piece which best completes the");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "design at the top.");
			Y+=28;
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "Have a go now...");
		}
		if (m_GameID == 1)
		{
			int X = 20;
			int Y = 24;
			m_playing_board->Canvas->Font->Size = 18;
			m_playing_board->Canvas->TextOutW(X, Y, "Here is another practise puzzle.");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "Touch the piece which best");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "completes the design.");
		}
		if (m_GameID == 2)
		{
			int X = 20;
			int Y = 24;
			m_playing_board->Canvas->Font->Size = 18;
			m_playing_board->Canvas->TextOutW(X, Y, "This is the last practise puzzle.");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "Again, touch the piece which");
			Y+=28;
			m_playing_board->Canvas->TextOutW(X, Y, "best completes the design.");
		}
	}
}

// ---------------------------------------------------------------------------

void MATRIX_GAME::DrawQuestion(int level)
{
	Graphics::TBitmap *_img = new Graphics::TBitmap();
	_img->LoadFromResourceName((int) HInstance, m_levels[level]);
	m_playing_board->Canvas->CopyMode = cmSrcCopy;

	int cols = 2;
	int rows = 2;
	int height = height32;
	int width = width32;

	if (MATRIX_GAME::m_Buttons[level] == 8)
	{ //3x3
		rows = 3;
		cols = 3;
		height = height42;
		width = width42;
	}
	int startX = m_playing_board->Width/2 - ((((float)cols/2.0f)*(float)width));
	int startY = 30;

	int index = 0;
	for (int r=0;r<rows;r++)
	{
		for (int c=0;c<cols;c++)
		{
			int buttonIndex = m_layout_questions[level][index];
			if ((r == rows-1) && (c == cols-1))
				continue;
			RECT SrcRect = Bounds(buttonIndex*width,0,width,height);
			RECT DstRect = Bounds(startX+c*width,startY+r*height,width,height);
			m_playing_board->Canvas->CopyRect(DstRect, _img->Canvas, SrcRect);
			index++;
		}
	}
}
// ---------------------------------------------------------------------------
void MATRIX_GAME::DrawMissing(int level,int srcBlock)
{
	Graphics::TBitmap *_img = new Graphics::TBitmap();
	_img->LoadFromResourceName( (int) HInstance, m_levels[level]);
	m_playing_board->Canvas->CopyMode = cmSrcCopy;

	int cols = 2;
	int rows = 2;
	int height = height32;
	int width = width32;

	if (MATRIX_GAME::m_Buttons[level] == 8)
	{ //3x3
		rows = 3;
		cols = 3;
		height = height42;
		width = width42;
	}
	int startX = m_playing_board->Width/2 - ((((float)cols/2.0f)*(float)width));
	int startY = 30;

	int r=rows-1;
	int c=cols-1;

	int srcC = m_layout_buttons[level][srcBlock];

	RECT SrcRect = Bounds(srcC*width,0,width,height);
	RECT DstRect = Bounds(startX+c*width,startY+r*height,width,height);
	m_playing_board->Canvas->CopyRect(DstRect, _img->Canvas, SrcRect);
}
// ---------------------------------------------------------------------------

int MATRIX_GAME::getAnswer(int level,TPoint &clickPos)
{
	float cols = 3.0f;
	int rows = 2;
	int height = height32;
	int width = width32;

	if (MATRIX_GAME::m_Buttons[level] == 8)
	{ //3x3
		cols = 4.0f;
		height = height42;
		width = width42;
	}

	int startX = (m_playing_board->Width/2) - ((cols/2.0f)*(float)width) - ((cols/2.0f)*(float)answerPadding);
	int startY = m_playing_board->Height - 30 - (height*rows + answerPadding*rows);

	for (int r=0;r<rows;r++)
	{
		for (int c=0;c<cols;c++)
		{
			int X = startX+c*width+answerPadding+c*answerPadding;
			int Y = startY+r*height+r*answerPadding;
			System::Types::TRect DstRect(X,Y,X+width,Y+height);
			if (DstRect.Contains(clickPos))
				return c+cols*r;
		}
	}
	return -1;
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::DrawAnswers(int level)
{
	Graphics::TBitmap *_img = new Graphics::TBitmap();
	_img->LoadFromResourceName( (int) HInstance, m_levels[level]);
	m_playing_board->Canvas->CopyMode = cmSrcCopy;

	float cols = 3.0f;
	int rows = 2;
	int height = height32;
	int width = width32;

	if (MATRIX_GAME::m_Buttons[level] == 8)
	{ //3x3
		cols = 4.0f;
		height = height42;
		width = width42;
	}

	int startX = (m_playing_board->Width/2) - ((cols/2.0f)*(float)width) - ((cols/2.0f)*(float)answerPadding);
	int startY = m_playing_board->Height - 30 - (height*rows + answerPadding*rows);
	int index = 0;
	for (int r=0;r<rows;r++)
	{
		for (int c=0;c<cols;c++)
		{
			int buttonIndex = m_layout_buttons[level][index];
			RECT SrcRect = Bounds(buttonIndex*width,0,width,height);
			RECT DstRect = Bounds(startX+c*width+answerPadding+c*answerPadding,startY+r*height+r*answerPadding,width,height);
			m_playing_board->Canvas->CopyRect(DstRect, _img->Canvas, SrcRect);
			index++;
		}
	}
}

// ---------------------------------------------------------------------------

void MATRIX_GAME::drawGame()
{
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	m_playing_board->Canvas->FillRect(m_playing_board->ClientRect);
	m_playing_board->Canvas->Font->Name = "Arial";

	DrawQuestion(m_GameID);
	DrawAnswers(m_GameID);
	showButtons(false);
}
// ---------------------------------------------------------------------------

long MATRIX_GAME::milliSecondsToDeciSeconds(System::TDateTime &timeNow,System::TDateTime &timeThen)
{
	__int64 timemilli = MilliSecondsBetween(timeNow, timeThen);
	timemilli/=100;
	return (long)timemilli;
}

// ---------------------------------------------------------------------------
bool MATRIX_GAME::initGame(const int gameid)
{
	ignore_click = false;
	m_GameID = gameid;

	if (m_isLive[m_GameID] == level_PRACTICE)
	{
		if (m_GameID == 0)
		{
			initalise(); // set up inital game state
			doIntoScreen();
			drawArrow();
		}
		else
			doIntoScreen();
		return true;
	}

	System::TDateTime timeNow = Now();
	if (m_isLive[m_GameID-1] == level_TRANSITION)
	{
		// help is finished..
		m_returnDataHeader.instrelapsed = milliSecondsToDeciSeconds(timeNow, m_started_ts);
		setTimeOutFunction(true); // set timeout 180mins for the real thing
		isLive = true;
		m_liveGame_ts = timeNow;
	}

	m_NextButton->Hide();
	drawGame();

	if ((m_isLive[m_GameID] == level_LIVE) && (m_isLive[m_GameID-1] != level_TRANSITION))
		m_returnDataHeader.flashlapsed +=  milliSecondsToDeciSeconds(timeNow,m_flashStart_ts);

	m_levelStart_ts = timeNow;
	return true;
}
//----------------------------------------------------------------------------

void MATRIX_GAME::NextClicked()
{
	initGame(m_GameID+1);
}

//----------------------------------------------------------------------------
void MATRIX_GAME::PrevClicked()
{
	initGame(m_GameID-1);
}

//----------------------------------------------------------------------------
void MATRIX_GAME::fillHeaderData()
{
	System::TDateTime timeNow = Now();
	end_level = clock();

	if (!isLive)
		m_returnDataHeader.liveelapsed = 0;
	else
		m_returnDataHeader.liveelapsed = milliSecondsToDeciSeconds(timeNow, m_liveGame_ts);
	m_returnDataHeader.totelapsed = milliSecondsToDeciSeconds(timeNow, m_started_ts);
	m_returnDataHeader.score = m_score;
	m_returnDataHeader.abandon = false;
	m_returnDataHeader.timedout = m_timedOut;
	String startDate = m_started_ts.FormatString("yyyy-mm-dd") + "T" + m_started_ts.FormatString("hh:mm:ss");
	m_returnDataHeader.dateStarted=startDate; //L"2013-08-30T10:16:30:000";
}

// ---------------------------------------------------------------------------
bool MATRIX_GAME::handleClick(const int x, const int y)
{
	if (ignore_click) // PREVENT OVER-LAPPING CALLS
		return (false);

	if (m_isLive[m_GameID] == level_TRANSITION)
		return (false);

	ignore_click = true;
	TPoint p(x,y);
	int whichButton = getAnswer(m_GameID,p);

	if (whichButton == -1)
	{
		ignore_click = false;
		return (false);
	}

	if (m_isLive[m_GameID] == level_PRACTICE)
	{
		DrawMissing(m_GameID,whichButton);

		if (m_Expected[m_GameID] != whichButton)
		{
			m_playing_board->Canvas->Font->Size = 20;
			m_playing_board->Canvas->Brush->Color = clRed;//USERINPUT_WHITE;

			String text = "Sorry, try a different one";
			TSize textSize = m_playing_board->Canvas->TextExtent(text);

			m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), m_playing_board->Height-60, text);
			m_toNextLevel = false;
		}
		else
		{
			m_toNextLevel = true;
		}
	}
	else // level_LIVE)
	{
		DrawMissing(m_GameID,whichButton);
		m_toNextLevel = true;
		showButtons(false);

		int expected = m_Expected[m_GameID];
		if ((whichButton == expected))
			m_score++;

		System::TDateTime timeNow = Now();
		m_CurrentRow->level = m_GameID-LIVE_LEVELS_START;
		m_CurrentRow->expected =  expected;
		m_CurrentRow->selected = whichButton;
		m_CurrentRow->elapsed =  milliSecondsToDeciSeconds(timeNow,m_levelStart_ts);
		m_CurrentRow->complete = !m_timedOut;  //dpn't save timedout
		NewSaveRow();
	}

	if ((m_timedOut) || (m_GameID == NO_LEVELS-1))
	{
		setTimeOutFunction(false);
		fillHeaderData();
		is_running = false;
	}
	else
	{//next level
	  	System::TDateTime timeNow = Now();
		m_flashStart_ts = timeNow;
		setFlashTimeOutFunction(true,1500);
	}
	return (false);
}

// ---------------------------------------------------------------------------
bool MATRIX_GAME::isRunning(void)
{
	return (is_running);
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::abandon(void)
{
// we are fine for timeout, as it is never processed until
//the user interacts. and they can't if the abondon box is open.
	fillHeaderData();
	m_returnDataHeader.abandon = true;
	is_running = false;
}

// ---------------------------------------------------------------------------
void MATRIX_GAME::runStart(void)
{
	is_running = true;
}

// ---------------------------------------------------------------------------
bool MATRIX_GAME::run()
{
	ignore_click = true;
	is_running = true;
	runStart();
	ignore_click = false;
	start_level = clock();
	end_level = start_level;
	Application->ProcessMessages();
	return (true);
}

// ---------------------------------------------------------------------------
/* RETURN RUN-TIME IN DECI-SECONDS */
int MATRIX_GAME::getRunTime(void)
{
	return ((int)((10 * (end_level - start_level)) / CLK_TCK));
}
// ---------------------------------------------------------------------------

const char *MATRIX_GAME::m_levels[NO_LEVELS] = {
			"matrix_ex1",
			"matrix_ex2",
			"matrix_ex3",
			"transition",
			"matrix_ex4",
			"matrix_ex5",
			"matrix_ex6",
			"matrix_ex7",
			"matrix_ex8",
			"matrix_ex9",
			"matrix_ex10",
			"matrix_ex11",
			"matrix_ex12",
			"matrix_ex13",
			"matrix_ex14",
			"matrix_ex15",
			"matrix_ex16",
			"matrix_ex17",
			"matrix_ex18"};

const int MATRIX_GAME::m_isLive[NO_LEVELS] = {0,0,0,level_TRANSITION,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const int MATRIX_GAME::m_Buttons[NO_LEVELS] = {6,6,8,level_TRANSITION,8,6,6,6,6,8,8,8,8,8,8,8,8,8,8};
const int MATRIX_GAME::m_Expected[NO_LEVELS] ={4,4,5,level_TRANSITION,3,2,3,0,3,5,0,5,3,0,7,6,7,2,6};


const int MATRIX_GAME::m_layout_questions[NO_LEVELS][8] = {
													{4,4,4,-1,-1,-1,-1,-1},
													{4,4,4,-1,-1,-1,-1,-1},
													{8,9,10,0,1,2,4,5},
													{-1,-1,-1,-1,-1,-1,-1,-1},
													{1,1,1,2,2,2,3,3},
													{6,7,5,-1,-1,-1,-1,-1},
													{0,1,2,-1,-1,-1,-1,-1},
													{0,1,2,-1,-1,-1,-1,-1},
													{4,2,0,-1,-1,-1,-1,-1},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{0,1,2,3,4,5,6,7},
													{8,9,10,11,12,13,14,15},
													{0,1,2,3,4,5,6,7}
													};


const int MATRIX_GAME::m_layout_buttons[NO_LEVELS][8] ={
												{0,1,2,3,4,5,-1,-1},
												{0,1,2,3,4,5,-1,-1},
												{7,1,3,12,8,6,9,13},
												{-1,-1,-1,-1,-1,-1,-1,-1},
												{0,1,2,3,4,5,6,7},
												{0,1,2,5,3,4,-1,-1},
												{2,1,5,3,4,6,-1,-1},
												{3,4,5,6,7,8,-1,-1},
												{0,1,2,3,4,5,-1,-1},
												{2,1,8,9,10,11,12,13},
												{8,9,10,11,12,13,14,15},
												{6,8,2,0,9,10,11,4},
												{8,9,10,11,12,13,14,15},
												{8,9,10,11,12,13,14,15},
												{8,9,10,11,12,13,14,15},
												{8,9,10,11,12,13,14,15},
												{8,9,10,11,12,13,14,15},
												{0,1,2,3,4,5,6,7},
												{8,9,10,11,12,13,14,15}
												};

// ===========================================================================


