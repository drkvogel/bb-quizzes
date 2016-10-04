// $Id: kipper.cpp,v 1.6 2015/08/05 08:22:56 keitha Exp $

#include "kipper.h"

#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

// zlib may or may not be provided by the operating system
#include "zlib.h"

#include "xmd5.h"


KIPPER::KIPPER( )
    : m_status(UNSET)
    , m_data(0)
    , m_size(0)
{
}

KIPPER::~KIPPER( )
{
    myFree(&m_data);
}

bool
KIPPER::setUData( const char * data )
{
    (void) setUData((const unsigned char *) data, myStrlen(data) + 1);

    return isValid();
}

bool
KIPPER::setUData( const std::string & data )
{
    (void) setUData((const unsigned char *) (data.c_str()), data.length());

    return isValid();
}

bool
KIPPER::setUData( const unsigned char * data, const int size )
{
    mySetData(data, size);

    return isValid();
}

bool
KIPPER::setUData( const std::vector<unsigned char> & data )
{
    mySetData(&data[0], data.size());

    return isValid();
}

bool
KIPPER::getUData( char ** data )
{
    do
    {
        unsigned char * mydata = 0;
        int mysize = -1;
        if (! getUData(&mydata, &mysize))
        {
            break;
        }

        if (! myRealloc(&mydata, mysize + 1))
        {
            myFree(&mydata);
            mySetStatus(MEMORY);
            break;
        }

        mydata[mysize] = '\0';
        *data = (char *) mydata;

    } while (false);

    return isValid();
}

bool
KIPPER::getUData( std::string * data )
{
    do
    {
        unsigned char * mydata = 0;
        int mysize = -1;
        if (! getUData(&mydata, &mysize))
        {
            break;
        }

        *data = std::string((char *) mydata, mysize);

        myFree(&mydata);

    } while (false);

    return isValid();
}

bool
KIPPER::getUData( unsigned char ** data, int * size )
{
    mySetStatus(uncompress(data, size, m_data, m_size));

    return isValid();
}

bool
KIPPER::getUData( std::vector<unsigned char> * data )
{
    do
    {
        unsigned char * mydata = 0;
        int mysize = -1;
        if (! getUData(&mydata, &mysize))
        {
            break;
        }

        *data = std::vector<unsigned char>(&mydata[0], &mydata[mysize]);

        myFree(&mydata);

    } while (false);

    return isValid();
}

bool
KIPPER::readUFile( const std::string & name, const bool isBinary )
{
    do
    {
        const char * mode = (isBinary) ? "rb" : "r";
        FILE * ifp = fopen(name.c_str(), mode);
        (void) readUFile(ifp);
        if (fclose(ifp) != 0)
        {
            if (isValid())
            {
                mySetStatus(FILE_IO);
            }
        }

    } while (false);

    return isValid();
}

bool
KIPPER::readUFile( FILE * ifp )
{
    myReadFile(ifp);

    return isValid();
}

bool
KIPPER::writeUFile( const std::string & name, const bool isBinary )
{
    do
    {
        const char * mode = (isBinary) ? "wb" : "w";
        FILE * ofp = fopen(name.c_str(), mode);
        writeUFile(ofp);
        if (fclose(ofp) != 0)
        {
            if (isValid())
            {
                mySetStatus(FILE_IO);
            }
        }

    } while (false);

    return isValid();
}

bool
KIPPER::writeUFile( FILE * ofp )
{
    unsigned char * data = 0;
    int size = 0;
    mySetStatus(uncompress(&data, &size, m_data, m_size));
    if (isValid())
    {
        myWriteFile(ofp, data, size);
    }
    myFree(&data);

    return isValid();
}

bool
KIPPER::setCData( const char * data )
{
    return setCData((const unsigned char *) data, myStrlen(data) + 1);
}

bool
KIPPER::setCData( const std::string & data )
{
    return setCData((const unsigned char *) (data.c_str()), data.length());
}

bool
KIPPER::setCData( const unsigned char * data, const int size )
{
    mySetData(data, size);

    return isValid();
}

bool
KIPPER::setCData( const std::vector<unsigned char> & data )
{
    mySetData(&data[0], data.size());

    return isValid();
}

bool
KIPPER::readCFile( const std::string & name, const bool isBinary )
{
    do
    {
        const char * mode = (isBinary) ? "rb" : "r";
        FILE * ifp = fopen(name.c_str(), mode);
        readCFile(ifp);
        if (fclose(ifp) != 0)
        {
            if (isValid())
            {
                mySetStatus(FILE_IO);
            }
        }

    } while (false);

    return isValid();
}

bool
KIPPER::readCFile( FILE * ifp )
{
    myReadFile(ifp);

    return isValid();
}

bool
KIPPER::getCData( char ** data )
{
    do
    {
        unsigned char * mydata = 0;
        int mysize = -1;
        if (! getCData(&mydata, &mysize))
        {
            break;
        }

        if (! myRealloc(&mydata, mysize + 1))
        {
            myFree(&mydata);
            mySetStatus(MEMORY);
            break;
        }

        mydata[mysize] = '\0';
        *data = (char *) mydata;

    } while (false);

    return isValid();
}

bool
KIPPER::getCData( std::string * data )
{
    do
    {
        unsigned char * mydata = 0;
        int mysize = -1;
        if (! getCData(&mydata, &mysize))
        {
            break;
        }

        *data = std::string((char *) mydata, mysize);

        myFree(&mydata);

    } while (false);

    return isValid();
}

bool
KIPPER::getCData( unsigned char ** data, int * size )
{
    mySetStatus(compress(data, size, m_data, m_size));

    return isValid();
}

bool
KIPPER::getCData( std::vector<unsigned char> * data )
{
    do
    {
        unsigned char * mydata = 0;
        int mysize = -1;
        if (! getCData(&mydata, &mysize))
        {
            break;
        }

        *data = std::vector<unsigned char>(&mydata[0], &mydata[mysize]);

        myFree(&mydata);

    } while (false);

    return isValid();
}

bool
KIPPER::writeCFile( const std::string & name, const bool isBinary )
{
    do
    {
        const char * mode = (isBinary) ? "wb" : "w";
        FILE * ofp = fopen(name.c_str(), mode);
        writeCFile(ofp);
        if (fclose(ofp) != 0)
        {
            if (isValid())
            {
                mySetStatus(FILE_IO);
            }
        }

    } while (false);

    return isValid();
}

bool
KIPPER::writeCFile( FILE * ofp )
{
    unsigned char * data = 0;
    int size = 0;
    mySetStatus(compress(&data, &size, m_data, m_size));
    if (isValid())
    {
        myWriteFile(ofp, data, size);
    }
    myFree(&data);

    return isValid();
}

bool
KIPPER::isValid( ) const
{
    return getStatus() == OK;
}

int
KIPPER::getStatus( ) const
{
    return m_status;
}

std::string
KIPPER::getDump( ) const
{
    return (m_data == 0) ? std::string("(null)") : myHexDump(m_data, m_size);
}

std::string
KIPPER::getDigest( ) const
{
    std::string digest = "(null)";
    XMD5_DIGEST md5;
    if (XMD5::calc(&md5, (const char *) m_data, m_size))
    {
        digest = md5.hex;
    }
    return digest;
}

// static

int
KIPPER::compress( unsigned char ** cdata, int * cdatasize,
    const unsigned char * udata, const int udatasize )
{
    int status = INTERNAL;

    do
    {
        uLongf ubuflen = udatasize;
        Bytef * ubuf = (Bytef *) udata;

        uLongf cbuflen = ubuflen + (6 + 5 * (1 + ubuflen / (6 * 1024)));
        unsigned char * mycbuf = 0;
        if (! myRealloc(&mycbuf, cbuflen))
        {
            status = MEMORY;
            break;
        }

        Bytef * cbuf = (Bytef *) mycbuf;
        int zst = ::compress(cbuf, &cbuflen, ubuf, ubuflen);
        if (zst != Z_OK)
        {
            myFree(&mycbuf);
            cbuflen = 0;
            status = COMPRESS;
            break;
        }
        if (! myRealloc(&mycbuf, cbuflen))
        {
            myFree(&mycbuf);
            cbuflen = 0;
            status = MEMORY;
            break;
        }

        *cdata = mycbuf;
        *cdatasize = cbuflen;

        status = OK;

    } while (false);

    return status;
}

int
KIPPER::uncompress( unsigned char ** udata, int * udatasize,
    const unsigned char * cdata, const int cdatasize )
{
    int status = INTERNAL;

    do
    {
        uLongf cbuflen = cdatasize;
        Bytef * cbuf = (Bytef *) cdata;

        uLongf ubuflen = 1024 * 16;
        unsigned char * myubuf = 0;
        if (! myRealloc(&myubuf, ubuflen))
        {
            status = MEMORY;
            break;
        }
        Bytef * ubuf = (Bytef *) myubuf;

        bool rebreak = false;
        for (;;)
        {
            int zst = ::uncompress(ubuf, &ubuflen, cbuf, cbuflen);
            if (zst == Z_OK)
            {
                break;
            }
            if (zst != Z_BUF_ERROR)
            {
                status = UNCOMPRESS;
                rebreak = true;
                break;
            }
            const int ubufinc = (ubuflen < (1024 * 1024))
                ? ubuflen
                : (1024 * 1024);
            ubuflen += ubufinc;
            if (! myRealloc(&myubuf, ubuflen))
            {
                status = MEMORY;
                rebreak = true;
                break;
            }
            ubuf = (Bytef *) myubuf;
        }
        if (rebreak)
        {
            myFree(&myubuf);
            ubuflen = 0;
            break;
        }
        if (! myRealloc(&myubuf, ubuflen))
        {
            myFree(&myubuf);
            ubuflen = 0;
            status = MEMORY;
            break;
        }

        *udata = myubuf;
        *udatasize = ubuflen;

        status = OK;

    } while (false);

    return status;
}

// private

void
KIPPER::mySetStatus( const int newStatus )
{
    m_status = newStatus;

    if (m_status != OK)
    {
        // ?
    }

    return;
}

void
KIPPER::mySetData( const unsigned char * data, const int size )
{
    do
    {
        if (data == 0)
        {
            mySetStatus(DATA);
            break;
        }

        if (size <= 0)
        {
            mySetStatus(SIZE);
            break;
        }

        myFree(&m_data);
        m_size = 0;

        m_size = (size_t) size;
        if (! myRealloc(&m_data, m_size))
        {
            mySetStatus(MEMORY);
            break;
        }

        (void) memcpy(m_data, data, m_size);

        mySetStatus(OK);

    } while (false);

    return;
}

void
KIPPER::myReadFile( FILE * ifp, unsigned char ** data, size_t * size )
{
    do
    {
        if (ifp == 0)
        {
            mySetStatus(FILE_IO);
            break;
        }

        if (myFilesize(ifp) < 0)
        {
            mySetStatus(FILE_IO);
            break;
        }

        if (data == 0)
        {
            data = &m_data;
            size = &m_size;
        }

        size_t index = 0;
        int nasked = 1024 * 16;

        bool rebreak = false;

        for (;;)
        {
            nasked += (nasked < (1024 * 1024))
                ? nasked
                : (1024 * 1024);
            if (! myRealloc(data, index + nasked))
            {
                mySetStatus(MEMORY);
                rebreak = true;
                break;
            }
            const int nactual = fread((*data) + index, 1, nasked, ifp);
            if (ferror(ifp))
            {
                mySetStatus(FILE_IO);
                rebreak = true;
                break;
            }
            if ((nactual == 0) && (feof(ifp)))
            {
                break;
            }
            if (nactual <= 0)
            {
                mySetStatus(FILE_IO);
                rebreak = true;
                break;
            }
            index += nactual;
        }

        if (rebreak)
        {
            myFree(data);
            *size = 0;
            break;
        }

        if (! myRealloc(data, index))
        {
            mySetStatus(MEMORY);
            myFree(data);
            *size = 0;
            break;
        }

        *size = index;

        mySetStatus(OK);

    } while (false);

    return;
}

void
KIPPER::myWriteFile( FILE * ofp, const unsigned char * data, size_t size )
{
    do
    {
        if (ofp == 0)
        {
            mySetStatus(FILE_IO);
            break;
        }

        if (data == 0)
        {
            data = m_data;
            size = m_size;
        }

        size_t index = 0;
        bool rebreak = false;
        for (;;)
        {
            const int nasked = size - index;
            if (nasked == 0)
            {
                break;
            }
            if (nasked < 0)
            {
                mySetStatus(INTERNAL);
                rebreak = true;
                break;
            }
            const int nactual = fwrite(data + index, 1, nasked, ofp);
            if (ferror(ofp))
            {
                mySetStatus(FILE_IO);
                rebreak = true;
                break;
            }
            if (nactual <= 0)
            {
                mySetStatus(FILE_IO);
                rebreak = true;
                break;
            }
            if (nactual != nasked)
            {
                ; // assume ok
            }
            index += nactual;
        }

        if (rebreak)
        {
            break;
        }

        mySetStatus(OK);

    } while (false);

    return;
}

// static

int
KIPPER::myFilesize( FILE * ifp )
{
    int size = -1;

    struct stat statbuf;

    if (fstat(fileno(ifp), &statbuf) == 0)
    {
        size = statbuf.st_size;
    }

    return size;
}

int
KIPPER::myStrlen( const char * data )
{
    int len = -1;
    if (data != 0)
    {
        len = strlen(data);
    }
    return len;
}

std::string
KIPPER::myHexDump( const unsigned char * data, const size_t size )
{
    std::string str = "";
    char buff[16];
    for (size_t i=0; i<size; i++)
    {
        sprintf(buff, "%02x ", data[i]);
        str += buff;
        if (((i+1) % (80/3)) == 0) str += '\n';
    }
    if (str[str.length() - 1] != '\n') str += '\n';
    return str;
}

void
KIPPER::myFree( void * pdata )
{
    unsigned char ** data = (unsigned char **) pdata;
    if (*data != 0)
    {
        free(*data);
        *data = 0;
    }
    return;
}

bool
KIPPER::myRealloc( void * pdata, size_t size )
{
    bool ok = false;
    do
    {
        unsigned char ** data = (unsigned char **) pdata;
        unsigned char * newdata = (unsigned char *) realloc(*data, size);
        if (size == 0)
        {
            newdata = 0;
        }
        if ((size > 0) && (newdata == 0))
        {
            break;
        }
        *data = newdata;
        ok = true;

    } while (false);

    return ok;
}

