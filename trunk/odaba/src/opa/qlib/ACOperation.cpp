/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACOperation

\brief    Operation nodes
          Operation  nodes are nodes that derive instances from a calling object
          node  (nodenode). An  operation node  may have multiple sources, which
          are  not  necessarily  identical  with  the  calling object. When a an
          operation  node may create more than  one instance per instance in the
          calling object, it is a "multiple children node".
          Multiple  children  sources  are  defined  static  field  definitions 
          (fmcbstat  = YES). Multiple children sources form a sub-node hierarchy
          when being defined as transient (fmcbtrans = YES).
          The  field  definition  contains  the source definition in the sources
          field.  The  field  name  may  differ  from the source name when being
          defined as:
          from(p=Person,c=Company).select(p.name, c.name)
          where  p and c are the fieldnames for further references. When no name
          has  been defined the  source expression is  used as name, i.e. a name
          should  always be defined,  when the source  is not simply a name. For
          field   deriviations,   operand   nodes   are   created performing the
          operation.

\date     $Date: 2006/08/30 18:21:05,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOperation"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sACOperand.hpp>
#include  <sBNFData.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sFieldSource.hpp>
#include  <sOPBase.hpp>
#include  <sOperEnvironment.hpp>
#include  <sPropertyHandle.hpp>
#include  <sinti.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <ssinti.hpp>
#include  <ssmcb.hpp>
#include  <sACOperation.hpp>


/******************************************************************************/
/**
\brief  ACOperation - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  structdef - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOperation"

     ACOperation :: ACOperation (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv )
                     : ACNode (),
  has_references(NO),
  temp_struct(NO),
  bnf_owner(NO),
  oper_env(operenv),
  oper_bnf(NULL),
  multiple_children(NO),
  struct_def(NULL),
  created(NO),
  auto_create(NO)
{

  Open(obhandle,nodeptr,structdef);
  nodetype = NT_ACOperation;
  
  if ( structdef )
  {
    struct_def = structdef;
    InitFieldDef(struct_def->smcbname);
  }

}

/******************************************************************************/
/**
\brief  i04 - 



\param  opernode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOperation"

     ACOperation :: ACOperation (ACOperation &opernode_ref )
                     : ACNode (opernode_ref),
  has_references(NO),
  multiple_children(NO),
  temp_struct(NO),
  bnf_owner(NO),
  oper_env(opernode_ref.get_oper_env()),
  oper_bnf(opernode_ref.get_oper_bnf()),
  struct_def(opernode_ref.get_struct_def()),
  created(NO),
  auto_create(opernode_ref.get_auto_create())
{

  nodetype = NT_ACOperation;

  InitFieldDef(opernode_ref.get_nodefield()->fmcbname);


}

/******************************************************************************/
/**
\brief  Add - 



\return instptr - 

\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACOperation :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  int16      talevel = 0;
  void      *instptr = NULL;
BEGINSEQ
  if ( Check(YES) )                                   ERROR
  if ( CheckAccess(PI_Write) )                        ERROR
  if ( Switch(AUTO) )	                              ERROR

  nodeinst->Save(NO,NO,NO);                           // write data back to origin
  if ( idkey )
    skey = idkey;
  if ( !skey )
  {
    if ( !initinst )                               SDBERR(81)
    if ( !(skey = ACNode::ExtractKey(NULL,initinst,NO)) )  SDBERR(99)
  }
  else
    id_key->kcbkpt(nodeinst->get_iselarea(),skey);
  
  if ( multiple_children )
  {
    talevel = StartTA();
    nodeinst->Initialize(initinst);  // inti erzeugt Init-Event sowohl füe base als auch für attr!
  
    if ( !LocateKey(skey,YES,NO) )                     SDBERR(64)
    if ( nodeinst->Add(global_add) )                   ERROR
  }
  else if ( nodenode )
    nodenode->Add(lindx0,skey,idkey,initinst,global_add);

  instptr = SetupInstance();
RECOVER
  Cancel();
  instptr = NULL;
ENDSEQ
  if ( talevel )
    if ( StopTA(instptr == NULL) )
      instptr = NULL;
  return(instptr);
}

/******************************************************************************/
/**
\brief  CanUpdateCollection - 



\return cond - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanUpdateCollection"

logical ACOperation :: CanUpdateCollection (logical chknode )
{
  logical           cond = YES;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( multiple_children && noderefp )
  {
    if ( !ACNode::CanUpdateCollection() )            ERROR
  }
  else if ( nodenode )  
    if ( nodenode->CanUpdateCollection() )           ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical ACOperation :: Cancel (logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode )
  {
    if ( Check(NO,NO) )                              ERROR
    if ( nodenode )
      term = nodenode->Cancel(NO);  // nur für echtes Cancel, nicht, wenn expression nicht erfüllt
  }
  nodecur = AUTO;
  if ( nodeinst )
    nodeinst->Cancel();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeBuffer - 



\return bufnum - 

\param  bufnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeBuffer"

int16 ACOperation :: ChangeBuffer (int16 bufnum )
{

  if ( has_references )
    bufnum = 1;
  else
    bufnum = ACNode::ChangeBuffer(bufnum);
  return(bufnum);
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

PIACC ACOperation :: ChangeMode (PIACC accopt, char chkopt )
{
  int32         curri = nodecur;
  PIACC         oldmode = nodeacc;
BEGINSEQ
  if ( nodecur != AUTO )
    Save(NO,YES,NO);
  
  if ( nodenode->ChangeMode(accopt) == PI_undefined )       ERROR
  if ( (oldmode = ACNode::ChangeMode(accopt,NO)) == PI_undefined )
                                                     ERROR
  if ( nodenode && nodenode->Exist() )
    nodecur = curri;
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

logical ACOperation :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
BEGINSEQ
  if ( stscusr3() )                                  LEAVESEQ
  
  if ( autoini )
  {
    stssusr3();
    term = Init(NULL);
    stsrusr3();
  }
  
//  if ( ParentChanged() )
//    Execute();
    
  if ( ACNode::Check(autoini,acccheck) )              ERROR
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

logical ACOperation :: Close ( )
{
  DBStructDef               *dbstruct;
BEGINSEQ
  if ( nodeidnt != NODE_ID )                         LEAVESEQ
  Save(YES,NO,NO);
  
  if ( temp_struct && !origin && nodefield && (dbstruct = GetStructDef()) )
  {
    GetDictionary()->RemoveStructDef(dbstruct->GetTypeKey());
    delete dbstruct;
    nodefield->fmcbsmcb = NULL;
  }
  
  ACNode::Close();
  delete nodefield;
  nodefield = NULL;

  nodenode = NULL;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  CreateFields - 



\return fieldlist - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFields"

DBFieldList *ACOperation :: CreateFields ( )
{
  Dictionary             *dictionary  = GetDictionary();
  DBFieldList            *dbfieldlist = NULL;
  DBFieldDef             *dbflddef;
  BNFData                *parameter;
  BNFData                *bdata;
  BNFData                *bnf_data    = oper_bnf;
  int32                   curindx     = 0;
BEGINSEQ
// Select, Product
  if ( bnf_data->IsA("operand_list") )
    bnf_data = bnf_data->GetElement(1);
  if ( !bnf_data->IsA("parm_list") )                 SDBERR(777)
  bnf_data = bnf_data->GetSymbol("parm_list");
  
  if ( !(dbfieldlist = new DBFieldList(bnf_data->GetElementCount())))
                                                     SDBERR(95)
                                                     SDBCERR
  parameter  = bnf_data->GetElement(curindx++);  
  while ( parameter )
  {
    dbflddef = dbfieldlist->GetEntry(curindx);
    if ( dbflddef->Fill(struct_def,parameter,dictionary) )
                                                     ERROR
    parameter = (bdata = bnf_data->GetElement(curindx++)) 
                ? bdata->GetElement(1)
                : NULL;
  } 

  dbfieldlist->srtsetc(curindx-1);

RECOVER
  dbfieldlist = NULL;
ENDSEQ
  return(dbfieldlist);
}

/******************************************************************************/
/**
\brief  CreateInti - 



\return intiptr - 

\param  nodeptr - 
\param  strdef_ptr - Internal data structure definition
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *ACOperation :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti                   *intiptr = NULL;
BEGINSEQ
  if ( !(intiptr = new sinti(this,
                             strdef_ptr,instptr,init_nodes,
                             oper_env)) ) 
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  delete intiptr;
  intiptr = NULL;
ENDSEQ
  return(intiptr);
}

/******************************************************************************/
/**
\brief  CreateNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  op_base - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *ACOperation :: CreateNode (OPBase *op_base )
{
  node              *nodeptr;
  ACOperand         *oprd_node = NULL;
BEGINSEQ
  nodeptr = oprd_node = new ACOperand(op_base);
  if ( oprd_node->Open(this) )                      ERROR
  
  op_base->GetValue()->RegisterNode(nodeptr);
  Bnodeinst->get_node_base().AddTail(nodeptr);


RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *ACOperation :: CreateNode (DBFieldDef *fielddef )
{
  OPBase                 *op_node = NULL;
  FieldSource            *srce_def;
  char                   *expr_str;
  node                   *parent  = NULL;
  DBObjectHandle          obh(object_ref);
  PropertyHandle          pph;
  PropertyHandle          ph;
  node                   *nodeptr = NULL;
  logical                 stat;
  logical                 base;
  logical                 trans;
BEGINSEQ
  if ( !(srce_def = fielddef->GetSource(0)) ||
       !(expr_str = srce_def->GetString())     )     SDBERR(99)
  
  if ( fielddef->fmcbtrans )                         // Join 
    parent = Bnodeinst->get_node_base().GetTail();
  if ( !parent ) 
    parent = nodenode;
    
  if ( parent )
  {
    pph.RegisterNode(parent);
    if ( ph.Open(pph,expr_str) )                     ERROR
  }
  else
    if ( ph.Open(obh,expr_str,nodeacc) )             ERROR
  
  if ( !(nodeptr = ph.get_nodeptr()) )               ERROR
  Bnodeinst->get_node_base().AddTail(nodeptr);

  stat  = fielddef->get_static();
  trans = fielddef->fmcbtrans;
  base  = fielddef->fmcbbstr;
  *fielddef = *Bnodeptr->get_nodefield();
  fielddef->fmcbrlev = RL_direct;
  fielddef->set_static_field(stat);
  fielddef->fmcbtrans = trans;
  fielddef->fmcbbstr  = base;
  
  multiple_children = YES;

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateStruct - 



\return dbstrdef - Structure definition

\param  fldnames - Property name
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStruct"

DBStructDef *ACOperation :: CreateStruct (char *fldnames, char *strnames_w )
{
  DBFieldList            *dbfieldlist = NULL;
  TypeKey                 tkey(strnames_w,SYS_NSID);
  int32                   curindex    = 0;
  char                    string[ID_SIZE+1];
  DBFieldDef             *dbflddef;
BEGINSEQ
  if ( !strnames_w || *strnames_w <= ' ' || 
       !(struct_def = GetDictionary()->GetStructDef(tkey)) )
  {                     
    if ( !strnames_w || *strnames_w <= ' ' )
    {
      *string = 0;
      strnames_w = GetDictionary()->GetTempName(string);                              
    }
    if ( !(dbfieldlist = CreateFields()) )           ERROR
    while ( (dbflddef = dbfieldlist->GetEntry(++curindex)) && dbflddef->fmcbrlev != R_REFR ) ;
    curindex--;

// das ist noch unklar, vielleicht lieber ViewStructDecl, vielleicht lieber ST_USER
    if ( !(struct_def = GetDictionary()->ProvideStructDcl(tkey,
                                        ERIC,UNDEF,UNDEF,TYP_Structure,ST_VIEW,  
                                        UNDEF,UNDEF,UNDEF,UNDEF,NULL,NO,CUR_VERSION)) )
                                                     ERROR
    temp_struct = YES;
    struct_def->smcbfmcl = dbfieldlist;
    dbfieldlist = NULL;
  }
  
  InitFieldDef(fldnames);

RECOVER
  delete dbfieldlist;
  dbfieldlist = NULL;
  delete struct_def;
  struct_def = NULL;
ENDSEQ
  return(struct_def);
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

logical ACOperation :: Delete (int32 indx0, logical chknode, logical del_dep, logical del_inst )
{
  logical        term = NO;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
    
  if ( indx0 != AUTO )
    if ( !Get(indx0) )                               ERROR

  if ( Delete(del_dep) )                             ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACOperation :: Delete (logical del_dep )
{
  logical        term = NO;
BEGINSEQ
  if ( multiple_children )
  {
    if ( noderefp )
    {
      if ( ACNode::Delete(AUTO,del_dep) )            ERROR
    }
    else
      nodeinst->Delete(NULL,NO,del_dep);  
  }
  else if ( nodenode )
    if ( nodenode->Delete(AUTO,del_dep) )            ERROR

  ResetInstance();
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

logical ACOperation :: Delete (char *skey, logical chknode )
{
  logical                 term;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
    
  if ( !Get(skey) )                                  ERROR

  if ( Delete(NO) )                             ERROR

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

logical ACOperation :: ExecPropCtxFunc (char *fnames, char *w_parms )
{
  logical    term = NO;
BEGINSEQ
  if ( !CheckPropCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecPropCtxFunc(fnames,w_parms) )    ERROR
  }
  else if ( nodenode )
  {
    if ( nodenode->ExecPropCtxFunc(fnames,w_parms) ) ERROR
    nstring = nodenode->get_nstring();
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

logical ACOperation :: ExecStrCtxFunc (char *fnames, char *w_parms )
{
  logical   term = NO;
BEGINSEQ
  if ( !CheckStrCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecStrCtxFunc(fnames,w_parms) )    ERROR
  }
  else if ( nodenode )
  {
    if ( nodenode->ExecStrCtxFunc(fnames,w_parms) ) ERROR
    nstring = nodenode->get_nstring();
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
\brief  NODEKE - 



\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ACOperation :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{
   char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractKey(keyptr,instptr,chknode) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = nodenode->ExtractKey(keyptr,NULL);

RECOVER
  kptr = NULL;
ENDSEQ
  return(kptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  keyptr - 
\param  kcbptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ACOperation :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{
    char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractKey(keyptr,kcbptr,instptr) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = nodenode->ExtractKey(keyptr,NULL);

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

char *ACOperation :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{
  char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractSortKey(keyptr,instptr,chknode) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = nodenode->ExtractSortKey(keyptr,NULL);

RECOVER
  kptr = NULL;
ENDSEQ
  return(kptr);

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

char *ACOperation :: FirstKey (logical chknode )
{
  char                   *keyptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  Save(AUTO,NO,NO);
  
  if ( multiple_children )
  {
    if ( nodeinst->Get(0) )                            ERROR
    nodecur = nodeinst->get_inst_index();

    keyptr = ACNode::ExtractKey(NULL,NULL);  
  }
  else if ( nodenode )  
  {
    keyptr = nodenode->FirstKey(chknode);
  }

  SetupInstance();
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
\brief  NODEIG - 



\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACOperation :: Get (int32 indx0, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                        ERROR
  
  if ( indx0 == AUTO )
    indx0 = nodecur;
  if ( indx0 == AUTO )
    indx0 = FIRST_INSTANCE;
    
  if ( multiple_children )
  {
    switch ( indx0 )
    {
      case FIRST_INSTANCE : 
      case LAST_INSTANCE  : if ( !nodeinst->Get(indx0) )
                                                     ERROR
                            break;
      default             : if ( nodeinst->Position(indx0-nodecur) ) 
                                                     ERROR
    }

    if ( nodeinst->Get(nodeinst->get_inst_index()) ) ERROR
  }
  else if ( nodenode )
  {
    nodenode->Get(indx0,chknode);
    nodeinst->Get(0);                 // GetData()
  }  

  if ( CheckExpression() )                           ERROR
  instptr = SetupInstance();

RECOVER
  Cancel();
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

void *ACOperation :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
  int32                   inst_index;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  
  inst_index = nodeinst->get_inst_index();
  
  if ( multiple_children )
  {
    if ( LocateKey(skey,YES,NO) )                    ERROR
    if ( nodeinst->Get(inst_index) )                 ERROR
  }
  else if ( nodenode )
  {
    nodenode->Get(skey,chknode);
    nodeinst->Get(0);
  }  
  
  if ( CheckExpression() )                           ERROR
  instptr = SetupInstance();

RECOVER
  Cancel();
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetCount - 



\return count - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACOperation :: GetCount (logical chknode )
{
  int32          count = ERIC;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  
  if ( nodenode && !nodenode->IsPositioned() )       ERROR
    
  count = multiple_children ? nodeinst->GetCount() : 1;

RECOVER
  count = ERIC;
ENDSEQ
  return(count);
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

EB_Number ACOperation :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number         entnr;
  if ( multiple_children )
  {
    if ( nodeinst )
      entnr = nodeinst->GetID();
  }
  else if ( nodenode )
    entnr = nodenode->GetID(indx0);

  return(entnr);
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

EB_Number ACOperation :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

  return( nodenode->GetID(keyptr) );


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

void *ACOperation :: GetInitInstance (logical set_init )
{
  void             *instptr = NULL;
BEGINSEQ
  if  ( nodenode ) 
    if ( !(instptr = nodenode->GetInitInstance(set_init)) )
                                                     ERROR
  Initialize_intern(NULL);
  nodeinst->Get(nodeinst->get_inst_index());    

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetInstance - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

void *ACOperation :: GetInstance ( )
{

  return( this && nodeinst && nodecur != AUTO 
          ? nodeinst->get_iselarea() : GetArea() );

}

/******************************************************************************/
/**
\brief  GetKeyLength - 



\return klen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 ACOperation :: GetKeyLength ( )
{
  int16                   klen = 0;
  return( klen = bnode::GetKeyLength() 
          ? klen 
          : nodenode ? nodenode->GetKeyLength() : NULL );


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

smcb *ACOperation :: GetKeySMCB (char *key_name_w )
{
  smcb                   *smcbptr = NULL;
  return( smcbptr = bnode::GetKeySMCB(key_name_w) 
          ? smcbptr 
          : nodenode ? nodenode->GetKeySMCB(key_name_w) : NULL);


}

/******************************************************************************/
/**
\brief  GetMode - 



\return accopt - Access mode

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMode"

PIACC ACOperation :: GetMode (logical chknode )
{

  return ( multiple_children 
           ? bnode::GetMode(chknode)
           : nodenode ? nodenode->GetMode() : PI_undefined );

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

int16 ACOperation :: GetSortKeyLength (logical chknode )
{
  int16                   klen = 0;
  return( klen = bnode::GetSortKeyLength() 
          ? klen 
          : nodenode ? nodenode->GetSortKeyLength() : NULL);


}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 



\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *ACOperation :: GetSortKeySMCB ( )
{
  smcb                   *smcbptr = NULL;
  return( smcbptr = bnode::GetSortKeySMCB() 
          ? smcbptr 
          : nodenode ? nodenode->GetSortKeySMCB() : NULL);


}

/******************************************************************************/
/**
\brief  Init - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical ACOperation :: Init (void *instptr )
{
  CTX_Base               *highctx;
  logical                 term = NO;
BEGINSEQ
// we can create an sinti only, when the source is initialized
  if ( nodeinst )                                    LEAVESEQ
    
  if ( nodenode )
    highctx = nodenode->get_nodeinst()->GetContext();
  else
    highctx = object_ref->get_ocontext();
  if ( bnode::Open(object_ref,nodenode,nodefield,highctx,nodeacc) )
                                                     ERROR
  if ( GetStructDef() )
    if ( InitInti(GetStructDef(),NULL,YES) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitFieldDef - 



\return term - Termination code

\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFieldDef"

logical ACOperation :: InitFieldDef (char *fldnames )
{
  int32                   intpos      = 0;
  int32                   extpos      = 0;
  int8                    max_aligned = 1;
  logical                 term = NO;
BEGINSEQ
  nodefield = new DBFieldDef(fldnames,struct_def->smcbname,struct_def->smcbnsid,
                              RL_reference,struct_def->GetInstLength(NO),UNDEF,UNDEF,struct_def,NULL,NO,NULL,NULL,NULL); 
  nodefield->set_resource(new DBResource(NULL));
  nodefield->SetupField(intpos,extpos,UNDEF,max_aligned);

//  if ( dbstrdef->CreateKeyDefs(NULL,dbstrdef->smcbidky) )   
//                                                     ERROR
//  if ( dbstrdef->SetupKeyDefs(GetSystemVersion()) )  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitOperandBNF - 



\return term - Termination code

\param  exprstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOperandBNF"

logical ACOperation :: InitOperandBNF (char *exprstr )
{
  Dictionary           *dictionary = object_ref->GetDictionary();
  char                 *symbol     = "parm_list";
  logical               term       = NO;
BEGINSEQ
  if ( *exprstr == '(' )
    symbol = "operand_list";
  
  if ( !(oper_bnf = dictionary->ParseExpression(exprstr,symbol,NULL)) )
                                                     ERROR
  bnf_owner = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical ACOperation :: IsPositioned ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( nodenode && !nodenode->IsPositioned() )       ERROR
                                                     
  if ( multiple_children && !nodeinst->IsPositioned() )
                                                     ERROR
  if ( nodecur == AUTO )                             ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsSelected - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical ACOperation :: IsSelected ( )
{

  return ( IsPositioned() );

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

logical ACOperation :: LocateKey (char *skey, logical exact, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  Save(AUTO,NO,NO);
  
  if ( multiple_children )
  {
    if ( nodeinst->LocateKey(skey,exact) )           ERROR
  }
  else if ( nodenode )  
  {
    if ( nodenode->LocateKey(skey,exact) )           ERROR
  }

  if ( CheckExpression() )                           ERROR
  SetupInstance();
RECOVER
  Cancel();
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

logical ACOperation :: Lock ( )
{
  logical                 term = NO;

  return(term);
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

logical ACOperation :: LockSet (logical chknode )
{
  logical                 term = NO;

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

void *ACOperation :: Modify (logical chknode )
{
  char                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
    
  stssmod();

  instptr = nodeinst->get_iselarea();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
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

char *ACOperation :: NextKey (char *skey, int16 switch_level )
{
  char                    *keyptr = NULL;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  
  if ( nodecur != AUTO && !skey )
  {
    if ( keyptr = FirstKey(NO) )                     LEAVESEQ
  }
  
  if ( multiple_children )
  {
    if ( skey )
    {
      Switch(AUTO);
      if ( LocateKey(skey,NO,NO) )                   ERROR
      if ( CompareKey(skey,ExtractKey(NULL,NULL),NO) ) LEAVESEQ
    }
    else 
    {
      Save(NO,NO,NO);
      if ( nodeinst->Position(1) )                   ERROR
    }
  
    if ( nodeinst->Position(1) )                     ERROR
  
    while ( CheckExpression() )         
      if ( nodeinst->Position(1) )                   ERROR
  
    if ( !(keyptr = ExtractKey(NULL,nodeinst->get_iselarea(),NO)) )
                                                     ERROR
  }
  else if ( nodenode )
    keyptr = nodenode->NextKey(skey,switch_level);

  SetupInstance();

RECOVER
  Cancel();
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Open - 




\param  obhandle - Database Object handle
\param  nodeptr - 
\param  structdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

void ACOperation :: Open (ACObject *obhandle, node *nodeptr, DBStructDef *structdef )
{

  ACNode::Open(obhandle ? obhandle : nodeptr->GetObjectHandle(),
               nodeptr ? nodeptr->GetNode() : NULL,
               NULL,NULL,
               nodeptr ? nodeptr->GetMode() : obhandle->GetAccess());
  
  nodetype = NT_ACOperation;
  
  if ( structdef )
  {
    struct_def = structdef;
    InitFieldDef(struct_def->smcbname);
  }

}

/******************************************************************************/
/**
\brief  Reset - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ACOperation :: Reset ( )
{
  int32                 inst_index = nodeinst->get_inst_index();
  logical               term = NO;
BEGINSEQ
  if ( multiple_children )
    term = nodeinst->ResetInstance();
  else if ( nodenode )
    term = nodenode->Reset();

  if ( term )                                        ERROR
  SetupInstance();

RECOVER
  term = YES;
ENDSEQ
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

logical ACOperation :: Save (logical switchopt, logical overwrite, logical chknode )
{
  int16    talevel = 0;
  logical  term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  talevel = StartTA();

  if ( multiple_children )
  {
    if ( nodeinst->Save(switchopt,overwrite,NO) )      ERROR
  }
  else if ( nodenode )
    if ( nodenode->Save(switchopt,overwrite,NO) )      ERROR
      
  if ( switchopt )
  {
    nodecur = AUTO;
    nodewrit = NO;
  }

RECOVER
  Cancel();
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  SetCO - 




\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCO"

void ACOperation :: SetCO (node *nodeptr )
{

  Close();

  if ( nodeptr )
  {
    nodenode = nodeptr->GetNode();
    object_ref = nodeptr->GetObjectHandle();  
  }
  Init(NULL);

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

logical ACOperation :: SetContextVariables (char *context_string )
{

  return( nodenode ? nodenode->SetContextVariables(context_string) : YES);

}

/******************************************************************************/
/**
\brief  SetKey - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  - 



\param  kcbptr - 
\param  keyptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical ACOperation :: SetKey (kcb *kcbptr, char *keyptr, void *instptr )
{

  return( multiple_children 
          ? ACNode::SetKey(kcbptr,keyptr,instptr)
          : nodenode ? nodenode->SetKey(kcbptr,keyptr,instptr)
                    : YES      );


}

/******************************************************************************/
/**
\brief  NODEKX - 



\param  keyptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical ACOperation :: SetKey (char *keyptr, void *instptr )
{
  logical        term = NO;
BEGINSEQ
  if ( multiple_children )
  {
    if ( !id_key )                                   ERROR
    SetKey(id_key,keyptr,instptr);    
  }
  else if ( nodenode )
    nodenode->SetKey(keyptr,instptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical ACOperation :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  logical    term = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR

  Save(AUTO,NO,NO);
//  if ( nodeinst->SetOrder(strnames,attrtype,attrstr) )
//                                                     ERROR

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

logical ACOperation :: SetSortKey (char *keyptr, void *instptr )
{

  return( multiple_children 
          ? ACNode::SetSortKey(keyptr,instptr)
          : nodenode ? nodenode->SetSortKey(keyptr,instptr)
                    : YES      );


}

/******************************************************************************/
/**
\brief  SetupInstance - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInstance"

void *ACOperation :: SetupInstance ( )
{
  void              *instptr = NULL;

  if ( multiple_children )
  {
    if ( nodeacc > PI_Read )
      nodewrit = YES;
    objid = Bnodeinst->get_objid();
    nodecur = nodeinst->get_inst_index();
  }
  else if ( nodenode )
  {
    nodewrit = Bnodenode->get_nodewrit();
    objid    = Bnodenode->get_objid();
    nodecur  = 0;
  }
  
  instptr = nodeinst->get_iselarea();
  

  return(instptr);
}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical ACOperation :: Unlock ( )
{
  logical                 term = NO;

  return(term);
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

logical ACOperation :: UnlockSet (logical extlock, logical chknode )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOperation - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOperation"

     ACOperation :: ~ACOperation ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

  if ( bnf_owner )
    delete oper_bnf;
  oper_bnf = NULL;

}


