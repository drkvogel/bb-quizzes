#ifndef xwinmsgH
#define xwinmsgH
#include <windows.h>
#include <string>
//---------------------------------------------------------------------------
class XWINMSG
{
private:
	bool	is_valid;
	UINT	ui_message;
public:
	XWINMSG( const std::string label );
	~XWINMSG( void );
	bool	isValid( void ) const;
	bool	broadcast( const int type, const int value );
	UINT	getMessageIdent( void ) const;
};
//---------------------------------------------------------------------------
#endif

