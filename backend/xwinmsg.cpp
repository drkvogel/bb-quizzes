#include "xwinmsg.h"
//===========================================================================
/*
http://msdn.microsoft.com/en-gb/library/windows/desktop/ms632590%28v=vs.85%29.aspx
*/
XWINMSG::XWINMSG( const std::string label )
	:
	is_valid( false ),
	ui_message( true )
{					// GET UNIQUE+SHARED MESSAGE ID
	ui_message = RegisterWindowMessageA( label.c_str() );
	if ( 0 != ui_message )
		{is_valid = true;
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XWINMSG::~XWINMSG( void )
{
}
//---------------------------------------------------------------------------
bool XWINMSG::isValid( void ) const
{
	return( is_valid );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
UINT XWINMSG::getMessageIdent( void ) const
{
	return( ui_message );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XWINMSG::broadcast( const int type, const int value )
{
	if ( ! isValid() )
		{return( false );
		}
	WPARAM 	wParam = type;
	LPARAM 	lParam = value;
	BOOL	ok = SendNotifyMessage( HWND_BROADCAST, ui_message, type,value);
	return( ok != 0 );
}
//===========================================================================

