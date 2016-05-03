// 3 mins to complete as many as possible or complete 18
// elapsed times in deciseconds  (1/10 secs)

// ---------------------------------------------------------------------------

#include <vcl.h>
#include <sstream>
#include <iostream>  //cout

#include "rand.h"
#include "System.DateUtils.hpp"
#include "TowerOfLondonGame.h"
#include "theTrail.h"
#define	PLAY_BACKGROUND	((TColor) 0xffffff)
#define PLAY_BOARD ((TColor) 0x495585)
#define	USERINPUT_WHITE	((TColor) 0xFFFFFF)
#define USERINPUT_NUMBERPAD_GRAY ((TColor) 0xCCCCCC)
#define	USERINPUT_BORDER	((TColor) 0x6F5F00)

#define USERINPUT_NUMBERPAD_DISABLED ((TColor) 0xCCCCCC)
#define	USERINPUT_BORDER_DISABLED	((TColor) 0xDDDDDD)

#define RED_COLOUR_BALL 1
#define GREEN_COLOUR_BALL 2
#define BLUE_COLOUR_BALL 3

// ===========================================================================
TOWEROFLONDON_GAME::TOWEROFLONDON_GAME(TImage *board, const TColor background,void(* setTimeOut)(bool),void(* setFlashTimeOut)(bool), TButton *NextButton, TButton *PrevButton)
	: m_NextButton(NextButton),m_PrevButton(PrevButton), setTimeOutFunction(setTimeOut), setFlashTimeOutFunction(setFlashTimeOut)
{
	m_returnDataHeader.flashlapsed = 0;
	m_playing_board = board;
	m_CurrentRow = NULL;
	m_DRAW_paddingX = -1;
	m_levelData = NULL;

	ajust_boardHeight = 0;
	ajust_paddingBetweenBoards = 0;
	ajust_offsetFromScreenTop = 0;
	ajust_widthofboard = 0;

	m_flashCounter = 0;
}

// ---------------------------------------------------------------------------
TOWEROFLONDON_GAME::~TOWEROFLONDON_GAME(VOID)
{
	if (m_levelData)
	{
		delete m_levelData;
		m_levelData = NULL;
	}
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
void TOWEROFLONDON_GAME::SetUpConsts()
{
	int windowHeight = m_playing_board->Height + ajust_paddingBetweenBoards;

	m_DRAW_paddingX = 250 + ajust_widthofboard;
	m_DRAW_paddingY = 150 + ajust_boardHeight;
	m_DRAW_board1_Top = m_DRAW_paddingY;
	m_DRAW_board1_Bottom = (windowHeight / 2) - m_DRAW_paddingY;
	m_DRAW_board2_Top = m_DRAW_paddingY + m_DRAW_board1_Bottom;
	m_DRAW_board2_Bottom = windowHeight - m_DRAW_paddingY;
	m_DRAW_board_Left = m_DRAW_paddingX;
	m_DRAW_board_Right = m_playing_board->Width - m_DRAW_paddingX;
	m_DRAW_board_Width = m_DRAW_board_Right - m_DRAW_board_Left;
	m_DRAW_board_Height = m_DRAW_board1_Bottom - m_DRAW_board1_Top;
	m_DRAW_unitHight = m_DRAW_board_Height / 3;
	m_DRAW_blockWidth = 30;
	m_DRAW_halfBlockWidth = m_DRAW_blockWidth / 2;
	m_DRAW_middle = m_DRAW_board_Width / 2 + m_DRAW_paddingX;
	m_DRAW_rightpos = m_DRAW_middle + (m_DRAW_board_Right - m_DRAW_middle) / 2;
	m_DRAW_leftpos = m_DRAW_board_Left + (m_DRAW_middle - m_DRAW_board_Left) / 2;

	m_DRAW_board1_Top += ajust_offsetFromScreenTop;
	m_DRAW_board1_Bottom += ajust_offsetFromScreenTop;
	m_DRAW_board2_Top += ajust_offsetFromScreenTop;
	m_DRAW_board2_Bottom += ajust_offsetFromScreenTop;
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::NewSaveRow()
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
void TOWEROFLONDON_GAME::drawBlock(String Image, TColor PenCol, TColor BrushCol,int PosX, int PosY)
{
	const int Size = getGamePadSize();
	const int padding = getGamePadPadding();

	m_playing_board->Canvas->Pen->Width = 4.0;
	m_playing_board->Canvas->Pen->Color = PenCol;
	m_playing_board->Canvas->Brush->Color = BrushCol;
	m_playing_board->Canvas->Rectangle(PosX+padding, PosY+padding, PosX + Size-padding, PosY + Size-padding);
	m_playing_board->Canvas->Font->Size = 20;
	m_playing_board->Canvas->Font->Name = "Arial Black";

	if (Image.Length() > 0)
	{
		TSize textSize = m_playing_board->Canvas->TextExtent(Image);
		m_playing_board->Canvas->TextOutW(PosX + (Size / 2) - (textSize.Width / 2),PosY + (Size / 2) - (textSize.Height / 2), Image);
	}
	m_playing_board->Canvas->Font->Name = "Arial";
	m_playing_board->Canvas->Pen->Width = 1.0;
	m_playing_board->Canvas->Pen->Color = USERINPUT_BORDER;
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawGameText()
{
	showButtons(false);
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	m_playing_board->Canvas->Font->Name = "Arial";
	m_playing_board->Canvas->Font->Size = 15;
	TSize textSize = m_playing_board->Canvas->TextExtent(m_inGameText[0]);

	const int Size = getGamePadSize();
	int YPos = getGamePadY() - Size - Size/2;
	m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), YPos, m_inGameText[0]);
}
// ---------------------------------------------------------------------------

int TOWEROFLONDON_GAME::getGamePadX()
{
	return (m_playing_board->Width / 2) - (getGamePadSize() * 3);
}
// ---------------------------------------------------------------------------

int TOWEROFLONDON_GAME::getGamePadY()
{
	return m_playing_board->Height - getGamePadSize();
}
// ---------------------------------------------------------------------------

int TOWEROFLONDON_GAME::getGamePadSize()
{
	return 80;
}
// ---------------------------------------------------------------------------
int TOWEROFLONDON_GAME::getGamePadPadding()
{
	return 10;
}
// ---------------------------------------------------------------------------

void TOWEROFLONDON_GAME::NumberPadDisabled()
{
	const int Size = getGamePadSize();
	int XPos = getGamePadX();
	int YPos = getGamePadY() - Size;

	drawBlock(String("1"), USERINPUT_BORDER_DISABLED, USERINPUT_NUMBERPAD_DISABLED, XPos, YPos);
	XPos += Size;
	drawBlock(String("2"), USERINPUT_BORDER_DISABLED, USERINPUT_NUMBERPAD_DISABLED, XPos, YPos);
	XPos += Size;
	drawBlock(String("3"), USERINPUT_BORDER_DISABLED, USERINPUT_NUMBERPAD_DISABLED, XPos, YPos);
	XPos += Size;
	drawBlock(String("4"), USERINPUT_BORDER_DISABLED, USERINPUT_NUMBERPAD_DISABLED, XPos, YPos);
	XPos += Size;
	drawBlock(String("5"), USERINPUT_BORDER_DISABLED, USERINPUT_NUMBERPAD_DISABLED, XPos, YPos);
	XPos += Size;
	drawBlock(String("6"), USERINPUT_BORDER_DISABLED, USERINPUT_NUMBERPAD_DISABLED, XPos, YPos);
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawNumberPad()
{
	const int Size = getGamePadSize();
	int XPos = getGamePadX();
	int YPos = getGamePadY() - Size;

	drawBlock(String("1"), USERINPUT_BORDER, USERINPUT_NUMBERPAD_GRAY, XPos, YPos);
	XPos += Size;
	drawBlock(String("2"), USERINPUT_BORDER, USERINPUT_NUMBERPAD_GRAY, XPos, YPos);
	XPos += Size;
	drawBlock(String("3"), USERINPUT_BORDER, USERINPUT_NUMBERPAD_GRAY, XPos, YPos);
	XPos += Size;
	drawBlock(String("4"), USERINPUT_BORDER, USERINPUT_NUMBERPAD_GRAY, XPos, YPos);
	XPos += Size;
	drawBlock(String("5"), USERINPUT_BORDER, USERINPUT_NUMBERPAD_GRAY, XPos, YPos);
	XPos += Size;
	drawBlock(String("6"), USERINPUT_BORDER, USERINPUT_NUMBERPAD_GRAY, XPos, YPos);
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawNumberPadFlash()
{
	//clear the discs half way though the button flash
	if ((m_GameID >= 0) && (m_flashCounter == 3))
	{
		m_toparray[0]=m_toparray[1]=m_toparray[2]=0;
		m_toparray[3]=m_toparray[4]=m_toparray[5]=0;
		drawGameBoard();
	}
	NumberPadDisabled();

	TColor ButtonCol = USERINPUT_NUMBERPAD_GRAY;
// 	if (m_flashCounter%2==0)
		ButtonCol = USERINPUT_WHITE;

	const int Size = getGamePadSize();
	int XPos = getGamePadX();
	int YPos = getGamePadY() - Size;
	XPos += Size * (m_iuserkeyinput-1);

	std::stringstream ss;
	ss << m_iuserkeyinput;
	drawBlock(String(ss.str().c_str()), USERINPUT_BORDER_DISABLED, ButtonCol, XPos, YPos);
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawBall(int Floor_posY, int Ball, int Pos)
{
	int ballSize = m_DRAW_unitHight - 5; //5 pixels smaller then each poles section, so we see the ends poking through
	if (Ball == 0) // 0 emtpy position;
		return;

	m_playing_board->Canvas->Pen->Width = 2.0;

	if (Ball == 1)
		m_playing_board->Canvas->Brush->Color = clBlack;
	else if (Ball == 2)
		m_playing_board->Canvas->Brush->Color = clWhite;
	else
		m_playing_board->Canvas->Brush->Color = clYellow;

	int posX, posY;
	int BoardFloor = Floor_posY - m_DRAW_blockWidth;
	// LEFT
	if (Pos == 0) // top left
	{
		posX = m_DRAW_leftpos;
		posY = BoardFloor - ballSize - ballSize;
	}
	else if (Pos == 1) // middle left
	{
		posX = m_DRAW_leftpos;
		posY = BoardFloor - ballSize;
	}
	else if (Pos == 2) // bottomleft
	{
		posX = m_DRAW_leftpos;
		posY = BoardFloor;
	}
	// middle
	else if (Pos == 3) // middle top
	{
		posX = m_DRAW_middle;
		posY = BoardFloor - ballSize;
	}
	else if (Pos == 4) // middle bottom
	{
		posX = m_DRAW_middle;
		posY = BoardFloor;
	}
	// right
	else if (Pos == 5) // middle bottom
	{
		posX = m_DRAW_rightpos;
		posY = BoardFloor;
	}
	m_playing_board->Canvas->RoundRect(posX - ballSize, posY, posX + ballSize,posY - ballSize, ballSize / 2, ballSize / 2);
	m_playing_board->Canvas->Pen->Width = 1.0;
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawExampleBoard()
{
	SetUpConsts();

	m_playing_board->Canvas->Font->Size = 15;
	drawBoard(m_DRAW_board1_Bottom);
	for (int i = 0; i < 6; i++)
		drawBall(m_DRAW_board1_Bottom, m_toparray[i], i);

	drawBoard(m_DRAW_board2_Bottom);
	for (int i = 0; i < 6; i++)
		drawBall(m_DRAW_board2_Bottom, m_bottomarray[i], i);
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawGameBoard()
{
	SetUpConsts();
	m_playing_board->Canvas->Pen->Width = 1.0;
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	m_playing_board->Canvas->FillRect(m_playing_board->ClientRect);

	drawBoard(m_DRAW_board1_Bottom);
	for (int i = 0; i < 6; i++)
		drawBall(m_DRAW_board1_Bottom, m_toparray[i], i);

	drawBoard(m_DRAW_board2_Bottom);
	for (int i = 0; i < 6; i++)
		drawBall(m_DRAW_board2_Bottom, m_bottomarray[i], i);

//	if (!((m_NextButton->Visible) && (m_GameID == -6)))
//		drawNumberPad();
	drawGameText();

	m_playing_board->Canvas->Font->Size = 40;
	m_playing_board->Canvas->TextOutW(200, 130 + ajust_offsetFromScreenTop, "A");
	m_playing_board->Canvas->TextOutW(200, 470 + ajust_offsetFromScreenTop, "B");
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::drawBoard(int WhereBase)
{
	m_playing_board->Canvas->Brush->Color = PLAY_BOARD;

	int board_Bottom = WhereBase;
	// base
	int Left = m_DRAW_board_Left;
	int Right = m_DRAW_board_Right;
	int Top = board_Bottom - m_DRAW_blockWidth;
	int Bottom = board_Bottom;
	m_playing_board->Canvas->Rectangle(Left, Top, Right, Bottom);

	// middle 2
	Left = m_DRAW_middle - m_DRAW_halfBlockWidth;
	Right = m_DRAW_middle + m_DRAW_halfBlockWidth;
	Top = board_Bottom - m_DRAW_blockWidth - (m_DRAW_unitHight * 2);
	Bottom = board_Bottom;
	m_playing_board->Canvas->Rectangle(Left, Top, Right, Bottom);

	// left 3
	Left = m_DRAW_leftpos - m_DRAW_halfBlockWidth;
	Right = m_DRAW_leftpos + m_DRAW_halfBlockWidth;
	Top = board_Bottom - m_DRAW_blockWidth - (m_DRAW_unitHight * 3);
	Bottom = board_Bottom;
	m_playing_board->Canvas->Rectangle(Left, Top, Right, Bottom);

	// right 1
	Left = m_DRAW_rightpos - m_DRAW_halfBlockWidth;
	Right = m_DRAW_rightpos + m_DRAW_halfBlockWidth;
	Top = board_Bottom - m_DRAW_blockWidth - (m_DRAW_unitHight);
	Bottom = board_Bottom;
	m_playing_board->Canvas->Rectangle(Left, Top, Right, Bottom);
}
// ---------------------------------------------------------------------------

void TOWEROFLONDON_GAME::showButtons(bool show)
{
	if (!show)
	{
		m_NextButton->Hide();
		m_PrevButton->Hide();
		return;
	}

	m_playing_board->Canvas->Font->Size = 15;
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	int YPos = getGamePadY();// - getGameSize();

	if (m_GameID == START_LEVEL)
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
void TOWEROFLONDON_GAME::doIntoTextScreen()
{
	m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
	m_playing_board->Canvas->FillRect(m_playing_board->ClientRect);
	m_playing_board->Canvas->Font->Name = "Arial";

	if (m_GameID == -6)
	{
		ajust_boardHeight = -110;
		ajust_paddingBetweenBoards = -405;
		ajust_offsetFromScreenTop = 135;

		m_toparray[0] = 0;
		m_toparray[1] = 0;
		m_toparray[2] = RED_COLOUR_BALL;
		m_toparray[3] = 0;
		m_toparray[4] = BLUE_COLOUR_BALL;
		m_toparray[5] = GREEN_COLOUR_BALL;

		m_bottomarray[0] = 0;
		m_bottomarray[1] = 0;
		m_bottomarray[2] = RED_COLOUR_BALL;
		m_bottomarray[3] = GREEN_COLOUR_BALL;
		m_bottomarray[4] = BLUE_COLOUR_BALL;
		m_bottomarray[5] = 0;

		m_playing_board->Canvas->Font->Size = 40;
		m_playing_board->Canvas->TextOutW(200, 100 + ajust_offsetFromScreenTop, "A");
		m_playing_board->Canvas->TextOutW(200, 350 + ajust_offsetFromScreenTop, "B");

		drawExampleBoard();
		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		m_playing_board->Canvas->Font->Size = 35;
		int LineY = 25;
		TSize textSize = m_playing_board->Canvas->TextExtent(m_introText_7[0]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_7[0]);

		m_playing_board->Canvas->Font->Size = 15;
		LineY += 60;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_7[1]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_7[1]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_7[2]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_7[2]);

		LineY += 550;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_7[3]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_7[3]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_7[4]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_7[4]);

		int YPos = getGamePadY();
		textSize = m_playing_board->Canvas->TextExtent(m_introText_7[5]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), YPos-30, m_introText_7[5]);

		showButtons(true);
	}
	else if (m_GameID == -5)
	{
		m_playing_board->Canvas->Font->Size = 40;
		m_playing_board->Canvas->TextOutW(200, 100 + ajust_offsetFromScreenTop, "A");
		m_playing_board->Canvas->TextOutW(200, 350 + ajust_offsetFromScreenTop, "B");
		drawExampleBoard();
		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		int LineY = 50;
		m_playing_board->Canvas->Font->Size = 15;
		TSize textSize = m_playing_board->Canvas->TextExtent(m_introText_6[0]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[0]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[1]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[1]);

		LineY += 550;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[2]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[2]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[3]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[3]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[4]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[4]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[5]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[5]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[6]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_6[6]);

		int YPos = getGamePadY();
		textSize = m_playing_board->Canvas->TextExtent(m_introText_6[7]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), YPos-30, m_introText_6[7]);

		showButtons(true);
	}
	else if (m_GameID == -4)
	{
		m_playing_board->Canvas->Font->Size = 40;
		m_playing_board->Canvas->TextOutW(200, 100 + ajust_offsetFromScreenTop, "A");
		m_playing_board->Canvas->TextOutW(200, 350 + ajust_offsetFromScreenTop, "B");
		drawExampleBoard();
		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		int LineY = 50;
		m_playing_board->Canvas->Font->Size = 15;
		TSize textSize = m_playing_board->Canvas->TextExtent(m_introText_5[0]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_5[0]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_5[1]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_5[1]);
		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_5[2]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_5[2]);

		LineY += 550;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_5[3]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_5[3]);

		int YPos = getGamePadY();
		textSize = m_playing_board->Canvas->TextExtent(m_introText_5[4]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), YPos-30, m_introText_5[4]);

//DRAW RED ARROW
		m_playing_board->Canvas->Pen->Width = 7.0;
		m_playing_board->Canvas->Pen->Color = clBlack;
		m_playing_board->Canvas->MoveTo(685,500);
		m_playing_board->Canvas->LineTo(780,555);
		m_playing_board->Canvas->MoveTo(685+13,500+25);
		m_playing_board->Canvas->LineTo(685,500);
		m_playing_board->Canvas->MoveTo(685+24,500-5);
		m_playing_board->Canvas->LineTo(685,500);

		m_playing_board->Canvas->Pen->Width = 5.0;
		m_playing_board->Canvas->Pen->Color = clPurple;
		m_playing_board->Canvas->MoveTo(685,500);
		m_playing_board->Canvas->LineTo(780,555);
		m_playing_board->Canvas->MoveTo(685+13,500+25);
		m_playing_board->Canvas->LineTo(685,500);
		m_playing_board->Canvas->MoveTo(685+24,500-5);
		m_playing_board->Canvas->LineTo(685,500);

 		m_playing_board->Canvas->Pen->Width = 1.0;
		m_playing_board->Canvas->Pen->Color = USERINPUT_BORDER;
		showButtons(true);
	}
	else if (m_GameID == -3)
	{
		m_toparray[0] = 0;
		m_toparray[1] = BLUE_COLOUR_BALL;
		m_toparray[2] = GREEN_COLOUR_BALL;
		m_toparray[3] = 0;
		m_toparray[4] = RED_COLOUR_BALL;
		m_toparray[5] = 0;

		m_bottomarray[0] = 0;
		m_bottomarray[1] = RED_COLOUR_BALL;
		m_bottomarray[2] = GREEN_COLOUR_BALL;
		m_bottomarray[3] = 0;
		m_bottomarray[4] = 0;
		m_bottomarray[5] = BLUE_COLOUR_BALL;

		ajust_boardHeight = -105;
		ajust_paddingBetweenBoards = -220;
		ajust_offsetFromScreenTop = 35;

		m_playing_board->Canvas->Font->Size = 40;
		m_playing_board->Canvas->TextOutW(200, 100 + ajust_offsetFromScreenTop+30, "A");
		m_playing_board->Canvas->TextOutW(200, 350 + ajust_offsetFromScreenTop+130, "B");
		drawExampleBoard();
		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		const int Size = getGamePadSize();
		int LineY = getGamePadY() - Size - Size/2;

		m_playing_board->Canvas->Font->Size = 15;
		TSize textSize = m_playing_board->Canvas->TextExtent(m_introText_4[0]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_4[0]);

		drawNumberPad();
		showButtons(false);
	}
	else if (m_GameID == -2)
	{
		m_toparray[0] = 0;
		m_toparray[1] = BLUE_COLOUR_BALL;
		m_toparray[2] = GREEN_COLOUR_BALL;
		m_toparray[3] = 0;
		m_toparray[4] = RED_COLOUR_BALL;
		m_toparray[5] = 0;

		m_bottomarray[0] = 0;
		m_bottomarray[1] = BLUE_COLOUR_BALL;
		m_bottomarray[2] = GREEN_COLOUR_BALL;
		m_bottomarray[3] = 0;
		m_bottomarray[4] = RED_COLOUR_BALL;
		m_bottomarray[5] = 0;

		ajust_boardHeight = -85;
		ajust_paddingBetweenBoards = -370;
		ajust_offsetFromScreenTop = 45;
		ajust_widthofboard = 0;

		SetUpConsts();

		m_playing_board->Canvas->Font->Size = 40;
		m_playing_board->Canvas->TextOutW(200, 100 + ajust_offsetFromScreenTop, "A");
		m_playing_board->Canvas->Font->Size = 20;
		m_playing_board->Canvas->TextOutW(300, 300 + ajust_offsetFromScreenTop, "1");

		m_playing_board->Canvas->Font->Size = 15;
		drawBoard(m_DRAW_board1_Bottom);
		for (int i = 0; i < 6; i++)
			drawBall(m_DRAW_board1_Bottom, m_toparray[i], i);

		ajust_boardHeight = -85;
		ajust_paddingBetweenBoards = -450;
		ajust_offsetFromScreenTop = 15;
		ajust_widthofboard = 90;

		SetUpConsts();

		drawBoard(m_DRAW_board2_Bottom);
		for (int i = 0; i < 6; i++)
			drawBall(m_DRAW_board2_Bottom, m_bottomarray[i], i);

		ajust_boardHeight = -85;
		ajust_paddingBetweenBoards = -370;
		ajust_offsetFromScreenTop = 565;
		ajust_widthofboard = 0;

		SetUpConsts();
		m_bottomarray[0] = 0;
		m_bottomarray[1] = 0;
		m_bottomarray[2] = GREEN_COLOUR_BALL;
		m_bottomarray[3] = 0;
		m_bottomarray[4] = RED_COLOUR_BALL;
		m_bottomarray[5] = BLUE_COLOUR_BALL;

		m_toparray[0] = 0;
		m_toparray[1] = RED_COLOUR_BALL;
		m_toparray[2] = GREEN_COLOUR_BALL;
		m_toparray[3] = 0;
		m_toparray[4] = 0;
		m_toparray[5] = BLUE_COLOUR_BALL;

 		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;
		m_playing_board->Canvas->Font->Size = 20;
		m_playing_board->Canvas->TextOutW(300, -75 + ajust_offsetFromScreenTop, "2");
		m_playing_board->Canvas->Font->Size = 40;
		m_playing_board->Canvas->TextOutW(200, 75 + ajust_offsetFromScreenTop, "B");

		m_playing_board->Canvas->Font->Size = 15;
		drawBoard(m_DRAW_board1_Bottom);
		for (int i = 0; i < 6; i++)
			drawBall(m_DRAW_board1_Bottom, m_toparray[i], i);


		ajust_boardHeight = -85;
		ajust_paddingBetweenBoards = -450;
		ajust_offsetFromScreenTop = 155;
		ajust_widthofboard = 90;

		SetUpConsts();

		drawBoard(m_DRAW_board2_Bottom);
		for (int i = 0; i < 6; i++)
			drawBall(m_DRAW_board2_Bottom, m_bottomarray[i], i);

		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		std::stringstream ss;
		ss << stdstring(m_introText_3[0]) << m_iuserkeyinput;
		String resultText = ss.str().c_str();
		int LineY = 50;
		m_playing_board->Canvas->Font->Size = 15;
		TSize textSize = m_playing_board->Canvas->TextExtent(resultText);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, resultText);

		LineY += 25;
		textSize = m_playing_board->Canvas->TextExtent(m_introText_3[1]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_3[1]);

		int YPos = getGamePadY();
		textSize = m_playing_board->Canvas->TextExtent(m_introText_3[2]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), YPos-30, m_introText_3[2]);

//DRAW RED ARROW BLUE
		m_playing_board->Canvas->Pen->Width = 7.0;
		m_playing_board->Canvas->Pen->Color = clBlack;
		m_playing_board->Canvas->MoveTo(516,349);
		m_playing_board->Canvas->LineTo(735,349);
		m_playing_board->Canvas->MoveTo(735-20,349-10);
		m_playing_board->Canvas->LineTo(735,349);
		m_playing_board->Canvas->MoveTo(735-20,349+10);
		m_playing_board->Canvas->LineTo(735,349);

		m_playing_board->Canvas->Pen->Width = 5.0;
		m_playing_board->Canvas->Pen->Color = clPurple;
		m_playing_board->Canvas->MoveTo(516,349);
		m_playing_board->Canvas->LineTo(735,349);
		m_playing_board->Canvas->MoveTo(735-20,349-10);
		m_playing_board->Canvas->LineTo(735,349);
		m_playing_board->Canvas->MoveTo(735-20,349+10);
		m_playing_board->Canvas->LineTo(735,349);


//DRAW RED ARRAY
 		m_playing_board->Canvas->Pen->Width = 7.0;
		m_playing_board->Canvas->Pen->Color = clBlack;
		m_playing_board->Canvas->MoveTo(516,480);
		m_playing_board->Canvas->LineTo(590,505);
		m_playing_board->Canvas->MoveTo(516+16,480-5);
		m_playing_board->Canvas->LineTo(516,480);
		m_playing_board->Canvas->MoveTo(516+10,480+15);
		m_playing_board->Canvas->LineTo(516,480);

 		m_playing_board->Canvas->Pen->Width = 5.0;
		m_playing_board->Canvas->Pen->Color = clPurple;
		m_playing_board->Canvas->MoveTo(516,480);
		m_playing_board->Canvas->LineTo(590,505);
		m_playing_board->Canvas->MoveTo(516+16,480-5);
		m_playing_board->Canvas->LineTo(516,480);
		m_playing_board->Canvas->MoveTo(516+10,480+15);
		m_playing_board->Canvas->LineTo(516,480);

		m_playing_board->Canvas->Pen->Width = 1.0;
		m_playing_board->Canvas->Pen->Color = USERINPUT_BORDER;

		showButtons(true);
	}
	else if (m_GameID == -1)
	{
		m_playing_board->Canvas->Brush->Color = PLAY_BACKGROUND;

		int LineY = 450;
		m_playing_board->Canvas->Font->Size = 15;
		TSize textSize = m_playing_board->Canvas->TextExtent(m_introText_2[0]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), LineY, m_introText_2[0]);

		int YPos = getGamePadY();
		textSize = m_playing_board->Canvas->TextExtent(m_introText_2[1]);
		m_playing_board->Canvas->TextOutW((m_playing_board->Width / 2) - (textSize.Width / 2), YPos-30, m_introText_2[1]);
		showButtons(true);
	}
}
// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::timeout()
{
	m_timedOut = true;
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::flashTimeout()
{
	if (m_disabledCounter >= 0)
	{
		ignore_click = true;

		if (m_disabledCounter == 0)
			NumberPadDisabled();

		if (m_disabledCounter >= 4)
		{
			m_disabledCounter = -1;
			setFlashTimeOutFunction(false);
			drawNumberPad();
			ignore_click = false;
		}
		else
			m_disabledCounter++;
	}
	else
	{
//		if (m_flashCounter == 0)
//			NumberPadDisabled(); //clear the boarder.

		if (m_flashCounter < 10)
		{
			drawNumberPadFlash();
		}
		else
		{
			setFlashTimeOutFunction(false);
			initGame(m_GameID + 1);
			if (m_GameID <=0)
				ignore_click = false;
		}
		m_flashCounter++;
	}
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::initalise()
{
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
	m_levelData = levelData::getRandomiseWithFixedDifficulty();

	m_iuserkeyinput = -1; // clear user input history
	m_score = 0;
	m_londonstarted_ts = Now();
	NewSaveRow();
}

// ---------------------------------------------------------------------------
bool TOWEROFLONDON_GAME::initGame(const int gameid)
{
	m_GameID = gameid;
	if (m_GameID < 0)
	{
		if (m_GameID == START_LEVEL)
			initalise(); // set up inital game state
		doIntoTextScreen();
		return true;
	}

	if (m_GameID == 0)
	{
		// help is finished..
		System::TDateTime timeNow = Now();
		m_returnDataHeader.instrelapsed = milliSecondsToDeciSeconds(timeNow, m_londonstarted_ts);
		for (int i = 0; i < 6; i++)
			m_bottomarray[i] = m_TOL_wantedGameData[i];
	}

	//m_GAMEID is the level index
	m_NextButton->Hide();
	if (m_GameID == 0)
		setTimeOutFunction(true); // set timeout 180mins for the real thing

	int index = m_levelData->getGameLevel(m_GameID);
	for (int i = 0; i < 6; i++)
		m_toparray[i] = m_TOLgameData[index][i];

//size the boards
	ajust_boardHeight = -105;
	ajust_paddingBetweenBoards = -220;
	ajust_offsetFromScreenTop = 35;
	ajust_widthofboard = 0;

	drawGameBoard(); // redraw old trail, updating text.
	m_iuserkeyinput = -1; // clear user input history

	System::TDateTime timeNow = Now();

	if (m_GameID > 0)
		m_returnDataHeader.flashlapsed +=  milliSecondsToDeciSeconds(timeNow,m_flashStart_ts);

	if (m_GameID == 0)
		m_liveGame_ts = timeNow;

	m_levelStart_ts = timeNow;

    if (m_GameID >= 0)
	{
		m_disabledCounter = 0;  //this triggers the 1 second no input
		setFlashTimeOutFunction(true);
	}
	return true;
}
//----------------------------------------------------------------------------

void TOWEROFLONDON_GAME::NextClicked()
{
	initGame(m_GameID+1);
}

//----------------------------------------------------------------------------
void TOWEROFLONDON_GAME::PrevClicked()
{
	initGame(m_GameID-1);
}

//----------------------------------------------------------------------------
void TOWEROFLONDON_GAME::fillHeaderData()
{
	System::TDateTime timeNow = Now();
	end_level = clock();
	m_returnDataHeader.liveelapsed = milliSecondsToDeciSeconds(timeNow, m_liveGame_ts);
	m_returnDataHeader.totelapsed = milliSecondsToDeciSeconds(timeNow, m_londonstarted_ts);
	m_returnDataHeader.score = m_score;
	m_returnDataHeader.abandon = false;
	m_returnDataHeader.timedout = m_timedOut;
	String startDate = m_londonstarted_ts.FormatString("yyyy-mm-dd") + "T" + m_londonstarted_ts.FormatString("hh:mm:ss");
	m_returnDataHeader.dateStarted=startDate; //L"2013-08-30T10:16:30:000";
}
// ---------------------------------------------------------------------------
long TOWEROFLONDON_GAME::milliSecondsToDeciSeconds(System::TDateTime &timeNow,System::TDateTime &timeThen)
{
	__int64 timemilli = MilliSecondsBetween(timeNow, timeThen);
	timemilli/=100;
	return (long) timemilli;
}

// ---------------------------------------------------------------------------
bool TOWEROFLONDON_GAME::handleClick(const int x, const int y)
{
	if (ignore_click) // PREVENT OVER-LAPPING CALLS
		return (false);

 	 if (m_NextButton->Visible)
		return false;

	ignore_click = true;

	const int Size = getGamePadSize();
	int XPos = getGamePadX();
	int YPos = getGamePadY() - Size;
	int Selected = -1;

	if ((x >= XPos) && (y >= YPos + getGamePadPadding()))
	{
		if ((x < XPos + Size * 6) && (y < YPos + Size - getGamePadPadding()))
		{
//we know which box they clicked on.. now take into account the padding in the x
			XPos = (x - XPos) / Size;
			int boxXPos = getGamePadX() + (XPos * Size); //start of x

			if ((x >= boxXPos + getGamePadPadding()) && (x < boxXPos+Size - getGamePadPadding()))
				Selected = XPos + 1;
		}
	}

	if (Selected == -1)
	{
		ignore_click = false;
		return (false);
	}
	m_iuserkeyinput = Selected;

	if (m_GameID < 0)
	{
		//this is the example, we don't need to do any thing, but store input
		m_flashCounter = 0;
		setFlashTimeOutFunction(true);
		return (false);
	}

	int expected = m_levelData->getExpectedAnswer(m_GameID);
	int level = m_levelData->getGameLevel(m_GameID);

	if (Selected == expected)
		m_score++;

	System::TDateTime timeNow = Now();
	m_flashStart_ts = timeNow;

	m_CurrentRow->level = m_GameID;
	m_CurrentRow->game_index = level;
	m_CurrentRow->expected =  expected;
	m_CurrentRow->selected = Selected;
	m_CurrentRow->elapsed =  milliSecondsToDeciSeconds(timeNow,m_levelStart_ts);
	m_CurrentRow->complete = !m_timedOut;  //dpn't save timedout
	NewSaveRow();

	if ((m_timedOut) || (m_GameID == 17))
	{
		setTimeOutFunction(false);
		fillHeaderData();
		is_running = false;
	}
	else
	{//next level
		m_flashCounter = 0;
		m_disabledCounter = -1;
		setFlashTimeOutFunction(true);
	}
	return (false);
}

// ---------------------------------------------------------------------------
bool TOWEROFLONDON_GAME::isRunning(void)
{
	return (is_running);
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::abandon(void)
{
// we are fine for timeout, as it is never processed until
//the user interacts. and they can't if the abondon box is open.
	fillHeaderData();
	m_returnDataHeader.abandon = true;
	is_running = false;
}

// ---------------------------------------------------------------------------
void TOWEROFLONDON_GAME::runStart(void)
{
	is_running = true;
}

// ---------------------------------------------------------------------------
bool TOWEROFLONDON_GAME::run()
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
int TOWEROFLONDON_GAME::getRunTime(void)
{
	return ((int)((10 * (end_level - start_level)) / CLK_TCK));
}
// ---------------------------------------------------------------------------


const int TOWEROFLONDON_GAME::m_TOLgameData[18][6] = {
	{0, 1, 2, 0, 0, 3}, {3, 1, 2, 0, 0, 0}, {0, 0, 2, 1, 3, 0},
	{0, 0, 2, 0, 3, 1}, {0, 0, 0, 2, 3, 1}, {0, 0, 2, 0, 1, 3},
	{0, 0, 0, 1, 3, 2}, {0, 3, 2, 0, 0, 1}, {0, 3, 2, 0, 1, 0},
	{0, 0, 2, 3, 1, 0}, {0, 2, 1, 0, 3, 0}, {0, 0, 3, 2, 1, 0},
	{0, 3, 1, 0, 0, 2}, {0, 0, 0, 3, 1, 2}, {0, 2, 3, 0, 1, 0},
	{0, 0, 3, 0, 1, 2}, {3, 2, 1, 0, 0, 0}, {2, 3, 1, 0, 0, 0}};

const int TOWEROFLONDON_GAME::m_TOL_wantedGameData[6] = {0, 1, 2, 0, 3, 0};

const String TOWEROFLONDON_GAME::m_inGameText[1] = {
	{"How many moves would it take to make picture 'A' look like picture 'B'?"}
};

const String TOWEROFLONDON_GAME::m_introText_7[6] = {
	{"Hoops"},
	{"You will be shown two pictures at a time."},
	{""},

	{"Each picture shows a set of three pegs onto which black, yellow and white hoops have been placed."},
	{"The left peg can hold 3 hoops, the middle peg 2 hoops and the right peg only 1 hoop."},

	{"Touch \"Next\" to continue."}};

const String TOWEROFLONDON_GAME::m_introText_6[8] = {
	{"The goal is to make picture A look like picture B by moving the hoops on picture A."},
	{"Your task is to work out how to do this in as few moves as possible."},

	{""},
	{"Taking a hoop off one peg and putting it on another is a single move and you can only shift one hoop at a time."},
	{"You might need to shift one hoop to get at the one below it or do something more complicated to swap them around."},
	{""},
	{""},

	{"Touch \"Next\" for an example."}};

const String TOWEROFLONDON_GAME::m_introText_5[5] = {
	{"Here you can see that the white hoop in picture A needs to be moved to the middle peg to make it look like picture B."},
	{""},
	{""},

	{"This can be done in a single move, so the answer to the fewest moves question is 1 move."},

	{"Touch \"Next\" for a practice puzzle"}};

const String TOWEROFLONDON_GAME::m_introText_4[1] = {
	{"How few moves would it take to make picture A look like picture B?"}};

const String TOWEROFLONDON_GAME::m_introText_3[3] = {
	{"You answered: "},
	{"It can be done in: 2"},
	{"Touch \"Next\" to continue."}};

const String TOWEROFLONDON_GAME::m_introText_2[2] = {
	{"Touch \"Next\" when you are ready to begin.  You will have 3 minutes to do as many puzzles as you can."},
	{""}};

// ===========================================================================
