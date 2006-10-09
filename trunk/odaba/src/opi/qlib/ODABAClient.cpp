/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    ODABAClient

\brief    ODABA client
          To  run  client  server  applications  you  must create a ODABA client
          instance.  To support several connections to different servers you can
          create one or more clients within your application.
          When  connecting to different  servers you must  create one client for
          each  server.  You  can  open  several  clients in an application. The
          first  client, however, is considered to  be the main client. The main
          client  should  be  the  last  client  closed in an application. After
          closing  the main client you can open another main client. Since there
          is no hierarchy defined between clients the system will not check 
          The  main  client  registers  the  process and activates the error log
          file.  It opens the  system database for  providing error messages and
          the  data  catalogue  if  one  has  been  specified  in  the  system 
          environment  (see  ODABAClient  constructor).  These  information  are
          described in an ini-file, which can be passed to the client.
          For  initializing and registring the  process properly a client should
          be created also for locally running applications.

\date     $Date: 2006/06/25 17:21:42,89 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODABAClient"

#include  <pdefault.h>
#include  <cclient.h>
#include  <sCClient.hpp>
#include  <sCheckOptions.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sError.hpp>
#include  <sODABAClient.hpp>
#include  <sObjectReferenceHandle.hpp>
#include  <sODABAClient.hpp>


/******************************************************************************/
/**
\brief  ActivateGUIMessages - Activate GUI-Messages
        For  console applications  messages will  be sent  to the console, only.
        When  messages should be displayed in GUI  message boxes as well you can
        use the Activate GUIMessages() function to enable this feature.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateGUIMessages"

void ODABAClient :: ActivateGUIMessages ( )
{
  CClient    *odaba_client = GetClientPtr();
  odaba_client->ActivateGUIError();

}

/******************************************************************************/
/**
\brief  BackupDB - 


\return cond - Return value

\param  cpath - Complete path
\param  target - 
\param  wait_sec - Number of seconds to wait
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical ODABAClient :: BackupDB (char *cpath, char *target, int32 wait_sec )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->BackupDB(cpath,target,wait_sec));


}

/******************************************************************************/
/**
\brief  CheckDB - 


\return cond - Return value

\param  dict_path - 
\param  cpath - Complete path
\param  check_opts - 
\param  source - 
\param  wait_sec - Number of seconds to wait
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical ODABAClient :: CheckDB (char *dict_path, char *cpath, CheckOptions check_opts, char *source, int32 wait_sec )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->CheckDB(dict_path,cpath,check_opts,source,wait_sec));

}

/******************************************************************************/
/**
\brief  Close - Close the client
        The  function closes  the client.  This implies disconnecting the client
        when still being connected.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ODABAClient :: Close ( )
{

  return(ObjectReferenceHandle::Close());

}

/******************************************************************************/
/**
\brief  CloseDataSource - Close data source
        The  function  closes  the  database  object  handle  opened  for a data
        source.  You can  only close  an object  handle with this function, that
        has  been opened with OpenDataSource(). Otherwise the function may cause
        unpredictable reactions.

\return term - Termination code

\param  dbo_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDataSource"

logical ODABAClient :: CloseDataSource (DBObjectHandle &dbo_handle )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Connect - Connect to server
        This  function  establishs  a  connection  to  the  server.  When  not 
        connecting  the cleint to  a server the  client runs in local mode. When
        running in local mode all resources are located on th client machine. 
        When  being connected to  a server you  can access ressources located on
        the    server    or    on    the    local    machine    by   setting the
        "local_resources"-parameter  when  constructing  dictionary  or database
        handles.
        When  connecting  several  times  for  closing  the  connection you must
        disconnect  as  often  as  you  have  connected  to the server. When the
        client  is connected once it cannot be connected to another server until
        the open connection is closed.

\return term - Termination code

\param  server_name - Server name
\param  host_port - Port number
\param  cache_string - Unique connection name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical ODABAClient :: Connect (char * server_name, uint32 host_port, char *cache_string )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->Connect(server_name,host_port,cache_string));

}

/******************************************************************************/
/**
\brief  DictDisplay - 


\return term - Termination code

\param  dbpath - Complete database path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictDisplay"

logical ODABAClient :: DictDisplay (char *dbpath, char *ppath )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->DictDisplay(dbpath,ppath));



}

/******************************************************************************/
/**
\brief  Disconnect - Disconnect from server
        Please  make  shure  that  all resources are closed before disconnecting
        the  client. Disconnecting the client  before closing all opened handles
        may cause problems and not all changes are stored.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void ODABAClient :: Disconnect ( )
{
  CClient    *odaba_client = GetClientPtr();
  odaba_client->Disconnect();

}

/******************************************************************************/
/**
\brief  Exist - 


\return cond - Return value

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical ODABAClient :: Exist (char *cpath )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->Exist(cpath));


}

/******************************************************************************/
/**
\brief  GetClientPtr - 


\return cclient - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientPtr"

CClient *ODABAClient :: GetClientPtr ( ) const
{

  return(object_handle ? (CClient *)object_handle : NULL);

}

/******************************************************************************/
/**
\brief  GetConnectionID - ID for a client server connection
        When  running in client  server mode, The  function returns the ID for a
        client  server connection or 0, when  no connection is established. When
        running in local mode, the function returns 1 always.

\return connect_id - Server connection identifier

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionID"

int32 ODABAClient :: GetConnectionID ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  GetDBError - Get last database error
        The  function returns the last database error including error number and
        description. For more details see Error class definition.

\return dberror - Database error

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBError"

Error *ODABAClient :: GetDBError ( )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->GetDBError());

}

/******************************************************************************/
/**
\brief  GetDataSource - Get data source name
        The  function  returns  the  data  source  name  on  position indx0. The
        function  returns a  value, only,  if the  application is working with a
        data  catalogue, i.e.  the ini-file  must contain a valid DATA-CATALOGUE
        section.

\return data_source_name - Data source name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataSource"

char *ODABAClient :: GetDataSource (int32 indx0 )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->GetDataSource(indx0));

}

/******************************************************************************/
/**
\brief  GetHost - 


\return host_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHost"

char *ODABAClient :: GetHost ( )
{
  CClient    *odaba_client = GetClientPtr();
  return ( odaba_client
           ? odaba_client->GetHost()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetPort - 


\return port_number - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPort"

uint32 ODABAClient :: GetPort ( )
{
  CClient    *odaba_client = GetClientPtr();
  return ( odaba_client
           ? odaba_client->GetPort()
           : UNDEF );

}

/******************************************************************************/
/**
\brief  GetServerVariable - 


\return var_string - Value for the system variable

\param  var_name - System variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerVariable"

char *ODABAClient :: GetServerVariable (char *var_name )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->GetServerVariable(var_name));


}

/******************************************************************************/
/**
\brief  Initialize - Initialize client
        The  initialize function can be used to initialize an ODABA client after
        construction.  Initialize  will  setup  the  main  client  when  not yet
        active.  This includes initializing the main client including the system
        services  fron  the  SYSTEM  section  in  the  ini  file  passed  to the
        function. 
        Initialize  can be called  any number of  times, but it should be called
        before  connectin  to  a  database  or  after  disconnecting  and  befor
        conecting again. Initialize does not disconnect automatically. 
        When  the ini-file changes the system section, initialize must be called
        for the main client as
        ODABAClient()->Initialize(...)
        In  this case,  the main  client will  be disconnected and reconnected o
        the  server in order  to re-establish the  system connection. When using
        the   system   connection   provided   by   the   main  client for  data
        communication,  all  dictionaries  and  databases  must be closed before
        calling  initialize.  Otherwise,  data  communication  will  fail  after
        initialize.


\param  inipath - 
\param  application_name - Allication name
\param  progpath - Programme path
\param  application_type - Run as console application
\param  init_services - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ODABAClient :: Initialize (char *inipath, char *application_name, char *progpath, ApplicationTypes application_type, logical init_services )
{
  CClient    *odaba_client = GetClientPtr();
  odaba_client->Initialize(inipath,application_name,progpath,application_type,init_services);

}

/******************************************************************************/
/**
\brief  IsConnected - Is client connected
        The  function checks whether the client  is connected or not. When being
        connected the function returns YES, NO otherwise.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConnected"

logical ODABAClient :: IsConnected ( )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->IsConnected());



}

/******************************************************************************/
/**
\brief  KillClient - Kill client on the server
        The  function  allows  killing  one  or  all clients on the server. When
        killing all clients the client sending the command is not killed.
        Befor killing the client(s) the system is waiting wait_sec seconds.

\return term - Termination code

\param  client_id - Client the message is send to
\param  wait_sec - Number of seconds to wait
\param  send_message - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KillClient"

logical ODABAClient :: KillClient (int32 client_id, int32 wait_sec, logical send_message )
{
  CClient    *odaba_client = GetClientPtr();
  logical     term = NO;
BEGINSEQ
  if ( !odaba_client )                               ERROR
  odaba_client->KillClient(client_id,wait_sec,send_message);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ODABAClient - Constructor
        To  run an application in client/server mode at least one client must be
        constructed  for an  application. The  first client  created is the main
        client  that should be created at  the very beginning of the application
        and that should be closed at the very end of the application. 
        In  addition  a  number  of  other  clients can be created to connect to
        different  servers in  one application.  When creating  a main client an
        ini  file can be provided to the  constructor. This ini file defines the
        application section. 
        System  and catalogue sections are read from the ODABA2.INI file that is
        stored  in  the  ODABA2  installation  path. It is, however, possible to
        provide  separate system  and catalogue  definitions for the client with
        the  passed  INI-file.  In  this  case  the passed INI-file must contain
        either  the  system  and  catalogue  sections  or  it  must  refer to an
        INI-file  that  contains  these  sections  by  defining the path for the
        system INI-file in the variable SYSTEM_ENVIRONMENT.
        The  INI-file passed to the client must  contain a section with the name
        of  the  application  or  (when  no  application name has been passed) a
        section with the name "APPLICATION_DATA".

-------------------------------------------------------------------------------
\brief  i00 - 


\param  inipath - 
\param  application_name - Allication name
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABAClient"

     ODABAClient :: ODABAClient (char *inipath, char *application_name, char *progpath, ApplicationTypes application_type )
                     : ObjectReferenceHandle()
{

  Open(inipath,application_name,progpath,application_type);

}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABAClient"

     ODABAClient :: ODABAClient ( )
                     : ObjectReferenceHandle()
{
  CClient  *client = GetMainClient().GetClientPtr();
  if ( !client )
  {
    client = new CClient();  // setzt c_client 
    object_handle = client;   
    object_handle->Connect(this);   
  }
  else
    Open(client);


}

/******************************************************************************/
/**
\brief  i02 - 


\param  client_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABAClient"

     ODABAClient :: ODABAClient (const ODABAClient &client_refc )
                     : ObjectReferenceHandle()
{

  Open(client_refc);

}

/******************************************************************************/
/**
\brief  i03 - 


\param  cclient_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABAClient"

     ODABAClient :: ODABAClient (CClient *cclient_ptr )
                     : ObjectReferenceHandle()
{

  Open(cclient_ptr);

}

/******************************************************************************/
/**
\brief  Open - Open ODABA client
        The  function opens an ODABA client. The  first client that is opened is
        considered to be the main client.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  inipath - 
\param  application_name - Allication name
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ODABAClient :: Open (char *inipath, char *application_name, char *progpath, ApplicationTypes application_type )
{
  logical       term = NO;
BEGINSEQ
  Close();
  
  if ( !(object_handle = new CClient(inipath,application_name,progpath,application_type)) )
                                                     SDBERR(95)
                                                     SDBCERR
  object_handle->Connect(this);

RECOVER
  Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  client_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ODABAClient :: Open (const ODABAClient &client_refc )
{

  return( Open(client_refc.GetClientPtr()) );
  return(NO);
}

/******************************************************************************/
/**
\brief  i03 - 


\param  cclient_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ODABAClient :: Open (CClient *cclient_ptr )
{

  return ( ObjectReferenceHandle::Open(cclient_ptr) );

}

/******************************************************************************/
/**
\brief  OpenDataSource - Open data source
        The  data source  to be  opened must  be defined in the ini-file for the
        application  or  in  the  data  catalogue. When the data source has been
        opened  successfully the function returns a pointer to a database object
        handle.  The application  is responsible  to destroy the database object
        handle,   when   it   is   not   being   used   anymore   by calling the
        CloseDataSource() function.
        The  access  mode  (accopt)  can  be  passed to reduce the access rights
        defined  in the data  source (typically from  write to read). You cannot
        increase the access rights (e.g. from read to write).

\return dbo_handle - 

\param  datasource_name - Name of the data source
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDataSource"

DBObjectHandle *ODABAClient :: OpenDataSource (char *datasource_name, PIACC accopt )
{
  DBObjectHandle        *dbo_handle = NULL;

  return(dbo_handle);
}

/******************************************************************************/
/**
\brief  PackDatabase - Pack database
        The  function  packs  a  database.  The  function  packs the database by
        copying  it to a  new file. If  there is not  enough space on the disk a
        path  refering  to  temporary  directory  must  be passed to the packing
        function. Otherwise the database is packed in the same folder.
        When  the  database  consists  of  several main or sub-bases each one is
        copied in its own location or to the temporary folder.

\return term - Termination code

\param  cpath - Complete path
\param  temp_path - Temporary path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PackDatabase"

logical ODABAClient :: PackDatabase (char *cpath, char *temp_path )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->PackDatabase(cpath,temp_path));

}

/******************************************************************************/
/**
\brief  RestoreDB - 


\return cond - Return value

\param  cpath - Complete path
\param  source - 
\param  wait_sec - Number of seconds to wait
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical ODABAClient :: RestoreDB (char *cpath, char *source, int32 wait_sec )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->RestoreDB(cpath,source,wait_sec));


}

/******************************************************************************/
/**
\brief  SayHello - 


\return var_string - Value for the system variable

\param  testdata - 
\param  size - Size
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SayHello"

char *ODABAClient :: SayHello (void *testdata, uint32 size )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->SayHello(testdata,size));


}

/******************************************************************************/
/**
\brief  SendClientMessage - Send message to one or all clients
        The  function sends  a message  to one  or all clients. Depending on the
        client   type   the   message   is   displayed   on the console (console
        applications) or as message box. 
        The  message  is  sent  to  the client adressed via the client_id. If no
        client_id  is passed (UNDEF)  the message is  send to all clients except
        the sending one.

\return term - Termination code

\param  client_id - Client the message is send to
\param  mtext - Message text
\param  mtitle - Message title
\param  mtype - Message Type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendClientMessage"

logical ODABAClient :: SendClientMessage (int32 client_id, char *mtext, char *mtitle, char mtype )
{
  CClient    *odaba_client = GetClientPtr();
  logical     term = NO;
BEGINSEQ
  if ( !odaba_client )                               ERROR
  odaba_client->SendClientMessage(client_id,mtext,mtitle,mtype);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetServerVariable - Set system variable on server side
        Systemvariables  can  be  set  for  the  server.  This  is necessary for
        controlling functions running on the server side.
        Server variables are valid on the server only for the connected client.

\return term - Termination code

\param  var_name - System variable name
\param  var_string - Value for the system variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServerVariable"

logical ODABAClient :: SetServerVariable (char *var_name, char *var_string )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->SetServerVariable(var_name,var_string));

}

/******************************************************************************/
/**
\brief  ShutDown - Shut down client
        Usually  the last ODABAClient  handle referring to  the client will shut
        down  the  client  when  being  destructed.  In  some  cases,  e.g. when
        creating  a client  with an  ini-file and  using system services as data
        catalogue  or error  logs, some  system references  are still active and
        referring  to the main client. To be sure that the main client is closed
        properly  you should use the  ShutDown() function before destructing the
        client.  Make sure that  there are no  other references to the client in
        your application anymore. 
        The  function will delete  all resources associated  with the client and
        close  the client. When the client is  the default or main client, which
        has  been  created  automatically,  the  function  will  close  the main
        client.

\return term - Termination code

\param  close_system - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShutDown"

logical ODABAClient :: ShutDown (char close_system )
{
  CClient    *odaba_client = GetClientPtr();
  logical     term = NO;
  if ( odaba_client )
    term = odaba_client->ShutDown(close_system);
  Close();
  return(term);
}

/******************************************************************************/
/**
\brief  StartPause - Pause Server
        When  pausing  the  server  no  more transactions can be committed until
        pausing  the server is stopped (Stop-Pause()). The server can pause only
        after  finishing all running transaction commits. If any commit is still
        run-ning  after five  minutes or  a given  number seconds (wait_sec) the
        server  will  not  pause  (error  323). When the server cannot pause the
        function stops without pausing the server. 
        The  …Pause  functions  can  be  used  for  keeping  the  database  in a
        consistent  state  while  backing  up  the  database without closing the
        server.   Pause   commands   should   not   be   used  when running long
        transactions as large imports or database reorganizations. 
        Transactions  will  not  be  committed anymore after pausing the server.
        The  timeout  interval  for  committing transactions is 10 minutes. When
        not  being able to  start committing the  transaction within the timeout
        interval the transaction is cancelled.  
        Any  application may access  the database in  the pause state as long as
        not  writing to the  database, i.e. as  long as not storing transactions
        to the database. 
        For  allowing  storing  data  to  the  database  again  you must use the
        StopPause() function.

\return term - Termination code

\param  wait_sec - Number of seconds to wait
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartPause"

logical ODABAClient :: StartPause (int32 wait_sec )
{
  CClient    *odaba_client = GetClientPtr();
  logical     term = NO;
  term = odaba_client->StartPause(wait_sec);

  return(term);
}

/******************************************************************************/
/**
\brief  StatDisplay - 


\return term - Termination code

\param  dbpath - Complete database path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StatDisplay"

logical ODABAClient :: StatDisplay (char *dbpath, char *ppath )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->StatDisplay(dbpath,ppath));



}

/******************************************************************************/
/**
\brief  StopPause - Stop pausing server
        This  command  stops  pausing  the  server and allows committing further
        transactions.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopPause"

void ODABAClient :: StopPause ( )
{
  CClient    *odaba_client = GetClientPtr();
  logical     term = NO;
  odaba_client->StopPause();


}

/******************************************************************************/
/**
\brief  SysInfoDisplay - Display system information
        The  function  creates  system  information  for  the database passed in
        dbpath. The database must be available via a local or a net drive.

\return term - Termination code

\param  dbpath - Complete database path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SysInfoDisplay"

logical ODABAClient :: SysInfoDisplay (char *dbpath, char *ppath )
{
  CClient    *odaba_client = GetClientPtr();
  return(odaba_client->SysInfoDisplay(dbpath,ppath));

}

/******************************************************************************/
/**
\brief  operator bool - Compare clients
        The  function compares two ODABA clients and returns true (YES) when the
        clients  are the same. Clients are the same when they have been assigned
        using  the  =operator.  Clients  are  not  the  seme when the are opened
        separately.

\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator bool"

NOTYPE ODABAClient :: operator bool ( )
{

  return ( object_handle ? YES : NO );

}

/******************************************************************************/
/**
\brief  operator= - Assign ODABA client handle
        The  function assigns the odaba client  to another client handle. When a
        client  has been created for the source  the client is referenced in the
        target  handle as well.  Whne no client  is opened for the source handle
        the target client gandle will be empty as well.

\return client_ref - 

\param  client_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

ODABAClient &ODABAClient :: operator= (ODABAClient &client_ref )
{

  *(ObjectReferenceHandle *)this = *(ObjectReferenceHandle *)&client_ref;

  return(*this);
}

/******************************************************************************/
/**
\brief  ~ODABAClient - Destructor
        When  destructing  the  client  the  client disconnects from the server.
        When  disconnecting  the  main  client  (the  first client that has been
        opened  in  the  application)  ´services  as  error  messages  and  data
        catalogue  are  disabled  (until  another  client  is constructed, which
        becomes the main client again).


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODABAClient"

     ODABAClient :: ~ODABAClient ( )
{

  Close();

}


