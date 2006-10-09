/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OListView

\brief    


\date     $Date: 2006/08/01 13:36:02,00 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OListView"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOListView.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOListView.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OListView :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( !ini )
  {
//  Qt4 hat anstelle eines SIGNAL currentChanged 
//             einen virtual SLOT currentChanged 
//    connect(this,SIGNAL(currentChanged(QListViewItem *)),
//            this,SLOT  (doCurrentChanged(QListViewItem *)));
  }

  term = OListCtl::Activate();
  
  if ( !ini )
  {
    if ( event_filter )
      viewport()->installEventFilter(event_filter);
 			
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate - 



\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OListView :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( ini && event_filter && !data_only )
    viewport()->removeEventFilter(event_filter);

  term = OListCtl::Deactivate(data_only);
  
  if ( ini && !data_only )
  {
//  siehe Activate
//    disconnect(this,SIGNAL(currentChanged(QListViewItem *)),
//               this,SLOT  (doCurrentChanged(QListViewItem *)));
  }

  return(term);
}

/******************************************************************************/
/**
\brief  FrameQ - 



\return pQFrame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OListView :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  Initialize - 




\param  multi_sel - 
\param  sort_order - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OListView :: Initialize (logical multi_sel, int8 sort_order, logical check_items )
{

  OListCtl::Initialize(multi_sel,sort_order,check_items);
  
  installEventFilter(this);                       // find as you type


}

/******************************************************************************/
/**
\brief  ItemViewQ - 



\return pQAbstractItemView - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemViewQ"

QAbstractItemView *OListView :: ItemViewQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  OListView - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
\param  multi_sel_w - 
\param  sort_order - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListView"

     OListView :: OListView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical multi_sel_w, int8 sort_order, logical check_items )
                     : QListView (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OListCtl (pODataWidget,oODataWidget,create_ods)
{

BEGINSEQ
  OGUICERR
  Initialize(multi_sel_w,sort_order,check_items);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
\param  multi_sel_w - 
\param  sort_order - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListView"

     OListView :: OListView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical multi_sel_w, int8 sort_order, logical check_items )
                     : QListView (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OListCtl (pODataWidget,oODataWidget,pODS)
{

BEGINSEQ
  OGUICERR 
  Initialize(multi_sel_w,sort_order,check_items);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetSpacing - 




\param  inner_dist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSpacing"

void OListView :: SetSpacing (int16 inner_dist )
{

  setSpacing(inner_dist);

}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OListView :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  currentChanged - The current cell has been changed

        This is an overloaded slot from QT


\param  qt_current - 
\param  qt_previous - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "currentChanged"

void OListView :: currentChanged (const QModelIndex &qt_current, const QModelIndex &qt_previous )
{


BEGINSEQ
  QListView::currentChanged(qt_current,qt_previous);
  
  if ( qt_current.row() == qt_previous.row() )       LEAVESEQ

  doCurrentChanged(qt_current);
  
  emit OnCurrentRowChanged(cur_item);


ENDSEQ

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

bool OListView :: eventFilter (QObject *pQObject, QEvent *pQEvent )
{
  QKeyEvent        *k         = NULL;
  ItemData         *pItemData = NULL;
  logical           bubble    = YES;
  logical           term      = false;
BEGINSEQ
/*  
  if ( !pQEvent )                                    ERROR
  
  if ( pQEvent->type() == QEvent::KeyRelease )
  {
    k = (QKeyEvent*)pQEvent;
    if ( k->modifiers() & Qt::AltModifier)
    {
      k->accept();
      term = YES; // eat this!
    }
  }
  
  if ( pQEvent->type() == QEvent::MouseButtonDblClick )
    bubble = NO;
    
  if ( pQEvent->type() == QEvent::KeyPress )
  {
    k = (QKeyEvent*)pQEvent;
    switch ( k->key() )
    {
      /// Bookmark Controls
      case Qt::Key_Right:
        if( k->modifiers() & Qt::ControlModifier){
          term = YES; bubble = NO;
          k->accept();
          BookmarkNext();
        }
        break;
      case Qt::Key_Left:
        if( k->modifiers() & Qt::ControlModifier){
          term = YES; bubble = NO;
          k->accept();
          BookmarkPrevious();
        }
        break;
      case Qt::Key_Up:
        if( k->modifiers() & Qt::ControlModifier){
          term = YES; bubble = NO;
          k->accept();
          BookmarkRemove();
        }
        break;
      case Qt::Key_Down:
        if( k->modifiers() & Qt::ControlModifier){
          term = YES; bubble = NO;
          k->accept();
          BookmarkStore();
        }
        break;
      /// TypeAhead
      case Qt::Key_Enter  : // inputscroll
      case Qt::Key_Return :
        
        if ( !inputtip )
          term = NO;
        if ( inputitem )
        {
          SetCurrentItem(inputitem);
          if( pItemData = SelectedItem() )
            doCurrentChanged(pItemData->GetQListWidgetItem());
        }
      case Qt::Key_Escape :
        InputHide();
        term = YES;
        break;
      case Qt::Key_F3     :
        term = InputUpdate(0);
        break;
      case Qt::Key_Backspace:
        term = InputUpdate(1);
        break;
      // unhandled Alphanumeric Keys
      default         : // bookmarks -> setdefaultr

        if ( !k->text().isEmpty() )
        {
          term = InputUpdate(k->text());
          bubble = NO;
        }
        break;
    }
  }
*/
RECOVER
  term = true;
ENDSEQ
  if ( bubble )
    term = QListView::eventFilter(pQObject,pQEvent);


  return term;
}

/******************************************************************************/
/**
\brief  ~OListView - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OListView"

     OListView :: ~OListView ( )
{

  Deactivate(NO);

}


