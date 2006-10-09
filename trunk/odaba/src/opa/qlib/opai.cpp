/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    opai

\brief    


\date     $Date: 2006/08/26 14:13:20,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "opai"

#include  <popa7.h>
#include  <cdlhdl.h>
#include  <exthrde.h>
#include  <ljump.h>
#include  <versions.h>
#include  <sCAU_Reaction.hpp>
#include  <sCClient.hpp>
#include  <sCSUtilityHandle.hpp>
#include  <sCS_Handle.hpp>
#include  <sCServer.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDLL_Handle.hpp>
#include  <sEventHandler.hpp>
#include  <sEventLink.hpp>
#include  <sExecExchange.hpp>
#include  <sHandleInfo.hpp>
#include  <sInitArea.hpp>
#include  <sInstance.hpp>
#include  <sODABAServer.hpp>
#include  <sOPAGlobals.hpp>
#include  <sOPA_Variables.hpp>
#include  <sPIStack.hpp>
#include  <sProcessInfo.hpp>
#include  <sQueryHandle.hpp>
#include  <sServices.hpp>
#include  <sSystemClass.hpp>
#include  <sThreadEntry.hpp>
#include  <sUtilityHandle.hpp>
#include  <snode.hpp>

#include  <iopai.h>

/******************************************************************************/
/**
\brief  CTXError - 



\return error - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTXError"

Error &__cdecl CTXError ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  Error       *error = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  error = (Error *)proc_info->GetProcessVariable(PVN_OPACTXError);

RECOVER

ENDSEQ
  return(*error);
}

/******************************************************************************/
/**
\brief  DLLHandle - 



\return dllhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLLHandle"

DLL_Handle *__cdecl DLLHandle ( )
{

  if ( !dllhandle )
    dllhandle = new DLL_Handle();
  return(dllhandle);
}

/******************************************************************************/
/**
\brief  GetActiveHandle - Get active handle

        In  client server mode the function returns the handle that is active in
        the  thread. This is the handle from the object that called the function
        entering the thread.

\return client_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveHandle"

int64 __cdecl GetActiveHandle ( )
{
  ProcessInfo   *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  int64         *client_handle;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  client_handle = (int64 *)proc_info->GetProcessVariable(PVN_OPAActiveHandle);

RECOVER

ENDSEQ
  return(client_handle ? *client_handle : 0);
}

/******************************************************************************/
/**
\brief  GetDataCatalogue - 



\return object_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataCatalogue"

DBObjectHandle &__cdecl GetDataCatalogue ( )
{

  return(SystemServices()->GetSystemObject());

}

/******************************************************************************/
/**
\brief  GetFunctionPtr - 



\return func_ptr - 

\param  dllname - 
\param  fnames - 
\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFunctionPtr"

void *__cdecl GetFunctionPtr (char *dllname, char *fnames, logical check_opt )
{

  return( DLLHandle()->GetFunctionPtr(dllname,fnames,check_opt) );

}

/******************************************************************************/
/**
\brief  GetHandleCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHandleCount"

int32 __cdecl GetHandleCount ( )
{

  return(node_count);

}

/******************************************************************************/
/**
\brief  GetMainClient - 



\return main_client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainClient"

ODABAClient &__cdecl GetMainClient ( )
{
  extern ObjectReference  *c_client;

  return(*(ODABAClient *)&c_client);

}

/******************************************************************************/
/**
\brief  GetMetaAttributeType - 



\return meta_type - 

\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMetaAttributeType"

MAT_Types __cdecl GetMetaAttributeType (char *prop_names )
{
  MAT_Types     meta_type = MAT_undefined;
BEGINSEQ
  if ( !prop_names )                                 ERROR
  if ( !strcmp(prop_names,"__SORTKEY") )
    meta_type = MAT_SortKey;
  else if ( !strcmp(prop_names,"__KEY") )
    meta_type = MAT_Key;
  else if ( !strcmp(prop_names,"__IDENTITY") )
    meta_type = MAT_GUID;
  else if ( !strcmp(prop_names,"__LOID") )
    meta_type = MAT_LOID;
  else if ( !strcmp(prop_names,"__GUID") )
    meta_type = MAT_GUID;
  else if ( !strcmp(prop_names,"__TYPE") )
    meta_type = MAT_Type;
  else if ( !strcmp(prop_names,"__PROPERTY") )
    meta_type = MAT_Property;

RECOVER
  meta_type = MAT_undefined;
ENDSEQ
  return(meta_type);
}

/******************************************************************************/
/**
\brief  GetOPAProcessVariable - 



\return pvariable - 

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOPAProcessVariable"

void *__cdecl GetOPAProcessVariable (ProcessVariableNames pv_name )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  void        *proc_var = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  proc_var = proc_info->GetProcessVariable(pv_name);

RECOVER

ENDSEQ
  return(proc_var);
}

/******************************************************************************/
/**
\brief  GetSystemDBObject - 



\return object_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemDBObject"

DBObjectHandle &__cdecl GetSystemDBObject ( )
{

  return(SystemServices()->GetSystemObject());

}

/******************************************************************************/
/**
\brief  GetSystemDictionary - 



\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemDictionary"

DictionaryHandle &__cdecl GetSystemDictionary ( )
{
  static   DictionaryHandle   dict_null;
  DictionaryHandle           *sysdict;
  if ( !(sysdict = &SystemServices()->GetSystemDictionary()) )
    if ( sdbuptr && sdbuptr->sdbusys )
      sysdict = &sdbuptr->sdbusys->dictionary;
  
  return(sysdict ? *sysdict : dict_null);

}

/******************************************************************************/
/**
\brief  INITArea - 



\return init_area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "INITArea"

InitArea *__cdecl INITArea ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  InitArea    *init_area = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  init_area = (InitArea *)proc_info->GetProcessVariable(PVN_OPAInitArea);

RECOVER

ENDSEQ
  return(init_area);
}

/******************************************************************************/
/**
\brief  LockGlobal - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockGlobal"

logical __cdecl LockGlobal ( )
{
  extern OPAGlobals opa_globals;
  return( opa_globals.ILockGlobal() );

}

/******************************************************************************/
/**
\brief  ODABA2Version - 



\return version_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABA2Version"

char *__cdecl ODABA2Version ( )
{


  return(ODABA_Version);
}

/******************************************************************************/
/**
\brief  OPAInitProcessInfo - 



\return proc_info - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPAInitProcessInfo"

ProcessInfo *__cdecl OPAInitProcessInfo ( )
{
  ProcessInfo *proc_info = NULL;

  if ( thread_list )
    if ( !(proc_info = ThreadEntry::GetCurProcInfo()) )
      proc_info = ThreadEntry::CreateCurProcInfo(NULL);
  
  if ( proc_info && !proc_info->GetVariableManager(PVT_OPA) )
    proc_info->SetVariableManager(new OPA_Variables(proc_info->GetProcessVariables()));
  return(proc_info);
}

/******************************************************************************/
/**
\brief  OPAResources - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPAResources"

void __cdecl OPAResources ( )
{
  extern        int32 acb_count;
  extern        int32 exd_count;
  extern        int32 dbf_count;
  extern        int32 inti_count;
  extern        int32 inti_max;
  extern        int32 node_count;
  extern        int32 node_max;
  extern        int32 node_total;
  extern        int32 dbres_count;
  char          string[16];
  SDBError().TraceMessage("acb count : ",gvtxltoa(acb_count,string,10));
  acb_count = 0;
  SDBError().TraceMessage("exd count : ",gvtxltoa(exd_count,string,10));
  exd_count = 0;
  SDBError().TraceMessage("dbf count: ",gvtxltoa(dbf_count,string,10));
  dbf_count = 0;
  SDBError().TraceMessage("inti count: ",gvtxltoa(inti_count,string,10));
  inti_count = 0;
  SDBError().TraceMessage("inti max  : ",gvtxltoa(inti_max,string,10));
  inti_max = 0;
  SDBError().TraceMessage("node count: ",gvtxltoa(node_count,string,10));
  node_count = 0;
  SDBError().TraceMessage("node total: ",gvtxltoa(node_total,string,10));
  node_total = 0;
  SDBError().TraceMessage("dbres count:",gvtxltoa(dbres_count,string,10));
  dbres_count = 0;


}

/******************************************************************************/
/**
\brief  OQLError - 



\return error - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OQLError"

Error &__cdecl OQLError ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  Error       *error = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  error = (Error *)proc_info->GetProcessVariable(PVN_OPAOQLError);

RECOVER

ENDSEQ
  return(*error);
}

/******************************************************************************/
/**
\brief  RegisterTA - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterTA"

logical __cdecl RegisterTA ( )
{
  extern OPAGlobals opa_globals;
  return(opa_globals.RegisterTA());

}

/******************************************************************************/
/**
\brief  RootBaseShared - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RootBaseShared"

logical __cdecl RootBaseShared ( )
{
  extern OPAGlobals opa_globals;

  return( opa_globals.RootBaseShared() );

}

/******************************************************************************/
/**
\brief  SDBError - 



\return error - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDBError"

Error &__cdecl SDBError ( )
{
  ProcessInfo *proc_info;
  Error       *error = NULL;
BEGINSEQ
  proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);  
  
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  error = (Error *)proc_info->GetProcessVariable(PVN_OPASDBError);

RECOVER

ENDSEQ
  return(*error);
}

/******************************************************************************/
/**
\brief  SetActiveHandle - Ste active handle

        This  function  is  used  by  the  server setting the active handle when
        entering  the  exec  thread.  The  handle  should  not  be  changed  by 
        applications.


\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActiveHandle"

void __cdecl SetActiveHandle (int64 client_handle )
{
  ProcessInfo   *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  int64         *client_handle_ptr;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  if ( client_handle_ptr = (int64 *)proc_info->GetProcessVariable(PVN_OPAActiveHandle) )
    *client_handle_ptr = client_handle;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetUtilityCB - 




\param  utilitycb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUtilityCB"

void __cdecl SetUtilityCB (UtilityHandle *utilitycb )
{
  ProcessInfo   *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  proc_info->SetProcessVariable(PVN_OPAUtilityCB,utilitycb);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetUtilityHandle - 




\param  utilitycb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUtilityHandle"

void __cdecl SetUtilityHandle (UtilityHandle *utilitycb )
{
  ProcessInfo   *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  proc_info->SetProcessVariable(PVN_OPAUtilityCB,utilitycb);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ShareRootBase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShareRootBase"

void __cdecl ShareRootBase ( )
{
  extern OPAGlobals opa_globals;
  opa_globals.ShareRootBase();

}

/******************************************************************************/
/**
\brief  ShutDownODABA - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShutDownODABA"

void __cdecl ShutDownODABA ( )
{

  GetMainClient().ShutDown();

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

logical __cdecl StartPause (int32 wait_sec )
{
  extern OPAGlobals opa_globals;
  return( opa_globals.StartPause(wait_sec) );

}

/******************************************************************************/
/**
\brief  StopPause - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopPause"

void __cdecl StopPause ( )
{
  extern OPAGlobals opa_globals;
  opa_globals.StopPause();

}

/******************************************************************************/
/**
\brief  SystemServices - 



\return services - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemServices"

Services *__cdecl SystemServices ( )
{
  extern ObjectReference     *c_client;
  extern CServer             *c_server;
  return ( c_client ? GetMainClient().GetClientPtr()->get_services() :
           c_server ? c_server->get_services() :
           NULL                                         );

}

/******************************************************************************/
/**
\brief  ThreadException - 




\param  sign - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadException"

void __cdecl ThreadException (int sign )
{

#ifdef __unix__
  signal(SIGSEGV, ThreadException);
  signal(SIGFPE, ThreadException);
  signal(SIGBUS, ThreadException);
  signal(SIGABRT, ThreadException);
  longjmp(GetProcessVariable(PVN_SOSLONG_JUMP), sign);
#endif

}

/******************************************************************************/
/**
\brief  UnlockGlobal - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockGlobal"

logical __cdecl UnlockGlobal ( )
{
  extern OPAGlobals opa_globals;
  return( opa_globals.IUnlockGlobal() );

}

/******************************************************************************/
/**
\brief  UnregisterTA - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterTA"

void __cdecl UnregisterTA ( )
{
  extern OPAGlobals opa_globals;
  opa_globals.UnregisterTA();

}

/******************************************************************************/
/**
\brief  UtilityControlBlock - 



\return utilitycb - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UtilityControlBlock"

UtilityHandle *__cdecl UtilityControlBlock ( )
{
  ProcessInfo   *proc_info = ThreadEntry::GetCurProcInfo(PVT_OPA);
  UtilityHandle *utilitycb = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OPAInitProcessInfo()) )          ERROR

  utilitycb = (UtilityHandle *)proc_info->GetProcessVariable(PVN_OPAUtilityCB);

RECOVER

ENDSEQ
  return(utilitycb);
}

/******************************************************************************/
/**
\brief  __TraceNodes - 



\return count - 

\param  max_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__TraceNodes"

int32 __cdecl __TraceNodes (int32 max_count )
{

  return(node::__TraceList(max_count));

}

