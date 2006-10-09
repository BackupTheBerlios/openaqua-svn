/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACRelationship

\brief    


\date     $Date: 2006/08/30 18:15:22,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACRelationship"

#include  <popa7.h>
#ifndef   DLL_ACRelationship_HPP
#define   DLL_ACRelationship_HPP
#include  <sACRelationship.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_PropertyHandle_HPP
#define   DLL_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDLL.h>
#endif
#ifndef   GSRT_PropertyHandle_HPP
#define   GSRT_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sGSRT.h>
#endif
#include  <sACExtend.hpp>
#include  <sACObject.hpp>
#include  <sACProperty.hpp>
#include  <sACRelationship.hpp>
#include  <sACStructure.hpp>
#include  <sACTopNode.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sLACObject.hpp>
#include  <sSDB_Structure.hpp>
#include  <sbinti.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <snodelist.hpp>
#include  <sref.hpp>
#include  <sACRelationship.hpp>


/******************************************************************************/
/**
\brief  ACRelationship - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  sysnode - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  extoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACRelationship"

     ACRelationship :: ACRelationship (node *nodeptr, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt )
                     : ACReference(),
  system_node(sysnode),
  derived_nodes(NULL)
{

  Open(nodeptr,dbfield_ptr,highctx,extoff,accopt);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  sysnode - 
\param  dbfield_ptr - Property definition
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACRelationship"

     ACRelationship :: ACRelationship (ACExtend *sysnode, DBFieldDef *dbfield_ptr, PIACC accopt )
                     : ACReference (NULL,dbfield_ptr,NULL,UNDEF,accopt),
  system_node(sysnode),
  derived_nodes(NULL)
{

  nodetype = NT_ACRelationship;


}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACRelationship"

     ACRelationship :: ACRelationship ( )
                     : ACReference (),
  system_node(NULL),
  derived_nodes(NULL)
{

  nodetype = NT_ACRelationship;


}

/******************************************************************************/
/**
\brief  i2 - 



\param  acrelref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACRelationship"

     ACRelationship :: ACRelationship (ACRelationship &acrelref )
                     : ACReference (acrelref),
  system_node(acrelref.get_system_node()),
  derived_nodes(acrelref.get_derived_nodes())
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

void *ACRelationship :: Add (int32 lindx0, logical global_add )
{
  isel            *iselptr = (isel *)nodenode->get_nodeinst();
  logical          siw     = AUTO;
  logical          term    = NO;
  int16            talevel = 0;
  logical          extlock = noderefl->stsclck();
  void            *instptr = NULL;
BEGINSEQ
  if ( !extlock && LockSet(NO) )                     ERROR
  talevel = StartTA();

  siw = iselptr->SetInWork(YES);
  
  if ( instptr = ProvideInstance(lindx0,global_add) ) 
  {
    if ( !stscres() )                  // instance wurde neu zur Referenz hinzugefügt
      term = AddInverse(global_add);
  }
  else
    term = YES;
  
  iselptr->SetInWork(siw);
  
  if ( term )                                        ERROR
RECOVER
  int saveerr = SDBERROR;
  if ( nodeinst )
    nodeinst->ResetNodes();
  ResetInstance();
  SDBISET(saveerr);

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

logical ACRelationship :: AddGenericRef (char *fldname )
{
  ACRelationship         *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( nodeinst->get_struct_def()->smcbsts.stscusr1() )  // generischen Schlüssel
  {  
    if ( !(nodeptr = GetInverse(NO)) )
    {
      if ( ACReference::AddGenericRef(fldname) )       ERROR
    }
    else 
      nodeptr->ReleaseField();
  }
   
  if ( system_node )
  {
    if ( !nodeinst->SetInWork(YES) ) // noch nicht erledigt
    {
      term = system_node->AddGenericRef(fldname,Bnodeinst);
      nodeinst->SetInWork(NO);
      if ( term )                                    ERROR
    }
  }
  else
    if ( Bnodeinst->AddGenericRef(fldname) )         ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddInstance - 



\return instptr - 

\param  bintiptr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInstance"

void *ACRelationship :: AddInstance (binti *bintiptr, int32 lindx0 )
{
  void                   *instptr = NULL;
BEGINSEQ
// hier fehlt noch die Pflege der BaseExtents!!
  
  if ( !(instptr = ACReference::AddInstance(bintiptr,lindx0)) )
                                                     ERROR
  if ( AddInverse(NO) )                              ERROR

RECOVER
  if ( nodeinst )
    nodeinst->ResetNodes();
  ResetInstance();

  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  AddInvDeriGenRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInvDeriGenRef"

logical ACRelationship :: AddInvDeriGenRef (char *fldname )
{
  int32           curidx = nodecur;
  logical         exist  = nodeinst && nodeinst->IsPositioned();
  ref            *curref;
  ACRelationship *nodeptr = NULL;
  smcb           *smcbptr;
  int32           count;
  logical         term = NO;

BEGINSEQ
  curref = noderefp;
  if ( noderefp && noderefp != noderefmain )
    SetMainRef();
    
  DisableContext(); // das müssen wir tun, da sonst ungewollte Modifikationen auftreten - durch Read-Contexte, die generische Attribute anlegen
  for (count=GetCount()-1; count>=0; count-- )
  {
    if ( Get(count) && (nodeptr = GetInverseI()) )
    {
      if ( !((isel *)nodeinst)->IsInWork() )
      {
        if ( nodeptr->IsVariableType() )
          if ( nodeptr->SetType(nodenode->GetCurrentType()) )
                                                     ERROR
        smcbptr = nodeptr->get_nodefield()->fmcbsmcb;
      
if ( nodefield->get_weak_typed() &&
     Bnodeinst->get_weak_typed_offset() != nodeptr->get_nodefield()->fmcbposn )
SDBSET(777)   // 8.11.2004
        smcbptr->CopyInstance(nodeinst->get_iselarea()+nodeptr->get_nodefield()->fmcbposn,
                              smcbptr,
                              nodenode->get_nodeinst()->get_iselarea(),
                              REPL_GUID,UNDEF);
        if ( AddGenericRef(fldname) )                  ERROR
      }    
      nodeptr->ReleaseField();
      nodeptr = NULL;
    }
  }
  SDBCERR
RECOVER
  term = YES;
ENDSEQ
  if ( curref )
    SetOrderRef(curref);
  ResetIntern(curidx,exist);
  if ( nodeptr )
    nodeptr->ReleaseField();
  EnableContext();
  return(term);
}

/******************************************************************************/
/**
\brief  AddInversGenRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInversGenRef"

logical ACRelationship :: AddInversGenRef (char *fldname )
{
  ACRelationship   *nodeptr = NULL;
  isel             *iselptr = (isel *)nodenode->get_nodeinst();
  ref              *curref;
  int32              count;
  int32              curidx;
  logical           exist = NO;
  logical           term = NO;
BEGINSEQ
  if ( !nodenode->get_nodeinst()->get_struct_def()->smcbsts.stscusr1() )  // keine generischen Schlüssel
  {
    if ( !GenInvDeriRef() )                             LEAVESEQ
  }

  if ( nodeptr = GetInverse(NO) )
  {
    if ( nodeptr->get_nodefield()->fmcbrlev == R_DIRECT )      // abgeleitete Structures
    {
      nodeptr->ReleaseField();
      nodeptr = NULL;
      term = AddInvDeriGenRef(fldname);
    }
    else
    {
      if ( nodeptr->get_noderefl()->get_generic() )
      {
        curidx  = nodecur;
        curref = noderefp;
        if ( noderefp && noderefp != noderefmain )
          SetMainRef();
        exist   = nodeinst && nodeinst->IsPositioned();
    
        if ( nodeptr->IsVariableType() )
          term = nodeptr->SetType(nodenode->GetCurrentType());
      
        for (count=GetCount()-1; count>= 0 && !term; count-- )
          if ( Get(count) )
          {
            nodeptr->Check(YES,NO);            
            term = nodeptr->get_noderefl()->AddGenericRef(fldname,iselptr,iselptr->GetID());
          }
        SDBCERR
      
        if ( curref )
          SetOrderRef(curref);
        ResetIntern(curidx,exist);
        if ( term )                                  SDBERR(152)
      }
    }
  }
  else
  {
    if ( SDBERROR == 74 )                            ERROR
    term = AddInvDeriGenRef(fldname);     // erforderlich, falls bei GetInverse FieldReserved()
  }

RECOVER
  term = YES;
ENDSEQ
  if ( nodeptr )
    nodeptr->ReleaseField();
  return(term);
}

/******************************************************************************/
/**
\brief  AddInverse - 



\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInverse"

logical ACRelationship :: AddInverse (logical global_add )
{
  ACRelationship  *nodeptr = NULL;
  binti           *bintiptr = Bnodenode->get_bnodeinst();
  node            *collnode;
  logical          siw = NO;
  char            *save_inst;
  logical          term = NO;
BEGINSEQ
  if ( (!nodeinst->SetInWork(NO) || nodeinst->GetID() == bintiptr->GetID())
       && (nodeptr = GetInverse(NO)) )
  {
    // geändert am 27.2.2006 ( --> Delete() )
    if ( nodeptr->IsVariableType() && 
         !nodeptr->get_nodefield()->get_sec_reference() )
    {
      collnode = *GetHighPIPointer();
      if ( nodeptr->SetType(collnode->GetCurrentType()) )
                                                     ERROR
      bintiptr = ((bnode *)collnode)->get_bnodeinst();
    }
    
    nodeptr->Switch(AUTO);
    save_inst = bintiptr->GetStructAccess()->get_instarea();
    memcpy(save_inst,bintiptr->get_iselarea(),bintiptr->get_struct_def()->GetLength());
    bintiptr->GetOldInst(bintiptr->get_iselarea());
    
    if ( nodeptr->GenerateEvent(DBP_Insert) )         ERROR
    if ( !(term = nodeptr->LNode::AddID(bintiptr,bintiptr->GetID())) )
      if ( nodeptr->get_system_node() )
      {
        siw = bintiptr->SetInWork(NO);
        term = nodeptr->get_system_node()->Add(bintiptr,NO,NO,global_add);
        bintiptr->SetInWork(siw);
      }
    
    if ( term ) // hier versuchen wir eine kleine Autokorrektur (27.11.99)
    { 
      if ( bintiptr->GetID() == nodeptr->GetID(nodeptr->ExtractSortKey(NULL,bintiptr->get_iselarea(),NO)) )
      {
        SDBRESET
        term = NO;
      }
    }

    if ( !term )
      nodeptr->GenerateEvent(DBO_Inserted);
                                                  
    nodeptr->Switch(AUTO);
    nodeptr->ReleaseField();
    nodeptr = NULL;
    memcpy(bintiptr->get_iselarea(),save_inst,bintiptr->get_struct_def()->GetLength());
    
    if ( term )                                      SDBERR(152)
    Save(NO,NO,NO);
  }
  else
    if ( SDBERROR == 74 )                            ERROR
RECOVER
  if ( nodeptr )
    nodeptr->GenerateEvent(DBO_NotInserted);
  term = YES;
ENDSEQ
  if ( nodeptr )
    nodeptr->ReleaseField();
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

logical ACRelationship :: AddReference (node *srcenode, int32 lindx0 )
{
  int16                   talevel = 0;
  logical                 term = NO;
BEGINSEQ
  talevel = StartTA();
  
  if ( GenerateEvent(DBP_Insert) )                   ERROR
  if ( ACNode::AddReference(srcenode,lindx0) )       ERROR
  
  if ( AddInverse() )                                ERROR
  GenerateEvent(DBO_Inserted);

// das ist zu wenig, wenn die relationship Extentbasiert ist. 
// In diesem Fall muß dafür gesorgt werden, dass die Instanz entlang der Hierarchie in allen Basismengen hinzugefügt wird.
// es können sowiso nur instanzen aus Basismengen hinzugefügt werden.
// am besten ist es, ein entsprechendes ACExtend::AddReference zu machen oder AddReference nur für Referenzen und temporäre Mengen zuzulassen.
RECOVER
  GenerateEvent(DBO_NotInserted);
  if ( nodeinst )
    nodeinst->ResetNodes();
  ResetInstance();

  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
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

PIACC ACRelationship :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC     oldmode = PI_undefined;

BEGINSEQ
  if ( chkopt && Check(NO,NO) )                       ERROR

  if ( noderefp && !nodefield->get_owning() )
  {
    if ( system_node )   
    {
      if ( system_node->Upgrade(NULL,accopt) )        ERROR
    }
    else
      if ( nodefield->get_extend() && *nodefield->get_extend() != '*' )
        if ( !(system_node = object_ref->GetLocalACObject()->ProvideACExtend(
                  (char *)nodefield->get_extend(),nodeacc,this,nodeacc > PI_Read)) ) 
                                                      ERROR
  }
  if ( !(oldmode = ACSubNode::ChangeMode(accopt,chkopt)) ) 
                                                      ERROR
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

logical ACRelationship :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
BEGINSEQ
  if ( ACReference::Check(autoini,acccheck) )        ERROR

  if ( autoini && !system_node && 
       nodeacc > PI_Read && nodefield->get_extend() &&
       nodefield->get_weak_typed() && *nodefield->get_extend() == '*' )
    SetType_intern(nodefield->fmcbtype);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBCollection - 



\return term - Termination code

\param  nresult - 
\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBCollection"

logical ACRelationship :: CheckDBCollection (NString &nresult, CheckOptions check_opts )
{
  logical                 term = NO;
  term = LNode::CheckDBCollection(nresult,check_opts);

  if ( check_opts.inverse_references )
    if ( CheckDBInverseRefs(nresult,check_opts.repair_all) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBInverseRefs - 



\return term - Termination code

\param  nresult - 
\param  repair - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBInverseRefs"

logical ACRelationship :: CheckDBInverseRefs (NString &nresult, logical repair )
{
  int32               indx0 = 0;
  ACRelationship     *nodeptr = (ACRelationship *)GetInverse(NO);
  int64               obj_id = Bnodenode->get_objid();
  logical             err;
  logical             term = NO;
BEGINSEQ
  if ( !nodeptr )                                    LEAVESEQ
  
  while ( Get(indx0++) ) 
  {
    if ( nodeptr = (ACRelationship *)GetInverse(NO) )
    {
      nodeptr->Check(YES,NO);
      if ( !nodeptr->IsVariableType() )
        if ( nodeptr->Locate(obj_id,NO) )   // inverse does not exist
        {
          if ( repair )
            err = nodeptr->AddID((binti *)nodenode->get_nodeinst(),obj_id);
      
          nresult += "\n      missing inverse reference in";
          nresult += ' ';
          nresult += prop_path;
          nresult += ':';
          nresult += (int32)obj_id;
          nresult += " - ";
          nresult += (char*)(repair && !err ? (char*)" (corrected)" : (char*)" (not corrected)");
          term = YES;
        }
    }
  }
  nodeptr->ReleaseField();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckInverse - 



\return term - 

\param  srce_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckInverse"

logical ACRelationship :: CheckInverse (node *srce_node )
{
  ACRelationship    *sinverse = NULL;
  logical            term = NO;
BEGINSEQ
// function is called only, when copying within the same database
// and same data type
  if ( !system_node )                                LEAVESEQ
  
  if ( !(sinverse = ((ACRelationship *)srce_node)->GetInverse(NO)) )
                                                     LEAVESEQ
  if ( sinverse->GetID(0).IsEmpty(NO) )              LEAVESEQ
  
  if ( !system_node->GetGlobalID((binti *)srce_node->get_nodeinst()).IsEmpty(NO) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  if (sinverse) 
    sinverse->ReleaseField();
  return(term);
}

/******************************************************************************/
/**
\brief  CheckOrder - 



\return term - Termination code

\param  root_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckOrder"

logical ACRelationship :: CheckOrder (logical root_opt )
{
  ACNode                 *base_coll;
  smcb                   *ksmcbptr;
  smcb                   *basksmcb;
  ACExtend               *sysnode;
  char                   *keyname = NULL;
  logical                 set_order = NO;
  logical                 term = NO;

BEGINSEQ
  if ( !system_node )                                LEAVESEQ
  sysnode = root_opt ? system_node->get_root_extend() : system_node;
  if ( !sysnode->IsLocal() )                         LEAVESEQ
    
  base_coll = sysnode->get_extend_node();
  if ( ksmcbptr = GetSortKeySMCB() )
  {
    set_order = YES;
    if ( !(basksmcb = base_coll->GetSortKeySMCB()) )
    {
      set_order = NO;
      if ( !(basksmcb = base_coll->GetKeySMCB()) )  SDBERR(99)
    }
    if ( !memcmp(basksmcb->smcbname,ksmcbptr->smcbname,ID_SIZE) )
                                                     LEAVESEQ
    if ( set_order && base_coll->get_noderefl()->GetReference(ksmcbptr->smcbname) )
      keyname = ksmcbptr->smcbname;
  }
  
  if ( set_order )
    base_coll->SetOrder(keyname,UNDEF,NULL);

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

logical ACRelationship :: Close ( )
{
  PropertyHandle     *pibptr;
  int32                indx = 1;
  Switch(AUTO);

  if ( !origin )
  {
    if ( derived_nodes )
    {
/*      
      while ( pibptr = derived_nodes->GetEntry(indx++) )
        delete pibptr->get_nodeptr();
      delete derived_nodes;
*/
      while ( pibptr = derived_nodes->RemoveTail() )
        delete pibptr;
      delete derived_nodes;
    }
    ACReference::Close();
    
    if ( system_node->IsLocal() )
      delete system_node;
  }
  else
    ACReference::Close();
  
  derived_nodes = NULL;
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

node *ACRelationship :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACRelationship(*this) ) )     SDBERR(95)
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

logical ACRelationship :: DelGenericRef (char *fldname )
{
  logical                 term = NO;
BEGINSEQ
  if ( ACReference::DelGenericRef(fldname) )         ERROR

  if ( system_node && !nodeinst->SetInWork(YES) ) // noch nicht erledigt
  {
    term = system_node->get_root_extend()->DelGenericRef(fldname,Bnodeinst);
    nodeinst->SetInWork(NO);
    if ( term )                                      ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DelInvDeriGenRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelInvDeriGenRef"

logical ACRelationship :: DelInvDeriGenRef (char *fldname )
{
  int32            curidx = nodecur;
  logical         exist  = nodeinst && nodeinst->IsPositioned();
  ref            *curref;
  ACRelationship *nodeptr = NULL;
  int32            count;
  logical         term = NO;

BEGINSEQ
  curref = noderefp;
  if ( noderefp && noderefp != noderefmain )
    SetMainRef();
    
  for (count=GetCount()-1; count>=0; count-- )
  {
    if ( Get(count) && (nodeptr = GetInverseI()) )
    {
      if ( DelGenericRef(fldname) )                  ERROR
      
      nodeptr->ReleaseField();
      nodeptr = NULL;
    }
  }
  SDBCERR
RECOVER
  term = YES;
ENDSEQ
  if ( curref )
    SetOrderRef(curref);
  ResetIntern(curidx,exist);
  if ( nodeptr )
    nodeptr->ReleaseField();
  return(term);
}

/******************************************************************************/
/**
\brief  DelInversGenRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelInversGenRef"

logical ACRelationship :: DelInversGenRef (char *fldname )
{
  ACRelationship   *nodeptr = NULL;
  isel             *iselptr = (isel *)nodenode->get_nodeinst();
  ref              *curref;
  int32              count;
  int32              curidx;
  logical           exist = NO;
  logical           term = NO;
BEGINSEQ
  if ( !nodenode->get_nodeinst()->get_struct_def()->smcbsts.stscusr1() )  // keine generischen Schlüssel
  {
    if ( !GenInvDeriRef() )                             LEAVESEQ
  }
  
  if ( nodeptr = GetInverse(NO) )
  {
    if ( nodeptr->get_nodefield()->fmcbrlev == R_DIRECT )      // abgeleitete Structures
    {
      nodeptr->ReleaseField();
      nodeptr = NULL;
      term = DelInvDeriGenRef(fldname);
    }
    else
    {
      if ( nodeptr->get_noderefl()->get_generic() )
      {
        curidx  = nodecur;
        curref = noderefp;
        if ( noderefp && noderefp != noderefmain )
          SetMainRef();
        exist   = nodeinst && nodeinst->IsPositioned();
    
        if ( nodeptr->IsVariableType() )
          term = nodeptr->SetType(nodenode->GetCurrentType());
      
        for (count=GetCount()-1; count>= 0 && !term; count-- )
          if ( Get(count) )
          {
            nodeptr->Check(YES,NO);            
            term = nodeptr->get_noderefl()->DelGenericRef(fldname,iselptr,iselptr->GetID());
          }
        SDBCERR
      
        if ( curref )
          SetOrderRef(curref);
        ResetIntern(curidx,exist);
        if ( term )                                  SDBERR(152)
      }
    }
  }
  else
  {
    if ( SDBERROR == 74 )                            ERROR
    term = DelInvDeriGenRef(fldname);     // erforderlich, falls bei GetInverse FieldReserved()
  }

RECOVER
  term = YES;
ENDSEQ
  if ( nodeptr )
    nodeptr->ReleaseField();
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

logical ACRelationship :: Delete (int32 lindx0, logical chknode, logical del_dep, logical del_inst )
{
  logical         delopt;
  ACRelationship *nodeptr = NULL;
  binti          *bintiptr;
  DB_Event        intevent= DB_undefined;
  int64           object_id = 0;
  EB_Number       entnr(objid);
  logical         siw;
  char            extlock;
  int16           talevel = 0;
  int32            curi = 0;
  logical         del_inv = NO;
  logical         term    = NO;

BEGINSEQ
  if ( (extlock = CheckDel(lindx0,chknode)) == ERIC ) ERROR
    
  bintiptr = Bnodenode->get_bnodeinst();
  delopt = del_inst || nodefield->get_owning() 
                    || (del_dep && nodefield->get_depend());

  nodeinst->Save(NO,NO);  // war bisher NO (16.4.97), wieder NO (16.9.97)
  object_id = entnr.FromPIF(object_ref->GetLocalACObject()->get_pif()).get_ebsnum();
  
  talevel = StartTA();
  if ( GenerateEvent(DBP_Remove) )                   ERROR
  
  if ( IsBaseCollection() )
    DeleteDerived(delopt);
    
  if ( delopt && DeleteDepend(delopt) )             ERROR
  if ( nodeptr = GetInverse(NO) )
  {
    if ( chknode && nodeptr->get_nodefield()->fmcbrlev == R_DIRECT )
                                                     SDBERR(156)
    // seit 27.2.2006 machen wir das nur noch für primäre collections.
    // secundäre weak-typed referenzen nehmen immer die "kleinste" gespeicherte Instance.
    // sonst ist nicht entscheidbar, welche Instanz in der Referenz landet.
    if ( nodeptr->IsVariableType() && 
         !nodeptr->get_nodefield()->get_sec_reference() )
      bintiptr = ((bnode *)*GetHighPIPointer())->get_bnodeinst();
    
    del_inv = nodeptr->get_nodefield()->get_owning() || nodeptr->get_nodefield()->get_depend();
    if ( delopt && chknode && del_inv ) 
    {           
      if ( !nodeptr->LocateID(bintiptr) )
        SDBERR(163)
      else
        del_inv = NO;  // wenn keine instance da, muss auch keine gelöscht werden
    }      
    if ( !((isel *)bintiptr)->IsInWork() )
      if ( CheckDelInstance(bintiptr->get_objid(),nodeptr->get_noderefl()->GetID(),del_inv) )
                                                     SDBERR(528)
    
    if ( !nodeptr->LocateID(bintiptr) )
      if ( nodeptr->GenerateEvent(DBP_Remove) )      ERROR
    nodeptr->Save(NO,NO,NO);
    if ( nodeptr->DeleteID(bintiptr) )               ERROR
      
    nodeptr->ReleaseField();
    nodeptr->GenerateEvent(DBO_Removed);
    nodeptr = NULL;
  }
  else
    if ( SDBERROR == 74 )                            ERROR
  
  if ( ((isel *)nodeinst)->IsInWork() )
  {
    del_dep = NO;
    del_inst = NO;
  }
  
  if ( system_node && 
       ( (del_dep && nodefield->get_depend()) ||
         (del_inst && !nodefield->get_owning()) ) )
  {
    if ( stscmod() )
      nodeinst->Save(NO,NO); 
     
    siw = nodeinst->SetInWork(YES);
    term = Bnodeinst->DeleteRelationships(system_node->GetExtendName(),system_node->IsRoot(),YES,del_dep); // 16.9.98 nach DeleteID können Remove/Delete Events für untergeordnete nicht mehr arbeiten, da übergeordnete Instance nicht eingestellt
    nodeinst->SetInWork(siw);
    if ( term )                                      ERROR
    
    curi = nodecur;
    if ( DeleteID(Bnodeinst) )                       ERROR
    nodecur = curi;
    if ( system_node->IsLocal() )
    {
      if ( system_node->Delete(Bnodeinst) )          ERROR
    }
    else
      if ( system_node->get_root_extend()->Delete(Bnodeinst) )
                                                     ERROR
  }
  else
    if ( DeleteInstance(nodeinst,NULL,NO,del_dep,YES,del_inst) )
                                                     ERROR
  
  intevent = DBO_Removed;
  ResetInstance();

RECOVER
  if ( nodeptr )
  {
    nodeptr->ReleaseField();
    nodeptr->GenerateEvent(DBO_NotRemoved);
  }
  RecoverSelection(object_id);
  intevent = DBO_NotRemoved;
  term = YES;
ENDSEQ
  if ( UnlockSet(extlock,NO) )
    term = YES;
  if ( talevel )
    term = StopTA(term);
  if ( curi )
    nodecur = AUTO;
  GenerateEvent(intevent);
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteDepend - Delete instances in derived collections



\return term - Termination code

\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteDepend"

logical ACRelationship :: DeleteDepend (logical del_dep )
{
  nodelist  cursor(Bnodeinst->get_node_rshp());
  bnode    *bnode_ptr;
  logical   term = NO;
BEGINSEQ
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    if ( bnode_ptr->get_nodefield()->get_owning() || 
         (del_dep && bnode_ptr->get_nodefield()->get_depend()) )
    {
      if ( bnode_ptr->CheckDelEmpty() )              ERROR
      if ( bnode_ptr->DeleteSet(YES,del_dep) )       ERROR
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteDerived - 



\return term - Termination code

\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteDerived"

logical ACRelationship :: DeleteDerived (logical del_opt )
{
  PropertyHandle  *pibptr;
  node            *bi_node;
  char            *skey;
  ACRelationship  *acrelptr;
  logical          siw;
  logical          siwi;
  EB_Number        entnr;
  char             key[512];
  int32             indx = 1;
  int32             indx0= 0;
  logical          inv_ref = NO;
  logical          get = NO;
  logical          term = NO;
BEGINSEQ
  if ( !derived_nodes )                                 LEAVESEQ
  
  siw = nodeinst->SetInWork(YES);
  
  derived_nodes->GoTop();
  while ( pibptr = derived_nodes->GetNext() )
    if ( (acrelptr = (ACRelationship *)pibptr->get_nodeptr())->IsValid() )
    {
      inv_ref = acrelptr->get_nodefield()->get_inverse() ? YES : NO;
        
      get = NO;
      if ( !(skey = acrelptr->ExtractSortKey(key,nodeinst->get_iselarea())) )
      {
        get = YES;
        skey = acrelptr->ExtractKey(key,nodeinst->get_iselarea());
      }
      
      if ( !del_opt && inv_ref ) 
      {
        // see comments in Docu (deutch)
        bi_node = acrelptr->get_nodenode();     // inverse for sub-collection (derived collection)
        indx0 = 0;
        bi_node->ToTop();
        while ( bi_node->Get(indx0++) )
        {
          entnr = acrelptr->get_system_node()->GetBaseInstID();
          if ( entnr == nodenode->GetID(AUTO) )
          {
            if ( (get && acrelptr->Get(skey)) || !acrelptr->LocateKey(skey,YES) )
            {
              siwi = bi_node->get_nodeinst()->SetInWork(YES);  // sonst gibts Verklemmungen ... 24.8.2004
              if ( acrelptr->Delete(AUTO) )
                term = YES;
              bi_node->get_nodeinst()->SetInWork(siwi);
            }
            else term = YES;
          }
        }
      }
      else if ( !inv_ref )
      {
        if ( ((get && acrelptr->Get(skey)) || !acrelptr->LocateKey(skey,YES)) )
        {
          if ( acrelptr->Delete(AUTO) )
            term = YES;
        }
        else term = YES;
      }
    }

  nodeinst->SetInWork(siw);
ENDSEQ
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

logical ACRelationship :: DeleteIndex (logical gen_events )
{
  ACRelationship *nodeptr = NULL;
  DB_Event        intevent= DB_undefined;
  char            extlock;
  int16           talevel = 0;
  int32           curi    = 0;
  logical         term    = NO;

BEGINSEQ
  if ( gen_events )
    if ( GenerateEvent(DBP_Remove) )                 ERROR
  
  if ( IsBaseCollection() )
    DeleteDerived(NO);
  if ( nodeptr = GetInverse(NO) )
  {
    if ( !nodeptr->LocateID(Bnodenode->get_bnodeinst()) )
      if ( gen_events )
        if ( nodeptr->GenerateEvent(DBP_Remove) )      ERROR
    nodeptr->Save(NO,NO,NO);
    if ( nodeptr->DeleteID(Bnodenode->get_bnodeinst()) )
                                                     ERROR
    nodeptr->ReleaseField();
    nodeptr->GenerateEvent(DBO_Removed);
    nodeptr = NULL;
  }
  if ( LNode::DeleteIndex(NO) )                      ERROR
  intevent = DBO_Removed;
RECOVER
  if ( nodeptr )
  {
    nodeptr->ReleaseField();
    if ( gen_events )
      nodeptr->GenerateEvent(DBO_NotRemoved);
  }
  intevent = DBO_NotRemoved;
  term = YES;
ENDSEQ
  if ( UnlockSet(extlock,NO) )
    term = YES;
  if ( talevel )
    term = StopTA(term);
  if ( curi )
    nodecur = AUTO;
  if ( gen_events )
    GenerateEvent(intevent);
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteInvDeri - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteInvDeri"

logical ACRelationship :: DeleteInvDeri (char *extnames )
{
  ACRelationship  *nodeptr = NULL;
  char            *extnamept;
  int32             indx0 = 0;
  logical          term = NO;
  indx0 = GetCount();
  while ( indx0 && Get(--indx0) )
  {
    if ( (nodeptr = GetInverseI()) && 
         (extnamept = nodeptr->get_nodefield()->GetExtendName()) && 
         !strcmp(extnames,extnamept)                                 )
    {
      nodeptr->ReleaseField();
      nodeptr = NULL;
      if ( get_system_node()->get_root_extend()->Delete(Bnodeinst) )
        term = YES;
    }
    
    if ( nodeptr )
      nodeptr->ReleaseField();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteInverse - 



\return term - Termination code

\param  extnames - Extent name
\param  bintiptr - 
\param  is_root - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteInverse"

logical ACRelationship :: DeleteInverse (char *extnames, binti *bintiptr, logical is_root, logical del_dep )
{
  ACRelationship  *nodeptr   = NULL;
  char            *extnamept = NULL;
  int32             indx0    = 0; 
  char              extlock  = UNDEF;
  logical           term     = NO;
BEGINSEQ
  if ( !extnames || !*extnames )                     LEAVESEQ
    
  if ( (nodeptr = GetInverse(NO,bintiptr)) ) 
  { 
    if ( nodeptr->get_nodefield()->fmcbrlev == R_DIRECT )
      term = DeleteInvDeri(extnames);
    else
      if ( extnamept = nodeptr->get_nodefield()->GetExtendName() )  
        if ( !strcmp(extnames,extnamept) ||
             (!strcmp(extnamept,"*") && is_root) )
        { 
          nodeptr->ReleaseField();
          nodeptr = NULL;
          if ( (extlock = CheckDelSet(YES)) == ERIC )
            term = YES;
          else
          {
            term = DeleteSet(YES,del_dep);
            if ( UnlockSet(extlock,NO) )
              term = YES;
          }
        }
  }
  else
  {
    if ( SDBERROR == 74 )                            ERROR
    term = DeleteInvDeri(extnames);
  }

RECOVER
  term = YES;
ENDSEQ
  if ( nodeptr )
    nodeptr->ReleaseField();
  return(term);
}

/******************************************************************************/
/**
\brief  GenInvDeriRef - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenInvDeriRef"

logical ACRelationship :: GenInvDeriRef ( )
{
  fmcb                   *fielddef;
  logical                 cond = NO;
BEGINSEQ
  if ( !nodefield->get_inverse_name() || stscerr() ) LEAVESEQ
  
  if ( !(fielddef = nodefield->get_inverse()) )
  {
    object_ref->GetDictionary()->ProvideStructDef(nodefield->fmcbtype);
    if ( !(fielddef = nodefield->get_inverse()) )    LEAVESEQ
  }
  
  if ( fielddef->fmcbrlev == R_REFR )                LEAVESEQ
  
  // das könnte noch verbessert werden, da nicht jede Spezialisierung gepflegt werden muß.
  // nur ist das ein wenig kompliziert, wegen weiteren Ableitungen. Nur wenn alle möglichen 
  // Ableitungen nicht gepflegt werden müssen, können wir NO sagen!!
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetExtentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentNode"

node *ACRelationship :: GetExtentNode ( )
{
  node         *extend_node = NULL;
BEGINSEQ
  if ( !system_node )                                
  {
    if ( nodeacc > PI_Read )                         ERROR
    if ( ProvideExtendNode() )                       ERROR
  }
    
  if ( Exist() )
    system_node->PositionTop(YES);  
  
  extend_node = system_node->GetExtentNode();

RECOVER

ENDSEQ
  return(extend_node);
}

/******************************************************************************/
/**
\brief  GetGlobalID - 



\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

EB_Number ACRelationship :: GetGlobalID ( )
{
  EB_Number      entnr;
BEGINSEQ
  if ( !system_node )                                LEAVESEQ
    
  if ( system_node->get_root_extend()->IsLocal() )
    CheckOrder(YES);
  entnr = system_node->GetGlobalID(Bnodeinst);
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetInverse - 



\return acrelptr - 

\param  optimize - 
\param  bintiptr_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInverse"

ACRelationship *ACRelationship :: GetInverse (logical optimize, binti *bintiptr_w )
{
  ACRelationship  *acrelptr = NULL;
  int32            pos      = 0;
  DBFieldDef      *fielddef;
BEGINSEQ
  if ( !nodefield->get_inverse_name() || stscerr() ) LEAVESEQ
  
  if ( optimize && (fielddef = nodefield->get_inverse()) )
    if ( fielddef->fmcbrlev == R_REFR )              LEAVESEQ
  
  if ( !nodeinst || !stscfil() )
  {
    Check(YES,NO);
    if ( stscerr() )                                 LEAVESEQ
    if ( bintiptr_w )
      SetupNode_intern(bintiptr_w,NO,NO);
  }
  if ( !nodeinst )                                   SDBERR(99)
  fielddef = nodefield->get_inverse();
  
  if ( fielddef && !FieldReserved() )
  {
    switch ( fielddef->fmcbrlev )  
    {
      case R_REFR   : pos = nodefield->get_weak_typed() 
                            ? Bnodeinst->get_weak_typed_offset() + fielddef->fmcbposn
                            : fielddef->fmcbposn;
                      acrelptr = (ACRelationship *)*(node **)(nodeinst->get_iselarea()+pos);
                      acrelptr->Check(YES,NO);            
                      break;
      case R_DIRECT : acrelptr = (ACRelationship *)Bnodeinst->get_node_base().GetNode(fielddef->fmcbname,(CTX_Property *)NULL,NO);
                      break;
      default       :                                SDBERR(74)
    }
    if ( acrelptr )
      acrelptr->ReserveField();
  }

RECOVER
  acrelptr = NULL;

ENDSEQ
  return(acrelptr);
}

/******************************************************************************/
/**
\brief  GetInverseI - 



\return acrelptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInverseI"

ACRelationship *ACRelationship :: GetInverseI ( )
{
  ACRelationship *acrelptr = NULL;
BEGINSEQ
  if ( !nodefield->get_inverse_name() )      LEAVESEQ
  if ( !nodeinst )                           SDBERR(99)

/* 19.12.97 - muß nicht immer so sein, siehe Title->typdesc_ref->TypeDescription
  if ( nodefield->get_week_typed() && 
       strcmp(nodefield->fmcbtype,nodenode->GetType()) )
                                                     SDBERR(74)
*/
  
  if ( acrelptr = (ACRelationship *)Bnodeinst->get_node_base().GetNode((char *)nodefield->get_inverse_name(),(CTX_Property *)NULL,NO) )
    acrelptr->ReserveField();

RECOVER
  acrelptr = NULL;
ENDSEQ
  return(acrelptr);
}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACRelationship :: GetMainBase ( )
{

  return ( system_node ? system_node->GetMainBase() 
                       : nodenode->get_nodenode() ? ((ACProperty *)nodenode)->GetMainBase() 
                       :                            ((ACTopNode *)nodenode)->GetMainBase()  );

}

/******************************************************************************/
/**
\brief  GetSystemNode - 



\return sysnode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemNode"

ACExtend *ACRelationship :: GetSystemNode ( )
{

BEGINSEQ
  if ( system_node )                                 LEAVESEQ
  
  if ( Check(YES,NO) )                               ERROR
RECOVER

ENDSEQ
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

logical ACRelationship :: InitReference ( )
{
  logical  term = NO;
BEGINSEQ
  if ( ACProperty::InitReference() )                 ERROR
  
  if ( !system_node && nodefield->get_extend() )
    if ( !nodefield->get_weak_typed() || *nodefield->get_extend() != '*' )
      if ( nodeacc > PI_Read )
        if ( ProvideExtendNode() )                   ERROR
      


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsBaseCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBaseCollection"

logical ACRelationship :: IsBaseCollection ( )
{
  logical                 cond = YES;
  ACRelationship         *acrelptr;
  ACRelationship         *nodeptr;
  PropertyHandle         *pibptr;
BEGINSEQ
  if ( derived_nodes )                               LEAVESEQ

  if ( !nodefield->IsBaseCollection(GetDictionary(),nodenode->GetTypeKey()) )
                                                     ERROR
  
  if ( !(derived_nodes = new DLL(PropertyHandle)()) )
                                                     SDBERR(95)
// base collections via inverse references
  DLL(node) node_list(Bnodeinst->get_node_rshp());
  node_list.GoTop();
  while ( acrelptr = (ACRelationship *)node_list.GetNext() )
    if ( acrelptr->get_nodefield()->IsInverseBased(GetDictionary(),nodenode->GetTypeKey(),nodefield->fmcbname) )
    {
      if ( !(nodeptr = acrelptr->GetInverse(NO)) )   SDBERR(99)
      nodeptr->ReleaseField();
      if ( !(acrelptr = (ACRelationship *)nodeptr->CreateCopyNode()) ) 
                                                     ERROR
      acrelptr->Check(YES,NO);
      derived_nodes->AddTail( pibptr = new PropertyHandle() );
      pibptr->RegisterNode(acrelptr);
    }
  
// local base collections (in the same or in a base structure
  DLL(node) parent_list(((binti *)nodenode->get_nodeinst())->get_node_rshp());
  parent_list.GoTop();
  while ( acrelptr = (ACRelationship *)parent_list.GetNext() )
    if ( acrelptr->get_nodefield()->IsBased(GetDictionary(),nodenode->GetTypeKey(),nodefield->fmcbname) )
    {
      if ( !(acrelptr = (ACRelationship *)acrelptr->CreateCopyNode()) ) 
                                                     ERROR
      acrelptr->Check(YES,NO);
      derived_nodes->AddTail( pibptr = new PropertyHandle() );
      pibptr->RegisterNode(acrelptr);
    }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

void ACRelationship :: Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt )
{

  ACReference::Open(nodeptr, dbfield_ptr,highctx,extoff,accopt);

  nodetype = NT_ACRelationship;


}

/******************************************************************************/
/**
\brief  ProvideExtendNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendNode"

logical ACRelationship :: ProvideExtendNode ( )
{
  logical  term = NO;
BEGINSEQ
  if ( !nodefield->get_extend() )                    ERROR
  
  if ( *nodefield->get_extend() == '.' )
    if ( InitIsel(GetMainBase(),NULL) )              ERROR
  stssusr3();
  system_node = object_ref->GetLocalACObject()->ProvideACExtend(
                        (char *)nodefield->get_extend(),nodeacc,this,nodeacc > PI_Read );
  stsrusr3();
  if ( !system_node && *nodefield->get_extend() != '.' )  
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideInstance - 



\return instptr - 

\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInstance"

void *ACRelationship :: ProvideInstance (int32 lindx0, logical global_add )
{
  void            *instptr;
  EB_Number        entnr;
BEGINSEQ
  if ( system_node )
  {  
    if ( SetAutoIdent() == ERIC )                    ERROR
    
    if ( !memcmp(nodefield->fmcbtype,"SDB_Structure ",14) && 
         (((SDB_Structure *)nodeinst->get_iselarea())->get_itype() &&
          ((SDB_Structure *)nodeinst->get_iselarea())->get_access_type() != AT_NONE ) )
    {
      nodewrit = AUTO;
      if ( system_node->Get(Bnodeinst,YES) )
      {
        char     string[120];
        char     names[ID_SIZE+1];
        gvtxbts(strcpy(string,"Field : ")+8,nodefield->fmcbname,ID_SIZE);
        strcat(strcat(string," Structure : "),gvtxbts(names,nodeinst->get_iselarea(),ID_SIZE));
        SDBError().TraceMessage(string);                SDBERR(126)
      }
    }
    else
    {
      
      if ( !nodefield->get_create() )
      {
        CheckOrder(YES);    // ist problematisch, da für weak typed Basismengen der rootextent meistens falsch ist
        if ( system_node->get_root_extend()->GetID(Bnodeinst,YES).IsEmpty()) SDBERR(170)
      }  
      
      CheckOrder(NO);
      nodewrit = AUTO;
      if ( GetKeySMCB() && GetKeySMCB()->smcbsts.stscnof() )
      {
        if ( system_node->IdentityAdd(Bnodeinst,(char *)noderefp->get_refsakcb()->GetKeyName(),NO,global_add) )
                                                     ERROR
      }
      else
      {
        if ( IsVariableType() && !(entnr = system_node->GetID(Bnodeinst,NO)).IsEmpty() )
          if ( ProvideInti(entnr) )                  ERROR
        if ( system_node->Add(Bnodeinst,NO,YES,global_add) )
                                                     ERROR
      }
    }
    
    if ( AddID(lindx0) )                             ERROR
    instptr = ReserveInstance();
  }
  else 
    if ( !(instptr = ACReference::Add(lindx0,global_add)) )     ERROR
RECOVER
  instptr = NULL;
  nodewrit = NO;

ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  ProvideInti - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInti"

logical ACRelationship :: ProvideInti (EB_Number entnr )
{

  return ( ACReference::ProvideInti(entnr) );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInti"

logical ACRelationship :: ProvideInti (int16 sid )
{
  logical                 term = NO;
BEGINSEQ
  if ( ACReference::ProvideInti(sid) )                ERROR
  
  if ( nodeacc > PI_Read && nodefield->get_extend() )
  {
    if ( *nodefield->get_extend() == '*' )
    {
      if ( !(system_node = object_ref->GetLocalACObject()->ProvideACExtend(
                                struct_access->get_struct_def()->smcbname,
                                nodeacc,nodeacc > PI_Read )) )      ERROR
    }
    else if ( system_node && system_node->IsLocal() )
      system_node->SetType(struct_access->get_struct_def()->smcbname);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetIntern - 




\param  indx0 - Position in collection
\param  exist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetIntern"

void ACRelationship :: ResetIntern (int32 indx0, logical exist )
{

// soll instanzen-Einstelllung für ... InvDeriGenRef zurücknehmen

  if ( exist )
    Get(indx0);
  else
  {
    Cancel();              // sonst kommt es ggf. zur Doppeländerung in der BasisInstanz, Error 167
    nodecur = indx0;  
  }


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

logical ACRelationship :: Save (logical switchopt, logical overwrite, logical chknode )
{
  int16            talevel  = 0;
  ACRelationship  *nodeptr  = NULL;
  logical          term     = NO;
BEGINSEQ
  if ( !stscfil() )                                 LEAVESEQ
  if ( chknode && Check(NO) )                       ERROR
  
  if ( !nodeinst || 
       (!stscmod() && !stscsav() && !stscwpt() && nodecur == AUTO) )  
  
  if ( TARequired() )                            
    talevel = StartTA();
    
  if ( stscsav() || stscmod() )
  {
    if ( SaveInitInst() )                            ERROR
    if ( Bnodeinst->SaveGenAttr(switchopt,overwrite) )
                                                     ERROR
    if ( system_node )
    {
      if ( system_node->Save(Bnodeinst) )            ERROR
    }
    if ( !(nodeptr = GetInverse(NO)) )
    {
      if ( UpdateID() )                              ERROR
    }
    else
    { 
      nodeptr->ReleaseField();
      UpdateID(YES);  // nur temporäre Indizees
    }
    if ( UpdateCurIndex(!switchopt,overwrite) )      ERROR
  }
  else
    if ( ACProperty::Save(switchopt,overwrite,NO) )  ERROR

RECOVER
  term = YES;

ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);

}

/******************************************************************************/
/**
\brief  SetAutoIdent - 



\return cond_setting - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoIdent"

char ACRelationship :: SetAutoIdent ( )
{
  char       cond_setting = NO;
BEGINSEQ
  if ( system_node &&
       (cond_setting = system_node->SetAutoIdent(Bnodeinst,
                                                 noderefp->get_refsakcb()->get_key_def(),
                                                 GetGenOrderType())) )
                                                     LEAVESEQ
  cond_setting = noderefl->SetAutoIdent(GetKeyInstance(nodeinst,NULL));
ENDSEQ
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  UpdateInvDeri - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateInvDeri"

logical ACRelationship :: UpdateInvDeri ( )
{
  int32            curidx = nodecur;
  logical         exist  = nodeinst && nodeinst->IsPositioned();
  ref            *curref;
  ACRelationship *nodeptr = NULL;
  smcb           *smcbptr;
  char           *oldinst = NULL;
  int32           count;
  int32           pos;
  logical         term = NO;

BEGINSEQ
  curref = noderefp;
  if ( noderefp && noderefp != noderefmain )
    SetMainRef();
    
  for (count=GetCount()-1; count>=0; count-- )
  {
    if ( Get(count) && (nodeptr = GetInverseI()) )
    {
// wahrscheinlich gehts nur mit oldinst??      
      if ( !oldinst && 
           !(oldinst = Bnodenode->get_bnodeinst()->GetOldInst(NULL)) )
                                                     ERROR
      smcbptr = nodeptr->get_nodefield()->fmcbsmcb;

if ( nodefield->get_weak_typed() &&
     Bnodeinst->get_weak_typed_offset() != nodeptr->get_nodefield()->fmcbposn )
SDBSET(777)   // 8.11.2004
//      pos = nodefield->get_weak_typed() 
//            ? Bnodeinst->get_weak_typed_offset() + nodeptr->get_nodefield()->fmcbposn
//            : nodeptr->get_nodefield()->fmcbposn;
//      smcbptr->CopyInstance(nodeinst->get_iselarea()+pos,
      smcbptr->CopyInstance(nodeinst->get_iselarea()+nodeptr->get_nodefield()->fmcbposn,
                            smcbptr,
                            nodenode->get_nodeinst()->get_iselarea(),
                            REPL_GUID,UNDEF);
      if ( term = UpdateID() )                       ERROR
      if ( !nodeinst->SetInWork(YES) )                  // noch nicht erledigt
      {
        stssmod();
        nodeinst->stssmod();
        term = Save(NO,NO,NO);
        nodeinst->SetInWork(NO);
        if ( term )                                  ERROR
      }
      nodeptr->ReleaseField();
      nodeptr = NULL;
    }
  }
  SDBCERR
RECOVER
  term = YES;
ENDSEQ
  if ( curref )
    SetOrderRef(noderefp);
  ResetIntern(curidx,exist);
  if ( nodeptr )
    nodeptr->ReleaseField();
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateInverse - 



\return term - Termination code

\param  keymod - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateInverse"

logical ACRelationship :: UpdateInverse (logical keymod )
{
  ACRelationship   *nodeptr  = NULL;
  binti            *bintiptr = Bnodenode->get_bnodeinst();
  EB_Number         entnr;
  ref              *curref;
  char             *oldinst;
  int32              count;
  int32              curidx;
  logical           extlock = NO;
  logical           exist = NO;
  logical           term = NO;
BEGINSEQ
  if ( nodeptr = GetInverse(!keymod) )
  {
    if ( nodeptr->get_nodefield()->fmcbrlev == R_DIRECT )      // abgeleitete Structures
    {
      nodeptr->ReleaseField();
      nodeptr = NULL;
      term = UpdateInvDeri();
    }
    else
    {
      if ( nodeptr->get_nodefield()->fmcbdim == 1 )  LEAVESEQ
      if ( !(oldinst = bintiptr->GetOldInst(NULL)) )  ERROR
      if ( !nodeptr->get_noderefl()->CheckMod(Bnodenode->GetKeyInstance(NULL,NULL),
                                              Bnodenode->GetKeyInstance(NULL,oldinst)) )
                                                     LEAVESEQ
      
      curidx  = nodecur;
      curref = noderefp;
      if ( noderefp && noderefp != noderefmain )
        SetMainRef();
      exist   = nodeinst && nodeinst->IsPositioned();
      
      extlock = noderefl->stsclck();
      if ( noderefl->HasKeyLocks() )                 SDBERR(6)
      if ( noderefl->Lock() )                                   SDBERR(6)
      for (count=GetCount()-1; count>= 0 && !term; count-- )
      {
        if ( Get(count) )
        {
          if ( nodefield->get_weak_typed() )
          {
            nodeptr->ReleaseField();
            nodeptr = GetInverse(!keymod);
          }
          else
            nodeptr->Check(YES,NO);            
          
          if ( nodeptr->get_nodefield()->get_weak_typed() )  // geht nicht so fuer not unique keys
            entnr = nodeptr->GetID(Bnodenode->ExtractSortKey(NULL,oldinst,NO),NO,NO);
          if ( entnr.IsEmpty() )
            entnr = bintiptr->GetID();
          term = nodeptr->get_noderefl()->UpdateID(bintiptr,oldinst,entnr);
          nodeptr->SetSave();
        }
      }
      noderefl->Unlock(extlock);
      SDBCERR
      
      if ( curref )
        noderefp = curref;
      ResetIntern(curidx,exist);
      if ( term )                                    SDBERR(152)
    }
  }
  else
  {
    if ( SDBERROR == 74 )                            ERROR
    if ( nodefield->get_inverse() && nodefield->get_inverse()->fmcbrlev != R_REFR ) 
      term = UpdateInvDeri();     // erforderlich, falls bei GetInverse FieldReserved()
  }

RECOVER
  term = YES;
ENDSEQ
  if ( nodeptr )
    nodeptr->ReleaseField();
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACRelationship - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACRelationship"

     ACRelationship :: ~ACRelationship ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


