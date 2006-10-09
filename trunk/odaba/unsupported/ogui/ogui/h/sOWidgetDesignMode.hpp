/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OWidgetDesignMode

\brief    Design Mode
          The  Design Mode  provides event  filter, event  handler and a context
          menu to manipulate a widget's appearance.

          Most  of  it's  functionality  is  inside virtual methods which can be
          reimplemented for higher level (more intelligent ;) ) widgets.
          "

\date     $Date: 2006/05/22 17:47:49,71 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWidgetDesignMode_HPP
#define   OWidgetDesignMode_HPP

class     OWidgetDesignMode;

#define  FRAME_HEIGHT                              2
#define  FRAME_WIDTH                               2
class     OWidget;
#include  <cOnFramePositions.h>
#include  <sDMouseButtons.hpp>
#include  <sDPoint.hpp>
#include  <sOWidgetDesignModeBase.hpp>
class  OWidgetDesignMode :public OWidgetDesignModeBase
{
protected  :         QMenu                                       *context_menu;                                              
protected  :         QPoint                                       click_origin;                                              
protected  :         OnFramePositions                             resize_pos;                                                

public     :
public     : virtual          OGUIImpExp            void CalcResizePos (QPoint cursor_pos );
public     : virtual          OGUIImpExp            logical ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical EnterEvent (QEvent *pQEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical Event (QEvent *pQEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical FocusInEvent (QFocusEvent *pQFocusEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical FocusOutEvent (QFocusEvent *pQFocusEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical Initialize ( );
public     : virtual          OGUIImpExp            logical KeyPressEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical KeyReleaseEvent (QKeyEvent *pQKeyEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseButtonPressEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseButtonReleaseEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MouseMoveEvent (QMouseEvent *pQMouseEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical MoveBy (QPoint &qpoint );
public     : virtual          OGUIImpExp            logical MoveTo (const QPoint &rcqpoint );
public     :                  OGUIImpExp                 OWidgetDesignMode (OWidget *pOWidget );
public     : virtual          OGUIImpExp            logical PaintEvent (QPaintEvent *pQPaintEvent, QWidget *event_target );
public     : virtual          OGUIImpExp            logical Refresh ( );
public     : virtual          OGUIImpExp            logical ResizeBy (QSize &qsize );
public     : virtual          OGUIImpExp            logical ResizeTo (const QSize &rcqsize );
public     : virtual          OGUIImpExp            logical SetGeometry (const QRect &rcQRect );
public     : virtual          OGUIImpExp            logical SetMouseCursor (const QCursor &rc_qcursor, QWidget *event_target );
public     : virtual          OGUIImpExp            logical SetMouseCursor (QWidget *event_target );
public     : virtual          OGUIImpExp            logical UpdateOWColors ( );
public     : virtual          OGUIImpExp            logical UpdateOWGeometry ( );
public     : virtual          OGUIImpExp                 ~OWidgetDesignMode ( );
};

#endif
