/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACPath_old



\date     $Date: 2006/03/12 19:15:58,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACPath_old"

#include  <popa7.h>
#include  <sACPath_old.hpp>


/******************************************************************************/
/**
\brief  ACPath - 


-------------------------------------------------------------------------------
\brief i00


\param  dict_ptr - Dictionary handle
\param  obhandle - Database Object handle
\param  nodeptr -
\param  bnf_data -
\param  parm_list -
\param  var_list
\param  accmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

void ACPath_old :: ACPath (Dictionary *dict_ptr, ACObject *obhandle, node *nodeptr, BNFData *bnf_data, ParmList *parm_list, ParmList *var_list, PIACC accmode )
                     : LNode (obhandle,nodeptr,NULL,NULL,
       nodeptr ? nodeptr->GetMode() 
       : accmode 
         ? accmode 
         : obhandle ? obhandle->GetAccess():PI_Read),
  dictionary(dict_ptr),
  elements(),
  current_element(AUTO),
  expression(NULL),
  expression_bnf(NULL),
  parent_objid(0),
  parameters(parm_list),
  variables(var_list)
{

  Initialize(bnf_data);

}

/******************************************************************************/
/**
\brief i01


\param  lobhandle -
\param  dbextdef - Extent definition
\param  accmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

void ACPath_old :: ACPath (LACObject *lobhandle, DBExtend *dbextdef, PIACC accmode )
                     : LNode (lobhandle,NULL,dbextdef,NULL,accmode),
  dictionary(lobhandle->GetDictionary()),
  elements(),
  current_element(UNDEF),
  expression(NULL),
  expression_bnf(NULL),
  parent_objid(0),
  parameters(NULL),
  variables(NULL)
{

  Initialize(lobhandle);

}

/******************************************************************************/
/**
\brief i02


\param  acpathref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

void ACPath_old :: ACPath (ACPath &acpathref )
                     : LNode (acpathref),
  dictionary(acpathref.get_dictionary()),
  elements(),
  current_element(acpathref.get_current_element()),
  expression(NULL),
  expression_bnf(acpathref.get_expression_bnf()),
  parent_objid(0),
  parameters(acpathref.get_parameters()),
  variables(acpathref.get_variables())
{
  DLL(ACPathElement)  cursor(acpathref.get_elements());
  ACPathElement      *pelement;
  ACPathElement      *copy_element;

  is_opened = NO;
  
  if ( expression_bnf )
    Initialize(expression_bnf);            // is expression
  else if ( acpathref.get_nodenode() )     // is SDB_View field
    Initialize(acpathref.get_nodefield());
  else 
    Initialize(object_ref);                // is SDB_View extewnt



}

/******************************************************************************/
/**
\brief i03


\param  co_node -
\param  fielddef - Internal field defintion
\param  accmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACPath"

void ACPath_old :: ACPath (node *co_node, DBFieldDef *fielddef, PIACC accmode )
                     : LNode (co_node ? co_node->GetObjectHandle() : NULL,
       co_node,NULL,NULL,
       co_node ? co_node->GetMode() 
       : accmode),
  dictionary(co_node->GetDictionary()),
  elements(),
  current_element(UNDEF),
  expression(NULL),
  expression_bnf(NULL),
  parent_objid(0),
  parameters(NULL),
  variables(NULL)
{

  Initialize(fielddef);

}

/******************************************************************************/
/**
\brief  Add

\return instptr -
-------------------------------------------------------------------------------
\brief i0


\param  lindx0 -
\param  global_add -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACPath_old :: Add (int32 lindx0, logical global_add )
{
  ACPathElement *last_node = elements.GetTail();
  void          *instptr = NULL;

BEGINSEQ
  if ( !last_node->Add(lindx0,global_add) )          ERROR
  
  SetupInstance();
  if ( !(instptr = GetArea()) )                      ERROR
RECOVER
  ResetInstance();
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

void *ACPath_old :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  ACPathElement *last_node = GetAccessNode();
  void          *instptr = NULL;

BEGINSEQ
  if ( !last_node->Add(lindx0,skey,idkey,initinst,global_add) )
                                                     ERROR
  SetupInstance();
  if ( !(instptr = GetArea()) )                      ERROR
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

logical ACPath_old :: CanUpdateCollection (logical chknode )
{
  ACPathElement *last_node = GetAccessNode();

  return( last_node ? last_node->CanUpdateCollection(chknode) : NO);

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

logical ACPath_old :: Cancel (logical chknode )
{
  ACPathElement *last_node = GetAccessNode();
  logical        term = NO;
  Switch(AUTO);
  
  nodecur = AUTO;
  stsrfil();

  last_node->Cancel(NO);
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

PIACC ACPath_old :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC     oldmode = PI_undefined;
BEGINSEQ
  if ( chkopt && Check(NO,NO) )                      ERROR
  if ( chkopt && CheckAccess(accopt) )               ERROR
  
  if ( inti_buffer && accopt > PI_Read )             SDBERR(244)
       
  oldmode = nodeacc;
  nodeacc = accopt;
  
  if ( GetAccessNode()->ChangeMode(accopt) == PI_undefined )
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

logical ACPath_old :: Check (logical autoini, logical acccheck )
{
  ACPathElement *last_node = GetAccessNode();
  logical        term = NO;
BEGINSEQ
  if ( acccheck && !fldfmcb )
  {
    last_node->InitPath();
    Cancel();                  // stscini muss zurückgenommen werden
//    Save(YES,NO,NO);         // ist ein Cancel
  }
  
  if ( last_node && nodenode )
  {
    if ( parent_objid != Bnodenode->get_objid() )
    {
      Cancel();
      parent_objid = Bnodenode->get_objid();
      last_node->UpdateSelectionValue();
    }
  }
  
  if ( autoini )
  {
    if ( !is_opened )
      Open();
    if ( !last_node )                                ERROR
    if ( !(nodeinst = last_node->get_nodeinst()) )   LEAVESEQ
  }
  
  if ( LNode::Check(autoini,acccheck) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CompareKey - 


\return cmpval -

\param  skey1 -
\param  skey2 -
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareKey"

int8 ACPath_old :: CompareKey (char *skey1, char *skey2, logical chknode )
{
  smcb     *smcbptr;
  int       cmpval = ERIC;

BEGINSEQ
  if ( !(smcbptr = GetKeySMCB()) )                   SDBERR(71)

  cmpval = smcbptr->smcbfmcl->fmclicmp(smcbptr->smcbfmcl,skey1,skey2);

RECOVER

ENDSEQ
  return(cmpval);

}

/******************************************************************************/
/**
\brief  CompareSortKey - 


\return cmpval -

\param  skey1 -
\param  skey2 -
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareSortKey"

int8 ACPath_old :: CompareSortKey (char *skey1, char *skey2, logical chknode )
{
  smcb     *smcbptr;
  int       cmpval = ERIC;

BEGINSEQ
  if ( !(smcbptr = GetSortKeySMCB()) )           SDBERR(71)

  cmpval = smcbptr->smcbfmcl->fmclicmp(smcbptr->smcbfmcl,skey1,skey2);

RECOVER

ENDSEQ
  return(cmpval);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACPath_old :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACPath(*this) ) )             SDBERR(95)
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

logical ACPath_old :: Delete (int32 indx0, logical chknode, logical del_dep )
{
  ACPathElement *last_node = elements.GetTail();
  logical        term = NO;

BEGINSEQ
  if ( !last_node || last_node->Delete(indx0,chknode,del_dep) )
                                                     ERROR
  nodecur = AUTO;
  stsrfil();

  ResetInstance();

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

logical ACPath_old :: Delete (char *skey, logical chknode )
{
  ACPathElement *last_node = GetAccessNode();
  logical        term = NO;

BEGINSEQ
  if ( !last_node || last_node->Delete(skey,chknode) )
                                                     ERROR
  nodecur = AUTO;
  stsrfil();

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

logical ACPath_old :: ExecPropCtxFunc (char *fnames, char *w_parms )
{
  ACPathElement *last_node = GetAccessNode();
  logical        term = NO;
BEGINSEQ
  if ( !CheckPropCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecPropCtxFunc(fnames,w_parms) )    ERROR
  }
  else
  {
    if ( last_node->ExecPropCtxFunc(fnames,w_parms) )
                                                     ERROR
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

logical ACPath_old :: ExecStrCtxFunc (char *fnames, char *w_parms )
{
  ACPathElement *last_node = GetAccessNode();
  logical        term = NO;
BEGINSEQ
  if ( !CheckStrCtxFunc(fnames) )                        
  {  
    if ( bnode::ExecStrCtxFunc(fnames,w_parms) )    ERROR
  }
  else
  {
    if ( last_node->ExecStrCtxFunc(fnames,w_parms) )
                                                     ERROR
    nstring = last_node->get_nstring();
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

char *ACPath_old :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{
  ACPathElement *last_node = elements.GetTail();
  char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractKey(keyptr,instptr,chknode) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = last_node->ExtractKey(keyptr,instptr,chknode);

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

char *ACPath_old :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{
  ACPathElement *last_node = GetAccessNode();
  char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractKey(keyptr,kcbptr,instptr) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = last_node->ExtractKey(keyptr,kcbptr,NULL);

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

char *ACPath_old :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{
  ACPathElement *last_node = GetAccessNode();
  char          *kptr = NULL;
BEGINSEQ
  if ( kptr = bnode::ExtractSortKey(keyptr,instptr,chknode) ) 
                                                     LEAVESEQ
  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     SDBERR(99)
  kptr = last_node->ExtractSortKey(keyptr,NULL,chknode);

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

void *ACPath_old :: Get (int32 indx0, logical chknode )
{
  ACPathElement *last_node = elements.GetTail();
  int32          curri;
  void      *instptr = NULL;
BEGINSEQ
  if ( chknode )
  {
    if ( nodenode && !nodenode->IsPositioned() )     LEAVESEQ
    if ( Check(YES,NO) )                             ERROR
  }
  curri = nodecur;

  if ( indx0 == AUTO )
    indx0 = curri;
  
  if ( (indx0 == AUTO || indx0 == nodecur) && IsPositioned() ) 
  {
    instptr = nodeinst ? nodeinst->get_iselarea() : flddata;
                                                     LEAVESEQ
  }

  if ( inti_buffer && !stscusr3() )
  {
//  Switch(AUTO);
    if ( !GetBuffer(indx0,0) )                       ERROR
    LEAVESEQ
  }

  if ( !last_node->Get(indx0) )                      ERROR
  nodecur = indx0;
  
  if ( !is_opened )
    Open();
    
  if ( nodesel && CheckExpression() ) 
  {
    instptr = NULL;                                  LEAVESEQ
  }
  SetupInstance();
      
  if ( !(instptr = GetArea()) )                      ERROR
RECOVER
  ResetInstance();
  nodecur = AUTO;
  instptr = NULL;
ENDSEQ
  if ( instptr )
    GenerateEvent(DBO_Read);
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

void *ACPath_old :: Get (char *skey, logical chknode )
{
  void           *instptr = NULL;
  if ( instptr = GetAccessNode()->Get(skey,chknode) )
    SetupInstance();
  
  relative_index = LAST_INSTANCE;        // relative position unknown
  if ( instptr )
    GenerateEvent(DBO_Read);
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetAccessNode - 


\return pe_node -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccessNode"

ACPathElement *ACPath_old :: GetAccessNode ( )
{

  return ( elements.GetTail()->AccessNode() );

}

/******************************************************************************/
/**
\brief  GetCount

\return ecnt -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACPath_old :: GetCount ( )
{


  return ( GetAccessNode()->GetCount() );

}

/******************************************************************************/
/**
\brief  GetElementNode - 


\return pelement
-------------------------------------------------------------------------------
\brief i0


\param  accpath -
\param  parent_element -
\param  co -
\param  bnf_data -
\param  key_name_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementNode"

ACPathElement *ACPath_old :: GetElementNode (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *co, BNFData *bnf_data, char *key_name_w )
{
  BNFData       *path_element;
  BNFData       *path_operand;
  BNFData       *parm_data;
  ACPathElement *pelement = NULL;
BEGINSEQ
  if ( bnf_data )                   
  {
    if ( !(path_element = bnf_data->GetSymbol("path_element")) )
      if ( path_element = bnf_data->GetSymbol("access_path") )
        path_element = path_operand->GetElement(0);
    
    if ( !path_element )                             SDBERR(99)
      
    path_operand = path_element->GetElement(0);
    parm_data    = path_element->GetElement(1);
  }
  pelement = GetElementNode(accpath,parent_element,co,path_operand,parm_data,key_name_w);
RECOVER
  delete pelement;
  pelement = NULL;
ENDSEQ
  return(pelement);
}

/******************************************************************************/
/**
\brief i01


\param  symbol -
\param  parent_element -
\param  bnf_data -
\param  optional -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementNode"

ACPathElement *ACPath_old :: GetElementNode (char *symbol, ACPathElement *parent_element, BNFData *bnf_data, logical optional )
{
  BNFData                *path_operand;
  BNFData                *parm_data;
  PropertyHandle         *prophdl;
  ACPathElement          *pelement = NULL;
BEGINSEQ
  if ( bnf_data->IsSymbol(symbol) || (bnf_data = bnf_data->GetElement(symbol)) )
  {
    path_operand = bnf_data->GetElement(0);
    parm_data    = bnf_data->GetElement(1);
    
    prophdl = parent_element ? &parent_element->get_operand()
                             : nodenode ? (PropertyHandle *)&nodenode : NULL;
    if ( !(pelement = GetElementNode(this,parent_element,prophdl,path_operand,parm_data)) )
                                                     ERROR
    elements.AddTail(pelement);
  }
  else if ( optional )
    pelement = parent_element;
  

RECOVER
  delete pelement;
  pelement = NULL;
ENDSEQ
  return(pelement);
}

/******************************************************************************/
/**
\brief i02


\param  accpath -
\param  parent_element -
\param  co -
\param  path_operand -
\param  parm_data -
\param  key_name_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementNode"

ACPathElement *ACPath_old :: GetElementNode (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *co, BNFData *path_operand, BNFData *parm_data, char *key_name_w )
{
  BNFData                *bnf_data;     
  BNFData                *bdata;     
  BNFData                *scoped_name;     
  FunctionTypes           fttype = FT_undefined;
  char                    opname[ID_SIZE+1];
  char                   *string;
  ACPathElement          *pelement = NULL;
BEGINSEQ
  if ( !path_operand )                               SDBERR(99)
    
  SDBEV1(path_operand->GetStringValue(NULL,NULL),30);
  if ( string = path_operand->GetElement("pname")->GetStringValue(NULL,NULL) )
    SDBEV3(string,UNDEF)
  else
    SDBEV3("",UNDEF)
  
  switch ( fttype = GetElementType(co,path_operand) )
  {
    case FT_SysVariable      : path_operand->GetElement("identifier")->GetValue(opname,sizeof(opname)-1);
                               break;
    case FT_View             : strcpy(opname,"from");
                               if ( path_operand->IsValue("from") )  
                               {
                                 path_operand = parm_data;  // operand_list
                                 parm_data = NULL;              
                               }
                               break;
    case FT_InlineExpression : strcpy(opname,"__inline_expression__");
                               break;
    case FT_Collection       : strcpy(opname,"__collection_operand__");
                               break;
    case FT_error            : SDBERR(372)
    default                  : bdata = path_operand;
                               if ( scoped_name = bdata->GetSymbol("scoped_name") )
                                 if ( scoped_name->GetElement(1) )   // name is really scoped
                                   bdata = scoped_name->GetElement(1)->GetElement("identifier");
                               bdata->GetValue(opname,sizeof(opname)-1);
                               // select() or select(*)
                               if ( !gvtsicmp(opname,"select",UNDEF) && parm_data )
                               {
                                 bnf_data = parm_data->GetElement(1);
                                 if ( bnf_data->IsValue("*") || bnf_data->IsValue(")") ) 
                                                     LEAVESEQ
                               }
  }
  
  pelement = new ACPathElement(this,parent_element,co,fttype,opname,path_operand,parm_data,key_name_w);
  if ( pelement->InitElement(dictionary) )           SDBERR(109)
RECOVER
  pelement = NULL;
ENDSEQ
  return(pelement);
}

/******************************************************************************/
/**
\brief  GetElementType - 


\return fttype -

\param  co -
\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementType"

FunctionTypes ACPath_old :: GetElementType (PropertyHandle *co, BNFData *bnf_data )
{
  int            indx0 = 0;
  FunctionTypes  fttype = FT_undefined;
BEGINSEQ
  if ( !bnf_data )                                       ERROR
  
  if ( (fttype = IsInlineExpression(bnf_data)) == FT_InlineExpression )  
                                                     LEAVESEQ
  if ( (fttype = IsViewPath(bnf_data)) == FT_View )  LEAVESEQ
  if ( (fttype = IsCollectionOperand(bnf_data)) == FT_Collection )  
                                                     LEAVESEQ
  if ( (fttype = IsSysVariable(bnf_data)) == FT_SysVariable )  
                                                     LEAVESEQ

RECOVER
  fttype = FT_error;
ENDSEQ
  return(fttype);
}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum -
-------------------------------------------------------------------------------
\brief NODEKL


\param  indx0 - Position in collection
\param  chknode -
\param  pif_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACPath_old :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number       ebsnum(objid);
  logical         term = NO;
BEGINSEQ
  if ( (indx0 == AUTO || indx0 == nodecur) &&
       nodecur != AUTO && objid != UNDEF      )      LEAVESEQ
       
  ebsnum = noderefp ? LNode::GetID(indx0,chknode,pif_opt)
                    : GetAccessNode()->GetID(indx0,chknode,pif_opt);
  
  if ( ebsnum.IsEmpty() )                            ERROR

RECOVER
  ebsnum = NULL;
  term    = YES;
ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief i01


\param  skey -
\param  chknode -
\param  pif_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACPath_old :: GetID (char *skey, logical chknode, logical pif_opt )
{
  EB_Number       ebsnum(objid);
  logical         term = NO;
BEGINSEQ
  ebsnum = noderefp ? LNode::GetID(skey,chknode,pif_opt)
                    : GetAccessNode()->GetID(skey,chknode,pif_opt);
  
  if ( ebsnum.IsEmpty() )                            ERROR

RECOVER

ENDSEQ
  return(ebsnum);
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

void *ACPath_old :: GetInitInstance (logical set_init )
{
  void             *instptr = NULL;
BEGINSEQ
  if ( !(instptr = GetAccessNode()->GetInitInstance(set_init)) )  ERROR

  SetupInstance();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetInstModCount - 


\return modcount -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 ACPath_old :: GetInstModCount ( )
{
  int16                   modcount = AUTO;
BEGINSEQ
  if ( !nodenode )                                   ERROR
  
  modcount = nodenode->GetInstModCount();

RECOVER

ENDSEQ
  return(modcount);
}

/******************************************************************************/
/**
\brief  GetKeyLength - 


\return klen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 ACPath_old :: GetKeyLength ( )
{
  int16                   klen = 0;
  return( (klen = bnode::GetKeyLength()) 
          ? klen : GetAccessNode()->GetKeyLength() );

  return(klen);
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

smcb *ACPath_old :: GetKeySMCB (char *key_name_w )
{
  smcb          *smcbptr = NULL;
  return( (smcbptr = bnode::GetKeySMCB(key_name_w)) 
          ? smcbptr : GetAccessNode()->GetKeySMCB(key_name_w) );


}

/******************************************************************************/
/**
\brief  GetPathElement - 


\return prophdl -

\param  path_element -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathElement"

PropertyHandle *ACPath_old :: GetPathElement (char *path_element )
{
  ACPathElement          *pelement;
  char                   *path;
  PropertyHandle         *prophdl = NULL;
BEGINSEQ
  elements.GoTop();
  while ( pelement = elements.GetNext() )
    if ( (path = pelement->get_prop_path()) && !strcmp(path,path_element) )
      break;

  if ( !pelement )                                   ERROR
  
  prophdl = &pelement->get_operand();
RECOVER
  prophdl = NULL;
ENDSEQ
  return(prophdl);
}

/******************************************************************************/
/**
\brief  GetRefModCount - 


\return modcount -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 ACPath_old :: GetRefModCount ( )
{
  int16                   modcount;
BEGINSEQ
  if ( !nodenode )                                   ERROR
  
  modcount = nodenode->GetRefModCount();

RECOVER

ENDSEQ
  return(modcount);
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

int16 ACPath_old :: GetSortKeyLength (logical chknode )
{
  int16                   klen = 0;
  return( (klen = bnode::GetSortKeyLength()) 
          ? klen : GetAccessNode()->GetSortKeyLength() );


}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 


\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *ACPath_old :: GetSortKeySMCB ( )
{
  smcb          *smcbptr = NULL;
  return( (smcbptr = bnode::GetSortKeySMCB()) 
          ? smcbptr : GetAccessNode()->GetSortKeySMCB() );


}

/******************************************************************************/
/**
\brief  InitAccessPath - 


\return term - Termination code

\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitAccessPath"

logical ACPath_old :: InitAccessPath (BNFData *bnf_data )
{
  ACPathElement   *pelement       = NULL;
  ACPathElement   *parent_element = NULL;
  PropertyHandle  *prophdl        = nodenode ? (PropertyHandle *)&nodenode : NULL;
  BNFData         *accpath        = bnf_data;
  BNFData         *path_element;
  BNFData         *next_elm;
  int              elmindx      = 0;
  logical          term         = NO;
BEGINSEQ
  if ( !(accpath = bnf_data->GetSymbol("access_path")) )
                                                     SDBERR(99)
    
  if ( !(path_element = accpath->GetElement(elmindx++)) )
                                                     SDBERR(99)
  while ( path_element )
  {
    if ( pelement = GetElementNode(this,parent_element,prophdl,path_element) )
    {
      elements.AddTail(pelement);
      prophdl        = &pelement->get_operand();
      parent_element = pelement;
    }
    else                                             SDBCERR
    
    pelement       = NULL;
    path_element   = NULL;
    if ( next_elm = accpath->GetElement(elmindx++) )
      if ( !(path_element = next_elm->GetElement("path_element")) )
                                                     SDBERR(99)
  }

RECOVER
  if ( pelement )
    delete pelement;
  pelement = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitElements - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitElements"

logical ACPath_old :: InitElements (BNFData *bnf_data )
{
  smcb            *smcbptr;
  logical          term = NO;
BEGINSEQ
  nodetype       = NT_ACPath;
  is_opened      = NO;
  is_collection  = YES;
  expression_bnf = bnf_data;
  
  if ( Check(NO,NO) )                                ERROR
  
  SDBEV1("",UNDEF)
  SDBEV2("",UNDEF)
  if ( smcbptr = nodenode && nodenode->get_fldfmcb() ? nodenode->get_fldfmcb()->fmcbsmcb : NULL )
    SDBEV2(smcbptr->smcbname,ID_SIZE)
  
  if ( bnf_data->IsSymbol("OQLSelect") 
       ? InitOQLSelect(bnf_data) 
       : InitAccessPath(bnf_data)         )          ERROR
  
  if ( nodenode && nodenode->IsCollection() )
    ((bnode *)nodenode->GetNode())->AddPathNode(this);

  Open();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  dbview_str -
\param  source_list -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitElements"

logical ACPath_old :: InitElements (DBStructDef *dbview_str, DLL(FieldSource) *source_list )
{
  logical     term = NO;
BEGINSEQ
  nodetype       = NT_ACPath;
  is_opened      = NO;
  is_collection  = YES;
  
  if ( Check(NO,NO) )                                ERROR
  
  SDBEV2("",UNDEF)

  if ( InitFromElement(dbview_str,source_list) )     ERROR
  if ( InitViewElements(dbview_str) )                ERROR

  if ( nodenode && nodenode->IsCollection() )
    ((bnode *)nodenode->GetNode())->AddPathNode(this);
  
  Open();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitFromElement

\return term - Termination code

\param  dbview_str -
\param  source_list -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFromElement"

logical ACPath_old :: InitFromElement (DBStructDef *dbview_str, DLL(FieldSource) *source_list )
{
  DLL(DBViewPath)        *from_list = dbview_str->get_from();
  DBViewPath             *from_path;
  FieldSource            *source;
  ACPathElement          *pelement;
  NString                 fstring;
  NString                 kstring;
  BNFData                *bdata  = NULL;
  char                   *string = NULL;
  int32                   indx0;
  logical                 first = YES;
  logical                 term = NO;
BEGINSEQ
  if ( !source_list )                                SDBERR(246)
  if ( !from_list )                                  SDBERR(99)

  if ( source_list->GetCount() != from_list->GetCount() )
                                                     SDBERR(246)
  from_list->GoTop();
  source_list->GoTop();

  fstring = "from(";
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
      fstring += ',';
      kstring += ',';
      first = NO;
    }
    fstring += source->GetString();
    kstring += source->GetOrder();
    
    if ( *from_path->get_path() )
    {
      fstring += '.';
      fstring += from_path->get_path();
    }
    indx0++;
  }
  fstring += ")";

  if ( !(bdata = dictionary->ParseExpression(fstring,"operand",&string)) )
                                                     ERROR
  if ( !(pelement = GetElementNode(this,NULL,(PropertyHandle *)&nodenode,
                                   (BNFExpData *)bdata,kstring)) )
                                                     ERROR
  pelement->set_bnftop(bdata,string); 
  elements.AddTail(pelement);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitOQLSelect - 


\return term - Termination code

\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOQLSelect"

logical ACPath_old :: InitOQLSelect (BNFData *bnf_data )
{
  ACPathElement   *pelement       = NULL;
  PropertyHandle  *prophdl        = nodenode ? (PropertyHandle *)&nodenode : NULL;
  int              elmindx      = 0;
  logical          term         = NO;
BEGINSEQ
  if ( !(bnf_data = bnf_data->GetSymbol("OQLSelect")) ) SDBERR(99)
    
  if ( !(pelement = GetElementNode("from_spec",NULL,bnf_data,NO)) )
                                                     ERROR
  if ( !(pelement = GetElementNode("where_spec",pelement,bnf_data,YES)) )
                                                     ERROR
  if ( !(pelement = GetElementNode("sel_spec",pelement,bnf_data,NO)) )
                                                     ERROR
  if ( !(pelement = GetElementNode("group_spec",pelement,bnf_data,YES)) )
                                                     ERROR
  if ( !(pelement = GetElementNode("having_spec",pelement,bnf_data,YES)) )
                                                     ERROR
  if ( bnf_data = bnf_data->GetElement("output_spec") )
  {
    bnf_data = bnf_data->GetElement(0);
    if ( !(pelement = GetElementNode(bnf_data->IsSymbol("to_file") ? "to_file" : "to_database",
                              pelement,bnf_data,YES)) )
                                                     ERROR
  }

RECOVER
  if ( pelement )
    delete pelement;
  pelement = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitTopElementNode - 


\return pelement

\param  accpath -
\param  parent_element -
\param  co -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitTopElementNode"

ACPathElement *ACPath_old :: InitTopElementNode (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *co )
{
  BNFExpData    *path_operand;
  BNFExpData    *parm_data;
  FunctionTypes  fttype = FT_undefined;
  char           opname[ID_SIZE+1];
  char          *string;
  ACPathElement *pelement = NULL;
BEGINSEQ
  if ( !bdata )                                      SDBERR(99)
  if ( !(path_operand = bdata->GetElement(0)) )      SDBERR(99)
  parm_data    = bdata->GetElement(1);
  
  SDBEV1(bdata->GetStringValue(NULL,NULL),30);
  if ( string = path_operand->GetElement("pname")->GetStringValue(NULL,NULL) )
    SDBEV3(string,UNDEF)
  else
    SDBEV3("",UNDEF)
  
  switch ( fttype = GetElementType(co,path_operand) )
  {
    case FT_View             : strcpy(opname,"from");
                               if ( path_operand->GetElement(0)->IsA("pname") )  // 'from'
                               {
                                 path_operand = parm_data;
                                 parm_data = NULL;                           // operand_list
                               }
                               break;
    case FT_InlineExpression : strcpy(opname,"__inline_expression__");
                               break;
    case FT_Collection       : strcpy(opname,"__collection_operand__");
                               break;
    case FT_error            : SDBERR(372)
    default                  : path_operand->GetElement(0)->GetValue(opname,sizeof(opname)-1);
                               // select() or select(*)
                               if ( !gvtsicmp(opname,"select",UNDEF) && parm_data )
                               {
                                 bdata = parm_data->GetElement(1);
                                 if ( bdata->IsValue("*") || bdata->IsValue(")") ) 
                                                     LEAVESEQ
                               }
  }
  
  pelement = new ACPathElement(this,parent_element,co,fttype,opname,path_operand,parm_data,NULL);
  if ( pelement->InitElement(dictionary) )           SDBERR(109)
RECOVER
  delete pelement;
  pelement = NULL;
ENDSEQ
  return(pelement);
}

/******************************************************************************/
/**
\brief  InitViewElements

\return term - Termination code

\param  dbview_str -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewElements"

logical ACPath_old :: InitViewElements (DBStructDef *dbview_str )
{
  BNFData                *bdata;
  PropertyHandle         *prophdl;
  ACPathElement          *pelement;
  NString                 fstring;
  char                   *string = NULL;
  logical                 term = NO;
BEGINSEQ
  pelement        = elements.GetTail();
  if ( string = dbview_str->get_where() )
  {
    fstring = "where(";
    fstring+= string;
    fstring += ')';
    if ( !(bdata = dictionary->ParseExpression(fstring,"operand",&string)) )
                                                     ERROR
    prophdl         = &pelement->get_operand();
    if ( !(pelement = GetElementNode(this,pelement,prophdl,(BNFExpData *)bdata)) )
                                                     ERROR
    pelement->set_bnftop(bdata,string);
    elements.AddTail(pelement);
  }

  prophdl         = &pelement->get_operand();
  pelement = new ACPathElement(this,pelement,prophdl,dbview_str);
                                                     SDBCERR
  elements.AddTail(pelement);
  
// group_by is missing

  if ( string = dbview_str->get_having() )
  {
    fstring = "where(";
    fstring+= string;
    fstring += ')';
    if ( !(bdata = dictionary->ParseExpression(fstring,"operand",&string)) )
                                                     ERROR
    prophdl         = &pelement->get_operand();
    if ( !(pelement = GetElementNode(this,pelement,prophdl,(BNFExpData *)bdata)) )
                                                     ERROR
    pelement->set_bnftop(bdata,string);
    elements.AddTail(pelement);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize

-------------------------------------------------------------------------------
\brief i00


\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ACPath_old :: Initialize (BNFData *bnf_data )
{

  InitElements(bnf_data);

}

/******************************************************************************/
/**
\brief i01


\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ACPath_old :: Initialize (ACObject *obhandle )
{
  DBExtend  *dbextdef = nodefield ? (DBExtend *)nodefield : NULL;
  DBStructDef   *dbstr_def;
  ACPathElement *pelement;
  node          *nodeptr;
BEGINSEQ
  if ( !dbextdef )                                   SDBERR(99)
  SDBEV1(dbextdef->fmcbname,ID_SIZE)
    
  dbstr_def = dbextdef->GetDBStruct();
  if ( dbstr_def->GetViewStructDef() )
  {
    if ( InitElements(dbstr_def,dbextdef->get_sources()) )
                                                     ERROR
  }
  else
  {
    if ( !(nodeptr = obhandle->CreateNode(dbextdef,nodeacc)) )
                                                     ERROR
    pelement = new ACPathElement(this,NULL,nodeptr,NULL);
                                                     SDBCERR
    elements.AddTail(pelement);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i03


\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ACPath_old :: Initialize (DBFieldDef *fielddef )
{
  DBStructDef          *dbstr_def;
  FieldSource          *source;
  ACPathElement        *pelement;
  node                 *nodeptr;
  node                **pnodeptr;

BEGINSEQ
  if ( !fielddef )                                  ERROR
    
  SDBEV1(fielddef->fmcbname,ID_SIZE)
    
  dbstr_def = fielddef->GetDBStruct();
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

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsCollectionOperand - 


\return fttype -

\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollectionOperand"

FunctionTypes ACPath_old :: IsCollectionOperand (BNFData *bnf_data )
{
  FunctionTypes  fttype = FT_undefined;
// path elements like [...] are considered as collection operands 
  
  if ( bnf_data->GetElement(0)->IsA("coll_operand") )
    fttype = FT_Collection;

  return(fttype);
}

/******************************************************************************/
/**
\brief  IsGlobalVariable - 


\return cond

\param  opname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGlobalVariable"

logical ACPath_old :: IsGlobalVariable (char *opname )
{
  logical                 cond = NO;
  if ( GetDictionary()->GetGlobalVariable(opname) )
    cond = YES;
  return(cond);
}

/******************************************************************************/
/**
\brief  IsInlineExpression - 


\return fttype -

\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInlineExpression"

FunctionTypes ACPath_old :: IsInlineExpression (BNFData *bnf_data )
{
  FunctionTypes  fttype = FT_undefined;
// path elements like {...} are considered as inline-expressions 
  
  if ( ((BNFExpData *)bnf_data->GetElement(0))->IsExpression() )
    fttype = FT_InlineExpression;

  return(fttype);
}

/******************************************************************************/
/**
\brief  IsLocalVariable - 


\return cond

\param  opname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalVariable"

logical ACPath_old :: IsLocalVariable (char *opname )
{
  logical                 cond = NO;
  if ( variables && variables->Get(opname) )
    cond = YES;
  return(cond);
}

/******************************************************************************/
/**
\brief  IsParameter - 


\return cond

\param  opname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsParameter"

logical ACPath_old :: IsParameter (char *opname )
{
  logical                 cond = NO;
  if ( parameters && parameters->Get(opname) )
    cond = YES;
  return(cond);
}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical ACPath_old :: IsPositioned ( )
{

  return (   nodeinst 
           ? LNode::IsPositioned()
           : nodecur >= 0 ? node::IsPositioned()
                          : NO );

}

/******************************************************************************/
/**
\brief  IsSelected - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical ACPath_old :: IsSelected ( )
{

  return (   nodeinst 
           ? LNode::IsSelected()
           : nodecur >= 0 ? node::IsSelected()
                          : NO );

}

/******************************************************************************/
/**
\brief  IsSysVariable - 


\return fttype -

\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSysVariable"

FunctionTypes ACPath_old :: IsSysVariable (BNFData *bnf_data )
{
  FunctionTypes     fttype = FT_undefined;
BEGINSEQ
  fttype = FT_SysVariable;
  
  if ( !bnf_data->IsSymbol("sys_variable") )         ERROR

RECOVER
  fttype = FT_undefined;
ENDSEQ
  return(fttype);
}

/******************************************************************************/
/**
\brief  IsViewPath

\return fttype -

\param  bnf_data -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsViewPath"

FunctionTypes ACPath_old :: IsViewPath (BNFData *bnf_data )
{
  BNFData          *element = bnf_data;
  FunctionTypes     fttype = FT_undefined;
BEGINSEQ
// path elements like (...) and from(...) are considered as views. 
  
  fttype = FT_View;
  
  if ( bnf_data->IsSymbol("operand_list")   || 
       bnf_data->IsSymbol("from")           ||
       bnf_data->IsSymbol("from_spec")         )     LEAVESEQ
  
  if ( !(bnf_data = bnf_data->GetSymbol("path_operand")) ) 
                                                     ERROR
  if ( !(element = bnf_data->GetElement(0)) ||
       !element->IsSymbol("pname")          || 
       gvtsicmp(element->StringValue(),"from",UNDEF) )
                                                     ERROR

RECOVER
  fttype = FT_undefined;
ENDSEQ
  return(fttype);
}

/******************************************************************************/
/**
\brief  LocateKey

\return term - Termination code

\param  skey -
\param  exact -
\param  chknode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical ACPath_old :: LocateKey (char *skey, logical exact, logical chknode )
{
  ACPathElement  *last_node = GetAccessNode();
  logical         term = NO;
BEGINSEQ
  if ( (noderefp ? LNode::LocateKey(skey,exact)
                 : last_node->LocateKey(skey,exact)) ) 
                                                     ERROR
      
  nodecur = nodesel ? LAST_INSTANCE : last_node->get_nodecur();
  relative_index = LAST_INSTANCE;        // relative position unknown
RECOVER
  nodecur = AUTO;
  term    = YES;
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

logical ACPath_old :: Lock ( )
{

  return ( (noderefp ? LNode::Lock()
                     : GetAccessNode()->Lock()) );

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

logical ACPath_old :: LockSet (logical chknode )
{

  return ( (noderefp ? LNode::LockSet(chknode)
                     : GetAccessNode()->LockSet(chknode)) );

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

char *ACPath_old :: NextKey (char *skey, int16 switch_level )
{
  int32           klen;
  char            savekey[513];
  char           *keyptr = NULL;
BEGINSEQ
  if ( Check(YES) )	                             ERROR
  if ( noderefp )
  {
    keyptr = LNode::NextKey(skey,switch_level);
    LEAVESEQ
  }
  
  if ( nodecur == AUTO && !skey )
  {
    if ( !(keyptr = FirstKey(NO)) )                  ERROR
    LEAVESEQ
  }
  
  if ( !skey )
  {
    if ( Position(1) < 0 )                          ERROR
  }
  else
  {
    if ( !(klen = GetSortKeyLength(NO)) )            ERROR
    memcpy(savekey,skey,klen);
    if ( LocateKey(skey,NO,NO) )                     ERROR
    if ( !Get(AUTO) )                                ERROR
    while ( !CompareSortKey(ExtractSortKey(NULL,NULL,NO),savekey,NO) )
      if ( Position(1) < 0 )                        ERROR
  }
  if ( !(keyptr = klen ? ExtractSortKey(NULL,NULL,NO)
                       : ExtractKey(NULL,NULL,NO)) ) ERROR

RECOVER
  ResetInstance();
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACPath_old :: Open ( )
{
  ACPathElement *last_node = GetAccessNode();
  bnode         *op_node;
  node          *onode;
  DBFieldDef    *field_def;
  logical        term = NO;
BEGINSEQ
  if ( !last_node || 
       !(onode = last_node->get_operand().get_nodeptr()) )
                                                     ERROR
  last_node->SetLast();
  
  op_node = onode->get_nodetype() == NT_Node ? NULL : (bnode *)onode;  
  if ( !is_opened && !stscerr() )
  {
    last_node->Check(YES,NO);
    field_def = op_node ? op_node->GetFieldDef()
                        : onode->GetFieldDef();
    if ( !field_def )
      field_def = last_node->GetFieldDef();
    if ( field_def )
      if ( !bnode::Open(object_ref,nodenode,field_def,NULL,nodeacc) )
      {
        is_opened = YES;
        if ( !last_node->IsCollection() )
          is_collection = NO;
        if ( last_node->IsMemo() )
          is_memo = YES;
      }
      else
      {
        stsserr();                                 ERROR
      }
  }
  
  if ( op_node )
  {
    id_key   = op_node->get_id_key();
    sk_index = op_node->get_sk_index();
  }
  SetupInstance();

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

int32 ACPath_old :: Position (int32 count, logical chknode )
{
  logical         pos_invalid = NO;
  int32           lindx0;
BEGINSEQ
  if ( relative_index == LAST_INSTANCE )
  {
    absolute_index = nodecur;
    relative_index = count > 0 ? 0 : LAST_INSTANCE;
    pos_invalid = YES;
  }

  lindx0 = count;
  if ( relative_index != AUTO )
    lindx0 += relative_index;
  if ( !GetRelative(lindx0) )                       ERROR

RECOVER
  lindx0 = AUTO;
ENDSEQ
  if ( pos_invalid )
    relative_index = LAST_INSTANCE;
  return(lindx0);

}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ACPath_old :: Reset ( )
{
  logical        term = NO;

BEGINSEQ
  if ( GetAccessNode()->Reset() )                      ERROR

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

logical ACPath_old :: ResetNode (logical reset_all )
{

  Cancel();
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

logical ACPath_old :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical        term = NO;
BEGINSEQ
  if ( switchopt )
    nodecur = AUTO;

  if ( GetAccessNode()->Save(switchopt,overwrite,chknode) )
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

logical ACPath_old :: SetContextVariables (char *context_string )
{

  return( GetAccessNode()->SetContextVariables(context_string) );

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

logical ACPath_old :: SetKey (kcb *kcbptr, char *keyptr, void *instptr )
{

  return( GetAccessNode()->SetKey(kcbptr,keyptr,instptr) );


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

logical ACPath_old :: SetKey (char *keyptr, void *instptr )
{

  return( GetAccessNode()->SetKey(keyptr,instptr) );

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

logical ACPath_old :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  logical        term = NO;

BEGINSEQ
  if ( GetAccessNode()->SetOrder(strnames,attrtype,attrstr) )
                                                     ERROR
  nodecur = AUTO;
  stsrfil();

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

logical ACPath_old :: SetSortKey (char *keyptr, void *instptr )
{

  return( GetAccessNode()->SetKey(keyptr,instptr) );

}

/******************************************************************************/
/**
\brief  SetupInstance - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInstance"

void ACPath_old :: SetupInstance ( )
{
  ACPathElement *last_node = elements.GetTail();
  ACPathElement *nodeptr = GetAccessNode();

  nodewrit = NO;
  
  if ( nodeptr->get_nodeinst() )
  {
    node::SetCurrentInti(nodeptr->get_nodeinst());
    if ( nodeacc != PI_Read )
      nodewrit = nodeptr->IsWrite();
    nodeinst->SetObjectID(objid = Bnodeptr->get_objid());
  }
  else
    node::SetArea(nodeptr->GetArea());
  
  SetDescription(nodeptr->GetInstFieldDef());
  nodefield = nodeptr->GetFieldDef();

  variable_type = nodeptr->get_variable_type();

  absolute_index = last_node->get_absolute_index();
  relative_index = last_node->get_relative_index();


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

logical ACPath_old :: Switch (int32 indx0 )
{
  logical        term = NO;
  if ( indx0 != nodecur )
    GetAccessNode()->Switch(indx0);

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

logical ACPath_old :: Unlock ( )
{

  return ( (noderefp ? LNode::Unlock()
                     : GetAccessNode()->Unlock()) );

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

logical ACPath_old :: UnlockSet (logical extlock, logical chknode )
{

  return ( (noderefp ? LNode::UnlockSet(extlock,chknode)
                     : GetAccessNode()->UnlockSet(extlock,chknode)) );

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

node *ACPath_old :: ValidateNode (logical crt_opt )
{
  node          *new_node  = this;

  GetAccessNode()->ValidateNode(crt_opt);
  return(new_node);
}

/******************************************************************************/
/**
\brief  set_expression - 



\param  path_def -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_expression"

void ACPath_old :: set_expression (char *path_def )
{

  expression = path_def;

}

/******************************************************************************/
/**
\brief  ~ACPath - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACPath"

void ACPath_old :: ~ACPath ( )
{
  nodelist        nl;
  ACPathElement   *pelement;
  nodeinst  = NULL;
  nodefield = NULL;
  id_key    = NULL;
  sk_index  = NULL;
  
  if ( nodenode && nodenode->IsCollection() )
    Bnodenode->RemovePathNode(this);
  
  if ( expression )
  {
    delete expression_bnf;
    free (expression);
    expression = NULL;
  }
  expression_bnf = NULL;
  
  while ( pelement = elements.RemoveTail() )
    delete pelement;

}


