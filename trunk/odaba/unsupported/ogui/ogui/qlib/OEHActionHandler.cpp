/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEHActionHandler

\brief    Base Class for Action Handler


\date     $Date: 2006/05/03 18:29:45,48 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHActionHandler"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOEHActionHandler.hpp>


/******************************************************************************/
/**
\brief  ExecuteAction - Execute action
        The  function calls an action initiated by  an event or user action. The
        function  can be overloaded in the  application for hanling actions in a
        proper  way.  Actions  not  handled  will be handled by a default action
        handler. Actions not handled at all are disconnected from the event. 
        When  an action has  been handled, the  action handler should return YES
        or  NO to  indicate error  or succes.  When no handler was found (AUTO),
        the  action  will  automatically  disconnected  from  the  event,  which
        initiated  the action. In this case  the application must reactivate the
        event for setting the action again.

\return executed - Action executed

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 OEHActionHandler :: ExecuteAction (char *act_names )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  ExecuteActionCall

\return executed - Action executed

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteActionCall"

int8 OEHActionHandler :: ExecuteActionCall (char *act_names )
{
  int8  executed = AUTO;
//  if ( gui_call )
//    executed = NO;
//  else
//  {
//    gui_call = YES;
    executed = ExecuteAction(act_names);
//    gui_call = NO;
//  }
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteDBEventAction - 


\return rc

\param  ogui_db_event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDBEventAction"

int32 OEHActionHandler :: ExecuteDBEventAction (ADK_DBEVENT ogui_db_event )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  ExecuteDataEventAction - Execute data event action
        This  function can be overloaded for executing actions associated with a
        specific data event.

\return rc

\param  ogui_data_event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDataEventAction"

int32 OEHActionHandler :: ExecuteDataEventAction (ADK_DATAEVENT ogui_data_event )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  ExecuteGUIEventAction - 


\return rc

\param  ogui_event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteGUIEventAction"

int32 OEHActionHandler :: ExecuteGUIEventAction (ADK_GUIEVENT ogui_event )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  IsGUICall

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGUICall"

logical OEHActionHandler :: IsGUICall ( )
{
  return ( this ? gui_call : UNDEF );
}

/******************************************************************************/
/**
\brief  OEHActionHandler


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHActionHandler"

     OEHActionHandler :: OEHActionHandler ( )
                     : vcls(),
  gui_call(UNDEF)
{
}

/******************************************************************************/
/**
\brief  ProcessKeyEvent - Process general key events
        This  functions can  be overloaded  for overloading  any or an undefined
        key  event.  The  function  is  executed, after looking for specific key
        events  and  their  associated  actions,  i.e. actions associated with a
        specific  key  event,  are  called  prior  to  general  key  events. The
        function  must return the success code of the action executed or AUTO in
        case of no action.

\return executed - Action executed

\param  dkey
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessKeyEvent"

int8 OEHActionHandler :: ProcessKeyEvent (DKey &dkey )
{

  return(AUTO);

}


