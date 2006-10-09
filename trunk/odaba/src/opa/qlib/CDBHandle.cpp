/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CDBHandle

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

\date     $Date: 2006/08/26 12:56:09,60 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CDBHandle"

#include  <popa7.h>
#include  <sofifct.h>
#include  <sCDBHandle.hpp>
#include  <sCDictionary.hpp>
#include  <sCS_Connection.hpp>
#include  <sClientConnection.hpp>
#include  <sDictionary.hpp>
#include  <sODABAClient.hpp>
#include  <sCDBHandle.hpp>


/******************************************************************************/
/**
\brief  ActivateShadowBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateShadowBase"

logical CDBHandle :: ActivateShadowBase ( )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      if ( db_handle )
        CloseObject();
      DBHandle::CloseDBHandle();  
      
      if ( cdictionary )
      {
        LockSendParms().Fill();
        if ( CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ActivateShadowBase_ci) ||
             Get_rec_result()[0].GetUChar() )
          term = YES;
        UnlockSendParms();
        SetServerPointer((void *)NULL); 
      }
    }
    UninitHandle();
    cdictionary = NULL;
    dictionary  = NULL;
  }
  
  return(term);  

#else             // server version

  ((SC_Database *)cso_ptr)->SetClientObject(0);
  term = ((SC_Database *)cso_ptr)->ActivateShadowBase();
  
  result->Fill(term);

  return(NO);

#endif

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

logical CDBHandle :: BackupDB (char *target )
{
  logical   term = YES;
BEGINSEQ
  SDBEV1("BackupDB",UNDEF)
  SDBERR(381)
RECOVER

ENDSEQ
  return(YES);
}

/******************************************************************************/
/**
\brief  CDBHandle - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
\param  online_version - 
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CDBHandle"

     CDBHandle :: CDBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical online_version, uint16 version_nr, char sysenv )
                     : DBHandle (dict_ptr,cpath,accopt,YES,version_nr,sysenv),
CACObject (dict_ptr->GetClientDictionary()->IsValid() 
? dict_ptr->GetClientDictionary()->get_csconnection() 
: NULL),
ACObject(),
  cdictionary(dict_ptr->GetClientDictionary()),
  server_path(NULL),
  schema_version(CUR_VERSION),
  system_version(CUR_VERSION)

{

BEGINSEQ
#ifndef IF_Class  // client version

  InitHandle(NO);
  if ( !csconnection )                                 
    SDBSET(517)
  else
  {
    ACObject::Initialize(this,accopt,version_nr);
    LockSendParms().Fill((CS_Handle *)cdictionary,cpath,(int32)accopt,online_version,version_nr,sysenv);
    SetClientPointer(this); 
    
    if ( CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_CDBHandle_ci0) )
                                                     ERROR
    if ( !Get_rec_result()[0].GetUChar() )
      SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
    CreateContext();  
    if ( context && context->ExecuteAction(DBP_Open) )
      CloseDBHandle();
    UnlockSendParms();
  }
  if ( context )
    context->ExecuteAction(DBO_Opened);
  net_option = YES;

#else             // server version

  SC_Database *sc_db;
  CS_Handle   *handle = parms->GetHandle();
  
  sc_db = ((SC_Dictionary *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideDatabase(
                  handle->GetClientObject(),
                  (*parms)[1].GetString(),                                  // cpath
                  (PIACC)(*parms)[2].GetLong(connection->get_conversion()), // accopt
                  (*parms)[3].GetUChar(),                                   // online_version
                  (*parms)[4].GetUShort(connection->get_conversion()),      // version_nr
                  (*parms)[5].GetUChar()                             );     // sysenv
   
  handle->SetServerPointer(sc_db);
  *result->GetHandle() = *handle;
  result->Fill((logical)!sc_db);

  return(NO);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i00 - 



\param  cs_connection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CDBHandle"

     CDBHandle :: CDBHandle (CS_Connection *cs_connection )
                     : DBHandle (),
CACObject (cs_connection),
ACObject (), 
  cdictionary(NULL),
  server_path(NULL),
  schema_version(CUR_VERSION),
  system_version(CUR_VERSION)
{



}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CDBHandle"

     CDBHandle :: CDBHandle ( )
                     : DBHandle (),
CACObject (),
ACObject (), 
  cdictionary(NULL),
  server_path(NULL),
  schema_version(CUR_VERSION),
  system_version(CUR_VERSION)
{



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

logical CDBHandle :: ChangeRecovery (RecoveryType rec_type, char *rec_path )
{
  logical      term = YES;
#ifndef IF_Class  // client version
  
  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill((int32)rec_type,rec_path);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ChangeRecovery_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);

#else             // server version
  
  term = ((SC_Database *)cso_ptr)->ChangeRecovery(
                  (RecoveryType)(*parms)[0].GetLong(connection->get_conversion()), // rec_type
                  (*parms)[1].GetString()      );                                  // rec_path
  result->Fill(term);

  return(NO);

#endif

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

logical CDBHandle :: CheckDB (CheckOptions check_opts, char *resnames )
{
  logical   term = YES;
BEGINSEQ
  SDBEV1("CheckDB",UNDEF)
  SDBERR(381)
RECOVER

ENDSEQ
  return(YES);
}

/******************************************************************************/
/**
\brief  CheckLicence - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci1 - 



\param  applname_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical CDBHandle :: CheckLicence (char *applname_w )
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      if ( applname_w )  
        SetSysVariable("__APPLICATION_NAME",applname_w);
      
      LockSendParms().Fill(applname_w);
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_CheckLicence_ci1) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->CheckLicence(
                  (*parms)[0].GetString()
          );
   
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ci2 - 



\param  lic_owner - 
\param  lic_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical CDBHandle :: CheckLicence (char *lic_owner, char *lic_number )
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(lic_owner,lic_number);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_CheckLicence_ci2) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->CheckLicence(
                  (*parms)[0].GetString(),
                  (*parms)[1].GetString()
          );
   
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CloseDBHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDBHandle"

logical CDBHandle :: CloseDBHandle ( )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection || CConnection()->Check() )                                 
      SDBSET(517)
    else
    {
      if ( db_handle )
        CloseObject();
      DBHandle::CloseDBHandle();  
      
      if ( cdictionary && GetServerObject() )
      {
        LockSendParms().Fill();
        if ( CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_CloseDBHandle_ci) ||
             Get_rec_result()[0].GetUChar() )
          term = YES;
        UnlockSendParms();
        SetServerPointer((void *)NULL); 
      }
    }
    UninitHandle();
    cdictionary = NULL;
    dictionary  = NULL;
  }
  
  return(term);  

#else             // server version

  ((SC_Database *)cso_ptr)->SetClientObject(0);
  term = ((SC_Database *)cso_ptr)->Remove();
  
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CloseRecovery - Close recovery file



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseRecovery"

logical CDBHandle :: CloseRecovery ( )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_CloseRecovery_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);

#else             // server version

  term = ((SC_Database *)cso_ptr)->CloseRecovery();   
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CloseWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseWorkspace"

logical CDBHandle :: CloseWorkspace ( )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_CloseWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->CloseWorkspace();
  result->Fill(term);

  return(NO);
  
#endif

}

/******************************************************************************/
/**
\brief  ConsolidateWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateWorkspace"

logical CDBHandle :: ConsolidateWorkspace ( )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ConsolidateWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->ConsolidateWorkspace();
  result->Fill(term);

  return(NO);
  
#endif

}

/******************************************************************************/
/**
\brief  DeactivateShadowBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateShadowBase"

logical CDBHandle :: DeactivateShadowBase ( )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      if ( db_handle )
        CloseObject();
      DBHandle::CloseDBHandle();  
      
      if ( cdictionary )
      {
        LockSendParms().Fill();
        if ( CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_DeactivateShadowBase_ci) ||
             Get_rec_result()[0].GetUChar() )
          term = YES;
        UnlockSendParms();
        SetServerPointer((void *)NULL); 
      }
    }
    UninitHandle();
    cdictionary = NULL;
    dictionary  = NULL;
  }
  
  return(term);  

#else             // server version

  ((SC_Database *)cso_ptr)->SetClientObject(0);
  term = ((SC_Database *)cso_ptr)->DeactivateShadowBase();
  
  result->Fill(term);

  return(NO);

#endif

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

logical CDBHandle :: DeleteWorkspace (char *names, char *user_name )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(names,user_name);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_DeleteWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->DeleteWorkspace(
                  (*parms)[0].GetString(),                              // work space name
                  (*parms)[1].GetString()                               // user name
           ); 
  result->Fill(term);

  return(NO);
  
#endif
  return(term);
}

/******************************************************************************/
/**
\brief  DisableWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableWorkspace"

logical CDBHandle :: DisableWorkspace ( )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_DisableWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->DisableWorkspace();
  result->Fill(term);

  return(NO);
  
#endif

}

/******************************************************************************/
/**
\brief  DiscardWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiscardWorkspace"

logical CDBHandle :: DiscardWorkspace ( )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_DiscardWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->DiscardWorkspace();
  result->Fill(term);

  return(NO);
  
#endif

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

logical CDBHandle :: EnableWorkspace (char *cpath )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(cpath);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_EnableWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->EnableWorkspace(
                  (*parms)[0].GetString()                               // filename
           ); 
  result->Fill(term);

  return(NO);
  
#endif

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

logical CDBHandle :: ExecDBCtxFunc (char *fnames, char *w_parms )
{
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(fnames,w_parms);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ExecDBCtxFunc_ci) )
        if ( !(term = Get_rec_result()[0].GetUChar()) )
        {
          set_result_string(Get_rec_result()[1].GetString(),UNDEF);
          term = DBHandle::ExecDBCtxFunc(fnames,w_parms);  // Client kann Ergebnis überschreiben
        }
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  SC_Database   *sc_db      = ((SC_Database *)cso_ptr);
  char          *result_str = NULL;
  
  if ( !(term =  sc_db->ExecuteDatabaseAction(
                     (*parms)[0].GetString(),                               // fnames
                     (*parms)[1].GetString()          )) )                 // w_parms
    result_str = ((DatabaseHandle *)sc_db)->GetActionResult();
            
  result->Fill(term,result_str);

  return(NO);
  
#endif

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

logical CDBHandle :: ExistWorkspace (char *names )
{
  logical                 cond = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(names);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ExistWorkspace_ci) )
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(cond);

#else             // server version
  
  cond =  ((SC_Database *)cso_ptr)->ExistWorkspace(
                  (*parms)[0].GetString()                               // filename
           ); 
  result->Fill(cond);

  return(NO);
  
#endif
  return(cond);
}

/******************************************************************************/
/**
\brief  FlushClusterPool - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical CDBHandle :: FlushClusterPool ( )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_FlushClusterPool_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term = ((SC_Database *)cso_ptr)->FlushClusterPool();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetClientDBHandle - Provide client handle



\return cdbhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientDBHandle"

CDBHandle *CDBHandle :: GetClientDBHandle ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetDatabaseID - 



\return db_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDatabaseID"

int32 CDBHandle :: GetDatabaseID ( )
{
  int32       db_id = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetDatabaseID_ci) )
        db_id = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }    
  return(db_id);

#else             // server version
  
  db_id = ((SC_Database *)cso_ptr)->GetDatabaseID();    // database id
  result->Fill(db_id);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetNewTypeID - Get next available type id



\return sid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewTypeID"

int16 CDBHandle :: GetNewTypeID ( )
{
  int16   sid = UNDEF;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetNewTypeID_cidb) )
        sid = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(sid);
  
#else             // server version
  
  sid =  ((SC_Database *)cso_ptr)->GetNewTypeID();
   
  result->Fill(sid);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetPath - Get path for the opened database



\return dbpath - Complete database path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPath"

char *CDBHandle :: GetPath ( )
{
  char       *path = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      if ( !(path = server_path) )
      {
        LockSendParms().Fill();
    
        if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetPath_ci) )
          if ( path = Get_rec_result()[0].GetString() )
          {
            server_path = new char[strlen(path)+1];
            path = strcpy(server_path,path);
          }
        UnlockSendParms();
      }
    }
  }  
  return(path);

#else             // server version
  
  path = ((SC_Database *)cso_ptr)->GetPath();
  result->Fill(path);

  return(NO);

#endif

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

char *CDBHandle :: GetRecoveryFile (uint16 recnum )
{
  char       *path = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(recnum);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetRecoveryFile_ci) )
        if ( path = Get_rec_result()[0].GetString() )
          path = strncpy(return_buffer,path,RET_BUF_LEN);
      UnlockSendParms();
    }
  }    
  return(path);

#else             // server version
  
  path = ((SC_Database *)cso_ptr)->GetRecoveryFile(
                  (*parms)[0].GetUShort(connection->get_conversion()) );    // recnum
  result->Fill(path);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetRecoveryNum - Provide number for current recovery file



\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryNum"

uint16 CDBHandle :: GetRecoveryNum ( )
{
  uint16      recnum = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetRecoveryNum_ci) )
        recnum = Get_rec_result()[0].GetUShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(recnum);

#else             // server version

  recnum = ((SC_Database *)cso_ptr)->GetRecoveryNum();
  result->Fill(recnum,connection->get_conversion());

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetRecoveryPath - Provide path for recovery folder



\return recpath - Recovery path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryPath"

char *CDBHandle :: GetRecoveryPath ( )
{
  char       *path = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetRecoveryPath_ci) )
        if ( path = Get_rec_result()[0].GetString() )
          path = strncpy(return_buffer,path,RET_BUF_LEN);
      UnlockSendParms();
    }
  }    
  return(path);

#else             // server version
  
  path = ((SC_Database *)cso_ptr)->GetRecoveryPath();
  result->Fill(path);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetRecoveryStartNumber - 



\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryStartNumber"

uint16 CDBHandle :: GetRecoveryStartNumber ( )
{
  uint16      recnum = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetRecoveryStartNumber_ci) )
        recnum = Get_rec_result()[0].GetUShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(recnum);

#else             // server version

  recnum = ((SC_Database *)cso_ptr)->GetRecoveryStartNumber();
  result->Fill(recnum,connection->get_conversion());

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetRecoveryType - 



\return rec_type - Type of recovery support

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryType"

RecoveryType CDBHandle :: GetRecoveryType ( )
{
  RecoveryType   rec_type = RECOVERY_none;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetRecoveryType_ci) )
        rec_type = (RecoveryType)Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(rec_type);
  
#else             // server version

  rec_type = ((SC_Database *)cso_ptr)->GetRecoveryType();
  result->Fill((int32)rec_type);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetSchemaVersion - 



\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSchemaVersion"

uint16 CDBHandle :: GetSchemaVersion ( )
{
  uint16      version = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( schema_version == CUR_VERSION )
    {  
      if ( !csconnection )                                 
        SDBSET(517)
      else
      {
        LockSendParms().Fill();
    
        if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetSchemaVersion_ci) )
          schema_version = Get_rec_result()[0].GetUShort(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
  }
  return(schema_version);
  
#else             // server version
  
  version = ((SC_Database *)cso_ptr)->GetSchemaVersion();
  result->Fill(version,connection->get_conversion());

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetSystemVersion - 



\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemVersion"

uint16 CDBHandle :: GetSystemVersion ( )
{
  uint16      version = UNDEF;
#ifndef IF_Class  // client version

  version = system_version;
  if ( IsValid() && system_version == CUR_VERSION )
  {
    version = UNDEF;
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetSystemVersion_ci) )
        version = system_version = Get_rec_result()[0].GetUShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(version);
  
#else             // server version
  
  version = ((DatabaseHandle *)(SC_Database *)cso_ptr)->GetSystemVersion();
  result->Fill(version,connection->get_conversion());

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  GetVersionString - 



\return version_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionString"

char *CDBHandle :: GetVersionString ( )
{
  char        *version_string = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetVersionString_ci) )
        if ( version_string = Get_rec_result()[0].GetString() )
          version_string = strncpy(return_buffer,version_string,RET_BUF_LEN);
      UnlockSendParms();
    }
  }
  return(version_string);
  
#else             // server version
  
  version_string = ((SC_Database *)cso_ptr)->GetVersionString();
  result->Fill(version_string);

  return(NO);

#endif

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

char *CDBHandle :: GetWorkspace (char *ws_root, int32 lindx0, char *user_name, char *names, logical refresh, char *ws_info )
{
  char                   *wsnames = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(ws_root,lindx0,user_name,names,refresh);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_GetWorkspace_ci) )
      {
        if ( wsnames = Get_rec_result()[0].GetString() )
        {
          nstring = wsnames;
          wsnames = nstring;
          if ( names )
            strncpy(names,wsnames,128);
        }
        if ( ws_info && Get_rec_result()[1].GetString() )
          strncpy(ws_info,Get_rec_result()[1].GetString(),255);
      }
      UnlockSendParms();
    }
  }  
  return(wsnames);

#else             // server version
  
  char       ws_info[256];
  
  wsnames =  ((SC_Database *)cso_ptr)->GetWorkspace(
                  (*parms)[0].GetString(),                              // work space root
                  (*parms)[1].GetLong(connection->get_conversion()),    // work space index                  
                  (*parms)[2].GetString(),                              // user name
                  (*parms)[3].GetString(),                              // work space name
                  (*parms)[4].GetUChar(),                               // refresh
                  ws_info
           ); 
  result->Fill(wsnames,ws_info);

  return(NO);
  
#endif

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
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDataArea"

logical CDBHandle :: InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize )
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(mbnumber,sbnumber,danumber,filename,dasize);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_InitDataArea_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->InitDataArea(
                  (*parms)[0].GetShort(connection->get_conversion()),   // mbnumber
                  (*parms)[1].GetShort(connection->get_conversion()),   // sbnumber
                  (*parms)[2].GetShort(connection->get_conversion()),   // danumber
                  (*parms)[3].GetString(),                              // filename
                  (*parms)[4].GetLong(connection->get_conversion())  ); // dasize
  result->Fill(term);

  return(NO);

#endif

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
\param  largedb - Indicates a large database
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMainBase"

logical CDBHandle :: InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize, logical largedb, logical pindep )
{
  logical    term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(mbnumber,filename,lowEBN,highEBN,dasize,largedb,pindep);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_InitSubBase_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->InitMainBase(
                  (*parms)[0].GetShort(connection->get_conversion()),   // mbnumber
                  (*parms)[1].GetString(),                              // filename
                  (*parms)[2].GetUShort(connection->get_conversion()),  // lowEBN
                  (*parms)[3].GetUShort(connection->get_conversion()),  // highEBN
                  (*parms)[4].GetLong(connection->get_conversion()),    // dasize
                  (*parms)[5].GetUChar(),                               // largedb
                  (*parms)[5].GetUChar()  );                            // pindep
  result->Fill(term);

  return(NO);

#endif

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

logical CDBHandle :: InitRecovery (char *recpath, uint16 recnum )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(recpath,recnum);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_InitRecovery_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
#else             // server version
  
  term = ((SC_Database *)cso_ptr)->InitRecovery(
                  (*parms)[0].GetString(),                               // recpath
                  (*parms)[1].GetUShort(connection->get_conversion()) ); // recnum
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  InitSubBase - Initialise SubBase



\return term - Termination code

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSubBase"

logical CDBHandle :: InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize )
{
  logical    term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(mbnumber,sbnumber,filename,dasize);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_InitSubBase_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->InitSubBase(
                  (*parms)[0].GetShort(connection->get_conversion()),   // mbnumber
                  (*parms)[1].GetShort(connection->get_conversion()),   // sbnumber
                  (*parms)[2].GetString(),                              // filename
                  (*parms)[3].GetLong(connection->get_conversion())  ); // dasize
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  IsLicenced - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLicenced"

logical CDBHandle :: IsLicenced ( )
{
  logical    cond = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_IsLicenced_ci) )
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(cond);
  
#else             // server version
  
  cond = ((SC_Database *)cso_ptr)->IsLicenced();
  result->Fill(cond);

  return(NO);

#endif

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

logical CDBHandle :: LocateWorkspace (char *names )
{
  logical                 cond = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(names);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_LocateWorkspace_ci) )
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(cond);

#else             // server version
  
  cond =  ((SC_Database *)cso_ptr)->LocateWorkspace(
                  (*parms)[0].GetString()                               // work space name
          ); 
  result->Fill(cond);

  return(NO);
  
#endif

}

/******************************************************************************/
/**
\brief  OpenRecovery - Open recovery file



\return term - Termination code

\param  userinfo - Area for application recovery information
\param  uilen - Length of application data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRecovery"

logical CDBHandle :: OpenRecovery (char *userinfo, int16 uilen )
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(userinfo,(uint16)uilen);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_OpenRecovery_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);

#else             // server version
  
  term = ((SC_Database *)cso_ptr)->OpenRecovery(
                  (char *)(*parms)[0].GetBuffer(),          // userinfo
                  (int16)(*parms)[0].GetCurSize()  );       // uilen
  result->Fill(term);

  return(NO);

#endif

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

logical CDBHandle :: OpenWorkspace (char *names, char *user_name, logical exclusive, char *cpath_w )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(names,user_name,exclusive,cpath_w);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_OpenWorkspace_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }  
  return(term);

#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->OpenWorkspace(
                  (*parms)[0].GetString(),                              // work space name
                  (*parms)[1].GetString(),                              // user name
                  (*parms)[2].GetUChar(),                               // exclusive
                  (*parms)[3].GetString()                               // work space location
           ); 
  result->Fill(term);

  return(NO);
  
#endif
  return(term);
}

/******************************************************************************/
/**
\brief  ResetLastSchemaVersion - 



\return cond - 

\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastSchemaVersion"

logical CDBHandle :: ResetLastSchemaVersion (logical reset_opt )
{
  logical    term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(reset_opt);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ResetLastSchemaVersion_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term = ((SC_Database *)cso_ptr)->ResetLastSchemaVersion(
                  (*parms)[0].GetUChar()                                // reset_opt
         );
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ResetLastVersion - 



\return cond - 

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastVersion"

logical CDBHandle :: ResetLastVersion (uint16 version_nr )
{
  logical    term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(version_nr);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_ResetLastVersion_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term = ((SC_Database *)cso_ptr)->ResetLastVersion();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  RestoreDB - 



\return term - Termination code

\param  target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical CDBHandle :: RestoreDB (char *target )
{
  logical   term = YES;
BEGINSEQ
  SDBEV1("RestoreDB",UNDEF)
  SDBERR(381)
RECOVER

ENDSEQ
  return(YES);
}

/******************************************************************************/
/**
\brief  SetupTypeID - Update type id



\return term - Termination code

\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTypeID"

logical CDBHandle :: SetupTypeID (int16 sid )
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(sid);
    
      if ( !CConnection()->SendCSMessage(this,S_CDBHandle,SF_CDBHandle_SetupTypeID_cidb) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_Database *)cso_ptr)->SetupTypeID(
                  (*parms)[0].GetShort(connection->get_conversion())
              );
   
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ~CDBHandle - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CDBHandle"

     CDBHandle :: ~CDBHandle ( )
{

  if ( dictionary )
    CloseDBHandle();
  
  delete server_path;
  server_path = NULL;

}


