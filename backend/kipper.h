// $Id: kipper.h,v 1.5 2015/08/05 08:20:52 keitha Exp $

#ifndef IN_KIPPER
#define IN_KIPPER

#include <stdio.h>

#include <string>
#include <vector>

class KIPPER
{

public:

    KIPPER( );
    ~KIPPER( );

    enum
    {
          UNSET
        , OK
        , DATA
        , SIZE
        , FILE_IO
        , COMPRESS
        , UNCOMPRESS
        , MEMORY
        , INTERNAL
    };

    bool setUData( const char * data );
    bool setUData( const std::string & data );
    bool setUData( const unsigned char * data, const int size );
    bool setUData( const std::vector<unsigned char> & data );
    bool readUFile( const std::string & filename, const bool isBinary );
    bool readUFile( FILE * ifp );
    bool getUData( char ** data );
    bool getUData( std::string * data );
    bool getUData( unsigned char ** data, int * size );
    bool getUData( std::vector<unsigned char> * data );
    bool writeUFile( const std::string & name, const bool isBinary = true );
    bool writeUFile( FILE * ofp );

    bool setCData( const char * data );
    bool setCData( const std::string & data );
    bool setCData( const unsigned char * data, const int size );
    bool setCData( const std::vector<unsigned char> & data );
    bool readCFile( const std::string & filename, const bool isBinary = true );
    bool readCFile( FILE * ifp );
    bool getCData( char ** data );
    bool getCData( std::string * data );
    bool getCData( unsigned char ** data, int * size );
    bool getCData( std::vector<unsigned char> * data );
    bool writeCFile( const std::string & name, const bool isBinary = true );
    bool writeCFile( FILE * ofp );

    bool isValid( ) const;
    int getStatus( ) const;
    std::string getDump( ) const;
    std::string getDigest( ) const;
    static int compress( unsigned char ** cdata, int * cdatasize,
        const unsigned char * udata, const int udatasize );
    static int uncompress( unsigned char ** udata, int * udatasize,
        const unsigned char * cdata, const int cdatasize );

private:

    void mySetStatus( const int newStatus );
    void mySetData( const unsigned char * data, const int size );
    void myReadFile( FILE * ifp,
        unsigned char ** data = 0, size_t * size = 0 );
    void myWriteFile( FILE * ofp,
        const unsigned char * data = 0, size_t size = 0 );

    static int myFilesize( FILE * ifp );
    static int myStrlen( const char * data );
    static std::string myHexDump( const unsigned char * data,
        const size_t size );
    static void myFree( void * pdata );
    static bool myRealloc( void * pdata, size_t size );

    int m_status;
    unsigned char * m_data;
    size_t m_size;
};

#endif
