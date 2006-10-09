/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OActionList



\date     $Date: 2006/05/04 12:43:18,01 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OActionList"

#include  <pogui7.h>
#include  <decl_mt.h>
#include  <sDPixmap.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOIconSet.hpp>
#include  <sOActionList.hpp>


/******************************************************************************/
/**
\brief  Clear


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void OActionList :: Clear ( )
{
  OEHAction  *oeh_action = NULL;
  QAction    *pQAction   = NULL;
  QVariant    qvar;
  int         count      = size();
  int         indx0      = 0;
  while ( indx0 < count ) 
    if ( oeh_action = GetAction(pQAction = at(indx0++)) )
    {
      pQAction->setData(qvar);
      delete oeh_action;
    }

  clear();
}

/******************************************************************************/
/**
\brief  DeleteOEHActions


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteOEHActions"

void OActionList :: DeleteOEHActions ( )
{
  OEHAction  *pOEHAction = NULL;
  QAction    *pQAction   = NULL;
  QVariant    qvar;
  int         count      = size();
  int         indx0      = 0;
  while ( indx0 < count ) 
    if ( pOEHAction = GetAction(pQAction = at(indx0++)) )
    {
      pQAction->setData(qvar);
      delete pOEHAction;
    }


}

/******************************************************************************/
/**
\brief  FindAction

\return pOEHAction
-------------------------------------------------------------------------------
\brief  i00


\param  act_names - Action name
\param  loid - Identification for an action object
\param  on_top_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindAction"

OEHAction *OActionList :: FindAction (char *act_names, char *loid, logical on_top_w )
{

  return ( FindNextAction(act_names,loid,NULL,on_top_w) );

}

/******************************************************************************/
/**
\brief  i01


\param  pOEHAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindAction"

OEHAction *OActionList :: FindAction (OEHAction *pOEHAction )
{
  OEHAction  *oeh_action = NULL;
  int         count      = size();
  int         indx0      = 0;
BEGINSEQ
  while ( count-- ) 
    if ( oeh_action = GetAction(at(count)) )
      if ( oeh_action == pOEHAction )                LEAVESEQ

  ERROR
RECOVER
  oeh_action = NULL;
ENDSEQ
  return(oeh_action);
}

/******************************************************************************/
/**
\brief  FindNextAction

\return pOEHAction

\param  act_names - Action name
\param  loid - Identification for an action object
\param  pOEHAction
\param  on_top_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindNextAction"

OEHAction *OActionList :: FindNextAction (char *act_names, char *loid, OEHAction *pOEHAction, logical on_top_w )
{
  OEHAction  *oeh_action = NULL;
  int         count      = size();
  int         indx0      = 0;
BEGINSEQ
  if ( pOEHAction )
  {
    if ( loid || on_top_w )                          ERROR
    if ( (indx0 = indexOf(pOEHAction->get_qaction())) == -1 )
                                                     ERROR
    indx0++;
  }

  while ( indx0 < count ) 
    if ( oeh_action = GetAction(at(indx0++)) )
    {
      if ( oeh_action->Is(act_names,loid) )          LEAVESEQ
      if ( on_top_w )                                ERROR
    }

  ERROR
RECOVER
  oeh_action = NULL;
ENDSEQ
  return(oeh_action);
}

/******************************************************************************/
/**
\brief  FirstAction

\return pOEHAction

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstAction"

OEHAction *OActionList :: FirstAction ( )
{

  return ( GetAction(first()) );

}

/******************************************************************************/
/**
\brief  GetAction

\return pOEHAction

\param  pQAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAction"

OEHAction *__cdecl OActionList :: GetAction (QAction *pQAction )
{

  return ( pQAction ? pQAction->data().value<OEHAction *>() 
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

logical OActionList :: IsActionDisabled (char *act_names, char *loid )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        cond       = YES;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  if ( oeh_action->IsDisabled() )                    LEAVESEQ
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    if ( oeh_action->IsDisabled() )                  LEAVESEQ
      
  ERROR
  
  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical OActionList :: IsActionGrouped (char *act_names, char *loid )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        cond       = YES;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  if ( oeh_action->IsGrouped() )                     LEAVESEQ
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    if ( oeh_action->IsGrouped() )                   LEAVESEQ
       
  ERROR
  
  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical OActionList :: IsActionSeparated (char *act_names, char *loid )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        cond       = YES;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  if ( oeh_action->IsSeparated() )                   LEAVESEQ
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    if ( oeh_action->IsSeparated() )                 LEAVESEQ
       
  ERROR
  
  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical OActionList :: IsActionToggled (char *act_names, char *loid )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        cond       = YES;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  if ( oeh_action->IsToggled() )                     LEAVESEQ
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    if ( oeh_action->IsToggled() )                   LEAVESEQ
       
  ERROR
  
  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical OActionList :: IsActionVisible (char *act_names, char *loid )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        cond       = YES;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  if ( oeh_action->IsVisible() )                     LEAVESEQ
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    if ( oeh_action->IsVisible() )                   LEAVESEQ
       
  ERROR
  
  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  OActionList

-------------------------------------------------------------------------------
\brief  i0


\param  pQListQAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OActionList"

     OActionList :: OActionList (QList<QAction *> *pQListQAction )
                     : QList<QAction *> (*pQListQAction)
{

}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OActionList"

     OActionList :: OActionList ( )
                     : QList<QAction *> ()
{
}

/******************************************************************************/
/**
\brief  i02


\param  pOActionList
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OActionList"

     OActionList :: OActionList (const OActionList &pOActionList )
                     : QList<QAction *> (*(QList<QAction *> *)&pOActionList)
{
}

/******************************************************************************/
/**
\brief  i03


\param  rQListQAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OActionList"

     OActionList :: OActionList (const QList<QAction *> &rQListQAction )
                     : QList<QAction *> (rQListQAction)
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

logical OActionList :: RemoveAction (OEHAction *pOEHAction )
{
  QAction    *pQAction   = NULL;
  QVariant    qvar;
  int         count      = size();
  int         indx0      = 0;
  logical     term       = NO;
BEGINSEQ
  while ( indx0 < count ) 
    if ( GetAction(pQAction = at(indx0)) != pOEHAction )
      indx0++;
    else
    {
      pQAction->setData(qvar);
      delete pOEHAction;
      removeAt(indx0);
      LEAVESEQ
    }

  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionDisabled

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionDisabled"

logical OActionList :: SetActionDisabled (char *act_names, char *loid, logical fEnable )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetDisabled(fEnable);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetDisabled(fEnable);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionGrouped

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionGrouped"

logical OActionList :: SetActionGrouped (char *act_names, char *loid, logical fEnable )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetGrouped(fEnable);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetGrouped(fEnable);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionIcon

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  text
\param  pOIcon
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionIcon"

logical OActionList :: SetActionIcon (char *act_names, char *loid, char *text, OIconSet *pOIcon )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetIcon(text,pOIcon);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetIcon(text,pOIcon);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionSeparated

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionSeparated"

logical OActionList :: SetActionSeparated (char *act_names, char *loid, logical fEnable )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetSeparated(fEnable);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetSeparated(fEnable);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionShortcut

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionShortcut"

logical OActionList :: SetActionShortcut (char *act_names, char *loid, char *string )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  OEHShortcut    shortcut(string);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetShortcut(&shortcut);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetShortcut(&shortcut);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionText

\return term - 

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

logical OActionList :: SetActionText (char *act_names, char *loid, char *text, char *tip, char *status_tip, char *what )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetText(text,tip,status_tip,what);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetText(text,tip,status_tip,what);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionToggled

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionToggled"

logical OActionList :: SetActionToggled (char *act_names, char *loid, logical fEnable )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetToggled(fEnable);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetToggled(fEnable);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionVisible

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionVisible"

logical OActionList :: SetActionVisible (char *act_names, char *loid, logical fEnable )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetVisible(fEnable);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetVisible(fEnable);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionWidget

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionWidget"

logical OActionList :: SetActionWidget (char *act_names, char *loid, ODataWidget *pODataWidget )
{
  OEHAction     *oeh_action = FindAction(act_names,loid,NO);
  logical        term       = NO;
BEGINSEQ
  if ( !oeh_action )                                 ERROR
  oeh_action->SetWidget(pODataWidget);
  
  while ( oeh_action = FindNextAction(act_names,loid,oeh_action,NO) )
    oeh_action->SetWidget(pODataWidget);
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


