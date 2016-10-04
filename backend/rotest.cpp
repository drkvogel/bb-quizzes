//---------------------------------------------------------------------------
/*
			ROSETTA TEST HARNESS
*/
//---------------------------------------------------------------------------
#include <stdio.h>
#include "rosetta.h"
//---------------------------------------------------------------------------
int	nfails = 0;
FILE	*fo = NULL;
//---------------------------------------------------------------------------
#define	I0	(-1234)
#define	R0	(-2345.6)
#define	L0	(12345671234567LL)
#define	S0	"Negative number"
#define	X0	(true)
#define	B0	"BinarY"
#define	B0N	6
#define	I1	(1)
#define	R1	(7654321.1234567)
#define	L1	(-8765432187654321LL)
#define	S1	"three"
#define	X1	(false)
#define	B1	"bInArY ObJeCt"
#define	B1N	13
#define	I2	(22)
#define	R2	(33.44556677e+29)  // ~ 3.3e+30
#define	L2	(303)
#define	S2	"forty four"
#define	X2	(true)
//---------------------------------------------------------------------------
std::string	stmp, sdbg;
std::string	output_file = "";
XDATE	d0;
XDATE	*d1 = NULL, *d2 = NULL;
XTIME	t2;
XTIME	*t1 = NULL;
XBINOB	b0;
XBINOB	*b1 = NULL;
ROSETTA	r0;
ROSETTA	*r1 = NULL, *r2 = NULL;
//---------------------------------------------------------------------------
void checkTrue( const bool true_expr, const std::string txt )
{
	fflush( fo );
	if ( ! true_expr )
		{nfails++;
		fprintf( fo, "\nFAIL %d : %s", nfails, txt.c_str() );
		fflush( fo );
		}
}
//---------------------------------------------------------------------------
#define	CHK( expr )	checkTrue( (expr), #expr );
//---------------------------------------------------------------------------
void createBasics( void )
{
	fprintf( fo, "\nCreating basic objects" );
						// INITIAL DATE OBJECTS
	d0.set( 1944, 6, 6 );
	d1 = new XDATE( 2001, 2, 3 );
	d2 = new XDATE();
	d2->set( 2001, 8, 4 );
						// INITIAL TIME OBJECTS
	t1 = new XTIME( 1977, 5, 6, 2, 0, 0 );
	t2.set( 2001, 2, 3, 4, 5, 6 );
						// INITIAL XBINOB OBJECTS
	b0.insert( B0N, (const unsigned char *) B0 );
	b1 = new XBINOB( B1N, (const unsigned char *) B1 );
						// INITIAL ROSETTA OBJECT 0
	r0.setInt( "in0", I0 );
	r0.setReal( "re0", R0 );
	r0.setLint( "li0", L0 );
	r0.setString( "st0", S0 );
	r0.setBinob( "bi0", b0 );
	r0.setBool( "xb0", X0 );

						// INITIAL ROSETTA OBJECT 1
	r1 = new ROSETTA();
	r1->setInt( "in1", I1 );
	r1->setReal( "re1", R1 );
	r1->setLint( "li1", L1 );
	r1->setString( "st1", S1 );
	r1->setDate( "da1", *d1 );
	r1->setBinob( "bi1", *b1 );
	r1->setBool( "xb1", X1 );

	r1->setTime( "ti1", *t1 );
						// INITIAL ROSETTA OBJECT 2
	r2 = new ROSETTA();
	r2->setTime( "ti2", t2 );
	r2->setDate( "da2", *d2 );
	stmp = S2;
	r2->setString( "st2", stmp );
	r2->setRosetta( "r1", r1 );		// COPY CONTENTS
	r2->setReal( "re2", R2 );
	r2->setInt( "in2", I2 );
	r2->setLint( "li2", L2 );
	r2->setBool( "xb2", X2 );
}
//---------------------------------------------------------------------------
void removeBasics( void )
{
	fprintf( fo, "\nRemoving basic objects" );
	delete	d1;
	delete	d2;
	delete	t1;
	delete	b1;
	delete	r1;
	delete 	r2;

}
//---------------------------------------------------------------------------
void basic( void )
{
	fprintf( fo, "\nChecking creation" );
	CHK( r0.isValid() );
	CHK( r1->isValid() );
	CHK( r2->isValid() );
	CHK( ROSETTA::typeInt    == r0.getType( "in0" ) );
	CHK( ROSETTA::typeReal   == r0.getType( "re0" ) );
	CHK( ROSETTA::typeString == r0.getType( "st0" ) );
	CHK( ROSETTA::typeLint   == r0.getType( "li0" ) );
	CHK( ROSETTA::typeBool   == r0.getType( "xb0" ) );
	CHK( ROSETTA::typeInt    == r1->getType( "in1" ) );
	CHK( ROSETTA::typeReal   == r1->getType( "re1" ) );
	CHK( ROSETTA::typeLint   == r1->getType( "li1" ) );
	CHK( ROSETTA::typeBool   == r1->getType( "xb1" ) );
	CHK( ROSETTA::typeString == r1->getType( "st1" ) );
	CHK( ROSETTA::typeDate   == r1->getType( "da1" ) );
	CHK( ROSETTA::typeTime   == r1->getType( "ti1" ) );
	CHK( ROSETTA::typeInt    == r2->getType( "in2" ) );
	CHK( ROSETTA::typeReal   == r2->getType( "re2" ) );
	CHK( ROSETTA::typeLint   == r2->getType( "li2" ) );
	CHK( ROSETTA::typeBool   == r2->getType( "xb2" ) );
	CHK( ROSETTA::typeString == r2->getType( "st2" ) );
	CHK( ROSETTA::typeTime   == r2->getType( "ti2" ) );
	CHK( ROSETTA::typeRosetta== r2->getType( "r1" ) );
	CHK( ROSETTA::typeInt    == r2->getType( "r1.in1" ) );
	CHK( ROSETTA::typeReal   == r2->getType( "r1.re1" ) );
	CHK( ROSETTA::typeString == r2->getType( "r1.st1" ) );
	CHK( ROSETTA::typeDate   == r2->getType( "r1.da1" ) );
	CHK( ROSETTA::typeTime   == r2->getType( "r1.ti1" ) );
}
//---------------------------------------------------------------------------
void equalities( void )
{
	fprintf( fo, "\nChecking equalities" );
	CHK( I0 == r0.getInt( "in0" ) );
	CHK( R0 == r0.getReal( "re0" ) );
	CHK( L0 == r0.getLint( "li0" ) );
	CHK( S0 == r0.getString( "st0" ) );
	CHK( X0 == r0.getBool( "xb0" ) );

	CHK( I1 == r1->getInt( "in1" ) );
	CHK( R1 == r1->getReal( "re1" ) );
	CHK( L1 == r1->getLint( "li1" ) );
	CHK( S1 == r1->getString( "st1" ) );
	CHK( X1 == r1->getBool( "xb1" ) );

	CHK( *d1 == r1->getDate( "da1" ) );
	CHK( *t1 == r1->getTime( "ti1" ) );
	CHK( I2  == r2->getInt( "in2" ) );
	CHK( R2  == r2->getReal( "re2" ) );
	CHK( L2  == r2->getLint( "li2" ) );
	CHK( S2  == r2->getString( "st2" ) );
	CHK( X2  == r2->getBool( "xb2" ) );
	CHK( t2  == r2->getTime( "ti2" ) );
	ROSETTA	*rtmp = r2->getRosetta( "r1" );	// AVOID MEMORY LEAK ?
	CHK( *r1 == *rtmp );
	delete rtmp;
	ROSETTA	*ptmp = r2->pointerRosetta( "r1" );
	CHK( *r1 == *ptmp );
}
//---------------------------------------------------------------------------
void transformations( void )
{
	fprintf( fo, "\nChecking transformations" );
	const	std::string	ser0 = r0.serializeOut();
	const	std::string	ser1 = r1->serializeOut();
	const	std::string	ser2 = r2->serializeOut();
	fprintf( fo, "\nSer0 : %s", ser0.c_str() );
	fprintf( fo, "\nSer1 : %s", ser1.c_str() );
	fprintf( fo, "\nSer2 : %s", ser2.c_str() );
						// DE-SERIALIZE COPIES
	ROSETTA	u0( ser0 );
	ROSETTA	u1( ser1 );
	ROSETTA	u2( ser2 );
	CHK( u0.isValid() );
	CHK( u1.isValid() );
	CHK( u2.isValid() );
	CHK( u0 == r0 );
	CHK( u1 == *r1 );
	CHK( u2 == *r2 );
	CHK( ser0 == u0.serializeOut() );
	CHK( ser1 == u1.serializeOut() );
	CHK( ser2 == u2.serializeOut() );
						// CONSTRUCT COPIES
	ROSETTA	*c0 = new ROSETTA( r0 );
	ROSETTA	*c1 = new ROSETTA( r1 );
	ROSETTA	*c2 = new ROSETTA( r2 );
	CHK( c0->isValid() );
	CHK( c1->isValid() );
	CHK( c2->isValid() );
	CHK( *c0 == r0 );
	CHK( *c1 == *r1 );
	CHK( *c2 == *r2 );
	CHK( ser0 == c0->serializeOut() );
	CHK( ser1 == c1->serializeOut() );
	CHK( ser2 == c2->serializeOut() );

	sdbg = c2->serializeOut();
						// MAKE COPIES
	ROSETTA	m0 = r0;
	ROSETTA	m1 = *r1;
	ROSETTA	m2 = *r2;
	CHK( m0.isValid() );
	CHK( m1.isValid() );
	CHK( m2.isValid() );
	CHK( ser0 == m0.serializeOut() );
	CHK( ser1 == m1.serializeOut() );
	CHK( ser2 == m2.serializeOut() );
						// SET COPIES
	ROSETTA	k0, k1, k2;
	k0 = r0;
	k1 = r1;  	// ?
	k2 = r2;
	CHK( k0.isValid() );
	CHK( k1.isValid() );
	CHK( k2.isValid() );
	CHK( ser0 == k0.serializeOut() );
	CHK( ser1 == k1.serializeOut() );
	CHK( ser2 == k2.serializeOut() );


	delete c0;
	delete c1;
	delete c2;
}
//---------------------------------------------------------------------------
void removals( void )
{
	std::string	ser0, ser1, ser2;
	fprintf( fo, "\nChecking removals" );
	CHK( r0.remove( "re0" ) );

	ser0 = r0.serializeOut();
	fprintf( fo, "\nSer0 : %s", ser0.c_str() );

	CHK( r2->remove( "ti2" ) );
	CHK( r2->remove( "r1.da1" ) );

	ser1 = r1->serializeOut();
	ser2 = r2->serializeOut();
	fprintf( fo, "\nSer1 : %s", ser1.c_str() );
	fprintf( fo, "\nSer2 : %s", ser2.c_str() );

	CHK( r2->remove( "r1" ) );

	ser2 = r2->serializeOut();
	fprintf( fo, "\nSer2 : %s", ser2.c_str() );
}
//---------------------------------------------------------------------------
static bool errHand( const ROSETTA *r, const int cod, const std::string msg )
{
	if ( NULL == r )
		{printf( "\nerrHand, NULL *r" );
		}
	printf( "\nERROR %d\n%d : %s\n", ++nfails, cod, msg.c_str() );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
static bool wrnHand( const ROSETTA *r, const int cod, const std::string msg )
{
	if ( NULL == r )
		{printf( "\nwrnHand, NULL *r" );
		}
	printf( "\nWARNING %d\n%d : %s\n", ++nfails, cod, msg.c_str() );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void setHandlers( void )
{
	ROSETTA::setErrorHandler( errHand );
	ROSETTA::setWarningHandler( wrnHand );
}
//---------------------------------------------------------------------------
void run( void )
{
	setHandlers();
	createBasics();
	basic();
	equalities();
	transformations();
	removals();
	removeBasics();
}
//---------------------------------------------------------------------------
void showUsage( void )
{
	printf( "\nusage: rotest [-oFILE]\n" );
}
//---------------------------------------------------------------------------
bool getParams( int argc, char **argv )
{
	bool	ok = true;
	char	*c;
	int	i;
	for ( i = 1; i < argc; i++ )
		{
		c = argv[i];
		if ( *c != '-' || strlen( c ) < 3 )
			{printf( "\nParameters should begin with '-'" );
			ok = false;
			break;
			}
		switch( c[1] )
			{
			case 'o':
				output_file = *(c+2);
				break;
			default:
				printf( "Unrecognised parameter %s", c );
				ok = false;
				break;
			}
		}
	if ( ! ok )
		{return( false );
		}
	if ( output_file != "" )
		{fo = fopen( output_file.c_str(), "w" );
		if ( NULL == fo )
			{printf( "\nFailed to open output file \"%s\"",
				output_file.c_str() );
			return( false );
			}
		printf( "\nOpened output file \"%s\"", output_file.c_str() );
		}
	return( true );
}
//---------------------------------------------------------------------------
int main( int argc, char **argv )
{
	fo = stdout;
	if ( ! getParams( argc, argv ) )
		{showUsage();
		exit( EXIT_FAILURE );
		}
	try
		{run();
		}
	catch ( ... )
		{
		fprintf( fo, "\nUnhandled exception thrown" );
		nfails++;
		}
	fprintf( fo, "\nEND of run, %d failures\n", nfails );
	if ( stdout != fo )
		{fclose( fo );
		}
	return( EXIT_SUCCESS );
}
//---------------------------------------------------------------------------


