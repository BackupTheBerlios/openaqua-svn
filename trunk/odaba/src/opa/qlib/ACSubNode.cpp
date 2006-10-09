/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACSubNode

\brief    


\date     $Date: 2006/08/30 18:10:40,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACSubNode"

#include  <popa7.h>
#ifndef   DPA_isel_HPP
#define   DPA_isel_HPP
#include  <sisel.hpp>
#include  <sDPA.h>
#endif
#include  <sACObject.hpp>
#include  <sACProperty.hpp>
#include  <sACStructure.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sStructAccess.hpp>
#include  <sacb.hpp>
#include  <snode.hpp>
#include  <sACSubNode.hpp>


/******************************************************************************/
/**
\brief  ACSubNode - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  extoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACSubNode"

     ACSubNode :: ACSubNode (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt )
                     : ACProperty()
{

  Open(nodeptr,dbfield_ptr,highctx,extoff,accopt);


}

/******************************************************************************/
/**
\brief  i1 - 



\param  subnoderef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACSubNode"

     ACSubNode :: ACSubNode (ACSubNode &subnoderef )
                     : ACProperty (subnoderef)
{



}

/******************************************************************************/
/**
\brief  i2 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACSubNode"

     ACSubNode :: ACSubNode ( )
                     : ACProperty ()
{



}

/******************************************************************************/
/**
\brief  ChangeMode - 



\return accopt - Access mode

\param  accopt - Access mode
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC ACSubNode :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC     oldmode = PI_undefined;

BEGINSEQ
  return(LNode::ChangeMode(accopt,chkopt));
// 21.5.04: Sonst bleiben lokale instancen gesperrt, wenn wir im UpdateMode arbeiten (s. Konstruktor)
/*
  if ( chkopt && Check(NO,NO) )                      ERROR
  

  if ( chkopt != YES )  
    if ( !nodefield->get_update() && accopt == PI_Update && nodetype != NT_ACGenericAttr)
      accopt = PI_Write;
  
  if ( !(oldmode = LNode::ChangeMode(accopt,chkopt)) ) 
                                                      ERROR
*/
RECOVER
//  if ( oldmode != PI_undefined && chkopt )
//  {
//    ChangeMode(oldmode,NO);
//    oldmode = PI_undefined;
//  }
ENDSEQ
//  return(oldmode);

}

/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACSubNode :: Close ( )
{

  ACProperty::Close();

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

node *ACSubNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACSubNode(*this) ) )         SDBERR(95)
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
\brief  Open - 




\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  extoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

void ACSubNode :: Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt )
{

  ACProperty::Open(Bnodeptr->get_object_ref(),nodeptr,dbfield_ptr,highctx,accopt);

  nodeoff += extoff;

//  if ( dbfield_ptr->get_cluster_opt() &&
//       !nodeptr->get_nodefield()->get_cluster_opt() )
//    nodeptr->get_nodeinst()->set_cluster_crt();
    


}

/******************************************************************************/
/**
\brief  ~ACSubNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACSubNode"

     ACSubNode :: ~ACSubNode ( )
{


  if ( nodeidnt == NODE_ID )
    Close();

}


