/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OToolButton

\brief    


\date     $Date: 2006/03/13 21:36:19,54 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OToolButton"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOIconSet.hpp>
#include  <sOToolBar.hpp>
#include  <sOToolButton.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OToolButton :: Activate ( )
{
  QIcon         *pQIcon = NULL;
  logical        term      = NO;
  SetupFont();
  
  if ( pQIcon = olayout->GetIcon() )
    setIconSet(*pQIcon);
  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate

\return term -

\param  data_only -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OToolButton :: Deactivate (logical data_only )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  OToolButton - 


-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  toggle_state -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolButton"

                        OToolButton :: OToolButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, int8 toggle_state )
                     : QToolButton (pODataWidget->WidgetQ(),NULL),
ODataWidget (pODataWidget,oODataWidget,NO)
{

  OGUIRESET
  
  setToggleButton(toggle_state > 1 ? TRUE : FALSE);
  
  connect(this,SIGNAL(clicked()),oeh(),SLOT(doClicked()));


}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
\param  riconSet -
\param  qscLabel -
\param  qscGroup -
\param  pQObject -
\param  szcSlot -
\param  pOToolBar -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolButton"

                        OToolButton :: OToolButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, const QIconSet &riconSet, const QString &qscLabel, const QString &qscGroup, QObject *pQObject, const char *szcSlot, OToolBar *pOToolBar )
                     : QToolButton (riconSet,qscLabel,qscGroup,pQObject,szcSlot,(QToolBar*)pOToolBar),
ODataWidget (pODataWidget,oODataWidget,create_ods)
{



}

/******************************************************************************/
/**
\brief  i02


\param  riconSet -
\param  qscLabel -
\param  qscGroup -
\param  pQObject -
\param  szcSlot -
\param  pOToolBar -
\param  szcName -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolButton"

                        OToolButton :: OToolButton (const QIconSet &riconSet, const QString &qscLabel, const QString &qscGroup, QObject *pQObject, const char *szcSlot, OToolBar *pOToolBar, const char *szcName )
                     : QToolButton (riconSet,qscLabel,qscGroup,pQObject,szcSlot,(QToolBar*)pOToolBar,szcName),
ODataWidget (pOToolBar->get_parent_odw()
,pOToolBar->get_owning_odw()
,pOToolBar->get_odw_ods())
{



}

/******************************************************************************/
/**
\brief  SetStandardAction - 


\return term -

\param  act_namesc - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStandardAction"

logical OToolButton :: SetStandardAction (const char *act_namesc, char *loid )
{

  return ( SetAction(act_namesc,loid,GEV_Click,this) );

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OToolButton :: WidgetQ ( )
{

  return ( this );

}


