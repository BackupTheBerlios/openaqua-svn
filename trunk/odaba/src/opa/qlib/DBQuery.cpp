/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBQuery

\brief    


\date     $Date: 2006/03/12 19:17:08,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBQuery"

#include  <popa7.h>
#include  <sNString.hpp>
#include  <sDBQuery.hpp>


/******************************************************************************/
/**
\brief  ConnectDataSource - 


\return data_source_id - Data source connection identifier
-------------------------------------------------------------------------------
\brief i00


\param  data_source_name - Data source name
\param  access_mode -
\param  ini_file - Ini-file for data source definitions
\param  user_name_w -
\param  password - Password
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectDataSource"

int32 DBQuery :: ConnectDataSource (char *data_source_name, PIACC access_mode, char *ini_file, char *user_name_w, char *password )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief i01


\param  data_source_id - Data source connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectDataSource"

int32 DBQuery :: ConnectDataSource (int32 data_source_id )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  ConnectServer - 


\return connect_id - Server connection identifier
-------------------------------------------------------------------------------
\brief i00


\param  server_name -
\param  port_number - Port number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectServer"

int32 DBQuery :: ConnectServer (char *server_name, int32 port_number )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief i01


\param  connect_id - Server connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectServer"

int32 DBQuery :: ConnectServer (int32 connect_id )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  DBQuery - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBQuery"

                        DBQuery :: DBQuery ( )
{



}

/******************************************************************************/
/**
\brief  Define - 


\return query_id - Query identifier

\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Define"

int32 DBQuery :: Define (char *view_definition )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  DisconnectDataSource - 


\return term - Termination code

\param  data_source_id - Data source connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectDataSource"

logical DBQuery :: DisconnectDataSource (int32 data_source_id )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  DisconnectServer - 


\return term - Termination code

\param  connect_id - Server connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectServer"

logical DBQuery :: DisconnectServer (int32 connect_id )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Execute - 


\return result_area -
-------------------------------------------------------------------------------
\brief i00


\param  query_id - Query identifier
\param  parm_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char *DBQuery :: Execute (int32 query_id, char *parm_string )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief i01


\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char *DBQuery :: Execute (char *view_definition )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  ShowAttributes - 


\return term - Termination code

\param  structure_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowAttributes"

logical DBQuery :: ShowAttributes (char *structure_name )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ShowExtents - 


\return term - Termination code

\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowExtents"

logical DBQuery :: ShowExtents (char *view_definition )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ShowHelp - 


\return term - Termination code

\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowHelp"

logical DBQuery :: ShowHelp (char *view_definition )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ShowReferences - 


\return term - Termination code

\param  structure_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowReferences"

logical DBQuery :: ShowReferences (char *structure_name )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Undefine - 


\return term - Termination code

\param  query_id - Query identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Undefine"

logical DBQuery :: Undefine (int32 query_id )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ~DBQuery - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBQuery"

                        DBQuery :: ~DBQuery ( )
{



}


