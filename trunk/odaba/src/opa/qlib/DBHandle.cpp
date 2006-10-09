/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBHandle

\brief    Database Handle
          Database  handle  must  be  created  for  accessing  data in an ODABA2
          database.  An  ODABA2  database  must  be  connected  with  a  {\b {.r
          Dictionary}}, which defines the object model for the database. 
          Each  ODABA database is a Database  Object (RootObject) that may refer
          to  subordinated root Database Objects.  Each Database Object within a
          database  has  its  own  name  space, i.e. identifying keys are unique
          only within a Database Object. 
          When   creating   a   database   handle   the   object handle ({\b {.r
          ACObject}})  for  the  root  Database  Object is created automatically
          (the  database handle is an Database  Object handle), i.e. besides the
          DBHandle  functions all ACObject functions  can be called. In addition
          the database handle is responsible for the log and recovery file.

\date     $Date: 2006/08/26 12:55:55,46 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBHandle"

#include  <fileacc.h>
#include  <popa7.h>
#include  <coctp.h>
#ifndef   DLL_ACObject_HPP
#define   DLL_ACObject_HPP
#include  <sACObject.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DBHandle_HPP
#define   DLL_DBHandle_HPP
#include  <sDBHandle.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sCDBHandle.hpp>
#include  <sCTX_DataBase.hpp>
#include  <sCheckOptions.hpp>
#include  <sDBHandle.hpp>
#include  <sDBResource.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Header.hpp>
#include  <sLDBHandle.hpp>
#include  <sOperation.hpp>
#include  <sRessourceLock.hpp>
#include  <sexd.hpp>
#include  <sDBHandle.hpp>


/******************************************************************************/
/**
\brief  ActivateShadowBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateShadowBase"

logical DBHandle :: ActivateShadowBase ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  BackupDB - 



\return term - Termination code

\param  target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical DBHandle :: BackupDB (char *target )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ChangeRecovery - Enable/disable recovery support



\return term - Termination code

\param  rec_type - Type of recovery support
\param  rec_path - Folder for recovery files
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeRecovery"

logical DBHandle :: ChangeRecovery (RecoveryType rec_type, char *rec_path )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  CheckDB - 



\return term - Termination code

\param  check_opts - 
\param  resnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical DBHandle :: CheckDB (CheckOptions check_opts, char *resnames )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CheckLicence - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  lic_owner - 
\param  lic_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical DBHandle :: CheckLicence (char *lic_owner, char *lic_number )
{

  return( YES );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  applname_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical DBHandle :: CheckLicence (char *applname_w )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CloseDBHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDBHandle"

logical DBHandle :: CloseDBHandle ( )
{


  if ( dictionary && dictionary->get_handle_list() )
    if ( dictionary->get_handle_list()->Find(this) )
      dictionary->get_handle_list()->RemoveAt();
  return(NO);
}

/******************************************************************************/
/**
\brief  CloseRecovery - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseRecovery"

logical DBHandle :: CloseRecovery ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  CloseWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseWorkspace"

logical DBHandle :: CloseWorkspace ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ConsolidateWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateWorkspace"

logical DBHandle :: ConsolidateWorkspace ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CreateACObject - 



\return obhandle - Database Object handle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *DBHandle :: CreateACObject (PIACC accopt, uint16 version_nr )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i3 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *DBHandle :: CreateACObject ( )
{

  return(new ACObject());

}

/******************************************************************************/
/**
\brief  CreateContext - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContext"

logical DBHandle :: CreateContext ( )
{
  int32                    id = 0;
  logical                 term = NO;

BEGINSEQ
//  if ( !dictionary || !(id = GetDatabaseID()) )      LEAVESEQ
  if ( !dictionary )                                   LEAVESEQ
  
  id = GetDatabaseID();                                                   
  if ( !(context = DLLHandle()->CreateDBCtx(GetCTXIPath(),id)) )
                                                     ERROR
  context->Initialize(this,NULL);
  
  if ( ACObject::CreateContext() )                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateEntry - 



\return entnr - 

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  clnumb - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEntry"

EB_Number DBHandle :: CreateEntry (int16 mbnumber, uint16 sbnumber, EB_Number clnumb, uint16 version_nr )
{


  return(UNDEF);

}

/******************************************************************************/
/**
\brief  DBHandle - Create a database handle



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBHandle"

     DBHandle :: DBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, uint16 version_nr, char sysenv )
                     : ACObject(), 
  dictionary(NULL),
  root_object_list(new DLL(ACObject)()),
  net_option(NO),
  system_env(UNDEF), 
  resource(NULL),
  db_lock(new RessourceLock(YES)),
  context(NULL)
{

  Initialize(dict_ptr,cpath,accopt,netopt,version_nr,sysenv);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  dictptr - Dictionary handle
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBHandle"

     DBHandle :: DBHandle (Dictionary *dictptr, PIACC accopt )
                     : ACObject(this,accopt), 
  dictionary(dictptr),
  root_object_list(new DLL(ACObject)()),
  net_option(NO),
  system_env(NO), 
  resource(NULL),
  db_lock(new RessourceLock(YES)),
  context(NULL)
{




}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBHandle"

     DBHandle :: DBHandle ( )
                     : ACObject (), 
  dictionary(NULL),
  root_object_list(new DLL(ACObject)()),
  net_option(NO),
  system_env(NO),
  resource(NULL),
  db_lock(new RessourceLock(YES)),
  context(NULL)
{





}

/******************************************************************************/
/**
\brief  i2 - 



\param  cpath - Complete path
\param  lowEBN - First entry number in database
\param  highEBN - Last entry number in database
\param  dasize - Size of data area in byte
\param  largedb - Indicates a large database
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBHandle"

     DBHandle :: DBHandle (char *cpath, int16 lowEBN, int16 highEBN, int32 dasize, logical largedb )
                     : ACObject (),
  dictionary(NULL),
  root_object_list(new DLL(ACObject)()),
  net_option(NO),
  system_env(UNDEF),
  resource(NULL),
  db_lock(new RessourceLock(YES)),
  context(NULL)
{





}

/******************************************************************************/
/**
\brief  DeactivateShadowBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateShadowBase"

logical DBHandle :: DeactivateShadowBase ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DeleteWorkspace - 



\return term - Termination code

\param  names - 
\param  user_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWorkspace"

logical DBHandle :: DeleteWorkspace (char *names, char *user_name )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  DiffersFrom - 



\return cond - 

\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiffersFrom"

logical DBHandle :: DiffersFrom (DBHandle *dbhandle )
{
  char     *p1;
  char     *p2;
  logical   cond = NO;
BEGINSEQ
  if ( this == dbhandle )                           LEAVESEQ
  if ( !this || !dbhandle )                         ERROR

  if ( IsServerObject() ^ dbhandle->IsServerObject() )
                                                    ERROR
  p1 = GetPath();
  p2 = dbhandle->GetPath();
  
  if ( !p1 || !p2 )                                 ERROR
  if ( strcmp(p1,p2) )                              ERROR

RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  DisableWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableWorkspace"

logical DBHandle :: DisableWorkspace ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  DiscardWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiscardWorkspace"

logical DBHandle :: DiscardWorkspace ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  EnableWorkspace - 



\return term - Termination code

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableWorkspace"

logical DBHandle :: EnableWorkspace (char *cpath )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ExecDBCtxFunc - 



\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecDBCtxFunc"

logical DBHandle :: ExecDBCtxFunc (char *fnames, char *w_parms )
{
  logical     term = NO;
BEGINSEQ
  if ( !context )                                   ERROR
    
  context->SetParm(w_parms);
  if ( context->ExecuteFunction(fnames) )
  {
    SDBCTXCERR                                     
    ERROR
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExistWorkspace - 



\return cond - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistWorkspace"

logical DBHandle :: ExistWorkspace (char *names )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  FlushClusterPool - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical DBHandle :: FlushClusterPool ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  GetClientDBHandle - 



\return cdbhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientDBHandle"

CDBHandle *DBHandle :: GetClientDBHandle ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetDatabaseHandle - 



\return dbhandleptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDatabaseHandle"

DatabaseHandle *DBHandle :: GetDatabaseHandle ( )
{
  DatabaseHandle  stat_dbh_ptr;
  return( this ? (DatabaseHandle *)&db_hdl : &stat_dbh_ptr );

}

/******************************************************************************/
/**
\brief  GetDatabaseID - 



\return db_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDatabaseID"

int32 DBHandle :: GetDatabaseID ( )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetLocalDBHandle - 



\return ldbhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalDBHandle"

LDBHandle *DBHandle :: GetLocalDBHandle ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetNewTypeID - 



\return sid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewTypeID"

int16 DBHandle :: GetNewTypeID ( )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetRecoveryFile - Provide name of recovery file



\return rfilname - 

\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryFile"

char *DBHandle :: GetRecoveryFile (uint16 recnum )
{


  return (NULL);
}

/******************************************************************************/
/**
\brief  GetRecoveryNum - Provide number for current recovery file



\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryNum"

uint16 DBHandle :: GetRecoveryNum ( )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetRecoveryPath - Provide path for recovery folder



\return recpath - Recovery path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryPath"

char *DBHandle :: GetRecoveryPath ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetRecoveryStartNumber - Get number for first recovery file



\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryStartNumber"

uint16 DBHandle :: GetRecoveryStartNumber ( )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetRecoveryType - 



\return rec_type - Type of recovery support

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryType"

RecoveryType DBHandle :: GetRecoveryType ( )
{


  return(RECOVERY_none);
}

/******************************************************************************/
/**
\brief  GetSchemaVersion - 



\return schemaversion - Scheme version

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSchemaVersion"

uint16 DBHandle :: GetSchemaVersion ( )
{

  return( GetCurrentSystemVersion() );

}

/******************************************************************************/
/**
\brief  GetSystemVersion - 



\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemVersion"

uint16 DBHandle :: GetSystemVersion ( )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  GetTempMain - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempMain"

int16 DBHandle :: GetTempMain ( )
{

  return ( UNDEF );

}

/******************************************************************************/
/**
\brief  GetThisDBHandle - 



\return dbhandle - Database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThisDBHandle"

DBHandle *DBHandle :: GetThisDBHandle ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  GetVersionString - 



\return version_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionString"

char *DBHandle :: GetVersionString ( )
{

  return( NULL );

}

/******************************************************************************/
/**
\brief  GetWorkspace - 



\return names - 

\param  ws_root - 
\param  lindx0 - 
\param  user_name - 
\param  names - 
\param  refresh - 
\param  ws_info - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspace"

char *DBHandle :: GetWorkspace (char *ws_root, int32 lindx0, char *user_name, char *names, logical refresh, char *ws_info )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  IgnoreWriteProtect - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IgnoreWriteProtect"

logical DBHandle :: IgnoreWriteProtect ( )
{

  SetSysVariable("__IGNORE_WPT__","Y");
  return(NO);
}

/******************************************************************************/
/**
\brief  InitDataArea - Initialise DataArea



\return term - Termination code

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  danumber - Number for DataArea
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDataArea"

logical DBHandle :: InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{



  return(YES);
}

/******************************************************************************/
/**
\brief  InitMainBase - Initialize MainBase



\return term - Termination code

\param  mbnumber - MainBase number
\param  filename - File name for DataArea file
\param  lowEBN - First entry number in database
\param  highEBN - Last entry number in database
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
\param  largedb - Indicates a large database
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMainBase"

logical DBHandle :: InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize, char *server, EB_Header *headerpt, logical largedb, logical pindep )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  InitRecovery - Initialise recovery file



\return term - Termination code

\param  recpath - Recovery path
\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRecovery"

logical DBHandle :: InitRecovery (char *recpath, uint16 recnum )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  InitSubBase - Initialise SubBase



\return term - Termination code

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSubBase"

logical DBHandle :: InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Initialize - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DBHandle :: Initialize (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, uint16 version_nr, char sysenv )
{

  Initialize(dict_ptr,accopt);
  
  net_option       = netopt;
  system_env       = sysenv; 
  context          = NULL;

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dict_ptr - Dictionary handle
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DBHandle :: Initialize (Dictionary *dict_ptr, PIACC accopt, uint16 version_nr )
{

  ACObject::Initialize(this,accopt,version_nr);
  
  dictionary  = dict_ptr;
  access_mode = accopt; 


}

/******************************************************************************/
/**
\brief  IsLicenced - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLicenced"

logical DBHandle :: IsLicenced ( )
{

  return( NO );

}

/******************************************************************************/
/**
\brief  LocateWorkspace - 



\return cond - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateWorkspace"

logical DBHandle :: LocateWorkspace (char *names )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  OpenRecovery - 



\return term - Termination code

\param  userinfo - Area for application recovery information
\param  uilen - Length of application data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRecovery"

logical DBHandle :: OpenRecovery (char *userinfo, int16 uilen )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  OpenWorkspace - 



\return term - Termination code

\param  names - 
\param  user_name - 
\param  exclusive - 
\param  cpath_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWorkspace"

logical DBHandle :: OpenWorkspace (char *names, char *user_name, logical exclusive, char *cpath_w )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  RecreateExtent - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecreateExtent"

logical DBHandle :: RecreateExtent (char *extnames )
{

BEGINSEQ
  SDBERR(999)   // function not supported in Client/server mode
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ResetLastSchemaVersion - 



\return term - Termination code

\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastSchemaVersion"

logical DBHandle :: ResetLastSchemaVersion (logical reset_opt )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ResetLastVersion - 



\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastVersion"

logical DBHandle :: ResetLastVersion (uint16 version_nr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  RestoreDB - 



\return term - Termination code

\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical DBHandle :: RestoreDB (char *source )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  SetupTypeID - 



\return term - Termination code

\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTypeID"

logical DBHandle :: SetupTypeID (int16 sid )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Write - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical DBHandle :: Write (exd *exdptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ~DBHandle - Destructur




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBHandle"

     DBHandle :: ~DBHandle ( )
{
  ACObject  *obhandle;
  while ( obhandle = root_object_list->RemoveTail() )
    delete obhandle;
  
  if ( dictionary )
    CloseDBHandle();
  
  delete context;
  context = NULL;  
  
  delete resource;
  resource = NULL;
  
  delete db_lock;
  db_lock = NULL;
  
  delete root_object_list;
  root_object_list = NULL;
  
  db_handle = NULL;

}


