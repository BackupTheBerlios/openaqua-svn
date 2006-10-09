/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OEventActionControl



\date     $Date: 2006/04/28 16:37:44,01 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEventActionControl"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#ifndef   DLL_OEventAction_HPP
#define   DLL_OEventAction_HPP
#include  <sOEventAction.hpp>
#include  <sDLL.h>
#endif
#include  <sOADKFactory.hpp>
#include  <sOCAU_Action.hpp>
#include  <sOCBitmap.hpp>
#include  <sOEventActionControl.hpp>
#include  <sOField.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOEventActionControl.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OEventActionControl :: CastPointer (char *typenames )
{

  return (   !typenames                               ? NULL
           : !strcmp(typenames,"OEventActionControl") ? this
                                                      : OEventAction_intern::CastPointer(typenames) );

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

int32 OEventActionControl :: CreateInstance (void **instptrp )
{
  *instptrp = new OEventActionControl();
  return(0);
}

/******************************************************************************/
/**
\brief  GroupItem

\return action_item

\param  index
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GroupItem"

OEventActionControl *OEventActionControl :: GroupItem (int index )
{

  return ( group_actions->Get(index) );




}

/******************************************************************************/
/**
\brief  ListItem

\return action_item

\param  index
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListItem"

OEventActionControl *OEventActionControl :: ListItem (int index )
{

  return ( sub_actions->Get(index) );




}

/******************************************************************************/
/**
\brief  OEventActionControl

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventActionControl"

     OEventActionControl :: OEventActionControl ( )
                     : OEventAction_intern (),
  type(EAT_command),
  action_field(NULL),
  group_actions(NULL),
  sub_actions(NULL)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOEventAction_intern
\param  iEAType
\param  pOField
\param  pOEventActions
\param  pOSubEventActions
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventActionControl"

     OEventActionControl :: OEventActionControl (OEventAction_intern bcOEventAction_intern, int16 iEAType, OField *pOField, DLL(OEventAction) *pOEventActions, DLL(OEventAction) *pOSubEventActions )
                     :  OEventAction_intern(bcOEventAction_intern)
,type((EventActionType)iEAType)
,action_field(pOField)
,group_actions(pOEventActions)
,sub_actions(pOSubEventActions)
{
/*
  "OEventActionControl("
   + ADK_EventAction_intern::Generate()
   + ", " + type
   + ", " + action_field.GenerateList()
   + ", " + sub_actions.GenerateList()
   + ", " + group_actions.GenerateList()
   + ")";
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

logical OEventActionControl :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OResource::Reset();
  OElementStyle::Read(ph);
  OEventAction_intern::Read(ph);
  
  type = (EventActionType)ph->GPH("type")->GetInt();
  action_field = CACHE_READ(ph,"action_field",OField);  
  
  ReadActions(ph->GPH("sub_actions"),&sub_actions);
  ReadActions(ph->GPH("group_actions"),&group_actions);
    

  return(term);
}

/******************************************************************************/
/**
\brief  ReadAction

\return term

\param  ph
\param  action_prop
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadAction"

logical OEventActionControl :: ReadAction (PropertyHandle *ph, char *action_prop )
{
  logical                 term = NO;
  if ( action_control = CACHE_READ(ph,action_prop,OEventActionControl) )
    *(OEventActionControl *)this = *action_control;
  
  OResource::Reset();
  OStyleElement::Read(ph);


  return(term);
}

/******************************************************************************/
/**
\brief  ReadActions

\return term

\param  ph
\param  p_action_list
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadActions"

logical OEventActionControl :: ReadActions (PropertyHandle *ph, DLL(OEventAction) **p_action_list )
{
  OEventAction     *action;
  long              indx0 = 0;
  logical           term = NO;
  if ( !*p_action_list )
    *p_action_list = new DLL(OEventAction)();
    
  while ( ph->Get(indx0++) )
    if ( action = CACHE_READ(ph,NULL,OEventAction) )
      (*p_action_list)->AddTail(action);
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OEventActionControl :: Reset ( )
{

  ResetActions(group_actions);
  ResetActions(sub_actions);

  if ( action_field )
    action_field->Release();
  action_field = NULL;
  
  OEventAction_intern::Reset();

}

/******************************************************************************/
/**
\brief  ~OEventActionControl


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEventActionControl"

     OEventActionControl :: ~OEventActionControl ( )
{

  if ( !Deleting() )
    Reset();
    
  delete sub_actions;
  sub_actions = NULL;

  delete group_actions;
  group_actions = NULL;

}


