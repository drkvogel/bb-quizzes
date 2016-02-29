//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", Form1);
USEFORM("board.cpp", fm_board);
USEFORM("tSymbolDigitBoard.cpp", symbolDigitBoard);
USEFORM("tTowerOfLondonGameBoard.cpp", TowerOfLondonBoard);
USEFORM("tTrailBoard.cpp", TrailBoard);
USEFORM("tmessage.cpp", fm_tmessage);
USEFORM("tMatrixBoard.cpp", MatrixBoard);
USEFORM("result.cpp", fm_result);
USEFORM("Thanks.cpp", Form2);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(Tfm_result), &fm_result);
		Application->CreateForm(__classid(Tfm_board), &fm_board);
		Application->CreateForm(__classid(TTrailBoard), &TrailBoard);
		Application->CreateForm(__classid(Tfm_tmessage), &fm_tmessage);
		Application->CreateForm(__classid(TsymbolDigitBoard), &symbolDigitBoard);
		Application->CreateForm(__classid(TTowerOfLondonBoard), &TowerOfLondonBoard);
		Application->CreateForm(__classid(TMatrixBoard), &MatrixBoard);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
