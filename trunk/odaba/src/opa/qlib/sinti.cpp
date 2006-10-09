/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    sinti

\brief    Instance area for operations
          Operation  instances are created for  different types of ACOperations.
          Operation  instances  are  based  on  a  calling  node  (nodenode  in 
          ACOperation).  Instance  areas  for  operations  may  consist  of four
          parts:
          Base  structures:  Base  structures  describe instances inherited from
          other  nodes. Usually,  base instances  inherit the instance area from
          the  referenced node. Base instances  do nor contain values calculated
          in the context of the operation (Product, Join)
          Attributes:  attribute values are attributes derived from the instance
          in the calling object  (Select, GrupBy). 
          References:  reference values are collections derived from the calling
          object (Select, GrupBy).
          An  sinti may  contain multiple  instances (Product, Join) when having
          one  or more base structures. otherwise it inherits the selection from
          its calling object.

\date     $Date: 2006/07/16 12:28:35,56 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sinti"

#include  <popa7.h>
#include  <sACOperand.hpp>
#include  <sACOperation.hpp>
#include  <sACViewProperty.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOPParmList.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <ssinti.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical sinti :: Add (logical global_add )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( Switch() )                                    ERROR
  
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    if ( nodeptr->Add(AUTO,NULL,NULL,
                      nodeptr->get_nodeinst()->get_iselarea(),global_add) )
                                                     ERROR

  objid = ((bnode *)node_base.GetHead())->get_objid();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical sinti :: Cancel ( )
{
  node                   *nodeptr;
  logical                 term = NO;
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    if ( nodeptr->Cancel() )                      
      term = YES;

  ResetNodes();  
  Reset();
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  extname - Extent name
\param  is_root - 
\param  delopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical sinti :: Delete (char *extname, logical is_root, int16 delopt )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_base.GoBottom();
  nodeptr = node_base.GetPrev();
  
  if ( nodeptr->Delete(AUTO,delopt) )                  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  First - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "First"

logical sinti :: First ( )
{
  logical          term = NO;
BEGINSEQ
  Switch();
  if ( Next(1) )                                     ERROR
  
  inst_index = 0;
  objid = ((bnode *)node_base.GetHead())->get_objid();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return term - Termination code

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical sinti :: Get (EB_Number entnr )
{
  uint32     indx0 = entnr.get_ebsnum();
  int32      count = 0;
  logical    term  = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( indx0 != inst_index )
  {
    if ( indx0 == FIRST_INSTANCE )
    {
      if ( First() )                                 ERROR
    }
    else if ( indx0 == LAST_INSTANCE )
    {
      if ( Last() )                                  ERROR
    }
    else
    {
      count = indx0 - inst_index;
      if ( indx0 < LAST_INSTANCE/2 &&
           (indx0 < inst_index/2 || inst_index > LAST_INSTANCE/2) )
      {
        if ( First() )                               ERROR
        count = indx0;
      }
      if ( indx0 > LAST_INSTANCE/2 &&
           (indx0 > (LAST_INSTANCE + inst_index)/2 || inst_index < LAST_INSTANCE/2) )
      {
        if ( Last() )                                ERROR
        count = indx0 - LAST_INSTANCE;
      }
      if ( Position(count) )                         ERROR
    }
  }
  
  inst_index = indx0;
  objid = ((bnode *)node_base.GetHead())->get_objid();

  if ( GetData() )                                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetData - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

logical sinti :: GetData ( )
{
  nodelist   cursor;
  node      *nodeptr;
  logical    term  = NO;
BEGINSEQ
  if ( stscfil() )                                   LEAVESEQ
    
  (cursor = node_attr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    ((ACOperand *)nodeptr)->Read();
  
  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    ((ACOperand *)nodeptr)->Read();
  
  stssfil();
  stsrini();

  ProcessEvent(DBO_Read);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitBaseInti - 



\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitBaseInti"

void sinti :: InitBaseInti (node *nodeptr )
{

  nodeptr->Check(YES,NO);
  nodeptr->get_nodeinst()->ReleaseArea();
  nodeptr->get_nodeinst()->InitArea(iselarea+Bnodeptr->get_nodefield()->fmcbposn);


}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical sinti :: IsPositioned ( )
{

  return( inst_index >= 0 && stscfil() ? YES : NO );


}

/******************************************************************************/
/**
\brief  Last - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Last"

logical sinti :: Last ( )
{
  logical          term = NO;
BEGINSEQ
  Switch();
  if ( Previous(1) )                                ERROR
  
  inst_index = LAST_INSTANCE;
  objid = ((bnode *)node_base.GetHead())->get_objid();
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey - 


\return term - Termination code

\param  skey - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical sinti :: LocateKey (char *skey, logical exact )
{
  node                   *nodeptr;
  int32                    pos = 0;
  logical                 term = NO;
BEGINSEQ
  if ( Switch() )                                    ERROR
  
// das funktioniert nicht richtig, wenn der view key identity-Sortierungen enthält
  if ( struct_def->smcbidky->scbsmcb->smcbsts.stsclck() )  // damit wir nicht abstürzen
                                                     SDBERR(99)
  
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
  {
    if ( nodeptr->LocateKey(skey+pos,exact) )        ERROR
    if ( nodeptr->CompareSortKey(skey,nodeptr->ExtractKey(NULL,NULL,NO),NO) )
    {
      if ( exact )                                   ERROR
      while ( nodeptr = node_base.GetNext() )
        if ( !nodeptr->Get(0) )                      ERROR
      LEAVESEQ
    }
    pos += nodeptr->GetSortKeyLength(NO);
  }

  stsrfil();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Next - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical sinti :: Next (int32 count )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( count <= 0 )                                  ERROR
  node_base.GoTop();
  while ( (nodeptr = node_base.GetNext()) && nodeptr->Exist() ) ;
  
  if ( !nodeptr )
  {  
    node_base.GoBottom();
    nodeptr = node_base.GetPrev();
  }
  
  if ( Next(nodeptr) )                               ERROR
  
  node_base.GoBottom();
  nodeptr = node_base.GetPrev();
  while ( --count )
    if ( Next(nodeptr) )                             ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical sinti :: Next (node *nodeptr )
{
  logical                 term = NO;
BEGINSEQ
  while ( true )
  {
    while ( nodeptr->Position(1) && (nodeptr = node_base.GetPrev()) ) ;
  
    if ( !nodeptr )                                  ERROR
    
    while ( nodeptr = node_base.GetNext() )
      if ( !nodeptr->Get(FIRST_INSTANCE) )
      {
        nodeptr = node_base.GetPrev();
        break;
      }
    
    if ( nodeptr )                                   LEAVESEQ
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenOperands - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenOperands"

logical sinti :: OpenOperands ( )
{
  node                   *nodeptr;
  OPBase                 *op_base;
  int32                   indx0 = 0;
  int32                   intpos = 0;
  int32                   extpos = 0;
  int32                   netpos = 0;
  short int               defined_align;   
  int8                    plattform_align; 
  logical                 term = NO;
BEGINSEQ
  if ( parmlist )
    while ( op_base = parmlist->GetAt(indx0++) )
      if ( operation->CreateNode(op_base) )              ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Position - 


\return term - Termination code

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical sinti :: Position (int32 count )
{
  logical                 term = NO;
BEGINSEQ
  if ( !count )                                      LEAVESEQ
  
  if ( count > 0 ? Previous(-count)
                 : Next(count)       )               ERROR

  inst_index += count;
  objid = ((bnode *)node_base.GetHead())->get_objid();
  stsrfil();
RECOVER
  inst_index = AUTO;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Previous - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical sinti :: Previous (int32 count )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( count <= 0 )                                  ERROR
  node_base.GoTop();
  while ( (nodeptr = node_base.GetNext()) && nodeptr->Exist() ) ;
  
  if ( !nodeptr )
  {  
    node_base.GoBottom();
    nodeptr = node_base.GetPrev();
  }
  
  if ( Previous(nodeptr) )                           ERROR
  
  node_base.GoBottom();
  nodeptr = node_base.GetPrev();
  while ( --count )
    if ( Previous(nodeptr) )                         ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical sinti :: Previous (node *nodeptr )
{
  logical                 term = NO;
BEGINSEQ
  while ( true )
  {
    while ( nodeptr->Position(-1) && (nodeptr = node_base.GetPrev()) ) ;
  
    if ( !nodeptr )                                  ERROR
    
    while ( nodeptr = node_base.GetNext() )
      if ( !nodeptr->Get(LAST_INSTANCE) )
      {
        nodeptr = node_base.GetPrev();
        break;
      }
    
    if ( nodeptr )                                   LEAVESEQ
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetInstance - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

logical sinti :: ResetInstance ( )
{
  node                   *nodeptr;
  logical                 term = NO;
  if ( nodeptr = node_base.GetTail() )
    term = ResetInstance(nodeptr);


  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

logical sinti :: ResetInstance (node *nodeptr )
{
  int32           curri = nodeptr->get_nodecur();
  node           *cur_node = nodeptr;
  logical         term = NO;
  if ( nodeptr = node_base.GetNext() )
  {
    term = ResetInstance(nodeptr);
    
    if ( term || !cur_node->Get(curri) )
      term = YES;
  }
  else
    term = cur_node->Reset();

  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical sinti :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{
  nodelist   cursor;
  node      *node_ptr;
  logical    term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  (cursor = node_refr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->Store();
  
  (cursor = node_attr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->Store();
  
  if ( switchopt )
    ResetReferences();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Switch - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Switch"

logical sinti :: Switch ( )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    if ( nodeptr->Switch(AUTO) )                      
      term = YES;

  inst_index = AUTO;
  ResetNodes();
  Reset();
  return(term);
}

/******************************************************************************/
/**
\brief  sinti - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  op_node - 
\param  strdef - Structure definition
\param  instptr - 
\param  crt_opt - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sinti"

     sinti :: sinti (ACOperation *op_node, DBStructDef *strdef, void *instptr, logical crt_opt, OperEnvironment *operenv )
                     : binti (),
OPDecl (NULL),
  operation(op_node),
  oper_env(operenv),
  is_multiple(NO)
{
  DBFieldDef       *fielddef;
  ACOperand        *view_prop;
  node             *nodeptr;
  int32             indx = 0;
BEGINSEQ
  struct_def = strdef;
  operation->set_nodeinst(this);
  
  if ( CreateEnvironment(NULL,NULL,NULL,NULL,NULL,operation->GetPH(),this) )
                                                     ERROR
  CopyEnvironment(oper_env,YES);
  class_ref = Scope();
  
  while ( fielddef = strdef->GetEntry(++indx) )
  {
    if ( fielddef->get_static() )                    // multiple child source
    {
      if ( !operation->CreateNode(fielddef) )        ERROR
    }
    else                                             // operand
      if ( !AddParameter(this,fielddef) )            ERROR
  }
   
  if ( OpenOperands() )                              ERROR
    
  struct_def->SetupCounts();
  if ( !struct_def->Setup(DictHandle()->get_dictionary()) )       
                                                     ERROR
  Init(operation,NULL,strdef,iselarea);
  
  InitInit();
  operation->SetInti(this);    // for weak-typed, only

  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    nodeptr->SetIntiArea(iselarea+Bnodeptr->get_nodefield()->fmcbposn);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sinti"

     sinti :: sinti ( )
                     : binti (),
OPDecl (NULL),
  operation(NULL),
  oper_env(NULL),
  is_multiple(NO)
{



}

/******************************************************************************/
/**
\brief  ~sinti - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sinti"

     sinti :: ~sinti ( )
{
  node          *nodeptr;
  while ( nodeptr = node_base.RemoveTail() )
    delete nodeptr;

  while ( nodeptr = node_attr.RemoveTail() )
    delete nodeptr;

  while ( nodeptr = node_refr.RemoveTail() )
    delete nodeptr;


}


