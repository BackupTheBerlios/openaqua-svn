/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACTopNode

\brief    


\date     $Date: 2006/08/30 13:09:03,53 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACTopNode"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sLACObject.hpp>
#include  <sStructAccess.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>
#include  <sACTopNode.hpp>


/******************************************************************************/
/**
\brief  ACTopNode - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  sysnode - 
\param  accopt - Access mode
\param  w_instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTopNode"

     ACTopNode :: ACTopNode (ACExtend *sysnode, PIACC accopt, char *w_instptr )
                     : ACNode(),
system_node(sysnode)
{

BEGINSEQ
  nodetype = NT_ACTopNode;
  if ( Open(accopt,w_instptr) )                         ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



\param  obhandle - Database Object handle
\param  dbfield_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTopNode"

     ACTopNode :: ACTopNode (ACObject *obhandle, DBFieldDef *dbfield_def )
                     : ACNode (obhandle,NULL,dbfield_def,NULL,PI_Write),
  system_node(NULL)
{

  nodetype = NT_ACTopNode;


}

/******************************************************************************/
/**
\brief  i1 - 



\param  topnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTopNode"

     ACTopNode :: ACTopNode (ACTopNode &topnode_ref )
                     : ACNode (topnode_ref),
  system_node(topnode_ref.get_system_node())
{

  if ( system_node )
    system_node->AddTopNode(this);
  else
    if ( topnode_ref.stscerr() )
      stsserr();

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

void *ACTopNode :: Add (int32 lindx0, logical global_add )
{
  char    *instptr = NULL;
  smcb    *smcbptr;

BEGINSEQ
  if ( system_node->SetAutoIdent(Bnodeinst,
                                 noderefp ? noderefp->get_refsakcb()->get_key_def() : (kcb *)NULL,
                                 GetGenOrderType()) == ERIC ) 
                                                     ERROR
  nodewrit = AUTO;
  if ( (smcbptr = GetKeySMCB()) && smcbptr->smcbsts.stscnof() && 
       noderefp && noderefp != noderefmain )
  {
    if ( system_node->IdentityAdd(Bnodeinst,(char *)noderefp->get_refsakcb()->GetKeyName(),YES,global_add) )
                                                     ERROR
  }
  else
    if ( system_node->Add(Bnodeinst,YES,YES,global_add) )   
                                                     ERROR
  nodecur = noderefp ? noderefp->GetRefCuri() :
                       nodeinst->GetIndex(AUTO);
  if ( noderefp && nodecur == AUTO )
    nodecur = noderefp->WSGetIndex(ExtractSortKey(NULL,nodeinst->get_iselarea(),NO),nodeinst->GetID(),YES);

  new_instance = system_node->get_extend_node()->IsNewInstance();
  instptr = ReserveInstance();
RECOVER
  nodecur  = AUTO;
  nodewrit = NO;
ENDSEQ
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

logical ACTopNode :: AddGenericRef (char *fldname )
{
  logical    siw;
  logical    term = NO;
BEGINSEQ
  siw = nodeinst->SetInWork(YES);
  if ( system_node->get_root_extend()->AddGenericRef(fldname,Bnodeinst) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  nodeinst->SetInWork(siw);
  return(term);
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

PIACC ACTopNode :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC     oldmode = PI_undefined;

BEGINSEQ
  if ( Check(NO) )                                    ERROR
  if ( accopt > object_ref->get_access_mode() )       SDBERR(72)

  if ( system_node->Upgrade(NULL,accopt) )            ERROR

  if ( !(oldmode = ACNode::ChangeMode(accopt,chkopt)) ) ERROR

RECOVER

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

logical ACTopNode :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
BEGINSEQ
  if ( stscerr() )                                   ERROR

  if ( autoini && !system_node )  // temporary extent
    InitNode();

  if ( ACNode::Check(autoini,acccheck) )              ERROR

RECOVER
  ResetOnError();
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

logical ACTopNode :: Close ( )
{

  return(system_node->Close());

}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACTopNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACTopNode(*this) ) )         SDBERR(95)
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
\brief  CreateInti - 



\return intiptr - 

\param  nodeptr - 
\param  strdefptr - 
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *ACTopNode :: CreateInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical init_nodes )
{
  inti      *intiptr;
  logical    term = NO;
BEGINSEQ
  if ( !(intiptr = system_node->CreateInti(nodeptr,strdefptr,instptr,init_nodes)) )
                                                       ERROR
//  SetCurrentInti(intiptr);

RECOVER

ENDSEQ
  return(intiptr);
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

logical ACTopNode :: DelGenericRef (char *fldname )
{
  logical    siw;
  logical    term = NO;
BEGINSEQ
  siw = nodeinst->SetInWork(YES);
  if ( system_node->get_root_extend()->DelGenericRef(fldname,Bnodeinst) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  nodeinst->SetInWork(siw);
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code

\param  lindx0 - 
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACTopNode :: Delete (int32 lindx0, logical chknode, logical del_dep, logical del_inst )
{
  int16     talevel = 0;
  DB_Event  intevent= DB_undefined;
  int64     object_id = 0;
  EB_Number entnr(objid);
  logical   term = NO;

BEGINSEQ
  if ( !Get(lindx0,chknode) )          
  {
    if ( SDBERROR ) // für loeschen ueber selektion
      if ( nodedel(lindx0,chknode) )                 ERROR
                                                     LEAVESEQ
  }
  
  object_id = entnr.FromPIF(object_ref->GetLocalACObject()->get_pif()).get_ebsnum();
  
  if ( chknode )
  {
    if ( CheckUpdateSet(NO) )                        ERROR
    if ( (nodefield->get_owning() || (del_dep && nodefield->get_depend())) && !nodewrit )
                                                     SDBERR(28)
  }
  nodeinst->Save(NO,NO);   // war YES,NO bis 7.10.97

  talevel = StartTA();
  if ( GenerateEvent(DBP_Remove) )                   ERROR
    
  if ( system_node->Delete(Bnodeinst,YES,del_dep,YES,del_inst) )
                                                     ERROR
  ResetInstance();
  intevent = DBO_Removed;
RECOVER
  intevent = DBO_NotRemoved;
  RecoverSelection(object_id);
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  GenerateEvent(intevent);
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

logical ACTopNode :: DeleteIndex (logical gen_events )
{
  int16     talevel = 0;
  DB_Event  intevent= DB_undefined;
  logical   term = NO;

BEGINSEQ
  if ( gen_events )
    if ( GenerateEvent(DBP_Remove) )                 ERROR
  
  if ( system_node )
    term = system_node->DeleteIndex(Bnodeinst,nodeinst->GetID());
  
  if ( LNode::DeleteIndex(NO) )                        ERROR

  intevent = DBO_Removed;

RECOVER
  intevent = DBO_NotRemoved;
  term = YES;
ENDSEQ
  if ( gen_events )
    GenerateEvent(intevent);
  nodecur = AUTO;
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteIndexEntry - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIndexEntry"

logical ACTopNode :: DeleteIndexEntry ( )
{
 

  return( LNode::DeleteIndexEntry() );


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

int32 ACTopNode :: GetCount (logical chknode )
{
  int32                   count = 0;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
    
  if ( noderefp )            
  {
    if ( (count = noderefp->WSGetCount()) < 0 )      ERROR
  }
  else
  {
    if ( system_node )
      count = system_node->GetCount();
    if ( count == ERIC )
      count = nodeinst->GetCount();
  }

RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetExtentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentNode"

node *ACTopNode :: GetExtentNode ( )
{

  return(system_node ? system_node->GetExtentNode() : NULL );

}

/******************************************************************************/
/**
\brief  GetGlobalID - 



\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

EB_Number ACTopNode :: GetGlobalID ( )
{

  return ( system_node->GetGlobalID(Bnodeinst) );

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

EB_Number ACTopNode :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number               ebsnum;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( stscusr2() )
    indx0 = AUTO;
  
  if ( (ebsnum = LNode::GetID(indx0,NO,pif_opt)).IsEmpty() )
  {
    if ( indx0 == AUTO )
      indx0 = nodecur;
    if ( indx0 == AUTO )                             ERROR
    ebsnum = nodeinst->GetID(indx0);
  }
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

EB_Number ACTopNode :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

  return ( stscusr2() ? GetID(AUTO,chknode,pif_opt)
                      : ACNode::GetID(keyptr,chknode,pif_opt)  );

}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACTopNode :: GetMainBase ( )
{

  return ( system_node->GetMainBase() );

}

/******************************************************************************/
/**
\brief  GetSystemNode - 



\return sysnode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemNode"

ACExtend *ACTopNode :: GetSystemNode ( )
{

  return(system_node);

}

/******************************************************************************/
/**
\brief  InitNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitNode"

logical ACTopNode :: InitNode ( )
{
  char                   *extnames;
  logical                 term = NO;
BEGINSEQ
  if ( !(extnames = object_ref->GetDictionary()->CreateTempExtent(nodefield)) )
                                                     ERROR
  if ( !(system_node = object_ref->GetLocalACObject()->ProvideACExtend(extnames,PI_Write,YES)) )
                                                     ERROR
  
  nodefield = system_node->get_extend_node()->get_nodefield();

  if ( Open(nodeacc) )                               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsTempExtent - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTempExtent"

logical ACTopNode :: IsTempExtent ( )
{
  logical                 cond = NO;
BEGINSEQ
  if ( stscerr() )                                   LEAVESEQ
  if ( !system_node || nodefield->get_log_reference() )
    cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  accopt - Access mode
\param  w_instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACTopNode :: Open (PIACC accopt, char *w_instptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !system_node )                                LEAVESEQ

  ACNode::Open(system_node->get_extend_node()->get_object_ref(),NULL,
               system_node->get_extend_node()->get_nodefield(),NULL,accopt);
               
  if ( !strcmp(system_node->GetExtendName(),"VOID") )
  {
// wir müssen noch sichern, daß für void-PIs keine sensitiven Attribute modifiziert werden!! das macht z.z. nur die Anwendung
//    nodeacc = PI_Read; für Barto 23.1.02
    stssusr2();
  }
   
  if ( system_node->NotCreated() )  // 26.11.2002 haben wir hier nur stserr gesetzt
  {
    stsserr();                                       SDBERR(349)
  }
  
  noderefmain = system_node->get_extend_node()->GetMainRef();
  SetOrderRef(noderefmain);
  noderefl = system_node->get_extend_node()->get_noderefl();

//  if ( InitIsel(system_node->GetMainBase(),NULL) ) ERROR
  if ( nodefield->get_weak_typed() && w_instptr )     SDBERR(99)
  if ( InitInti(nodefield->GetDBStruct(GetDictionary()),w_instptr) )  ERROR
  stssfil();
  
  id_key = nodefield->GetDBStruct()->smcbidky;
  system_node->AddTopNode(this);
  
// wenn der MainIndex temporär ist, ist er noch nicht gesetzt. 
// Wir machen für diesen Fall hier ein SetOrder 23.10.2001 (aufgefallen beim Lesen XML über temp. Indizes)
  if ( !noderefmain && system_node->get_extend_node()->get_noderefmain() 
                    && system_node->get_extend_node()->get_noderefmain()->IsTemporary() )
    SetOrder((char *)system_node->get_extend_node()->get_noderefmain()->get_refsakcb()->GetKeyName(),UNDEF,NULL);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical ACTopNode :: Refresh ( )
{

  return(system_node->Refresh());

}

/******************************************************************************/
/**
\brief  Release - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

logical ACTopNode :: Release ( )
{
  logical                 cond = NO;
BEGINSEQ
  if ( use_count <= 1 && !origin && system_node && 
       !system_node->IsTemporary() )
    if ( system_node && !system_node->ReleaseNode(this) )
                                                     LEAVESEQ
  cond = ACNode::Release(NULL);

ENDSEQ
  return(cond);
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

logical ACTopNode :: Save (logical switchopt, logical overwrite, logical chknode )
{
  int16     talevel = 0;
  logical   siw;
  char     *keyptr;
  logical   term    = NO;

BEGINSEQ
  if ( chknode && Check(NO) )                        ERROR
  
  if ( TARequired() )                            
    talevel = StartTA();

  if ( stscsav() || stscmod() )
  {
    if ( SaveInitInst() )                            ERROR
    if ( Bnodeinst->SaveGenAttr(switchopt,overwrite) )
                                                     ERROR
    if ( system_node->Save(Bnodeinst) )              ERROR
    
    if ( UpdateCurIndex(!switchopt,overwrite) )      ERROR
  }
  else
    if ( ACNode::Save(switchopt,overwrite,NO) )      ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);

}

/******************************************************************************/
/**
\brief  ~ACTopNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACTopNode"

     ACTopNode :: ~ACTopNode ( )
{

  Switch(AUTO);
  noderefl = NULL;

  if ( nodeidnt == NODE_ID )
    ACNode::Close(); 
  
  if ( system_node )
    system_node->RemoveTopNode(this);

}


