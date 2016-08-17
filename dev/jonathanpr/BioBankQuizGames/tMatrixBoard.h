//---------------------------------------------------------------------------

#ifndef tMatrixBoardH
#define tMatrixBoardH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "MatrixGame.h"
#include "rosetta.h"
#include "main.h"
//---------------------------------------------------------------------------
class TMatrixBoard : public TForm
{
__published:	// IDE-managed Components
	TPanel *panel_abandon;
	TPanel *panel_play;
	TImage *image_play;
	TButton *NextButton;
	TButton *PrevButton;
	TTimer *gameTimer;
	TSaveTextFileDialog *SaveTextFileDialog;
	TTimer *flashTimer;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall panel_abandonClick(TObject *Sender);
	void __fastcall panel_playMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PrevButtonClick(TObject *Sender);
	void __fastcall NextButtonClick(TObject *Sender);
	void __fastcall flashTimerTimer(TObject *Sender);
	void __fastcall gameTimerTimer(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	bool in_game;
	int	score;
	int	margin;
	int	level;
	MATRIX_GAME *game;
	void 	resetBoard( void );
	void 	abandonGame( void );
	void	extractResults();
 	std::string toSTD(String in);
public:		// User declarations
	void setGameTimeOut(bool start);
	void setFlashTimeOut(bool start, int timeout = 500);
	bool playGame( TForm1 *caller, int gameid );
	bool	is_valid;
	bool	abandon;

	static	ROSETTA	*results;
	__fastcall TMatrixBoard(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMatrixBoard *MatrixBoard;
//---------------------------------------------------------------------------
#endif
