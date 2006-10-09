/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ServerConnection

\brief    


\date     $Date: 2006/07/24 14:31:13,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ServerConnection"

#include  <popa7.h>
#include  <csfctp.h>
#include  <iopai.h>
#include  <sofifct.h>
#include  <sCSInstanceList.hpp>
#include  <sCS_Handle.hpp>
#include  <sCS_Message.hpp>
#include  <sCServer.hpp>
#include  <sDBHandle.hpp>
#include  <sIFClass.hpp>
#include  <sIFFunction.hpp>
#include  <sLDBHandle.hpp>
#include  <sSC_Connection.hpp>
#include  <sSC_Database.hpp>
#include  <sSC_Dictionary.hpp>
#include  <sSC_Handle.hpp>
#include  <sServerConnection.hpp>


/******************************************************************************/
/**
\brief  BackupDB - 



\return term - Termination code

\param  cpath - Complete path
\param  target - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical ServerConnection :: BackupDB (char *cpath, char *target, int32 wait_sec )
{
  logical                 term = NO;
BEGINSEQ
  if ( StartPause(wait_sec) )                        ERROR
  
  term = sc_connection->BackupDB(cpath,target);
  
  StopPause();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CacheConnection - 



\return term - Termination code

\param  connection_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheConnection"

logical ServerConnection :: CacheConnection (char *connection_string )
{
  logical                 term = NO;
BEGINSEQ
  if ( sc_connection )                               SDBERR(99)

  if ( !connection_string || !*connection_string ) // not cached
    sc_connection = new SC_Connection(this);
  else
  {
    if ( !(sc_connection = odaba_server->ProvideConnection(this,connection_string)) )
                                                     SDBERR(99)
    if ( sc_connection->get_sub_handles() )
    {
      delete sub_handles;
      Reparent(sc_connection);
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDB - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  sc_database - 
\param  check_opts - 
\param  source - 
\param  result - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical ServerConnection :: CheckDB (SC_Database *sc_database, CheckOptions check_opts, char *source, CSInstanceList *result, int32 wait_sec )
{
  DictionaryHandle        dict;
  char                    cpath[513];
  logical                 term = NO;
  strncpy(cpath,sc_database->DatabaseHandle::GetPath(),sizeof(cpath)-1);
  dict = sc_database->DatabaseHandle::GetDictionary();
  sc_database->SetDBOHdl(NULL);
  sc_database->DatabaseHdl::Close();
  
  term = CheckDB(dict,cpath,check_opts,source,result,wait_sec);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  dict_hdl - Dictionary handle
\param  cpath - Complete path
\param  check_opts - 
\param  source - 
\param  result - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical ServerConnection :: CheckDB (DictionaryHandle &dict_hdl, char *cpath, CheckOptions check_opts, char *source, CSInstanceList *result, int32 wait_sec )
{
  NString                 nstring;
  logical                 term = NO;
BEGINSEQ
  if ( odaba_server->StopDBClients(current_index,cpath,nstring,wait_sec) )
  {
    result->Fill(nstring);                           ERROR
  }
  
  term = sc_connection->CheckDB(dict_hdl,cpath,check_opts,source,nstring);
  result->Fill((char *)nstring);
  
  odaba_server->StartDBClients();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dict_path - 
\param  cpath - Complete path
\param  check_opts - 
\param  source - 
\param  result - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical ServerConnection :: CheckDB (char *dict_path, char *cpath, CheckOptions check_opts, char *source, CSInstanceList *result, int32 wait_sec )
{
  ODABAClient             client;
  DictionaryHandle        dict_hdl;
  logical                 term = NO;
BEGINSEQ
  if ( dict_hdl.Open(client,dict_path,PI_Read,YES) )     ERROR

  term = CheckDB(dict_hdl,cpath,check_opts,source,result,wait_sec);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 



\return term - Termination code

\param  dwServiceClass - 
\param  dwServiceFunc - 
\param  cpParams - 
\param  cpResult - 
\param  errptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ServerConnection :: Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *cpParams, CS_Message *cpResult, logical *errptr )
{
  logical                 term = NO;
BEGINSEQ
  rec_parms.Setup(cpParams);
  send_result.Reset();
  
  if ( errptr )
    *errptr = NO;
    
  if ( error_check )                                 ERROR
  
  switch ( dwServiceClass )
  {
    case UNDEF     : break;  // system call
    case CSA_EVENT : GenerateEvent(dwServiceFunc,
                                   cpParams->GetHandle()->GetClientPointer(),
                                   &rec_parms);
                     break;
    default        : if ( shutting_down )
                       term = YES;
                     else
                     {
                       SetActiveHandle(cpParams->GetHandle()->GetClientObject());
                       if ( !(term = function_table[dwServiceClass].
                             Execute(dwServiceClass,dwServiceFunc,this,
                                     cpParams->GetHandle()->GetServerPointer(),
                                     &rec_parms,&send_result)) )
                         cpResult->Copy(send_result.GetCSMessage());
                       SetActiveHandle(NULL);
                     }
                     if ( errptr )
                     {
                       *errptr = term;
                       if ( !*errptr && SDBERROR )
                         *errptr = YES;
                     }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillDSResult - 



\return term - Termination code

\param  result - 
\param  data_source_name - Data source name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDSResult"

logical ServerConnection :: FillDSResult (CSInstanceList *result, char *data_source_name )
{
  Services          *services = SystemServices();
  logical            conversion = result->get_conversion();
  DataSourceHandle   ds_handle;
  logical     term = NO;
BEGINSEQ
  result->Reset();
  
  strcpy(ds_handle.data_source,data_source_name);
  if ( services->SetupDataSource(&ds_handle) )
  {
    result->get_inst_area().Fill((logical)YES,conversion,YES);
                                                     // 0 - term
    LEAVESEQ
  }
  result->get_inst_area().Fill((logical)NO,conversion,YES);
                                                     // 0 - term
  result->get_inst_area().Fill(ds_handle.server_name,conversion,YES);
                                                     // 1 - server name
  result->get_inst_area().Fill(ds_handle.server_port,conversion,YES);
                                                     // 2 - server port
  result->get_inst_area().Fill(ds_handle.dict_path,conversion,YES);
                                                     // 3 - dictionary path
  result->get_inst_area().Fill(ds_handle.db_path,conversion,YES);
                                                     // 4 - database path
  result->get_inst_area().Fill(ds_handle.object_name,conversion,YES);
                                                     // 5 - object name
  result->get_inst_area().Fill(ds_handle.extent_name,conversion,YES);
                                                     // 6 - extent name
  result->get_inst_area().Fill((uint8)ds_handle.sys_appl,conversion,YES);
                                                     // 7 - no context
  result->get_inst_area().Fill(ds_handle.netopt,conversion,YES);
                                                     // 8 - multi user environment
  result->get_inst_area().Fill(ds_handle.version,conversion,YES);
                                                     // 9 - version
  result->get_inst_area().Fill(ds_handle.schema_version,conversion,YES);
                                                     // 9 - schema version
  result->get_inst_area().Fill(ds_handle.online_version,conversion,YES);
                                                     // 10 - online version
  result->get_inst_area().Fill((int32)ds_handle.accmode,conversion,YES);
                                                     // 11 - access mode
  result->Terminate();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FireEvent - 



\return term - Termination code

\param  sc_handle - 
\param  event_id - Ivend type
\param  parmstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FireEvent"

logical ServerConnection :: FireEvent (SC_Handle *sc_handle, CSA_Events event_id, char *parmstring )
{
  int64                   client_handle;
  logical                 term = NO;
BEGINSEQ
  if ( !threadExec )                                 LEAVESEQ
  
  if ( (client_handle = sc_handle->GetClientObject()) && client_handle != GetActiveHandle() )
  {
    if ( parmstring )
      send_parms.Fill(parmstring);
  
    SendCSMessage(sc_handle,CSA_EVENT,event_id);
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ForceClose - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void ServerConnection :: ForceClose ( )
{

  closing = YES;  // 27.10.2004
  
  MSG_Closed();
  Flush();
    
  if ( sc_connection )
    sc_connection->ForceClose();
  
  Flush();


}

/******************************************************************************/
/**
\brief  GenerateEvent - 



\return term - Termination code

\param  dwServiceFunc - 
\param  cso_ptr - 
\param  csparms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical ServerConnection :: GenerateEvent (uint32 dwServiceFunc, void *cso_ptr, CSInstanceList *csparms )
{
  char                   *parmstring = NULL;
  logical                 term = NO;
  if ( csparms->GetCount() ) 
  {
    parmstring=(*csparms)[0].GetString();
  }
  term = ((CSA_Handle *)cso_ptr)->ExecuteEvent(dwServiceFunc,parmstring);
  return(term);
}

/******************************************************************************/
/**
\brief  GetName - 



\return resource_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *ServerConnection :: GetName ( )
{

  return( client_name );

}

/******************************************************************************/
/**
\brief  GetTypeName - 



\return resource_type - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *ServerConnection :: GetTypeName ( )
{

  return ( "ODABAClient" );

}

/******************************************************************************/
/**
\brief  IsCached - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCached"

logical ServerConnection :: IsCached ( )
{

  return(this ? sc_connection->IsCached() : NO);

}

/******************************************************************************/
/**
\brief  IsUsingDB - 



\return sc_handle - 

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUsingDB"

SC_Handle *ServerConnection :: IsUsingDB (char *cpath )
{

  return( sc_connection->IsUsingDB(cpath,AUTO) );

}

/******************************************************************************/
/**
\brief  KillClient - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KillClient"

logical ServerConnection :: KillClient ( )
{
  logical                 term = NO;
  error_check = YES;
  CS_ServerClient::KillClient();


  return(term);
}

/******************************************************************************/
/**
\brief  ProvideDict - 



\return sc_dictionary - 

\param  client_handle - 
\param  cpath - Complete path
\param  version - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDict"

SC_Dictionary *ServerConnection :: ProvideDict (int64 client_handle, char *cpath, uint16 version, PIACC accopt )
{

  return( sc_connection->ProvideDict(client_handle,cpath,
                                     version,accopt) );

}

/******************************************************************************/
/**
\brief  ReleaseConnection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseConnection"

void ServerConnection :: ReleaseConnection ( )
{

  if ( this )
    sc_connection = NULL;

}

/******************************************************************************/
/**
\brief  ReleaseDict - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDict"

logical ServerConnection :: ReleaseDict (CS_Handle *handle )
{

  return( sc_connection->ReleaseDict(handle) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dict_client - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDict"

logical ServerConnection :: ReleaseDict (SC_Dictionary *dict_client )
{

  return( odaba_server->ReleaseDict(dict_client) );

}

/******************************************************************************/
/**
\brief  RestoreDB - 



\return term - Termination code

\param  cpath - Complete path
\param  source - 
\param  nresult - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical ServerConnection :: RestoreDB (char *cpath, char *source, NString &nresult, int32 wait_sec )
{
  logical                 term = NO;
BEGINSEQ
  if ( odaba_server->StopDBClients(current_index,cpath,nresult,wait_sec) )
                                                     ERROR
  term = sc_connection->RestoreDB(cpath,source);
  
  odaba_server->StartDBClients();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SendCSMessage - 



\return term - Termination code

\param  handle - 
\param  dwServiceClass - 
\param  dwServiceFunc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendCSMessage"

logical ServerConnection :: SendCSMessage (CS_Handle *handle, uint32 dwServiceClass, uint32 dwServiceFunc )
{
  logical            term;
  SDBRESET
  
  send_parms.SetHandle(handle);
  CS_ServerClient::SendCSMessage(dwServiceClass,dwServiceFunc,
                                 send_parms.GetCSMessage(),NULL);
  return(term);
}

/******************************************************************************/
/**
\brief  SendClientMessage - 



\return term - Termination code

\param  mtext - 
\param  mtitle - 
\param  mtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendClientMessage"

logical ServerConnection :: SendClientMessage (char *mtext, char *mtitle, uint8 mtype )
{
  uint32                  type;
  logical                 term = NO;
BEGINSEQ
  send_parms.Fill(mtext,mtitle,mtype);
//  send_parms.GetCSMessage()->Flush(); // immediate output
  
  switch ( mtype )
  {
    case 'I' : type = APL_MSG_INFO;              break;
    case 'W' : type = APL_MSG_WARNING;           break;
    case 'E' : type = APL_MSG_ERROR;             break;
    default  : type = APL_MSG_ERROR;
  }

  SendCSMessage(this,(int32)CSA_MESSAGE,type);
  Flush();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ServerConnection - 




\param  cserver - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ServerConnection"

     ServerConnection :: ServerConnection (CServer *cserver )
                     : SC_Handle(this,NULL,0),
CS_ServerClient (),
  function_table(NULL),
  send_parms(32,NO,1024),
  send_result(4,NO,128),
  rec_parms(32,NO,0),
  rec_result(4,NO,0),
  error_check(NO),
  odaba_server(cserver),
  sc_connection(NULL)
{
  ErrorHandle   *error_handle;
#include <_cs_tbl_OPA.hpp>

  function_table = ServerClasses;
  *client_name = 0;
  *user_name = 0;
  
  conversion   = YES;   // für test, später raus auch aus ClientConnection

  rec_parms.SetConversion(conversion);
  send_parms.SetConversion(conversion);
  rec_result.SetConversion(conversion);
  send_result.SetConversion(conversion);

  SystemServices()->RegisterThread();
    
  SetServerPointer(this);

}

/******************************************************************************/
/**
\brief  SetClientName - 



\return term - Termination code

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClientName"

logical ServerConnection :: SetClientName (char *string )
{

  strncpy(client_name,string,sizeof(client_name)-1);
  client_name[sizeof(client_name)-1] = 0;

  SDBError().DisplayMessage(-409,client_name);
  return(NO);
}

/******************************************************************************/
/**
\brief  ~ServerConnection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ServerConnection"

     ServerConnection :: ~ServerConnection ( )
{
  char       scalls[20];
  char       stime[20];
  gvtxltoa(all_calls,scalls,10);
  gvtxltoa(all_time/(perf_freq/1000),stime,10);
  SDBError().DisplayMessage(-412,GetName(),scalls,stime);
  
  delete sc_connection;
  sc_connection = NULL;


}


