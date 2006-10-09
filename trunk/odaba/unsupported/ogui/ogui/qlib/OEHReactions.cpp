/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEHReactions

\brief    List of reactions
          The  class  lists  the  reactions  for  a  certain GUI resource. Since
          reactions  for  a  control  can  be  caused by different reaources (as
          buttons  associated  with  a  control), actions are collected for each
          resource associated with the event handling control.

\date     $Date: 2006/05/04 12:33:16,71 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHReactions"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHEvent.hpp>
#include  <sOEHReactions.hpp>


/******************************************************************************/
/**
\brief  FindReaction - Find current reaction for an event


\return actin

\param  pOEHEvent - Event pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindReaction"

OEHAction *OEHReactions :: FindReaction (OEHEvent *pOEHEvent )
{
  OEHReaction     *react;
  OEHAction       *action = NULL;
  reactions.GoTop();
  while ( react = reactions.GetNext() )
    if ( *react->get_event() == *pOEHEvent )
      break;

  if ( react ) 
    action = react->GetAction();



  return(action);
}

/******************************************************************************/
/**
\brief  IsEmpty

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical OEHReactions :: IsEmpty ( )
{

  return ( this && reactions.GetCount() ? NO : YES );

}

/******************************************************************************/
/**
\brief  OEHReactions - Constructor



\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHReactions"

     OEHReactions :: OEHReactions (ODataWidget *oODataWidget )
                     :   ogui_causer(oODataWidget),
  qt_causer(NULL),
  reactions()
{
BEGINSEQ
  if ( !ogui_causer )                                ERROR
  qt_causer = ogui_causer->WidgetQ();
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  RemoveAction


\param  action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAction"

void OEHReactions :: RemoveAction (OEHAction *action )
{
  OEHReaction     *react;
  reactions.GoBottom();
  while ( react = reactions.GetPrev() )
  {
    react->RemoveAction(action,ogui_causer);
    if ( react->IsEmpty() )
    {  
      reactions.RemoveAt();
      delete react;
    }
  }

}

/******************************************************************************/
/**
\brief  RemoveReaction


\param  pOEHEvent - Event pointer
\param  on_top_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveReaction"

void OEHReactions :: RemoveReaction (OEHEvent *pOEHEvent, logical on_top_w )
{
  OEHReaction     *react;
  logical          term = NO;
  reactions.GoTop();
  while ( react = reactions.GetNext() )
    if ( *react->get_event() == *pOEHEvent )
      break;

  if ( react )
  {
    if ( on_top_w )
      react->RemoveAction(react->GetAction(),ogui_causer);
    else
      react->RemoveActions(ogui_causer);
      
    if ( react->IsEmpty() )
    {  
      reactions.RemoveAt();
      delete react;
    }
  }

}

/******************************************************************************/
/**
\brief  SetReaction - Set reaction for an event
        Reactions  can be set  for different events.  Setting a reaction for the
        same event again will push the current event to the stack.

\return term - 

\param  pOEHEvent - Event pointer
\param  action
\param  new_event_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReaction"

logical OEHReactions :: SetReaction (OEHEvent *pOEHEvent, OEHAction *action, logical new_event_opt )
{
  OEHReaction     *react = NULL;
  logical          term  = NO;
BEGINSEQ
  if ( ogui_causer )
    ogui_causer->ConnectAction(action);
    
  if ( !new_event_opt )
  {    
    reactions.GoTop();
    while ( react = reactions.GetNext() )
      if ( *react->get_event() == *pOEHEvent )
        break;
  }
  
  if ( react )
    delete pOEHEvent;
  else
  {
    if ( !(react = new OEHReaction(pOEHEvent)) )     OGUIERR(95)
    reactions.AddHead(react);
    new_event_opt = YES;
  }
      
  react->AddAction(ogui_causer,action,new_event_opt);
RECOVER
  term = YES;
ENDSEQ

  return(term);
}

/******************************************************************************/
/**
\brief  ~OEHReactions - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHReactions"

     OEHReactions :: ~OEHReactions ( )
{
  OEHReaction     *raction;
  while ( raction = reactions.RemoveTail() )
    delete raction;
    

}


