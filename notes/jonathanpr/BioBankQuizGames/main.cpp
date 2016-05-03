//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "board.h"
#include "tTrailBoard.h"
#include "tSymbolDigitBoard.h"
#include "tMatrixBoard.h"
#include "tTowerOfLondonGameBoard.h"
#include "Thanks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


 #define	NLAYOUT	4
static LAYOUT layout[NLAYOUT] =
	{// COLS, ROWS
		{	2,	2,	0, 0, 0, 0, 6	},
		{	3,	2,	0, 0, 0, 0, 12	},
		{	4,	3,	0, 0, 0, 0, 32	},
		{	4,	4,	0, 0, 0, 0, 32	}
	};


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int indx = 3;
	fm_board->playGame(this, layout + indx);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	TrailBoard->playGame(this, 1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	symbolDigitBoard->playGame(this,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	TowerOfLondonBoard->playGame(this,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	MatrixBoard->playGame(this,0);
}
//---------------------------------------------------------------------------
void TForm1::ShowThanks()
{
	this->Hide();
	Form2->ShowModal();
	this->Show();
}
//---------------------------------------------------------------------------



