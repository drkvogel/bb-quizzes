#ifndef xemailH
#define xemailH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "xerror.h"
#include "xtime.h"
//---------------------------------------------------------------------------
class XBINOB;
class XDB;
//---------------------------------------------------------------------------
class XEMAIL : public XERROR
{
private:
	int	msg_id;
	const	std::string	owner, auth, subj, body_text, addr_sender;
	std::string	addr_reply, notes;
	std::vector<std::string>	addr_to, addr_cc, addr_bcc;
protected:
	bool 	inVector( const std::vector<std::string> *v,
			const std::string a ) const;
	std::string 	catenateAddresses( const std::vector<std::string> *v );
	int 	getNextId( XDB *db ) const;
public:
	XEMAIL( const std::string owner_ident, const std::string authoriser,
		const std::string subject, const std::string sender,
		const std::string body );
	virtual	~XEMAIL( void );
	std::string	addTo( const std::string address );
	std::string	addCC( const std::string address );
	std::string	addBCC( const std::string address );
	std::string	setReplyTo( const std::string address );
	std::string	setNotes( const std::string nots );
	std::string	sendViaDB( XDB *db );
	std::string	sendViaDBScheduled( XDB *db, const XTIME when );
	std::string	addAttachment( const std::string ctype,
		const std::string ctrenc, const XBINOB *contents );
	int	getMsgId( void ) const;
	static	std::string isPlausibleAddress( const std::string ad );
	static	const	char	address_separator = ',';
};
//---------------------------------------------------------------------------
#endif

