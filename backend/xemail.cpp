#include "xemail.h"
#include "xdb.h"
#include "xexec.h"
#include "xquery.h"
//===========================================================================
XEMAIL::XEMAIL( const std::string owner_ident, const std::string authoriser,
	const std::string subject, const std::string sender,
	const std::string body )
	:
	XERROR(),
	owner( ROSETTA::compressString( owner_ident ) ),
	auth( ROSETTA::compressString( authoriser ) ),
	subj( subject ),
	addr_sender( ROSETTA::compressString( sender ) ),
	body_text( body ),
	msg_id( 0 )
{
	if ( owner.empty() )
		{setInvalid( "Authoriser must be non-empty" );
		return;
		}
	if ( auth.empty() )
		{setInvalid( "Authoriser must be non-empty" );
		return;
		}
	if ( subj.empty() )
		{setInvalid( "Subject cannot be empty" );
		return;
		}
	if ( addr_sender.empty() )
		{setInvalid( "Sender cannot be empty" );
		return;
		}
	std::string	e = isPlausibleAddress( addr_sender );
	if ( ! e.empty() )
		{setInvalid( std::string("Bad sender address: ") + e );
		return;
		}
	if ( body.empty() )
		{setInvalid( "Body cannot be empty" );
		}
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XEMAIL::~XEMAIL( void )
{
}
//---------------------------------------------------------------------------
std::string XEMAIL::isPlausibleAddress( const std::string em )
{
	const	int	len = em.size();
	if ( len < 5 )				// MINIMUM WOULD BE "A@B.C"
		{return( "too short to be valid" );
		}
	if ( len > 254 )
		{return( "too long (cannot exceed 254 characters)" );
		}
	const	char	at = '@', dot = '.';
	if ( dot == em[0] || at == em[0] || address_separator == em[0]
			|| dot == em[len-1] || at == em[len-1]
			|| address_separator == em[len-1] )
		{return( "cannot begin or end with dot '.' or '@' or ','" );
		}
	char	last = em[0];
	int	dots_after = 0, at_pos = -1;
	int	i;
	for ( i = 1; i < len; i++ )
		{if ( address_separator == em[i] )
			{return( "commas cannot be part of address" );
			}
		else if ( at == em[i] )
			{if ( at_pos < 0 )
				{at_pos = i;
				if ( at_pos > 64 )
					{return(
			"local-part of address cannot exceed 64 characters" );
					}
				}
			else
				{return( "more than one `@' character present");
				}
			if ( dot == last )
				{return(
				"cannot have '@' immediately after dot '.'" );
				}
			}
		else if ( dot == em[i] )
			{if ( at_pos >= 0 )
				{dots_after++;
				}
			if ( dot == last )
				{return( "cannot have 2 dots '..' adjacent" );
				}
			if ( at == last )
				{return(
		"cannot have dot '.' immediately after '@'" );
				}
			}
		last = em[i];
		}
	if ( at_pos < 0 )
		{return( "'@' character not found" );
		}
	if ( dots_after < 1 )
		{return(
		"must be at least one dot '.' after '@' character");
		}
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XEMAIL::inVector( const std::vector<std::string> *v, const std::string a )
	const
{
	std::vector<std::string>::const_iterator	vi = v->begin();
	while ( vi != v->end() )
		{if ( *vi == a )
			{return( true );
			}
		vi++;
		}
	return( false );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::catenateAddresses( const std::vector<std::string> *v )
{
	std::string	ad;
	std::vector<std::string>::const_iterator	vi = v->begin();
	while ( vi != v->end() )
		{if ( ! ad.empty() )
			{ad += address_separator;
			}
		ad += *vi;
		vi++;
		}
	return( ad );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::addTo( const std::string address )
{
	const	std::string	addr = ROSETTA::compressString( address );
	std::string	e = isPlausibleAddress( addr );
	if ( ! e.empty() )
		{setCaveat( std::string("implausible To address \"" )
			+ addr + "\"" );
		return( e );
		}
	if ( ! inVector( &addr_to, addr ) )
		{addr_to.push_back( addr );
		}
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::addCC( const std::string address )
{
	const	std::string	addr = ROSETTA::compressString( address );
	std::string	e = isPlausibleAddress( addr );
	if ( ! e.empty() )
		{setCaveat( std::string("implausible CC address \"" )
			+ addr + "\"" );
		return( e );
		}
	if ( ! inVector( &addr_cc, addr ) )
		{addr_cc.push_back( addr );
		}
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::addBCC( const std::string address )
{
	const	std::string	addr = ROSETTA::compressString( address );
	std::string	e = isPlausibleAddress( addr );
	if ( ! e.empty() )
		{setCaveat( std::string("implausible BCC address \"" )
			+ addr + "\"" );
		return( e );
		}
	if ( ! inVector( &addr_bcc, addr ) )
		{addr_bcc.push_back( addr );
		}
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::setReplyTo( const std::string address )
{
	const	std::string	addr = ROSETTA::compressString( address );
	std::string	e = isPlausibleAddress( addr );
	if ( ! e.empty() )
		{return( e );
		}
	if ( ! addr_reply.empty() )
		{return( "ReplyTo cannot be set more than once" );
		}
	addr_reply = addr;
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::setNotes( const std::string nots )
{
	notes = nots;
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int XEMAIL::getNextId( XDB *db ) const
{
	XQUERY	qi( db, "SELECT email_nextid.nextval AS eid" );
	const	int	eid = qi.fetchInt( 0 );
	return( eid );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::addAttachment( const std::string ctype,
	const std::string ctrenc, const XBINOB *contents )
{
	return( "This bit of code not written" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::sendViaDB( XDB *db )
{
	const	XTIME	t( 1999, 1, 1, 12, 0, 0 );
	return( sendViaDBScheduled( db, t ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XEMAIL::sendViaDBScheduled( XDB *db, const XTIME when )
{
	if ( ! isValid() )
		{return( "Message parameters previously marked as not-valid" );
		}
	if ( msg_id != 0 )
		{return( "Message already saved to database" );
		}
	const	std::string	ad_to = catenateAddresses( &addr_to );
	const	std::string	ad_cc = catenateAddresses( &addr_cc );
	const	std::string	ad_bc = catenateAddresses( &addr_bcc );
	if ( ad_to.empty() )
		{return( "Address field \"To:\" is empty" );
		}
	const	int	eid = getNextId( db );
	if ( 0 == eid )
		{return( "Unable to fetch unique email ID" );
		}
	XEXEC	xm( db, "INSERT INTO email_out (email_id,owner_ident,subj,body"
		",ad_to,ad_cc,ad_bcc,ad_sender,ad_reply,notes,when"
		",auth)"
		" VALUES "
		" (:ei,:oi,:su,:bo,:to,:cc,:bc,:se,:re,:no,:wh,:au)" );
	xm.param.setInt( "ei", eid );
	xm.param.setString( "oi", owner );
	xm.param.setString( "su", subj );
	xm.param.setString( "bo", body_text );
	xm.param.setString( "to", ad_to );
	xm.param.setString( "cc", ad_cc );
	xm.param.setString( "bc", ad_bc );
	xm.param.setString( "se", addr_sender );
	xm.param.setString( "re", addr_reply );
	xm.param.setString( "no", notes );
	xm.param.setTime(   "wh", when );
	xm.param.setString( "au", auth );
	xm.param.attachTag( "bo", XSQL::blob );
	xm.param.attachTag( "to", XSQL::blob );
	xm.param.attachTag( "cc", XSQL::blob );
	xm.param.attachTag( "bc", XSQL::blob );
	xm.param.attachTag( "no", XSQL::blob );
	const	bool	ok = xm.exec();
	if ( ! ok )
		{return( "Failed to save email to database" );
		}
	msg_id = eid;
	return( "" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int XEMAIL::getMsgId( void ) const
{
	return( msg_id );
}
//===========================================================================

