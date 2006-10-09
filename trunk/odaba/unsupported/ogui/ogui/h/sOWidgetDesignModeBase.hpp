/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OWidgetDesignModeBase



\date     $Date: 2006/05/22 17:34:36,72 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWidgetDesignModeBase_HPP
#define   OWidgetDesignModeBase_HPP

class     OWidgetDesignModeBase;

class     OWidget;
#include  <sDMouseButtons.hpp>
class  OWidgetDesignModeBase :public QObject
{
protected  :                                                      Q_OBJECT;                                                  
protected  :         OWidget                                     *parent_owidget;                                            
protected  :         QWidget                                     *parent_qwidget;                                            
protected  :         DMouseButtons                                click_buttons;                                             

public     :
                     OWidget                                     *get_parent_owidget() { return(parent_owidget); }
                     QWidget                                     *get_parent_qwidget() { return(parent_qwidget); }
                     DMouseButtons                               &get_click_buttons() { return(click_buttons); }
public     : virtual          OGUIImpExp            logical ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical ContextMenuEvent (QContextMenuEvent *pQContextMenuEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical CreateContextMenu ( );
public     : virtual          OGUIImpExp            logical EnterEvent (QEvent *pQEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical Event (QEvent *pQEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical FocusEvent (QFocusEvent *pQFocusEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical FocusInEvent (QFocusEvent *pQFocusEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical FocusOutEvent (QFocusEvent *pQFocusEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical Initialize ( );
public     : virtual          OGUIImpExp            logical KeyEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical KeyPressEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical KeyReleaseEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical LeaveEvent (QEvent *pQEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseButtonEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseButtonPressEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseButtonReleaseEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseClickEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseDoubleClickEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseMoveEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     :                  OGUIImpExp                 OWidgetDesignModeBase (OWidget *pOWidget );
public     : virtual          OGUIImpExp            logical WheelEvent (QWheelEvent *pQWheelEvent, QWidget *event_target );
protected  : virtual          OGUIImpExp            bool eventFilter (QObject *pQObject, QEvent *pQEvent );
public     : virtual          OGUIImpExp                 ~OWidgetDesignModeBase ( );
};

#endif
