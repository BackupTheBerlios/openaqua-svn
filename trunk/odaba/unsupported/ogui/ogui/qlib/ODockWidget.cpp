/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODockWidget

\brief    ODockWidget
          ODockWidget  enables  any  Widget  to  get  dockable in any ODockArea.
          ODockWidgets can be ODockAreas

\date     $Date: 2006/06/21 18:59:36,42 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODockWidget"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mODockWidget.h>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sOEH.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOSimpleWidget.hpp>
#include  <sODockWidget.hpp>


/******************************************************************************/
/**
\brief  EventHandlingODW - 


\return pODataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventHandlingODW"

ODataWidget *ODockWidget :: EventHandlingODW ( )
{
  ODataWidget *   pODataWidget;
BEGINSEQ
  if( ! centralWidget )                             ERROR
  pODataWidget = centralWidget->EventHandlingODW();
RECOVER
  pODataWidget = NULL;
ENDSEQ
  return(pODataWidget);
}

/******************************************************************************/
/**
\brief  ODockWidget - Constructor
        pQWidget  parameter is  the constructed  activated widget that should be
        dockable


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODockWidget"

     ODockWidget :: ODockWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, ODataWidget *oODataWidget_w )
                     : ODataWidget(pODataWidget,oODataWidget,pODS),
centralWidget(oODataWidget_w),
qaction(NULL)
{
  QWidget      *pQWidget = NULL;
BEGINSEQ
  if(!oODataWidget_w)                               ERROR
  pQWidget = oODataWidget_w->WidgetQ();
  pQWidget->setParent((QWidget*)this);
  // MainWindow??? there are no DockAreas 
  WidgetQ()->layout()->addWidget(pQWidget);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  connect(this,SIGNAL(topLevelChanged(bool)),
          this,SLOT(TopLevelChanged(bool)));

  // hide the dock if the pOEHDataWidget is hidden
  if(pQWidget->isHidden()){
    hide();
    VisibilityChanged(false);
  }

  qaction = toggleViewAction();

  connect(qaction,SIGNAL(toggled(bool)),
          this,SLOT(VisibilityChanged(bool)));
          
    
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetHidden - 



\param  hidden - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHidden"

void ODockWidget :: SetHidden (logical hidden )
{

  qaction->setChecked(!hidden);

}

/******************************************************************************/
/**
\brief  TopLevelChanged - 



\param  top_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TopLevelChanged"

void ODockWidget :: TopLevelChanged (bool top_level )
{
  ODataWidget   *odw = od_control ? 
                       od_control->get_controlWidget() : NULL;
//  setFloating(top_level);
    
  if ( odw )
    odw->oeh()->GenerateEvent(top_level ? GEV_Undock : GEV_Dock,odw);



}

/******************************************************************************/
/**
\brief  VisibilityChanged - 



\param  checked - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VisibilityChanged"

void ODockWidget :: VisibilityChanged (bool checked )
{
ODataWidget *c;
BEGINSEQ
  if( !centralWidget )                              ERROR
  OSimpleWidget *s;
  s = (OSimpleWidget*)centralWidget;
  c = s->get_control()->get_controlWidget();
  if ( checked )
    c->GenerateEvent(GEV_Show);
  else
    c->GenerateEvent(GEV_Hide);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODockWidget :: WidgetQ ( )
{


  return((QDockWidget*)this);
}

/******************************************************************************/
/**
\brief  xxshow - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxshow"

void ODockWidget :: xxshow ( )
{
  ODataWidget   *odw = od_control ? 
                       od_control->get_controlWidget() : NULL;
  QDockWidget::show();
// hier wollten wir noch einmal die Grösse der DWs korrigieren. Geht aber nicht!!
//  ResetSize(odw);

}

/******************************************************************************/
/**
\brief  ~ODockWidget - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODockWidget"

     ODockWidget :: ~ODockWidget ( )
{

  if ( od_control )
    od_control->ResetDockWidget();
  od_control = NULL;

}


