/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    DesignerModeControl

\brief    


\date     $Date: 2006/07/25 14:56:46,86 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DesignerModeControl"

#include  <podcp8.h>
#include  <cqt.h>
#include  <sCTX_Design.hpp>
#include  <sDMCLayoutItem.hpp>
#include  <sOWidget.hpp>
#include  <sDesignerModeControl.hpp>


/******************************************************************************/
/**
\brief  CellizePosition - Calculates the position in the controls grid layout

        Calculates  the  position  in  the  controls grid layout. If the control
        does  not use a grid to layout its children, the return value equals the
        passed parameter.

\return rQPoint - 

\param  rcQPos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CellizePosition"

QPoint DesignerModeControl :: CellizePosition (const QPoint rcQPos )
{
QPoint                    rQPoint = rcQPos;
BEGINSEQ
if ( !grid )                                       LEAVESEQ

rQPoint = QPoint(0, 0);
  
int rows   = grid->rowCount();
int cols   = grid->columnCount();
int border = grid->spacing() / 2;
for ( int i = 0; i < rows; i++ )
  for ( int j = 0; j < cols; j++ )
  {
    QRect rect      = grid->cellRect(i,j);
    rect.setTop(rect.top()-border);
    rect.setLeft(rect.left()-border);
    rect.setBottom(rect.bottom()+border);
    rect.setRight(rect.right()+border);
    if ( rect.contains(rcQPos) )
      rQPoint = QPoint(j, i);
}

ENDSEQ
return(rQPoint);
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

logical DesignerModeControl :: ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target )
{

OWidgetDesignModeBase::ChildEvent(pQChildEvent, event_target);
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
\brief  DesignerModeControl - 




\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DesignerModeControl"

     DesignerModeControl :: DesignerModeControl (OWidget *pOWidget )
                     : OWidgetDesignModeBase (pOWidget),
  ctx_design(NULL),
  client_qwidget(NULL),
  control_qwidget(NULL),
  grid(NULL),
  grid_backup(NULL),
  viewport(NULL),
  preview(NO)
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
\brief  DropEvent - 



\return term - 

\param  pQDropEvent - 
\param  event_target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DropEvent"

logical DesignerModeControl :: DropEvent (QDropEvent *pQDropEvent, QWidget *event_target )
{
QPoint       pos    = pQDropEvent->pos();

BEGINSEQ
if ( event_target != client_qwidget )
pos = client_qwidget->mapFrom(event_target, pos);

pQDropEvent->accept();
if ( pos.x() < 0 || pos.y() < 0 )   LEAVESEQ

QDropEvent my_drop(
  CellizePosition(pos),
  pQDropEvent->possibleActions(),
  pQDropEvent->mimeData(),
  pQDropEvent->mouseButtons(),
  pQDropEvent->keyboardModifiers(),
  pQDropEvent->type()
);

event_target->removeEventFilter(this);
QCoreApplication::sendEvent (event_target, &my_drop);
event_target->installEventFilter(this);

pQDropEvent->setAccepted(my_drop.isAccepted());
ENDSEQ
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

logical DesignerModeControl :: Event (QEvent *pQEvent, QWidget *event_target )
{
logical                 term = NO;
switch ( pQEvent->type() )
{
case QEvent::DragEnter:
case QEvent::DragMove:
case QEvent::DragLeave:
  term = NO;
  break;
case QEvent::Drop:
  term = DropEvent((QDropEvent*)pQEvent, event_target);
  break;
case QEvent::Paint:
  term = PaintEvent((QPaintEvent*)pQEvent, event_target);
  break;
default:
  term = OWidgetDesignModeBase::Event(pQEvent, event_target);
}
return(term);
}

/******************************************************************************/
/**
\brief  HasPreview - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasPreview"

logical DesignerModeControl :: HasPreview ( )
{


return(preview);
}

/******************************************************************************/
/**
\brief  InitGrid - 



\return size - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitGrid"

DSize DesignerModeControl :: InitGrid ( )
{
DSize                   size;
if (
     ctx_design
  && client_qwidget
  && !client_qwidget->inherits("OTab")  // we (or qt) cannot create a TAB in a grid!!
  && ( ctx_design->LoadControlAttribute("allign.hori_cell") > 0 )
  && ( ctx_design->LoadControlAttribute("allign.vert_cell") > 0 )
){
  grid = (QGridLayout*)client_qwidget->layout();
  if ( client_qwidget->inherits("QScrollArea") )
  {
    viewport = ((QScrollArea*)client_qwidget)->viewport();
    if ( viewport )
      viewport->installEventFilter(this);
  }
} else
{
  grid = NULL;
}
if ( grid )
{
  grid_backup = new QGridLayout();
  grid_backup->setSpacing(grid->spacing());

  grid->addItem(
    new DMCLayoutItem(),
    ctx_design->LoadControlAttribute("allign.vert_cell").GetInt() - 1,
    ctx_design->LoadControlAttribute("allign.hori_cell").GetInt() - 1
  );
/*
  grid->addWidget(
    new QWidget(client_qwidget),
    ctx_design->LoadControlAttribute("allign.hori_cell").GetInt() - 1,
    ctx_design->LoadControlAttribute("allign.vert_cell").GetInt() - 1
  );
*/
  int rows = grid->rowCount();
  int cols = grid->columnCount();
  for ( int i = 0; i < rows; i++ )
  for ( int j = 0; j < cols; j++ )
  {
    grid->addItem(new DMCLayoutItem(), i, j);
//    QWidget * widget = new QWidget(client_qwidget);
//    widget->setSizePolicy(QSizePolicy());
//    widget->resize(0,0);
//    grid->addWidget(widget, i, j);
  }
/*  {
    grid_backup->setRowMinimumHeight(i, grid->rowMinimumHeight(i));
    grid->setRowMinimumHeight(i, 22);
  }
  {
    grid_backup->setColumnMinimumWidth(j, grid->columnMinimumWidth(j));
    grid->setColumnMinimumWidth(j, 22);
  }
*/
}

size = Preview(NO);
return(size);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DesignerModeControl :: Initialize ( )
{
logical                 term = NO;
OWidgetDesignModeBase::Initialize();

return(term);
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

logical DesignerModeControl :: PaintEvent (QPaintEvent *pQPaintEvent, QWidget *event_target )
{
logical                 term = YES;
BEGINSEQ
event_target->removeEventFilter(this);
term = QCoreApplication::sendEvent(event_target, pQPaintEvent);
event_target->installEventFilter(this);

if ( !grid || preview || ( event_target != viewport ) )
                                                     LEAVESEQ

QPainter paint(viewport);
int rows   = grid->rowCount();
int cols   = grid->columnCount();
int border = grid->spacing() / 2;
for ( int i = 0; i < rows; i++ )
  for ( int j = 0; j < cols; j++ )
  {
    QRect rect = grid->cellRect(i,j);
    rect.setTop(rect.top() - border);
    rect.setLeft(rect.left() - border);
    rect.setBottom(rect.bottom() + border);
    rect.setRight(rect.right() + border);
    if ( rect.isValid() )
      paint.drawRect(rect);
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Preview - 



\return size - 

\param  pv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Preview"

DSize DesignerModeControl :: Preview (logical pv )
{
DSize                   size(0, 0);
static const int        edit_spacing = 12;
int                     old_spacing;
int                     new_spacing;
BEGINSEQ
preview = pv;
if ( !grid )                                       LEAVESEQ

old_spacing = grid->spacing();

if ( preview )
  new_spacing = grid_backup->spacing();
else
  new_spacing = edit_spacing;

grid->setSpacing(new_spacing);
size.Width  = (new_spacing - old_spacing) * (grid->columnCount() - 1);
size.Height = (new_spacing - old_spacing) * (grid->rowCount() - 1);

Refresh();

ENDSEQ
return(size);
}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical DesignerModeControl :: Refresh ( )
{
logical                 term = NO;
if ( grid )
{
  grid->invalidate();
  grid->activate();
}

if ( viewport )
  viewport->repaint();
  return(term);
}

/******************************************************************************/
/**
\brief  SetClientWidget - 



\return term - 

\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClientWidget"

logical DesignerModeControl :: SetClientWidget (OWidget *pOWidget )
{
logical                 term = NO;
if ( !pOWidget )
  client_qwidget = NULL;
else
  client_qwidget = pOWidget->WidgetQ();
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

logical DesignerModeControl :: SetContext (CTX_Design *ctx_dsgn )
{
logical                 term = NO;
ctx_design = ctx_dsgn;
return(term);
}

/******************************************************************************/
/**
\brief  SetControlWidget - 



\return term - 

\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControlWidget"

logical DesignerModeControl :: SetControlWidget (OWidget *pOWidget )
{
logical                 term = NO;
if ( !pOWidget )
  control_qwidget = NULL;
else
  control_qwidget = pOWidget->WidgetQ();

if ( control_qwidget )
  control_qwidget->setAcceptDrops(YES);
return(term);
}

/******************************************************************************/
/**
\brief  ~DesignerModeControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DesignerModeControl"

     DesignerModeControl :: ~DesignerModeControl ( )
{



}


