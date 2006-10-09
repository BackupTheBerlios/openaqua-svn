/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    binti

\brief    


\date     $Date: 2006/08/30 16:47:20,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "binti"

#include  <popa7.h>
#include  <cevtp.h>
#ifndef   DLL_EventLink_HPP
#define   DLL_EventLink_HPP
#include  <sEventLink.hpp>
#include  <sDLL.h>
#endif
#include  <sACGenericAttr.hpp>
#include  <sACObject.hpp>
#include  <sACShareBase.hpp>
#include  <sACTransientReference.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDLL_Handle.hpp>
#include  <sEB_Number.hpp>
#include  <sEventLink.hpp>
#include  <sEventLinkList.hpp>
#include  <sProcessEventHandler.hpp>
#include  <sPropertyHandle.hpp>
#include  <sStructAccess.hpp>
#include  <sbinti.hpp>
#include  <sbnode.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <sbinti.hpp>


/******************************************************************************/
/**
\brief  AddGenericRef - 



\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGenericRef"

logical binti :: AddGenericRef (char *fldname )
{
  logical                 term = NO;

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

logical binti :: Cancel ( )
{
  nodelist  cursor(node_rshp);
  node     *node_ptr;

  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->CancelNode();

  (cursor = node_refr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->CancelNode();

  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->CancelNode();

  (cursor = node_base).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->CancelNode();

  ResetNodes();
    
/*  führt zu Rekursion, muß auch nicht sein
  (cursor = node_tref).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr = node_ptr->GetNode() )
      node_ptr->CancelNode();
*/
  return(NO);

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

logical binti :: ChangeMode (PIACC accopt )
{
  nodelist  cursor(node_base);
  node     *node_ptr;
  logical   term = NO;
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    term = (node_ptr->ChangeMode(accopt) == PI_undefined);
  
  (cursor = node_rshp).GoTop();
  while ( node_ptr = cursor.GetNext() )
    term = (node_ptr->ChangeMode(accopt) == PI_undefined); 

  (cursor = node_refr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    term = (node_ptr->ChangeMode(accopt) == PI_undefined);

  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    term = (node_ptr->ChangeMode(accopt) == PI_undefined);

  (cursor = node_attr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    term = (node_ptr->ChangeMode(accopt) == PI_undefined);

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

logical binti :: CheckAddReference ( )
{
  nodelist  cursor(node_base);
  node     *node_ptr;
  logical   term = NO;
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    ((binti *)node_ptr->get_nodeinst())->CheckAddReference();
  
  (cursor = node_refr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr->IsInitInstance() && node_ptr->stscmod() )
    {
      node_ptr->SetupNode(YES,YES);
      node_ptr->Add(AUTO);
    }
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDelEmpty - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDelEmpty"

logical binti :: CheckDelEmpty ( )
{
  nodelist  cursor;
  node     *nodeptr;
  logical   term = NO;
BEGINSEQ
  if ( !struct_def->get_check_del_empty() )          LEAVESEQ

// Prüfung für Attribute fehlt noch

  (cursor = node_rshp).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Bnodeptr->CheckDelEmpty() )                 ERROR

  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Bnodeptr->CheckDelEmpty() )                 ERROR

  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( Bnodeptr->CheckDelEmpty() )                 ERROR

  (cursor = node_base).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( ((binti *)nodeptr->get_nodeinst())->CheckDelEmpty() )
                                                     ERROR

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

logical binti :: Close ( )
{

  inti::Close();                      // DeleteSubNodes();
  
  delete context;
  context = NULL;
  
  delete inst_field;
  inst_field = NULL;

  if ( iselifo )
    if ( isel_init )
      msmfs((void **)&isel_init); 
  isel_init = NULL;

  if ( proc_event_handler )
    proc_event_handler->Release();
  proc_event_handler = NULL;

  if ( event_handler )
    event_handler->Release();
  event_handler = NULL;

  return(NO);
}

/******************************************************************************/
/**
\brief  Copy - 



\return converr - 

\param  srceinti - 
\param  nodeptr - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

int16 binti :: Copy (inti *srceinti, node *nodeptr, PIREPL db_replace, PIREPL copy_type )
{
  int16     converr = NO;

BEGINSEQ
  if ( !copy_type )
    copy_type = REPL_all;
    
  if ( copy_type == REPL_all )
  {
    if ( db_replace && db_replace != REPL_direct )
      RemoveReferences(srceinti);
    if ( Copy(srceinti,nodeptr,db_replace,REPL_instance) ||
         Copy(srceinti,nodeptr,db_replace,REPL_relationships) )
                                                     ERROR
    LEAVESEQ
  }

  SetOldBaseInst();
  
  if ( stscold() && copy_type != REPL_relationships )
  {
    // hier werden keine GUIDs kopiert
    struct_def->CopyInstance(iselarea,srceinti->get_struct_def(),srceinti->get_iselarea(),REPL_direct,UNDEF);
    Modify();
  }
  if ( CopyGenAttr(srceinti,db_replace,copy_type) )  
    converr = nodeptr->ConversionError(srceinti->get_iselarea(),srceinti->get_struct_def());
  if ( CopyOReferences(srceinti,db_replace,copy_type) )
    converr = nodeptr->ConversionError(srceinti->get_iselarea(),srceinti->get_struct_def());
  if ( CopyBReferences(srceinti,db_replace,copy_type) )
    converr = nodeptr->ConversionError(srceinti->get_iselarea(),srceinti->get_struct_def());

  if ( db_replace != REPL_direct )
    SetIdentity();
  
  ResetOldBaseInst();

RECOVER
//GenerateEvent(DBO_NotStored);  kommt später, vielleicht
ENDSEQ
  return(converr);

}

/******************************************************************************/
/**
\brief  CopyBReferences - 



\return term - Termination code

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyBReferences"

logical binti :: CopyBReferences (inti *srceinti, PIREPL db_replace, PIREPL copy_type )
{
  nodelist  cursor(node_base);
  PIREPL    db_repl = db_replace == REPL_local ||
                      db_replace == REPL_no_create
                      ? REPL_none : db_replace;
  logical   term    = NO;  
  bnode    *targ_node;
  node     *srce_node;
BEGINSEQ
  if ( copy_type != REPL_relationships )             LEAVESEQ
  if ( db_replace == REPL_direct )                   LEAVESEQ
//  if ( stscold() && !db_replace )                    LEAVESEQ

  cursor.GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    if ( !targ_node->get_nodeinst()->stscold() || db_replace == REPL_all )
    {
      if ( srce_node = srceinti->GetPropNode(targ_node->get_nodefield()->fmcbname,targ_node->get_prop_path()) )
      {
        if ( srce_node->Get(FIRST_INSTANCE) )
          if ( targ_node->get_bnodeinst()->CopyBReferences(srce_node->get_nodeinst(),db_replace,copy_type) )
            term = YES;
      }
      else
        if ( targ_node->get_bnodeinst()->CopyBReferences(srceinti,db_replace,copy_type) )
          term = YES;
    }
  }  
  
  // dieser teil kann später raus, da references eigentlich keine Relationships haben sollten. Wird aber noch nicht geprüft.
  (cursor = node_refr).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
    if ( targ_node->CopyBReferences(srceinti,db_repl,copy_type) )
      term = YES;

  (cursor = node_rshp).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    if ( !targ_node->get_nodefield()->get_owning() )
      if ( targ_node->CopyReference(srceinti,db_repl,REPL_all) )
        term = YES;
    if ( targ_node->get_nodefield()->get_owning() )  // kopiert ggf. auch Sekundär-refernzen
      if ( targ_node->CopyBReferences(srceinti,db_repl,copy_type) )
        term = YES;
  }      

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CopyBufferInstance - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyBufferInstance"

logical binti :: CopyBufferInstance (inti *intiptr )
{
  binti                   *bintiptr = (binti *)intiptr;
  nodelist                 scursor(bintiptr->get_node_base());
  nodelist                 tcursor(node_base);
  node                    *source;
  node                    *target;
  logical                 term = NO;
  scursor.GoTop();
  tcursor.GoTop();
  while ( target = tcursor.GetNext() )
  {
    source = scursor.GetNext();
    target->get_nodeinst()->CopyBufferInstance(source->get_nodeinst());
  }
  
  inti::CopyBufferInstance(intiptr);
  
  if ( !stsctrans() )
    ResetSubNodes();

  objid = ((binti *)intiptr)->get_objid();

  return(term);
}

/******************************************************************************/
/**
\brief  CopyEventHandler - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyEventHandler"

logical binti :: CopyEventHandler (binti *bintiptr )
{
  logical     term = NO;
  if ( !event_handler )
    if ( event_handler = bintiptr->get_event_handler() )
      event_handler->Reserve();

  if ( !proc_event_handler )
    if ( proc_event_handler = bintiptr->get_proc_event_handler() )
      proc_event_handler->Reserve();

  return(term);
}

/******************************************************************************/
/**
\brief  CopyGenAttr - 



\return term - Termination code

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyGenAttr"

logical binti :: CopyGenAttr (inti *srceinti, PIREPL db_replace, PIREPL copy_type )
{
  nodelist  cursor(node_base);
  PIREPL    db_repl = db_replace != REPL_all ? REPL_none : db_replace;
  logical   term    = NO;  
  bnode    *targ_node;
  node     *srce_node;
BEGINSEQ
  if ( copy_type == REPL_relationships )             LEAVESEQ
  if ( stscold() && !db_replace )                    LEAVESEQ
  
  cursor.GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    if ( srce_node = srceinti->GetPropNode(targ_node->get_nodefield()->fmcbname,targ_node->get_prop_path()) )
    {
      if ( srce_node->Get(FIRST_INSTANCE) )
        if ( targ_node->get_bnodeinst()->CopyGenAttr(srce_node->get_nodeinst(),db_repl,copy_type) )
          term = YES;
    }
    else
      if ( targ_node->get_bnodeinst()->CopyGenAttr(srceinti,db_repl,copy_type) )
        term = YES;
  }  
  
  (cursor = node_genattr).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    targ_node->DeleteSet();
    if ( targ_node->CopyReference(srceinti,db_replace,copy_type) )
      term = YES;
  }

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CopyGlobalInst - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyGlobalInst"

logical binti :: CopyGlobalInst (binti *bintiptr )
{
  nodelist  target(node_base);
  nodelist  source(bintiptr->get_node_base());
  bnode     *tnode_ptr;
  bnode     *snode_ptr;
  inti::Copy(bintiptr,NULL,REPL_GUID);
  
  source.GoTop();
  target.GoTop();
  while ( tnode_ptr = target.GetNextBNode() )
  {
    if ( snode_ptr = source.GetNextBNode() )
      if ( tnode_ptr->get_nodeinst() )
        tnode_ptr->get_bnodeinst()->CopyGlobalInst(snode_ptr->get_bnodeinst());
  }
  
  (target = node_genattr).GoTop();
  (source = bintiptr->get_node_genattr()).GoTop();
  while ( tnode_ptr = target.GetNextBNode() )
  {
    if ( snode_ptr = source.GetNextBNode() )
// hier müssen wir eigentlich auch MEMOS übernehmen, da sonst initialisierte Memos beim AddGlobal nicht gebildet werden.
      if ( snode_ptr->stscmod() )
        tnode_ptr->stssmod();
  }


  return(NO);
}

/******************************************************************************/
/**
\brief  CopyOReferences - 



\return term - Termination code

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyOReferences"

logical binti :: CopyOReferences (inti *srceinti, PIREPL db_replace, PIREPL copy_type )
{
  nodelist  cursor(node_base);
  PIREPL    db_repl = db_replace == REPL_local ||
                      db_replace == REPL_no_create
                      ? REPL_none : db_replace;
  logical   term    = NO;  
  bnode    *targ_node;
  node     *srce_node;
BEGINSEQ
  if ( db_replace == REPL_direct || copy_type != REPL_instance )
                                                     LEAVESEQ
  if ( stscold() && !db_replace )                    LEAVESEQ
  
  cursor.GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    if ( srce_node = srceinti->GetPropNode(targ_node->get_nodefield()->fmcbname,targ_node->get_prop_path()) )
    {
      if ( srce_node->Get(FIRST_INSTANCE) )
        if ( targ_node->get_bnodeinst()->CopyOReferences(srce_node->get_nodeinst(),db_repl,copy_type) )
          term = YES;
    }
    else
      if ( targ_node->get_bnodeinst()->CopyOReferences(srceinti,db_repl,copy_type) )
        term = YES;
  }  

  (cursor = node_refr).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
    if ( targ_node->CopyReference(srceinti,db_replace,copy_type) )
      term = YES;
  
  (cursor = node_rshp).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
    if ( targ_node->get_nodefield()->get_owning() )  
      if ( targ_node->CopyReference(srceinti,db_replace,copy_type) )
        term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CopySubnodes - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySubnodes"

logical binti :: CopySubnodes (binti *bintiptr )
{
  binti            *bpt;
  logical           term = NO;
  if ( bpt = bintiptr->GetBaseBinti(struct_def->smcbname,YES) )
    bintiptr = bpt;
  
  node_rshp    = bintiptr->get_node_rshp();
  node_refr    = bintiptr->get_node_refr();
  node_tref    = bintiptr->get_node_tref();
  
  node_genattr = bintiptr->get_node_genattr();
  node_base    = bintiptr->get_node_base();
  
  memcpy(iselarea,bintiptr->get_iselarea(),GetInstLength());
  return(term);
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

logical binti :: DelGenericRef (char *fldname )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DeleteInverseRef - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteInverseRef"

logical binti :: DeleteInverseRef ( )
{
  nodelist  cursor(node_rshp);
  bnode    *bnode_ptr;
  logical   term = NO;
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( bnode_ptr->get_nodefield()->get_inverse() )    
      bnode_ptr->DeleteSet();

  return(term);
}

/******************************************************************************/
/**
\brief  DeleteReferences - 



\return term - Termination code

\param  extnames - Extent name
\param  is_root - 
\param  delopt - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteReferences"

logical binti :: DeleteReferences (char *extnames, logical is_root, int16 delopt, logical del_dep )
{
  nodelist  cursor(node_base);
  bnode    *bnode_ptr;
  logical   term = NO;
BEGINSEQ
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    if ( extnames && bnode_ptr->IsACShareBase() )
    {
      if ( ((ACShareBase *)bnode_ptr)->DeleteInverse(extnames,this,is_root,del_dep) )
                                                     ERROR
    }
    else              // 14.6.98, da sonst rekursives löschen für extents nicht klappt
      if ( delopt )
        bnode_ptr->Switch(AUTO);
    if ( delopt )
      if ( bnode_ptr->DeleteSet(NO,del_dep) )       ERROR
  }
  
  if ( delopt )
  {
    (cursor = node_genattr).GoTop();
    while ( bnode_ptr = cursor.GetNextBNode() )
    {
      if ( bnode_ptr->Check(YES,NO) )                ERROR
      if ( delopt && bnode_ptr->CheckDelEmpty() )    ERROR
      if ( ((ACGenericAttr *)bnode_ptr)->DeleteReference() )
                                                     ERROR
    }
    (cursor = node_refr).GoTop();
    while ( bnode_ptr = cursor.GetNextBNode() )
    {
      if ( bnode_ptr->Check(YES,NO) )                ERROR
      if ( delopt && bnode_ptr->CheckDelEmpty() )    ERROR
      if ( ((ACReference *)bnode_ptr)->DeleteReference() )
                                                     ERROR
    }
  }
RECOVER
  GenerateEvent(DBO_NotDeleted);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteRelationships - 



\return term - Termination code

\param  extnames - Extent name
\param  is_root - 
\param  delopt - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteRelationships"

logical binti :: DeleteRelationships (char *extnames, logical is_root, int16 delopt, logical del_dep )
{
  nodelist  cursor(node_rshp);
  bnode    *bnode_ptr;
  logical   term = NO;
BEGINSEQ
  if ( delopt && !stscdel() )
    if ( RecursiveEvents(DBP_Delete) )                 ERROR
  
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    if ( bnode_ptr->get_nodefield()->get_owning() )
    {
      if ( delopt && bnode_ptr->CheckDelEmpty() )      ERROR
      
      if ( ((ACRelationship *)bnode_ptr)->DeleteInverse(extnames,this,is_root,del_dep) )
                                                     ERROR
      if ( !delopt )
        bnode_ptr->Switch(AUTO);
      else
        if ( ((ACRelationship *)bnode_ptr)->DeleteReference() )
                                                     ERROR
    }
  }
  
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    if ( !bnode_ptr->get_nodefield()->get_owning() )
    {
      if ( delopt && bnode_ptr->CheckDelEmpty() )      ERROR
      
      if ( ((ACRelationship *)bnode_ptr)->DeleteInverse(extnames,this,is_root,del_dep) )
                                                     ERROR
      if ( !delopt )
        bnode_ptr->Switch(AUTO);
      else
        if ( ((ACRelationship *)bnode_ptr)->DeleteReference() )
                                                     ERROR
    }
  }
  
  stssdel();

RECOVER
  GenerateEvent(DBO_NotDeleted);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteSubNodes - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSubNodes"

void binti :: DeleteSubNodes ( )
{

  node_rshp.DeleteNodes();
  node_refr.DeleteNodes();
  node_tref.DeleteNodes();
  
  inti::DeleteSubNodes();
  
  node_genattr.DeleteNodes();
  node_base.DeleteNodes();
  


}

/******************************************************************************/
/**
\brief  DisableContext - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableContext"

void binti :: DisableContext ( )
{
  nodelist  cursor(node_base);
  node     *nodeptr;
  if ( context )
    context->Disable();

  while ( nodeptr = cursor.GetNext() )
    Bnodeptr->DisableContext();


}

/******************************************************************************/
/**
\brief  EnableContext - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableContext"

void binti :: EnableContext ( )
{
  nodelist  cursor(node_base);
  node     *nodeptr;
  if ( context )
    context->Enable();

  while ( nodeptr = cursor.GetNext() )
    Bnodeptr->EnableContext();


}

/******************************************************************************/
/**
\brief  ExecuteFunction - 



\return term - Termination code

\param  fnames - 
\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical binti :: ExecuteFunction (char *fnames, logical check_opt )
{

  return ( context ? context->ExecuteFunction(fnames,check_opt) : YES );

}

/******************************************************************************/
/**
\brief  GenerateCSEvent - 




\param  event_id - Ivend type
\param  identity - Local Instance identity (LOID)
\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCSEvent"

void binti :: GenerateCSEvent (CSA_Events event_id, int64 identity, node *nodeptr )
{
  EventLink              *evt_link;
  if ( context && context->IsEnabled() )
    context->Notify(event_id,identity);
    
  if ( event_handler && GetOBHandle()->EventHandling() )
  {
    PropertyHandle  ph(nodeptr);
    
    event_handler->GoTop();
    while ( evt_link = event_handler->GetNext() )
      evt_link->Call(event_id,identity,ph);
  }
  


}

/******************************************************************************/
/**
\brief  GenerateEvent - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical binti :: GenerateEvent (DB_Event intevent )
{
  logical                 term = NO;
BEGINSEQ
  if ( !context )                                LEAVESEQ
    
  if ( struct_def->get_resource() && context->IsEnabled() )    
    term = struct_def->get_resource()->GenerateEvent(intevent,context);
  
  GenerateProcessEvent(intevent);

/* für week_typed ev. zusätzlich machen ????
  if ( struct_def != field_def->GetDBStruct() )
    if ( field_def->GetDBStruct()->get_resource() )
      term = field_def->GetDBStruct()->get_resource()->GenerateEvent(intevent,context);
*/
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateProcessEvent - 




\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateProcessEvent"

void binti :: GenerateProcessEvent (DB_Event intevent )
{

  if ( proc_event_handler )
  {
    proc_event_handler->set_causer(GetParentNode());
    proc_event_handler->GenerateEvent(intevent);
  }

}

/******************************************************************************/
/**
\brief  GetBaseBinti - 



\return bintiptr - 

\param  strname - Type name
\param  shared_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseBinti"

binti *binti :: GetBaseBinti (char *strname, logical shared_only )
{
  nodelist          base_list(node_base);
  nodelist          attr_list(node_attr);
  binti            *bintiptr;
  bnode            *nodeptr;
  logical           term = NO;
BEGINSEQ
  bintiptr = this;
  if ( !memcmp(strname,struct_def->smcbname,ID_SIZE) )
                                                     LEAVESEQ
  bintiptr = NULL;
  
  if ( !shared_only )
  {
    attr_list.GoTop();
    while ( nodeptr = attr_list.GetNextBNode() )
      if ( Bnodeptr->get_nodefield()->fmcbbstr )
        if ( bintiptr = nodeptr->get_bnodeinst()->GetBaseBinti(strname,shared_only) )
          LEAVESEQ
  }

  base_list.GoTop();
  while ( nodeptr = base_list.GetNextBNode() )
    if ( bintiptr = nodeptr->get_bnodeinst()->GetBaseBinti(strname,shared_only) )
      LEAVESEQ


ENDSEQ
  return(bintiptr);
}

/******************************************************************************/
/**
\brief  GetClusterNumber - 



\return clnumb - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClusterNumber"

EB_Number binti :: GetClusterNumber ( )
{

  return(0);

}

/******************************************************************************/
/**
\brief  GetContext - 



\return strctx - Structure Context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Structure *binti :: GetContext ( )
{

  return ( context );

}

/******************************************************************************/
/**
\brief  GetEXD - 



\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *binti :: GetEXD ( )
{

  return ( this && stscusr3() ? ((isel *)this)->get_exd_area() : NULL );

}

/******************************************************************************/
/**
\brief  GetExtInst - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInst"

char *binti :: GetExtInst ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetGenAttrNode - 



\return acgnodeptr - 

\param  fldnames - Property name
\param  propctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrNode"

ACGenericAttr *binti :: GetGenAttrNode (char *fldnames, CTX_Property *propctx )
{
  nodelist         cursor(node_base);
  ACGenericAttr   *acgnodeptr = NULL;
  bnode           *bnode_ptr;
  char             fldname[ID_SIZE];
  int16                   talevel = 0;
  logical                 term    = NO;
BEGINSEQ
  if ( fldnames )
  {
    gvtxstb(fldname,fldnames,ID_SIZE);
    acgnodeptr = (ACGenericAttr *)node_genattr.GetNode(fldname,propctx,NO);
  }
  else
    acgnodeptr = (ACGenericAttr *)node_genattr.GetHead();
                                                     
  if ( acgnodeptr )                                  LEAVESEQ
  cursor.GoTop();
  while ( !acgnodeptr && (bnode_ptr = cursor.GetNextBNode()) )
    acgnodeptr = bnode_ptr->get_bnodeinst()->GetGenAttrNode(fldnames,propctx);

  if ( acgnodeptr )                                  LEAVESEQ
  (cursor = node_attr).GoTop();
  while ( !acgnodeptr && (bnode_ptr = cursor.GetNextBNode()) )
    acgnodeptr = bnode_ptr->get_bnodeinst()->GetGenAttrNode(fldnames,propctx);

ENDSEQ
  return(acgnodeptr);
}

/******************************************************************************/
/**
\brief  GetGlobalInstanceIdentity - 



\return id_string - Identifier string

\param  id_string - Identifier string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalInstanceIdentity"

char *binti :: GetGlobalInstanceIdentity (char *id_string )
{

BEGINSEQ
  if ( !id_string )                                 SDBERR(99)
  *id_string = 0; 
  
  if ( objid > 0 )
    gvtxltoa(objid,id_string,10);

RECOVER

ENDSEQ
  return(id_string);
}

/******************************************************************************/
/**
\brief  GetIdentity - 



\return entnr_pt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentity"

EB_Number *binti :: GetIdentity ( )
{
  EB_Number              *entnr_pt = NULL;
  if ( identity_pos >= 0 )
    entnr_pt = (EB_Number *)(iselarea + identity_pos);
  else
    entnr_pt = (EB_Number *)&objid;

  return(entnr_pt);
}

/******************************************************************************/
/**
\brief  GetMBNumber - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBNumber"

int16 binti :: GetMBNumber ( )
{

  return(0);

}

/******************************************************************************/
/**
\brief  GetOldInst - 



\return instptr - 

\param  oldinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldInst"

char *binti :: GetOldInst (void *oldinst )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetParentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParentNode"

bnode *binti :: GetParentNode ( )
{
  PropertyHandle  *ph;
  bnode           *nodeptr = NULL;
BEGINSEQ
  if ( !context )                                    ERROR

  if ( ph = context->GetPropertyHandle() )
    nodeptr = (bnode *)ph->get_nodeptr();
RECOVER

ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetPropNodePtr - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropNodePtr"

node **binti :: GetPropNodePtr (char *prop_names, CTX_Property *highprop_ctx )
{
  char       propname[ID_SIZE];
  node     **pnodeptr = NULL;
BEGINSEQ
  gvtxstb(propname,prop_names,ID_SIZE);

  if ( pnodeptr = node_attr.GetNodePtr(propname,highprop_ctx,NO) )    LEAVESEQ
  if ( pnodeptr = node_genattr.GetNodePtr(propname,highprop_ctx,NO) ) LEAVESEQ
  if ( pnodeptr = node_refr.GetNodePtr(propname,highprop_ctx,NO) )    LEAVESEQ
  if ( pnodeptr = node_rshp.GetNodePtr(propname,highprop_ctx,NO) )    LEAVESEQ
  if ( pnodeptr = node_tref.GetNodePtr(propname,highprop_ctx,NO) )
  {
    pnodeptr = ((ACTransientReference *)*pnodeptr)->GetNodePtr();
    LEAVESEQ
  }
  if ( pnodeptr = node_base.GetNodePtr(propname,highprop_ctx,YES) )   LEAVESEQ

ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_names - Property name
\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropNodePtr"

node **binti :: GetPropNodePtr (char *prop_names, char *proppath )
{
  char       propname[ID_SIZE];
  node     **pnodeptr = NULL;
BEGINSEQ
  gvtxstb(propname,prop_names,ID_SIZE);

  if ( pnodeptr = node_attr.GetNodePtr(propname,proppath,NO) )    LEAVESEQ
  if ( pnodeptr = node_genattr.GetNodePtr(propname,proppath,NO) ) LEAVESEQ
  if ( pnodeptr = node_refr.GetNodePtr(propname,proppath,NO) )    LEAVESEQ
  if ( pnodeptr = node_rshp.GetNodePtr(propname,proppath,NO) )    LEAVESEQ
  if ( pnodeptr = node_tref.GetNodePtr(propname,proppath,NO) )   
  {
    pnodeptr = ((ACTransientReference *)*pnodeptr)->GetNodePtr();
    LEAVESEQ
  }

  if ( proppath && *proppath )
    if ( pnodeptr = node_base.GetNodePtr(propname,proppath,NO) )  LEAVESEQ
 
  if ( pnodeptr = node_base.GetNodePtr(propname,(char *)NULL,YES) )
                                                     LEAVESEQ

ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  GetStructAccess - 



\return struct_access - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *binti :: GetStructAccess ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetSubNodePtr - 



\return nodeptr - 

\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubNodePtr"

node **binti :: GetSubNodePtr (char *prop_names, CTX_Property *highprop_ctx )
{
  nodelist                cursor(node_base);
  char                   *proppath = NULL;
  char                    propname[ID_SIZE];
  char                   *pos;
  node                  **pnodeptr   = NULL;
  node                   *base_node = NULL;
BEGINSEQ
  if ( !(pos = strchr(prop_names,'.')) )
    gvtxstb(propname,prop_names,sizeof(propname));
  else
  {
    proppath = pos+1;
    memset(propname,' ',sizeof(propname));
    memcpy(propname,prop_names,MIN(pos-prop_names,sizeof(propname)));
  }

  if ( (pnodeptr = node_base.GetNodePtr(propname,highprop_ctx,NO)) ||
       (pnodeptr = node_genattr.GetNodePtr(propname,highprop_ctx,NO))  )
  {
    if ( !proppath )                                 LEAVESEQ
    if ( pnodeptr = (*pnodeptr)->GetSubNodePtr(proppath,(*pnodeptr)->GetContext()) )
                                                     LEAVESEQ
  }
  if ( (pnodeptr = node_attr.GetNodePtr(propname,highprop_ctx,NO)) )
  {
    if ( !proppath )                                 LEAVESEQ
    if ( pnodeptr = GetSubNodePtr(proppath,(*pnodeptr)->GetContext()) )
                                                     LEAVESEQ
  }
   
  cursor.GoTop();
  while ( !pnodeptr && (base_node = cursor.GetNext()) )
    pnodeptr = base_node->GetSubNodePtr(prop_names,base_node->GetContext());

ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  HasBaseAutoIdKey - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasBaseAutoIdKey"

logical binti :: HasBaseAutoIdKey ( )
{
  nodelist       cursor(node_base);
  ACShareBase   *nodeptr;
  logical        cond = YES;
BEGINSEQ
  cursor.GoTop();
  while ( nodeptr = (ACShareBase *)cursor.GetNext() )
    if ( nodeptr->IsACShareBase() && nodeptr->get_autoid_key() ) 
                                                       LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  HasGenAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasGenAttribute"

logical binti :: HasGenAttribute ( )
{
  nodelist                cursor(node_base);
  bnode                  *bnode_ptr;
  logical                 cond = YES;
BEGINSEQ
  if ( node_genattr.GetCount() > 0 )                 LEAVESEQ
  
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if (bnode_ptr->get_bnodeinst()->HasGenAttribute())  LEAVESEQ

  (cursor = node_attr).GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if (bnode_ptr->get_bnodeinst()->HasGenAttribute())  LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Init - 



\return term - Termination code

\param  nodeptr - 
\param  mspool - 
\param  strdefptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical binti :: Init (node *nodeptr, void *mspool, DBStructDef *strdefptr, void *instptr )
{
  logical    term = NO;
BEGINSEQ
  if ( !struct_def && nodeptr )
    struct_def = field_def->GetDBStruct(nodeptr->GetObjectHandle()->GetDictionary());
    
  if ( InitArea(instptr) )                            ERROR
    
  if ( iselarea && !instptr )
    if ( isel_init = AllocateArea() )
      memcpy(isel_init,iselarea,GetInstLength());
      
  if ( nodeptr && struct_def && 
       ( struct_def->smcbityp > 0 || struct_def->smcbityp == TEMPSID || struct_def->smcbityp == T_DATETIME) && // auch für temporäre Strukturen!!
       struct_def->smcbstyp != ST_CODE )
  {
    if ( !(context = DLLHandle()->CreateStrCtx(nodeptr->GetObjectHandle()->GetCTXIPath(),
                                             struct_def->get_resource()->get_res_id())) )
                                                     ERROR
    context->Initialize(this,(CTX_Base *)nodeptr->GetContext());
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitGenAttr - 



\return term - Termination code

\param  initinst - 
\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitGenAttr"

logical binti :: InitGenAttr (void *initinst, logical set_init )
{
  nodelist  cursor(node_base);
  bnode     *bnode_ptr;
  node      *node_ptr;
BEGINSEQ
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( bnode_ptr->get_nodeinst() )
    {
      bnode_ptr->get_bnodeinst()->RecursiveEvents(DBO_Initialize);
      bnode_ptr->get_bnodeinst()->InitGenAttr(initinst 
                                              ? ((char *)initinst)+(bnode_ptr->get_bnodeinst()->get_iselarea()-iselarea)
                                              : NULL,set_init);
    }
  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr->Initialize(node_ptr->get_nodeinst()->get_iselarea(),set_init) )  ERROR // wert der initinst ist irrelevant


RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  InitInit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInit"

void binti :: InitInit ( )
{
  DBFieldDef     *fielddef;
  if ( isel_init )
    memcpy(isel_init,iselarea,(int32)GetInstLength());

  if ( struct_def &&
       (fielddef = struct_def->GetEntry("__IDENTITY")) && 
        fielddef->get_transient()                         )
    identity_pos = fielddef->fmcbposn;

}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code

\param  initinst - 
\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical binti :: Initialize (void *initinst, logical set_init )
{
  nodelist  cursor(node_base);
  node      *node_ptr;
  bnode     *bnode_ptr;
  logical    init_opt = initinst && initinst != iselarea ? YES : NO;
BEGINSEQ
  if ( stscini() )                                   LEAVESEQ
    
  ResetSubNodes();         // um init-state in nachgeordneten instanzen wegzuräumen
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    ((binti *)node_ptr->get_nodeinst())->ResetSubNodes();
    
  if ( !initinst )
  {
    if ( isel_init )
      struct_def->CopyInstance(iselarea,struct_def,isel_init,REPL_GUID,UNDEF);  // 30.3.00
    else
    {
      if ( field_def->fmcbityp == T_MEMO )
        memset(iselarea,0,field_def->fmcbsize+1);
      else if ( field_def->fmcbityp == T_BLOB )
        memset(iselarea,0,field_def->fmcbsize);
      else if ( struct_def && struct_def->smcbstyp != ST_CODE )
        struct_def->smcbfmcl->fmcliini(iselarea);
      else
        field_def->InitAttribute(iselarea);
    }
  }
  else if ( initinst != iselarea )
  {
    if ( struct_def->smcbityp == T_MEMO )
      gvtxbts(iselarea,(char *)initinst,field_def->fmcbsize);
    else if ( struct_def->smcbityp == T_BLOB )
      memcpy(iselarea,initinst,field_def->fmcbsize);
    else if ( struct_def && struct_def->smcbstyp != ST_CODE )
      struct_def->CopyInstance(iselarea,struct_def,(char *)initinst,REPL_GUID,UNDEF);
    else
      field_def->InitAttribute(initinst);
  }
  else
    initinst = NULL;
  
  if ( set_init )
    SetInitialize();  // 14.5.02
    
  SetInitializeEvent();
  if ( InitGenAttr(initinst,set_init) )              ERROR
  
  RecursiveEvents(DBO_Initialize);
  ResetInitializeEvent();

  (cursor = node_refr).GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    bnode_ptr->GenerateEvent(DBO_Refresh);
  
  (cursor = node_rshp).GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    bnode_ptr->GenerateEvent(DBO_Refresh);

RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical binti :: IsPositioned ( )
{

  return(stscusr1() ? NO : YES);



}

/******************************************************************************/
/**
\brief  Modify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

logical binti :: Modify ( )
{
  nodelist  cursor(node_genattr); 
  node      *node_ptr;
  logical    term = NO;
BEGINSEQ
  if ( RecursiveEvents(DBP_Modify) )                 ERROR 
  
  if ( !stscmod() )                                  // 14.9.2005
  {
    stssmod();
    term = node_base.Modify();

    cursor.GoTop();
    while ( node_ptr = cursor.GetNext() )
      if ( !((ACGenericAttr *)node_ptr)->Modify(NO) )
        term = YES;
  
    if ( term )                                        ERROR
  }
  
  if ( context )
    context->get_resource()->CheckEvent(context,NO);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MoveInstance - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveInstance"

logical binti :: MoveInstance (inti *intiptr )
{
  binti                   *bintiptr = (binti *)intiptr;
  nodelist                 scursor(bintiptr->get_node_base());
  nodelist                 tcursor(node_base);
  node                    *source;
  node                    *target;
  logical                 term = NO;
BEGINSEQ
  scursor.GoTop();
  tcursor.GoTop();
  while ( target = tcursor.GetNext() )
  {
    source = scursor.GetNext();
    target->get_nodeinst()->MoveInstance(source->get_nodeinst());
  }
  
  inti::MoveInstance(intiptr);
  
  (tcursor = node_genattr).GoTop();
  while ( target = tcursor.GetNextBNode() )
  {
    if ( target->SetupNode((logical)NO,NO) )      ERROR
  }
  
  ResetSubNodes();

  objid = ((binti *)intiptr)->get_objid();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenEvent - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenEvent"

logical binti :: OpenEvent ( )
{
  logical                 term = NO;
  term = GenerateEvent(DBO_Opened);
  
  if ( isel_init )
    memcpy(isel_init,iselarea,(int32)GetInstLength());

  return(term);
}

/******************************************************************************/
/**
\brief  PrepareGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrepareGenAttribute"

logical binti :: PrepareGenAttribute ( )
{
  nodelist                cursor(node_base);
  logical                 term = NO;
  ACGenericAttr          *acgnode;
  bnode                  *bnode_ptr;
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( bnode_ptr->get_bnodeinst()->PrepareGenAttribute() )
      term = YES;
    
  (cursor = node_genattr).GoTop();
  while ( acgnode = (ACGenericAttr *)cursor.GetNext() )
    if ( acgnode->PrepareGenAttribute() )
      term = YES;


  return(term);
}

/******************************************************************************/
/**
\brief  ProcessEvent - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessEvent"

logical binti :: ProcessEvent (DB_Event intevent )
{
  logical                 term = NO;
BEGINSEQ
  if ( context )
  {
    if ( GenerateEvent(intevent) )                   ERROR
    switch ( intevent )
    {
      case DBO_Read   : context->get_resource()->CheckEvent(context,YES);
                        break;
      default         : ;
    }
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

logical binti :: ProvGenAttribute ( )
{
  nodelist                cursor(node_base);
  logical                 siw;
  logical                 term = NO;
  ACGenericAttr          *acgnode;
  bnode                  *bnode_ptr;
  siw = SetInWork(YES);
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    bnode_ptr->get_bnodeinst()->ProvGenAttribute();
  SetInWork(siw);
    
  (cursor = node_genattr).GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    bnode_ptr->SetGenAttribute(AUTO,NULL);
    if ( bnode_ptr->IsInitInstance() && bnode_ptr->CanUpdateCollection() )
      bnode_ptr->Add(AUTO);
  }


  return(term);
}

/******************************************************************************/
/**
\brief  ProvideInstField - 



\return db_field - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInstField"

PropertyHandle *binti :: ProvideInstField ( )
{

  if ( !inst_field )
  {
    PropertyHandle  field(field_def,NULL);
    field.get_nodeptr()->Dereference(NULL);     // 7.1.02
    inst_field = new PropertyHandle(&field);
    inst_field->SetArea(iselarea);
    inst_field->Get(0);
  }

  return(inst_field);
}

/******************************************************************************/
/**
\brief  ReadEvent - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadEvent"

logical binti :: ReadEvent ( )
{
  bnode    *bnode_ptr;
  logical   ro;
  logical   term   = NO;
  RecursiveEvents(DBO_Read);
    
  if ( context )
  {
//  GenerateEvent(DBO_Read);  wird in RecursiveEvents gemacht
    context->get_resource()->CheckEvent(context,YES);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  RecursiveEvents - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecursiveEvents"

logical binti :: RecursiveEvents (DB_Event intevent )
{
  logical    term;
  bnode     *bnode_ptr;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  node_base.GoTop();
  while ( bnode_ptr = node_base.GetNextBNode() )
    bnode_ptr->Event(intevent);
    
  node_attr.GoTop();
  while ( bnode_ptr = node_attr.GetNextBNode() )
  {
    bnode_ptr->Event(intevent);
    bnode_ptr->get_bnodeinst()->RecursiveEvents(intevent);
  }
  
  node_genattr.GoTop();
  while ( bnode_ptr = node_genattr.GetNextBNode() )
    bnode_ptr->Event(intevent);

  term = GenerateEvent(intevent);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Release - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void binti :: Release ( )
{
  logical    is_isel = stscusr3();
  if ( stsclck() )
    Unlock();

  inti::Reset();
  stssnof();
  if ( is_isel )
    stssusr3();



}

/******************************************************************************/
/**
\brief  ReleaseProcessEvents - 



\return term - Termination code

\param  emit_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessEvents"

logical binti :: ReleaseProcessEvents (logical emit_opt )
{
  logical                 term = NO;
  if ( this && proc_event_handler )
    proc_event_handler->EmitEvents(emit_opt);

  return(term);
}

/******************************************************************************/
/**
\brief  RemoveReferences - 



\return term - Termination code

\param  srce_inti - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveReferences"

logical binti :: RemoveReferences (inti *srce_inti )
{
  nodelist                cursor(node_base);
  int32                    offset = 0;
  bnode                  *targ_node;
  node                   *srce_node;
  logical                 term = NO;
  cursor.GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    if ( srce_node = srce_inti->GetPropNode(targ_node->get_nodefield()->fmcbname,targ_node->get_prop_path()) )
    {
      if ( !srce_node->Check(YES) )
        if ( targ_node->get_bnodeinst()->RemoveReferences(srce_node->get_nodeinst()) )
          term = YES;
    }
    else
      if ( targ_node->get_bnodeinst()->RemoveReferences(srce_inti) )
        term = YES;
  }  
  
  (cursor = node_refr).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    offset = 0;
    if ( targ_node->FindSource(srce_inti,&offset) )
      targ_node->DeleteSet();
  }
  
  (cursor = node_rshp).GoTop();
  while ( targ_node = cursor.GetNextBNode() )
  {
    offset = 0;
    if ( !targ_node->get_nodefield()->get_sec_reference() && targ_node->FindSource(srce_inti,&offset) )
      targ_node->DeleteSet();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void binti :: Reset ( )
{

  if ( context )
  {
    GenerateEvent(DBO_Reset);
    context->SetDataState(DAT_undefined);
//  context->ShowInstance();
//  das geht nicht so, da dabei die hierarchisch gesetzten read-only stati vermurkst werden!!
//  aber wir wisssen auch nicht mehr, welches Problem damit gelöst werden sollte
  }
  
  objid = AUTO;
  inti::Reset();
  stssnof();

}

/******************************************************************************/
/**
\brief  ResetEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetEventHandler"

void binti :: ResetEventHandler (EventLink *event_link )
{

  if ( this && event_handler && event_handler->Find(event_link) )
    event_handler->RemoveAt();

}

/******************************************************************************/
/**
\brief  ResetGUID - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetGUID"

void binti :: ResetGUID ( )
{
  nodelist                cursor(node_base);
  bnode                  *nodeptr;
  inti::ResetGUID();

  cursor.GoTop();
  while ( nodeptr = cursor.GetNextBNode() )
    nodeptr->get_nodeinst()->ResetGUID();


}

/******************************************************************************/
/**
\brief  ResetGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetGenAttribute"

logical binti :: ResetGenAttribute ( )
{
  nodelist                cursor(node_base);
  logical                 term = NO;
  ACGenericAttr          *acgnode;
  bnode                  *bnode_ptr;
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( bnode_ptr->get_bnodeinst()->ResetGenAttribute() )
      term = YES;
    
  (cursor = node_genattr).GoTop();
  while ( acgnode = (ACGenericAttr *)cursor.GetNext() )
    if ( acgnode->ResetGenAttribute() )
      term = YES;


  return(term);
}

/******************************************************************************/
/**
\brief  ResetIdentity - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetIdentity"

logical binti :: ResetIdentity ( )
{
  nodelist                cursor(node_base);
  bnode                  *bnode_ptr;
  logical                 term = NO;
  if ( identity_pos >= 0 )
    *(EB_Number *)(iselarea+identity_pos) = 0;

  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    bnode_ptr->get_bnodeinst()->ResetIdentity();

  return(term);
}

/******************************************************************************/
/**
\brief  ResetInitializeEvent - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInitializeEvent"

logical binti :: ResetInitializeEvent ( )
{
  nodelist  cursor(node_base);
  node     *node_ptr;
  logical   term = NO;
  stsrusr1();
  while ( node_ptr = cursor.GetNext() )
    ((binti *)node_ptr->get_nodeinst())->ResetInitializeEvent();

  return(term);
}

/******************************************************************************/
/**
\brief  ResetInitialized - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInitialized"

void binti :: ResetInitialized ( )
{
  nodelist  cursor(node_base);
  node     *node_ptr;
  inti::ResetInitialized();
  
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->ResetInitInstance();



}

/******************************************************************************/
/**
\brief  ResetInstanceProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceProcessHandler"

void binti :: ResetInstanceProcessHandler (EventLink *event_link )
{

  if ( this && proc_event_handler )
    proc_event_handler->Remove(event_link);

}

/******************************************************************************/
/**
\brief  ResetNodes - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNodes"

logical binti :: ResetNodes ( )
{
  nodelist  cursor(node_rshp);
  node     *nodeptr;
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_tref).GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_base).GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  node_attr.GoTop();
  while ( nodeptr = node_attr.GetNext() )
  {
    nodeptr->GenerateEvent(DBO_Reset);
    Bnodeptr->get_bnodeinst()->RecursiveEvents(DBO_Reset);
  }
  return(NO);

}

/******************************************************************************/
/**
\brief  ResetOldBaseInst - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetOldBaseInst"

void binti :: ResetOldBaseInst ( )
{
  bnode      *bnode_ptr;
  node_base.GoTop();
  while ( bnode_ptr = node_base.GetNextBNode() )
  {
    bnode_ptr->GetFieldDef()->fmcbold = NO;
    bnode_ptr->get_bnodeinst()->ResetOldBaseInst();
  }

}

/******************************************************************************/
/**
\brief  ResetReferences - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetReferences"

logical binti :: ResetReferences ( )
{
  node     *node_ptr;

  node_rshp.GoTop();
  while ( node_ptr = node_rshp.GetNext() )
    node_ptr->ResetReference();

  node_refr.GoTop();
  while ( node_ptr = node_refr.GetNext() )
    node_ptr->ResetReference();

  node_genattr.GoTop();
  while ( node_ptr = node_genattr.GetNext() )
    node_ptr->ResetReference();

  node_base.GoTop();
  while ( node_ptr = node_base.GetNext() )
    node_ptr->ResetReference();
  return(NO);

}

/******************************************************************************/
/**
\brief  ResetSubNodes - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSubNodes"

logical binti :: ResetSubNodes ( )
{
  nodelist   cursor;
  node      *node_ptr;
  logical    term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  (cursor = node_refr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->ResetNode(YES);
  
  (cursor = node_rshp).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->ResetNode(YES);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetSubNodesRecursive - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSubNodesRecursive"

logical binti :: ResetSubNodesRecursive ( )
{
  nodelist  cursor(node_rshp);
  node     *nodeptr;
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_tref).GoTop();
  while ( nodeptr = cursor.GetNext() )
    nodeptr->ResetNode(YES);

  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    ((binti *)nodeptr->get_nodeinst())->ResetSubNodesRecursive();

  (cursor = node_base).GoTop();
  while ( nodeptr = cursor.GetNext() )
    ((binti *)nodeptr->get_nodeinst())->ResetSubNodesRecursive();

  node_attr.GoTop();
  while ( nodeptr = node_attr.GetNext() )
  {
    nodeptr->GenerateEvent(DBO_Reset);
    Bnodeptr->get_bnodeinst()->RecursiveEvents(DBO_Reset);
  }
  return(NO);

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

logical binti :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{
  nodelist  cursor(node_refr);
  logical   keymod  = YES;
  logical   term    = NO;
  node     *node_ptr;
BEGINSEQ
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr->SaveNode(switchopt,overwrite) )   ERROR

/*  führt zu Rekursion, muß auch nicht sein
  (cursor = node_tref).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr = node_ptr->GetNode() )
      if ( node_ptr->SaveNode(switchopt,overwrite) ) ERROR
*/

  if ( node_rshp.GetCount() )
  {
    keymod  = stscmod() ? struct_def->CheckKeyMod(iselarea,GetOldInst(NULL)) : NO;
    (cursor = node_rshp).GoTop();
    while ( node_ptr = cursor.GetNext() )
      if ( node_ptr->get_nodeidnt() == NODE_ID )
      {      
        if ( stscmod() )
          if ( ((ACRelationship *)node_ptr)->UpdateInverse(keymod) )
                                                     ERROR
        if ( node_ptr->SaveNode(switchopt,overwrite) )    
                                                     ERROR
      }
  }

  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr->SaveNode(switchopt,overwrite) )    ERROR

  inti::Save(switchopt,overwrite,refresh_opt);
RECOVER
//GenerateEvent(DBO_NotStored);  kommt später, vielleicht
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SaveGenAttr - 



\return term - Termination code

\param  switchopt - 
\param  overwrite - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveGenAttr"

logical binti :: SaveGenAttr (logical switchopt, logical overwrite )
{
  nodelist  cursor(node_base);
  bnode     *bnode_ptr;
  node      *node_ptr;
  logical    term = NO;
BEGINSEQ
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( bnode_ptr->get_nodeinst() )
      if ( bnode_ptr->get_bnodeinst()->SaveGenAttr(switchopt,overwrite) )
                                                     ERROR
  
  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( node_ptr->get_nodecur() == AUTO && node_ptr->get_nodeinst()->stscini() && node_ptr->stscmod() )
      if ( !node_ptr->Add(AUTO,NULL,NULL,node_ptr->get_nodeinst()->get_iselarea(),NO) ) 
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetAutoIdent - 



\return cond_setting - 

\param  kcbptr - 
\param  attrtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoIdent"

char binti :: SetAutoIdent (kcb *kcbptr, int attrtype )
{
  nodelist       cursor(node_base);
  ACShareBase   *nodeptr;
  char           cond_setting = NO;
  cursor.GoTop();
  while ( nodeptr = (ACShareBase *)cursor.GetNext() )
    if ( nodeptr->IsACShareBase() && (cond_setting = nodeptr->SetAutoIdent(kcbptr,attrtype)) )
      break;
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  SetClusterNumber - 




\param  clnumb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClusterNumber"

void binti :: SetClusterNumber (EB_Number clnumb )
{



}

/******************************************************************************/
/**
\brief  SetEventHandler - 




\param  event_links - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEventHandler"

void binti :: SetEventHandler (EventLinkList *event_links )
{

BEGINSEQ
  if ( event_handler && event_links != event_handler ) 
                                                    SDBERR(99)
  if ( event_handler = event_links )
    event_handler->Reserve();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetGenAttrMod - 



\return term - Termination code

\param  initinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttrMod"

logical binti :: SetGenAttrMod (void *initinst )
{
  nodelist  cursor(node_base);
  bnode     *bnode_ptr;
  node      *node_ptr;
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( bnode_ptr->get_nodeinst() )
      bnode_ptr->get_bnodeinst()->SetGenAttrMod();
  
  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    if ( ((ACGenericAttr *)node_ptr)->get_attr_type() )
      node_ptr->stssmod();


  return(NO);
}

/******************************************************************************/
/**
\brief  SetIdentity - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIdentity"

void binti :: SetIdentity ( )
{

  if ( identity_pos >= 0 )
    *(EB_Number *)(iselarea+identity_pos) = objid;



}

/******************************************************************************/
/**
\brief  SetInitialize - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInitialize"

logical binti :: SetInitialize ( )
{
  nodelist  cursor(node_base);
  node     *node_ptr;
  logical                 term = NO;
  stssini();
  while ( node_ptr = cursor.GetNext() )
    ((binti *)node_ptr->get_nodeinst())->SetInitialize();

  return(term);
}

/******************************************************************************/
/**
\brief  SetInitializeEvent - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInitializeEvent"

logical binti :: SetInitializeEvent ( )
{
  nodelist  cursor(node_base);
  node     *node_ptr;
  logical                 term = NO;
  stssusr1();
  while ( node_ptr = cursor.GetNext() )
    ((binti *)node_ptr->get_nodeinst())->SetInitializeEvent();

  return(term);
}

/******************************************************************************/
/**
\brief  SetInstanceEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceEventHandler"

void binti :: SetInstanceEventHandler (EventLink *event_link )
{

  if ( !event_handler )
    event_handler = new EventLinkList();
  
  event_handler->AddEventLink(event_link);


}

/******************************************************************************/
/**
\brief  SetInstanceProcessHandler - 




\param  bnodeptr - 
\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceProcessHandler"

void binti :: SetInstanceProcessHandler (bnode *bnodeptr, EventLink *event_link )
{

  if ( this )
  {
    if ( !proc_event_handler )
      proc_event_handler = new ProcessEventHandler(bnodeptr);
  
    proc_event_handler->AddEventLink(event_link);
  }

}

/******************************************************************************/
/**
\brief  SetMBNumber - 




\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMBNumber"

void binti :: SetMBNumber (int16 mbnumber )
{



}

/******************************************************************************/
/**
\brief  SetObjectID - 




\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetObjectID"

void binti :: SetObjectID (int64 obj_id )
{

  objid = obj_id;

}

/******************************************************************************/
/**
\brief  SetOldBaseInst - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOldBaseInst"

void binti :: SetOldBaseInst ( )
{
  nodelist   cursor(node_base);
  bnode     *bnode_ptr;
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    bnode_ptr->GetFieldDef()->fmcbold = bnode_ptr->get_nodeinst()->stscold();
    bnode_ptr->get_bnodeinst()->SetOldBaseInst();
  }

}

/******************************************************************************/
/**
\brief  SetProcEventHandler - 




\param  peh_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProcEventHandler"

void binti :: SetProcEventHandler (ProcessEventHandler *peh_ptr )
{

BEGINSEQ
  if ( proc_event_handler && proc_event_handler != peh_ptr )
                                                    SDBERR(99)
  if ( proc_event_handler = peh_ptr )
    proc_event_handler->Reserve();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetReadOnly - 



\return term - Termination code

\param  readonly - Read-only state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

logical binti :: SetReadOnly (logical readonly )
{
  nodelist  cursor;
  bnode    *node_ptr = NULL;
  logical   term     = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ

  (cursor = node_base).GoTop();
  while ( node_ptr = (bnode *)cursor.GetNext() )
  {
    node_ptr->MarkReadOnly(readonly);
    ((binti *)node_ptr->get_nodeinst())->SetReadOnly(readonly);
  }

  (cursor = node_refr).GoTop();
  while ( node_ptr = (bnode *)cursor.GetNext() )
  {
    node_ptr->MarkReadOnly(readonly);
    node_ptr->GetStructContext()->SetReadOnly(readonly);
  }
  
  (cursor = node_rshp).GoTop();
  while ( node_ptr = (bnode *)cursor.GetNext() )
  {
    node_ptr->MarkReadOnly(readonly);
    node_ptr->GetStructContext()->SetReadOnly(readonly);
  }

  (cursor = node_genattr).GoTop();
  while ( node_ptr = (bnode *)cursor.GetNext() )
  {
    node_ptr->MarkReadOnly(readonly);
    node_ptr->GetStructContext()->SetReadOnly(readonly);
  }
  
  (cursor = node_attr).GoTop();
  while ( node_ptr = (bnode *)cursor.GetNext() )
  {
    node_ptr->MarkReadOnly(readonly);
    node_ptr->GetStructContext()->SetReadOnly(readonly);
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetRefContext - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRefContext"

logical binti :: SetRefContext (inti *intiptr )
{
   CTX_Structure   *ref_context = intiptr ? intiptr->GetContext() : NULL;
  if ( context  )
    context->SetRefContext(ref_context);
  return(NO);
}

/******************************************************************************/
/**
\brief  SetStructAccess - 




\param  struct_access - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructAccess"

void binti :: SetStructAccess (StructAccess *struct_access )
{



}

/******************************************************************************/
/**
\brief  SetupInst - 




\param  update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInst"

void binti :: SetupInst (logical update )
{
  bnode    *bnode_ptr;

BEGINSEQ
  node_genattr.GoTop();
  while ( bnode_ptr = node_genattr.GetNextBNode() )
  {
    if ( bnode_ptr->SetupNode((logical)NO,NO) )      ERROR
    bnode_ptr->SetGenAttribute(AUTO,NULL);
  }
  
  if ( iselarea )
    SetIdentity();
  
  stssfil();
  if ( update )
    stsssav();
  stssold();
  
  ReadEvent();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetupNewInst - 



\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNewInst"

logical binti :: SetupNewInst (logical global_add )
{
  nodelist       cursor(node_base);
  logical        mod;
  logical        siw;
  node          *node_ptr;
  ACGenericAttr *genattr;
  logical        term = NO;
BEGINSEQ
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
  {
    mod = node_ptr->stscmod();
    if ( node_ptr->SetupNode(YES,NO) )                ERROR
    if ( !node_ptr->Add(0,global_add) )               ERROR
    if ( mod )
      node_ptr->get_nodeinst()->Save(NO,NO,NO);
  }
  
  siw = SetInWork(YES);
  (cursor = node_genattr).GoTop();
  while ( genattr = (ACGenericAttr *)cursor.GetNext() )
  {
    mod = genattr->stscmod();
//  if ( genattr->SetupNode(YES,NO) )               // nimmt das ini für nachgeordnete MEMOS weg!!
//  if ( genattr->ACReference::SetupNode(YES,NO) )  23.5.2003: setzt ini für nachgeordnete MEMOS zurück
    if ( genattr->ACReference::SetupNode(YES,YES) ) 
      term = YES;
    if ( mod )
    {
      if ( genattr->AddGenAttribute() )
        term = YES;
      else
        genattr->get_nodeinst()->Save(NO,NO,NO);   // damit auch Memos und Referenzen gesichert werden!!
    }
  }
  SetInWork(siw);
  
  if ( term )                                        ERROR
  CheckAddReference();
  if ( SetupSubNodes(YES,NO) )                       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupReadOnly - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReadOnly"

logical binti :: SetupReadOnly ( )
{
  nodelist  cursor(node_base);
  bnode    *bnode_ptr;
  logical   ro;
  logical   term   = NO;
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    bnode_ptr->ReserveInstance();
    ((isel *)bnode_ptr->get_nodeinst())->SetupReadOnly();
    if ( !bnode_ptr->get_nodewrit() )
      stsswpt(1);
  }
  (cursor = node_genattr).GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    bnode_ptr->ReserveInstance();

  return(term);
}

/******************************************************************************/
/**
\brief  SetupSubNodes - 



\return term - Termination code

\param  create_ref - 
\param  for_event_handling - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSubNodes"

logical binti :: SetupSubNodes (logical create_ref, logical for_event_handling )
{
  nodelist   cursor(node_refr);
  bnode     *node_ptr;
  logical    term = NO;
  cursor.GoTop();
  while ( node_ptr = cursor.GetNextBNode() )
    if ( !for_event_handling || node_ptr->get_has_event_handler() )
      if ( node_ptr->SetupSubNode(create_ref) )
        term = YES;
  
  (cursor = node_rshp).GoTop();
  while ( node_ptr = cursor.GetNextBNode() )
    if ( !for_event_handling || node_ptr->get_has_event_handler() )
      if ( node_ptr->SetupSubNode(create_ref) )
        term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  StructAttrEvents - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructAttrEvents"

logical binti :: StructAttrEvents (DB_Event intevent )
{
  nodelist   cursor(node_attr);
  logical    term;
  node      *node_ptr;
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->get_nodeinst()->StructAttrEvents(intevent);
  
  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->get_nodeinst()->StructAttrEvents(intevent);

  term = GenerateEvent(intevent);
  return(term);
}

/******************************************************************************/
/**
\brief  StructureEvents - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructureEvents"

logical binti :: StructureEvents (DB_Event intevent )
{
  nodelist   cursor(node_base);
  logical    term;
  node      *node_ptr;
  cursor.GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->get_nodeinst()->StructureEvents(intevent);
    
  (cursor = node_attr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->get_nodeinst()->StructureEvents(intevent);
  
  (cursor = node_genattr).GoTop();
  while ( node_ptr = cursor.GetNext() )
    node_ptr->get_nodeinst()->StructureEvents(intevent);

  term = GenerateEvent(intevent);
  return(term);
}

/******************************************************************************/
/**
\brief  after_add - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "after_add"

void binti :: after_add ( )
{

  stsrsav();
  stsrmod();
  stsrold();
  stssfil();
  
  if ( context )
  {
    RecursiveEvents(DBO_Created);
    StructureEvents(DBO_Stored);
    context->get_resource()->CheckEvent(context,YES);
  }

}

/******************************************************************************/
/**
\brief  before_add - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "before_add"

logical binti :: before_add ( )
{

  return( context ? RecursiveEvents(DBP_Create) : NO );


}

/******************************************************************************/
/**
\brief  binti - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  mspool - 
\param  strdefptr - 
\param  instptr - 
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "binti"

     binti :: binti (node *nodeptr, void *mspool, DBStructDef *strdefptr, void *instptr, logical crt_opt )
                     : inti (nodeptr,strdefptr,instptr,NO),
  node_base(),
  node_refr(),
  node_rshp(),
  node_genattr(),
  node_tref(),
  isel_init(NULL),
  cluster_crtopt(NO),
  context(NULL),
  identity_pos(AUTO),
  inst_field(NULL),
  objid(AUTO),
  event_handler(NULL),
  proc_event_handler(NULL),
  weak_typed_offset(0)
{
  binti          *base_binti;
BEGINSEQ
  stssnof();
  stssusr1();
  if ( Init(nodeptr,NULL,strdefptr,instptr) )         ERROR
    
  if ( struct_def && crt_opt )
  {  
    if ( struct_def->CreateSubNodes(nodeptr,this,context,iselarea,0) )
                                                      ERROR
//    InitInit();
  }

  InitInit();
  if ( nodeptr )
  {
    if ( Bnodeptr->get_nodefield()->get_weak_typed() && Bnodeptr->get_nodefield()->fmcbityp != T_VOID )
    {
      if ( !(base_binti = GetBaseBinti(Bnodeptr->get_nodefield()->fmcbtype,NO)) )
                                                     SDBERR(99)
      weak_typed_offset = base_binti->get_iselarea() - iselarea;
      if ( weak_typed_offset < 0 || weak_typed_offset > GetInstLength() )
                                                     SDBERR(99)  // sicherheitsabfrage
    }
    Bnodeptr->SetInti(this);
  }
  if ( nodeptr && !Bnodeptr->IsContextEnabled() )
    DisableContext();
RECOVER


ENDSEQ
  stsrusr1();
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "binti"

     binti :: binti ( )
                     : inti (),
  node_base(),
  node_refr(),
  node_rshp(),
  node_genattr(),
  node_tref(),
  isel_init(NULL),
  cluster_crtopt(NO),
  context(NULL),
  identity_pos(AUTO),
  inst_field(NULL),
  objid(AUTO),
  event_handler(NULL),
  proc_event_handler(NULL),
  weak_typed_offset(0)
{

  stssnof();

}

/******************************************************************************/
/**
\brief  set_objid - 




\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_objid"

void binti :: set_objid (int64 obj_id )
{

  objid = obj_id;

}

/******************************************************************************/
/**
\brief  ~binti - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~binti"

     binti :: ~binti ( )
{

  binti::Close();


}


