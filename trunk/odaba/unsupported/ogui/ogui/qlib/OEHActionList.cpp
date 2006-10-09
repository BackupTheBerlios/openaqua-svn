/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEHActionList



\date     $Date: 2006/05/02 12:44:34,60 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHActionList"

#include  <pogui7.h>
#include  <sOEHAction.hpp>
#include  <sOEHActionList.hpp>


/******************************************************************************/
/**
\brief  AddAction

\return term - 

\param  action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAction"

logical OEHActionList :: AddAction (OEHAction *action )
{
  logical                 term = NO;
  append(action);
  return(term);
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

OEHAction *OEHActionList :: FindAction (char *act_names, char *loid, logical on_top_w )
{
  OEHAction  *action     = NULL;
  int         count      = size();
  int         indx0      = 0;
BEGINSEQ
  while ( indx0 < count ) 
  {
    action = at(indx0++);
    if ( action->Is(act_names,loid) )                LEAVESEQ
    if ( on_top_w )                                  ERROR
  }

  ERROR
RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  OEHActionList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHActionList"

     OEHActionList :: OEHActionList ( )
                     : QList<OEHAction *> ()
{
}

/******************************************************************************/
/**
\brief  RemoveAction

\return term - 

\param  pOEHAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAction"

logical OEHActionList :: RemoveAction (OEHAction *pOEHAction )
{
  int         indx0 = 0;
  logical     term  = NO;
BEGINSEQ
  if ( (indx0 = indexOf(pOEHAction)) == -1 )         ERROR
  removeAt(indx0);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetIcons


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcons"

void OEHActionList :: SetIcons ( )
{
  OEHAction  *action     = NULL;
  int         count      = size();
  int         indx0      = 0;
  while ( indx0 < count ) 
  {
    action = at(indx0++);
    action->SetIcon();
  }

}

/******************************************************************************/
/**
\brief  SetupGroup

\return term - 

\param  pQActionGroup
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupGroup"

logical OEHActionList :: SetupGroup (QActionGroup *pQActionGroup )
{
  int         count      = UNDEF;
  int         indx0      = 0;
  logical     term       = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  count = size();
  while ( indx0 < count ) 
    pQActionGroup->addAction(at(indx0++)->get_qaction());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


