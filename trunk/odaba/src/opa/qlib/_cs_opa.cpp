/******************************** Interface Declaration *****************************************************/
/**
\class OPA

\brief Function Source Code for Client Server Interface

\date $Date: 2006/07/24 14:29:06,89 $
\dbsource l:\opa\opa.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_OPA"

#include  <popa7.h>

#include  <_cs_OPA.h>
#include  <sServerConnection.hpp>
#include  <sCSInstanceList.hpp>


#undef     MOD_ID
#define    MOD_ID  "CACObject_CACObject_ci"

logical CACObject_CACObject_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{

#ifndef IF_Class  // client version
  
  CDBHandle  *cdbhandle = dbhandle->GetClientDBHandle();
  
  if ( !csconnection )                                 
    SDBSET(517)
  else
  {
    InitHandle();
    LockSendParms().Fill((CS_Handle *)cdbhandle,(int32)accopt,version_nr);
    
    if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_CACObject_ci) )
    {
      if ( !Get_rec_result()[0].GetUChar() )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        CreateContext(); 
      }
    }
    UnlockSendParms();
  }
#else             // server version

  SC_DBObject *sc_dbo;
  CS_Handle   *handle = parms->GetHandle();
  
  sc_dbo = ((SC_Database *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideDBObject(
                  handle->GetClientObject(),
                  (PIACC)(*parms)[1].GetLong(connection->get_conversion()), // accopt
                  (*parms)[2].GetUShort(connection->get_conversion()) );    // version_nr
   
  handle->SetServerPointer(sc_dbo);
  *result->GetHandle() = *handle;
  result->Fill((logical)!sc_dbo);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_CACObject_ci1"

logical CACObject_CACObject_ci1                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{


#ifndef IF_Class  // client version

  CACObject  *cobhandle = obhandle->GetClientACObject();
  
  if ( !csconnection )                                 
    SDBSET(517)
  else
  {
    InitHandle();
    LockSendParms().Fill((CS_Handle *)cobhandle,objid,(int32)accopt,version_nr);
    
    if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_CACObject_ci1) )
    {
      if ( !Get_rec_result()[0].GetUChar() )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        CreateContext(); 
      }
    }
    UnlockSendParms();
  }
#else             // server version

  SC_DBObject *sc_dbo;
  CS_Handle   *handle = parms->GetHandle();
  
  sc_dbo = ((SC_DBObject *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideDBObject(
                  handle->GetClientObject(),
                  (*parms)[1].GetLong(connection->get_conversion()),        // objid
                  (PIACC)(*parms)[2].GetLong(connection->get_conversion()), // accopt
                  (*parms)[3].GetUShort(connection->get_conversion()) );    // version_nr
   
  handle->SetServerPointer(sc_dbo);
  *result->GetHandle() = *handle;
  result->Fill((logical)!sc_dbo);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_CACObject_ci2"

logical CACObject_CACObject_ci2                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{

#ifndef IF_Class  // client version

  CACObject  *cobhandle = obhandle->GetClientACObject();
  
  if ( !csconnection )                                 
    SDBSET(517)
  else
  {
    InitHandle();
    LockSendParms().Fill((CS_Handle *)cobhandle,objname,(int32)accopt,version_nr);
    
    if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_CACObject_ci2) )
    {
      if ( !Get_rec_result()[0].GetUChar() )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        CreateContext(); 
      }
    }
    UnlockSendParms();
  }
#else             // server version

  SC_DBObject *sc_dbo;
  CS_Handle   *handle = parms->GetHandle();
  
  sc_dbo = ((SC_DBObject *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideDBObject(
                  handle->GetClientObject(),
                  (*parms)[1].GetString(),                                  // objname
                  (PIACC)(*parms)[2].GetLong(connection->get_conversion()), // accopt
                  (*parms)[3].GetUShort(connection->get_conversion()) );    // version_nr
   
  handle->SetServerPointer(sc_dbo);
  *result->GetHandle() = *handle;
  result->Fill((logical)!sc_dbo);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_ChangeTimeStamp_ci"

logical CACObject_ChangeTimeStamp_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(version_nr,timestamp);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_ChangeTimeStamp_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->ChangeTimeStamp(
                  (*parms)[0].GetUShort(connection->get_conversion()),
                  (*parms)[1].GetTimestamp(connection->get_conversion())
          );
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_CloseObject_ci"

logical CACObject_CloseObject_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version
  DLL(CNode)  *nodelist;
  CNode       *cnodeptr;
  ACObject    *objptr;

  if ( IsValid() )
  {
    ACObject::CloseObject();
  
    if ( nodelist = topnode_list )
    {
      topnode_list = NULL;
      while ( cnodeptr = nodelist->RemoveTail() )
      {
        cnodeptr->Switch(AUTO);
        delete cnodeptr;
      }
      delete nodelist;
    }
    while ( objptr = object_list->GetTail() )
      delete objptr;

    if ( (ACObject *)db_handle != (ACObject *)this && GetServerObject() )
    {
      LockSendParms().Fill();
      CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_CloseObject_ci);
      UnlockSendParms();
      UninitHandle();
    }
  }
  
  return(term);
  
#else             // server version
  
  ((SC_DBObject *)cso_ptr)->SetClientObject(0);
  ((SC_DBObject *)cso_ptr)->Remove();
   
  result->Fill();

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_DeleteExtent_ci"

logical CACObject_DeleteExtent_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(extnames);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_DeleteExtent_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->DeleteExtent(
                  (*parms)[0].GetString()
          );
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_DeleteExtentRef_ci"

logical CACObject_DeleteExtentRef_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(extnames);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_DeleteExtentRef_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->DeleteExtent(
                  (*parms)[0].GetString()
          );
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_ExecObjCtxFunc_ci"

logical CACObject_ExecObjCtxFunc_ci                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_ExecObjCtxFunc_ci) )
        if ( !(term = Get_rec_result()[0].GetUChar()) )
        {
          set_result_string(Get_rec_result()[1].GetString(),UNDEF);
          term = ACObject::ExecObjCtxFunc(fnames,w_parms);  // Client kann Ergebnis überschreiben
        }
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_DBObject    *sc_dbo     = (SC_DBObject *)cso_ptr;
  char           *result_str = NULL;
  
  if ( !(term =  sc_dbo->ExecuteDBObjectAction(
                      (*parms)[0].GetString(),
                      (*parms)[0].GetString()   )) )
    result_str = sc_dbo->GetActionResult();
   
  result->Fill(term,result_str);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_ExtentExist_ci"

logical CACObject_ExtentExist_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 cond = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(extnames);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_ExtentExist_ci) )
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(cond);
  
#else             // server version
  
  cond =  ((SC_DBObject *)cso_ptr)->ExtentExist(
                  (*parms)[0].GetString()
          );
   
  result->Fill(cond);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_GetAccess_ci"

logical CACObject_GetAccess_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  PIACC       accmode = PI_Read;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_GetAccess_ci) )
        accmode = (PIACC)Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(accmode);
  
#else             // server version
  
  accmode = ((SC_DBObject *)cso_ptr)->GetAccess();
   
  result->Fill((int32)accmode);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_GetExtent_ci"

logical CACObject_GetExtent_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char       *extentnames = NULL;
  char       *results     = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(indx0);
    
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_GetExtent_ci) )
        if ( extentnames = (char *)Get_rec_result()[0].GetString() )
          results = set_result_string(extentnames,RET_STR_LEN);
      UnlockSendParms();
    }
  }
  return(results);
  
#else             // server version
  
  extentnames = ((SC_DBObject *)cso_ptr)->GetExtent(
                  (*parms)[0].GetLong(connection->get_conversion())
               );
   
  result->Fill(extentnames);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_GetModCount_ci"

logical CACObject_GetModCount_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int16        modcount = UNDEF;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill((int32)entnr.get_ebsnum());
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_GetModCount_ci) )
        modcount = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(modcount);
  
#else             // server version
  
  modcount = ((SC_DBObject *)cso_ptr)->GetExtInstModCount(
                  (*parms)[0].GetLong(connection->get_conversion())
               );
   
  result->Fill(modcount);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_GetTALevel_ci"

logical CACObject_GetTALevel_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int16       talevel = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_GetTALevel_ci) )
        talevel = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(talevel);
  
#else             // server version
  
  talevel = ((SC_DBObject *)cso_ptr)->GetTransactionLevel();
   
  result->Fill(talevel);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_GetTimeStamp_ci"

logical CACObject_GetTimeStamp_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  dttm   timestamp;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(version_nr);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_GetTimeStamp_ci) )
        timestamp = Get_rec_result()[0].GetTimestamp(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(timestamp);
  
#else             // server version
  
  timestamp = ((SC_DBObject *)cso_ptr)->GetTimeStamp(
                  (*parms)[0].GetUShort(connection->get_conversion())
              );
   
  result->Fill(timestamp);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_GetVersion_ci"

logical CACObject_GetVersion_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  uint16      version = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(timestamp);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_GetVersion_ci) )
        version = Get_rec_result()[0].GetUShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(version);
  
#else             // server version
  
  version = ((SC_DBObject *)cso_ptr)->GetVersion(
                  (*parms)[0].GetTimestamp(connection->get_conversion())
            );
   
  result->Fill(version);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_NewVersion_ci"

logical CACObject_NewVersion_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(timestamp,version_nr);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_NewVersion_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->NewVersion(
                  (*parms)[0].GetTimestamp(connection->get_conversion()),     // timestamp
                  (*parms)[1].GetUShort(connection->get_conversion())     );  // version_nr
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_SetOverload_ci"

logical CACObject_SetOverload_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     overload = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(overload_opt);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_SetOverload_ci) )
        overload = Get_rec_result()[0].GetUChar();
      ACObject::SetOverload(overload_opt);
      UnlockSendParms();
    }
  }
  return(overload);
  
#else             // server version
  
  overload = ((SC_DBObject *)cso_ptr)->SetOverload(
                     (*parms)[0].GetUChar()
                 );
   
  result->Fill(overload);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_SetUserDefinedIdentity_ci"

logical CACObject_SetUserDefinedIdentity_ci                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     userdefined_id = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(identity_opt);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_SetUserDefinedIdentity_ci) )
        userdefined_id = Get_rec_result()[0].GetUChar();
      ACObject::SetUserDefinedIdentity(userdefined_id);
      UnlockSendParms();
    }
  }
  return(userdefined_id);
  
#else             // server version
  
  userdefined_id = ((SC_DBObject *)cso_ptr)->SetOverload(
                     (*parms)[0].GetUChar()
                 );
   
  result->Fill(userdefined_id);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_SetVersion_ci0"

logical CACObject_SetVersion_ci0                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(version_nr);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_SetVersion_ci0) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->SetVersion(
                  (*parms)[0].GetUShort(connection->get_conversion())
          );
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_SetVersion_ci1"

logical CACObject_SetVersion_ci1                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(timestamp);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_SetVersion_ci1) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->SetVersion(
                  (*parms)[0].GetTimestamp(connection->get_conversion())
          );
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_SetVersion_ci2"

logical CACObject_SetVersion_ci2                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = NO;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(date.GetLongInt());
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_SetVersion_ci2) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  term =  ((SC_DBObject *)cso_ptr)->SetVersion(
                  dbdt((*parms)[0].GetLong(connection->get_conversion()))
          );
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_StartTA_ci"

logical CACObject_StartTA_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int16       talevel = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(ext_TA,w_maxnum);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_StartTA_ci) )
        talevel = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(talevel);
  
#else             // server version
  
  talevel = ((SC_DBObject *)cso_ptr)->BeginTransaction(
                  (*parms)[0].GetUChar(),
                  (*parms)[1].GetShort(connection->get_conversion())
            );
   
  result->Fill(talevel);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_StopTA_ci"

logical CACObject_StopTA_ci                                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(talevel,error_case_w);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_StopTA_ci) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  logical error_case = (*parms)[1].GetUChar();

  term =  error_case
          ? ((SC_DBObject *)cso_ptr)->RollBack((*parms)[0].GetShort(connection->get_conversion()))
          : ((SC_DBObject *)cso_ptr)->CommitTransaction((*parms)[0].GetShort(connection->get_conversion()));
   
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_UpdateTimestamp_ci"

logical CACObject_UpdateTimestamp_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    oldmode = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(timestamp_enabled);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_UpdateTimestamp_ci) )
        oldmode = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(oldmode);
  
#else             // server version
  
  oldmode =  ((SC_DBObject *)cso_ptr)->UpdateTimestamp(
                  (*parms)[0].GetUChar()
          );
   
  result->Fill(oldmode);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_VersionCount_ci"

logical CACObject_VersionCount_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int32        count = 0;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill();
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_VersionCount_ci) )
        count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(count);
  
#else             // server version
  
  count =  ((SC_DBObject *)cso_ptr)->VersionCount();
   
  result->Fill(count);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CACObject_VersionIntervall_ci"

logical CACObject_VersionIntervall_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  INTERVAL(dttm)   timeint;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                                 
      SDBSET(517)
    else
    {
      LockSendParms().Fill(version_nr);
      if ( !CConnection()->SendCSMessage(this,S_CACObject,SF_CACObject_VersionIntervall_ci) )
      {
        timeint.get_low()  = Get_rec_result()[0].GetTimestamp(csconnection->get_conversion());
        timeint.get_high() = Get_rec_result()[1].GetTimestamp(csconnection->get_conversion());
      }
      UnlockSendParms();
    }
  }
  return(timeint);
  
#else             // server version
  
  timeint = ((SC_DBObject *)cso_ptr)->VersionIntervall(
                  (*parms)[1].GetUShort(connection->get_conversion())
            );
   
  result->Fill(timeint.get_low(),timeint.get_high());

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CClient_BackupDB_ci"

logical CClient_BackupDB_ci                                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_CacheConnection_ci"

logical CClient_CacheConnection_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_CheckDB_ci"

logical CClient_CheckDB_ci                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_DictDisplay_ci"

logical CClient_DictDisplay_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_Exist_ci"

logical CClient_Exist_ci                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetClientHandle_ci0"

logical CClient_GetClientHandle_ci0                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetClientHandle_ci1"

logical CClient_GetClientHandle_ci1                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

}

#undef     MOD_ID
#define    MOD_ID  "CClient_GetDBError_ci"

logical CClient_GetDBError_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical      term = NO;
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
}

#undef     MOD_ID
#define    MOD_ID  "CClient_GetDataSource_ci"

logical CClient_GetDataSource_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetHandleInfo_ci1"

logical CClient_GetHandleInfo_ci1                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetMachineType_ci"

logical CClient_GetMachineType_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetPointerSize_ci"

logical CClient_GetPointerSize_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetServerVariable_ci"

logical CClient_GetServerVariable_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_GetServerVersion_ci"

logical CClient_GetServerVersion_ci                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_KillClient_ci"

logical CClient_KillClient_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_RestoreDB_ci"

logical CClient_RestoreDB_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_SayHello_ci"

logical CClient_SayHello_ci                                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_SendClientMessage_ci0"

logical CClient_SendClientMessage_ci0                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

}

#undef     MOD_ID
#define    MOD_ID  "CClient_SetClientName_ci"

logical CClient_SetClientName_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_SetServerVariable_ci"

logical CClient_SetServerVariable_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_SetupDataSource_ci"

logical CClient_SetupDataSource_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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
}

#undef     MOD_ID
#define    MOD_ID  "CClient_StartPause_ci"

logical CClient_StartPause_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_StatDisplay_ci"

logical CClient_StatDisplay_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_StopPause_ci"

logical CClient_StopPause_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CClient_SysInfoDisplay_ci"

logical CClient_SysInfoDisplay_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ActivateShadowBase_ci"

logical CDBHandle_ActivateShadowBase_ci                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_CDBHandle_ci0"

logical CDBHandle_CDBHandle_ci0                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{

#ifndef IF_Class  // client version

  InitHandle(NO);
  if ( !csconnection )                                 
    SDBSET(517)
  else
  {
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
}

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ChangeRecovery_ci"

logical CDBHandle_ChangeRecovery_ci                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_CheckLicence_ci1"

logical CDBHandle_CheckLicence_ci1                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_CheckLicence_ci2"

logical CDBHandle_CheckLicence_ci2                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_CloseDBHandle_ci"

logical CDBHandle_CloseDBHandle_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_CloseRecovery_ci"

logical CDBHandle_CloseRecovery_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_CloseWorkspace_ci"

logical CDBHandle_CloseWorkspace_ci                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ConsolidateWorkspace_ci"

logical CDBHandle_ConsolidateWorkspace_ci                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_DeactivateShadowBase_ci"

logical CDBHandle_DeactivateShadowBase_ci                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_DeleteWorkspace_ci"

logical CDBHandle_DeleteWorkspace_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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
}

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_DisableWorkspace_ci"

logical CDBHandle_DisableWorkspace_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_DiscardWorkspace_ci"

logical CDBHandle_DiscardWorkspace_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_EnableWorkspace_ci"

logical CDBHandle_EnableWorkspace_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ExecDBCtxFunc_ci"

logical CDBHandle_ExecDBCtxFunc_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ExistWorkspace_ci"

logical CDBHandle_ExistWorkspace_ci                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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
}

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_FlushClusterPool_ci"

logical CDBHandle_FlushClusterPool_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetDatabaseID_ci"

logical CDBHandle_GetDatabaseID_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetNewTypeID_cidb"

logical CDBHandle_GetNewTypeID_cidb                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetPath_ci"

logical CDBHandle_GetPath_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetRecoveryFile_ci"

logical CDBHandle_GetRecoveryFile_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetRecoveryNum_ci"

logical CDBHandle_GetRecoveryNum_ci                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetRecoveryPath_ci"

logical CDBHandle_GetRecoveryPath_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetRecoveryStartNumber_ci"

logical CDBHandle_GetRecoveryStartNumber_ci                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetRecoveryType_ci"

logical CDBHandle_GetRecoveryType_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetSchemaVersion_ci"

logical CDBHandle_GetSchemaVersion_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetSystemVersion_ci"

logical CDBHandle_GetSystemVersion_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetVersionString_ci"

logical CDBHandle_GetVersionString_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_GetWorkspace_ci"

logical CDBHandle_GetWorkspace_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_InitDataArea_ci"

logical CDBHandle_InitDataArea_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_InitMainBase_ci"

logical CDBHandle_InitMainBase_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_InitRecovery_ci"

logical CDBHandle_InitRecovery_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_InitSubBase_ci"

logical CDBHandle_InitSubBase_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_IsLicenced_ci"

logical CDBHandle_IsLicenced_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_LocateWorkspace_ci"

logical CDBHandle_LocateWorkspace_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_OpenRecovery_ci"

logical CDBHandle_OpenRecovery_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_OpenWorkspace_ci"

logical CDBHandle_OpenWorkspace_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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
}

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ResetLastSchemaVersion_ci"

logical CDBHandle_ResetLastSchemaVersion_ci                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_ResetLastVersion_ci"

logical CDBHandle_ResetLastVersion_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDBHandle_SetupTypeID_cidb"

logical CDBHandle_SetupTypeID_cidb                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
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

#undef     MOD_ID
#define    MOD_ID  "CDictionary_CDictionary_ci0"

logical CDictionary_CDictionary_ci0                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical       term = NO;
#ifndef IF_Class  // client version

  if ( !csconnection )                               SDBERR(517)
     
  LockSendParms().Fill(cpath,version_nr,(int32)accopt);
  SetClientPointer(this); 
    
  if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CDictionary_ci0) )
  {
    SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
    term = Get_rec_result()[0].GetUChar();      
  }
  UnlockSendParms();
  if ( term )                                        ERROR
    
  SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
  if ( Get_rec_result()[0].GetUChar())               ERROR
  
  InitHandle(NO);
  
  if ( OpenDictionary() )                            ERROR
  if ( OpenPIs() )                                   ERROR
  
#else             // server version

  SC_Dictionary *sc_dict;
  CS_Handle   *handle = parms->GetHandle();
//SDBError().TraceMessage("OpenDictionary");  
  sc_dict = ((ServerConnection *)connection)->ProvideDict(
                  handle->GetClientObject(),
                  (*parms)[0].GetString(),                                    // cpath
                  (*parms)[1].GetUShort(connection->get_conversion()),        // version_nr
                  (PIACC)(*parms)[2].GetLong(connection->get_conversion()) ); // accopt
   
  handle->SetServerPointer(sc_dict);
  *result->GetHandle() = *handle;
  result->Fill((logical)!sc_dict);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CDictionary_CloseDictionary_ci"

logical CDictionary_CloseDictionary_ci                         ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    Dictionary::CloseDictionary();
    if ( !csconnection || CConnection()->Check() )                                 
      SDBSET(517)
    else
    {
      if ( GetServerObject() )
      {
        LockSendParms().Fill();
        if ( CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CloseDictionary_ci) ||
             Get_rec_result()[0].GetUChar() )
          term = YES;
        UnlockSendParms();
      }    
      SetServerPointer((void *)NULL); 
    }
    UninitHandle();
  }

#else             // server version

  ((SC_Dictionary *)cso_ptr)->SetClientObject(0);
  term = ((ServerConnection *)connection)->ReleaseDict(parms->GetHandle());
  
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CDictionary_CreateExtentDef_ci"

logical CDictionary_CreateExtentDef_ci                         ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  DBExtend        *extdef = NULL;
  int32            indx0  = 0;
#ifndef IF_Class  // client version

char      string[ID_SIZE+1];

  if ( IsValid() )
  {
    if ( !csconnection )
      SDBSET(517)
    else
    {
      CConnection()->PushResult();
      LockSendParms().Fill(gvtxbts(string,tkey.Name(),ID_SIZE),tkey.GetID());
      if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateExtentDef_ci) )
        extdef = SetupDBExtent();
      UnlockSendParms();
      CConnection()->PopResult();
    }
  }
  
  return(extdef);

#else             // server version

  extdef = ((SC_Dictionary *)cso_ptr)->DictionaryHandle::ProvideExtentDef(
                  (*parms)[0].GetString(),                          // extnames
                  (*parms)[1].GetLong(connection->get_conversion()) // nsid
           );
  result->FillDBExtentExt(((SC_Dictionary *)cso_ptr)->get_dictionary(),extdef);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CDictionary_CreateStructDef_ci"

logical CDictionary_CreateStructDef_ci                         ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{


#ifndef IF_Class  // client version

char      string[ID_SIZE+1];
  
  if ( IsValid() )
  {
    if ( !strdef || !strdef->smcbsts.stscerr() )
    {
      if ( !csconnection )
        SDBSET(517)
      else
      {
        CConnection()->PushResult();
        LockSendParms().Fill(gvtxbts(string,tkey.Name(),ID_SIZE),tkey.GetID());
        if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateStructDef_ci) )
          strdef = SetupDBStructDef(strdef);
        UnlockSendParms();
        CConnection()->PopResult();
      }
    }
    if ( strdef && strdef->smcbsts.stscerr() )
      strdef = NULL;
  }
  
  return(strdef);

#else             // server version
  DBStructDef    *strdef;

  strdef = ((SC_Dictionary *)cso_ptr)->DictionaryHandle::ProvideStructureDef(
                  (*parms)[0].GetString(),                          // strnames
                  (*parms)[1].GetLong(connection->get_conversion()) // nsid
           );
  result->FillDBStructDefExt(((SC_Dictionary *)cso_ptr)->get_dictionary(),strdef);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CDictionary_CreateTempExtent_ci"

logical CDictionary_CreateTempExtent_ci                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char  *extnames = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )                               
      SDBSET(517)
    else
    {
      LockSendParms().Fill(strnames,extnames_w,key_name_w,baseexts_w,weak_opt_w,own_opt_w);
      if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_CreateTempExtent_ci) )
        if ( extnames = Get_rec_result()[0].GetString() )
          if ( !Dictionary::CreateTempExtent(strnames,extnames,key_name_w,baseexts_w,weak_opt_w,own_opt_w) )
            extnames = NULL;
      UnlockSendParms();
    }
  }
  
  return(extnames);

#else             // server version

  extnames = ((SC_Dictionary *)cso_ptr)->CreateTempExtent(
                  (*parms)[0].GetString(),     // strnames
                  (*parms)[1].GetString(),     // extnames_w
                  (*parms)[2].GetString(),     // key_name_w
                  (*parms)[3].GetString(),     // baseexts_w
                  (*parms)[4].GetUChar(),      // weak_opt_w
                  (*parms)[5].GetUChar() );    // own_opt_w
  result->Fill(extnames);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CDictionary_GetTempName_ci"

logical CDictionary_GetTempName_ci                             ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char       *ext_names = NULL;
#ifndef IF_Class  // client version

  if ( IsValid() )
  {
    if ( !csconnection )
      SDBSET(517)
    else
    {
      if ( !extnames )
        SDBSET(99)
      else
      {
        if ( *extnames )
          ext_names = extnames;
        else
        {
          LockSendParms().Fill(extnames);
          if ( !CConnection()->SendCSMessage(this,S_CDictionary,SF_CDictionary_GetTempName_ci) )
            if ( ext_names = Get_rec_result()[0].GetString() )
              ext_names = strncpy(extnames,ext_names,ID_SIZE);
          UnlockSendParms();
        }
      }
    }
  }
  
  return(ext_names);

#else             // server version

  char   extnames[ID_SIZE+1];
  char  *extname_ptr;
  
  strncpy(extnames,(*parms)[0].GetString(),sizeof(extnames));
  extname_ptr = ((SC_Dictionary *)cso_ptr)->GetTempName(extnames);
  result->Fill(extname_ptr);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Add_ci"

logical CNode_Add_ci                                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb         *skeysmcb;
  smcb         *idkeysmcb;
  DBStructDef  *strdef;
  logical       rerun   = YES;
  logical       term    = YES;
  void         *instptr = NULL;

#ifndef IF_Class  // client version
  
  if ( !Check(YES) && CheckAddSet() == NO )
  {
    LockSendParms();
    if ( nodeinst->stscini() || !Switch(AUTO) )	                             
    {    
      Initialize_intern(initinst);
      if ( !GenerateEvent(DBP_Insert) )
      {
        nodewrit = AUTO;
        if ( !Cnodeinst->before_add() )     // der inhalt der instanz ist hier zufaellig/nicht initialisiert
        {
          skeysmcb   = get_sortkey_smcb();
          idkeysmcb  = get_idkey_smcb();
          strdef     = nodeinst->get_struct_def();
          is_updated = NO; // 22.10.02  
      
          stssnof(); // node is acting
          while ( rerun )
          {
            Get_send_parms().Fill(indx0,                                      
                                  sort_key,skeysmcb ? skeysmcb : idkeysmcb,
                                  ident_key,idkeysmcb,
                                  initinst,strdef,nodeinst->GetSize(),
                                  initinst == nodeinst->get_iselarea() ? YES : NO,  // is_iselarea
                                  global_add );
                          
            if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Add_ci) )
              rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
            else
              term = Get_rec_result()[0].GetUChar();
          }
          stsrnof();
        }
      }
    }
    instptr = Inst_setup(term,YES);  // macht das DB_Inserted
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  void         *newinst;
  
  skeysmcb  = sc_prop->GetSortKeySMCB();
  idkeysmcb = sc_prop->GetKeySMCB();
  strdef    = sc_prop->GetCurrentTypeDef();
  newinst   = (*parms)[5].GetInstance(strdef,
                              sc_prop->Get_instarea(),
                              connection->get_conversion()).GetData();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( (*parms)[7].GetUChar() )                                      // is_iselarea
    {
      sc_prop->GetInitInstance();
      sc_prop->CopyInstance(newinst);
    }

    if ( (*parms)[8].GetUChar()  )        // global_add
    {
      if ( sc_prop->AddGlobal(
           (*parms)[0].GetLong(connection->get_conversion()),           // indx0
           (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,
                              sc_prop->Get_skeyarea(),
                              connection->get_conversion()).GetData(),  // sort_key
                                                                        // sort key name
           (*parms)[3].GetKey(idkeysmcb,
                              sc_prop->Get_idkeyarea(),
                              connection->get_conversion()).GetData(),  // ident_key
                                                                        // ident key name
           newinst)   )
        term = NO;
    }
    else                                 // local_add
    {
      if ( sc_prop->Add(
           (*parms)[0].GetLong(connection->get_conversion()),           // indx0
           (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,
                              sc_prop->Get_skeyarea(),
                              connection->get_conversion()).GetData(),  // sort_key
                                                                        // sort key name
           (*parms)[3].GetKey(idkeysmcb,
                              sc_prop->Get_idkeyarea(),
                              connection->get_conversion()).GetData(),  // ident_key
                                                                        // ident key name
           newinst)   )
        term = NO;
    }
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_AddReference_ci0"

logical CNode_AddReference_ci0                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && !srcenode->Check(YES) )
  {
    LockSendParms();
    if ( srcenode->get_nodetype() != NT_ClientNode )
      SDBSET(99)
    else
    {
      if ( !Switch(AUTO) )
      {
        if ( !GenerateEvent(DBP_Insert) )
        {
          stssnof(); // node is acting
          while ( rerun )
          {
            Get_send_parms().Fill((CS_Handle *)Csrcenode,
                                  lindx0);
            if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_AddReference_ci0) )
              rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
            else
              term = Get_rec_result()[0].GetUChar();
          }
          stsrnof();
        }
      }
    }
    Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->pib::AddReference(
              *(pib *)((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer()),  // source_handle
              (*parms)[1].GetLong(connection->get_conversion()) );                   // lindx0
  sc_prop->FillInstResult(result,term);
  
  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_CanUpdateCollection_ci"

logical CNode_CanUpdateCollection_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 cond = NO;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( nodenode && nodenode->IsInitInstance() )
      cond = bnode::CanUpdateCollection(NO);
    else
    {
      LockSendParms().Fill();
      if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CanUpdateCollection_ci) )
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(cond);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  sc_prop->CheckInstance();
  cond = sc_prop->IsCollectionUpdate();
   
  result->Fill(cond);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Cancel_ci0"

logical CNode_Cancel_ci0                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(NO,NO)  )
  {
    if ( chknode && inti_buffer )
      inti_buffer->Cancel();
    
    term = NO;
    if ( is_opened && IsPositioned() )
    {
      term = YES;
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Cancel_ci0) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
    ResetInstance();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->Cancel();
   
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ChangeBuffer_ci0"

logical CNode_ChangeBuffer_ci0                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun       = YES;
  int16       new_buffnum = AUTO;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    Switch(AUTO);
    
    while ( rerun )
    {
      LockSendParms().Fill(buffnum);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ChangeBuffer_ci0) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        new_buffnum = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
    }
    if ( new_buffnum > 1 )
    {
      SetSysVariable("MAX_BUFFER_SIZE","");
      if ( bnode::ChangeBuffer(new_buffnum) != new_buffnum )
      {
        SDBSET(99)
        new_buffnum = AUTO;
      }
    }
  }
  return(new_buffnum);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    new_buffnum = sc_prop->ChangeBuffer((*parms)[0].GetShort(connection->get_conversion()));  // buffnum
  
  result->Fill(new_buffnum);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ChangeMode_ci0"

logical CNode_ChangeMode_ci0                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  PIACC    oldmode = PI_undefined;
  logical  rerun   = YES;

#ifndef IF_Class  // client version

  if ( !chkopt || !Check(YES,NO) )
  {
    if ( !Switch(AUTO) )
    {
      while ( rerun )
      {
        LockSendParms().Fill((int32)newmode);
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ChangeMode_ci0) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          oldmode = (PIACC)Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
    ChangeMode_intern(oldmode == PI_undefined ? YES : NO,newmode);
  }
  return(oldmode);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    oldmode =  sc_prop->ChangeMode((PIACC)
                            (*parms)[0].GetLong(connection->get_conversion()) ); 
     
  result->Fill((int32)oldmode);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_CheckReadOnly_ci"

logical CNode_CheckReadOnly_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 cond = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms().Fill();
           
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CheckReadOnly_ci) )
      cond = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(cond);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  cond = sc_prop->IsReadOnly();  
  
  result->Fill(cond);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_CheckWProtect_ci0"

logical CNode_CheckWProtect_ci0                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    wpt = NO;
#ifndef IF_Class  // client version

  if ( IsPositioned() )
  {
    LockSendParms().Fill();
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CheckWProtect_ci0) )
      wpt = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(wpt);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  sc_prop->CheckInstance();
  wpt = sc_prop->CheckWProtect();
   
  result->Fill(wpt);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Close_ci0"

logical CNode_Close_ci0                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = NO;
#ifndef IF_Class  // client version

  if ( nodeidnt == NODE_ID )
  {
    if ( csconnection && !Check(NO,NO) && GetServerObject() ) // csconnection-pruefung, damit Check keinen fehler setzt
    {
      Switch(AUTO);
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Close_ci0) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
    Close_intern();
  }
  return(term);
  
#else             // server version
  
  ((SC_Property *)cso_ptr)->SetClientObject(0);
  term = ((SC_Property *)cso_ptr)->Remove();
  
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Contains_ci"

logical CNode_Contains_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     cond  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(reg_string,                  // regular expression
                            case_opt);                   // case sensitive option
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Contains_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(cond);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( !(rerun = sc_prop->CheckInstance()) )
    cond = sc_prop->Contains(
              (*parms)[0].GetString(),         // regular expression
              (*parms)[1].GetUChar() );        // case sensitive option
  
  result->Fill(cond);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_CopyInst_ci"

logical CNode_CopyInst_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb         *skeysmcb;
  smcb         *idkeysmcb;
  void         *instptr = NULL;
  logical       rerun   = YES;
  logical       term    = YES;

#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( csconnection != Csrcenode->get_csconnection() )
      instptr = bnode::CopyInst(srcenode,db_replace,copy_type,w_newkey,set_pos0_w,chknode);
    else
    {
      if ( !Switch(AUTO) )
      {
        skeysmcb  = get_sortkey_smcb();
        idkeysmcb = get_idkey_smcb();
      
        stssnof(); // node is acting
        while ( rerun )
        {
          Get_send_parms().Fill((CS_Handle *)Csrcenode,                                      
                                Key(w_newkey),skeysmcb ? skeysmcb : idkeysmcb,
                                set_pos0_w,
                                (int32)db_replace,
                                (int32)copy_type);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CopyInst_ci) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
        stsrnof();
      }
    }
    if ( !instptr )
      instptr = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  skeysmcb  = sc_prop->GetSortKeySMCB();
  idkeysmcb = sc_prop->GetKeySMCB();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    sc_prop->Copy(
      *(SC_Property *)(*parms)[0].GetHandle()->GetServerPointer(),     // srcenode
      (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,              // w_new_key
                         sc_prop->Get_skeyarea(),
                         connection->get_conversion()).GetData(),     
      (*parms)[3].GetLong(connection->get_conversion()),               // set_pos0
      (PIREPL)(*parms)[4].GetLong(connection->get_conversion()),       // db_replace
      (PIREPL)(*parms)[5].GetLong(connection->get_conversion())        // copy_type
                );
  
    term = SDBERROR ? YES : NO;
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_CopySet_ci"

logical CNode_CopySet_ci                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int32      count = ERIC;
  logical   rerun = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( srcenode->get_nodetype() != NT_ClientNode || csconnection != Csrcenode->get_csconnection() )
      count = bnode::CopySet(srcenode,check_inverse,db_replace,copy_type,chknode);
    else
    {
      if ( !Switch(AUTO) )
      {
        stssnof(); // node is acting
        while ( rerun )
        {
          LockSendParms().Fill((CS_Handle *)Csrcenode,   
                                check_inverse,                                   
                                (int32)db_replace,
                                (int32)copy_type);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CopySet_ci) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            count = Get_rec_result()[0].GetLong(conversion);
          UnlockSendParms();
        }
        stsrnof();
      }
      ResetInstance();
    }
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->CopySet(
      *(SC_Property *)(*parms)[0].GetHandle()->GetServerPointer(),     // srcenode
      (PIREPL)(*parms)[2].GetLong(connection->get_conversion()),       // db_replace
      (PIREPL)(*parms)[3].GetLong(connection->get_conversion()),       // copy_type
      (PIREPL)(*parms)[1].GetUChar()                                   // check_inverse
                );
  result->Fill(count);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Delete_ci0"

logical CNode_Delete_ci0                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb       *keysmcb;
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  int32        obj_id = objid;
  
  if ( !Check(YES) )
  {
    if ( !GenerateEvent(DBP_Remove) )
    {
      if ( keysmcb = CheckSKey_intern() )
      {  
        while ( rerun )
        {
          LockSendParms().Fill(sort_key,keysmcb);  // sort_key + keynames
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Delete_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
          UnlockSendParms();
        }
      }
      if ( !term) 
      {
        ResetInstance();
        if ( origin )
          origin->ResetCopyNodes(this,obj_id);
        else
          ResetCopyNodes(this,obj_id); 
      }
      else
        RecoverSelection(obj_id);  // generates Read-event
      GenerateEvent(term ? DBO_NotRemoved : DBO_Removed);
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(keysmcb = sc_prop->CheckSKey((*parms)[1].GetString())) )
    rerun = NO;
  else   
    if ( !(rerun = sc_prop->CheckInstance()) )
      term = sc_prop->Delete(
          (*parms)[0].GetKey(keysmcb,
                             sc_prop->Get_skeyarea(),
                             connection->get_conversion()).GetData()  // sort_key
                            );                                       
  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Delete_ci1"

logical CNode_Delete_ci1                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  int32         obj_id = objid;
  
  if ( !Check(YES) )
  {
    if ( !GenerateEvent(DBP_Remove) )
    {
      stssnof(); // node is acting
      while ( rerun )
      {
        LockSendParms().Fill(set_pos0_w,del_dep,del_inst);
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Delete_ci1) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
      stsrnof();
      if ( !term) 
      {
        ResetInstance();
        if ( origin )
          origin->ResetCopyNodes(this,obj_id);
        else
          ResetCopyNodes(this,obj_id); 
      }
      else
        RecoverSelection(obj_id);  // generates Read-event
      GenerateEvent(term ? DBO_NotRemoved : DBO_Removed);
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->Delete(
        (*parms)[0].GetLong(connection->get_conversion()),  // indx0
        (*parms)[1].GetUChar(),                             // del_dep
        (*parms)[1].GetUChar() );                           // del_inst
  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_DeleteSet_ci"

logical CNode_DeleteSet_ci                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    stssnof(); // node is acting
    while ( rerun )
    {
      LockSendParms().Fill(del_dep);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_DeleteSet_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
    stsrnof(); 
    ResetInstance();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->DeleteSet(
        (*parms)[0].GetUChar() );                // del_dep
  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_DisableKeyCheck_ci0"

logical CNode_DisableKeyCheck_ci0                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES,NO) )
  {
    term = NO;
    if ( is_opened )
    {
      term = YES;
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_DisableKeyCheck_ci0) )
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->DisableKeyCheck();
   
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Duplicate_ci0"

logical CNode_Duplicate_ci0                                    ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  Instance     ph_inst = NULL;
  smcb        *keysmcb = NULL;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( Exist() )
  {
    LockSendParms();
    if ( (keysmcb = CheckSKey_intern()) )
    {
      if ( !Save(NO,NO) )
      {
        stssnof(); // node is acting
        while ( rerun )
        {
          Get_send_parms().Fill(keyptr,keysmcb,(int32)db_replace);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Duplicate_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
        stsrnof();
      }
    }
    ph_inst = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(&ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  sc_prop->CheckInstance();
  if ( !(keysmcb = sc_prop->GetSortKeySMCB()) )
    keysmcb = sc_prop->GetKeySMCB();
  
  term = !sc_prop->Duplicate(
              (*parms)[0].GetKey(keysmcb,
                                 sc_prop->Get_skeyarea(),
                                 connection->get_conversion()).GetData(),   // sort_key
              (PIREPL)(*parms)[1].GetLong(connection->get_conversion()) );  // repl_opt
  
  sc_prop->FillInstResult(result,term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_EnableKeyCheck_ci0"

logical CNode_EnableKeyCheck_ci0                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES,NO) )
  {
    term = NO;
    if ( is_opened )
    {
      term = YES;
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_EnableKeyCheck_ci0) )
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->EnableKeyCheck();
   
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ExecPropCtxFunc_ci"

logical CNode_ExecPropCtxFunc_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(fnames,w_parms);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ExecPropCtxFunc_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        if ( !(term = Get_rec_result()[0].GetUChar()) )
        {
          set_result_string(Get_rec_result()[1].GetString(),UNDEF);
          term = bnode::ExecPropCtxFunc(fnames,w_parms);   // Client kann Ergebnis überschreiben
        }
      UnlockSendParms();
    }
  }
  if ( is_dirty )
    Reset();
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  char         *result_str = NULL;
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    if ( !( term = sc_prop->ExecutePropertyAction(
                            (*parms)[0].GetString(),        //  action_name
                            (*parms)[1].GetString()         //  parameter string
            )) )
      result_str = sc_prop->GetActionResult();
   
  result->Fill(term,result_str);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ExecStrCtxFunc_ci"

logical CNode_ExecStrCtxFunc_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(fnames,w_parms);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ExecStrCtxFunc_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        if ( !(term = Get_rec_result()[0].GetUChar()) )
        {
          set_result_string(Get_rec_result()[1].GetString(),UNDEF);
          term = bnode::ExecStrCtxFunc(fnames,w_parms);  // Client kann Ergebnis überschreiben
        }
      UnlockSendParms();
    }
  }
  if ( is_dirty )
    Reset();
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  char         *result_str = NULL;
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    if ( !( term = sc_prop->ExecuteInstanceAction(
                            (*parms)[0].GetString(),        //  action_name
                            (*parms)[1].GetString()         //  parameter string
            )) )
      result_str = sc_prop->GetActionResult();
   
  result->Fill(term,result_str);
  
  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_FirstKey_ci"

logical CNode_FirstKey_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char       *sort_key;
  char       *keyptr = NULL;
  logical     rerun = YES;

  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    LockSendParms();
    if ( !Switch(AUTO) )
    {
      while ( rerun )
      {
        Get_send_parms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_FirstKey_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
    }
    sort_key = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(sort_key);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = (keyptr = sc_prop->FirstKey()) ? NO : YES;
  sc_prop->FillKeyResult(result,keyptr,term);

  return(term);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Get_ci0"

logical CNode_Get_ci0                                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *instptr = NULL;
  logical      rerun   = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( !(instptr = Get_optimized(lindx0,chknode)) )
    {
      LockSendParms();
      if ( csconnection && !Switch(AUTO) )
      {
        while ( rerun )
        {
          Get_send_parms().Fill(lindx0);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Get_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = NO;
        }
      }
      instptr = Inst_setup(term);
      UnlockSendParms();
    }
    if ( instptr )
      GenerateEvent(DBO_Read);
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->Get((*parms)[0].GetLong(connection->get_conversion())) ? NO : YES;  // indx0
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Get_ci1"

logical CNode_Get_ci1                                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *instptr = NULL;
  smcb        *keysmcb;
  char         wskey[MAX_KEYLEN];
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) && skey )
  {
    if ( stscusr2() )                        // VOID-Extent
      instptr = Get_ByID(skey);
    else
    {
      SaveKey(wskey,skey);
      if ( !(instptr = bnode::Get_optimized(skey)) )
      {
        if ( nodefield->fmcbdim != 1          &&
             (keysmcb = CheckSKey_intern())       )
        {  
          if ( inti_buffer )
          {
            if ( instptr = GetBuffer(skey,0) ) 
              Cnodeinst->SetupInst(nodecur,objid,UNDEF,YES);
          }
          else if ( csconnection && !Switch(AUTO) )
          {
            LockSendParms();
            while ( rerun )
            {
              Get_send_parms().Fill(wskey,keysmcb);           // sort_key + keynames
              if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Get_ci1) )
                rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
              else
                term = NO;
            }
            instptr = Inst_setup(term);
            UnlockSendParms();
          }
        }
        if ( instptr )
          GenerateEvent(DBO_Read);
        if ( instptr && cache_list )
          cache_list->AddEntry(nodeinst);    
      }
    }
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(keysmcb = sc_prop->CheckSKey((*parms)[1].GetString())) )
    rerun = NO;
  else
    if ( !(rerun = sc_prop->CheckInstance()) )
      term = sc_prop->Get(
                (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData())  // sort_key
             ? NO : YES;
   
  sc_prop->FillInstResult(result,term);
  
  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetCollectionID_ci"

logical CNode_GetCollectionID_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  int32       coll_id = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( IsAttribute() )
      coll_id = nodefield->fmcbdim;
    else
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetCollectionID_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          coll_id = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
  }
  return(coll_id);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    coll_id = sc_prop->GetCollectionID();
  
  result->Fill(coll_id);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetCount_ci"

logical CNode_GetCount_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  int32        count = ERIC;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( IsAttribute() )
      count = nodefield->fmcbdim;
    else
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetCount_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->GetCount();
  
  result->Fill(count);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetGenAttrType_ci"

logical CNode_GetGenAttrType_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun    = YES;
  int32        attrtype = UNDEF;

#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun)
    {
      LockSendParms().Fill(w_propnames);    
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetGenAttrType_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        attrtype = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(attrtype);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    attrtype = sc_prop->GetGenAttrType(
                          (*parms)[0].GetString() ); // w_propnames
  result->Fill(attrtype);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetGenOrderType_ci"

logical CNode_GetGenOrderType_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun    = YES;
  int32        attrtype = UNDEF;

#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill();    
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetGenOrderType_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        attrtype = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(attrtype);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    attrtype = sc_prop->GetGenOrderType();
  
  result->Fill(attrtype);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetGlobalID_ci0"

logical CNode_GetGlobalID_ci0                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical      rerun   = YES;
  DBStructDef *strdef;
  int32         obident = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    strdef    = nodeinst->get_struct_def();
      
    while ( rerun )
    {
      LockSendParms().Fill(nodeinst->get_iselarea(),strdef,nodeinst->GetSize());
      
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetGlobalID_ci0) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  strdef       = sc_prop->GetCurrentTypeDef();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( !sc_prop->CopyInstance((*parms)[0].GetInstance(strdef,
                                sc_prop->Get_instarea(),
                                connection->get_conversion()).GetData()  // instance
                     ) )
      obident = sc_prop->GetGlobalID();
  }
    
  result->Fill(obident);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetID_ci0"

logical CNode_GetID_ci0                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun   = YES;
  int32        obident = UNDEF;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( nodecur && objid && (lindx0 == AUTO || lindx0 == nodecur) )
      obident = objid;
    else  
    {
      while ( rerun )
      {
        LockSendParms().Fill(lindx0);   // indx0
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetID_ci0) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    obident = sc_prop->GetID(
                       (*parms)[0].GetLong(connection->get_conversion()));    // indx0
  
  result->Fill(obident);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetID_ci1"

logical CNode_GetID_ci1                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb       *keysmcb;
  logical     rerun   = YES;
  int32        obident = UNDEF;

#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( IsPositioned() )
      obident = objid;
    else if ( stscusr2() )               // VOID-Extent
    {
      obident = GetID_ByID(keyptr).get_ebsnum();
    }
    else if ( keysmcb = CheckSKey_intern() )
    {  
      while ( rerun )
      {
        LockSendParms().Fill(keyptr,keysmcb); // sort_key + keynames
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetID_ci1) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
   
  if ( !(keysmcb = sc_prop->CheckSKey((*parms)[1].GetString())) )
    rerun = NO;
  else
    if ( !(rerun = sc_prop->CheckInstance()) )
      obident = sc_prop->GetID((*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData()); // sort_key
  
  result->Fill(obident);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetID_ByID_ci1"

logical CNode_GetID_ByID_ci1                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb       *keysmcb;
  logical     rerun   = YES;
  int32        obident = UNDEF;

#ifndef IF_Class  // client version

  if ( !csconnection )
    SDBSET(517)
  else while ( rerun )
  {
    
    LockSendParms().Fill(keyptr); // sort_key string
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetID_ByID_ci1) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
    UnlockSendParms();
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
   
  if ( !(rerun = sc_prop->CheckInstance()) )
    obident = sc_prop->GetID((*parms)[0].GetString()); // sort_key string
  
  result->Fill(obident);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetInstModCount_ci"

logical CNode_GetInstModCount_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun    = YES;
  int16       modcount = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms().Fill();
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetInstModCount_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else  
      modcount = Get_rec_result()[0].GetShort(csconnection->get_conversion());
    UnlockSendParms();
  }
  return(modcount);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    modcount =  sc_prop->GetInstModCount();
  result->Fill(modcount);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetKey_ci"

logical CNode_GetKey_ci                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char       *sort_key;
  char       *keyptr = NULL;
  logical     rerun = YES;
  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(lindx0);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetKey_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = NO;
        
    }
    sort_key = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(sort_key);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = (keyptr = sc_prop->GetKey((*parms)[0].GetLong(connection->get_conversion()))) ? NO : YES;
  sc_prop->FillKeyResult(result,keyptr,term);

  return(term);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetRefModCount_ci"

logical CNode_GetRefModCount_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun    = YES;
  int16       modcount = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms().Fill();
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRefModCount_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      modcount = Get_rec_result()[0].GetShort(csconnection->get_conversion());
    UnlockSendParms();
  }
  return(modcount);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    modcount =  sc_prop->GetRefModCount();
  result->Fill(modcount);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetRelative_ci0"

logical CNode_GetRelative_ci0                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *instptr = NULL;
  logical      rerun   = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( !(instptr = Get_optimized(lindx0,chknode)) )
    {
      LockSendParms();
      if ( !Switch(AUTO) )
      {
        while ( rerun )
        {
          Get_send_parms().Fill(lindx0);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRelative_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = NO;
        }
      }
      if ( instptr = Inst_setup(term) )
        GenerateEvent(DBO_Read);
      UnlockSendParms();
    }
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->GetRelative((*parms)[0].GetLong(connection->get_conversion())) ? NO : YES;  // indx0
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetRelativeCount_ci"

logical CNode_GetRelativeCount_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  int32        count = ERIC;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( IsAttribute() )
      count = nodefield->fmcbdim;
    else
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRelativeCount_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->GetRelativeCount();
  
  result->Fill(count);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetRelativeIndex_ci"

logical CNode_GetRelativeIndex_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 rerun = YES;
  int32                   lindx0 = AUTO;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(last_opt);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRelativeIndex_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        lindx0 = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(lindx0);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    lindx0 = sc_prop->GetRelativeIndex((*parms)[0].GetUChar());
  
  result->Fill(lindx0);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_GetSelectedKey_ci"

logical CNode_GetSelectedKey_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char       *sort_key;
  char       *keyptr = NULL;
  logical     rerun = YES;

  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetSelectedKey_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = NO;
    }
    sort_key = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(sort_key);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = (keyptr = sc_prop->GetSelectedKey()) ? NO : YES;
  sc_prop->FillKeyResult(result,keyptr,term);

  return(term);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Get_ByID_ci1"

logical CNode_Get_ByID_ci1                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *instptr = NULL;
  smcb        *keysmcb;
  char         wskey[MAX_KEYLEN];
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Switch(AUTO) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(skey);           // sort_key string
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Get_ByID_ci1) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = NO;
    }
    if ( instptr = Inst_setup(term) )
      GenerateEvent(DBO_Read);
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->Get(
              (*parms)[0].GetString())  // sort_key string
           ? NO : YES;
   
  sc_prop->FillInstResult(result,term);
  
  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Group_ci"

logical CNode_Group_ci                                         ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun   = YES;
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    Switch(AUTO);
    
    while ( rerun )
    {
      LockSendParms().Fill((CS_Handle *)Cnodeptr,
                                distinct);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Group_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
/*  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->pib::group(
              *(pib *)((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer()),  // source_handle
              NULL,                                                                  // grouping rule defined in target
              (*parms)[1].GetUChar() );                                              // distinct
*/  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_IsNewInstance_ci"

logical CNode_IsNewInstance_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   cond = NO;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( new_instance == AUTO )
    {
      LockSendParms().Fill();
           
      if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_IsNewInstance_ci) )
        new_instance = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(new_instance == YES ? YES : NO );
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  cond =  sc_prop->IsNewInstance();
  
  result->Fill(cond);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Locate_ci"

logical CNode_Locate_ci                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  void     *ph_inst;
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && entnr.get_ebsnum() != AUTO )
  {
    if ( read_opt )  // fuer ! siehe docu
      Switch(AUTO);

    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill((int32)entnr.get_ebsnum(),read_opt);
    
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Locate_ci) )
        rerun  = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    ph_inst = Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  !sc_prop->Locate(
                      (*parms)[0].GetLong(connection->get_conversion()),     // objid
                      (*parms)[1].GetUChar()                                 // read_opt
                );
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_LocateKey_ci"

logical CNode_LocateKey_ci                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb       *keysmcb;
  logical     rerun = YES;
  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( (keysmcb = CheckSKey_intern()) )
    {
      Switch(AUTO);
      LockSendParms();
      while ( rerun )
      {
        Get_send_parms().Fill(sort_key,keysmcb,            // sort_key + keynames
                              exact);                      // exact
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_LocateKey_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
      }
      InstKey_setup(term,sort_key);
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    if ( !(rerun = sc_prop->CheckInstance()) )
      term = sc_prop->LocateKey(
              (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData(), // sort_key
              (*parms)[2].GetUChar() );                                                                   // exact
  
  sc_prop->FillKeyResult(result,sc_prop->Get_skeyarea(),term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Lock_ci"

logical CNode_Lock_ci                                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( Exist() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Lock_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->Lock();
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_LockSet_ci"

logical CNode_LockSet_ci                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( !chknode || !Check(YES) )
  {
    if ( chknode && inti_buffer )
      inti_buffer->Cancel();
    
    if ( !Switch(AUTO) )
    {
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_LockSet_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
    if ( chknode )
      ResetInstance();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->LockSet();
  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Modify_ci"

logical CNode_Modify_ci                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void       *ph_inst = NULL;
  logical     term    = YES;
#ifndef IF_Class  // client term
  
  if ( !chknode || !Check(YES,NO) )  // siehe bnode
  {
    if ( IsTransient() )
      term = NO;
    else if ( IsAttribute() )
      term = ModifyAttribute(chknode) ? NO : YES;
    else
    {
      if ( !(term = CheckModify()) )
        if ( !(term = GenerateEvent(DBP_Modify)) )
          if ( IsWrite() && !nodeinst->stscini() )
            if ( nodeinst->IsPositioned() )  
              term = nodeinst->Modify();
    
      if ( !term )
        SetModified();
    }
    if ( !term )
      ph_inst = nodeinst->get_iselarea();
  }
  return(ph_inst);

/* 
wir probierens erstmal ohne kommunikation
  if ( !chknode || !Check(YES) )
  {
    if ( IsTransient() )
      term = NO;
    else
    {
      if ( IsWrite() || (nodeinst && nodeinst->stscini()) )  
      {
        if ( GetServerPointer() )
        {
          LockSendParms().Fill();
    
          if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Modify_ci) )
            term = Get_rec_result()[0].GetUChar();
          UnlockSendParms();
        }
      }
      if ( !term )
        SetModified();
    }
    if ( !term )
      ph_inst = nodeinst->get_iselarea();
  }
  return(ph_inst);
wir probierens erstmal ohne kommunikation
*/  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term = ((pib *)sc_prop)->Modify();
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Move_ci"

logical CNode_Move_ci                                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb         *skeysmcb;
  smcb         *idkeysmcb;
  void         *instptr = NULL;
  logical       rerun   = YES;
  logical       term    = YES;

#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( csconnection != Csrcenode->get_csconnection() )
    {
      if ( instptr = bnode::CopyInst(srcenode,db_replace,REPL_all,w_newkey,setwpt) )
        srcenode->Delete(AUTO);
    }
    else
    {
      skeysmcb  = get_sortkey_smcb();
      idkeysmcb = get_idkey_smcb();
      
      Switch(AUTO);
      stssnof(); // node is acting
      
      while ( rerun )
      {
        Get_send_parms().Fill((CS_Handle *)Csrcenode,                                      
                              Key(w_newkey),skeysmcb ? skeysmcb : idkeysmcb,
                              (int32)db_replace);
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Move_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
      }
      stsrnof();
    }
    if ( !instptr )
      instptr = Inst_setup(term);
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  skeysmcb  = sc_prop->GetSortKeySMCB();
  idkeysmcb = sc_prop->GetKeySMCB();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    sc_prop->Move(
      *(SC_Property *)(*parms)[0].GetHandle()->GetServerPointer(),     // srcenode
      (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,              // w_new_key
                         sc_prop->Get_skeyarea(),
                         connection->get_conversion()).GetData(),     
      (PIREPL)(*parms)[3].GetLong(connection->get_conversion())        // db_replace
                );
  
    term = SDBERROR ? YES : NO;
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_MoveDown_ci"

logical CNode_MoveDown_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( !Save(NO,NO) )
    {
      stssnof(); // node is acting
      while ( rerun )
      {
        Get_send_parms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_MoveDown_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
      stsrnof(); 
    }
    Inst_setup(term);
    UnlockSendParms();
    term = (nodecur == AUTO ? YES : NO);
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->MoveDown();
      
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_MoveUp_ci"

logical CNode_MoveUp_ci                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( !Save(NO,NO) )
    {
      stssnof(); // node is acting
      while ( rerun )
      {
        Get_send_parms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_MoveUp_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
      stsrnof(); 
    }
    Inst_setup(term);
    UnlockSendParms();
    term = (nodecur == AUTO ? YES : NO);
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->MoveUp();
      
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_NextKey_ci"

logical CNode_NextKey_ci                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb       *keysmcb = NULL;
  char       *keyptr  = NULL;
  logical     rerun = YES;
  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( keysmcb = CheckSKey_intern() )
    {        
      Switch(AUTO);
      while ( rerun )
      {
        Get_send_parms().Fill(sort_key_w,keysmcb,       // sort_key + keynames
                              switch_level);            // switch_level
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_NextKey_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
    }
    keyptr = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(keyptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    if ( !(rerun = sc_prop->CheckInstance()) )
      if ( keyptr = sc_prop->NextKey(
             (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData(), // sort_key
             (*parms)[2].GetShort(connection->get_conversion())) )                                       // switch_level
        term = NO;
  
  sc_prop->FillKeyResult(result,keyptr,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenAccessPath_ci1"

logical CNode_OpenAccessPath_ci1                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;

#ifndef IF_Class  // client version
   
  if ( !csconnection )
    SDBSET(517)
  else if ( object_ref->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)object_ref->GetClientACObject(),  // object_handle
                          prop_path,                                     // access path
                          (int32)nodeacc,                                // accopt
                          temp_opt_w);                                   // temp_opt_w
    InitHandle();
      
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenAccessPath_ci1) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
        obhandle->GetClientACObject()->get_topnode_list()->AddTail(this);
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_DBObject *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),
                    (*parms)[1].GetString(),                                  // access path
                    (PIACC)(*parms)[2].GetLong(connection->get_conversion()), // accopt
                    (*parms)[3].GetUChar()) )                                 // temp_opt_w
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif

}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenAccessPath_ci2"

logical CNode_OpenAccessPath_ci2                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;

#ifndef IF_Class  // client version 
  
  if ( !csconnection )
    SDBSET(517)
  else if ( object_ref->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref,                 // parent
                          prop_path);                              // access path
    InitHandle();
      
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenAccessPath_ci2) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),                     // parent
                    (*parms)[1].GetString()) );                    // access path
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenBaseNode_ci"

logical CNode_OpenBaseNode_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( base_reference->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)(CNode *)base_reference);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenBaseNode_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->GetBaseProperty(
                     handle->GetClientObject())  )               // sc_property
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenCopyNode_ci"

logical CNode_OpenCopyNode_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( !cnode_ref.Check(YES,NO) )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenCopyNode_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                     handle->GetClientObject(),               // sc_property
                     NULL)  )                                 // prop_names
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenOperationNode_ci1"

logical CNode_OpenOperationNode_ci1                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( !csconnection )
    SDBSET(517)
  else if ( nodenode->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref,                        // parent handle
                          rule,                                          // operation rule
                          (int32)op_type);                               // op_type
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenOperationNode_ci1) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        Open_setup();  
        object_ref->GetClientACObject()->get_topnode_list()->AddTail(this);
      }
    UnlockSendParms();
  }
    
  return(term);
   
#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),                                // sc_property
                    (*parms)[1].GetString(),                                  // operation rule
                    (ST_OpCodes)(*parms)[2].GetLong(connection->get_conversion())) ) // op_type
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenOperationNode_ci2"

logical CNode_OpenOperationNode_ci2                            ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( !csconnection )
    SDBSET(517)
  else if ( object_ref->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)object_ref->GetClientACObject(),  // object_handle
                          rule,                                          // operation rule
                          (int32)op_type );                              // operation type
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenOperationNode_ci2) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        Open_setup();  
        object_ref->GetClientACObject()->get_topnode_list()->AddTail(this);
      }
    UnlockSendParms();
  }
    
  return(term);
   
#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_DBObject *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),
                    (*parms)[1].GetString(),                                  // operation rule
                    (ST_OpCodes)(*parms)[2].GetLong(connection->get_conversion())) ) // operation_type
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenPathCopy_ci"

logical CNode_OpenPathCopy_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( !cnode_ref.Check(YES,NO) )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref,(CS_Handle *)&last_node,path_opt,(int32)accmode,copy_selection);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenPathCopy_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                     handle->GetClientObject(),                                       // sc_property
                     *(SC_Property *)(*parms)[1].GetHandle()->GetServerPointer(),     // last node
                     (*parms)[2].GetUChar(),                                          // path_opt
                     (PIACC)(*parms)[3].GetLong(connection->get_conversion()),        // accmode
                     (*parms)[4].GetUChar() )      )                                  // copy selection
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_OpenSubNode_ci"

logical CNode_OpenSubNode_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( nodenode->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)Cnodenode,prop_path);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenSubNode_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                     handle->GetClientObject(),                 // sc_property
                     (*parms)[1].GetString())    )              // prop_names
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Position_ci"

logical CNode_Position_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int32        lindx0 = AUTO;
  void        *instptr = NULL;
  logical      rerun  = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    lindx0 = nodecur;
    if ( count )
    {
      if ( inti_buffer )
      {
        if ( instptr = GetBuffer(nodecur,count) ) 
        {
          Cnodeinst->SetupInst(nodecur,objid,UNDEF,YES);
          lindx0 = nodecur;
        }
      }
      else 
      {
        LockSendParms();
        if ( !Save(NO,NO) )
        {    
          while ( rerun )
          {
            Get_send_parms().Fill(count,relative_index);
            if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Position_ci) )
              rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
            else
              term = NO;
          }
        }
        instptr = Inst_setup(term);
        UnlockSendParms();
        lindx0 = nodecur;
      }
    }
    if ( instptr )
      GenerateEvent(DBO_Read);
  }
  return(lindx0);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance((*parms)[1].GetLong(connection->get_conversion()))) )
    term = sc_prop->Position((*parms)[0].GetLong(connection->get_conversion()));
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ProvGenAttribute_ci"

logical CNode_ProvGenAttribute_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ProvGenAttribute_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->ProvGenAttribute();
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Provide_ci0"

logical CNode_Provide_ci0                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *ph_inst;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) ) 
  {
    if ( !(ph_inst = Get_optimized(lindx0,NO)) )
    {
      LockSendParms();
      if ( !Switch(AUTO) )
      {
        while ( rerun )
        {
          Get_send_parms().Fill(lindx0,global_add);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Provide_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
      }
//      ph_inst = Inst_setup(term,new_instance);
      ph_inst = Inst_setup(term,AUTO);
      UnlockSendParms();
    }
  }
  return(ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( (*parms)[1].GetUChar()  )        // global_add
    {
      if ( sc_prop->ProvideGlobal(
              (*parms)[0].GetLong(connection->get_conversion())) )  // indx0
        term = NO;
    }
    else                                  // not global_add
    {
      if ( sc_prop->Provide(
              (*parms)[0].GetLong(connection->get_conversion())) )  // indx0
        term = NO;
    }
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Provide_ci1"

logical CNode_Provide_ci1                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *ph_inst;
  smcb        *keysmcb = NULL;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( stscusr2() || (keysmcb = CheckSKey_intern()) )
    {  
      stssnof(); // node is acting
      while ( rerun )
      {
        Get_send_parms().Fill(skey,keysmcb,global_add);           // sort_key + keynames
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Provide_ci1) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
      }
      stsrnof();
    }
    ph_inst = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  sc_prop->CheckInstance();
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    if ( !(rerun = sc_prop->CheckInstance()) )
    {
      if ( (*parms)[2].GetUChar()  )        // global_add
      {
        if ( sc_prop->ProvideGlobal(
                  Key((*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData())) )  // ident_key
          term = NO;
      }        
      else                                  // not global_add
      {
        if ( sc_prop->Provide(
                  Key((*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData())) )  // ident_key
          term = NO;
      }        
    }        
  term = (term || SDBERROR) ? YES : NO;
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Provide_ci2"

logical CNode_Provide_ci2                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  void        *ph_inst;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    Save(YES,NO,NO);
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(datarea,nodeinst->get_struct_def(),nodeinst->GetSize(),global_add);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Provide_ci2) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    ph_inst = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop = ((SC_Property *)cso_ptr);
  DBStructDef  *strdef  = sc_prop->GetCurrentTypeDef();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( (*parms)[2].GetUChar()  )        // global_add
    {
      if ( sc_prop->ProvideGlobal(
             Instance((*parms)[0].GetInstance(strdef,sc_prop->Get_instarea(),connection->get_conversion()).GetData())) )   // newitp
        term = NO;
    }
    else                                  // not global_add
    {
      if ( sc_prop->Provide(
             Instance((*parms)[0].GetInstance(strdef,sc_prop->Get_instarea(),connection->get_conversion()).GetData())) )   // newitp
        term = NO;
    }
  }
  term = (term || SDBERROR) ? YES : NO;
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ProvideGUID_ci"

logical CNode_ProvideGUID_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char       *guid_string;
  logical     rerun = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && !(guid_string = GetGUID()) )
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ProvideGUID_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        guid_string = Get_rec_result()[0].GetString();
      UnlockSendParms();
    }
 
  return(guid_string);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    guid_string = sc_prop->ProvideGUID();
  result->Fill(guid_string);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ReadBuffer_ci0"

logical CNode_ReadBuffer_ci0                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  int32         count = AUTO;
  logical      rerun   = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && inti_buffer )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(set_pos0,(int32)direction);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ReadBuffer_ci0) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
    }
    InstBuffer_setup(count);
    UnlockSendParms();
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->ReadBuffer((*parms)[0].GetLong(connection->get_conversion()),   // indx0
                                (*parms)[1].GetLong(connection->get_conversion()));  // direction
  
  sc_prop->FillInstBuffer(result,count);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Refresh_ci"

logical CNode_Refresh_ci                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )  // Check(YES,YES) geht nicht, da der Pfad nach oben nicht eingestellt sein muß.
  {
    if ( nodenode &&  !nodenode->Exist() )
    {
      nodenode->PositionTop();
      nodenode->Get(FIRST_INSTANCE);
    }      
    
    if ( IsActive() )
    {
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Refresh_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
  }
  if ( !term )
    term = GenerateEvent(DBO_Refresh);
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->Refresh(
            );
   
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_RegisterHandle_ci"

logical CNode_RegisterHandle_ci                                ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client term

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_RegisterHandle_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->RegisterHandle();
    
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_RemoveFromCollection_ci"

logical CNode_RemoveFromCollection_ci                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;
#ifndef IF_Class  // client term

  if ( Exist() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_RemoveFromCollection_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->RemoveFromCollection();
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Rename_ci"

logical CNode_Rename_ci                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  smcb        *keysmcb;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( Exist() )
  {
    LockSendParms();
    if ( keysmcb = CheckSKey_intern() )
    {  
      if ( !Save(NO,NO) )
      {
        stssnof(); // node is acting
        while ( rerun )
        {
          Get_send_parms().Fill(new_key,keysmcb);       // sort_key + keynames
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Rename_ci) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
        stsrnof();
      }
    }
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    term = sc_prop->Rename(
              (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData() );  // ident_key
  
  sc_prop->FillInstResult(result,term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Reopen_intern_ci"

logical CNode_Reopen_intern_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    term = YES;
#ifndef IF_Class  // client version
  
  Close_intern();
// danach waere alle weg!   
// wozu wird Reopen_intern noch gebraucht?
  
  Get_send_parms().Fill(prop_path);
    
  if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Reopen_intern_ci) )
    term = Get_rec_result()[0].GetUChar();

  if ( !term )
    Open_setup();  
      
  return(term);

#else             // server version
  
  SC_Property *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( sc_prop->ReopenProperty(
                (*parms)[0].GetString()) )                              // prop_names
    sc_prop = NULL;
  
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_RepairIndex_ci"

logical CNode_RepairIndex_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) && is_collection )
  {
    if ( inti_buffer )
      inti_buffer->Cancel();
    
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(key_name,attrstr);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_RepairIndex_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    InstOrder_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property *sc_prop = ((SC_Property *)cso_ptr);
  smcb        *skeysmcb = NULL;
  char         string[ID_SIZE+1];
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    term =  sc_prop->RepairIndex(
                 (*parms)[0].GetString(),                            // key_names
                 (*parms)[1].GetString() );                          // attrstr
  }
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Reset_ci"

logical CNode_Reset_ci                                         ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( Exist() )
  {
    LockSendParms().Fill();
    
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Reset_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      term = Get_rec_result()[0].GetUChar();
    
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->Reset();
  
  sc_prop->FillInstResult(result,term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ResetExpression_ci"

logical CNode_ResetExpression_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( !Check(YES,NO) )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ResetExpression_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->Lock();
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_ResetWProtect_ci"

logical CNode_ResetWProtect_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( !Exist() )
  {
    LockSendParms().Fill();
    
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ResetWProtect_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      term = Get_rec_result()[0].GetUChar();
    
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->ResetWProtect();
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Save_intern_ci"

logical CNode_Save_intern_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    term = YES;
#ifndef IF_Class  // client version
  if ( !csconnection )                                 SDBERR(517)

  LockSendParms().Fill(switchopt);
    
  if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Save_intern_ci) )
    term = Get_rec_result()[0].GetUChar();
  UnlockSendParms();
    
  if ( switchopt )
    ResetInstance();
  else if ( term )
  {
    Error           saveerr  = SDBError();
    Reset();   
    SDBError() = saveerr;
  }
  
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop = ((SC_Property *)cso_ptr);
  
  term = sc_prop->Save(NO,
                       (*parms)[0].GetUChar()       // switchopt
                      );                       
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetAction_ci"

logical CNode_SetAction_ci                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical    term = YES;
  SDBSET(99)
  return(term);
  // muss ci werden
  // is so erstmal witzlos, da die Action von aussen nicht aufrufbar!


}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetBaseNode_ci"

logical CNode_SetBaseNode_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical                 term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( !cnode_ptr->Check(YES,NO) )
  {
    LockSendParms().Fill((CS_Handle *)cnode_ptr);
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetBaseNode_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop   = (SC_Property *)cso_ptr;
  SC_Property *bn_prop   = (SC_Property *)(*parms)[0].GetHandle()->GetServerPointer();
  
  term = YES;
  if ( sc_prop && bn_prop )
    term = sc_prop->SetBaseNode(bn_prop);
  
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetContextVariables_ci"

logical CNode_SetContextVariables_ci                           ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(context_string);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetContextVariables_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        if ( !(term = Get_rec_result()[0].GetUChar()) )
          term = bnode::SetContextVariables(context_string);
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->SetContextVariables(
                 (*parms)[0].GetString());   // context string
  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetExpression_ci"

logical CNode_SetExpression_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term  = YES;

#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(expression);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetExpression_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->SetSelection(
                 (*parms)[0].GetString());   // expression
  
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetGenAttribute_ci"

logical CNode_SetGenAttribute_ci                               ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(fldnames,(int32)attrtype,attrstr);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetGenAttribute_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    if ( Inst_setup(term) )
      GenerateEvent(DBO_Read);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    char   *propnames = (*parms)[0].GetString();
    int     attrtype  = (*parms)[1].GetLong(connection->get_conversion());
    char   *attrstr   = (*parms)[2].GetString();
    
    term = propnames && attrstr ? sc_prop->SetGenAttribute(attrstr,propnames)
         : propnames            ? sc_prop->SetGenAttribute(attrtype,propnames)
         : attrstr              ? sc_prop->SetGenAttribute(attrstr)
         :                        sc_prop->SetGenAttribute(attrtype);
  } 
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetInstAction_ci"

logical CNode_SetInstAction_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
  SDBSET(99)
  return(term);
  // muss ci werden
  // is so erstmal witzlos, da die Action von aussen nicht aufrufbar!

}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetOrder_ci"

logical CNode_SetOrder_ci                                      ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   rerun = YES;
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) && is_collection )
  {
    if ( inti_buffer )
      inti_buffer->Cancel();
    
    Switch(AUTO);
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(key_name,attrtype,attrstr);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetOrder_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    InstOrder_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property *sc_prop = ((SC_Property *)cso_ptr);
  smcb        *skeysmcb = NULL;
  char         string[ID_SIZE+1];
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    term =  sc_prop->SetOrder(
                 (*parms)[0].GetString(),                            // key_names
                 (*parms)[1].GetLong(connection->get_conversion()),  // attrtype
                 (*parms)[2].GetString() );                          // attrstr
    skeysmcb = sc_prop->GetSortKeySMCB();  
  }
  result->Fill(term,
               skeysmcb ? gvtxbts(string,skeysmcb->smcbname,ID_SIZE) : (char *)NULL);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetType_ci"

logical CNode_SetType_ci                                       ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  char      struct_names[ID_SIZE+1];
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES,NO) )
  {
    gvtxbts(struct_names,strnames,ID_SIZE);
    if ( !IsVariableType(NO) )                       SDBERR(158)
    Switch(AUTO);
    ResetInstance();
    
    while ( rerun )
    {
      LockSendParms().Fill(struct_names);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetType_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
    
    if ( !term )
      term = SetType_intern(struct_names);
  }

  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->SetType(
                 (*parms)[0].GetString()
            );
   
  result->Fill(term);
  
  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_SetWProtect_ci"

logical CNode_SetWProtect_ci                                   ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( IsWrite() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetWProtect_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
    
    nodewrit = NO;
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->SetWProtect();
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Unlock_ci"

logical CNode_Unlock_ci                                        ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( IsPositioned() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Unlock_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->Unlock();
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_UnlockSet_ci"

logical CNode_UnlockSet_ci                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term = YES;

#ifndef IF_Class  // client term

  if ( !chknode || !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_UnlockSet_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
//      ResetInstance();
  }
  
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->UnlockSet();
    
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_UnregisterHandle_ci"

logical CNode_UnregisterHandle_ci                              ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client term

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_UnregisterHandle_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->UnregisterHandle();
    
  result->Fill(term);

  return(rerun);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "CNode_Update_intern_ci"

logical CNode_Update_intern_ci                                 ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical   term = YES;
#ifndef IF_Class  // client version
  if ( !csconnection )                                 SDBERR(517)

  LockSendParms().Fill(nodeinst->get_iselarea(),nodeinst->get_struct_def(),nodeinst->GetSize(), // inst + strname
                        switchopt);
    
  if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Update_intern_ci) )
    if ( !(term = Get_rec_result()[0].GetUChar()) )
      nodeinst->StructureEvents(DBO_Stored);
  UnlockSendParms();
    
  if ( switchopt )
    ResetInstance();
  else if ( term )
  {
    Error           saveerr  = SDBError();
    Reset();   
    SDBError() = saveerr;
  }
  
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop = ((SC_Property *)cso_ptr);
  
  term = sc_prop->CopyData(
      (char *)(*parms)[0].GetFieldInst(sc_prop->GetDescription()->GetDescription(),
                                       sc_prop->Get_instarea(),
                                       connection->get_conversion()).GetData(),   // newitp
      (*parms)[2].GetUChar()                                                      // switchopt
  );                       
//  sc_prop->FillInstResult(result,term);
  result->Fill(term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "COperation_Execute_ci"

logical COperation_Execute_ci                                  ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical        term = YES;
#ifndef IF_Class  // client version

  if ( !get_nodeptr() || IsValid(NO) )
  {
    LockSendParms();
    if ( !csconnection )
      SDBSET(517)
    else  
    {
      Get_send_parms().Fill((CS_Handle *)(CNode *)calling_object->get_nodeptr(),
                            parameters);
   
      if ( !CConnection()->SendCSMessage(this,S_COperation,SF_COperation_Execute_ci) )
        term = Get_rec_result()[0].GetUChar();
    }
    SetupResult_intern(term);
    SetupInstance(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  ParmList      *parmlist;
  SC_Operation *sc_oper = ((SC_Operation *)cso_ptr);
  
// hier müssen wir ggf. noch den Client-Pointer setzen, wenn das ServerHandle noch keinen Client hat und
// mit dem übergebenen Serverhandle identisch ist. Wenn anderes Serverhandle->Katastrophe  
  parmlist = (*parms)[1].GetParmList(connection->get_conversion());
  term = sc_oper->Execute(parmlist);
  delete parmlist;
   
  sc_oper->FillResult(result,term);

  return(NO);

#endif
}

#undef     MOD_ID
#define    MOD_ID  "COperation_Open_ci"

logical COperation_Open_ci                                     ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical       term = YES;

#ifndef IF_Class  // client version
  
  if ( !Operation::Open(prophdl_ref) )
  {
    if ( calling_object->get_nodeptr()->IsLocalNode() )
      SDBSET(526)
    else
      if ( !csconnection )
        SDBSET(517)
      else      
      {
        LockSendParms().Fill((CS_Handle *)(CNode *)calling_object->get_nodeptr());
        InitHandle();
    
        if ( !CConnection()->SendCSMessage(this,S_COperation,SF_COperation_Open_ci) )
          if ( !(term = Get_rec_result()[0].GetUChar()) )
            SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        UnlockSendParms();
      }
  }

  return(term);
  
#else             // server version
  
  SC_Operation *sc_oper;
  CS_Handle    *handle = parms->GetHandle();
  
  if ( sc_oper = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideOperation(
                     handle->GetClientObject()
                 ) )
  {
    handle->SetServerPointer(sc_oper);
    *result->GetHandle() = *handle;
    term = NO;
  }
  result->Fill(term);
  return(NO);


#endif

}

#undef     MOD_ID
#define    MOD_ID  "COperation_ProvExpression_ci1"

logical COperation_ProvExpression_ci1                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical        term = YES;
#ifndef IF_Class  // client version

  if ( !get_nodeptr() || IsValid(NO) )
  {
    LockSendParms();
    if ( !csconnection )
      SDBSET(517)
    else  
    {    
      Get_send_parms().Fill(expr_string);
    
      if ( !CConnection()->SendCSMessage(this,S_COperation,SF_COperation_ProvExpression_ci1) )
        term = Get_rec_result()[0].GetUChar();
    }
    SetupResult_intern(term);
    UnlockSendParms();
    set_expression(expr_string);
  }
  return(term);
  
#else             // server version
  
  SC_Operation *sc_oper = ((SC_Operation *)cso_ptr);
  
  ParmList *parmlist = (*parms)[1].GetParmList(connection->get_conversion());
  term =  sc_oper->ProvideExpression((*parms)[0].GetString()
          );
  delete parmlist;
   
  sc_oper->FillResult(result,term);

  return(NO);

#endif

}

#undef     MOD_ID
#define    MOD_ID  "COperation_ProvExpression_ci2"

logical COperation_ProvExpression_ci2                          ( CS_Connection *connection, void *cso_ptr, CSInstanceList *parms, CSInstanceList *result)
{
  logical        term = YES;
#ifndef IF_Class  // client version
  
  SDBSET(999)  // kommt später
  return(term);
  
#else             // server version
  
  return(NO);

#endif


}

