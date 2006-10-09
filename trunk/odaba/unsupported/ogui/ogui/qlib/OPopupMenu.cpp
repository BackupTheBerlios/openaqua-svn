/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OPopupMenu

\brief    Popup menu


\date     $Date: 2006/03/13 21:36:09,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPopupMenu"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOPopupMenu.hpp>


/******************************************************************************/
/**
\brief  OPopupMenu - Constructor


-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPopupMenu"

                        OPopupMenu :: OPopupMenu (ODataWidget *pODataWidget, ODataWidget *oODataWidget )
                     : QMenu(),
OMenu(pODataWidget,oODataWidget)
{

  qwidget = this;

}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPopupMenu"

                        OPopupMenu :: OPopupMenu (ODataWidget *pODataWidget )
                     : QMenu(pODataWidget->WidgetQ()),
OMenu(pODataWidget,pODataWidget)
{

  qwidget = this;

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OPopupMenu :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  ~OPopupMenu - Destructor


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPopupMenu"

                        OPopupMenu :: ~OPopupMenu ( )
{



}


