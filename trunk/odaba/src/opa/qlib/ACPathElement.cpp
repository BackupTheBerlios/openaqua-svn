/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACPathElement

\brief    Path element
          Path  elements are  used to  control access  for complex access paths.
          Path  elements allow navigating and iterating through a path. The path
          elements  optimize iteration through a  path. This optimisation can be
          disturbed, when mixing iteration and navigation (access by key).

\date     $Date: 2006/03/12 19:15:45,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACPathElement"

#include  <popa7.h>
#include  <sACElmView.hpp>
#include  <sACOPSelect.hpp>
#include  <sACObject.hpp>
#include  <sACOperation.hpp>
#include  <sACPath.hpp>
#include  <sACPathElement.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDBViewStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbinti.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <sACPathElement.hpp>


/******************************************************************************/
/**
\brief  ACPathElement - 


-------------------------------------------------------------------------------
\brief i0


\param  accpath -
\param  parent_element -
\param  prophdl -
\param  fttype -
\param  opname -
\param  path_operand -
\param  parm_data -
\param  key_names -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathElement"

                        ACPathElement :: ACPathElement (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *prophdl, FunctionTypes fttype, char *opname, BNFData *path_operand, BNFData *parm_data, char *key_names )
                     : bnode (),
  acc_path(accpath),
  parameters(NULL),
  parm_count(0),
  class_ref(NULL),
  co(prophdl),
  op_type(fttype),
  op_code(ST_undefined),
  bnf_top_string(NULL),
  bnf_top(NULL),
  bnf_operand(path_operand),
  bnf_parm(parm_data),
  operation(NULL),
  selection(),
  operand(),
  order(NULL),
  set_operation(NO),
  meta_operation(NO),
  var_selection(NO),
  path_index(AUTO),
  start_index(AUTO),
  path_objid(0),
  stop_index(AUTO),
  last_node(NO)
{

  nodetype = NT_ACPathElement;
  
  nodenode   = parent_element;
  object_ref = accpath->get_object_ref();
  nodeacc    = nodenode ? nodenode->GetMode(NO) : acc_path->GetMode(NO);
  
  gvtxbts(op_name,opname,ID_SIZE);
  set_order(key_names);  


}

/******************************************************************************/
/**
\brief i01


\param  acpelmref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathElement"

                        ACPathElement :: ACPathElement (ACPathElement &acpelmref )
                     : bnode (acpelmref),
  acc_path(NULL),
  parameters(NULL),
  parm_count(0),
  class_ref(acpelmref.get_class_ref()),
  co(NULL),
  op_type(FT_undefined),
  op_code(ST_undefined),
  bnf_top_string(NULL),
  bnf_top(NULL),
  bnf_operand(NULL),
  bnf_parm(NULL),
  operation(NULL),
  selection(),
  operand(),
  order(NULL),
  set_operation(NO),
  meta_operation(NO),
  var_selection(NO),
  path_index(AUTO),
  start_index(AUTO),
  path_objid(0),
  stop_index(AUTO),
  last_node(NO)
{



}

/******************************************************************************/
/**
\brief i02


\param  accpath -
\param  co_node -
\param  nodeptr -
\param  key_names -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathElement"

                        ACPathElement :: ACPathElement (ACPath *accpath, node *co_node, node *nodeptr, char *key_names )
                     : bnode (),
  acc_path(accpath),
  parameters(NULL),
  parm_count(0),
  class_ref(NULL),
  co(NULL),
  op_type(FT_undefined),
  op_code(ST_undefined),
  bnf_top_string(NULL),
  bnf_top(NULL),
  bnf_operand(NULL),
  bnf_parm(NULL),
  operation(NULL),
  selection(),
  operand(),
  order(NULL),
  set_operation(NO),
  meta_operation(NO),
  var_selection(NO),
  path_index(AUTO),
  start_index(AUTO),
  path_objid(0),
  stop_index(AUTO),
  last_node(NO)
{

  nodetype = NT_ACPathElement;
  
  nodenode   = co_node;
  object_ref = nodeptr->GetObjectHandle();
  nodeacc    = nodeptr->GetMode(NO);
    
  strcpy(op_name,nodeptr->get_prop_path());
  operand.RegisterNode(nodeptr);
  
  set_order(key_names);
  
  Setup();

}

/******************************************************************************/
/**
\brief i03


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathElement"

                        ACPathElement :: ACPathElement ( )
                     : bnode (),
  acc_path(NULL),
  parameters(NULL),
  parm_count(0),
  class_ref(NULL),
  co(NULL),
  op_type(FT_undefined),
  op_code(ST_undefined),
  bnf_top_string(NULL),
  bnf_top(NULL),
  bnf_operand(NULL),
  bnf_parm(NULL),
  operation(NULL),
  selection(),
  operand(),
  order(NULL),
  set_operation(NO),
  meta_operation(NO),
  var_selection(NO),
  path_index(AUTO),
  start_index(AUTO),
  path_objid(0),
  stop_index(AUTO),
  last_node(NO)
{



}

/******************************************************************************/
/**
\brief i04


\param  accpath -
\param  parent_element -
\param  prophdl -
\param  dbview_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPathElement"

                        ACPathElement :: ACPathElement (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *prophdl, DBStructDef *dbview_str )
                     : bnode (),
  acc_path(accpath),
  parameters(NULL),
  parm_count(0),
  class_ref(dbview_str),
  co(prophdl),
  op_type(FT_Operation),
  op_code(ST_set_select),
  bnf_top_string(NULL),
  bnf_top(NULL),
  bnf_operand(NULL),
  bnf_parm(NULL),
  operation(NULL),
  selection(),
  operand(),
  order(NULL),
  set_operation(NO),
  meta_operation(NO),
  var_selection(NO),
  path_index(AUTO),
  start_index(AUTO),
  path_objid(0),
  stop_index(AUTO),
  last_node(NO)
{
  node             *nodeptr;
// for select operations, only
  nodetype = NT_ACPathElement;
//  set_operation = YES;
  
  nodenode   = parent_element;
  object_ref = accpath->get_object_ref();
  nodeacc    = co->GetNode()->GetMode(NO);
  
  gvtxbts(op_name,"select",ID_SIZE);

  if ( nodeptr = new ACOPSelect(co->GetNode(),dbview_str) )
    operand.RegisterNode(nodeptr);

}

/******************************************************************************/
/**
\brief  AccessNode - 


\return pelement

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AccessNode"

ACPathElement *ACPathElement :: AccessNode ( )
{

  return ( this && meta_operation
           ? Pnodenode->AccessNode() 
           : this                                    );

}

/******************************************************************************/
/**
\brief  AccessParent

\return pelement

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AccessParent"

ACPathElement *ACPathElement :: AccessParent ( )
{

  return ( this && (set_operation || meta_operation)
           ? Pnodenode->AccessParent() 
           : Pnodenode                  );

}

/******************************************************************************/
/**
\brief  Add - 


\return instptr -
-------------------------------------------------------------------------------
\brief i0


\param  lindx0 -
\param  global_add -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACPathElement :: Add (int32 lindx0, logical global_add )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( !(global_add 
         ? operand.AddGlobal(lindx0)
         : operand.Add(lindx0)        )  ) ERROR

  SetupInstance();
  instptr = nodeinst->get_iselarea();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief i1


\param  lindx0 -
\param  skey -
\param  idkey -
\param  initinst -
\param  global_add -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACPathElement :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( !(global_add 
         ? operand.AddGlobal(lindx0,skey,idkey,initinst)
         : operand.Add(lindx0,skey,idkey,initinst))  ) ERROR

  SetupInstance();
  instptr = nodeinst->get_iselarea();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  CanUpdateCollection - 


\return cond

\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanUpdateCollection"

logical ACPathElement :: CanUpdateCollection (logical chknode )
{

  return( operand.IsCollectionUpdate(chknode) );

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

logical ACPathElement :: Cancel (logical chknode )
{
  logical                 term = NO;
  operand.Cancel();
  ResetNode(NO);
  
  if ( nodenode )
    nodenode->Cancel();

  path_objid = UNDEF;
  start_index = AUTO;
  stop_index  = AUTO;
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

PIACC ACPathElement :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC       oldmode;
BEGINSEQ
  if ( (oldmode = operand.ChangeMode(accopt)) == PI_undefined )
                                                     ERROR
  nodeacc = accopt;
  SetupInstance();
RECOVER
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

logical ACPathElement :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
BEGINSEQ
  if ( autoini )
  {
    if ( Pnodenode && Pnodenode->Check(autoini,acccheck) )
                                                     ERROR
    if ( operand.GetNode() )
    {
      if ( !is_opened )
        Open(NULL);
      else
        nodeinst = operand.GetNode()->get_nodeinst(); // uebergeht die nodeinst des ACTransientReference ????
    }
  }
  
  bnode::Check(autoini,acccheck);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACPathElement :: Close ( )
{

  nodeinst = NULL;
  
//operand.Close();
  bnode::Close();

  dbf::Reset();
  return(NO);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACPathElement :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACPathElement(*this) ) )      SDBERR(95)
                                                     SDBCERR

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief NODEID


\param  indx0 - Position in collection
\param  chknode -
\param  del_dep -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACPathElement :: Delete (int32 indx0, logical chknode, logical del_dep )
{
  logical                 term;
BEGINSEQ
  if ( operand.Delete(indx0,del_dep) )          ERROR

  ResetNode(NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i1


\param  skey -
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACPathElement :: Delete (char *skey, logical chknode )
{
  logical                 term;
BEGINSEQ
  if ( operand.Delete(skey) )                    ERROR

  ResetNode(NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical ACPathElement :: ExecPropCtxFunc (char *fnames, char *w_parms )
{
  logical    term = NO;
BEGINSEQ
  if ( !CheckPropCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecPropCtxFunc(fnames,w_parms) )    ERROR
  }
  else
  {
    if ( operand.ExecutePropertyAction(fnames,w_parms) )
                                                     ERROR
    nstring = operand.GetActionResult();
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

logical ACPathElement :: ExecStrCtxFunc (char *fnames, char *w_parms )
{
  logical   term = NO;
BEGINSEQ
  if ( !CheckStrCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecStrCtxFunc(fnames,w_parms) )    ERROR
  }
  else
  {
    if ( operand.ExecuteInstanceAction(fnames,w_parms) )
                                                     ERROR
    nstring = operand.GetActionResult();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExtractKey - 


\return keyptr -
-------------------------------------------------------------------------------
\brief NODEKE


\param  keyptr -
\param  instptr -
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ACPathElement :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{
  char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractKey(keyptr,instptr,chknode) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = operand.ExtractKey(keyptr,NULL);

RECOVER
  kptr = NULL;
ENDSEQ
  return(kptr);

}

/******************************************************************************/
/**
\brief i1


\param  keyptr -
\param  kcbptr -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ACPathElement :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{
  char          *kptr = NULL;

BEGINSEQ
  if ( kptr = bnode::ExtractKey(keyptr,kcbptr,instptr) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = operand.ExtractKey(keyptr,NULL);

RECOVER
  kptr = NULL;
ENDSEQ
  return(kptr);
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

char *ACPathElement :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{
  char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractSortKey(keyptr,instptr,chknode) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = operand.ExtractSortKey(keyptr,NULL);

RECOVER
  kptr = NULL;
ENDSEQ
  return(kptr);
}

/******************************************************************************/
/**
\brief  Get - 


\return instptr -
-------------------------------------------------------------------------------
\brief NODEIG


\param  indx0 - Position in collection
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPathElement :: Get (int32 indx0, logical chknode )
{
  int32      curri   = AUTO;
  void      *instptr = NULL;
BEGINSEQ
  if ( indx0 == AUTO )
    indx0 = 0;
  
  if ( last_node )
    SetupPathIndex(indx0);
  
  curri = indx0;
  if ( indx0 > nodecur/2 ) 
    indx0 -= nodecur; 
  else 
  {
    Switch(AUTO);
    Cancel();
    indx0++;
  }
    
  if ( indx0 >= 0 ? Next(indx0) : Prev(-indx0) )     ERROR

  nodecur = curri;
  instptr = nodeinst ? nodeinst->get_iselarea() : flddata;
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief i1


\param  skey -
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPathElement :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( !operand.Get(skey) )                            ERROR 

  SetupInstance();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACPathElement :: Get ( )
{
  void                   *instptr = NULL;

  return(instptr);
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

int32 ACPathElement :: GetCount (logical chknode )
{
  int32                   count = 0;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  Switch(AUTO);
  Cancel();
  
  while ( !NextParent() )
    count += operand.GetCount();

RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetElementType - 


\return fttype -

\param  dictionary -
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementType"

FunctionTypes ACPathElement :: GetElementType (Dictionary *dictionary, smcb *smcbptr )
{
  DBStructDef   *strdef;
  BNFData       *scoped_name;
  logical        is_top = smcbptr ? NO : YES;
  int            indx0 = 0;

BEGINSEQ
/*  
  if ( op_type != FT_undefined )                     LEAVESEQ
  if ( !bnf_operand )                                ERROR
  
  if ( !smcbptr )
    smcbptr = co->GetCurrentTypeDef();
  class_ref = DBStructDef::GetDBStruct(smcbptr);
    
  if ( (op_type = IsOperation()) == FT_Operation )   LEAVESEQ
    
  if ( bnf_operand->IsSymbol("path_name") )
  {
    if ( scoped_name = bnf_operand->GetSymbol("scoped_name") )
      if ( scoped_name->GetElement(1) )   // name is really scoped
      {
        if ( !(class_ref = dictionary->ProvideStructDef(scoped_name->GetElement(0)->StringValue())) )
                                                     ERROR
        bnf_operand = scoped_name->GetElement(1)->GetElement("identifier");
        smcbptr = class_ref;
      }
  }

  if ( is_top )
  {
    if ( (op_type = IsLocalVariable()) == FT_Variable ) 
                                                     LEAVESEQ
    if ( (op_type = IsParameter()) == FT_Parameter ) LEAVESEQ
  }
  if ( smcbptr )
  {
    if ( smcbptr->smcbityp )
      strdef = (DBStructDef *)smcbptr;
    else
      if ( !(strdef = dictionary->GetStructDef(smcbptr->smcbname,smcbptr->smcbnsid)) )
                                                     ERROR
    
    if ( (op_type = IsProperty(smcbptr)) == FT_Property )
                                                     LEAVESEQ
    if ( (op_type = IsFunction(dictionary,smcbptr)) == FT_Function )
                                                     LEAVESEQ
    if ( (op_type = IsExpression(dictionary,smcbptr)) == FT_Expression )
                                                     LEAVESEQ
    if ( (op_type = IsAction(smcbptr)) == FT_Action )
                                                     LEAVESEQ
    
    for ( indx0 = 1; indx0 <= strdef->get_base_info().get_count() && op_type == FT_undefined; indx0++ )
      op_type = GetElementType(dictionary,smcbptr->GetEntry(indx0)->fmcbsmcb);         
      
    if ( op_type == FT_error )                       ERROR
    if ( op_type != FT_undefined )                   LEAVESEQ
      
    if ( (op_type = xCheckPHFunction(co,op_name,NULL)) == FT_PHFunction )  // PropertyHandle-Function
                                                     LEAVESEQ
    if ( nodenode )    // path extensions, only                              
    {
      SDBERR(109)   // verhindert spätere Auflösung von Membern in weak/untyped references
      LEAVESEQ      // so war es vorher, aber dann sehen wir keine Fehler
    }
  }
  else if ( is_top )
  {
    if ( (op_type = IsGlobalVariable()) == FT_Global )
                                                     LEAVESEQ
    if ( co )  // base type operations
    {
      if ( (op_type = xCheckPHFunction(co,op_name,NULL)) == FT_PHFunction )  // PropertyHandle-Function
                                                     LEAVESEQ
    }

    if ( !nodenode ) // global resources
    {
      if ( (op_type = xCheckSysFunction(op_name,NULL)) == FT_SysFunction )  // System-Function
                                                     LEAVESEQ
      if ( (op_type = IsEnumeration(dictionary)) == FT_Enumeration)
                                                     LEAVESEQ
      if ( (op_type = IsExtent(dictionary)) == FT_Extent)   LEAVESEQ
    }
  }
  if ( is_top )
    SDBERR(109)   // verhindert spätere Auflösung von Membern in weak/untyped references 
*/
RECOVER

ENDSEQ
  if ( op_type != FT_error )
    SDBRESET
  return(op_type);
}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum -
-------------------------------------------------------------------------------
\brief NODEGID


\param  indx0 - Position in collection
\param  chknode -
\param  pif_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACPathElement :: GetID (int32 indx0, logical chknode, logical pif_opt )
{

  return( operand.GetLOID(indx0) );

}

/******************************************************************************/
/**
\brief NODEGID_


\param  keyptr -
\param  chknode -
\param  pif_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACPathElement :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

  return( operand.GetLOID(keyptr) );

}

/******************************************************************************/
/**
\brief  GetInitInstance - 


\return instptr -

\param  set_init -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitInstance"

void *ACPathElement :: GetInitInstance (logical set_init )
{
  void             *instptr = NULL;
BEGINSEQ
  if ( !(instptr = (set_init ? operand.GetInitInstance() 
                             : operand.GetInitArea()).GetData()) ) 
                                                     ERROR
  SetupInstance();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetKeyLength - 


\return klen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 ACPathElement :: GetKeyLength ( )
{
  int16          klen;
  return( (klen = bnode::GetKeyLength()) 
          ? klen : operand.GetKeyLength() );

}

/******************************************************************************/
/**
\brief  GetKeySMCB - 


\return smcbptr - Pointer to general structure definition

\param  key_name_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeySMCB"

smcb *ACPathElement :: GetKeySMCB (char *key_name_w )
{
  smcb             *smcbptr;
  return( (smcbptr = bnode::GetKeySMCB(key_name_w)) 
          ? smcbptr : operand.GetKeySMCB(key_name_w) );


}

/******************************************************************************/
/**
\brief  GetNodePtr - 


\return nodeptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node *ACPathElement :: GetNodePtr ( )
{
  node           *nodeptr;
  if ( !(nodeptr = operation->GetNode()) )
    nodeptr = operand.GetNode();
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetSortKeyLength - 


\return klen -

\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeyLength"

int16 ACPathElement :: GetSortKeyLength (logical chknode )
{
  int16          klen;
  return( (klen = bnode::GetSortKeyLength()) 
          ? klen : operand.GetSortKeyLength() );


}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 


\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *ACPathElement :: GetSortKeySMCB ( )
{
  smcb             *smcbptr;
  return( (smcbptr = bnode::GetSortKeySMCB()) 
          ? smcbptr : operand.GetSortKeySMCB() );


}

/******************************************************************************/
/**
\brief  InitCollection - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitCollection"

logical ACPathElement :: InitCollection (Dictionary *dict_ptr )
{
  BNFData     *bdata;
  node        *nodeptr;
  logical      term = NO;
BEGINSEQ
  if ( co && !co->GetDescription() )                 LEAVESEQ
  
  if ( !(bdata = bnf_operand->GetElement(0)) )       SDBERR(99)
  if ( !(bdata = ((BNFExpData *)bdata)->GetAccessPath()) )           SDBERR(99)
  
  if ( !(nodeptr = new ACPath(dict_ptr,object_ref,co->GetNode(),bdata,
                              acc_path->get_variables(),acc_path->get_parameters())) )
                                                     ERROR
  operand.RegisterNode(nodeptr);  
  
  if ( bnf_parm )         
    if ( InitSelection(dict_ptr) )                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitElement - 


\return term - Termination code

\param  dictionary -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitElement"

logical ACPathElement :: InitElement (Dictionary *dictionary )
{
  logical                 term = NO;
BEGINSEQ
  if ( op_type == FT_undefined )
    GetElementType(dictionary,NULL);

  switch ( op_type )
  {
    case FT_Property         : term = InitProperty(dictionary);
                               break;
    case FT_View             : term = InitView(dictionary);
                               break;
    case FT_Extent           : 
    case FT_Enumeration      : term = InitProperty(dictionary,acc_path->get_nodeacc());
                               break;
    
    case FT_Operation        : 
    case FT_Function         : 
    case FT_Expression       : 
    case FT_PHFunction       : 
    case FT_SysFunction      : term = InitOperation(dictionary);
                               break;
    case FT_Global           : term = InitGlobalVariable(dictionary);
                               break;
    case FT_SysVariable      : term = InitSysVariable(dictionary);
                               break;
    case FT_Collection       : term = InitCollection(dictionary);
                               break;
    case FT_InlineExpression : term = InitInlineExpression(dictionary);
                               break;
    case FT_OQLOperation     : // term = InitOQLOperation(dictionary);
                               // break;
    case FT_Action           : // term = InitAction(dictionary);
                               // break;
    case FT_Variable         : // term = InitLocalVariable(dictionary);
                               // break;
    case FT_Parameter        : // term = InitParameter(dictionary);
                               // break;
                               SDBERR(109)
    case FT_undefined        : LEAVESEQ
    default                  : term = YES;
  }
  if ( term )                                   SDBERR(109)
  Setup();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitGlobalVariable - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitGlobalVariable"

logical ACPathElement :: InitGlobalVariable (Dictionary *dict_ptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( operand.Open(dict_ptr->GetGlobalVariable(op_name)) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitGroupOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitGroupOperation"

logical ACPathElement :: InitGroupOperation (Dictionary *dict_ptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitInlineExpression - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInlineExpression"

logical ACPathElement :: InitInlineExpression (Dictionary *dict_ptr )
{
  int          len        = bnf_operand->GetValueLength();
  DBFieldDef  *field_def;
  char        *expression = NULL;
  BNFData     *bdata      = bnf_operand->GetElement(0);
  logical      term       = NO;
BEGINSEQ
  if ( co && !co->GetDescription() )                 LEAVESEQ
  if ( operation )                                   LEAVESEQ
      
  if ( !((BNFExpData *)bdata)->IsBlock() && !bdata->IsA("operand") )
    if ( !(bdata = ((BNFExpData *)bnf_operand)->GetSimpleOp()) )     SDBERR(99)  // block or operation
  
  operation = new Operation();
  operation->SetCallingObject(co);
  
  if ( operation->ProvExpression(dict_ptr,NULL,NULL,bnf_operand) )      
                                                     ERROR
  Open(field_def = operation->GetRetvalDefinition());
  if ( field_def )
    set_operation = field_def->get_set_operation();
  
  if ( fldfmcb )
    gvtxstb(fldfmcb->fmcbname,op_name,ID_SIZE);


RECOVER
  if ( expression )
    free(expression);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitIntersectOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitIntersectOperation"

logical ACPathElement :: InitIntersectOperation (Dictionary *dict_ptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitJoinOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitJoinOperation"

logical ACPathElement :: InitJoinOperation (Dictionary *dict_ptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitLocation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitLocation"

logical ACPathElement :: InitLocation (Dictionary *dict_ptr )
{
  BNFData     *bdata;
  logical      term = NO;
BEGINSEQ
  parameters = new ParmList();
  
  switch ( ((BNFExpData *)bnf_parm)->GetParmCount() )
  {
    case 0    : LEAVESEQ
    case 1    : if ( bdata = ((BNFExpData *)bnf_parm)->GetOperand() ) 
                {
                  bdata = ((BNFExpData *)bdata)->GetSimpleOp();
                  if ( bdata->IsA("std_constant") )
                    term = operand.GetNode()->SetPathExpression(bdata->GetStringValue(NULL,NULL),'(');
                  else if ( bdata->IsA("access_path") )
                  {
                    DBObjectHandle    dbo(object_ref);
                    if ( co ? selection.OpenAccessPath(*co,bdata,acc_path->get_variables(),
                                                       acc_path->get_parameters(),YES)
                            : selection.OpenAccessPath(dbo,bdata,acc_path->get_variables(),
                                                       acc_path->get_parameters(),PI_Read) )
                                                     ERROR
                    var_selection = YES;
                  }
                }
                break;
    case AUTO : 
    default   : SDBERR(99)
  }
  if ( term )                                        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitMetaOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMetaOperation"

logical ACPathElement :: InitMetaOperation (Dictionary *dict_ptr )
{
  char        *expression = NULL;
  logical      term = NO;
BEGINSEQ
  if ( !bnf_parm )                                   SDBERR(99)
  meta_operation = YES;
    
  operand.Open(co);
                             
  switch ( op_code )
  {
    case ST_set_locate   : if ( InitLocation(dict_ptr) )
                                                     ERROR
                           break;
    case ST_set_where    : if ( InitSelection(dict_ptr) )
                                                     ERROR
                           break;
    case ST_set_order_by : if ( InitParmList(dict_ptr) )
                                                     ERROR
                           if ( parm_count < 1 || parm_count > 2 )
                                                     SDBERR(79)
                           co->SetOrder((*parameters)[0]->GetString(),
                                        parm_count == 2 ? (*parameters)[1]->GetString() : NULL);                        
                           break;
    default : ;
  }
    


RECOVER
  if ( expression )
    free(expression);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitMinusOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMinusOperation"

logical ACPathElement :: InitMinusOperation (Dictionary *dict_ptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOperation"

logical ACPathElement :: InitOperation (Dictionary *dict_ptr )
{
  char        *expression = NULL;
  DBFieldDef  *field_def;
  logical      term = NO;
BEGINSEQ
  if ( co && !co->GetDescription() )                 LEAVESEQ
      
  if ( op_type == FT_Operation )  // system operation
    switch ( op_code )
    {
      case ST_set_where    : 
      case ST_set_order_by : if ( InitMetaOperation(dict_ptr) )
                                                     ERROR
                             LEAVESEQ
      case ST_set_select   : if ( operand.Open(*co,ST_set_select,bnf_parm) )
                                                     ERROR
//                             set_operation = YES;
                             LEAVESEQ
      case ST_set_group_by : if ( InitGroupOperation(dict_ptr) )
                                                     ERROR
                             LEAVESEQ
      case ST_set_union    : if ( InitUnionOperation(dict_ptr) )
                                                     ERROR
                             LEAVESEQ
      case ST_set_intersect: if ( InitIntersectOperation(dict_ptr) )
                                                     ERROR
                             LEAVESEQ
      case ST_set_minus    : if ( InitMinusOperation(dict_ptr) )
                                                     ERROR
                             LEAVESEQ
      case ST_set_join     : if ( InitJoinOperation(dict_ptr) )
                                                     ERROR
                             LEAVESEQ
      case ST_file_output  : 
      case ST_db_output    : if ( operand.Open(*co,op_code,bnf_parm) )
                                                     ERROR
                             set_operation = YES;
                             LEAVESEQ
      default : ;
    }
  
  if ( operation )                                   LEAVESEQ
  
  operation = new Operation();
  operation->SetCallingObject(co);
  
  if ( bnf_parm )         
    if ( InitParmList(dict_ptr) )                    ERROR
  
// mit OP... anders
//  if ( operation->ProvOperation(dict_ptr,class_ref,op_name,op_type,op_code,parameters) )    
                                                     ERROR
  Open(field_def = operation->GetRetvalDefinition());
    
  if ( field_def )
  {
    set_operation = field_def->get_set_operation();
    operand.Open(operation);
  }
    
  if ( fldfmcb && fldfaloc )
    gvtxstb(fldfmcb->fmcbname,op_name,ID_SIZE);


RECOVER
  if ( expression )
    free(expression);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitParmList - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitParmList"

logical ACPathElement :: InitParmList (Dictionary *dict_ptr )
{
  BNFExpData                *plist;
  BNFExpData                *parm_data;
  BNFExpData                *parm_ext;
  logical                 term = NO;
BEGINSEQ
  switch ( parm_count = ((BNFExpData *)bnf_parm)->GetParmCount() )
  {
    case AUTO : ERROR
    case 0    : LEAVESEQ;
    default   : plist = ((BNFExpData *)bnf_parm)->GetParmList();  // parm_list
                parameters = new ParmList(YES);
  }
    
  parm_count = 0;
  parm_data = plist->GetElement(parm_count);     // parameter
  while ( parm_data )
  {
    parameters->AddParm(NULL);
    if ( OpenParmHandle((*parameters)[parm_count],parm_data) )
                                                     ERROR
    if ( parm_ext = plist->GetElement(++parm_count) )  // param_ext
      parm_data = parm_ext->GetElement(1);         // , parameter
    else
      parm_data = NULL;
  }
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitPath - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitPath"

logical ACPathElement :: InitPath ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( Pnodenode ) 
    Pnodenode->InitPath();

  if ( InitializeOperand() )                         ERROR
  operand.Get(FIRST_INSTANCE);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitProperty - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i00


\param  dict_ptr - Dictionary handle
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitProperty"

logical ACPathElement :: InitProperty (Dictionary *dict_ptr, PIACC accopt )
{
  DBObjectHandle          obh(object_ref);
  logical                 term = NO;
BEGINSEQ
  if ( operand.Open(obh,op_name,accopt) )             ERROR
  
  if ( bnf_parm )         
    if ( InitSelection(dict_ptr) )                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitProperty"

logical ACPathElement :: InitProperty (Dictionary *dict_ptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !co->GetDescription() )                       LEAVESEQ
    
  if ( operand.Open(co,op_name) )                    ERROR

  if ( bnf_parm )
    if ( InitSelection(dict_ptr) )                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitSelection - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSelection"

logical ACPathElement :: InitSelection (Dictionary *dict_ptr )
{
  BNFData     *bdata;
  logical      term = NO;
BEGINSEQ
  parameters = new ParmList();
  
  switch ( ((BNFExpData *)bnf_parm)->GetParmCount() )
  {
    case 0    : LEAVESEQ
    case 1    : if ( bdata = ((BNFExpData *)bnf_parm)->GetOperand() ) 
                  term = operand.SetSelection(bdata); 
                break;
    case AUTO : 
    default   : SDBERR(99)
  }
  if ( term )                                        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitSysVariable

\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSysVariable"

logical ACPathElement :: InitSysVariable (Dictionary *dict_ptr )
{
  DBFieldDef             *field_def;
  char                   *string;
  logical                 term = NO;
  if ( !(string = GetSysVariable(op_name)) )
    string = "";
    
  operand.AllocDescription();
  field_def = operand.GetDescription();
  *(fmcb *)field_def = *fmcb::GetStaticFMCB(T_STRING);
  gvtxstb(field_def->fmcbname,op_name,ID_SIZE);
  field_def->fmcbbyte = (field_def->fmcbsize = strlen(string)) + 1;
  operand.AllocateArea();
  operand = string;

  return(term);
}

/******************************************************************************/
/**
\brief  InitUnionOperation - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitUnionOperation"

logical ACPathElement :: InitUnionOperation (Dictionary *dict_ptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitView - 


\return term - Termination code

\param  dict_ptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitView"

logical ACPathElement :: InitView (Dictionary *dict_ptr )
{
  DBObjectHandle    obh(object_ref);
  logical           term    = NO;
BEGINSEQ
  if ( co->GetDescription() ? operand.Open(*co,bnf_operand->GetStringValue(NULL,NULL)) 
                            : operand.Open(obh,bnf_operand->GetStringValue(NULL,NULL),nodeacc) )             
                                              ERROR
  if ( bnf_parm )
    if ( InitSelection(dict_ptr) )                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeOperand - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeOperand"

logical ACPathElement :: InitializeOperand ( )
{
  PropertyHandle         *parameter;
  int                     indx0 = 0;  
  logical                 term = NO;
BEGINSEQ
  nodecur = AUTO;
  
  if ( op_type == FT_error )                         ERROR
  if ( op_type == FT_undefined || !operand.GetNode() )
    if ( InitElement(acc_path->get_dictionary()) )   ERROR
        
  if ( parameters )
    while ( parameter = (*parameters)[indx0++] )
    {
      if ( !parameter->IsPositioned() )
      {
        parameter->PositionTop();
        parameter->Get(FIRST_INSTANCE);
      }
    }

  if ( operation )
  {
    Close();
    operation->SetCallingObject(co);
    if ( operation->Execute(parameters) )
                                                     ERROR
    operand.Open(operation);
    if ( op_type == FT_InlineExpression && bnf_parm )         
      if ( InitSelection(acc_path->get_dictionary()) )
                                                     ERROR
  }
  
  if ( Open(NULL) )                                  ERROR
  stssfil();
  nodecur = AUTO;    // 30.8.2004, damit Next auch für Attribute geht

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeOperands - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeOperands"

logical ACPathElement :: InitializeOperands ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( set_operation && Pnodenode )
    if ( Pnodenode->InitializeOperands() )           ERROR
      
  if ( !meta_operation )
    if ( InitializeOperand() )                       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsAction - 


\return fttype -

\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAction"

FunctionTypes ACPathElement :: IsAction (smcb *smcbptr )
{

BEGINSEQ
  if ( strlen(op_name) > ID_SIZE )                  LEAVESEQ
    
  LEAVESEQ // kommst später
  op_type = FT_Action;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsEnumeration - 


\return fttype -

\param  dictionary -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

FunctionTypes ACPathElement :: IsEnumeration (Dictionary *dictionary )
{
  DBExtend   *dbext;
  char       *ext_type;
BEGINSEQ
  if ( strlen(op_name) > ID_SIZE )                   LEAVESEQ
    
  if ( !dictionary->GetExtentType(op_name) )         LEAVESEQ
    
  if ( !(dbext = dictionary->ProvideExtendDef(op_name)) || 
         dbext->fmcbsmcb->smcbstyp != ST_CODE )      LEAVESEQ
    
  op_type = FT_Enumeration;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsExpression - 


\return fttype -

\param  dictionary -
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpression"

FunctionTypes ACPathElement :: IsExpression (Dictionary *dictionary, smcb *smcbptr )
{

BEGINSEQ
  if ( strlen(op_name) > ID_SIZE )                   LEAVESEQ
    
  if ( !dictionary->ProvExpression(NULL,smcbptr->smcbname,op_name,NULL,NULL,NULL) )
                                                     LEAVESEQ
  op_type = FT_Expression;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsExtent - 


\return fttype -

\param  dictionary -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExtent"

FunctionTypes ACPathElement :: IsExtent (Dictionary *dictionary )
{

BEGINSEQ
  if ( strlen(op_name) > ID_SIZE )                   LEAVESEQ
    
  if ( !dictionary->GetExtentType(op_name) )         LEAVESEQ
    op_type = FT_Extent;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsFunction - 


\return fttype -

\param  dictionary -
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFunction"

FunctionTypes ACPathElement :: IsFunction (Dictionary *dictionary, smcb *smcbptr )
{

BEGINSEQ
  if ( strlen(op_name) > ID_SIZE )                   LEAVESEQ
    
  if ( !dictionary->ProvFunction(NULL,smcbptr->smcbname,op_name,co,NULL) )
                                                     LEAVESEQ
  op_type = FT_Function;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsGlobalVariable - 


\return fttype -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGlobalVariable"

FunctionTypes ACPathElement :: IsGlobalVariable ( )
{

  if ( acc_path->IsGlobalVariable(op_name) )
    op_type = FT_Global;
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsLocalVariable - 


\return fttype -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalVariable"

FunctionTypes ACPathElement :: IsLocalVariable ( )
{

  if ( acc_path->IsLocalVariable(op_name) )
    op_type = FT_Variable;
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsOperation - 


\return fttype -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOperation"

FunctionTypes ACPathElement :: IsOperation ( )
{

BEGINSEQ
  if ( !gvtsicmp(op_name,"select",0) ||
       !gvtsicmp(op_name,"define",0)    )
    op_code = ST_set_select;
  if ( !gvtsicmp(op_name,"having",0) ||
       !gvtsicmp(op_name,"where",0)    )
    op_code = ST_set_where;
  if ( !gvtsicmp(op_name,"group",0) ||
       !gvtsicmp(op_name,"group_by",0)    )
    op_code = ST_set_group_by;
  if ( !gvtsicmp(op_name,"order",0) ||
       !gvtsicmp(op_name,"order_by",0)    )
    op_code = ST_set_order_by;
  if ( !gvtsicmp(op_name,"minus",0) )
    op_code = ST_set_minus;
  if ( !gvtsicmp(op_name,"intersect",0) )
    op_code = ST_set_intersect;
  if ( !gvtsicmp(op_name,"union",0) )
    op_code = ST_set_union;
  if ( !gvtsicmp(op_name,"join",0) )
    op_code = ST_set_join;
  if ( !gvtsicmp(op_name,"distinct",0) )
    op_code = ST_set_distinct;
  if ( !gvtsicmp(op_name,"to_file",0)     ||
       !gvtsicmp(op_name,"ToFile",0)        )
    op_code = ST_file_output;
  if ( !gvtsicmp(op_name,"to_database",0) ||
       !gvtsicmp(op_name,"ToDatabase",0)    )
    op_code = ST_db_output;
  
  if ( op_code == ST_undefined )                     LEAVESEQ
  op_type = FT_Operation;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsParameter - 


\return fttype -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsParameter"

FunctionTypes ACPathElement :: IsParameter ( )
{

  if ( acc_path->IsParameter(op_name) )
    op_type = FT_Parameter;
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsProperty - 


\return fttype -

\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsProperty"

FunctionTypes ACPathElement :: IsProperty (smcb *smcbptr )
{
  int32          offset = 0;
BEGINSEQ
  if ( !smcbptr->SearchField(op_name,&offset) )     LEAVESEQ
    
  op_type = FT_Property;
ENDSEQ
  return(op_type);
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

logical ACPathElement :: LocateKey (char *skey, logical exact, logical chknode )
{
  logical           term = NO;
BEGINSEQ
  if ( operand.LocateKey(skey,exact) )               ERROR
  
  if ( operand.GetNode() )
    nodecur = operand.GetNode()->get_nodecur();

RECOVER
  nodecur = AUTO;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical ACPathElement :: Lock ( )
{

  return( operand.Lock() );

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

logical ACPathElement :: LockSet (logical chknode )
{

  return( operand.LockSet() );

}

/******************************************************************************/
/**
\brief  Next - 


\return term - Termination code

\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical ACPathElement :: Next (int32 count )
{
  int32                   indx0    = 0;
  int32                   rindx0   = 0;
  int32                   position = 0;
  logical                 term     = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( meta_operation && nodenode )
  {
    term = Pnodenode->Next(position);                   LEAVESEQ
  }
  
  if ( nodecur == AUTO )
  {
    if ( Pnodenode )
    {
      if ( NextParent() )                            ERROR
    }
    if ( !stscfil() )
      if ( InitializeOperand() )                     ERROR
  }
  
  rindx0 = nodecur+count;
  while ( rindx0 != nodecur )
  {
    if ( operand.GetRelative(rindx0) )
      nodecur = rindx0;
    else 
    {
      if ( (position = operand.GetRelativeIndex(YES)) != AUTO )
      {
        rindx0 -= (position+1);
        nodecur = AUTO;
        if ( last_node )
          path_index += (position+1);
      }
      if ( NextParent() )                           ERROR
      ResetNode(NO);
    }
  }
  
  SetupInstance();
RECOVER
  if ( this )
    ResetNode(NO);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NextParent - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextParent"

logical ACPathElement :: NextParent ( )
{
  ACPathElement          *parent = AccessParent();
  logical                 term = NO;
BEGINSEQ
  if ( !parent )
  {
//  wir müssen darauf achten, dass stsfill immer ordentlich gesetzt ist (auch, wenns schwer fällt
    if ( stscfil() )                                 ERROR
  }
  else
  {
    parent->set_path_index(path_index);
    if ( parent->Next(1) )                          ERROR
    start_index = path_index;
    stop_index  = AUTO;
    path_objid  = parent->GetID(AUTO).get_ebsnum();
  }  
  
  if ( InitializeOperands() )                       ERROR


RECOVER
  ResetNode(NO); // ev. ist op_curri = AUTO zuviel ?
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  field_def -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACPathElement :: Open (DBFieldDef *field_def )
{
  logical                 term = NO;
BEGINSEQ
  if ( !field_def && !operand.GetNode() )        ERROR
  
  if ( !nodeinst && operand.GetNode() )
    operand.GetNode()->Check(YES,NO);
  
  if ( !field_def ) 
    field_def = operand.GetFieldDef();
    
  if ( !is_opened && !stscerr() && op_type != FT_error)
  {
    if ( !bnode::Open(object_ref,nodenode,field_def,NULL,nodeacc) )
    {
      is_opened = YES;
      if ( operand.IsCollection() )
      {
        is_collection = YES;
        SetOrder(NULL,UNDEF,NULL);
      }
      if ( operand.IsMemo() )
        is_memo = YES;
    }
    else
    {
      stsserr();                                     ERROR
    }
  }
  
  SetupInstance();
  
  variable_type = operand.IsVariableType();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenParmHandle - 


\return term - Termination code

\param  prophdl -
\param  parm_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenParmHandle"

logical ACPathElement :: OpenParmHandle (PropertyHandle *prophdl, BNFData *parm_data )
{
  node          *co_node = acc_path->get_nodenode();
  BNFData       *operand;
  BNFExpData    *simple_op;
  char          *string;
  logical        term = NO;

BEGINSEQ
  if ( !(operand = ((BNFExpData *)parm_data)->GetOperand()) )
  {
    // parm = '*'
  }
  else
  {
    PropertyHandle  co_ph(co_node);
    DBObjectHandle  temp_obh(object_ref);
    simple_op = ((BNFExpData *)operand)->GetSimpleOp();
    
    if ( ((BNFExpData *)operand)->IsExpression() )
    { // ist nicht besonders schön, da jetzt noch einmal syntax-Analyse gemacht wird
      string = operand->GetStringValue("{","}");
      term = co_node ? prophdl->OpenAccessPath(co_ph,string,acc_path->get_variables(),
                                               acc_path->get_parameters(),YES)
                     : prophdl->OpenAccessPath(temp_obh,string,acc_path->get_variables(),
                                               acc_path->get_parameters(),PI_Read);
    }
    if ( simple_op->IsA("std_constant") )
    {
      if ( string = simple_op->GetStringConstant() )
        term = prophdl->Open(string);
      else
      {
        term = prophdl->Open(0.0);
        *prophdl = simple_op->GetStringValue(NULL,NULL);
      }
    }
    if ( simple_op->IsA("access_path") )
    {
      term = co_node ? prophdl->OpenAccessPath(co_ph,simple_op,acc_path->get_variables(),
                                               acc_path->get_parameters(),YES)
                     : prophdl->OpenAccessPath(temp_obh,simple_op,acc_path->get_variables(),
                                               acc_path->get_parameters(),PI_Read);
    }
    if ( term )                                      ERROR
  }
// es fehlt noch die Übernahme von Prop_spec wie bei "xx(10):name"

RECOVER
  prophdl->Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Prev - 


\return term - Termination code

\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Prev"

logical ACPathElement :: Prev (int32 count )
{
  int32                   indx0 = 0;
  int32                   rindx0 = 0;
  logical                 term  = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( meta_operation && nodenode )
  {
    term = Pnodenode->Prev(count);                   LEAVESEQ
  }
  
  if ( last_node )
    path_index = acc_path->get_nodecur();
  
  if ( nodecur == AUTO )
  {
    if ( Pnodenode )
    {
      if ( PrevParent() )                            ERROR
    }
    if ( !stscfil() )
      if ( InitializeOperand() )                     ERROR
  }
  
  rindx0 = nodecur+1;
  while ( rindx0 <= count )
  {
    count -= rindx0;
    ResetNode(NO);
    if ( PrevParent() )                              ERROR
    if ( (rindx0 = operand.GetRelativeCount()) < 0 ) SDBERR(99)
  }
    
  nodecur = (rindx0-1) - count;
  if ( !operand.GetRelative(nodecur) )             SDBERR(99)
  
  SetupInstance();
RECOVER
  if ( this )
    ResetNode(NO);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PrevParent - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrevParent"

logical ACPathElement :: PrevParent ( )
{
  ACPathElement          *parent = AccessParent();
  logical                 term = NO;
BEGINSEQ
  if ( !parent )
  {
//  wir müssen darauf achten, dass stsfill immer ordentlich gesetzt ist (auch, wenns schwer fällt
    if ( stscfil() )                               ERROR
  }
  else
  {
    parent->set_path_index(path_index);
    if ( parent->Prev(1) )                         ERROR
    stop_index  = path_index;
    start_index = AUTO;
    path_objid  = parent->GetID(AUTO).get_ebsnum();
  }  
    
  if ( InitializeOperands() )                      ERROR
RECOVER
  ResetNode(NO); // ev. ist op_curri = AUTO zuviel ?
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ACPathElement :: Reset ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( operand.Reset() )                             ERROR

  SetupInstance();
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical ACPathElement :: ResetNode (logical reset_all )
{

  nodecur  = AUTO;
  stsrfil();

  return(NO);
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

logical ACPathElement :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
// das müssen wir so machen, damit ToTop alle nodes im Path 
// zurücksetzt. Das Save wird nicht von bnode::Switch aufgerufen,
// da es überladen ist!
  term = operand.Save(overwrite,switchopt);
  if ( switchopt )
    ResetNode(NO);
  
  if ( nodenode && switchopt )
    if ( nodenode->Save(switchopt,overwrite,chknode) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetContextVariables - 


\return term - Termination code

\param  context_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContextVariables"

logical ACPathElement :: SetContextVariables (char *context_string )
{

  return( operand.SetContextVariables(context_string) );

}

/******************************************************************************/
/**
\brief  SetKey - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief


\param  kcbptr -
\param  keyptr -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical ACPathElement :: SetKey (kcb *kcbptr, char *keyptr, void *instptr )
{
  node           *nodeptr;
  return( (nodeptr = operand.GetNode()) ? 
          nodeptr->SetKey(kcbptr,keyptr,instptr) : NULL);


}

/******************************************************************************/
/**
\brief NODEKX


\param  keyptr -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical ACPathElement :: SetKey (char *keyptr, void *instptr )
{

  return( operand.SetKey(keyptr,instptr) );

}

/******************************************************************************/
/**
\brief  SetLast - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLast"

void ACPathElement :: SetLast ( )
{

  last_node = YES;

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

logical ACPathElement :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  smcb                   *smcbptr;
  char                    string[ID_SIZE];
  int32                   current;
  logical                 term = NO;
BEGINSEQ
  if ( !operand.IsValid() )                          ERROR
    
  if ( !strnames )  
    if ( !(strnames = order) )                       LEAVESEQ
      
  if ( !(smcbptr = operand.GetSortKeySMCB()) )       LEAVESEQ
  if ( !memcmp(gvtxstb(string,strnames,ID_SIZE),
               smcbptr->smcbname,ID_SIZE)        )   LEAVESEQ

  current = operand.GetCurrentIndex();

  if ( term = operand.SetOrder(strnames,attrtype,attrstr) )
    if ( operand.GetCurrentIndex() != current )
      operand.Get(current);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetSortKey - 


\return term - Termination code

\param  keyptr -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSortKey"

logical ACPathElement :: SetSortKey (char *keyptr, void *instptr )
{

  return( operand.SetSortKey(keyptr,instptr) );

}

/******************************************************************************/
/**
\brief  Setup

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical ACPathElement :: Setup ( )
{
  ACPathElement          *parent_element = NULL; 
  logical                 term = NO;
  // x().y sagt, dass y keine Mengen-Expression ist (nur für Expression)
  // das kann weg, wenn wir die Metainformation woanders herbekommen
//  if ( operation && Pnodenode && !Pnodenode->get_parameters() ) 
//    set_operation = YES;
  
  Check(YES,NO);

  return(term);
}

/******************************************************************************/
/**
\brief  SetupInstance - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInstance"

void ACPathElement :: SetupInstance ( )
{
  node         *nodeptr = operand.GetNode();
  int32         oid     = 0;
BEGINSEQ
  if ( !nodeptr )                                   LEAVESEQ
    
  if ( !nodeptr->IsSelected() && nodeptr->get_nodecur() != AUTO )
    nodeptr->Get(AUTO);
    
  nodewrit = NO;
  if ( nodeptr->get_nodeinst() )
  {
    node::SetCurrentInti(nodeptr->get_nodeinst());
    if ( nodeacc != PI_Read )
      nodewrit = nodeptr->IsWrite();
    nodeinst->SetObjectID(objid = Bnodeptr->get_objid());
    if ( nodenode && ((oid = nodenode->GetID(AUTO).get_ebsnum()) != path_objid) )
      path_objid = UNDEF;
  }
  else
    node::SetArea(operand.GetArea());
    
  if ( (nodecur = operand.GetCurrentIndex()) != AUTO )
    absolute_index = (relative_index = operand.GetRelativeIndex(YES)) != AUTO 
                     ? nodecur : AUTO;

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetupPathIndex - 


\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupPathIndex"

logical ACPathElement :: SetupPathIndex (int32 indx0 )
{
  ACPathElement          *parent = AccessParent();
  logical                 term = NO;
BEGINSEQ
  if ( !parent )                                     LEAVESEQ
  if ( last_node && nodecur != AUTO )                LEAVESEQ

  if ( path_objid != parent->GetID(AUTO).get_ebsnum() )
  {
    path_objid  = UNDEF;
    start_index = AUTO;
    stop_index  = AUTO;
    nodecur     = AUTO;
    parent->SetupPathIndex(indx0); 
    path_index = parent->get_start_index();          
    LEAVESEQ
  }
  
  if ( start_index != AUTO )
  {
    if ( start_index < indx0 )
    {
      nodecur = start_index;
    }
    else
    {
      parent->SetupPathIndex(indx0); 
      path_index = parent->get_start_index();
    }
    nodecur = start_index;
  }
  else
  {
    if ( stop_index > indx0 )
    {
      nodecur = stop_index;
    }
    else
    {
      parent->SetupPathIndex(indx0); 
      path_index = parent->get_stop_index();
    }
    nodecur = stop_index;
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Switch - 


\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Switch"

logical ACPathElement :: Switch (int32 indx0 )
{
  logical                 term = NO;
BEGINSEQ
  if ( !operand.get_nodeptr() )                      LEAVESEQ
  
  operand.get_nodeptr()->Switch(indx0);
  
//  if ( nodenode )
//    nodenode->Switch(AUTO);
ENDSEQ
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

logical ACPathElement :: Unlock ( )
{

  return( operand.Unlock() );

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

logical ACPathElement :: UnlockSet (logical extlock, logical chknode )
{

  return( operand.UnlockSet() );

}

/******************************************************************************/
/**
\brief  UpdateSelectionValue - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateSelectionValue"

logical ACPathElement :: UpdateSelectionValue ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !operand.GetNode() )                        LEAVESEQ
    
  if ( var_selection )
    operand.GetNode()->SetPathExpression(selection.GetString(),'(');

  if ( Pnodenode )
    Pnodenode->UpdateSelectionValue();
ENDSEQ
  return(term);
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

node *ACPathElement :: ValidateNode (logical crt_opt )
{
  node            *old_node = operand.GetNode();
  node            *new_node = this;

BEGINSEQ
  if ( !old_node )                                   LEAVESEQ

  operand.ValidateNode();
  new_node = operand.GetNode();
  
  if ( new_node != old_node )
  {
    Close();
    Open(NULL);
  }

  new_node = this;
ENDSEQ
  return(new_node);
}

/******************************************************************************/
/**
\brief  set_bnftop - 



\param  bnf_data -
\param  string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_bnftop"

void ACPathElement :: set_bnftop (BNFData *bnf_data, char *string )
{

  bnf_top_string = string;
  bnf_top        = bnf_data;

}

/******************************************************************************/
/**
\brief  set_order - 



\param  string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_order"

void ACPathElement :: set_order (char *string )
{

  if ( order )
    free(order);
  order = NULL;
    
  if ( string )
    order = strdup(string);


}

/******************************************************************************/
/**
\brief  set_path_index - 



\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_path_index"

void ACPathElement :: set_path_index (int32 indx0 )
{

  path_index = indx0;

}

/******************************************************************************/
/**
\brief  set_set_operation - 



\param  set_op_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_set_operation"

void ACPathElement :: set_set_operation (logical set_op_opt )
{

  set_operation = set_op_opt;

}

/******************************************************************************/
/**
\brief  ~ACPathElement - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACPathElement"

                        ACPathElement :: ~ACPathElement ( )
{

  nodeinst  = NULL;
  nodefield = NULL;
  
  set_order(NULL);
  
  if ( parameters )
    delete parameters;
  parameters = NULL;

  delete operation;
  operation = NULL;

  delete bnf_top;
  bnf_top     = NULL;
  bnf_operand = NULL;
  bnf_parm    = NULL;
  
  if ( bnf_top_string )
  {
    free(bnf_top_string);
    bnf_top_string = NULL;
  }



}


