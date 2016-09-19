#include "rosetta.h"
#include "rosebase.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
using namespace std;

//===========================================================================
#define	AND		'&'
#define	BAR		'|'
#define	COLON		':'
#define	DOT		'.'
#define	EOS		'\0'
#define	EQUALS		'='
#define	HASH		'#'
#define	LSB		'['
#define	MINUS		'-'
#define	PERCENT		'%'
#define	PLUS		'+'
#define	RSB		']'
#define	SPACE		' '
#define	UNDERSCORE	'_'
#define	ZERO		'0'
//===========================================================================
				/* CONVERT S IN-SITU TO LOWERCASE */
static char make_lower( char c )
{	return( (char) tolower( c ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
static void makeLowerCase( std::string *s )
{
	std::transform( s->begin(), s->end(), s->begin(), make_lower );
}
//===========================================================================
const	int 	ROSETTA::errorInt    = (-9991999);
const	bool	ROSETTA::errorBool   = false;
const	double	ROSETTA::errorReal   = (-9.991999);
const	std::string	ROSETTA::errorString = "";
const	XDATE	ROSETTA::errorDate( 1800, 1, 1 );
const	XTIME	ROSETTA::errorTime( 1800, 1, 1, 0, 0, 0 );
const	XBINOB	ROSETTA::errorBinob( -1, NULL );
const	ROSETTA *ROSETTA::errorRosetta = NULL;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool	(*ROSETTA::warningHandler)( std::string ) = NULL;
bool	(*ROSETTA::errorHandler)( std::string ) = NULL;
//---------------------------------------------------------------------------
bool ROSETTA::use_exceptions = true;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::useExceptions( const bool ue )
{	use_exceptions = ue;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::usingExceptions( void )
{	return( use_exceptions );
}
//---------------------------------------------------------------------------
ROSETTA::ROSETTA( void )
{	init();
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSETTA::ROSETTA( const ROSETTA *old )
{
	init();
	insert( old );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						// COPY CONSTRUCTOR
ROSETTA::ROSETTA( const ROSETTA &old )
{	init();
	insert( &old );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						// DE-SERIALIZATION CONSTRUCTOR
ROSETTA::ROSETTA( const std::string serial )
{	init();
	serializeIn( serial, true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::init( void )
{
	pairs.clear(); // PAIRS IS CREATED EMPTY, BUT ALLOW RE-INITIALISING
	valid = true;
	nerrors = 0;
	sorted = true;		// EMPTY DATASETS ARE CONSIDERED SORTED
	case_sensitive = true;	// DEFAULT TO A<>a
	allow_insert = true;
	allow_update = true;
	nchanges = 0;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSETTA::~ROSETTA( void )
{
	clear();
}
//---------------------------------------------------------------------------
void ROSETTA::setWarningHandler( bool (*handler)( std::string ) )
{
	warningHandler = handler;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::setErrorHandler( bool (*handler)( std::string ) )
{
	errorHandler = handler;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::warning( const std::string emsg ) const
{
	std::string	txt = std::string( "ROSETTA Warning: ") + emsg;
	if ( NULL != warningHandler )
		{warningHandler( txt );
		}
	else if ( usingExceptions() )
		{throw( txt );
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::error( const std::string emsg ) const
{
	std::string	txt = std::string( "ROSETTA Error: ") + emsg;
	if ( NULL != errorHandler )
		{errorHandler( txt );
		}
	else if ( usingExceptions() )
		{throw( txt );
		}
}
//---------------------------------------------------------------------------
void ROSETTA::forceValid( void )
{
	valid = true;	// FOR EXTRACTING VALUES FROM INVALID ROSETTAS
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::isValid( void ) const
{	return( valid );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int ROSETTA::getNChanges( void ) const
{
	return( nchanges );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::canUpdate( void ) const
{
	return( allow_update );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::allowUpdate( const bool allow )
{
	allow_update = allow;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::canInsert( void ) const
{
	return( allow_insert );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::allowInsert( const bool allow )
{
	allow_insert = allow;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::canChange( void ) const
{
	return( allow_insert || allow_update );	// DUNNO IF `AND' OR 'OR' IS BEST
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::allowChanges( const bool allow )
{
	allowInsert( allow );
	allowUpdate( allow );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::caseSensitive( const bool cs )
{
	if ( pairs.empty() )
		{case_sensitive = cs;
		nchanges++;
		}
	else
		{error( "caseSensitive can only be modified on empty Rosetta");
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::isCaseSensitive( void ) const
{
	return( case_sensitive );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* HOW MANY PAIRS */
int ROSETTA::count( void ) const
{	return( pairs.empty() ? 0 : pairs.size() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* ARE THERE ZERO PAIRS */
bool ROSETTA::isEmpty( void ) const
{	return( pairs.empty() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* REMOVE ALL CONTENTS */
void ROSETTA::clear( void )
{
	nchanges++;
	std::vector<ROSE_BASE *>::iterator it = pairs.begin();
	while ( it != pairs.end() )
		{delete *it;
		it++;
		}
	pairs.clear();
	sorted = true;
	valid = true;
	nerrors = 0;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				/* StrictWeakOrdering for std::sort */
bool ROSETTA_compare( const ROSE_BASE *a, const ROSE_BASE *b )
{
	return( a->lessThan( b ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::sort( void )
{
	nchanges++;
	std::vector<ROSE_BASE *>::iterator it = pairs.begin();
	while ( it != pairs.end() )
		{(*it)->sort();	// SORT ANY SUB-ROSETTAS RECURSIVELY
		it++;
		}
	std::sort( pairs.begin(), pairs.end(), ROSETTA_compare );
	sorted = true;
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::isSorted( void ) const
{	return( sorted );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* RETURN POINTER TO A NAMED PAIR */
ROSE_BASE *ROSETTA::find( const std::string name, const bool warnOnFailure ) const
{
	std::string	target = name;
	if ( ! case_sensitive )
		{makeLowerCase( &target );
		}
	if ( sorted )					// BINARY SEARCH
		{
		int	npairs = pairs.size();
		int	lo = -1;
		int	hi = npairs;
		int	probe;
		while ( hi - lo > 1 )
			{
			probe = ( hi + lo ) / 2;
			if ( pairs[probe]->id > target )
				{hi = probe;
				}
			else
				{lo = probe;
				}
			}
		if ( lo != -1 && target == pairs[lo]->id )
			{return( pairs[lo] );
			}
		}
	else						// LINEAR SEARCH
		{
		std::vector<ROSE_BASE *>::const_iterator it = pairs.begin();
		while ( it != pairs.end() )
			{if ( target == (*it)->id )
				{return( *it );
				}
			it++;
			}
		}
	if ( warnOnFailure )
		{error( std::string("member \"") + name
			+ std::string("\" not found") );
		}
	return( NULL );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			/* COMPOUND NAMES ARE MULTI-LEVEL A.B, A.B.C ETC */
bool ROSETTA::isSimpleName( const char *s ) const
{	while ( *s != 0 )
		{if ( DOT == *s++ )
			{return( false );
			}
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* RETURN POINTER TO A NAMED PAIR, ALLOW A.B.C NAMING */
ROSE_BASE *ROSETTA::findCompound( const std::string name, const bool warnOnFailure ) const
{
	const	char	*c = name.c_str();
	int	pos = 0;
	while ( c[pos] != DOT )
		{if ( 0 == c[pos++] ) 	// SIMPLE NAME, NO DOTS
			{return( find( name, warnOnFailure ) );
			}
		}
	char	*first = (char *) malloc( pos+2 );
	strncpy( first, c, pos );
	first[pos] = 0;
	ROSE_BASE *b = find( first, false );
	free( first );
	if ( NULL == b )
		{if ( warnOnFailure )
			{error( std::string("member \"") + name
				+ std::string("\" not found") );
			}
		return( NULL );
		}
	if ( b->type() != typeRosetta )	     // NAME X.Y => X MUST BE A ROSETTA
		{if ( warnOnFailure )
			{error( "Rosetta member not a Rosetta" );
			}
		return( NULL );
		}
	return( ((ROSE_ROSETTA *)b)->val->findCompound( c+pos+1, warnOnFailure ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* IS A NAME CONTAINED WITHIN SET */
bool ROSETTA::exists( const std::string name ) const
{	return( NULL != findCompound( name, false ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* RETURN NAME OF A PAIR */
std::string ROSETTA::getName( const int index ) const
{	return( ( index >= 0 && index < (int) pairs.size() )
		? pairs[index]->id : std::string("") );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* RETURN TYPE OF A PAIR */
int ROSETTA::getType( const int index ) const
{	return( ( index >= 0 && index < (int) pairs.size() )
		? pairs[index]->type() : typeError );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* RETURN TYPE OF A PAIR */
int ROSETTA::getType( const std::string name ) const
{
	ROSE_BASE *b = findCompound( name, false );
	return( ( NULL != b ) ? b->type() : typeError );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* ADD A TAG TO MEMBER */
bool ROSETTA::attachTag( const int index, const std::string tag_name )
{
	return( ( index >= 0 && index < (int) pairs.size() )
		? pairs[index]->attachTag( tag_name ) : false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* ADD A TAG TO MEMBER */
bool ROSETTA::attachTag( const std::string name, const std::string tag_name )
{
	ROSE_BASE *b = findCompound( name, false );
	return( ( NULL != b ) ? b->attachTag( tag_name ) : false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* REMOVE A TAG FROM MEMBER */
bool ROSETTA::removeTag( const int index, const std::string tag_name )
{
	return( ( index >= 0 && index < (int) pairs.size() )
		? pairs[index]->removeTag( tag_name ) : false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* REMOVE A TAG FROM MEMBER */
bool ROSETTA::removeTag( const std::string name, const std::string tag_name )
{
	ROSE_BASE *b = findCompound( name, false );
	return( ( NULL != b ) ? b->removeTag( tag_name ) : false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* IS A TAG ATTACHED TO MEMBER */
bool ROSETTA::hasTag( const int index, const std::string tag_name ) const
{
	return( ( index >= 0 && index < (int) pairs.size() )
		? pairs[index]->hasTag( tag_name ) : false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* IS A TAG ATTACHED TO MEMBER */
bool ROSETTA::hasTag( const std::string name, const std::string tag_name ) const
{
	ROSE_BASE *b = findCompound( name, false );
	return( ( NULL != b ) ? b->hasTag( tag_name ) : false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* ARE TWO SETS IDENTICAL */
bool ROSETTA::isEqual( const ROSETTA *other ) const
{
	if ( pairs.size() != other->pairs.size() )
		{return( false );
		}
	ROSE_BASE	*b;
	std::vector<ROSE_BASE *>::const_iterator it = pairs.begin();
	while ( it != pairs.end() )
		{b = other->find( (*it)->id, false );
		if ( NULL == b || ! b->equalValue( *it ) )
			{return( false );
			}
		it++;
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* ARE TWO SETS IDENTICAL */
bool ROSETTA::operator==( const ROSETTA &p ) const
{	return( isEqual( &p ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
						/* ARE TWO SETS IDENTICAL */
bool ROSETTA::operator!=( const ROSETTA &p ) const
{	return( ! isEqual( &p ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* PUSH ONE SET INTO ANOTHER, OVER-WRITE DIFFERENT VALUES */
bool ROSETTA::insert( const ROSETTA *extra )
{
	if ( NULL == extra || this == extra ) 		// DO NOTHING
		{return( true );
		}
	int	i;
	int	n = extra->count();
	bool	ok = true;
	for ( i = 0; i < n; i++ )
		{ok &= appendMember( extra->pairs[i]->copy( this ) );
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				/* REMOVE A NAMED ELEMENT FROM A ROSETTA */
bool ROSETTA::remove( const std::string name )
{
	if ( ! checkUpdate() )
		{return( false );
		}
	ROSE_BASE *b = findCompound( name, false );
	if ( NULL == b )
		{return( true );		// EFFECTIVELY REMOVED ALREADY
		}
	std::vector<ROSE_BASE *> *pa = &(((ROSETTA *)b->owner_rosetta)->pairs);
	std::vector<ROSE_BASE *>::iterator pi = pa->begin();
	while ( pi != pa->end() )
		{if ( *pi == b )
			{delete b;
			pa->erase( pi );
			break;
			}
		pi++;
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* SET ON ROSETTA EQUAL TO ANOTHER */
ROSETTA &ROSETTA::operator=( const ROSETTA &p )
{
	clear();
	insert( &p );
	return( *this );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	/* PUSH SUBSET OF ONE SET INTO ANOTHER, OVER-WRITE DIFFERENT VALUES */
bool ROSETTA::insertFiltered( const ROSETTA *extra, const ROSETTA_FILTER filter,
	const bool recurse )
{
	if ( NULL == extra || this == extra ) 		// DO NOTHING
		{return( true );
		}
	if ( ! extra->isValid() )
		{return( false );
		}
	int	i;
	int	n = extra->count();
	bool	ok = true;
	ROSE_BASE	*b;
	for ( i = 0; i < n; i++ )
		{b = extra->pairs[i];
		if ( filter( b ) )
			{if ( b->type() != typeRosetta || ! recurse )
				{ok &= appendMember( b->copy( this ) );
				}
			else		// APPLY FILTER TO SUB-ROSETTA
				{ROSETTA	*sub = new ROSETTA();
				sub->insertFiltered( ((ROSE_ROSETTA *) b)->val,
					filter, true );
				if ( sub->isValid() )
					{ok &= attachSubRosetta( b->getName(),
						sub );
					}
				else
					{delete sub;
					ok = false;
					}
				}
			}
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* APPEND A NEW PAIR INTO SET */
bool ROSETTA::appendMember( ROSE_BASE *b )
{
	if ( NULL == b )
		{error( "ROSETTA::appendMember, NULL" );
		return( false );
		}
	if ( ! b->isValid() )
		{error( "ROSETTA:appendMember, new member not valid" );
		return( false );
		}
	nchanges++;
	int	np = pairs.size();
	if ( sorted && np > 0 ) 	// IS SORTED ARRAY STILL IN ORDER
		{sorted = b->greaterThan( pairs[np-1] );
		}
	pairs.push_back( b );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string ROSETTA::serializeOut( void ) const
{
	char	buf[30];
	sprintf( buf, "[%d", pairs.size() ); // WRITE NPAIRS AS FIRST FIELD
	std::string	ser = buf;
	std::vector<ROSE_BASE *>::const_iterator it = pairs.begin();
	while ( it != pairs.end() )
		{
		ser += "&";
		ser += (*it)->serializeOut();
		it++;
		}
	ser += "]";
	return( ser );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string ROSETTA::exportXML( const std::string name ) const
{
	char	buf[100];
	sprintf( buf, "\" t=\"R\" members=\"%d\">", pairs.size() );
	std::string	ser = std::string("\n<r n=\"") + name + buf;
	std::vector<ROSE_BASE *>::const_iterator it = pairs.begin();
	while ( it != pairs.end() )
		{ser += (*it)->exportXML();
		it++;
		}
	ser += "\n</r>";
	return( ser );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string ROSETTA::exportFlatXML( const std::string label ) const
{
	std::string	ser;
	std::vector<ROSE_BASE *>::const_iterator it = pairs.begin();
	std::string	prefix = label + ".";
	while ( it != pairs.end() )
		{ser += (*it)->exportFlatXML( prefix );
		it++;
		}
	return( ser );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::checkInsert( void )
{
	if ( allow_insert )
		{nchanges++;
		return( true );
		}
	error( "insert not allowed" );
	return( false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::checkUpdate( void )
{
	if ( allow_update )
		{nchanges++;
		return( true );
		}
	error( "update not allowed" );
	return( false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define	CHECK_INSERT if ( !checkInsert() ){ return(NULL); }
#define	CHECK_UPDATE if ( !checkUpdate() ){ return(NULL); }
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setFlagPRet( const std::string name )
{
	ROSE_FLAG	*b = (ROSE_FLAG *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_FLAG( this, name );
		appendMember( b );
		}	// FLAGS ARE NOT UPDATED SINCE THEY HAVE NO VALUE
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setFlag( const std::string name )
{	return( NULL != setFlagPRet( name ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setIntPRet( const std::string name, const int value )
{
	ROSE_INT	*b = (ROSE_INT *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_INT( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setInt( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setInt( const std::string name, const int value )
{	return( NULL != setIntPRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setBoolPRet( const std::string name, const bool value )
{
	ROSE_BOOL	*b = (ROSE_BOOL *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_BOOL( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setBool( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setBool( const std::string name, const bool value )
{	return( NULL != setBoolPRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setRealPRet( const std::string name, const double value )
{
	ROSE_REAL	*b = (ROSE_REAL *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_REAL( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setReal( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setReal( const std::string name, const double value )
{	return( NULL != setRealPRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setStringPRet( const std::string name, const std::string value )
{
	ROSE_STRING	*b = (ROSE_STRING *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_STRING( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setString( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setString( const std::string name, const std::string value )
{	return( NULL != setStringPRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setDatePRet( const std::string name, const XDATE value )
{
	ROSE_XDATE	*b = (ROSE_XDATE *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_XDATE( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setDate( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setDate( const std::string name, const XDATE value )
{	return( NULL != setDatePRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setTimePRet( const std::string name, const XTIME value )
{
	ROSE_XTIME	*b = (ROSE_XTIME *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_XTIME( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setTime( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setTime( const std::string name, const XTIME value )
{	return( NULL != setTimePRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setBinobPRet( const std::string name, const XBINOB value )
{
	ROSE_XBINOB	*b = (ROSE_XBINOB *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_XBINOB( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setBinob( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setBinob( const std::string name, const XBINOB value )
{	return( NULL != setBinobPRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSE_BASE *ROSETTA::setRosettaPRet( const std::string name, const ROSETTA * value )
{
	ROSE_ROSETTA	*b = (ROSE_ROSETTA *) find( name, false );
	if ( NULL == b )
		{CHECK_INSERT;
		b = new ROSE_ROSETTA( this, name, value );
		appendMember( b );
		}
	else
		{CHECK_UPDATE;
		b->setRosetta( value );
		}
	return( b );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::setRosetta( const std::string name, const ROSETTA * value )
{	return( NULL != setRosettaPRet( name, value ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			/* ASSUME OWNERSHIP OF EXTERNAL ROSETTA OBJECT */
bool ROSETTA::attachSubRosetta( const std::string name, ROSETTA *sub )
{
	if ( NULL == sub )
		{return( false );
		}
	ROSE_ROSETTA	*b = (ROSE_ROSETTA *) find( name, false );
	if ( NULL != b )
		{if ( b->type() != ROSETTA::typeRosetta )
			{return( false );
			}
		if ( ! checkUpdate() )
			{return( false );
			}
		delete b->val;		// REMOVE EARLIER CONTENTS
		b->val = NULL;
		}
	else
		{b = new ROSE_ROSETTA( this, name );
		if ( NULL == b || ! b->isValid() ) 	// ILLEGAL NAME
			{delete b;
			b = NULL;
			return( false );
			}
		if ( ! checkInsert() )
			{return( false );
			}
		appendMember( b );
		}
	b->val = sub;
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::insertFlag( const ROSETTA &src, const std::string name )
{	ROSE_BASE	*b = src.findCompound( name, true );
	if ( NULL == b || b->type() != typeFlag )
		{return( false );
		}
	setFlag( name );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::flagExists( const std::string name ) const
{	return( typeFlag == getType( name ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/* MACROS, T=TYPE, X=NAME */
#define INOUT(t,x)							\
t ROSETTA::get##x ( const std::string name ) const			\
{	ROSE_BASE *b = findCompound( name, true );			\
	return( ( NULL != b ) ? b->get##x () : (t) error##x );		\
}									\
t ROSETTA::get##x ( const int index ) const				\
{return( ( index>=0 && index<(int)pairs.size() )			\
	? pairs[index]->get##x () : (t) error##x ); 			\
}									\
t ROSETTA::get##x##Default ( const std::string name, t def ) const 	\
{	ROSE_BASE *b = findCompound( name, false );			\
	return( ( NULL != b ) ? b->get##x () : def );			\
}									\
t ROSETTA::get##x##Default ( const int index, t def ) const		\
{return( ( index>=0 && index<(int)pairs.size() )			\
	? pairs[index]->get##x () : def );	 			\
}									\
bool ROSETTA::insert##x ( const ROSETTA &src, const std::string name )  \
{	ROSE_BASE	*b = src.findCompound( name, true );		\
	if ( NULL == b || b->type() != type##x )			\
		{return( false );					\
		}							\
	set##x ( name, b->get##x() );					\
	return( true );							\
}
INOUT(int,Int)
INOUT(bool,Bool)
INOUT(double,Real)
INOUT(std::string,String)
INOUT(XDATE,Date)
INOUT(XTIME,Time)
INOUT(XBINOB,Binob)
INOUT(ROSETTA *,Rosetta)
#undef GET
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define PGET(t,x,c)							\
const t *ROSETTA::pointer##x ( const std::string name ) const           \
{	ROSE_BASE *b = findCompound( name, true );                      \
	return( ( NULL != b && b->type() == type##x  )                  \
		? &(((c *)b)->val) : NULL );                            \
}                                                                       \
const t *ROSETTA::pointer##x ( const int index ) const                  \
{                                                                       \
	if ( index < 0 || index >= (int)pairs.size() )                  \
		{return( NULL );                                        \
		}                                                       \
	ROSE_BASE *b = pairs[index];                                    \
	return( ( b->type() == type##x )                                \
		? &(((c *)b)->val) : NULL );                            \
}
PGET(std::string,String,ROSE_STRING)
PGET(XDATE,Date,ROSE_XDATE)
PGET(XTIME,Time,ROSE_XTIME)
PGET(XBINOB,Binob,ROSE_XBINOB)
#undef PGET
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSETTA *ROSETTA::pointerRosetta( const std::string name ) const
{	ROSE_BASE *b = findCompound( name, true );
	return( ( NULL != b && b->type() == typeRosetta  )
		? ((ROSE_ROSETTA *)b)->val : NULL );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSETTA *ROSETTA::pointerRosetta( const int index ) const
{
	if ( index < 0 || index >= (int)pairs.size() )
		{return( NULL );
		}
	ROSE_BASE *b = pairs[index];
	return( ( b->type() == typeRosetta )? ((ROSE_ROSETTA *)b)->val : NULL );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
static int offset( char *s, char seek )
{
	int	count = 0;
	while ( s[count] != '\0' )
		{if ( s[count] == seek )
			{return( count );
			}
		count++;
		}
	return( -1 );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::serializeInMember( const int typ, const char *nam, char *sval )
{
	ROSE_BASE	*b = NULL;
	if ( typeInt == typ )
		{b = setIntPRet( nam, errorInt );
		}
	else if ( typeString == typ )
		{b = setStringPRet( nam, errorString.c_str() );
		if ( ! b->decodeURL( sval ) )
			{return( false );
			}
		}
	else if ( typeDate == typ )
		{b = setDatePRet( nam, (XDATE) errorDate );
		}
	else if ( typeTime == typ )
		{b = setTimePRet( nam, (XTIME) errorTime );
		}
	else if ( typeBinob == typ )
		{b = setBinobPRet( nam, (XBINOB) errorBinob );
		}
	else if ( typeRosetta == typ )
		{b = setRosettaPRet( nam, (ROSETTA *) errorRosetta );
		}
	else if ( typeBool == typ )
		{b = setBoolPRet( nam, errorBool );
		}
	else if ( typeReal == typ )
		{b = setRealPRet( nam, errorReal );
		}
	else if ( typeFlag == typ )
		{b = setFlagPRet( nam );
		}
	if ( NULL == b )
		{return( false );
		}
	return( b->serializeInValue( sval ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSETTA::serializeInSplit( char *c, const bool stop_on_error )
{
	char	*init = c;
	while ( isdigit( *c ) )		// EXTRACT NPAIRS
		{c++;
		}
	if ( *c != AND )
		{return( false );
		}
	*c++ = EOS;
	int	npairs_expected = atoi( init );
	if ( npairs_expected < 1 )
		{return( false );
		}
	char	*name, *value;
	int	typ, nesting;
	int	count = 0;
	bool	more = true;
	bool	ok = true;
	do					// EXTRACT TYPE#NAME=VALUE&
		{typ = (int) *c++;		// TYPE IS ALWAYS SINGLE BYTE
		if ( *c++ != HASH )
			{return( false );
			}
		name = c; 	   			// ISOLATE NAME
		while ( isalnum( *c ) || UNDERSCORE == *c )
			{c++;
			}
		if ( EQUALS != *c || name == c )
			{return( false );
			}
		*c++ = EOS;
		value = c;				// ISOLATE VALUE
		nesting = 0;
		while( ( *c != AND && *c != RSB ) || nesting > 0 )
			{if ( EOS == *c )		// PREMATURE END
				{return( false );
				}
			if ( LSB == *c )
				{nesting++;
				}
			else if ( RSB == *c )
				{nesting--;
				}
			c++;
			}
		if ( *c == RSB )
			{more = false;
			}
		*c++ = EOS;
		if ( ! serializeInMember( typ, name, value ) )
			{if ( stop_on_error )
				{return( false );
				}
			else
				{ok = false;
				}
			}
		count++;
		}
		while( more );
	if ( ( ! ok ) || *c != EOS )
		{return( false );	// EXTRA CHARACTERS AFTER ']'
		}
	return( count == npairs_expected );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	/* RE-CONSTRUCT OBJECT FROM SERIALIZATION, APPENDING CONTENTS */
/* "[NPAIRS&TYPE0:NAME0=VALUE0&....TYPEX:NAMEX=VALUEX]" WITH   NPAIR=X+1 */
bool ROSETTA::serializeIn( const std::string serial_in,
	const bool stop_on_error )
{
	if ( serial_in == "[0]" )
		{return( true ); 		// EMPTY (VALID) ROSETTA
		}
	const char	*serial = serial_in.c_str();
	if ( *serial != '[' )
		{valid = false;
		return( false );
		}
	int	len = strlen( serial );
	char	*c = (char *) malloc( len + 1 );
	if ( NULL == c )
		{valid = false;
		return( false );
		}
	strcpy( c, serial+1 );			// CREATE MODIFY-ABLE BUFFER
	bool	ok = serializeInSplit( c, stop_on_error );
	free( c );
	valid &= ok;
	return( ok );
}
//---------------------------------------------------------------------------
  /* REMOVE DUPLICATE WHITE-SPACE AND CONVERT SINGLE WHITE-SPACE TO SPACE */
std::string ROSETTA::compressString( const std::string input )
{
	if ( input.empty() )
		{return( "" );
		}
	char	*com = (char *) malloc( input.size() + 2 );
	if ( NULL == com )
		{return( "" );
		}
	const	char	*c = input.c_str();
	int	pos = 0;
	bool	last_space = true;
	while ( *c != 0 )
		{
		if ( isspace( *c ) )
			{if ( ! last_space )
				{last_space = true;
				com[pos++] = ' ';
				}
			}
		else
			{last_space = false;
			com[pos++] = *c;
			}
		c++;
		}
	if ( last_space && pos > 0 )
		{pos--;
		}
	com[pos] = 0;
	std::string	val = std::string( com );
	free( com );
	return( val );
}
//---------------------------------------------------------------------------
				/* CONVERT S IN-SITU TO LOWERCASE */
static char rosettaMakeLower( char c )
{	return( (char) tolower( c ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
static char rosettaMakeUpper( char c )
{	return( (char) tolower( c ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::makeLowerCase( std::string *s )
{
	if ( NULL == s )
		{return;
		}
	std::transform( s->begin(), s->end(), s->begin(), rosettaMakeLower );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ROSETTA::makeUpperCase( std::string *s )
{
	if ( NULL == s )
		{return;
		}
	std::transform( s->begin(), s->end(), s->begin(), rosettaMakeUpper );
}
//===========================================================================





