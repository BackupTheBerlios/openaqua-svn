/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CClient

\brief    


\date     $Date: 2006/07/24 14:31:32,46 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CClient"

#include  <popa7.h>
#include  <coclient.h>
#include  <sofifct.h>
#include  <versions.h>
#include  <sCSA_Handle.hpp>
#include  <sCS_Client.hpp>
#include  <sCS_Handle.hpp>
#include  <sCS_ServerClient.hpp>
#include  <sDBErrorHandle.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDLL_Handle.hpp>
#include  <sError.hpp>
#include  <sHandleInfo.hpp>
#include  <sInstance.hpp>
#include  <sLDBHandle.hpp>
#include  <sLDictionary.hpp>
#include  <sProcessInfo.hpp>
#include  <sReferenceObject.hpp>
#include  <sSC_Handle.hpp>
#include  <sServerConnection.hpp>
#include  <sServices.hpp>
#include  <sThreadEntry.hpp>
#include  <sThreadList.hpp>
#include  <seb_RootBase.hpp>
#include  <snode.hpp>
#include  <ssvel.hpp>
#include  <sCClient.hpp>


/******************************************************************************/
/**
\brief  ActivateGUIError - Activate GUI Error messaging




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateGUIError"

void CClient :: ActivateGUIError ( )
{

  services->get_error_handle()->ActivateGUIMessages();


}

/******************************************************************************/
/**
\brief  BackupDB - 



\return cond - 

\param  cpath - Complete path
\param  target - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical CClient :: BackupDB (char *cpath, char *target, int32 wait_sec )
{
  logical     term = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    term = FileCopy(target,cpath,YES);
  else
  {
    LockSend();
    send_parms.Fill(cpath,wait_sec,target);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_BackupDB_ci) )
      term = (*rec_result)[0].GetUChar();
    UnlockSend();
  }
  return(term);
  
#else             // server version
  
  term = ((ServerConnection *)connection)->BackupDB(
                  (*parms)[0].GetString(),               // cpath
                  (*parms)[2].GetString(),               // target
                  (*parms)[1].GetLong(connection->get_conversion())); // wait_sec
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CClient - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  inipath - 
\param  application_name - 
\param  progpath - 
\param  application_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CClient"

     CClient :: CClient (char *inipath, char *application_name, char *progpath, ApplicationTypes application_type )
                     : ClientConnection (),
ObjectReference (NO),
  services(NULL),
  appl_type(application_type)
{

  if ( !c_client )   // main client object
    Initialize(inipath,application_name,progpath,application_type);
  else
    services = GetMainClient().GetClientPtr()->get_services();
    
  services->RegisterThread();
  
  InitHandle(NO);
  
  SDBRESET


}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CClient"

     CClient :: CClient ( )
                     : ClientConnection (),
ObjectReference (NO),
  services(NULL),
  appl_type(APT_Console)
{

  if ( !c_client )   // main client object
    Initialize(NULL,NULL,NULL,APT_Console);
  else
    services = GetMainClient().GetClientPtr()->get_services();

  services->RegisterThread();
  
  SDBRESET


}

/******************************************************************************/
/**
\brief  CSAClosed - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAClosed"

void CClient :: CSAClosed (char *string )
{

  connected = 0;
  shutting_down = YES;

}

/******************************************************************************/
/**
\brief  CacheConnection - 



\return term - Termination code

\param  cache_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheConnection"

logical CClient :: CacheConnection (char *cache_string )
{

#ifndef IF_Class  // client version

  if ( !cache_string )
    cache_string = ""; 
  
  if ( !is_local ) 
  {
    LockSend();
    send_parms.Fill(cache_string);
    SendCSMessage(NULL,S_CClient,SF_CClient_CacheConnection_ci);
    UnlockSend();
  }
  return(NO);
  
#else             // server version
  
  ((ServerConnection *)connection)->CacheConnection((*parms)[0].GetString());
  result->Fill((logical)NO);
  return(NO);
  
#endif

}

/******************************************************************************/
/**
\brief  CheckDB - 



\return cond - 

\param  dict_path - 
\param  cpath - Complete path
\param  check_opts - 
\param  source - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical CClient :: CheckDB (char *dict_path, char *cpath, CheckOptions check_opts, char *source, int32 wait_sec )
{
  logical     term = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    ; // term = Copy(target,cpath,YES);
  else
  {
    LockSend();
    send_parms.Fill(dict_path,cpath,source,*(short *)&check_opts,wait_sec);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_CheckDB_ci) )
      printf(Get_rec_result()[0].GetString());
    UnlockSend();
  }
  return(term);
  
#else             // server version
  
  short check_opts = (*parms)[3].GetShort(connection->get_conversion());
  term = ((ServerConnection *)connection)->CheckDB(
                  (*parms)[0].GetString(),               // dict path
                  (*parms)[1].GetString(),               // cpath
                  *(CheckOptions*)&check_opts,
                  (*parms)[2].GetString(),               // source
                  result,
                  (*parms)[4].GetLong(connection->get_conversion()) ); // wait_sec

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Connect - 



\return term - Termination code

\param  server_name - 
\param  host_port - 
\param  cache_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical CClient :: Connect (char *server_name, uint32 host_port, char *cache_string )
{
  char       *string;
  int         soserr = 0;
  logical     term = NO;
BEGINSEQ
  conversion   = YES;   // für test, später raus auch aus ClientConnection
  
  if ( !cache_string || !*cache_string )
    cache_string = GetSysVariable("CONNECTION_NAME");
  
  if ( !server_name || !*server_name )
  {
    svel svelinst(10);
    server_name = svelinst.svelget("ODABA_SERVER");
  }
  if ( !server_name || !*server_name )               ERROR
  
  if ( connected )
  {
    connected++;
    if ( strcmp(server_name,GetHost()) || host_port != GetPort() ) 
                                                     SDBERR(515)
    LEAVESEQ
  }
  if ( ConnectServer(server_name,host_port) ) 
  {
    soserr = SOSERROR;                               ERROR
  }
  connected = YES;  
  is_local = NO;
    
  csconnection = this; 
  if ( !(string = GetServerVersion()) || strcmp(ODABA2Version(),string) )
  {
    SDBEV1(ODABA2Version(),UNDEF)
    SDBEV2(string,UNDEF)
    SDBERR(506)
  }
  server_ptr_size = (int16)GetPointerSize(pointer_size);
  server_mtype    = GetMachineType(machine_type);
  if ( server_mtype != machine_type )
  {
    conversion = YES;
  }

  CacheConnection(cache_string);
  SetClientName();
  
  rec_parms.SetConversion(conversion);
  send_parms.SetConversion(conversion);
  rec_result->SetConversion(conversion);
  send_result.SetConversion(conversion);

RECOVER
  if ( connected > 0 && --connected == 0)
    DisconnectServer();
  if ( soserr )
    SDBSET(soserr+200);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DictDisplay - 



\return cond - 

\param  cpath - Complete path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictDisplay"

logical CClient :: DictDisplay (char *cpath, char *ppath )
{
  logical     cond = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    cond = LDictionary::DictDisplay(cpath,ppath);
  else
  {
    LockSend();
    send_parms.Fill(cpath,ppath);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_DictDisplay_ci) )
      cond = (*rec_result)[0].GetUChar();
    UnlockSend();
  }
  return(cond);
  
#else             // server version
  
  cond = LDictionary::DictDisplay((*parms)[0].GetString(),        // cpath
                                  (*parms)[1].GetString() );      // ppath
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Disconnect - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void CClient :: Disconnect ( )
{

  if ( connected > 0 && !--connected )
  {
    DisconnectServer();
    SetServerObject(0); 
  }

}

/******************************************************************************/
/**
\brief  Exist - 



\return cond - 

\param  cpath - Complete path
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical CClient :: Exist (char *cpath, char chkopt )
{
  
  logical     cond = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    cond = LDBHandle::Exist(cpath);
  else
  {
    LockSend();
    send_parms.Fill(cpath);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_Exist_ci) )
      cond = (*rec_result)[0].GetUChar();
    UnlockSend();
  }
  return(cond);
  
#else             // server version
  
  cond = LDBHandle::Exist((*parms)[0].GetString() );      // cpath
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  FillHandleInfo - 



\return term - Termination code

\param  hi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillHandleInfo"

logical CClient :: FillHandleInfo (HandleInfo &hi )
{
  char       *str;
  logical     term = NO;
BEGINSEQ
  if ( term = (*rec_result)[0].GetUChar() )           ERROR
  
  strcpy(hi.name,(str = (*rec_result)[1].GetString()) ? str : "__unknown__");
  strcpy(hi.type,(str = (*rec_result)[2].GetString()) ? str : "__unknown__");
  hi.calls          = (*rec_result)[3].GetLong(conversion);
  hi.calls_time     = (*rec_result)[4].GetLong(conversion);
  hi.all_calls      = (*rec_result)[5].GetLong(conversion);
  hi.all_calls_time = (*rec_result)[6].GetLong(conversion);
  hi.n_sub_handles  = (*rec_result)[7].GetLong(conversion);
  gvtxltp((char *)memcpy(hi.number,"ZZZZ9",5),(*rec_result)[8].GetLong(conversion),5);
  hi.is_active      = (*rec_result)[9].GetUChar();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClientHandle - 



\return cs_handle - 
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientHandle"

CS_Handle *CClient :: GetClientHandle (int32 indx0 )
{
  CS_Handle              *cs_handle = NULL;
#ifndef IF_Class  // client version

  if ( is_local )
    return(NULL);
  else
  {
    LockSend();
    send_parms.Fill(indx0);
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_GetClientHandle_ci0) )
      cs_handle = (*rec_result)[0].GetHandle();
    UnlockSend();
  }
  return(cs_handle && cs_handle->GetServerPointer() ? cs_handle : NULL);
  
#else             // server version

  cs_handle = ((ServerConnection *)connection)->get_odaba_server()->GetClientHandle((*parms)[0].GetLong(connection->get_conversion()));
  result->Fill(cs_handle);

  return(NO);

#endif


}

/******************************************************************************/
/**
\brief  ci1 - 



\param  ch - 
\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientHandle"

CS_Handle *CClient :: GetClientHandle (CS_Handle *ch, int32 indx0 )
{
  CS_Handle              *cs_handle = NULL;
#ifndef IF_Class  // client version

  if ( is_local )
    return(NULL);
  else
  {
    LockSend();
    send_parms.Fill(ch,indx0);
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_GetClientHandle_ci1) )
      cs_handle = (*rec_result)[0].GetHandle();
    UnlockSend();
  }
  return(cs_handle);
  
#else             // server version

  cs_handle = ((SC_Handle *)(*parms)[0].GetHandle()->GetServerPointer())->GetSubHandle((*parms)[1].GetLong(connection->get_conversion()));
  result->Fill(cs_handle);

  return(NO);

#endif

  return(cs_handle);
}

/******************************************************************************/
/**
\brief  GetDBError - 



\return dberror - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBError"

Error *CClient :: GetDBError ( )
{
  logical      term = NO;
BEGINSEQ
#ifndef IF_Class  // client version

  if ( !is_local ) 
  {
    LockSend();
    send_parms.Fill();
    if ( SendCSMessage(NULL,S_CClient,SF_CClient_GetDBError_ci) )
                                                     ERROR
    SDBError().Copy(*(Error *)(*rec_result)[0].GetBuffer());
    SDBIERR(conversion ? ntohl(SDBERROR) : SDBERROR);
    UnlockSend();
  }
  return ( &SDBError() );
                
#else             // server version
  
  result->Fill((void *)&SDBError(),sizeof(Error),SDBERROR);
  SDBRESET
  return(NO);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetDSResult - 



\return term - Termination code

\param  ds_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDSResult"

logical CClient :: GetDSResult (DataSourceHandle *ds_handle )
{
  Services          *services = SystemServices();
  logical            term = NO;
BEGINSEQ
  if ( term = (*rec_result)[0].GetUChar() )           ERROR
  
  strcpy(ds_handle->server_name,(*rec_result)[1].GetString());
  ds_handle->server_port   = (*rec_result)[2].GetLong(conversion);
  strcpy(ds_handle->dict_path,(*rec_result)[3].GetString());
  strcpy(ds_handle->db_path,(*rec_result)[4].GetString());
  strcpy(ds_handle->object_name,(*rec_result)[5].GetString());
  strcpy(ds_handle->extent_name,(*rec_result)[6].GetString());
  ds_handle->sys_appl       = (*rec_result)[7].GetUChar();
  ds_handle->netopt         = (*rec_result)[8].GetUChar();
  ds_handle->version        = (*rec_result)[9].GetUShort(conversion);
  ds_handle->schema_version = (*rec_result)[10].GetUShort(conversion);
  ds_handle->online_version = (*rec_result)[11].GetUChar();
  ds_handle->accmode        = (PIACC)(*rec_result)[12].GetLong(conversion);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDataSource - 



\return var_string - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataSource"

char *CClient :: GetDataSource (int32 indx0 )
{
  char    *ds_name = NULL;
#ifndef IF_Class  // client version

  if ( is_local )
    ds_name = SystemServices()->GetDataSource(indx0);
  else 
  {
    LockSend();
    send_parms.Fill(indx0);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_GetDataSource_ci) )
      ds_name = (*rec_result)[0].GetString();
    UnlockSend();
  }
  return(ds_name);
  
#else             // server version
  
  ds_name = SystemServices()->GetDataSource((*parms)[0].GetLong(connection->get_conversion()));
   
  result->Fill(ds_name);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetHandleInfo - 



\return term - Termination code

\param  ch - 
\param  hi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHandleInfo"

logical CClient :: GetHandleInfo (CS_Handle *ch, HandleInfo &hi )
{
  logical           term = YES;
#ifndef IF_Class  // client version

  if ( is_local )
    return(NULL);
  else
  {
    LockSend();
    send_parms.Fill(ch);
    term = SendCSMessage(NULL,S_CClient,SF_CClient_GetHandleInfo_ci1);
    if ( !term )
      term = FillHandleInfo(hi);
    UnlockSend();
  }
  return(term);
  
#else             // server version

  ((SC_Handle *)(*parms)[0].GetHandle()->GetServerPointer())->FillResult(result);

  return(NO);

#endif


}

/******************************************************************************/
/**
\brief  GetMachineType - 



\return machtype - 

\param  machtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMachineType"

MachineTypes CClient :: GetMachineType (MachineTypes machtype )
{

#ifndef IF_Class  // client version
  
  if ( !server_mtype )
  {
    if ( is_local )
      server_mtype = machine_type;
    else
    {
      LockSend();
      send_parms.Fill((int32)machtype);
      if ( !SendCSMessage(NULL,S_CClient,SF_CClient_GetMachineType_ci) )
        server_mtype = (MachineTypes)(*rec_result)[0].GetLong(conversion);
      UnlockSend();
    }
  }
  return(server_mtype);
  
#else             // server version
  
  ((CS_ServerClient *)connection)->SetCMachineType((MachineTypes)(*parms)[0].GetLong(connection->get_conversion()));
  result->Fill((int32)connection->get_machine_type());
  
  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetPointerSize - 



\return pointer_size - 

\param  pointer_size - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPointerSize"

int32 CClient :: GetPointerSize (int32 pointer_size )
{

#ifndef IF_Class  // client version
  if ( !server_ptr_size )
  {
    if ( is_local )
      server_ptr_size = sizeof(void *);
    else
    {
      LockSend();
      send_parms.Fill(pointer_size);
      if ( !SendCSMessage(NULL,S_CClient,SF_CClient_GetPointerSize_ci) )
        server_ptr_size = (int16)(*rec_result)[0].GetLong(conversion);
      UnlockSend();
    }
  }
  return(server_ptr_size);
  
#else             // server version

  ((CS_ServerClient *)connection)->SetCPointerSize((*parms)[0].GetLong(connection->get_conversion()));
  result->Fill((int32)sizeof(void *));

  return(NO);

#endif


}

/******************************************************************************/
/**
\brief  GetServerVariable - 



\return var_string - 

\param  var_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerVariable"

char *CClient :: GetServerVariable (char *var_name )
{
  char    *var_string = NULL;
#ifndef IF_Class  // client version

  if ( is_local )
    var_string = GetSysVariable(var_name);
  else 
  {
    LockSend();
    send_parms.Fill(var_name);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_GetServerVariable_ci) )
      var_string = (*rec_result)[0].GetString();
    UnlockSend();
  }
  return(var_string);
  
#else             // server version
  
  var_string =  GetSysVariable(
                  (*parms)[0].GetString()
          );
   
  result->Fill(var_string);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetServerVersion - 



\return version_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerVersion"

char *CClient :: GetServerVersion ( )
{
  char      *string = NULL;
#ifndef IF_Class  // client version

  if ( is_local ) 
    return (ODABA2Version());

  SetClientPointer(this);
  
  LockSend();
  send_parms.Fill();
  if ( !SendCSMessage(this,S_CClient,SF_CClient_GetServerVersion_ci) )
  {
    SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
    string = (*rec_result)[0].GetString();
  }
  UnlockSend();
  return(string);

#else             // server version
  
// nur hier, weil das die erste Function ist, die nach dem Connect läuft
  CS_Handle   *handle = parms->GetHandle();
  
  SystemServices()->RegisterThread(); 
  
  ((ServerConnection *)connection)->SetClientPointer(handle->GetClientPointer());
  handle->SetServerPointer(((ServerConnection *)connection));
  *result->GetHandle() = *handle;
// alles Initialisierung
  
  result->Fill(ODABA2Version());
  return(NO);

#endif


  


}

/******************************************************************************/
/**
\brief  InitConnection - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitConnection"

logical CClient :: InitConnection ( )
{
  logical                 term = NO;
  services->RegisterThread();

// ggf. müssen noch die Services gesetzt werden

  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 




\param  inipath - 
\param  application_name - 
\param  progpath - 
\param  application_type - 
\param  init_services - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CClient :: Initialize (char *inipath, char *application_name, char *progpath, ApplicationTypes application_type, logical init_services )
{
  ProcessInfo   *procinfo;
  char          *prot_file;
  char          *old_prot_file = NULL;
  int            usecount;

  if ( !c_client )
  {
    c_client = (ObjectReference *)this;
    RegisterProcess();
#ifdef __unix__
    signal(SIGSEGV, ThreadException);
    signal(SIGABRT, ThreadException);
    signal(SIGFPE, ThreadException);
    signal(SIGBUS, ThreadException);
#endif
  }
    
  if ( inipath )
  {
     if (application_name) {
       SetSysVarINIFile(inipath, application_name);
     } else {
       SetSysVarINIFile(inipath, "APPLICATION_DATA");
     }
    
    if ( GetSysVariable("SYSTEM_ENVIRONMENT") )
      inipath = GetSysVariable("SYSTEM_ENVIRONMENT");
  }
    
  procinfo = ThreadEntry::GetCurProcInfo();

  appl_type = application_type;
  if ( appl_type == APT_Console )
  {
    if ( inipath )
    {
      old_prot_file = GetSysVariable("TRACE");
      RemoveSysVariable("TRACE");
    }
      
    if ( (prot_file = GetSysVariable("TRACE")) ||
         (prot_file = GetSysVariable("TEMP"))     )
    {
      SetSysVariable("TRACE",prot_file);
      procinfo->SetProtocolFile(prot_file);
    }
    else
      SetSysVariable("TRACE",old_prot_file);
    
  }
    
  client_reference = (ObjectReference *)this;
  
  UtilityControlBlock();  // das machen wir, um die Client-Reservierungen im UtilityHandle, das indirect über die Services angelegt wird, nicht zurückzusetzen.
  if ( !services )  
  {
    services = new Services();
    init_services = YES;
  }
  usecount = use_count;
  if ( init_services )
    services->Initialize(this,inipath,progpath);
//  use_count = usecount;  // das ist nötig, damit auch der Main-Client einmal destruiert wird
    
  if ( application_name && *application_name )
    SetSysVariable("__APPLICATION_NAME",application_name);

  if ( appl_type == APT_Windows )
    services->get_error_handle()->ActivateGUIMessages();
  SDBRESET


}

/******************************************************************************/
/**
\brief  IsConnected - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConnected"

logical CClient :: IsConnected ( )
{

  return( ClientConnection::IsConnected() );

}

/******************************************************************************/
/**
\brief  KillClient - 



\return term - Termination code

\param  client_id - 
\param  wait_sec - 
\param  send_message - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KillClient"

logical CClient :: KillClient (int32 client_id, int32 wait_sec, logical send_message )
{

#ifndef IF_Class  // client version

  if ( is_local )
    return(NULL);
  else
  {
    LockSend();
    send_parms.Fill(client_id,wait_sec,send_message);
    SendCSMessage(NULL,S_CClient,SF_CClient_KillClient_ci);
    UnlockSend();
  }
  return(NO);
  
#else             // server version

  ((ServerConnection *)connection)->get_odaba_server()->KillClient(
                  ((ServerConnection *)connection)->get_current_index(), // sending client
                  (*parms)[0].GetLong(connection->get_conversion()),     // client_id
                  (*parms)[1].GetLong(connection->get_conversion()),     // waiting time
                  (*parms)[2].GetUChar()                                 // send_message
              );
  result->Fill((logical)NO);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  PackDatabase - 



\return term - Termination code

\param  cpath - Complete path
\param  temp_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PackDatabase"

logical CClient :: PackDatabase (char *cpath, char *temp_path )
{
  logical         local = temp_path && *temp_path ? NO : YES;
  uint16          version_nr;
  logical         term  = NO;
  char            targ_path[513];
  char            filename[128];
  char            filext[32];
BEGINSEQ
  if ( !cpath || !*cpath )                           SDBERR(200)
  
  if ( local )
  {
    strcpy(targ_path,cpath);
    filextr(targ_path,"#_O");
  }
  else
  {
    if ( !IsDirectory(temp_path) )
      if ( MakePathDirectories(temp_path) )          SDBERR(200)
    GetFileNameInfo(cpath,filename,filext,sizeof(filename)-1,sizeof(filext)-1);
    strcat(strcat(strcat(strcat(strcpy(targ_path,temp_path),"/"),filename),"."),filext);
  }

  {
    eb_RootBase     srce_base(NO,NO);
    eb_RootBase     targ_base(NO,NO);
  
    if ( srce_base.Open(cpath,NO,NO,YES) )           ERROR
    
    if (srce_base.get_pif()) {
       SetSysVariable("PLATFORM_INDEPENDENT", "YES");
    } else {
       SetSysVariable("PLATFORM_INDEPENDENT", "NO");
    }
    
    
    if ( targ_base.Provide(targ_path,PI_Write,NO,YES) )ERROR
    if ( targ_base.Copy(&srce_base,appl_type == APT_Console ? YES : NO,AUTO) )
                                                     ERROR
  }    
  
  if ( local )
  {
    remove(cpath);
    if ( rename(targ_path,cpath) != 0 )         SDBERR(217)
  }
  else
  {
    remove(cpath);
    printf("restoring database %s",cpath);
    CopySingleFile(targ_path,cpath);
    remove(targ_path);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RestoreDB - 



\return cond - 

\param  cpath - Complete path
\param  source - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical CClient :: RestoreDB (char *cpath, char *source, int32 wait_sec )
{
  logical     term = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    term = FileCopy(source,cpath,AUTO);
  else
  {
    LockSend();
    send_parms.Fill(cpath,wait_sec,source);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_RestoreDB_ci) )
      if ( term = (*rec_result)[0].GetUChar() )
        printf((*rec_result)[1].GetString());
    UnlockSend();
  }
  return(term);
  
#else             // server version
  NString         nresult;
  term = ((ServerConnection *)connection)->RestoreDB(
                  (*parms)[0].GetString(),               // cpath
                  (*parms)[2].GetString(),               // source
                  nresult,
                  (*parms)[1].GetLong(connection->get_conversion()) ); // wait_sec
  result->Fill(term,term ? nresult : "");
  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SayHello - Test function for performance test



\return string - 

\param  testdata - 
\param  size - Field size
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SayHello"

char *CClient :: SayHello (void *testdata, uint32 size )
{
  char                   *string = NULL;
#ifndef IF_Class  // client version

  if ( connected )
  {
    LockSend();
    send_parms.Fill(testdata,size);
    SendCSMessage(this,S_CClient,SF_CClient_SayHello_ci);
    string = (*rec_result)[0].GetString();
    UnlockSend();
  }
  return(string);

#else             // server version
  
  result->Fill("Hello");
  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SendClientMessage - Send message to clients



\return term - Termination code

\param  client_id - 
\param  mtext - 
\param  mtitle - 
\param  mtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendClientMessage"

logical CClient :: SendClientMessage (int32 client_id, char *mtext, char *mtitle, uint8 mtype )
{

#ifndef IF_Class  // client version

  if ( is_local )
    return(NULL);
  else
  {
    LockSend();
    send_parms.Fill(client_id,mtext,mtitle,mtype);
    SendCSMessage(NULL,S_CClient,SF_CClient_SendClientMessage_ci0);
    UnlockSend();
  }
  return(NO);
  
#else             // server version

  ((ServerConnection *)connection)->get_odaba_server()->SendClientMessage(
                  ((ServerConnection *)connection)->get_current_index(), // sending client
                  (*parms)[0].GetLong(connection->get_conversion()),     // client_id
                  (*parms)[1].GetString(),                               // message text
                  (*parms)[2].GetString(),                               // message title
                  (*parms)[3].GetUChar()                                 // message type
              );
  result->Fill((logical)NO);

  return(NO);

#endif

  return(NO);
}

/******************************************************************************/
/**
\brief  SendDummy - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendDummy"

logical CClient :: SendDummy ( )
{
  logical                 term = NO;
  LockSend();
  send_parms.Fill();
  term = SendCSMessage(NULL,0,7);
  UnlockSend();

  return(term);
}

/******************************************************************************/
/**
\brief  SetClientName - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClientName"

logical CClient :: SetClientName ( )
{
  char     *appl_name = GetSysVariable("__APPLICATION_NAME");
#ifndef IF_Class  // client version

  char    string[256];
  
  if ( !is_local ) 
  {
    GetConnectionName(string,sizeof(string));
    if ( appl_name && *appl_name )
      strcat(strcat(strcat(string,"("),appl_name),")");
    LockSend();
    send_parms.Fill(string);
    SendCSMessage(NULL,S_CClient,SF_CClient_SetClientName_ci);
    UnlockSend();
  }
  return(NO);
  
#else             // server version
  
  ((ServerConnection *)connection)->SetClientName((*parms)[0].GetString());
  result->Fill((logical)NO);
  return(NO);
  
#endif

}

/******************************************************************************/
/**
\brief  SetServerVariable - 



\return term - Termination code

\param  var_name - 
\param  var_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServerVariable"

logical CClient :: SetServerVariable (char *var_name, char *var_string )
{
  logical   term = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    SetSysVariable(var_name,var_string);
  else
  {
    LockSend();
    send_parms.Fill(var_name,var_string);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_SetServerVariable_ci) )
      if ( !(term = (*rec_result)[0].GetUChar()) )
        SetSysVariable(var_name,var_string);
    UnlockSend();
  }
  return(term);
  
#else             // server version
  
  term =  SetSysVariable(
                  (*parms)[0].GetString(),
                  (*parms)[1].GetString()
          );
   
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SetupDataSource - 



\return term - Termination code

\param  ds_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDataSource"

logical CClient :: SetupDataSource (DataSourceHandle *ds_handle )
{
  logical                 term = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    term = SystemServices()->SetupDataSource(ds_handle);
  else 
  {
    LockSend();
    send_parms.Fill(ds_handle->data_source);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_SetupDataSource_ci) )
      term = GetDSResult(ds_handle);
    UnlockSend();
  }
  return(term);
  
#else             // server version
  
  ((ServerConnection *)connection)->FillDSResult(result,(*parms)[0].GetString());

  return(NO);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  ShutDown - 



\return term - Termination code

\param  close_system - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShutDown"

logical CClient :: ShutDown (logical close_system )
{
  logical                 deleted = NO;
  UtilityHandle          *uh;
  logical                 term = NO;
BEGINSEQ
  if ( this && this == GetMainClient().GetClientPtr() )
  {
    if ( use_count > 0 )
    {
      ReferenceObject::Reserve();
      deleted = NO;
    }
    c_client = NULL;
    delete services;
    services = NULL;
    if ( connected )
      DisconnectServer();
    connected = 0;    
    SetUtilityCB(NULL);
    if ( !deleted )                 // damit der client auch mal gelöscht wird
      use_count = 2;                // ob das so geht, müssen wir sehen 03.02.2003
    ReferenceObject::Release();
    UnregisterProcess();
    if ( close_system )
    {
      ThreadList::Reset();
      DLL_Handle::Delete();
    }
    LEAVESEQ
  }
  services = NULL;
  
  if ( connected )
    DisconnectServer();
  connected = 0;


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StartPause - 



\return term - Termination code

\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartPause"

logical CClient :: StartPause (int32 wait_sec )
{
  logical                 term = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    term = ::StartPause(wait_sec);
  else
  {
    LockSend();
    send_parms.Fill(wait_sec);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_StartPause_ci) )
      term = (*rec_result)[0].GetUChar();
    UnlockSend();
  }
  return(term);
  
#else             // server version
  
  term = StartPause((*parms)[0].GetLong(connection->get_conversion()));        // wait_sec
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  StatDisplay - 



\return cond - 

\param  cpath - Complete path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StatDisplay"

logical CClient :: StatDisplay (char *cpath, char *ppath )
{
  logical     cond = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    cond = LDBHandle::StatDisplay(cpath,ppath);
  else
  {
    LockSend();
    send_parms.Fill(cpath,ppath);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_StatDisplay_ci) )
      cond = (*rec_result)[0].GetUChar();
    UnlockSend();
  }
  return(cond);
  
#else             // server version
  
  cond = LDBHandle::StatDisplay((*parms)[0].GetString(),        // cpath
                                (*parms)[1].GetString() );      // ppath
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  StopPause - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopPause"

void CClient :: StopPause ( )
{

#ifndef IF_Class  // client version

  if ( is_local )
    ::StopPause();
  else
  {
    LockSend();
    send_parms.Fill();
    
    SendCSMessage(NULL,S_CClient,SF_CClient_StopPause_ci);
    UnlockSend();
  }
  
#else             // server version
  
  StopPause(); 
  result->Fill();

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SysInfoDisplay - 



\return cond - 

\param  cpath - Complete path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SysInfoDisplay"

logical CClient :: SysInfoDisplay (char *cpath, char *ppath )
{
  logical     cond = NO;
#ifndef IF_Class  // client version

  if ( is_local )
    cond = !LDBHandle::SysInfoDisplay(cpath,ppath);
  else
  {
    LockSend();
    send_parms.Fill(cpath,ppath);
    
    if ( !SendCSMessage(NULL,S_CClient,SF_CClient_SysInfoDisplay_ci) )
      cond = (*rec_result)[0].GetUChar();
    UnlockSend();
  }
  return(cond);
  
#else             // server version
  
  extern  CServer  *c_server;
  char              dbpath[256];
    
  if ( c_server->GetCatlgName((*parms)[0].GetString(),dbpath,sizeof(dbpath)-1) )
    cond = !LDBHandle::SysInfoDisplay(dbpath,                         // cpath
                                      (*parms)[1].GetString() );      // ppath
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ~CClient - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CClient"

     CClient :: ~CClient ( )
{

//statistics1.Print("  Check1",YES);
//statistics2.Print("  Check4",NO);
//  statistics1.TraceMessage("  PTA Delete",YES);
//  statistics2.TraceMessage("  PTA Write",NO);
  use_count = 0;
  ShutDown(NO);



}


