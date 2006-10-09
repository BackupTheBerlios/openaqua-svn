/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Query

\brief    


\date     $Date: 2006/03/12 19:18:10,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Query"

#include  <popa7.h>
#include  <sCS_Connection.hpp>
#include  <sCServer.hpp>
#include  <sSC_Query.hpp>


/******************************************************************************/
/**
\brief  SC_Query - Konstruktor



\param  cs_connection -
\param  client_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Query"

                        SC_Query :: SC_Query (CS_Connection *cs_connection, int64 client_handle )
                     : /* j: QueryHandle gibts nicht mehr apr 05
SC_Handle (cs_connection,NULL,client_handle),
QueryHandle(NO)
*/
{



}

/******************************************************************************/
/**
\brief  ~SC_Query - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Query"

                        SC_Query :: ~SC_Query ( )
{



}


