/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OWorkspace

\brief    


\date     $Date: 2006/03/13 21:36:26,15 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWorkspace"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODataWidget.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sOWidgetDesignModeFactory.hpp>
#include  <sOWorkspace.hpp>


/******************************************************************************/
/**
\brief  DisableDesignMode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableDesignMode"

void OWorkspace :: DisableDesignMode ( )
{

  ODataWidget::DisableDesignMode();

  setAcceptDrops(FALSE);

}

/******************************************************************************/
/**
\brief  EnableDesignMode - 


\return designer_mode -

\param  dmode_factory -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableDesignMode"

OWidgetDesignModeBase *OWorkspace :: EnableDesignMode (OWidgetDesignModeFactory *dmode_factory )
{

  ODataWidget::EnableDesignMode(dmode_factory);

  setAcceptDrops(TRUE);
  return(design_mode);
}

/******************************************************************************/
/**
\brief  OWorkspace - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWorkspace"

                        OWorkspace :: OWorkspace (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QWorkspace(pODataWidget ? pODataWidget->WidgetQ() : NULL),
OEHDataWidget(pODataWidget,oODataWidget,create_ods)

{



}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OWorkspace :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  ~OWorkspace - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWorkspace"

                        OWorkspace :: ~OWorkspace ( )
{



}


