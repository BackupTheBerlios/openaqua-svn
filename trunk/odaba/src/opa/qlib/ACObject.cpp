/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACObject

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

\date     $Date: 2006/08/26 12:06:50,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACObject"

#include  <popa7.h>
#include  <coctp.h>
#include  <idbd.h>
#ifndef   P_ODC_NamedObject_HPP
#define   P_ODC_NamedObject_HPP
#include  <sPI.hpp>
class       ODC_NamedObject;
PI_dcl     (ODC_NamedObject)
#endif
#ifndef   P_SDB_ObjectID_HPP
#define   P_SDB_ObjectID_HPP
#include  <sPI.hpp>
class       SDB_ObjectID;
PI_dcl     (SDB_ObjectID)
#endif
#ifndef   DLL_ACObject_HPP
#define   DLL_ACObject_HPP
#include  <sACObject.hpp>
#include  <sDLL.h>
#endif
#ifndef   GSRT_ExtentListEntry_HPP
#define   GSRT_ExtentListEntry_HPP
#include  <sGSRT.h>
#endif
#include  <sACNode.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCACObject.hpp>
#include  <sCClient.hpp>
#include  <sCTX_Object.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sDictionary.hpp>
#include  <sError.hpp>
#include  <sLACObject.hpp>
#include  <sODC_NamedObject.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sRessourceLock.hpp>
#include  <sStructAccess.hpp>
#include  <sbnode.hpp>
#include  <sexd.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <sACObject.hpp>


/******************************************************************************/
/**
\brief  ACObject - Create an Database Object handle



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbhandle - Database handle
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACObject"

     ACObject :: ACObject (DBHandle *dbhandle, PIACC accopt, uint16 version_nr )
                     : ObjectReference(YES),
  ident(OBJECT_ID),
  obj_handle(NULL), 
  db_handle(NULL), 
  object_list(new DLL(ACObject)()),
  objid_pi(NULL), 
  objname_pi(NULL),
  access_mode(PI_undefined), 
  obj_overload(NO),
  resource(NULL),
  version(UNDEF),
  is_global_object(NO),
  update_timestamp(YES),
  nstring(),
  db_hdl(NULL),
  ocontext(NULL),
  userdef_id(NO),
  event_handling(YES),
  context_path(NULL),
  ds_handle(NULL),
  rta_count(0),
  data_version(UNDEF),
  nresult(NULL),
  sys_version(CUR_SYSVERSION)
{

  Initialize(dbhandle,accopt,version_nr);


}

/******************************************************************************/
/**
\brief  i04 - 



\param  obhandle_ref - 
\param  gl_object - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACObject"

     ACObject :: ACObject (ACObject &obhandle_ref, logical gl_object )
                     : ObjectReference(YES),
  ident(OBJECT_ID),
  obj_handle(obhandle_ref.get_obj_handle()), 
  db_handle(obhandle_ref.get_db_handle()), 
  object_list(new DLL(ACObject)()),
  objid_pi(NULL), 
  objname_pi(NULL),
  access_mode(obhandle_ref.get_access_mode()), 
  obj_overload(NO),
  resource(NULL),
  version(obhandle_ref.get_version()),
  is_global_object(gl_object),
  update_timestamp(YES),
  nstring(),
  db_hdl(NULL),
  ocontext(NULL),
  userdef_id(NO),
  event_handling(YES),
  context_path(NULL),
  ds_handle(NULL),
  rta_count(0),
  data_version(UNDEF),
  nresult(NULL),
  sys_version(CUR_SYSVERSION)
{

  Initialize();


}

/******************************************************************************/
/**
\brief  i1 - 



\param  obhandle - Database Object handle
\param  objid - Instance or index identity
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACObject"

     ACObject :: ACObject (ACObject *obhandle, int32 objid, PIACC accopt, uint16 version_nr )
                     : ObjectReference(YES),
  ident(OBJECT_ID),
  obj_handle(NULL), 
  db_handle(obhandle->get_db_handle()),
  object_list(new DLL(ACObject)()),
  objid_pi(NULL), 
  objname_pi(NULL),
  access_mode(accopt), 
  obj_overload(NO),
  resource(NULL),
  version(version_nr),
  is_global_object(NO),
  update_timestamp(YES),
  nstring(),
  db_hdl(NULL),
  ocontext(NULL),
  userdef_id(NO),
  event_handling(YES),
  context_path(NULL),
  ds_handle(NULL),
  rta_count(0),
  data_version(obhandle->get_data_version()),
  nresult(NULL),
  sys_version(CUR_SYSVERSION)

{

  Initialize();

}

/******************************************************************************/
/**
\brief  i2 - 



\param  obhandle - Database Object handle
\param  obname - 
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACObject"

     ACObject :: ACObject (ACObject *obhandle, char *obname, PIACC accopt, uint16 version_nr )
                     : ObjectReference(YES),
  ident(OBJECT_ID),
  obj_handle(NULL), 
  db_handle(obhandle->get_db_handle()),
  object_list(new DLL(ACObject)()),
  objid_pi(NULL), 
  objname_pi(NULL), 
  access_mode(accopt), 
  obj_overload(NO),
  resource(NULL),
  version(version_nr),
  is_global_object(NO),
  update_timestamp(YES),
  nstring(),
  db_hdl(NULL),
  ocontext(NULL),
  userdef_id(NO),
  event_handling(YES),
  context_path(NULL),
  ds_handle(NULL),
  rta_count(0),
  data_version(obhandle->get_data_version()),
  nresult(NULL),
  sys_version(CUR_SYSVERSION)
{

  Initialize();


}

/******************************************************************************/
/**
\brief  i3 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACObject"

     ACObject :: ACObject ( )
                     : ObjectReference(YES),
  ident(OBJECT_ID),
  obj_handle(NULL),
  db_handle(NULL),
  object_list(new DLL(ACObject)()),
  objid_pi(NULL),
  objname_pi(NULL),
  access_mode(PI_undefined),
  obj_overload(NO),
  resource(NULL),
  version(0),
  is_global_object(NO),
  update_timestamp(YES),
  nstring(),
  db_hdl(NULL),
  ocontext(NULL),
  userdef_id(NO),
  event_handling(YES),
  context_path(NULL),
  ds_handle(NULL),
  rta_count(0),
  data_version(UNDEF),
  nresult(NULL),
  sys_version(CUR_SYSVERSION)
{

  db_hdl = this;    
  sdb_error = &SDBError();
  sdb_error->ResetError();


}

/******************************************************************************/
/**
\brief  AddEventNode - 



\return term - Termination code

\param  bnodeptr - 
\param  seq_opt - Sequence option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEventNode"

logical ACObject :: AddEventNode (bnode *bnodeptr, int8 seq_opt )
{
  bnode                  *curnode = NULL;
  bnode                  *child   = NULL;
  logical                 term    = NO;
BEGINSEQ
  if ( !bnodeptr->IsValid() )                        ERROR
  if ( !seq_opt && bnodeptr->get_registered() )      LEAVESEQ
  bnodeptr->set_registered(YES);
      
  if ( seq_opt )
  {
    event_queue.GoTop();
    while ( curnode = event_queue.GetNext() )
    {
      if ( curnode = CheckEventNode(curnode) )
      {
        if ( curnode == (bnode *)bnodeptr->get_nodenode() )
          break;
        if ( seq_opt == 1 && (bnode *)curnode->get_nodenode() == bnodeptr )
        {
          child = curnode;
          curnode = NULL;
          break;
        }
      }
      else 
        event_queue.GoTop();
    }
    if ( child || curnode )
    {
      event_queue.Remove(bnodeptr);
      event_queue.Find(curnode ? curnode : child);
      if ( (seq_opt < 0 && curnode) || (seq_opt > 0 && child) )
        event_queue.InsertBefore(bnodeptr);
      else
        event_queue.InsertAfter(bnodeptr);
      LEAVESEQ
    }
  }
  if ( !event_queue.Find(bnodeptr) )
    event_queue.AddTail(bnodeptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddPathNode - 



\return term - Termination code

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddPathNode"

logical ACObject :: AddPathNode (bnode *bnodeptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !bnodeptr->IsValid() )                        ERROR
    
  path_nodes.AddTail(bnodeptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical ACObject :: ChangeTimeStamp (uint16 version_nr, dttm timestamp )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CheckAccess - 



\return term - Termination code

\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAccess"

logical ACObject :: CheckAccess (PIACC accmode )
{
  logical                 term = NO;
BEGINSEQ
  if ( db_handle && db_handle->get_access_mode() == PI_Read &&
       accmode > PI_Read                          )  SDBERR(120)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckEventNode - 



\return bnodeptr - 

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEventNode"

bnode *ACObject :: CheckEventNode (bnode *bnodeptr )
{

BEGINSEQ
// das müssen wir klären, da dieser Fall nicht auftreten darf
// weak-typed nodes verhalten sich da aber manchmal komisch
  if ( !bnodeptr->IsValid() )                        ERROR
  if ( !bnodeptr->get_proc_event_handler() )         ERROR

  bnodeptr->set_registered(YES);  // damit er auch wirklich rausgeschmissen wird

RECOVER
  RemoveEventNode(bnodeptr);
  bnodeptr = NULL;
ENDSEQ
  return(bnodeptr);
}

/******************************************************************************/
/**
\brief  CloseObject - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseObject"

logical ACObject :: CloseObject ( )
{
  bnode      *nodeptr;
BEGINSEQ
  SDBRESET
  
  while ( nodeptr = path_nodes.RemoveTail() )
  {
    if ( nodeptr->IsValid() || !SDBERROR )
      delete nodeptr;
    else
      SDBRESET
  }
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  CreateACObject - 



\return obhandle - Database Object handle
-------------------------------------------------------------------------------
\brief  i1 - 



\param  objid - Instance or index identity
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *ACObject :: CreateACObject (int32 objid, PIACC accopt, uint16 version_nr )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i2 - 



\param  obname - 
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *ACObject :: CreateACObject (char *obname, PIACC accopt, uint16 version_nr )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  CreateContext - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContext"

logical ACObject :: CreateContext ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( ocontext ) 
  {
    if ( !ocontext->get_high_ctx() )
      get_ocontext()->set_high_ctx(obj_handle ? (CTX_DBBase *)obj_handle->get_ocontext()
                                              : (CTX_DBBase *)db_handle->get_context());
    LEAVESEQ
  }
    
  if ( !(ocontext = DLLHandle()->CreateObjCtx(GetCTXIPath(),UNDEF)) )
                                                     ERROR
  ocontext->Initialize(this,obj_handle ? (CTX_DBBase *)obj_handle->get_ocontext()
                                       : (CTX_DBBase *)db_handle->get_context());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbextdef - Extent definition
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *ACObject :: CreateNode (DBExtend *dbextdef, PIACC accopt )
{


  return(NULL);
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

node *ACObject :: CreateNode (char *extnames, PIACC accopt )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  CreatePathNode - 



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

node *ACObject :: CreatePathNode (char *prop_path, OperEnvironment *operenv, PIACC accopt )
{


  return(NULL);
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

node *ACObject :: CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv, PIACC accopt )
{


  return(NULL);
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

node *ACObject :: CreateTempNode (DBFieldDef *dbfield_def )
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

node *ACObject :: CreateTempNode (node *basenode )
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

node *ACObject :: CreateTempNode (node *basenode, char *grouping_rule )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  DeleteExtendRef - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtendRef"

logical ACObject :: DeleteExtendRef (char *extnames )
{

  return(YES);

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

logical ACObject :: DeleteExtent (char *extnames )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  DiffersFrom - 



\return cond - 

\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiffersFrom"

logical ACObject :: DiffersFrom (ACObject *obhandle )
{
  logical               cond = NO;
BEGINSEQ
  if ( this == obhandle )                           LEAVESEQ
  
  if ( !this || !obhandle )                         ERROR
  
  if ( IsServerObject() ^ obhandle->IsServerObject() )
                                                    ERROR
  if ( db_handle->DiffersFrom(obhandle->GetDBHandle()) ) 
                                                    ERROR

  // comparing database objects is still missing
  

RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  DisableEventHandling - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableEventHandling"

void ACObject :: DisableEventHandling ( )
{

  event_handling = NO;

}

/******************************************************************************/
/**
\brief  EnableEventHandling - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableEventHandling"

void ACObject :: EnableEventHandling ( )
{

  event_handling = YES;

}

/******************************************************************************/
/**
\brief  EventHandling - 



\return event_handling - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventHandling"

logical ACObject :: EventHandling ( )
{

  return(this ? event_handling : NO);

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

logical ACObject :: ExecObjCtxFunc (char *fnames, char *w_parms )
{
  logical                 term = NO;
BEGINSEQ
  if ( !ocontext )                                   ERROR
    
  ocontext->SetParm(w_parms);
  if ( ocontext->ExecuteFunction(fnames) )
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
\brief  ExecuteExpression - 



\return prophdl - 

\param  resobj - 
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteExpression"

PropertyHandle ACObject :: ExecuteExpression (ACObject *resobj, char *expression )
{
  PropertyHandle      ph;
  Operation      op;
  if ( !op.ProvExpression(GetDictionary(),resobj,this,expression) )
    if ( !op.Execute(this,NULL) )
      ph.Open(&op);


  return(&ph);
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

logical ACObject :: ExtentExist (char *extnames )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  GetAccess - Get access mode for object handle



\return accopt - Access mode

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccess"

PIACC ACObject :: GetAccess ( )
{
  PIACC     accopt = PI_undefined;
BEGINSEQ
  if ( !this )                                     SDBERR(70)
  accopt = access_mode;
RECOVER

ENDSEQ
  return(accopt);
}

/******************************************************************************/
/**
\brief  GetCTXIPath - 



\return ctxi_path - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCTXIPath"

char *ACObject :: GetCTXIPath ( )
{
  char             *string = NULL;
BEGINSEQ
  if ( context_path || db_handle->get_system_env() == YES )
                                                     LEAVESEQ
  if ( db_handle == (DBHandle *)GetDictionary() )
  {
    nstring.Resize(RET_STR_LEN);
    string = GetDictionary()->GetDLLPath((char *)nstring,"ctxi");
  }
  else
    string = GetDictionary()->GetCTXIPath();

  if ( !string )                                     ERROR
  context_path = strdup(string);
RECOVER
  context_path = NULL;
ENDSEQ
  return(context_path);
}

/******************************************************************************/
/**
\brief  GetClient - 



\return odaba_client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClient"

CClient *ACObject :: GetClient ( )
{
  CClient     *cc = NULL;
  if ( GetClientACObject() )
    cc = (CClient *)GetClientACObject()->get_csconnection();
  return(cc);
}

/******************************************************************************/
/**
\brief  GetClientACObject - 



\return cobhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientACObject"

CACObject *ACObject :: GetClientACObject ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetConnectionClient - 



\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient &ACObject :: GetConnectionClient ( )
{

  return(GetMainClient());

}

/******************************************************************************/
/**
\brief  GetCurrentSystemVersion - 



\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentSystemVersion"

uint16 ACObject :: GetCurrentSystemVersion ( )
{

  return ( sys_version );

}

/******************************************************************************/
/**
\brief  GetDBHandle - Get database handle



\return dbhandle - Database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBHandle"

DBHandle *ACObject :: GetDBHandle ( )
{

  return( this ? db_handle : NULL );

}

/******************************************************************************/
/**
\brief  GetDBObjectHandle - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBObjectHandle"

DBObjectHandle *ACObject :: GetDBObjectHandle ( )
{
  DBObjectHandle  stat_dbh_ptr;  

  return( this ? (DBObjectHandle *)&db_hdl : &stat_dbh_ptr );

}

/******************************************************************************/
/**
\brief  GetDataSource - 



\return dahandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataSource"

DataSourceHandle *ACObject :: GetDataSource ( )
{

  return( this ? ds_handle : NULL );

}

/******************************************************************************/
/**
\brief  GetDictionary - Get dictionary handle



\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

Dictionary *ACObject :: GetDictionary ( )
{

  return ( this && db_handle ? db_handle->get_dictionary() : NULL);

}

/******************************************************************************/
/**
\brief  GetErrorCode - 



\return errcd - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorCode"

int32 ACObject :: GetErrorCode ( )
{
  Error                *error;
  int32                 err = 0;
  if ( this )
  {
    error = sdb_error ? sdb_error : &SDBError(); 
    err = error->CheckError();
  }

  return(err);
}

/******************************************************************************/
/**
\brief  GetExtent - Provide extent form Database Object



\return ext_name - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtent"

char *ACObject :: GetExtent (int32 indx0 )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetExtentList - 



\return extent_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentList"

GSRT(ExtentListEntry) *ACObject :: GetExtentList ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetHighObject - Get parent object



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighObject"

ACObject *ACObject :: GetHighObject ( )
{

  return(obj_handle);

}

/******************************************************************************/
/**
\brief  GetHighObjectPtr - 



\return pobjptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighObjectPtr"

ACObject **ACObject :: GetHighObjectPtr ( )
{

  return(&obj_handle);

}

/******************************************************************************/
/**
\brief  GetID_SIZE - 



\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID_SIZE"

int16 ACObject :: GetID_SIZE ( )
{

  return(GetDictionary()->GetID_SIZE());

}

/******************************************************************************/
/**
\brief  GetLocalACObject - 



\return lobhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalACObject"

LACObject *ACObject :: GetLocalACObject ( )
{

  return(NULL);

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

int16 ACObject :: GetModCount (EB_Number entnr )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetNodePtr - 



\return nodeptr - 

\param  prop_path - Property path
\param  operenv - 
\param  path_type - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node *ACObject :: GetNodePtr (char *prop_path, OperEnvironment *operenv, FunctionTypes &path_type, PIACC accopt )
{
  logical      is_transient = NO;
  node        *nodeptr = NULL;
  node       **pnodeptr = NULL;

BEGINSEQ
  nstring = prop_path;
  if ( prop_path = strchr(nstring,'.') )
  {
    *prop_path = 0;
    prop_path++;
  }
           
  if ( !(nodeptr = GetStartNode(operenv,nstring,path_type,accopt)) )
                                                    ERROR
  if ( prop_path )
    if ( pnodeptr = nodeptr->GetNodePtr(prop_path,&is_transient) )
      nodeptr = *pnodeptr;

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetObject - Get Database Object



\return objname - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObject"

char *ACObject :: GetObject (int32 indx0 )
{
  char    *objname = NULL;
BEGINSEQ
  if ( !this )                                       SDBERR(70)

  if ( !objname_pi->Get(indx0) )                     ERROR
  if ( !(objname = objname_pi->ExtractKey()) )       ERROR
  objname = set_result_string(objname,RET_STR_LEN);
RECOVER

ENDSEQ
  return(objname);
}

/******************************************************************************/
/**
\brief  GetOutputResult - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOutputResult"

char *ACObject :: GetOutputResult ( )
{
  char       *string = "";
  if ( nresult )
    string = *nresult;

  return (string);
}

/******************************************************************************/
/**
\brief  GetResourceType - 



\return res_type - 

\param  local_ressources - Resource type
\param  cpath_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceType"

ResourceTypes ACObject :: GetResourceType (ResourceTypes local_ressources, char *cpath_w )
{
  ResourceTypes     res_type = RES_automatic;
  logical           local_name = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(521)
 
  if ( local_ressources == RES_server && !GetClientACObject() )
                                                     SDBERR(519)
  if ( cpath_w && *cpath_w != '%' )
    local_name = YES;
    
  if ( local_ressources == RES_automatic ) 
    local_ressources = GetClientACObject() && !local_name ? RES_server : RES_local;
                      

RECOVER
  local_ressources = RES_automatic;
ENDSEQ
  return(local_ressources);
}

/******************************************************************************/
/**
\brief  GetSMCB - Get simple structure definition



\return smcbptr - Pointer to general structure definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMCB"

smcb *ACObject :: GetSMCB (TypeKey &tkey )
{
  smcb     *smcbptr = NULL;
BEGINSEQ
  if ( !this )                                     SDBERR(70)

  if ( db_handle && db_handle->get_dictionary() )
    smcbptr = db_handle->get_dictionary()->ProvideStructDef(tkey);
RECOVER

ENDSEQ
  return(smcbptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  strnames - Type name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMCB"

smcb *ACObject :: GetSMCB (char *strnames, int32 nsid )
{
  TypeKey       tkey(strnames,nsid);
  return( GetSMCB(tkey) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMCB"

smcb *ACObject :: GetSMCB (char *scoped_name )
{
  TypeKey       tkey(GetDictionary(),scoped_name);
  return( GetSMCB(tkey) );

}

/******************************************************************************/
/**
\brief  GetSchemaVersion - 



\return schemaversion - Scheme version

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSchemaVersion"

uint16 ACObject :: GetSchemaVersion ( )
{

  return(db_handle ? db_handle->GetSchemaVersion() 
                   : GetCurrentSystemVersion()     );

}

/******************************************************************************/
/**
\brief  GetStartNode - 



\return nodeptr - 

\param  operenv - 
\param  propnames - 
\param  path_type - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStartNode"

node *ACObject :: GetStartNode (OperEnvironment *operenv, char *propnames, FunctionTypes &path_type, PIACC accopt )
{
  node        *nodeptr = NULL;

  switch ( path_type )
  {
    case FT_Extent   : nodeptr = CreateNode(propnames,accopt); 
                       break;
    case FT_Global   : nodeptr = GetDictionary()->GetGlobalVariable(propnames)->get_nodeptr(); 
                       break;
    case FT_Variable : nodeptr = operenv->GetVariableNode(propnames); 
                       break;
    case FT_Parameter: nodeptr = operenv->GetParameterNode(propnames); 
                       break;
  }

  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetStructAccess - 



\return structacc - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *ACObject :: GetStructAccess (int16 sid )
{


  return (NULL);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  strdefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *ACObject :: GetStructAccess (DBStructDef *strdefptr )
{
  StructAccess  *structacc = NULL;
BEGINSEQ
  if ( !strdefptr )                                  ERROR
  if ( !strdefptr->smcbityp ) // 20.8.98, Optimierung
    if ( !GetDictionary()->ProvideStructDef(strdefptr->smcbname) )
                                                     ERROR
  structacc = GetStructAccess(strdefptr->smcbityp);

RECOVER
  structacc = NULL;
ENDSEQ
  return(structacc);
}

/******************************************************************************/
/**
\brief  GetSystemVersion - 



\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemVersion"

uint16 ACObject :: GetSystemVersion ( )
{

  return(db_handle ? db_handle->GetSystemVersion() 
                   : GetCurrentSystemVersion()     );

}

/******************************************************************************/
/**
\brief  GetTALevel - 



\return talevel - Transaction level

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTALevel"

int16 ACObject :: GetTALevel ( )
{


  return ( 0 );

}

/******************************************************************************/
/**
\brief  GetThisDBHandle - 



\return dbhandle - Database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThisDBHandle"

DBHandle *ACObject :: GetThisDBHandle ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetThisDictionary - 



\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThisDictionary"

Dictionary *ACObject :: GetThisDictionary ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetThisObject - 



\return object - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThisObject"

ACObject *ACObject :: GetThisObject ( )
{


  return(this);
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

dttm ACObject :: GetTimeStamp (uint16 version_nr )
{


  return dttm();
}

/******************************************************************************/
/**
\brief  GetTypes - 



\return term - Termination code

\param  scoped_name - 
\param  itypptr - 
\param  stypptr - 
\param  atypptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypes"

logical ACObject :: GetTypes (char *scoped_name, int16 *itypptr, int16 *stypptr, int16 *atypptr )
{
  TypeKey    tkey(db_handle->get_dictionary(),scoped_name);
  logical  term = NO;
BEGINSEQ
  if ( !this )                                     SDBERR(70)

  if ( db_handle->get_dictionary()->GetTypeSpec(tkey,itypptr,stypptr,atypptr) )
                                                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

uint16 ACObject :: GetVersion (dttm timestamp )
{



  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetVoidPI - 



\return piptr - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVoidPI"

PropertyHandle *ACObject :: GetVoidPI ( )
{
  DBObjectHandle     obhandle(this);
  PropertyHandle    *piptr = NULL;
BEGINSEQ
  if ( !void_pi.IsValid() )
    if ( void_pi.Open(obhandle,"VOID",PI_Read) )      ERROR

  piptr = &void_pi;
RECOVER
  piptr = NULL;
ENDSEQ
  return(piptr);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ACObject :: Initialize ( )
{
  logical                 term = NO;
  sdb_error = &SDBError();
  sdb_error->ResetError();
  CTXRESET
  
  if ( obj_handle )
    obj_handle->get_object_list()->AddTail(this);
    
  if ( this != (ACObject *)db_handle )
    CheckAccess(access_mode);
  db_hdl = db_handle;    
  
  if ( TestSysVariable("MAINTENANCE_PROCESS","YES") )
    update_timestamp = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - Database handle
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ACObject :: Initialize (DBHandle *dbhandle, PIACC accopt, uint16 version_nr )
{
  logical                 term = NO;
  db_handle   = dbhandle; 
  access_mode = accopt; 
  version     = version_nr;

  Initialize();
  return(term);
}

/******************************************************************************/
/**
\brief  IsClientObject - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsClientObject"

logical ACObject :: IsClientObject ( )
{
  LACObject  *lobhandle;
  return ( GetClientACObject() ||
           ((lobhandle = GetLocalACObject()) && 
            !lobhandle->get_server_object())     );

}

/******************************************************************************/
/**
\brief  IsDBHandleDict - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDBHandleDict"

logical ACObject :: IsDBHandleDict ( )
{

  return (   db_handle && 
             db_handle == (DBHandle *)db_handle->get_dictionary()
           ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsModified - 



\return cond - 

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

int8 ACObject :: IsModified (exd *exdptr )
{


  return(YES);

}

/******************************************************************************/
/**
\brief  IsServerObject - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsServerObject"

logical ACObject :: IsServerObject ( )
{

  return ( GetLocalACObject() ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsSystemObject - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSystemObject"

logical ACObject :: IsSystemObject ( )
{

  return(db_handle ? NO : YES);

}

/******************************************************************************/
/**
\brief  IsUserDefinedIdentity - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUserDefinedIdentity"

logical ACObject :: IsUserDefinedIdentity ( )
{

  return ( userdef_id );

}

/******************************************************************************/
/**
\brief  IsValid - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical ACObject :: IsValid ( )
{
  logical                 term = YES;
BEGINSEQ
  try 
  {
    if ( !this )                                     ERROR
    if ( ident != OBJECT_ID )                        SDBERR(9)
  }
  catch (...)
  {
    SDBERR(9)
  }
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsXMLBase - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsXMLBase"

logical ACObject :: IsXMLBase ( )
{

  return(NO);

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

logical ACObject :: NewVersion (dttm timestamp, uint16 version_nr )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  ebsnum - 
\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACObject :: Open (EB_Number ebsnum, ACObject *obhandle )
{

  if ( obhandle)
  {
    obj_handle = obhandle;
    obj_overload = YES;
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  OpenPIs - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenPIs"

logical ACObject :: OpenPIs ( )
{
  logical        term = NO;
  DBObjectHandle obhandle(this);

BEGINSEQ
  if ( !(objid_pi = new PI(SDB_ObjectID)(obhandle,"SDB_ObjectID",access_mode)) )
                                                     SDBERR(95)
                                                     SDBCERR
// kommt wieder rein, wenn Schemaversion zurückgesetzt ist
//  if ( !(objname_pi = new PI(SDB_NamedObject)(obhandle,"SDB_NamedObject",access_mode)) )
//                                                     SDBERR(95)
//                                                     SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OutputResult - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OutputResult"

void ACObject :: OutputResult (char *string )
{

  if ( this )
  {
    if ( IsClientObject() )
      printf(string);
    else
    {
      if ( !nresult )
        nresult = new NString();
      *nresult += string;
    }
  }

}

/******************************************************************************/
/**
\brief  PopConnectionResult - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopConnectionResult"

logical ACObject :: PopConnectionResult ( )
{

  return ( this ? GetClientACObject()->PopResult() : YES );

}

/******************************************************************************/
/**
\brief  PushConnectionResult - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushConnectionResult"

logical ACObject :: PushConnectionResult ( )
{

  return ( this ? GetClientACObject()->PushResult() : YES );

}

/******************************************************************************/
/**
\brief  ReleaseEvents - 



\return term - Termination code

\param  emit_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEvents"

logical ACObject :: ReleaseEvents (logical emit_opt )
{
  bnode                  *nodeptr;
  LACObject              *lacobj;
  logical                 term = NO;
  while ( nodeptr = event_queue.GetHead() )
    if ( nodeptr = CheckEventNode(nodeptr) )
      nodeptr->ReleaseProcessEvents(emit_opt);
  
  if ( lacobj = GetLocalACObject() )
  {
    lacobj->GenerateLocalEvents();

// um die events abzuarbeiten, die ggf. beim abarbeiten der localen events erzeugt wurden
    while ( nodeptr = event_queue.GetHead() )
      if ( nodeptr = CheckEventNode(nodeptr) )
        nodeptr->ReleaseProcessEvents(emit_opt);
  }
// Theoretisch könnte die node-event-Schleife wieder local events
// erzeugen (nur update oder delete events). Wenn ein event handler
// update oder delete actions ausführt, werden diese events etwas 
// verzögert gesendet. Ist nicht ganz ok ...
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveEventNode - 



\return term - Termination code

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEventNode"

logical ACObject :: RemoveEventNode (bnode *bnodeptr )
{
  logical                 term = NO;
  event_queue.Remove(bnodeptr);

  if ( bnodeptr->IsValid() )
    bnodeptr->set_registered(NO);

  return(term);
}

/******************************************************************************/
/**
\brief  RemovePathNode - 



\return term - Termination code

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemovePathNode"

logical ACObject :: RemovePathNode (bnode *bnodeptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !bnodeptr->IsValid() )                        ERROR
    
  path_nodes.Remove(bnodeptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetError"

void ACObject :: ResetError ( )
{
  Error           *error;
  if ( this ) 
  {
    error = sdb_error ? sdb_error : &SDBError(); 
    error->ResetError();
  }

}

/******************************************************************************/
/**
\brief  ResetErrorObject - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetErrorObject"

void ACObject :: ResetErrorObject ( )
{

  if ( this ) 
    sdb_error = NULL;

}

/******************************************************************************/
/**
\brief  ResetOutputResult - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetOutputResult"

void ACObject :: ResetOutputResult ( )
{

  delete nresult;
  nresult = NULL;


}

/******************************************************************************/
/**
\brief  SaveExtentList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveExtentList"

logical ACObject :: SaveExtentList ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  SetActVersion - 



\return term - Termination code

\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActVersion"

logical ACObject :: SetActVersion (ACObject *obhandle )
{
  logical       term = NO;
BEGINSEQ
  if ( version == CUR_VERSION )
  {
    if ( (version = GetVersion(dttm().SetCurrent())) == CUR_VERSION )
                                                     SDBERR(207)
      
    if ( obhandle && obhandle->get_version() < version )
      version = obhandle->get_version();
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDataSource - 




\param  ds_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

void ACObject :: SetDataSource (DataSourceHandle *ds_handle )
{

  this->ds_handle = ds_handle;
  use_count = 1;  // machen wir, damit das Object wieder freigegeben wird
                  // nur für objects, die über DataSource geöffnet wurden


}

/******************************************************************************/
/**
\brief  SetErrorVariables - 




\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrorVariables"

void ACObject :: SetErrorVariables (char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{
  Error          *error;
  if ( this )
  {
    error = sdb_error ? sdb_error : &SDBError(); 
    error->ResetError();
    
    if ( parm1 )
      error->SetErrorVariable(1,parm1,UNDEF);
    if ( parm2 )
      error->SetErrorVariable(2,parm2,UNDEF);
    if ( parm3 )
      error->SetErrorVariable(3,parm3,UNDEF);
    if ( parm4 )
      error->SetErrorVariable(4,parm4,UNDEF);
    if ( parm5 )
      error->SetErrorVariable(5,parm5,UNDEF);
  }

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

logical ACObject :: SetOverload (logical overload_opt )
{
  logical  old_opt = obj_overload;
  obj_overload = overload_opt;
  return(old_opt);
}

/******************************************************************************/
/**
\brief  SetTransactionError - Set transaction error

        The  function marks a transaction as  errounus. This leads to a rollback
        of  the transaction when  the transaction is  finished. The function can
        be  called  in  post  handlers  (as  inserted  or  deleted)  to undo the
        performed operation.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransactionError"

void ACObject :: SetTransactionError ( )
{



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

logical ACObject :: SetUserDefinedIdentity (logical identity_opt )
{
  logical  old_opt = userdef_id;
  userdef_id = identity_opt;
  return(old_opt);
}

/******************************************************************************/
/**
\brief  SetVersion - Set current version



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical ACObject :: SetVersion (uint16 version_nr )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  date - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical ACObject :: SetVersion (dbdt date )
{

  return ( YES );


}

/******************************************************************************/
/**
\brief  i2 - 



\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical ACObject :: SetVersion (dttm timestamp )
{

  return ( YES );

}

/******************************************************************************/
/**
\brief  StartReadTA - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartReadTA"

void ACObject :: StartReadTA ( )
{

  ILock(YES);
  rta_count++;
  ResetError();


}

/******************************************************************************/
/**
\brief  StartTA - Start transaction



\return talevel - Transaction level

\param  ext_TA - External transaction
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartTA"

int16 ACObject :: StartTA (logical ext_TA, int16 w_maxnum )
{


  return ( StartTAIntern(ext_TA,NO,w_maxnum) );

}

/******************************************************************************/
/**
\brief  StartTAIntern - 



\return talevel - Transaction level

\param  ext_TA - External transaction
\param  intern_TA - 
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartTAIntern"

int16 ACObject :: StartTAIntern (logical ext_TA, logical intern_TA, int16 w_maxnum )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  StopReadTA - 




\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopReadTA"

void ACObject :: StopReadTA (logical error_case )
{
  int32       saverr = 0;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  saverr = sdb_error->CheckError();    

  if ( --rta_count <= 0 )
  {
    rta_count = 1;
    ReleaseEvents(!error_case);
    rta_count = 0;
  }
  IUnlock();

ENDSEQ
  if ( saverr )
    sdb_error->SetError(saverr,NULL,NULL);
}

/******************************************************************************/
/**
\brief  StopTA - Terminate transaction



\return term - Termination code

\param  talevel - Transaction level
\param  error_case_w - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopTA"

logical ACObject :: StopTA (int16 talevel, logical error_case_w )
{


  return(YES);
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

logical ACObject :: UpdateTimestamp (logical timestamp_enabled )
{
  logical    old_mode = update_timestamp;
  update_timestamp = timestamp_enabled;
  return(old_mode);
}

/******************************************************************************/
/**
\brief  VersionCount - Get number of versions



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCount"

int32 ACObject :: VersionCount ( )
{

  return( 0 );

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

INTERVAL(dttm) ACObject :: VersionIntervall (uint16 version_nr )
{
  INTERVAL(dttm)     timint;


  return(timint);
}

/******************************************************************************/
/**
\brief  set_result_string - 



\return string - 

\param  char_buffer - 
\param  longlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_result_string"

char *ACObject :: set_result_string (char *char_buffer, int32 longlen )
{

  return( nstring.SetString(char_buffer,longlen) );

}

/******************************************************************************/
/**
\brief  ~ACObject - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACObject"

     ACObject :: ~ACObject ( )
{


  db_hdl = NULL;
  
  ResetOutputResult();
  
  delete resource;
  resource = NULL;
  
  delete ocontext;
  ocontext = NULL;
  
  delete object_list;
  object_list = NULL;

  if ( context_path )
    free(context_path);
  context_path = NULL;
  
  event_queue.Clear();

  delete ds_handle;
  ds_handle = NULL;
  
  ident = UNDEF;

}


