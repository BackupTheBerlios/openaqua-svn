/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    db_RootBase

\brief    


\date     $Date: 2006/06/25 16:19:28,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "db_RootBase"

#include  <popa7.h>
#include  <cRootBase_Types.h>
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEBI.hpp>
#include  <sEB_Header.hpp>
#include  <sEntryEvent.hpp>
#include  <sKeyCacheBase.hpp>
#include  <sSDB_Workspace.hpp>
#include  <sWorkspace.hpp>
#include  <sacb.hpp>
#include  <sdb_RootBase.hpp>
#include  <seb_DataArea.hpp>
#include  <seb_RootBase.hpp>
#include  <sieh.hpp>
#include  <sdb_RootBase.hpp>


/******************************************************************************/
/**
\brief  CheckEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical db_RootBase :: CheckEBI (acb *acbptr )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Check_WProtect - 


\return wptmode - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_WProtect"

uint8 db_RootBase :: Check_WProtect (acb *acbptr )
{


  return(UNDEF);

}

/******************************************************************************/
/**
\brief  Close - 


\return rootbase - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

db_RootBase *db_RootBase :: Close ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  Consolidate - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Consolidate"

logical db_RootBase :: Consolidate ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Create - 


\return entnr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  clnumb - 
\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number db_RootBase :: Create (EB_Number clnumb, int16 mbnumber, uint16 sbnumber, uint16 version_nr )
{


  return(0);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number db_RootBase :: Create (acb *acbptr )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical db_RootBase :: Delete (acb *acbptr )
{


  return(YES);

}

/******************************************************************************/
/**
\brief  DeleteRB - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteRB"

logical db_RootBase :: DeleteRB ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  ReferenceObject::Release();                    // root base destroyed

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteWorkspaces - 


\return term - Termination code

\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWorkspaces"

logical db_RootBase :: DeleteWorkspaces (DBHandle *dbhandle )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Discard - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Discard"

logical db_RootBase :: Discard ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Exist - 


\return cond - 

\param  path - 
\param  netopt - Multi-user access
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical __cdecl db_RootBase :: Exist (char *path, logical netopt, char chkopt )
{

  SDBRESET
  return ( eb_DataArea::Exist(path,netopt,chkopt) );


}

/******************************************************************************/
/**
\brief  ExistEBI - 


\return cond - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistEBI"

logical db_RootBase :: ExistEBI (acb *acbptr )
{


  return(NO);
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

logical db_RootBase :: ExistWorkspace (char *names )
{
 


  return(NO);
}

/******************************************************************************/
/**
\brief  Flush - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical db_RootBase :: Flush ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  FlushCluster - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushCluster"

logical db_RootBase :: FlushCluster (acb *acbptr )
{


  return(YES);

}

/******************************************************************************/
/**
\brief  FlushClusterPool - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical db_RootBase :: FlushClusterPool ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  GenerateServerEvent - 


\return term - Termination code

\param  ev_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateServerEvent"

logical db_RootBase :: GenerateServerEvent (EntryEvent *ev_ptr )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  GetDataVersion - 


\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataVersion"

int16 db_RootBase :: GetDataVersion ( )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  GetEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

EBI *db_RootBase :: GetEBI (acb *acbptr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetEntryHeader - 


\return iehptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryHeader"

ieh *db_RootBase :: GetEntryHeader (acb *acbptr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetFirstEBNumber - 


\return entnr - 

\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFirstEBNumber"

EB_Number db_RootBase :: GetFirstEBNumber (int16 mbnumber )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetLastEBNumber - 


\return entnr - 

\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastEBNumber"

EB_Number db_RootBase :: GetLastEBNumber (int16 mbnumber )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetMBCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBCount"

int32 db_RootBase :: GetMBCount ( )
{


  return(0);
}

/******************************************************************************/
/**
\brief  GetMBNumber - 


\return mbnumber - MainBase number

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBNumber"

int16 db_RootBase :: GetMBNumber (EB_Number entnr )
{

  return (0);

}

/******************************************************************************/
/**
\brief  GetRBType - 


\return rbtype - 

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRBType"

RootBase_Types __cdecl db_RootBase :: GetRBType (char *cpath )
{
  RootBase_Types  rb_type = RBT_ODABA;
  char           *rb_types[] = {"ODABA", "ORACLE", "XML", "MS_SQL", "ODBC"};
  char           *value;

  if ( value = GetSysVariable("DATABASE_TYPE") )
    rb_type = (RootBase_Types)STRToPosition(value,
                          sizeof(rb_types)/sizeof(rb_types[1]),rb_types);

  return(rb_type);
}

/******************************************************************************/
/**
\brief  GetRootBase - 


\return rootbase - 

\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootBase"

db_RootBase *db_RootBase :: GetRootBase (uint8 wslevel )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetWorkspace - 


\return ws_entry - 

\param  lindx0 - 
\param  user_name - 
\param  refresh - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspace"

SDB_Workspace *db_RootBase :: GetWorkspace (int32 lindx0, char *user_name, logical refresh )
{



  return(NULL);
}

/******************************************************************************/
/**
\brief  GetWorkspaceNumber - 


\return wsnumber - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceNumber"

int32 db_RootBase :: GetWorkspaceNumber (char *names )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceNumber"

int32 db_RootBase :: GetWorkspaceNumber ( )
{

  return ( IsWorkspace() ? ((Workspace *)this)->get_ws_number() 
                         : 0                                    );

}

/******************************************************************************/
/**
\brief  Get_Length - 


\return entlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Length"

int32 db_RootBase :: Get_Length (acb *acbptr )
{


  return(UNDEF);

}

/******************************************************************************/
/**
\brief  Get_Mod - 


\return modcnt - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Mod"

uint8 db_RootBase :: Get_Mod (acb *acbptr )
{


  return(UNDEF);

}

/******************************************************************************/
/**
\brief  IgnoreSharedRB - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IgnoreSharedRB"

void db_RootBase :: IgnoreSharedRB ( )
{



}

/******************************************************************************/
/**
\brief  InitDataArea - 


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

logical db_RootBase :: InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  InitKeyCache - 


\return term - Termination code

\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitKeyCache"

logical db_RootBase :: InitKeyCache (ACObject *obhandle )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  InitMainBase - 


\return term - Termination code

\param  mbnumber - MainBase number
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMainBase"

logical db_RootBase :: InitMainBase (int16 mbnumber, char *filename, int32 dasize, char *server, EB_Header *headerpt, logical pindep )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  InitSubBase - 


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

logical db_RootBase :: InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  InitWSList - 


\return term - Termination code

\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitWSList"

logical db_RootBase :: InitWSList (DBHandle *dbhandle )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  IntGetEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntGetEBI"

EBI *db_RootBase :: IntGetEBI (acb *acbptr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  IntPutEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntPutEBI"

EBI *db_RootBase :: IntPutEBI (acb *acbptr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  IsODABARootBase - 


\return eb_rootbase - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsODABARootBase"

eb_RootBase *db_RootBase :: IsODABARootBase ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  IsPIF - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPIF"

logical db_RootBase :: IsPIF ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  IsWorkspace - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWorkspace"

logical db_RootBase :: IsWorkspace ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  IsXMLBase - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsXMLBase"

logical db_RootBase :: IsXMLBase ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Locate - 


\return area - 

\param  acbptr - 
\param  entlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *db_RootBase :: Locate (acb *acbptr, int32 entlen )
{


  return(NULL);

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical db_RootBase :: Lock (acb *acbptr, logical wait )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  LockInternal - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical db_RootBase :: LockInternal (acb *acbptr, logical wait )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  LockKey - 


\return term - Termination code

\param  entnr - 
\param  db_index - 
\param  keyptr - 
\param  owner_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockKey"

logical db_RootBase :: LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{

  return( key_cache ? key_cache->LockKey(entnr,db_index,keyptr,owner_id) : NO);

}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  path - 
\param  outopt - 
\param  exclusive - 
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical db_RootBase :: Open (char *path, logical outopt, logical exclusive, char sysenv )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  OpenWorkspace - 


\return workspace - 

\param  dbhandle - Database handle
\param  names - 
\param  user_name - 
\param  cpath - Complete path
\param  exclusive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWorkspace"

Workspace *db_RootBase :: OpenWorkspace (DBHandle *dbhandle, char *names, char *user_name, char *cpath, logical exclusive )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  Provide - 


\return term - Termination code

\param  cpath - Complete path
\param  accopt - Access mode
\param  exclusive - 
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

logical db_RootBase :: Provide (char *cpath, PIACC accopt, logical exclusive, char sysenv )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  ProvideWSEntry - 


\return term - Termination code

\param  acbptr - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideWSEntry"

logical db_RootBase :: ProvideWSEntry (acb *acbptr, logical del_dep )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  ProvideWorkspace - 


\return cpath - Complete path

\param  names - 
\param  user_name - 
\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideWorkspace"

char *db_RootBase :: ProvideWorkspace (char *names, char *user_name, char *cpath )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  RBType - 


\return rbtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RBType"

RootBase_Types db_RootBase :: RBType ( )
{
  RootBase_Types  rb_type = RBT_ODABA;
  char           *rb_types[] = {"ODABA", "ORACLE", "XML", "MS_SQL", "ODBC"};
  char           *value;

  return(RBT_undefined);

}

/******************************************************************************/
/**
\brief  ReleaseEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

logical db_RootBase :: ReleaseEntry (acb *acbptr )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  ReleaseWSEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseWSEntry"

logical db_RootBase :: ReleaseWSEntry (acb *acbptr )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  RemoveWorkspace - 


\return term - Termination code

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveWorkspace"

logical db_RootBase :: RemoveWorkspace (char *names )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical db_RootBase :: Reserve (acb *acbptr, logical wait )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  ReserveEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

logical db_RootBase :: ReserveEntry (acb *acbptr )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  ReserveWSEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveWSEntry"

logical db_RootBase :: ReserveWSEntry (acb *acbptr )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  SaveBuffer - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveBuffer"

logical db_RootBase :: SaveBuffer ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Undelete - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Undelete"

logical db_RootBase :: Undelete (acb *acbptr )
{


  return(YES);

}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical db_RootBase :: Unlock (acb *acbptr )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  UnlockInternal - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical db_RootBase :: UnlockInternal (acb *acbptr )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  UnlockKey - 


\return term - Termination code

\param  entnr - 
\param  db_index - 
\param  keyptr - 
\param  owner_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockKey"

logical db_RootBase :: UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{

  return ( key_cache ? key_cache->UnlockKey(entnr,db_index,keyptr,owner_id) : YES );

}

/******************************************************************************/
/**
\brief  Update - 


\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical db_RootBase :: Update (acb *acbptr, int32 entlen, int32 offset )
{


  return(YES);

}

/******************************************************************************/
/**
\brief  db_RootBase - 



\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "db_RootBase"

     db_RootBase :: db_RootBase (logical netopt )
                     : ReferenceObject (NO),
  key_cache(NULL),
  root_path(NULL),
  net_option(netopt),
  level(UNDEF),
  temp_main(AUTO)

{



}

/******************************************************************************/
/**
\brief  ~db_RootBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~db_RootBase"

     db_RootBase :: ~db_RootBase ( )
{

  delete key_cache;
  key_cache = NULL;
  
  Close();
  
  if ( root_path )
    free(root_path);
  root_path = NULL;


}


