/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OWidgetDesignMode

\brief    Design Mode
          The  Design Mode  provides event  filter, event  handler and a context
          menu to manipulate a widget's appearance.

          Most  of  it's  functionality  is  inside virtual methods which can be
          reimplemented for higher level (more intelligent ;) ) widgets.
          item  once it is a listitem -  it technicaly stays a listitem forever,
          but is not visible as one
          you  cannot change  the document  font for multiple paragraphs without
          loosing other formats (underlines and colors)
          the  size of the data in the  control is doubled even trippled because
          it now contains a lot of style data.
          == drag and drop ==
          dnd works as expected:
          from  any text source the plain text will appear at the position where
          you drop it

          there are two ways to get the image to display:
          create a local copy of the image at the disk the ogui80.dll exists:
          ogui80.dll ist in d:/dll/ogui80.dll
          "/images/logos/run.png" will be found as d:/images/logos/run.png
          "images/logos/run.png" will be found d:/dll/images/logos/run.png

\date     $Date: 2006/08/30 12:49:11,83 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWidgetDesignMode"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <cDesignModeContextMenuItems.h>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignMode.hpp>


/******************************************************************************/
/**
\brief  CalcResizePos - 




\param  cursor_pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalcResizePos"

void OWidgetDesignMode :: CalcResizePos (QPoint cursor_pos )
{
int          ra_height   = parent_qwidget->height();
int          ra_width    = parent_qwidget->width();
ra_height  = MIN(ra_height / 2, 12);
ra_width   = MIN(ra_width  / 2, 12);
cursor_pos = parent_qwidget->mapFromGlobal(cursor_pos);
resize_pos = OF_undefined;

if ( (cursor_pos.y() < parent_qwidget->rect().top() + 4) )
  resize_pos = OnFramePositions(resize_pos | OF_Top);

if ( (cursor_pos.y() > parent_qwidget->rect().bottom() - 4) )
  resize_pos = OnFramePositions(resize_pos | OF_Bottom);

if ( (cursor_pos.x() < parent_qwidget->rect().left() + 4) )
  resize_pos = OnFramePositions(resize_pos | OF_Left);
  
if ( (cursor_pos.x() > parent_qwidget->rect().right() - 4) )
  resize_pos = OnFramePositions(resize_pos | OF_Right);


}

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

logical OWidgetDesignMode :: ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target )
{

OWidgetDesignModeBase::ChildEvent(pQChildEvent, event_target);
switch ( pQChildEvent->type() )
{
  case QEvent::ChildAdded:
    if ( pQChildEvent->child()->isWidgetType() )
    {
      ((QWidget*)pQChildEvent->child())->setFocusPolicy(Qt::StrongFocus);
      ((QWidget*)pQChildEvent->child())->setMouseTracking(YES);
    }
  break;
}
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

logical OWidgetDesignMode :: EnterEvent (QEvent *pQEvent, QWidget *event_target )
{
logical                 term = NO;
SetMouseCursor(Qt::CrossCursor, event_target);
term = OWidgetDesignModeBase::EnterEvent(pQEvent, event_target);
return(term);
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

logical OWidgetDesignMode :: Event (QEvent *pQEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQEvent->type() )
{
  case QEvent::Paint:
    term = PaintEvent((QPaintEvent*) pQEvent, event_target);
  break;
  default:
    term = OWidgetDesignModeBase::Event(pQEvent, event_target);
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

logical OWidgetDesignMode :: FocusInEvent (QFocusEvent *pQFocusEvent, QWidget *event_target )
{

if ( event_target == parent_qwidget )
  Refresh();
else
  parent_qwidget->setFocus();

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

logical OWidgetDesignMode :: FocusOutEvent (QFocusEvent *pQFocusEvent, QWidget *event_target )
{

if ( event_target == parent_qwidget )
{
  parent_qwidget->releaseMouse();
  Refresh();
}

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

logical OWidgetDesignMode :: Initialize ( )
{
logical                 term = NO;
OWidgetDesignModeBase::Initialize();
  
parent_qwidget->setMinimumSize(QSize(0, 0));
parent_qwidget->setMaximumSize(QSize(4096, 4096));

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

logical OWidgetDesignMode :: KeyPressEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{
logical  term = YES;
QSize    sleft(-1,  0);
QSize    sright(+1,  0);
QSize    sup( 0, -1);
QSize    sdown( 0, +1);
QPoint   pleft(-1,  0);
QPoint   pright(+1,  0);
QPoint   pup( 0, -1);
QPoint   pdown( 0, +1);

switch ( pQKeyEvent->modifiers() )
{
  case Qt::AltModifier:
  case Qt::ControlModifier:
  break;
    
  case Qt::ShiftModifier:
    switch ( pQKeyEvent->key() )
    {
      case Qt::Key_Left:  ResizeBy(sleft);
      break;
      case Qt::Key_Right: ResizeBy(sright);
      break;
      case Qt::Key_Up:    ResizeBy(sup);
      break;
      case Qt::Key_Down:  ResizeBy(sdown);
      break;
      case Qt::Key_Tab:   term = NO;
      break;
    }
  break;
    
  default:
    switch ( pQKeyEvent->key() )
    {
      case Qt::Key_Left:  MoveBy(pleft);
      break;
      case Qt::Key_Right: MoveBy(pright);
      break;
      case Qt::Key_Up:    MoveBy(pup);
      break;
      case Qt::Key_Down:  MoveBy(pdown);
      break;
      case Qt::Key_Tab:   term = NO;
      break;
    }
}
return(term);
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

logical OWidgetDesignMode :: KeyReleaseEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{

switch ( pQKeyEvent->key() )
{
  case Qt::Key_Left:
  case Qt::Key_Right:
  case Qt::Key_Up:
  case Qt::Key_Down:
    if ( ! pQKeyEvent->isAutoRepeat() )
      UpdateOWGeometry();
  break;
}
return(YES);
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

logical OWidgetDesignMode :: MouseButtonPressEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{

parent_qwidget->setFocus();

CalcResizePos(pQMouseEvent->globalPos());
SetMouseCursor(event_target);
click_origin = pQMouseEvent->globalPos();

OWidgetDesignModeBase::MouseButtonPressEvent(pQMouseEvent, event_target);
return(YES);
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

logical OWidgetDesignMode :: MouseButtonReleaseEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{

parent_qwidget->releaseMouse();
switch ( pQMouseEvent->button() )
{
  case Qt::LeftButton:
    if ( ! click_buttons.Left() )
      UpdateOWGeometry();
  break;
}

OWidgetDesignModeBase::MouseButtonReleaseEvent(pQMouseEvent, event_target);
return(YES);
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

logical OWidgetDesignMode :: MouseMoveEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical      term  = YES;
QPoint       delta = pQMouseEvent->globalPos() - click_origin;
QPoint       pdelta;
QSize        sdelta;
OWidgetDesignModeBase::MouseMoveEvent(pQMouseEvent, event_target);

parent_qwidget->releaseMouse();

if ( pQMouseEvent->buttons() & Qt::LeftButton )
{
  if ( ! resize_pos )
  {
    MoveBy(delta);
  } else
  {
    if ( resize_pos & OF_Top )
    { 
      pdelta = QPoint(0,   delta.y());
      sdelta = QSize(0, -delta.y());
      MoveBy(pdelta);
      ResizeBy(sdelta);
    }
    if ( resize_pos & OF_Bottom )
    {
      sdelta = QSize(0, delta.y());
      ResizeBy(sdelta);
    }
    if ( resize_pos & OF_Left )
    {
      pdelta = QPoint(  delta.x(), 0);
      sdelta = QSize(-delta.x(), 0);
      MoveBy(pdelta);
      ResizeBy(sdelta);
    }
    if ( resize_pos & OF_Right ){
      sdelta = QSize(delta.x(), 0);
      ResizeBy(sdelta);
    }
  }
  click_origin = pQMouseEvent->globalPos();
}
  
if (
      parent_qwidget->hasFocus()
  && (pQMouseEvent->buttons() & Qt::MouseButtonMask)
)
  parent_qwidget->grabMouse();
else
  CalcResizePos(pQMouseEvent->globalPos());

SetMouseCursor(event_target);

  return(term);
}

/******************************************************************************/
/**
\brief  MoveBy - 



\return term - 

\param  qpoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveBy"

logical OWidgetDesignMode :: MoveBy (QPoint &qpoint )
{
logical  term = NO;
QPoint   pos  = parent_owidget->WidgetQ()->pos();
pos += qpoint;
MoveTo(pos);
return(term);
}

/******************************************************************************/
/**
\brief  MoveTo - 



\return term - 

\param  rcqpoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveTo"

logical OWidgetDesignMode :: MoveTo (const QPoint &rcqpoint )
{
logical                 term = NO;
parent_qwidget->move(rcqpoint);
return(term);
}

/******************************************************************************/
/**
\brief  OWidgetDesignMode - Konstruktor




\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWidgetDesignMode"

     OWidgetDesignMode :: OWidgetDesignMode (OWidget *pOWidget )
                     : OWidgetDesignModeBase (pOWidget),
context_menu(NULL),
click_origin(),
resize_pos()
{

if ( !parent_qwidget )
  
parent_qwidget->setFocusPolicy(Qt::StrongFocus);
parent_qwidget->setMouseTracking(YES);

foreach (
  QWidget * child,
  parent_qwidget->findChildren<QWidget *>()
) {
    child->setFocusPolicy(Qt::StrongFocus);
    child->setMouseTracking(YES);
}

}

/******************************************************************************/
/**
\brief  PaintEvent - 



\return term - 

\param  pQPaintEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PaintEvent"

logical OWidgetDesignMode :: PaintEvent (QPaintEvent *pQPaintEvent, QWidget *event_target )
{
logical                 term  = YES;
static  QPainter        paint;
static  QColor          color(0, 127, 255, 127);
event_target->removeEventFilter(this);
term = QCoreApplication::sendEvent(event_target, pQPaintEvent);
event_target->installEventFilter(this);

if ( parent_qwidget && parent_qwidget->hasFocus() )
{
  paint.begin(event_target);
//  paint.setClipping(true);
//  paint.setClipRegion(pQPaintEvent->region());
  paint.fillRect(pQPaintEvent->rect(), color);
  paint.end();
}

  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical OWidgetDesignMode :: Refresh ( )
{
logical                 term = NO;

foreach (
  QWidget * child,
  parent_qwidget->findChildren<QWidget*>()
) child->update();
parent_qwidget->update();

return(term);
}

/******************************************************************************/
/**
\brief  ResizeBy - 



\return term - 

\param  qsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResizeBy"

logical OWidgetDesignMode :: ResizeBy (QSize &qsize )
{
logical  term = NO;
QSize    size = parent_owidget->WidgetQ()->size();
size += qsize;
ResizeTo(size);
return(term);
}

/******************************************************************************/
/**
\brief  ResizeTo - 



\return term - 

\param  rcqsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResizeTo"

logical OWidgetDesignMode :: ResizeTo (const QSize &rcqsize )
{
logical                 term = NO;
parent_qwidget->resize(rcqsize);
Refresh();
return(term);
}

/******************************************************************************/
/**
\brief  SetGeometry - 



\return term - 

\param  rcQRect - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGeometry"

logical OWidgetDesignMode :: SetGeometry (const QRect &rcQRect )
{
logical                 term = NO;
parent_qwidget->setGeometry(rcQRect);
return(term);
}

/******************************************************************************/
/**
\brief  SetMouseCursor - 

        Changes  the mouse cursor  to reflect the  action that would be/is being
        performed by pressing the left mouse button.
        IMPORTANT:  This  function  relies  on  event_target. Therefore it works
        only  inside event  handling (especialy  it does  nothing if called from
        the con/destructor).

\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  rc_qcursor - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMouseCursor"

logical OWidgetDesignMode :: SetMouseCursor (const QCursor &rc_qcursor, QWidget *event_target )
{
logical                 term = NO;

if ( event_target )
  event_target->setCursor(rc_qcursor);
return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMouseCursor"

logical OWidgetDesignMode :: SetMouseCursor (QWidget *event_target )
{
  logical                 term = NO;

  switch ( resize_pos )
  {
    case OF_Top:
    case OF_Bottom:
      SetMouseCursor(Qt::SizeVerCursor, event_target);
    break;
    case OF_Left:
    case OF_Right:
      SetMouseCursor(Qt::SizeHorCursor, event_target);
    break;
    case OF_TopLeft:
    case OF_BottomRight:
      SetMouseCursor(Qt::SizeFDiagCursor, event_target);
    break;
    case OF_TopRight:
    case OF_BottomLeft:
      SetMouseCursor(Qt::SizeBDiagCursor, event_target);
    break;
    default:
      SetMouseCursor(Qt::CrossCursor, event_target);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  UpdateOWColors - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateOWColors"

logical OWidgetDesignMode :: UpdateOWColors ( )
{
logical                 term = NO;

return(term);
}

/******************************************************************************/
/**
\brief  UpdateOWGeometry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateOWGeometry"

logical OWidgetDesignMode :: UpdateOWGeometry ( )
{
logical   term     = NO;

return(term);
}

/******************************************************************************/
/**
\brief  ~OWidgetDesignMode - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWidgetDesignMode"

     OWidgetDesignMode :: ~OWidgetDesignMode ( )
{

delete context_menu;

}


