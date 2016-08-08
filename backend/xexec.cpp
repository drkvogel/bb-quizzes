#include "xdb.h"
#include "xexec.h"
#include "rosetta.h"
#include <stdio.h>
#include <set>
//===========================================================================
XEXEC::XEXEC( XDB *db, const std::string query )
	:
	XSQL( db, query )
{
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
XEXEC::~XEXEC( void )
{
}
//---------------------------------------------------------------------------
std::string XEXEC::getClass( void )
{	return( "XEXEC" );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int XEXEC::getNRows( void )
{
	return( nrows_altered );
}
//---------------------------------------------------------------------------
#if X_BDE
bool XEXEC::bdeExecAction( void )
{
	bool	ok = true;
	try
		{qry->ExecSQL();
		}
	catch ( Exception &e )
		{ok = false;
		}
	return( ok );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XEXEC::bdeExec( void )
{
	bool 	ok;
	Screen->Cursor = crSQLWait;
	try
		{ok = bdeExecAction();
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
const char *XEXEC::ingPlaceholder( void )
{
	return( " ? " );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XEXEC::ingExecParams( void )
{
	IIAPI_SETDESCRPARM		setDescrParm;
	IIAPI_PUTPARMPARM		putParmParm;
	IIAPI_GETDESCRPARM		getDescrParm;
	bool	ok = true;
	static	int	exec_counter = 1;
	static	std::set<int>	buffers;
	char	exec_name[20], exec_text[30];
	exec_counter++;
	int	i;
	int	buffer_id = -1;
	for ( i = 0; i < exec_counter; i++ )
		{if ( buffers.find(i) == buffers.end() )
			{buffer_id = i;
			buffers.insert( buffer_id );
			break;	// FIND UNIQUE UN-USED BUFFER ID
			}
		}
	if ( buffer_id < 0 || buffer_id >= exec_counter )
		{error( 0, "out of buffer IDs" );
		return( false );
		}
	sprintf( exec_name, "e%d", buffer_id );
	sprintf( exec_text, "EXECUTE %s", exec_name );
	queryParm.qy_genParm.gp_callback = NULL;
	queryParm.qy_genParm.gp_closure = NULL;
	queryParm.qy_connHandle = database->getConnHandle();
	queryParm.qy_queryType = IIAPI_QT_QUERY;
	queryParm.qy_queryText = (char *) malloc( query_text.size() + 50 );
	sprintf( queryParm.qy_queryText, "PREPARE %s FROM %s", exec_name,
		query_text.c_str() );
	queryParm.qy_parameters = FALSE;
	queryParm.qy_tranHandle = database->getTranHandle();
	queryParm.qy_stmtHandle = ( II_PTR )NULL;
	IIapi_query( &queryParm );			// INVOKE OPENAPI
	database->setTranHandle( queryParm.qy_tranHandle );
	if ( ! ingGetResult( &queryParm.qy_genParm ) )
		{return( false );
		}
	free( queryParm.qy_queryText );
	if ( ! ingGetDescr( &getDescrParm, queryParm.qy_stmtHandle ) )
		{ingClose();
		return( false );
		}
	if ( getDescrParm.gd_descriptorCount != 0 )
		{error( 0, "number of descriptors is incorrect" );
		ingClose();
		return( false );
		}
    /*
    ** Call IIapi_getQueryInfo()
    ** and process result.
    */
//    IIapi_getQueryInfo( (IIAPI_GETQINFOPARM *) queryParm.qy_stmtHandle );

	if ( ! ingClose() )
		{return( false );
		}

	queryParm.qy_connHandle = database->getConnHandle();
	queryParm.qy_queryType = IIAPI_QT_EXEC;
	queryParm.qy_queryText = (char *) malloc( strlen(exec_text) + 1 );
	strcpy( queryParm.qy_queryText, exec_text );
	queryParm.qy_parameters = (nparam > 0 ) ? TRUE : FALSE;
	queryParm.qy_tranHandle = database->getTranHandle();
	queryParm.qy_stmtHandle = ( II_PTR )NULL;
	IIapi_query( &queryParm );
	database->setTranHandle( queryParm.qy_tranHandle );
	if ( ! ingGetResult( &queryParm.qy_genParm ) )
		{return( false );
		}
	free( queryParm.qy_queryText );
	setDescrParm.sd_genParm.gp_callback = NULL;
      	setDescrParm.sd_genParm.gp_closure = NULL;
  	setDescrParm.sd_stmtHandle = queryParm.qy_stmtHandle;
	setDescrParm.sd_descriptorCount = (II_INT2) nparam;
	setDescrParm.sd_descriptor = ( IIAPI_DESCRIPTOR * )
	    malloc( ( setDescrParm.sd_descriptorCount + 1 ) *
			  sizeof( IIAPI_DESCRIPTOR ) );

	ok = ingDescribeUserParameters( setDescrParm.sd_descriptor );
	if ( ! ok )
		{return( false );
		}
	IIapi_setDescriptor( &setDescrParm );
	if ( ! ingGetResult( &setDescrParm.sd_genParm ) )
		{
//		ingCancel();
		return( false );
		}				// * * * leaks memory
	free( ( II_PTR )setDescrParm.sd_descriptor );
				/* Provide parameters for IIapi_putParms() */
	putParmParm.pp_genParm.gp_callback = NULL;
	putParmParm.pp_genParm.gp_closure = NULL;
	putParmParm.pp_stmtHandle = queryParm.qy_stmtHandle;
	putParmParm.pp_parmCount = 1;
	IIAPI_DATAVALUE		data;
	putParmParm.pp_parmData = (IIAPI_DATAVALUE *) &data;
	ok = ingPutUserParameters( &putParmParm );
	buffers.erase( buffer_id );		// RETURN BUFFER_ID TO POOL
	if ( ! ok )
		{return( false );
		}
	/*
	** Call IIapi_getQueryInfo()
	*/
//	IIapi_getQueryInfo( (IIAPI_GETQINFOPARM *) queryParm.qy_stmtHandle );
	return( ingClose() );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XEXEC::ingExecSimple( void )
{
	IIAPI_GETDESCRPARM		getDescrParm;
	queryParm.qy_genParm.gp_callback = NULL;
	queryParm.qy_genParm.gp_closure = NULL;
	queryParm.qy_connHandle = database->getConnHandle();
	queryParm.qy_queryType = IIAPI_QT_QUERY;
	queryParm.qy_queryText = (char *) malloc( query_text.size() + 1 );
	strcpy( queryParm.qy_queryText, query_text.c_str() );
	queryParm.qy_parameters = FALSE;
	queryParm.qy_tranHandle = database->getTranHandle();
	queryParm.qy_stmtHandle = ( II_PTR )NULL;
	IIapi_query( &queryParm );			// INVOKE OPENAPI
	database->setTranHandle( queryParm.qy_tranHandle );
	if ( ! ingGetResult( &queryParm.qy_genParm ) )
		{return( false );
		}
	free( queryParm.qy_queryText );
	if ( ! ingGetDescr( &getDescrParm, queryParm.qy_stmtHandle ) )
		{ingClose();
		return( false );
		}
	if ( getDescrParm.gd_descriptorCount != 0 )
		{error( 0, "number of descriptors is incorrect" );
		ingClose();
		return( false );
		}
    			/* Call IIapi_getQueryInfo() and process result */
//    IIapi_getQueryInfo( (IIAPI_GETQINFOPARM *) queryParm.qy_stmtHandle );
	if ( ! ingClose() )
		{return( false );
		}
	return( true );
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool XEXEC::exec( void )
{
	nrows_fetched = 0;
	if ( ! construct() )
		{return( false );
		}
#if X_BDE
	return( bdeExec() );
#elif X_ING
	return( ( nparam > 0 ) ? ingExecParams() : ingExecSimple() );
#endif
}
//===========================================================================
#pragma package(smart_init)

