/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OMenu

\brief    


\date     $Date: 2006/03/13 21:36:07,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OMenu"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHActionList.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOMenu.hpp>


/******************************************************************************/
/**
\brief  AddAction - 


-------------------------------------------------------------------------------
\brief  i0


\param  pQAction -
\param  before_action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAction"

void OMenu :: AddAction (QAction *pQAction, QAction *before_action )
{

  if ( pQAction )
  {
    if ( before_action )
      qwidget->insertAction(before_action,pQAction);
    else
      qwidget->addAction(pQAction);
  }

}

/******************************************************************************/
/**
\brief  i01


\param  action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAction"

void OMenu :: AddAction (OEHAction *action )
{

  if ( action )
    AddAction(action->get_qaction());

}

/******************************************************************************/
/**
\brief  AddActions - 



\param  pQActionList -
\param  before_action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddActions"

void OMenu :: AddActions (QList<QAction *> *pQActionList, QAction *before_action )
{

  if ( before_action )
    qwidget->insertActions(before_action,*pQActionList);
  else
    qwidget->addActions(*pQActionList);

}

/******************************************************************************/
/**
\brief  AddMenu - 


-------------------------------------------------------------------------------
\brief  i0


\param  pQAction -
\param  pQMenu -
\param  before_action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddMenu"

void OMenu :: AddMenu (QAction *pQAction, QMenu *pQMenu, QAction *before_action )
{

  if ( pQAction )
  {
    pQAction->setMenu(pQMenu);
    AddAction(pQAction,before_action);
  }


}

/******************************************************************************/
/**
\brief  i01


\param  action -
\param  before_action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddMenu"

void OMenu :: AddMenu (OEHAction *action, QAction *before_action )
{
  OPopupMenu    *menu = NULL;
BEGINSEQ
  if ( !(menu = new OPopupMenu(this,this)) )       OGUIERR(95)
    
  menu->SetupActions(action);
  
  AddMenu(action->get_qaction(),menu,before_action);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  AddSeparator - 



\param  before_action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddSeparator"

void OMenu :: AddSeparator (QAction *before_action )
{
  QAction   *qaction = NULL;
  qaction = new QAction(qwidget);
  qaction->setSeparator(true);
  
  AddAction(qaction,before_action);

}

/******************************************************************************/
/**
\brief  OMenu - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMenu"

                        OMenu :: OMenu (ODataWidget *pODataWidget, ODataWidget *oODataWidget )
                     : bsts (),
ODataWidget(pODataWidget,oODataWidget,NO),
  qwidget(NULL),
  menu_action(NULL)
{

  qwidget = WidgetQ();

}

/******************************************************************************/
/**
\brief  SetupActions - 


\return term -

\param  action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupActions"

logical OMenu :: SetupActions (OEHAction *action )
{
  QAction       *before_action = NULL;
  OEHAction     *oeh_action    = NULL;
  OPopupMenu    *sub_menu      = NULL;
  int            count         = 0;
  int            indx0         = 0;
  logical        term          = NO;
BEGINSEQ
  if( !qwidget )                                     ERROR
  if( !action || !action->get_childs() )             ERROR
  if ( !qwidget->actions().isEmpty() )
    before_action = qwidget->actions().first();
  count = action->get_childs()->size();
  
  menu_action = action;
  qwidget->setObjectName(action->GetName());

  while ( indx0 < count )
  {
    oeh_action = action->get_childs()->at(indx0++);
    if ( oeh_action->IsSeparated() )
      AddSeparator(before_action);
    if ( !oeh_action->get_childs() || oeh_action->get_childs()->size() <= 0 )
      AddAction(oeh_action->get_qaction(),before_action);
    else if ( oeh_action->IsGrouped() )
      AddActions(&oeh_action->get_group()->actions(),before_action);
    else
      AddMenu(oeh_action,before_action);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OMenu - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OMenu"

                        OMenu :: ~OMenu ( )
{



}


