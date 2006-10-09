/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    DesignerMode

\brief    


\date     $Date: 2006/07/25 14:56:04,71 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DesignerMode"

#include  <podcp8.h>
#include  <cqt.h>
#include  <cDesignModeContextMenuItems.h>
#include  <sCTX_Design.hpp>
#include  <sDesignerModeControl.hpp>
#include  <sDesignerModeFactory.hpp>
#include  <sNString.hpp>
#include  <sODControl.hpp>
#include  <sODataWidget.hpp>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignMode.hpp>
#include  <sTWidgetControl.hpp>
#include  <sDesignerMode.hpp>


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

logical DesignerMode :: ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target )
{

OWidgetDesignMode::ChildEvent(pQChildEvent, event_target);
switch ( pQChildEvent->type() )
{
  case QEvent::ChildAdded:
    if ( pQChildEvent->child()->isWidgetType() )
      ((QWidget*)pQChildEvent->child())->setAcceptDrops(NO);
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

logical DesignerMode :: ContextMenuEvent (QContextMenuEvent *pQContextMenuEvent, QWidget *event_target )
{
logical                 term = YES;
QAction                *action;
bool ok = FALSE;
QString text;
BEGINSEQ
  if ( !context_menu )
    CreateContextMenu();

  if ( !ctx_design || !control )                     ERROR

  if ( action = context_menu->exec(pQContextMenuEvent->globalPos()) )
  switch ( action->data().toInt() )
  {
    case DMC_Label:
      ctx_design->EditFieldLabel(control);
    break;
    case DMC_Edit:
      ctx_design->EditField(control);
    break;
    case DMC_Refresh:
      ctx_design->RefreshField(control);
    break;
    case DMC_ResetSize:
      ResetFieldSize();
    break;
    case DMC_Preview:
      ctx_design->Preview(!ctx_design->HasPreview());
    break;
    case DMC_ReloadControl:
      ctx_design->RefreshControl();
    break;
    case DMC_Delete:
      ctx_design->DeleteField(control);
    break;
  }

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateContextMenu - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContextMenu"

logical DesignerMode :: CreateContextMenu ( )
{
  logical                 term = NO;
  context_menu = new QMenu(NULL);
  
  context_menu->addAction(SZ2QS("&Label text"))->setData(DMC_Label);
  context_menu->addAction(SZ2QS("&Edit"))->setData(DMC_Edit);
  context_menu->addSeparator();
  context_menu->addAction(SZ2QS("&Refresh"))->setData(DMC_Refresh);
  context_menu->addAction(SZ2QS("Reset &size"))->setData(DMC_ResetSize);
  context_menu->addAction(SZ2QS("&Toggle Preview"))->setData(DMC_Preview);
  context_menu->addAction(SZ2QS("Reload &Control"))->setData(DMC_ReloadControl);
  context_menu->addSeparator();
  context_menu->addAction(SZ2QS("&Delete"))->setData(DMC_Delete);

  return(term);
}

/******************************************************************************/
/**
\brief  DesignerMode - Konstruktor




\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DesignerMode"

     DesignerMode :: DesignerMode (OWidget *pOWidget )
                     : OWidgetDesignMode(pOWidget),
control(NULL),
ctx_design(NULL),
geometry(),
cw_geometry()
{

BEGINSEQ
if ( !parent_qwidget )                             ERROR

parent_qwidget->setAcceptDrops(NO);

foreach (
  QWidget * child,
  parent_qwidget->findChildren<QWidget *>()
) child->setAcceptDrops(NO);

RECOVER

ENDSEQ

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

logical DesignerMode :: Event (QEvent *pQEvent, QWidget *event_target )
{
QDropEvent * drop   = NULL;
QWidget    * widget = NULL;
QPoint       pos;
logical      term = NO;
if ( ctx_design && ctx_design->get_control() && ctx_design->get_control()->get_complexWidget() )
  widget = ctx_design->get_control()->get_complexWidget()->WidgetQ();

switch ( pQEvent->type() )
{
  case QEvent::Show:
    InitializeGeometry();
  default:
    term = OWidgetDesignMode::Event(pQEvent, event_target);
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

logical DesignerMode :: FocusInEvent (QFocusEvent *pQFocusEvent, QWidget *event_target )
{
logical             term = YES;
if ( ctx_design && control )
  ctx_design->SelectField(control);
term = OWidgetDesignMode::FocusInEvent(pQFocusEvent, event_target);

return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DesignerMode :: Initialize ( )
{
logical                 term = NO;
OWidgetDesignMode::Initialize();
InitializeGeometry();
return(term);
}

/******************************************************************************/
/**
\brief  InitializeGeometry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeGeometry"

logical DesignerMode :: InitializeGeometry ( )
{
logical                 term = NO;
geometry = parent_qwidget->geometry();
if ( control )
  cw_geometry = control->ControlWidget()->WidgetQ()->geometry();
geometry = cw_geometry;
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

logical DesignerMode :: KeyEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQKeyEvent->key() )
{
  case Qt::Key_R:
  case Qt::Key_Tab:
    if ( ctx_design && control )
      QApplication::sendEvent(ctx_design->get_control()->get_complexWidget()->WidgetQ(), pQKeyEvent);
  default:
    term = OWidgetDesignMode::KeyEvent(pQKeyEvent, event_target);
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

logical DesignerMode :: KeyPressEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{
  logical                 term = YES;
  QPoint                  pos;
if ( 
   ( ctx_design->LoadFieldAttribute(control, "allign.arrange") == PropertyHandle("AT_Grid") )
&& ( ! pQKeyEvent->modifiers() ) // no modifier key is pressed
){
  switch ( pQKeyEvent->key() )
  {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
      pos.rx() = ctx_design->LoadFieldAttribute(control, "position.opsx").GetInt();
      pos.ry() = ctx_design->LoadFieldAttribute(control, "position.opsy").GetInt();

      if ( pQKeyEvent->key() == Qt::Key_Right )
        pos.rx()++;
      if ( pQKeyEvent->key() == Qt::Key_Left )
        pos.rx()--;
      if ( pQKeyEvent->key() == Qt::Key_Up )
        pos.ry()--;
      if ( pQKeyEvent->key() == Qt::Key_Down )
        pos.ry()++;

      ctx_design->StoreFieldAttribute(control, "position.opsx", pos.x());
      ctx_design->StoreFieldAttribute(control, "position.opsy", pos.y());
      ctx_design->RefreshField(control, YES);
        
      term = YES;
    break;
  }
} else
  term = OWidgetDesignMode::KeyPressEvent(pQKeyEvent, event_target);

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

logical DesignerMode :: KeyReleaseEvent (QKeyEvent *pQKeyEvent, QWidget *event_target )
{
logical                 term = YES;
switch ( pQKeyEvent->key() )
{
  case Qt::Key_Delete:
    if ( ctx_design && control )
    {
      if ( !pQKeyEvent->modifiers() )
        ctx_design->DeleteField(control);
    }
  break;
  case Qt::Key_Left:
  case Qt::Key_Right:
  case Qt::Key_Up:
  case Qt::Key_Down:
    if ( 
       ( ctx_design->LoadFieldAttribute(control, "allign.arrange") == PropertyHandle("AT_Grid") )
    && ( ! pQKeyEvent->modifiers() ) // no modifier key is pressed
    )
      term = YES;
    else
      term = OWidgetDesignMode::KeyReleaseEvent(pQKeyEvent, event_target);
  break;
  default:
    term = OWidgetDesignMode::KeyReleaseEvent(pQKeyEvent, event_target);
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

logical DesignerMode :: MouseButtonPressEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical             term = YES;
if ( pQMouseEvent->button() == Qt::LeftButton )
  geometry = cw_geometry;
  // parent_owidget->WidgetQ()->geometry();

term = OWidgetDesignMode::MouseButtonPressEvent(pQMouseEvent, event_target);

return(term);
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

logical DesignerMode :: MouseDoubleClickEvent (QMouseEvent *pQMouseEvent, QWidget *event_target )
{
logical             term = YES;
BEGINSEQ
if ( !ctx_design || !control )                     ERROR

ctx_design->EditFieldControl(control);
  

RECOVER
term = NO;
ENDSEQ
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

logical DesignerMode :: MoveTo (const QPoint &rcqpoint )
{
logical                 term = NO;
QPoint                  top_left;
OWidgetDesignMode::MoveTo(rcqpoint);
top_left = parent_owidget->WidgetQ()->pos();
if ( control )
  cw_geometry.moveTopLeft(top_left);

return(term);
}

/******************************************************************************/
/**
\brief  ResetFieldSize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetFieldSize"

logical DesignerMode :: ResetFieldSize ( )
{
logical                  term         = NO;
BEGINSEQ
if ( !ctx_design || !control )                     ERROR
  
ctx_design->StoreFieldAttribute(control, "size.oszhgth", 0);
ctx_design->StoreFieldAttribute(control, "size.oszwdth", 0);
ctx_design->RefreshField(control);

RECOVER
term = YES;
ENDSEQ
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

logical DesignerMode :: ResizeTo (const QSize &rcqsize )
{
logical               term = NO;
QSize                 size = parent_owidget->WidgetQ()->size();
QSize                 cw_size = cw_geometry.size();

OWidgetDesignMode::ResizeTo(rcqsize);
cw_size += rcqsize - size;
cw_geometry.setSize(cw_size);

return(term);
}

/******************************************************************************/
/**
\brief  SetContext - 



\return term - 

\param  ctx_dsgn - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

logical DesignerMode :: SetContext (CTX_Design *ctx_dsgn )
{
logical                 term = NO;
ctx_design = ctx_dsgn;
return(term);
}

/******************************************************************************/
/**
\brief  SetODControl - 



\return term - 

\param  od_control - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetODControl"

logical DesignerMode :: SetODControl (ODControl *od_control )
{


control = od_control;
InitializeGeometry();
return(NO);
}

/******************************************************************************/
/**
\brief  UpdateOWGeometry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateOWGeometry"

logical DesignerMode :: UpdateOWGeometry ( )
{
logical   term         = NO;
QRect     new_geometry = parent_owidget->WidgetQ()->geometry();
QPoint    cell_pos;
BEGINSEQ
if ( !ctx_design || !control)                      ERROR

if ( ctx_design->LoadFieldAttribute(control, "allign.arrange") == PropertyHandle("AT_Absolut") )
{
  if ( geometry.width() != cw_geometry.width() )
    ctx_design->StoreFieldAttribute(control, "size.oszwdth", cw_geometry.width());
  if ( geometry.height() != cw_geometry.height() )
    ctx_design->StoreFieldAttribute(control, "size.oszhgth", cw_geometry.height());
  if ( geometry.x() != cw_geometry.x() )
    ctx_design->StoreFieldAttribute(control, "position.opsx", cw_geometry.x());
  if ( geometry.y() != cw_geometry.y() )
    ctx_design->StoreFieldAttribute(control, "position.opsy", cw_geometry.y());
}

if ( ctx_design->LoadFieldAttribute(control, "allign.arrange") == PropertyHandle("AT_Grid") )
{ 
  if ( geometry.width() != cw_geometry.width() )
    ctx_design->StoreFieldAttribute(control, "size.oszwdth", cw_geometry.width());
  if ( geometry.height() != cw_geometry.height() )
    ctx_design->StoreFieldAttribute(control, "size.oszhgth", cw_geometry.height());

  cell_pos = ((DesignerModeControl*)control->GetParent()->GetDesignMode())->CellizePosition(new_geometry.topLeft());
  
  QWidget     * parent;
  QGridLayout * layout;
  if (
       ( parent = (QWidget*)parent_owidget->WidgetQ()->parent() )
    && ( layout = (QGridLayout*)parent->layout() )
    && ( layout->inherits("QGridLayout") )
  ){
    layout->removeWidget(parent_owidget->WidgetQ());
    layout->addWidget(parent_owidget->WidgetQ(), cell_pos.y(), cell_pos.x());
  }   
  
  ctx_design->StoreFieldAttribute(control, "position.opsx", cell_pos.x());
  ctx_design->StoreFieldAttribute(control, "position.opsy", cell_pos.y());
  
  ((DesignerModeControl*)control->GetParent()->GetDesignMode())->Refresh();
}

RECOVER
  term = YES;
ENDSEQ
  geometry = new_geometry;
  return(term);
}

/******************************************************************************/
/**
\brief  ~DesignerMode - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DesignerMode"

     DesignerMode :: ~DesignerMode ( )
{



}


