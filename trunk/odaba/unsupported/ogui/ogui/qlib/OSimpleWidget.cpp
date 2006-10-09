/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OSimpleWidget

\brief    


\date     $Date: 2006/06/21 18:59:21,23 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSimpleWidget"

#include  <pogui7.h>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODataWidgetEventFilter.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sOWidgetDesignModeFactory.hpp>
#include  <sOSimpleWidget.hpp>


/******************************************************************************/
/**
\brief  DisableDesignMode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableDesignMode"

void OSimpleWidget :: DisableDesignMode ( )
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

OWidgetDesignModeBase *OSimpleWidget :: EnableDesignMode (OWidgetDesignModeFactory *dmode_factory )
{

  ODataWidget::EnableDesignMode(dmode_factory);

  setAcceptDrops(TRUE);

  return(design_mode);
}

/******************************************************************************/
/**
\brief  EventHandlingODW - 


\return pODataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventHandlingODW"

ODataWidget *OSimpleWidget :: EventHandlingODW ( )
{
  ODataWidget *   pODataWidget;
BEGINSEQ
  if ( !control || control->get_controlWidget() )   ERROR
  pODataWidget = control->get_controlWidget()->EventHandlingODW();
RECOVER
  pODataWidget = NULL;
ENDSEQ
  return(pODataWidget);
}

/******************************************************************************/
/**
\brief  OSimpleWidget - Konstruktor


-------------------------------------------------------------------------------
\brief  i0 - 


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSimpleWidget"

     OSimpleWidget :: OSimpleWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QWidget (pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget (pODataWidget,oODataWidget,create_ods),
  control(NULL)
{

  new ODataWidgetEventFilter(this);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSimpleWidget"

     OSimpleWidget :: OSimpleWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QWidget (pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget (pODataWidget,oODataWidget,pODS),
  control(NULL)
{

  new ODataWidgetEventFilter(this);

}

/******************************************************************************/
/**
\brief  PaintLayout - 



\param  pQPainter - 
\param  pQLayoutItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PaintLayout"

void OSimpleWidget :: PaintLayout (QPainter *pQPainter, QLayoutItem *pQLayoutItem )
{
  QLayout *layout = pQLayoutItem->layout();

  if (layout) 
    for (int i = 0; i < layout->count(); ++i)
      PaintLayout(pQPainter, layout->itemAt(i));
    
  pQPainter->drawRect(pQLayoutItem->geometry());


}

/******************************************************************************/
/**
\brief  SetControl - 



\param  pODControl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControl"

void OSimpleWidget :: SetControl (ODControl *pODControl )
{

  control = pODControl;

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OSimpleWidget :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  xpaintEvent - 



\param  pQPaintEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xpaintEvent"

void OSimpleWidget :: xpaintEvent (QPaintEvent *pQPaintEvent )
{
  QPainter painter(this);


  if (layout())
    PaintLayout(&painter, layout());



}

/******************************************************************************/
/**
\brief  ~OSimpleWidget - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSimpleWidget"

     OSimpleWidget :: ~OSimpleWidget ( )
{

  


}


