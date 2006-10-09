/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACProperty

\brief    


\date     $Date: 2006/08/30 19:28:22,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACProperty"

#include  <popa7.h>
#ifndef   DLL_ACNode_HPP
#define   DLL_ACNode_HPP
#include  <sACNode.hpp>
#include  <sDLL.h>
#endif
#include  <sACGenericAttr.hpp>
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sACProperty.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sFieldDef.hpp>
#include  <sLACObject.hpp>
#include  <sStructAccess.hpp>
#include  <sXInti.hpp>
#include  <sbinti.hpp>
#include  <sdisel.hpp>
#include  <sexd.hpp>
#include  <sgmvl.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>
#include  <ssmcb.hpp>
#include  <sACProperty.hpp>


/******************************************************************************/
/**
\brief  ACProperty - 



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
#define    MOD_ID  "ACProperty"

     ACProperty :: ACProperty (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
                     : ACNode(),
  nodecln(0),
  nodeoff(0),
  struct_access(NULL)
{

  Open(obhandle,nodeptr,dbfield_ptr,highctx,accopt);

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACProperty"

     ACProperty :: ACProperty ( )
                     : ACNode (),
  nodecln(0),
  nodeoff(0),
  struct_access(NULL)
{

  nodetype = NT_ACProperty;
  SDBRESET

}

/******************************************************************************/
/**
\brief  i2 - 



\param  acpnoderef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACProperty"

     ACProperty :: ACProperty (ACProperty &acpnoderef )
                     : ACNode (acpnoderef),
  nodecln(acpnoderef.get_nodecln()),
  nodeoff(acpnoderef.get_nodeoff()),
  struct_access(acpnoderef.get_struct_access())
{



}

/******************************************************************************/
/**
\brief  CancelNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelNode"

logical ACProperty :: CancelNode ( )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  term = LNode::CancelNode();
  
  if ( copies )
  {
    copies->GoTop();
    while ( nodeptr = copies->GetNext() )
      nodeptr->Cancel();
  }

  if ( stsclck() && UnlockSet(NO,NO) )               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical ACProperty :: Check (logical autoini, logical acccheck )
{
  logical   term = NO;

BEGINSEQ
  if ( stscerr() )                                   ERROR
  
  if ( autoini == YES && !nodeinst )
    if ( InitIsel(GetMainBase(),NULL) )              ERROR
  
  if ( stscusr3() || stscfil() )                     LEAVESEQ
  if ( LNode::Check(autoini,acccheck) )              ERROR

  if ( autoini )
  {
    if ( !noderefp )
      if ( InitReference() )     
        switch ( SDBERROR )
        {
          case 0  :
          case 68 : // Extend nicht definiert oder nicht angelegt
                    ResetOnError();
          default : ERROR
        }
  
    if ( nodetype != NT_CSNode ) 
      if ( (!nodenode || 
//            ( nodenode->get_nodeinst() && nodenode->get_nodeinst()->IsPositioned())) ) 
            ( nodenode->get_nodeinst() && nodenode->get_nodeinst()->IsSelected())) ) 
//      SetupNode(NO,NO);
        SetupNode(YES,NO);   // wegen autokorrektur legen wir references auch beim check an (upgrade8 to V9)
    if ( nodenode && !stscfil() )
      noderefl->ResetEBNumber();  // das sollte aber nicht passieren
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CheckNewID - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckNewID"

logical ACProperty :: CheckNewID ( )
{

  return ( noderefl->CheckNewID(GetKeyInstance(NULL,NULL),
                                nodeinst->GetID()) );



}

/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACProperty :: Close ( )
{

  ACNode::Close();

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

node *ACProperty :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACProperty(*this) ) )        SDBERR(95)
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

inti *ACProperty :: CreateInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical init_nodes )
{
  isel     *iselptr = NULL;
  inti     *intiptr = NULL;
BEGINSEQ
  if ( object_ref->IsXMLBase() )
    intiptr = new XInti(nodeptr,strdefptr,instptr,init_nodes);
  else if ( nodefield->get_clst_table() && !object_ref->GetLocalACObject()->IsPIF())
  {
    if ( !noderefp )
      if ( InitReference() )                         ERROR
    intiptr = new disel(nodeptr,strdefptr,instptr,noderefp,init_nodes);
  }
  else
    if ( nodeptr )
    {
      if ( intiptr = iselptr = new isel(nodeptr,strdefptr,instptr,init_nodes) )
        iselptr->set_mb_number(((LNode *)nodeptr)->GetMainBase());      
    }
    else
      intiptr = iselptr = new isel(strdefptr,instptr);
    
  if ( !intiptr )                                     SDBERR(95)
                                                      SDBCERR

RECOVER
  delete intiptr;
  intiptr = NULL;
ENDSEQ
  return(intiptr);
}

/******************************************************************************/
/**
\brief  DeleteReference - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteReference"

logical ACProperty :: DeleteReference ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( DeleteSet(YES) )                              ERROR
  if ( noderefl->DeleteReference() )                 ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDimension - 



\return pecnt - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 ACProperty :: GetDimension (logical chknode )
{
  int32     dim = AUTO;
BEGINSEQ
  if ( Check(YES,NO) )                              ERROR
  dim = noderefp->get_refsakcb()->get_max_count();

RECOVER

ENDSEQ
  return(dim);
}

/******************************************************************************/
/**
\brief  GetGlobalID - 



\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

EB_Number ACProperty :: GetGlobalID ( )
{

  return(0);

}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACProperty :: GetMainBase ( )
{
  int16      mbnumber = nodefield->get_mb_number();
  if ( !nodenode && mbnumber == TEMP_MAIN )
    mbnumber = object_ref->get_db_handle()->GetTempMain();

  return(mbnumber);
}

/******************************************************************************/
/**
\brief  InitIsel - 



\return term - Termination code

\param  mbnumber - MainBase number
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitIsel"

logical ACProperty :: InitIsel (int16 mbnumber, void *instptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !noderefp )
    if ( InitReference() )                           ERROR
      
  if ( InitInti(struct_access->get_struct_def(),instptr) )
                                                     ERROR
  Bnodeinst->SetMBNumber(mbnumber);

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

logical ACProperty :: InitReference ( )
{
  logical    term     = NO;
BEGINSEQ
  if ( !nodefield )                                  ERROR
  if ( !struct_access )
  {  
    if ( !nodefield->fmcbityp &&
         !nodefield->GetDBStruct(object_ref->GetDictionary()) )
    {
      stsserr();                                     ERROR
    }
    if ( !(struct_access = object_ref->GetStructAccess(nodefield->fmcbityp)) )
                                                     ERROR
  }
  
  if ( nodeinst )
    Bnodeinst->SetStructAccess(struct_access);
      
  if ( LNode::InitReference() )                      ERROR

RECOVER
  term     = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsNewReference - 



\return cond - 

\param  create_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewReference"

logical ACProperty :: IsNewReference (logical create_ref )
{
  binti                  *bintiptr;
  char                   *extinst;
  EB_Number              *entnr;
  logical                 cond = NO;
BEGINSEQ
  if ( !nodenode || !(bintiptr = Bnodenode->get_bnodeinst()) )
                                                     ERROR
  if ( !noderefl )
    if ( InitReference() )                           ERROR
  if( !noderefl->get_topref() )                      ERROR
  
  if ( !(extinst = bintiptr->GetExtInst()) )         ERROR
  entnr = (EB_Number *)(extinst+nodeoff);
  
  if ( *entnr != noderefl->get_topref()->GetExtInstID() )
                                                     ERROR
  if ( create_ref && entnr->IsEmpty() )              ERROR
RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  obhandle - Database Object handle
\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACProperty :: Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
{
  logical           term(NO);
BEGINSEQ
  ACNode::Open(obhandle,nodeptr,dbfield_ptr,highctx,accopt);
  nodetype = NT_ACProperty;

  if ( nodefield )
     nodeoff = nodefield->get_offset_ext(); 
//  if ( nodefield )
//    struct_access = obhandle->GetStructAccess(nodefield->GetDBStruct(obhandle->GetDictionary()));
  
  if ( CheckAccess(accopt) )                         ERROR
  
  SDBRESET
RECOVER
  nodeidnt = 0;
  term = YES;

ENDSEQ
  return(term);
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

logical ACProperty :: ProvideInti (EB_Number entnr )
{

  return(ACNode::ProvideInti(entnr));

}

/******************************************************************************/
/**
\brief  i1 - 



\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInti"

logical ACProperty :: ProvideInti (int16 sid )
{
  StructAccess *structacc;
  logical       term = NO;
BEGINSEQ
  if ( sid != struct_access->get_struct_def()->smcbityp )
  {    
    if ( !(structacc = object_ref->GetStructAccess(sid)) )   
                                                     SDBERR(99)
    struct_access = structacc;
  }
  
  if ( ACNode::ProvideInti(sid) )                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetInstance - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

void ACProperty :: ResetInstance ( )
{

  LNode::ResetInstance();


}

/******************************************************************************/
/**
\brief  SetupNode - 



\return term - Termination code

\param  create_ref - 
\param  retain_mod - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNode"

logical ACProperty :: SetupNode (logical create_ref, logical retain_mod )
{
  EB_Number   clnumb;
  EB_Number  *entnr;
  logical     term   = NO;

BEGINSEQ
  if ( stscerr() )                                   LEAVESEQ
  if ( stscfil() && 
       (!create_ref || (noderefp && noderefp->get_refrex())) )
                                                     LEAVESEQ
  if ( ACNode::SetupNode(create_ref,retain_mod) )    ERROR
  if ( !noderefp )                                   LEAVESEQ
    
  if ( nodenode )
  {
    if ( version != ((ACNode *)nodenode)->get_version() )
    {
      version = ((ACNode *)nodenode)->get_version();
      noderefl->SetVersion(version);
      SetVersion(version);
    }
    if ( SetupNode_intern(Bnodenode->get_bnodeinst(),create_ref,retain_mod) )
                                                     ERROR
  }
  
  if ( noderefl->stscold() || noderefp->stscold() )
    SetupIndex(noderefp->stscold());

  GenerateEvent(DBO_Refresh);  // machen wir vor allem für transiente Mengen, aber auch für OGUI (Collection changed)

RECOVER
  switch ( SDBERROR )
  {
    case 0  :
    case 68 : // Extend nicht definiert oder nicht angelegt
              ResetOnError();
              break;
    default : term = YES;
  }
ENDSEQ
  return (term);

}

/******************************************************************************/
/**
\brief  SetupNode_intern - 



\return term - Termination code

\param  bintiptr - 
\param  create_ref - 
\param  retain_mod - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNode_intern"

logical ACProperty :: SetupNode_intern (binti *bintiptr, logical create_ref, logical retain_mod )
{
  logical     is_ini = nodeinst ? nodeinst->stscini() : NO;
  logical     is_mod = nodeinst ? nodeinst->stscmod() : NO;
  logical     is_coll_mod = stscmod();
  EB_Number   clnumb;
  EB_Number  *entnr;
  char       *instptr;
  logical     term   = NO;

BEGINSEQ
  if ( stscerr() || !bintiptr )                       LEAVESEQ
  
  if ( instptr = bintiptr->GetExtInst() )
  {
    if ( nodefield->get_cluster_opt() )
      clnumb = bintiptr->GetClusterNumber();
    entnr    = (EB_Number *)(instptr+nodeoff);
    
// besser wäre PI_Write nur für updatefähige Referenzen
// ansonsten werden sackweise EBIs für refx erzeugt, die später sowieso kein Schw. will
    if ( noderefl->Setup(entnr,clnumb,bintiptr->GetMBNumber(),
                         Bnodenode->get_nodewrit() && nodeacc != PI_Read && create_ref ? PI_Write : PI_Read) ) 
                                                     ERROR
// Das Beschaffen derMB_Number aus dem isel ist nur sinnvoll, 
// wenn die collection keine eigene MB-Number definiert.
    SetSave();
  }
  else if ( !object_ref->IsXMLBase() )
  {
    noderefl->ResetEBNumber();      // noderefl->Reset();
    if ( bintiptr->stscini() )
      retain_mod = YES;  // parent is init-instance -> init for current instance must be retained    
  }

  if ( !IsValidForParent() )                        SDBIERR(390)   // SDBERR(390) kommt aus ValidateNode immer zu diesem fehler
  else
  {
    stssfil();  // setzt mod zurück!!!

    if ( nodeinst ) 
    {
      nodeinst->Setup(clnumb,GetMainBase());
      if ( retain_mod && nodecur == AUTO )
      {
        if ( is_ini )
          nodeinst->stssini();
        if ( is_mod )
          nodeinst->stssmod();
        if ( is_coll_mod )
          SetMod();
      }
    }  
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  set_nodecln - 




\param  clnumber - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_nodecln"

void ACProperty :: set_nodecln (EB_Number clnumber )
{

  nodecln = clnumber;

}

/******************************************************************************/
/**
\brief  ~ACProperty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACProperty"

     ACProperty :: ~ACProperty ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


