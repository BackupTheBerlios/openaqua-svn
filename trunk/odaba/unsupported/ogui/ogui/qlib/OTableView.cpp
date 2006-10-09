/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OTableView

\brief    TableView
          class provides a model/view implementation of a table view
          "

\date     $Date: 2006/07/31 16:45:19,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTableView"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOTableView.h>
#include  <sItemData.hpp>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOHeaderView.hpp>
#include  <sQAbstractItemView.hpp>
#include  <sOTableView.hpp>


/******************************************************************************/
/**
\brief  Activate - Activates the Class

        fills the control with data

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OTableView :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  term = OListCtl::Activate();
  
  if ( !IsTransposed() || !listCache.DefinesCollection() )
    setSelectionBehavior(SelectRows);
  else
    setSelectionBehavior(SelectColumns);
  
  if ( !ini )
  {
	  if ( Header())
	  {
	    //connect(Header(), SIGNAL(sectionClicked(int)),
	    //        this, SLOT(sortByColumn(int)));
	    //toohot 060730setModel(listCache.GetSortProxy(this));
	  }				
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate - Deactivates the Control

        and removes all filled in data

\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OTableView :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( ini && !data_only )
  {
    if ( event_filter )
      viewport()->removeEventFilter(event_filter);
  }
    
  term = OListCtl::Deactivate(data_only);
  return(term);
}

/******************************************************************************/
/**
\brief  FocusOutEvent - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusOutEvent"

int8 OTableView :: FocusOutEvent ( )
{
  int8 executed = NO;
  executed = OEHDataWidget::FocusOutEvent();
  scrollStore();
  return executed;
}

/******************************************************************************/
/**
\brief  FrameQ - 



\return pQFrame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OTableView :: FrameQ ( )
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

OHeaderView *OTableView :: Header ( )
{

  return (   IsTransposed() 
           ? (OHeaderView *)verticalHeader()
           : (OHeaderView *)horizontalHeader() );

}

/******************************************************************************/
/**
\brief  Initialize - Initializes

        Initializes the members


\param  multi_sel - 
\param  transposed - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OTableView :: Initialize (logical multi_sel, logical transposed )
{
  OHeaderView *vert_header = NULL;
  OHeaderView *hori_header = NULL;

  listCache.SetTransposed(transposed);
  
  setHorizontalHeader(hori_header = new OHeaderView(this,Qt::Horizontal,QHeaderView::Stretch));
  setVerticalHeader(vert_header = new OHeaderView(this,Qt::Vertical,QHeaderView::Interactive));
  
  if ( !IsTransposed() )
    vert_header->hide();
  else
    hori_header->Minimize();

  OListCtl::Initialize(multi_sel,NO);
  Header()->setDefaultSectionSize(22);

}

/******************************************************************************/
/**
\brief  ItemViewQ - 



\return pQAbstractItemView - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemViewQ"

QAbstractItemView *OTableView :: ItemViewQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  ListChanged - 




\param  chk_visible - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListChanged"

void OTableView :: ListChanged (logical chk_visible )
{

  if ( listCache.DefinesCollection() )
    OEHControlList::ListChanged(chk_visible);
  else
  {
    SetLastKey(&listCache);
    OEHControlData::ListChanged(chk_visible);
  }
  scrollRestore();
    



}

/******************************************************************************/
/**
\brief  OTableView - Constructor

        Initializes the base classes and the Member


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
\param  multi_sel_w - 
\param  transpose_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTableView"

     OTableView :: OTableView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical multi_sel_w, logical transpose_w )
                     : QTableView (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OListCtl (pODataWidget,oODataWidget,pODS),
settings(SZ2QS("OTableView"),this)

{

BEGINSEQ
  OGUICERR
  Initialize(multi_sel_w,transpose_w);

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

void OTableView :: OnCurrentRowChanged (ItemData *pItemData )
{



}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OTableView :: WidgetQ ( )
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

void OTableView :: currentChanged (const QModelIndex &qt_current, const QModelIndex &qt_previous )
{

BEGINSEQ
  QTableView::currentChanged(qt_current,qt_previous);
  
  if ( IsTransposed() )
  {
     if ( qt_current.column() == qt_previous.column() &&
          qt_current.parent() == qt_previous.parent() ) LEAVESEQ
  }
  else
  {
    if ( qt_current.row()    == qt_previous.row() &&
         qt_current.parent() == qt_previous.parent() )  LEAVESEQ
  }
  
  doCurrentChanged(qt_current);
  
  emit OnCurrentRowChanged(cur_item);
ENDSEQ

}

/******************************************************************************/
/**
\brief  scrollRestore - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scrollRestore"

void OTableView :: scrollRestore ( )
{

BEGINSEQ
if(!IsTransposed())                                 ERROR
verticalScrollBar()->setValue(iScrollY);


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  scrollStore - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scrollStore"

void OTableView :: scrollStore ( )
{

BEGINSEQ
if(!IsTransposed())                                 ERROR
iScrollY = verticalScrollBar()->value();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OTableView - Destructor

        Does nothing


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OTableView"

     OTableView :: ~OTableView ( )
{

  Deactivate(NO);

}


