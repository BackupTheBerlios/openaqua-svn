/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    bnode

\brief    


\date     $Date: 2006/08/30 20:11:45,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "bnode"

#include  <popa7.h>
#include  <cactp.h>
#include  <cevtp.h>
#include  <cfctp.h>
#ifndef   DLL_bnode_HPP
#define   DLL_bnode_HPP
#include  <sbnode.hpp>
#include  <sDLL.h>
#endif
#ifndef   DPA_inti_HPP
#define   DPA_inti_HPP
#include  <sinti.hpp>
#include  <sDPA.h>
#endif
#include  <sACExtend.hpp>
#include  <sACGenericAttr.hpp>
#include  <sACObject.hpp>
#include  <sACPath.hpp>
#include  <sACRelationship.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCSHandle.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDictionary.hpp>
#include  <sEventLink.hpp>
#include  <sEventLinkList.hpp>
#include  <sEventParms.hpp>
#include  <sInstBuffer.hpp>
#include  <sInstanceCache.hpp>
#include  <sLACObject.hpp>
#include  <sProcessEventHandler.hpp>
#include  <sbinti.hpp>
#include  <sbnode.hpp>
#include  <scvb.hpp>
#include  <sdbf.hpp>
#include  <sflnk.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <ssmcb.hpp>
#include  <sbnode.hpp>


/******************************************************************************/
/**
\brief  AddPathNode - 



\return term - Termination code

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddPathNode"

logical bnode :: AddPathNode (bnode *bnodeptr )
{
  logical                 term = NO;
  if ( !path_nodes )
    path_nodes = new DLL(bnode)();

  path_nodes->AddTail(bnodeptr);
  return(term);
}

/******************************************************************************/
/**
\brief  CacheSize - 



\return term - Termination code

\param  bufnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheSize"

logical bnode :: CacheSize (int16 bufnum )
{
  logical                 term = NO;
  if ( bufnum == 0 )
  {
    delete cache_list;
    cache_list = NULL;
  }
  else
  {
    if ( !cache_list )
      cache_list = new InstanceCache(this);
    cache_list->Resize(bufnum);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  CanUpdateCollection - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanUpdateCollection"

logical bnode :: CanUpdateCollection (logical chknode )
{
  logical           cond = YES;
BEGINSEQ
  if ( chknode && Check(YES) )	                     ERROR
  
  if ( nodeacc == PI_Read )                          ERROR
  cond = context && context->IsReadOnly() ? NO : YES; 

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  CancelBuffer - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelBuffer"

logical bnode :: CancelBuffer ( )
{
  logical                 term = NO;
  if ( inti_buffer )
    term = inti_buffer->Cancel();
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeBuffer - 



\return bufnum - 

\param  bufnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeBuffer"

int16 bnode :: ChangeBuffer (int16 bufnum )
{

BEGINSEQ
  if ( bufnum == 0 || bufnum == 1 )
  {
    if ( !inti_buffer )                              LEAVESEQ
    Switch(AUTO);
    ReleaseBuffer();
  }

  if ( !nodefield->IsTyped() || nodeacc != PI_Read ) SDBERR(230)
  if ( inti_buffer && bufnum == inti_buffer->get_buf_count() )
                                                     LEAVESEQ
  Switch(AUTO);
  ReleaseBuffer();
  
  if ( bufnum == AUTO )
    bufnum = GetCount();
  
  if ( !(inti_buffer = new InstBuffer(bufnum,this)) ) SDBERR(95)
  bufnum = inti_buffer->get_buf_count();
RECOVER
  bufnum = AUTO;
ENDSEQ
  return(bufnum);
}

/******************************************************************************/
/**
\brief  ChangeMode - 



\return oldmode - 

\param  accopt - Access mode
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC bnode :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC     oldmode = PI_undefined;
BEGINSEQ
  if ( chkopt && Check(NO,NO) )                      ERROR
  if ( chkopt && CheckAccess(accopt) )               ERROR
  
  if ( inti_buffer && accopt > PI_Read )             SDBERR(244)
  if ( chkopt && nodecur != AUTO )
    if ( Switch(AUTO) )                              ERROR
       
  oldmode = nodeacc;
  nodeacc = accopt;
  
  if ( nodeinst )
    if ( nodeinst->ChangeMode(accopt) )              ERROR
RECOVER
  if ( oldmode != PI_undefined && chkopt )
  {
    ChangeMode(oldmode,NO);
    oldmode = PI_undefined;
  }
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

logical bnode :: Check (logical autoini, logical acccheck )
{
  logical   term = NO;
BEGINSEQ
  if ( stscusr3() || stscfil() )                     LEAVESEQ
  if ( stscerr() )                                   ERROR
    
  if ( acccheck )
    if ( nodenode && Bnodenode->Check_intern() )     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckAccess - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  NODEICK - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAccess"

logical bnode :: CheckAccess ( )
{
  logical   term   = NO;

BEGINSEQ
  if ( nodeacc == PI_Read                ||
       ( !nodefield->get_update() &&
         nodenode && !Bnodenode->nodewrit ) )        SDBERR(28)
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAccess"

logical bnode :: CheckAccess (PIACC accopt )
{
  logical    term = NO;
BEGINSEQ
  if ( accopt == PI_Read || accopt == PI_undefined ) LEAVESEQ
  if ( nodefield && nodefield->get_log_reference() ) LEAVESEQ // temporärer Extent
  if ( GetObjectHandle() && GetObjectHandle()->get_access_mode() == PI_Read &&
       (!nodenode || Bnodenode->get_nodeacc() < accopt) )    
                                                     SDBERR(121)
                                                     
                                                     
/*  wenn die ebi's alle beim Isel-Add erzeugt werden (ist der Fall) 
    und nicht gelöscht werden (ist nicht der Fall bei refx), kann diese 
    Prüfung entfallen, da dann alle Referenzen updatefähig sind. 
  if ( !nodefield->get_update() )
  {
    if ( accopt != PI_Write )                        SDBERR(121)
    if ( nodenode && nodenode->get_nodeacc() != PI_Write )
                                                     SDBERR(121)
  }
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckAddSet - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAddSet"

char bnode :: CheckAddSet ( )
{
  char    term = NO;
BEGINSEQ
  if ( nodenode && nodenode->get_nodeinst()->stscini() )
  {
    nodeinst->stsrini();              // muss gesetzt sein, aber wir müssen sichern nach unten von oben verhindern
    if ( !nodenode->Add(AUTO,NULL,NULL,nodenode->get_nodeinst()->get_iselarea()) )
                                                     ERROR
    if ( nodeinst->IsPositioned() )  // sonst ist Add schon gelaufen
    {
      term = AUTO;                                   LEAVESEQ
    }
    nodeinst->stssini();            // nu isses wida da
  }
  
  if ( CheckUpdateSet(NO) )                          ERROR

RECOVER
  term = YES;
ENDSEQ
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

logical bnode :: CheckDelEmpty ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !nodefield->get_del_empty() )                 LEAVESEQ

  if ( GetCount() > 0 )                              
  {
    SDBEV1(prop_path,UNDEF)
    SDBEV2(nodenode->GetCurrentType(),ID_SIZE)
    SDBERR(375)
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckGenAttribute"

logical bnode :: CheckGenAttribute ( )
{
  node               *high_node;
  ACGenericAttr      *gena_node;
  logical             term = NO;
BEGINSEQ
  if ( nodewrit != 255 && nodeacc > PI_Read )         
  {  
//    if ( GenerateEvent(DBP_Modify) )                 ERROR modif. sind noch nicht in instanz!

    if ( high_node = nodenode )
      if ( high_node->get_nodetype() == NT_ACGenericAttr ||
           ( (high_node = nodenode->get_nodenode() )     && 
             high_node->get_nodetype() == NT_ACGenericAttr) )
        if ( !high_node->IsPositioned() && high_node->get_nodenode()->IsPositioned() )
        {
          gena_node = (ACGenericAttr *)high_node;
          gena_node->SetGenAttribute(gena_node->get_attr_type(),NULL);
        }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical bnode :: CheckModify ( )
{
  logical             term = NO;
BEGINSEQ
  if ( CheckGenAttribute() )                         ERROR // stand bisher hinter der Prüfung, geht aber nicht, da für felder in generischen Memos das ini hier erst gesetzt wird 29.1.03
  
  if ( !IsWrite() && (!nodeinst || !nodeinst->stscini()) )          
                                                     SDBERR(76)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckPropCtxFunc - 



\return term - Termination code

\param  fnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPropCtxFunc"

logical bnode :: CheckPropCtxFunc (char *fnames )
{
  logical    term = NO;
BEGINSEQ
  if ( !context )                                    ERROR
    
  if ( context->ExecuteFunction(fnames,YES) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckStrCtxFunc - 



\return term - Termination code

\param  fnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckStrCtxFunc"

logical bnode :: CheckStrCtxFunc (char *fnames )
{
  logical   term = NO;
BEGINSEQ
  if ( !nodeinst || !Bnodeinst->get_context() )       ERROR
    
  if ( Bnodeinst->ExecuteFunction(fnames,YES) )      ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckUpdateSet - 



\return term - Termination code

\param  no_error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckUpdateSet"

logical bnode :: CheckUpdateSet (logical no_error )
{
  logical                 term = NO;
BEGINSEQ
  if ( nodeacc == PI_Read || !CanUpdateCollection(NO) )  
  {
    if ( !no_error )                                 SDBERR(28)
                                                     ERROR
  }

  if ( !nodenode || Bnodenode->get_nodewrit() || 
       (nodecur != AUTO && nodeacc == PI_Update) )   LEAVESEQ

  if ( Bnodenode->get_nodeacc() == PI_Write )        
  {
    if ( !IsInitInstance() )
    {
      if ( !no_error )                               SDBERR(28)
                                                     ERROR
    }
    if ( nodenode && nodenode->CheckUpdate() )       ERROR
  }
  else
    if ( !nodefield->get_update() )
    {
      if ( !no_error )                               SDBERR(28)
                                                     ERROR
    }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Check_intern - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_intern"

logical bnode :: Check_intern ( )
{
  logical         term = NO;
BEGINSEQ
  if ( nodewrit != 255 && !(nodeinst && nodeinst->IsSelected()) )
    if ( AutoPosition() )                           SDBERR(235)
  
    

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

logical bnode :: Close ( )
{
  bnode    *bnodeptr;
  uint16    count;
  inti     *intiptr;
BEGINSEQ
  if ( nodeidnt != NODE_ID )                         LEAVESEQ
  
  if ( path_nodes )
  {
    path_nodes->GoTop();
    while ( bnodeptr = path_nodes->RemoveTail() )
      delete bnodeptr;
    delete path_nodes;
    path_nodes = NULL;
  }
  
  if ( cache_list )
  {
    cache_list->Resize(0);
    delete cache_list;
    cache_list = NULL;
  }
    
  if ( context->ProcessState() != PRC_Busy && context->ProcessState() != PRC_Closed )
  {
    context->SetProcessState(PRC_Busy);
    if ( nodeinst )
      nodeinst->Close();
    GenerateEvent(DBO_Close);
    context->SetProcessState(PRC_Closed);
  }
  ReleaseProcessEvents(YES);

  ReleaseBaseNode();
  if ( base_reference )
    ((bnode *)base_reference)->set_base_node(NULL);
  
  if ( type_inti )
  {
    nodeinst  = NULL;
    count = type_inti->GetSize();
    while ( count-- )
      if ( intiptr = (*type_inti)[count] )
        delete intiptr;
    delete type_inti;
    type_inti = NULL;
  }

  is_opened = NO;
  ReleaseBuffer();
  
  node::Close();
  id_key    = NULL;
  sk_index  = NULL;
  nodefield = NULL;
  
  UninitHandle();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  CompareKey - 



\return cmpval - 

\param  skey1 - 
\param  skey2 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareKey"

int8 bnode :: CompareKey (char *skey1, char *skey2, logical chknode )
{
  int       cmpval = ERIC;

BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  SDBEV1(nodefield->fmcbsmcb->smcbname,ID_SIZE)

  if ( !id_key )                                     SDBERR(71)
  cmpval = id_key->kcbkcp(skey1,skey2);

RECOVER

ENDSEQ
  return(cmpval);  

}

/******************************************************************************/
/**
\brief  CompareSortKey - 



\return cmpval - 

\param  skey1 - 
\param  skey2 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareSortKey"

int8 bnode :: CompareSortKey (char *skey1, char *skey2, logical chknode )
{
  int        cmpval = ERIC;
  kcb       *kcbptr;
BEGINSEQ
  if ( chknode && Check(YES) )	                    ERROR

  if ( !(sk_index && (kcbptr = sk_index->get_key_def())) &&
       !(kcbptr = id_key)   )                       ERROR
  
  cmpval = kcbptr->kcbkcp(skey1,skey2);

RECOVER

ENDSEQ
  return(cmpval);  

}

/******************************************************************************/
/**
\brief  CopyBReferences - 



\return term - Termination code

\param  srce_inti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyBReferences"

logical bnode :: CopyBReferences (inti *srce_inti, PIREPL db_replace, PIREPL copy_type )
{
  node                   *srce_node;
  fmcb                   *srce_fmcb;
  kcb                    *kcbptr  = NULL;
  char                    keyarea[MAX_KEYLEN];
  logical                 idkey   = NO;
  int32                    lindx0  = 0;
  int32                    offset  = 0;
  logical                 term    = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  if ( nodefield->get_sec_reference() )              LEAVESEQ
  if ( Bnodeinst->get_node_base().GetCount() +
       Bnodeinst->get_node_refr().GetCount() +
       Bnodeinst->get_node_rshp().GetCount()  == 0 ) LEAVESEQ
  
  if ( !(srce_fmcb = FindSource(srce_inti,&offset,&srce_node)) )
                                                     LEAVESEQ
  if ( !srce_node )                                  LEAVESEQ // das ist auch fehler, wenn srce nicht Elementarfeld

  if ( sk_index ) 
  {
    if ( kcbptr = sk_index->get_key_def() )
      if ( nodefield->fmcbdim != 1 &&
           !sk_index->get_unique()  ) SDBERR(99)
  }
  if ( !kcbptr && nodefield->GetDBStruct() )
    if ( kcbptr = id_key )
      idkey = YES;
  
  if ( kcbptr && kcbptr->scbsmcb->smcbsts.stscnof() )
    kcbptr = NULL;
      
  while ( srce_node->Get(lindx0) )
  {
    if ( Switch(AUTO) )                              ERROR
    if ( nodefield->get_weak_typed() )
      if ( SetType(srce_node->get_nodeinst()->get_struct_def()->smcbname) )
                                                     ERROR
//    if ( kcbptr )  hier haben wir Probleme, wenn wir die wfd's kopieren.     15.11.00
    if ( kcbptr && !idkey )  // bis auf weiteres alle unsortierten über index. 15.11.00
    {
      Initialize_intern(NULL);
      GetCurrentTypeDef()->CopyInstance(nodeinst->get_iselarea(),srce_node->GetCurrentTypeDef(),srce_node->get_nodeinst()->get_iselarea(),AUTO,UNDEF);
      Get(idkey 
          ? ExtractKey(keyarea,nodeinst->get_iselarea(),NO)
          : ExtractSortKey(keyarea,nodeinst->get_iselarea(),NO));
    }
    else
      Get(lindx0);
    
    if ( Exist() )
    {
      Bnodeinst->CopyBReferences(srce_node->get_nodeinst(),db_replace,copy_type);
      Save(YES,NO,NO);
    }
    else
      term = YES;
    lindx0++;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CopyEventHandler - 



\return term - Termination code

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyEventHandler"

logical bnode :: CopyEventHandler (bnode *bnodeptr )
{
  int         count = 0;
  inti       *intiptr;
  logical     term = NO;
  if ( !Check(YES,NO) )
  {
    if ( !event_handler )
      if ( event_handler = bnodeptr->get_event_handler() )
        event_handler->Reserve();

    if ( !proc_event_handler )
      if ( proc_event_handler = bnodeptr->get_proc_event_handler() )
        proc_event_handler->Reserve();

    if ( nodeinst && bnodeptr->get_nodeinst() )
    {
      if ( !type_inti )
        Bnodeinst->CopyEventHandler((binti *)bnodeptr->get_nodeinst());   
      else
      {
        count = type_inti->GetSize();
        while ( count-- )
          if ( intiptr = (*type_inti)[count] )
            Bintiptr->CopyEventHandler((binti *)bnodeptr->get_nodeinst());   
      }
    }
  }

  return(term);
}

/******************************************************************************/
/**
\brief  CopyInst - 



\return targinst - 
-------------------------------------------------------------------------------
\brief  NODEIC - 



\param  srcenode - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  set_pos0_w - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInst"

void *bnode :: CopyInst (node *srcenode, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical chknode )
{
  char     *targinst = NULL;
  logical   setwpt   = NO;

BEGINSEQ
  if ( Check(YES) || srcenode->Check(YES) )          ERROR
    
  if ( srcenode->get_nodecur() == AUTO || 
       (!srcenode->IsDirectField() && !srcenode->get_nodeinst()->stscfil()) ||
       (srcenode->IsDirectField()  && !srcenode->get_highnod()->get_nodeinst()->stscfil()) )
                                                     SDBERR(76)
  if ( srcenode->get_nodetype() != NT_CSNode )
    setwpt = (srcenode->get_nodeinst()->CheckWProtect() == 1 );
  nodeinst->SetRefContext(srcenode->get_nodeinst());
  srcenode->get_nodeinst()->SetRefContext(nodeinst);
  if ( !(targinst = CopyInstance(srcenode->get_nodeinst(),db_replace,copy_type,w_newkey,
                                 set_pos0_w,setwpt)) ) ERROR
  nodeinst->SetRefContext(NULL);
  srcenode->get_nodeinst()->SetRefContext(NULL);

RECOVER

ENDSEQ
  return(targinst);

}

/******************************************************************************/
/**
\brief  NODEIC_ - 



\param  srceinst - 
\param  srcesmcb - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  set_pos0_w - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInst"

void *bnode :: CopyInst (void *srceinst, smcb *srcesmcb, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical setwpt )
{
  char     *keyptr  = NULL;
  char     *sortkey = NULL;
  smcb     *targsmcb;
  kcb      *kcbptr = NULL;
  char     *targinst;
  logical   exist   = NO;
  PIREPL    replopt = db_replace;
  int16     converr = NO;
BEGINSEQ
  if ( Check(YES) || !srcesmcb )                    ERROR
  if ( replopt == REPL_none && copy_type == REPL_relationships )
    replopt = REPL_local;
    
  if ( CheckAccess(PI_Write) )                      ERROR

  if ( Switch(AUTO) )                               ERROR
  if ( nodefield->get_weak_typed() )
    if ( SetType(srcesmcb->smcbname) )              ERROR
      
  targsmcb = GetCurrentTypeDef();    
  Initialize_intern(NULL);
  targinst = nodeinst->get_iselarea();

  targsmcb->CopyInstance(targinst,srcesmcb,(char *)srceinst,REPL_GUID,UNDEF);
  Bnodeinst->ResetIdentity();

  if ( sk_index && (kcbptr = sk_index->get_key_def()) )
  {
    if ( w_newkey )
      kcbptr->kcbkpt(GetKeyInstance(NULL,targinst),w_newkey);
    if ( sk_index->get_unique() )
      if ( sortkey = ExtractSortKey(NULL,targinst) )
      {
        if ( !(exist = !LocateKey(sortkey,YES)) )
          if ( nodefield->fmcbdim == 1 )
            exist = Get(sortkey,NO) ? YES : NO;
        targsmcb->CopyInstance(targinst,srcesmcb,(char *)srceinst,REPL_GUID,UNDEF);
      }
    if ( exist && !replopt )                         ERROR
  }
                                                          
  if ( exist )
  {
    if ( !Get(sortkey,NO) )                          ERROR
  }  
  else
  {
    if ( nodefield->fmcbsmcb->smcbidky ) 
      exist = GetGlobalID().IsEmpty() ? NO : YES;    SDBCERR
    if ( !Add(set_pos0_w,NULL,NULL,targinst) )       ERROR
    if ( exist && !replopt )                         LEAVESEQ
  }

  if ( exist )
  { 
    if ( !replopt )                                  LEAVESEQ
//  this check permits copying instances in not owning collections for repl_local
//  not checking this may cause other problems 3.4.2006 (see also CopyInstance)
//    if ( replopt == REPL_local && copy_type != REPL_relationships)
//      if ( nodenode && !nodefield->get_owning() )    LEAVESEQ
  }

  if ( !IsWrite() )                                  SDBERR(28)
    
  if ( replopt == REPL_none || replopt == REPL_local )
    Bnodeinst->SetOldBaseInst();
  
  if ( replopt != REPL_direct )
  {
    if ( targsmcb->CopyInstance(targinst,srcesmcb,(char *)srceinst,db_replace,copy_type) )
      converr = ConversionError(srceinst,srcesmcb);
    Bnodeinst->SetIdentity();
  }
  
  if ( replopt == REPL_none || replopt == REPL_local )
    Bnodeinst->ResetOldBaseInst();
  
  if ( kcbptr && w_newkey )
    kcbptr->kcbkpt(GetKeyInstance(NULL,targinst),w_newkey);
  
  if ( !Modify(NO) )                                 ERROR
  if ( Save(NO,NO,NO) )                              ERROR
  
  if ( setwpt && nodeinst->CheckWProtect() != 1 )    
    SetWProtect();
RECOVER
  targinst = NULL;
  switch ( SDBERROR )
  {
    case 209 : 
               SDBRESET
    default  : ;
  }
ENDSEQ
  if ( converr && !SDBERROR )
    SDBISET(converr)
  return(targinst);

}

/******************************************************************************/
/**
\brief  CopyInstance - 



\return targinst - 
-------------------------------------------------------------------------------
\brief  NODEIC_ - 



\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  set_pos0_w - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstance"

char *bnode :: CopyInstance (inti *srceinti, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical setwpt )
{
  char     *keyptr    = NULL;
  char     *sortkey   = NULL;
  smcb     *targsmcb  = NULL;
  kcb      *kcbptr    = NULL;
  char     *targinst  = NULL;
  PIREPL    inst_repl = REPL_GUID;
  logical   exist     = NO;
  PIREPL    replopt   = db_replace;
BEGINSEQ
  if ( Check(YES) || !srceinti )                    ERROR
  if ( replopt == REPL_none && copy_type == REPL_relationships )
    replopt = REPL_local;

  if ( CheckAccess(PI_Write) )                      ERROR

  if ( Switch(AUTO) )                               ERROR
  if ( nodefield->get_weak_typed() )
    if ( SetType(srceinti->get_struct_def()->smcbname) )    
                                                    ERROR
  targsmcb = GetCurrentTypeDef();    
  Initialize_intern(NULL);
  targinst = nodeinst->get_iselarea();

  if ( srceinti->stscusr3() && nodeinst->stscusr3() &&
       ((isel *)srceinti)->get_ob_handle() == ((isel *)nodeinst)->get_ob_handle() )
    inst_repl = REPL_direct;    // die Abfrage auf Gleicheit der Objekte muss später intelligenter erfolgen ...
    
  targsmcb->CopyInstance(targinst,srceinti->get_struct_def(),srceinti->get_iselarea(),inst_repl,UNDEF);
  Bnodeinst->ResetIdentity();
  
  if ( sk_index && (kcbptr = sk_index->get_key_def()) )
  {
    if ( w_newkey )
      kcbptr->kcbkpt(GetKeyInstance(NULL,targinst),w_newkey);
    if ( sk_index->get_unique() )
      if ( sortkey = ExtractSortKey(NULL,targinst) )
      {
        if ( !(exist = !LocateKey(sortkey,YES)) )
          if ( nodefield->fmcbdim == 1 )
            exist = Get(sortkey,NO) ? YES : NO;
        targsmcb->CopyInstance(targinst,srceinti->get_struct_def(),srceinti->get_iselarea(),inst_repl,UNDEF);
        Bnodeinst->ResetIdentity();
        if ( w_newkey )
          kcbptr->kcbkpt(GetKeyInstance(NULL,targinst),w_newkey);
      }
    if ( exist )
    {
      if ( !replopt )                                ERROR 
      if ( GetID(AUTO) == srceinti->GetID() &&        
           !object_ref->DiffersFrom(srceinti->GetOBHandle()) )  
                                                     SDBERR(389)
    }
  }
                                                          
  // wenn keine Übernahme der GlobalID gefordert ist
  // Bnodeinst->ResetGUID();  
  
  if ( exist )
  {
    if ( !Get(sortkey,NO) )                          ERROR
  }  
  else
  {
    if ( nodefield->fmcbsmcb && nodefield->fmcbsmcb->smcbidky ) 
      exist = GetGlobalID().IsEmpty() ? NO : YES;    SDBCERR
    if ( !Add(set_pos0_w,NULL,NULL,targinst) )             ERROR
    if ( exist && !replopt )                         LEAVESEQ
  }

  if ( exist )
  { 
    if ( !replopt )                                  LEAVESEQ
//  this check permits copying instances in not owning collections for repl_local
//  not checking this may cause other problems 3.4.2006 (see also CopyInst)
//    if ( replopt == REPL_local && copy_type != REPL_relationships)
//      if ( nodenode && !nodefield->get_owning() )    LEAVESEQ
  }

  if ( !(targinst = CopyInstanceData(srceinti,db_replace,copy_type,w_newkey,setwpt)) )
                                                     ERROR
RECOVER
  targinst = NULL;
  switch ( SDBERROR )
  {
    case 209 : 
               SDBRESET
    default  : ;
  }
ENDSEQ
  return(targinst);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  srce_node - 
\param  db_replace - Replace option
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstance"

char *bnode :: CopyInstance (node *srce_node, PIREPL db_replace, logical setwpt )
{
  char         skey[1025];
  char        *key      = NULL;
  char        *targinst = NULL;
BEGINSEQ
  if ( Check(YES) || !srce_node )                    ERROR
  if ( CheckAccess(PI_Write) )                       ERROR
  if ( !IsSelected() || !srce_node->IsPositioned() ) ERROR
  
  if ( key = ExtractSortKey(skey,nodeinst->get_iselarea(),NO) ) 
    memcpy(skey,key,GetSortKeyLength());
  else if ( key = ExtractKey(skey,nodeinst->get_iselarea(),NO) )
    memcpy(skey,key,GetKeyLength());
    
  if ( !(targinst = CopyInstanceData(srce_node->get_nodeinst(),db_replace,REPL_all,key ? skey : NULL,setwpt)) )
                                                     ERROR
RECOVER
  targinst = NULL;

ENDSEQ
  return(targinst);
}

/******************************************************************************/
/**
\brief  CopyInstanceData - 



\return targinst - 

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstanceData"

char *bnode :: CopyInstanceData (inti *srceinti, PIREPL db_replace, PIREPL copy_type, char *w_newkey, logical setwpt )
{
  char     *keyptr    = NULL;
  char     *sortkey   = NULL;
  smcb     *targsmcb  = NULL;
  kcb      *kcbptr    = NULL;
  char     *targinst  = NULL;
  PIREPL    inst_repl = REPL_GUID;
  logical   exist     = NO;
  logical   mod       = NO;
  PIREPL    replopt   = db_replace;
  int16     converr   = NO;

BEGINSEQ
  if ( !IsWrite() )
  {
    if ( copy_type == REPL_relationships && nodeinst->CheckWProtect() == 1 )
      if ( !ResetWProtect() )
        setwpt = YES;
    if ( !IsWrite() )                                SDBERR(28)
  }
  
  converr = nodeinst->Copy(srceinti,this,db_replace,copy_type);
  if ( nodeinst->stscmod() )
    mod = YES;
  
  if ( sk_index && (kcbptr = sk_index->get_key_def()) )
    if ( kcbptr && w_newkey )
    {
      kcbptr->kcbkpt(GetKeyInstance(NULL,NULL),w_newkey);
      mod = YES;
    }
  
  Bnodeinst->ProvGenAttribute();
  if ( (mod && !Modify(NO)) || Save(NO,NO,NO) )
    targinst = NULL;
  if ( setwpt && nodeinst->CheckWProtect() != 1 )    
    SetWProtect();
    
  if ( !(targinst = nodeinst->get_iselarea()) )      ERROR
RECOVER
  targinst = NULL;
  switch ( SDBERROR )
  {
    case 209 : 
               SDBRESET
    default  : ;
  }
ENDSEQ
  if ( converr && !SDBERROR )
    SDBISET(converr)
  return(targinst);

}

/******************************************************************************/
/**
\brief  CopyReference - 



\return term - Termination code

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyReference"

logical bnode :: CopyReference (inti *srceinti, PIREPL db_replace, PIREPL copy_type )
{
  node                   *srce_node;
  node                   *targ_node = this;
  void                   *srceinst;
  fmcb                   *srce_fmcb;
  int32                    offset    = 0;
  logical                 term      = NO;
BEGINSEQ
  if ( nodefield->get_sec_reference() )              LEAVESEQ
  if ( GetCount() > 0 )                              LEAVESEQ
  
  if ( !(srce_fmcb = FindSource(srceinti,&offset,&srce_node)) )
                                                     LEAVESEQ
  if ( nodefield->fmcbityp == T_MEMO || nodefield->fmcbityp == T_BLOB )
  {
    if ( srce_node )
      srceinst = srce_node->Get(FIRST_INSTANCE);
    else
      srceinst = srceinti->get_iselarea()+offset+srce_fmcb->fmcbposn;

    if ( srceinst )
    {
      if ( !Provide(FIRST_INSTANCE) )                ERROR
      if ( cvb(srce_fmcb,nodefield,(char *)srceinst,nodeinst->get_iselarea()).cvbconv(db_replace,NO,copy_type) )
                                                     ERROR
      Modify();                                      SDBCERR 
    }
    else  
      if ( DeleteSet() )                             ERROR
  }
  else
  {
    if ( srce_node )
    {
      if ( CopySet(srce_node,YES,db_replace,copy_type) < 0) 
                                                     ERROR
    }
    else
    {
      srceinst = srceinti->get_iselarea()+offset+srce_fmcb->fmcbposn;
      if ( !srce_fmcb->fmcbbase() )                  SDBERR(99)
      Provide(srceinst);                             SDBCERR  // quelle ist basistyp (oder enum?)
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopySet - 



\return count - 

\param  srcenode - 
\param  check_inverse - 
\param  db_replace - Replace option
\param  copy_type - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySet"

int32 bnode :: CopySet (node *srcenode, logical check_inverse, PIREPL db_replace, PIREPL copy_type, logical chknode )
{
  logical   term = NO;
  int32  count = 0;     
  int32  indx0 = 0;
  int32  setcnt;


BEGINSEQ
  if ( Check(YES) )                                    ERROR
  
  if ( copy_type == REPL_relationships        &&
       !nodefield->get_weak_typed()           && 
       memcmp(nodefield->fmcbname,"VOID ",5)  &&
       (Bnodeinst->get_node_base().GetCount() +
        Bnodeinst->get_node_refr().GetCount() +
        Bnodeinst->get_node_rshp().GetCount()  == 0) ) LEAVESEQ
  
  if ( (setcnt = srcenode->GetCount()) == ERIC )       ERROR
  
  if ( chknode && (srcenode->Check(YES) || 
                   CheckAccess()) )                    ERROR

  if ( srcenode->Cancel(NO) )                          ERROR
  
  if ( check_inverse )
    if ( nodefield->get_owning()                || 
         !nodefield->get_inverse()              ||
         nodefield->get_inverse()->fmcbdim != 1 ||
         nodefield->fmcbityp != srcenode->dbf::GetFMCB()->fmcbityp ||
         srcenode->GetObjectHandle()->DiffersFrom(object_ref)    )
      check_inverse = NO;

  while ( indx0 < setcnt )
    if ( srcenode->Get(indx0++,NO) )                              
    {
      if ( !check_inverse || 
           !((ACRelationship *)this)->CheckInverse(srcenode) )
        if ( !CopyInst(srcenode,db_replace,copy_type,NULL,AUTO,NO) )
                                                       SDBCERR
      else
      {
        count++;
        if ( SDBERROR == 91 )
          term = YES;
      }
    }
    
  Switch(AUTO);
RECOVER
  count = -1;
ENDSEQ
  if ( term && !SDBERROR )
    SDBSET(91)
  return(count);

}

/******************************************************************************/
/**
\brief  CreateAccessPath - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  parm_bnf - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *bnode :: CreateAccessPath (BNFData *parm_bnf, OperEnvironment *operenv )
{
  node *   nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACPath(GetObjectHandle(),this,parm_bnf,operenv,PI_undefined);
                                                     SDBCERR
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
#define    MOD_ID  "CreateAccessPath"

node *bnode :: CreateAccessPath (char *prop_path, OperEnvironment *operenv )
{

BEGINSEQ
  SDBERR(99)
RECOVER

ENDSEQ
  return(NULL);
}

/******************************************************************************/
/**
\brief  CreateContext - 



\return term - Termination code

\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContext"

logical bnode :: CreateContext (CTX_Base *highctx )
{
  logical                 term = NO;
BEGINSEQ
  if ( nodefield && nodefield->get_resource())
  {
    if ( !(context = DLLHandle()->CreatePropCtx(object_ref->GetCTXIPath(),
                                              nodefield->get_resource()->get_res_id())) )
                                                     ERROR
    context->Initialize(this,highctx);
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateInti - 



\return intiptr - 

\param  nodeptr - 
\param  strdef_ptr - Internal data structure definition
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *bnode :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti      *intiptr = NULL;
BEGINSEQ
  if ( !(intiptr = new binti(nodeptr,NULL,strdef_ptr,instptr,init_nodes)) ) 
                                                      SDBERR(95)
                                                      SDBCERR

RECOVER
  delete intiptr;
  intiptr = NULL;
ENDSEQ
  return(intiptr);
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

node *bnode :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{
  node     *subnode = NULL;
BEGINSEQ
  SDBERR(99)

// bnode ist abstrakte Basisklasse; node::CreateSubNode ist zu verhindern
RECOVER

ENDSEQ
  return(subnode);
}

/******************************************************************************/
/**
\brief  DisableContext - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableContext"

void bnode :: DisableContext ( )
{

  if ( context )
    context->Disable();

  if ( Bnodeinst )
    Bnodeinst->DisableContext();

}

/******************************************************************************/
/**
\brief  DisableEventHandling - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableEventHandling"

void bnode :: DisableEventHandling ( )
{

  object_ref->DisableEventHandling();

}

/******************************************************************************/
/**
\brief  DisableKeyCheck - 



\return term - Termination code

\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableKeyCheck"

logical bnode :: DisableKeyCheck (char chkopt )
{
  logical                 term = NO;
BEGINSEQ
  if ( chkopt && Check(NO) )                         ERROR

  key_check = NO;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EnableContext - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableContext"

void bnode :: EnableContext ( )
{

  if ( context )
    context->Enable();

  if ( Bnodeinst )
    Bnodeinst->EnableContext();

}

/******************************************************************************/
/**
\brief  EnableEventHandling - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableEventHandling"

void bnode :: EnableEventHandling ( )
{

  object_ref->EnableEventHandling();

}

/******************************************************************************/
/**
\brief  EnableKeyCheck - 



\return term - Termination code

\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableKeyCheck"

logical bnode :: EnableKeyCheck (char chkopt )
{
  logical                 term = NO;
BEGINSEQ
  if ( chkopt && Check(NO) )                         ERROR

  key_check = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Event - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Event"

logical bnode :: Event (DB_Event intevent )
{

  GenerateEvent(intevent);
  
  if ( nodefield && nodefield->get_resource() )  
    nodefield->get_resource()->CheckEvent(context,YES);
  return(NO);
}

/******************************************************************************/
/**
\brief  ExecPropCtxFunc - 



\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecPropCtxFunc"

logical bnode :: ExecPropCtxFunc (char *fnames, char *w_parms )
{
  logical    term = NO;
BEGINSEQ
  if ( !context )                                      ERROR
    
  SOSRESET
  context->SetParm(w_parms);
  if ( context->ExecuteFunction(fnames,NO) )
  {
    SDBCTXCERR                                     
    if ( SDBERROR == 100 )
      SDBERR1(999,fnames)
    ERROR
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecStrCtxFunc - 



\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecStrCtxFunc"

logical bnode :: ExecStrCtxFunc (char *fnames, char *w_parms )
{
  logical   term = NO;
BEGINSEQ
  if ( !nodeinst || !Bnodeinst->get_context() )       ERROR
    
  SOSRESET
  Bnodeinst->get_context()->SetParm(w_parms);
  if ( Bnodeinst->ExecuteFunction(fnames) )
  {
    SDBCTXCERR                                     
    if ( SDBERROR == 100 )
      SDBERR1(999,fnames)
    ERROR
  }



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteEvent - 



\return term - Termination code

\param  int_event_id - 
\param  parmstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteEvent"

logical bnode :: ExecuteEvent (uint32 int_event_id, char *parmstring )
{
  EventLink              *evt_link;
  CSA_Events              event_id = (CSA_Events)int_event_id;
  EventParms             *ps   = (EventParms *)parmstring;
  logical                 term = NO;
BEGINSEQ
  if ( stscnof() )                                   LEAVESEQ   // if this node caused the event
    
  if ( ps->IsInstance() )
    Bnodeinst->GenerateCSEvent(event_id,ps->GetID(),this);
  else
  {
    if ( context )
      context->Notify(event_id,ps->GetID());
    
    if ( event_handler )
    {
      PropertyHandle  ph(this);
      event_handler->GoTop();
      while ( evt_link = event_handler->GetNext() )
        evt_link->Call(event_id,ps->GetID(),ph);
    }
    else
      CSA_Handle::ExecuteEvent(event_id,parmstring);
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExtractKey - 



\return keyptr - 
-------------------------------------------------------------------------------
\brief  NODEKE - 



\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *bnode :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{
 

BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR
  SDBEV1(nodefield->fmcbsmcb->smcbname,ID_SIZE)

  if ( !id_key )                                     SDBERR(71)
  keyptr = ExtractKey(keyptr,id_key,instptr);
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  keyptr - 
\param  kcbptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *bnode :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{

  if ( !instptr )
    if ( !(instptr = IsPositioned() 
                     ? nodeinst->get_iselarea()
                     : Get(AUTO,YES)) )              
      return(NULL);

  return( node::ExtractKey(keyptr,kcbptr,GetKeyInstance(NULL,instptr)) );

}

/******************************************************************************/
/**
\brief  ExtractSortKey - 



\return keyptr - 

\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractSortKey"

char *bnode :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{
  kcb      *kcbptr;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                   ERROR
  
  if ( !(sk_index && (kcbptr = sk_index->get_key_def())) )                             
                                                    ERROR
  keyptr = node::ExtractKey(keyptr,kcbptr,GetKeyInstance(NULL,instptr));
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

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

logical bnode :: GenerateEvent (DB_Event intevent )
{
  logical                 term = NO;
BEGINSEQ
  if ( intevent == DB_undefined )                    LEAVESEQ
  
  if ( nodefield && nodefield->get_resource() ) 
    if ( context && context->IsEnabled() ) 
      term = nodefield->get_resource()->GenerateEvent(intevent,context);
  
  if ( !term && proc_event_handler)
  {
    proc_event_handler->set_causer(this);
    term = proc_event_handler->GenerateEvent(intevent);
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetBaseNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseNode"

node **bnode :: GetBaseNode ( )
{
  bnode    *ext_node;
  node     *nodeptr;
BEGINSEQ
  if ( Check(AUTO,NO) )                               ERROR
    
  if ( !base_node )
  {
    if ( ext_node = (bnode *)GetExtentNode() )
    {
      if ( nodeptr = ext_node->CreateCopyNode() )
        nodeptr->ChangeMode(PI_Read);
    }
    else
    {
      if ( !IsEnumeration() )                        ERROR
      nodeptr = object_ref->GetDictionary()->CreateNode(nodefield->fmcbtype,PI_Read);
    }
    if ( !nodeptr )                                  ERROR
    SetBaseNode(Bnodeptr);
  }
  else
    if ( Exist() )
      ((bnode *)base_node)->ValidatePosition(YES);
  
  if ( sk_index && sk_index->get_key_def() )
    if ( ((bnode *)base_node)->get_nodefield()->GetIndexDef((char *)sk_index->GetKeyName()) )
      base_node->SetOrder((char *)sk_index->GetKeyName(),UNDEF,NULL);


RECOVER

ENDSEQ
  return ( (node **)&base_node );
}

/******************************************************************************/
/**
\brief  GetBuffer - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  lindx0 - 
\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBuffer"

void *bnode :: GetBuffer (int32 lindx0, int16 direction )
{
  void     *instptr = NULL;
BEGINSEQ
  instptr = inti_buffer->Get(lindx0,direction);
  if ( !instptr )                                  ERROR 
  instptr = nodeinst->get_iselarea();
  nodecur = nodeinst->get_inst_index();
  objid   = Bnodeinst->get_objid();


RECOVER
  nodeinst->Reset();
  nodecur = direction || inti_buffer->GetLastPos() < lindx0 ? AUTO : lindx0;
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  skey - 
\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBuffer"

void *bnode :: GetBuffer (char *skey, int16 direction )
{
  void     *instptr = NULL;
BEGINSEQ
  instptr = inti_buffer->Get(skey,direction);
  if ( !instptr )                                  ERROR 
  instptr = nodeinst->get_iselarea();
  nodecur = nodeinst->get_inst_index();
  objid   = Bnodeinst->get_objid();
 

RECOVER
  nodeinst->Reset();
  nodecur = AUTO;
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetBufferInstance - 



\return instptr - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBufferInstance"

void *bnode :: GetBufferInstance (int32 indx0 )
{
  void        *instptr = NULL;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( !inti_buffer )                                ERROR
  if ( Switch(AUTO) )                                ERROR

  if ( inti_buffer->Locate(indx0) )                  ERROR
  instptr = nodeinst->get_iselarea();
  nodecur = nodeinst->get_inst_index();

RECOVER
  nodecur = AUTO;
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetConnectionClient - 



\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient &bnode :: GetConnectionClient ( )
{

  return(GetClient());

}

/******************************************************************************/
/**
\brief  GetContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Property *bnode :: GetContext ( )
{

  return(context);

}

/******************************************************************************/
/**
\brief  GetCurrentIndex - 



\return lindx0 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentIndex"

int32 bnode :: GetCurrentIndex ( )
{

  return( node::GetCurrentIndex() );  // keine Ahnung, warum die in hier überladen wurde (rk)

}

/******************************************************************************/
/**
\brief  GetDictionary - 



\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

Dictionary *bnode :: GetDictionary ( )
{

  return(object_ref->GetDictionary());

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

int32 bnode :: GetDimension (logical chknode )
{
  int32     dim = AUTO;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                      ERROR
  
  dim = nodefield ? nodefield->fmcbdim : UNDEF;


RECOVER

ENDSEQ
  return(dim);
}

/******************************************************************************/
/**
\brief  GetErrorCode - 



\return errcd - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorCode"

int32 bnode :: GetErrorCode ( )
{

  return ( this ? object_ref->GetErrorCode() : 0 );

}

/******************************************************************************/
/**
\brief  GetExtentName - 



\return extname - Extent name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentName"

char *bnode :: GetExtentName ( )
{

  return(nodefield->GetExtendName());

}

/******************************************************************************/
/**
\brief  GetExtentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentNode"

node *bnode :: GetExtentNode ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetFieldDef - 



\return fdefptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldDef"

DBFieldDef *bnode :: GetFieldDef (logical chknode )
{
  DBFieldDef               *fdefptr = NULL;
BEGINSEQ
  if ( is_opened && chknode && Check(NO,NO) )               ERROR
  fdefptr = nodefield;

RECOVER

ENDSEQ
  return(fdefptr);
}

/******************************************************************************/
/**
\brief  GetIdentity - 



\return id_string - Identifier string

\param  id_string - Identifier string
\param  first - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentity"

char *bnode :: GetIdentity (char *id_string, logical first )
{
  char       string[RET_STR_LEN];
  int        len;
BEGINSEQ
  *string = 0; 
  if ( !first && is_collection )
  {
    if ( objid )
    {
      gvtxltoa(objid,string,10);
      strcat(string,"|");
    }
  }
  else
    if ( nodenode && nodenode->GetIdentity(string,NO) )
    {
      if ( (len = strlen(string)) > 500 )            ERROR
      if ( string[strlen(string)-1] != '|' )
        strcat(string,".");
      if ( sizeof(string)-len-1-strlen(prop_path) < 0 ) ERROR
      strcat(string,prop_path);
    }


RECOVER
  strcat(string,"...");
ENDSEQ
  return(id_string ? 
         strcpy(id_string,string) : set_result_string(string,0));
}

/******************************************************************************/
/**
\brief  GetInstContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstContext"

CTX_Structure *bnode :: GetInstContext ( )
{

  return ( !Check(YES,NO) && nodeinst ? 
           Bnodeinst->get_context() : NULL );

}

/******************************************************************************/
/**
\brief  GetKCB - 



\return kcbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKCB"

kcb *bnode :: GetKCB ( )
{
  kcb            *kcbptr = NULL;
  if ( sk_index )
    kcbptr = sk_index->get_key_def();
    
  if ( !kcbptr )
    kcbptr = id_key;

  return(kcbptr);
}

/******************************************************************************/
/**
\brief  GetKeyInstance - 



\return instptr - 

\param  intiptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyInstance"

char *bnode :: GetKeyInstance (inti *intiptr, void *instptr )
{

  if ( !intiptr )
    intiptr = nodeinst;
  if ( !instptr )
    instptr = intiptr->get_iselarea();
    
  return ( nodefield->get_weak_typed() 
           ? ((char *)instptr) + Bintiptr->get_weak_typed_offset()
           : (char *)instptr                );

}

/******************************************************************************/
/**
\brief  GetKeyLength - 



\return klen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 bnode :: GetKeyLength ( )
{
  int16 klen = 0; 

BEGINSEQ
  if ( Check(YES,NO) )                                 ERROR
  
  if ( id_key )
    klen = id_key->kcbklng();
    
  if ( IsGUID() )
    klen = 41;

RECOVER

ENDSEQ
  return(klen);

}

/******************************************************************************/
/**
\brief  GetMode - 



\return accopt - Access mode

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMode"

PIACC bnode :: GetMode (logical chknode )
{
 PIACC     accmode = PI_undefined;
BEGINSEQ
  if ( chknode && Check(NO,NO) )                      ERROR
    
  accmode = nodeacc;

RECOVER

ENDSEQ
  return(accmode);
}

/******************************************************************************/
/**
\brief  GetObjectHandle - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandle"

ACObject *bnode :: GetObjectHandle ( )
{

  return(object_ref);

}

/******************************************************************************/
/**
\brief  GetObjectHandlePtr - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandlePtr"

ACObject **bnode :: GetObjectHandlePtr ( )
{

  return(&object_ref);

}

/******************************************************************************/
/**
\brief  GetPIF - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPIF"

logical bnode :: GetPIF ( )
{

  return(object_ref->GetLocalACObject()->get_pif());

}

/******************************************************************************/
/**
\brief  GetPropPath - 



\return proppath - 

\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropPath"

char *bnode :: GetPropPath (char *proppath )
{
  CTX_Base               *highprop_ctx;
  node                   *highprop_node;

BEGINSEQ
  if ( nodenode && nodetype != NT_ACTempExtent && 
       nodetype != NT_ACOPView && nodetype != NT_ACOperation )
  {
    if ( !(highprop_ctx  = context->HighContext()->HighContext()) ||
         highprop_ctx->GetContextType() != CTXT_Property          ||  // Enum-nodes
         !(highprop_node = ((CTX_Property *)highprop_ctx)->get_prop_node()) )
                                                     ERROR
    if ( highprop_node != nodenode )  
    {
      if ( !Bnodenode->get_nodefield()->get_weak_typed() || 
           memcmp(nodenode->get_fldfmcb()->fmcbtype,
                  highprop_node->get_fldfmcb()->fmcbtype,ID_SIZE) )
      ((bnode *)highprop_node)->GetPropPath(proppath);
    }
  }
  
//if ( nodetype == NT_ACBaseStruct )                  LEAVESEQ
    
  if ( proppath )
  {
    if ( *proppath )
      strcat(proppath,".");
    gvtxbcs(proppath,nodefield->fmcbname,ID_SIZE,512);
  }
RECOVER
  proppath = NULL;
ENDSEQ
  return(proppath);
}

/******************************************************************************/
/**
\brief  GetRelative - 



\return instptr - 

\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelative"

void *bnode :: GetRelative (int32 indx0, logical chknode )
{
  int32                    count;
  int32                    start_indx0;
  int16                    direction;
  void                    *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( !HasFilter() )  // no filter 
  {
    if ( !stscold() )  // not a lower path node
    {
      instptr = Get(indx0,NO);                         
      absolute_index = nodecur;
      relative_index = nodecur;
      LEAVESEQ
    }
  }

  if ( indx0 == AUTO )
    indx0 = nodecur != AUTO ? nodecur : 0;
  
  if ( inti_buffer && !stscusr3() )
  {
    Switch(AUTO);
    if ( !GetBuffer(indx0,0) )                       ERROR
    LEAVESEQ
  }
  
  if ( absolute_index != AUTO )
    if ( absolute_index != nodecur )
      if ( !Get(absolute_index) )
        absolute_index = AUTO;
  
  start_indx0 = 0;

  if ( indx0 == LAST_INSTANCE )
  {
    direction = BACKWARD;
    count = 1;
  }
  else
  {
    if ( relative_index != AUTO && indx0 >= relative_index/2 )
    {
      count = indx0 - relative_index;
      start_indx0 = absolute_index;
    }
    else
    {
      count = indx0;
      Switch(AUTO);
    }
    direction = count >= 0 ? FOREWARD : BACKWARD;
  }
  
  GetAt(start_indx0,direction,NO);
  if ( start_indx0 == AUTO )
    count--;
  while ( nodecur != AUTO && count )
    if ( GetAt(nodecur+direction,direction,NO) != AUTO )
    {  
      count -= direction;
//    absolute_index = nodecur;
//    relative_index += direction;
    }
    
  if ( nodecur == AUTO )                       ERROR
  absolute_index = nodecur;
  relative_index = indx0;
  instptr        = nodeinst->get_iselarea();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetRelativeCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeCount"

int32 bnode :: GetRelativeCount ( )
{
  int32                   current = nodecur;
  int32                   count = 0;
BEGINSEQ
  if ( HasFilter() )
  {
    while ( GetRelative(count++) ) ;                   SDBCERR
    count--;
    if ( current >= 0 )
      Get(current);  
  }
  else
  {
    count = GetCount();
  }

RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetRelativeIndex - 



\return lindx0 - 

\param  last_opt - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeIndex"

int32 bnode :: GetRelativeIndex (logical last_opt, logical chknode )
{
  int32                   lindx0 = AUTO;
  if ( !HasFilter() && !stscold() )
    lindx0 = nodecur;
  else if ( last_opt || nodecur == absolute_index )
    lindx0 = relative_index;
  return(lindx0);
}

/******************************************************************************/
/**
\brief  GetSortKeyLength - 



\return klen - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeyLength"

int16 bnode :: GetSortKeyLength (logical chknode )
{
  kcb      *kcbptr;
  int16 klen = 0; 

BEGINSEQ
  if ( chknode && Check(YES,NO) )                       ERROR
  
  if ( sk_index && (kcbptr = sk_index->get_key_def()) )                             
    klen = kcbptr->kcbklng();

  if ( IsGUID() )
    klen = 41;

RECOVER

ENDSEQ
  return(klen);

}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 



\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *bnode :: GetSortKeySMCB ( )
{
  smcb     *smcbptr = NULL;

BEGINSEQ
  if ( Check(AUTO,NO) )                                  ERROR
  
  smcbptr = get_sortkey_smcb();

RECOVER

ENDSEQ
  return(smcbptr);

}

/******************************************************************************/
/**
\brief  GetStructContext - 



\return struct_context - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructContext"

CTX_Structure *bnode :: GetStructContext ( )
{
  CTX_Structure    *struct_context = NULL;
BEGINSEQ
  if ( !this )                                       ERROR

  if ( !nodeinst )                                   ERROR

  struct_context = Bnodeinst->get_context();
RECOVER

ENDSEQ
  return(struct_context);
}

/******************************************************************************/
/**
\brief  Get_attribute - 



\return instptr - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_attribute"

void *bnode :: Get_attribute (int32 lindx0, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( chknode )
    if ( nodenode && !nodenode->IsSelected() )      LEAVESEQ
  
  if ( auto_position >= 0 )
    lindx0 = auto_position;
    
  if ( lindx0 == LAST_INSTANCE )
    lindx0 = GetCount()-1;
  
  if ( lindx0 >= GetCount() )                        ERROR

  if ( lindx0 == AUTO )
    if ( (lindx0 = nodecur) == AUTO ) 
      lindx0 = 0;
  
  flddata = nodeinst->get_iselarea();
  nodecur = 0;
  instptr = dbf::Get(lindx0);
  nodecur = lindx0;
  if ( stsctrans() )
    relative_index = nodecur;
  
  if ( instptr && type_inti )
  {
    if ( (*type_inti)[nodecur] )
      SetCurrentInti((*type_inti)[nodecur]);
    else
    {
      SetCurrentInti(NULL);
      if ( InitInti(NULL,instptr,NO) )               ERROR
      Bnodeinst->SetEventHandler(((binti *)(*type_inti)[0])->get_event_handler());
      Bnodeinst->SetProcEventHandler(((binti *)(*type_inti)[0])->get_proc_event_handler());
      Bnodeinst->GenerateProcessEvent(DBO_Opened);
    }
  }


RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Get_optimized - 



\return instptr - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_optimized"

void *bnode :: Get_optimized (char *skey )
{
  int32  indx0 = 0;
  void     *instptr = NULL; 
  char      keyarea[MAX_KEYLEN];
  char      wskey[MAX_KEYLEN];
BEGINSEQ
  if ( stscusr2() )         // VOID-Extend
  {
SDBSET(777)  // 17.11.04 das sollte nicht mit zahl auftreten (nur mit string!)
SDBRESET
    if ( skey[1] == '-' )                            ERROR // GUID
    memcpy(&indx0,skey,sizeof(int32));
    return ( Get(indx0) );
  }

  SaveKey(wskey,skey);

  instptr = nodeinst->get_iselarea();

  if ( nodefield->fmcbdim == 1 )
  {
    if ( !Get(FIRST_INSTANCE,NO) )                   ERROR
    instptr = nodeinst->get_iselarea();   // area may change for weak typed nodes
    if ( GetSortKeyLength(NO)
         ? CompareSortKey(ExtractSortKey(keyarea,instptr,NO),wskey,NO)
         : CompareKey(ExtractKey(keyarea,instptr),wskey) )
                                                     ERROR
    LEAVESEQ
  }

  if ( nodecur >= 0 && nodeinst->IsPositioned() )
  {                                                   
    if ( sk_index && sk_index->get_key_def() )
    {
      if ( !CompareSortKey(ExtractSortKey(keyarea,instptr,NO),wskey,NO) ) 
                                                     LEAVESEQ
    }
    else if ( id_key )
      if ( !CompareKey(ExtractKey(keyarea,instptr,NO),wskey,NO) ) 
                                                     LEAVESEQ
  }
  if ( cache_list && (instptr = cache_list->Locate(wskey)) )
  {
    nodecur = nodeinst->get_inst_index();
    ReserveInstance();
    LEAVESEQ
  }
  ERROR
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  HasGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasGenAttribute"

logical bnode :: HasGenAttribute ( )
{
  logical   cond = YES;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( nodeinst )
    cond = Bnodeinst->HasGenAttribute();
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  HasIndex - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasIndex"

logical bnode :: HasIndex ( )
{

  return ( sk_index ? YES : NO );

}

/******************************************************************************/
/**
\brief  Init - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical bnode :: Init (void *instptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( InitReference() )                             ERROR

  if ( InitInti(nodefield->GetDBStruct(),instptr) )  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitInti - 



\return term - Termination code

\param  strdefptr - 
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInti"

logical bnode :: InitInti (DBStructDef *strdefptr, void *instptr, logical init_nodes )
{
  logical      newinst = !nodeinst;
  logical      term    = NO;
BEGINSEQ
  if ( node::InitInti(strdefptr,instptr,init_nodes) ) ERROR
  
  if ( newinst )    
    Bnodeinst->OpenEvent();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitTempExtent - 



\return term - Termination code

\param  dbstrdef - Structure definition
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitTempExtent"

logical bnode :: InitTempExtent (DBStructDef *dbstrdef, char *key_name_w )
{
  kcb        *kcbptr = NULL;
  char        string[ID_SIZE+1];
  logical     term   = NO;
BEGINSEQ
  if ( !key_name_w )
    kcbptr = dbstrdef->smcbidky;
  else
  {
    SDBEV2(key_name_w,ID_SIZE)
    if ( !(kcbptr = dbstrdef->GetKCB(key_name_w)) )  SDBERR(79)
  }
      
  if ( !(sk_index = new DBIndex(kcbptr,YES,YES,YES,NO,UNDEF,SET_SMAL,NO)) )
                                                     SDBERR(95)

  if ( !(nodefield = new DBFieldDef(dbstrdef->smcbname,dbstrdef->smcbname,dbstrdef->smcbnsid,
                                    RL_reference,dbstrdef->GetInstLength(NO),0,UNDEF,dbstrdef,
                                    NULL,NO,NULL,NULL,sk_index)) )   
                                                     SDBERR(95)
                                                     SDBCERR
  
  set_prop_path(gvtxbts(string,dbstrdef->smcbname,ID_SIZE));
  nodefield->set_clst_table(YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InstanceInserted - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceInserted"

logical bnode :: InstanceInserted ( )
{

  return( instance_inserted );

}

/******************************************************************************/
/**
\brief  IsActive - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActive"

logical bnode :: IsActive ( )
{
  logical  cond = YES;
BEGINSEQ
  if ( !GetFieldDef() )                              ERROR
  
  cond = nodefield->IsActive();

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsClientNode - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsClientNode"

logical bnode :: IsClientNode ( )
{

  return ( object_ref ? object_ref->IsClientObject()
                      : node::IsClientNode()          );

}

/******************************************************************************/
/**
\brief  IsCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollection"

logical bnode :: IsCollection ( )
{

  return(is_collection);

}

/******************************************************************************/
/**
\brief  IsContextEnabled - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsContextEnabled"

logical bnode :: IsContextEnabled ( )
{

  return ( context ? context->IsEnabled() : NO );


}

/******************************************************************************/
/**
\brief  IsDirectField - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDirectField"

logical bnode :: IsDirectField ( )
{

  return( !is_collection            && 
          !is_memo                  && 
          nodefield->get_privilege() != PI_Share );

}

/******************************************************************************/
/**
\brief  IsDirty - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDirty"

logical bnode :: IsDirty ( )
{

  return(this ? is_dirty : NULL);

}

/******************************************************************************/
/**
\brief  IsEnumeration - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

logical bnode :: IsEnumeration ( )
{

  return(is_codeset);

}

/******************************************************************************/
/**
\brief  IsInstReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInstReadOnly"

logical bnode :: IsInstReadOnly ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( nodeacc == PI_Read || nodeinst->CheckWProtect() ) 
                                                     LEAVESEQ
//  if ( context && context->DisplayState() == DSP_Disabled ) 
//                                                     LEAVESEQ
  if ( Bnodeinst->get_context() && Bnodeinst->get_context()->IsReadOnly() )
                                                     LEAVESEQ
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsMemo - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMemo"

logical bnode :: IsMemo ( )
{

  return(is_memo);

}

/******************************************************************************/
/**
\brief  IsMoveableInstance - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMoveableInstance"

logical bnode :: IsMoveableInstance ( )
{

  return(moveable_instance);

}

/******************************************************************************/
/**
\brief  IsNewInstance - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical bnode :: IsNewInstance ( )
{

  return ( new_instance );

}

/******************************************************************************/
/**
\brief  IsPIF - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPIF"

logical bnode :: IsPIF ( )
{

  return( this && object_ref ? object_ref->GetLocalACObject()->get_pif() : NO);

}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical bnode :: IsPositioned ( )
{

  return( nodewrit > PI_Write || 
          ( stscfil() && nodecur >= 0 && nodeinst && 
            nodeinst->IsPositioned() ) );
           
//            && (!nodenode || nodenode->IsPositioned()) )         );

}

/******************************************************************************/
/**
\brief  IsReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical bnode :: IsReadOnly ( )
{
  inti                  *intiptr;
  logical                cond = YES;
BEGINSEQ
  if ( nodeacc == PI_Read )                          LEAVESEQ
//  if ( context && context->DisplayState() == DSP_Disabled ) 
//                                                     LEAVESEQ
  if ( nodenode && (intiptr = nodenode->get_nodeinst()) )
    if ( intiptr->IsReadOnly() )                     LEAVESEQ
      
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsReserved - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReserved"

int8 bnode :: IsReserved ( )
{
  logical                 cond = NO;
BEGINSEQ
// 0 not reserved
// 1 reserved by other resource
// 2 reserved by this resource


  if ( !nodeinst || !nodeinst->stscusr3() )  // no isel
                                                     ERROR
  cond = ((isel *)nodeinst)->IsReserved();
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsSelected - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical bnode :: IsSelected ( )
{

  return( nodewrit > PI_Write || 
          ( stscfil() && nodeinst && nodeinst->IsSelected() ) );
//            (!nodenode || nodenode->IsSelected()) )         );

}

/******************************************************************************/
/**
\brief  IsServerNode - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsServerNode"

logical bnode :: IsServerNode ( )
{

  return ( object_ref ? object_ref->IsServerObject()
                      : node::IsServerNode()          );

}

/******************************************************************************/
/**
\brief  IsTypeVariable - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTypeVariable"

logical bnode :: IsTypeVariable ( )
{

  return(variable_type);

}

/******************************************************************************/
/**
\brief  IsValidForParent - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValidForParent"

logical bnode :: IsValidForParent ( )
{

  return ( !moveable_instance || !iChanged() );


}

/******************************************************************************/
/**
\brief  IsWrite - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical bnode :: IsWrite ( )
{

  return( nodeacc != PI_Read && 
          ( nodewrit                                 || 
//            (nodeacc == PI_Update && IsPositioned()) || 29.11.2004 damit context zu NoWrite fuehrt, kann aber intern zu viel sein
            IsInitInstance()                           ) );
//         && !nodeinst->IsReadOnly()                               );

}

/******************************************************************************/
/**
\brief  MarkReadOnly - 



\return term - Termination code

\param  readonly - Read-only state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MarkReadOnly"

logical bnode :: MarkReadOnly (logical readonly )
{
  node              *nodeptr;
  logical            term = NO;
  context->MarkReadOnly(readonly);
  
  if ( copies )
  {
    copies->GoTop();
    while ( nodeptr = copies->GetNext() ) 
      Bnodeptr->MarkReadOnly(readonly);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Modify - 



\return instptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *bnode :: Modify (logical chknode )
{
  char               *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR
// wenn wir die Einstellung prüfen (Check(YES,YES)), können wir keine Attributwerte  für neue instanzen setzen!! s.a. CNode
  
  if ( nodeinst )
    instptr = nodeinst->get_iselarea();
    
  if ( CheckModify() )                               ERROR
  if ( GenerateEvent(DBP_Modify) )                   ERROR
  
  if ( IsWrite() && !nodeinst->stscini() )
    if ( nodeinst->IsPositioned() )
      if ( nodeinst->Modify() )                      ERROR
  
  if ( is_memo && highnod && 
       highnod->get_nodeinst()->get_struct_def()->GetGUIDPosition() >= 0 )
    highnod->Modify();
    
  SetMod();

RECOVER
  int        saveerr = SDBERROR;
  Reset();
  SDBISET(saveerr);
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  ModifyAttribute - 



\return instptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ModifyAttribute"

void *bnode :: ModifyAttribute (logical chknode )
{
  node               *high_node;
  char               *instptr = NULL;
BEGINSEQ
  if ( nodeinst ) 
    instptr = nodeinst->get_iselarea();
  
  if ( IsTransient() )                               LEAVESEQ
    
  if ( GenerateEvent(DBP_Modify) )                   ERROR
  
  if ( nodenode && !nodenode->Modify() )             ERROR


RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
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

logical bnode :: Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
{
  char       proppath[1025];
  logical    term = NO;
BEGINSEQ
  node::Open(nodeptr,dbfield_ptr);
  
  nodeacc    = accopt;
  nodefield  = dbfield_ptr;
  object_ref = obhandle;
  high_inti  = nodenode ? nodenode->get_nodeinst() : NULL;

  if ( !highctx && high_inti )     // new 4.8.2002
    highctx = high_inti->GetContext();
  
  if ( !highctx && obhandle )
    highctx = obhandle->get_ocontext();
    
  if ( !context )
    if ( CreateContext(highctx) )                    ERROR
    
  SDBRESET

  *proppath = 0;
  if ( nodefield && GetPropPath(proppath) )
    set_prop_path(proppath);
    
  if ( nodefield  )
  {
    if ( nodefield->get_weak_typed() )
      type_inti = new DPA(inti)();
    
    if ( !nodefield->IsTyped() )        // neu 12.1.2004
      moveable_instance = YES;          // bisher nur wenn auch nodenode
    
    if ( nodefield->fmcbityp == T_MEMO || nodefield->fmcbityp == T_BLOB )
      is_memo = YES;
    else
      if ( nodefield->fmcbrlev == R_REFR || nodefield->fmcbrlev == R_GENERIC )
        is_collection = YES;
      
    if ( IsTransient() )  // transient references may change its type
      variable_type = YES;

    if ( nodenode )
    {
      if ( Bnodenode->get_moveable_instance()                     || 
           (nodenode->get_nodenode() && Bnodenode->IsTransient()) ||
           !nodefield->IsTyped()                 )
      {
        moveable_instance = YES;
        if ( Bnodenode->get_variable_type() || !Bnodenode->get_nodefield()->IsTyped() )
          if ( !IsBasetypeProperty() )
            variable_type = YES;
      }
    }
  }

  if ( nodetype != NT_ClientNode )
    GenerateEvent(DBO_Opened);
  context->SetProcessState(PRC_Opened);
  object_ref->ResetError();  
// id_key = nodefield->GetDBStruct()->smcbidky;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PositionTop - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop"

logical bnode :: PositionTop ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( nodewrit == 255 )                              ERROR
    
  term = node::PositionTop();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PositionTop_intern - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop_intern"

node *bnode :: PositionTop_intern ( )
{
  node              *nodeptr = this;
BEGINSEQ
  if ( !nodenode || nodenode->IsSelected() )      LEAVESEQ
  
  if ( !(nodeptr = ValidatePosition(YES)) )         ERROR
  

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  PrepareGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrepareGenAttribute"

logical bnode :: PrepareGenAttribute ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !IsPositioned() )                             LEAVESEQ

  if ( Bnodeinst->PrepareGenAttribute() )            ERROR
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

logical bnode :: ProvGenAttribute ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !nodewrit || nodeacc == PI_Read || 
       !IsPositioned() || context->IsReadOnly() )    LEAVESEQ

  Bnodeinst->ProvGenAttribute();
ENDSEQ
  return(term);
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

void *bnode :: Provide (char *skey, logical global_add )
{

BEGINSEQ
  return(NULL);
RECOVER

ENDSEQ

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

void *bnode :: Provide (int32 lindx0, logical global_add )
{
 

  return(NULL);
 

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

void *bnode :: Provide (void *datarea, logical global_add )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  ProvideExtentNode - 



\return nodeptr - 

\param  extent_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtentNode"

node *bnode :: ProvideExtentNode (char *extent_path )
{
  PropertyHandle  *extent_hdl = NULL;
  node            *nodeptr    = NULL;
  node            *cancelnod  = NULL;
  node            *topnode;
  node            *srcnode;
  node           **nodepptr;
  PIACC            accmode;
BEGINSEQ
  if ( (!extent_path && !(extent_path = GetExtentName())) )
                                                     LEAVESEQ
  switch ( *extent_path )
  {
    case 0   :
    case ' ' : LEAVESEQ
    
    case '.' : srcnode = this;
               while ( *(++extent_path) == '.' && srcnode )
                 srcnode = srcnode->get_highnod();
  
               if ( !(nodepptr = srcnode->GetNodePtr(extent_path)) ||  
                    !(*nodepptr)->IsValid()                           )  
               {
                 SDBCERR
                 SDBERR(99)
               }  
               nodeptr = *nodepptr;   
               if ( Exist() )
                 nodeptr = Bnodeptr->ValidatePosition(NO);
//             if ( !(nodeptr = nodeptr->CreateCopyNode()) )
               topnode = nodeptr;
               while ( topnode->get_highnod() != srcnode )
                 topnode = topnode->get_highnod();
               
               if ( Bnodeptr->get_moveable_instance() )
                 if ( !(nodeptr = Bnodeptr->ValidateExtentNode(topnode,&cancelnod)) )
                                                     ERROR
               
               if ( (accmode = Bnodeptr->get_nodeacc()) > PI_Update )
                 accmode = PI_Update;
               if ( !(nodeptr = nodeptr->PathCreateCopy(topnode,accmode,AUTO)) )
                                                     ERROR
               if ( cancelnod )
                 cancelnod->Cancel();
               break;
               
    case '*' : if ( !(extent_path = GetCurrentType()) )
                                                     ERROR
    default  : DBObjectHandle      temp_objhdl(object_ref);
               if ( !(extent_hdl = new PropertyHandle(temp_objhdl,extent_path,PI_Read)) )
                                                     SDBERR(95)
                                                     SDBCERR
               nodeptr = extent_hdl->get_nodeptr();
    
  }

  

RECOVER
  delete extent_hdl;
  extent_hdl = NULL;
  nodeptr    = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  ProvideInti - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInti"

logical bnode :: ProvideInti (EB_Number entnr )
{
  int16         inst_sid;
  logical       term = NO;
BEGINSEQ
  if ( !nodefield->get_weak_typed() && GetCurrentTypeDef()->smcbityp != T_VOID )
                                                     LEAVESEQ
  switch ( inst_sid = nodeinst->GetSID(entnr) )
  {
    case UNDEF : SDBERR(99)
    case AUTO  : ERROR
    default    : if ( ProvideInti(inst_sid) )        ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInti"

logical bnode :: ProvideInti (int16 sid )
{
  DBStructDef          *strdef    = NULL;
  DBStructDef          *structdef = NULL;
  EventLinkList        *evt_hdls  = NULL;
  ProcessEventHandler  *pevt_hdls = NULL;
  int16                 count     = 0;
  inti                 *old_inti  = nodeinst;
  logical               term = NO;
BEGINSEQ
  if ( nodeinst && sid == nodeinst->get_struct_def()->smcbityp )
                                                     LEAVESEQ
  if ( !(strdef = object_ref->GetDictionary()->ProvideStructDef(sid,object_ref->GetSchemaVersion())) ||
       !type_inti )                                 SDBERR(99)

  SetCurrentInti(NULL);
  for ( count = type_inti->GetSize()-1; !nodeinst && count >= 0; count--) 
  {
    evt_hdls  = ((binti *)(*type_inti)[count])->get_event_handler();
    pevt_hdls = ((binti *)(*type_inti)[count])->get_proc_event_handler();
    structdef = (*type_inti)[count]->get_struct_def();
    if ( sid == structdef->smcbityp )
      SetCurrentInti((*type_inti)[count]);
  }
  if ( !nodeinst )
  {
    if ( InitInti(strdef,NULL) )                     ERROR
    Bnodeinst->SetEventHandler(evt_hdls);
    Bnodeinst->SetProcEventHandler(pevt_hdls);
    Bnodeinst->GenerateProcessEvent(DBO_Opened);   // neu 2.8.04
  }
  if ( old_inti && old_inti->stscini() )
  {
    old_inti->ResetInitialized(); // 29.11.2003, vorher: old_inti->stsrini();
    nodeinst->get_struct_def()->CopyInstance(nodeinst->get_iselarea(),old_inti->get_struct_def(),old_inti->get_iselarea(),REPL_direct,UNDEF);
    ((binti *)nodeinst)->SetInitialize(); // 29.11.2003, vorher: nodeinst->stssini();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadBuffer - 



\return count - 

\param  lindx0 - 
\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBuffer"

int32 bnode :: ReadBuffer (int32 lindx0, int16 direction )
{
  int16          bufnum;
  int16          count = 0;
  logical        eof = NO;
  logical        term = NO;
BEGINSEQ
  if ( !inti_buffer )                                LEAVESEQ
  if ( lindx0 == LAST_INSTANCE )
    lindx0 = GetCount()-1;
    
  if ( lindx0 == CUR_INSTANCE )
    lindx0 = nodecur;
        
  Switch(AUTO);
  
  stssusr3();   // mark node as 'in buffer read'
  count = inti_buffer->Read(lindx0,direction);
  stsrusr3();

ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  RecoverSelection - 



\return term - Termination code

\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecoverSelection"

logical bnode :: RecoverSelection (int64 obj_id )
{
  EB_Number               entnr(obj_id);
  int32                   indx0;
  logical                 term = NO;
BEGINSEQ
  if ( !obj_id )                                     LEAVESEQ
  if ( !IsPositioned() && nodecur >= 0 )
    Get(nodecur);

  entnr.ToPIF(object_ref->GetLocalACObject()->get_pif());
  if ( objid == entnr.get_ebsnum() )                 LEAVESEQ

  if ( Locate(obj_id,YES) )                          ERROR
  if ( objid != obj_id )                             ERROR
RECOVER
  Cancel();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RegisterPathNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterPathNode"

void bnode :: RegisterPathNode ( )
{

  if ( nodenode && nodenode->IsCollection() )
    ((bnode *)nodenode->GetNode())->AddPathNode(this);
  else if ( object_ref )
    object_ref->AddPathNode(this);


}

/******************************************************************************/
/**
\brief  ReleaseBaseNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseBaseNode"

void bnode :: ReleaseBaseNode ( )
{
  bnode    *basnod = base_node ? ((bnode *)base_node) : NULL;

  if ( basnod )
  {
    basnod->set_base_reference(NULL);
    set_base_node(NULL);
    delete basnod;
    base_node = NULL;
  }
  


}

/******************************************************************************/
/**
\brief  ReleaseBuffer - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseBuffer"

logical bnode :: ReleaseBuffer ( )
{
  logical        term = NO;
BEGINSEQ
  if ( !inti_buffer )                                LEAVESEQ
  Switch(AUTO);
  
  delete inti_buffer;
  inti_buffer = NULL;
ENDSEQ
  return(term);
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

logical bnode :: ReleaseProcessEvents (logical emit_opt )
{
  binti                  *bintiptr;
  logical                 term = NO;
  if ( proc_event_handler )
  {
    proc_event_handler->set_causer(this);
    term = proc_event_handler->EmitEvents(emit_opt);
  }
  
  if ( (bintiptr = Bnodeinst) && bintiptr->get_proc_event_handler() )
  {
    bintiptr->get_proc_event_handler()->set_causer(this);
    if ( bintiptr->ReleaseProcessEvents(emit_opt) )
      term = YES;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  RemoveField - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveField"

void bnode :: RemoveField ( )
{

  delete nodefield;
  nodefield = NULL;     


}

/******************************************************************************/
/**
\brief  RemovePathNode - 



\return term - Termination code

\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemovePathNode"

logical bnode :: RemovePathNode (bnode *bnodeptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || !path_nodes )                    LEAVESEQ

  path_nodes->Remove(bnodeptr);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveInstance - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveInstance"

char *bnode :: ReserveInstance ( )
{


  return(this && nodeinst ? nodeinst->get_iselarea() : NULL);
}

/******************************************************************************/
/**
\brief  ResetGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetGenAttribute"

logical bnode :: ResetGenAttribute ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !IsPositioned() )                             LEAVESEQ

  if ( Bnodeinst->ResetGenAttribute() )              ERROR
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

void bnode :: ResetInstance ( )
{
  logical   positioned = nodeinst ? nodeinst->IsSelected() : NO; 
  node     *nodeptr;
BEGINSEQ
// das alles müssen wir auch machen, wenn instanz nicht 'positioned' ist,
// da sonst stsfil in subnodes nicht zurückgesetzt wird!!

  if ( !stscfil() || stscerr() )                     LEAVESEQ

  node::ResetInstance();
  
  if ( path_nodes )
  {
    path_nodes->GoTop();
    while ( nodeptr = path_nodes->GetNext() )
      nodeptr->ResetNode(YES);
  }
  nodewrit          = NO;
  objid             = 0;
  new_instance      = NO;
  instance_inserted = NO;
  
  if ( context )
    context->SetDataState(DAT_undefined);

  if ( positioned )
    Bnodeinst->GenerateEvent(DBO_Reset);

ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetInstanceEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceEventHandler"

void bnode :: ResetInstanceEventHandler (EventLink *event_link )
{
  inti          *intiptr = NULL;
  int32          count   = 0;
  if ( !Check(NO,NO) && nodeinst )
  {
    if ( !type_inti )
      Bnodeinst->ResetEventHandler(event_link);  
    else
    {
      count = type_inti->GetSize();
      while ( count-- )
        if ( intiptr = (*type_inti)[count] )
          Bintiptr->ResetEventHandler(event_link);
    }
  }
    


}

/******************************************************************************/
/**
\brief  ResetInstanceProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceProcessHandler"

void bnode :: ResetInstanceProcessHandler (EventLink *event_link )
{
  inti          *intiptr = NULL;
  int32          count   = 0;
  if ( !Check(NO,NO) && nodeinst )
  {
    if ( !type_inti )
      Bnodeinst->ResetInstanceProcessHandler(event_link);  
    else
    {
      count = type_inti->GetSize();
      while ( count-- )
        if ( intiptr = (*type_inti)[count] )
          Bintiptr->ResetInstanceProcessHandler(event_link);
    }
  }


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

logical bnode :: ResetNode (logical reset_all )
{
  logical       old = stscold();
  logical       reset = NO;
BEGINSEQ
  if ( reset = node::ResetNode(reset_all) )
  {
    if ( stscerr() || !stscfil() )                       LEAVESEQ //28.11.2004: node ist schon reseted
  
    absolute_index = AUTO;
    relative_index = AUTO;
  
    if ( old )
      stssold();
    
    GenerateEvent(DBO_Reset);
  }


ENDSEQ
  return(reset);

}

/******************************************************************************/
/**
\brief  ResetPropertyEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyEventHandler"

void bnode :: ResetPropertyEventHandler (EventLink *event_link )
{

  if ( !Check(NO,NO) )
    if ( event_handler && event_handler->Find(event_link) )
      event_handler->RemoveAt();

}

/******************************************************************************/
/**
\brief  ResetPropertyProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyProcessHandler"

void bnode :: ResetPropertyProcessHandler (EventLink *event_link )
{

  if ( !Check(NO,NO) )
    if ( proc_event_handler )
      proc_event_handler->Remove(event_link);

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

logical bnode :: SaveNode (logical switchopt, logical overwrite )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( Save(switchopt,overwrite,NO) )                ERROR
  
//if ( switchopt && copies ) 30.11.2004: hier wird bei Save(NO,...) zu spät gesichert
  if ( copies )
  {
    DLL(node)  cursor(*copies);
    cursor.GoTop();
    while ( nodeptr = cursor.GetNext() )
      nodeptr->SaveNode(switchopt,overwrite);
  }

  if ( switchopt )
    ResetNode(YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetArea - 



\return datarea - 

\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetArea"

void *bnode :: SetArea (void *datarea )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  SetBaseNode - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBaseNode"

logical bnode :: SetBaseNode (bnode *bnodeptr )
{

  set_base_node(bnodeptr);
  bnodeptr->set_base_reference(this);
  return(NO);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBaseNode"

logical bnode :: SetBaseNode (PropertyHandle &prophdl_ref )
{
  node    *ext_node = prophdl_ref.GetNode();
  node    *nodeptr;
BEGINSEQ
  ReleaseBaseNode();

  if ( !ext_node )                                   LEAVESEQ
  nodeptr = ext_node->CreateCopyNode();
  SetBaseNode(Bnodeptr);

ENDSEQ
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

void bnode :: SetCurrentInti (inti *intiptr )
{

  node::SetCurrentInti(intiptr);

  if ( context )
    context->SetDataState(DAT_undefined);

}

/******************************************************************************/
/**
\brief  SetDescription - 




\param  field_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

void bnode :: SetDescription (DBFieldDef *field_def )
{



}

/******************************************************************************/
/**
\brief  SetDirty - 




\param  dirty_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDirty"

void bnode :: SetDirty (logical dirty_opt )
{

  if ( this )
    is_dirty = dirty_opt;

}

/******************************************************************************/
/**
\brief  SetDynLength - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDynLength"

logical bnode :: SetDynLength ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  SetInstance - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

void *bnode :: SetInstance ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  SetInstanceEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceEventHandler"

void bnode :: SetInstanceEventHandler (EventLink *event_link )
{
  EventLinkList      *hdl_dll;
  int                 count;
  inti               *intiptr;
  if ( !Check(YES,NO) && nodeinst )
    Bnodeinst->SetInstanceEventHandler(event_link);
  
  if ( type_inti )
  {
    hdl_dll = Bnodeinst->get_event_handler();
    count = type_inti->GetSize();
    while ( count-- )
      if ( intiptr = (*type_inti)[count] )
        Bintiptr->SetEventHandler(hdl_dll);
  }

}

/******************************************************************************/
/**
\brief  SetInstanceProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceProcessHandler"

void bnode :: SetInstanceProcessHandler (EventLink *event_link )
{
  ProcessEventHandler *hdl_dll;
  int                  count;
  inti                *intiptr;
  if ( !Check(YES,NO) && nodeinst )
    Bnodeinst->SetInstanceProcessHandler(this,event_link);

  if ( type_inti )
  {
    hdl_dll = Bnodeinst->get_proc_event_handler();
    count = type_inti->GetSize();
    while ( count-- )
      if ( intiptr = (*type_inti)[count] )
        Bintiptr->SetProcEventHandler(hdl_dll);
  }


}

/******************************************************************************/
/**
\brief  SetInti - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInti"

logical bnode :: SetInti (inti *intiptr )
{

BEGINSEQ
  if ( !type_inti )                                  LEAVESEQ
    
  if ( IsAttribute() || Get_data_nodetype() == NT_ACAttribute )
    (*type_inti)[nodecur] = intiptr;
  else  
    type_inti->Add(intiptr);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetMode - 



\return term - Termination code

\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMode"

logical bnode :: SetMode (PIACC accopt )
{

  nodeacc = accopt;
  return(NO);

}

/******************************************************************************/
/**
\brief  SetPropertyEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyEventHandler"

void bnode :: SetPropertyEventHandler (EventLink *event_link )
{

  if ( !Check(NO,NO) )
  {
    if ( !event_handler )
      event_handler = new EventLinkList();
    event_handler->AddEventLink(event_link);
  }

}

/******************************************************************************/
/**
\brief  SetPropertyProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyProcessHandler"

void bnode :: SetPropertyProcessHandler (EventLink *event_link )
{

  if ( !Check(NO,NO) )
  {
    if ( !proc_event_handler )
      proc_event_handler = new ProcessEventHandler(this);
    proc_event_handler->AddEventLink(event_link);
    
    if ( nodenode )
      Bnodenode->set_has_event_handler(YES);
    if ( !nodenode || nodenode->IsPositioned() )
      GenerateEvent(DBO_Refresh);  // CollectionChanged
    if ( IsPositioned() )
      GenerateEvent(DBO_Read);       // nd 3.8.04  DBP_ wird nicht in ReadTA gespeichert -> nicht generiert
  }

}

/******************************************************************************/
/**
\brief  SetSortKey - 



\return term - Termination code

\param  keyptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSortKey"

logical bnode :: SetSortKey (char *keyptr, void *instptr )
{
  kcb       *kcbptr;
  void      *instance;
  logical    term = NO;
BEGINSEQ
  if ( Check(YES,NO) )                                  ERROR			
  if ( !(sk_index && (kcbptr = sk_index->get_key_def())) )                             
                                                     ERROR
  if ( SetKey(kcbptr,keyptr,GetKeyInstance(NULL,instptr)) )               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetType - 



\return term - Termination code

\param  strnames - Type name
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical bnode :: SetType (char *strnames, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR
  if ( !IsVariableType(NO) )                         SDBERR(158)
  
  if ( SetType_intern(strnames) )                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetType_intern - 



\return term - Termination code

\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType_intern"

logical bnode :: SetType_intern (char *strnames )
{
  DBStructDef  *dbstrdef;
  logical       term = NO;
BEGINSEQ
  if ( nodefield->fmcbsmcb->smcbstyp == ST_CODE )    LEAVESEQ
    
  if ( !(dbstrdef = object_ref->GetDictionary()->ProvideStructDef(strnames)) )
                                                     SDBERR(20)
  if ( dbstrdef->smcbityp == 16 )                    LEAVESEQ   // SDB_CSEntry
  if ( nodefield->fmcbityp != T_VOID )  
    if ( memcmp(dbstrdef->smcbname,nodefield->fmcbsmcb->smcbname,ID_SIZE) &&
         !dbstrdef->IsBasedOn(nodefield->fmcbsmcb->smcbname) )
                                                     SDBERR(157)
  if ( nodewrit != 255 )
    Switch(AUTO);
  if ( ProvideInti(dbstrdef->smcbityp) )             ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupViewOrder - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupViewOrder"

logical bnode :: SetupViewOrder ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( GetStructDef()->SetupViewOrder(Bnodeinst) )   ERROR

  id_key = GetStructDef()->smcbidky;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StartReadTA - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartReadTA"

ACObject *bnode :: StartReadTA ( )
{

  if ( this && object_ref )
    object_ref->StartReadTA();
  return ( this ? object_ref : NULL );
}

/******************************************************************************/
/**
\brief  StopReadTA - 




\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopReadTA"

void bnode :: StopReadTA (logical error_case )
{

  if ( this && object_ref )
    object_ref->StopReadTA(error_case);

}

/******************************************************************************/
/**
\brief  Store - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical bnode :: Store ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsTransient() )                               LEAVESEQ
  GenerateEvent(DBO_Stored);
  nodefield->get_resource()->CheckEvent(context,NO);
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

logical bnode :: Switch (int32 indx0 )
{
  int16     saveerr;
  logical   term = NO;

BEGINSEQ
  if ( !nodeinst )                                   LEAVESEQ
  
//  if ( indx0 != nodecur && (nodecur != AUTO || nodeinst->stscini()) )
  if ( (indx0 != nodecur && nodecur != AUTO) || nodeinst->stscini() )
  {
    if ( cache_list )   // wir arbeiten mit cache
    {
      if ( !cache_list->Save(nodeinst) )             
      {
        ResetInstance();
        nodecur = AUTO;
        LEAVESEQ
      }
    }
    if ( Save(YES,NO,NO) )
    {
      saveerr = SDBERROR ? SDBERROR : 2;
      Cancel();
      SDBSET(saveerr);
    }   
  }
  else if ( nodecur == AUTO )
    if ( nodeinst->IsPositioned() || nodeinst->stscini() )
      ResetInstance();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnregisterPathNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterPathNode"

void bnode :: UnregisterPathNode ( )
{

  if ( nodenode )
  {
    if ( nodenode->IsValid() && nodenode->IsCollection() )
      ((bnode *)nodenode->GetNode())->RemovePathNode(this);
  }
  else if ( object_ref )
    object_ref->RemovePathNode(this);


}

/******************************************************************************/
/**
\brief  UserEventHandler - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UserEventHandler"

logical bnode :: UserEventHandler ( )
{

  return(has_event_handler && object_ref->EventHandling() );

}

/******************************************************************************/
/**
\brief  ValidateExtentNode - 



\return nodeptr - 

\param  top_node - 
\param  pcancel_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateExtentNode"

node *bnode :: ValidateExtentNode (node *top_node, node **pcancel_node )
{
  node                 *parent;
  node                 *nodeptr = this;
  node                **pnodeptr;
  int32                 indx0;
BEGINSEQ
  if ( !this || !highnod || IsSelected() )           LEAVESEQ
  
  if ( this != top_node ) 
    if ( !highnod->IsSelected() )
    {
      if ( !(parent = ((bnode *)highnod)->ValidateExtentNode(top_node,pcancel_node)) )
                                                     ERROR
      if ( !(pnodeptr = parent->GetNodePtr(prop_path)) ||
           !(nodeptr = *pnodeptr)           )        ERROR
                                 
    }
    
  if ( nodeptr->IsSelected() || 
       (nodeptr->get_highnod() && !nodeptr->get_highnod()->IsSelected()) )        
                                                     LEAVESEQ
  if ( (indx0 = nodeptr->get_nodecur()) < 0 )
    indx0 = FIRST_INSTANCE;
  Bnodeptr->DisableContext();
  nodeptr->Get(indx0);
  Bnodeptr->EnableContext();

  if ( !*pcancel_node )
    *pcancel_node = nodeptr;
RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  ValidateNode - 



\return new_node - 

\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateNode"

node *bnode :: ValidateNode (logical crt_opt )
{
  node         *new_node = this;
  node         *parent   = NULL;
BEGINSEQ
  if ( stscfil() )                                   LEAVESEQ
  if ( highnod )
  {  
    if ( !IsPositioned() )                            
    {  
      if ( !highnod->get_nodeinst() )                ERROR
      if ( parent = highnod->ValidateNode(NO) ) 
        if ( !parent->IsPositioned() && !parent->IsInitInstance() &&             
              parent->IsAutoPosition()                               )
          parent->Get(FIRST_INSTANCE);
          
      if ( !parent || (!parent->IsPositioned() && !parent->IsInitInstance()) )
      {
        if ( !base_reference )
        {
          if ( !parent || parent == highnod )        ERROR
          if ( new_node = iRefresh(crt_opt,parent) ) LEAVESEQ
          ERROR
        }

        if ( !base_reference->get_nodenode()->Exist() )
                                                     ERROR
        if ( !(new_node = ValidatePosition(crt_opt)) ) 
                                                     ERROR
        if ( !new_node->get_nodenode()->IsPositioned() )
                                                     ERROR
      }
      if ( nodefield && nodefield->get_transient() && nodefield->GetResourceID() > 0 )
      {
        if ( !highnod->Exist() )
        {
          nodenode->PositionTop();
          nodenode->Get(FIRST_INSTANCE);
        }      
        GenerateEvent(DBO_Refresh);
      }
    }
    else if ( !moveable_instance )                   LEAVESEQ
//    if ( !((bnode *)highnod)->get_moveable_instance() ) LEAVESEQ
      
    if ( !(new_node = iRefresh(crt_opt,parent)) )    ERROR
  }
RECOVER
  new_node = NULL;
ENDSEQ
  return(new_node);
}

/******************************************************************************/
/**
\brief  ValidatePosition - 



\return new_node - 

\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidatePosition"

node *bnode :: ValidatePosition (logical crt_opt )
{
  node         *new_highnod;
  node         *new_node    = this;
  int32         indx0;
BEGINSEQ
  if ( highnod )
  {  
    if ( !(new_highnod = ((bnode *)highnod)->ValidatePosition(NO)) )
                                                     ERROR
    if ( !new_highnod->IsSelected() )
    {
      if ( !new_highnod->get_nodenode() || new_highnod->get_nodenode()->IsSelected() )
      {
        if ( (indx0 = new_highnod->get_nodecur()) < 0 )
          indx0 = FIRST_INSTANCE;
        new_highnod->Get(indx0);
      }
      else
        new_highnod->Check(YES,NO);  // no acc-check  18.3.2003
    } 
    if ( !(new_node = iRefresh(crt_opt,new_highnod)) )
                                                     ERROR
  }


RECOVER
  new_node = NULL;
ENDSEQ
  return(new_node);
}

/******************************************************************************/
/**
\brief  bnode - 



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
#define    MOD_ID  "bnode"

     bnode :: bnode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
                     : CSHandle (),
node(), 
  nodewrit(NO),
  is_dirty(NO),
  nodeacc(accopt),
  nodefield(dbfield_ptr),
  context(NULL),
  object_ref(obhandle),
  type_inti(NULL),
  inti_buffer(NULL),
  base_node(NULL),
  id_key(NULL),
  sk_index(NULL),
  base_reference(NULL),
  is_collection(NO),
  is_opened(NO),
  is_memo(NO),
  is_codeset(NO),
  variable_type(NO),
  moveable_instance(NO),
  is_updated(NO),
  is_valid(NO),
  has_event_handler(NO),
  key_check(NO),
  reserve_lo(NO),
  registered(NO),
  objid(AUTO),
  new_instance(AUTO),
  instance_inserted(NO),
  high_inti(NULL),
  spec_info(NULL),
  event_handler(NULL),
  proc_event_handler(NULL),
  cache_list(NULL),
  absolute_index(AUTO),
  relative_index(AUTO),
  path_nodes(NULL)
{
 

  InitHandle(NO);
  Open(obhandle,nodeptr,dbfield_ptr,highctx,accopt);


}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bnode"

     bnode :: bnode ( )
                     : CSHandle (),
node(), 
  nodewrit(NO),
  is_dirty(NO),
  nodeacc(PI_Read),
  nodefield(NULL),
  context(NULL),
  object_ref(NULL),
  type_inti(NULL),
  inti_buffer(NULL),
  base_node(NULL),
  id_key(NULL),
  sk_index(NULL),
  is_collection(NO),
  base_reference(NULL),
  is_opened(NO),
  is_memo(NO),
  is_codeset(NO),
  variable_type(NO),
  moveable_instance(NO),
  is_updated(NO),
  is_valid(NO),
  has_event_handler(NO),
  key_check(NO),
  reserve_lo(NO),
  registered(NO),
  objid(AUTO),
  new_instance(AUTO),
  instance_inserted(NO),
  high_inti(NULL),
  spec_info(NULL),
  event_handler(NULL),
  proc_event_handler(NULL),
  cache_list(NULL),
  absolute_index(AUTO),
  relative_index(AUTO),
  path_nodes(NULL)
{

  InitHandle(NO);


}

/******************************************************************************/
/**
\brief  i2 - 



\param  bnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bnode"

     bnode :: bnode (bnode &bnode_ref )
                     : CSHandle (),
node (bnode_ref),
  nodewrit(NO),
  nodeacc(bnode_ref.get_nodeacc()),
  nodefield(bnode_ref.get_nodefield()),
  context(NULL),
  object_ref(bnode_ref.get_object_ref()),
  type_inti(NULL),
  inti_buffer(NULL),
  base_node(NULL),
  id_key(bnode_ref.get_id_key()),
  sk_index(bnode_ref.get_sk_index()),
  is_collection(bnode_ref.get_is_collection()),
  base_reference(NULL),
  is_opened(bnode_ref.get_is_opened()),
  is_memo(bnode_ref.get_is_memo()),
  is_codeset(bnode_ref.get_is_codeset()),
  variable_type(bnode_ref.get_variable_type()),
  moveable_instance(bnode_ref.get_moveable_instance()),
  is_updated(NO),
  is_valid(bnode_ref.get_is_valid()),
  has_event_handler(NO),
  registered(NO),
  objid(AUTO),
  new_instance(AUTO),
  high_inti(bnode_ref.get_high_inti()),
  spec_info(NULL),
  event_handler(NULL),
  proc_event_handler(NULL),
  cache_list(NULL),
  key_check(NO),
  reserve_lo(NO),
  absolute_index(AUTO),
  relative_index(AUTO),
  path_nodes(NULL)
{
  instance_inserted = NO;  // passt nicht in ini-code
BEGINSEQ
  is_dirty = bnode_ref.IsDirty();
  
  if ( CreateContext(bnode_ref.context->HighContext()) ) 
                                                     ERROR
  if ( bnode_ref.context->IsReadOnly() )
    MarkReadOnly(YES);
  
  id_key = bnode_ref.get_id_key();

  if ( nodefield->get_weak_typed() )
    type_inti = new DPA(inti)();
  
  InitHandle(NO);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i3 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  prop_names - Property name
\param  typenames - Type name
\param  nsid - 
\param  ref_level - Level, data is referenced
\param  size - Field size
\param  precision - 
\param  dimension - Dimension of property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bnode"

     bnode :: bnode (ACObject *obhandle, node *nodeptr, char *prop_names, char *typenames, int32 nsid, SDB_RLEV ref_level, uint32 size, int32 precision, uint32 dimension )
                     : CSHandle (),
node (obhandle->GetDictionary(),prop_names,typenames,
      nsid,ref_level,size,precision,dimension,NULL),
  nodewrit(NO),
  is_dirty(NO),
  nodeacc(PI_Read),
  nodefield(NULL),
  context(NULL),
  object_ref(obhandle),
  type_inti(NULL),
  inti_buffer(NULL),
  base_node(NULL),
  id_key(NULL),
  sk_index(NULL),
  is_collection(NO),
  is_opened(YES),
  is_memo(NO),
  is_codeset(NO),
  variable_type(NO),
  moveable_instance(NO),
  is_updated(NO),
  is_valid(NO),
  has_event_handler(NO),
  key_check(NO),
  reserve_lo(NO),
  registered(NO),
  objid(AUTO),
  new_instance(AUTO),
  instance_inserted(NO),
  high_inti(NULL),
  base_reference(NULL),
  spec_info(NULL),
  event_handler(NULL),
  proc_event_handler(NULL),
  cache_list(NULL),
  absolute_index(AUTO),
  relative_index(AUTO),
  path_nodes(NULL)
{

  InitHandle(NO);

  if ( obhandle )
    CreateContext(obhandle->get_ocontext());

}

/******************************************************************************/
/**
\brief  get_bnodenode - 



\return bnode_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_bnodenode"

bnode *bnode :: get_bnodenode ( )
{

  return ( nodenode ? ((bnode *)nodenode) : NULL );

}

/******************************************************************************/
/**
\brief  get_idkey_smcb - 



\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_idkey_smcb"

smcb *bnode :: get_idkey_smcb ( )
{

  return ( id_key ? id_key->scbsmcb : NULL );

}

/******************************************************************************/
/**
\brief  get_sortkey_smcb - 



\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_sortkey_smcb"

smcb *bnode :: get_sortkey_smcb ( )
{
  kcb      *kcbptr;
  smcb     *smcbptr = NULL;
  if ( sk_index && (kcbptr = sk_index->get_key_def()) )                             
    smcbptr = kcbptr->scbsmcb;

  return(smcbptr);
}

/******************************************************************************/
/**
\brief  iChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "iChanged"

logical bnode :: iChanged ( )
{

  return ( !high_inti || !nodenode || nodenode->get_nodeinst() == high_inti 
           ? NO : YES );

}

/******************************************************************************/
/**
\brief  iCheck - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "iCheck"

logical bnode :: iCheck ( )
{
  logical                 term = NO;
BEGINSEQ
//  if ( IsDirectField() && nodecur != 0 )  // direkt-feld
//    Get(FIRST_INSTANCE);
// nd 28.7.04 Get(FIRST_INSTANCE) und nodecur > 0 nimmt fuer Bereiche einstellung weg
//            Get(AUTO) und nodecur != 0 verschickt zuoft property Read-Events
  
  if ( IsDirectField() && nodecur < 0 )  // direkt-feld
    Get(FIRST_INSTANCE);     
  else if ( !is_opened )
    if ( Check(AUTO,NO) )                             ERROR  // war bisher YES, 29.4.2006
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  iRefresh - 



\return new_node - 

\param  crt_opt - 
\param  parent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "iRefresh"

bnode *bnode :: iRefresh (logical crt_opt, node *parent )
{
  char                   *datarea;
  node                   *nodeptr;
  bnode                  *new_node = this;
  node                  **pnew_node;
  logical                 changed = NO;
  logical                 term = NO;
BEGINSEQ
  if ( parent && parent != highnod )
    changed = YES;
    
  if ( nodenode != highnod )
  {
    if ( nodenode != (nodeptr = Bnodenode->iRefresh(NO,parent)) )
    {
      if ( !nodeptr )                                ERROR
      if ( origin )                                  SDBERR(524)  // ich bin ein CopyNode!!
      if ( !prop_path )                              SDBERR(99)
      if ( !(pnew_node = nodeptr->GetNodePtr(prop_path) ) )
                                                     ERROR
      if ( !(new_node = (bnode *)*pnew_node) )       ERROR
    }
  }
  else if ( moveable_instance && (changed || iChanged()) )
  {
    if ( !crt_opt && origin )                        SDBERR(524)  // ich bin ein CopyNode!!
    if ( !(new_node = iReopen(parent)) )             ERROR
  }          
    
  if ( new_node->iCheck() )                          ERROR
RECOVER
  if ( SDBERROR == 109 )
    SDBSET(99)
  new_node = NULL;
ENDSEQ
  return(new_node);
}

/******************************************************************************/
/**
\brief  iReopen - 



\return new_node - 

\param  parent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "iReopen"

bnode *bnode :: iReopen (node *parent )
{
  node    **pnew_node = NULL;
  bnode    *new_node  = this;
  node     *nodeptr;
  logical   term = NO;
BEGINSEQ
  if ( !parent )
    parent = nodenode;
    
  if ( !prop_path || !parent )                       SDBERR(99)

  if ( nodetype == NT_ACShareBase &&
       !memcmp(nodeinst->get_struct_def()->smcbname,
               nodenode->get_nodeinst()->get_struct_def()->smcbname,ID_SIZE) )
    pnew_node = &nodenode;
  else
    if ( !(pnew_node = parent->GetNodePtr(prop_path,NULL,YES) ) )
                                                     ERROR
  if ( !origin )
  {
    if ( *pnew_node == this )                        LEAVESEQ
    new_node = (bnode *)*pnew_node;
  }
  else
  {
    if ( (*pnew_node)->get_copies() )
    {
      (*pnew_node)->get_copies()->GoTop();
      while ( nodeptr = (*pnew_node)->get_copies()->GetNext() )
        if ( this == nodeptr )                       LEAVESEQ
    }
    new_node = (bnode *)(*pnew_node)->CreateCopyNode();
  }
  new_node->set_auto_position(auto_position); 
  new_node->set_auto_key(auto_key); 
  new_node->set_auto_provide(auto_provide); 
    
  if ( base_reference )
    ((bnode *)base_reference)->SetBaseNode(new_node);
  base_reference = NULL;


RECOVER
  if ( SDBERROR == 109 )
    SDBSET(99)
  new_node = NULL;
ENDSEQ
  return(new_node);

}

/******************************************************************************/
/**
\brief  set_absolute_index - 




\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_absolute_index"

void bnode :: set_absolute_index (int32 lindx0 )
{

  absolute_index = lindx0;

}

/******************************************************************************/
/**
\brief  set_base_node - 




\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_base_node"

void bnode :: set_base_node (node *nodeptr )
{

  if ( base_node )
    base_node->ResetPIRef((PropertyHandle *)&base_node);    
  
  base_node = nodeptr;

  if ( base_node )
    base_node->SetPIRef((PropertyHandle *)&base_node);


}

/******************************************************************************/
/**
\brief  set_base_reference - 




\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_base_reference"

void bnode :: set_base_reference (node *nodeptr )
{

  base_reference = nodeptr;

}

/******************************************************************************/
/**
\brief  set_has_event_handler - 




\param  has_evthdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_has_event_handler"

void bnode :: set_has_event_handler (logical has_evthdl )
{

  has_event_handler = has_evthdl;

}

/******************************************************************************/
/**
\brief  set_nodeacc - 




\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_nodeacc"

void bnode :: set_nodeacc (PIACC accopt )
{

  nodeacc = accopt;

}

/******************************************************************************/
/**
\brief  set_nodewrit - 




\param  writeopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_nodewrit"

void bnode :: set_nodewrit (logical writeopt )
{

  nodewrit = writeopt;

}

/******************************************************************************/
/**
\brief  set_objid - 




\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_objid"

void bnode :: set_objid (int64 obj_id )
{

  objid = obj_id;

}

/******************************************************************************/
/**
\brief  set_relative_index - 




\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_relative_index"

void bnode :: set_relative_index (int32 lindx0 )
{

  relative_index = lindx0;

}

/******************************************************************************/
/**
\brief  ~bnode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~bnode"

     bnode :: ~bnode ( )
{

  bnode::Close();   // ist eigentlich nur zur Sicherheit
  
  delete context;
  context = NULL;

  if ( proc_event_handler )
    proc_event_handler->Release();
  proc_event_handler = NULL;

  if ( event_handler )
    event_handler->Release();
  event_handler = NULL;
  
  delete path_nodes;
  path_nodes = NULL;

}


