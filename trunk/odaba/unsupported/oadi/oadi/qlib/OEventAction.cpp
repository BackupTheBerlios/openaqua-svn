/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OEventAction



\date     $Date: 2006/04/28 16:41:01,29 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEventAction"

#include  <poadi.h>
#include  <cmacros.h>
#ifndef   DLL_OEventAction_HPP
#define   DLL_OEventAction_HPP
#include  <sOEventAction.hpp>
#include  <sDLL.h>
#endif
#include  <sOCBitmap.hpp>
#include  <sODControl.hpp>
#include  <sOEHAction.hpp>
#include  <sOEventAction.hpp>
#include  <sOField.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sTWidgetControl.hpp>
#include  <sOEventAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OEventAction :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OEventAction") ? this
                                               : OEventActionControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OEventAction :: CreateInstance (void **instptrp )
{
  *instptrp = new OEventAction();
  return(0);
}

/******************************************************************************/
/**
\brief  OEventAction

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventAction"

     OEventAction :: OEventAction ( )
                     : OEventActionControl ()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOEventActionControl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventAction"

     OEventAction :: OEventAction (OEventActionControl bcOEventActionControl )
                     : OEventActionControl(bcOEventActionControl)
{
/*
  "OEventAction("
  + ADK_EventActionControl::Generate()
  + ")";
  // ReadAction(action_control)
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

logical OEventAction :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  ReadAction(ph,"action_control"); 
  OResource::Reset();
  OElementStyle::Read(ph);
  
  SetupAction();
  OEventAction_intern::Read(ph);



  return(term);
}

/******************************************************************************/
/**
\brief  ReadAction

\return pOEventActionControl

\param  ph
\param  action_prop
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadAction"

OEventActionControl *OEventAction :: ReadAction (PropertyHandle *ph, char *action_prop )
{
  OEventActionControl    *ac = NULL;
  logical                 term = NO;
  if ( ac = CACHE_READ(ph,action_prop,OEventActionControl) )
  {
    *(OEventActionControl *)this = *ac;
    action_control = ac;
  }

  return(ac);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OEventAction :: Reset ( )
{
  if ( action_control )
    action_control->Release();
  action_control = NULL;
  OEventActionControl oeac;
  *(OEventActionControl *)this = oeac;  // das koennte zu einfach sein, vor allen fuer recursiv

  OEventActionControl::Reset();
}

/******************************************************************************/
/**
\brief  SetAction

\return term

\param  parent_field
\param  parent_action
\param  event_frame
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

logical OEventAction :: SetAction (TWidgetControl *parent_field, OEventAction *parent_action, OEH_Frame event_frame )
{
  ODControl              *oc       = parent_field->get_complexWidget();
  OEHAction              *act      = NULL;
  char                   *act_id   = NULL;
  char                   *act_name = NULL;
  char                   *parent   = NULL;
  TWidgetControl         *t        = NULL;
  logical                 term     = NO;
BEGINSEQ
  if ( !autoOpen )                                   LEAVESEQ
    
  act_id   = action_control ? action_control->get_sys_ident() : NULL;
  act_name = default_action.get_actionType() != ACT_undefined
             ? default_action.get_sys_ident() : NULL;
  parent   = parent_action && parent_action->get_action_control()
             ? parent_action->get_action_control()->get_sys_ident() : NULL;
  
  if ( !(act = oc->SetAction(act_name,act_id,parent,
                      bubble_type ? bubble_type : ABT_never,
                      bubble_path)) )                ERROR
  
  if ( mouse_clicks )
    oc->SetAction(act_name,act_id,
                  mouse_clicks,mouse_alt,mouse_shift,mouse_ctrl,
                  mouse_button == MK_Right,
                  mouse_button == MK_Middle,
                  mouse_button == MK_Left);
  
  if ( key_string && *key_string )
    oc->SetAction(act_name,act_id,
                  key_string,event_frame);
  
  if ( system_event_id )
    oc->SetAction(act_name,act_id,system_event_id);
  
  if ( !start_date.IsEmpty() || !start_time.IsEmpty() )
    oc->SetAction(act_name,act_id,
                  start_date,start_time,day_cyclus,time_cyclus);
  
  switch ( type )
  {
    case EAT_undefined :
    case EAT_command   : 
                         break;
    case EAT_group     : SetActions(parent_field,group_actions,event_frame);
                         act->SetGrouped(YES);
                         break;
    case EAT_list      : SetActions(parent_field,sub_actions,event_frame);
                         break;
    case EAT_toggle    : act->SetToggled(checked);
                         break;
    case EAT_field     : if ( action_field && action_field->IsAutoOpen() )
                         {
                           t = (TWidgetControl *)action_field->Open(parent_field,YES);
                           act->SetWidget(t->get_complexWidget());
                         }
                         break;
  }

  act->SetText(textDefinitions.get_title(),
               textDefinitions.get_tooltip(),
               textDefinitions.get_tooltip(),
               textDefinitions.get_long_text());
  
  if ( disabled )
    act->SetDisabled(YES);

  if ( bitmap )
    act->SetIcon(textDefinitions.get_title(),
                 bitmap->GetInactiveBitmap(),
                 bitmap->GetActiveBitmap(),
                 bitmap->GetDisabledBitmap());
  if ( separate )
    act->SetSeparated(YES);

  if ( hidden )
    act->SetVisible(YES);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActions

\return term

\param  parent_field
\param  action_list
\param  event_frame
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActions"

logical OEventAction :: SetActions (TWidgetControl *parent_field, DLL(OEventAction) *action_list, OEH_Frame event_frame )
{
  OEventAction           *action;
  logical                 term = NO;
  action_list->GoTop();
  while ( action = action_list->GetNext() )
    parent_field->SetAction(action,this,event_frame);
  return(term);
}

/******************************************************************************/
/**
\brief  SetupAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAction"

void OEventAction :: SetupAction ( )
{

BEGINSEQ
  if ( !action_control )                             LEAVESEQ

  textDefinitions.SetupText(&action_control->get_textDefinitions());

  if ( !style )
  {
    style = action_control->get_style();
    style->Reserve();
  }

  if ( !font )
  {
    font = action_control->get_font();
    font->Reserve();
  }

  if ( !layout )
  {
    layout = action_control->get_layout();
    layout->Reserve();
  }

  if ( !bitmap )
  {
    bitmap = action_control->get_bitmap();
    bitmap->Reserve();
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OEventAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEventAction"

     OEventAction :: ~OEventAction ( )
{
  if ( !Deleting() )
    Reset();
  else
  {
    OEventActionControl oeac;
    *(OEventActionControl *)this = oeac;  // das koennte zu einfach sein, vor allen fuer recursiv
    Deleting();
  }
}


