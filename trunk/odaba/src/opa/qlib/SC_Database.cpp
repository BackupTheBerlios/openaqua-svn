/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    SC_Database



\date     $Date: 2006/05/31 18:29:11,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Database"

#include  <popa7.h>
#ifndef   DLL_SC_DBObject_HPP
#define   DLL_SC_DBObject_HPP
#include  <sSC_DBObject.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sCS_Connection.hpp>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sSC_DBObject.hpp>
#include  <sSC_Dictionary.hpp>
#include  <sSC_Handle.hpp>
#include  <sSC_Database.hpp>


/******************************************************************************/
/**
\brief  CheckDB

\return term - Termination code

\param  check_opts
\param  source
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical SC_Database :: CheckDB (CheckOptions check_opts, char *source )
{
  DBHandle               *dbhandle = get_dbhandle();
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ForceClose - Force database close



\param  cache_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void SC_Database :: ForceClose (logical cache_opt )
{
  SC_DBObject   *sc_dbo;
  if ( db_objects )
  {  
    db_objects->GoBottom();
    while ( sc_dbo = db_objects->GetPrev() )
      sc_dbo->ForceClose(cache_opt);
  }
  
  SC_DBObject::ForceClose(cache_opt);
  
  if ( db_objects )
  {  
    if ( !cache_opt )
      while ( sc_dbo = db_objects->GetTail() )
        ReleaseDBObject(sc_dbo);
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

char *SC_Database :: GetName ( )
{

  return ( GetPath() );

}

/******************************************************************************/
/**
\brief  GetTypeName

\return resource_type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *SC_Database :: GetTypeName ( )
{

  return( "DatabaseHandle" );

}

/******************************************************************************/
/**
\brief  IsUsingDB

\return sc_handle

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUsingDB"

SC_Handle *SC_Database :: IsUsingDB (char *cpath )
{
  char    *path = DatabaseHandle::GetPath();
  return ( path && cpath && !stricmp(cpath,path) ? this : NULL );

}

/******************************************************************************/
/**
\brief  ProvideDBObject - 


\return sc_dbobject

\param  client_handle
\param  accopt - Access mode
\param  version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDBObject"

SC_DBObject *SC_Database :: ProvideDBObject (int64 client_handle, PIACC accopt, uint16 version )
{
  SC_DBObject *sc_dbo = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  sc_dbo = new SC_DBObject(this,client_handle);
  if ( sc_dbo->Open(*this,accopt,version,RES_server_intern) )  
                                                     ERROR
  sc_dbo->get_obhandle()->GetLocalACObject()->SetServer();
  
  db_objects->AddTail(sc_dbo);
RECOVER
  delete sc_dbo;
  sc_dbo = NULL;
ENDSEQ
  return(sc_dbo);
}

/******************************************************************************/
/**
\brief  ReleaseDBObject

\return term - Termination code

\param  sc_dbobject
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDBObject"

logical SC_Database :: ReleaseDBObject (SC_DBObject *sc_dbobject )
{
  logical                 term = NO;
BEGINSEQ
  if ( !sc_dbobject )                                ERROR
    
  if ( db_objects->Find(sc_dbobject) )
    db_objects->RemoveAt();

  sc_dbobject->ReleaseSubObjects(NO);
  term = sc_dbobject->Close();
  
  delete sc_dbobject;
  sc_dbobject = NULL;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Remove

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical SC_Database :: Remove ( )
{

  return ( this ? ((SC_Dictionary *)parent)->ReleaseDatabase(this) : YES);

}

/******************************************************************************/
/**
\brief  SC_Database

-------------------------------------------------------------------------------
\brief  i0


\param  parent_handle
\param  client_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Database"

     SC_Database :: SC_Database (SC_Handle *parent_handle, int64 client_handle )
                     : SC_DBObject (parent_handle,client_handle),
DatabaseHandle (),
  db_objects(new DLL(SC_DBObject))
{
  SetServerPointer(this);
}

/******************************************************************************/
/**
\brief  i01


\param  cs_connection
\param  parent_handle
\param  client_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Database"

     SC_Database :: SC_Database (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle )
                     : SC_DBObject (cs_connection,parent_handle,client_handle),
DatabaseHandle (),
  db_objects(new DLL(SC_DBObject))
{

}

/******************************************************************************/
/**
\brief  SetDBHdl


\param  dbhdl_ptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDBHdl"

void SC_Database :: SetDBHdl (DatabaseHandle *dbhdl_ptr )
{

  *(DatabaseHdl *)this = *dbhdl_ptr;
  SetDBOHdl(dbhdl_ptr);

}

/******************************************************************************/
/**
\brief  ~SC_Database


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Database"

     SC_Database :: ~SC_Database ( )
{

  ForceClose(NO);
  delete db_objects;
  db_objects = NULL;

}


