#ifndef xbinobH
#define xbinobH
#include <string>
/* OBJECT TO SIMPLIFY HANDLING BINARY DATA */
//---------------------------------------------------------------------------
class XBINOB
{
private:
	int	nbytes;			// -1 IF DATA IS NOT VALID
	unsigned char *value;
	void	setInvalid( void );
	static	bool 	use_exceptions;
protected:
	virtual	void	error( const std::string etxt ) const;
public:
	XBINOB( void );
	XBINOB( const int input_size, const unsigned char *data );
	XBINOB( const std::string b64 );
	XBINOB( const XBINOB &b );			// COPY CONSTRUCTOR
	virtual	~XBINOB( void );
	void	clear( void );
	bool	insert( const int input_size, const unsigned char *data );
	bool	insert( const XBINOB &b );
	bool	append( const int input_size, const unsigned char *data );
	bool	append( const XBINOB &b );
	bool	extract( int *output_size, unsigned char **data ) const;
	const unsigned char *data( void ) const;
	std::string	extractHex( void ) const;
	std::string	extractBase64( void ) const;
	bool 	insertHex( const std::string hex );
	bool 	insertBase64( const std::string b64 );
	bool	isValid( void ) const;
	int	size( void ) const;
	XBINOB	&operator=( const XBINOB &b );
	bool	isEqual( const XBINOB &b ) const;
	bool	operator==(const XBINOB &b ) const;
	bool	operator!=(const XBINOB &b ) const;
	static	void	useExceptions( const bool ue );
	static	bool 	usingExceptions( void );
};
//---------------------------------------------------------------------------
#endif

