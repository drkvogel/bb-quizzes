#include "xquery.h"
#include "rosetta.h"
#include "xdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
//===========================================================================
XQUERY::XQUERY( XDB *db, const std::string query )
	:
	XSQL( db, query )
{
	result.caseSensitive( false );
	res_ptr = &result;
#if X_ING
	char	name_buf[20];
	sprintf( name_buf, "X%dquery", object_instance );
	object_name = name_buf;
	is_open = false;
#endif
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XQUERY::~XQUERY( void )
{
	close();
#if X_BDE
	if ( NULL != qry )
		{qry->Tag = 0;		// MARK FOR RE-ALLOCATION BY DATABASE OBJECT
		}
#elif X_ING
	ingBufRemove();
#endif
}
//---------------------------------------------------------------------------
std::string XQUERY::getClass( void )
{	return( "XQUERY" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::isOpen( void )
{
#if X_BDE
	is_open = ( NULL != qry && qry->Active );
#endif
	return( is_open );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int XQUERY::getNRows( void )
{
	return( nrows_fetched );
}
//---------------------------------------------------------------------------
#if X_BDE
bool XQUERY::bdeOpenAction( void )
{
	qry->UniDirectional = true;	// SPEED OPTIMIZATION
	try
		{qry->Open();
		}
	catch ( Exception &e )
		{error( 0, "query failed" );
		}
	return( isOpen() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::bdeOpen( void )
{
	bool 	ok;
	TCursor	old_cur = Screen->Cursor;
	Screen->Cursor = crSQLWait;
	try
		{ok = bdeOpenAction();
		}
	__finally
		{Screen->Cursor = old_cur;
		}
	return( ok );
}
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if X_ING
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const char *XQUERY::ingPlaceholder( void )
{
	return( " ~V " );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingOpen( void )
{
	bool	ok = true;
	IIAPI_SETDESCRPARM 	setDescrParm;
	IIAPI_PUTPARMPARM 	putParmParm;
	queryParm.qy_genParm.gp_callback = NULL;
	queryParm.qy_genParm.gp_closure = NULL;
	queryParm.qy_connHandle = database->getConnHandle();
	queryParm.qy_queryType  = IIAPI_QT_OPEN;
	queryParm.qy_queryText  = ( char * ) malloc( query_text.size() + 1 );
	strcpy( queryParm.qy_queryText, query_text.c_str() );
	queryParm.qy_parameters = TRUE;
	queryParm.qy_tranHandle = database->getTranHandle();
	queryParm.qy_stmtHandle = NULL;
	IIapi_query( &queryParm );		// INVOKE OPENAPI
	database->setTranHandle( queryParm.qy_tranHandle );
	if ( ! ingGetResult( &queryParm.qy_genParm ) )
		{return( false );
		}
	free( queryParm.qy_queryText );
						// NAME OF CURSOR OBJECT
	setDescrParm.sd_genParm.gp_callback = NULL;
	setDescrParm.sd_genParm.gp_closure = NULL;
	setDescrParm.sd_stmtHandle = queryParm.qy_stmtHandle;
	setDescrParm.sd_descriptorCount = (II_INT2) ( nparam + 1 );
	setDescrParm.sd_descriptor = (IIAPI_DESCRIPTOR *) malloc(
		( setDescrParm.sd_descriptorCount * sizeof(IIAPI_DESCRIPTOR) ));
	if ( NULL == setDescrParm.sd_descriptor )
		{return( false );
		}
	setDescrParm.sd_descriptor[0].ds_dataType = IIAPI_CHA_TYPE;
	setDescrParm.sd_descriptor[0].ds_nullable = FALSE;
	setDescrParm.sd_descriptor[0].ds_length = (II_UINT2) object_name.size();
	setDescrParm.sd_descriptor[0].ds_precision = 0;
	setDescrParm.sd_descriptor[0].ds_scale = 0;
	setDescrParm.sd_descriptor[0].ds_columnType = IIAPI_COL_SVCPARM;
	setDescrParm.sd_descriptor[0].ds_columnName = NULL;
	ok = ingDescribeUserParameters( setDescrParm.sd_descriptor + 1 );
	if ( ! ok )
		{ingClose();
		return( false );
		}
	IIapi_setDescriptor( &setDescrParm );		// INVOKE API
	if ( ! ingGetResult( &setDescrParm.sd_genParm ) )
		{ingClose();
		return( false );
		}
	free( setDescrParm.sd_descriptor );
	setDescrParm.sd_descriptor = NULL;    	// TRAP FOR MEMORY PROBLEMS
	putParmParm.pp_genParm.gp_closure = NULL;
	putParmParm.pp_genParm.gp_callback = NULL;
	putParmParm.pp_stmtHandle = queryParm.qy_stmtHandle;
	IIAPI_DATAVALUE		data;
	putParmParm.pp_parmData = ( IIAPI_DATAVALUE * ) &data;
	putParmParm.pp_parmData->dv_null = FALSE;
	putParmParm.pp_parmData->dv_length = (II_UINT2) object_name.size();
	putParmParm.pp_parmData->dv_value = (char *) malloc( object_name.size() + 1 );
	strcpy( (char *) putParmParm.pp_parmData[0].dv_value, object_name.c_str() );
	putParmParm.pp_parmCount = 1;
	ok = ingPutUserParamsDo( &putParmParm );
	free( putParmParm.pp_parmData->dv_value );
	putParmParm.pp_parmData->dv_value = NULL;
	if ( ok )
		{ok = ingPutUserParameters( &putParmParm );
		}
	if ( ! ok )
		{return( false );
		}
	if ( ! ingGetDescr( &getDescrParm, queryParm.qy_stmtHandle ) )
		{ingClose();
		return( false );
		}
	if ( ! ingBufInit() )
		{ingClose();
		return( false );
		}
	is_open = true;
	return( true );
}
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::open( void )
{
	close();
	result.clear();
	nrows_fetched = 0;
	if ( ! construct() )
		{return( false );
		}
#if X_BDE
	return( bdeOpen() );
#elif X_ING
	return( ingOpen() );
#endif
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if X_BDE
bool XQUERY::bdeFetchAction( void )
{
	if ( ! isOpen() )
		{error( 0, "fetch called on closed query" );
		return( false );
		}
	if ( qry->Eof )
		{return( false );
		}
	if ( nrows_fetched++ > 0 )
		{qry->Next();	// GET NEW ROW ONLY ON 2ND-AND-SUBSQUENT CALLS
		if ( qry->Eof )
			{return( false );
			}
		}
	int	i;
	std::string	nam;
	int	nf = qry->Fields->Count;
	TField	*fld;
	for ( i = 0; i < nf; i++ )
		{
		fld = qry->Fields->Fields[i];
		nam = String( fld->FieldName ).c_str();	
		switch( fld->DataType )
			{
			case ftInteger:
			case ftSmallint:
			case ftAutoInc:
				res_ptr->setInt( nam, fld->AsInteger );
				break;
			case ftString:
			case ftMemo:
				res_ptr->setString( nam, fld->AsString.c_str() );
				break;
			case ftDateTime:
				res_ptr->setTime( nam, XTIME( fld->AsDateTime ) );
				break;
			case ftDate:
				res_ptr->setDate( nam, XDATE( fld->AsDateTime ) );
				break;
			case ftFloat:
				res_ptr->setReal( nam, fld->AsFloat );
				break;
			case ftBoolean:
				res_ptr->setBool( nam, fld->AsBoolean );
				break;
			case ftVarBytes:
			case ftBlob:
				{
				AnsiString	s = fld->AsString;
				res_ptr->setBinob( nam, XBINOB( s.Length(),
					(const unsigned char *) s.c_str() ) );
				}
				break;
			default:
				res_ptr->setString( nam,
					"XQUERY::fetch,invalid field type" );
				error( 0, std::string( "invalid type for field ")
					+ nam );
				break;
			}
		}
	return( isValid() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::bdeFetch( void )
{
	bool	ok;
	Screen->Cursor = crSQLWait;
	try
		{ok = bdeFetchAction();
		}
	__finally
		{Screen->Cursor = crDefault;
		}
	return( ok );
}
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if X_ING
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackKey( const char *name, const IIAPI_DATAVALUE *v )
{
	int	i;              // RETURNING BINARY VALUE AS HEX STRING
	char 	c, d;
	char	*hex = (char *) malloc( ( 3 * v->dv_length ) + 1 );
	char	*buf = hex;
	for( i = 0; i < v->dv_length; i++ )
		{
		if ( i > 0 )	// PADDING TO MAKE OUTPUT MORE READABLE
			{*buf++ = ' ';
			}
		c = ( ( II_CHAR * ) v->dv_value )[i];
		d = (char) ( ( c >> 4 ) & 0x0f );
		*buf++ = (char) ( ( d < 10 ) ? d + '0' : (d - 10) + 'A' );
		d = (char) ( c & 0x0f );
		*buf++ = (char) ( ( d < 10 ) ? d + '0' : (d - 10) + 'A' );
		}
	*buf = '\0';
	free( hex );
	res_ptr->setString( name, hex );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackInt( const char *name, const IIAPI_DATAVALUE *v )
{
	bool	ok = true;
	switch( v->dv_length )
		{
		case 1:
			II_INT1	*integer1;
			integer1 = (II_INT1 *) v->dv_value;
			res_ptr->setInt( name, (int) *integer1 );
			break;
		case 2:
			II_INT2	*integer2;
			integer2 = (II_INT2 *) v->dv_value;
			res_ptr->setInt( name, (int) *integer2 );
			break;
		case 4:
			II_INT4	*integer4;
			integer4 = (II_INT4 *) v->dv_value;
			res_ptr->setInt( name, (int) *integer4 );
			break;
		default:
			error( 0, "fetch(), invalid length of integer field" );
			ok = false;
		break;
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackReal( const char *name, const IIAPI_DATAVALUE *v  )
{
	bool	ok = true;
	switch( v->dv_length )
		{
		case 4:
			II_FLOAT4 *float4;
			float4 = (II_FLOAT4 *) v->dv_value;
			res_ptr->setReal( name, (double) *float4 );
			break;
		case 8:
			II_FLOAT8 *float8;
			float8 = (II_FLOAT8 *) v->dv_value;
			res_ptr->setReal( name, (double) *float8 );
			break;
		default:
			error( 0, "fetch(), invalid length of real/float field" );
			ok = false;
			break;
	    }
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackVarchar( const char *name, const IIAPI_DATAVALUE *v )
{
	II_INT2		length;
	memcpy( &length, v->dv_value, sizeof( length ) );
	char	*buf = (char *) malloc( length + 1 );
	if ( NULL == buf )
		{error( 0, "fetch(), unable to allocate string storage" );
		res_ptr->setString( name, "*ERROR*" );
		return( false );
		}
	memcpy( buf, (char *) v->dv_value + sizeof( length ), length );
	buf[length] = '\0';
	res_ptr->setString( name, buf );
	free( buf );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackChar( const char *name, const IIAPI_DATAVALUE *v )
{
	II_INT2		length = v->dv_length;
	char	*buf = (char *) malloc( length + 1 );
	if ( NULL == buf )
		{error( 0, "fetch(), unable to allocate string storage" );
		res_ptr->setString( name, "*ERROR*" );
		return( false );
		}
	memcpy( buf, (const char *) v->dv_value, length );
	buf[length] = '\0';
	res_ptr->setString( name, buf );
	free( buf );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackByte( const char *name, const IIAPI_DATAVALUE *v )
{
	II_INT2		length;
	memcpy( &length, v->dv_value, sizeof( length ) );
	res_ptr->setBinob( name, XBINOB( (int) length,
		(const unsigned char *) v->dv_value + sizeof( length ) ) );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackBlob( const IIAPI_DATAVALUE *v, int *total, char **buf )
{
	II_INT2		length;
	*total = 0;
	*buf = NULL;
	bool	more = true;
	do    				// APPEND SEGMENTS TO BUFFER
		{memcpy( &length, v->dv_value, sizeof( length ) );
		void *ptr = realloc( (*buf), (*total) + length + 1 );
		if ( NULL == ptr )
			{error( 0, "fetch(), unable to allocate blob storage" );
			if ( NULL != *buf )
				{free( *buf );
				*buf = NULL;
				}
			return( false );
			}
		*buf = (char *) ptr;
		memcpy( (*buf) + (*total), (char *) v->dv_value + sizeof( length ),
			length );
		*total += length;
		more = ( getColParm.gc_moreSegments != 0 );
		if ( more )
			{		// READ NEXT SEGMENT
			IIapi_getColumns( &getColParm );
			if ( ! ingGetResult( &getColParm.gc_genParm ) )
				{return( false );
				}
			if ( getColParm.gc_genParm.gp_status == IIAPI_ST_NO_DATA )
				{return( false ); 	// NO DATA - ERROR
				}
			}
		}
		while ( more );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackLVarchar( const char *name, const IIAPI_DATAVALUE *v )
{
	int	len;
	char	*buf;
	bool	ok = ingFetchRepackBlob( v, &len, &buf );
	if ( ok )
		{buf[len] = '\0';
		res_ptr->setString( name, buf );
		}
	if ( NULL != buf )
		{free( buf );
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackLByte( const char *name, const IIAPI_DATAVALUE *v )
{
	int	siz;
	char	*buf;
	bool	ok = ingFetchRepackBlob( v, &siz, &buf );
	if ( ok )
		{res_ptr->setBinob( name, XBINOB( siz, (unsigned char *) buf ) );
		}
	if ( NULL != buf )
		{free( buf );
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					/* EXTRACT AND PROCESS TIME VALUE */
	/* BIT-FIELD VALUES STORED IN FIRST BYTE OF INGRES DATE FIELD	*/
#define XSQL_DATETIME_BIT_EMPTY         0	// EMPTY DATE (NULL?)
#define XSQL_DATETIME_BIT_ABSOLUTE      1	// DATE IS CALENDAR VALUE
#define XSQL_DATETIME_BIT_INTERVAL      2	// DATE IS A DURATION
#define XSQL_DATETIME_BIT_YEAR          4	// YEAR VALUE IS PRESENT
#define XSQL_DATETIME_BIT_MONTH         8	// MONTH VALUE IS PRESENT
#define XSQL_DATETIME_BIT_DAY           16	// DAY VALUE IS PRESENT
#define XSQL_DATETIME_BIT_TIME          32	// TIME OF DAY IS PRESENT
/*
 N.B. IF DATE IS ABSOLUTE THEN DMY SEEMS ALWAYS PRESENT, EVEN IF FLAG=33 (WHICH
      IT IS SET TO IF THE DATE IS INSERTED AS `NOW') - GRRR....
      SOMETIMES SECS ARE < 0, AM ASSUMING THIS IS AN ALTERNATE WAY OF
      STORING TIME-SHIFT (BST->GMT) WITHOUT WRAPPING DAY VALUE
*/
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackDate( const char *name, const IIAPI_DATAVALUE *v )
{
	bool    convert_normal = true;
	bool	convert2local = true;
	char	*tf = (char *)  v->dv_value;          	// FLAG IN BYTE 0
	short	*st = (short *) v->dv_value;           	// DMY  IN BYTE 1,2,3
	bool	absolute_value = ( *tf & XSQL_DATETIME_BIT_ABSOLUTE );
	bool	clock_present = ( *tf & XSQL_DATETIME_BIT_TIME );
	if ( ! absolute_value )		// XSQL WILL REFUSE TO HANDLE INTERVALS
		{if ( res_ptr->exists( name ) )
			{res_ptr->remove( name );
			}	// REMOVE ANY VALUE STORED FROM PREVIOUS ROW
		error( 0, "ingres DATE contains unsupported interval-value" );
		return( false );
		}
	int	year  = (int) st[1];
	int	month = (int) st[2];
	int	day   = (int) st[3];
	int	rtype = res_ptr->getType( name );
	if ( clock_present )
		{if ( ROSETTA::typeDate == rtype )
			{res_ptr->remove( name );
			error( 0,
			"ingres DATE returns both ROSETTA Date and Time types" );
			return( false );
			}
		// tm->contents |= XTIME_CLOCK_SET;
		int	*it = (int *)   v->dv_value;   	// MSEC IN BYTES 4+5
		int	sc = it[2] / 1000;	// CLOCK IS MSEC AFTER MIDNIGHT
		if ( sc < 0 )
			{sc += 3600;
			convert_normal = false;
			}
		int	hour   = (int) ( sc / 3600 );
		int	minute = (int) ( ( sc / 60 ) % 60 );
		int	second = (int) ( sc % 60 );
		if ( convert_normal && database->returningLocalTime() )
			{
			//time_gmt_to_local( tm );
			}       	// INGRES ALWAYS STORES GMT INTERNALLY
		XTIME	t( year, month, day, hour, minute, second);
		if ( convert2local )   		// CONVERT NATIVE GMT TO LOCAL TIME
			{t.GMT2Local();
			}
		res_ptr->setTime( name, t );
		}
	else
		{if ( ROSETTA::typeTime == rtype )
			{res_ptr->remove( name );
			error( 0,
			"ingres DATE returns both ROSETTA Date and Time types" );
			return( false );
			}
		XDATE	a( year, month, day );
		res_ptr->setDate( name, a );
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepackOther( const char *name, IIAPI_DESCRIPTOR *descriptor,
	const IIAPI_DATAVALUE *v )
{
	char	buffer[500];	// RANDOM GUESS AT SIZE
	IIAPI_CONVERTPARM	cv;
	cv.cv_srcDesc.ds_dataType = descriptor->ds_dataType;
	cv.cv_srcDesc.ds_nullable = descriptor->ds_nullable;
	cv.cv_srcDesc.ds_length = descriptor->ds_length;
	cv.cv_srcDesc.ds_precision = descriptor->ds_precision;
	cv.cv_srcDesc.ds_scale = descriptor->ds_scale;
	cv.cv_srcDesc.ds_columnType = descriptor->ds_columnType;
	cv.cv_srcDesc.ds_columnName = descriptor->ds_columnName;
	cv.cv_srcValue.dv_null   = v->dv_null;
	cv.cv_srcValue.dv_length = v->dv_length;
	cv.cv_srcValue.dv_value  = v->dv_value;
	cv.cv_dstDesc.ds_dataType = IIAPI_CHA_TYPE;
	cv.cv_dstDesc.ds_nullable = FALSE;
	cv.cv_dstDesc.ds_length = 32;
	cv.cv_dstDesc.ds_precision = 0;
	cv.cv_dstDesc.ds_scale = 0;
	cv.cv_dstDesc.ds_columnType = IIAPI_COL_TUPLE;
	cv.cv_dstDesc.ds_columnName = NULL;
	cv.cv_dstValue.dv_null = FALSE;
	cv.cv_dstValue.dv_length = cv.cv_dstDesc.ds_length;
	cv.cv_dstValue.dv_value = buffer;
	IIapi_convertData( &cv );
	if ( cv.cv_status != IIAPI_ST_SUCCESS )
		{
		error( 0, "ingFetchRepackOther, invalid type" );
		return( false );
		}
	buffer[ cv.cv_dstValue.dv_length ] = '\0';
	res_ptr->setString( name, buffer );
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				/* CREATE VARIABLE AND SET NULL TAG */
bool XQUERY::ingFetchSetNull( const char *nam, const int typ )
{
	bool	ok = true;
	switch( abs( typ ) )
		{
		case IIAPI_INT_TYPE:
			res_ptr->setInt( nam, ROSETTA::errorInt );
			break;
		case IIAPI_LVCH_TYPE:
			res_ptr->setString( nam, ROSETTA::errorString );
			break;
		case IIAPI_FLT_TYPE:
			res_ptr->setReal( nam, ROSETTA::errorReal );
			break;
		case IIAPI_DTE_TYPE:
			if ( ROSETTA::typeTime == res_ptr->getType( nam ) )
				{res_ptr->setTime( nam, ROSETTA::errorTime );
				}
			else			// ASSUME A PURE-DATE
				{res_ptr->setDate( nam, ROSETTA::errorDate );
				}
			break;
		case IIAPI_VBYTE_TYPE:
			res_ptr->setBinob( nam, ROSETTA::errorBinob);
			break;
		case IIAPI_LBYTE_TYPE:
			res_ptr->setBinob( nam, ROSETTA::errorBinob);
			break;
		case IIAPI_VCH_TYPE:
		case IIAPI_CHA_TYPE:
		case IIAPI_CHR_TYPE:
		case IIAPI_DEC_TYPE:
		case IIAPI_MNY_TYPE:
		case IIAPI_LTXT_TYPE:
		case IIAPI_TXT_TYPE:
		case IIAPI_BYTE_TYPE:
		case IIAPI_LOGKEY_TYPE:
		case IIAPI_TABKEY_TYPE:
			res_ptr->setString( nam, ROSETTA::errorString );
			break;
		default:
			error( 0, "fetch(), invalid field type" );
			ok = false;
			break;
		}
	res_ptr->attachTag( nam, XSQL::null );
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetchRepack( IIAPI_DESCRIPTOR *d, const IIAPI_DATAVALUE *v )
{
	bool	ok = true;
	if ( v->dv_null )
		{error( 0, "ingFetchRepack(), NULL buffer" );
		return( false);
		}
	char	*nam;				// NAME OF DATABASE FIELD
	if ( NULL != d->ds_columnName )
		{nam = d->ds_columnName;
		}
	else
		{nam = "NONAME";
		}
	if ( d->ds_nullable && v->dv_null )
		{ok = ingFetchSetNull( nam, d->ds_dataType );
		}
	else
		{switch( abs( d->ds_dataType ) )
			{
			case IIAPI_INT_TYPE:
				ok = ingFetchRepackInt( nam, v );
				break;
			case IIAPI_VCH_TYPE:
				ok = ingFetchRepackVarchar( nam, v );
				break;
			case IIAPI_LVCH_TYPE:
				ok = ingFetchRepackLVarchar( nam, v );
				break;
			case IIAPI_FLT_TYPE:
				ok = ingFetchRepackReal( nam, v );
				break;
			case IIAPI_DTE_TYPE:
				ok = ingFetchRepackDate( nam, v );
				break;
			case IIAPI_VBYTE_TYPE:
				ok = ingFetchRepackByte( nam, v );
				break;
			case IIAPI_LBYTE_TYPE:
				ok = ingFetchRepackLByte( nam, v );
				break;
			case IIAPI_CHA_TYPE:
				ok = ingFetchRepackChar( nam, v );
				break;
			case IIAPI_CHR_TYPE:
			case IIAPI_DEC_TYPE:
			case IIAPI_MNY_TYPE:
			case IIAPI_LTXT_TYPE:
			case IIAPI_TXT_TYPE:
			case IIAPI_BYTE_TYPE:
				ok = ingFetchRepackOther( nam, d, v );
				break;
			case IIAPI_LOGKEY_TYPE:
			case IIAPI_TABKEY_TYPE:
				ok = ingFetchRepackKey( nam, v );
				break;
			default:
				error( 0, "fetch(), invalid field type" );
				ok = false;
				break;
			}
		}
	if ( d->ds_nullable )
		{if ( nrows_fetched < 1 )
			{res_ptr->attachTag( nam, XSQL::nullable );
			}
		else if ( ! v->dv_null )	// ONLY NEEDED IF ROW > 0
			{res_ptr->removeTag( nam, XSQL::null );
			}
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingBufInit( void )
{
	int	i;
	char	*bf;
	bool	ok = true;
	ingBufRemove();
	for ( i = 0; i < getDescrParm.gd_descriptorCount; i++ )
		{
		bf = (char *) malloc( getDescrParm.gd_descriptor[i].ds_length );
		if ( NULL != bf )
			{ing_val_buf.push_back( bf );
			}
		else
			{ok = false;
			}
		}
	if ( ! ok )
		{error( 0, "ingBufInit, malloc failure" );
		ingBufRemove();
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void XQUERY::ingBufRemove( void )
{
	if ( ing_val_buf.size() < 1 )
		{return;
		}
	std::vector<char *>::iterator vi = ing_val_buf.begin();
	while ( vi != ing_val_buf.end() )
		{
		if ( NULL != *vi )
			{free( *vi );
			}
		vi++;
		}
	ing_val_buf.clear();
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::ingFetch( void )
{
	if ( ! is_open )
		{error( 0, "fetch called on closed query" );
		return( false );
		}
	int	i;
	bool	ok = true;
	getColParm.gc_columnData = &ing_val;
	for ( i = 0; i < getDescrParm.gd_descriptorCount; i++ )
		{
		getColParm.gc_genParm.gp_callback = NULL;
		getColParm.gc_genParm.gp_closure = NULL;
		getColParm.gc_rowCount = 1;
		getColParm.gc_columnCount = 1;//getDescrParm.gd_descriptorCount;
//		getColParm.gc_columnData->dv_value
		ing_val.dv_value = ing_val_buf[i];
//			= malloc( getDescrParm.gd_descriptor[i].ds_length );
		getColParm.gc_stmtHandle = getDescrParm.gd_stmtHandle;
		getColParm.gc_moreSegments = 0;
		IIapi_getColumns( &getColParm );
		if ( ! ingGetResult( &getColParm.gc_genParm ) )
			{return( false );
			}
		if ( getColParm.gc_genParm.gp_status == IIAPI_ST_NO_DATA )
			{return( false );		// NO DATA
			}
		ok &= ingFetchRepack( &getDescrParm.gd_descriptor[i],
			getColParm.gc_columnData );
//		free( getColParm.gc_columnData->dv_value );
//		free( ing_val.dv_value );
		}
	return( ok );
}
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::fetch( void )
{
	return( fetch( &result ) );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::fetch( ROSETTA *output )	// EXTRACT RESULTS INTO OUTPUT
{
	if ( NULL == output )
		{error( 0, "fetch(output) called with NULL output" );
		return( false );
		}
	res_ptr = output;
#if X_BDE
	bool	ok = bdeFetch();
#elif X_ING
	bool	ok = ingFetch();
#endif
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int XQUERY::fetchInt( const int default_value )
{                                                // BRING BACK A SINGLE INT
	if ( ! open() )
		{return( default_value );
		}
	int	v = default_value;
	if ( fetch() && ROSETTA::typeInt == result.getType( 0 ) )
		{v = result.getInt( 0 );
		}
	close();
	return( v );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string XQUERY::fetchString( const std::string default_value )
{						// BRING BACK SINGLE STRING
	if ( ! open() )
		{return( default_value );
		}
	std::string	v = default_value;
	if ( fetch() )
		{try			   	// CONVERT TYPE IF REQUIRED
			{v = result.getString( 0 );
			}
		catch( ... )
			{v = default_value;
			}
		}
	close();
	return( v );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if X_BDE
bool XQUERY::bdeClose( void )
{
	if ( NULL != qry && qry->Active )   
		{qry->Close();
		}
	return( true );
}
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if X_ING
bool XQUERY::ingQueryClose( void )
{
	if ( ! is_open )                // FREE DYNAMIC DATA BUFFER
		{return( false );
		}
	is_open = false;
	ingBufRemove();
	return( ingClose() );
}
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XQUERY::close( void )
{
#if X_BDE
	return( bdeClose() );
#elif X_ING
	return( ingQueryClose() );
#endif
}
//===========================================================================

