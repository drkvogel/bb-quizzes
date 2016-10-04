#ifndef xgdiH
#define xgdiH
//---------------------------------------------------------------------------
#include <windows.h>
#pragma warn -8071
#pragma warn -8022
#include <gdiplus.h>
#pragma warn +8022
#pragma warn +8071
#include <string>
#include <vector>
#include "xerror.h"
//---------------------------------------------------------------------------
class MISTREAM;
//---------------------------------------------------------------------------
class XGDI : public XERROR
{
private:
	ULONG_PTR gdiplusToken;
	void	startup( void );
	void	shutdown( void );
	MISTREAM	*mis;
	static	int	instance_count;
	static	UINT	ncodec_info;
	static	Gdiplus::ImageCodecInfo *codec_info;
protected:
	Gdiplus::Image 	*im;
	Gdiplus::Status  stat;
	wchar_t *char2wchar( const char *source ) const;
	char 	*wchar2char( const wchar_t *wsource ) const;
	bool 	getImageEncoderClsid( const std::string format,
		CLSID *pClsid ) const;
	bool 	getEncoderClsid( const WCHAR *format, CLSID *pClsid ) const;
	int 	normaliseQuadrant( int nquad ) const;
public:
	XGDI( void );
	~XGDI( void );
	std::vector<std::string> listEncoders( void ) const;
	bool 	insert( const int nbytes, const unsigned char *buf );
	bool 	insertFileMS( const std::string file_name );
	bool	insertFile( const std::string file_name );
	std::string	extract( int *output_size, unsigned char **data,
		const std::string format );
	std::string	saveFileMS( const std::string file_name,
		const std::string format );
	std::string	saveFile( const std::string file_name,
		const std::string format );
	std::string	rotateQuadrants( const int nquadrants );
};
//---------------------------------------------------------------------------
/*
Note from: http://www.leunen.com/cbuilder/gdiplus.html
[1] Create library with
implib -c -f gdiplus.lib gdiplus.dll, link library into project
[2]
You might have problems compiling code using GDI+. If some functions
repeatedly return an error, check the following points: Put the STRICT
define in the Project/Options/Conditionnal defines instead of putting
it in your code. Graham Thompson reported that with BCB5  functions
including enumerated parameters failed returning 'invalid parameter'
error. Setting 'Treat enum types as ints' to true in the project's
compiler options took the error off. Others reported that building
the application in release mode helped too.
*/
//---------------------------------------------------------------------------
#endif

