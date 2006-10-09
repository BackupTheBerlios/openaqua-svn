/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    vinti

\brief    


\date     $Date: 2006/03/12 19:19:34,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "vinti"

#include  <popa7.h>
#include  <sACElmView.hpp>
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sDBStructDef.hpp>
#include  <snode.hpp>
#include  <svinti.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  skey -
\param  global_add -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical vinti :: Add (char *skey, logical global_add )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( Switch() )                                    ERROR
  
  if ( skey )
    struct_def->smcbidky->kcbkpt(iselarea,skey);

  node_refr.GoTop();
  while ( nodeptr = node_refr.GetNext() )
    if ( ((LNode *)nodeptr)->PathAdd(global_add) )   ERROR

  objid = ((bnode *)node_refr.GetHead())->get_objid();

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

logical vinti :: Cancel ( )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    if ( nodeptr->Cancel() )                      
      term = YES;

  cur_index = AUTO;
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

logical vinti :: Close ( )
{

  node_base.DeleteNodes();
  node_attr.Clear();
  node_refr.Clear();

  binti::Close();
  return(NO);
}

/******************************************************************************/
/**
\brief  ExtractKey - 


\return term - Termination code

\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

logical vinti :: ExtractKey (char *keyptr )
{
  node            *nodeptr;
  smcb            *keysmcb = struct_def->smcbidky->scbsmcb;
  smcb            *ksmcb;
  fmcb            *fmcbptr;
  int32             i = 1;
  int32             j = 1;
  nodelist         cursor(node_attr);
  logical          term = NO;
BEGINSEQ
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
  {
    if ( !struct_def->GetEntry(j++) )
      break;
    if ( !(fmcbptr = keysmcb->GetEntry(i)) )         SDBERR(99)
    if ( !nodeptr->ExtractSortKey(keyptr+fmcbptr->fmcbposn,NULL,NO) &&
         !nodeptr->ExtractKey(keyptr+fmcbptr->fmcbposn,(char *)NULL,NO)        )
                                                     SDBERR(99)
    if ( !(ksmcb = Bnodeptr->get_sortkey_smcb()) )
      ksmcb = Bnodeptr->get_idkey_smcb();
    i += ksmcb->smcbfmcl->GetCount();
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  First

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "First"

logical vinti :: First ( )
{
  logical          term = NO;
BEGINSEQ
  Switch();
  if ( Next(1) )                                     ERROR
  inst_index = cur_index = 0;
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical vinti :: Get ( )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_attr.GoTop();
  while ( nodeptr = node_attr.GetNext() )
    if ( !nodeptr->Get(AUTO) )                       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCount - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 vinti :: GetCount ( )
{
  node                   *nodeptr;
  int32                    tcount = 1;
  int32                    count = 0;
  logical                 term = NO;
BEGINSEQ
  node_refr.GoTop();
  while ( (nodeptr = node_refr.GetNext()) && (count = ((LNode *)nodeptr)->PathGetCount()) != ERIC )
    tcount *= count;

  if ( count == ERIC )                               ERROR
RECOVER
  tcount = ERIC;
ENDSEQ
  return(tcount);
}

/******************************************************************************/
/**
\brief  GetID - 


\return entnr -

\param  w_indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number vinti :: GetID (int32 w_indx0 )
{

  return( this ? objid : AUTO );

}

/******************************************************************************/
/**
\brief  GetTopNode - 


\return nodeptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTopNode"

ACNode *vinti :: GetTopNode ( )
{

  return((ACNode *)node_attr.GetHead());

}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical vinti :: IsPositioned ( )
{

  return( inst_index != AUTO ? YES : NO );

}

/******************************************************************************/
/**
\brief  Last

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Last"

logical vinti :: Last ( )
{
  logical          term = NO;
BEGINSEQ
  Switch();
  if ( Previous(1) )                                ERROR
  inst_index = cur_index = LAST_INSTANCE;
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey

\return term - Termination code

\param  skey -
\param  exact -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical vinti :: LocateKey (char *skey, logical exact )
{
  node                   *nodeptr;
  int32                    pos = 0;
  logical                 term = NO;
BEGINSEQ
  if ( Switch() )                                    ERROR
  
// das funktioniert nicht richtig, wenn der view key identity-Sortierungen enthält
  if ( struct_def->smcbidky->scbsmcb->smcbsts.stsclck() )  // damit wir nicht abstürzen
                                                     SDBERR(99)
  
  node_refr.GoTop();
  while ( nodeptr = node_refr.GetNext() )
    switch ( ((LNode *)nodeptr)->PathLocate(skey,&pos,exact) ) 
    {
      case YES  :                                    ERROR 
      case AUTO : if ( exact )                       ERROR
                  if ( nodeptr = node_refr.GetNext() )
                  {
                    ((LNode *)nodeptr)->PathTop()->Cancel();
                    if ( ((LNode *)nodeptr)->PathNext() )
                                                     ERROR
                  }
                  LEAVESEQ
      default  : ;
    }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Modify - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

logical vinti :: Modify ( )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
BEGINSEQ
  node_attr.GoTop();
  while ( nodeptr = node_attr.GetNext() )
    if ( !nodeptr->Modify() )                        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Next

\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical vinti :: Next (int32 indx0 )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_refr.GoTop();
  while ( (nodeptr = node_refr.GetNext()) && nodeptr->IsPositioned() ) ;
  
  if ( !nodeptr )
  {  
    node_refr.GoBottom();
    nodeptr = node_refr.GetPrev();
  }
  if ( Next(nodeptr) )                               ERROR
  while ( --indx0 )
  {
    node_refr.GoBottom();
    nodeptr = node_refr.GetPrev();
    if ( Next(nodeptr) )                             ERROR
  }
  objid = ((bnode *)node_refr.GetHead())->get_objid();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i1


\param  nodeptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical vinti :: Next (node *nodeptr )
{
  logical                 term = NO;
BEGINSEQ
  while ( ((LNode *)nodeptr)->PathNext() && (nodeptr = node_refr.GetPrev()) ) ;
  
  if ( !nodeptr )                                    ERROR
    
  while ( nodeptr = node_refr.GetNext() )
  {
    ((LNode *)nodeptr)->PathTop()->Switch(AUTO);
    if ( ((LNode *)nodeptr)->PathNext() )            ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Position

\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical vinti :: Position (int32 indx0 )
{
  logical                 term = NO;
BEGINSEQ
  if ( indx0 < 0 )                                   ERROR

  if ( cur_index > indx0 )
  {
    if ( indx0 < cur_index/2 )
      if ( First() )                                 ERROR
  }
  else
  {
    if ( indx0 > LAST_INSTANCE/2 + cur_index/2 )
      if ( Last() )                                  ERROR
  }
  
  if ( cur_index == AUTO )
  {
    if ( First() )                                   ERROR
  }    
  
  if ( indx0 == cur_index )                          LEAVESEQ
  
  if ( cur_index > indx0 ? Previous( cur_index - indx0 )
                         : Next( indx0 - cur_index )      )
                                                     ERROR
  cur_index = indx0;
RECOVER
  cur_index = AUTO;
  term = YES;
ENDSEQ
  inst_index = cur_index;
  return(term);
}

/******************************************************************************/
/**
\brief  Previous

\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical vinti :: Previous (int32 indx0 )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  node_refr.GoTop();
  while ( (nodeptr = node_refr.GetNext()) && nodeptr->Exist() ) ;
  
  if ( !nodeptr )
  {
    node_refr.GoBottom();
    nodeptr = node_refr.GetPrev();
  }
  
  if ( Previous(nodeptr) )                           ERROR
  node_refr.GoBottom();
  nodeptr = node_refr.GetPrev();
  while ( --indx0 )
    if ( Previous(nodeptr) )                         ERROR

  objid = ((bnode *)node_refr.GetHead())->get_objid();

RECOVER
  cur_index = AUTO;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i1


\param  nodeptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical vinti :: Previous (node *nodeptr )
{
  logical                 term = NO;
BEGINSEQ
  while ( ((LNode *)nodeptr)->PathPrev() && (nodeptr = node_refr.GetPrev()) ) ;
  
  while ( nodeptr = node_refr.GetNext() )
  {
    ((LNode *)nodeptr)->PathTop()->Switch(AUTO);
    if ( ((LNode *)nodeptr)->PathPrev() )               ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvGenAttribute - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvGenAttribute"

logical vinti :: ProvGenAttribute ( )
{
  bnode                  *bnodeptr = NULL;
  logical                 term = NO;
  node_attr.GoTop();
  while ( bnodeptr = node_attr.GetNextBNode() )
    bnodeptr->get_bnodeinst()->ProvGenAttribute();
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void vinti :: Reset ( )
{

  inst_index = AUTO;

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

logical vinti :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
BEGINSEQ
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    if ( nodeptr->Save(switchopt,overwrite,refresh_opt) )                      
                                                     ERROR

  if ( switchopt )
    cur_index = AUTO;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Switch

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Switch"

logical vinti :: Switch ( )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
    if ( nodeptr->Switch(AUTO) )                      
      term = YES;

  cur_index = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  vinti - 



\param  op_node -
\param  dbstrdef - Structure definition
\param  instptr -
\param  crt_opt -
\param  operenv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "vinti"

                        vinti :: vinti (ACOperation *op_node, DBStructDef *dbstrdef, void *instptr, logical crt_opt, OperEnvironment *operenv )
                     : sinti (op_node,dbstrdef,instptr,crt_opt,operenv),
  cur_index(AUTO)
{

BEGINSEQ
  field_def = op_node->get_nodefield();
  struct_def = dbstrdef;
  
  if ( Init(el_view,NULL,struct_def,NULL) )           ERROR
  if ( struct_def->CreateViewNodes(op_node,this,iselarea,high_node,init_nodes) )
                                                      ERROR
  InitInit();
RECOVER


ENDSEQ

}

/******************************************************************************/
/**
\brief  ~vinti - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~vinti"

                        vinti :: ~vinti ( )
{

  Close();

}


