#ifndef XCGI_C_INCLUDED
#define XCGI_C_INCLUDED       1
/*===========================================================================*/
/*		UTILITIES FOR CONSTRUCTING CGI SCRIPTS			*/
/*===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <stdarg.h>
#include "xbasic.h"
#include "xtime.h"
#include "xcgi.h"

/*===========================================================================*/
#ifndef __BORLANDC__
#define	stricmp	strcasecmp
#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int    	XCGI::debug = 1;
char	*XCGI::logname = "xcgi.log";
int	XCGI::max_param_num = 1000;		// CRASH PREVENTION LIMITS
int	XCGI::max_param_len = 3000;
int	XCGI::max_param_totlen = 50000;
/*===========================================================================*/
				/* INITIALIZE SYSTEM AND GET PARAMETERS */
XCGI::XCGI( int ac, char **av )
	:
	is_valid( true ),
	method( methodError ),
	flog( NULL )
{	int	i, content_length;
	char	*pbuf;
	FILE	*fi;
	setvbuf( stdout, NULL, _IONBF, 0 );		// DISABLE BUFFERING
	char	*mev = getenv( "REQUEST_METHOD" );
	if ( NULL == mev )
		{
		if ( ac > 2 && 0 == stricmp( "-qf", av[1] )
				&& NULL != ( fi = fopen(
				av[2], "r" ) ) )
			{
			method = methodFile;
			pbuf = (char *) malloc( 5002 );
			fgets( pbuf, 5000, fi );
			fclose( fi );
			}
		else if ( ac > 2 && 0 == strcmp( "-qs", av[1] ) )
			{
			method = methodString;
			pbuf = (char *) malloc( strlen( av[2] ) + 2 );
			strcpy( pbuf, av[2] );
			}
		else
			{printf( "\nUnsupported CGI method"
			"\nInteractive usage (2 types):"
		"\n\"-qf param\"  reads line from file 'param'"
		"\n\"-qs param\"  uses `param' as QUERY_STRING" );
			endFail(
	"Client not using a supported CGI method to request data." );
			is_valid = false;
			exit( EXIT_SUCCESS );	// IMMEDIATE EXIT
			}
		splitParams( pbuf );
		free( pbuf );
		}
	else if ( 0 == stricmp( mev, "GET" ) )
		{method = methodGet;
		splitParams( getenv( "QUERY_STRING" ) );
		}
	else if ( 0 == stricmp( mev, "POST" ) )
		{method = methodPost;
		content_length = atoi( getenv( "CONTENT_LENGTH" ) );
		if ( content_length < 0 || content_length > max_param_totlen
			|| ( NULL == ( pbuf = (char *)
				malloc( content_length + 2 ) ) ) )
			{log(
			"total of %ld bytes recieved from user script",
				content_length );
			endFail("too much input transmitted by script" );
			}
		for ( i = 0; i < content_length; i++ )
			{pbuf[i] = fgetc( stdin );
			}
		pbuf[ content_length ] = 0;
		splitParams( pbuf );
		free( pbuf );
		}
	else
		{log( "internal error, method = %ld", method );
		endFail( "server error" );
		}
	flush();
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
XCGI::~XCGI( void )
{
}
/*===========================================================================*/
void XCGI::flush( void ) const
{
	fflush( stdout );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
					/* WRITE LOG OF INTERNAL MESSAGES */
void XCGI::log( const char *txt, ... )
{	time_t	tnow;
	va_list	args;				// VARIABLE ARGUMENT LIST
	time( &tnow );
	if ( NULL == ( flog = fopen( logname, "w" ) ) )
		{return;			// NO LOGGING POSSIBLE
		}
	fprintf( flog, "\n\nLogtime %s\n", ctime( &tnow ) );
	va_start( args, txt );
	vfprintf( flog, txt, args );
	va_end( args );				// TIDY ARGUMENT LIST
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
bool XCGI::isValid( void ) const
{
	return( is_valid );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
						/* SET INTERNAL DEBUG VALUE */
void XCGI::setDebug( const int dbg )
{
	debug = dbg;
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int XCGI::getDebug( void ) const
{
	return( debug );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int XCGI::getMethod( void ) const
{
	return( method );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
std::string XCGI::getMethodName( void ) const
{
	if ( methodGet == method )
		{return( "GET" );
		}
	if ( methodPost == method )
		{return( "POST" );
		}
	if ( methodString == method )
		{return( "String" );
		}
	if ( methodFile == method )
		{return( "File" );
		}
	if ( methodUnknown == method )
		{return( "Unknown" );
		}
	if ( methodError == method )
		{return( "Error" );
		}
	return( "BUG" );
}
/*---------------------------------------------------------------------------*/
			/* READ FILE AND COPY VERBATIM TO OUTPUT STREAM */
void XCGI::verbatim( const char *vfname )
{       int	c;
	FILE	*fi;
	flush();
	if ( NULL == ( fi = fopen( vfname, "r" ) ) )
		{log( "xcgi_verbatim, unable to find file \"%s\"",
			vfname );
		printf( "\n<p><hr><b>SERVER ERROR</b><br>" );
		printf( "<i>Unable to include document</i> " );
		printf( "\n<tt>%s</tt><hr><p>\n", vfname );
		return;
		}
	while ( EOF != ( c = fgetc( fi ) ) )
		{fputc( c, stdout );	/* READ THEN WRITE EACH CHARACTER */
		}
	flush();
	fclose( fi );
}
/*---------------------------------------------------------------------------*/
							/* EXIT NICELY */
void XCGI::end( void )
{       long	i;
	flush();
	if ( NULL != flog )
		{fclose( flog );
		}
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
				/* TERMINATE DODGY REQUEST AND EXIT */
void XCGI::endFail( const char *err_txt )
{
	is_valid = false;
	log( err_txt );
	end();
}
/*---------------------------------------------------------------------------*/
		/* CONVERT 2-DIGIT HEXADECIMAL STRING TO NUMERIC VALUE */
int XCGI::unhex( const char *hx )
{       int	i, c;
	int	val = 0;
	for ( i = 0; i < 2; i++ )
		{c = hx[i];
		if ( '0' <= c && c <= '9' )
			{c -= '0';
			}
		else if ( 'a' <= c && c <= 'f' )
			{c -= ( 'a' - 10 );
			}
		else if ( 'A' <= c && c <= 'F' )
			{c -= ( 'A' - 10 );
			}
		else
			{log( "unhex: bad value \"%s\"", hx );
			return( (int) '?' );
			}
		val += ( i < 1 ) ? ( 16 * c ) : c;
		}
	return( val );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
				/* DECODE URL-ENCODED STRING IN PLACE */
void XCGI::decodeURL( char *txt )
{       int	code;
	int	pos = 0, newpos = 0;
	while ( txt[pos] != 0 )
		{if ( '+' == txt[pos] )		/* CONVERT PLUS TO SPACE */
			{txt[newpos] = ' ';
			}
		else if ( '%' == txt[pos] )	/* UN-ESCAPE HEX CODE */
			{code = unhex( txt + pos + 1 );
			if ( code > 8 )
				{txt[newpos] = (char) code;
				}
			else
				{log(
			"xcgi_decode_URL: suspicious escape code %d ignored",
					code );
				txt[newpos] = '?';
				}
			pos += 2;
			}
		else				/* COPY NORMAL CHARACTER */
			{txt[newpos] = txt[pos];
			}
		pos++;
		newpos++;
		}
	txt[newpos] = 0;
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
					/* GET NEXT PARAMETER FROM STRING */
int XCGI::nextParam( const char *in, const char terminator, char **out )
{	int	nc = 0;
	if ( NULL == ( *out = (char *) malloc( 52 ) ) )
		{endFail( "memory error on server" );
		}
	while ( terminator != in[nc] && 0 != in[nc] )
		{(*out)[nc] = in[nc];
		if ( 0 == ++nc % 50 )
			{if ( NULL == ( *out = (char *) realloc( *out, nc + 52 ) ) )
				{endFail( "server out of memory" );
				}
			if ( nc > max_param_len )
				{log( "runway parameter ?   length > %d",
					nc );
				endFail(	"overlong parameter in user script" );
				}
			}
		}
	(*out)[ nc ] = 0;
	decodeURL( *out );
	return( nc );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
			/* CONVERT PARAMETER STRING INTO SEPARATE ITEMS */
void XCGI::splitParams( const char *prm )
{	int	pos = 0;
	if ( debug > 0 )
		{log( "splitting\n\"%s\"", prm );
		}
	while ( 0 != prm[pos] )
		{char	*name, *value;
		pos += nextParam( prm + pos, '=', &name );
		if ( 0 != prm[pos] )
			{pos++;
			}
		pos += nextParam( prm + pos, '&', &value );
		if ( name != NULL && value != NULL )
			{param.setString( name, value );
			free( name );
			free( value );
			}
		else
			{endFail( "memory error extracting parameters" );
			return;
			}
		if ( 0 != prm[pos] )
			{pos++;
			}
		if ( param.count() > max_param_num )
			{log( "splitParams: at least %d parameters",
					param.count() );
			endFail( "script has sent too many parameters" );
			return;
			}
		}
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
bool XCGI::paramExists( const std::string pname ) const
{
	return( ROSETTA::typeString == param.getType( pname ) );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int XCGI::paramAsInt( const std::string pname ) const
{
	if ( ROSETTA::typeString != param.getType( pname ) )
		{return( invalidInt );
		}
	std::string	v = param.getString( pname );
	const	char	*s = v.c_str();
	if ( '-' == *s ) 	// ENSURE ONLY VALID NON-EMPTY INTS
		{s++;
		}
	while ( 0 != *s )
		{if ( ! isdigit( *s ) )
			{return( invalidInt );
			}
		s++;
		}
	return( atoi( v.c_str() ) );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
						/* FIND DATA RECEIPT METHOD */
int XCGI::findMethod( void )
{
	return( methodUnknown );
}
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
				/* WRITE INITIAL MIME HEADER TO OUTPUT */
void XCGI::writeHeader( const int typ )
{      
	char	*mime_fmt;
	if ( typeHtml == typ  )
		{mime_fmt = "text/html";
		printf( "content-type: text/html\n\n" );
		}
	else if ( typePlain == typ )
		{mime_fmt = "text/plain";
		printf( "content-type: text/plain\n\n" );
		}
	else if ( typeTiff == typ )
		{mime_fmt = "image/tiff";
		printf( "content-type: image/tiff\n\n" );
		}
    else if ( typeJSON == typ )
        {mime_fmt = "application/json";
        printf( "content-type: application/json\n\n" );
        }
	else
		{mime_fmt = "text/plain";
		printf( "content-type: text/plain\n\n" );
		log( "unrecognized format type=%d", typ );
		}
	log( "Mime format = \"%s\"", mime_fmt );
	flush();
}
/*---------------------------------------------------------------------------*/
				/* SHOW ALL PARAMETERS AS COMMENTS IN OUTPUT */
void XCGI::paramShowall( void )
{	int	i, np;
	np = param.count();
	printf( "\n\n<!-- XCGI found %d parameters -->\n", np );
	for ( i = 0; i < np; i++ )
		{printf( "\n<!--  \"%s\"=\"%s\"  -->",
			param.getName( i ).c_str(),
			param.getString( i ).c_str() );
		}
	printf( "\n" );
}
/*===========================================================================*/
#endif                                                  	/* XCGI.C */
