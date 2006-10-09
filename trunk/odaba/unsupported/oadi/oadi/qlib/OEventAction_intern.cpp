/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OEventAction_intern



\date     $Date: 2006/04/29 12:08:49,04 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEventAction_intern"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cADK_GUIEVENT.h>
#include  <sOEventActionControl.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOEventAction_intern.hpp>


/******************************************************************************/
/**
\brief  ActionID

\return act_names

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActionID"

char *OEventAction_intern :: ActionID ( )
{

  return ( this 
           ? default_action.get_sys_ident()
           : NULL );

}

/******************************************************************************/
/**
\brief  ActionItemID

\return act_id

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActionItemID"

char *OEventAction_intern :: ActionItemID ( )
{

  return ( this 
           ? action_control
             ? action_control->get_sys_ident()
             : default_action.get_sys_ident()
           : NULL );

}

/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OEventAction_intern :: CastPointer (char *typenames )
{

  return (   !typenames                               ? NULL
           : !strcmp(typenames,"OEventAction_intern") ? this
                                                      : OElementStyle::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  OEventAction_intern

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventAction_intern"

     OEventAction_intern :: OEventAction_intern ( )
                     : OElementStyle(),
  default_action(),
  bubble_type(ABT_undefined),
  bubble_path(NULL),
  system_event_id(0),
  mouse_clicks(0),
  mouse_alt(NO),
  mouse_shift(NO),
  mouse_ctrl(NO),
  mouse_button(MK_undefined),
  key_string(NULL),
  start_date(),
  start_time(),
  time_cyclus(),
  day_cyclus(0),
  action_control(NULL)


{

}

/******************************************************************************/
/**
\brief  i01


\param  bcOElementStyle
\param  default_action
\param  bubble_type
\param  bubble_path
\param  system_event_id
\param  mouse_clicks
\param  mouse_alt
\param  mouse_shift
\param  mouse_ctrl
\param  mouse_button
\param  key_string
\param  start_date
\param  start_time
\param  time_cyclus
\param  day_cyclus
\param  action_control
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventAction_intern"

     OEventAction_intern :: OEventAction_intern (OElementStyle bcOElementStyle, OCAU_Action default_action, ActionBubbleType bubble_type, char *bubble_path, int32 system_event_id, int8 mouse_clicks, logical mouse_alt, logical mouse_shift, logical mouse_ctrl, MOUSKEY mouse_button, char *key_string, dbdt start_date, dbtm start_time, dbtm time_cyclus, int8 day_cyclus, OEventActionControl *action_control )
                     : OElementStyle(bcOElementStyle),
  default_action(default_action),
  bubble_type(bubble_type),
  bubble_path(NULL), // strdup
  system_event_id(system_event_id),
  mouse_clicks(mouse_clicks),
  mouse_alt(mouse_alt),
  mouse_shift(mouse_shift),
  mouse_ctrl(mouse_ctrl),
  mouse_button(mouse_button),
  key_string(NULL), //strdup
  start_date(start_date),
  start_time(start_time),
  time_cyclus(time_cyclus),
  day_cyclus(day_cyclus),
  action_control(action_control)

{
  this->bubble_path = strdup(bubble_path);
  this->key_string  = strdup(key_string);
/*
  "OEventAction_intern("
  + ADK_ElementStyle::Generate()
  + ", " + default_action.Generate()
  + ", " + bubble_type
  + ", \"" + bubble_path + "\""
  + ", " + system_event.event_id
  + ", " + mouse_event.clicks
  + ", " + mouse_event.alt
  + ", " + mouse_event.shift
  + ", " + mouse_event.ctrl
  + ", " + mouse_event.mode
  + ", \"" + key_event.key_string + "\"" 
  + ", " + time_event.start_date
  + ", " + time_event.start_time
  + ", " + time_event.time_cyclus
  + ", " + time_event.day_cyclus
  + ", " + action_control.Generate()
  + ") ";

*/
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OEventAction_intern :: Read (PropertyHandle *ph )
{
  char                   *str = NULL;
  char                    old_action[ID_SIZE];
  ActionType              old_type;
  int32                   number;
  logical                 term = NO;
  memcpy(old_action,default_action.get_sys_ident(),ID_SIZE);
  old_type = default_action.get_actionType();
  default_action.SetAction("",ACT_undefined);
  default_action.Read(ph->GPH("default_action"));
  if ( default_action.get_actionType() )
  { 
    if ( *default_action.get_sys_ident() <= ' ' )
      memcpy(default_action.get_sys_ident(),sys_ident,ID_SIZE);
  }
  else
    default_action.SetAction(old_action,old_type);
      
  if ( number = ph->GetInt("bubble_type") )
  {
    (int&)bubble_type = number;
    if ( (str = ph->GetString("bubble_path")) && *str )
      bubble_path = strdup(str);
  }

  if ( number = ph->GetInt("system_event.event_id") )
    system_event_id = number;
  
  if ( number = ph->GetInt("mouse_event.clicks") )
  {
    mouse_clicks       = number;
    mouse_alt          = ph->GetInt("mouse_event.alt");
    mouse_shift        = ph->GetInt("mouse_event.shift");
    mouse_ctrl         = ph->GetInt("mouse_event.ctrl");
    (int&)mouse_button = ph->GetInt("mouse_event.mode");
  }
  
  if ( !ph->GetDate("time_event.start_date").IsEmpty() || 
       !ph->GetTime("time_event.start_time").IsEmpty()   )
  {
    start_date  = ph->GetDate("time_event.start_date");
    start_time  = ph->GetTime("time_event.start_time");
    day_cyclus  = ph->GetInt("time_event.day_cyclus");
    time_cyclus = ph->GetTime("time_event.time_cyclus");
  }
  
  if ( (str = ph->GetString("key_event.key_string")) && *str )
    key_string = strdup(str);
  

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OEventAction_intern :: Reset ( )
{
  system_event_id = 0;
  mouse_clicks    = 0;
  mouse_alt       = NO;
  mouse_shift     = NO;
  mouse_ctrl      = NO;
  mouse_button    = MK_undefined;
  start_date      = dbdt();
  start_time      = dbtm();
  time_cyclus     = dbtm();
  day_cyclus      = 0;
  bubble_type     = ABT_undefined;
  if ( bubble_path )
    free(bubble_path);
  bubble_path = NULL;
  if ( key_string )
    free(key_string);
  key_string = NULL;
  
  default_action.Deleting();
  default_action.Reset();
  
  OElementStyle::Reset();
}

/******************************************************************************/
/**
\brief  SetContextMenuProperty


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContextMenuProperty"

void OEventAction_intern :: SetContextMenuProperty ( )
{

  system_event_id = GEV_ContextMenu;
  
  default_action.SetAction("UserContextMenu",ACT_Menu);


}

/******************************************************************************/
/**
\brief  ~OEventAction_intern


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEventAction_intern"

     OEventAction_intern :: ~OEventAction_intern ( )
{
  if ( !Deleting() )
    Reset();
  else
    default_action.Deleting();
}


