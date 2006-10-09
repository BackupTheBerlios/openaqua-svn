/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBResource

\brief    


\date     $Date: 2006/06/01 17:38:10,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBResource"

#include  <popa7.h>
#ifndef   DPA_DBEvent_HPP
#define   DPA_DBEvent_HPP
#include  <sDBEvent.hpp>
#include  <sDPA.h>
#endif
#ifndef   DLL_DBReaction_HPP
#define   DLL_DBReaction_HPP
#include  <sDBReaction.hpp>
#include  <sDLL.h>
#endif
#ifndef   DPA_UCA_CAction_HPP
#define   DPA_UCA_CAction_HPP
#include  <sUCA_CAction.hpp>
#include  <sDPA.h>
#endif
#include  <cDB_Event.h>
#include  <sACObject.hpp>
#include  <sCAU_Action.hpp>
#include  <sCAU_Causality.hpp>
#include  <sCAU_Reaction.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sDBEvent.hpp>
#include  <sDBEventList.hpp>
#include  <sDBReaction.hpp>
#include  <sDictionary.hpp>
#include  <sUCA_CAction.hpp>
#include  <sUCA_CActionList.hpp>
#include  <sDBResource.hpp>

int32 dbres_count = 0;

/******************************************************************************/
/**
\brief  CheckEvent - 


\return term - Termination code

\param  ctxptr - 
\param  clear_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEvent"

logical DBResource :: CheckEvent (CTX_DBBase *ctxptr, logical clear_event )
{

  return ( ctxptr && events ? events->Check(ctxptr,clear_event) : NO);


}

/******************************************************************************/
/**
\brief  ContextRequired - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ContextRequired"

logical DBResource :: ContextRequired ( )
{

//  return ( this && (events || action_list) ? YES : NO);  
  return ( this && res_id ? YES : NO);

}

/******************************************************************************/
/**
\brief  DBResource - 



\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBResource"

     DBResource :: DBResource (Dictionary *dictptr )
                     : res_id(0),
  events(NULL),
  action_list(NULL),
  int_reactions(NULL),
  dictionary(dictptr)
{


dbres_count++;
}

/******************************************************************************/
/**
\brief  GenerateEvent - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  intevent - Event identifier
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical DBResource :: GenerateEvent (DB_Event intevent, CTX_DBBase *ctxptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !ctxptr )                                     LEAVESEQ
    
//*** wenn reactions implementiert werden müssen datastates an dieser Stelle mitbehandelt werden 
//*** werden jetzt in CTX_DBBase::ExecuteAction gesetzt
    
  if ( int_reactions && (*int_reactions)[intevent] )
    term = GenerateEvent((*int_reactions)[intevent],ctxptr);
  else
    if ( term = ctxptr->ExecuteAction(intevent) )
      SDBCTXCERR
    else
      SDBRESET

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  evtnames - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical DBResource :: GenerateEvent (char *evtnames, CTX_DBBase *ctxptr )
{

  return ( GenerateEvent(events->Search(evtnames),ctxptr) );


}

/******************************************************************************/
/**
\brief  i2 - 


\param  dbevent - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical DBResource :: GenerateEvent (DBEvent *dbevent, CTX_DBBase *ctxptr )
{
  DBReaction             *reaction;
  logical                 term = NO;
BEGINSEQ
  if ( !dbevent )                                    ERROR
    
  dbevent->get_reactions()->GoTop();
  while ( reaction = dbevent->get_reactions()->GetNext() )
  {
    if ( reaction->get_react_id() != AUTO )
      reaction->Connect(get_dictionary());
    if ( reaction->Execute(ctxptr) )
      term = YES;
  }
  if ( term )
    SDBCTXCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  causality - 
\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBResource :: Initialize (CAU_Causality *causality, int32 resid )
{
  int32                    indx0 = 0;
  CAU_Action             *action;
  UCA_CAction            *caction;
  CTX_DBBase              context;
  DBEvent                *cevent;
  CAU_Event              *cau_event;
  logical                 term = NO;
BEGINSEQ
  res_id = resid;
  if ( !causality )                                  LEAVESEQ
  
  if ( causality->get_actions().GetCount() > 0 )
  {
    if ( !(action_list = new UCA_CActionList()) )    SDBERR(95)
      
    while (  action = causality->get_actions().Get(indx0++) )
      if ( caction = context.CreateCAction(
              (SimpleAction *)action->get_pre_handler()(0L),
              (SimpleAction *)action,
              (SimpleAction *)action->get_post_handler()(0L)) )
        action_list->AddTail(caction);
  }
    
  if ( causality->get_event().GetCount() > 0 )
  {
    if ( !(int_reactions = new DPA(DBEvent)(16)) )   SDBERR(95)
    if ( !(events = new DBEventList) )               SDBERR(95)
    indx0 = 0;
    while ( cau_event = causality->get_event().Get(indx0++) )
    {
      if ( !(cevent = new DBEvent(cau_event,&context)) )  
                                                     SDBERR(95)
      events->Append(cevent);
      if ( cevent->get_int_event() )
      {
        (*int_reactions)[cevent->get_int_event()] = cevent;
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
\brief  i01 - 


\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBResource :: Initialize (PropertyHandle &ph )
{
  int32                    indx0 = 0;
  CAU_Action             *action;
  UCA_CAction            *caction;
  CTX_DBBase              context;
  DBEvent                *cevent;
  CAU_Event              *cau_event;
  logical                 term = NO;
BEGINSEQ
  if ( !(res_id = ph.GetInt("res_id")) )
  {
    PH(&ph,resource_ref)
    if ( resource_ref.Get(FIRST_INSTANCE) )
      res_id = resource_ref.GetInt("__AUTOIDENT");
  }
  
  PH(&ph,actions)
  if ( actions.GetCount() > 0 )
  {
    if ( !(action_list = new UCA_CActionList()) )    SDBERR(95)
      
    while (  actions.Get(indx0++) )
      if ( caction = context.CreateCAction(
              (SimpleAction *)actions.GPH("pre_handler")->Get(0L).GetData(),
              (SimpleAction *)actions.GetArea(),
              (SimpleAction *)actions.GPH("pre_handler")->Get(0L).GetData()) )
        action_list->AddTail(caction);
  }
    
  PH(&ph,event)
  if ( event.GetCount() > 0 )
  {
    if ( !(int_reactions = new DPA(DBEvent)(16)) )   SDBERR(95)
    if ( !(events = new DBEventList) )               SDBERR(95)
    indx0 = 0;
    while ( event.Get(indx0++) )
    {
      if ( !(cevent = new DBEvent(event,&context)) )  
                                                     SDBERR(95)
      events->Append(cevent);
      if ( cevent->get_int_event() )
      {
        (*int_reactions)[cevent->get_int_event()] = cevent;
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
\brief  ~DBResource - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBResource"

     DBResource :: ~DBResource ( )
{
  DBReaction    *rctptr;

  delete int_reactions;
  
  delete events;
  events = NULL;
    
  delete action_list;
  action_list = NULL;

dbres_count--;
}


