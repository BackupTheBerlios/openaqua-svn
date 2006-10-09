/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACReference

\brief    


\date     $Date: 2006/08/30 18:13:03,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACReference"

#include  <popa7.h>
#include  <sACNode.hpp>
#include  <sACProperty.hpp>
#include  <sACStructure.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sStructAccess.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>
#include  <sACReference.hpp>


/******************************************************************************/
/**
\brief  ACReference - 



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
#define    MOD_ID  "ACReference"

     ACReference :: ACReference (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt )
                     : ACSubNode(),
owning_ref(YES)
{

  Open(nodeptr,dbfield_ptr,highctx,extoff,accopt);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  acpnodeptr - 
\param  refopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACReference"

     ACReference :: ACReference (ACProperty *acpnodeptr, logical refopt )
                     : ACSubNode(acpnodeptr->get_nodenode(),
          acpnodeptr->get_nodefield(),
          NULL,
          acpnodeptr->get_nodeoff(),
          acpnodeptr->get_nodeacc()),
owning_ref(YES)
{

BEGINSEQ
  nodetype = NT_ACReference;
  
  if ( !refopt )
  {
    SetOrderRef(acpnodeptr->get_noderefp());
    noderefl    = acpnodeptr->get_noderefl();
    noderefmain = acpnodeptr->get_noderefmain();
    owning_ref = NO;
  }
  else
    if ( InitReference() )                        ERROR

  if ( InitIsel(UNDEF,NULL) )                     ERROR
  
  SetupNode(YES,NO);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i2 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACReference"

     ACReference :: ACReference ( )
                     : ACSubNode (),
  owning_ref(NO)
{

  nodetype = NT_ACReference;


}

/******************************************************************************/
/**
\brief  i3 - 



\param  acrefref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACReference"

     ACReference :: ACReference (ACReference &acrefref )
                     : ACSubNode (acrefref),
  owning_ref(NO)
{



}

/******************************************************************************/
/**
\brief  Add - 



\return instptr - 

\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACReference :: Add (int32 lindx0, logical global_add )
{
  logical   extlock = noderefl->stsclck();
  int16     talevel = 0;
  char     *instptr;
BEGINSEQ
  if ( !extlock && LockSet(NO) )                     ERROR
  if ( noderefl->SetAutoIdent(GetKeyInstance(nodeinst,NULL)) == ERIC ) 
                                                     ERROR
  talevel = StartTA();

  if ( nodefield->get_cluster_opt() )
    Bnodeinst->SetClusterNumber(Bnodenode->get_bnodeinst()->GetClusterNumber());

  nodewrit = AUTO;
  if ( !nodefield->get_owning() || !nodefield->get_create() )
                                                     SDBERR(170)
  if ( nodeinst->Add() )                             ERROR
  
  if ( lindx0 == AUTO )
    lindx0 = noderefp->WSGetCount();
  if ( AddID(lindx0) )                               ERROR
  instptr = ReserveInstance();
RECOVER
  if ( nodeinst->IsPositioned() )
  {
    int saveerr = SDBERROR;
    nodeinst->Delete(NULL,NO);
    SDBISET(saveerr);
  }
  ResetInstance();
  instptr = NULL;

ENDSEQ
  if ( UnlockSet(extlock,NO) )
    instptr = NULL;
  if ( talevel )
    if ( StopTA(!instptr) ) 
      instptr = NULL;
  return(instptr);

}

/******************************************************************************/
/**
\brief  AddGenericRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGenericRef"

logical ACReference :: AddGenericRef (char *fldname )
{
  logical      term = NO;
BEGINSEQ
  if ( nodewrit == 255 || !nodeinst->get_struct_def()->smcbsts.stscusr1() )  // keine generischen Schlüssel
                                                     LEAVESEQ

  if ( noderefl->AddGenericRef(fldname,nodeinst,GetID(AUTO)) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical ACReference :: AddReference (node *srcenode, int32 lindx0 )
{
  int16                   talevel = 0;
  logical                 term = NO;
BEGINSEQ
  talevel = StartTA();
  
  if ( GenerateEvent(DBP_Insert) )                   ERROR
  if ( ACNode::AddReference(srcenode,lindx0) )       ERROR
  GenerateEvent(DBO_Inserted);

RECOVER
  GenerateEvent(DBO_NotInserted);
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDel - 



\return term - Termination code

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDel"

char ACReference :: CheckDel (int32 lindx0, logical chknode )
{
  char        extlock = YES;
  logical     del_inst = NO;
BEGINSEQ
  if ( (extlock = CheckDelSet(chknode)) == ERIC )    ERROR
  
  if ( !Get(lindx0,NO) )  
  {
    if ( lindx0 == AUTO )                            ERROR
    nodedel(lindx0,NO);                              ERROR
  }

  if ( chknode )
  {
    del_inst = nodefield->get_owning() || nodefield->get_depend();
    if ( nodenode && ((LNode *)nodenode)->CheckDelInstance(objid,noderefl->GetID(),del_inst) )
                                                     SDBERR(528)
    if ( CheckUpdateSet(NO) )                        ERROR
    if ( del_inst )
      if ( (!stscusr3() || !((isel *)nodeinst)->IsInWork()) && !nodewrit ) 
                                                     SDBERR(28)
  }
RECOVER
  UnlockSet(extlock,NO);
  extlock = ERIC;
ENDSEQ
  return(extlock);
}

/******************************************************************************/
/**
\brief  CheckDelSet - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDelSet"

char ACReference :: CheckDelSet (logical chknode )
{
  char        extlock = YES;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  extlock = noderefl ? noderefl->stsclck() : NO;
                             
  if ( !extlock )
  {
    switch ( LockSet(NO) )
    {
      case 0 : break;
      case 1 : ERROR
      case 2 : extlock = YES;
    }
  }
  
/*  fragwuerdig  
  if ( chknode )
    if ( CheckUpdateSet(NO) )                        ERROR
*/
RECOVER
  UnlockSet(extlock,NO);
  extlock = ERIC;
ENDSEQ
  return(extlock);
}

/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACReference :: Close ( )
{

  Switch(AUTO);
  
  ACSubNode::Close();
  
  if ( owning_ref )
    RemoveReference();
  else 
    noderefl = NULL;
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

node *ACReference :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACReference(*this) ) )        SDBERR(95)
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
\brief  DelGenericRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelGenericRef"

logical ACReference :: DelGenericRef (char *fldname )
{
  logical     term = NO;
BEGINSEQ
  if ( !nodeinst->get_struct_def()->smcbsts.stscusr1() )  // keine generischen Schlüssel
                                                     LEAVESEQ
  term = noderefl->DelGenericRef(fldname,Bnodeinst,GetID(AUTO));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code

\param  indx0 - Position in collection
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACReference :: Delete (int32 indx0, logical chknode, logical del_dep, logical del_inst )
{
  char      extlock; 
  DB_Event  intevent= DB_undefined;
  int16     talevel = 0;
  logical   term = NO;

BEGINSEQ
  if ( (extlock = CheckDel(indx0,chknode)) == ERIC ) ERROR
  nodeinst->Save(YES,NO);  
  
  talevel = StartTA();
  if ( GenerateEvent(DBP_Remove) )                   ERROR
  
  if ( DeleteInstance(nodeinst,NULL,NO,del_dep,YES,del_inst) )ERROR
  ResetInstance();

  intevent = DBO_Removed;

RECOVER
  intevent = DBO_NotRemoved;
  term = YES;
ENDSEQ
  if ( UnlockSet(extlock,NO) )
    term = YES;
  if ( talevel )
    term = StopTA(term);
  GenerateEvent(intevent);
  return(term);

}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACReference :: GetMainBase ( )
{

  return ( nodenode->get_nodeinst() ? Bnodenode->get_bnodeinst()->GetMBNumber() : 0);

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

void ACReference :: Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt )
{

  ACSubNode::Open(nodeptr,dbfield_ptr,highctx,extoff,accopt);
  nodetype = NT_ACReference;
//  noderefp->refprvc(IDB_INSL);


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

logical ACReference :: Save (logical switchopt, logical overwrite, logical chknode )
{
  int16     talevel  = 0;
  logical   term     = NO;

BEGINSEQ
  if ( !stscfil() )                                 LEAVESEQ
  if ( chknode && Check(NO) )                       ERROR
  
  if ( TARequired() )                            
    talevel = StartTA();
  
  if ( (stscsav() || stscmod()) && nodecur != AUTO )
  {
    if ( SaveInitInst() )                            ERROR
    if ( get_bnodeinst()->SaveGenAttr(switchopt,overwrite) )
                                                     ERROR
    if ( UpdateID() )                                ERROR
  }

  if ( ACProperty::Save(switchopt,overwrite,NO) )    ERROR

RECOVER
  term = YES;

ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);


}

/******************************************************************************/
/**
\brief  ~ACReference - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACReference"

     ACReference :: ~ACReference ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


