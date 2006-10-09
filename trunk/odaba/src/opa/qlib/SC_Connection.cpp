/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    SC_Connection

\brief    


\date     $Date: 2006/07/12 19:17:01,18 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Connection"

#include  <popa7.h>
#include  <iopai.h>
#include  <sCS_Handle.hpp>
#include  <sCServer.hpp>
#include  <sDBHandle.hpp>
#include  <sLDBHandle.hpp>
#include  <sSC_CacheInfo.hpp>
#include  <sSC_Dictionary.hpp>
#include  <sSC_Handle.hpp>
#include  <sServerConnection.hpp>
#include  <sSC_Connection.hpp>


/******************************************************************************/
/**
\brief  BackupDB - 



\return term - Termination code

\param  cpath - Complete path
\param  target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical SC_Connection :: BackupDB (char *cpath, char *target )
{
  logical                 term = NO;
  term = FileCopy(cpath,target,YES);
  return(term);
}

/******************************************************************************/
/**
\brief  CacheConnection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheConnection"

logical SC_Connection :: CacheConnection ( )
{

  return(cache_info ? YES : NO);

}

/******************************************************************************/
/**
\brief  CheckDB - 



\return term - Termination code

\param  dict_hdl - Dictionary handle
\param  cpath - Complete path
\param  check_opts - 
\param  source - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical SC_Connection :: CheckDB (DictionaryHandle &dict_hdl, char *cpath, CheckOptions check_opts, char *source, NString &nstring )
{
  logical                 term = NO;
  DatabaseHandle   dbh(dict_hdl,cpath,PI_Write,NO,YES,CUR_VERSION,RES_server_intern,YES);
  if ( dbh.IsValid() )
  {
    dbh.get_dbhandle()->GetLocalDBHandle()->IgnoreSharedRB();
    term = dbh.CheckDB(check_opts,source);
    nstring = dbh.get_dbhandle()->GetOutputResult();
    dbh.get_dbhandle()->ResetOutputResult();
  }
  else
  {
    nstring = "\nCould not open database:";
    nstring+= ' ';
    nstring+= cpath;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ForceClose - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void SC_Connection :: ForceClose ( )
{
  logical         cache_opt = cache_info ? YES : NO;
  SC_Dictionary  *dict_client = NULL;
  dict_clients.GoBottom();
  while ( dict_client = dict_clients.GetPrev() )
    dict_client->ForceClose(cache_opt);

  if ( !cache_opt )
    while ( dict_client = dict_clients.GetTail() )
      ReleaseDict(dict_client);




}

/******************************************************************************/
/**
\brief  GetCacheInfo - 



\return cacheinfo - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCacheInfo"

SC_CacheInfo *SC_Connection :: GetCacheInfo ( )
{


  return(cache_info);
}

/******************************************************************************/
/**
\brief  IsCached - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCached"

logical SC_Connection :: IsCached ( )
{

  return(this && cache_info ? YES : NO);

}

/******************************************************************************/
/**
\brief  IsUsingDB - 



\return sc_handle - 

\param  cpath - Complete path
\param  database_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUsingDB"

SC_Handle *SC_Connection :: IsUsingDB (char *cpath, int8 database_opt )
{
  DLL(SC_Dictionary)      cursor(dict_clients);
  SC_Dictionary          *dict;
  SC_Handle              *sc_handle;
BEGINSEQ
  cursor.GoTop();
  while ( dict = cursor.GetNext() )
    if ( sc_handle = dict->IsUsingDB(cpath,database_opt) )
      LEAVESEQ

  ERROR
RECOVER
  sc_handle = NULL;
ENDSEQ
  return(sc_handle);
}

/******************************************************************************/
/**
\brief  LocateDict - 



\return dict_client - 

\param  handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateDict"

SC_Dictionary *SC_Connection :: LocateDict (CS_Handle *handle )
{
  SC_Dictionary  *dict_client = NULL;
BEGINSEQ
  dict_clients.GoTop();
  while ( dict_client = dict_clients.GetNext() )
    if ( *(CS_Handle *)dict_client == *handle )
      LEAVESEQ
ENDSEQ
  return(dict_client);
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

SC_Dictionary *SC_Connection :: ProvideDict (int64 client_handle, char *cpath, uint16 version, PIACC accopt )
{
  SC_Dictionary    *sc_dict   = NULL;
  SC_Handle        *sc_handle = NULL;
  DictionaryHandle  sys_dict  = GetSystemDictionary();
  char              path[1024];
BEGINSEQ
  odaba_server->GetCatlgName(cpath,path,sizeof(path)-1);
  
  if ( IsCached() )
    if ( (sc_handle = IsUsingDB(path,NO)) && (sc_dict = LocateDict(sc_handle)) )
      if ( !sc_dict->GetClientObject()    &&
           accopt == sc_dict->DictionaryHandle::GetAccess() &&
           (version == CUR_VERSION || version == sc_dict->DictionaryHandle::GetVersion())  )       
      {
        sc_dict->InitHandle(connection,client_handle);
        LEAVESEQ
      }

  sc_dict  = new SC_Dictionary(connection,connection,client_handle);
  if ( odaba_server->ProvideDict(path,version,sc_dict,accopt) )
                                                     ERROR
  sc_dict->DictionaryHandle::get_obhandle()->GetLocalACObject()->SetServer();
  dict_clients.AddTail(sc_dict);

  if ( sys_dict ) // && !resource_db.IsOpened()) --> Explicit OpenResourceDB required!!
    resource_db.Open(sys_dict,sc_dict->DictionaryHandle::GetPath(),PI_Read,YES,YES,CUR_VERSION,RES_server_intern);
  if ( sys_dict && resource_db.IsOpened())
    CTXError().SetSource((void *)&resource_db);

RECOVER
  delete sc_dict;
  sc_dict = NULL;
ENDSEQ
  return(sc_dict);
}

/******************************************************************************/
/**
\brief  ReleaseConnection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseConnection"

void SC_Connection :: ReleaseConnection ( )
{

  Reparent(connection);
  connection->ReleaseConnection();  
  
  connection = NULL;

}

/******************************************************************************/
/**
\brief  ReleaseDict - 



\return term - Termination code

\param  handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDict"

logical SC_Connection :: ReleaseDict (CS_Handle *handle )
{
  SC_Dictionary  *dict_client;
  logical         term = NO;
BEGINSEQ
  if ( !(dict_client = LocateDict(handle)) )         ERROR
    
  dict_clients.RemoveAt();
  odaba_server->ReleaseDict(dict_client);
  delete dict_client;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RestoreDB - 



\return term - Termination code

\param  cpath - Complete path
\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical SC_Connection :: RestoreDB (char *cpath, char *source )
{
  logical                 term = NO;
  term = FileCopy(source,cpath,AUTO);
  return(term);
}

/******************************************************************************/
/**
\brief  SC_Connection - 




\param  sconnection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Connection"

     SC_Connection :: SC_Connection (ServerConnection *sconnection )
                     : SC_Handle(sconnection,NULL,0),
  odaba_server(sconnection->get_odaba_server()),
  cache_info(NULL)

{



}

/******************************************************************************/
/**
\brief  SetCacheInfo - 




\param  cacheinfo - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCacheInfo"

void SC_Connection :: SetCacheInfo (SC_CacheInfo *cacheinfo )
{

  cache_info = cacheinfo;

}

/******************************************************************************/
/**
\brief  Setup - 




\param  sconnection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

void SC_Connection :: Setup (ServerConnection *sconnection )
{

  connection = sconnection;

}

/******************************************************************************/
/**
\brief  ~SC_Connection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Connection"

     SC_Connection :: ~SC_Connection ( )
{

  delete cache_info;
  cache_info = NULL;


}


