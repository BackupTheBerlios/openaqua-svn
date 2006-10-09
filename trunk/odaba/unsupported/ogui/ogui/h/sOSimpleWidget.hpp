/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OSimpleWidget

\brief    


\date     $Date: 2006/06/21 18:59:19,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSimpleWidget_HPP
#define   OSimpleWidget_HPP

class     OSimpleWidget;

class     ODControl;
class     ODS;
class     OWidgetDesignModeBase;
class     OWidgetDesignModeFactory;
#include  <sODataWidget.hpp>
class  OSimpleWidget :public QWidget,
public ODataWidget
{
protected  :         ODControl                                   *control;                                                   // 

public     :
                     ODControl                                   *get_control() { return(control); }
public     : virtual                                void DisableDesignMode ( );
public     : virtual                                OWidgetDesignModeBase *EnableDesignMode (OWidgetDesignModeFactory *dmode_factory=NULL );
public     : virtual          OGUIImpExp            ODataWidget *EventHandlingODW ( );
public     :                                             OSimpleWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                             OSimpleWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                        void PaintLayout (QPainter *pQPainter, QLayoutItem *pQLayoutItem );
public     :                                        void SetControl (ODControl *pODControl );
public     : virtual                                QWidget *WidgetQ ( );
public     :                                        void xpaintEvent (QPaintEvent *pQPaintEvent );
public     : virtual                                     ~OSimpleWidget ( );
};

#endif
