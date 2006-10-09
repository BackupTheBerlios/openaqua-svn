/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHAction

\brief    Action
          An  action  is  defined  in  the  context  of  an event for a GUI data
          widget.

\date     $Date: 2006/07/09 17:29:35,42 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHAction"

#include  <pogui7.h>
#include  <decl_mt.h>
#include  <mOEHAction.h>
#include  <sDAction.hpp>
#include  <sDPixmap.hpp>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHActionList.hpp>
#include  <sOEHShortcut.hpp>
#include  <sOFont.hpp>
#include  <sOIconSet.hpp>
#include  <sOWidget.hpp>
#include  <sOEHAction.hpp>

int32 oact_count = 0;
int32 oact_max = 0;
int32 oact_total = 0;

/******************************************************************************/
/**
\brief  AddAction - 



\return term - 

\param  pOEHAction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAction"

logical OEHAction :: AddAction (OEHAction *pOEHAction )
{
  logical                 term = NO;
BEGINSEQ
  if ( !childs )
    if ( !(childs = new OEHActionList()) )           OGUIERR(95)

  if ( childs->AddAction(pOEHAction) )                ERROR
  
  if ( group )
    group->addAction(pOEHAction->get_qaction());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddCauser - 




\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCauser"

void OEHAction :: AddCauser (OWidget *pOWidget )
{

  causer.AddTail(pOWidget);

}

/******************************************************************************/
/**
\brief  GetAction - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAction"

char *OEHAction :: GetAction ( )
{

  return ( action );

}

/******************************************************************************/
/**
\brief  GetName - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *OEHAction :: GetName ( )
{
  static  char   name[ID_SIZE+1] ;
  QString        object   = objectName();
  char          *name_ptr = name;
  memset(name,0,sizeof(name));
  
  if ( !object.isEmpty() )
    strncpy(name_ptr,QS2SZ(object),ID_SIZE);
  else
    name_ptr = action;
  return(name_ptr ? name_ptr : "");
}

/******************************************************************************/
/**
\brief  Is - 



\return cond - 

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Is"

logical OEHAction :: Is (char *act_names, char *loid )
{
  QString      object = objectName();
  QString      obj_names;
  logical      cond   = YES;
BEGINSEQ
  if ( loid )
    obj_names = SZ2QS(loid);
    
  if ( !action || !act_names )
  {
    if ( !action && act_names )                      ERROR
    if ( object.isNull() || obj_names.isNull() || 
         object != obj_names )                       ERROR
    LEAVESEQ
  }
  
  if ( strcmp(action,act_names) )                    ERROR
  if ( obj_names.isNull() )                          LEAVESEQ
    
  if ( object.isNull() )
    object = obj_names;
  else    
    if ( object != obj_names )                       ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsDefault - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDefault"

logical OEHAction :: IsDefault ( )
{

  return ( is_default == YES ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsDisabled - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDisabled"

logical OEHAction :: IsDisabled ( )
{

  return ( is_active && (!qaction || qaction->isEnabled()) ? NO : YES );

}

/******************************************************************************/
/**
\brief  IsGrouped - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGrouped"

logical OEHAction :: IsGrouped ( )
{

  return ( group ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsSeparated - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSeparated"

logical OEHAction :: IsSeparated ( )
{

  return ( separate );

}

/******************************************************************************/
/**
\brief  IsToggled - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsToggled"

logical OEHAction :: IsToggled ( )
{

  return ( qaction ? qaction->isChecked() : UNDEF );

}

/******************************************************************************/
/**
\brief  IsVisible - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsVisible"

logical OEHAction :: IsVisible ( )
{

  return ( qaction ? qaction->isVisible() : NO );

}

/******************************************************************************/
/**
\brief  OEHAction - Konstruktor




\param  act_names - Action name
\param  loid - Identification for an action object
\param  pQAction - 
\param  pOEH - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHAction"

     OEHAction :: OEHAction (char *act_names, char *loid, QAction *pQAction, OEH *pOEH )
                     :   qaction(pQAction),
  oeh(pOEH),
  action(NULL),
  childs(NULL),
  group(NULL),
  widget(NULL),
  causer(),
  is_default(AUTO),
  is_active(YES),
  separate(NO),
  pass(ABT_never),
  pass_info(NULL)
{
  QVariant   qvar(QVariant::UserType+1);

  if ( act_names )
    action = strdup(act_names);
  
  if ( loid )
    setObjectName(loid);

  if ( pQAction )
  {
    qvar.setValue<OEHAction *>(this);
    pQAction->setData(qvar);
    connect(pQAction,SIGNAL(triggered(bool)),
            this,    SLOT(doTriggered(bool)));
  }
oact_total++;
if ( ++oact_count > oact_max ) oact_max = oact_count;
}

/******************************************************************************/
/**
\brief  RemoveCauser - 




\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveCauser"

void OEHAction :: RemoveCauser (OWidget *pOWidget )
{

  if ( causer.Find(pOWidget) )
    causer.RemoveAt();

}

/******************************************************************************/
/**
\brief  SetActive - 




\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActive"

void OEHAction :: SetActive (logical fEnabled )
{

  if ( this )
  {
    is_active = fEnabled;
    SetVisible(fEnabled);
    SetDisabled(!fEnabled);
  }


}

/******************************************************************************/
/**
\brief  SetDefault - 




\param  def_action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefault"

void OEHAction :: SetDefault (logical def_action )
{

  if ( is_default == 255 )
    is_default = def_action;
  else
    is_default = MIN(is_default,def_action);

  if ( def_action && qaction && qaction->text().isEmpty() )
  {
    QString  text = action;
    text.remove("Entry",Qt::CaseSensitive);
    text.remove("Text",Qt::CaseSensitive);
    qaction->setText(text);
  }

}

/******************************************************************************/
/**
\brief  SetDisabled - 




\param  disabled_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisabled"

void OEHAction :: SetDisabled (logical disabled_opt )
{

  if ( qaction )
    if ( is_active || disabled_opt )
      if ( qaction->isEnabled() != !disabled_opt )
        qaction->setEnabled(!disabled_opt);

}

/******************************************************************************/
/**
\brief  SetFont - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pOFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void OEHAction :: SetFont (OFont *pOFont )
{

BEGINSEQ
  if ( !qaction )                                   ERROR
  
  if ( pOFont )
    qaction->setFont(*pOFont);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  text - 
\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void OEHAction :: SetFont (char *text, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled )
{
  OIconSet     icon(pDPixmap_normal,pDPixmap_active,
                    pDPixmap_disabled);
  SetIcon(text,&icon);

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void OEHAction :: SetFont ( )
{

  if ( action )
  {
    qaction->setIcon(OIconSet(action));
    qaction->setIconText(action);
  }


}

/******************************************************************************/
/**
\brief  SetGrouped - 




\param  group_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGrouped"

void OEHAction :: SetGrouped (logical group_opt )
{

BEGINSEQ
  if ( !qaction )                                    ERROR
  
  if ( group_opt )
  {
    if ( group )                                     LEAVESEQ
    if ( !(group = new QActionGroup(qaction->parent())) )
                                                     OGUIERR(95)
    childs->SetupGroup(group);
  }
  else
  {
    if ( !group )                                    LEAVESEQ
    delete group;
    group = NULL;
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetIcon - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  text - 
\param  pOIcon - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

void OEHAction :: SetIcon (char *text, OIconSet *pOIcon )
{

BEGINSEQ
  if ( !qaction )                                   ERROR
  
  if ( text )
    qaction->setIconText(text);
    
  if ( pOIcon )
    qaction->setIcon(*pOIcon);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  text - 
\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

void OEHAction :: SetIcon (char *text, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled )
{
  OIconSet     icon(pDPixmap_normal,pDPixmap_active,
                    pDPixmap_disabled);
  SetIcon(text,&icon);

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

void OEHAction :: SetIcon ( )
{

  if ( action )
  {
    qaction->setIcon(OIconSet(action));
    qaction->setIconText(action);
  }


}

/******************************************************************************/
/**
\brief  SetPass - 




\param  pass_opt - 
\param  pass_to - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPass"

void OEHAction :: SetPass (ActionBubbleType pass_opt, char *pass_to )
{

  if ( !(pass = pass_opt) )
    pass = ABT_never;
  
  if ( pass_info )
  {
    free(pass_info);
    pass_info = NULL;
  }

  if ( pass_to )
    pass_info = strdup(pass_to);

}

/******************************************************************************/
/**
\brief  SetSeparated - 




\param  sep_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSeparated"

void OEHAction :: SetSeparated (logical sep_opt )
{

  if ( this )
    separate = sep_opt;

}

/******************************************************************************/
/**
\brief  SetShortcut - 




\param  pOEHShortcut - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetShortcut"

void OEHAction :: SetShortcut (OEHShortcut *pOEHShortcut )
{

  if ( qaction )
  {
    qaction->setShortcut(pOEHShortcut->Shortcut());
    qaction->setShortcutContext(pOEHShortcut->ShortcutContext());
  }

}

/******************************************************************************/
/**
\brief  SetText - 




\param  text - 
\param  tip - 
\param  status_tip - 
\param  what - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void OEHAction :: SetText (char *text, char *tip, char *status_tip, char *what )
{

BEGINSEQ
  if ( !qaction )                                   LEAVESEQ
  
  if ( text )
    qaction->setText(text);
    
  if ( tip )
    qaction->setToolTip(tip);

  if ( status_tip )
    qaction->setStatusTip(status_tip);

  if ( what )
    qaction->setWhatsThis(what);

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetToggled - 




\param  toggle_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetToggled"

void OEHAction :: SetToggled (logical toggle_opt )
{

BEGINSEQ
  if ( !qaction )                                   ERROR
  
  if ( !qaction->isCheckable() )
    qaction->setCheckable(true);
    
  if ( qaction->isChecked() != (bool)toggle_opt )
    qaction->setChecked(toggle_opt);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetVisible - 




\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVisible"

void OEHAction :: SetVisible (logical fEnabled )
{

BEGINSEQ
  if ( !qaction )                                   ERROR
  
  if ( qaction->isVisible() != (bool)fEnabled )
    qaction->setVisible(fEnabled);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetWidget - 




\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWidget"

void OEHAction :: SetWidget (ODataWidget *pODataWidget )
{

  widget = pODataWidget;

}

/******************************************************************************/
/**
\brief  Setup - 



\return term - 

\param  pDAction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical OEHAction :: Setup (DAction *pDAction )
{
  logical             term = NO;
  if ( pDAction->get_short_cut() )
  {
    OEHShortcut   osc(pDAction->get_short_cut(),OEH_Widget);
    SetShortcut(&osc);
  }
  
  if ( pDAction->get_text() )
    SetText(pDAction->get_text(),pDAction->get_tool_tip(),pDAction->get_tool_tip(),pDAction->get_help());

  if ( pDAction->get_icon() )
    SetIcon(pDAction->get_text(),pDAction->get_icon());

  if ( pDAction->get_font() )
    SetFont(pDAction->get_font());

  return(term);
}

/******************************************************************************/
/**
\brief  doTriggered - 



\return term - 

\param  bChecked - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doTriggered"

logical OEHAction :: doTriggered (bool bChecked )
{

  return ( oeh->ExecuteReaction(this,NO) );

}

/******************************************************************************/
/**
\brief  ~OEHAction - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHAction"

     OEHAction :: ~OEHAction ( )
{

  if ( action )
    free (action);
  action = NULL;

  causer.Clear();

  delete childs;
  childs = NULL;
oact_count--;
}


