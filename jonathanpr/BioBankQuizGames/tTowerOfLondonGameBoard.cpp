//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tTowerOfLondonGameBoard.h"
#include "mess.h"
#include "rand.h"
#include "tmessage.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTowerOfLondonBoard *TowerOfLondonBoard;
ROSETTA *TTowerOfLondonBoard::results = NULL;
#define	PLAY_BACKGROUND	((TColor) 0x005000)
#define	PLAY_BACKGROUND_DONE	((TColor) 0x004000)
#define TIMEOUT_SECONDS 3*60
#define	POPUP_COLOUR			(clMaroon)

//---------------------------------------------------------------------------
__fastcall TTowerOfLondonBoard::TTowerOfLondonBoard(TComponent* Owner) : TForm(Owner)
{
}
// ---------------------------------------------------------------------------

static void setTimeOut(bool Start)
{
	TowerOfLondonBoard->setGameTimeOut(Start);
}

static void setflashTimeOut(bool start)
{
	TowerOfLondonBoard->setFlashTimeOut(start);
}

//---------------------------------------------------------------------------
void __fastcall TTowerOfLondonBoard::FormCreate(TObject *Sender)
{
	abandon = false;
	is_valid = true;
	String image;
	try {
		game = new TOWEROFLONDON_GAME(image_play, PLAY_BACKGROUND, setTimeOut,setflashTimeOut, NextButton,PrevButton);
	}
	catch (Exception &e)
	{
		MESS::error("Failed to initialise cards", MB_OK);
		is_valid = false;
	}
	Top = 0;
	Left = 0;
	Height = Screen->Height;
	Width = Screen->Width;
	margin = 10;
	in_game = false;
	time_t now;
	time(&now);
	RANDOM::randSetSeed((long) now);
}
// ---------------------------------------------------------------------------

void TTowerOfLondonBoard::resetBoard(void)
{
	int h = 57; // HEIGHT OF CONTROL PANELS
	int board_width = Width - (2 * margin);
	// MAIN PANEL
	panel_play->Left = margin;
	panel_play->Top = margin;
	panel_play->Width = board_width;
	panel_play->Height = Height - (3 * margin) - h;
	panel_play->Color = PLAY_BACKGROUND;
	// IMAGE PLAYING AREA
	image_play->Top = 4;
	image_play->Left = 4;
	image_play->Height = panel_play->Height - 12;
	image_play->Width = panel_play->Width - 12;
	TowerOfLondonBoard->Color = clBlack;
	image_play->Canvas->Brush->Color = PLAY_BACKGROUND;
	image_play->Canvas->FillRect(image_play->ClientRect);
	// ABANDON BUTTON
	panel_abandon->Visible = false;
	panel_abandon->Color = this->Color;
	panel_abandon->Height = 41;
	panel_abandon->Top = Height - panel_abandon->Height - margin;
	panel_abandon->Left = margin;
}
//---------------------------------------------------------------------------
void __fastcall TTowerOfLondonBoard::FormDestroy(TObject *Sender)
{
	delete game;
	if (results)
	{
		delete results;
		results = NULL;
	}
}
// ---------------------------------------------------------------------------

std::string TTowerOfLondonBoard::toSTD(String in)
{
	return std::string(AnsiString(in).c_str());
}
// ---------------------------------------------------------------------------

void TTowerOfLondonBoard::extractResults()
{
	if (results)
	{
		delete results;
		results = NULL;
	}
	results = new ROSETTA();

	ROSETTA *g = new ROSETTA();
	System::TDateTime DT = Now();
	String completeDate = DT.FormatString("yyyy-mm-dd") + "T" + DT.FormatString("hh:mm:ss");
	g->setString("dateCompleted", std::string(toSTD(completeDate)));
	g->setString(toSTD(L"dateStarted"), toSTD(game->m_returnDataHeader.dateStarted));
	g->setInt(toSTD(L"abandon"), game->m_returnDataHeader.abandon);
	g->setInt(toSTD(L"totelapsed"), game->m_returnDataHeader.totelapsed);
	g->setInt(toSTD(L"liveelapsed"), game->m_returnDataHeader.liveelapsed);
	g->setInt(toSTD(L"instrelapsed"), game->m_returnDataHeader.instrelapsed);
	g->setInt(toSTD(L"flashlapsed"), game->m_returnDataHeader.flashlapsed);
	g->setInt(toSTD(L"score"), game->m_returnDataHeader.score);
	g->setInt(toSTD(L"noLevels"), game->m_returnDataRow.size());

	results->attachSubRosetta("header", g);
	for (unsigned int i = 0; i < game->m_returnDataRow.size(); i++)
	{
		ROSETTA *l = new ROSETTA();
		TOWEROFLONDON_GAME::returnDataRow *m_CurrentRow = game->m_returnDataRow[i];
		if (!m_CurrentRow->complete)
			 continue; //if not complete it is timedout

		l->setInt(toSTD("level"),i);
		l->setInt(toSTD("game_index"),m_CurrentRow->game_index);
		l->setInt(toSTD("expected"),m_CurrentRow->expected);
		l->setInt(toSTD("selected"),m_CurrentRow->selected);
		l->setInt(toSTD("elapsed"),m_CurrentRow->elapsed);
		std::stringstream ss;
		ss << i;
		g->attachSubRosetta(ss.str(), l);
//		delete l;
	}
}
// ---------------------------------------------------------------------------

bool TTowerOfLondonBoard::playGame(TForm1 *caller, int gameid)
{
	resetBoard();

	if (!game->initGame())
	{
		MESS::bug("Error in playGame random allocation");
		return (false);
	}
	Show();
	panel_abandon->Visible = true;

	caller->Hide();
	game->run();
	while (game->isRunning()) // WAIT FOR END SIGNAL
	{
		Application->ProcessMessages();
	}

	panel_abandon->Visible = false;
	std::stringstream timeString;
	timeString << game->getRunTime();

	extractResults();
  /*	std::string resultString = results->serializeOut();

	if (SaveTextFileDialog->Execute())
	{
		int iFileHandle = FileCreate(SaveTextFileDialog->FileName);
		if (iFileHandle > 0)
			FileWrite(iFileHandle, (void*)AnsiString(resultString.c_str()).c_str (), resultString.length());
		FileClose(iFileHandle);
	}
 */
	caller->Show();
	Hide();
	caller->ShowThanks();
	return (true);
}

//---------------------------------------------------------------------------
void __fastcall TTowerOfLondonBoard::panel_abandonClick(TObject *Sender)
{
	abandonGame();
}
// ---------------------------------------------------------------------------

void TTowerOfLondonBoard::abandonGame(void)
{
	if (mrYes != fm_tmessage->msgYesNo
		("You have not yet completed the task."
		"\n\nAre you certain you wish to abandon this game?" "\n\nYou will not be able to attempt it again.",
		"Please check!", POPUP_COLOUR))
	{
		return;
	}
	game->abandon();
}
//---------------------------------------------------------------------------

void __fastcall TTowerOfLondonBoard::image_playMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	game->handleClick(X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TTowerOfLondonBoard::PrevButtonClick(TObject *Sender)
{
	game->PrevClicked();
}

//---------------------------------------------------------------------------
void __fastcall TTowerOfLondonBoard::NextButtonClick(TObject *Sender)
{
	game->NextClicked();
}

// ---------------------------------------------------------------------------
void TTowerOfLondonBoard::setGameTimeOut(bool start)
{
	if (!start)
		gameTimer->Enabled = false;
	else
	{
		gameTimer->Interval = TIMEOUT_SECONDS * 1000;
		gameTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TTowerOfLondonBoard::gameTimerTimer(TObject *Sender)
{
	gameTimer->Enabled = false;
	game->timeout();
}
// ---------------------------------------------------------------------------
void TTowerOfLondonBoard::setFlashTimeOut(bool start)
{
	if (!start)
		flashTimer->Enabled = false;
	else
	{
		flashTimer->Interval = 100;
		flashTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TTowerOfLondonBoard::flashTimerTimer(TObject *Sender)
{
	game->flashTimeout();
}
//---------------------------------------------------------------------------

