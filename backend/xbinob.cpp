#include "xbinob.h"
#include "xencode.h"
#include <stdlib.h>
#include <stdio.h>
//#include <mem.h>
#include <string>
//===========================================================================
bool XBINOB::use_exceptions = true;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void XBINOB::useExceptions( const bool ue )
{	use_exceptions = ue;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::usingExceptions( void )
{	return( use_exceptions );
}
//---------------------------------------------------------------------------
XBINOB::XBINOB( void )
	:
	nbytes( 0 ),
	value( NULL )
{
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XBINOB::XBINOB( const int input_size, const unsigned char *data )
	:
	nbytes( 0 ),
	value( NULL )
{
	insert( input_size, data );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XBINOB::XBINOB( const std::string b64 )
	:
	nbytes( 0 ),
	value( NULL )
{
	insertBase64( b64 );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XBINOB::XBINOB( const XBINOB &b )
	:
	nbytes( 0 ),
	value( NULL )
{
	insert( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XBINOB::~XBINOB( void )
{
	clear();
}
//---------------------------------------------------------------------------
void XBINOB::clear( void )
{
	if ( NULL != value )
		{free( value );
		value = NULL;
		}
	nbytes = 0;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void XBINOB::error( const std::string emsg ) const
{
	if ( usingExceptions() )
		{std::string	e = std::string( "XBINOB exception: ") + emsg;
		throw( e );
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				/* SET CONTENTS WHEN DATA IS INVALID */
void XBINOB::setInvalid( void )
{
	clear();
	nbytes = -1;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int XBINOB::size( void ) const
{
	return( nbytes );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::isValid( void ) const
{
	return( nbytes >= 0 );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::insert( const int input_size, const unsigned char *data )
{
	setInvalid();                   // MARK INITIALLY AS INVALID
	if ( input_size < 0 || NULL == data )
		{return( false );
		}
	value = (unsigned char *) malloc( input_size + 1 );
	if ( NULL == value )
		{error( "malloc-failure" );
		return( false );
		}
	void *destination = memcpy( value, data, input_size );
	if ( destination != (void *) value )
		{free( value );		// REMOVE CORRUPT DATA
		value = NULL;
		error( "memcpy-failure" );
		}
	else
		{nbytes = input_size;	// GOOD COPY
		}
	return( isValid() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::insert( const XBINOB &b )
{
	return( insert( b.nbytes, b.value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::append( const int input_size, const unsigned char *data )
{
	if ( ! isValid() )
		{return( false );
		}
	if ( input_size < 0 || NULL == data )
		{setInvalid();
		return( false );
		}
	if ( 0 == nbytes )
		{return( insert( input_size, data ) );
		}
	int	new_size = nbytes + input_size;
	void	*ptr = realloc( value, new_size + 1 );
	if ( NULL == ptr )
		{setInvalid();
		error( "realloc-failure" );
		return( false );
		}
	value = (unsigned char *) ptr;
	void *destination = memcpy( value+nbytes, data, input_size );
	if ( destination != (void *) (value+nbytes) )
		{setInvalid();
		error( "memcpy-failure" );
		}
	else
		{nbytes = new_size;	// GOOD COPY
		}
	return( isValid() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::append( const XBINOB &b )
{
	return( append( b.nbytes, b.value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::extract( int *output_size, unsigned char **data ) const
{
	*output_size = -1;			// INITIALISE AS INVALID
	*data = NULL;
	if ( ! isValid() )		     	// INVALID CONTENTS
		{return( false );
		}
	if ( 0 == nbytes )			// EMPTY CASE
		{*output_size = 0;
		return( true );
		}
	*data = (unsigned char *) malloc( nbytes );
	if ( NULL == *data )
		{return( false );
		}
	void *destination = memcpy( *data, value, nbytes );
	if ( destination != *data )
		{free( *data );
		*data = NULL;
		error( "memcpy-failure" );
		return( false );
		}
	*output_size = nbytes;
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const unsigned char *XBINOB::data( void ) const
{
	return( (const unsigned char *) value );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XBINOB::extractHex( void ) const
{
	if ( ! isValid() )
		{error( "extractHex, not possible with invalid data" );
		return( "!" );	// NOT HEX, SO CALLER SHOULD CHECK VALIDITY FIRST
		}
	int	len;
	char	*hx;
	if ( ! XENCODE::binToHex( value, nbytes, &hx, &len ) )
		{error( "extractHex, internal failure in binToHex" );
		return( "!" );
		}
	std::string	s( hx );
	free( hx );
	return( s );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XBINOB::extractBase64( void ) const
{
	if ( ! isValid() )
		{error( "extractBase64, not possible with invalid data" );
		return( "!" );	// NOT HEX, SO CALLER SHOULD CHECK VALIDITY FIRST
		}
	if ( 0 == nbytes )
		{return( "" );
		}
	int	len_out;
	char	*out = NULL;
	if ( ! XENCODE::binToB64( value, nbytes, &out, &len_out ) )
		{error( "extractBase64, internal failure in XENCODE::binToB64");
		return( "" );
		}
	std::string	b( out );
	free( out );
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::insertHex( const std::string hex )
{
	clear();
	int	sz = hex.size();
	if ( sz % 2 != 0 )
		{setInvalid();
		error( "invalid length for Hex input" );
		}
	if ( ! XENCODE::hexToBin( hex, &value, &nbytes ) )
		{setInvalid();
		error( "insertHex, internal failure in XENCODE::hexToBin" );
		return( false );
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::insertBase64( const std::string b64 )
{
	clear();
	if ( ! XENCODE::b64ToBin( b64, &value, &nbytes ) )
		{setInvalid();
		error( "insertBase64, internal failure in XENCODE::b64ToBin" );
		return( false );
		}
	return( true );
}
//---------------------------------------------------------------------------
XBINOB &XBINOB::operator=( const XBINOB &b )
{
	insert( b );
	return( *this );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::isEqual( const XBINOB &b ) const
{
	if ( nbytes != b.nbytes )
		{return( false );
		}
	int	i;
	for ( i = 0; i < nbytes; i++ )
		{if ( value[i] != b.value[i] )
			{return( false );
			}
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::operator==( const XBINOB &b ) const
{
	return( isEqual( b ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XBINOB::operator!=( const XBINOB &b ) const
{
	return( ! isEqual( b ) );
}
//===========================================================================


