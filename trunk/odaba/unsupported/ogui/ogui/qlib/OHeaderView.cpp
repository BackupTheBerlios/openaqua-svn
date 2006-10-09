/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OHeaderView

\brief    


\date     $Date: 2006/07/30 20:07:53,65 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OHeaderView"

#include  <pogui7.h>
#include  <sOItemHeaderDelegate.hpp>
#include  <sOListCtl.hpp>
#include  <sOHeaderView.hpp>


/******************************************************************************/
/**
\brief  Minimize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Minimize"

void OHeaderView :: Minimize ( )
{

  minimized = YES;
  size      = 1;
  
  if ( orientation() == Qt::Horizontal )
  {
    viewport()->setFixedHeight(1);
    setFixedHeight(1);
  }
  else
  {
    viewport()->setFixedWidth(1);
    setFixedWidth(1);
  }


}

/******************************************************************************/
/**
\brief  OHeaderView - 




\param  pOListCtl - 
\param  qt_orientation - 
\param  qt_resize_mode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OHeaderView"

     OHeaderView :: OHeaderView (OListCtl *pOListCtl, Qt::Orientation qt_orientation, QHeaderView::ResizeMode qt_resize_mode )
                     : QHeaderView (qt_orientation,pOListCtl ? pOListCtl->WidgetQ() : NULL),
  list_control(pOListCtl),
  size(AUTO),
  minimized(NO)
{

  setItemDelegate( new OItemHeaderDelegate(this) );

  if ( orientation() == Qt::Horizontal )
  {
    setResizeMode(qt_resize_mode); 
    setStretchLastSection(true);
    setClickable(true);
    setSortIndicatorShown(true);
  }
  else
    setClickable(false);


}

/******************************************************************************/
/**
\brief  SetSize - 




\param  siz - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void OHeaderView :: SetSize (int siz )
{

BEGINSEQ
  if ( minimized )                                   LEAVESEQ
    
  if ( (size = siz) <= 0 )                           LEAVESEQ
  
  if ( orientation() == Qt::Horizontal )
  {
    viewport()->setFixedHeight(size);
    setFixedHeight(size);
  }
  else
  {
    viewport()->setFixedWidth(size);
    setFixedWidth(size);
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  sizeHint - 



\return qsize - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sizeHint"

QSize OHeaderView :: sizeHint ( ) const
{
  QSize   qsize = QHeaderView::sizeHint();
  if ( size > 0 )
  {
    if ( orientation() == Qt::Horizontal )  
      qsize.setHeight(size);    
    else
      qsize.setWidth(size);
  }
  return(qsize);
}

/******************************************************************************/
/**
\brief  sizeHintForRowx - 



\return height - 

\param  row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sizeHintForRowx"

int OHeaderView :: sizeHintForRowx (int row ) const
{
  int     height = QHeaderView::sizeHintForRow(row);
  if ( height >= 8 && orientation() == Qt::Horizontal )
    height -= 6;
  return(height);
}

/******************************************************************************/
/**
\brief  ~OHeaderView - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OHeaderView"

     OHeaderView :: ~OHeaderView ( )
{



}


