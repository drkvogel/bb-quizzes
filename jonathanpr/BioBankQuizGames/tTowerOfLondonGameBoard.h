//---------------------------------------------------------------------------

#ifndef tTowerOfLondonGameBoardH
#define tTowerOfLondonGameBoardH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include "rosetta.h"
#include "TowerOfLondonGame.h"
#include "main.h"
//---------------------------------------------------------------------------
class TTowerOfLondonBoard : public TForm
{
__published:	// IDE-managed Components
	TPanel *panel_abandon;
	TPanel *panel_play;
	TImage *image_play;
	TButton *NextButton;
	TTimer *gameTimer;
	TSaveTextFileDialog *SaveTextFileDialog;
	TTimer *flashTimer;
	TButton *PrevButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall gameTimerTimer(TObject *Sender);
	void __fastcall panel_abandonClick(TObject *Sender);
	void __fastcall image_playMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PrevButtonClick(TObject *Sender);
	void __fastcall NextButtonClick(TObject *Sender);
	void __fastcall flashTimerTimer(TObject *Sender);

private:	// User declarations
	bool in_game;
	int	score;
	int	level;
	int	margin;
	TOWEROFLONDON_GAME	*game;
	void 	resetBoard( void );
	void 	abandonGame( void );
	void	extractResults();
	std::string toSTD(String in);

public:		// User declarations
	void setGameTimeOut(bool start);
	void setFlashTimeOut(bool start);
	bool	is_valid;
	bool	abandon;
	static	ROSETTA	*results;
public:		// User declarations
	__fastcall TTowerOfLondonBoard(TComponent* Owner);
	bool playGame( TForm1 *caller, int gameid );
};
//---------------------------------------------------------------------------
extern PACKAGE TTowerOfLondonBoard *TowerOfLondonBoard;
//---------------------------------------------------------------------------
#endif
