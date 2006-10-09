/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_CacheInfo

\brief    Connection cache data
          Connection  cache data  provides information  for reusing connections.
          For  re-using a connection,  the connection is  stored in a connection
          cache  instead  of  closing  the  connection  when  the  client  has 
          terminated.  A connection from the  connection cache can be identified
          by  a connection ID, or by the  connection name, which has passed when
          creating  the connection the first time. Cached connections are closed
          after a timeout interval defined in the server ini-file.

\date     $Date: 2006/03/12 19:18:05,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_CacheInfo"

#include  <popa7.h>
#include  <sSC_Connection.hpp>
#include  <sSC_CacheInfo.hpp>


/******************************************************************************/
/**
\brief  SC_CacheInfo - Constructor



\param  sc_connection -
\param  connection_string -
\param  connection_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_CacheInfo"

                        SC_CacheInfo :: SC_CacheInfo (SC_Connection *sc_connection, char *connection_string, int32 connection_id )
                     : connection(sc_connection),
  name(NULL),
  id(connection_id)
{

  SetConnectionString(connection_string);

  SetLastUsed();

  sc_connection->SetCacheInfo(this);

}

/******************************************************************************/
/**
\brief  SetConnectionString - 



\param  connection_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetConnectionString"

void SC_CacheInfo :: SetConnectionString (char *connection_string )
{

  if ( name )
    free(name);
  name = NULL;
  
  if ( connection_string && *connection_string )
    name = strdup(connection_string);

}

/******************************************************************************/
/**
\brief  SetLastUsed - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastUsed"

void SC_CacheInfo :: SetLastUsed ( )
{

  last_used.SetTime();

}

/******************************************************************************/
/**
\brief  ~SC_CacheInfo - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_CacheInfo"

                        SC_CacheInfo :: ~SC_CacheInfo ( )
{

  SetConnectionString(NULL);



}


