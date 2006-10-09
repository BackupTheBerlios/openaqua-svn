/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACPath

\brief    


\date     $Date: 2006/08/04 12:06:41,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACPath"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDBViewPath.hpp>
#include  <sDictionary.hpp>
#include  <sFieldSource.hpp>
#include  <sLACObject.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sbinti.hpp>
#include  <snode.hpp>
#include  <sACPath.hpp>


/******************************************************************************/
/**
\brief  ACPath - 


-------------------------------------------------------------------------------
\brief  i01 - 


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  structdef - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

     ACPath :: ACPath (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv),
  operation(NULL),
  parent_objid(0)
{

BEGINSEQ
  nodetype = NT_ACOPView;

  nodeacc  = accopt;

  if ( InitOQLElements(structdef) )                 ERROR
  if ( Initialize((char *)NULL) )         
  {
    SDBOQLCERR
    ERROR
  }
  Open();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  proppath - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

     ACPath :: ACPath (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv),
  operation(NULL),
  parent_objid(0)


{

BEGINSEQ
  nodetype = NT_ACOPView;
  set_prop_path(proppath);
  
  nodeacc  = accopt;
  
  if ( InitExpression(proppath) )                      ERROR
  if ( Initialize(strnames_w) )
  {
    SDBOQLCERR
    ERROR
  }
  Open();
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  bnf_data - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

     ACPath :: ACPath (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv),
  operation(NULL),
  parent_objid(0)
{

BEGINSEQ
  nodetype = NT_ACOPView;
  set_prop_path(bnf_data->StringValue());  
  
  nodeacc  = accopt;
  oper_bnf = bnf_data;

  if ( Initialize(strnames_w) )
  {
    SDBOQLCERR
    ERROR
  }

  Open();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04 - 


\param  obhandle - Database Object handle
\param  dbextdef - Extent definition
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

     ACPath :: ACPath (ACObject *obhandle, DBExtend *dbextdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,NULL,dbextdef->GetDBStruct(),operenv),
  operation(NULL),
  parent_objid(0)
{

BEGINSEQ
  if ( Initialize(obhandle) )
  {
    SDBOQLCERR
    ERROR
  }

  nodeacc  = accopt;
  
  Open();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i05 - 


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  fielddef - Internal field defintion
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

     ACPath :: ACPath (ACObject *obhandle, node *nodeptr, DBFieldDef *fielddef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,fielddef->GetDBStruct(),operenv),
  operation(NULL),
  parent_objid(0)
{

BEGINSEQ
  if ( Initialize(fielddef) )
  {
    SDBOQLCERR
    ERROR
  }

  nodeacc  = accopt;
  
  Open();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i06 - 


\param  acpathref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

     ACPath :: ACPath (ACPath &acpathref )
                     : ACOperation (acpathref.object_ref,acpathref.nodenode,NULL,acpathref.oper_env),
  operation(NULL),
  parent_objid(0)
{


BEGINSEQ
  nodetype = NT_ACOPView;
  
  nodeacc  = acpathref.nodeacc;
  oper_bnf = acpathref.oper_bnf;
  set_prop_path(oper_bnf->StringValue());  

  if ( Initialize((char *)NULL) )
  {
    SDBOQLCERR
    ERROR
  }

  Open();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  BuildResult - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildResult"

logical ACPath :: BuildResult ( )
{
  logical                 term = NO;
// create temporary collection by running the path
  return(term);
}

/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical ACPath :: Cancel (logical chknode )
{
  logical        term = NO;
  Switch(AUTO);
  
  nodecur = AUTO;
  stsrfil();

  operation->ToTop();
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeMode - Change access mode


\return oldmode - 

\param  accopt - Access mode
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC ACPath :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC          oldmode = PI_undefined;
BEGINSEQ
  if ( chkopt && Check(NO,NO) )                      ERROR
  if ( chkopt && CheckAccess(accopt) )               ERROR
  
  if ( inti_buffer && accopt > PI_Read )             SDBERR(244)
       
  oldmode = nodeacc;
  nodeacc = accopt;
  
  if ( created == YES )
  {
    if ( LNode::ChangeMode(accopt) == PI_undefined ) ERROR
  }
  else if ( operation->ChangeMode(accopt) == PI_undefined )
                                                     ERROR
  SetupInstance();

RECOVER
  if ( oldmode != PI_undefined && chkopt )
  {
    ChangeMode(oldmode,NO);
    oldmode = PI_undefined;
  }
ENDSEQ
  return(oldmode);
}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  autoini - 
\param  acccheck - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ACPath :: Check (logical autoini, logical acccheck )
{
  logical        term = NO;
BEGINSEQ
  if ( acccheck && nodenode )
  {
    if ( nodenode->IsSelected() && parent_objid != Bnodenode->get_objid() )
    {
      ResetResult();
      created = NO;
      parent_objid = Bnodenode->get_objid();
      if ( InitResult() )                            ERROR
    }
  }
  
  if ( autoini )
  {
    if ( !is_opened )
      Open();
    if ( !nodeinst && GetResultNode() )
      if ( !(nodeinst = GetResultNode()->get_nodeinst()) )
                                                     LEAVESEQ
  }
  
  if ( LNode::Check(autoini,acccheck) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACPath :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACPath(*this) ) )             SDBERR(95)
                                                     SDBCERR
  if ( nodefield->get_weak_typed() || !memcmp(nodefield->fmcbname,"VOID ",5) )
    nodeptr->SetType(GetCurrentType());

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  ExecPropCtxFunc - 


\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecPropCtxFunc"

logical ACPath :: ExecPropCtxFunc (char *fnames, char *w_parms )
{
  node           *result = GetResultNode();
  bnode          *last_node = result ? (bnode *)result : NULL;
  PropertyHandle *ph;
  logical         term = NO;
BEGINSEQ
  if ( !CheckPropCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecPropCtxFunc(fnames,w_parms) )    ERROR
    if ( ph = Bnodeinst->get_context()->GetPropertyHandle() )
      nstring = ph->GetActionResult();
  }
  else
  {
    if ( last_node->ExecPropCtxFunc(fnames,w_parms) )ERROR
    nstring = last_node->get_nstring();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecStrCtxFunc - 


\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecStrCtxFunc"

logical ACPath :: ExecStrCtxFunc (char *fnames, char *w_parms )
{
  node           *result = GetResultNode();
  bnode          *last_node = result ? (bnode *)result : NULL;
  PropertyHandle *ph;
  logical         term = NO;
BEGINSEQ
  if ( !CheckStrCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecStrCtxFunc(fnames,w_parms) )     ERROR
    if ( ph = Bnodeinst->get_context()->GetPropertyHandle() )
      nstring = ph->GetActionResult();
  }
  else
  {
    if ( last_node->ExecStrCtxFunc(fnames,w_parms) ) ERROR
    nstring = last_node->get_nstring();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ACPath :: Execute (ParmList *parmlist )
{
  PropertyHandle   *co = operation->get_calling_object();
  logical           term = NO;
BEGINSEQ
  ResetInstance(); 

  if ( oper_env && oper_env->CO() )
    co = oper_env->CO();
  
  if ( operation->Execute(co,parmlist) )         ERROR

  SetupInstance();
  
  if ( !created && GetInstance() )
    nodecur = 0; 

RECOVER
  ResetInstance();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG - 


\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPath :: Get (int32 indx0, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR

  if ( created == YES )
    instptr = LNode::Get(indx0,NO);
  else
    if ( Position(indx0 - nodecur) >= 0 )
      instptr = GetInstance();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPath :: Get (char *skey, logical chknode )
{
  void          *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  
  if ( created == YES )
    instptr = LNode::Get(skey,NO);
  else
    instptr = operation->Get(skey).GetData();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetContext - 


\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Property *ACPath :: GetContext ( )
{
  node        *nodeptr = GetResultNode();

  return(nodeptr ? nodeptr->GetContext() : NULL);

}

/******************************************************************************/
/**
\brief  GetResultNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResultNode"

node *ACPath :: GetResultNode ( )
{

  return(this && operation ? operation->get_nodeptr() : NULL);

}

/******************************************************************************/
/**
\brief  InitExpression - 


\return term - Termination code

\param  exprstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExpression"

logical ACPath :: InitExpression (char *exprstr )
{
  Dictionary *dictionary = object_ref->GetDictionary();
  logical     term = NO;
BEGINSEQ
  if ( !(oper_bnf = dictionary->ParseExpression(exprstr,"simple_op",NULL)) )
                                                     ERROR
  bnf_owner = YES;
RECOVER
  delete oper_bnf;
  oper_bnf = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitOQLElements - 


\return term - Termination code

\param  dbview_str - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOQLElements"

logical ACPath :: InitOQLElements (DBStructDef *dbview_str )
{
  NString                 nstring;
  logical                 term = NO;
BEGINSEQ
  nstring = "";
  
  if ( InitOQLFrom(dbview_str,nstring) )             ERROR
  
  if ( dbview_str->get_where() )
  {
    nstring = ".where(";
    nstring+= dbview_str->get_where();
    nstring += ')';
  }

  nstring += ".use(";
  nstring.Append(dbview_str->smcbname,ID_SIZE);
  nstring += ')';
  
  if ( InitOQLGroupBy(dbview_str,nstring) )          ERROR

  if ( dbview_str->get_having() )
  {
    nstring = ".having(";
    nstring+= dbview_str->get_having();
    nstring += ')';
  }
  set_prop_path(nstring);

  if ( !(oper_bnf = object_ref->GetDictionary()->ParseExpression(nstring,"access_path",NULL)) )
                                                     ERROR
  bnf_owner = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitOQLFrom - 


\return term - Termination code

\param  dbview_str - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOQLFrom"

logical ACPath :: InitOQLFrom (DBStructDef *dbview_str, NString &nstring )
{
  DBExtend               *dbextdef    = (DBExtend *)nodefield;
  DLL(FieldSource)       *source_list = dbextdef->get_sources();
  DLL(DBViewPath)        *from_list   = dbview_str->get_from();
  DBViewPath             *from_path;
  FieldSource            *source;
  logical                 first       = YES;
  logical                 term        = NO;
BEGINSEQ
  if ( !source_list )                                SDBERR(246)
  if ( !from_list )                                  SDBERR(99)

  if ( source_list->GetCount() != from_list->GetCount() )
                                                     SDBERR(246)
  from_list->GoTop();
  source_list->GoTop();

  nstring += "from(";
  while ( (from_path = from_list->GetNext()) && (source = source_list->GetNext()) )
  {
    if ( !source->GetString() )                      SDBERR(99)
/*    
    if ( !nodenode )
    {
      PropertyHandle ph(object_ref,source->GetString(),PI_Read);
                                                     SDBCERR
      strdef = ph.GetStructDef();
    }
    else
    {    
      PropertyHandle    co(nodenode);
      PropertyHandle    ph(&co,source->GetString()); SDBCERR
      strdef = ph.GetStructDef();
    }
    if ( !strdef->Inherits(from_path->get_struct_name()) )
                                                     SDBERR(247)
*/    
    if ( !first )
    {
      nstring += ',';
      first = NO;
    }
    nstring += source->GetString();
    if ( source->GetOrder() )
    {
      nstring += ".order_by(";
      nstring += source->GetOrder();
      nstring += ')';
    }
    
    if ( *from_path->get_path() )
    {
      nstring += '.';
      nstring += from_path->get_path();
    }
  }
  nstring += ')';


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitOQLGroupBy - 


\return term - Termination code

\param  dbview_str - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOQLGroupBy"

logical ACPath :: InitOQLGroupBy (DBStructDef *dbview_str, NString &nstring )
{
  logical                 term        = NO;
// missing
  return(term);
}

/******************************************************************************/
/**
\brief  InitResult - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical ACPath :: InitResult ( )
{
  logical                 term = NO;
  operation->InitResult(*nodenode->GetPH());
  if ( auto_create )
  {
    if ( !BuildResult() )
      created = YES;  
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ACPath :: Initialize (char *strnames_w )
{
  PropertyHandle     ph(nodenode);
  ACObject          *obhandle = NULL;
  logical            term = NO;
BEGINSEQ
  is_opened      = NO;
  
  if ( Check(NO,NO) )                                ERROR
  
  if ( nodenode )
    operation = new Operation(*nodenode->GetPH(),oper_env);
  else
    operation = new Operation(oper_env);

  if ( oper_env )
    obhandle = oper_env->ObjectHandle();
  if ( !obhandle )
    obhandle = object_ref->GetDictionary();
  if ( operation->ProvAccessPath(object_ref->GetDictionary(),
                                 obhandle,object_ref,oper_bnf) )
                                                     ERROR

RECOVER
  delete operation;
  operation = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ACPath :: Initialize (ACObject *obhandle )
{
  DBExtend      *dbextdef = NULL;
  DBStructDef   *dbstr_def;
  logical        term = NO;
BEGINSEQ
  if ( Check(NO,NO) )                                ERROR
  if ( !nodefield )                                  SDBERR(99)
  
  SDBEV1(nodefield->fmcbname,ID_SIZE)
  SDBEV2("",UNDEF)
    
  dbstr_def = nodefield->GetDBStruct();
  if ( !dbstr_def->GetViewStructDef() )              SDBERR(99)
    
  is_opened      = NO;
  is_collection  = YES;
  
  if ( InitOQLElements(dbstr_def) )                  ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 


\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ACPath :: Initialize (DBFieldDef *fielddef )
{
  DBStructDef          *dbstr_def;
  FieldSource          *source;
  logical               term = NO;
  node                 *nodeptr;
  node                **pnodeptr;

BEGINSEQ
  if ( !fielddef )                                  ERROR
    
  SDBEV1(fielddef->fmcbname,ID_SIZE)
    
  dbstr_def = fielddef->GetDBStruct();
/*
  if ( dbstr_def->GetViewStructDef() )
  {
    if ( InitElements(dbstr_def,fielddef->get_sources()) )
                                                     ERROR
  }
  else
  {
    if ( !fielddef->get_sources() || fielddef->get_sources()->GetCount() != 1 )
                                                     SDBERR(99)
    source = fielddef->get_sources()->GetHead();
    if ( !(pnodeptr = nodenode->GetNodePtr(source->GetString())) ||
         !(nodeptr = *pnodeptr)                   )  ERROR
    pelement = new ACPathElement(this,NULL,nodeptr,source->GetOrder());
                                                     SDBCERR
    elements.AddTail(pelement);
  }
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACPath :: Open ( )
{
  node          *nodeptr;
  DBFieldDef    *field_def;
  smcb          *smcbptr;
  logical        term = NO;
BEGINSEQ
  if ( !(nodeptr = GetResultNode()) )                ERROR
  
  if ( !is_opened && !stscerr() )
  {
    nodeptr->Check(YES,NO);
    if ( field_def = nodeptr->GetFieldDef() )
      if ( !bnode::Open(object_ref,nodenode,field_def,NULL,nodeacc) )
      {
        is_opened = YES;
        is_collection = nodeptr->IsCollection();
        is_memo = nodeptr->IsMemo();
        variable_type = nodeptr->IsVariableType();
      }
      else
      {
        stsserr();                                 ERROR
      }
  }
  
  if ( nodeptr )
  {
    if ( smcbptr = nodeptr->GetSMCB(NO) )
      id_key   = smcbptr->smcbidky;
    if ( nodeptr->get_nodetype() != NT_Node )
      sk_index = Bnodeptr->get_sk_index();
  }
  SetupInstance();
  
  RegisterPathNode();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Position - 


\return rindx0 - 

\param  count - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

int32 ACPath :: Position (int32 count, logical chknode )
{
  logical         pos_invalid = NO;
  int32           lindx0;
BEGINSEQ
  if ( Check(YES,YES) )                              ERROR
  
  if ( created == YES )
    lindx0 = LNode::Position(count);
  else
  {
    if ( nodecur += count )
      nodecur = AUTO;
    lindx0 = nodecur;
  }
RECOVER
  lindx0 = AUTO;
ENDSEQ
  if ( pos_invalid )
    relative_index = LAST_INSTANCE;
  return(lindx0);

}

/******************************************************************************/
/**
\brief  ResetInstance - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

void ACPath :: ResetInstance ( )
{

  ACOperation::ResetInstance();
  
  nodeinst = NULL;
  node::SetArea(NULL);
  nodecur = AUTO;

}

/******************************************************************************/
/**
\brief  ResetResult - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetResult"

logical ACPath :: ResetResult ( )
{
  logical                 term = NO;
  operation->InitResult(*nodenode->GetPH());
  if ( created )
  {
    LNode::DeleteSet();
    created = NO;  
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACPath :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical       term = NO;
  term = created 
         ? LNode::Save(switchopt,overwrite,chknode)
         : NO;
  if ( switchopt )
    nodecur = AUTO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupInstance - 


\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInstance"

void *ACPath :: SetupInstance ( )
{
  void        *instptr = NULL;
  node        *nodeptr = GetResultNode();
BEGINSEQ
  if ( created )                                     LEAVESEQ

  if ( !nodeptr )                                    ERROR
  nodewrit = NO;
  
  if ( nodeptr->get_nodeinst() )
  {
    node::SetCurrentInti(nodeptr->get_nodeinst());
    if ( nodeacc != PI_Read )
      nodewrit = nodeptr->IsWrite();
    nodeinst->SetObjectID(objid = Bnodeptr->get_objid());
  }
  else
  {
    nodeinst = NULL;
    node::SetArea(nodeptr->GetArea());
  }
  
  SetDescription(nodeptr->GetInstFieldDef());
  nodefield = nodeptr->GetFieldDef();

  if ( nodeptr->get_nodetype() != NT_Node )
    variable_type  = Bnodeptr->get_variable_type();

RECOVER
  ResetInstance();
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  ValidateNode - 


\return new_node - 

\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateNode"

node *ACPath :: ValidateNode (logical crt_opt )
{
  node *   new_node = this;
// in diesem Fall sollten sich die entsprechenden PropertyHandle (value) 
// um die Anpassung kümmenr, d,h, ACPath ist immer ok.
  return(new_node);
}

/******************************************************************************/
/**
\brief  ~ACPath - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACPath"

     ACPath :: ~ACPath ( )
{

  nodeinst  = NULL;
  if ( nodeidnt == NODE_ID )
  {
    UnregisterPathNode();  
    Close();
  }
  nodefield = NULL;
  id_key    = NULL;
  sk_index  = NULL;
  
  delete operation;
  operation = NULL;
  



}


