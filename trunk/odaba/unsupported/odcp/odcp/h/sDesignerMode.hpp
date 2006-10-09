/********************************* Class Declaration ***************************/
/**
\package  ODCP
\class    DesignerMode



\date     $Date: 2006/05/22 17:53:32,43 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DesignerMode_HPP
#define   DesignerMode_HPP

class     DesignerMode;

class     CTX_Design;
class     ODControl;
class     ODataWidget;
class     OWidget;
#include  <sDPoint.hpp>
#include  <sOWidgetDesignMode.hpp>
#include  <sOWidgetDesignModeBase.hpp>
class  DesignerMode :protected OWidgetDesignMode
{
protected  :         ODControl                                   *control;                                                   
protected  :         CTX_Design                                  *ctx_design;                                                
protected  :         QRect                                        geometry;                                                  
protected  :         QRect                                        cw_geometry;                                               

public     :
public     : virtual          ODCPImpExp            logical ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target );
public     : virtual                                logical ContextMenuEvent (QContextMenuEvent *pQContextMenuEvent, QWidget *event_target );
public     : virtual                                logical CreateContextMenu ( );
public     :                                             DesignerMode (OWidget *pOWidget );
public     : virtual                                logical Event (QEvent *pQEvent, QWidget *event_target );
public     : virtual                                logical FocusInEvent (QFocusEvent *pQFocusEvent, QWidget *event_target );
public     : virtual          ODCPImpExp            logical Initialize ( );
public     :                                        logical InitializeGeometry ( );
public     : virtual                                logical KeyEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual                                logical KeyPressEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual                                logical KeyReleaseEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual          ODCPImpExp            logical MouseButtonPressEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          ODCPImpExp            logical MouseDoubleClickEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          ODCPImpExp            logical MoveTo (const QPoint &rcqpoint );
public     :                                        logical ResetFieldSize ( );
public     : virtual          ODCPImpExp            logical ResizeTo (const QSize &rcqsize );
public     :                                        logical SetContext (CTX_Design *ctx_dsgn );
public     :                                        logical SetODControl (ODControl *od_control );
public     : virtual                                logical UpdateOWGeometry ( );
public     : virtual                                     ~DesignerMode ( );
};

#endif
