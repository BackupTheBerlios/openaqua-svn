/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CACObject

\brief    Database Object handle
          Database  Object  handle  (Object  handle) are necessary for accessing
          data  in an Database Object. It  allows accessing extents that contain
          the  main instances  in a  Database Object.  The object handle for the
          root  Database Object it the database  handle ({\b {.r DBHandle}}) and
          need not to be opened explicitly. 
          An  object handle is necessary for opening collection handles (PI) for
          accessing object instances stored in extents.  
          Moreover;  the object handle  administrates transactions. Transactions
          can be started and stopped for each object handle. 
          The  object handle  allows also  defining Database Object versions for
          creating and accessing version slices for a Database Object.

\date     $Date: 2006/08/26 12:07:29,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CACObject"

#include  <popa7.h>
#include  <igvtx.h>
#include  <sofifct.h>
#ifndef   DLL_ACObject_HPP
#define   DLL_ACObject_HPP
#include  <sACObject.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_CNode_HPP
#define   DLL_CNode_HPP
#include  <sCNode.hpp>
#include  <sDLL.h>
#endif
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCACObject.hpp>
#include  <sCClient.hpp>
#include  <sCDBHandle.hpp>
#include  <sCS_Connection.hpp>
#include  <sClientConnection.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <sCACObject.hpp>


/******************************************************************************/
/**
\brief  CACObject - Create an Database Object handle



-------------------------------------------------------------------------------
\brief  ci - 



\param  dbhandle - Database handle
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CACObject"

     CACObject :: CACObject (DBHandle *dbhandle, PIACC accopt, uint16 version_nr )
                     : CSHandle (dbhandle->GetClientDBHandle()->IsValid() ? dbhandle->GetClientDBHandle()->get_csconnection() : NULL ),
ACObject(dbhandle,accopt,version_nr),
  cdbhandle(dbhandle->GetClientDBHandle()),
  topnode_list(new DLL(CNode))
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

/******************************************************************************/
/**
\brief  ci1 - 



\param  obhandle - Database Object handle
\param  objid - Instance or index identity
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CACObject"

     CACObject :: CACObject (ACObject *obhandle, int32 objid, PIACC accopt, uint16 version_nr )
                     : CSHandle (obhandle->GetClientACObject()->IsValid() ? obhandle->GetClientACObject()->get_csconnection() : NULL),
ACObject(obhandle,objid,accopt,version_nr),
 cdbhandle(obhandle->GetDBHandle()->GetClientDBHandle()),
  topnode_list(new DLL(CNode))
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

/******************************************************************************/
/**
\brief  ci2 - 



\param  obhandle - Database Object handle
\param  objname - 
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CACObject"

     CACObject :: CACObject (ACObject *obhandle, char *objname, PIACC accopt, uint16 version_nr )
                     : CSHandle (obhandle->GetClientACObject()->IsValid() ? obhandle->GetClientACObject()->get_csconnection() : NULL),
ACObject(obhandle,objname,accopt,version_nr),
 cdbhandle(obhandle->GetDBHandle()->GetClientDBHandle()),
  topnode_list(new DLL(CNode))
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

/******************************************************************************/
/**
\brief  i04 - 



\param  cs_connection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CACObject"

     CACObject :: CACObject (CS_Connection *cs_connection )
                     : CSHandle (cs_connection),
ACObject(),
  cdbhandle(NULL),
  topnode_list(new DLL(CNode))
{

  InitHandle();

}

/******************************************************************************/
/**
\brief  i3 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CACObject"

     CACObject :: CACObject ( )
                     : CSHandle (),
ACObject(),
  cdbhandle(NULL),
  topnode_list(NULL)
{

  InitHandle();


}

/******************************************************************************/
/**
\brief  ChangeTimeStamp - Change time stamp for current version



\return term - Termination code

\param  version_nr - Internal version number
\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeTimeStamp"

logical CACObject :: ChangeTimeStamp (uint16 version_nr, dttm timestamp )
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

/******************************************************************************/
/**
\brief  CloseObject - Close Object Handle



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseObject"

logical CACObject :: CloseObject ( )
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

/******************************************************************************/
/**
\brief  CreateNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  dbextdef - Extent definition
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *CACObject :: CreateNode (DBExtend *dbextdef, PIACC accopt )
{
  node          *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new CNode(this,dbextdef,accopt)) ) SDBCERR

RECOVER
  delete nodeptr;
  nodeptr = NULL;

ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  extnames - Extent name
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *CACObject :: CreateNode (char *extnames, PIACC accopt )
{
  DBExtend      *dbext;
  node          *nodeptr = NULL;
  TypeKey     tkey(GetDictionary(),extnames);
  if ( (dbext = GetDictionary()->ProvideExtendDef(tkey,GetSchemaVersion())) )
    nodeptr = CreateNode(dbext,accopt);

  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreatePathNode - Create Vies and path nodes

        In client/server, Function is also used for crating views!!

\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *CACObject :: CreatePathNode (char *prop_path, OperEnvironment *operenv, PIACC accopt )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new CNode(this,prop_path,accopt)) ) SDBCERR
                                                     

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  parm_bnf - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *CACObject :: CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv, PIACC accopt )
{
  node                   *nodeptr = NULL;
  nodeptr = CreatePathNode(parm_bnf->StringValue(),operenv,accopt);
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateTempNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbfield_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempNode"

node *CACObject :: CreateTempNode (DBFieldDef *dbfield_def )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  basenode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempNode"

node *CACObject :: CreateTempNode (node *basenode )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  basenode - 
\param  grouping_rule - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempNode"

node *CACObject :: CreateTempNode (node *basenode, char *grouping_rule )
{
  node                   *nodeptr = NULL;

  return(nodeptr);
}

/******************************************************************************/
/**
\brief  DeleteExtent - Delete extent



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtent"

logical CACObject :: DeleteExtent (char *extnames )
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

/******************************************************************************/
/**
\brief  DeleteExtentRef - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtentRef"

logical CACObject :: DeleteExtentRef (char *extnames )
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
  return(term);
}

/******************************************************************************/
/**
\brief  ExecObjCtxFunc - 



\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecObjCtxFunc"

logical CACObject :: ExecObjCtxFunc (char *fnames, char *w_parms )
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

/******************************************************************************/
/**
\brief  ExtentExist - 



\return cond - 

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtentExist"

logical CACObject :: ExtentExist (char *extnames )
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

/******************************************************************************/
/**
\brief  GetAccess - Get access mode for object handle



\return accopt - Access mode

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccess"

PIACC CACObject :: GetAccess ( )
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

/******************************************************************************/
/**
\brief  GetClientACObject - Get client handle



\return cobhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientACObject"

CACObject *CACObject :: GetClientACObject ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetClientConnect - 



\return cl_connection - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientConnect"

ClientConnection *CACObject :: GetClientConnect ( )
{

  return ( csconnection ? (ClientConnection *)csconnection
                      : (ClientConnection *)NULL       );

}

/******************************************************************************/
/**
\brief  GetConnectionClient - 



\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient &CACObject :: GetConnectionClient ( )
{

  return(CSHandle::GetClient());

}

/******************************************************************************/
/**
\brief  GetExtent - Provide extent form Database Object

        The  function returns the name of the n-th extent in the list of extents
        that  are allocated for the database object. The collection of allocated
        extents  does not necessarily include  all defined extents. Extent names
        are provided in alphabetic order.
        After  providing the last extent name  the function returns NULL for the
        next extent name.

\return extentname - Extent name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtent"

char *CACObject :: GetExtent (int32 indx0 )
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

/******************************************************************************/
/**
\brief  GetExtentList - 



\return extent_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentList"

GSRT(ExtentListEntry) *CACObject :: GetExtentList ( )
{
  GSRT(ExtentListEntry) *   extent_list = NULL;
// not yet supported in CS
  return(extent_list);
}

/******************************************************************************/
/**
\brief  GetModCount - 



\return modcount - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 CACObject :: GetModCount (EB_Number entnr )
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

/******************************************************************************/
/**
\brief  GetTALevel - 



\return talevel - Transaction level

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTALevel"

int16 CACObject :: GetTALevel ( )
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

/******************************************************************************/
/**
\brief  GetTimeStamp - Get date/time for version



\return timestamp - Date/time value

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimeStamp"

dttm CACObject :: GetTimeStamp (uint16 version_nr )
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

/******************************************************************************/
/**
\brief  GetVersion - Get version number for the time point



\return version_nr - Internal version number

\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 CACObject :: GetVersion (dttm timestamp )
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

/******************************************************************************/
/**
\brief  InitHandle - 




\param  alloc_buffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandle"

void CACObject :: InitHandle (logical alloc_buffer )
{

BEGINSEQ
  if ( CSHandle::InitHandle(alloc_buffer) )           ERROR
  
  if ( alloc_buffer )  // nur für client/server
    SetClientPointer(this); 
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  NewVersion - Create new version



\return term - Termination code

\param  timestamp - Date/time value
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewVersion"

logical CACObject :: NewVersion (dttm timestamp, uint16 version_nr )
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

/******************************************************************************/
/**
\brief  PopResult - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopResult"

logical CACObject :: PopResult ( )
{
  logical   term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( !csconnection )                               ERROR

  term = CConnection()->PopResult();
  csconnection->UnlockSend();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PushResult - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushResult"

logical CACObject :: PushResult ( )
{
  logical   term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( !csconnection )                               ERROR

  csconnection->LockSend();
  term = CConnection()->PushResult();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetOverload - 



\return overload_opt - 

\param  overload_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOverload"

logical CACObject :: SetOverload (logical overload_opt )
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

/******************************************************************************/
/**
\brief  SetUserDefinedIdentity - 



\return term - Termination code

\param  identity_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserDefinedIdentity"

logical CACObject :: SetUserDefinedIdentity (logical identity_opt )
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

/******************************************************************************/
/**
\brief  SetVersion - Set current version



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical CACObject :: SetVersion (uint16 version_nr )
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

/******************************************************************************/
/**
\brief  ci1 - 



\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical CACObject :: SetVersion (dttm timestamp )
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

/******************************************************************************/
/**
\brief  ci2 - 



\param  date - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical CACObject :: SetVersion (dbdt date )
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

/******************************************************************************/
/**
\brief  StartTA - 



\return talevel - Transaction level

\param  ext_TA - External transaction
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartTA"

int16 CACObject :: StartTA (logical ext_TA, int16 w_maxnum )
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

/******************************************************************************/
/**
\brief  StopTA - 



\return term - Termination code

\param  talevel - Transaction level
\param  error_case_w - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopTA"

logical CACObject :: StopTA (int16 talevel, logical error_case_w )
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

/******************************************************************************/
/**
\brief  UninitHandle - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UninitHandle"

void CACObject :: UninitHandle ( )
{

  CSHandle::UninitHandle();

}

/******************************************************************************/
/**
\brief  UpdateTimestamp - 



\return timestamp_enabled - 

\param  timestamp_enabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTimestamp"

logical CACObject :: UpdateTimestamp (logical timestamp_enabled )
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
  return(timestamp_enabled);
}

/******************************************************************************/
/**
\brief  VersionCount - Get number of versions



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCount"

int32 CACObject :: VersionCount ( )
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

/******************************************************************************/
/**
\brief  VersionIntervall - Get version interval



\return timeint - Time interval

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionIntervall"

INTERVAL(dttm) CACObject :: VersionIntervall (uint16 version_nr )
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

/******************************************************************************/
/**
\brief  ~CACObject - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CACObject"

     CACObject :: ~CACObject ( )
{

  if ( db_handle )
    CloseObject();
  


}


