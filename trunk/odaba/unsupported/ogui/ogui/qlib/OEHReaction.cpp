/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEHReaction

\brief    O-Control Reaction
          An  O-control  reaction  defines  a stack for possible reactions. Only
          the  reaction  on  top  of  the  stack  is  executed when activating a
          reaction.

\date     $Date: 2006/05/04 12:32:28,51 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHReaction"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHEvent.hpp>
#include  <sOEHReaction.hpp>


/******************************************************************************/
/**
\brief  AddAction - Add current action
        The  function inserts the current action on top of the action list. Thus
        the action becomes the current action executed for the event.


\param  ogui_causer
\param  action
\param  new_event_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAction"

void OEHReaction :: AddAction (ODataWidget *ogui_causer, OEHAction *action, logical new_event_opt )
{
  OEHAction   *prev_action = NULL;
BEGINSEQ
  if ( !new_event_opt && (prev_action = GetAction()) )
  {
    if ( prev_action == action )                     LEAVESEQ
    prev_action->RemoveCauser(ogui_causer->GetDetailedCauser(event));
  }

//  action_list.prepend(action->get_qaction());
  action_list.AddHead(action);
  action->AddCauser(ogui_causer->GetDetailedCauser(event));
ENDSEQ

}

/******************************************************************************/
/**
\brief  FindAction

\return action

\param  act_names - Action name
\param  loid - Identification for an action object
\param  on_top_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindAction"

OEHAction *OEHReaction :: FindAction (char *act_names, char *loid, logical on_top_w )
{
  OEHAction    *action = NULL;
BEGINSEQ
  action_list.GoTop();
  while ( action = action_list.GetNext() )
  {
    if ( action->Is(act_names,loid) )              LEAVESEQ
    if ( on_top_w )                                ERROR
  }
  ERROR

//  return ( action_list.FindAction(act_names,loid,on_top_w) );

RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  GetAction - Get current action
        The function returns the current action (action on top of the list).

\return action

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAction"

OEHAction *OEHReaction :: GetAction ( )
{

  return ( action_list.GetHead() );
/*
  if ( action_list.isEmpty() )
    return NULL;
  return ( action_list.FirstAction() );
*/

}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical OEHReaction :: IsEmpty ( )
{

  return ( this && action_list.GetCount() ? NO : YES );
//  return ( this && action_list.size() ? NO : YES );

}

/******************************************************************************/
/**
\brief  OEHReaction - Constructor



\param  pOEHEvent - Event pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHReaction"

     OEHReaction :: OEHReaction (OEHEvent *pOEHEvent )
                     :   event(pOEHEvent),
  action_list()
{

}

/******************************************************************************/
/**
\brief  RemoveAction

\return term - 
-------------------------------------------------------------------------------
\brief  i0


\param  action
\param  ogui_causer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAction"

logical OEHReaction :: RemoveAction (OEHAction *action, ODataWidget *ogui_causer )
{
  logical            term = NO;
BEGINSEQ
  if ( !action )                                     LEAVESEQ
    
  if ( action == GetAction() )
    action->RemoveCauser(ogui_causer->GetDetailedCauser(event));
  
  if ( term = RemoveAction(action) )                 ERROR
  
  if ( action = GetAction() )
    action->AddCauser(ogui_causer->GetDetailedCauser(event));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAction"

logical OEHReaction :: RemoveAction (OEHAction *action )
{
  logical    term = NO;
BEGINSEQ
  if ( !action_list.Find(action) )                   ERROR
  action_list.RemoveAt();
    
//  term = action_list.RemoveAction(action);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveActions


\param  ogui_causer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveActions"

void OEHReaction :: RemoveActions (ODataWidget *ogui_causer )
{
  OEHAction    *action = NULL;
  if ( action = GetAction() )
    action->RemoveCauser(ogui_causer->GetDetailedCauser(event));
    
  while ( action = action_list.RemoveTail() )
    if ( !action->get_qaction() )
      delete action;

//  action_list.clear();

}

/******************************************************************************/
/**
\brief  ~OEHReaction - Sestructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHReaction"

     OEHReaction :: ~OEHReaction ( )
{

  action_list.Clear();
    
  delete event;
  event = NULL;
}


