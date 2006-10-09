/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    DataSourceHandle

\brief    Data source
          A  data  source  describes  an  ODABA  data  source on a certain level
          (Dictionary,  Database, DBObject, Extent, Instance). A data source can
          be  parametrized by  means of  an INI-file.  The INI file contains the
          names  for the  objects on  the different  levels. Not specified lower
          levels  are not opened and have to  be opened in the application (e.g.
          when  defining only dictionary  and database the  extent is not opened
          and  no instance is selected), The datasource is defined as section in
          the INI-file starting with the [datasource name]. 
          A  data  source  can  be  directed  to  a  server.  In  this  case the
          datasource  has  to  be  opened  with  a connected ODABA client or the
          INI-file  must contain  a server  specification. In  the last case the
          data  source  connects  to  the  server automatically when opening the
          data source. The connection is owned by the datasource in this case.
          A  data source cane be opened and  closed as a whole (Open(), Close())
          or  separately on each  definition level (Connect(), OpenDictionary(),
          ...).
          A  data source may have a connection  name, which is used to cache the
          connection  when running in client/server mode. The connection name is
          used  to reconnect to  the server using  a cached connection, which is
          faster than re-establishing the connection from scratch.

\date     $Date: 2006/06/25 19:05:23,00 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DataSourceHandle"

#include  <pdefault.h>
#include  <igvts.h>
#include  <igvtx.h>
#include  <iopai.h>
#include  <isosi.h>
#include  <sDBObjectHandle.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sPropertyHandle.hpp>
#include  <sServices.hpp>
#include  <ssvel.hpp>
#include  <sDataSourceHandle.hpp>


/******************************************************************************/
/**
\brief  BeginTransaction - Start transaktion for the data source
        Data   sources   provide   simple   transaction   control.   Data source
        transactions  cannot be nested,  i.e. when a  transaction is running for
        the datasource no other transaction can be started. 
        Using nested transactions is possible with the DBObjectHandle.

\return term - Termination code

\param  ext_ta - External Transaction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BeginTransaction"

logical DataSourceHandle :: BeginTransaction (logical ext_ta )
{
  DBObjectHandle object;
  logical        term = NO;
BEGINSEQ
  object = object_handle ? (DBObjectHandle &)object_handle
                         : (DBObjectHandle &)dbhandle;
  if ( transaction )                                 ERROR

  if ( !(transaction = object.BeginTransaction(ext_ta)) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close - Close DataSourceHandle
        The  handles on all  hierarchy levels (Dictionary  to Extent) are closed
        when they are owned (opened) by the DataSourceHandle.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical DataSourceHandle :: Close ( )
{

  Disconnect();


  return(NO);
}

/******************************************************************************/
/**
\brief  CloseDBObject - Close DBObjectHandle
        The  DBObjectHandle and subsequent  handles (PropertyHandles) are closed
        beginning  with the lowest  opened handle. Handles  are closed only when
        they  have been opened by the datasource handle. Property handles opened
        by the application must be closed by the application before.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDBObject"

logical DataSourceHandle :: CloseDBObject ( )
{

  CloseProperty();
  
  if ( object_opened )
  {
    if ( transaction )
      CommitTransaction();
    object_handle.Close();
    object_opened = NO;
  }
  object_handle.Close();

  return(NO);
}

/******************************************************************************/
/**
\brief  CloseDatabase - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDatabase"

logical DataSourceHandle :: CloseDatabase ( )
{

  if ( transaction )
    CommitTransaction();
  
  CloseDBObject();
  
  if ( base_opened )
  {
    if ( transaction )
      CommitTransaction();
    base_opened = NO;
  }
  dbhandle.Close();

  return(NO);
}

/******************************************************************************/
/**
\brief  CloseDictionary - Close DictionaryHandle
        The   DictionaryHandle   and   subsequent   handles   for   Database,  
        DatabaseObject  and Extent  are closed  beginning with the lowest opened
        handle.  Handles  are  closed  only  when  they  have been opened by the
        datasource handle.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDictionary"

logical DataSourceHandle :: CloseDictionary ( )
{

  CloseDatabase();
  CloseResourceDB();
  
  if ( dict_opened )
  {
    dict_opened = NO;
  }
  dictionary.Close();

  return(NO);
}

/******************************************************************************/
/**
\brief  CloseProperty - Close PropertyHandle
        The  PropertyHandle for the defined extent is closed. Handles are closed
        only when they have been opened by the datasource handle.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseProperty"

logical DataSourceHandle :: CloseProperty ( )
{

  if ( extent_opened )
  {
    delete extent_pi;
    extent_opened = NO;
  }
  extent_pi = NULL;

  return(NO);
}

/******************************************************************************/
/**
\brief  CloseResourceDB - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseResourceDB"

logical DataSourceHandle :: CloseResourceDB ( )
{

  res_opened = NO;
  reshandle.Close();

  return(NO);
}

/******************************************************************************/
/**
\brief  CommitTransaction - Terminate transaction
        The  datasource transaction  it stopped  and modifications are stored to
        the  database.  Commiting  the  data  source transaction will commit all
        subsequent DBObjectHandle transactions that are still running.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommitTransaction"

logical DataSourceHandle :: CommitTransaction ( )
{
  DBObjectHandle object = object_handle;
  logical       term = NO;
BEGINSEQ
  object = object_handle ? (DBObjectHandle &)object_handle
                         : (DBObjectHandle &)dbhandle;
  
  if ( !transaction )                                ERROR
  
  term = object.CommitTransaction(transaction);
  transaction = 0;   // geht nur solange in BeginTransaction keine Verschachtelung zugelassen wird


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Connect - Connect DataSourceHandle to server
        The  function connects the DataSourceHandle to a server. The server name
        (server_name)  and  port  number  (port_number)  must  be defined in the
        DataSourceHandle before calling this function. 
        If  no client object (odaba_client) is passed a client object is created
        when  a  server  is  defined.  If no server name is defined the function
        does not try to connect.

\return term - Termination code

\param  odaba_client - ODABA Client Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical DataSourceHandle :: Connect (ODABAClient &odaba_client )
{
  ODABAClient             main_client(GetMainClient());
  logical                 term = NO;
BEGINSEQ
  Disconnect();
  
  if ( !(client = odaba_client) )
    if ( main_client && 
         ( !main_client.IsConnected()  ||
           (!strcmp(server_name,main_client.GetHost()) &&
            server_port == main_client.GetPort()         )  )  )
      client = main_client;
  
  if ( !client )
  {
    client.Open(NULL,NULL);
    client_created = YES;
  }
  
  if ( *server_name )
  {
    if ( !server_port )
      server_port = 6123;
    if ( client.Connect(server_name,server_port,connection_name) )  ERROR
    client_connected = YES;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DataSourceHandle - Construcktor
        The   constructor   creates   a   DataSourceHandle.   Before  openeing a
        datasource  database pathes and object and  extent names have to be set.
        This  can  be  done  by  explicitly  setting the pathes and names in the
        programm  or  by  means  of  an  INI-file  using  the  SetupVariables() 
        function..


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataSourceHandle"

     DataSourceHandle :: DataSourceHandle ( )
                     :   extent_pi(NULL),
  accmode(PI_Read),
  transaction(UNDEF),
  version(USHORTMAX),
  schema_version(USHORTMAX),
  online_version(NO),
  sys_appl(AUTO),
  collopt(NO), 
  netopt(NO), 
  dict_opened(NO),
  res_opened(NO),
  base_opened(NO),
  object_opened(NO),
  extent_opened(NO),
  client_created(NO),
  client_connected(NO)
{

  SDBRESET
  
  Initialize();

}

/******************************************************************************/
/**
\brief  Disconnect - Disconnect from server
        The  function disconnects from the  server. When the DataSourceHandle is
        still opened it is closed (Close()) before disconnecting. 
        Disconnecting  will delete the  ODABAClient when it  has been created by
        the DataSourceHandle.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

logical DataSourceHandle :: Disconnect ( )
{
  logical                 term = NO;
  CloseDictionary();
  
  if ( client &&  client_connected == YES )
    client.Disconnect();
  client_connected = NO;
  
  client.Close();
  client_created = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  GetClient - Get client handle from data source
        The function returns the client handle from the data source.

\return odaba_client - ODABA Client Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClient"

ODABAClient &DataSourceHandle :: GetClient ( )
{


  return(client);
}

/******************************************************************************/
/**
\brief  Initialize - Initialize DataSourceHandles



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DataSourceHandle :: Initialize ( )
{

  memset(server_name    ,0,sizeof(server_name));
  memset(connection_name,0,sizeof(connection_name));
  memset(dict_path      ,0,sizeof(dict_path));
  memset(res_path       ,0,sizeof(res_path));
  memset(db_path        ,0,sizeof(db_path));
  memset(workspace      ,0,sizeof(workspace));
  memset(object_name    ,0,sizeof(object_name));
  memset(struct_name    ,0,sizeof(struct_name));
  memset(extent_name    ,0,sizeof(extent_name));
  memset(inst_key       ,0,sizeof(inst_key));
  
  server_port    = 0;
  version        = CUR_VERSION;
  schema_version = CUR_VERSION;
  system_version = CUR_VERSION;
  accmode        = PI_Read;
  netopt         = NO;

}

/******************************************************************************/
/**
\brief  Open - Open DataSourceHandle
        A  Datasource  consists  of  a  Dictionary and a Database. In addition a
        DatabaseObject  and  an  Extent  can  be defined. The data source can be
        closed  using  the  function  Close().  If a DataSourceHandle is already
        opened  this  is  closed  before reopening the DataSourceHandle with the
        current parameters.
        The  data source is defined by  means of external resource defintions in
        the  DataSourceHandle  (server_name,  dict_path,  db_path,  object_name,
        extent_name, inst_key).

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - Open empty data source
        A  data  source  can  be  opened  when  the  application  has filled the
        external  specifications  for  the  data  source. At least the dict_path
        should be set in the data source before openeing. 
        The  data source should  be opened only,  when all external resources to
        be  accessed  are  defined  in  the  data source. When the client is not
        connected  the  server  specifications  (server_name  and  port_number) 
        shuold  be  set  as  well.  This  is  not necessary when running a local
        application.

\param  odaba_client - ODABA Client Handle
\param  acc_mod - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DataSourceHandle :: Open (ODABAClient &odaba_client, PIACC acc_mod )
{
  char        sysver[17];
  logical     term = NO;
BEGINSEQ
  if ( Connect(odaba_client) )                       ERROR
 
  if ( system_version != CUR_VERSION )
  {
    gvtxltoa(system_version,sysver,10);
    SetSysVariable("SYSTEM_VERSION",sysver);
  }

  if ( !OpenDictionary(acc_mod) )                    ERROR
  
  RemoveSysVariable("SYSTEM_VERSION");
  OpenResourceDB();
  
  if ( !OpenDatabase() )                             ERROR
  if ( !OpenDBObject() )                             ERROR
  if ( *extent_name && *extent_name != '*' && !OpenProperty(NULL) )      
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - Opening datasource based on ini-file section
        The  function  opens  the  data  source  based  on  external  resource 
        definitions   passsed   in   the   ini-file.   The  inifile section name
        containing  the resource definitions is passed as datasource_name to the
        function.  The resource definitions  in the data  source are filled from
        the corresponding resource definitions in the ini-file.

\param  odaba_client - ODABA Client Handle
\param  ini_file - Application ini-file
\param  datasource_name - Name of the data source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DataSourceHandle :: Open (ODABAClient &odaba_client, char *ini_file, char *datasource_name )
{
  logical      term    = NO;
  if ( ini_file && *ini_file )
  {
    PushSystemVariables();
    SystemVariables()->svelfini(ini_file,datasource_name);
  }
  else if ( datasource_name && *datasource_name > ' ' )
    strncpy(data_source,datasource_name,sizeof(data_source)-1);
  
  term = Open(odaba_client,datasource_name);
  
  if ( ini_file && *ini_file )
    PopSystemVariables();


  return(term);
}

/******************************************************************************/
/**
\brief  i1 - Opening data source from catalogue
        The  function  opens  the  data  source  based  on  external  resource 
        definitions  passsed stored in  the data source  catalogue. In this case
        the  external resource  defitions are  read from  the catalogue where an
        entry with the passed datasource_name must exist. 
        Using  the catalogue feature the catalogue  data source must be provided
        in  a  catalogue  [DATA-CATALOGUE]  section  of  the  ini-file  (local 
        application)  or in a corresponding section  of the server. The resource
        definitions  in  the  data  source  are  filled  from  the corresponding
        resource  definitions  in  the  catalogue  entry before opening the data
        source.

\param  odaba_client - ODABA Client Handle
\param  datasource_name - Name of the data source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DataSourceHandle :: Open (ODABAClient &odaba_client, char *datasource_name )
{
  char      *ldb = GetSysVariable("LARGE_DB");
  char      *pif = GetSysVariable("PLATFORM_INDEPENDENT");
  char      *sysvar;
  logical    term = NO;

BEGINSEQ
  Close();
  
  if ( SetupVariables(datasource_name) )             ERROR

  if ( sysvar = GetSectionVariable("LARGE_DB",datasource_name) )
    if ( *sysvar == 'Y' )
      SetSysVariable("LARGE_DB","YES");
  if ( sysvar = GetSectionVariable("PLATFORM_INDEPENDENT",datasource_name) )
    if ( *sysvar == 'Y' )
      SetSysVariable("PLATFORM_INDEPENDENT","YES");
      
  term = Open(odaba_client,PI_Read);
  
  if ( ldb && *ldb )
    SetSysVariable("LARGE_DB",ldb);
  else
    RemoveSysVariable("LARGE_DB");
  
  if ( pif && *pif )
    SetSysVariable("PLATFORM_INDEPENDENT",pif);
  else
    RemoveSysVariable("PLATFORM_INDEPENDENT");
  

RECOVER
  Close();
  Initialize();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenDBObject - Open DBObjectHandle
        The  DBObjectHandle  is  opened  for  the database object defined in the
        database  path (object_name). The DatabaseHandle  of the DataSource must
        be  opened before.  If the  DBObjectHandle is  already opened it will be
        closed before opening the new DBObjectHandle (CloseDBObject()). 
        When  the object name is empty the root object of the opened database is
        provided.

\return ohandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDBObject"

DBObjectHandle &DataSourceHandle :: OpenDBObject ( )
{

BEGINSEQ
  if ( !dbhandle )                                   SDBERR(107)
    
  if ( object_handle )
    if ( CloseDBObject() )                           ERROR

  if ( transaction )                                 SDBERR(516)

  if ( !*object_name || *object_name == '*' )
    object_handle = (DBObjectHandle &)dbhandle;
  else
  {
    if ( object_handle.Open(dbhandle,object_name,accmode,version) )
                                                     ERROR
    object_opened = YES;  
  }

RECOVER
  int   saverr = SDBERROR;
  CloseDBObject();
  SDBISET(saverr)
ENDSEQ
  return(object_handle);
}

/******************************************************************************/
/**
\brief  OpenDatabase - 


\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDatabase"

DatabaseHandle &DataSourceHandle :: OpenDatabase ( )
{

BEGINSEQ
  if ( !dictionary )                                 SDBERR(106)
    
  if ( dbhandle )
    if ( CloseDatabase() )                           ERROR

  if ( !*db_path )
    dbhandle = (DatabaseHandle &)dictionary;
  else
  {
    if ( dbhandle.Open(dictionary,db_path,accmode,netopt,online_version,
                                   !*object_name || *object_name == '*' ? version : CUR_VERSION,
                                   RES_automatic,sys_appl) )
                                                     ERROR
    base_opened = YES;  
  }

  if ( dbhandle.IsOpened() && *workspace > ' ' )
    if ( dbhandle.OpenWorkspace(workspace,NULL,!netopt) )  // ggf. brauchen wir noch den Nutzer
                                                     ERROR
  
  if ( !*object_name || *object_name == '*' )
    object_handle = (DBObjectHandle &)dbhandle;
RECOVER
  int   saverr = SDBERROR;
  CloseDatabase();
  SDBISET(saverr)

ENDSEQ
  return(dbhandle);
}

/******************************************************************************/
/**
\brief  OpenDictionary - Open DictionaryHandle
        The  DictionaryHandle  is  opened  only  when a dictionary path has been
        defined  (dict_path). If  another dictionary  has already been opened it
        is  closed  (CloseDictionary())  before re-opening the DictionaryHandle.
        The  DictionaryHandle  is  opened  with  the  access  mode passed to the
        function.  When no database path (db_path) is defined and no access mode
        is  passed the DictionaryHandle  is opened with  the access mode defined
        for the database,

\return dictptr - Dictionary handle

\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDictionary"

DictionaryHandle &DataSourceHandle :: OpenDictionary (PIACC accopt )
{

BEGINSEQ
  if ( dictionary )
    if ( CloseDictionary() )                         ERROR

  if ( !*dict_path )                                 SDBERR(186)
    
  if ( dictionary.Open(client,dict_path,*db_path ? accopt : accmode,YES,schema_version,RES_automatic,sys_appl) )
                                                     ERROR
  dict_opened = YES;  

RECOVER
  int   saverr = SDBERROR;
  CloseDictionary();
  SDBISET(saverr)

ENDSEQ
  return(dictionary);
}

/******************************************************************************/
/**
\brief  OpenProperty - Open PropertyHandle
        The  PropertyHandle can be opened only when the DBObjectHandle is opened
        for  the  data  source  and  an  extent  name  (extent_name)  has  been 
        specified.  If  a   PropertyHandle  is  already opened it will be closed
        (CloseProperty()) before re-open the handle.

\return property_handle - Pointer to a property handle

\param  extname - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenProperty"

PropertyHandle *DataSourceHandle :: OpenProperty (char *extname )
{

BEGINSEQ
  if ( !extname )
    extname = extent_name;
    
  if ( !object_handle || !*extname || *extname == '*' )
                                                     SDBERR(108)
    
  if ( extent_pi )
    if ( CloseProperty() )                           ERROR

  if ( !(extent_pi = new PropertyHandle(object_handle,extname,accmode) ) )
                                                     SDBERR(95)
                                                     SDBCERR
  extent_opened = YES;
RECOVER
  int   saverr = SDBERROR;
  CloseProperty();
  SDBISET(saverr)

ENDSEQ
  return(extent_pi);
}

/******************************************************************************/
/**
\brief  OpenResourceDB - 


\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenResourceDB"

DatabaseHandle &DataSourceHandle :: OpenResourceDB ( )
{

BEGINSEQ
  if ( !dictionary )                                 SDBERR(106)
    
  if ( reshandle )
    if ( CloseResourceDB() )                         ERROR

  if ( !*res_path )
    ; // hier sollte das dictionary als db geoeffnet werden, dazu felt aber (system)dict
  else
  {
    if ( reshandle.Open(dictionary,res_path,PI_Read,YES,YES,CUR_VERSION,
                                   RES_automatic,sys_appl) )
                                                     ERROR
    res_opened = YES;  
  }
RECOVER
  int   saverr = SDBERROR;
  CloseResourceDB();
  SDBISET(saverr)

ENDSEQ
  return(reshandle);
}

/******************************************************************************/
/**
\brief  ResetObjectHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetObjectHandle"

void DataSourceHandle :: ResetObjectHandle ( )
{

  if ( object_handle == dbhandle )
  {
    dbhandle.Reset();
    if ( dbhandle == dictionary )
      dictionary.Reset();
  }
  object_handle.Reset();

}

/******************************************************************************/
/**
\brief  RollBack - Roll back modifications made in the transaction
        All  modification  made  since  the  transaction  has  been  started are
        removed.   The   transaction   is   stopped.   If   there sur subsequent
        transactions opened by DBObjectHandles those are closed as well.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RollBack"

logical DataSourceHandle :: RollBack ( )
{
  DBObjectHandle object;
  logical        term = NO;
BEGINSEQ
  object = object_handle ? (DBObjectHandle &)object_handle
                         : (DBObjectHandle &)dbhandle;
  if ( !transaction )                                ERROR
  
  term = object.RollBack(transaction);
  transaction = 0;   // geht nur solange in BeginTransaction keine Verschachtelung zugelassen wird
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetConnectionName - Set name for connection cache
        The  function wil initialize  a unique name  for the connection to cache
        the  connection on  the server  side. When  no name (cache_string) or an
        empty string has passed, the connection name is reset.

\return term - Termination code

\param  cache_string - Unique connection name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetConnectionName"

logical DataSourceHandle :: SetConnectionName (char *cache_string )
{
  logical                 term = NO;
  memset(connection_name,0,sizeof(connection_name));

  if ( cache_string && *cache_string )
    strncpy(connection_name,cache_string,sizeof(connection_name)-1);

  return(term);
}

/******************************************************************************/
/**
\brief  SetDBObject - Set DBObjectHandle
        The  function allows setting an  opened DBObjectHandle as DBObjectHandle
        for  the  DataSourceHandle.  A  DBObjectHandle set with this function is
        not  closed  when  calling  (CloseDBObject()). When the DataSourceHandle
        has  already opened  it will  be closed (CloseDBObject()) before setting
        the new DBObjectHandle.

\return term - Termination code

\param  ohandle - 
\param  w_objname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDBObject"

logical DataSourceHandle :: SetDBObject (DBObjectHandle &ohandle, char *w_objname )
{
  logical                 term = NO;
BEGINSEQ
  if ( CloseDBObject() )                             ERROR
  
  if ( w_objname )
    gvtxbts(object_name,w_objname,sizeof(object_name)-1);
  
  object_handle = ohandle;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDataSource - Set data source definitions
        The  function sets  the external  and internal  resources as copied from
        the  passed  data  source  handle.  Opened  internal  resources  (access
        handle)  will not be closed when  closing or destructing the data source
        handle but when closing the original data source handle.

\return term - Termination code

\param  dbdefptr - Data source handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical DataSourceHandle :: SetDataSource (DataSourceHandle *dbdefptr )
{
  logical                 term = NO;
  netopt  = dbdefptr->netopt;
  accmode = dbdefptr->accmode;
  
  if ( *dbdefptr->server_name )
    strcpy(server_name,dbdefptr->server_name);
  if ( dbdefptr->server_port )
    server_port = dbdefptr->server_port;
    
  SetDictionary(dbdefptr->dictionary,dbdefptr->dict_path);
  SetResourceDB(dbdefptr->reshandle,dbdefptr->res_path);
  SetDatabase(dbdefptr->dbhandle,dbdefptr->db_path);
  SetDBObject(dbdefptr->object_handle,dbdefptr->object_name);
  return(term);
}

/******************************************************************************/
/**
\brief  SetDatabase - 


\return term - Termination code

\param  db_handle - Pointer to database handle
\param  w_basepath - Path for the opened database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDatabase"

logical DataSourceHandle :: SetDatabase (DatabaseHandle &db_handle, char *w_basepath )
{
  logical                 term = NO;
BEGINSEQ
  if ( CloseDatabase() )                                ERROR
  
  if ( w_basepath )
    gvtxbts(db_path,w_basepath,sizeof(db_path)-1);

  dbhandle = db_handle;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDictionary - Set DictionaryHandle
        The   function   allows   setting   an   opened   DictionaryHandle   as 
        DictionaryHandle  for the DataSourceHandle.  A DictionaryHandle set with
        this  function  is  not  closed when calling (CloseDictionary()). If the
        DataSourceHandle  has  already  an  opened   DictionaryHandle it will be
        closed (CloseDictionary()) before setting the new handle.

\return term - Termination code

\param  dictptr - Dictionary handle
\param  w_dictpath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDictionary"

logical DataSourceHandle :: SetDictionary (DictionaryHandle &dictptr, char *w_dictpath )
{
  logical                 term = NO;
BEGINSEQ
  if ( CloseDictionary() )                          ERROR
  
  if ( w_dictpath )
    gvtxbts(dict_path,w_dictpath,sizeof(dict_path)-1);

  dictionary = dictptr;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetResourceDB - 


\return term - Termination code

\param  db_handle - Pointer to database handle
\param  w_basepath - Path for the opened database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetResourceDB"

logical DataSourceHandle :: SetResourceDB (DatabaseHandle &db_handle, char *w_basepath )
{
  logical                 term = NO;
BEGINSEQ
  if ( CloseResourceDB() )                            ERROR
  
  if ( w_basepath )
    gvtxbts(res_path,w_basepath,sizeof(res_path)-1);

  reshandle = db_handle;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetVariables - Set variables from INI-File
        The  function  Initializes  the  DataSourceHandle  from  the data source
        section in the INI-file.
        The   data   source   variables   must   be   defined   in   a   section
        [datasource_name]  in  the  INI-file.  This  section  may  contain  the 
        following variables:
        ODABA_SERVER=server_name
        The  server_location  specifies  the  server  name ( e.g. ODABAServer1).
        When  no server is specified the  resources are supposed to be available
        locally. 
        ODABA_SERVER_PORT=server_port
        The  port number  must be  the same  that has been used for starting the
        servers (default is 6123).
        DICTIONARY=dict_path
        This  variable defines the resource database (dictionary). This variable
        is  mandatory. The value may refer to a server variable that defines the
        path  on the server.  Server variables must  be enclosed in % characters
        (e.g. %DICT_PATH%).
        DATABASE=db_path
        This  variable defines the  complete path to  the database that contains
        the  application  data.  The  value  may refer to a server variable that
        defines  the path on the server. Server  variables must be enclosed in %
        characters (e.g. %DB_PATH%).
        WORKSPACE=workspace
        When  the workspace feature is enabled  for the database a workspace can
        be  defined  as  active  workspace  for  the  data  source  by passing a
        workspace name or a workspace path.. 
        OBJECT=object_name
        The  name of database object must be  specified if a sub object space in
        the database is to be opened..
        EXTENT=extent_name
        Name of an extent when the DataSource refers to a certain collection. 
        STRUCTURE=struct_name
        The  structure  name  is  used  in  some  cases  for performing metadata
        operetions  (e.g. copying a structure definition to another dictionary).
        It  is has no direct  influence on the data  source but can be retrieved
        from the application. 
        SCHEMA_VERSION=schema_version
        Schema  version  when  the  application  should  be opened with an older
        version   (not   the   current   version)   of  the dictionary (resource
        database).  When no schema  version or AUTO  is passed the database will
        be opened with the current schema version.
        VERSION=version  
        Version  number  for  the  database  object (DBObject) when the database
        object  should be opened  with an older  (not the current) version. When
        no  version number  or AUTO  is passed  the database will be opened with
        the current version.
        ONLINE_VERSION=online_version 
        This  option activates online-versioning (YES)  when the database schema
        has  been  changed.  When  not  using  online  version  feature (NO) the
        database  has to be reorganized before a new schema version can be used.
        Default is NO.
        NET=netopt     
        When  opening  a  data  source  in  local or file server mode (no server
        defined)  this option  can be  defined in  Windows environments to share
        the database with other applications. Default is NO.
        ACCESS_MODE=accmode
        This  variable  has  to  be  defined for accessing the database in write
        mode (Write).
        DISABLE_CONTEXT=sys_appl
        This  option  allows  deactivating  the database context defined fpr the
        project,  i.e. the logical  consistency or busines  rules defined by teh
        application.  This  is  useful  e.g.  for  maintenance or reorganisation
        processes. Default is NO.
        Alternatively  to  the  ini-file  definitions  tha  data  source  can be
        described  in a data catalogue.  In this case you  can refer to the data
        catalogue, instead using the inivariable
        DATA_SOURCE=data_source
        Data  source  refers  to  the  data  source  to  be  opened  in the file
        catalogue.  Usually this is teh same name as the data source name passed
        to  the function,  but it  is also  possible to refer to another name in
        this place.

\return term - Termination code

\param  datasource_name - Name of the data source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVariables"

logical DataSourceHandle :: SetVariables (char *datasource_name )
{
  char      *sysvar;
  logical    term = NO;
BEGINSEQ
  Initialize();
  
  if ( datasource_name && *datasource_name > ' ')
  {
    RemoveSysVariable("ODABA_SERVER");
    RemoveSysVariable("CONNECTION_ID");
    RemoveSysVariable("DICTIONARY");
    RemoveSysVariable("DATABASE");
    RemoveSysVariable("RESOURCES");
    RemoveSysVariable("WORKSPACE");
    RemoveSysVariable("OBJECT");
    RemoveSysVariable("EXTENT");
    RemoveSysVariable("STRUCTURE");   // nur für Metadaten-operationen
    RemoveSysVariable("INSTANCE");
    RemoveSysVariable("SCHEMA_VERSION");
    RemoveSysVariable("VERSION");
    RemoveSysVariable("NET");
    RemoveSysVariable("ACCESS_MODE");
    RemoveSysVariable("DISABLE_CONTEXT");
    RemoveSysVariable("ONLINE_VERSION");
    RemoveSysVariable("DATA_SOURCE");
    RemoveSysVariable("XS_NAMESPACE");
    RemoveSysVariable("OXS_NAMESPACE");
  }
  GetSectionVariable("XS_NAMESPACE",datasource_name);
  GetSectionVariable("OXS_NAMESPACE",datasource_name);

  *dict_path   = 0;
  if ( datasource_name != data_source )
    *data_source = 0;
  
  if ( sysvar = GetSectionVariable("SYSTEM_VERSION",datasource_name) )
    system_version = atoi(sysvar);
  
  if ( (sysvar = GetSectionVariable("DATA_SOURCE",datasource_name)) &&
       *sysvar )            
  {
    SDBEV1("DATA_SOURCE",0)
    if ( strlen(sysvar) >= sizeof(data_source) )     SDBERR(58)
    strncpy(data_source,sysvar,sizeof(data_source)-1);
    LEAVESEQ  // open using catalogue
  }
  
  if ( (sysvar = GetSectionVariable("ODABA_SERVER",datasource_name)) &&
       *sysvar )            
  {
    SDBEV1("ODABA_SERVER",0)
    if ( strlen(sysvar) >= sizeof(server_name) )     SDBERR(58)
    strncpy(server_name,sysvar,sizeof(server_name)-1);
    server_port = 6123;

    if ( (sysvar = GetSectionVariable("ODABA_SERVER_PORT",datasource_name)) &&
         *sysvar )            
      server_port = atol(sysvar);
  }
  
  if ( (sysvar = GetSectionVariable("CONNECTION_ID",datasource_name)) &&
       *sysvar )                                    
  {  
    SDBEV1("CONNECTION_ID",0)
    if ( strlen(sysvar) >= sizeof(connection_name) )SDBERR(58)
    strncpy(connection_name,sysvar,sizeof(connection_name)-1);
  }     
  
  if ( !(sysvar = GetSectionVariable("DICTIONARY",datasource_name)) ||
       !*sysvar )                                    ERROR
  SDBEV1("DICTIONARY",0)
  if ( strlen(sysvar) >= sizeof(dict_path) )         SDBERR(58)
  strncpy(dict_path,sysvar,sizeof(dict_path)-1);
       
  if ( sysvar = GetSectionVariable("DATABASE",datasource_name) )                              
  {
    SDBEV1("DATABASE",0)
    if ( strlen(sysvar) >= sizeof(db_path) )         SDBERR(58)
    strncpy(db_path,sysvar,sizeof(db_path)-1);
  }
  
  if ( sysvar = GetSectionVariable("RESOURCES",datasource_name) )                              
  {
    SDBEV1("RESOURCES",0)
    if ( strlen(sysvar) >= sizeof(res_path) )        SDBERR(58)
    strncpy(res_path,sysvar,sizeof(res_path)-1);
  }
  
  if ( sysvar = GetSectionVariable("WORKSPACE",datasource_name) )                              
  {
    SDBEV1("WORKSPACE",0)
    if ( strlen(sysvar) >= sizeof(workspace) )         SDBERR(58)
    strncpy(workspace,sysvar,sizeof(workspace)-1);
  }
  
  if ( sysvar = GetSectionVariable("OBJECT",datasource_name) )   
  {
    SDBEV1("OBJECT",0)
    if ( strlen(sysvar) >= sizeof(object_name) )     SDBERR(58)
    strncpy(object_name,sysvar,sizeof(object_name)-1);
  }

  if ( sysvar = GetSectionVariable("EXTENT",datasource_name) )   
  {
    SDBEV1("EXTENT",0)
    if ( strlen(sysvar) >= sizeof(extent_name) )     SDBERR(58)
    strncpy(extent_name,sysvar,sizeof(extent_name)-1);
  }
  
  if ( sysvar = GetSectionVariable("STRUCTURE",datasource_name) )   
  {
    SDBEV1("STRUCTURE",0)
    if ( strlen(sysvar) >= sizeof(struct_name) )     SDBERR(58)
    strncpy(struct_name,sysvar,sizeof(struct_name)-1);
  }
  
  if ( sysvar = GetSectionVariable("INSTANCE",datasource_name) )   
  {
    SDBEV1("INSTANCE",0)
    if ( strlen(sysvar) >= sizeof(inst_key) )        SDBERR(58)
    strncpy(inst_key,sysvar,sizeof(inst_key)-1);
  }
  
  if ( (sysvar = GetSectionVariable("SCHEMA_VERSION",datasource_name)) && gvtsicmp(sysvar,"AUTO",0) )   
    if ( !strcmp(sysvar,"CURRENT_VERSION") )
      schema_version = USHORTMAX;
    else
      schema_version = atoi(sysvar);
  
  if ( (sysvar = GetSectionVariable("VERSION",datasource_name)) && gvtsicmp(sysvar,"AUTO",0) )   
    if ( !strcmp(sysvar,"CURRENT_VERSION") )
      version = USHORTMAX;
    else
      version = atoi(sysvar);
  
  if ( (sysvar = GetSectionVariable("NET",datasource_name)) && !gvtsicmp(sysvar,"YES",0) )   
    netopt = YES;
  
  if ( (sysvar = GetSectionVariable("DISABLE_CONTEXT",datasource_name)) )
    sys_appl = gvtsicmp(sysvar,"YES",0) ? NO : YES;   
  
  if ( (sysvar = GetSectionVariable("ONLINE_VERSION",datasource_name)) && !gvtsicmp(sysvar,"YES",0) )   
    online_version = YES;
  else
    online_version = NO;
//    SetSysVariable("ONLINE_VERSION","YES");
  
  if ( (sysvar = GetSectionVariable("ACCESS_MODE",datasource_name)) && !gvtsicmp(sysvar,"WRITE",0) )   
    accmode = PI_Write;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup - Setup data source parameters
        The  function updates the external resource references from the ini-file
        and/or  the data catalogue.  The ini-file passed  to the function is set
        as current ini-file for the data source. 
        External  definitions  are  copied  from  the ini-file or data catalogue
        section according to the passed datasource_name into the data source.

\return term - Termination code

\param  ini_file - Application ini-file
\param  datasource_name - Name of the data source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical DataSourceHandle :: Setup (char *ini_file, char *datasource_name )
{

  if ( ini_file && *ini_file )
  {
    PushSystemVariables();
    SystemVariables()->svelfini(ini_file,datasource_name);
    SetVariables(datasource_name);
    PopSystemVariables();
  }
  else if ( datasource_name && *datasource_name > ' ' )
    strncpy(data_source,datasource_name,sizeof(data_source)-1);
  
  return(SystemServices()->SetupDataSource(this));

}

/******************************************************************************/
/**
\brief  SetupVariables - Setup data source variables from INI-file
        The  function  tries  to  initialize  the  data source parameters from a
        section  defined in the  ini-file. If no  such section is defined or the
        section  refers to a data source in  the catalogue the function tries to
        setup the variables from the corresponding catalogue entry.

\return term - Termination code

\param  datasource_name - Name of the data source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupVariables"

logical DataSourceHandle :: SetupVariables (char *datasource_name )
{
  logical                 term = NO;
BEGINSEQ
  SetVariables(datasource_name);
  
  if ( !*dict_path && !*data_source )
    gvtxbts(data_source,datasource_name,ID_SIZE);
  
  if ( *data_source > ' ' && SystemServices() ) // get data source definition from catalogue
    if ( SystemServices()->SetupDataSource(this) )   ERROR

  if ( !*dict_path )                                 ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  get_dictionary - 


\return Dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_dictionary"

DictionaryHandle &DataSourceHandle :: get_dictionary ( )
{

  return(dictionary);

}

/******************************************************************************/
/**
\brief  get_object_handle - 


\return objhdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_object_handle"

DBObjectHandle &DataSourceHandle :: get_object_handle ( )
{

  return(object_handle);

}

/******************************************************************************/
/**
\brief  get_res_handle - 


\return db_handle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_res_handle"

DatabaseHandle &DataSourceHandle :: get_res_handle ( )
{

  return(reshandle);

}

/******************************************************************************/
/**
\brief  operator= - 


\return datasource_ref - 

\param  datasource_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DataSourceHandle &DataSourceHandle :: operator= (DataSourceHandle &datasource_ref )
{

  Close();
  Initialize();
  
  strcpy(server_name,datasource_ref.server_name);
  server_port = datasource_ref.server_port;
  Connect(datasource_ref.GetClient());
  
  SetDataSource(&datasource_ref);

  return(*this);
}

/******************************************************************************/
/**
\brief  ~DataSourceHandle - Destructor
        Destructing  the  datasource  will  close  all  handles that are not yet
        closed.  When a  data source  transaction is  still running this will be
        comitted before destroying the data source. 
        When working with recovery file thsi is closed as well.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DataSourceHandle"

     DataSourceHandle :: ~DataSourceHandle ( )
{

  if ( transaction )
    CommitTransaction();

  Close();

}


