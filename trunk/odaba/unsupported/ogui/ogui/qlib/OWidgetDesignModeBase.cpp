/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OWidgetDesignModeBase

\brief    


\date     $Date: 2006/07/25 14:55:05,72 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWidgetDesignModeBase"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOWidgetDesignModeBase.h>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignModeBase.hpp>


/******************************************************************************/
/**
\brief  ChildEvent - 



\return term - 

\param  pQChildEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChildEvent"

logical OWidgetDesignModeBase :: ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target )
{

switch ( pQChildEvent->type() )
{
  case QEvent::ChildAdded:
    if ( pQChildEvent->child()->isWidgetType() )
    {
      pQChildEvent->child()->installEventFilter(this);
      ((QWidget*)pQChildEvent->child())->setEnabled(YES);
    }
  break;
}

return(NO);
}

/******************************************************************************/
/**
\brief  ContextMenuEvent - 



\return term - 

\param  pQContextMenuEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ContextMenuEvent"

logical OWidgetDesignModeBase :: ContextMenuEvent (QContextMenuEvent *pQContextMenuEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  CreateContextMenu - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContextMenu"

logical OWidgetDesignModeBase :: CreateContextMenu ( )
{


return(NO);
}

/******************************************************************************/
/**
\brief  EnterEvent - 



\return term - 

\param  pQEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnterEvent"

logical OWidgetDesignModeBase :: EnterEvent (QEvent *pQEvent, QWidget *event_target )
{

event_target->setMouseTracking(YES);

return(YES);
}

/******************************************************************************/
/**
\brief  Event - 



\return term - 

\param  pQEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Event"

logical OWidgetDesignModeBase :: Event (QEvent *pQEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQEvent->type() )
{
  case QEvent::KeyPress:
  case QEvent::KeyRelease:
    term = KeyEvent((QKeyEvent*)pQEvent, event_target);
  break;

  case QEvent::MouseButtonPress:
  case QEvent::MouseButtonRelease:
  case QEvent::MouseButtonDblClick:
  case QEvent::MouseMove:
    term = MouseEvent((QMouseEvent*)pQEvent, event_target);
  break;
  
  case QEvent::Wheel:
    term = WheelEvent((QWheelEvent*)pQEvent, event_target);
  break;
  case QEvent::ContextMenu:
    term = ContextMenuEvent((QContextMenuEvent*)pQEvent, event_target);
  break;

  case QEvent::FocusIn:
  case QEvent::FocusOut:
    term = FocusEvent((QFocusEvent*)pQEvent, event_target);
  break;
  
  case QEvent::Enter:
    term = EnterEvent(pQEvent, event_target);
  break;
  case QEvent::Leave:
    term = LeaveEvent(pQEvent, event_target);
  break;

  case QEvent::ChildAdded:
  case QEvent::ChildRemoved:
    term = ChildEvent((QChildEvent*)pQEvent, event_target);
  break;
  
  default:
    term = NO;
}

return(term);
}

/******************************************************************************/
/**
\brief  FocusEvent - 



\return term - 

\param  pQFocusEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusEvent"

logical OWidgetDesignModeBase :: FocusEvent (QFocusEvent *pQFocusEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQFocusEvent->type() )
{
  case QEvent::FocusIn:
    term = FocusInEvent(pQFocusEvent, event_target);
  break;
  case QEvent::FocusOut:
    term = FocusOutEvent(pQFocusEvent, event_target);
  break;

  default:
    term = YES;
}

return(term);
}

/******************************************************************************/
/**
\brief  FocusInEvent - 



\return term - 

\param  pQFocusEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusInEvent"

logical OWidgetDesignModeBase :: FocusInEvent (QFocusEvent *pQFocusEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  FocusOutEvent - 



\return term - 

\param  pQFocusEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusOutEvent"

logical OWidgetDesignModeBase :: FocusOutEvent (QFocusEvent *pQFocusEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OWidgetDesignModeBase :: Initialize ( )
{
logical                 term = NO;
CreateContextMenu();
return(term);
}

/******************************************************************************/
/**
\brief  KeyEvent - 



\return term - 

\param  pQKeyEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyEvent"

logical OWidgetDesignModeBase :: KeyEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQKeyEvent->type() )
{
  case QEvent::KeyPress:
    term = KeyPressEvent(pQKeyEvent, event_target);
  break;
  case QEvent::KeyRelease:
    term = KeyReleaseEvent(pQKeyEvent, event_target);
  break;
  
  default:
    term = YES;
}

return(term);
}

/******************************************************************************/
/**
\brief  KeyPressEvent - 



\return term - 

\param  pQKeyEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyPressEvent"

logical OWidgetDesignModeBase :: KeyPressEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  KeyReleaseEvent - 



\return term - 

\param  pQKeyEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyReleaseEvent"

logical OWidgetDesignModeBase :: KeyReleaseEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  LeaveEvent - 



\return term - 

\param  pQEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LeaveEvent"

logical OWidgetDesignModeBase :: LeaveEvent (QEvent *pQEvent, QWidget *event_target )
{

event_target->setMouseTracking(NO);
return(YES);
}

/******************************************************************************/
/**
\brief  MouseButtonEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseButtonEvent"

logical OWidgetDesignModeBase :: MouseButtonEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQMouseEvent->type() )
{
  case QEvent::MouseButtonPress:
    term = MouseButtonPressEvent(pQMouseEvent, event_target);
  break;
  case QEvent::MouseButtonRelease:
    term = MouseButtonReleaseEvent(pQMouseEvent, event_target);
  break;

  default:
    term = YES;
}
return(term);
}

/******************************************************************************/
/**
\brief  MouseButtonPressEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseButtonPressEvent"

logical OWidgetDesignModeBase :: MouseButtonPressEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQMouseEvent->button() )
{
  case Qt::LeftButton:
    click_buttons.SetLeft(YES);
  break;
  case Qt::MidButton:
    click_buttons.SetMiddle(YES);
  break;
  case Qt::RightButton:
    click_buttons.SetRight(YES);
  break;
}
return(term);
}

/******************************************************************************/
/**
\brief  MouseButtonReleaseEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseButtonReleaseEvent"

logical OWidgetDesignModeBase :: MouseButtonReleaseEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQMouseEvent->button() )
{
  case Qt::LeftButton:
    if ( click_buttons.Left() )
      term = MouseClickEvent(pQMouseEvent, event_target);
  break;
  case Qt::MidButton:
    if ( click_buttons.Middle() )
      term = MouseClickEvent(pQMouseEvent, event_target);
  break;
  case Qt::RightButton:
    if ( click_buttons.Right() )
      term = MouseClickEvent(pQMouseEvent, event_target);
  break;

  default:
    term = YES;
}
click_buttons.Reset();
return(term);
}

/******************************************************************************/
/**
\brief  MouseClickEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseClickEvent"

logical OWidgetDesignModeBase :: MouseClickEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  MouseDoubleClickEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseDoubleClickEvent"

logical OWidgetDesignModeBase :: MouseDoubleClickEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  MouseEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseEvent"

logical OWidgetDesignModeBase :: MouseEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQMouseEvent->type() )
{
  case QEvent::MouseButtonPress:
  case QEvent::MouseButtonRelease:
    term = MouseButtonEvent(pQMouseEvent, event_target);
  break;

  case QEvent::MouseButtonDblClick:
    term = MouseDoubleClickEvent(pQMouseEvent, event_target);
  break;

  case QEvent::MouseMove:
    term = MouseMoveEvent(pQMouseEvent, event_target);
  break;
  
  default:
    term = YES;
}

return(term);
}

/******************************************************************************/
/**
\brief  MouseMoveEvent - 



\return term - 

\param  pQMouseEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseMoveEvent"

logical OWidgetDesignModeBase :: MouseMoveEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical                 term = YES;
click_buttons.Reset();
return(term);
}

/******************************************************************************/
/**
\brief  OWidgetDesignModeBase - Konstruktor




\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWidgetDesignModeBase"

     OWidgetDesignModeBase :: OWidgetDesignModeBase (OWidget *pOWidget )
                     : QObject (),
parent_owidget(pOWidget),
parent_qwidget(pOWidget->WidgetQ()),
click_buttons()
{

BEGINSEQ
if ( !parent_qwidget )      ERROR

parent_qwidget->installEventFilter(this);
foreach (
  QWidget * child,
  parent_qwidget->findChildren<QWidget *>()
) {
  child->installEventFilter(this);
  child->setEnabled(YES);
}
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  WheelEvent - 



\return term - 

\param  pQWheelEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WheelEvent"

logical OWidgetDesignModeBase :: WheelEvent (QWheelEvent *pQWheelEvent, QWidget *event_target )
{


return(YES);
}

/******************************************************************************/
/**
\brief  eventFilter - 



\return term - 

\param  pQObject - 
\param  pQEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eventFilter"

bool OWidgetDesignModeBase :: eventFilter (QObject *pQObject, QEvent *pQEvent )
{
logical term = YES;
if ( pQObject->isWidgetType() )
  term = Event(pQEvent, (QWidget*)pQObject);

return (term);
}

/******************************************************************************/
/**
\brief  ~OWidgetDesignModeBase - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWidgetDesignModeBase"

     OWidgetDesignModeBase :: ~OWidgetDesignModeBase ( )
{

BEGINSEQ
/*
if ( !parent_qwidget )      ERROR

foreach( QWidget * child, parent_qwidget->findChildren<QWidget *>() )
  child->removeEventFilter(this);

parent_qwidget->removeEventFilter(this);
*/
RECOVER

ENDSEQ

}


