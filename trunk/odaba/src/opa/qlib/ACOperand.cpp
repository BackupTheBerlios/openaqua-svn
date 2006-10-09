/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACOperand

\brief    Operand node
          Operand  nodes  are  used  for  operations  representing  the operands
          passed  to the operation  (Select, Product, ...).  The operand node it
          set  in the  query node  (op_base) as  value. The expression is set in
          the source node.

\date     $Date: 2006/04/03 15:40:08,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOperand"

#include  <popa7.h>
#include  <sACOperation.hpp>
#include  <sOPBase.hpp>
#include  <sbinti.hpp>
#include  <snode.hpp>
#include  <sACOperand.hpp>


/******************************************************************************/
/**
\brief  ACOperand - 



\param  op_base - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOperand"

                        ACOperand :: ACOperand (OPBase *op_base )
                     : bnode (),
  op_base(op_base)
{

  nodetype = NT_ACOperand;

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

logical ACOperand :: Cancel (logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(NO,NO) )                     ERROR
  if ( !stscfil() )                                  LEAVESEQ

  if ( nodefield->fmcbrlev = R_REFR )
    op_base->SourceNode()->Cancel();
  ResetNode(YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  op_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACOperand :: Open (ACOperation *op_node )
{
  PropertyHandle     *source    = op_base->Source()->GetValue();
  binti              *binti_ptr = (binti *)op_node->get_nodeinst();
  logical             term      = NO;
BEGINSEQ
  if ( is_opened )
  {    
    if ( bnode::Open(op_node->get_object_ref(),op_node,op_base->GetDescription(),NULL,op_node->GetMode()) )
                                                     ERROR
    if ( nodefield->fmcbrlev == R_REFR)         // reference
    {
      binti_ptr->SetPI(this,NULL);
      binti_ptr->get_node_refr().AddTail(this);
    }
    else
    {
      if ( !(nodeinst = new binti(this,NULL,NULL,
                           binti_ptr->get_iselarea()+fldfmcb->fmcbposn,NO)) )
                                                     SDBERR(95)
                                                     SDBCERR
      binti_ptr->get_node_attr().AddTail(this);
    }
  }
  
  if ( source->IsValid() )
  {
    source->Refresh();
    if ( source->GetMode() < nodeacc )
      ChangeMode(source->GetMode());
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical ACOperand :: Read ( )
{
  logical         term = NO;
BEGINSEQ
  if ( is_collection )                               LEAVESEQ
    
  if ( !stscfil() )
  {
    op_base->Source()->Execute();
    op_base->SetValue(op_base->SourceNode());
    stssfil();
    if ( nodeacc > PI_Read )
      nodewrit = op_base->SourceNode()->IsWrite();
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Store - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical ACOperand :: Store ( )
{
  logical         term = NO;
BEGINSEQ
  if ( nodeacc <= PI_Read )                          SDBERR(28)
  
  if ( stscmod() || stscsav() )
    if ( nodefield->fmcbrlev != R_REFR )
      op_base->StoreValue();

  stsrmod();
  stsrsav();
RECOVER
  term = YES;
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

logical ACOperand :: Switch (int32 indx0 )
{
  logical                 term = NO;
BEGINSEQ
  if ( !stscfil() )                                  LEAVESEQ 

  if ( nodefield->fmcbrlev = R_REFR )
    op_base->SourceNode()->Switch(AUTO);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOperand - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOperand"

                        ACOperand :: ~ACOperand ( )
{



}


