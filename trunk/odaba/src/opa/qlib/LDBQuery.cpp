/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    LDBQuery

\brief    Database Query
          DBQuery  allows defining  database queries  by means  of an ODABA view
          definition.  A  database  query  usually  re-trieves  data  from  the 
          database.  It  is,  however,  also  pos-sible  to  update  data in the
          database. 
          A  database  query  may  refer  in  different  places  to  OD-ABA  OQL
          expressions.  ODABA-OQL  is  an  object  query  language with specific
          ODABA extensions. 
          You  may run a query against the complete database (global context) or
          in  a reduced context (instance con-text). The context for running the
          query  can be  defined in  the query.  The result  of the query can be
          printed to the console or directed to an output data source.

\date     $Date: 2006/03/12 19:17:49,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LDBQuery"

#include  <popa7.h>
#ifndef   GSRT_DBViewDefEntry_HPP
#define   GSRT_DBViewDefEntry_HPP
#include  <sDBViewDefEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sDBViewDefEntry.hpp>
#include  <sNString.hpp>
#include  <sLDBQuery.hpp>


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
\param  access_mode -
\param  ini_file - Ini-file for data source definitions
\param  user_name_w -
\param  password - Password
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectDataSource"

int32 LDBQuery :: ConnectDataSource (char *data_source_name, PIACC access_mode, char *ini_file, char *user_name_w, char *password )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
    
  if ( dbhandle.IsOpened() )
    DisconnectDataSource(datasource_connection);

  if ( !data_source_name || !*data_source_name )    SDBERR(897)
  strncpy(data_source,data_source_name,sizeof(data_source)-1); 
  
  if ( user_name_w && *user_name_w )    
    strncpy(user,user_name_w,sizeof(user)-1); 
  
  if ( password && *password )    
    strncpy(pwd,password,sizeof(pwd)-1); 

  if ( ini_file && *ini_file )    
    strncpy(LDBQuery::ini_file,ini_file,sizeof(ini_file)-1); 

  client.Initialize(ini_file,"DBQuery",NULL,APT_Console);
  if (  SetupVariables(data_source_name) )           ERROR

  if ( access_mode > PI_Read )
    SetSysVariable("ACCESS_MODE","Write");  
    
  if ( !OpenDictionary(PI_Read) )                    ERROR
  if ( !OpenDatabase() )                             ERROR
  if ( !OpenDBObject() )                             ERROR

  datasource_connection = 1;
RECOVER
  datasource_connection = 0;
ENDSEQ
  return(datasource_connection);
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

int32 LDBQuery :: ConnectDataSource (int32 data_source_id )
{

BEGINSEQ
  if ( datasource_connection == data_source_id )     LEAVESEQ

  if ( !datasource_connection )
    datasource_connection = ConnectDataSource(NULL,PI_Read);
  else                                               SDBERR(898)
RECOVER
  datasource_connection = 0;
ENDSEQ
  return(datasource_connection);
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

\param  server_name -
\param  port_number - Port number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectServer"

int32 LDBQuery :: ConnectServer (char *server_name, int32 port_number )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( server_name )
    strncpy(DataSourceHandle::server_name,server_name,sizeof(DataSourceHandle::server_name));
  server_port = port_number;
  if ( Connect(client) )                         ERROR

  server_connection = 1;
RECOVER

ENDSEQ
  return(server_connection);
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

int32 LDBQuery :: ConnectServer (int32 connect_id )
{

BEGINSEQ
  if ( server_connection == connect_id )             LEAVESEQ

  if ( !server_connection )
    server_connection = ConnectServer(server_name,server_port);
  else                                               SDBERR(898)
RECOVER
  server_connection = 0;
ENDSEQ
  return(server_connection);
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

int32 LDBQuery :: Define (char *view_definition )
{
  DBViewDefEntry   vde(this,++last_qid,view_definition);
  int32        query_id = 0;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( !view_definition )                            ERROR

  view_definitions->AddEntry(&vde);
  query_id = last_qid;

  // hier sollte später noch ein Check erfolgen ...

RECOVER
  query_id = 0;
ENDSEQ
  return(query_id);
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

logical LDBQuery :: DisconnectDataSource (int32 data_source_id )
{
  int             count;
  DBViewDefEntry *vde;
  if ( this )
  {
    count = view_definitions->GetCount();
    while ( count > 0 )
    {
      if ( vde = view_definitions->GetEntry(count) )
        vde->Clear();
      view_definitions->DeleteEntry(count--);
    }
  }
  CloseDictionary();

  return (NO);
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

logical LDBQuery :: DisconnectServer (int32 connect_id )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  Disconnect();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - Execute Query
        The  function executes a  pre-defined aor an  ad-hok database query. The
        result  is returned in area as defined in the query definition. The area
        is  administrated  by  DBQuery  and  will  be removed automatically when
        running the next query.

\return result_area -
-------------------------------------------------------------------------------
\brief i00 - Execute pre-defined database query
        You  may  run  a  pre-defined  database query by referring to  the query
        identifier from the query definition (-> DefineQuery()).
        When  the view definition contains  placeholders a parameter string with
        the  actual values for the placeholders can be passed (e.g. "parm1=Paul;
        …"  for  replacing  %parm1%  with  Paul),  which  will replace the place
        holders in the view definition.

\param  query_id - Query identifier
\param  parm_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char *LDBQuery :: Execute (int32 query_id, char *parm_string )
{
  DBViewDefEntry         *vde;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( !(vde = view_definitions->GetEntry(&query_id)) )
                                                     SDBERR(354)
  result_area = vde->Execute(result_area,parm_string);

RECOVER

ENDSEQ
  return(result_area);
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

char *LDBQuery :: Execute (char *view_definition )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( *view_definition == '?' )
    ShowHelp(view_definition);
  else
  {
    DBViewDefEntry   vde(this,AUTO,view_definition);   SDBCERR
    result_area = vde.Execute(result_area,NULL);
    vde.Clear();
  }
RECOVER

ENDSEQ
  return(result_area);
}

/******************************************************************************/
/**
\brief  LDBQuery - Constructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDBQuery"

                        LDBQuery :: LDBQuery ( )
                     : DataSourceHandle (),
  server_connection(0),
  result_area(NULL,10000),
  datasource_connection(0),
  current_view(NULL),
  view_definitions(NULL)
{

  memset(ini_file,0,sizeof(ini_file));
  memset(user,0,sizeof(user));
  memset(pwd,0,sizeof(pwd));
  
  view_definitions = new GSRT(DBViewDefEntry)(NULL,10,sizeof(DBViewDefEntry),4,1,'I',YES);


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

logical LDBQuery :: ShowAttributes (char *structure_name )
{
  DBStructDef            *struct_def;
  fmcb                   *fmcbptr;
  int32                    offset = 0;
  char                    area[256];
  int32                    indx0 = 0;
  logical                 term = NO;
  result_area = "";
  if ( struct_def = dictionary.GetStructDef(structure_name) )
    while ( struct_def->GetAttrPath(indx0,NO,area,sizeof(area),YES,YES) == indx0 )
    {
      indx0++;
      result_area+=area;
      result_area+='\t';
      if ( fmcbptr = struct_def->SearchField(area,&offset,NULL) )
        result_area+= gvtxbts(area,fmcbptr->fmcbtype,ID_SIZE);
      result_area += '\n';
    }

  return(term);
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

logical LDBQuery :: ShowExtents (char *view_definition )
{
  int32                    indx0 = 0;
  logical                 term = NO;
  PropertyHandle     extents(dictionary,"SDB_Extend",PI_Read);
  PropertyHandle     structures(dictionary,"SDB_Structure",PI_Read);
  PH(extents,ddetype)
  PH(extents,sys_ident)
  PH(structures,ready)
  
  result_area = "";
  while ( extents(indx0++).GetArea() )
  {
    if ( structures(ddetype) && ready.IsTrue() )
    {
      result_area+=sys_ident.GetString();
      result_area+='\t';
      result_area+=ddetype.GetString();
      result_area += '\n';
    }
  }

  return(term);
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

logical LDBQuery :: ShowHelp (char *view_definition )
{
  char                   *arg;
  logical                 term = NO;
  if ( arg = GetKeyParm(view_definition,"Extents",YES,YES) )  
    ShowExtents(arg);
  else if ( arg = GetKeyParm(view_definition,"Attributes",YES,YES) )
    ShowAttributes(arg);
  else if ( arg = GetKeyParm(view_definition,"References",YES,YES) )
    ShowReferences(arg);
  else 
  {
    result_area = "";
    result_area += "Query commands:\n";
    result_area += "  [ DataSource ( data_source_name ) ]\n";
    result_area += "  Select( field=source | field={ expression }; ... )\n";
    result_area += "  From  ( viewpath,...,viewpath | { expression } )\n";
    result_area += "  [ Within ( global_id | local_id | db_oject_name ) ]\n";
    result_area += "  [ Where ( expression ) ]\n";
    result_area += "  [ For   ( expression ) ]\n";
    result_area += "  [ To    ( Path(pathname) [FieldSeparator(char)] [LineSeparator(char)] \n";
    result_area += "                           [StringDelimiter(char)]                      |\n";
    result_area += "            Extent(ext_name) [DataSource(ds_name)]                      )  ]\n";
    result_area += "\nHelp commands:\n";
    result_area += "  ?Extents\n";
    result_area += "  ?Attributes ( structure_name )\n";
    result_area += "  ?References ( structure_name )\n";
  }

  return(term);
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

logical LDBQuery :: ShowReferences (char *structure_name )
{
  DBStructDef            *struct_def;
  fmcb                   *fmcbptr;
  int32                    offset = 0;
  char                    area[256];
  int32                    indx0 = 0;
  logical                 term = NO;
  result_area = "";
  if ( struct_def = dictionary.GetStructDef(structure_name) )
    while ( struct_def->GetRefPath(indx0,NO,area,sizeof(area),NO,YES) == indx0 )
    {
      indx0++;
      result_area+=area;
      result_area+='\t';
      if ( fmcbptr = struct_def->SearchField(area,&offset,NULL) )
        result_area+= gvtxbts(area,fmcbptr->fmcbtype,ID_SIZE);
      result_area += '\n';
    }

  return(term);
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

logical LDBQuery :: Undefine (int32 query_id )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(99)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~LDBQuery - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~LDBQuery"

                        LDBQuery :: ~LDBQuery ( )
{

  if ( this )
    DisconnectDataSource(datasource_connection);

  delete view_definitions;
  view_definitions = NULL;

}


