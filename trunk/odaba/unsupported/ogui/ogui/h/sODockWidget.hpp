/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODockWidget

\brief    ODockWidget
          ODockWidget  enables  any  Widget  to  get  dockable in any ODockArea.
          ODockWidgets can be ODockAreas

\date     $Date: 2006/06/21 18:59:32,74 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODockWidget_HPP
#define   ODockWidget_HPP

class     ODockWidget;

class     ODS;
class     OEHDataWidget;
#include  <sODataWidget.hpp>
class  ODockWidget :public QDockWidget,
public ODataWidget
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         ODataWidget                                 *centralWidget;                                             // 
protected  :         QAction                                     *qaction;                                                   // 

public     :
                     ODataWidget                                 *get_centralWidget() { return(centralWidget); }
                     QAction                                     *get_qaction() { return(qaction); }
public     : virtual          OGUIImpExp            ODataWidget *EventHandlingODW ( );
public     :                  OGUIImpExp                 ODockWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, ODataWidget *oODataWidget_w=NULL );
public     : virtual          OGUIImpExp            void SetHidden (logical hidden );
protected  : private slots:                         void TopLevelChanged (bool top_level );
protected  : private slots:                         void VisibilityChanged (bool checked );
public     : virtual                                QWidget *WidgetQ ( );
public     : virtual                                void xxshow ( );
public     : virtual                                     ~ODockWidget ( );
};

#endif
