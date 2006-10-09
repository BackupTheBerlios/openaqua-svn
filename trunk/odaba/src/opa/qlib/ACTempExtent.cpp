/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACTempExtent

\brief    


\date     $Date: 2006/08/30 23:44:01,33 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACTempExtent"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDictionary.hpp>
#include  <sLACObject.hpp>
#include  <sbnode.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <sACTempExtent.hpp>


/******************************************************************************/
/**
\brief  ACTempExtent - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  bnode_ptr - 
\param  extname_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTempExtent"

     ACTempExtent :: ACTempExtent (bnode *bnode_ptr, char *extname_w )
                     : ACReference(),
  system_node(NULL),
  current_id(0)
{
  CTX_DBBase     *highctx = NULL;
  DBExtend       *dbfield_ptr;
BEGINSEQ
  nodetype = NT_ACTempExtent;
  if ( !bnode_ptr )                                    SDBERR(99)
    
  owning_ref = YES;
  if ( !(extname_w = bnode_ptr->GetDictionary()->CreateTempExtent(bnode_ptr->get_nodefield(),extname_w)) )
                                                     ERROR
  if ( !(dbfield_ptr = bnode_ptr->GetDictionary()->GetExtendDef(extname_w)) )
                                                     SDBERR(99)
  dbfield_ptr->set_owning(NO);
  system_node = new ACExtend(bnode_ptr,extname_w);     SDBCERR
  
  if ( bnode_ptr->get_nodenode() )
    highctx = bnode_ptr->get_nodenode()->get_nodeinst()->GetContext();
  if ( bnode::Open(bnode_ptr->GetObjectHandle(),bnode_ptr,dbfield_ptr,highctx,PI_Write) )
                                                     ERROR
  if ( !strcmp(system_node->GetExtendName(),"VOID") )
    stssusr2();
   
  if ( system_node->NotCreated() )
    stsserr();
  else
  {
    if ( InitReference() )                           ERROR
    if ( noderefl->stscold() )
      SetupIndex();
  }
  if ( InitInti(nodefield->GetDBStruct(GetDictionary()),NULL) )  ERROR
  stssfil();
  
  nodenode = bnode_ptr->get_nodenode();
  highnod  = bnode_ptr->get_highnod();
  system_node->AddTopNode(this);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTempExtent"

     ACTempExtent :: ACTempExtent ( )
                     : ACReference (),
  system_node(NULL),
  current_id(0)
{

  nodetype = NT_ACTempExtent;

}

/******************************************************************************/
/**
\brief  i2 - 



\param  actempref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTempExtent"

     ACTempExtent :: ACTempExtent (ACTempExtent &actempref )
                     : ACReference (actempref),
  system_node(actempref.get_system_node()),
  current_id(actempref.get_current_id())
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

void *ACTempExtent :: Add (int32 lindx0, logical global_add )
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
    if ( system_node->Add(Bnodeinst,NO,YES,global_add) )      
                                                   ERROR
  if ( AddID(lindx0) )                             ERROR
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

logical ACTempExtent :: AddGenericRef (char *fldname )
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

PIACC ACTempExtent :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC     oldmode = PI_undefined;

BEGINSEQ
  if ( Check(NO) )                                    ERROR
  if ( accopt > object_ref->get_access_mode() )       SDBERR(72)

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

logical ACTempExtent :: Check (logical autoini, logical acccheck )
{
  EB_Number       id;
  logical         term = NO;
BEGINSEQ
  if ( stscerr() )                                   ERROR

  if ( ACNode::Check(autoini,acccheck) )             ERROR

  if ( nodenode )
  {
    if ( nodenode->IsPositioned() )
      id = nodenode->GetID(AUTO);
    if ( !current_id.IsEmpty(object_ref->GetLocalACObject()->get_pif()) && id != current_id )
      noderefl->DeleteReference();   
    current_id = id;
    if ( current_id.IsEmpty(object_ref->GetLocalACObject()->get_pif()) )
                                                     ERROR
  }
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

logical ACTempExtent :: Close ( )
{
  int32                indx = 1;
  Switch(AUTO);

  if ( !origin )
  {
    if ( system_node )
      system_node->RemoveTopNode(this);
    
    ACReference::Close();
    
    if ( system_node->IsLocal() )
      delete system_node;
  }
  system_node = NULL;

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

node *ACTempExtent :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACTempExtent(*this) ) )       SDBERR(95)
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

logical ACTempExtent :: DelGenericRef (char *fldname )
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

logical ACTempExtent :: Delete (int32 lindx0, logical chknode, logical del_dep, logical del_inst )
{
  char            extlock;
  DB_Event        intevent= DB_undefined;
  int16           talevel = 0;
  int32           curi;
  logical         term    = NO;
BEGINSEQ
  if ( (extlock = CheckDel(lindx0,chknode)) == ERIC )ERROR
  nodeinst->Save(NO,NO);  
  
  talevel = StartTA();
  if ( GenerateEvent(DBP_Remove) )                   ERROR
       
  if ( stscmod() )
    nodeinst->Save(NO,NO);  
  
  curi = nodecur;
  if ( DeleteID() )                                  ERROR
  nodecur = curi;
  
  nodeinst->Cancel();
  intevent = DBO_Removed;
  ResetInstance();

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
\brief  GetExtentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentNode"

node *ACTempExtent :: GetExtentNode ( )
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

EB_Number ACTempExtent :: GetGlobalID ( )
{

  return ( system_node->GetGlobalID(Bnodeinst) );


}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACTempExtent :: GetMainBase ( )
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

ACExtend *ACTempExtent :: GetSystemNode ( )
{

  return(system_node);

}

/******************************************************************************/
/**
\brief  InitReference - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitReference"

logical ACTempExtent :: InitReference ( )
{
  EB_Number   *ext_ref      = NULL;
  int16        mbnumber     = 0;
  logical      term         = NO;
  int16        index        = 0;
BEGINSEQ
  TypeKey    tkey(nodefield->fmcbname,nodefield->fmcbnsid);
  if ( !(ext_ref = object_ref->GetLocalACObject()->GetExtendRef(tkey)) )
  {
    SDBCERR
    if ( object_ref->get_access_mode() == PI_Read )  SDBERR(68)
    if ( !(ext_ref = object_ref->GetLocalACObject()->AddExtendRef((DBExtend *)nodefield)) )
                                                     ERROR
  }
  if ( ACReference::InitReference() )                ERROR
  if ( ext_ref )
    int_extref = *ext_ref;  
  
  if ( (mbnumber = ((DBExtend *)nodefield)->GetMainBase(object_ref)) == AUTO )       
                                                     SDBERR(169)
  if ( noderefl->Setup(&int_extref,0,mbnumber,nodeacc,YES) )  
                                                     ERROR
RECOVER
  int_extref = 0;
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

logical ACTempExtent :: IsTempExtent ( )
{

  return ( stscerr() ? NO : YES );

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

logical ACTempExtent :: Save (logical switchopt, logical overwrite, logical chknode )
{
  int16     talevel = 0;
  logical   siw;
  char     *keyptr;
  logical   term    = NO;

BEGINSEQ
  if ( chknode && Check(NO) )                        ERROR
  if ( !stscmod() && nodecur == AUTO )               LEAVESEQ

  talevel = StartTA();
  if ( stscsav() || stscmod() )
  {
    if ( Bnodeinst->SaveGenAttr(switchopt,overwrite) )
                                                     ERROR
    if ( system_node->Save(Bnodeinst) )              ERROR
    if ( UpdateID() )                                ERROR
    
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
\brief  ~ACTempExtent - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACTempExtent"

     ACTempExtent :: ~ACTempExtent ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


