#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "xregist.h"
#include "xuc.h"
//===========================================================================
XREGISTRY::XREGISTRY( const std::string registry_name )
	:
	XERROR( "XREGISTRY" ),
	reg_name( registry_name ), 	// HKEY NAME UNDER HKEY_CURRENT_USER
	reg( NULL )
{
	reg = new TRegistry();
	if ( NULL == reg )
		{setInvalid( "Failed to create TRegistry" );
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XREGISTRY::XREGISTRY( const std::string registry_name, HKEY__ *root_key )
	:
	XERROR( "XREGISTRY" ),
	reg_name( registry_name ),
	root( root_key ),
	reg( NULL )
{
	reg = new TRegistry();
	reg->RootKey = root;
	if ( NULL == reg )
		{setInvalid( "Failed to create TRegistry" );
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XREGISTRY::~XREGISTRY( void )
{
	delete reg;
}
//---------------------------------------------------------------------------
bool XREGISTRY::openForReading( void )
{					// OPEN REGISTRY, DO NOT CREATE
	if ( ! isValid() )
		{return( false );
		}
	bool	opened = false;
	try
		{//opened = reg->OpenKey( reg_name.c_str(), false );
		opened = reg->OpenKeyReadOnly( reg_name.c_str() );
		}
	catch ( ... )
		{opened = false;
		}
	return( opened );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XREGISTRY::openForWriting( void )
{					// OPEN REGISTRY, CREATE IF NECESSARY
	if ( ! isValid() )
		{return( false );
		}
	bool	opened = false;
	try
		{opened = reg->OpenKey( reg_name.c_str(), true );
		}
	catch ( ... )
		{opened = false;
		}
	if ( ! opened )
		{setCaveat( "Failed to open/create" );
		}
	return( opened );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void XREGISTRY::close( void )
{
	reg->CloseKey();
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TRegistry *XREGISTRY::getRegPtr( void ) const
{
	return( reg );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* LOAD A BOOL FROM REGISTRY */
bool XREGISTRY::getBool( const std::string name, bool *value )
{
	if ( ! openForWriting() )
		{return( false );
		}
	bool	ok = false;
	try
		{const	bool tmp = reg->ReadBool( name.c_str() );
		*value = tmp;
		ok = true;
		}
	catch ( ... )	// THROWN IF PARAMETER DOES NOT EXIST
		{ok = false;
		}
	close();
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* PUT A BOOL INTO REGISTRY KEY - CREATE IF NECESSARY */
bool XREGISTRY::putBool( const std::string name, const bool value )
{
	if ( ! openForWriting() )
		{return( false );
		}
	bool	ok = false;
	try
		{reg->WriteBool( name.c_str(), value );
		ok = true;
		}
	catch ( ... )
		{ok = false;
		}
	close();
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* LOAD AN INTEGER FROM REGISTRY */
bool XREGISTRY::getInt( const std::string name, int *value )
{
	if ( ! openForReading() )
		{return( false );
		}
	bool	ok = false;
	try
		{const	int tmp = reg->ReadInteger( name.c_str() );
		*value = tmp;
		ok = true;
		}
	catch ( ... )	// THROWN IF PARAMETER DOES NOT EXIST
		{ok = false;
		}
	close();
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* PUT AN INTEGER INTO REGISTRY KEY - CREATE IF NECESSARY */
bool XREGISTRY::putInt( const std::string name, const int value )
{
	if ( ! openForWriting() )
		{return( false );
		}
	bool	ok = false;
	try
		{reg->WriteInteger( name.c_str(), value );
		ok = true;
		}
	catch ( ... )
		{ok = false;
		}
	close();
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* LOAD A STRING FROM REGISTRY */
bool XREGISTRY::getString( const std::string name, std::string *value )
{
	if ( ! openForReading() )
		{return( false );
		}
	bool	ok = false;
	try
		{String tmp = reg->ReadString( name.c_str() );
		*value = XUC::cbs2stds( tmp );
		ok = true;
		}
	catch ( ... )
		{ok = false;
		}
	close();
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* PUT A STRING INTO REGISTRY KEY - CREATE IF NECESSARY */
bool XREGISTRY::putString( const std::string name, const std::string value )
{
	if ( ! openForWriting() )
		{return( false );
		}
	bool	ok = false;
	try
		{reg->WriteString( name.c_str(), value.c_str() );
		ok = true;
		}
	catch ( ... )
		{ok = false;
		}
	close();
	return( ok );
}
//===========================================================================

