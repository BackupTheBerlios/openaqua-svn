/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OTreeView

\brief    


\date     $Date: 2006/08/22 17:39:53,57 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTreeView"

#include  <pogui7.h>
#include  <mOTreeView.h>
#include  <sDBObjectHandle.hpp>
#include  <sItemData.hpp>
#include  <sItemTreeModel.hpp>
#include  <sODS.hpp>
#include  <sODSRegion.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOHeaderView.hpp>
#include  <sQAbstractItemView.hpp>
#include  <sOTreeView.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OTreeView :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;

  term = OListCtl::Activate();
  
  if ( !ini )
  {
	  if ( Header())
	  {
	    //connect(Header(), SIGNAL(sectionClicked(int)),
	    //        this, SLOT(sortByColumn(int)));
	    // too hot 060730 setModel(listCache.GetSortProxy(this));
	  }				
  }

  return(term);
}

/******************************************************************************/
/**
\brief  AutoExpand - 



\return term - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoExpand"

logical OTreeView :: AutoExpand (const QModelIndex &model_index )
{
  logical                 term = NO;
  if(dnd_expand_timer_index != model_index){
    if(dnd_expand_timer_id)
      killTimer(dnd_expand_timer_id);
    dnd_expand_timer_index = model_index;
    //dnd_expand_timer_id = startTimer(1000);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  AutoScroll - 



\return term - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoScroll"

logical OTreeView :: AutoScroll (const QModelIndex &model_index )
{
  logical                 term = NO;
  QModelIndex             miBefore,miAfter;
  QRect                   rBefore,rAfter;
  miBefore = indexAbove(model_index);
  miAfter  = indexBelow(model_index);
  rBefore  = visualRect(miBefore);
  rAfter   = visualRect(miAfter);
  
  if(!rAfter.isValid()||rAfter.bottom()>viewport()->height())
     dnd_scroll_timer_direction = 1;
  else if(!rBefore.isValid()||rBefore.top()<0)
     dnd_scroll_timer_direction = -1;
  else
     dnd_scroll_timer_direction = 0;
  
/*
  if(!dnd_scroll_timer_id && dnd_scroll_timer_direction)
    dnd_scroll_timer_id = startTimer(200);
 */

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

logical OTreeView :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( ini && event_filter && !data_only )
    viewport()->removeEventFilter(event_filter);
  if(input_timer_id)
    killTimer(input_timer_id);
  term = OListCtl::Deactivate(data_only);
  return(term);
}

/******************************************************************************/
/**
\brief  ExpandIndex - 



\return term - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpandIndex"

logical OTreeView :: ExpandIndex (const QModelIndex &model_index )
{
  ItemData               *item       = NULL;
  QAbstractItemModel     *item_model = model();
  logical                 term       = NO;

BEGINSEQ
  if ( !item_model )                                ERROR
  if ( !(item = ((ItemTreeModel*)item_model)->Item(model_index)) )
                                                    ERROR
  setExpanded(model_index,item->get_expanded() ? false : true);
RECOVER
  term = YES;
ENDSEQ
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

QFrame *OTreeView :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  Header - 



\return pOHeaderView - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Header"

OHeaderView *OTreeView :: Header ( )
{

  return ( (OHeaderView *)header() );

}

/******************************************************************************/
/**
\brief  Initialize - 




\param  multi_sel - 
\param  sort_order - 
\param  tree_opt - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OTreeView :: Initialize (logical multi_sel, int8 sort_order, logical tree_opt, logical check_items )
{

  setHeader(new OHeaderView(this,Qt::Horizontal,QHeaderView::Interactive));
  
  OListCtl::Initialize(multi_sel,sort_order,check_items);  
  
  setRootIsDecorated(tree_opt ? true : false);
  setSelectionBehavior(SelectRows);
  
  setDragEnabled(true);
  setDropIndicatorShown(true);
  
  installEventFilter(this);
  
  connect(this,SIGNAL(expanded(const QModelIndex &)),
          this,SLOT(slotItemExpanded(const QModelIndex &)));
           
  connect(this,SIGNAL(collapsed(const QModelIndex &)),
          this,SLOT(slotItemCollapsed(const QModelIndex &)));

}

/******************************************************************************/
/**
\brief  InputHide - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputHide"

logical OTreeView :: InputHide ( )
{
  logical term = YES;
  if(inputtip)
    delete inputtip;
  if(input_timer_id)
    killTimer(input_timer_id);
  input_timer_id = 0;
  inputtip = NULL;
  if(inputitem){
    // remove highlight
    inputitem = NULL;
    viewport()->update(lastinputitemrect);
    
  }  

  return (term);
}

/******************************************************************************/
/**
\brief  InputItemRect - 



\return itemRect - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputItemRect"

QRect OTreeView :: InputItemRect ( )
{

BEGINSEQ
  if(!inputitem)                                    ERROR
  return visualRect(inputitem->GetModelIndex());
RECOVER
  return QRect();
ENDSEQ

}

/******************************************************************************/
/**
\brief  InputScroll - 



\return term - 

\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputScroll"

logical OTreeView :: InputScroll (const QString &qscText )
{
  logical term = YES;
  QModelIndex indx = QModelIndex();
  if( qscText.length()==0 )
    return InputHide();
  if(inputitem)
    indx = inputitem->GetModelIndex();
  else
    indx = get_cur_item()?get_cur_item()->GetModelIndex():QModelIndex();
    
  ItemData *item = LocateItem(indx,qscText,NO);
  if(item){
    scrollTo(item->GetModelIndex(),QAbstractItemView::PositionAtTop);
    if(inputitem){
      // remove highlight

      inputitem = NULL;
      viewport()->update(lastinputitemrect);
    }
    // highlight
    inputitem = item;
    viewport()->update(InputItemRect());
  }
  return (term);
}

/******************************************************************************/
/**
\brief  InputShow - 



\return term - 

\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputShow"

logical OTreeView :: InputShow (const QString &qscText )
{
  logical                 term = YES;
  int                     iWidth,iHeight;
  QPalette                pal;
  if(input_timer_id)
    killTimer(input_timer_id);
  input_timer_id = 0;
  if(!inputtip){
    inputtip = new QLabel(WidgetQ());
    // make up 
    inputtip->setAutoFillBackground(true);
    inputtip->setFrameStyle(Box + Plain);
 //   inputtip->setBackgroundRole(QPalette::Light);
  }
  inputtip->setText(qscText);
  QSize   vps = maximumViewportSize();
  iWidth  = vps.width();
  iHeight = vps.height();
  inputtip->setGeometry(iWidth-100
                       ,iHeight-20
                       ,100
                       ,20);
  inputtip->show();
  input_timer_id = startTimer(5000);


  return (term);
}

/******************************************************************************/
/**
\brief  InputUpdate - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputUpdate"

logical OTreeView :: InputUpdate (const QString &qscText )
{
  logical term = YES;
  if(!inputtip)
    inputbuffer_s.truncate(0);
  inputbuffer_s.append(qscText);
  InputScroll(inputbuffer_s);
  
  return InputShow(inputbuffer_s);
  return (term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputUpdate"

logical OTreeView :: InputUpdate (int count )
{
  logical term = YES;
  inputbuffer_s.truncate(inputbuffer_s.length()-count);
  term = InputUpdate(QString());
  return(term);
}

/******************************************************************************/
/**
\brief  IsItemExpanded - 



\return cond - 

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemExpanded"

logical OTreeView :: IsItemExpanded (ItemData *pItemData )
{

  return ( isExpanded(pItemData->GetModelIndex()) );

}

/******************************************************************************/
/**
\brief  ItemViewQ - 



\return pQAbstractItemView - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemViewQ"

QAbstractItemView *OTreeView :: ItemViewQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  NextItem - 



\return pItemData - ItemData

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextItem"

ItemData *OTreeView :: NextItem (ItemData *pItemData )
{
  QModelIndex  index;  

BEGINSEQ
  if ( pItemData )
    index  = pItemData->GetModelIndex();

  index = indexBelow(index);
  if ( !index.isValid() )                             ERROR

  pItemData = listCache.Item(index);

RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  OTreeView - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
\param  multi_sel_w - 
\param  sort_order - 
\param  tree_opt - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeView"

     OTreeView :: OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical multi_sel_w, int8 sort_order, logical tree_opt, logical check_items )
                     : QTreeView (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OListCtl (pODataWidget,oODataWidget,create_ods)
,dnd_scroll_timer_id(0)
,dnd_scroll_timer_direction(0)
,dnd_expand_timer_id(0)
,dnd_expand_timer_index()
,input_timer_id(0)
,inputitem(NULL)
,inputtip(NULL)
,lastinputitemrect()
{

BEGINSEQ
  OGUICERR 
  Initialize(multi_sel_w,sort_order,tree_opt,check_items);
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
\param  tree_opt - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeView"

     OTreeView :: OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical multi_sel_w, int8 sort_order, logical tree_opt, logical check_items )
                     : QTreeView (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OListCtl (pODataWidget,oODataWidget,pODS)
,dnd_scroll_timer_id(0)
,dnd_scroll_timer_direction(0)
,dnd_expand_timer_id(0)
,dnd_expand_timer_index()
,input_timer_id(0)
,inputitem(NULL)
,inputtip(NULL)


{

BEGINSEQ
  OGUICERR  
  Initialize(multi_sel_w,sort_order,tree_opt,check_items);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OnCurrentRowChanged - 




\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnCurrentRowChanged"

void OTreeView :: OnCurrentRowChanged (ItemData *pItemData )
{



}

/******************************************************************************/
/**
\brief  PreviousItem - 



\return pItemData - ItemData

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PreviousItem"

ItemData *OTreeView :: PreviousItem (ItemData *pItemData )
{
  QModelIndex  index;  

BEGINSEQ
  if ( pItemData )
    index  = pItemData->GetModelIndex();

  index = indexAbove(index);
  if ( !index.isValid() )                             ERROR

  pItemData = listCache.Item(index);

RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  Scroll - 



\return term - 

\param  iDirection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Scroll"

logical OTreeView :: Scroll (int32 iDirection )
{
  logical                 term = NO;
  QModelIndex             mi;
  if(iDirection > 0){
    mi = indexAt( QPoint(1,viewport()->height()) );
    scrollTo(indexBelow(mi));
  }else{
    mi = indexAt( QPoint(1,1) );
    scrollTo(indexAbove(mi));
  }
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OTreeView :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  currentChanged - 




\param  qt_current - 
\param  qt_previous - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "currentChanged"

void OTreeView :: currentChanged (const QModelIndex &qt_current, const QModelIndex &qt_previous )
{

BEGINSEQ
  QTreeView::currentChanged(qt_current,qt_previous);
  
  if ( qt_current.row()    == qt_previous.row() &&
       qt_current.parent() == qt_previous.parent() ) LEAVESEQ

  doCurrentChanged(qt_current);
  
  emit OnCurrentRowChanged(cur_item);

ENDSEQ

}

/******************************************************************************/
/**
\brief  dnd_drop - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop"

logical OTreeView :: dnd_drop ( )
{
  logical   term = YES;
  QAbstractItemView::dropEvent(drop_event);
  if(drop_event->isAccepted())
    term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_end - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_end"

logical OTreeView :: dnd_drop_end ( )
{
  logical                 term = NO;

  if(dnd_scroll_timer_id)
    killTimer(dnd_scroll_timer_id);
  if(dnd_expand_timer_id)
    killTimer(dnd_expand_timer_id);
  dnd_scroll_timer_id = 0;
  dnd_scroll_timer_direction = 0; 
  dnd_expand_timer_id = 0;
  dnd_expand_timer_index = QModelIndex(); 

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_move - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_move"

logical OTreeView :: dnd_drop_move ( )
{
  logical                 term = YES;
  QModelIndex             miAt;
  QRect                   rBefore,rAfter;
BEGINSEQ
/*
  miAt = indexAt(viewport()->mapFromParent(drop_move_point));
  if(!miAt.isValid())
    if(!model()->rowCount())                            
      LEAVESEQ  // accept the drop on empty lists
    else
      ERROR
  //if(dnd_preview_index == miAt)                      LEAVESEQ
  //dnd_preview_index = miAt;
  AutoScroll(miAt);
  AutoExpand(miAt);
*/



RECOVER
  term = NO;
ENDSEQ
  return(term);
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

bool OTreeView :: eventFilter (QObject *pQObject, QEvent *pQEvent )
{
  QKeyEvent              *k      = NULL;
  logical                 bubble = YES;
  logical                 term   = NO;
  ItemData               *pItemData = NULL;
  ItemData               *pFirst    = NULL;
  QModelIndex             indx;


BEGINSEQ
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
  if ( pQEvent->type() == QEvent::FocusOut ){
    HistoryStore();
  }
  
  if ( pQEvent->type() == QEvent::MouseButtonDblClick )
    bubble = NO;
    
  if ( pQEvent->type() == QEvent::KeyPress )
  {
    k = (QKeyEvent*)pQEvent;
    switch ( k->key() )
    {
      case Qt::Key_Left:
        pItemData = GetCurrentItem();
        if(pItemData && !isExpanded(pItemData->GetModelIndex())){
          pFirst = pItemData->Parent();
          if(pFirst){
            SetCurrentItem(pFirst);
            bubble  = NO;
            term    = YES;
            k->accept();
          }
        }
        break;
      /// TypeAhead
      case Qt::Key_Enter  : // commit 
      case Qt::Key_Return :
        
        if ( !inputtip )
          term = NO;
        if ( inputitem )
        {
          SetCurrentItem(inputitem);
        }
      case Qt::Key_Escape : // cancel
        InputHide();
        term = YES;
        break;
      case Qt::Key_F3     : // next
        term = InputUpdate(0);
        break;
      case Qt::Key_Backspace: // edit
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
RECOVER
  term = YES;
ENDSEQ
  if ( bubble )
    term = QTreeView::eventFilter(pQObject,pQEvent);
  return term;
}

/******************************************************************************/
/**
\brief  paintEvent - 




\param  pQPaintEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "paintEvent"

void OTreeView :: paintEvent (QPaintEvent *pQPaintEvent )
{
  QRect r;
  QTreeView::paintEvent(pQPaintEvent);
  if(inputitem){
    QPainter p(viewport());
    r = InputItemRect();
    p.setClipping(false);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(238,225,179,128));
    p.drawRect(r);
    lastinputitemrect = r;
  }
 
  



}

/******************************************************************************/
/**
\brief  rowsAboutToBeRemoved - 




\param  mi_parent - 
\param  start_index - 
\param  end_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rowsAboutToBeRemoved"

void OTreeView :: rowsAboutToBeRemoved (const QModelIndex &mi_parent, int start_index, int end_index )
{

  if ( mi_parent.isValid() )
    setCurrentIndex(mi_parent);
    
  QTreeView::rowsAboutToBeRemoved(mi_parent,start_index,end_index);

//*** QT-BUG
// die Basisklasseninplementierung (QAbstractItemView) setzt neuen currentIndex,
// den wir erstens nicht wollen (den davor)
// was zweitens zum Absturz fuehrt, weil durch das expand des parents 
// der zu removende index wieder in die itemView-Liste hineinkommt

}

/******************************************************************************/
/**
\brief  slotItemCollapsed - 




\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemCollapsed"

void OTreeView :: slotItemCollapsed (const QModelIndex &model_index )
{
  ItemData   *item_data = listCache.Item(model_index);
BEGINSEQ
  if ( !item_data )                                  ERROR
    
  if ( !IsCurItem(item_data,NO) && IsCurItem(item_data,YES) )
    SetCurrentItem(item_data);  
  
  item_data->SetExpanded(NO);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotItemExpanded - 




\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemExpanded"

void OTreeView :: slotItemExpanded (const QModelIndex &model_index )
{

  listCache.Item(model_index)->SetExpanded(YES);

}

/******************************************************************************/
/**
\brief  timerEvent - 




\param  pQTimerEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "timerEvent"

void OTreeView :: timerEvent (QTimerEvent *pQTimerEvent )
{

  if(pQTimerEvent->timerId() == dnd_scroll_timer_id)
    if(dnd_scroll_timer_direction)
      Scroll(dnd_scroll_timer_direction);
    else{
      killTimer(dnd_scroll_timer_id);
      dnd_scroll_timer_id = 0;
    }
  if(pQTimerEvent->timerId() == dnd_expand_timer_id){
    ExpandIndex(dnd_expand_timer_index);
    killTimer(dnd_expand_timer_id);
    dnd_expand_timer_id = 0;
  }
  if(pQTimerEvent->timerId() == input_timer_id){
    killTimer(input_timer_id);
    InputHide();
  }

  QTreeView::timerEvent(pQTimerEvent);
}

/******************************************************************************/
/**
\brief  ~OTreeView - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OTreeView"

     OTreeView :: ~OTreeView ( )
{


  Deactivate(NO);


}


