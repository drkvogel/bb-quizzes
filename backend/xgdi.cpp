#pragma hdrstop
#include <stdio.h>
#include "xgdi.h"
#include "mistream.h"
//===========================================================================
int	XGDI::instance_count = 0;
UINT	XGDI::ncodec_info = 0;	// NUMBER OF IMAGE ENCODERS
Gdiplus::ImageCodecInfo* XGDI::codec_info = NULL;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define	XDELETE(a)	{if ( NULL != a ){delete a; a = NULL; }}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XGDI::XGDI( void )
	:
	mis( NULL ),
	im( NULL )
{
	if ( 0 == instance_count++ )
		{startup();
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XGDI::~XGDI( void )
{
	XDELETE( im );
	XDELETE( mis );
	if ( 0 == --instance_count )
		{shutdown();
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void XGDI::startup( void )				// INITIALIZE GDI+
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	UINT  size = 0;         	// SIZE OF ENCODER ARRAY (IN BYTES)
	Gdiplus::GetImageEncodersSize( &ncodec_info, &size );
	if ( 0 == size )
		{setInvalid( "GetImageEncoders failed" );
		return;
		}
	codec_info = (Gdiplus::ImageCodecInfo*) malloc( size );
	if( NULL == codec_info )
		{setInvalid( "NULL code_info" );
		return;
		}
	Gdiplus::GetImageEncoders( ncodec_info, size, codec_info );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void XGDI::shutdown( void )
{
	if ( NULL != codec_info )
		{free(codec_info);
		codec_info = NULL;
		}
	Gdiplus::GdiplusShutdown( gdiplusToken );
}
//---------------------------------------------------------------------------
wchar_t *XGDI::char2wchar( const char *source ) const
{
	if ( NULL == source )
		{return( NULL );
		}
	int	outlen = strlen( source );   // DUNNO IF OUTPUT SIZE IS GOOD
	wchar_t	*wresult = (wchar_t *) malloc( sizeof(wchar_t) * ( outlen + 1 ) );
	if ( NULL == wresult )
		{return( NULL );
		}
	if ( (size_t) -1 == mbstowcs( wresult, source, outlen + 1 ) )
		{free( wresult ); 		// CONVERSION FAILURE
		return( NULL );
		}
	return( wresult );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
char *XGDI::wchar2char( const wchar_t *wsource ) const
{
	if ( NULL == wsource )
		{return( NULL );
		}
	int	outlen = wcslen(wsource);
	char	*result = (char *) malloc( outlen + 1 );
	if ( NULL == result )
		{return( NULL );
		}
	if ( (size_t) -1 ==  wcstombs( result, wsource, outlen + 1 ) )
		{free( result );		// CONVERSION FAILURE
		return( NULL );
		}
	return( result );
}
//---------------------------------------------------------------------------
bool XGDI::getEncoderClsid( const WCHAR *format, CLSID *pClsid ) const
{
	int	i;
	for( i = 0; i < (int) ncodec_info; i++ )
		{if( 0 == wcscmp( codec_info[i].MimeType, format) )
			{*pClsid = codec_info[i].Clsid;
			return( true );
			}
		}
	return( false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XGDI::getImageEncoderClsid( const std::string format, CLSID *pClsid ) const
{
	std::string	mime_type = std::string( "image/" ) + format;
	wchar_t	*mt = char2wchar( mime_type.c_str() );
	if ( NULL == mt )
		{return( false );
		}
	bool	match = getEncoderClsid( mt, pClsid );
	free( mt );
	return( match );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::vector<std::string> XGDI::listEncoders( void ) const
{
	std::vector<std::string> enc;
	char	*name = NULL;
	int	i;
	for( i = 0; i < (int) ncodec_info; i++ )
		{
		name = wchar2char( codec_info[i].MimeType );
		if ( NULL != name )
			{enc.push_back( std::string(name) );
			free( name );
			name = NULL;
			}
		else
			{enc.push_back( "?unknown" );
			}
		}
	return( enc );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string resetStream( IStream *is )
{
	LARGE_INTEGER liDistanceToMove;
	liDistanceToMove.QuadPart = 0;
	DWORD dwOrigin = 0;
	ULARGE_INTEGER *lpNewPointer = NULL;
	HRESULT sk_res = is->Seek( liDistanceToMove, dwOrigin, lpNewPointer );
	if ( S_OK != sk_res )
		{char	sbuf[100];
		sprintf( sbuf,
			"failure at IStream->Seek, sk_res=%d",
			(int) sk_res  );
		return( std::string(sbuf) );
		}
	return( std::string( "" ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XGDI::insert( const int nbytes, const unsigned char *buf )
{
	if ( ! isValid() )
		{return( false );
		}
	mis = new MISTREAM( nbytes, buf );
	if ( ! mis->isValid() )
		{setInvalid( mis->getLastError() );
		return( false );
		}
	mis->gotoStart();
	im = new Gdiplus::Image( mis->ptrIStream(), TRUE );
	stat = im->GetLastStatus();
	if ( Gdiplus::Ok == stat )
		{return( true );
		}
	char	mbuf[100];
	sprintf( mbuf, "insert, failure creating Gdiplus::Image, stat=%d",
		(int) stat );
	setInvalid( mbuf );
	return( false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XGDI::insertFile( const std::string file_name )
{
	FILE	*f = fopen( file_name.c_str(), "rb" );
	if ( NULL == f )
		{setInvalid( "unable to open input file" );
		return( false );
		}
	int	c;
	int	buf_step = 10000;
	int	buf_size = 10000;
	int	nbytes = 0;
	unsigned char *value = (unsigned char *) malloc( buf_size + 5 );
	if ( NULL == value )
		{setInvalid( "malloc failure" );
		return( false );
		}
	while ( EOF != ( c = fgetc( f ) ) )
		{value[nbytes] = (unsigned char) c;
		if ( ++nbytes > buf_size )
			{buf_size += buf_step;
			value = (unsigned char *) realloc( value, buf_size + 5 );
			if ( NULL == value )
				{setInvalid( "realloc failure" );
				return( false );
				}
			}
		}
	fclose( f );
	bool	done = insert( nbytes, value );
	free( value );
	return( done );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XGDI::insertFileMS( const std::string file_name )
{
	FILE	*ftest = fopen( file_name.c_str(), "rb" );
	if ( NULL == ftest )
		{setInvalid( "failed to open file" );
		return( false );
		}
	fclose( ftest );
	wchar_t	*fname = char2wchar( file_name.c_str() );
	if ( NULL == fname )
		{setInvalid( "failure at char2wchar" );
		return( false );
		}
	im = new Gdiplus::Image( fname );
//	stat = im->GetLastError();
	free( fname );
	return( true );
}
//---------------------------------------------------------------------------
			/* SAVE-FILE USING DIRECT MicroSoft OUTPUT ROUTINE */
std::string XGDI::saveFileMS( const std::string file_name,
	const std::string format )
{
	if ( ! isValid() )
		{return( std::string("invalid on entry") );
		}
	if ( NULL == im )
		{return( std::string("no contents to output") );
		}
	CLSID   encoder;
	if ( ! getImageEncoderClsid( format, &encoder ) )
		{return( std::string("output format invalid" ) );
		}
	wchar_t	*fname = char2wchar( file_name.c_str() );
	if ( NULL == fname )
		{return( std::string("failure at char2wchar") );
		}
	stat = im->Save( fname, &encoder, NULL);	// `RAW' GDIPLUS METHOD
	free( fname );
	if( Gdiplus::Ok == stat )
		{return( std::string("") );
		}
	char	mbuf[100];
	sprintf( mbuf, "failure at Gdiplus::Save, stat=%d",
		(int) stat );
	return( std::string(mbuf) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XGDI::extract( int *output_size, unsigned char **data,
	const std::string format )
{
	*output_size = -1;
	*data = NULL;
	CLSID   encoder;
	if ( ! getImageEncoderClsid( format, &encoder ) )
		{return( std::string("output format invalid" ) );
		}
	if ( ! mis->gotoStart() )
		{return( std::string("gotoStart failure for internal stream") );
		}
	MISTREAM	mout;			// `RAW' GDIPLUS METHOD
	stat = im->Save( mout.ptrIStream(), &encoder, NULL);
	if ( S_OK != stat )
		{return( std::string( "im->Save" ) );
		}
	std::string	e = mout.extract( output_size, data );
	return( e );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XGDI::saveFile( const std::string file_name,
	const std::string format )
{
	int	output_size = -1;
	unsigned char	*data = NULL;
	std::string	e = extract( &output_size, &data, format );
	if ( ! e.empty() )
		{return( e );
		}
	FILE	*fo = fopen( file_name.c_str(), "wb" );
	if ( NULL == fo )
		{return( std::string( "fopen" ) );
		}
	int	i;
	for ( i = 0; i < output_size; i++ )
		{if ( EOF == fputc( data[i], fo ) )
			{e = "fputc failure";
			break;
			}
		}
	fclose( fo );
	free( data );
	return( e );
}
//---------------------------------------------------------------------------
int XGDI::normaliseQuadrant( int nquad ) const
{					// CONVERT QUADRANTS TO RANGE [0,3]
	while ( nquad < 0 )
		{nquad += 4000000;
		}
	return( nquad % 4 );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XGDI::rotateQuadrants( const int nquadrants )
{
	if ( NULL == im )
		{return( "insert() must be called first" );
		}
	int	nq = normaliseQuadrant( nquadrants );
	if ( 0 == nq )				// NO TRANSFORMATION REQUIRED
		{return( "" );
		}
	Gdiplus::RotateFlipType	transform = Gdiplus::RotateNoneFlipNone;
	switch( nq )
		{
		case 1:
			transform = Gdiplus::Rotate90FlipNone;
			break;
		case 2:
			transform = Gdiplus::Rotate180FlipNone;
			break;
		case 3:
			transform = Gdiplus::Rotate270FlipNone;
			break;
		default:			// SHOULDN'T HAPPEN
			break;
		}
	stat = im->RotateFlip( transform );
	if( Gdiplus::Ok == stat )
		{return( std::string("") );
		}
	char	mbuf[100];
	sprintf( mbuf, "failure at Gdiplus::RotateFlip, stat=%d",
		(int) stat );
	return( std::string(mbuf) );
}
//===========================================================================
#pragma warn -8080 		// REQUIRED TO SUPPRESS SPURIOUS WARNING

