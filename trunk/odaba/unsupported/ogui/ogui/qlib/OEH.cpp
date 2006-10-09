/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEH

\brief    Event Handler for O-Controls
          OEH  is an  event handler  class for  O-controls. On one hand OEH maps
          all  relevant  events  to  actions, which are activated for execution.
          Events,  which  are  not  mapped  to  an action, are associated with a
          defined  defaulT action, which  will be activated.  The set of default
          actions supported depends on the control type.

\date     $Date: 2006/05/04 12:36:32,17 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEH"

#include  <pogui7.h>
#include  <mOEH.h>
#include  <sOActionList.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHActionHandler.hpp>
#include  <sOEHEvent.hpp>
#include  <sOEHReactions.hpp>
#include  <sOIconSet.hpp>
#include  <standard.hpp>
#include  <sOEH.hpp>

int32 oeh_count = 0;
int32 oeh_total = 0;

/******************************************************************************/
/**
\brief  ActionList

\return pOActionList

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActionList"

OActionList OEH :: ActionList ( )
{
  QWidget       *qwidget     = oeh_widget ? oeh_widget->WidgetQ() 
                                          : NULL;
  return ( qwidget 
           ? OActionList(qwidget->actions())
           : OActionList() );


}

/******************************************************************************/
/**
\brief  CacheEvent

-------------------------------------------------------------------------------
\brief  i0


\param  ogui_data_event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheEvent"

void OEH :: CacheEvent (ADK_DATAEVENT ogui_data_event )
{

  CacheEvent((int)ogui_data_event);

}

/******************************************************************************/
/**
\brief  i01


\param  ogui_db_event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheEvent"

void OEH :: CacheEvent (ADK_DBEVENT ogui_db_event )
{
  CacheEvent((int)ogui_db_event);
}

/******************************************************************************/
/**
\brief  i02


\param  ogui_event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheEvent"

void OEH :: CacheEvent (ADK_GUIEVENT ogui_event )
{
  CacheEvent((int)ogui_event);
}

/******************************************************************************/
/**
\brief  i03


\param  etype
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheEvent"

void OEH :: CacheEvent (int etype )
{
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !event_cache )
    event_cache = new std::list<int>;

  event_cache->push_back(etype);

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void OEH :: Close ( )
{
  OEHReactions     *raction;
  while ( raction = reactions.RemoveTail() )
    delete raction;    

  ActionList().DeleteOEHActions();  // solche ohne causer

}

/******************************************************************************/
/**
\brief  ExecuteAction - Execute action


\return executed - Action executed

\param  act_names - Action name
\param  default_action - Default action
\param  no_user_handling
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 OEH :: ExecuteAction (char *act_names, logical default_action, logical no_user_handling )
{
  char       executed  = AUTO;
BEGINSEQ
  if ( !no_user_handling )
  {
    if ( (executed = ExecuteUserAction(act_names)) != AUTO ) 
                                                       LEAVESEQ
  }
  
  if ( (executed = ExecuteDefaultAction(act_names)) != AUTO)      
                                                     LEAVESEQ
    
  if ( !default_action )
  {
    OGUIEV1(act_names,0)
    OGUIERR(11)
  }
RECOVER

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteDefaultAction - 


\return executed - Action executed

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDefaultAction"

int8 OEH :: ExecuteDefaultAction (char *act_names )
{
  char         executed = AUTO;
BEGINSEQ
  if ( !default_hdl )                                LEAVESEQ
    
  executed = default_hdl->ExecuteAction(act_names);

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteReaction - 


\return executed - Action executed
-------------------------------------------------------------------------------
\brief  i00


\param  pOEHEvent - Event pointer
\param  causer - Causer of the event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteReaction"

int8 OEH :: ExecuteReaction (OEHEvent *pOEHEvent, ODataWidget *causer )
{

  return ( ExecuteReaction(FindReaction(pOEHEvent,causer),NO) );


}

/******************************************************************************/
/**
\brief  i01


\param  pOEHAction
\param  no_user_handling
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteReaction"

int8 OEH :: ExecuteReaction (OEHAction *pOEHAction, logical no_user_handling )
{
  char  *action   = NULL;
  int8   executed = AUTO;
BEGINSEQ
  if ( !pOEHAction || pOEHAction->IsDisabled() ||
       !(action = pOEHAction->GetAction())        )  LEAVESEQ
    
  cur_action = pOEHAction;
  executed   = ExecuteAction(action,pOEHAction->IsDefault(),no_user_handling);
  cur_action = NULL;

  if ( executed == AUTO )  // pOEHAction not implemented -> will be removed
    RemoveAction(pOEHAction);

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  i02


\param  pQAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteReaction"

int8 OEH :: ExecuteReaction (QAction *pQAction )
{
  return ( ExecuteReaction(OActionList::GetAction(pQAction),NO) );
}

/******************************************************************************/
/**
\brief  ExecuteUserAction - 


\return executed - Action executed

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteUserAction"

int8 OEH :: ExecuteUserAction (char *act_names )
{
  char      executed = AUTO;
BEGINSEQ
  if ( !user_hdl )                                   LEAVESEQ
    
  executed = user_hdl->ExecuteActionCall(act_names);

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  FindAction

\return pOEHAction

\param  act_names - Action name
\param  loid - Identification for an action object
\param  on_top_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindAction"

OEHAction *OEH :: FindAction (char *act_names, char *loid, logical on_top_w )
{

  return(ActionList().FindAction(act_names,loid,on_top_w));

}

/******************************************************************************/
/**
\brief  FindReaction - 


\return action

\param  pOEHEvent - Event pointer
\param  causer - Causer of the event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindReaction"

OEHAction *OEH :: FindReaction (OEHEvent *pOEHEvent, ODataWidget *causer )
{
  OEHReactions     *reacts;
  OEHAction        *action = NULL;
BEGINSEQ
  if ( causer )
  {
    cur_sender_odw = causer;
    cur_sender     = causer->WidgetQ();
  }  
  
  reactions.GoTop();
  while ( reacts = reactions.GetNext() )
    if ( reacts->get_qt_causer() == cur_sender ||
         ( !cur_sender && causer )                )  // 11.7.05 damit events der table-cellen (keine QWidget!) von table verarbeitet werden
      break;

  if ( !reacts )                                     ERROR
  
  if ( !(action = reacts->FindReaction(pOEHEvent)) )
                                                     ERROR
  cur_sender_odw = reacts->get_ogui_causer();

RECOVER
  cur_sender_odw = NULL;
  cur_retval     = NULL;
  action      = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  FindReactions

\return pOEHReactions

\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindReactions"

OEHReactions *OEH :: FindReactions (ODataWidget *oODataWidget )
{
  OEHReactions     *reacts = NULL;
BEGINSEQ
  if ( !this )                                       ERROR 

  reactions.GoTop();
  while ( reacts = reactions.GetNext() )
    if ( reacts->get_ogui_causer() == oODataWidget )
      break;

RECOVER

ENDSEQ

  return(reacts);
}

/******************************************************************************/
/**
\brief  FlushEventCache


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushEventCache"

void OEH :: FlushEventCache ( )
{
  std::list<int>::iterator  it;
  int                  etype = 0;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !event_cache )                                LEAVESEQ

  for ( it = event_cache->begin(); it != event_cache->end(); it++ )
  {
    etype = *it;
    
    if ( etype > 100 && etype < 200 )
      GenerateEvent(ADK_DATAEVENT(etype),oeh_widget);
    else if ( etype > 200 && etype < 300 )
      GenerateEvent(ADK_DBEVENT(etype),oeh_widget);
    else if ( etype > 300 && etype < 400 )
      GenerateEvent(ADK_GUIEVENT(etype),oeh_widget);
    else
      OGUISET(99)
  }

  event_cache->clear();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  GenerateEvent - 


\return executed - Action executed
-------------------------------------------------------------------------------
\brief  i00


\param  ogui_data_event
\param  causer - Causer of the event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

int8 OEH :: GenerateEvent (ADK_DATAEVENT ogui_data_event, ODataWidget *causer )
{
  OEHEvent    de(ogui_data_event);
  return( this
             ? ExecuteReaction(&de,causer)
             : NULL 
        );


}

/******************************************************************************/
/**
\brief  i01


\param  ogui_db_event
\param  causer - Causer of the event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

int8 OEH :: GenerateEvent (ADK_DBEVENT ogui_db_event, ODataWidget *causer )
{
  OEHEvent    dbe(ogui_db_event);

  return( this
             ? ExecuteReaction(&dbe,causer)
             : NULL 
        );


}

/******************************************************************************/
/**
\brief  i02


\param  ogui_event
\param  causer - Causer of the event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

int8 OEH :: GenerateEvent (ADK_GUIEVENT ogui_event, ODataWidget *causer )
{
  OEHEvent    ge(ogui_event);

  return( this
             ? ExecuteReaction(&ge,causer)
             : NULL 
        );


}

/******************************************************************************/
/**
\brief  GetActiveAction

\return loid - Identification for an action object

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveAction"

char *OEH :: GetActiveAction ( )
{

  return (   this && cur_action 
           ? cur_action->GetAction()
           : NULL   );

}

/******************************************************************************/
/**
\brief  GetActiveActionItem

\return loid - Identification for an action object

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveActionItem"

char *OEH :: GetActiveActionItem ( )
{

  return (   this && cur_action 
           ? cur_action->GetName()
           : NULL   );

}

/******************************************************************************/
/**
\brief  IsActionDisabled

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionDisabled"

logical OEH :: IsActionDisabled (char *act_names, char *loid )
{

  return ( this ? ActionList().IsActionDisabled(act_names,loid)
                : UNDEF );

}

/******************************************************************************/
/**
\brief  IsActionGrouped

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionGrouped"

logical OEH :: IsActionGrouped (char *act_names, char *loid )
{

  return ( this ? ActionList().IsActionGrouped(act_names,loid)
                : UNDEF );

}

/******************************************************************************/
/**
\brief  IsActionSeparated

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionSeparated"

logical OEH :: IsActionSeparated (char *act_names, char *loid )
{

  return ( this ? ActionList().IsActionSeparated(act_names,loid)
                : UNDEF );

}

/******************************************************************************/
/**
\brief  IsActionToggled

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionToggled"

logical OEH :: IsActionToggled (char *act_names, char *loid )
{

  return ( this ? ActionList().IsActionToggled(act_names,loid)
                : UNDEF );

}

/******************************************************************************/
/**
\brief  IsActionVisible

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionVisible"

logical OEH :: IsActionVisible (char *act_names, char *loid )
{

  return ( this ? ActionList().IsActionVisible(act_names,loid)
                : UNDEF );

}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical OEH :: IsEmpty ( )
{

  return ( this && reactions.GetCount() ? NO : YES  );

}

/******************************************************************************/
/**
\brief  NewAction

\return pOEHAction

\param  act_names - Action name
\param  loid - Identification for an action object
\param  sys_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewAction"

OEHAction *OEH :: NewAction (char *act_names, char *loid, logical sys_opt )
{
  OEHAction     *new_oeh_action = NULL;
  QAction       *new_qaction    = NULL;
  QWidget       *qwidget        = oeh_widget ? oeh_widget->WidgetQ() 
                                             : NULL;
BEGINSEQ
  if ( !sys_opt )
  {
    if ( !(new_qaction = new QAction(qwidget)) )     OGUIERR(95)
    qwidget->addAction(new_qaction);
  }
  
  if ( !(new_oeh_action = new OEHAction(act_names,loid,new_qaction,this)) )
                                                     OGUIERR(95)

RECOVER

ENDSEQ
  return(new_oeh_action);
}

/******************************************************************************/
/**
\brief  OEH - 



\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEH"

     OEH :: OEH (ODataWidget *pODataWidget )
                     : QObject (),
  oeh_widget(pODataWidget),
  reactions(),
  cur_action(NULL),
  cur_sender(NULL),
  cur_sender_odw(NULL),
  default_hdl(pODataWidget),
  user_hdl(NULL),
  event_cache(NULL)
{


oeh_count++;
oeh_total++;
}

/******************************************************************************/
/**
\brief  RemoveAction

\return term - 

\param  action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAction"

logical OEH :: RemoveAction (OEHAction *action )
{
  OEHReactions     *reacts;
  logical           term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  reactions.GoTop();
  while ( reacts = reactions.GetNext() )
  {
    reacts->RemoveAction(action);
    if ( reacts->IsEmpty() )
    {  
      reactions.RemoveAt();
      delete reacts;
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveReaction

\return term - 

\param  pOEHEvent - Event pointer
\param  oODataWidget - Owning data widget
\param  on_top_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveReaction"

logical OEH :: RemoveReaction (OEHEvent *pOEHEvent, ODataWidget *oODataWidget, logical on_top_w )
{
  OEHReactions     *reacts;
  logical           term = NO;

BEGINSEQ
  if ( !this )                                       ERROR
    
  reactions.GoTop();
  while ( reacts = reactions.GetNext() )
    if ( reacts->get_ogui_causer() == oODataWidget )
      break;
 
  if ( reacts )
  {
    reacts->RemoveReaction(pOEHEvent,on_top_w);
    if ( reacts->IsEmpty() )
    {  
      reactions.RemoveAt();
      delete reacts;
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetCauser - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCauser"

void OEH :: ResetCauser ( )
{
  cur_sender = NULL;
}

/******************************************************************************/
/**
\brief  SetActionDisabled

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionDisabled"

logical OEH :: SetActionDisabled (char *act_names, char *loid, logical fEnable )
{

  return (   this 
           ? ActionList().SetActionDisabled(act_names,loid,
                                             fEnable)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionGrouped

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionGrouped"

logical OEH :: SetActionGrouped (char *act_names, char *loid, logical fEnable )
{

  return (   this 
           ? ActionList().SetActionGrouped(act_names,loid,
                                            fEnable)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionIcon

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  text
\param  pOIcon
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionIcon"

logical OEH :: SetActionIcon (char *act_names, char *loid, char *text, OIconSet *pOIcon )
{

  return (   this 
           ? ActionList().SetActionIcon(act_names,loid,
                                         text,pOIcon)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionSeparated

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionSeparated"

logical OEH :: SetActionSeparated (char *act_names, char *loid, logical fEnable )
{

  return (   this 
           ? ActionList().SetActionSeparated(act_names,loid,
                                              fEnable)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionShortcut

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionShortcut"

logical OEH :: SetActionShortcut (char *act_names, char *loid, char *string )
{

  return (   this 
           ? ActionList().SetActionShortcut(act_names,loid,
                                             string)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionText

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  text
\param  tip
\param  status_tip
\param  what
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionText"

logical OEH :: SetActionText (char *act_names, char *loid, char *text, char *tip, char *status_tip, char *what )
{

  return (   this 
           ? ActionList().SetActionText(act_names,loid,
                                         text,tip,status_tip,what)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionToggled

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionToggled"

logical OEH :: SetActionToggled (char *act_names, char *loid, logical fEnable )
{

  return (   this 
           ? ActionList().SetActionToggled(act_names,loid,
                                            fEnable)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionVisible

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionVisible"

logical OEH :: SetActionVisible (char *act_names, char *loid, logical fEnable )
{

  return (   this 
           ? ActionList().SetActionVisible(act_names,loid,
                                            fEnable)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionWidget

\return cond

\param  act_names - Action name
\param  loid - Identification for an action object
\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionWidget"

logical OEH :: SetActionWidget (char *act_names, char *loid, ODataWidget *pODataWidget )
{

  return (   this 
           ? ActionList().SetActionWidget(act_names,loid,
                                           pODataWidget)
           : YES );

}

/******************************************************************************/
/**
\brief  SetCauser - 


\return cur_sender

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCauser"

QObject *OEH :: SetCauser ( )
{

  return ( cur_sender = (QObject *)sender() );

}

/******************************************************************************/
/**
\brief  SetReaction - 


\return action

\param  act_names - Action name
\param  loid - Identification for an action object
\param  parent_loid
\param  pOEHEvent - Event pointer
\param  oODataWidget - Owning data widget
\param  default_w
\param  pass_opt_w
\param  pass_to
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReaction"

OEHAction *OEH :: SetReaction (char *act_names, char *loid, char *parent_loid, OEHEvent *pOEHEvent, ODataWidget *oODataWidget, logical default_w, ActionBubbleType pass_opt_w, char *pass_to )
{
  OEHReactions     *reacts        = NULL;
  OEHAction        *parent_action = NULL;
  OEHAction        *action        = NULL;

BEGINSEQ
  if ( !this )                                       ERROR
  
// statt default_w sollte zusätzlicher parameter kommen fue nicht suchen muessen
  if ( default_w || !(action = FindAction(act_names,loid,NO)) )
    if ( !(action = NewAction(act_names,loid,pOEHEvent->IsSystemType())))
                                                     OGUIERR(95)

  action->SetDefault(default_w);
  action->SetPass(pass_opt_w,pass_to);
  if ( parent_loid )
  {
    if ( !(parent_action = FindAction(NULL,parent_loid,NO)) )
                                                     OGUIERR(99)
    parent_action->AddAction(action);
  }
  
  if ( pOEHEvent )
  {
    if ( pOEHEvent->get_type() == ET_Shortcut )
      action->SetShortcut(&pOEHEvent->get_shortcut());
    
    if ( !(reacts = FindReactions(oODataWidget)) )
    {
      if ( !(reacts = new OEHReactions(oODataWidget)) )
                                                     OGUIERR(95)
      reactions.AddHead(reacts);
    }
    if ( reacts->SetReaction(pOEHEvent,action,default_w) ) ERROR
  }

RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  SetUserActionHdl - 



\param  pOEHActionHandler
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserActionHdl"

void OEH :: SetUserActionHdl (OEHActionHandler *pOEHActionHandler )
{
  if ( this )
    user_hdl = pOEHActionHandler;


}

/******************************************************************************/
/**
\brief  xx_doClicked

\return term - 
-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xx_doClicked"

logical OEH :: xx_doClicked ( )
{
  OEHInternalEvent   intev(GEV_Click);
  OEHEvent           event(intev);
  logical            term = NO;
BEGINSEQ
  if ( !SetCauser() )                                ERROR
  
  if ( cur_sender && cur_sender->isWidgetType() )
    ((QWidget*)cur_sender)->setFocus();
    
  if ( ExecuteReaction(&event,NULL) )                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  pQObject - 
\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xx_doClicked"

logical OEH :: xx_doClicked (QObject *pQObject, int id )
{
  OEHInternalEvent   intev(GEV_Click);
  OEHEvent           event(intev,id);
  logical            term = NO;
BEGINSEQ
  cur_sender = pQObject;
  if ( ExecuteReaction(&event,NULL) )                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OEH - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEH"

     OEH :: ~OEH ( )
{


oeh_count--;
}


