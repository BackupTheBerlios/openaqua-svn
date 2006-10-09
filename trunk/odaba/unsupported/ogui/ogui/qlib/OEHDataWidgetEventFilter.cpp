/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEHDataWidgetEventFilter

\brief    Basic event filter for OEHDataWidget (an O-Control)
          This  event filter handles the basic events for any O-Control, such as
          focus in and out.

\date     $Date: 2006/05/22 16:47:52,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHDataWidgetEventFilter"

#include  <pogui7.h>
#include  <sOEHDataWidget.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>


/******************************************************************************/
/**
\brief  OEHDataWidgetEventFilter - Konstruktor



\param  pOEHDataWidget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHDataWidgetEventFilter"

     OEHDataWidgetEventFilter :: OEHDataWidgetEventFilter (OEHDataWidget *pOEHDataWidget )
                     : QObject (pOEHDataWidget->WidgetQ()),
  oeh_dw(pOEHDataWidget)
{
  pOEHDataWidget->WidgetQ()->installEventFilter(this);
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

bool OEHDataWidgetEventFilter :: eventFilter (QObject *pQObject, QEvent *pQEvent )
{
  OEHDataWidget    *odw     = oeh_dw;
  QObject          *qparent = parent();
  bool              term    = YES;
BEGINSEQ
  if ( odw->stscdel() )                              ERROR
//  if ( odw->IsInDesignMode() )
  if (odw->IsInTestRecordMode())
    odw->RecordTest(pQObject,pQEvent);
  
  switch ( pQEvent->type() ) 
  {
    case QEvent::DragEnter:
      term = odw->dragEnterEvent((QDragEnterEvent*)pQEvent);
      break;
    case QEvent::DragMove:
      term = odw->dragMoveEvent((QDragMoveEvent*)pQEvent);
      break;
    case QEvent::DragLeave:
      term = odw->dragLeaveEvent((QDragLeaveEvent*)pQEvent);
      break;
    case QEvent::Drop:
      term = odw->dropEvent((QDropEvent*)pQEvent);
      break;

//    case QEvent::Accel: break;
    
    case QEvent::KeyPress            :
           term = !odw->KeyEvent(((QKeyEvent*)pQEvent)->key(),
                                   ((QKeyEvent*)pQEvent)->modifiers(),
                                   NO);
           break;
    case QEvent::KeyRelease          : 
           term = !odw->KeyEvent(((QKeyEvent*)pQEvent)->key(),
                                   ((QKeyEvent*)pQEvent)->modifiers(),
                                   YES);
           break;

    case QEvent::ContextMenu         : 
           if ( term = !odw->ContextMenuEvent(pQObject,((QContextMenuEvent*)pQEvent)->x(),
                                           ((QContextMenuEvent*)pQEvent)->y()) )
             ((QContextMenuEvent*)pQEvent)->accept();
           break;
// Hier fangen wir noch nicht ab, wenn focus-out Fehler sagt und den Focus behalten möchte!!
    case QEvent::FocusIn             : 
           odw->FocusInEvent();
           term = NO;
           break;
    case QEvent::FocusOut            : 
           odw->FocusOutEvent();
           term = NO;
           break;
    case QEvent::Hide                : 
           odw->HideEvent();
           term = NO;
           break;
    case QEvent::Show                : 
           odw->ShowEvent();
           term = NO;
           break;
    case QEvent::MouseButtonPress    :
    case QEvent::MouseButtonRelease  :
           term = !odw->MouseClickEvent(((QMouseEvent*)pQEvent)->x(),((QMouseEvent*)pQEvent)->y(),1);
           break;
    case QEvent::MouseButtonDblClick :
           term = !odw->MouseClickEvent(((QMouseEvent*)pQEvent)->x(),((QMouseEvent*)pQEvent)->y(),2);
           break;
    case QEvent::MouseMove: 
           term = !odw->MouseMoveEvent(((QMouseEvent*)pQEvent)->x(),((QMouseEvent*)pQEvent)->y());
//           term = MouseEvent();
           break;
/*    
    case QEvent::Enter               : 
      term = parent_owdm->EnterEvent(pQEvent);
      break;
    case QEvent::Leave               : 
      term = parent_owdm->LeaveEvent(pQEvent);
    break;
*/
    default: term = NO;
  }

// hier darf nicht mehr auf ClassMembers zugegriffen werden, da das Objekt schon destruiert sein kann
  if ( !term && ((QObject *)odw->WidgetQ()) != qparent )
    term = odw->WidgetQ()->eventFilter(pQObject,pQEvent);
RECOVER
  term = NO;
ENDSEQ
  return(term);
}


