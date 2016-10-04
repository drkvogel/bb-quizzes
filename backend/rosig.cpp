#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "rosig.h"
#include "xmd5.h"
//===========================================================================
ROSIG_BASE::ROSIG_BASE( const ROSE_BASE *own, const std::string par )
	:
	owner( own ),
	parent( par )
{
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSIG_BASE::~ROSIG_BASE( void )
{
}
//===========================================================================
bool ROSIG::filter_null( const ROSE_BASE *b )
{						// INCLUDE ALL ITEMS
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSIG::filter_underscore( const ROSE_BASE *b )
{               	// OMIT ANY ITEM WHO'S NAME STARTS WITH AN UNDER_SCORE
	std::string	s = b->getName();
	const	char	*c = s.c_str();
	return( NULL != c && '_' != *c );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int	ROSIG::default_mode = ROSIG::ModeFull;
const	char	*ROSIG::PrefixData = "MD5:";
const	char	*ROSIG::PrefixName = "MN5:";
const	char	*ROSIG::PrefixFull = "MF5:";
//---------------------------------------------------------------------------
ROSIG::ROSIG( const ROSETTA *data, ROSETTA_FILTER filter, const int this_mode )
	:
	ROSETTA(),
	target( data ),
	filter_mask( filter ),
	mode( this_mode ),	// FIXED AT TIME OF CREATION
	prefix( "" ),
	is_valid( true )
{
	if ( NULL == data || ! data->isValid() )
		{is_valid = false;
		return;
		}
	if ( 0 == mode )
		{mode = default_mode;
		}
	switch( mode )
		{case ROSIG::ModeData:
			prefix = PrefixData;
			break;
		case ROSIG::ModeName:
			prefix = PrefixName;
			break;
		case ROSIG::ModeFull:
			prefix = PrefixFull;
			break;
		default:
			break;
		}
	if ( prefix.size() != 4 )
		{is_valid = false;
		return;
		}
	identify();
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ROSIG::~ROSIG( void )
{
}
//---------------------------------------------------------------------------
bool ROSIG::isValid( void ) const
{
	return( is_valid );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSIG::setDefaultMode( const int md )
{
	if ( md == ModeData || md == ModeName || md == ModeFull )
		{default_mode = md;
		return( true );
		}
	return( false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int ROSIG::getDefaultMode( void )
{
	return( default_mode );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int ROSIG::getMode( void ) const
{
	return( mode );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSIG::identifyRos( const ROSETTA *r, const std::string path )
{
	std::vector<ROSE_BASE *>::const_iterator it = r->pairs.begin();
	while ( it != r->pairs.end() )
		{if ( NULL == filter_mask || filter_mask( *it ) )
			{if ( ROSETTA::typeRosetta != (*it)->type() )
				{pairs_filter.push_back( ROSIG_BASE(*it,path) );
				}
			else			// PROCESS RECURSIVELY
				{identifyRos( ((ROSE_ROSETTA *)(*it))->val,
					( path + (*it)->getName() + "." ) );
				}
			}
		it++;
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* StrictWeakOrdering for std::sort BY data-value */
static bool RB_Data_compare( const ROSIG_BASE a, const ROSIG_BASE b )
{
	return( ( a.owner->getName() != b.owner->getName() )
		? ROSETTA_compare( a.owner, b.owner )
		: ( a.owner->getString() < b.owner->getString() ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		/* StrictWeakOrdering for std::sort BY name-path (and full) */
static bool RB_Name_compare( const ROSIG_BASE a, const ROSIG_BASE b )
{
	return( ( a.parent == b.parent )
		? ROSETTA_compare( a.owner, b.owner )
		: ( a.parent < b.parent ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	/* IDENTIFY WHICH ELEMENTS ARE TO BE CHECKED (NULL MASK => ALL) */
bool ROSIG::identify( void )
{
	pairs_filter.clear();
	if ( ! is_valid )
		{return( false );
		}
	identifyRos( target, "" );
	std::sort( pairs_filter.begin(), pairs_filter.end(),
		( ( ModeData == mode ) ? RB_Data_compare : RB_Name_compare ) );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string ROSIG::getSigInput( void ) const
{
	if ( ! is_valid )
		{return( "" );
		}
	std::string	total;
	char	type_buf[8];
	std::vector<ROSIG_BASE>::const_iterator it = pairs_filter.begin();
	while ( it != pairs_filter.end() )
		{
		total += "#";
		if ( ModeFull == mode )
			{sprintf( type_buf, "%c:",
				( ( (unsigned int) it->owner->type() ) % 256 ));
			total += type_buf;
			}
		if ( ModeData != mode )
			{total += it->parent;
			}
		total += it->owner->getName();
		total += "=";
		total += it->owner->getString();
		it++;
		}
	total += "#";
	return( total );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string ROSIG::getSignature( void ) const
{
	if ( ! is_valid )
		{return( "" );
		}
	const	std::string	ss = getSigInput();
	if ( ss.empty() )
		{return( "" );
		}
	const	std::string sig = prefix
		+ XMD5::calcHex( (char *) ss.c_str() );
	return( sig );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSIG::verifySignature( const std::string sig ) const
{	return( getSignature() == sig );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ROSIG::verify( const ROSETTA *data, ROSETTA_FILTER filter,
	const std::string sig )
{
	if ( sig.size() != 36 )
		{return( false );
		}
	int	m = -1;
	if ( 0 == strncmp( sig.c_str(), PrefixData, 4 ) )
		{m = ModeData;
		}
	else if ( 0 == strncmp( sig.c_str(), PrefixName, 4 ) )
		{m = ModeName;
		}
	else if ( 0 == strncmp( sig.c_str(), PrefixFull, 4 ) )
		{m = ModeFull;
		}
	ROSIG	r( data, filter, m );
	const	bool	same = r.verifySignature( sig );
	return( same );
}
//===========================================================================

