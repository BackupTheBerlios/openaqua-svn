/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    SC_Dictionary



\date     $Date: 2006/05/31 18:28:30,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Dictionary"

#include  <popa7.h>
#ifndef   DLL_SC_Database_HPP
#define   DLL_SC_Database_HPP
#include  <sSC_Database.hpp>
#include  <sDLL.h>
#endif
#include  <sCS_Connection.hpp>
#include  <sCS_Handle.hpp>
#include  <sCServer.hpp>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sODABAServer.hpp>
#include  <sSC_Database.hpp>
#include  <sSC_Handle.hpp>
#include  <sServerConnection.hpp>
#include  <sSC_Dictionary.hpp>


/******************************************************************************/
/**
\brief  ForceClose - Force closing dictionary



\param  cache_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void SC_Dictionary :: ForceClose (logical cache_opt )
{
  SC_Database *sc_db;
  if ( databases )
  {
    databases->GoBottom();
    while ( sc_db = databases->GetPrev() )
      sc_db->ForceClose(cache_opt);
  }
  
    SC_Database::ForceClose(cache_opt);
  
  if ( databases )
  {
    if ( !cache_opt )
      while ( sc_db = databases->GetTail() )
        ReleaseDatabase(sc_db);
  }
  
  MSG_Closed();
  if ( cache_opt )
    SetClientObject(0);

}

/******************************************************************************/
/**
\brief  GetName

\return resource_name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *SC_Dictionary :: GetName ( )
{

  return( SC_Database::GetPath() );

}

/******************************************************************************/
/**
\brief  GetTypeName

\return resource_type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *SC_Dictionary :: GetTypeName ( )
{

  return( "DictionaryHandle" );

}

/******************************************************************************/
/**
\brief  IsUsingDB

\return sc_handle

\param  cpath - Complete path
\param  database_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUsingDB"

SC_Handle *SC_Dictionary :: IsUsingDB (char *cpath, int8 database_opt )
{
  DLL(SC_Database)        cursor(*databases);
  char                   *path = DictionaryHandle::GetPath();
  SC_Database            *db;
  SC_Handle              *sc_handle = this;
BEGINSEQ
  if ( !cpath || !path )                             ERROR
  if ( database_opt != YES ) // NO or AUTO
    if ( !stricmp(cpath,path) )                      LEAVESEQ
  if ( database_opt == NO )                          ERROR
   
  cursor.GoTop();
  while ( db = cursor.GetNext() )
    if ( sc_handle = db->IsUsingDB(cpath) )
      LEAVESEQ

  ERROR
RECOVER
  sc_handle = NULL;
ENDSEQ
  return(sc_handle);
}

/******************************************************************************/
/**
\brief  ProvideDatabase - 


\return sc_database

\param  client_handle
\param  cpath - Complete path
\param  accopt - Access mode
\param  online_version
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDatabase"

SC_Database *SC_Dictionary :: ProvideDatabase (int64 client_handle, char *cpath, PIACC accopt, logical online_version, uint16 version_nr, char sysenv )
{
  SC_Database *sc_db = NULL;
  SC_Handle   *sc_handle;
  logical      netopt = YES;
  char         path[513];
BEGINSEQ
  connection->get_odaba_server()->GetCatlgName(cpath,path,sizeof(path)-1);
  
  if ( !this )                                       ERROR
  if ( connection->IsCached() )
    if ( (sc_handle = IsUsingDB(path,YES)) && 
         sc_handle->get_parent() == (SC_Handle *)this )
    {
      sc_db = (SC_Database *)sc_handle;
      if ( !sc_db->GetClientObject()    &&
           accopt == sc_db->DatabaseHandle::GetAccess() &&
           (version_nr == CUR_VERSION || version_nr == sc_db->DatabaseHandle::GetVersion())  )       
      {
        sc_db->InitHandle(connection,client_handle);
        if ( sc_db->get_dbhandle()->get_context() )
          sc_db->get_dbhandle()->get_context()->DBOpen();
        LEAVESEQ
      }
    }
  sc_db = new SC_Database(this,client_handle);
  if ( sc_db->DatabaseHandle::Open(*this,path,accopt,netopt,online_version,version_nr,RES_local,sysenv) )
                                                     ERROR
  sc_db->DatabaseHandle::get_obhandle()->GetLocalACObject()->SetServer();
  sc_db->SetDBOHdl((DatabaseHdl *)sc_db);
  databases->AddTail(sc_db);
RECOVER
  delete sc_db;
  sc_db = NULL;
ENDSEQ
  return(sc_db);
}

/******************************************************************************/
/**
\brief  ReleaseDatabase

\return term - Termination code

\param  sc_database
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDatabase"

logical SC_Dictionary :: ReleaseDatabase (SC_Database *sc_database )
{
  logical                 term = NO;
BEGINSEQ
  if ( !sc_database )                                ERROR
  if ( connection->IsCached() )                      LEAVESEQ
    
  if ( databases->Find(sc_database) )
    databases->RemoveAt();

  sc_database->ReleaseSubObjects(NO);
  sc_database->SetDBOHdl(NULL);
  term = sc_database->DatabaseHdl::Close();
  
  delete sc_database;
  sc_database = NULL;
  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SC_Dictionary


\param  cs_connection
\param  parent_handle
\param  client_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Dictionary"

     SC_Dictionary :: SC_Dictionary (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle )
                     : SC_Database (cs_connection,parent_handle,client_handle),
DictionaryHandle (),
  databases(new DLL(SC_Database))
{
  SetServerPointer(this);
}

/******************************************************************************/
/**
\brief  SetDictHdl


\param  dicthdl_ptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDictHdl"

void SC_Dictionary :: SetDictHdl (DictionaryHandle *dicthdl_ptr )
{
  *(DictionaryHdl *)this = *dicthdl_ptr;
  SetDBHdl(dicthdl_ptr);
}

/******************************************************************************/
/**
\brief  ~SC_Dictionary

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Dictionary"

     SC_Dictionary :: ~SC_Dictionary ( )
{

  ForceClose(NO);
  
  delete databases;
  databases = NULL;

}


