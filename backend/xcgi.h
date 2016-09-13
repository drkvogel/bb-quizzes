#ifndef XCGI_H_INCLUDED
#define XCGI_H_INCLUDED       1
/*===========================================================================*/
/*		UTILITIES FOR CONSTRUCTING CGI SCRIPTS			*/
/*===========================================================================*/
#include "rosetta.h"
#include <stdio.h>
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
class XCGI
{
private:
	FILE	*flog;
	bool	is_valid;
	int	method;
	int 	nextParam( const char *in, const char terminator, char **out );
	int 	findMethod( void );
	void 	splitParams( const char *prm );
	int 	unhex( const char *hx );
	void 	decodeURL( char *txt );
	void 	log( const char *txt, ... );    // WRITE INTERNAL MESSAGES
public:
	static	int    	debug;
	static	int	max_param_num;		// CRASH PREVENTION LIMITS
	static	int	max_param_len;
	static	int	max_param_totlen;
	static	char	*logname;
	static	void 	setDebug( const int dbg );      // SET INTERNAL DEBUG VALUE
	ROSETTA	param;
	XCGI( int ac, char **av );
	~XCGI( void );
	bool 	isValid( void ) const;
	int	getDebug( void ) const;
	int	getMethod( void ) const;
	std::string	getMethodName( void ) const;
	bool	paramExists( const std::string pname ) const;
	int 	paramAsInt( const std::string pname ) const;
	void	flush( void ) const;
	void 	verbatim( const char *vfname ); // READ FILE AND COPY TO OUTPUT
	void 	end( void );			// EXIT NICELY
	void 	endFail( const char *err_txt );	// TERMINATE DODGY REQUEST AND EXIT
	void 	writeHeader( const int typ );	// WRITE INITIAL MIME HEADER TO OUTPUT
	void 	paramShowall( void );

	static	const	int	methodError 	= 0;
	static	const	int	methodGet 	= 'G';
	static	const	int	methodPost 	= 'P';
	static	const	int	methodString 	= 'C';
	static	const	int	methodFile	= 'F';
	static	const	int	methodUnknown	= 'U';

	static	const	int	typeUnknown	= 0;
	static	const	int	typeHtml	= 'H';
	static	const	int	typePlain	= 'P';
	static	const	int	typeTiff	= 'T';
    static  const   int typeJSON    = 'J';

	static	const	int	invalidInt	= (-999666333);
};
/*===========================================================================*/
#endif                                                  	/* XCGI.H */
