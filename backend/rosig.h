#ifndef rosigH
#define rosigH
#include "rosebase.h"
#include "rosetta.h"
#include <string>
#include <vector>
//---------------------------------------------------------------------------
class ROSIG_BASE
{
private:
public:
	std::string	parent;
	ROSE_BASE const *owner;
	ROSIG_BASE( const ROSE_BASE *own, const std::string par );
	~ROSIG_BASE( void );
};
//---------------------------------------------------------------------------
class ROSIG : public ROSETTA
{
private:
	bool	is_valid;
	int	mode;
	std::string	prefix;
	static	int	default_mode;
protected:
	std::vector<ROSIG_BASE> pairs_filter; // POINTERS TO CHECKED ELEMENTS
	const	ROSETTA	*target;
	ROSETTA_FILTER	filter_mask;
	bool identifyRos( const ROSETTA *r, const std::string path );
	bool identify( void );
public:
	ROSIG( const ROSETTA *data, ROSETTA_FILTER filter,
		const int this_mode = 0 );
	~ROSIG( void );
	bool 	isValid( void ) const;
	int	getMode( void ) const;
	std::string 	getSigInput( void ) const;
	std::string 	getSignature( void ) const;
	bool	verifySignature( const std::string sig ) const;
				/* FILTER FUNCTIONS FOR EXTERNAL USE */
	static	bool	setDefaultMode( const int md );
	static	int	getDefaultMode( void );
	static	bool 	filter_null( const ROSE_BASE *b );
	static 	bool 	filter_underscore( const ROSE_BASE *b );
	static	const	int	ModeData = 1;
	static	const	int	ModeName = 2;
	static	const	int	ModeFull = 3;
	static	const	char	*PrefixData;
	static	const	char	*PrefixName;
	static	const	char	*PrefixFull;
	static	bool	verify( const ROSETTA *data, ROSETTA_FILTER filter,
		const std::string sig );
};
//---------------------------------------------------------------------------
#endif

