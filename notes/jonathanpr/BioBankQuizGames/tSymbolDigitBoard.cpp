// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tSymbolDigitBoard.h"
#include "mess.h"
#include "rand.h"
#include "tmessage.h"
#include <sstream>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TsymbolDigitBoard *symbolDigitBoard;
ROSETTA *TsymbolDigitBoard::results = NULL;
#define	PLAY_BACKGROUND	((TColor) 0x005000)
#define	PLAY_BACKGROUND_DONE	((TColor) 0x004000)
#define TIMEOUT_SECONDS 60
#define	POPUP_COLOUR			(clMaroon)

// ---------------------------------------------------------------------------
__fastcall TsymbolDigitBoard::TsymbolDigitBoard(TComponent* Owner) : TForm(Owner)
{
}
// ---------------------------------------------------------------------------

static void setTimeOut(bool Start)
{
	symbolDigitBoard->setGameTimeOut(Start);
}

// ---------------------------------------------------------------------------
static void setFlashingTimeOut(bool Start, int Timeout)
{
	symbolDigitBoard->setFlashTimeOut(Start, Timeout);
}

// ---------------------------------------------------------------------------
void __fastcall TsymbolDigitBoard::FormCreate(TObject *Sender)
{
	int i;
	abandon = false;
	is_valid = true;
	String image;
	try
	{
		game = new SYMBOLDIGIT_GAME(image_play, PLAY_BACKGROUND, setTimeOut, setFlashingTimeOut, NextButton);
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

void TsymbolDigitBoard::resetBoard(void)
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
	symbolDigitBoard->Color = clBlack;
	image_play->Canvas->Brush->Color = PLAY_BACKGROUND;
	image_play->Canvas->FillRect(image_play->ClientRect);
	// ABANDON BUTTON
	panel_abandon->Visible = false;
	panel_abandon->Color = this->Color;
	panel_abandon->Height = 41;
	panel_abandon->Top = Height - panel_abandon->Height - margin;
	panel_abandon->Left = margin;
}
// ---------------------------------------------------------------------------

void __fastcall TsymbolDigitBoard::FormDestroy(TObject *Sender)
{
	delete game;
	if (results)
	{
		delete results;
		results = NULL;
	}
}
// ---------------------------------------------------------------------------

std::string TsymbolDigitBoard::toSTD(String in)
{
	return std::string(AnsiString(in).c_str());
}
// ---------------------------------------------------------------------------

void TsymbolDigitBoard::extractResults()
{
	if (results)
	{
		delete results;
		results = NULL;
	}
	results = new ROSETTA();
	ROSETTA *g = new ROSETTA();
	g->setString(std::string("partid"), toSTD(game->m_returnDataHeader.partid));
	g->setString("sessionid", toSTD(game->m_returnDataHeader.sessionid));
	g->setString("sectionid", toSTD(game->m_returnDataHeader.sectionid));

	System::TDateTime DT = Now();
	String completeDate = DT.FormatString("yyyy-mm-dd") + "T" + DT.FormatString("hh:mm:ss");
	g->setString("dateCompleted", std::string(toSTD(completeDate)));
	results->attachSubRosetta("header", g);

	g = new ROSETTA();
	g->setString(toSTD(L"dateStarted"), toSTD(game->m_returnDataHeader.dateStarted));
	g->setInt(toSTD(L"abandon"), game->m_returnDataHeader.abandon);
	g->setInt(toSTD(L"totelapsed"), game->m_returnDataHeader.totelapsed);
	g->setInt(toSTD(L"liveelapsed"), game->m_returnDataHeader.liveelapsed);
	g->setInt(toSTD(L"instrelapsed"), game->m_returnDataHeader.instrelapsed);
	g->setInt(toSTD(L"attempted"), game->m_returnDataHeader.levels);
	g->setInt(toSTD(L"correct"), game->m_returnDataHeader.score);
	g->setInt(toSTD(L"startrow"), game->m_returnDataHeader.startrow);
	g->setInt(toSTD(L"pracelapsed"), game->m_returnDataHeader.pracelapsed);

	for (unsigned int i = 0; i < game->m_returnDataRow.size(); i++)
	{
		SYMBOLDIGIT_GAME::returnDataRow *m_CurrentRow = game->m_returnDataRow[i];

		if (!m_CurrentRow->complete)
			 continue;

		ROSETTA *l = new ROSETTA();

		// attempts start from 1
		l->setInt(toSTD(L"levelnum"),m_CurrentRow->trial_number);
		l->setInt(toSTD(L"index"),m_CurrentRow->trial_component);
		l->setInt(toSTD(L"attempt"),m_CurrentRow->attempt);

		l->setInt(toSTD(L"elapsed"), m_CurrentRow->elapsed);
		l->setInt(toSTD(L"symbol"), m_CurrentRow->symbol);
		l->setString(toSTD(L"wanted"), toSTD(m_CurrentRow->expected));
		l->setString(toSTD(L"entered"), toSTD(m_CurrentRow->selected));
		l->setInt(toSTD(L"valid"), m_CurrentRow->valid);
 //		g->setInt(toSTD("rsi_" + Combined), m_CurrentRow->rsi);

		std::stringstream ss;
		ss << i;
		g->attachSubRosetta(ss.str(), l);
//		delete l;
	}
	results->attachSubRosetta("qidresp", g);
}
// ---------------------------------------------------------------------------

bool TsymbolDigitBoard::playGame(TForm *caller, int gameid)
{
	resetBoard();

	if (!game->initGame()) {
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
	// current_layout->duration = game->getRunTime();

	panel_abandon->Visible = false;
	std::stringstream timeString;
	timeString << game->getRunTime();
 /*
	if (!game->wasAbandoned())
		fm_tmessage->msgOk("Congratulations!\n\nYou completed the test in " +
		timeString.str() + " deci-seconds " + "\n\nWell done.", "You win",
		POPUP_COLOUR);
  */
	extractResults();
 /*	std::string resultString = results->serializeOut();

	if (SaveTextFileDialog->Execute())
	{
		int iFileHandle = FileCreate(SaveTextFileDialog->FileName);

		if (iFileHandle > 0)
		{
			FileWrite(iFileHandle, (void*)AnsiString(resultString.c_str()).c_str(), resultString.length());
		}
		FileClose(iFileHandle);
	}
   */
	caller->Show();
	Hide();
	return (true);
}
// ---------------------------------------------------------------------------

void __fastcall TsymbolDigitBoard::panel_abandonClick(TObject *Sender)
{
	abandonGame();
}
// ---------------------------------------------------------------------------

void TsymbolDigitBoard::abandonGame(void)
{
	if (mrYes != fm_tmessage->msgYesNo
		("You have not yet completed the task."
		"\n\nAre you certain you wish to abandon this game?" "\n\nYou will not be able to attempt it again.",
		"Please check!", POPUP_COLOUR)) {
		return;
	}
	game->abandon();
}
// ---------------------------------------------------------------------------

void __fastcall TsymbolDigitBoard::image_playMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	game->handleClick(X, Y);
}

// ---------------------------------------------------------------------------
void __fastcall TsymbolDigitBoard::gameTimerTimer(TObject *Sender)
{
	gameTimer->Enabled = false;
	game->timeout();
}
// ---------------------------------------------------------------------------

void __fastcall TsymbolDigitBoard::flashTimerTimer(TObject *Sender)
{
	flashTimer->Enabled = false;
	game->flashTimeout();
}

// ---------------------------------------------------------------------------
void TsymbolDigitBoard::setGameTimeOut(bool start)
{
	if (!start)
		gameTimer->Enabled = false;
	else
	{
		gameTimer->Interval = TIMEOUT_SECONDS * 1000;
		gameTimer->Enabled = true;
	}
}
// ---------------------------------------------------------------------------

void TsymbolDigitBoard::setFlashTimeOut(bool start, int timeout)
{
	if (!start)
		flashTimer->Enabled = false;
	else
	{
		flashTimer->Interval = timeout;
		flashTimer->Enabled = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TsymbolDigitBoard::NextButtonClick(TObject *Sender)
{
	game->NextClicked();
}
// ---------------------------------------------------------------------------
