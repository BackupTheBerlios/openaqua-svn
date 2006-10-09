/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    LNode

\brief    


\date     $Date: 2006/08/30 13:37:14,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LNode"

#include  <popa7.h>
#include  <sACAttribute.hpp>
#include  <sACBaseStruct.hpp>
#include  <sACElmView.hpp>
#include  <sACExtend.hpp>
#include  <sACGenericAttr.hpp>
#include  <sACOPGroupBy.hpp>
#include  <sACOPOutput.hpp>
#include  <sACOPSelect.hpp>
#include  <sACObject.hpp>
#include  <sACPath.hpp>
#include  <sACPathNode.hpp>
#include  <sACReference.hpp>
#include  <sACRelationship.hpp>
#include  <sACShareBase.hpp>
#include  <sACTransientReference.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Number.hpp>
#include  <sInstBuffer.hpp>
#include  <sInstanceCache.hpp>
#include  <sLACObject.hpp>
#include  <sLNode.hpp>
#include  <iNetConversion.h>
#include  <sOPDecl.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <sSimpleAction.hpp>
#include  <sacb.hpp>
#include  <sbinti.hpp>
#include  <sexd.hpp>
#include  <sgmvl.hpp>
#include  <sguid.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <skcb.hpp>
#include  <skmvl.hpp>
#include  <smvlp.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>
#include  <ssmcb.hpp>
#include  <sLNode.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *LNode :: Add (int32 lindx0, logical global_add )
{
  char     *instptr = NULL;
BEGINSEQ
  if ( nodeinst->Add() )                             ERROR
  nodecur  = nodeinst->GetIndex(UNDEF);
  objid    = Bnodeinst->get_objid();
  nodewrit = YES;
  instptr  = nodeinst->get_iselarea();
  
//  return(NULL);

RECOVER

ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *LNode :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  kcb               *ik_kcbptr = NULL;
  kcb               *sk_kcbptr = NULL;
  ACGenericAttr     *acgnodeptr;
  int                attrtype;
  logical            ids = NO;
  logical            idk = NO;
  logical            ais = NO;
  logical            aik = NO;
  logical            user_inst = NO;
  void              *instptr;
  int16              talevel = 0;
// STARTSEQ
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  switch ( CheckAddSet() )
  {
    case  NO : break;
    case  YES: ERROR;
    default  : LEAVESEQ
  }
  
  if ( GenerateEvent(DBP_Insert) )                   ERROR
  
  if ( auto_position != AUTO && lindx0 == AUTO )
    lindx0 = auto_position;
    
  if ( (skey && auto_key && CompareSortKey(auto_key,skey,NO)) ||
       (auto_position != AUTO && lindx0 != auto_position)        )
                                                     SDBERR(346)
  if ( lindx0 == LAST_INSTANCE )
    lindx0 = GetCount();
  
  if ( lindx0 == AUTO )
    lindx0 = nodecur;

  if ( stscmod() )  
    stsssav();                // 29.01.03 wir setzen sav nur, wenn mod gesetzt war. s.u. 
//stsssav();                  // 27.12.02 sonst wird wieder nicht gesichert
  stsrmod();                  // 27.12.02 müssen wir zurücknehmen, damit Add nicht recursive laüft (z.B. für initinstances)
  if ( !nodeinst->stscini() || // 29.01.03 für ini dürfen wir nicht switchen
       (initinst && initinst != nodeinst->get_iselarea()) )
    if ( Switch(AUTO) )	                             ERROR

  talevel = StartTA();
  if ( noderefp && (sk_kcbptr = noderefp->get_refsakcb()->get_key_def()) )
  {
    ids = sk_kcbptr->scbsmcb->smcbsts.stscnof();                  // identity-Sortierung
    ais = sk_kcbptr->scbsmcb->smcbsts.stscold();                  // AUTOIDENT-Sortierung
    if ( !skey &&  !initinst && !ids && !ais )        SDBERR(81)
  }

  ik_kcbptr = nodefield->GetDBStruct()->smcbidky;
  if ( ik_kcbptr && !sk_kcbptr && skey && !idkey )
    idkey = skey;
  idk = ik_kcbptr ? ik_kcbptr->scbsmcb->smcbsts.stscnof() : NO;   // identity-Sortierung
  aik = ik_kcbptr ? ik_kcbptr->scbsmcb->smcbsts.stscold() : NO;   // AUTOIDENT-Sortierung
  
  if ( !ik_kcbptr && idkey && !idk )                  SDBERR(82)

  if ( nodefield->get_extend() )  // 15.6.98 ersetzt privilege() == PI_Share 
  {
    if ( sk_kcbptr == ik_kcbptr )
    {
      if ( idkey && skey && idkey != skey )           SDBERR(82)
    }
    else
    {
      if ( !idkey && !sk_kcbptr )
        idkey = skey;
//      if ( !idkey && !initinst && !idk && !aik )      SDBERR(81)  raus am 19.11.99, wir wollen Hinzufügen auch bei fehlendem IdentKey zulassen, da dieser ja noch im Context gesetzt werden kann!
    }
  }

  if ( initinst || nodeinst->stscini() )                            // vorinitialisierte instanz
    user_inst = YES;
  Initialize_intern(initinst);
  if ( sk_kcbptr && skey && !ids )
    sk_kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),skey);
  if ( ik_kcbptr && idkey && !idk )
    ik_kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),idkey);

  if ( (acgnodeptr = GetGenAttrNode()) && (attrtype = GetGenOrderType()) )
  {
    acgnodeptr->get_nodefield()->fmcbsmcb->smcbidky->
      kcbkpt(acgnodeptr->get_nodeinst()->get_iselarea(),(char *)&attrtype);
    acgnodeptr->Modify();     
  }
   
  if ( user_inst )
    Bnodeinst->SetGenAttrMod();     
  if ( !(instptr = Add(lindx0,global_add)) )         ERROR  // wegsprung neu 12.1.00
  if ( nodeinst->stscsav() )
    stsssav();    
  GenerateEvent(DBO_Inserted);
  
  if ( global_add && new_instance )  
  {
    nodeinst->stssmod();    
    stssmod();  
  }
  if ( Save(NO,NO,NO) )                              ERROR
  
  if ( is_memo && highnod && 
       highnod->get_nodeinst()->get_struct_def()->GetGUIDPosition() >= 0 )
    highnod->Modify();
  
  CheckExpression();

RECOVER
  int saveerr = SDBERROR;
  if ( saveerr )
    StructFieldError();
  GenerateEvent(DBO_NotInserted);

  if ( nodeinst )
    nodeinst->ResetNodes();
  ResetInstance();
  SDBISET(saveerr);

  instptr = NULL;
ENDSEQ
// STOPSEQ
  stsrres();
  if ( talevel )
    if ( StopTA(instptr == NULL) )
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

logical LNode :: AddGenericRef (char *fldname )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  AddID - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical LNode :: AddID (int32 indx0 )
{

  return ( AddID(Bnodeinst,nodeinst->GetID(),
                 indx0) );


}

/******************************************************************************/
/**
\brief  i03 - 


\param  keyptr - 
\param  ebsnum - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical LNode :: AddID (char *keyptr, EB_Number ebsnum, int32 lindx0 )
{

  return ( noderefp && noderefp->AddExt(ebsnum,keyptr,lindx0) != AUTO ? NO : YES );

}

/******************************************************************************/
/**
\brief  i1 - 


\param  bintiptr - 
\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical LNode :: AddID (binti *bintiptr, EB_Number ebsnum )
{
  logical    extlock = stsclck();
  logical    term = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
    
  if ( !extlock && LockSet(NO) )                     ERROR
    
  if ( AddID(bintiptr,ebsnum,AUTO) )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( UnlockSet(extlock) )
    term = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 


\param  bintiptr - 
\param  ebsnum - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical LNode :: AddID (binti *bintiptr, EB_Number ebsnum, int32 lindx0 )
{
  logical                 term = NO;
BEGINSEQ
  stsrres();
  if ( ebsnum.IsEmpty() )
    ebsnum = bintiptr->GetID();
  
  if ( nodefield->fmcbdim > 0 && 
    GetMainRef()->GetCount() >= nodefield->fmcbdim ) 
  {
    if ( nodefield->fmcbdim == 1 && 
         noderefp->WSGetID(0L) == ebsnum )  
    {
      nodecur = 0;
      stssres();
      LEAVESEQ
    }
    SDBERR(162)
  }
  
  if ( !stscres() )
  {
    if ( noderefl->CheckNewID(GetKeyInstance(bintiptr,NULL),ebsnum) ) 
                                                     ERROR
    if ( noderefl->AddID(bintiptr,ebsnum,lindx0) )   ERROR
    SetSave();
    
    instance_inserted = YES;
  }
  
  if ( noderefp )
  {
    nodecur = noderefp->GetRefCuri();
    nodeinst->set_inst_index(nodecur);
  }
  objid = Bnodeinst->get_objid();
  new_instance = nodecur >= 0 && !nodeinst->stscold();
  
  if ( nodefield->get_global_identity() )    // auto-guid
    ProvideGUID();
  
  if ( stscmod() )
    if ( Save(NO,YES,NO) )                           ERROR

RECOVER
  if ( SDBERROR )
    StructFieldError();
  nodecur = AUTO;
  term    = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddInstance - 


\return instptr - 

\param  bintiptr - 
\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInstance"

void *LNode :: AddInstance (binti *bintiptr, int32 indx0 )
{
  EB_Number               entnr;
  inti                   *oldinti = nodeinst;
  logical                 oldwrit = nodewrit;
  void                   *instptr = NULL;
BEGINSEQ
  entnr = bintiptr->GetID();
  
  nodeinst->MoveInstance(bintiptr);
  nodewrit = AUTO;
  if ( GenerateEvent(DBP_Insert) )                   ERROR
  nodewrit = oldwrit;
  
  if ( !AddID(Bnodeinst,entnr,indx0) )  
  {                
    GenerateEvent(DBO_Inserted);
    if ( Save(NO,NO,NO) )                            ERROR
    
    instptr = LNode::Get(AUTO);
  }
  else
  {
    GenerateEvent(DBO_NotInserted);                  ERROR
  }

RECOVER
  int saverr = SDBERROR;
  nodeinst->Cancel();
  ResetInstance();
  instptr  = NULL;
  nodewrit = NO;
  SDBISET(saverr);

ENDSEQ
  return(instptr);
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

logical LNode :: AddReference (node *srcenode, int32 lindx0 )
{
  LNode     *lsrcenode;
  kcb       *kcbptr;
  smcb      *sksmcb;
  char      *keyptr;
  EB_Number  entnr;
  int16      talevel = 0;
  logical    path_node = srcenode->stsctrans();
  logical    term = NO;
BEGINSEQ
  if ( Check(YES) || srcenode->Check(YES) )          ERROR
  if ( srcenode->IsLocalNode() != YES )              SDBERR(510)
  
  srcenode->stsrtrans();
  lsrcenode = (LNode *)srcenode;
  if ( nodeacc == PI_Read )                          SDBERR(28)

  if ( Switch(AUTO) )                                ERROR
    
  talevel = StartTA();
  
  if ( nodefield->get_owning() )                     SDBERR(159)
  if ( nodefield->get_weak_typed() ) 
  {
    if ( SetType(srcenode->GetCurrentType()) )       ERROR
  }
  else
    if ( lsrcenode->GetCurrentTypeDef()->smcbityp != GetCurrentTypeDef()->smcbityp )
                                                     SDBERR(236)

  if ( lsrcenode->get_nodecur() == AUTO && lsrcenode->get_nodewrit() < 255 ) ERROR
  
  if ( !lsrcenode->get_nodeinst()->IsPositioned() )
    srcenode->Get();
  entnr = lsrcenode->get_nodeinst()->GetID();
  
  Initialize_intern(NULL);
  if ( kcbptr = sk_index->get_key_def() )
  {
    if ( nodefield->get_index_list()->GetCount() > 1 || 
         !(sksmcb = srcenode->GetSortKeySMCB()) ||
         memcmp(kcbptr->scbsmcb->smcbname,sksmcb->smcbname,ID_SIZE)  )
    {
      GetInstance(entnr);  // geht nur, wenn srce und target wirklich im gleichen ACObject liegen. ggf. prüfen!
    }
    else
    {
      if ( !(keyptr = lsrcenode->get_noderefp()->WSGetKey(srcenode->get_nodecur(),GetKeyArea())) )
        if ( lsrcenode->IsPositioned() )
          keyptr = srcenode->ExtractSortKey(NULL,NULL,NO);
      if ( keyptr )
        kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),keyptr);
    }
  }
  
  if ( AddID(Bnodeinst,entnr,lindx0) )               ERROR
  LNode::Get(AUTO);

RECOVER
  if ( nodeinst )
    nodeinst->ResetNodes();
  ResetInstance();
    
  term = YES;
ENDSEQ
  if ( path_node )
    srcenode->stsstrans();
  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  CanUpdateCollection - 


\return cond - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanUpdateCollection"

logical LNode :: CanUpdateCollection (logical chknode )
{
  logical           cond = YES;
BEGINSEQ
  if ( !bnode::CanUpdateCollection(chknode) )          ERROR
  
  cond = noderefl ? !noderefl->CheckWProtect() : NO;


RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical LNode :: Cancel (logical chknode )
{
  int16     talevel = 0;
  logical   term    = NO;

BEGINSEQ
  if ( chknode && Check(NO,NO)  )                    ERROR
  
  if ( !nodeinst || (!IsPositioned() && !nodeinst->stscini()) )
  {  // das müssen wir machen, damit beim ToTop kein mod stehen bleibt 27.1.03
    stsrsav();
    stsrwpt();
    stsrmod();
    LEAVESEQ
  }
  
  if ( chknode && inti_buffer )
    inti_buffer->Cancel();
  
  talevel = StartTA();
  
  if ( (stscsav() || stscwpt()) )
  {
    stsrsav();
    stsrwpt();
    if ( nodeinst->Cancel() )         	             
    {
      nodeinst->ResetNodes();
      ResetInstance();
      ERROR
    }
  }
  else
    nodeinst->ResetNodes();
  
  if ( !chknode )
    if ( SaveReference() )                           ERROR

  ResetInstance();

RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term); 

}

/******************************************************************************/
/**
\brief  CancelNode - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelNode"

logical LNode :: CancelNode ( )
{

  return(Cancel(NO));

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

logical LNode :: Check (logical autoini, logical acccheck )
{
  logical term = NO;
BEGINSEQ
  if ( stscusr3() || stscfil() )                     LEAVESEQ

  if ( origin )
    origin->Check(autoini,acccheck);
  else
    if ( parent )
      if ( parent->Check(autoini,acccheck) )         ERROR
  
  if ( bnode::Check(autoini,acccheck) )              ERROR
  
  if ( !term && autoini )
    is_opened = YES;

RECOVER
  term = YES;
ENDSEQ
  return (term);

}

/******************************************************************************/
/**
\brief  CheckDB - 


\return term - Termination code

\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical LNode :: CheckDB (CheckOptions check_opts )
{
  int32                   indx0 = 0;
  NString                 ntitle;
  NString                 nresult;
  logical                 term  = NO;
  if ( check_opts.collections )
    if ( CheckDBCollection(nresult,check_opts) )
    {
      ntitle = "\n  Errors/warnings for collection";
      ntitle += ' ';
      ntitle +=  prop_path;
      ntitle += ':';
      OBHOutputResult(ntitle);
      OBHOutputResult(nresult);
    }

  if ( check_opts.instances )
    while ( Get(indx0++) )
      CheckDBInstance(check_opts);

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

logical LNode :: CheckDBCollection (NString &nresult, CheckOptions check_opts )
{
  ref                    *refptr;
  NString                 nstring;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  if ( Check(YES,NO) )                               LEAVESEQ
    
  if ( noderefl )
  { 
    if ( refptr = noderefl->get_keymvl() )
      if ( refptr->CheckDBIndex(nstring,check_opts) )
      {
        if ( nodenode && (refptr->stscmod() || refptr->stscsav()) )
          nodenode->Modify();
        term = YES;
        refptr->stsrsav();
      }
      
    while ( refptr = noderefl->GetReference(++indx0) )
      if ( refptr->CheckDBIndex(nstring,check_opts) )
      {
        if ( noderefl->get_keymvl() )
        {
          noderefl->get_keymvl()->Modify();
          noderefl->get_keymvl()->Save();
        }
        else if ( nodenode && (refptr->stscmod() || refptr->stscsav()) )
          nodenode->Modify();
        refptr->stsrsav();
        term = YES;
      }
  }
  else if ( noderefp )
    if ( noderefp->CheckDBIndex(nstring,check_opts) ) 
    {
      if ( nodenode && (refptr->stscmod() || refptr->stscsav()) )
        nodenode->Modify();
      refptr->stsrsav();
      term = YES;
    }
  
  if ( term ) 
  {
    nresult += "\n      Reference/collection";
    nresult += " '";
    nresult.Append(nodefield->fmcbname,ID_SIZE);
    nresult += "' contains damaged indexes or references:";
    nresult += nstring;
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBInstance - 


\return term - Termination code

\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBInstance"

logical LNode :: CheckDBInstance (CheckOptions check_opts )
{
  isel                   *iselptr = (isel *)nodeinst;
  NString                 nresult;
  NString                 nstring;
  char                   *keyptr;
  char                    keyarea[MAX_KEYLEN];
  logical                 term = NO;
BEGINSEQ
  if ( !nodeinst )                                   ERROR
  if ( iselptr->CheckDBInstance(nstring,check_opts) )
  {
    if ( stscmod() )
      Save(NO,NO);
    nresult += "\n  Errors/warnings for instance";
    nresult += ' ';
    nresult.Append(iselptr->get_struct_def()->smcbname,ID_SIZE);
    nresult += ':';
    nresult += Bnodeinst->get_objid();   
    if ( id_key )
    {
      keyptr = ExtractKey(keyarea,nodeinst->get_iselarea(),NO);
      nresult += '(';
      nresult += KeyToString(NULL,keyptr);
      nresult += ')';
    }

    OBHOutputResult(nresult);
    OBHOutputResult(nstring);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDelInstance - 


\return term - Termination code

\param  inst_id - 
\param  ref_id - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDelInstance"

logical LNode :: CheckDelInstance (int32 inst_id, EB_Number ref_id, logical del_inst )
{
  logical                 term = NO;
BEGINSEQ
  if ( ref_id.IsEmpty() || inst_id <= 0 )            LEAVESEQ

  if ( inst_id == objid )
    if ( del_inst || (noderefl && ref_id == noderefl->GetID()) )   
                                                     ERROR
      
  if ( nodenode && ((LNode *)nodenode)->CheckDelInstance(inst_id,ref_id,del_inst) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckExpression - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical LNode :: CheckExpression ( )
{
  logical                  accept = YES;
  int32                    curri;
  logical                 term = NO;
BEGINSEQ
  if ( nodesel )
  {
    PropertyHandle           phdl(this);
    accept = nodesel->Call(&phdl,(ParmList *)NULL,NO)
             ? NO : nodesel->GetValue()->IsTrue();
  }
  
  if ( !accept || 
       (Bnodeinst->get_context() && Bnodeinst->get_context()->IsHidden()) ||
       GenerateEvent(DBP_Select)                                            )
  {
    curri = nodecur;
//    Cancel(NO);  nach ResetInstance geändert: 20.5.2004
    ResetInstance();
    nodecur = curri;
    ERROR
  }
  
  if ( has_event_handler ) // subnodes have property process handler
    Bnodeinst->SetupSubNodes(NO,YES);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical LNode :: CheckWProtect ( )
{
  logical   term;

BEGINSEQ
  if ( Check(YES) )	                                   ERROR
  term = nodeinst->CheckWProtect() == 1;

RECOVER
  term = NO;
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

logical LNode :: Close ( )
{
  logical    is_cpy_node = origin ? YES : NO;
BEGINSEQ
  if ( nodeidnt != NODE_ID )                         LEAVESEQ
  
  bnode::Close();

  if ( is_cpy_node )
  {
    noderefl    = NULL;
    SetOrderRef(NULL);
    noderefmain = NULL;
  }
  


ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  Contains - 


\return cond - 

\param  reg_string - 
\param  case_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Contains"

logical LNode :: Contains (char *reg_string, logical case_opt )
{

  return(node::Contains(reg_string,case_opt));

}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *LNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new LNode(*this) ) )              SDBERR(95)
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
\brief  CreateGUID - 


\return term - Termination code

\param  transaction - Transaction option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGUID"

logical LNode :: CreateGUID (logical transaction )
{
  guid               _guid;
  int16              talevel = 0;
  logical            term;
BEGINSEQ
  if ( transaction )
    talevel = StartTA();
    
  BuildGUID(&_guid);
  if ( nodeinst->CreateGUID(&_guid) )                ERROR
  
  if ( transaction )
  {
    Modify();  
    Save(NO,NO,NO);
  }

RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    if ( StopTA(term) )
  return(term);
}

/******************************************************************************/
/**
\brief  CreatePathNode - 


\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  parm_bnf - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *LNode :: CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv )
{
  ACPathNode              *nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACPathNode(this,parm_bnf,operenv);   SDBCERR
  if ( !nodeptr->IsValid() )                         ERROR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  prop_path - Property path
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *LNode :: CreatePathNode (char *prop_path, OperEnvironment *operenv )
{
  ACPathNode              *nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACPathNode(this,prop_path,operenv);  SDBCERR
  if ( !nodeptr->IsValid() )                         ERROR
RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateSubNode - 


\return nodeptr - 

\param  nodeptr - 
\param  nodtype - 
\param  sysnode - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  extoff - 
\param  intoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubNode"

node *LNode :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{
  node         *subnode = NULL;
BEGINSEQ
  switch ( nodtype )
  {
    case  NT_ACAttribute    : subnode = new ACAttribute(nodeptr,dbfield_ptr,highctx,
                                                        instptr,accopt);
                              break;
    case  NT_ACBaseStruct   : subnode = new ACBaseStruct(nodeptr,dbfield_ptr,highctx,
                                                         instptr,accopt);
                              break;
    case  NT_ACGenericAttr  : subnode = new ACGenericAttr(nodeptr,dbfield_ptr,highctx,
                                                          instptr,extoff,intoff,accopt);
                              break;
    case  NT_ACReference    : subnode = new ACReference(nodeptr,dbfield_ptr,highctx,extoff,
                                                        accopt);
                              break;
    case  NT_ACTransientReference : subnode = new ACTransientReference(nodeptr,dbfield_ptr,highctx,accopt);
                              break;
    case  NT_ACRelationship : subnode = new ACRelationship(nodeptr,NULL,dbfield_ptr,highctx,
                                                           extoff,accopt);
                              break;
    case  NT_ACShareBase    : subnode = new ACShareBase(nodeptr,sysnode,dbfield_ptr,highctx,
                                                        instptr,extoff,accopt);
                              break;
    default                 : subnode = bnode::CreateSubNode(nodeptr,nodtype,sysnode,dbfield_ptr,highctx,instptr,extoff,intoff,accopt);
  }
  if ( !subnode )                                    SDBERR(95)
  SDBCERR
RECOVER
  delete subnode;
  subnode = NULL;
ENDSEQ
  return(subnode);
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

logical LNode :: DelGenericRef (char *fldname )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  NODEID - 


\param  indx0 - Position in collection
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical LNode :: Delete (int32 indx0, logical chknode, logical del_dep, logical del_inst )
{
  logical         term = NO;
BEGINSEQ
  if ( !Get(indx0,chknode) )                        
  {
    nodedel(indx0,chknode);  // auto correction      
    LEAVESEQ
  }
  if ( chknode && !IsWrite() )                       SDBERR(28)

  if ( DeleteInstance(nodeinst,NULL,NO,del_dep,YES,del_inst) )
                                                     ERROR
  ResetInstance();
    
//  return(YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical LNode :: Delete (char *skey, logical chknode )
{
  logical   extlock = noderefl->stsclck();
  int32      lindx0;
  logical   term = NO;

BEGINSEQ
  if ( !extlock && LockSet() )                       ERROR
  
  if ( !Get(skey) && noderefp )				 
  {
    SDBEV1(skey,GetSortKeyLength())
    if ( IsGUID() )
      skey = (char *)StringToGUID(NULL,skey);
    if ( (lindx0 = noderefp->WSGetIndex(skey,0,YES)) == AUTO )
                                                     SDBERR(80)
    nodedel(lindx0,NO);                              LEAVESEQ
  }

  if ( Delete(nodecur,chknode) )	             ERROR  // war YES bis 31.1.00
RECOVER
  term = YES;
  nodecur = AUTO;
ENDSEQ
  if ( UnlockSet(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteID - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  bintiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical LNode :: DeleteID (binti *bintiptr, void *oldinst, EB_Number entnr )
{
  logical    term = NO;
  if ( noderefl )
  {
    noderefl->DeleteID(bintiptr,oldinst,entnr);
    SetSave();
  }
  nodecur = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical LNode :: DeleteID (binti *bintiptr )
{
  logical    extlock = stsclck();
  logical    term = NO;
BEGINSEQ
  if ( Check(YES) )                                   ERROR
    
  if ( !extlock )
    switch ( LockSet(NO) )
    {
      case  1 : ERROR
      case  2 : if ( !FieldReserved() )              ERROR
                extlock = YES;
                break;
      default : ;
    }

  noderefl->DeleteID(bintiptr,
                     nodenode ? bintiptr->GetOldInst(NULL) : (char *)NULL,
                     bintiptr->GetID());
  SetSave();
RECOVER
  term = YES;
ENDSEQ
  if ( UnlockSet(extlock,NO) )
    term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical LNode :: DeleteID ( )
{

  return ( LNode::DeleteID(Bnodeinst,
                           noderefl->OldinstRequested() ? Bnodeinst->GetOldInst(NULL) : (char *)NULL,
                           nodeinst->GetID()) );


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

logical LNode :: DeleteIndex (logical gen_events )
{
  int32     obj_id = objid;
  DB_Event  intevent= DB_undefined;
  logical  term   = NO;
BEGINSEQ
  if ( gen_events )
    if ( GenerateEvent(DBP_Remove) )                 ERROR
  
  if ( DeleteID() )                                  ERROR
  
  if ( origin )
    origin->ResetCopyNodes(this,obj_id);
  else
    ResetCopyNodes(this,obj_id);
    
  nodecur  = AUTO;
  nodewrit = AUTO;  // sonst können wir nicht mehr auf die Instanz zugreifen - not selected/positione
  intevent = DBO_Removed;

RECOVER
  intevent = DBO_NotRemoved;
  term = YES;
ENDSEQ
  if ( gen_events )
    GenerateEvent(intevent);
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

logical LNode :: DeleteIndexEntry ( )
{
  logical           term = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  if ( nodeacc <= PI_Read )                          SDBERR(28)
  if ( nodecur == AUTO )                             ERROR

  nodeinst->Save(YES,NO);
  term = noderefp->DelExt(nodecur);

  ResetInstance();
RECOVER
  term = YES;
ENDSEQ
  return(YES);
}

/******************************************************************************/
/**
\brief  DeleteInstance - 


\return term - Termination code

\param  intiptr - 
\param  extnames - Extent name
\param  is_root - 
\param  del_dep - 
\param  switch_opt - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteInstance"

logical LNode :: DeleteInstance (inti *intiptr, char *extnames, logical is_root, logical del_dep, logical switch_opt, logical del_inst )
{
  logical   delopt = del_inst ? del_inst :
                     nodefield->get_owning() ? YES : 
                     del_dep ? nodefield->get_depend() : NO;
  int32     curi   = 0;
  int64     object_id = 0;
  EB_Number entnr = intiptr->GetID();
  exd      *exdptr = NULL;
  int32     obj_id = objid;
  logical   siw    = AUTO;
  logical   term   = NO;
BEGINSEQ
  object_id = entnr.FromPIF(IsPIF()).get_ebsnum();
  
  if ( delopt )
  {
    if ( nodeinst->stscwpt(1) )                      SDBERR(28)
//    if ( Bnodeinst->RecursiveEvents(DBP_Delete) )  ERROR  nach DeleteRelationships() verschoben
  }
       
  if ( stscmod() )
    nodeinst->Save(NO,NO);  
  
  if ( exdptr = Bnodeinst->GetEXD() )
    siw = nodeinst->SetInWork(YES);
  
  if ( Bnodeinst->DeleteRelationships(extnames,is_root,delopt,del_dep) )
                                                     ERROR
  curi = nodecur;
  if ( DeleteID() )                                  ERROR
  nodecur = curi;
  if ( Bnodeinst->DeleteReferences(extnames,is_root,delopt,del_dep) )
                                                     ERROR
  if ( delopt )
  {
    if ( nodeinst->DeleteInstance() )                ERROR
  }
  else if ( switch_opt )
    nodeinst->Cancel();
  
  if ( origin )
    origin->ResetCopyNodes(this,obj_id);
  else
    ResetCopyNodes(this,obj_id);
RECOVER
  RecoverSelection(object_id);
  term = YES;
ENDSEQ
  if ( siw != 255 )
    exdptr->SetInWork(siw);
  if ( curi )
    nodecur = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteSet - 


\return term - Termination code

\param  chknode - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSet"

logical LNode :: DeleteSet (logical chknode, logical del_dep )
{
  int32      count;
  char      string[13];
  logical   dsp_opt = GetSysVariable("DSPSTATUS") && !strcmp(GetSysVariable("DSPSTATUS"),"YES") ? YES : NO;
  logical   term = NO;

BEGINSEQ
  if ( chknode && Check(YES,YES)  )   
    if ( SDBERROR != 119 )                           ERROR
    
  if ( nodeacc == PI_Read )                          SDBERR(28)

  if ( Cancel(NO) )                                  ERROR
  
  if ( (count = GetCount(NO)) < 0 )                  ERROR
  
  if ( dsp_opt )
  {
    dsp_opt = 2;
    SDBError().InsertStatField();
    SetSysVariable("DSPSTATUS","NO");
  }
  
  while ( count-- )
  {
    if ( dsp_opt )
      SDBError().SetStatField(gvtxltoa(count,string,10));
    if ( Delete(count,NO,del_dep) )
      if ( SDBERROR )
      {
        if ( SDBERROR == 375 || SDBERROR == CONTEXT_ERROR )
                                                     ERROR
        term = YES; 
      }
  }
  if ( term ) 
  {
    term = nodedel(AUTO,NO);                         SDBERR(373)
  }
RECOVER
  term = YES;
ENDSEQ
  if ( dsp_opt == 2 )
  {
    SetSysVariable("DSPSTATUS","YES");
    SDBError().RemoveStatField();
  }
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteSetIndexes - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSetIndexes"

logical LNode :: DeleteSetIndexes ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( Check(YES,YES)  )                             ERROR
  if ( nodeacc == PI_Read )                          SDBERR(28)

  Cancel(NO);
  
  noderefl->DeleteReference();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Duplicate - 


\return instptr - 

\param  keyptr - 
\param  db_replace - Replace option
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Duplicate"

void *LNode :: Duplicate (char *keyptr, PIREPL db_replace, logical chknode )
{
  smcb     *smcbptr;
  EB_Number entnr;
  inti     *intiptr = NULL;
  int16     talevel = 0;
  char     *instptr = NULL;
  logical   term    = NO;
  fmcb     *auto_fmcb;
  int32     offset = 0;
  int32     autoid;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  if ( Save(NO,NO) )                                 ERROR
  
  talevel = StartTA();
  if ( !nodeinst->IsPositioned() )                   SDBERR(111)
  if ( Bnodeinst->SetupSubNodes(YES,NO) )            ERROR

  intiptr = nodeinst;
  SetCurrentInti(NULL);
  nodecur = AUTO;

  if ( db_replace ) 
  {
    Provide(keyptr);                                 SDBCERR
    if ( GetID(AUTO) == intiptr->GetID() )           SDBERR(389)
  }
  else
    if ( !Add(AUTO,keyptr,NULL,NULL) )               ERROR

  smcbptr = GetCurrentTypeDef();    
  
  if ( (auto_fmcb = smcbptr->SearchField("__AUTOIDENT",&offset)) || 
       (auto_fmcb = smcbptr->SearchField("#_AUTOIDENT",&offset))    )
    autoid = *(int32 *)nodeinst->get_iselarea()+offset+auto_fmcb->fmcbposn;
  smcbptr->CopyInstance(nodeinst->get_iselarea(),intiptr->get_struct_def(),intiptr->get_iselarea(),REPL_direct,UNDEF);
  if ( auto_fmcb )
    *(int32 *)(nodeinst->get_iselarea()+offset+auto_fmcb->fmcbposn) = autoid;
  SetSortKey(keyptr,NULL);
  
  term = nodeinst->Copy(intiptr,this,db_replace ? REPL_local : REPL_none,REPL_all);
  
  if ( SetKey(keyptr,GetKeyInstance(nodeinst,NULL))) ERROR
  if ( !Modify() )                                   ERROR
  Save(NO,NO,NO);
  instptr = nodeinst->get_iselarea();

RECOVER
  instptr = NULL;
ENDSEQ
  int saverr = SDBERROR;
  if ( intiptr )
  {
    entnr = nodeinst->GetID();
    nodeinst->Cancel();
    delete nodeinst;
    SetCurrentInti(intiptr);
    intiptr->Cancel();
    if ( !entnr.IsEmpty() )
    {
      intiptr->Get(entnr);
      ReserveInstance();
    }
  } 
  SDBISET(saverr);
  if ( talevel )
    if ( StopTA(instptr == NULL) )
      instptr = NULL;
  if ( term && !SDBERROR ) 
    SDBISET(156)
  return(instptr);

}

/******************************************************************************/
/**
\brief  FieldReserved - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldReserved"

logical LNode :: FieldReserved ( )
{

  return ( object_ref->GetLocalACObject()->FieldReserved(nodefield) );

}

/******************************************************************************/
/**
\brief  FirstKey - 


\return keyptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *LNode :: FirstKey (logical chknode )
{
  char      *keyptr = NULL; 
  kcb       *kcbptr;
BEGINSEQ
  if ( chknode && Check(YES) )	                     ERROR

  if ( Switch(AUTO) )                                ERROR

  if ( nodefield->fmcbdim == 1 )
  {
    if ( !Get(FIRST_INSTANCE,NO) )                     ERROR
    keyptr = GetSortKeyLength(NO)
             ? ExtractSortKey(NULL,nodeinst->get_iselarea(),NO)
             : ExtractKey(NULL,nodeinst->get_iselarea());
    LEAVESEQ
  }
  
  if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) ) 
  {
    if ( !(keyptr = noderefp->WSGetKey(0,GetKeyArea())) )
                                                      ERROR
    if ( kcbptr->scbsmcb->smcbsts.stscnof() )  // __IDENTITY
      ((EB_Number *)keyptr)->FromPIF(IsPIF());  
    
    nodecur = 0;
    nodewrit = NO;
    if ( !kcbptr->scbsmcb->smcbsts.stscnof() )
      kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),keyptr);
    if ( IsGUID() )
      keyptr = GUIDToString(NULL,(guid *)keyptr);
  }
  else if ( !nodesel )
  {
    if ( !GetKeySMCB() )                             SDBERR(174)
    if ( !Get(FIRST_INSTANCE,NO) )                   ERROR
    keyptr = GetSortKeyLength(NO)
             ? ExtractSortKey(NULL,nodeinst->get_iselarea(),NO)
             : ExtractKey(NULL,nodeinst->get_iselarea());
    if ( !keyptr )                                   ERROR
  }
  if ( !(keyptr = GetKeyAt(nodecur,FOREWARD,keyptr)) )
                                                     ERROR


RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  Get - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG - 


\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *LNode :: Get (int32 indx0, logical chknode )
{
  int32         curri;
  int64         indx64;
  char         *selection_key = auto_key;
  logical       no_event = NO;
  char         *save_key = auto_key;
  Operation    *save_sel = auto_selection;
  void         *instptr = NULL;
  kcb          *kcbptr;
BEGINSEQ
  if ( chknode )
  {
    if ( nodenode && !nodenode->IsPositioned() )     LEAVESEQ
    if ( Check(YES,NO) )                             ERROR
  }
  curri = nodecur;

  if ( auto_position >= 0 )
  {
    if ( indx0 <= 0 || indx0 == LAST_INSTANCE )
      indx0 = auto_position;
    if ( indx0 != auto_position )
    {
      Switch(AUTO);                                  ERROR
    }
  }
  if ( auto_selection )
  {
    if ( auto_selection->Execute(NULL) )             ERROR
    selection_key = auto_selection->GetString(); 
    selection_key = StringToKey(selection_key,NULL);
  }
  
  if ( selection_key )
  {
    if ( indx0 > 0 )                                 ERROR
    if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) )
    {
      indx0 = noderefp->WSGetIndex(selection_key,0,YES);
    }
    else
    {
      auto_selection = NULL;
      auto_key = NULL;
      Get(selection_key);
      indx0 = nodecur;
      auto_selection = save_sel;
      auto_key = save_key;
    }
    if ( indx0 == AUTO )
      if ( !auto_provide )                           ERROR
  }
  if ( stscusr2() )      // VOID-Extend
  {
    if ( indx0 == AUTO )
    {
      if ( nodecur == AUTO )                         ERROR
      instptr = nodeinst->get_iselarea();
    }
    else
    {
      if ( indx0 > 0 && nodecur == indx0 && nodeinst->IsPositioned() )
      {
        instptr = nodeinst->get_iselarea();          LEAVESEQ
      }
      Switch(AUTO);
      nodecur = indx0;
      indx64   = BigToPIF(indx0,IsPIF());
      if ( GenerateEvent(DBP_Read) )                 ERROR
      if ( !(instptr = GetInstance(EB_Number(indx64))) )
        nodecur = AUTO;
      else
        id_key = nodeinst->get_struct_def()->smcbidky;
    }
    LEAVESEQ
  }
  
  if ( indx0 == LAST_INSTANCE )
    indx0 = GetCount()-1;
    
  if ( (indx0 == AUTO || (indx0 == nodecur && (nodewrit || nodeacc == PI_Read))) && 
       (nodeinst->IsPositioned() || (nodecur == AUTO && nodeinst->stscini())) ) 
  {
    instptr = nodeinst->get_iselarea();              LEAVESEQ
  }
  
  if ( Switch(AUTO) )                                ERROR

  if ( indx0 == AUTO )
    if ( (indx0 = MIN(GetCount()-1,MAX(0,curri))) < 0 ) 
                                                     ERROR
  nodecur = indx0;
  if ( nodenode && nodenode->get_nodecur() == AUTO 
                && Bnodenode->get_nodewrit() != 255 )
  { // wenn der nodenode ini ist, kann keine Referenz verarbeitet werden
    if ( !auto_provide )
    {
      nodecur = AUTO;                                ERROR 
    }
    if ( !(instptr = Get()) )                        ERROR 
    LEAVESEQ
  }
  
  if ( GenerateEvent(DBP_Read) )                     ERROR
  if ( inti_buffer && !stscusr3() )
  {
    if ( !(instptr = GetBuffer(indx0,0)) )           ERROR
  }
  else 
    if ( !(instptr = Get()) )                        ERROR

RECOVER
  if ( SDBERROR && SDBERROR != 9 )
//if ( nodecur != AUTO ) must not be reset after cancel because of condition (see Get()) 9.6.2005
    Switch(AUTO);
  instptr = NULL;
ENDSEQ
 if ( instptr )
   GenerateEvent(DBO_Read);
 return(instptr);

}

/******************************************************************************/
/**
\brief  i1 - 


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *LNode :: Get (char *skey, logical chknode )
{
  int32     indx0 = 0;
  int32     pos   = 0;
  void     *instptr; 
  kcb      *kcbptr;
  char      keyarea[MAX_KEYLEN];
  char      wskey[MAX_KEYLEN];

BEGINSEQ
  if ( !skey || (chknode && Check(YES)) )            ERROR
  
  if ( auto_key )
  {
    if ( CompareSortKey(auto_key,skey,NO) )          ERROR
    instptr = Get(FIRST_INSTANCE);                   
    LEAVESEQ
  }
  if ( auto_selection )
  {
    if ( !(instptr = Get(FIRST_INSTANCE)) )          ERROR
    if ( CompareSortKey(ExtractSortKey(NULL,NULL),skey,NO) )          
                                                     ERROR
    LEAVESEQ
  }

  if ( stscusr2() )      // VOID-Extend
  {
    if ( skey[1] == '-' )  // GUID
    {
      guid    gid;
      gid.Initialize(skey);
      indx0 = object_ref->GetLocalACObject()->get_guid_pi().GetID(Key((char *)&gid));
    }
    else
      indx0 = atol(skey);
    instptr = Get(indx0,NO);
    LEAVESEQ
  }
  
  if ( IsGUID() )
    StringToGUID((guid *)wskey,skey);
  else
    SaveKey(wskey,skey);
    
  if ( instptr = Get_optimized(wskey) )              LEAVESEQ
  if ( nodefield->fmcbdim == 1 )                     ERROR

  instptr = nodeinst->get_iselarea();

  if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) )
  {
    if ( Switch(AUTO) )                              ERROR
    if ( nodenode && nodenode->get_nodecur() == AUTO 
                  && Bnodenode->get_nodewrit() != 255 )
    { // wenn der nodenode ini ist, kann keine Referenz verarbeitet werden
      if ( !auto_provide )                           ERROR
      if ( !(instptr = Get(0)) )                     ERROR 
      LEAVESEQ
    }
    if ( (indx0 = noderefp->WSGetIndex(wskey,0,YES)) == AUTO )
                                                     ERROR
    instptr = Get(indx0,NO);
  }
  else
  {
    SDBEV1(nodefield->fmcbsmcb->smcbname,ID_SIZE)
    if ( !GetKeySMCB() )                             SDBERR(71)
    
    if ( nodecur < 0 || CompareKey(ExtractKey(keyarea,instptr,NO),wskey,NO) )
    {
      Save(NO,NO,NO);
      Cancel();

      while ( instptr = Get(indx0++,NO) )
        if ( !CompareKey(ExtractKey(keyarea,instptr,NO),wskey,NO) )
          break;

      if ( !instptr )                                ERROR
    }
  }
  if ( instptr && cache_list )
    cache_list->AddEntry(nodeinst);
RECOVER
  int saverr = GetErrorCode();
  Cancel(NO);
  if ( saverr )
    SDBISET(saverr);
  instptr = NULL;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  i2 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *LNode :: Get ( )
{
  void     *instptr; 
  int32     current = nodecur;
  EB_Number entnr;

BEGINSEQ
  nodecur = AUTO;
  if ( !nodeinst )                                   ERROR
    
  if ( !auto_provide )
  {
    entnr = noderefp ? noderefp->WSGetID(current)
                     : nodeinst->GetID(current);
    if ( entnr == 0 )                                ERROR
  }
  else
  {
    if ( current > 0  )                              ERROR
    if ( noderefp && (!nodenode || nodenode->get_nodecur() != AUTO) )
    {
      current = auto_key ? noderefp->WSGetIndex(auto_key,UNDEF,YES)
                         : auto_position;
      if ( current != AUTO )
        entnr = noderefp->WSGetID(current);
    }
    else
      entnr = nodeinst->GetID(current);
    current = 0;
    if ( entnr == 0 )
    {
      if ( nodeacc <= PI_Read )                      ERROR
      if ( nodenode && !nodenode->IsSelected() )     ERROR
        
      instptr = auto_key ? Add(AUTO,auto_key,NULL,NULL)
                         : Add(auto_position,NULL,NULL,NULL);
      LEAVESEQ
    }
  }

  nodecur = current;
  nodeinst->set_inst_index(nodecur);
  if ( !(instptr = GetInstance(entnr)) )             ERROR

  if ( CheckExpression() )                           ERROR

  if ( !stscusr3() && auto_key && CompareSortKey(auto_key,ExtractSortKey(NULL,NULL),NO)) ERROR

RECOVER
  if ( nodecur != AUTO )
  {
    Cancel();
    nodecur = current;  // keep position when cancelled because of condition
  }
  instptr = NULL;
  objid   = 0;
  nodewrit = NO;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  GetAt - 


\return rindx0 - 

\param  lindx0 - 
\param  direction - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

int32 LNode :: GetAt (int32 lindx0, int16 direction, logical chknode )
{
  logical        term = NO;

BEGINSEQ
  if ( chknode && Check(YES) )	                     ERROR

  if ( auto_key )
  {
    if ( lindx0 > 0 )                                ERROR
    if ( auto_provide )
      Provide(auto_key);
    stssusr3();
    term = !Get(auto_key);
    stsrusr3();
    if ( term )                                      ERROR
    LEAVESEQ
  }
  
  if ( Get(lindx0,NO) )
  {
    lindx0 = nodecur;
    LEAVESEQ    
  }
  
  if ( nodecur == AUTO )                             ERROR
  lindx0 = nodecur;
  
  while ( direction && nodecur != AUTO )
  {
    lindx0 += direction;
    if ( Get(lindx0,NO) || nodecur < 0 )
      direction = 0;
  }
  if ( !IsPositioned() )                           ERROR
  if ( UserEventHandler() )
    Reset();


RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);

}

/******************************************************************************/
/**
\brief  GetAutoIdent - 


\return cond_setting - 

\param  intiptr - 
\param  kcbptr - 
\param  attrtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAutoIdent"

char LNode :: GetAutoIdent (inti *intiptr, kcb *kcbptr, int attrtype )
{
  char                    cond_setting = NO;
  fmcb                   *fmcbptr;
  char                    keyptr[513];
  int32                   offset = 0;
  logical                 found = NO;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR // 31.5.01
    
  if ( kcbptr                     &&
       noderefl->get_autoid_key() &&
       !kcbptr->scbsmcb->smcbsts.stscold() )
  {
    if ( noderefl->GetReference(kcbptr->scbsmcb->smcbname) &&
         !SetOrder(kcbptr->scbsmcb->smcbname,attrtype,NULL)   )
    {
      if ( noderefp->get_refsakcb()->get_unique() )
        if ( ExtractSortKey(keyptr,intiptr->get_iselarea(),NO) )
          found = Get(keyptr) ? YES : NO;
      SetMainRef();
      
      if ( found )
      {
        if ( !(fmcbptr = GetCurrentTypeDef()->SearchField("__AUTOIDENT",&offset)) &&
             !(fmcbptr = GetCurrentTypeDef()->SearchField("#_AUTOIDENT",&offset))   )
                                                     SDBERR(99)
        memcpy(intiptr->get_iselarea()+fmcbptr->fmcbposn + offset, 
               nodeinst->get_iselarea()+fmcbptr->fmcbposn + offset,
               fmcbptr->fmcbbyte);
        cond_setting = YES;
      }    
    }
  }

RECOVER
  cond_setting = ERIC;
ENDSEQ
  if ( found )
    Cancel();
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  GetCollectionID - 


\return coll_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollectionID"

int32 LNode :: GetCollectionID ( )
{
  ref         *refptr;
  int32        coll_id = UNDEF;
BEGINSEQ
  if ( nodenode && !nodenode->IsPositioned() )       ERROR
  if ( Check(AUTO,YES) )                             ERROR
  
  if ( !this || !(refptr = GetMainRef()) || !refptr->get_refrex() )  
                                                     ERROR

  if ( object_ref->GetLocalACObject()->get_pif() )
  {
    EB_Number   entnr = *refptr->get_refrex();
    coll_id = entnr.FromPIF(YES).get_ebsnum();
  }
  else
    coll_id = refptr->get_refrex()->get_ebsnum();

RECOVER

ENDSEQ
  return(coll_id);
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

int32 LNode :: GetCount (logical chknode )
{
  int32       count   = ERIC;

BEGINSEQ
  if ( chknode && Check(AUTO,YES) )                  ERROR
  
  if ( noderefp )  
  {
    if ( (count = noderefp->WSGetCount()) < 0 )      ERROR
  }
  else
    count = nodeinst->GetCount();

RECOVER
  count = ERIC;
ENDSEQ
  return (count);

}

/******************************************************************************/
/**
\brief  GetDBIndex - 


\return order - 

\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBIndex"

DBIndex *LNode :: GetDBIndex (char *key_name_w )
{
  ref          *refptr;
  DBIndex      *order = NULL;
  if ( !key_name_w )
    order = noderefp ? noderefp->get_refsakcb() : NULL;
  else
    if ( refptr = GetIndex(key_name_w) )
      order = refptr->get_refsakcb();

  return(order);
}

/******************************************************************************/
/**
\brief  GetExtInst - 


\return instptr - 

\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInst"

void *LNode :: GetExtInst (char *extinst )
{
  char     *instptr;

BEGINSEQ
  if ( Check(YES) )                                   ERROR

  if ( Switch(AUTO) )                                 ERROR

  if ( nodeinst->Get(extinst) )                       ERROR
  nodecur = 0;
  instptr = nodeinst->get_iselarea();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  GetGenAttrNode - 


\return acgnodeptr - 

\param  w_fldnames - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrNode"

ACGenericAttr *LNode :: GetGenAttrNode (char *w_fldnames )
{
  ACGenericAttr  *acgnodeptr = NULL;
  node           *nodeptr;
  char            string[ID_SIZE+1];
  char           *stringptr  = NULL;
  CTX_Property   *context    = NULL;
  char           *lastpos    = NULL;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
  
  if ( !w_fldnames )
  {
    if ( !noderefp || !noderefp->stscusr1() )        LEAVESEQ
    if ( w_fldnames = noderefp->get_refsakcb()->get_key_def()->get_kcbgfmcb()->fmcbname )
      w_fldnames = gvtxbts(string,w_fldnames,ID_SIZE);
  }
    
  if ( w_fldnames )
    w_fldnames = stringptr = strdup(w_fldnames);
  if ( w_fldnames && (lastpos = STRSearchChar(w_fldnames,'.',YES)) )
  {
    *lastpos = 0;
    if ( nodeptr = *GetNodePtr(w_fldnames) )
      context = Bnodeptr->get_context();
    w_fldnames = lastpos+1;
  }
  if ( !(acgnodeptr = Bnodeinst->GetGenAttrNode(w_fldnames,context)) )
                                                     SDBERR(185)

RECOVER
  acgnodeptr = NULL;
ENDSEQ
  if ( stringptr )
    free(stringptr);
  return(acgnodeptr);
}

/******************************************************************************/
/**
\brief  GetGenAttrType - 


\return attrtype - 

\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrType"

int LNode :: GetGenAttrType (char *fldnames )
{
  ACGenericAttr  *acgnodeptr;
  return (   (acgnodeptr = GetGenAttrNode(fldnames)) 
           ? acgnodeptr->get_attr_type()
           : UNDEF );


}

/******************************************************************************/
/**
\brief  GetGenOrderType - 


\return attrtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenOrderType"

int LNode :: GetGenOrderType ( )
{
  ref           *refptr;
  int            attrtype = UNDEF;

BEGINSEQ
  if ( Check(YES,NO) )	                             ERROR

  if ( !noderefp || !noderefp->stscusr1() )          LEAVESEQ

  if ( !(refptr = noderefl->GetReference(noderefp->get_refsakcb()->get_key_def()->scbsmcb->smcbname))) 
                                                     SDBERR(79)
  attrtype = ((gmvl *)refptr)->GetAttributeType(noderefp);

RECOVER

ENDSEQ
  return(attrtype);

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

EB_Number LNode :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number     ebsnum = 0;

BEGINSEQ
  if ( chknode && Check(AUTO) )                      ERROR
  if ( indx0 == AUTO )
    indx0 = nodecur;
  if ( nodewrit != 255 && indx0 == AUTO && (indx0 = GetCount()-1) != 0 )
                                                     ERROR
  
  if ( nodewrit == 255 ||
       (indx0 == nodecur && nodeinst && nodeinst->IsPositioned()) )
    ebsnum = nodeinst->GetID();
  else
    if ( noderefp )
      ebsnum = noderefp->WSGetID(indx0);
  if ( pif_opt )
    ebsnum.FromPIF(IsPIF());
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

EB_Number LNode :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  int32  indx0;
  EB_Number ebsnum = 0;

BEGINSEQ
  if ( !keyptr )                                     ERROR
  if ( chknode && Check(YES) )                       ERROR
  
  if ( noderefp && noderefp->get_refsakcb()->get_key_def() && 
       nodefield->fmcbdim != 1                                )
    indx0 = noderefp->WSGetIndex(keyptr,0,YES);
  else
  {
    Get(keyptr);
    indx0 = nodecur;
  }
    
  if ( indx0 == AUTO )                                   ERROR
  ebsnum = GetID(indx0,NO,pif_opt);
RECOVER

ENDSEQ
 return(ebsnum);

}

/******************************************************************************/
/**
\brief  GetIKRef - 


\return refptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIKRef"

ref *LNode :: GetIKRef ( )
{
  kcb     *kcbptr;
  ref     *refptr = NULL;
BEGINSEQ
  if ( nodefield->fmcbityp != T_VOID )
  {
    if ( !(kcbptr = nodefield->GetDBStruct()->smcbidky) )
                                                       ERROR
    refptr = GetIndex(kcbptr->scbsmcb->smcbname);
  }
  else
    refptr = GetIndex(NULL);

RECOVER

ENDSEQ
  return(refptr);
}

/******************************************************************************/
/**
\brief  GetIndex - 


\return refptr - 

\param  keynames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

ref *LNode :: GetIndex (char *keynames )
{
  char      name[ID_SIZE];
  refEntry *refeptr;
  refeptr = keynames 
            ? noderefl->GetEntry(gvtxstb(name,keynames,ID_SIZE))
            : noderefl->GetEntry(1);

  return ( refeptr ? refeptr->get_ref_pointer() : NULL );

}

/******************************************************************************/
/**
\brief  GetInstModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 LNode :: GetInstModCount ( )
{
  int16                   modcount = UNDEF;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  modcount = nodeinst->GetModCount();
RECOVER

ENDSEQ
  return(modcount);
}

/******************************************************************************/
/**
\brief  GetInstance - 


\return instptr - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

void *LNode :: GetInstance (EB_Number entnr )
{
  char      *instptr = NULL;
  logical    term;
BEGINSEQ
  if ( entnr.IsEmpty(object_ref->GetLocalACObject()->IsPIF()) )  
                                                     ERROR
  if ( ProvideInti(entnr) )                          ERROR
  nodewrit = AUTO;
  
  term = nodeinst->Get(entnr);
  if ( term )                                        ERROR
    
  if ( nodeinst->stscsav() )
  {
    if ( nodeacc == PI_Read )
      nodeinst->stsrsav();
    else
    {
      stsssav();
      SetSave();
    }
  }
  if ( instptr = ReserveInstance() )
    objid = Bnodeinst->get_objid();

RECOVER
  nodewrit = NO;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetKey - 


\return key_val - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *LNode :: GetKey (int32 lindx0, logical chknode )
{
  char                   *keyptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                 	     ERROR
  
  if ( lindx0 == AUTO )
    lindx0 = nodecur;
    
  if ( nodefield->fmcbdim == 1 )
  {
    if ( !IsSelected() )
      if ( !Get(FIRST_INSTANCE,NO) )                 ERROR
    keyptr = GetSortKeyLength(NO)
             ? ExtractSortKey(NULL,nodeinst->get_iselarea(),NO)
             : ExtractKey(NULL,nodeinst->get_iselarea());
    LEAVESEQ
  }
  
  if ( lindx0 == AUTO )                              ERROR
  if ( lindx0 != nodecur && nodecur != AUTO )
    Switch(AUTO);
    
  if ( noderefp && noderefp->get_refsakcb()->get_key_def() )
  {
    if ( !(keyptr = noderefp->WSGetKey(lindx0,GetKeyArea())) )
                                                       ERROR
    nodecur = lindx0;
    if ( IsGUID() )
      keyptr = GUIDToString(NULL,(guid *)keyptr);
  }
  else if ( !nodesel )
  {
    if ( !GetKeySMCB() )                             SDBERR(174)
    if ( lindx0 != nodecur || !IsSelected() )
      if ( !Get(lindx0,NO) )                         ERROR
    if ( !(keyptr = ExtractKey(NULL,nodeinst->get_iselarea(),NO)) )
                                                     ERROR
  }
  if ( !(keyptr = GetKeyAt(nodecur,FOREWARD,keyptr)) ) ERROR

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  GetKeyAt - 


\return keyptr - 

\param  indx0 - Position in collection
\param  direction - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyAt"

char *LNode :: GetKeyAt (int32 indx0, int16 direction, char *keyptr )
{
  int32       count;
  int32       next;
BEGINSEQ
  if ( nodesel && !GetKeySMCB() )                  SDBERR(174)
  next = indx0;
  
  if ( keyptr = KeyCheck(next,keyptr) )              LEAVESEQ
    
  switch ( direction )
  {
    case FOREWARD: count = GetCount();
                   while ( next < count && !(keyptr = KeyCheck(next++,keyptr)) ) ;
                   break;
    case BACKWARD: while ( next >= 0 && !(keyptr = KeyCheck(next--,keyptr)) ) ;
                   break;
    default      : keyptr = KeyCheck(next,keyptr);
  }

  
  
// noch ignorieren wir direction

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  GetMainBase - 


\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 LNode :: GetMainBase ( )
{

  return(0);

}

/******************************************************************************/
/**
\brief  GetMainRef - 


\return refptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainRef"

ref *LNode :: GetMainRef ( )
{
  ref      *refptr;
  char     *fldname;
  char      fldnames[ID_SIZE+1];
  refptr = noderefmain ? noderefmain          
                       : noderefl && noderefl->GetCount() 
                         ? noderefl->GetEntry(1)->get_ref_pointer() 
                         : NULL;

  if ( refptr && refptr->IsTemporary() &&  // wegen temporärer indizes in bina
       !nodefield->get_log_reference()   ) // extent not temporary
    refptr = NULL;
    
  if ( refptr && (fldname = refptr->GetGenAttribute()) )
    refptr = ((gmvl *)refptr)->GetReference(nodeinst ? GetGenAttrNode(gvtxbts(fldnames,fldname,ID_SIZE))->get_attr_type() : 0,nodewrit);

  return(refptr);
}

/******************************************************************************/
/**
\brief  GetRef - 


\return refptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRef"

ref *LNode :: GetRef ( )
{

  return(noderefp);

}

/******************************************************************************/
/**
\brief  GetRefModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 LNode :: GetRefModCount ( )
{
  int16                   modcount = UNDEF;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( noderefp )
    modcount = noderefp->GetModCount();
RECOVER

ENDSEQ
  return(modcount);
}

/******************************************************************************/
/**
\brief  GetSelectedKey - 


\return keyptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedKey"

char *LNode :: GetSelectedKey (logical chknode )
{
  char      *keyptr = NULL; 
  kcb       *kcbptr;
BEGINSEQ
  if ( chknode && Check(YES) )	                     ERROR

  if ( IsSelected() )
  {
    keyptr = GetSortKeyLength(NO)
             ? ExtractSortKey(NULL,nodeinst->get_iselarea(),NO)
             : ExtractKey(NULL,nodeinst->get_iselarea());
  }
  else if ( nodecur != AUTO && noderefp && 
            (kcbptr = noderefp->get_refsakcb()->get_key_def()) ) 
  {
    if ( !(keyptr = noderefp->WSGetKey(0,GetKeyArea())) )
                                                     ERROR
    if ( !kcbptr->scbsmcb->smcbsts.stscnof() )
      kcbptr->kcbkpt(nodeinst->get_iselarea(),keyptr);
  }
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  GetSystemNode - 


\return sysnode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemNode"

ACExtend *LNode :: GetSystemNode ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  Group - 


\return term - Termination code

\param  nodeptr - 
\param  distinct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Group"

logical LNode :: Group (node *nodeptr, logical distinct )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  HasFilter - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFilter"

logical LNode :: HasFilter ( )
{

  return(nodesel ? YES : NO);

}

/******************************************************************************/
/**
\brief  InitExtendRef - 


\return term - Termination code

\param  dbext_ptr - 
\param  extref - 
\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExtendRef"

logical LNode :: InitExtendRef (DBExtend *dbext_ptr, EB_Number *extref, logical extadd )
{
  EB_Number   *ext_ref;
  int16        mbnumber = 0;
  logical      term     = NO;
  int16        index  = 0;
BEGINSEQ
  TypeKey    tkey(nodefield->fmcbname,nodefield->fmcbnsid);
  if ( !(ext_ref = object_ref->GetLocalACObject()->GetExtendRef(tkey)) )
  {
    SDBCERR
    if ( !(extadd && nodeacc == PI_Write) )          SDBERR(68)
    if ( !(ext_ref = object_ref->GetLocalACObject()->AddExtendRef(dbext_ptr)) )
                                                     ERROR
  }
  if ( InitReference() )                             ERROR
  *extref = *ext_ref;  
  
  if ( (mbnumber = dbext_ptr->GetMainBase(object_ref)) == AUTO )       
                                                     SDBERR(169)
  if ( noderefl->Setup(extref,0,mbnumber,nodeacc) )  ERROR
  
  stssfil();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitReference"

logical LNode :: InitReference ( )
{
  DBFieldDef *field_def;
  logical     term     = NO;
BEGINSEQ
  if ( !noderefl )   
  {
    if ( !nodefield->GetDBStruct(object_ref->GetDictionary()) )
      if ( nodefield->fmcbityp != T_VOID )           ERROR
    
    if ( nodefield->fmcbsmcb )
      id_key = nodefield->fmcbsmcb->smcbidky;
      
    field_def = nodefield->GetDBField( object_ref->IsDBHandleDict()
                                       ? object_ref->GetSystemVersion()
                                       : object_ref->GetSchemaVersion() );
    if ( !(noderefl = new refTable(object_ref->GetLocalACObject(),field_def,&act_handle)) )     
                                                     SDBERR(95)
                                                     SDBCERR
    noderefmain = GetIKRef();
    SetOrderRef(GetMainRef());
    if ( !stscerr() && !nodenode && nodefield->get_log_reference() )
      stssfil();        // temporäre Extents (aber auch fremde Extents ?)
  }
  
  noderefl->OldinstRequested(noderefp);
RECOVER
  nodeidnt = 0;
  term     = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsLocalNode - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalNode"

logical LNode :: IsLocalNode ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  IsReadOnly - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical LNode :: IsReadOnly ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( bnode::IsReadOnly() )                         LEAVESEQ
  
  if ( highnod && !highnod->IsWrite() )              LEAVESEQ
  
  if ( nodetype == NT_ACGenericAttr )
    if ( !CanUpdateCollection() )                    LEAVESEQ
  
  if ( nodenode && nodenode->get_nodetype() == NT_ACGenericAttr ) //bis 21.10.2002 == NT_ACAttribute
    if ( !nodenode->CanUpdateCollection() )          LEAVESEQ
  
  if ( is_memo && nodenode->IsPositioned() && !GetID(FIRST_INSTANCE).IsEmpty() )  
  {
    Get(FIRST_INSTANCE);
    if ( !IsWrite() )                                LEAVESEQ
  }
  
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  KeyCheck - 


\return keyptr - 

\param  indx0 - Position in collection
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyCheck"

char *LNode :: KeyCheck (int32 indx0, char *keyptr )
{
  kcb       *kcbptr;
BEGINSEQ
  if ( Bnodeinst->GenerateEvent(DBP_Read) )          ERROR
  if ( Bnodeinst->get_context()->IsHidden() )        ERROR
    
  if ( nodesel )
  {
    if ( key_check )  
    {
      if ( !(kcbptr = noderefp->get_refsakcb()->get_key_def()) )
                                                     SDBERR(174)
      if ( kcbptr->scbsmcb->smcbsts.stscnof() )      ERROR
      if ( !(keyptr = noderefp->WSGetKey(0,GetKeyArea())) )
                                                     ERROR
      kcbptr->kcbkpt(nodeinst->get_iselarea(),keyptr);
      if ( CheckExpression() )                       ERROR
    }
    else
    {
      if ( !Get(indx0,NO) )                          ERROR
      if ( !Exist() || !(keyptr = ExtractKey(NULL,nodeinst->get_iselarea(),NO)) )
                                                     ERROR
    }
  }


RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  LNode - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LNode"

     LNode :: LNode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
                     : bnode (obhandle,nodeptr,dbfield_ptr,highctx,accopt),
  noderefl(NULL),
  noderefp(NULL),
  noderefmain(NULL),
  nodesel(NULL),
  act_handle(NULL)

{




}

/******************************************************************************/
/**
\brief  i1 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LNode"

     LNode :: LNode ( )
                     : bnode (),
  noderefl(NULL),
  noderefp(NULL),
  noderefmain(NULL),
  nodesel(NULL),
  act_handle(NULL)
{



}

/******************************************************************************/
/**
\brief  i2 - 


\param  lnoderef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LNode"

     LNode :: LNode (LNode &lnoderef )
                     : bnode(lnoderef),
  noderefl(NULL),
  noderefp(NULL),
  noderefmain(NULL),
  nodesel(NULL),
  act_handle(NULL)
{

  noderefl    = lnoderef.get_noderefl();
  SetOrderRef(lnoderef.get_noderefp());
  noderefmain = lnoderef.get_noderefmain();  

  if ( lnoderef.stscfil() )
    stssfil();


}

/******************************************************************************/
/**
\brief  Locate - 


\return term - Termination code

\param  entnr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical LNode :: Locate (EB_Number entnr, logical read_opt )
{
  PropertyHandle  *void_pi;
  int32             indx0 = AUTO;
  void            *instptr;
  char             keyarea[MAX_KEYLEN];
  EB_Number        defent = entnr;
  logical          term = NO;
BEGINSEQ
  if ( read_opt )
    Switch(AUTO);
  
  if ( IsPIF() )
    entnr.ToPIF(YES);
  
  if ( !noderefp )                                   ERROR
  if ( noderefp->get_refsakcb()->get_key_def() )
  {
    if ( !noderefp->IsIdentityOrder() )
    {
      if ( !(void_pi = object_ref->GetVoidPI()) )      ERROR
      if ( !(instptr = &void_pi->Get(defent.get_ebsnum())) )
                                                     ERROR
      ExtractSortKey(keyarea,instptr,NO);
    }
    indx0 = noderefp->WSGetIndex(keyarea,entnr,YES);
  }
  
  if ( indx0 == AUTO )
    indx0 = noderefp->WSGetIndex(entnr);
  if ( indx0 == AUTO )                               ERROR

  if ( !read_opt )
    nodecur = indx0;
  else
    if ( !Get(indx0) )                               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateID - 


\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateID"

logical LNode :: LocateID (binti *bintiptr )
{
  kcb       *kcbptr;
  char      *skey;
  logical    term = NO;
BEGINSEQ
  if ( !noderefp )                                   ERROR

  if ( kcbptr = noderefp->get_refsakcb()->get_key_def() )
  {
    if ( kcbptr->scbsmcb->smcbsts.stscnof() )
    {
      if ( !bintiptr->IsPositioned() )                ERROR
      skey = GetKeyArea();  
      *(EB_Number *)skey = nodeinst->GetID();
    }
    else
      skey = ExtractSortKey(NULL,bintiptr->get_iselarea());
    if ( !skey )                                     ERROR
    nodecur = noderefp->WSGetIndex(skey,bintiptr->GetID().ToPIF(IsPIF()),YES);
  }
  else
    if ( noderefp->WSGetCount() > 0 )
      nodecur = 0;

  if ( nodecur == AUTO )                             ERROR
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
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical LNode :: LocateKey (char *skey, logical exact, logical chknode )
{
  char      keyarea[MAX_KEYLEN];
  char      wskey[MAX_KEYLEN];
  int32      dbindx = AUTO;
  kcb       *kcbptr = NULL;
  logical    term   = NO;

BEGINSEQ
  if ( chknode && Check(YES) )                 	     ERROR

  if ( IsPositioned() && skey )
  {
    SaveKey(wskey,skey);
    if ( !CompareKey(ExtractKey(keyarea,nodeinst->get_iselarea(),NO),wskey,NO) )
                                                     LEAVESEQ
  }
  
  Switch(AUTO);
  if ( !skey )                                       ERROR
  
  if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) &&
       nodefield->fmcbdim != 1                                           )
  {
    if ( IsGUID() )
      skey = (char *)StringToGUID((guid *)NULL,skey);
    if ( (dbindx = noderefp->WSGetIndex(skey,UNDEF,exact)) == AUTO ) 
                                                     ERROR
    nodecur = dbindx;
    nodewrit = NO;
    InitInstance(NULL);  // 8.10.2003, damit stsini nicht gesetzt wird
    kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),skey);
    if ( !GetKeyAt(nodecur,UNDEF,skey) )             ERROR
  }
  else
    if ( !Get(skey) )                                ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  LocatePosition - 


\return term - Termination code

\param  pifent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocatePosition"

logical LNode :: LocatePosition (EB_Number pifent )
{
  int32             lindx0 = 0;
BEGINSEQ
  if ( !noderefp )                                   ERROR
  
  lindx0 = noderefp->GetIndex(pifent);
RECOVER
  lindx0 = 0;
ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical LNode :: Lock ( )
{
  logical   term = NO;

BEGINSEQ
  if ( Check(YES) )                                  ERROR
// Referenzen müssen nur gelockt werden, wenn übergeordneter nicht gelockt ist
  if ( nodecur == AUTO )                             SDBERR(73)

  if ( !nodeinst )
    if ( !Get(nodecur) )                             ERROR

  if ( nodeinst->Lock() )                            ERROR
  SetWPT();
RECOVER
  term = YES;
ENDSEQ
  return(term);

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

logical LNode :: LockSet (logical chknode )
{
  logical   term = NO;

BEGINSEQ
  if ( chknode )
  {
    if ( Check(YES) )                                ERROR
    if ( Switch(AUTO) )                              ERROR
    if ( inti_buffer )
      inti_buffer->Cancel();
  }
  
  if ( !noderefl || stsclck() )                      LEAVESEQ
  if ( noderefl->stsclck() )                         SDBERR(6)
  if ( term = noderefl->Lock() )                     ERROR
  if ( noderefl->stsclck() )
  {
    stsslck(); 
    SetWPT();
  }
RECOVER
  if ( !term )
    term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Move - 


\return instptr - 

\param  srcenode - 
\param  db_replace - Replace option
\param  w_newkey - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

void *LNode :: Move (node *srcenode, PIREPL db_replace, char *w_newkey, logical setwpt )
{
  smcb     *srcesmcb = srcenode->GetCurrentTypeDef();
  smcb     *targsmcb = GetCurrentTypeDef();
  int16     talevel  = 0;
  int32     indx0    = nodecur;
  EB_Number entnr(GetID(AUTO));
  inti     *srceinti;
  void     *instptr  = NULL;
BEGINSEQ
  if ( Check(YES) )	                             ERROR
  if ( !srcenode->IsPositioned() )                   ERROR

// hier müssen wir noch verhindern, dass in der gleichen collection (ohne neuen Schlüssel) gemoved wird 
// ausserdem muss gesichert werden, dass source und target gleiches Ownerlevel (beide owning oder beide 
// nicht) haben. Wenn source und target nicht owning, müssen beide auf die gleiche Basismenge verweisen. 
// ansonsten immer Copy!!

  srcenode->Save(NO,NO,NO);
  talevel = StartTA();
  Switch(AUTO);
  
  if ( nodefield->get_weak_typed() && 
       memcmp(srcesmcb->smcbname,targsmcb->smcbname,ID_SIZE) && 
       srcenode->IsBasedOn(targsmcb->smcbname)                )
    if ( SetType(srcesmcb->smcbname) )              ERROR
  targsmcb = GetCurrentTypeDef();    
  
  if ( memcmp(srcesmcb->smcbname,targsmcb->smcbname,ID_SIZE) || 
       GetObjectHandle()->GetDBHandle() != srcenode->GetObjectHandle()->GetDBHandle() )
  {
    instptr = CopyInst(srcenode,db_replace,REPL_all,w_newkey,AUTO,NO);
    LEAVESEQ
  }
  
  srceinti = srcenode->get_nodeinst();
  
  if ( srcenode->DeleteIndex(NO) )                  ERROR
  
  if ( !entnr.IsEmpty() && GetCollectionID() == srcenode->GetCollectionID() )  // move within the same collection
    indx0 = noderefp->GetIndex(entnr);                                        // re-locate position

  instptr = AddInstance((binti *)srceinti,indx0);
  srcenode->ResetInstance();
  if ( !instptr )                                   ERROR

RECOVER
  instptr = NULL;
ENDSEQ
  if ( talevel )
    if ( StopTA(instptr == NULL) )
      instptr = NULL;
  return(instptr);
}

/******************************************************************************/
/**
\brief  MoveDown - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical LNode :: MoveDown ( )
{
  kcb          *kcbptr;
  int16         talevel = 0;
  int32          cur_indx;
  int32          next_indx;
  int32          temp_indx = 0x7FFFFFFF;
  logical       term = NO;
BEGINSEQ
  if ( Check(YES) )	                             ERROR
  if ( !IsPositioned() )                             ERROR

  Save(NO,NO);
  
  talevel = StartTA();
  if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) )
  {
    if ( !kcbptr->scbsmcb->smcbsts.stscold() )       SDBERR(320)

    dbf   ident(this,"__AUTOIDENT",NO);
    cur_indx = ident.GetInt();
    if ( Position(1,NO) < 0 )                        ERROR
    next_indx = ident.GetInt();
  
    if ( !Get((char *)&cur_indx) )                   ERROR
    ident = dbf(temp_indx);
    Modify();
    if ( !Get((char *)&next_indx) )                  ERROR
    ident = dbf(cur_indx);
    Modify();
    if ( !Get((char *)&temp_indx) )                  ERROR
    ident = dbf(next_indx);
    Modify();
    if ( Save(NO,NO,NO) )                            ERROR
  }
  else
  {
    if ( (cur_indx = ((mvlp *)noderefp)->MoveDown(nodecur)) == AUTO ) 
                                                     ERROR
    if ( !Get(cur_indx) )                            ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  MoveUp - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical LNode :: MoveUp ( )
{
  kcb          *kcbptr;
  int16         talevel = 0;
  int32          cur_indx;
  int32          prev_indx;
  int32          temp_indx = 0x7FFFFFFF;
  logical       term = NO;
BEGINSEQ
  if ( Check(YES) )	                             ERROR
  if ( !IsPositioned() )                             ERROR

  Save(NO,NO);
  
  talevel = StartTA();
  if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) )
  {
    if ( !kcbptr->scbsmcb->smcbsts.stscold() )       SDBERR(320)

    dbf   ident(this,"__AUTOIDENT",NO);
    cur_indx = ident.GetInt();
    if ( Position(-1,NO) < 0 )                       ERROR
    prev_indx = ident.GetInt();
  
    if ( !Get((char *)&cur_indx) )                   ERROR
    ident = dbf(temp_indx);
    Modify();
    if ( !Get((char *)&prev_indx) )                  ERROR
    ident = dbf(cur_indx);
    Modify();
    if ( !Get((char *)&temp_indx) )                  ERROR
    ident = dbf(prev_indx);
    Modify();
    if ( Save(NO,NO,NO) )                            ERROR
  }
  else
  {
    if ( (cur_indx = ((mvlp *)noderefp)->MoveUp(nodecur)) == AUTO ) 
                                                     ERROR
    if ( !Get(cur_indx) )                            ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);
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

char *LNode :: NextKey (char *skey, int16 switch_level )
{
  int32  next;
  char     *keyptr = NULL; 
  kcb      *kcbptr;
  char      savekey[513];

BEGINSEQ
  if ( Check(YES) )	                              ERROR
  next = nodecur+1;
  
  if ( nodecur == AUTO && !skey )
  {
    if ( !(keyptr = FirstKey(NO)) )                   ERROR
                                                      LEAVESEQ
  }

  Switch(AUTO);
  if ( noderefp && (kcbptr = noderefp->get_refsakcb()->get_key_def()) )
  {
    if ( skey )
    {
      memcpy(savekey,skey,GetSortKeyLength(NO));
      if ( LocateKey(skey,NO,NO) )                      ERROR
      next = nodecur;
      while ( !CompareSortKey(noderefp->WSGetKey(next,GetKeyArea()),savekey,NO) )
        next++;
    }

    if ( !(keyptr = noderefp->WSGetKey(next,GetKeyArea())) )
                                                       ERROR

    if ( kcbptr->scbsmcb->smcbsts.stscnof() )  // __IDENTITY
      ((EB_Number *)keyptr)->FromPIF(IsPIF());  
                                                           
    nodewrit = NO;
    nodecur = next;
    Initialize_intern(NULL,NO);                // 5.10.2004, war vorher YES
    if ( !kcbptr->scbsmcb->smcbsts.stscnof() )
      kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),keyptr);
    if ( IsGUID() )
      keyptr = GUIDToString(NULL,(guid *)keyptr);
  }
  else if ( !nodesel )
  {
    if ( !GetKeySMCB() )                             SDBERR(174)
    if ( !Get(next,NO) )                             ERROR
    if ( !(keyptr = ExtractKey(NULL,nodeinst->get_iselarea(),NO)) )
                                                     ERROR
    next = nodecur;
  }
  if ( !(keyptr = GetKeyAt(next,FOREWARD,keyptr)) ) ERROR

RECOVER
  keyptr = NULL;
  nodecur = AUTO;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  PathAdd - 


\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PathAdd"

logical LNode :: PathAdd (logical global_add )
{
  char                    keyarea[MAX_KEYLEN];
  logical                 trans;
  logical                 term = NO;
BEGINSEQ
  relative_index = LAST_INSTANCE;
  
  if ( stscold() && nodenode )
  {
//  if ( !nodenode->IsPositioned() )                 ERROR
    if ( ((LNode *)nodenode)->PathAdd(global_add) )  ERROR
  }
  if ( GetSortKeySMCB() )
  {
    ExtractSortKey(keyarea,nodeinst->get_iselarea(),NO);
    if ( LocateKey(keyarea,YES,NO) )
    {
      if ( !Add(AUTO,keyarea,NULL,nodeinst->get_iselarea(),global_add) )
                                                     ERROR
    }
    else
      if ( !Get(keyarea) )                           ERROR
    LEAVESEQ
  }
  
  if ( GetKeySMCB() )
  {
    ExtractKey(keyarea,nodeinst->get_iselarea(),NO);
    if ( !Provide(keyarea,global_add) )              ERROR
  }
  else
    if ( !Provide(AUTO,global_add) )                 ERROR


RECOVER
  relative_index = AUTO;
  term = YES;
ENDSEQ
  if ( trans )
    stsstrans();
  return(term);
}

/******************************************************************************/
/**
\brief  PathCreateCopy - 


\return nodeptr - 

\param  top_node - 
\param  accmode - 
\param  copy_selection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PathCreateCopy"

node *LNode :: PathCreateCopy (node *top_node, PIACC accmode, logical copy_selection )
{
  node                  **pnodeptr;
  node                   *parent  = NULL;
  node                   *nodeptr = NULL;
  char                   *expr;
BEGINSEQ
  if ( !highnod                        ||           // extent node
       top_node == this                    )        // top node
  {
    if ( !(nodeptr = CreateCopyNode()) )             ERROR
  }
  else
  {
    parent = highnod->PathCreateCopy(top_node,accmode,copy_selection);
    if ( !(pnodeptr = parent->GetNodePtr(prop_path)) ||
         !(nodeptr = *pnodeptr) )                    SDBERR(99)
         
    nodeptr->stssold();
    nodeptr->set_auto_provide(auto_provide);
    nodeptr->set_auto_position(auto_position);
    nodeptr->set_auto_key(auto_key);
    
    if ( nodesel && (expr = nodesel->GetExpression()) )
      ((LNode *)nodeptr)->SetExpression(expr);
  }
  if ( nodeptr )
  {
    if ( accmode != PI_undefined )
      nodeptr->ChangeMode(accmode);
    
    if ( copy_selection && Exist() )
    {
      if ( stscusr2() )      // VOID-Extend
        nodeptr->Get(GetID(AUTO).get_ebsnum());
      else
        nodeptr->Get(GetCurrentIndex());
    }
  }



RECOVER
  if ( nodeptr )
    delete nodeptr;
  else if ( parent )
    delete parent;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
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

int32 LNode :: Position (int32 count, logical chknode )
{
  int32     indx0     = nodecur;
  int       direction = FOREWARD;
  logical   term = NO;
BEGINSEQ
  if ( !count )                                      LEAVESEQ
  if ( chknode && Check(YES) )	                     ERROR

  if ( nodecur >= 0 && nodecur+count < 0 )
  {
    indx0 = AUTO;
    Switch(AUTO);                                    LEAVESEQ
  }
  
  if ( inti_buffer && !stscusr3() )
  {
    if ( !GetBuffer(nodecur,count) )   ERROR
    indx0 = nodecur;
  }
  else 
  {
    if ( count <= 0 )
    { 
      direction = BACKWARD;
      count     = -count;
    }
    
    if ( nodecur == AUTO )
      indx0 = direction == FOREWARD ? FIRST_INSTANCE : LAST_INSTANCE;
    else
      indx0 = nodecur+direction;
    
    if ( (indx0 = GetAt(indx0,direction,NO)) == AUTO ) ERROR
    while ( indx0 != AUTO && --count )
      indx0 = GetAt(indx0+direction,direction,NO);
  }
RECOVER
  indx0 = AUTO;
ENDSEQ
  return(indx0);

}

/******************************************************************************/
/**
\brief  Provide - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEKP - 


\param  skey - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *LNode :: Provide (char *skey, logical global_add )
{
  char     *keyptr;
  char      wskey[MAX_KEYLEN];
  char     *instptr = NULL;

BEGINSEQ
  if ( !skey || Check(YES) )                          ERROR
  SaveKey(wskey,skey);
  instptr = nodeinst->get_iselarea();

  if ( nodefield->fmcbdim != 1 )
  {
    if ( Get(wskey) )                                 LEAVESEQ
    SDBCERR
  }
  else
  {
    if ( Get(FIRST_INSTANCE) )
    {
      // Vergleich mit Sortkey neu, 13.4.98, vorher nur IK-Abfrage
      if ( keyptr = ExtractSortKey(NULL,NULL,NO) )
      {
        if ( !CompareSortKey(wskey,keyptr,NO) )      LEAVESEQ
      }
      else
      {
        if ( !(keyptr = ExtractKey(NULL,NULL)) )     SDBERR(153)
        if ( !CompareKey(wskey,keyptr) )             LEAVESEQ
      }
      if ( Delete(FIRST_INSTANCE) )                  ERROR
    }  
    else 
      Delete(FIRST_INSTANCE);            // Fehlerkorrektur
  }  

  if ( !Add(AUTO,wskey,NULL,NULL,global_add) )       ERROR


RECOVER
  SDBEV1(nodefield->fmcbtype,ID_SIZE)
//  instptr = NULL;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  i1 - 


\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *LNode :: Provide (int32 lindx0, logical global_add )
{
  char     *instptr = NULL;

BEGINSEQ
  if ( !Get(lindx0) ) 
  {
    SDBCERR
    Add(lindx0,NULL,NULL,NULL,global_add);           SDBCERR
  }
  instptr = nodeinst->get_iselarea();

RECOVER

ENDSEQ
 return(instptr);

}

/******************************************************************************/
/**
\brief  i2 - 


\param  datarea - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *LNode :: Provide (void *datarea, logical global_add )
{
  void                   *instptr = NULL;
  char                    key[MAX_KEYLEN];
  char                   *keyptr;
BEGINSEQ
  if ( !datarea || Check(YES) )                       ERROR

  if ( nodefield->fmcbdim != 1 )
  {
    ExtractSortKey(key,(char *)datarea,NO);
    if ( instptr = Get(key) )                         LEAVESEQ
    SDBCERR
  }
  else
  {
    if ( instptr = Get(FIRST_INSTANCE) )
    {
      ExtractKey(key,(char *)datarea,NO);
      if ( !(keyptr = ExtractKey(NULL,NULL)) )       SDBERR(153)
      if ( !CompareKey(key,keyptr) )                 LEAVESEQ
      if ( Delete(FIRST_INSTANCE) )                  ERROR
    }  
    else 
      Delete(FIRST_INSTANCE);            // Fehlerkorrektur
  }  

  instptr = Add(AUTO,NULL,NULL,(char *)datarea,global_add);

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  RegisterHandle - 


\return term - Termination code

\param  cs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterHandle"

logical LNode :: RegisterHandle (CSA_Handle *cs_handle )
{

  act_handle = cs_handle ? cs_handle : this;
  return(NO);
}

/******************************************************************************/
/**
\brief  ReleaseField - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseField"

logical LNode :: ReleaseField ( )
{

  return ( object_ref->GetLocalACObject()->ReleaseField(nodefield) );

}

/******************************************************************************/
/**
\brief  RemoveFromCollection - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveFromCollection"

logical LNode :: RemoveFromCollection ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  if ( !IsWrite() )                                  SDBERR(28)

  if ( nodecur == AUTO )                             SDBERR(76)
    
  nodedel(nodecur,NO);        

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveGUID - 


\return term - Termination code

\param  transaction - Transaction option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveGUID"

logical LNode :: RemoveGUID (logical transaction )
{
  int16              talevel = 0;
  logical            term;
BEGINSEQ
  if ( transaction )
    talevel = StartTA();
    
  if ( nodeinst->RemoveGUID() )                      ERROR
  
  if ( transaction )
  {
    Modify();  
    Save(NO,NO,NO);
  }

RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    if ( StopTA(term) )
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveReference"

logical LNode :: RemoveReference ( )
{

  if ( noderefl )
  {
    noderefl->RemoveReference();
    delete noderefl;
    noderefl = NULL;
  }
  SetOrderRef(NULL);
  noderefmain = NULL;
  return(NO);
}

/******************************************************************************/
/**
\brief  Rename - 


\return term - Termination code

\param  identkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rename"

logical LNode :: Rename (char *identkey, logical chknode )
{
  int16     talevel = 0;
  kcb      *kcbptr  = NULL;
  logical   term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  if ( !IsWrite() )                                  SDBERR(28)

  if ( noderefp )
    kcbptr = noderefp->get_refsakcb()->get_key_def();
  if ( (!kcbptr && !(kcbptr = nodefield->fmcbsmcb->smcbidky)) ||
       kcbptr->scbsmcb->smcbsts.stscnof()  )         SDBERR(71)

  talevel = StartTA();
  kcbptr->kcbkpt(GetKeyInstance(nodeinst,NULL),identkey); 

  Modify();
  if ( Save(NO,NO,NO) )                              ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);

}

/******************************************************************************/
/**
\brief  RepairIndex - 


\return term - Termination code

\param  key_name - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RepairIndex"

logical LNode :: RepairIndex (char *key_name, char *attrstr )
{
  int16                   talevel = 0;
  logical                 term = NO;
BEGINSEQ
  if ( key_name && *key_name > ' ' && *key_name != '*' )
    if ( SetOrder(key_name,UNDEF,attrstr) )            ERROR

  talevel = StartTA();
  
  if ( key_name && *key_name == '*' )
  {
    noderefl->stssold();
    term = SetupIndex();
  }
  else
    term = noderefp->Repair();

  StopTA(term);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveField - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveField"

logical LNode :: ReserveField ( )
{

  return ( object_ref->GetLocalACObject()->ReserveField(nodefield) );

}

/******************************************************************************/
/**
\brief  ReserveInstance - 


\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveInstance"

char *LNode :: ReserveInstance ( )
{
  char                   *instptr = NULL;
BEGINSEQ
  nodewrit = NO;
  instptr = nodeinst->get_iselarea();
  if ( nodeacc == PI_Read )                          LEAVESEQ
    
  if ( nodeacc == PI_Write) 
  {                         
    if ( nodefield->get_update() ) 
      nodeinst->Reserve();
    else
    {
      nodewrit = nodenode && Bnodenode->get_nodewrit();
      LEAVESEQ
    }
  }

  switch ( nodeinst->stscwpt() )
  {
    case 0 : nodewrit = nodeacc != PI_Read ? !IsInstReadOnly() : NO;  
             break;
    case 1 : nodewrit = NO;                             
             break;
    case 2 : nodewrit = YES;
             SetWPT();                                  
             break;
  }

/* gültig bis 11.8.05
  nodewrit = NO;
    
  instptr = nodeinst->get_iselarea();
  if ( nodeacc == PI_Read )                          LEAVESEQ
  
  if ( nodeacc == PI_Write && 
       (nodefield->get_update() || (nodenode && Bnodenode->IsReserved() != 2)) )
    nodeinst->Reserve();
  else
  {
    if ( IsInstReadOnly() )                          LEAVESEQ
  }
    
  switch ( nodeinst->stscwpt() )
  {
    case 0 : nodewrit = nodeacc != PI_Read ? YES : NO;  break;
    case 1 : nodewrit = NO;                             break;
    case 2 : nodewrit = YES;
             SetWPT();                                  break;
  }

  if ( nodewrit && nodenode && nodeacc == PI_Write )
    if ( Bnodenode->get_nodeacc() == PI_Write && !Bnodenode->get_nodewrit() &&
         nodetype != NT_ACShareBase && Bnodenode->IsReserved() == 1 )
      nodewrit = NO;
*/
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical LNode :: Reset ( )
{
  EB_Number  entnr;
  char       keyarea[MAX_KEYLEN];
  logical    term = NO;
  int32   indx0;

BEGINSEQ
  if ( Check(NO) )                                   ERROR
  if ( (indx0 = nodecur) == AUTO ||
       (entnr = nodeinst->GetID()).IsEmpty() )       ERROR
       
  if ( nodeinst->IsNewInstance() )
  {
    // 30.3.03, sonst fehler für neue instanzen in Transaktionen
    Bnodeinst->ResetSubNodesRecursive();
    nodeinst->Initialize();
    Bnodeinst->ReadEvent(); 
    LEAVESEQ 
  }
  
  if ( Cancel(NO) )                                  ERROR
  
  if ( GenerateEvent(DBP_Read) )                     ERROR
  
  nodewrit = AUTO;
  nodecur = indx0;
  if ( nodeinst->Get(entnr) )                        ERROR
  
  if ( CheckExpression() )                           ERROR
  
  ReserveInstance();
  nodeinst->set_inst_index(nodecur);
  if ( noderefp && noderefp->get_refsakcb()->get_key_def() )
  {
    if ( (indx0 = noderefp->WSGetIndex(ExtractSortKey(keyarea,nodeinst->get_iselarea(),NO),entnr,YES)) == AUTO && 
         (indx0 = noderefp->WSGetIndex(entnr)) == AUTO ) 
                                                     ERROR
    else
      nodecur = indx0;
  }


RECOVER
  term = YES;
  Cancel(YES);
  nodewrit = NO;
ENDSEQ
 if ( !term )
   GenerateEvent(DBO_Read);
  return(term);


}

/******************************************************************************/
/**
\brief  ResetExpression - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetExpression"

logical LNode :: ResetExpression ( )
{

  delete nodesel;
  nodesel = NULL;
  return(NO);
}

/******************************************************************************/
/**
\brief  ResetInstance - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

void LNode :: ResetInstance ( )
{

  bnode::ResetInstance();
  
  if ( noderefp )
    noderefp->ResetRefCuri();   // node sollte aber nicht im ref rummehren

}

/******************************************************************************/
/**
\brief  ResetNode - 


\return reset - 

\param  reset_all - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNode"

logical LNode :: ResetNode (logical reset_all )
{
  logical         reset = NO;

  if ( reset = bnode::ResetNode(reset_all) )
  {  
    if ( reset && noderefl )
    {
      UnlockSet(NO,NO);
      noderefl->Reset();
    } 
  }

  return(reset);

}

/******************************************************************************/
/**
\brief  ResetReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetReference"

logical LNode :: ResetReference ( )
{

  if ( nodecur != AUTO && noderefp )
  {
    UnlockSet(NO,NO);
    bnode::SaveNode(YES,YES);
    
    if ( !noderefl->Save() )           
      if ( noderefl->stscsav() )
        nodenode->get_nodeinst()->stsssav();
  }
  
  if ( noderefl )
    noderefl->Reset();
  return(NO);
}

/******************************************************************************/
/**
\brief  ResetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical LNode :: ResetWProtect ( )
{
  logical   term = NO;
  int32  indx0;

BEGINSEQ
  if ( Check(YES) )                                  ERROR
  if ( nodecur == AUTO )                             SDBERR(76)
  if ( !CheckWProtect() )                            SDBERR(77)
  if ( nodeacc == PI_Read )                          SDBERR(28)

  indx0 = nodecur;
  Save(NO,NO,NO);
  
  nodeinst->ResetWProtect();

  Switch(AUTO);
  if ( !LNode::Get(indx0) )			    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

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

logical LNode :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical   term    = NO;

BEGINSEQ
  if ( !stscfil() )                                  LEAVESEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( nodeinst && (stscmod() || stscsav() || stscwpt() || nodecur != AUTO) )  
  {
    if ( nodecur == AUTO && stscmod() )  // brauchen wir zum automatischen hinzufügen für memos
    {
      if ( nodewrit == 255 )
      {
        term = YES;                                   SDBSET(321)
      }
      else if ( !nodenode || nodenode->IsSelected() )
        term = Add(AUTO,NULL,NULL,nodeinst->get_iselarea()) ? NO : YES;
    }
    if ( nodewrit && nodefield->get_global_identity() )
      ProvideGUID(NO);
    if ( nodeinst->Save(switchopt,overwrite,!nodewrit) )
      term = YES;
    stsrsav();
    stsrmod();
  }

  if ( switchopt )
  {
    ResetInstance();
    stsrwpt();
  }
  else if ( !term && nodesel )
    CheckExpression();

RECOVER
  term = YES;
ENDSEQ
  return(term); 

}

/******************************************************************************/
/**
\brief  SaveInitInst - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveInitInst"

logical LNode :: SaveInitInst ( )
{
  logical   term    = NO;

  if ( nodecur == AUTO && stscmod() )  // brauchen wir zum automatischen hinzufügen für memos
  {
    if ( nodewrit == 255 ) 
    {
      term = YES;                                   SDBSET(321)
    }
    else if ( !nodenode || nodenode->IsSelected() )
      term = Add(AUTO,NULL,NULL,nodeinst->get_iselarea()) ? NO : YES;
  }

  return(term); 

}

/******************************************************************************/
/**
\brief  SaveNode - 


\return term - Termination code

\param  switchopt - 
\param  overwrite - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveNode"

logical LNode :: SaveNode (logical switchopt, logical overwrite )
{
  node       *nodeptr;
  logical     term    = NO;
BEGINSEQ
  if ( !stscfil() )                                  LEAVESEQ
  if ( !noderefp )                                   LEAVESEQ
  
  if ( switchopt )
    UnlockSet(NO,NO);
  
  if ( bnode::SaveNode(switchopt,overwrite) )        ERROR
    
  if ( noderefl->Save() )                            ERROR
  if ( noderefl->stscsav() )
    nodenode->get_nodeinst()->stsssav();

  if ( switchopt && noderefl )
    noderefl->Reset();

RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SaveReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveReference"

logical LNode :: SaveReference ( )
{
  logical  term = NO;
BEGINSEQ
  if ( !noderefl )                                   LEAVESEQ
  if ( noderefl->Save() )                            ERROR
    
  if ( noderefl && noderefl->stscsav() )  // 21.3.2003 Sonst gibt es Endlosschleifen im Reset
    SetSave();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Select - 


\return term - Termination code

\param  nodeptr - 
\param  expression - Expression
\param  min_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

logical LNode :: Select (node *nodeptr, char *expression, int32 min_inst )
{
  int32             lindx0 = 0;
  int32             total  = nodeptr->GetCount();
  logical          term = NO;
BEGINSEQ
  DeleteSet();
  
  if ( expression && nodeptr->SetExpression(expression) )   ERROR
  while ( lindx0 < total )
  {
    if ( min_inst >= 0 && min_inst < lindx0 )
      ; // Reschedule()
    if ( nodeptr->Get(lindx0++) )    // prüfen der Expression
      if ( AddReference(nodeptr,AUTO) )
        term = YES;
  }
RECOVER
  term = YES;
ENDSEQ
  if ( expression ) 
    nodeptr->ResetExpression();
  return(term);
}

/******************************************************************************/
/**
\brief  SetAction - 


\return term - Termination code

\param  simple_action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

logical LNode :: SetAction (SimpleAction *simple_action )
{
  CTX_Property        *conetxt = GetContext();
  logical              term = NO;
BEGINSEQ
  if ( !context )                                    ERROR

  if ( context->CreateAction(simple_action) )        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetAutoIdent - 


\return term - Termination code

\param  autoidnt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoIdent"

logical LNode :: SetAutoIdent (uint32 *autoidnt )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  SetCurrentInti - 



\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentInti"

void LNode :: SetCurrentInti (inti *intiptr )
{

  bnode::SetCurrentInti(intiptr);
  
  if ( nodeinst )
  {
    if ( !Bnodeinst->GetStructAccess()  )  // 20.8.98, optimierung
      Bnodeinst->SetStructAccess(object_ref->GetStructAccess(intiptr->get_struct_def()));  
    if ( !Bnodeinst->IsPositioned() )
      Bnodeinst->SetMBNumber(GetMainBase());
  }

}

/******************************************************************************/
/**
\brief  SetExpression - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical LNode :: SetExpression (char *expression )
{
  PropertyHandle          phdl(this);
  logical                 term = NO;
BEGINSEQ
  ResetExpression();

  if ( !(nodesel = object_ref->GetDictionary()->ProvExpression(NULL,nodefield->fmcbtype,expression,
                                (PropertyHandle *)&ph,object_ref)) )
                                                     ERROR

RECOVER
  ResetExpression();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical LNode :: SetExpression (BNFData *bnf_data )
{
  logical                 term = NO;
BEGINSEQ
  ResetExpression(); 

  if ( !(nodesel = object_ref->GetDictionary()->ProvExpression(NULL,nodefield->fmcbtype,bnf_data,
                                (PropertyHandle *)&ph,object_ref)) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetGenAttribute - 


\return term - Termination code

\param  fldnames - Property name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical LNode :: SetGenAttribute (char *fldnames, int attrtype, char *attrstr )
{
  ACGenericAttr          *nodeptr;
  int16                   talevel = 0;
  logical                 term    = NO;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
  
  if ( !(nodeptr = GetGenAttrNode(fldnames)) )       
  {
    if ( fldnames && *fldnames )                     SDBERR(185)
    term = node::SetGenAttribute(fldnames,attrtype,attrstr);
    LEAVESEQ
  }
                                                     
  talevel = StartTA();
  if ( nodeptr->SetGenAttribute(attrtype,attrstr) )  ERROR
    
//  if ( nodeptr->get_nodeinst()->stscini() )
//    SetMod();  
/*
  if ( noderefp->stscusr1() )             // generic index
  {
    gvtxstb(fldname,fldnames,ID_SIZE);
    keyname = noderefp->get_refsakcb()->GetKeyName();
    if ( !memcmp(noderefl->GetReference(keyname)->GetGenAttribute(),fldname,ID_SIZE) )
      SetOrder(keyname);
  }
*/
RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  SetInstAction - 


\return term - Termination code

\param  simple_action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstAction"

logical LNode :: SetInstAction (SimpleAction *simple_action )
{
  CTX_Structure       *conetxt = GetInstContext();
  logical              term = NO;
BEGINSEQ
  if ( !context )                                    ERROR

  if ( context->CreateAction(simple_action) )        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetMainRef - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMainRef"

logical LNode :: SetMainRef ( )
{
  logical                 term = NO;
  SetOrderRef(GetMainRef());
  return(term);
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

logical LNode :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  ref           *refptr;
  char          *fldname;
  char           fldnames[ID_SIZE+1];
  char          *keynames = strnames;
  char           keyname[ID_SIZE];
  ACGenericAttr *acgnode;
  logical        term = NO;
BEGINSEQ
  if ( Check(AUTO,NO) )	                             ERROR
  
  if ( !strnames || !*strnames )
  {
    if ( noderefp == GetMainRef() )                  LEAVESEQ
  }
  else
    if ( (!attrstr || !*attrstr) && !attrtype && 
         !memcmp(gvtxstb(keyname,strnames,sizeof(keyname)),sk_index->GetKeyName(),ID_SIZE) )
                                                     LEAVESEQ
  Switch(AUTO);

  SDBEV1(nodefield->fmcbsmcb->smcbname,ID_SIZE)
  SDBEV2(strnames,ID_SIZE)
  
  if ( inti_buffer )
    inti_buffer->Cancel();
    
  if ( !strnames || !*strnames )
  {
    if ( !(refptr = GetMainRef()) )                  LEAVESEQ
  }    
  else
  {
    if ( *strnames == '*' )
    {
      if ( *sk_index->GetKeyName() <= ' ' )          LEAVESEQ
      keynames = (char *)sk_index->GetKeyName();
    }
  
    if ( !(refptr = noderefl->GetReference(keynames)) ) 
                                                     SDBERR(79)
    if ( fldname = refptr->GetGenAttribute() )
    {
      acgnode = GetGenAttrNode(gvtxbts(fldnames,fldname,ID_SIZE));
      
      if ( !attrtype && attrstr )
        attrtype = acgnode->GetGenAttrType(attrstr);
      
      if ( !attrtype && *strnames != '*' && noderefp )
        attrtype = ((gmvl *)refptr)->GetAttributeType(noderefp);
      
      if ( !attrtype )
        attrtype = acgnode->get_attr_type();
      
      if ( !(refptr  = ((gmvl *)refptr)->GetReference(attrtype,nodewrit)) )
                                                     ERROR
    }
  }
  
  SetOrderRef(refptr);
  if ( refptr->stscold() && (!nodenode || nodenode->IsPositioned()) ) // index noch nicht aufgebaut
    if ( SetupIndex(YES) )                           ERROR
  
  if ( auto_key )
    Get(FIRST_INSTANCE);

RECOVER
  if ( SDBERROR )
    UtilityHandle::StructFieldError(strnames,
                          nodefield->fmcbsmcb->smcbname);
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetOrderRef - 



\param  refptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrderRef"

void LNode :: SetOrderRef (ref *refptr )
{

  sk_index = (noderefp = refptr) ? refptr->get_refsakcb() : NULL;


}

/******************************************************************************/
/**
\brief  SetSave - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSave"

void LNode :: SetSave ( )
{
  node     *nodeptr = this;
  if ( nodenode && (noderefl->stscmod() || noderefl->stscsav()) )       
  {
    if ( noderefl->stscsav() )
      nodenode->get_nodeinst()->stsssav();
    
    while ( (nodeptr = nodeptr->get_nodenode()) && 
             !nodeptr->stscsav() )
      nodeptr->stsssav();
  }

}

/******************************************************************************/
/**
\brief  SetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical LNode :: SetWProtect ( )
{
  int32      indx0;
  logical   term = NO;

BEGINSEQ
/*
char   fields[ID_SIZE+1];
char   kstring[100];
gvtxbts(fields,nodefield->fmcbname,ID_SIZE);
SDBError().TraceMessage("Check WPT - ",fields,", Key: ",KeyToString(kstring,ExtractKey(NULL,NULL)));
*/
  if ( Check(YES) )                                  ERROR
  if ( CheckAccess(PI_Write) )                       ERROR

  if ( nodefield->get_privilege() != PI_Share )      SDBERR(78)
  if ( !nodewrit )                                   SDBERR(28)

  indx0 = nodecur;
  Save(NO,NO,NO);
  
  if ( nodeinst->SetWProtect() )                     ERROR
  nodewrit = NO;
RECOVER
//SDBError().TraceMessage("SetWPT failed");
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetupIndex - 


\return term - Termination code

\param  tempindx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupIndex"

logical LNode :: SetupIndex (logical tempindx )
{
  ref       *oldref = NULL;
  int32       indx0 = 0;
  logical    term = NO;
  char       string[12];
  logical    create = NO;
BEGINSEQ
  if ( stscerr() )                                   LEAVESEQ
  if ( !noderefl->stscold() && !tempindx )           LEAVESEQ
  if ( !tempindx && object_ref->get_access_mode() == PI_Read )
                                                     ERROR
  if ( noderefl->CheckNew() )
  {
    SDBEV1(nodefield->fmcbname,ID_SIZE);
    
    oldref = noderefp;
    SetOrderRef(noderefl->SelectSourceRef());   // muß auch ohne Reference gehen (für Bina)
    if ( GetCount() > 0 )
    {
      if ( !tempindx && HasWorkspace() ) 
      {
        SDBSET(338)
        term = YES;
      }
      else
      {
// keine Anzeige bei Umstellung auf V8 (Upgrade8)
//        SDBError().DisplayMessage(-410);
//        SDBError().InsertStatField();
    
        StartTA();
        LockSet();
        while ( LNode::Get(indx0++) )
        {
//          SDBError().SetStatField(gvtxltoa(indx0,string,10));
          if ( noderefl->UpdateNew(nodeinst,nodeinst->GetID(),indx0-1) )
            term = YES;
        }
        if ( UnlockSet(NO) )
          term = YES;
        term = StopTA(term);      }
    }
    SetOrderRef(oldref);
    noderefl->ResetNew();
//    SDBError().RemoveStatField();
//    SDBError().DisplayMessage(0,"");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StartTA - 


\return level - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartTA"

int16 LNode :: StartTA ( )
{
  int16     talevel = UNDEF;
  if ( nodeacc > PI_Read )
  {
    if ( !object_ref->GetLocalACObject()->IsInternalTA() )
      stssnof();
    talevel = object_ref->StartTAIntern(NO,YES,AUTO);
  }
  return(talevel);
}

/******************************************************************************/
/**
\brief  StopTA - 


\return term - Termination code

\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopTA"

logical LNode :: StopTA (logical error_case )
{
  int16      saveerr = UNDEF;
  exd       *exdptr;
  logical    term = NO;
BEGINSEQ
  if ( nodeacc == PI_Read )                          LEAVESEQ
    
  saveerr = (int16)SDBERROR;
  
  if ( (term = object_ref->StopTA(AUTO,error_case)) == 2 ) // Cancel transaction
  {
    Error      err;
    err = SDBError();
    term = YES;
    if ( IsPositioned() )
    {
      if ( exdptr = Bnodeinst->GetEXD() )
        exdptr->stssold();
      Reset();
    }
    if ( noderefl )
      noderefl->Refresh();
    SDBError() = err;
  }
  else if ( error_case )
    term = YES;
  
  if ( saveerr )
    SDBISET(saveerr);

  if ( !object_ref->GetLocalACObject()->IsInternalTA() )
    stsrnof();
RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  TARequired - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TARequired"

logical LNode :: TARequired ( )
{

  return ( nodeinst && nodeacc > PI_Read && 
           ( nodecur != AUTO     || 
             nodeinst->stscini() || 
             stscsav() || stscmod() )        );

}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical LNode :: Unlock ( )
{
  logical   term = NO;

BEGINSEQ
  if ( Check(YES) )	                              ERROR
  if ( nodecur == AUTO )                              SDBERR(73)

  if ( nodeinst->Unlock() )                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

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

logical LNode :: UnlockSet (logical extlock, logical chknode )
{
  int       saverr = GetErrorCode();
  logical   term = NO;

BEGINSEQ
  if ( !stsclck() )                                  LEAVESEQ
  if ( chknode )
  {
    if ( Check(YES) )	                             ERROR
//    if ( Switch(AUTO) )                            ERROR
  }
  
  if ( !noderefl->stsclck() )                        
  { 
    stsrlck();                                       
    if ( !noderefl->get_topref()->get_refrex()->get_ebsnum() )
                                                     ERROR
    SDBERR(6)
  }
  
  term = noderefl->Unlock(extlock);
  
  if ( !extlock )
    stsrlck();
RECOVER
  term = YES;
ENDSEQ
  if ( saverr )
    SDBISET(saverr);
  return(term);

}

/******************************************************************************/
/**
\brief  UnregisterHandle - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterHandle"

logical LNode :: UnregisterHandle ( )
{

  act_handle = PCSHandle(NULL);
  return(NO);
}

/******************************************************************************/
/**
\brief  UpdateID - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  bintiptr - 
\param  oldinst - 
\param  entnr - 
\param  temp_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical LNode :: UpdateID (binti *bintiptr, void *oldinst, EB_Number entnr, logical temp_only )
{
  int32     curri = noderefp ? noderefp->GetRefCuri() : AUTO;
  logical  term  = NO;
  if ( !oldinst && curri == AUTO && !entnr.IsEmpty() && 
       noderefp && nodecur != AUTO )
    noderefp->WSGetIndex(entnr);
    
//if ( oldinst && bintiptr->get_struct_def()->CheckKeyMod(bintiptr->get_iselarea(),oldinst) )
// geht so nicht, da dann indizes für referenzen mit einem Key nicht gepflegt werden  
  if ( !oldinst || bintiptr->get_struct_def()->CheckKeyMod(bintiptr->get_iselarea(),oldinst) )
    if ( noderefl->UpdateID(bintiptr,oldinst,entnr,temp_only) )
      term = YES;

  SetSave();
  
  if ( nodecur != AUTO && noderefp && 
       noderefp->GetRefCuri() != AUTO   && noderefp->GetRefCuri() != curri )
    nodecur = noderefp->GetRefCuri();
  nodeinst->set_inst_index(nodecur);

  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  temp_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical LNode :: UpdateID (logical temp_only )
{

  return ( UpdateID(Bnodeinst,
                    noderefl->OldinstRequested() ? Bnodeinst->GetOldInst(NULL) : (char *)NULL,
                    nodeinst->GetID(),temp_only) );


}

/******************************************************************************/
/**
\brief  nodedel - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "nodedel"

logical LNode :: nodedel (int32 lindx0, logical chknode )
{
  EB_Number  entnr;
  logical    term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR

  if ( lindx0 >= 0 )
  {
    if ( !(entnr = noderefp->WSGetID(lindx0)).IsEmpty() ) 
      noderefl->DeleteID(entnr);
  }
  else   // delete complete set
    if ( noderefl ) 
      noderefl->DeleteReference();
    
  SDBRESET
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "nodedel"

logical LNode :: nodedel (EB_Number entnr )
{

  noderefl->DeleteID(entnr);
  SDBRESET
  return(NO);
}

/******************************************************************************/
/**
\brief  nodetwm - 



\param  errtext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "nodetwm"

void LNode :: nodetwm (char *errtext )
{

  char      string[129];

  memset(string,0,sizeof(string));
  strcpy(string,errtext);
  strcat(string,"STR : ");
  gvtxbts(string+strlen(string),nodefield->fmcbsmcb->smcbname,ID_SIZE);
  strcat(string,"; INST : ");
  memcpy(&string[strlen(string)],nodeinst->get_iselarea(),32);
  SDBError().TraceMessage(string);


}

/******************************************************************************/
/**
\brief  ~LNode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~LNode"

     LNode :: ~LNode ( )
{

  if ( nodeidnt == NODE_ID )
    LNode::Close();   // ist eigentlich nur zur Sicherheit
  
  ResetExpression();
  RemoveReference();


}


