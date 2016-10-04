#ifndef xregistH
#define xregistH
//---------------------------------------------------------------------------
#include <string.h>
#include <registry.hpp>
#include "xerror.h"
//---------------------------------------------------------------------------
class XREGISTRY : public XERROR
{
private:
	const	std::string	reg_name;
	HKEY__	*root;
	TRegistry	*reg;
	bool 	openForReading( void );
	bool 	openForWriting( void );
	void	close( void );
public:
	XREGISTRY( const std::string registry_name, HKEY__ *root_key );
	XREGISTRY( const std::string registry_name );
	~XREGISTRY( void );
	TRegistry	*getRegPtr( void ) const;
	bool 	getBool(   const std::string name, bool *value );
	bool 	getInt(    const std::string name, int *value );
	bool 	getString( const std::string name, std::string *value );
	bool 	putBool(   const std::string name, const bool value );
	bool 	putInt(    const std::string name, const int value );
	bool 	putString( const std::string name, const std::string value );
};
//---------------------------------------------------------------------------
#endif

