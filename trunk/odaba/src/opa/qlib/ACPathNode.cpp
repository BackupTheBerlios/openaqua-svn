/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACPathNode

\brief    


\date     $Date: 2006/08/04 12:04:35,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACPathNode"

#include  <popa7.h>
#include  <sACAttribute.hpp>
#include  <sACBaseStruct.hpp>
#include  <sACExtend.hpp>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sCTX_Property.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sEventProxy.hpp>
#include  <sOperEnvironment.hpp>
#include  <skcb.hpp>
#include  <sACPathNode.hpp>


/******************************************************************************/
/**
\brief  ACPathNode - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  nodeptr - 
\param  parm_data - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathNode"

     ACPathNode :: ACPathNode (node *nodeptr, BNFData *parm_data, OperEnvironment *operenv )
                     : bnode (nodeptr->GetObjectHandle(),
       nodeptr->GetNode(),
       NULL,NULL,
       nodeptr->GetMode()),
  copy_node(NULL),
  bnf_spec(NULL),
  event_proxy(NULL),
  oper_env(operenv),
  owner(NO)
{

BEGINSEQ
  nodetype = NT_ACPathNode;
  
  set_prop_path(parm_data->StringValue());
  if ( Open(parm_data) )                                 ERROR
RECOVER
  Close();
ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 


\param  obhandle - Database Object handle
\param  parm_data - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathNode"

     ACPathNode :: ACPathNode (ACObject *obhandle, BNFData *parm_data, OperEnvironment *operenv, PIACC accopt )
                     : bnode (obhandle,NULL,NULL,NULL,accopt),
  copy_node(NULL),
  bnf_spec(NULL),
  event_proxy(NULL),
  oper_env(operenv),
  owner(NO)
{

BEGINSEQ
  nodetype = NT_ACPathNode;
  
  set_prop_path(parm_data->GetStringValue(NULL,NULL));
  if ( Open(parm_data) )                                 ERROR
RECOVER
  Close();
ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 


\param  acpath_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathNode"

     ACPathNode :: ACPathNode (ACPathNode &acpath_node )
                     :   bnode(acpath_node),
  copy_node(NULL),
  bnf_spec(NULL),
  event_proxy(NULL),
  oper_env(acpath_node.oper_env),
  owner(NO)
{

  nodetype = NT_ACPathNode;
  
  Open(acpath_node.get_prop_path());

}

/******************************************************************************/
/**
\brief  i03 - 


\param  obhandle - Database Object handle
\param  proppath - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathNode"

     ACPathNode :: ACPathNode (ACObject *obhandle, char *proppath, OperEnvironment *operenv, PIACC accopt )
                     : bnode (obhandle,NULL,NULL,NULL,accopt),
  copy_node(NULL),
  bnf_spec(NULL),
  event_proxy(NULL),
  oper_env(operenv),
  owner(NO)
{

BEGINSEQ
  nodetype = NT_ACPathNode;
  
  if ( Open(proppath) )                                 ERROR
RECOVER
  Close();
ENDSEQ

}

/******************************************************************************/
/**
\brief  i04 - 


\param  nodeptr - 
\param  proppath - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathNode"

     ACPathNode :: ACPathNode (node *nodeptr, char *proppath, OperEnvironment *operenv )
                     : bnode (nodeptr->GetObjectHandle(),
       nodeptr->GetNode(),
       NULL,NULL,
       nodeptr->GetMode()),
  copy_node(NULL),
  bnf_spec(NULL),
  event_proxy(NULL),
  oper_env(operenv),
  owner(NO)
{

BEGINSEQ
  nodetype = NT_ACPathNode;
  
  if ( Open(proppath) )                                 ERROR
RECOVER
  Close();
ENDSEQ

}

/******************************************************************************/
/**
\brief  Add - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACPathNode :: Add (int32 lindx0, logical global_add )
{
  void                *instptr;
  if ( instptr = Tail()->Add(lindx0,global_add) )
    UpdatePosition();


  return(instptr);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACPathNode :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  void                *instptr;
  if ( instptr = Tail()->Add(lindx0,skey,idkey,initinst,global_add) )
    UpdatePosition();

  return(instptr);
}

/******************************************************************************/
/**
\brief  AddReference - 


\return term - Termination code

\param  srcenode - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddReference"

logical ACPathNode :: AddReference (node *srcenode, int32 lindx0 )
{

  return( Tail()->AddReference(srcenode,lindx0) );

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

logical ACPathNode :: Cancel (logical chknode )
{
  logical   term    = NO;

BEGINSEQ
  if ( chknode && Check(NO,NO)  )                    ERROR
  
  Head()->Cancel();
  ResetPosition();

RECOVER
  term = YES;
ENDSEQ
  return(term); 

}

/******************************************************************************/
/**
\brief  ChangeMode - 


\return oldmode - 

\param  accopt - Access mode
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC ACPathNode :: ChangeMode (PIACC accopt, char chkopt )
{
  node                   *nodeptr;
  PIACC                   oldmode = Tail()->GetMode();
BEGINSEQ
  if ( chkopt && Check(YES,NO) )                 ERROR
  
  node_path.GoTop();
  while ( nodeptr = node_path.GetNext() )             
    if ( nodeptr->ChangeMode(accopt,NO) )        ERROR
      
  if ( !Tail()->IsPositioned() )
    ResetPosition();

RECOVER
  ResetPosition();
  oldmode = PI_undefined;
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

logical ACPathNode :: Check (logical autoini, logical acccheck )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( acccheck )
    if ( !ValidateNode(YES) )                        ERROR
  if ( !Tail() )                                     ERROR

  if ( !Tail()->IsSelected() )  
  {
    node_path.GoTop();
    while ( nodeptr = node_path.GetNext() )
    {
      if ( nodeptr->Check(autoini,acccheck) )        ERROR
      acccheck = NO;
    }
  }
  else if ( nodecur == AUTO )
    UpdatePosition();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical ACPathNode :: CheckWProtect ( )
{

  return( this ? Tail()->CheckWProtect() : YES );

}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACPathNode :: Close ( )
{
  logical                 term = NO;
//  if ( !nodenode && copy_node ) // wird bei nodenode über die Kette im nodenode gelöscht
  delete copy_node;
  copy_node = NULL;   
  
  UnregisterPathNode();
  
  CloseHierarchy();
    
  bnode::Close();
  
//  delete event_proxy;
//  event_proxy = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  CloseHierarchy - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseHierarchy"

logical ACPathNode :: CloseHierarchy ( )
{
  node                   *nodeptr;
  logical                 term = NO;
  nodeinst = NULL;
  nodefield = NULL;
  
  nodeptr = node_path.GetHead();
  node_path.Clear();
  is_opened = NO;

  if ( owner )
    delete nodeptr;
  return(term);
}

/******************************************************************************/
/**
\brief  Contains - 


\return cond - 

\param  reg_string - 
\param  case_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Contains"

logical ACPathNode :: Contains (char *reg_string, logical case_opt )
{

  return( this ? Tail()->Contains(reg_string,case_opt) : NO );

}

/******************************************************************************/
/**
\brief  CreateAccessPath - 


\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  parm_bnf - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *ACPathNode :: CreateAccessPath (BNFData *parm_bnf, OperEnvironment *operenv )
{
  node *   nodeptr = NULL;
  return( this ? Tail()->CreateAccessPath(parm_bnf,operenv) : NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  prop_path - Property path
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *ACPathNode :: CreateAccessPath (char *prop_path, OperEnvironment *operenv )
{
  node *   nodeptr = NO;

  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACPathNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACPathNode(*this) ) )         SDBERR(95)
                                                     SDBCERR

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreatePathNode - 


\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  parm_bnf - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *ACPathNode :: CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv )
{

  return( this ? Tail()->CreatePathNode(parm_bnf,operenv) : NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  prop_path - Property path
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *ACPathNode :: CreatePathNode (char *prop_path, OperEnvironment *operenv )
{

  return( Tail()->CreatePathNode(prop_path,operenv) );

}

/******************************************************************************/
/**
\brief  CreateSubNode - 


\return nodeptr - 

\param  nodeptr - 
\param  nodtype - 
\param  sysnode - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  extoff - 
\param  intoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubNode"

node *ACPathNode :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{
  node         *parent = Tail();
  node         *subnode = NULL;
BEGINSEQ
  return(parent ? parent->CreateSubNode(parent,nodtype,sysnode,dbfield_ptr,highctx,instptr,extoff,intoff,accopt) : NULL);
/*
  switch ( nodtype )
  {
    case  NT_ACAttribute    : subnode = new ACAttribute(nodeptr,dbfield_ptr,highctx,
                                                        instptr,accopt);
                              break;
    case  NT_ACBaseStruct   : subnode = new ACBaseStruct(nodeptr,dbfield_ptr,highctx,
                                                         instptr,accopt);
                              break;
    default                 : subnode = bnode::CreateSubNode(nodeptr,nodtype,sysnode,dbfield_ptr,highctx,instptr,extoff,intoff,accopt);
  }
  if ( !subnode )                                    SDBERR(95)
  SDBCERR
*/
RECOVER
//  delete subnode;
  subnode = NULL;
ENDSEQ
//  return(subnode);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  NODEID - 


\param  indx0 - Position in collection
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACPathNode :: Delete (int32 indx0, logical chknode, logical del_dep, logical del_inst )
{
  logical                 term = NO;
BEGINSEQ
  if ( !Get(indx0,chknode) )                         ERROR
  
  if ( Tail()->Delete(AUTO,NO,del_dep,del_inst) )    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACPathNode :: Delete (char *skey, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( !Get(skey) )                                  ERROR
  
  if ( Tail()->Delete(AUTO) )                        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteIndex - 


\return term - Termination code

\param  gen_events - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIndex"

logical ACPathNode :: DeleteIndex (logical gen_events )
{

  return( this ? Tail()->DeleteIndex(gen_events) : YES );

}

/******************************************************************************/
/**
\brief  DeleteSet - 


\return term - Termination code

\param  chknode - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSet"

logical ACPathNode :: DeleteSet (logical chknode, logical del_dep )
{
  node                   *last = Tail();
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  ToTop();
  
  while ( !NextCollection() ) 
    if ( last->DeleteSet(del_dep) )
      term = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Duplicate - 


\return instptr - 

\param  keyptr - 
\param  db_replace - Replace option
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Duplicate"

void *ACPathNode :: Duplicate (char *keyptr, PIREPL db_replace, logical chknode )
{

  return( this ? Tail()->Duplicate(keyptr,db_replace,chknode) : NULL );

}

/******************************************************************************/
/**
\brief  Execute - 


\return term - 

\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ACPathNode :: Execute (ParmList *parmlist )
{
  logical   term = NO;
  if ( moveable_instance )
  {
    Close();
    Open(bnf);
  }
  else
    if ( !is_collection && (!nodenode || nodenode->IsPositioned()) )
      First();

  return(term);
}

/******************************************************************************/
/**
\brief  ExtractKey - 


\return keyptr - 

\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ACPathNode :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{

  return( this ? Tail()->ExtractKey(keyptr,instptr,chknode) : NULL );

}

/******************************************************************************/
/**
\brief  ExtractSortKey - 


\return keyptr - 

\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractSortKey"

char *ACPathNode :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{

  return( this ? Tail()->ExtractSortKey(keyptr,instptr,chknode) : NULL );

}

/******************************************************************************/
/**
\brief  First - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "First"

logical ACPathNode :: First ( )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_path.GoTop();
  while ( nodeptr = node_path.GetNext() )
    if ( !nodeptr->Get(FIRST_INSTANCE) )             
    {
      if ( is_collection || nodeacc <= PI_Read )    ERROR
      if ( GetInitInstance() )                      ERROR
    }

  relative_index = nodecur = FIRST_INSTANCE;
  UpdatePosition();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FirstKey - 


\return keyptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *ACPathNode :: FirstKey (logical chknode )
{
  char                   *keyptr = NULL;
BEGINSEQ
  if ( !Get(FIRST_INSTANCE) )                      ERROR
  
  ExtractKey(NULL,NULL);
  keyptr = nstring;
  nodecur = 0;

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Get - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPathNode :: Get (int32 indx0, logical chknode )
{
  int32                   count     = indx0;
  int32                   direction = UNDEF;
  void                   *instptr   = NULL;

BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( indx0 == AUTO && nodecur != AUTO )  
  {
    if ( !Tail()->Get(AUTO) )                        ERROR
  }
  else  
  {
    if ( !is_collection )
    {
      if ( indx0 != 0 )                              ERROR
    }

    if ( indx0 == LAST_INSTANCE )
    {
      if ( Last() )                                  ERROR
    }
    else 
    {
      if ( indx0 >= nodecur/2 )
        count = indx0 - nodecur;
      else
      {
        if ( First() )                               ERROR
        count = indx0;
      }
    
      nodecur += count;
      direction = count > 0 ? FOREWARD : BACKWARD;
      while ( count && !GetPosition(direction) )
        count -= direction;

      if ( count )                                   ERROR
    }
  }
    
  instptr = UpdatePosition();

RECOVER
  ResetPosition();
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPathNode :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( LocateKey(skey,YES,chknode) )                 ERROR
  
  if ( !Tail()->Get(AUTO) )                          ERROR
    
  instptr = UpdatePosition();
RECOVER
  ResetPosition();
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

CTX_Property *ACPathNode :: GetContext ( )
{
  node        *nodeptr = Tail();

  return(nodeptr ? nodeptr->GetContext() : NULL);

}

/******************************************************************************/
/**
\brief  GetCount - 


\return ecnt - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACPathNode :: GetCount (logical chknode )
{
  node                   *nodeptr;
  int32                   tcount;
  int32                   count = 0;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  
  if ( !is_collection )
    count = First() ? 0 : 1;
  else
  {
    if ( node_path.GetCount() == 1 )
      count = Tail()->GetCount();
    else
    {
      if ( !copy_node )
        copy_node = new ACPathNode(*this);
    
      copy_node->ToTop();
      nodeptr = copy_node->Tail();
  
      while ( !copy_node->NextCollection() ) 
      {
        if ( (tcount = nodeptr->GetCount()) == ERIC)     ERROR
        count += tcount;            
      }
    }
  }
RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetCurrentTypeDef - 


\return strdef_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentTypeDef"

DBStructDef *ACPathNode :: GetCurrentTypeDef ( )
{

  return( this ? Tail()->GetCurrentTypeDef() : NULL );

}

/******************************************************************************/
/**
\brief  GetDimension - 


\return ecnt - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 ACPathNode :: GetDimension (logical chknode )
{

  if ( chknode )
    Check(YES,NO);


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum - 
-------------------------------------------------------------------------------
\brief  NODEGID - 


\param  indx0 - Position in collection
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACPathNode :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number               ebsnum;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( indx0 != AUTO ) 
    if ( !Get(indx0,chknode) )                       ERROR
  
  if ( !IsSelected() )                               ERROR
  
  ebsnum = Tail()->GetID(AUTO,NO,pif_opt);
RECOVER

ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  NODEGID_ - 


\param  keyptr - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACPathNode :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  EB_Number               ebsnum;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( keyptr )
    if ( !Get(keyptr,chknode) )                       ERROR
  
  ebsnum = Tail()->GetID(AUTO,chknode,pif_opt);
RECOVER

ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  GetInstModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 ACPathNode :: GetInstModCount ( )
{

  return( this ? Tail()->GetInstModCount() : UNDEF );

}

/******************************************************************************/
/**
\brief  GetKey - 


\return key_val - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *ACPathNode :: GetKey (int32 lindx0, logical chknode )
{
  char                   *keyptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( lindx0 != AUTO )
  {
    if ( !Get(lindx0,chknode) )                      ERROR
  }
  else
    if ( !Tail()->Get(AUTO) )                        ERROR
      
  keyptr = ExtractKey(NULL,NULL);
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  GetNodePtr - 


\return result_field - 

\param  prop_path - Property path
\param  is_transient - 
\param  supress_struct_error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **ACPathNode :: GetNodePtr (char *prop_path, logical *is_transient, logical supress_struct_error )
{

  return(   this
          ? Tail()->GetNodePtr(prop_path,is_transient,supress_struct_error) 
          : NULL );

}

/******************************************************************************/
/**
\brief  GetPosition - 


\return term - Termination code

\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

logical ACPathNode :: GetPosition (int16 direction )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_path.GoBottom();
  if ( GoUp(direction) )                             ERROR
  
  while ( nodeptr = node_path.GetNext() )             
    if ( PositionNode(nodeptr,direction,YES) )      
      if ( GoUp(direction) )                         ERROR

RECOVER
  ResetPosition();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetRefModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 ACPathNode :: GetRefModCount ( )
{

  return( this ? Tail()->GetRefModCount() : NULL );

}

/******************************************************************************/
/**
\brief  GoUp - 


\return term - Termination code

\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoUp"

logical ACPathNode :: GoUp (int16 direction )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  while ( nodeptr = node_path.GetPrev() )
    if ( !PositionNode(nodeptr,direction,NO) )      
      LEAVESEQ

  if ( !nodeptr )                                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  HasFilter - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFilter"

logical ACPathNode :: HasFilter ( )
{

  return( this ? Tail()->HasFilter() : NO );

}

/******************************************************************************/
/**
\brief  Head - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Head"

node *ACPathNode :: Head ( )
{

  return ( this ? node_path.GetHead() : NULL );

}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical ACPathNode :: IsPositioned ( )
{

  return ( this && nodecur != AUTO && Tail()->IsPositioned() );

}

/******************************************************************************/
/**
\brief  IsReadOnly - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical ACPathNode :: IsReadOnly ( )
{

  return( this ? Tail()->IsReadOnly() : NO );

}

/******************************************************************************/
/**
\brief  IsSelected - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical ACPathNode :: IsSelected ( )
{

  return ( this ? Tail()->IsSelected() : NO );

}

/******************************************************************************/
/**
\brief  KeyToString - 


\return key_string - 

\param  key_string - 
\param  key_val - 
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyToString"

char *ACPathNode :: KeyToString (char *key_string, char *key_val, char *key_name_w )
{
  char                   *keyarea;
  int32                   pos   = 0;
  logical                 first = YES;
BEGINSEQ
  if ( !this )                                       ERROR
  
  if ( !(keyarea = Tail()->KeyToString(key_string,key_val,key_name_w)) )
                                                     ERROR
  if ( key_string )
    strcpy(key_string,keyarea);
  else
    key_string = keyarea;
RECOVER
  key_string = NULL;
ENDSEQ
  return(key_string);
}

/******************************************************************************/
/**
\brief  Last - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Last"

logical ACPathNode :: Last ( )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_path.GoTop();
  while ( nodeptr = node_path.GetNext() )
    if ( !nodeptr->Get(LAST_INSTANCE) )              ERROR

  relative_index = nodecur = LAST_INSTANCE;
  nodeinst = Tail()->get_nodeinst();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Locate - 


\return term - Termination code

\param  entnr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical ACPathNode :: Locate (EB_Number entnr, logical read_opt )
{
  node                   *last = Tail();
  logical                 term = NO;

  ToTop();
  
  while ( !NextCollection() ) 
    if ( !last->Locate(entnr,read_opt) )   
      break;

  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey - 


\return term - Termination code

\param  skey - 
\param  exact - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical ACPathNode :: LocateKey (char *skey, logical exact, logical chknode )
{
  node                   *last = Tail();
  int32                   pos     = 0;
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( term = Tail()->LocateKey(skey,exact,chknode) )
  {
    ToTop();
    term = YES;
    while ( !NextCollection() )
      if ( !(term = Tail()->LocateKey(skey,exact,chknode)) )
        break;  
    if ( term )                                      ERROR
  }
  
  relative_index = nodecur = LAST_INSTANCE/2;

RECOVER
  ResetPosition();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateNode - 


\return nodeptr - 

\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateNode"

node *ACPathNode :: LocateNode (char *proppath )
{
  node                   *nodeptr = NULL;

BEGINSEQ
  node_path.GoBottom();
  while ( nodeptr = node_path.GetPrev() )
    if ( !strcmp(proppath,nodeptr->get_prop_path()) )     
      LEAVESEQ

ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical ACPathNode :: Lock ( )
{

  return( this ? Tail()->Lock() : YES );

}

/******************************************************************************/
/**
\brief  LockSet - 


\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockSet"

logical ACPathNode :: LockSet (logical chknode )
{
  logical          term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( Head()->LockSet() )                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Modify - 


\return instptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *ACPathNode :: Modify (logical chknode )
{
  void *   instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  instptr = Tail()->Modify(NO);
RECOVER

ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Move - 


\return targinst - 

\param  srcenode - 
\param  db_replace - Replace option
\param  w_newkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

void *ACPathNode :: Move (node *srcenode, PIREPL db_replace, char *w_newkey, logical chknode )
{
  void                 *targinst;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( !(targinst = Tail()->Move(srcenode,db_replace,w_newkey,chknode)) )
                                                     ERROR
RECOVER
  targinst = NULL;
ENDSEQ
  return(targinst);
}

/******************************************************************************/
/**
\brief  MoveDown - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical ACPathNode :: MoveDown ( )
{

  return( this ? Tail()->MoveDown() : YES );

}

/******************************************************************************/
/**
\brief  MoveUp - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical ACPathNode :: MoveUp ( )
{

    return( this ? Tail()->MoveUp() : YES );

}

/******************************************************************************/
/**
\brief  NextCollection - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextCollection"

logical ACPathNode :: NextCollection ( )
{
  node                   *nodeptr;
  node                   *last = Tail();
  logical                 term = NO;
BEGINSEQ
  node_path.GetTail();
  if ( GoUp(FOREWARD) )                             ERROR
  
  while ( nodeptr = node_path.GetNext() )      
  {
    if ( nodeptr == last )                           LEAVESEQ
    if ( PositionNode(nodeptr,FOREWARD,YES) )      
      if ( GoUp(FOREWARD) )                          ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NextKey - 


\return keyptr - 

\param  skey - 
\param  switch_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

char *ACPathNode :: NextKey (char *skey, int16 switch_level )
{
  char                   *keyptr = NULL;
BEGINSEQ
  if ( skey )
  {
    if ( LocateKey(skey,YES,NO) )
    {
      if ( LocateKey(skey,NO,NO) )                   ERROR
      nodecur++;
      LEAVESEQ
    }
  }

  if ( skey && !Get(AUTO) )                          ERROR

  if ( !Get(nodecur+1) )                             ERROR

  keyptr = ExtractKey(NULL,NULL);
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  parm_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACPathNode :: Open (BNFData *parm_data )
{
  node                   *nodeptr = nodenode;
  int32                   indx0 = 0;
  BNFData                *acp;
  logical                 copy = YES;
  logical                 col_opt = NO;
  logical                 term = NO;
BEGINSEQ
  if ( Open_intern(parm_data) )                     ERROR

  RegisterPathNode();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACPathNode :: Open (char *proppath )
{
  Dictionary      *dictptr = object_ref->GetDictionary();
  logical          term = NO;
BEGINSEQ
  delete bnf_spec;
  bnf_spec = NULL;
  
  if ( !(bnf_spec = dictptr->ParseExpression(proppath,"simple_op",NULL)) )
                                                     ERROR
  if ( Open(bnf_spec) )                              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenPathElement - 


\return nodeptr - 

\param  nodeptr - 
\param  acp - 
\param  indx_ref - 
\param  crt_copy - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenPathElement"

node *ACPathNode :: OpenPathElement (node *nodeptr, BNFData *acp, int32 &indx_ref, logical crt_copy )
{
  Dictionary      *dictptr   = object_ref->GetDictionary();
  smcb            *smcbptr   = nodeptr ? nodeptr->GetCurrentTypeDef() : NULL;
  fmcb            *fmcbptr;
  node            *pathnode  = NULL;
  FunctionTypes    path_type = FT_undefined;
  BNFData         *path_extension;
  int              autopos;
  char            *autokey = NULL;
  char             propname[1025];
  char             scope_name[65];
  char             names[ID_SIZE+1];
  BNFData         *bdata;
  int8             path_opt = 0;
  logical          first    = YES;
  node           **pnodeptr;
  node            *cpynode  = NULL;
  logical          term     = NO;
BEGINSEQ
  *propname = 0;
  if ( !acp->IsSymbol("access_path") && ++indx_ref == 1)
    bdata = acp;
  else if ( indx_ref == 0 )
    bdata = acp->GetElement(indx_ref++);
  else
    bdata = (path_extension = acp->GetElement(indx_ref++))
            ? path_extension->GetElement(1) : NULL;
  
  if ( !bdata )                                      ERROR
    
  while ( bdata )
  {
    if ( !(fmcbptr = ((BNFExpData *)bdata)->GetPathElement(dictptr,bdata,smcbptr,oper_env,path_type,path_opt,autopos,&autokey)) )
                                                     SDBERR(109)
    if ( !first )
      strcat(propname,".");
    gvtxbts(propname+strlen(propname),fmcbptr->fmcbname,ID_SIZE);
    
    if ( nodeptr )
    {
      if ( ((BNFExpData *)bdata)->GetScopeName(scope_name) )
        nodeptr->SetType(scope_name);
    }

    if ( first && indx_ref == 1 )
    {
      if ( pathnode = object_ref->GetStartNode(oper_env,propname,path_type,nodeacc) )
        switch ( path_type )
        {
          case FT_Extent   : owner = YES;
                             break;
          case FT_Variable : 
          case FT_Parameter: moveable_instance = YES;
                             break;
        }
      if ( moveable_instance && !pathnode )         ERROR
    }        
    if ( nodeptr && !pathnode && (fmcbptr->fmcbrlev == R_REFR || path_opt) )
    {
      if ( !(pnodeptr = nodeptr->GetNodePtr(propname)) ||
           !(pathnode = *pnodeptr) )               ERROR
           
      if ( first && crt_copy )
      {
        if ( !(pathnode = cpynode = pathnode->CreateCopy()) )
                                                    ERROR
        owner = YES;
      }
    }
    if ( pathnode )
    {
      switch ( path_opt )
      {
        case 1  : pathnode->SetAutoLocate(autopos,autokey,NO);
                  break;
        case 2  : pathnode->SetAutoLocate(autopos,autokey,YES);
                  break;
        case 3  : if ( pathnode->SetAutoLocateExpression(autokey,oper_env,NO) )
                                                    ERROR
                  break;
        case 4  : pathnode->stsstrans();
        default : ;
      }
      nodeptr = pathnode;
      if ( pathnode->IsCollection() )
        LEAVESEQ
    }
    
    if ( smcbptr = fmcbptr->fmcbsmcb )
      if ( smcbptr->smcbityp == UNDEF && dictptr )
        smcbptr = dictptr->ProvideStructDef(smcbptr->smcbname);
    
    if ( bdata == acp )
      bdata = NULL;
    else
      bdata = (path_extension = acp->GetElement(indx_ref++))
              ? path_extension->GetElement(1) : NULL;
            
    if ( nodeptr && !pathnode )     
      if ( !(pnodeptr = nodeptr->GetNodePtr(gvtxbts(names,fmcbptr->fmcbname,ID_SIZE))) ||
           !(pathnode = *pnodeptr) )               ERROR

    nodeptr = pathnode;
    pathnode = NULL;
    first = NO;
  }
RECOVER
  if ( owner )
    delete cpynode;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Open_intern - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  parm_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open_intern"

logical ACPathNode :: Open_intern (BNFData *parm_data )
{
  node                   *nodeptr = nodenode;
  int32                   indx0 = 0;
  BNFData                *acp;
  logical                 copy = YES;
  logical                 col_opt = NO;
  logical                 term = NO;
BEGINSEQ
  if ( !(bnf = parm_data) )                          SDBERR(99)
  if ( parm_data->IsSymbol("pname") )                ERROR

  if ( !(acp = parm_data->GetSymbol("access_path")) &&
       !(acp = parm_data->GetSymbol("path_element")))ERROR
  
  while ( nodeptr = OpenPathElement(nodeptr,acp,indx0,copy) )
  {
    node_path.AddTail(nodeptr);
    if ( !col_opt )
      if ( nodeptr->IsCollection() )
      {
        if ( nodeptr->IsAutoPosition() )
          nodeptr->Get(FIRST_INSTANCE);
        else
          col_opt = YES;
      }
        
    copy = NO;
  }
  
  SDBCERR
  context = new CTX_Property();
  context->Initialize(this,NULL);

  if ( !(nodeptr = Tail()) )
  {
    if ( moveable_instance )                         LEAVESEQ
    ERROR
  }
  nodeinst      = nodeptr->get_nodeinst();
  nodefield     = Bnodeptr->get_nodefield();
  sk_index      = Bnodeptr->get_sk_index();
  id_key        = Bnodeptr->get_id_key();
  is_collection = Bnodeptr->get_is_collection() && col_opt;
  is_memo       = Bnodeptr->get_is_memo();
  is_codeset    = Bnodeptr->get_is_codeset();
  is_opened     = YES;
  
  node::Open(nodenode,nodefield);
  if ( nodenode != highnod )
    nodenode = highnod;            // wegen check
  context->SetProcessState(PRC_Opened);
  
//  event_proxy = new EventProxy(*nodeptr->GetPH(),*GetPH());
//  event_proxy->ActivateProcessEventHandler();
//  event_proxy->ActivateServerEventHandler();

  if ( !is_collection && (!nodenode || nodenode->IsPositioned()) )
    First();
  SDBRESET
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open_intern"

logical ACPathNode :: Open_intern (char *proppath )
{
  Dictionary      *dictptr = object_ref->GetDictionary();
  logical          term = NO;
BEGINSEQ
  delete bnf_spec;
  bnf_spec = NULL;
  
  if ( !(bnf_spec = dictptr->ParseExpression(proppath,"simple_op",NULL)) )
                                                     ERROR
  if ( Open_intern(bnf_spec) )                       ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Position - 


\return indx0 - Position in collection

\param  count - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

int32 ACPathNode :: Position (int32 count, logical chknode )
{
  int8         direction = count > 0 ? FOREWARD : BACKWARD;
BEGINSEQ
  nodecur += count;
  while ( count && !GetPosition(direction) )
    count -= direction;

  if ( count )                                       ERROR
  
  UpdatePosition();
RECOVER

ENDSEQ
  return(nodecur);
}

/******************************************************************************/
/**
\brief  PositionNode - 


\return term - Termination code

\param  nodeptr - 
\param  direction - 
\param  accept_position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionNode"

logical ACPathNode :: PositionNode (node *nodeptr, int16 direction, logical accept_position )
{
  logical                 term = NO;
BEGINSEQ
  if ( !nodeptr )                                    ERROR
    
  if ( nodeptr->get_nodenode() && !nodeptr->get_nodenode()->IsPositioned() )
                                                     ERROR
  if ( nodeptr->stsctrans() )          // iteration node: a()
  {
    if ( nodeptr->Position(direction) == AUTO )      ERROR
  }
  else                                 // auto position: a, a(0), a('x')
  {
    if ( nodeptr->IsPositioned() )
    {
      if ( accept_position )                         LEAVESEQ
      nodeptr->Switch(AUTO);                         ERROR // do not read twice!!
    }
    if ( nodeptr->Get(AUTO) )                        LEAVESEQ
    if ( !nodeptr->Get(FIRST_INSTANCE) )             ERROR
    {
      if ( !nodeptr->IsMemo() )                      ERROR
      if ( !nodeptr->get_highnod() || !nodeptr->get_highnod()->IsSelected() )
                                                     ERROR
      if ( !nodeptr->GetInitInstance(YES) )          ERROR
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Provide - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEKP - 


\param  skey - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACPathNode :: Provide (char *skey, logical global_add )
{

BEGINSEQ
  SDBERR(99)
RECOVER

ENDSEQ
  return(NULL);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACPathNode :: Provide (int32 lindx0, logical global_add )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( !Get(lindx0) ) 
  {
    SDBCERR
    Tail()->Add(AUTO,NULL,NULL,NULL,global_add);      SDBCERR
  }
  instptr = nodeinst->get_iselarea();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i2 - 


\param  datarea - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACPathNode :: Provide (void *datarea, logical global_add )
{

  return( Tail()->Provide(datarea,global_add) );

}

/******************************************************************************/
/**
\brief  RegisterHandle - 


\return term - Termination code

\param  cs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterHandle"

logical ACPathNode :: RegisterHandle (CSA_Handle *cs_handle )
{

  return( Tail()->RegisterHandle(cs_handle) );

}

/******************************************************************************/
/**
\brief  Rename - 


\return term - Termination code

\param  identkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rename"

logical ACPathNode :: Rename (char *identkey, logical chknode )
{
  logical                term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( Tail()->Rename(identkey,chknode) )            ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReopenPath - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReopenPath"

logical ACPathNode :: ReopenPath ( )
{
  logical                 event_handling = object_ref->EventHandling();
  logical                 term = NO;
BEGINSEQ
  if ( context->ProcessState() == PRC_Busy )         ERROR

  Switch(AUTO);
  if ( event_handling )
    object_ref->DisableEventHandling();
  
  CloseHierarchy();
  
  if ( bnf_spec ? Open_intern(bnf_spec) : Open_intern(prop_path) ) 
                                                     ERROR


RECOVER
  term = YES;
ENDSEQ
  if ( event_handling )
    object_ref->EnableEventHandling();
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ACPathNode :: Reset ( )
{

  return( Tail()->Reset() );

}

/******************************************************************************/
/**
\brief  ResetExpression - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetExpression"

logical ACPathNode :: ResetExpression ( )
{

  return( Tail()->ResetExpression() );

}

/******************************************************************************/
/**
\brief  ResetInstanceEventHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceEventHandler"

void ACPathNode :: ResetInstanceEventHandler (EventLink *event_link )
{

  return( Tail()->ResetInstanceEventHandler(event_link) );

}

/******************************************************************************/
/**
\brief  ResetInstanceProcessHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceProcessHandler"

void ACPathNode :: ResetInstanceProcessHandler (EventLink *event_link )
{

  return( Tail()->ResetInstanceProcessHandler(event_link) );

}

/******************************************************************************/
/**
\brief  ResetNode - 


\return term - Termination code

\param  reset_all - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNode"

logical ACPathNode :: ResetNode (logical reset_all )
{
  node           *nodeptr;
  logical         reset = NO;
  if ( reset = bnode::ResetNode(reset_all) )
  {
    node_path.GoBottom();
    while ( nodeptr = node_path.GetPrev() )
      nodeptr->ResetNode(reset_all);
  }
  return(reset);
}

/******************************************************************************/
/**
\brief  ResetPosition - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPosition"

void ACPathNode :: ResetPosition ( )
{

  if ( is_opened && is_collection )
    Head()->ToTop();
  
  relative_index = AUTO;
  nodecur        = AUTO;
  nodewrit       = NO;

 

}

/******************************************************************************/
/**
\brief  ResetPropertyEventHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyEventHandler"

void ACPathNode :: ResetPropertyEventHandler (EventLink *event_link )
{

  return( Tail()->ResetPropertyEventHandler(event_link) );

}

/******************************************************************************/
/**
\brief  ResetPropertyProcessHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyProcessHandler"

void ACPathNode :: ResetPropertyProcessHandler (EventLink *event_link )
{

  return( Tail()->ResetPropertyProcessHandler(event_link) );

}

/******************************************************************************/
/**
\brief  ResetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical ACPathNode :: ResetWProtect ( )
{

  return( Tail()->ResetWProtect() );

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

logical ACPathNode :: Save (logical switchopt, logical overwrite, logical chknode )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(NO,NO) )                     ERROR
  if ( !IsSelected() )                               LEAVESEQ

  node_path.GoBottom();
  while ( nodeptr = node_path.GetPrev() )             
    if ( nodeptr->Save(switchopt,overwrite,chknode) )
      term = YES;

  if ( switchopt )
    ResetPosition();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Select - 


\return term - Termination code

\param  nodeptr - 
\param  expression - Expression
\param  min_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

logical ACPathNode :: Select (node *nodeptr, char *expression, int32 min_inst )
{
  logical                 term = NO;
BEGINSEQ
  SDBERR(99)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetExpression - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical ACPathNode :: SetExpression (char *expression )
{

  return( Tail()->SetExpression(expression) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical ACPathNode :: SetExpression (BNFData *bnf_data )
{

  return( Tail()->SetExpression(bnf_data) );

}

/******************************************************************************/
/**
\brief  SetGenAttribute - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  fldnames - Property name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACPathNode :: SetGenAttribute (char *fldnames, int attrtype, char *attrstr )
{

  return( Tail()->SetGenAttribute(fldnames,attrtype,attrstr) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACPathNode :: SetGenAttribute (int attrtype, char *attrstr )
{

  return( Tail()->SetGenAttribute(attrtype,attrstr) );

}

/******************************************************************************/
/**
\brief  i02 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACPathNode :: SetGenAttribute ( )
{

  return( Tail()->SetGenAttribute() );

}

/******************************************************************************/
/**
\brief  SetInstanceEventHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceEventHandler"

void ACPathNode :: SetInstanceEventHandler (EventLink *event_link )
{

  return( Tail()->SetInstanceEventHandler(event_link) );

}

/******************************************************************************/
/**
\brief  SetInstanceProcessHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceProcessHandler"

void ACPathNode :: SetInstanceProcessHandler (EventLink *event_link )
{

  return( Tail()->SetInstanceProcessHandler(event_link) );

}

/******************************************************************************/
/**
\brief  SetOrder - 


\return term - Termination code

\param  strnames - Type name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical ACPathNode :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  bnode              *last = (bnode *)Tail();
  logical             term = NO;
BEGINSEQ
  if ( last->SetOrder(strnames,attrtype,attrstr) ) ERROR
  
  sk_index = last->get_sk_index();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPropertyEventHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyEventHandler"

void ACPathNode :: SetPropertyEventHandler (EventLink *event_link )
{

  return( Tail()->SetPropertyEventHandler(event_link) );

}

/******************************************************************************/
/**
\brief  SetPropertyProcessHandler - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyProcessHandler"

void ACPathNode :: SetPropertyProcessHandler (EventLink *event_link )
{

  return( Tail()->SetPropertyProcessHandler(event_link) );

}

/******************************************************************************/
/**
\brief  SetType - 


\return term - Termination code

\param  strnames - Type name
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical ACPathNode :: SetType (char *strnames, logical chknode )
{

    return( Tail()->SetType(strnames,chknode) );

}

/******************************************************************************/
/**
\brief  SetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical ACPathNode :: SetWProtect ( )
{

  return( Tail()->SetWProtect() );

}

/******************************************************************************/
/**
\brief  Store - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical ACPathNode :: Store ( )
{

  return( Tail()->Store() );

}

/******************************************************************************/
/**
\brief  StringToKey - 


\return key_val - 

\param  key_string - 
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringToKey"

char *ACPathNode :: StringToKey (char *key_string, char *key_name_w )
{

  return( Tail()->StringToKey(key_string,key_name_w) );

}

/******************************************************************************/
/**
\brief  Tail - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Tail"

node *ACPathNode :: Tail ( )
{

  return ( this ? node_path.GetTail() : NULL );

}

/******************************************************************************/
/**
\brief  ToTop - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

logical ACPathNode :: ToTop ( )
{
  logical  term = NO;
  ResetPosition();
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical ACPathNode :: Unlock ( )
{

  return( Tail()->Unlock() );

}

/******************************************************************************/
/**
\brief  UnlockSet - 


\return term - Termination code

\param  extlock - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockSet"

logical ACPathNode :: UnlockSet (logical extlock, logical chknode )
{

  return( Head()->UnlockSet(extlock,chknode) );

}

/******************************************************************************/
/**
\brief  UnregisterHandle - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterHandle"

logical ACPathNode :: UnregisterHandle ( )
{

  return( Tail()->UnregisterHandle() );

}

/******************************************************************************/
/**
\brief  UpdatePosition - 


\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePosition"

void *ACPathNode :: UpdatePosition ( )
{
  bnode        *last = (bnode *)Tail();
  void         *instptr = NULL;
BEGINSEQ
  if ( nodecur != AUTO && !last->IsPositioned() )  
  {
    ResetInstance();                                ERROR
  }

  if ( nodecur == AUTO )
    nodecur = LAST_INSTANCE/2;
  if ( !is_collection )  
    nodecur = 0;
      
  nodeinst = last->get_nodeinst();
  nodewrit = last->IsWrite();

  instptr = last->GetArea();
  fld::SetArea((char *)instptr);

  stssfil();
RECOVER
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

node *ACPathNode :: ValidateNode (logical crt_opt )
{
  node     *nodeptr  = this ? node_path.GetHead() : NULL;
  node     *pathnode = NULL;
  node     *new_node = this;
BEGINSEQ
  if ( nodenode && !nodenode->IsSelected() )         ERROR

  if ( !is_opened || !Bnodeptr->IsValidForParent() )
  {
    if ( ReopenPath() )                              ERROR
  }
  else
  {
    node_path.GoTop();
    while ( pathnode = node_path.GetNext() )
      if ( nodeptr = pathnode->ValidateNode(crt_opt) )
        if ( nodeptr != pathnode )
          node_path.ReplaceAt(nodeptr);
  }
RECOVER
  new_node = NULL;
ENDSEQ
  return(new_node);
}

/******************************************************************************/
/**
\brief  ~ACPathNode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACPathNode"

     ACPathNode :: ~ACPathNode ( )
{

  Close();

  delete bnf_spec;
  bnf_spec = NULL;


}


