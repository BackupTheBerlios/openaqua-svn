/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    cinti

\brief    


\date     $Date: 2006/07/16 12:27:18,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cinti"

#include  <popa7.h>
#include  <sCNode.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <snode.hpp>
#include  <scinti.hpp>


/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical cinti :: Cancel ( )
{
  logical                 term = NO;
  ResetNodes();
  Reset();
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeMode - 


\return term - Termination code

\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

logical cinti :: ChangeMode (PIACC accopt )
{
  nodelist  cursor(node_base);
  node     *nodeptr;
  logical   term = NO;
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    Cnodeptr->ChangeMode_intern(NO,accopt);
  
  (cursor = node_rshp).GoTop();
  while ( nodeptr = cursor.GetNext() )
    Cnodeptr->ChangeMode_intern(NO,accopt); 

  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    Cnodeptr->ChangeMode_intern(NO,accopt);

  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    Cnodeptr->ChangeMode_intern(NO,accopt);

  (cursor = node_attr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    Cnodeptr->ChangeMode_intern(NO,accopt);

  return(term);
}

/******************************************************************************/
/**
\brief  CheckAddReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAddReference"

logical cinti :: CheckAddReference ( )
{
  nodelist  cursor(node_base);
  node     *nodeptr;
  logical   term = NO;
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    ((cinti *)nodeptr->get_nodeinst())->CheckAddReference();
  
  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( nodeptr->IsInitInstance() )
    {
      Cnodeptr->SetupCNode(0,YES);
      nodeptr->Add(AUTO);
    }

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

logical cinti :: Close ( )
{

  GenerateEvent(DBO_Close);
  
  binti::Close();

  return(NO);
}

/******************************************************************************/
/**
\brief  GetVersion - 


\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 cinti :: GetVersion ( )
{

  return ( version );

}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical cinti :: IsPositioned ( )
{

  return( inst_index >= 0 ? YES : NO );

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void cinti :: Reset ( )
{

  binti::Reset();

  inst_index = AUTO;
  version    = CUR_VERSION;

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

logical cinti :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{
  nodelist  cursor(node_base);
  logical   keymod  = YES;
  logical   term    = NO;  
  node     *nodeptr;
BEGINSEQ
  stsrini();
  
  if ( stscmod() || stscsav() )
    if ( StructureEvents(DBP_Store) )                ERROR
  
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( nodeptr->SaveNode(switchopt,overwrite) )    ERROR
  
  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( nodeptr->SaveNode(switchopt,overwrite) )    ERROR

  (cursor = node_rshp).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( nodeptr->SaveNode(switchopt,overwrite) )    ERROR

  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
  {
    Bnodeptr->set_nodewrit(((bnode *)nodeptr->get_nodenode())->get_nodewrit() ? YES : NO);
    if ( nodeptr->SaveNode(switchopt,overwrite) )    ERROR
  }
  inti::Save(switchopt,overwrite,refresh_opt);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupInst - 


\return term - Termination code

\param  lindx0 - 
\param  obj_id - 
\param  version_nr - Internal version number
\param  active - Active property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInst"

logical cinti :: SetupInst (int32 lindx0, int64 obj_id, uint16 version_nr, logical active )
{
  nodelist  cursor(node_base);
  node     *nodeptr;
  logical   term   = NO;
BEGINSEQ
  inst_index = lindx0;
  version    = version_nr;
  objid      = obj_id;
  
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
  {
    if ( Cnodeptr->SetupCNode(0,NO,active) )
      term = YES;
    else
      if ( active )  
        Cnodeptr->Event(DBO_Read);   // RecursiveEvents(DBO_Read); hat SetupCNode schon gemacht
  }

  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
  {
    if ( active )  
      Cnodeptr->Event(DBO_Read);
    if ( Cnodeptr->SetupCNode(0,NO,active) )
      term = YES;
  }
  
  if ( SetupSubNodes(active) )                       ERROR

  stssfil();
  stssold();
  
  if ( active )
  {
    (cursor = node_attr).GoTop();
    while ( nodeptr = cursor.GetNext() )
    {
      Cnodeptr->Event(DBO_Read);
      Cnodeptr->get_bnodeinst()->RecursiveEvents(DBO_Read);
    }
  
    (cursor = node_genattr).GoTop();
    while ( nodeptr = cursor.GetNext() )
    {
      Cnodeptr->Event(DBO_Read);
      Cnodeptr->get_bnodeinst()->RecursiveEvents(DBO_Read);
      Bnodeptr->set_nodewrit(((CNode *)nodeptr->get_nodenode())->get_nodewrit() ? YES : NO);
    }
  
    if ( context )
    {
      GenerateEvent(DBO_Read);
      context->get_resource()->CheckEvent(context,YES);
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupNewInst - 


\return term - Termination code

\param  lindx0 - 
\param  obj_id - 
\param  new_inst - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNewInst"

logical cinti :: SetupNewInst (int32 lindx0, int64 obj_id, logical new_inst, uint16 version_nr )
{
  nodelist  cursor(node_base);
  logical   siw;
  node     *nodeptr;
  logical   term = NO;
BEGINSEQ
  inst_index = lindx0;
  version    = version_nr;
  objid      = obj_id;
  
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Cnodeptr->SetupCNode(0,NO,YES) )             ERROR
  
  siw = SetInWork(YES);
  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Cnodeptr->SetupCNode(0,YES,YES) )                   
      term = YES;
  SetInWork(siw);
  
//  if ( !new_inst )  Parameter ist immer YES
    stssold();    // wer macht diese Dinge fuer shared basis ?    
  
  if ( term )                                        ERROR
  CheckAddReference();
  if ( SetupSubNodes(YES) )                          ERROR
  
  if ( new_inst ) // stand früher nach SetInWork. Subnodes sollten aber schon gesetzt sein. 15.6.01
    binti::after_add();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupSubNodes - 


\return term - Termination code

\param  active - Active property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSubNodes"

logical cinti :: SetupSubNodes (logical active )
{
  nodelist  cursor(node_base);
  node     *nodeptr;
  logical   term = NO;
  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Cnodeptr->SetupCNode(AUTO,YES,active) )
      term = YES;
  
  (cursor = node_rshp).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Cnodeptr->SetupCNode(AUTO,YES,active) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  cinti - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  nodeptr - 
\param  strdefptr - 
\param  instptr - 
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cinti"

     cinti :: cinti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical crt_opt )
                     : binti (nodeptr,NULL,strdefptr,instptr,crt_opt),
  version(CUR_VERSION)
{



}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cinti"

     cinti :: cinti ( )
                     : binti (),
  version(CUR_VERSION)
{



}

/******************************************************************************/
/**
\brief  ~cinti - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cinti"

     cinti :: ~cinti ( )
{

  Close();  



}


