/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    QueryHandle

\brief    Database Query Handle
          DBQuery  allows defining  database queries  by means  of an ODABA view
          definition.  A  database  query  usually  re-trieves  data  from  the 
          database.  It  is,  however,  also  possible  to  update  data  in the
          database. 
          A  database  query  may  refer  in  different  places  to  ODABA  OQL 
          expressions.  ODABA-OQL  is  an  object  query  language with specific
          ODABA extensions. 
          You  may run a query against the complete database (global context) or
          in  a reduced context (instance context).  The context for running the
          query  can be  defined in  the query.  The result  of the query can be
          printed to the console or directed to an output data source.

\date     $Date: 2006/03/12 19:10:50,82 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "QueryHandle"

#include  <pdefault.h>
#include  <sCDBQuery.hpp>
#include  <sDBQuery.hpp>
#include  <sLDBQuery.hpp>
#include  <sQueryHandle.hpp>


/******************************************************************************/
/**
\brief  Close

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical QueryHandle :: Close ( )
{

  delete query;
  query = NULL;
  return(NO);
}

/******************************************************************************/
/**
\brief  ConnectDataSource - Connect DBQuery to data source
        The  function allows  connection the  DBQuery to  a data source. DBQuery
        allows  only one connection at the time. When connecting to another data
        source the currently connected data source is diconnected before.

\return data_source_id - Data source connection identifier
-------------------------------------------------------------------------------
\brief i00 - Connect by data source name
        Connecting  by  data  source  name  is  required  when connecting to the
        database  the  first  time.  The  function  will  return  a  data source
        connection  identifier,  that  can  be  used  for  re-connecting  to the
        database.  The data source must be defined either in the catalogue or in
        a section of the ini-file with the same name. 
        Usually  the data source should be registered in a data catalogue on the
        server  side.  When  running  the  application in local mode or when the
        data  source is not registered in the data catalogue an ini-file must be
        defined that contains the data source specification.
        User  name and password must be passed  when the data source is password
        protected.

\param  data_source_name - Data source name
\param  access_mode - Access mode
\param  ini_file_w - Ini-file for data source definitions
\param  user_name - User name
\param  password_w - Password
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectDataSource"

int32 QueryHandle :: ConnectDataSource (char *data_source_name, PIACC access_mode, char *ini_file_w, char *user_name, char *password_w )
{

  return(query->ConnectDataSource(data_source_name,access_mode,
                                  ini_file_w,user_name,password_w));

}

/******************************************************************************/
/**
\brief i01 - Connect to data source by data source connection identifier
        The  data source connection identifier allows  refering to a data source
        connection  established in another session.  Data source connections are
        cached  and  can  be  re-used.  Re-using a data source within 15 minutes
        avoids  re-opening the data source. After  not being used 15 minutes the
        data  source  is  closed  and  will  be  re-opened  automatocally  when 
        referring  to the connection by  connection identifier. Thus, connecting
        by  identifier  will  increase  the  application speed especially in web
        applications.
        The  connection  identifier  cannot  be used anymore after disconnecting
        from the data source.

\param  data_source_id - Data source connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectDataSource"

int32 QueryHandle :: ConnectDataSource (int32 data_source_id )
{

  return(query->ConnectDataSource(data_source_id));

}

/******************************************************************************/
/**
\brief  ConnectServer - Connect to Database
        To  run queries in Client/Server mode the DBQuery object must connect to
        the database. Connect is not required when running in local mode.

\return connect_id - Server connection identifier
-------------------------------------------------------------------------------
\brief i00 - Connect by server name
        Connecting  by data server name and  port is required when connecting to
        the  server  the  first  time.  The  function  will return a data server
        connection identifier.
        The  connection identifier  allows re-connection  the application to the
        server.  Connections  are  kept  and  closed after not being used for 15
        minutes.  When referring to the connection via the connection identifier
        within  15 minutes  the opened  connection is re-used. Otherwise DBQuery
        will reconnect automatically.

\param  server_name - Server name
\param  port_number -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectServer"

int32 QueryHandle :: ConnectServer (char *server_name, int32 port_number )
{

  return(query->ConnectServer(server_name,port_number));

}

/******************************************************************************/
/**
\brief i01 - Reconnect server
        This  function  allows  reconnecting  to the server when connections are
        cached  on  the  server  side.  In  this  case  the  connection with the
        returned  connection-id  stays  open  for a defined timeout interval and
        can  be  re-used.  This  is  useful for web applications, where each web
        site connects and disconnects to the server.

\param  connect_id - Server connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectServer"

int32 QueryHandle :: ConnectServer (int32 connect_id )
{

  return(query->ConnectServer(connect_id));

}

/******************************************************************************/
/**
\brief  Define - Define Database Query
        Database  queries  can  be  defined  in  advance  for  running the query
        several  times. The query definition may  contain place holders that can
        be  replaced with updated values each time when executing the query. You
        may define any number of queries.

\return query_id - Query identifier

\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Define"

int32 QueryHandle :: Define (char *view_definition )
{

  return(query->Define(view_definition));

}

/******************************************************************************/
/**
\brief  DisconnectDataSource - Disconnect data source
        The  function  disconnects  the  DBQuery  from the data source. The data
        source  is kept open on the server  side for the next 15 minutes. Before
        running queries again DBQuery must connect to the data source again.

\return term - Termination code

\param  data_source_id - Data source connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectDataSource"

logical QueryHandle :: DisconnectDataSource (int32 data_source_id )
{

  return(query->DisconnectDataSource(data_source_id));

}

/******************************************************************************/
/**
\brief  DisconnectServer - Disconnect from database server
        Disconnecting  DBQuery from  the server  will disconnect the data source
        before  (when  being  opened).  After  disconnecting  you  may  use  the
        connection identifier to re-connect to the server again.

\return term - Termination code

\param  connect_id - Server connection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectServer"

logical QueryHandle :: DisconnectServer (int32 connect_id )
{

  return(query->DisconnectServer(connect_id));

}

/******************************************************************************/
/**
\brief  Execute - Execute Query
        The  function executes a  pre-defined aor an  ad-hok database query. The
        result  is returned in area as defined in the query definition. The area
        is  administrated  by  DBQuery  and  will  be removed automatically when
        running the next query.

\return result_area - Result area
-------------------------------------------------------------------------------
\brief i00 - Execute pre-defined database query
        You  may  run  a  pre-defined  database query by referring to  the query
        identifier from the query definition (-> DefineQuery()).
        When  the view definition contains  placeholders a parameter string with
        the  actual values for the placeholders can be passed (e.g. "parm1=Paul;
        …"  for  replacing  %parm1%  with  Paul),  which  will replace the place
        holders in the view definition.

\param  query_id - Query identifier
\param  parm_string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char *QueryHandle :: Execute (int32 query_id, char *parm_string )
{

  return(query->Execute(query_id,parm_string));

}

/******************************************************************************/
/**
\brief i01 - Execute ad-hok query
        The   function   allows   running   an   ad-hok   query passing the wiew
        definition.  View definitions for ad-hok  queries must not contain place
        holders.

\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char *QueryHandle :: Execute (char *view_definition )
{

  return(query->Execute(view_definition));

}

/******************************************************************************/
/**
\brief  QueryHandle - Constructor
        The  query handle perfoms  DB-query functions. For  running queries on a
        query server, you must pass YES for query client..


\param  query_client - Creating a query client
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QueryHandle"

                        QueryHandle :: QueryHandle (logical query_client )
                     : query(NULL)
{

  Close(); 
  
  if ( query_client )
    query = new CDBQuery();
  else
    query = new LDBQuery();


}

/******************************************************************************/
/**
\brief  Undefine - Undefine database query
        The  function removes a previously defined database query from the list.
        Afterwards  the query identifier vcannot be  used any more for executing
        the queries.

\return term - Termination code

\param  query_id - Query identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Undefine"

logical QueryHandle :: Undefine (int32 query_id )
{

  return(query->Undefine(query_id));

}

/******************************************************************************/
/**
\brief  ~QueryHandle - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~QueryHandle"

                        QueryHandle :: ~QueryHandle ( )
{

  delete query;
  query = NULL;

}


